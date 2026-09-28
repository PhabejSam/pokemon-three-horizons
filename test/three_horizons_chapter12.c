#include "global.h"
#include "test/test.h"
#include "three_horizons.h"
#include "event_data.h"
#include "item.h"
#include "money.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "malloc.h"
#include "constants/three_horizons.h"
#include "constants/trainers.h"
#if THREE_HORIZONS
TEST("Three Horizons playtest12 repeated Continue preserves completed earlier chapters")
{
    VarSet(VAR_TH_CLOCK_DISPLAY_HI, 0xA909);
    VarSet(VAR_TH_CLOCK_DISPLAY_LO, 12345);
    VarSet(VAR_TH_CLOCK_MODE, 1);
    VarSet(VAR_TH_SHINY_RATE, 3);
    VarSet(VAR_TH_FIRST_PARTNER, SPECIES_TORCHIC);
    VarSet(VAR_TH_RIVAL_PARTNER, SPECIES_TOTODILE);
    VarSet(VAR_TH_BROCK_GIFT, SPECIES_SQUIRTLE);
    VarSet(VAR_TH_MISTY_GIFT, SPECIES_CHIKORITA);
    FlagSet(FLAG_BADGE01_GET);
    FlagSet(FLAG_BADGE02_GET);
    FlagSet(FLAG_TH_FOSSIL_DOME);
    FlagSet(FLAG_TH_FOSSIL_HELIX);
    FlagSet(FLAG_TH_DIG_TM);
    FlagSet(FLAG_TH_ROCKET_DUO);
    FlagSet(TRAINER_FLAGS_START + TRAINER_TH11_JESSIE);
    FlagSet(TRAINER_FLAGS_START + TRAINER_TH11_JAMES);
    for (u32 pass = 0; pass < 2; pass++)
    {
        TH_MigrateSaveState();
        EXPECT_EQ(VarGet(VAR_TH_CLOCK_DISPLAY_HI), 0xA90B);
        EXPECT_EQ(VarGet(VAR_TH_CLOCK_DISPLAY_LO), 12345);
        EXPECT_EQ(VarGet(VAR_TH_CLOCK_MODE), 1);
        EXPECT_EQ(VarGet(VAR_TH_SHINY_RATE), 3);
        EXPECT_EQ(VarGet(VAR_TH_BROCK_GIFT), SPECIES_SQUIRTLE);
        EXPECT_EQ(VarGet(VAR_TH_MISTY_GIFT), SPECIES_CHIKORITA);
        EXPECT(FlagGet(FLAG_BADGE01_GET));
        EXPECT(FlagGet(FLAG_BADGE02_GET));
        EXPECT(FlagGet(FLAG_TH_FOSSIL_DOME));
        EXPECT(FlagGet(FLAG_TH_FOSSIL_HELIX));
        EXPECT(FlagGet(FLAG_TH_DIG_TM));
        EXPECT(FlagGet(FLAG_TH_ROCKET_DUO));
        EXPECT(FlagGet(TRAINER_FLAGS_START + TRAINER_TH11_JESSIE));
        EXPECT(FlagGet(TRAINER_FLAGS_START + TRAINER_TH11_JAMES));
    }
}

TEST("Three Horizons playtest12 upgrade initializes only new receipts and keeps party and boxes")
{
    u16 version;
    PARAMETRIZE { version = TH_STATE_VERSION_9; }
    PARAMETRIZE { version = TH_STATE_VERSION_10; }
    PARAMETRIZE { version = TH_STATE_VERSION_11; }
    PARAMETRIZE { version = TH_STATE_VERSION_12; }
    struct Pokemon *party = Alloc(sizeof(gPlayerParty));
    struct PokemonStorage *boxes = Alloc(sizeof(*gPokemonStoragePtr));
    EXPECT(party != NULL && boxes != NULL);
    memcpy(party, gPlayerParty, sizeof(gPlayerParty));
    memcpy(boxes, gPokemonStoragePtr, sizeof(*gPokemonStoragePtr));
    VarSet(VAR_TH_CLOCK_DISPLAY_HI, version | 1);
    VarSet(VAR_TH_CLOCK_DISPLAY_LO, 12345);
    FlagSet(FLAG_TH12_START_MONEY);
    FlagSet(FLAG_TH12_ULTRA_BALLS);
    FlagSet(FLAG_BADGE02_GET);
    FlagSet(FLAG_TH_FOSSIL_DOME);
    FlagSet(FLAG_TH_FOSSIL_HELIX);
    FlagSet(TRAINER_FLAGS_START + TRAINER_TH9_LEADER_MISTY);
    TH_MigrateSaveState();
    EXPECT_EQ(VarGet(VAR_TH_CLOCK_DISPLAY_HI), TH_STATE_VERSION_13 | 1);
    EXPECT_EQ(VarGet(VAR_TH_CLOCK_DISPLAY_LO), 12345);
    EXPECT_EQ(FlagGet(FLAG_TH12_START_MONEY), version == TH_STATE_VERSION_12);
    EXPECT_EQ(FlagGet(FLAG_TH12_ULTRA_BALLS), version == TH_STATE_VERSION_12);
    EXPECT(FlagGet(FLAG_BADGE02_GET));
    EXPECT(FlagGet(FLAG_TH_FOSSIL_DOME));
    EXPECT(FlagGet(FLAG_TH_FOSSIL_HELIX));
    EXPECT(FlagGet(TRAINER_FLAGS_START + TRAINER_TH9_LEADER_MISTY));
    EXPECT_EQ(memcmp(party, gPlayerParty, sizeof(gPlayerParty)), 0);
    EXPECT_EQ(memcmp(boxes, gPokemonStoragePtr, sizeof(*gPokemonStoragePtr)), 0);
    FlagSet(FLAG_TH12_START_MONEY);
    TH_ResetVisualClock();
    TH_MigrateSaveState();
    EXPECT(FlagGet(FLAG_TH12_START_MONEY));
    Free(party);
    Free(boxes);
}

TEST("Three Horizons playtest12 catching supplies retry a full bag without duplicate money")
{
    InitEventData();
    ClearBag();
    VarSet(VAR_TH_STAGE, TH_STAGE_COMPLETE);
    SetMoney(&gSaveBlock1Ptr->money, 3000);
    u32 capacity = gBagPockets[GetItemPocket(ITEM_POKE_BALL)].capacity;
    for (u32 i = 0; i < capacity; i++)
        EXPECT(AddBagItem(ITEM_POKE_BALL, MAX_BAG_ITEM_CAPACITY));
    TH_TryGiveChapter12Supplies();
    EXPECT(!gSpecialVar_Result);
    EXPECT_EQ(GetMoney(&gSaveBlock1Ptr->money), 5000);
    EXPECT(FlagGet(FLAG_TH12_START_MONEY));
    EXPECT(!FlagGet(FLAG_TH12_ULTRA_BALLS));
    TH_TryGiveChapter12Supplies();
    EXPECT_EQ(GetMoney(&gSaveBlock1Ptr->money), 5000);
    ClearBag();
    TH_TryGiveChapter12Supplies();
    EXPECT(gSpecialVar_Result);
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_ULTRA_BALL), 2);
    TH_TryGiveChapter12Supplies();
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_ULTRA_BALL), 2);
    EXPECT_EQ(GetMoney(&gSaveBlock1Ptr->money), 5000);
}

TEST("Three Horizons playtest12 supplies respect opening eligibility and the native money cap")
{
    InitEventData();
    ClearBag();
    SetMoney(&gSaveBlock1Ptr->money, 0);
    TH_TryGiveChapter12Supplies();
    EXPECT(!gSpecialVar_Result);
    EXPECT_EQ(GetMoney(&gSaveBlock1Ptr->money), 0);
    VarSet(VAR_TH_STAGE, TH_STAGE_PARTNER);
    SetMoney(&gSaveBlock1Ptr->money, MAX_MONEY - 1);
    TH_TryGiveChapter12Supplies();
    EXPECT(gSpecialVar_Result);
    EXPECT_EQ(GetMoney(&gSaveBlock1Ptr->money), MAX_MONEY);
    RemoveMoney(&gSaveBlock1Ptr->money, 2000);
    TH_TryGiveChapter12Supplies();
    EXPECT_EQ(GetMoney(&gSaveBlock1Ptr->money), MAX_MONEY - 2000);
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_ULTRA_BALL), 2);
}
#endif
