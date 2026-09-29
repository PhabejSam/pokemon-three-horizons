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
static void LoadCutMap(u16 map)
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
}

TEST("Three Horizons playtest13 Cut removal stays visually collision consistent")
{
    u16 map;
    PARAMETRIZE { map = MAP_TH_VIRIDIAN_ENTRANCE; }
    PARAMETRIZE { map = MAP_TH_ROUTE2; }
    PARAMETRIZE { map = MAP_TH12_VERMILION_CITY; }
    const struct MapHeader savedHeader = gMapHeader;
    const struct BackupMapLayout savedLayout = gBackupMapLayout;
    LoadCutMap(map);
    u32 index;
    for (index = 0; index < gMapHeader.events->objectEventCount; index++)
        if (gSaveBlock1Ptr->objectEventTemplates[index].graphicsId == OBJ_EVENT_GFX_CUTTABLE_TREE_FRLG)
            break;
    EXPECT_LT(index, gMapHeader.events->objectEventCount);
    const struct ObjectEventTemplate tree = gSaveBlock1Ptr->objectEventTemplates[index];
    u8 id = TrySpawnObjectEventTemplate(&tree, MAP_NUM(map), MAP_GROUP(map), 0, 0);
    EXPECT_LT(id, OBJECT_EVENTS_COUNT);
    u8 sprite = gObjectEvents[id].spriteId;
    EXPECT(gSprites[sprite].inUse);
    EXPECT_EQ(GetObjectEventIdByXY(tree.x + MAP_OFFSET, tree.y + MAP_OFFSET), id);
    RemoveObjectEventByLocalIdAndMap(tree.localId, MAP_NUM(map), MAP_GROUP(map));
    EXPECT(!gObjectEvents[id].active);
    EXPECT(!gSprites[sprite].inUse);
    EXPECT_EQ(GetObjectEventIdByXY(tree.x + MAP_OFFSET, tree.y + MAP_OFFSET), OBJECT_EVENTS_COUNT);
    gSaveBlock1Ptr->pos.x = tree.x;
    gSaveBlock1Ptr->pos.y = tree.y;
    TrySpawnObjectEvents(0, 0); // The first camera update after Cut.
    EXPECT(TryGetObjectEventIdByLocalIdAndMap(tree.localId, MAP_NUM(map), MAP_GROUP(map), &id));
    EXPECT_EQ(GetObjectEventIdByXY(tree.x + MAP_OFFSET, tree.y + MAP_OFFSET), OBJECT_EVENTS_COUNT);
    // Native map reload may regrow the tree, but sprite and occupancy agree.
    ClearTempFieldEventData();
    ResetSpriteData();
    FreeAllSpritePalettes();
    ResetObjectEvents();
    LoadObjEventTemplatesFromHeader();
    TrySpawnObjectEvents(0, 0);
    EXPECT(!TryGetObjectEventIdByLocalIdAndMap(tree.localId, MAP_NUM(map), MAP_GROUP(map), &id));
    EXPECT(gSprites[gObjectEvents[id].spriteId].inUse);
    EXPECT_EQ(GetObjectEventIdByXY(tree.x + MAP_OFFSET, tree.y + MAP_OFFSET), id);
    gMapHeader = savedHeader;
    gBackupMapLayout = savedLayout;
}

TEST("Three Horizons playtest13 Cut target remains removed while another tree is unaffected")
{
    const struct MapHeader savedHeader = gMapHeader;
    const struct BackupMapLayout savedLayout = gBackupMapLayout;
    const u16 map = MAP_TH_ROUTE2;
    LoadCutMap(map);
    const struct ObjectEventTemplate first = gSaveBlock1Ptr->objectEventTemplates[0];
    const struct ObjectEventTemplate other = gSaveBlock1Ptr->objectEventTemplates[1];
    EXPECT_EQ(first.graphicsId, OBJ_EVENT_GFX_CUTTABLE_TREE_FRLG);
    EXPECT_EQ(other.graphicsId, OBJ_EVENT_GFX_CUTTABLE_TREE_FRLG);
    u8 id = TrySpawnObjectEventTemplate(&first, MAP_NUM(map), MAP_GROUP(map), 0, 0);
    EXPECT_LT(id, OBJECT_EVENTS_COUNT);
    RemoveObjectEventByLocalIdAndMap(first.localId, MAP_NUM(map), MAP_GROUP(map));
    // Direct template spawning is used by field refresh as well as camera scans.
    EXPECT_EQ(TrySpawnObjectEventTemplate(&first, MAP_NUM(map), MAP_GROUP(map), 0, 0), OBJECT_EVENTS_COUNT);
    id = TrySpawnObjectEventTemplate(&other, MAP_NUM(map), MAP_GROUP(map), 0, 0);
    EXPECT_LT(id, OBJECT_EVENTS_COUNT);
    EXPECT(gObjectEvents[id].active);
    EXPECT(gSprites[gObjectEvents[id].spriteId].inUse);
    gMapHeader = savedHeader;
    gBackupMapLayout = savedLayout;
}
#endif
