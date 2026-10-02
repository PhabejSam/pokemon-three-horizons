#include "global.h"
#include "test/test.h"
#include "event_data.h"
#include "battle_setup.h"
#include "event_object_movement.h"
#include "item.h"
#include "malloc.h"
#include "overworld.h"
#include "fieldmap.h"
#include "sprite.h"
#include "script.h"
#include "field_player_avatar.h"
#include "constants/metatile_behaviors.h"
#include "constants/event_object_movement.h"
#include "three_horizons_chapter14.h"
#include "three_horizons_rematches.h"
#include "constants/three_horizons.h"
#include "constants/opponents.h"
#include "constants/maps.h"
#include "constants/event_objects.h"

#if THREE_HORIZONS
static void ResetHideout(void)
{
    InitEventData(); ClearBag(); TH13_ResetRematches();
    memset(gSaveBlock1Ptr->pcItems, 0, sizeof(gSaveBlock1Ptr->pcItems));
}

TEST("Three Horizons PT14 hideout: full key pocket leaves pickup retryable without unlocking")
{
    ResetHideout(); SetTrainerFlag(186);
    struct BagPocket *pocket = &gBagPockets[POCKET_KEY_ITEMS];
    for (u32 i = 0; i < pocket->capacity; i++)
        BagPocket_SetSlotItemIdAndCount(pocket, i, ITEM_BICYCLE, 1);
    ASSUME(!CheckBagHasSpace(ITEM_LIFT_KEY, 1));
    struct SaveBlock1 *before = Alloc(sizeof(*before)); EXPECT(before != NULL);
    memcpy(before, gSaveBlock1Ptr, sizeof(*before));
    EXPECT_EQ(TH14_TryGiveUniqueItem(ITEM_LIFT_KEY, FLAG_TH14_LIFT_KEY), TH14_GIFT_NO_ROOM);
    EXPECT_EQ(memcmp(before, gSaveBlock1Ptr, sizeof(*before)), 0);
    EXPECT(!FlagGet(FLAG_TH14_LIFT_KEY)); EXPECT(HasTrainerBeenFought(186));
    ClearTempFieldEventData();
    BagPocket_SetSlotItemIdAndCount(pocket, pocket->capacity - 1, ITEM_NONE, 0);
    EXPECT_EQ(TH14_TryGiveUniqueItem(ITEM_LIFT_KEY, FLAG_TH14_LIFT_KEY), TH14_GIFT_GIVEN);
    EXPECT(CheckBagHasItem(ITEM_LIFT_KEY, 1)); EXPECT(FlagGet(FLAG_TH14_LIFT_KEY));
    memcpy(before, gSaveBlock1Ptr, sizeof(*before));
    EXPECT_EQ(TH14_TryGiveUniqueItem(ITEM_LIFT_KEY, FLAG_TH14_LIFT_KEY), TH14_GIFT_ALREADY_OWNED);
    EXPECT_EQ(memcmp(before, gSaveBlock1Ptr, sizeof(*before)), 0);
    Free(before);
}

TEST("Three Horizons PT14 hideout: map-local readiness includes all eleven guards but no poster boss or trio")
{
    static const u8 maps[] = {28,28,28,28,28,29,30,30,31,31,31};
    static const u8 locals[] = {2,1,4,3,5,1,2,1,3,6,5};
    ResetHideout();
    for (u32 i = 0; i < ARRAY_COUNT(maps); i++)
    {
        gSaveBlock1Ptr->location.mapGroup = 76; gSaveBlock1Ptr->location.mapNum = maps[i];
        EXPECT_EQ(TH13_GetMapTrainer(locals[i]), 178 + i);
        SetTrainerFlag(178 + i); EXPECT(TH13_SetRematchReady(178 + i));
        TH13_ResetRematches(); EXPECT(HasTrainerBeenFought(178 + i));
    }
    for (u32 i = 177; i <= 191; i++)
    {
        if (i >= 178 && i <= 188) continue;
        SetTrainerFlag(i); EXPECT(!TH13_SetRematchReady(i));
    }
}

TEST("Three Horizons PT14 hideout: key spawn prerequisite never writes its delivery receipt")
{
    ResetHideout(); ResetSpriteData(); FreeAllSpritePalettes(); ResetObjectEvents();
    InitObjectEventPalettes(0);
    const struct MapHeader header = gMapHeader;
    // Exercise the real common spawn path with a controlled template. The
    // project map may not yet exist in the RED baseline; this requires no warp.
    gMapHeader = *Overworld_GetMapHeaderByGroupAndId(MAP_GROUP(MAP_TH13_ROUTE9), MAP_NUM(MAP_TH13_ROUTE9));
    gSaveBlock1Ptr->location.mapGroup = 76; gSaveBlock1Ptr->location.mapNum = 31;
    gSaveBlock1Ptr->pos.x = 4; gSaveBlock1Ptr->pos.y = 3;
    struct ObjectEventTemplate object = {.localId = 4, .graphicsId = OBJ_EVENT_GFX_ITEM_BALL,
        .x = 3, .y = 2, .elevation = 3, .movementType = MOVEMENT_TYPE_FACE_DOWN,
        .flagId = FLAG_TH14_LIFT_KEY};
    u8 rejected = TrySpawnObjectEventTemplate(&object, 31, 76, 0, 0);
    EXPECT_EQ(rejected, OBJECT_EVENTS_COUNT);
    EXPECT(!FlagGet(FLAG_TH14_LIFT_KEY));
    SetTrainerFlag(186);
    u8 id = TrySpawnObjectEventTemplate(&object, 31, 76, 0, 0);
    EXPECT_LT(id, OBJECT_EVENTS_COUNT);
    RemoveObjectEvent(&gObjectEvents[id]);
    EXPECT(!FlagGet(FLAG_TH14_LIFT_KEY));
    // Leaving the camera and returning still admits the dropped, unclaimed key.
    EXPECT_LT(TrySpawnObjectEventTemplate(&object, 31, 76, 0, 0), OBJECT_EVENTS_COUNT);
    ResetObjectEvents(); FlagSet(FLAG_TH14_LIFT_KEY);
    rejected = TrySpawnObjectEventTemplate(&object, 31, 76, 0, 0);
    EXPECT_EQ(rejected, OBJECT_EVENTS_COUNT);
    FlagClear(FLAG_TH14_LIFT_KEY); ClearTrainerFlag(186);
    // Identical local IDs on an upstream map must not inherit the TH gate.
    gSaveBlock1Ptr->location.mapGroup = 75; gSaveBlock1Ptr->location.mapNum = 94;
    EXPECT_LT(TrySpawnObjectEventTemplate(&object, 94, 75, 0, 0), OBJECT_EVENTS_COUNT);
    ResetObjectEvents();
    gSaveBlock1Ptr->location.mapGroup = 0; gSaveBlock1Ptr->location.mapNum = 0;
    EXPECT_LT(TrySpawnObjectEventTemplate(&object, 0, 0, 0, 0), OBJECT_EVENTS_COUNT);
    gMapHeader = header;
}

TEST("Three Horizons PT14 hideout: all lift destinations cancel and missing key preserve bounded return")
{
    ResetHideout();
    const u16 floors[] = {MAP_TH14_ROCKET_HIDEOUT_B1F, MAP_TH14_ROCKET_HIDEOUT_B2F, MAP_TH14_ROCKET_HIDEOUT_B4F};
    const u8 display[] = {3, 2, 0}, xs[] = {24, 28, 20}, ys[] = {25, 16, 23};
    struct WarpData original = gSaveBlock1Ptr->dynamicWarp;
    VarSet(VAR_FARAWAY_ISLAND_STEP_COUNTER, 73);
    for (u32 from = 0; from < 3; from++)
    {
        SetDynamicWarpWithCoords(0, 76, MAP_NUM(floors[from]), -1, xs[from], ys[from]);
        EXPECT_EQ(TH14_GetHideoutFloor(), display[from]);
        struct WarpData before = gSaveBlock1Ptr->dynamicWarp;
        for (u32 choice = 0; choice < 3; choice++)
        {
            EXPECT(!TH14_SelectHideoutFloor(choice));
            EXPECT_EQ(memcmp(&before, &gSaveBlock1Ptr->dynamicWarp, sizeof(before)), 0);
        }
        EXPECT(AddBagItem(ITEM_LIFT_KEY, 1));
        const u16 invalid[] = {3, 127, 255, 256, 65535};
        for (u32 i = 0; i < ARRAY_COUNT(invalid); i++)
        {
            EXPECT(!TH14_SelectHideoutFloor(invalid[i]));
            EXPECT_EQ(memcmp(&before, &gSaveBlock1Ptr->dynamicWarp, sizeof(before)), 0);
        }
        for (u32 to = 0; to < 3; to++)
        {
            gSaveBlock1Ptr->dynamicWarp = before;
            gSpecialVar_0x8004 = to;
            EXPECT(TH14_ScriptSelectHideoutFloor());
            EXPECT_EQ(gSpecialVar_0x8005, display[from]);
            EXPECT_EQ(gSpecialVar_0x8006, display[to]);
            EXPECT_EQ(TH14_GetHideoutFloor(), display[to]);
            EXPECT_EQ(gSaveBlock1Ptr->dynamicWarp.mapGroup, 76);
            EXPECT_EQ(gSaveBlock1Ptr->dynamicWarp.mapNum, MAP_NUM(floors[to]));
            EXPECT_EQ(gSaveBlock1Ptr->dynamicWarp.warpId, -1);
            EXPECT_EQ(gSaveBlock1Ptr->dynamicWarp.x, xs[to]);
            EXPECT_EQ(gSaveBlock1Ptr->dynamicWarp.y, ys[to]);
            EXPECT_EQ(VarGet(VAR_FARAWAY_ISLAND_STEP_COUNTER), 73);
        }
        EXPECT(RemoveBagItem(ITEM_LIFT_KEY, 1));
    }
    SetDynamicWarpWithCoords(0, 75, 31, -1, 1, 1);
    EXPECT_EQ(TH14_GetHideoutFloor(), TH14_INVALID_FLOOR);
    EXPECT(AddBagItem(ITEM_LIFT_KEY, 1));
    struct WarpData foreign = gSaveBlock1Ptr->dynamicWarp;
    EXPECT(!TH14_SelectHideoutFloor(0));
    EXPECT_EQ(memcmp(&foreign, &gSaveBlock1Ptr->dynamicWarp, sizeof(foreign)), 0);
    gSaveBlock1Ptr->dynamicWarp = original;
}

extern const u8 TH14_RocketHideout_B1F_OnLoad[], TH14_RocketHideout_B4F_OnLoad[];
extern const u8 TH14_HideoutPoster_OnLoad[], TH14_HideoutElevator_CheckReturn[];
static void LoadHideout(u16 map)
{
    gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(map);
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(map);
    gMapHeader = *Overworld_GetMapHeaderByGroupAndId(MAP_GROUP(map), MAP_NUM(map));
    LoadObjEventTemplatesFromHeader(); InitMap();
}

TEST("Three Horizons PT14 hideout: real load scripts recompute poster and both doors after reload")
{
    ResetHideout();
    const struct MapHeader header = gMapHeader;
    const struct BackupMapLayout layout = gBackupMapLayout;
    LoadHideout(MAP_TH14_CELADON_CITY_GAME_CORNER);
    RunScriptImmediately(TH14_HideoutPoster_OnLoad);
    u16 closed = MapGridGetMetatileIdAt(15 + MAP_OFFSET, 2 + MAP_OFFSET);
    SetTrainerFlag(TRAINER_TH14_GAME_CORNER_GRUNT);
    RunScriptImmediately(TH14_HideoutPoster_OnLoad);
    EXPECT_EQ(MapGridGetMetatileIdAt(15 + MAP_OFFSET, 2 + MAP_OFFSET), closed);
    FlagSet(FLAG_TH14_HIDEOUT_POSTER); ClearTempFieldEventData();
    RunScriptImmediately(TH14_HideoutPoster_OnLoad);
    EXPECT_NE(MapGridGetMetatileIdAt(15 + MAP_OFFSET, 2 + MAP_OFFSET), closed);
    EXPECT_EQ(MapGridGetCollisionAt(15 + MAP_OFFSET, 2 + MAP_OFFSET), 0);
    for (u32 won = 0; won < 2; won++)
    {
        LoadHideout(MAP_TH14_ROCKET_HIDEOUT_B1F);
        if (won) SetTrainerFlag(TRAINER_TH14_HIDEOUT_B1F_GRUNT5);
        RunScriptImmediately(TH14_RocketHideout_B1F_OnLoad);
        EXPECT_EQ(MapGridGetCollisionAt(20 + MAP_OFFSET, 19 + MAP_OFFSET) != 0, !won);
    }
    for (u32 mask = 0; mask < 4; mask++)
    {
        ClearTrainerFlag(TRAINER_TH14_HIDEOUT_B4F_GRUNT2);
        ClearTrainerFlag(TRAINER_TH14_HIDEOUT_B4F_GRUNT3);
        if (mask & 1) SetTrainerFlag(TRAINER_TH14_HIDEOUT_B4F_GRUNT2);
        if (mask & 2) SetTrainerFlag(TRAINER_TH14_HIDEOUT_B4F_GRUNT3);
        for (u32 reload = 0; reload < 2; reload++)
        {
            ClearTempFieldEventData(); LoadHideout(MAP_TH14_ROCKET_HIDEOUT_B4F);
            RunScriptImmediately(TH14_RocketHideout_B4F_OnLoad);
            EXPECT_EQ(MapGridGetCollisionAt(17 + MAP_OFFSET, 12 + MAP_OFFSET) != 0, mask != 3);
            EXPECT(!FlagGet(FLAG_TH14_LIFT_KEY));
            EXPECT(!FlagGet(FLAG_TH14_SILPH_SCOPE));
        }
    }
    gMapHeader = header; gBackupMapLayout = layout;
}

TEST("Three Horizons PT14 hideout: lift exit remains safe even without key or after invalid return")
{
    ResetHideout();
    const struct WarpData original = gSaveBlock1Ptr->dynamicWarp;
    SetDynamicWarpWithCoords(0, 76, 31, -1, 20, 23);
    struct WarpData before = gSaveBlock1Ptr->dynamicWarp;
    RunScriptImmediately(TH14_HideoutElevator_CheckReturn);
    EXPECT_EQ(memcmp(&before, &gSaveBlock1Ptr->dynamicWarp, sizeof(before)), 0);
    EXPECT_EQ(TH14_GetHideoutFloor(), 0); // B4F must never be mistaken for invalid.
    SetDynamicWarpWithCoords(0, -1, -1, -1, -1, -1);
    RunScriptImmediately(TH14_HideoutElevator_CheckReturn);
    EXPECT_EQ(TH14_GetHideoutFloor(), 3);
    EXPECT_EQ(gSaveBlock1Ptr->dynamicWarp.x, 24);
    EXPECT_EQ(gSaveBlock1Ptr->dynamicWarp.y, 25);
    EXPECT(!CheckBagHasItem(ITEM_LIFT_KEY, 1)); EXPECT(!FlagGet(FLAG_TH14_LIFT_KEY));
    gSaveBlock1Ptr->dynamicWarp = original;
}

TEST("Three Horizons PT14 hideout: native stop tiles clear spinning lock copy movement and follower invisibility")
{
    const struct PlayerAvatar avatar = gPlayerAvatar;
    const struct ObjectEvent object = gObjectEvents[0];
    const u8 spins[] = {MB_SPIN_RIGHT, MB_SPIN_LEFT, MB_SPIN_UP, MB_SPIN_DOWN};
    for (u32 i = 0; i < ARRAY_COUNT(spins); i++)
    {
        memset(&gPlayerAvatar, 0, sizeof(gPlayerAvatar));
        memset(&gObjectEvents[0], 0, sizeof(gObjectEvents[0]));
        gPlayerAvatar.flags = PLAYER_AVATAR_FLAG_FORCED_MOVE;
        gPlayerAvatar.lastSpinTile = spins[i];
        gObjectEvents[0].currentMetatileBehavior = spins[i];
        gObjectEvents[0].facingDirectionLocked = TRUE;
        gObjectEvents[0].facingDirection = DIR_SOUTH;
        gObjectEvents[0].playerCopyableMovement = COPY_MOVE_WALK;
        EXPECT(!IsFollowerVisible());
        gObjectEvents[0].currentMetatileBehavior = MB_STOP_SPINNING;
        EXPECT(!TryDoMetatileBehaviorForcedMovement());
        EXPECT(!(gPlayerAvatar.flags & PLAYER_AVATAR_FLAG_FORCED_MOVE));
        EXPECT(!gObjectEvents[0].facingDirectionLocked);
        EXPECT(gObjectEvents[0].enableAnim);
        EXPECT_EQ(gObjectEvents[0].playerCopyableMovement, COPY_MOVE_NONE);
        EXPECT(IsFollowerVisible());
    }
    gPlayerAvatar = avatar; gObjectEvents[0] = object;
}

#endif
