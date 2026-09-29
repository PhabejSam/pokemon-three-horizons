#include "global.h"
#include "test/test.h"
#include "event_data.h"
#include "overworld.h"
#include "script.h"
#include "three_horizons.h"
#include "item.h"
#include "money.h"
#include "constants/maps.h"
#include "constants/script_commands.h"
#include "constants/three_horizons.h"

#if THREE_HORIZONS
extern const u8 TH12_Bill_OnEntry[];
extern const u8 TH12_Cerulean_CatchUpSupplies[];

TEST("Three Horizons playtest13 Bill migration retains a witnessed machine entry")
{
    u32 state;
    PARAMETRIZE { state = 0; } // actual P12 save inside the machine sequence
    PARAMETRIZE { state = 1; } // same transient bits in another map
    PARAMETRIZE { state = 2; } // same map number in another group
    PARAMETRIZE { state = 3; } // help has not been accepted
    PARAMETRIZE { state = 4; } // human already rescued
    PARAMETRIZE { state = 5; } // older release does not prove this P12 scene
    PARAMETRIZE { state = 6; } // unrelated/incomplete temporary flags
    PARAMETRIZE { state = 7; }
    const struct WarpData savedLocation = gSaveBlock1Ptr->location;
    const struct MapHeader savedHeader = gMapHeader;
    InitEventData();
    ClearBag();
    VarSet(VAR_TH_CLOCK_DISPLAY_HI, state == 5 ? TH_STATE_VERSION_11 : TH_STATE_VERSION_12);
    gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(MAP_TH12_ROUTE25_SEA_COTTAGE) + (state == 2);
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(MAP_TH12_ROUTE25_SEA_COTTAGE) + (state == 1);
    if (state != 3) FlagSet(FLAG_TEMP_2);
    if (state != 6) FlagSet(FLAG_TEMP_3);
    if (state != 7) FlagSet(FLAG_TEMP_4);
    if (state == 4) FlagSet(FLAG_TH12_BILL_RESCUED);
    TH_MigrateSaveState();
    EXPECT_EQ(FlagGet(FLAG_TH13_BILL_IN_MACHINE), state == 0);
    // Continue rebuilds the map and clears temp flags after migration.
    gMapHeader = *Overworld_GetMapHeaderByGroupAndId(MAP_GROUP(MAP_TH12_ROUTE25_SEA_COTTAGE), MAP_NUM(MAP_TH12_ROUTE25_SEA_COTTAGE));
    LoadObjEventTemplatesFromHeader();
    ClearTempFieldEventData();
    RunScriptImmediately(TH12_Bill_OnEntry);
    EXPECT_EQ(FlagGet(FLAG_TEMP_2), state == 0);
    EXPECT(!FlagGet(FLAG_TH12_TICKET));
    gSaveBlock1Ptr->location = savedLocation;
    gMapHeader = savedHeader;
}

TEST("Three Horizons playtest13 aide acknowledges completed supplies")
{
    struct ScriptContext ctx;
    InitEventData();
    ClearBag();
    VarSet(VAR_TH_STAGE, TH_STAGE_PARTNER);
    FlagSet(FLAG_TH12_START_MONEY);
    FlagSet(FLAG_TH12_ULTRA_BALLS);
    SetMoney(&gSaveBlock1Ptr->money, 4321);
    EXPECT(AddBagItem(ITEM_ULTRA_BALL, 7));
    // Skip only the verified UI lock/facing prefix. Run the native bytecode
    // analyzer through receipt selection to the first external effect.
    EXPECT_EQ(TH12_Cerulean_CatchUpSupplies[0], SCR_OP_LOCK);
    EXPECT_EQ(TH12_Cerulean_CatchUpSupplies[1], SCR_OP_FACEPLAYER);
    EXPECT(RunScriptImmediatelyUntilEffect(SCREFF_V1 | SCREFF_ANY, TH12_Cerulean_CatchUpSupplies + 2, &ctx));
    EXPECT(!Script_MatchesSpecial(ctx.scriptPtr, TH_TryGiveChapter12Supplies));
    EXPECT(ctx.data[0] != 0); // an acknowledgment message was selected
    EXPECT_EQ(GetMoney(&gSaveBlock1Ptr->money), 4321);
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_ULTRA_BALL), 7);
}

TEST("Three Horizons playtest13 aide retries only missing supplies")
{
    u32 received;
    PARAMETRIZE { received = 0; }
    PARAMETRIZE { received = 1; }
    PARAMETRIZE { received = 2; }
    PARAMETRIZE { received = 3; }
    InitEventData();
    ClearBag();
    VarSet(VAR_TH_STAGE, TH_STAGE_PARTNER);
    SetMoney(&gSaveBlock1Ptr->money, 4321);
    EXPECT(AddBagItem(ITEM_ULTRA_BALL, 7));
    if (received & 1)
        FlagSet(FLAG_TH12_START_MONEY);
    if (received & 2)
        FlagSet(FLAG_TH12_ULTRA_BALLS);
    for (u32 visit = 0; visit < 2; visit++)
    {
        TH_TryGiveChapter12Supplies();
        EXPECT(gSpecialVar_Result);
        EXPECT_EQ(GetMoney(&gSaveBlock1Ptr->money), 4321 + ((received & 1) ? 0 : 2000));
        EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_ULTRA_BALL), (received & 2) ? 7 : 9);
        EXPECT(FlagGet(FLAG_TH12_START_MONEY));
        EXPECT(FlagGet(FLAG_TH12_ULTRA_BALLS));
    }
}

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
