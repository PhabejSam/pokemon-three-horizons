#include "global.h"
#include "test/test.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "overworld.h"
#include "fieldmap.h"
#include "sprite.h"
#include "constants/event_objects.h"
#include "constants/maps.h"

#if THREE_HORIZONS
static void LoadRoute9(u16 map, s16 x)
{
    InitEventData();
    ResetSpriteData();
    FreeAllSpritePalettes();
    ResetObjectEvents();
    gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(map);
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(map);
    gMapHeader = *Overworld_GetMapHeaderByGroupAndId(MAP_GROUP(map), MAP_NUM(map));
    LoadObjEventTemplatesFromHeader();
    InitMap();
    InitObjectEventPalettes(0);
    gSaveBlock1Ptr->pos.x = x;
    gSaveBlock1Ptr->pos.y = 8;
}

static struct ObjectEvent TestPlayer(void)
{
    return (struct ObjectEvent){.active = TRUE, .localId = OBJ_EVENT_ID_PLAYER,
        .currentCoords = {1 + MAP_OFFSET, 8 + MAP_OFFSET},
        .previousCoords = {1 + MAP_OFFSET, 8 + MAP_OFFSET}, .currentElevation = 3};
}

TEST("Three Horizons PT14 cut: Route9 current-map tree survives connection edge filter")
{
    u32 x;
    bool32 stale;
    PARAMETRIZE { x = 0; stale = FALSE; }
    PARAMETRIZE { x = 0; stale = TRUE; }
    PARAMETRIZE { x = 1; stale = FALSE; }
    const struct MapHeader header = gMapHeader;
    const struct BackupMapLayout layout = gBackupMapLayout;
    LoadRoute9(MAP_TH13_ROUTE9, x);
    if (stale) FlagSet(FLAG_TEMP_12);
    // The camera-transition owner clears the previous map's transient flags.
    ClearTempFieldEventData();
    TrySpawnObjectEvents(0, 0);
    u8 id;
    EXPECT(!FlagGet(FLAG_TEMP_12));
    EXPECT(!TryGetObjectEventIdByLocalIdAndMap(10, MAP_NUM(MAP_TH13_ROUTE9), MAP_GROUP(MAP_TH13_ROUTE9), &id));
    EXPECT_LT(id, OBJECT_EVENTS_COUNT);
    EXPECT(gObjectEvents[id].active);
    EXPECT_EQ(gObjectEvents[id].mapGroup, 75);
    EXPECT_EQ(gObjectEvents[id].mapNum, 94);
    EXPECT(gSprites[gObjectEvents[id].spriteId].inUse);
    EXPECT_EQ(GetObjectEventIdByXY(2 + MAP_OFFSET, 8 + MAP_OFFSET), id);
    struct ObjectEvent player = TestPlayer();
    EXPECT_EQ(GetCollisionAtCoords(&player, 2 + MAP_OFFSET, 8 + MAP_OFFSET, DIR_EAST), COLLISION_OBJECT_EVENT);
    gMapHeader = header; gBackupMapLayout = layout;
}

TEST("Three Horizons PT14 cut: visibility collision removal and reload agree")
{
    const struct MapHeader header = gMapHeader;
    const struct BackupMapLayout layout = gBackupMapLayout;
    LoadRoute9(MAP_TH13_ROUTE9, 1);
    TrySpawnObjectEvents(0, 0);
    u8 id;
    EXPECT(!TryGetObjectEventIdByLocalIdAndMap(10, 94, 75, &id));
    u8 sprite = gObjectEvents[id].spriteId;
    RemoveObjectEventByLocalIdAndMap(10, 94, 75);
    EXPECT(FlagGet(FLAG_TEMP_12));
    EXPECT(!gObjectEvents[id].active);
    EXPECT(!gSprites[sprite].inUse);
    TrySpawnObjectEvents(0, 0);
    EXPECT(TryGetObjectEventIdByLocalIdAndMap(10, 94, 75, &id));
    struct ObjectEvent player = TestPlayer();
    EXPECT_EQ(GetCollisionInDirection(&player, DIR_EAST), COLLISION_NONE);
    // Normal new visit clears the flag and may regrow, even at the entry edge.
    ClearTempFieldEventData();
    gSaveBlock1Ptr->pos.x = 0;
    TrySpawnObjectEvents(0, 0);
    EXPECT(!TryGetObjectEventIdByLocalIdAndMap(10, 94, 75, &id));
    EXPECT(gSprites[gObjectEvents[id].spriteId].inUse);
    EXPECT_EQ(GetCollisionInDirection(&player, DIR_EAST), COLLISION_OBJECT_EVENT);
    gMapHeader = header; gBackupMapLayout = layout;
}

TEST("Three Horizons PT14 cut: reload on previously cut tile keeps player free")
{
    const struct MapHeader header = gMapHeader;
    const struct BackupMapLayout layout = gBackupMapLayout;
    LoadRoute9(MAP_TH13_ROUTE9, 2);
    TrySpawnObjectEvents(0, 0);
    EXPECT(FlagGet(FLAG_TEMP_12));
    EXPECT_EQ(GetObjectEventIdByXY(2 + MAP_OFFSET, 8 + MAP_OFFSET), OBJECT_EVENTS_COUNT);
    gSaveBlock1Ptr->pos.x = 1;
    TrySpawnObjectEvents(0, 0);
    EXPECT_EQ(GetObjectEventIdByXY(2 + MAP_OFFSET, 8 + MAP_OFFSET), OBJECT_EVENTS_COUNT);
    gMapHeader = header; gBackupMapLayout = layout;
}

TEST("Three Horizons PT14 cut: connected clones retain the existing visibility policy")
{
    const struct MapHeader header = gMapHeader;
    const struct BackupMapLayout layout = gBackupMapLayout;
    LoadRoute9(MAP_TH13_ROUTE9, 0);
    struct ObjectEventTemplate clone = gSaveBlock1Ptr->objectEventTemplates[9];
    clone.kind = OBJ_KIND_CLONE;
    clone.x = 9; // Within-view check admits this distant clone; edge filter rejects it.
    clone.targetLocalId = 10;
    clone.targetMapNum = MAP_NUM(MAP_TH13_ROUTE9);
    clone.targetMapGroup = MAP_GROUP(MAP_TH13_ROUTE9);
    EXPECT_EQ(TrySpawnObjectEventTemplate(&clone, 94, 75, 0, 0), OBJECT_EVENTS_COUNT);
    EXPECT(FlagGet(FLAG_TEMP_12));
    gMapHeader = header; gBackupMapLayout = layout;
}

TEST("Three Horizons PT14 cut: upstream map ownership keeps existing edge policy")
{
    const struct MapHeader header = gMapHeader;
    const struct BackupMapLayout layout = gBackupMapLayout;
    // FRLG maps are not registered in the Three Horizons ROM. Exercise the
    // unchanged upstream ownership path with real TH tree geometry and the
    // registered upstream Route101 map identity; full donor builds run at gates.
    LoadRoute9(MAP_TH13_ROUTE9, 0);
    gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(MAP_ROUTE101);
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(MAP_ROUTE101);
    const struct ObjectEventTemplate *tree = &gSaveBlock1Ptr->objectEventTemplates[9];
    ASSUME(tree->graphicsId == OBJ_EVENT_GFX_CUTTABLE_TREE_FRLG);
    ASSUME(tree->x == 2 && tree->y == 8);
    EXPECT_EQ(TrySpawnObjectEventTemplate(tree, MAP_NUM(MAP_ROUTE101), MAP_GROUP(MAP_ROUTE101), 0, 0), OBJECT_EVENTS_COUNT);
    gMapHeader = header; gBackupMapLayout = layout;
}
#endif

