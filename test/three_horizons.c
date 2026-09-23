#include "three_horizons.h"
#include "global.h"
#include "test/test.h"
#include "event_data.h"
#include "item.h"
#include "pokemon.h"
#include "script.h"
#include "new_game.h"
#include "constants/maps.h"

#include "constants/three_horizons.h"
#include "constants/items.h"

#if THREE_HORIZONS
static void ResetOpening(void)
{
    InitEventData();
    ZeroPlayerPartyMons();
    gPartiesCount[B_TRAINER_PLAYER] = 0;
    ClearBag();
    TH_InitNewGame();
}

TEST("Three Horizons initializes only project progress")
{
    VarSet(VAR_STARTER_MON, 2);
    VarSet(VAR_TH_STAGE, TH_STAGE_COMPLETE);
    VarSet(VAR_TH_FIRST_PARTNER, SPECIES_TREECKO);
    TH_InitNewGame();
    EXPECT_EQ(VarGet(VAR_TH_STAGE), TH_STAGE_HOME);
    EXPECT_EQ(VarGet(VAR_TH_FIRST_PARTNER), SPECIES_NONE);
    EXPECT_EQ(VarGet(VAR_STARTER_MON), 2);
}

TEST("Three Horizons grants all nine partners once with correct rival and level")
{
    static const u16 choices[][2] = {
        {SPECIES_BULBASAUR, SPECIES_CHARMANDER},
        {SPECIES_CHARMANDER, SPECIES_SQUIRTLE},
        {SPECIES_SQUIRTLE, SPECIES_BULBASAUR},
        {SPECIES_CHIKORITA, SPECIES_CYNDAQUIL},
        {SPECIES_CYNDAQUIL, SPECIES_TOTODILE},
        {SPECIES_TOTODILE, SPECIES_CHIKORITA},
        {SPECIES_TREECKO, SPECIES_TORCHIC},
        {SPECIES_TORCHIC, SPECIES_MUDKIP},
        {SPECIES_MUDKIP, SPECIES_TREECKO},
    };
    u32 i;
    for (i = 0; i < ARRAY_COUNT(choices); i++)
    {
        ResetOpening();
        VarSet(VAR_TH_STAGE, TH_STAGE_INVITED);
        EXPECT(TH_TryGiveStarter(choices[i][0]));
        EXPECT_EQ(gPartiesCount[B_TRAINER_PLAYER], 1);
        EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_SPECIES), choices[i][0]);
        EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_LEVEL), 5);
        EXPECT_EQ(VarGet(VAR_TH_RIVAL_PARTNER), choices[i][1]);
        EXPECT_EQ(VarGet(VAR_TH_FIRST_PARTNER), choices[i][0]);
        EXPECT(!TH_TryGiveStarter(SPECIES_MUDKIP));
        EXPECT_EQ(gPartiesCount[B_TRAINER_PLAYER], 1);
    }
}

TEST("Three Horizons rejects invalid, premature and occupied-party grants")
{
    ResetOpening();
    EXPECT(!TH_TryGiveStarter(SPECIES_BULBASAUR));
    VarSet(VAR_TH_STAGE, TH_STAGE_INVITED);
    EXPECT(!TH_TryGiveStarter(SPECIES_NONE));
    EXPECT(!TH_TryGiveStarter(SPECIES_PIDGEY));
    EXPECT(!TH_TryGiveStarter(65535));
    EXPECT_EQ(gPartiesCount[B_TRAINER_PLAYER], 0);
    EXPECT_EQ(VarGet(VAR_TH_STAGE), TH_STAGE_INVITED);
    gPartiesCount[B_TRAINER_PLAYER] = 1;
    EXPECT(!TH_TryGiveStarter(SPECIES_TREECKO));
    gPartiesCount[B_TRAINER_PLAYER] = 0;
}

TEST("Three Horizons rewards are once-only even after spending supplies")
{
    ResetOpening();
    EXPECT(!TH_TryGiveSupplies());
    VarSet(VAR_TH_STAGE, TH_STAGE_INVITED);
    EXPECT(TH_TryGiveStarter(SPECIES_CHIKORITA));
    EXPECT(TH_TryGiveSupplies());
    EXPECT(CheckBagHasItem(ITEM_POKE_BALL, 5));
    EXPECT(!CheckBagHasItem(ITEM_POKE_BALL, 6));
    EXPECT(CheckBagHasItem(ITEM_POTION, 2));
    EXPECT(!CheckBagHasItem(ITEM_POTION, 3));
    EXPECT(RemoveBagItem(ITEM_POKE_BALL, 5));
    EXPECT(TH_TryGiveSupplies());
    EXPECT(!CheckBagHasItem(ITEM_POKE_BALL, 1));
    EXPECT(FlagGet(FLAG_SYS_POKEDEX_GET));
}

TEST("Three Horizons battle completion is monotonic and idempotent")
{
    ResetOpening();
    TH_FinishRivalBattle();
    EXPECT_EQ(VarGet(VAR_TH_STAGE), TH_STAGE_HOME);
    VarSet(VAR_TH_STAGE, TH_STAGE_PARTNER);
    TH_FinishRivalBattle();
    EXPECT_EQ(VarGet(VAR_TH_STAGE), TH_STAGE_BATTLE_DONE);
    TH_FinishRivalBattle();
    EXPECT_EQ(VarGet(VAR_TH_STAGE), TH_STAGE_BATTLE_DONE);
    VarSet(VAR_TH_STAGE, TH_STAGE_COMPLETE);
    TH_FinishRivalBattle();
    EXPECT_EQ(VarGet(VAR_TH_STAGE), TH_STAGE_COMPLETE);
}

TEST("Three Horizons retries partial supplies without duplicating balls")
{
    u32 i;
    ResetOpening();
    VarSet(VAR_TH_STAGE, TH_STAGE_INVITED);
    EXPECT(TH_TryGiveStarter(SPECIES_TOTODILE));
    for (i = 0; i < gBagPockets[GetItemPocket(ITEM_POTION)].capacity; i++)
        EXPECT(AddBagItem(ITEM_POTION, MAX_BAG_ITEM_CAPACITY));
    EXPECT(!TH_TryGiveSupplies());
    EXPECT_EQ(VarGet(VAR_TH_SUPPLY_MASK), TH_SUPPLY_BALLS);
    EXPECT(CheckBagHasItem(ITEM_POKE_BALL, 5));
    EXPECT(RemoveBagItem(ITEM_POTION, 2));
    EXPECT(TH_TryGiveSupplies());
    EXPECT(!CheckBagHasItem(ITEM_POKE_BALL, 6));
    EXPECT_EQ(VarGet(VAR_TH_SUPPLY_MASK), TH_SUPPLIES_COMPLETE);
}

TEST("Three Horizons original partner survives party replacement")
{
    ResetOpening();
    VarSet(VAR_TH_STAGE, TH_STAGE_INVITED);
    EXPECT(TH_TryGiveStarter(SPECIES_MUDKIP));
    ZeroPlayerPartyMons();
    gPartiesCount[B_TRAINER_PLAYER] = 0;
    EXPECT_EQ(VarGet(VAR_TH_FIRST_PARTNER), SPECIES_MUDKIP);
    EXPECT_EQ(VarGet(VAR_TH_RIVAL_PARTNER), SPECIES_TREECKO);
    EXPECT(!TH_TryGiveStarter(SPECIES_CHIKORITA));
}

TEST("Three Horizons map transitions derive Robin visibility from saved progress")
{
    extern const u8 TH_Pallet_OnLoad[];
    extern const u8 TH_Lab_OnLoad[];
    ResetOpening();
    FlagSet(FLAG_TH_HIDE_ROBIN_TOWN);
    RunScriptImmediately(TH_Pallet_OnLoad);
    EXPECT(!FlagGet(FLAG_TH_HIDE_ROBIN_TOWN));
    VarSet(VAR_TH_STAGE, TH_STAGE_INVITED);
    RunScriptImmediately(TH_Pallet_OnLoad);
    EXPECT(FlagGet(FLAG_TH_HIDE_ROBIN_TOWN));
    RunScriptImmediately(TH_Lab_OnLoad);
    EXPECT(!FlagGet(FLAG_TH_HIDE_ROBIN_LAB));
    VarSet(VAR_TH_STAGE, TH_STAGE_PARTNER);
    RunScriptImmediately(TH_Lab_OnLoad);
    EXPECT(FlagGet(FLAG_TH_HIDE_ROBIN_LAB));
    EXPECT_EQ(VarGet(VAR_TH_STAGE), TH_STAGE_PARTNER);
}

TEST("Three Horizons new game starts and recovers at home")
{
    NewGameInitData();
    EXPECT_EQ(gSaveBlock1Ptr->location.mapGroup, MAP_GROUP(MAP_TH_HOME_2F));
    EXPECT_EQ(gSaveBlock1Ptr->location.mapNum, MAP_NUM(MAP_TH_HOME_2F));
    EXPECT_EQ(gSaveBlock1Ptr->lastHealLocation.mapGroup, MAP_GROUP(MAP_TH_HOME_1F));
    EXPECT_EQ(gSaveBlock1Ptr->lastHealLocation.mapNum, MAP_NUM(MAP_TH_HOME_1F));
    EXPECT_EQ(VarGet(VAR_TH_STAGE), TH_STAGE_HOME);
}
#endif
