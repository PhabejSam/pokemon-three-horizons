#include "global.h"
#include "test/test.h"
#include "three_horizons.h"
#include "event_data.h"
#include "malloc.h"
#include "item.h"
#include "money.h"
#include "pokedex.h"
#include "constants/pokedex.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "constants/trainers.h"
#include "constants/three_horizons.h"
#if THREE_HORIZONS
TEST("Three Horizons RC2 state preserves RC1 receipts and clears only newly owned flags")
{
    InitEventData(); ClearBag();
    VarSet(VAR_TH_CLOCK_DISPLAY_HI, TH_STATE_VERSION_13 | 1);
    FlagSet(FLAG_TH13_GEAR); FlagSet(FLAG_TH13_PHOTO_FOREST_PAIR);
    FlagSet(FLAG_TH13_FLASH); FlagSet(FLAG_TH13_CALL_ACTIVATION_DELIVERED);
    FlagSet(FLAG_TH13_CALL_ROUTE10_DELIVERED);
    FlagSet(TRAINER_FLAGS_START + TRAINER_TH_BROCK);
    for (u32 flag = TH13_RC2_FLAGS_START; flag <= TH13_RC2_FLAGS_END; flag++) FlagSet(flag);
    TH_MigrateSaveState();
    EXPECT_EQ(VarGet(VAR_TH_CLOCK_DISPLAY_HI), TH_STATE_VERSION_CURRENT | 1);
    EXPECT(FlagGet(FLAG_TH13_GEAR)); EXPECT(FlagGet(FLAG_TH13_PHOTO_FOREST_PAIR));
    EXPECT(FlagGet(FLAG_TH13_FLASH)); EXPECT(FlagGet(FLAG_TH13_CALL_ROUTE10_DELIVERED));
    // RC1 activation really delivered all three professors; retain familiarity.
    EXPECT(FlagGet(FLAG_TH13_CALL_ELM_DELIVERED));
    EXPECT(FlagGet(FLAG_TH13_CALL_BIRCH_DELIVERED));
    EXPECT(!FlagGet(FLAG_TH13_CALL_ELM_PENDING)); EXPECT(!FlagGet(FLAG_TH13_CALL_BIRCH_PENDING));
    EXPECT(FlagGet(TRAINER_FLAGS_START + TRAINER_TH_BROCK));
    u8 flags[NUM_FLAG_BYTES]; memcpy(flags, gSaveBlock1Ptr->flags, sizeof(flags));
    TH_MigrateSaveState(); EXPECT_EQ(memcmp(flags, gSaveBlock1Ptr->flags, sizeof(flags)), 0);
    EXPECT_EQ(sizeof(struct SaveBlock1), 15568); EXPECT_EQ(sizeof(struct SaveBlock2), 3884);
}

TEST("Three Horizons RC2 state never treats its current marker as a legacy save")
{
    InitEventData(); ClearBag();
    VarSet(VAR_TH_CLOCK_DISPLAY_HI, TH_STATE_VERSION_CURRENT);
    FlagSet(FLAG_TH_ROCKET_DUO); FlagSet(FLAG_TH13_GEAR);
    FlagSet(FLAG_TH13_PHOTO_HOOTHOOT); FlagSet(FLAG_TH13_CALL_ELM_PENDING);
    FlagSet(FLAG_TH13_CALL_BIRCH_DELIVERED);
    u8 flags[NUM_FLAG_BYTES]; memcpy(flags, gSaveBlock1Ptr->flags, sizeof(flags));
    TH_MigrateSaveState();
    EXPECT_EQ(memcmp(flags, gSaveBlock1Ptr->flags, sizeof(flags)), 0);
    EXPECT_EQ(VarGet(VAR_TH_CLOCK_DISPLAY_HI), TH_STATE_VERSION_CURRENT);
}

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
    InitEventData();
    ClearBag();
    u8 attackEv = 252;
    u16 heldItem = ITEM_POWER_BRACER;
    static const u8 nickname[] = _("Lavender");
    CreateMonWithIVs(&gPlayerParty[0], first, 35, 0x3FFFFFFF, OTID_STRUCT_PLAYER_ID, 123);
    SetMonData(&gPlayerParty[0], MON_DATA_ATK_EV, &attackEv);
    SetMonData(&gPlayerParty[0], MON_DATA_HELD_ITEM, &heldItem);
    SetMonData(&gPlayerParty[0], MON_DATA_NICKNAME, nickname);
    gPokemonStoragePtr->boxes[0][0] = gPlayerParty[0].box;
    SetMoney(&gSaveBlock1Ptr->money, 54321);
    EXPECT(AddBagItem(ITEM_HM01, 1));
    EXPECT(AddBagItem(ITEM_OLD_ROD, 1));
    FlagSet(FLAG_BADGE01_GET);
    FlagSet(FLAG_BADGE02_GET);
    FlagSet(FLAG_BADGE03_GET);
    FlagSet(FLAG_TH_ROCKET_DUO);
    FlagSet(FLAG_TH_FOSSIL_DOME);
    FlagSet(FLAG_TH_FOSSIL_HELIX);
    VarSet(VAR_TH_TRAINING_KIT_MASK, 0x7F);
    GetSetPokedexFlag(NATIONAL_DEX_PIKACHU, FLAG_SET_CAUGHT);
    VarSet(VAR_TH_FIRST_PARTNER, first);
    VarSet(VAR_TH_RIVAL_PARTNER, first);
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
    EXPECT_EQ(VarGet(VAR_TH_CLOCK_DISPLAY_HI), TH_STATE_VERSION_CURRENT | 1);
    EXPECT_EQ(VarGet(VAR_TH_CLOCK_DISPLAY_LO), 12345);
    // Normalize only the explicitly newly owned bits and version, then compare
    // every byte. This catches accidental changes to money, items, Dex, flags,
    // settings, existing trainer wins, saved party and reserved old fields.
    for (u32 flag = TH13_FLAGS_START; flag <= TH13_RC2_FLAGS_END; flag++)
    {
        u8 bit = 1 << (flag % 8);
        before->flags[flag / 8] = (before->flags[flag / 8] & ~bit)
            | (gSaveBlock1Ptr->flags[flag / 8] & bit);
    }
    before->vars[VAR_TH_CLOCK_DISPLAY_HI - VARS_START] = TH_STATE_VERSION_CURRENT | 1;
    EXPECT_EQ(memcmp(before, gSaveBlock1Ptr, sizeof(*before)), 0);
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

TEST("Three Horizons playtest13 state remains current after clock update")
{
    VarSet(VAR_TH_CLOCK_DISPLAY_HI, 0xA90B);
    TH_ResetVisualClock();
    EXPECT_EQ(VarGet(VAR_TH_CLOCK_DISPLAY_HI) & 0xFFFE, TH_STATE_VERSION_CURRENT);
    TH_GetVisualTimeSeconds();
    EXPECT_EQ(VarGet(VAR_TH_CLOCK_DISPLAY_HI) & 0xFFFE, TH_STATE_VERSION_CURRENT);
}
TEST("Three Horizons playtest13 state initializes dirty slots only on upgrade")
{
    u16 version;
    PARAMETRIZE { version = 0; }
    PARAMETRIZE { version = TH_STATE_VERSION_9; }
    PARAMETRIZE { version = TH_STATE_VERSION_10; }
    PARAMETRIZE { version = TH_STATE_VERSION_11; }
    PARAMETRIZE { version = TH_STATE_VERSION_12; }
    PARAMETRIZE { version = TH_STATE_VERSION_13; }
    PARAMETRIZE { version = TH_STATE_VERSION_13_1; }
    InitEventData();
    ClearBag();
    VarSet(VAR_TH_CLOCK_DISPLAY_HI, version | 1);
    for (u32 flag = TH13_FLAGS_START; flag <= TH13_FLAGS_END; flag++)
        FlagSet(flag);
    TH_MigrateSaveState();
    EXPECT_EQ(VarGet(VAR_TH_CLOCK_DISPLAY_HI) & 0xFFFE, TH_STATE_VERSION_CURRENT);
    for (u32 flag = TH13_FLAGS_START; flag <= TH13_FLAGS_END; flag++)
        EXPECT_EQ(FlagGet(flag), version == TH_STATE_VERSION_13 || version == TH_STATE_VERSION_13_1);
    FlagSet(FLAG_TH13_PHOTO_LAVENDER);
    TH_MigrateSaveState();
    EXPECT(FlagGet(FLAG_TH13_PHOTO_LAVENDER));
}

TEST("Three Horizons playtest13 state imports witnessed reports without inventing photos")
{
    InitEventData();
    ClearBag();
    VarSet(VAR_TH_CLOCK_DISPLAY_HI, TH_STATE_VERSION_12);
    VarSet(VAR_TH_SIGHTING_SEEN, 1);
    FlagSet(FLAG_TH12_FOREST_SEEN);
    FlagSet(FLAG_TH12_CAVE_SEEN);
    EXPECT(AddBagItem(ITEM_HM05, 1));
    TH_MigrateSaveState();
    EXPECT(FlagGet(FLAG_TH13_OBS_HOOTHOOT));
    EXPECT(FlagGet(FLAG_TH13_OBS_FOREST_LEGACY));
    EXPECT(!FlagGet(FLAG_TH13_OBS_FOREST_TREECKO));
    EXPECT(!FlagGet(FLAG_TH13_OBS_FOREST_SHROOMISH));
    EXPECT(FlagGet(FLAG_TH13_OBS_MT_MOON));
    EXPECT(!FlagGet(FLAG_TH13_OBS_SHIP));
    EXPECT(!FlagGet(FLAG_TH13_SHIP_DEPARTED));
    EXPECT(!FlagGet(FLAG_TH13_GEAR));
    EXPECT(FlagGet(FLAG_TH13_FLASH));
    EXPECT(CheckBagHasItem(ITEM_HM05, 1));
    for (u32 flag = FLAG_TH13_PHOTO_HOOTHOOT; flag <= FLAG_TH13_PHOTO_LAVENDER; flag++)
        EXPECT(!FlagGet(flag));
}
TEST("Three Horizons playtest13 migration initializes new trainer wins once and preserves old wins")
{
    u16 version;
    PARAMETRIZE { version = TH_STATE_VERSION_12; }
    PARAMETRIZE { version = TH_STATE_VERSION_13; }
    PARAMETRIZE { version = TH_STATE_VERSION_13_1; }
    InitEventData();
    ClearBag();
    VarSet(VAR_TH_CLOCK_DISPLAY_HI, version | 1);
    // Audited P13-only first-battle IDs: Route11 through Tower Emilia.
    // Fill every trainer bit to simulate arbitrary old unused storage.
    for (u32 trainer = 1; trainer < TRAINERS_COUNT; trainer++)
        FlagSet(TRAINER_FLAGS_START + trainer);
    TH_MigrateSaveState();
    for (u32 trainer = 1; trainer < TRAINERS_COUNT; trainer++)
        EXPECT_EQ(FlagGet(TRAINER_FLAGS_START + trainer),
            (version == TH_STATE_VERSION_13 || version == TH_STATE_VERSION_13_1 || trainer < 104 || trainer > 156)
            && (trainer < 157 || trainer > 194));
    EXPECT_EQ(VarGet(VAR_TH_CLOCK_DISPLAY_HI), TH_STATE_VERSION_CURRENT | 1);
    // Actual P13 and new P14 wins survive every subsequent Continue.
    for (u32 trainer = 104; trainer <= 194; trainer++)
        FlagSet(TRAINER_FLAGS_START + trainer);
    TH_MigrateSaveState();
    for (u32 trainer = 1; trainer < TRAINERS_COUNT; trainer++)
        EXPECT(FlagGet(TRAINER_FLAGS_START + trainer));
}
#endif
