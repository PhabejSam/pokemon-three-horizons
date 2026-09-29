#include "global.h"
#include "test/test.h"
#include "event_data.h"
#include "overworld.h"
#include "script.h"
#include "constants/maps.h"
#include "constants/three_horizons.h"

#if THREE_HORIZONS
extern const u8 TH12_Bill_OnEntry[];

TEST("Three Horizons playtest13 Bill survives leaving before PC")
{
    bool32 inMachine, rescued;
    PARAMETRIZE { inMachine = FALSE; rescued = FALSE; }
    PARAMETRIZE { inMachine = TRUE; rescued = FALSE; }
    PARAMETRIZE { inMachine = FALSE; rescued = TRUE; }
    PARAMETRIZE { inMachine = TRUE; rescued = TRUE; }
    const struct MapHeader savedHeader = gMapHeader;
    InitEventData();
    gMapHeader = *Overworld_GetMapHeaderByGroupAndId(MAP_GROUP(MAP_TH12_ROUTE25_SEA_COTTAGE), MAP_NUM(MAP_TH12_ROUTE25_SEA_COTTAGE));
    LoadObjEventTemplatesFromHeader();
    if (inMachine)
        FlagSet(FLAG_TH13_BILL_IN_MACHINE);
    if (rescued)
        FlagSet(FLAG_TH12_BILL_RESCUED);
    for (u32 visit = 0; visit < 3; visit++)
    {
        // The actual field transition clears transient state on every visit.
        ClearTempFieldEventData();
        RunScriptImmediately(TH12_Bill_OnEntry);
        EXPECT_EQ(FlagGet(FLAG_TEMP_2), inMachine && !rescued);
        EXPECT_EQ(FlagGet(FLAG_TEMP_3), !rescued); // human hidden
        EXPECT_EQ(FlagGet(FLAG_TEMP_4), inMachine || rescued); // Clefairy hidden
        EXPECT_EQ(FlagGet(FLAG_TH12_BILL_RESCUED), rescued);
        EXPECT(!FlagGet(FLAG_TH12_TICKET)); // map entry never grants a ticket
        EXPECT_EQ(FlagGet(FLAG_TH13_BILL_IN_MACHINE), inMachine && !rescued);
    }
    gMapHeader = savedHeader;
}
#endif
