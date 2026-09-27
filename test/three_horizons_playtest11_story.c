#include "global.h"
#include "test/test.h"
#include "three_horizons.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "event_data.h"
#include "item.h"
#include "malloc.h"
#include "battle_setup.h"
#include "constants/three_horizons.h"
#include "constants/trainers.h"
#if THREE_HORIZONS
extern const u8 TH_RocketDuoBattle[];
extern const u8 TH_RocketDuoVictory[];
extern const u8 TH_Rival_ROUTE22_Bulbasaur[];
extern u8 TH_TryReviveFossil(u16 item);

TEST("Three Horizons fossil revival requires badge and consumes only a delivered fossil")
{
    struct PokemonStorage *savedStorage = gPokemonStoragePtr;
    struct Pokemon savedParty[PARTY_SIZE], mon;
    memcpy(savedParty, gPlayerParty, sizeof(savedParty));
    gPokemonStoragePtr = AllocZeroed(sizeof(*gPokemonStoragePtr));
    EXPECT(gPokemonStoragePtr != NULL);
    ClearBag();
    AddBagItem(ITEM_DOME_FOSSIL, 1);
    AddBagItem(ITEM_HELIX_FOSSIL, 1);
    memset(gPlayerParty, 0, sizeof(savedParty));
    CalculatePlayerPartyCount();
    FlagClear(FLAG_BADGE02_GET);
    FlagClear(FLAG_TH12_REVIVED_DOME);
    FlagClear(FLAG_TH12_REVIVED_HELIX);
    EXPECT_EQ(TH_TryReviveFossil(ITEM_DOME_FOSSIL), MON_CANT_GIVE);
    EXPECT(CheckBagHasItem(ITEM_DOME_FOSSIL, 1));
    FlagSet(FLAG_BADGE02_GET);
    EXPECT_EQ(TH_TryReviveFossil(ITEM_POTION), MON_CANT_GIVE);
    EXPECT_EQ(TH_TryReviveFossil(ITEM_DOME_FOSSIL), MON_GIVEN_TO_PARTY);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPECIES), SPECIES_KABUTO);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_LEVEL), 20);
    EXPECT(!CheckBagHasItem(ITEM_DOME_FOSSIL, 1));
    EXPECT(FlagGet(FLAG_TH12_REVIVED_DOME));
    EXPECT(!FlagGet(FLAG_TH12_REVIVED_HELIX));
    EXPECT_EQ(TH_TryReviveFossil(ITEM_DOME_FOSSIL), MON_CANT_GIVE);
    mon = gPlayerParty[0];
    for (u32 i = 0; i < PARTY_SIZE; i++) gPlayerParty[i] = mon;
    for (u32 b = 0; b < TOTAL_BOXES_COUNT; b++)
        for (u32 s = 0; s < IN_BOX_COUNT; s++) gPokemonStoragePtr->boxes[b][s] = mon.box;
    EXPECT_EQ(TH_TryReviveFossil(ITEM_HELIX_FOSSIL), MON_CANT_GIVE);
    EXPECT(CheckBagHasItem(ITEM_HELIX_FOSSIL, 1));
    memset(&gPokemonStoragePtr->boxes[0][0], 0, sizeof(mon.box));
    EXPECT_EQ(TH_TryReviveFossil(ITEM_HELIX_FOSSIL), MON_GIVEN_TO_PC);
    EXPECT_EQ(GetBoxMonData(&gPokemonStoragePtr->boxes[0][0], MON_DATA_SPECIES), SPECIES_OMANYTE);
    EXPECT(!CheckBagHasItem(ITEM_HELIX_FOSSIL, 1));
    EXPECT(FlagGet(FLAG_TH12_REVIVED_HELIX));
    FlagSet(FLAG_TH_FOSSIL_DOME);
    FlagSet(FLAG_TH_FOSSIL_HELIX);
    VarSet(VAR_TH_CLOCK_DISPLAY_HI, TH_STATE_VERSION_11);
    TH_MigrateSaveState();
    EXPECT(FlagGet(FLAG_TH12_REVIVED_DOME));
    EXPECT(FlagGet(FLAG_TH12_REVIVED_HELIX));
    Free(gPokemonStoragePtr);
    gPokemonStoragePtr = savedStorage;
    memcpy(gPlayerParty, savedParty, sizeof(savedParty));
    CalculatePlayerPartyCount();
    FlagClear(FLAG_BADGE02_GET);
    ClearBag();
}

TEST("Three Horizons Rocket duo has two distinct opponents and victory continuation")
{
    TrainerBattleParameter params;
    memcpy(&params, TH_RocketDuoBattle + TRAINERBATTLE_OPCODE_OFFSET, sizeof(params));
    EXPECT(params.params.isDoubleBattle);
    EXPECT_EQ(params.params.opponentA, TRAINER_TH11_JESSIE);
    EXPECT_EQ(params.params.opponentB, TRAINER_TH11_JAMES);
    EXPECT(params.params.battleScriptRetAddrA == TH_RocketDuoVictory);
    EXPECT(!params.params.earlyRival);
}

TEST("Three Horizons Route 22 rival has a loss speech without tutorial healing")
{
    TrainerBattleParameter params;
    memcpy(&params, TH_Rival_ROUTE22_Bulbasaur + TRAINERBATTLE_OPCODE_OFFSET, sizeof(params));
    EXPECT(params.params.earlyRival);
    EXPECT(params.params.victoryText != NULL);
    EXPECT(params.params.victoryText != params.params.defeatTextA);
    EXPECT_EQ(params.params.rivalBattleFlags, 0);
}

TEST("Three Horizons Playtest 10 upgrade preserves every earned chapter receipt")
{
    VarSet(VAR_TH_CLOCK_DISPLAY_HI, TH_STATE_VERSION_10 | 1);
    VarSet(VAR_TH_FIRST_PARTNER, SPECIES_TORCHIC);
    VarSet(VAR_TH_BROCK_GIFT, SPECIES_SQUIRTLE);
    FlagSet(FLAG_TH_DIG_TM);
    FlagSet(FLAG_TH_MAGIKARP);
    FlagSet(FLAG_TH_FOSSIL_DOME);
    FlagSet(FLAG_TH_MISTY_TM);
    TH_MigrateSaveState();
    EXPECT(FlagGet(FLAG_TH_DIG_TM));
    EXPECT(FlagGet(FLAG_TH_MAGIKARP));
    EXPECT(FlagGet(FLAG_TH_FOSSIL_DOME));
    EXPECT(FlagGet(FLAG_TH_MISTY_TM));
    EXPECT_EQ(VarGet(VAR_TH_BROCK_GIFT), SPECIES_SQUIRTLE);
    EXPECT_EQ(VarGet(VAR_TH_CLOCK_DISPLAY_HI), TH_STATE_VERSION_12 | 1);
}
#endif
