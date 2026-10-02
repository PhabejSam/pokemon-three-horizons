#include "global.h"
#include "test/test.h"
#include "three_horizons.h"
#include "three_horizons_chapter14.h"
#include "event_data.h"
#include "malloc.h"
#include "item.h"
#include "money.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "constants/three_horizons.h"

#if THREE_HORIZONS
// Independent approved save contract, usable against the pre-PT14 ROM too.
// This catches a skipped initialization, an overbroad reset, or an old gate
// mistakenly treating the new marker as a legacy save.
static bool32 IsPT14Receipt(u32 flag)
{
    return (flag >= 0x8E5 && flag <= 0x91E)
        || (flag >= 0x881 && flag <= 0x887) || flag == 0x88E;
}

static void ExpectedClearFlag(struct SaveBlock1 *save, u32 flag)
{
    save->flags[flag / 8] &= ~(1 << (flag % 8));
}

static void PrepareMigration(u16 version)
{
    InitEventData();
    ClearBag();
    VarSet(VAR_TH_CLOCK_DISPLAY_HI, version);
    VarSet(VAR_TH_FIRST_PARTNER, SPECIES_TORCHIC);
    VarSet(VAR_TH_RIVAL_PARTNER, SPECIES_TOTODILE);
    VarSet(VAR_TH_BROCK_GIFT, SPECIES_SQUIRTLE);
    VarSet(VAR_TH_MISTY_GIFT, SPECIES_CHIKORITA);
    VarSet(VAR_TH_CLOCK_MODE, 1);
    VarSet(VAR_TH_SHINY_RATE, 3);
    VarSet(VAR_TH_CLOCK_DISPLAY_LO, 23456);
    VarSet(VAR_TH_TRAINING_KIT_MASK, 0x7F);
    FlagSet(FLAG_BADGE01_GET);
    FlagSet(FLAG_BADGE02_GET);
    FlagSet(FLAG_BADGE03_GET);
    FlagSet(FLAG_TH_FOSSIL_DOME);
    FlagSet(FLAG_TH_FOSSIL_HELIX);
    FlagSet(FLAG_TH_ROCKET_DUO);
    FlagSet(FLAG_TH12_BILL_RESCUED);
    FlagSet(FLAG_TH13_GEAR);
    FlagSet(FLAG_TH13_PHOTO_LAVENDER);
    FlagSet(FLAG_TH13_CALL_ELM_PENDING);
    FlagSet(I_EXP_SHARE_FLAG);
    // These remain unassigned. A whole-pool reset would destroy them.
    FlagSet(0x88F); FlagSet(0x8E3); FlagSet(0x4F9); FlagSet(0x4FA);
    for (u32 flag = 0; flag < NUM_FLAG_BYTES * 8; flag++)
        if (IsPT14Receipt(flag)) FlagSet(flag);
    for (u32 trainer = 1; trainer < 864; trainer++)
        FlagSet(0x500 + trainer);
    SetMoney(&gSaveBlock1Ptr->money, 28106);
    EXPECT(AddBagItem(ITEM_HM01, 1));
    EXPECT(AddBagItem(ITEM_POKE_BALL, 17));
    CreateMonWithIVs(&gParties[B_TRAINER_PLAYER][0], SPECIES_GYARADOS, 51, 0x3FFFFFFF,
                    OTID_STRUCT_PLAYER_ID, 123);
    u8 ev = 252;
    u16 item = ITEM_POWER_BRACER;
    static const u8 nickname[] = _("Preserve");
    SetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_ATK_EV, &ev);
    SetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_HELD_ITEM, &item);
    SetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_NICKNAME, nickname);
    for (u32 box = 0; box < TOTAL_BOXES_COUNT; box++)
        gPokemonStoragePtr->boxes[box][box % IN_BOX_COUNT] = gParties[B_TRAINER_PLAYER][0].box;
    gPartiesCount[B_TRAINER_PLAYER] = 1;
    gSaveBlock1Ptr->playerPartyCount = 1;
    memcpy(gSaveBlock1Ptr->playerParty, gParties[B_TRAINER_PLAYER], sizeof(gParties[B_TRAINER_PLAYER]));
    gSaveBlock1Ptr->location.mapGroup = 75;
    gSaveBlock1Ptr->location.mapNum = 0;
}

TEST("Three Horizons PT14 state: legacy import touches only owned state")
{
    u16 version;
    PARAMETRIZE { version = 0xA902; }
    PARAMETRIZE { version = 0xA903; }
    PARAMETRIZE { version = 0xA904; }
    PARAMETRIZE { version = 0xA905; }
    PARAMETRIZE { version = 0xA906; }
    PARAMETRIZE { version = 0xA907; }
    PARAMETRIZE { version = 0xA908; }
    PARAMETRIZE { version = 0xA909; }
    PARAMETRIZE { version = 0xA90A; }
    PARAMETRIZE { version = 0xA90B; }
    PARAMETRIZE { version = 0xA90C; }
    PARAMETRIZE { version = 0xA90D; }
    PrepareMigration(version);
    struct SaveBlock1 *expected = Alloc(sizeof(*expected));
    struct SaveBlock2 *old2 = Alloc(sizeof(*old2));
    struct PokemonStorage *boxes = Alloc(sizeof(*boxes));
    EXPECT(expected != NULL && old2 != NULL && boxes != NULL);
    memcpy(expected, gSaveBlock1Ptr, sizeof(*expected));
    memcpy(old2, gSaveBlock2Ptr, sizeof(*old2));
    memcpy(boxes, gPokemonStoragePtr, sizeof(*boxes));
    struct Pokemon party[PARTY_SIZE];
    memcpy(party, gParties[B_TRAINER_PLAYER], sizeof(party));
    for (u32 flag = 0; flag < NUM_FLAG_BYTES * 8; flag++)
        if (IsPT14Receipt(flag)) ExpectedClearFlag(expected, flag);
    for (u32 trainer = 157; trainer <= 194; trainer++)
        ExpectedClearFlag(expected, 0x500 + trainer);
    if ((version & 0xFFFE) < 0xA904)
        ExpectedClearFlag(expected, 0x4F);
    if ((version & 0xFFFE) < 0xA906)
    {
        ExpectedClearFlag(expected, 0x54);
        ExpectedClearFlag(expected, 0x500 + 51);
        ExpectedClearFlag(expected, 0x500 + 52);
    }
    if ((version & 0xFFFE) < 0xA908)
    {
        for (u32 flag = 0x265; flag <= 0x2BB; flag++) ExpectedClearFlag(expected, flag);
        for (u32 trainer = 53; trainer <= 103; trainer++) ExpectedClearFlag(expected, 0x500 + trainer);
    }
    if ((version & 0xFFFE) <= 0xA908)
    {
        for (u32 flag = 0x493; flag <= 0x4EB; flag++) ExpectedClearFlag(expected, flag);
        for (u32 trainer = 104; trainer <= 156; trainer++) ExpectedClearFlag(expected, 0x500 + trainer);
    }
    if ((version & 0xFFFE) != 0xA90C)
        for (u32 flag = 0x4EC; flag <= 0x4EF; flag++) ExpectedClearFlag(expected, flag);
    expected->vars[VAR_TH_CLOCK_DISPLAY_HI - VARS_START] = 0xA90E | (version & 1);
    TH_MigrateSaveState();
    EXPECT_EQ(VarGet(VAR_TH_CLOCK_DISPLAY_HI), 0xA90E | (version & 1));
    EXPECT_EQ(memcmp(expected, gSaveBlock1Ptr, sizeof(*expected)), 0);
    EXPECT_EQ(memcmp(old2, gSaveBlock2Ptr, sizeof(*old2)), 0);
    EXPECT_EQ(memcmp(boxes, gPokemonStoragePtr, sizeof(*boxes)), 0);
    EXPECT_EQ(memcmp(party, gParties[B_TRAINER_PLAYER], sizeof(party)), 0);
    EXPECT(!FlagGet(FLAG_TH13_SHIP_DEPARTED));
    EXPECT(!FlagGet(FLAG_TH13_PHOTO_SHIP));
    Free(boxes); Free(old2); Free(expected);
}

TEST("Three Horizons PT14 state: current marker preserves receipts on repeated Continue")
{
    u16 version;
    PARAMETRIZE { version = 0xA90E; }
    PARAMETRIZE { version = 0xA90F; }
    PrepareMigration(version);
    // Positive witnessed state must survive too; the legacy cases above
    // separately prove that false ship/photo receipts are not fabricated.
    FlagSet(FLAG_TH13_SHIP_DEPARTED);
    FlagSet(FLAG_TH13_PHOTO_SHIP);
    struct SaveBlock1 *old1 = Alloc(sizeof(*old1));
    struct SaveBlock2 *old2 = Alloc(sizeof(*old2));
    struct PokemonStorage *boxes = Alloc(sizeof(*boxes));
    EXPECT(old1 != NULL && old2 != NULL && boxes != NULL);
    memcpy(old1, gSaveBlock1Ptr, sizeof(*old1));
    memcpy(old2, gSaveBlock2Ptr, sizeof(*old2));
    memcpy(boxes, gPokemonStoragePtr, sizeof(*boxes));
    for (u32 repeat = 0; repeat < 3; repeat++)
    {
        TH_MigrateSaveState();
        EXPECT_EQ(memcmp(old1, gSaveBlock1Ptr, sizeof(*old1)), 0);
        EXPECT_EQ(memcmp(old2, gSaveBlock2Ptr, sizeof(*old2)), 0);
        EXPECT_EQ(memcmp(boxes, gPokemonStoragePtr, sizeof(*boxes)), 0);
    }
    Free(boxes); Free(old2); Free(old1);
}

TEST("Three Horizons PT14 state: new game initializes chapter bits without touching reserves")
{
    InitEventData(); ClearBag();
    for (u32 flag = 0; flag < NUM_FLAG_BYTES * 8; flag++)
        if (IsPT14Receipt(flag)) FlagSet(flag);
    FlagSet(0x88F); FlagSet(0x8E3); FlagSet(0x4F9); FlagSet(0x4FA);
    FlagSet(I_EXP_SHARE_FLAG);
    VarSet(VAR_TH_FIRST_PARTNER, SPECIES_TORCHIC);
    VarSet(VAR_TH_STAGE, TH_STAGE_COMPLETE);
    TH_MigrateSaveState();
    EXPECT_EQ(VarGet(VAR_TH_CLOCK_DISPLAY_HI), 0xA90E);
    for (u32 flag = 0; flag < NUM_FLAG_BYTES * 8; flag++)
        if (IsPT14Receipt(flag)) EXPECT(!FlagGet(flag));
    EXPECT(FlagGet(0x88F)); EXPECT(FlagGet(0x8E3));
    EXPECT(FlagGet(0x4F9)); EXPECT(FlagGet(0x4FA));
    EXPECT(FlagGet(I_EXP_SHARE_FLAG));
    EXPECT_EQ(VarGet(VAR_TH_FIRST_PARTNER), SPECIES_TORCHIC);
    EXPECT_EQ(VarGet(VAR_TH_STAGE), TH_STAGE_COMPLETE);
    EXPECT(!FlagGet(FLAG_TH13_SHIP_DEPARTED));
    EXPECT(!FlagGet(FLAG_TH13_PHOTO_SHIP));
}
TEST("Three Horizons PT14 state: map family predicate rejects every out-of-range identity")
{
    for (u32 group = 0; group < 256; group++)
        for (u32 map = 0; map < 256; map++)
            EXPECT_EQ(TH_IsProjectMap(group, map),
                (group == 75 && map < 118) || (group == 76 && map < 37));
}

TEST("Three Horizons PT14 state: field and daily reset preserve every chapter receipt")
{
    InitEventData();
    for (u32 flag = 0; flag < NUM_FLAG_BYTES * 8; flag++)
        if (IsPT14Receipt(flag)) FlagSet(flag);
    FlagSet(FLAG_TEMP_1);
    FlagSet(DAILY_FLAGS_START);
    ClearTempFieldEventData();
    EXPECT(!FlagGet(FLAG_TEMP_1));
    for (u32 flag = 0; flag < NUM_FLAG_BYTES * 8; flag++)
        if (IsPT14Receipt(flag)) EXPECT(FlagGet(flag));
    ClearDailyFlags();
    EXPECT(!FlagGet(DAILY_FLAGS_START));
    for (u32 flag = 0; flag < NUM_FLAG_BYTES * 8; flag++)
        if (IsPT14Receipt(flag)) EXPECT(FlagGet(flag));
}

#endif
