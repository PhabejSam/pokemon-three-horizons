#include "global.h"
#include "test/test.h"
#include "overworld.h"
#include "event_scripts.h"
#include "region_map.h"
#include "strings.h"
#include "event_data.h"
#include "fieldmap.h"
#include "malloc.h"
#include "tv.h"
#include "constants/metatiles.h"
#include "constants/maps.h"
#include "constants/metatile_behaviors.h"

#if THREE_HORIZONS
extern const u8 *Test_TH_FieldRegionMapTitle(void);
extern const u8 *Test_TH_MetatileScript(u8 behavior);

TEST("Three Horizons playtest13 Kanto map interaction uses current region")
{
    u16 map;
    PARAMETRIZE { map = MAP_TH_RIVAL_HOUSE; }
    PARAMETRIZE { map = MAP_TH_VIRIDIAN_HOUSE; }
    PARAMETRIZE { map = MAP_TH_VIRIDIAN_SCHOOL; }
    PARAMETRIZE { map = MAP_TH12_SSANNE_CAPTAINS_OFFICE; }
    const struct MapHeader saved = gMapHeader;
    const struct WarpData location = gSaveBlock1Ptr->location;
    gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(map);
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(map);
    gMapHeader = *Overworld_GetMapHeaderByGroupAndId(MAP_GROUP(map), MAP_NUM(map));
    EXPECT_EQ(GetRegionMapType(gMapHeader.regionMapSectionId), REGION_MAP_KANTO);
    EXPECT_EQ(Test_TH_FieldRegionMapTitle(), gText_Kanto);
    EXPECT(Test_TH_MetatileScript(MB_REGION_MAP) != EventScript_RegionMap);
    gMapHeader = saved;
    gSaveBlock1Ptr->location = location;
}

TEST("Three Horizons playtest13 Kanto map preserves upstream Hoenn interaction")
{
    const struct MapHeader saved = gMapHeader;
    const struct WarpData location = gSaveBlock1Ptr->location;
    gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(MAP_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F);
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(MAP_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F);
    gMapHeader = *Overworld_GetMapHeaderByGroupAndId(gSaveBlock1Ptr->location.mapGroup, gSaveBlock1Ptr->location.mapNum);
    EXPECT_EQ(GetRegionMapType(gMapHeader.regionMapSectionId), REGION_MAP_HOENN);
    EXPECT_EQ(Test_TH_FieldRegionMapTitle(), gText_Hoenn);
    EXPECT_EQ(Test_TH_MetatileScript(MB_REGION_MAP), EventScript_RegionMap);
    gMapHeader = saved;
    gSaveBlock1Ptr->location = location;
}

extern void TurnOffTVScreen(void);
extern void TurnOnTVScreen(void);

static void LoadTVMap(u16 map)
{
    InitEventData();
    gSaveBlock1Ptr->pos.x = 0;
    gSaveBlock1Ptr->pos.y = 0;
    gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(map);
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(map);
    gMapHeader = *Overworld_GetMapHeaderByGroupAndId(MAP_GROUP(map), MAP_NUM(map));
    InitMap();
}

TEST("Three Horizons playtest13 Kanto TV preserves metatile")
{
    u16 map;
    PARAMETRIZE { map = MAP_TH_VIRIDIAN_HOUSE; }
    PARAMETRIZE { map = MAP_TH12_VERMILION_CITY_HOUSE1; }
    const struct MapHeader saved = gMapHeader;
    const struct BackupMapLayout layout = gBackupMapLayout;
    u16 *old1 = gOverworldTilemapBuffer_Bg1, *old2 = gOverworldTilemapBuffer_Bg2, *old3 = gOverworldTilemapBuffer_Bg3;
    gOverworldTilemapBuffer_Bg1 = AllocZeroed(BG_SCREEN_SIZE);
    gOverworldTilemapBuffer_Bg2 = AllocZeroed(BG_SCREEN_SIZE);
    gOverworldTilemapBuffer_Bg3 = AllocZeroed(BG_SCREEN_SIZE);
    for (u32 reload = 0; reload < 2; reload++)
    {
        LoadTVMap(map);
        u32 x = 5 + MAP_OFFSET, y = 1 + MAP_OFFSET;
        EXPECT_EQ(MapGridGetMetatileBehaviorAt(x, y), MB_TELEVISION);
        u16 entry = gBackupMapLayout.map[y * gBackupMapLayout.width + x];
        u32 id = MapGridGetMetatileIdAt(x, y);
        u8 elevation = MapGridGetElevationAt(x, y), collision = MapGridGetCollisionAt(x, y);
        for (u32 repeat = 0; repeat < 2; repeat++)
        {
            // Actual final special of the inherited dialogue, not a mock conversion.
            TurnOffTVScreen();
            EXPECT_EQ(gBackupMapLayout.map[y * gBackupMapLayout.width + x], entry);
            EXPECT_EQ(MapGridGetMetatileIdAt(x, y), id);
            EXPECT_EQ(MapGridGetElevationAt(x, y), elevation);
            EXPECT_EQ(MapGridGetCollisionAt(x, y), collision);
            // News/load-time animation shares the same conversion owner.
            TurnOnTVScreen();
            EXPECT_EQ(gBackupMapLayout.map[y * gBackupMapLayout.width + x], entry);
            EXPECT_EQ(Test_TH_MetatileScript(MB_TELEVISION), EventScript_PlayerFacingTVScreen);
        }
    }
    Free(gOverworldTilemapBuffer_Bg1);
    Free(gOverworldTilemapBuffer_Bg2);
    Free(gOverworldTilemapBuffer_Bg3);
    gOverworldTilemapBuffer_Bg1 = old1;
    gOverworldTilemapBuffer_Bg2 = old2;
    gOverworldTilemapBuffer_Bg3 = old3;
    gMapHeader = saved;
    gBackupMapLayout = layout;
}

TEST("Three Horizons playtest13 Kanto TV preserves Hoenn on off conversion")
{
    const struct MapHeader saved = gMapHeader;
    const struct BackupMapLayout layout = gBackupMapLayout;
    u16 *old1 = gOverworldTilemapBuffer_Bg1, *old2 = gOverworldTilemapBuffer_Bg2, *old3 = gOverworldTilemapBuffer_Bg3;
    gOverworldTilemapBuffer_Bg1 = AllocZeroed(BG_SCREEN_SIZE);
    gOverworldTilemapBuffer_Bg2 = AllocZeroed(BG_SCREEN_SIZE);
    gOverworldTilemapBuffer_Bg3 = AllocZeroed(BG_SCREEN_SIZE);
    LoadTVMap(MAP_LITTLEROOT_TOWN_BRENDANS_HOUSE_1F);
    u32 x, y;
    bool32 found = FALSE;
    for (y = 0; y < gBackupMapLayout.height && !found; y++)
        for (x = 0; x < gBackupMapLayout.width; x++)
            if (MapGridGetMetatileBehaviorAt(x, y) == MB_TELEVISION)
            {
                found = TRUE;
                TurnOnTVScreen();
                EXPECT_EQ(MapGridGetMetatileIdAt(x, y), METATILE_Building_TV_On);
                TurnOffTVScreen();
                EXPECT_EQ(MapGridGetMetatileIdAt(x, y), METATILE_Building_TV_Off);
                break;
            }
    EXPECT(found);
    EXPECT_EQ(Test_TH_MetatileScript(MB_TELEVISION), EventScript_TV);
    Free(gOverworldTilemapBuffer_Bg1);
    Free(gOverworldTilemapBuffer_Bg2);
    Free(gOverworldTilemapBuffer_Bg3);
    gOverworldTilemapBuffer_Bg1 = old1;
    gOverworldTilemapBuffer_Bg2 = old2;
    gOverworldTilemapBuffer_Bg3 = old3;
    gMapHeader = saved;
    gBackupMapLayout = layout;
}
#endif
