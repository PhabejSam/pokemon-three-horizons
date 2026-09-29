#include "global.h"
#include "test/test.h"
#include "overworld.h"
#include "event_scripts.h"
#include "region_map.h"
#include "strings.h"
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
#endif
