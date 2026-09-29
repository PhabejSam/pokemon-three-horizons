#include "global.h"
#include "test/test.h"
#include "event_data.h"
#include "field_control_avatar.h"
#include "fieldmap.h"
#include "item.h"
#include "overworld.h"
#include "script.h"
#include "three_horizons.h"
#include "load_save.h"
#include "constants/maps.h"
#include "constants/script_commands.h"
#include "constants/three_horizons.h"

#if THREE_HORIZONS
extern const u8 TH12_Captain_Talk[];

TEST("Three Horizons playtest13 ship final exit warns before departure")
{
    u32 ready;
    PARAMETRIZE { ready = 0; }
    PARAMETRIZE { ready = 1; }
    PARAMETRIZE { ready = 2; }
    PARAMETRIZE { ready = 3; }
    PARAMETRIZE { ready = 4; }
    PARAMETRIZE { ready = 5; }
    PARAMETRIZE { ready = 6; }
    PARAMETRIZE { ready = 7; }
    const struct MapHeader header = gMapHeader;
    const struct PlayerAvatar avatar = gPlayerAvatar;
    const struct ObjectEvent object = gObjectEvents[0];
    InitEventData();
    ClearBag();
    if (ready & 1) FlagSet(FLAG_TH12_SHIP_RIVAL);
    if (ready & 2) FlagSet(FLAG_TH12_CUT);
    if (ready & 4) EXPECT(AddBagItem(ITEM_HM01, 1));
    EXPECT(AddBagItem(ITEM_SS_TICKET, 1));
    gMapHeader = *Overworld_GetMapHeaderByGroupAndId(MAP_GROUP(MAP_TH12_SSANNE_EXTERIOR), MAP_NUM(MAP_TH12_SSANNE_EXTERIOR));
    gPlayerAvatar.objectEventId = 0;
    for (u32 x = 31; x <= 33; x++)
    {
        struct MapPosition pos = {.x = x + MAP_OFFSET, .y = 6 + MAP_OFFSET, .elevation = 3};
        const u8 *script = GetCoordEventScriptAtMapPosition(&pos);
        EXPECT(script != NULL);
        if (script == NULL) continue;
        for (u32 dir = DIR_SOUTH; dir <= DIR_EAST; dir++)
        {
            gObjectEvents[0].facingDirection = dir;
            EXPECT_EQ(Script_HasNoEffect(script), ready != 7 || dir != DIR_NORTH);
            EXPECT(!FlagGet(FLAG_TH13_SHIP_DEPARTED));
            EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_SS_TICKET), 1);
            EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_HM01), !!(ready & 4));
        }
    }
    gMapHeader = header;
    gPlayerAvatar = avatar;
    gObjectEvents[0] = object;
    ClearBag();
    InitEventData();
}

TEST("Three Horizons playtest13 ship P12 saves stay aboard until an accepted exit")
{
    bool32 captain;
    PARAMETRIZE { captain = FALSE; }
    PARAMETRIZE { captain = TRUE; }
    const struct WarpData location = gSaveBlock1Ptr->location;
    for (u32 map = MAP_NUM(MAP_TH12_SSANNE_1F_CORRIDOR); map <= MAP_NUM(MAP_TH12_SSANNE_KITCHEN); map++)
    {
        InitEventData();
        ClearBag();
        VarSet(VAR_TH_CLOCK_DISPLAY_HI, TH_STATE_VERSION_12);
        gSaveBlock1Ptr->location = (struct WarpData){.mapGroup = MAP_GROUP(MAP_TH12_SSANNE_EXTERIOR), .mapNum = map, .warpId = -1, .x = 3, .y = 4};
        FlagSet(FLAG_TH12_SHIP_RIVAL);
        if (captain) { FlagSet(FLAG_TH12_CUT); EXPECT(AddBagItem(ITEM_HM01, 1)); }
        FlagSet(FLAG_TH13_SHIP_DEPARTED); // old reserved bits do not prove departure
        TH_MigrateSaveState();
        EXPECT_EQ(gSaveBlock1Ptr->location.mapNum, map);
        EXPECT_EQ(gSaveBlock1Ptr->location.x, 3);
        EXPECT_EQ(gSaveBlock1Ptr->location.y, 4);
        EXPECT(!FlagGet(FLAG_TH13_SHIP_DEPARTED));
        EXPECT_EQ(FlagGet(FLAG_TH12_CUT), captain);
        EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_HM01), captain);
    }
    gSaveBlock1Ptr->location = location;
    ClearBag();
    InitEventData();
}

TEST("Three Horizons playtest13 ship departed-inside Continue recovers to safe dock")
{
    const struct WarpData location = gSaveBlock1Ptr->location;
    const struct Coords16 pos = gSaveBlock1Ptr->pos;
    const u16 layout = gSaveBlock1Ptr->mapLayoutId;
    const u8 warpFlags = gSaveBlock2Ptr->specialSaveWarpFlags;
    for (u32 map = MAP_NUM(MAP_TH12_SSANNE_1F_CORRIDOR); map <= MAP_NUM(MAP_TH12_SSANNE_KITCHEN); map++)
    {
        InitEventData();
        VarSet(VAR_TH_CLOCK_DISPLAY_HI, TH_STATE_VERSION_13);
        FlagSet(FLAG_TH13_SHIP_DEPARTED);
        gSaveBlock1Ptr->location = (struct WarpData){.mapGroup = MAP_GROUP(MAP_TH12_SSANNE_EXTERIOR), .mapNum = map, .warpId = -1, .x = 3, .y = 4};
        SetContinueGameWarpStatus();
        TH_MigrateSaveState();
        EXPECT_EQ(gSaveBlock1Ptr->location.mapGroup, MAP_GROUP(MAP_TH12_VERMILION_CITY));
        EXPECT_EQ(gSaveBlock1Ptr->location.mapNum, MAP_NUM(MAP_TH12_VERMILION_CITY));
        EXPECT_EQ(gSaveBlock1Ptr->location.warpId, -1);
        EXPECT_EQ(gSaveBlock1Ptr->pos.x, 23);
        EXPECT_EQ(gSaveBlock1Ptr->pos.y, 32);
        EXPECT_EQ(gSaveBlock1Ptr->mapLayoutId, Overworld_GetMapHeaderByGroupAndId(MAP_GROUP(MAP_TH12_VERMILION_CITY), MAP_NUM(MAP_TH12_VERMILION_CITY))->mapLayoutId);
        EXPECT(!UseContinueGameWarp());
        EXPECT(FlagGet(FLAG_TH13_SHIP_DEPARTED));
    }
    gSaveBlock1Ptr->location = location;
    gSaveBlock1Ptr->pos = pos;
    gSaveBlock1Ptr->mapLayoutId = layout;
    gSaveBlock2Ptr->specialSaveWarpFlags = warpFlags;
    InitEventData();
}

TEST("Three Horizons playtest13 ship captain remains seasick before help")
{
    bool32 rivalBeaten;
    PARAMETRIZE { rivalBeaten = FALSE; }
    PARAMETRIZE { rivalBeaten = TRUE; }
    struct ScriptContext ctx;
    InitEventData();
    ClearBag();
    if (rivalBeaten) FlagSet(FLAG_TH12_SHIP_RIVAL);
    EXPECT_EQ(TH12_Captain_Talk[0], SCR_OP_LOCK);
    EXPECT(RunScriptImmediatelyUntilEffect(SCREFF_V1 | SCREFF_ANY, TH12_Captain_Talk + 1, &ctx));
    // The first visible action must not turn the sick captain from his bin.
    EXPECT_NE(*ctx.scriptPtr, SCR_OP_FACEPLAYER);
    EXPECT(!FlagGet(FLAG_TH12_CUT));
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_HM01), 0);
}

TEST("Three Horizons playtest13 ship boarding requires ticket inspection in every lane")
{
    bool32 ticket, departed;
    PARAMETRIZE { ticket = TRUE; departed = FALSE; }
    PARAMETRIZE { ticket = FALSE; departed = FALSE; }
    PARAMETRIZE { ticket = FALSE; departed = TRUE; }
    PARAMETRIZE { ticket = TRUE; departed = TRUE; }
    const struct MapHeader saved = gMapHeader;
    const struct PlayerAvatar avatar = gPlayerAvatar;
    const struct ObjectEvent object = gObjectEvents[0];
    InitEventData();
    ClearBag();
    if (ticket) EXPECT(AddBagItem(ITEM_SS_TICKET, 1));
    if (departed) FlagSet(FLAG_TH13_SHIP_DEPARTED);
    gMapHeader = *Overworld_GetMapHeaderByGroupAndId(MAP_GROUP(MAP_TH12_VERMILION_CITY), MAP_NUM(MAP_TH12_VERMILION_CITY));
    gPlayerAvatar.objectEventId = 0;
    for (u32 x = 22; x <= 24; x++)
    {
        struct MapPosition pos = {.x = x + MAP_OFFSET, .y = 33 + MAP_OFFSET, .elevation = 3};
        const u8 *script = GetCoordEventScriptAtMapPosition(&pos);
        EXPECT(script != NULL);
        // Even ticket holders must see inspection; return travel is free.
        for (u32 direction = DIR_SOUTH; direction <= DIR_EAST; direction++)
        {
            gObjectEvents[0].facingDirection = direction;
            EXPECT_EQ(Script_HasNoEffect(script), direction != DIR_SOUTH);
            EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_SS_TICKET), ticket);
            EXPECT_EQ(FlagGet(FLAG_TH13_SHIP_DEPARTED), departed);
        }
    }
    gMapHeader = saved;
    gPlayerAvatar = avatar;
    gObjectEvents[0] = object;
}
#endif
