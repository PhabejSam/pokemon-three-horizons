#include "global.h"
#include "test/test.h"
#include "three_horizons.h"
#include "event_data.h"
#include "malloc.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "constants/trainers.h"
#include "constants/three_horizons.h"
#if THREE_HORIZONS
TEST("Three Horizons revision9 legacy state migration preserves established progress")
{
    VarSet(VAR_TH_STAGE,TH_STAGE_COMPLETE);
    VarSet(VAR_TH_FIRST_PARTNER,SPECIES_TORCHIC);
    VarSet(VAR_TH_RIVAL_PARTNER,SPECIES_TOTODILE);
    VarSet(VAR_TH_TRAINING_KIT_MASK,0x7F);
    FlagSet(FLAG_BADGE01_GET);
    FlagSet(FLAG_SET_WALL_CLOCK);
    FlagSet(I_EXP_SHARE_FLAG);
    VarSet(VAR_TH_BROCK_GIFT,0xFFFF);
    VarSet(VAR_TH_MISTY_GIFT,0xFFFF);
    VarSet(VAR_TH_SHINY_RATE,0xFFFF);
    VarSet(VAR_TH_CLOCK_MODE,0x0101);
    VarSet(VAR_TH_CLOCK_DISPLAY_HI,0xFFFF);
    FlagSet(FLAG_TH_CLOCK_ANCHORED);
    FlagSet(FLAG_TH_MAGIKARP);
    FlagSet(FLAG_TH_PICKUP_0);
    TH_MigrateSaveState();
    EXPECT_EQ(VarGet(VAR_TH_BROCK_GIFT),0);
    EXPECT_EQ(VarGet(VAR_TH_MISTY_GIFT),0);
    EXPECT_EQ(VarGet(VAR_TH_CLOCK_MODE),0);
    EXPECT_EQ(VarGet(VAR_TH_SHINY_RATE),0);
    EXPECT(!FlagGet(FLAG_TH_CLOCK_ANCHORED));
    EXPECT(!FlagGet(FLAG_TH_MAGIKARP));
    EXPECT(!FlagGet(FLAG_TH_PICKUP_0));
    EXPECT_EQ(VarGet(VAR_TH_FIRST_PARTNER),SPECIES_TORCHIC);
    EXPECT_EQ(VarGet(VAR_TH_RIVAL_PARTNER),SPECIES_TOTODILE);
    EXPECT_EQ(VarGet(VAR_TH_STAGE),TH_STAGE_COMPLETE);
    EXPECT_EQ(VarGet(VAR_TH_TRAINING_KIT_MASK),0x7F);
    EXPECT(FlagGet(FLAG_BADGE01_GET));
    EXPECT(FlagGet(FLAG_SET_WALL_CLOCK));
    EXPECT(FlagGet(I_EXP_SHARE_FLAG));
    VarSet(VAR_TH_BROCK_GIFT,SPECIES_SQUIRTLE);
    VarSet(VAR_TH_MISTY_GIFT,SPECIES_CHIKORITA);
    FlagSet(FLAG_TH_MAGIKARP);
    TH_MigrateSaveState();
    EXPECT_EQ(VarGet(VAR_TH_BROCK_GIFT),SPECIES_SQUIRTLE);
    EXPECT_EQ(VarGet(VAR_TH_MISTY_GIFT),SPECIES_CHIKORITA);
    EXPECT(FlagGet(FLAG_TH_MAGIKARP));
    TH_ResetVisualClock();
    TH_MigrateSaveState();
    EXPECT_EQ(VarGet(VAR_TH_BROCK_GIFT),SPECIES_SQUIRTLE);
    EXPECT_EQ(VarGet(VAR_TH_MISTY_GIFT),SPECIES_CHIKORITA);
    EXPECT(FlagGet(FLAG_TH_MAGIKARP));
    VarSet(VAR_TH_BROCK_GIFT,0xFFFF);
    TH_MigrateSaveState();
    EXPECT_EQ(VarGet(VAR_TH_BROCK_GIFT),0);
    EXPECT_EQ(VarGet(VAR_TH_MISTY_GIFT),0);
}
TEST("Three Horizons revision9 invalid full-width clock mode uses real time")
{
    volatile u16 invalid=0x0101;
    EXPECT_EQ(TH_AdvanceVisualClock(100,200,160,invalid),260);
}
TEST("Three Horizons playtest13 state migration preserves P12 payload")
{
    u16 first;
    PARAMETRIZE { first = SPECIES_BULBASAUR; }
    PARAMETRIZE { first = SPECIES_CHARMANDER; }
    PARAMETRIZE { first = SPECIES_SQUIRTLE; }
    PARAMETRIZE { first = SPECIES_CHIKORITA; }
    PARAMETRIZE { first = SPECIES_CYNDAQUIL; }
    PARAMETRIZE { first = SPECIES_TOTODILE; }
    PARAMETRIZE { first = SPECIES_TREECKO; }
    PARAMETRIZE { first = SPECIES_TORCHIC; }
    PARAMETRIZE { first = SPECIES_MUDKIP; }
    struct SaveBlock1 *before = Alloc(sizeof(*before));
    struct SaveBlock2 *before2 = Alloc(sizeof(*before2));
    struct PokemonStorage *boxes = Alloc(sizeof(*boxes));
    struct Pokemon party[PARTY_SIZE];
    EXPECT(before != NULL && before2 != NULL && boxes != NULL);
    VarSet(VAR_TH_FIRST_PARTNER, first);
    VarSet(VAR_TH_BROCK_GIFT, TH_GetBrockGift(first, 0));
    VarSet(VAR_TH_MISTY_GIFT, TH_GetMistyGift(first, VarGet(VAR_TH_BROCK_GIFT)));
    VarSet(VAR_TH_CLOCK_MODE, 1);
    VarSet(VAR_TH_SHINY_RATE, 3);
    VarSet(VAR_TH_CLOCK_DISPLAY_HI, 0xA909);
    VarSet(VAR_TH_CLOCK_DISPLAY_LO, 12345);
    // Preserve the entire old payload, including all P12 receipt combinations.
    for (u32 flag = TH12_FLAGS_START; flag <= TH12_FLAGS_END; flag++)
        FlagSet(flag);
    for (u32 trainer = TH12_TRAINERS_START; trainer <= TH12_TRAINERS_END; trainer++)
        FlagSet(TRAINER_FLAGS_START + trainer);
    memcpy(before, gSaveBlock1Ptr, sizeof(*before));
    memcpy(before2, gSaveBlock2Ptr, sizeof(*before2));
    memcpy(boxes, gPokemonStoragePtr, sizeof(*boxes));
    memcpy(party, gPlayerParty, sizeof(party));
    TH_MigrateSaveState();
    EXPECT_EQ(VarGet(VAR_TH_CLOCK_DISPLAY_HI), 0xA90B);
    EXPECT_EQ(VarGet(VAR_TH_CLOCK_DISPLAY_LO), 12345);
    // New state is checked separately; old flags/vars and all other bytes survive.
    EXPECT_EQ(memcmp(before2, gSaveBlock2Ptr, sizeof(*before2)), 0);
    EXPECT_EQ(memcmp(boxes, gPokemonStoragePtr, sizeof(*boxes)), 0);
    EXPECT_EQ(memcmp(party, gPlayerParty, sizeof(party)), 0);
    for (u32 flag = TH12_FLAGS_START; flag <= TH12_FLAGS_END; flag++)
        EXPECT(FlagGet(flag));
    for (u32 trainer = TH12_TRAINERS_START; trainer <= TH12_TRAINERS_END; trainer++)
        EXPECT(FlagGet(TRAINER_FLAGS_START + trainer));
    memcpy(before, gSaveBlock1Ptr, sizeof(*before));
    TH_MigrateSaveState();
    EXPECT_EQ(memcmp(before, gSaveBlock1Ptr, sizeof(*before)), 0);
    Free(boxes);
    Free(before2);
    Free(before);
}

TEST("Three Horizons playtest13 state remains version13 after clock update")
{
    VarSet(VAR_TH_CLOCK_DISPLAY_HI, 0xA90B);
    TH_ResetVisualClock();
    EXPECT_EQ(VarGet(VAR_TH_CLOCK_DISPLAY_HI) & 0xFFFE, 0xA90A);
    TH_GetVisualTimeSeconds();
    EXPECT_EQ(VarGet(VAR_TH_CLOCK_DISPLAY_HI) & 0xFFFE, 0xA90A);
}
#endif
