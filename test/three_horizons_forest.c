#include "global.h"
#include "test/test.h"
#include "three_horizons.h"
#include "event_data.h"
#include "overworld.h"
#include "constants/three_horizons.h"
#include "constants/maps.h"
#include "constants/layouts.h"
#include "constants/trainers.h"
#include "constants/opponents.h"

#if THREE_HORIZONS
TEST("Three Horizons playtest13 forest Continue replaces only obsolete forest layout")
{
    for (u32 version = TH_STATE_VERSION_12; version <= TH_STATE_VERSION_13; version += 2)
    {
        InitEventData();
        VarSet(VAR_TH_CLOCK_DISPLAY_HI, version);
        gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(MAP_TH_VIRIDIAN_FOREST);
        gSaveBlock1Ptr->location.mapNum = MAP_NUM(MAP_TH_VIRIDIAN_FOREST);
        gSaveBlock1Ptr->mapLayoutId = LAYOUT_VIRIDIAN_FOREST;
        gSaveBlock1Ptr->pos.x = 39;
        gSaveBlock1Ptr->pos.y = 34;
        memset(gSaveBlock1Ptr->mapView, 0x5A, sizeof(gSaveBlock1Ptr->mapView));
        FlagSet(FLAG_TH12_FOREST_SEEN);
        FlagSet(TRAINER_FLAGS_START + TRAINER_TH_RICK);
        TH_MigrateSaveState();
        EXPECT(gSaveBlock1Ptr->mapLayoutId != LAYOUT_VIRIDIAN_FOREST);
        EXPECT_EQ(gSaveBlock1Ptr->mapLayoutId, Overworld_GetMapHeaderByGroupAndId(MAP_GROUP(MAP_TH_VIRIDIAN_FOREST), MAP_NUM(MAP_TH_VIRIDIAN_FOREST))->mapLayoutId);
        EXPECT_EQ(gSaveBlock1Ptr->pos.x, 39);
        EXPECT_EQ(gSaveBlock1Ptr->pos.y, 34);
        EXPECT(FlagGet(FLAG_TH12_FOREST_SEEN));
        EXPECT(FlagGet(TRAINER_FLAGS_START + TRAINER_TH_RICK));
        for (u32 i=0;i<sizeof(gSaveBlock1Ptr->mapView);i++) EXPECT_EQ(((u8*)gSaveBlock1Ptr->mapView)[i],0);
        memset(gSaveBlock1Ptr->mapView,0x3C,sizeof(gSaveBlock1Ptr->mapView));
        TH_MigrateSaveState();
        for (u32 i=0;i<sizeof(gSaveBlock1Ptr->mapView);i++) EXPECT_EQ(((u8*)gSaveBlock1Ptr->mapView)[i],0x3C);
    }
    gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(MAP_TH_ROUTE2);
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(MAP_TH_ROUTE2);
    gSaveBlock1Ptr->mapLayoutId = LAYOUT_VIRIDIAN_FOREST;
    TH_MigrateSaveState();
    EXPECT_EQ(gSaveBlock1Ptr->mapLayoutId, LAYOUT_VIRIDIAN_FOREST);
}
#endif
