#include "global.h"
#include "test/test.h"
#include "three_horizons.h"
#include "event_data.h"
#include "pokemon.h"
#include "data.h"
#include "pokemon_storage_system.h"
#include "script.h"
#include "constants/script_commands.h"
#include "constants/trainers.h"
#include "constants/three_horizons.h"
#include "three_horizons_helpers.h"

#if THREE_HORIZONS
extern const u8 TH12_RocketSelectFormat[];
extern const u8 TH12_RocketSingleIntro[];
extern const u8 TH_RocketDuoIntro[];

TEST("Three Horizons playtest13 Rocket individual records permit singles")
{
    const struct Trainer *jessie = TH_TestGetActualTrainer(TRAINER_TH11_JESSIE);
    const struct Trainer *james = TH_TestGetActualTrainer(TRAINER_TH11_JAMES);
    EXPECT_EQ((u32)jessie->partySize, 1);
    EXPECT_EQ((u32)james->partySize, 1);
    EXPECT_EQ((u32)jessie->battleType, TRAINER_BATTLE_TYPE_SINGLES);
    EXPECT_EQ((u32)james->battleType, TRAINER_BATTLE_TYPE_SINGLES);
}

TEST("Three Horizons playtest13 Rocket usable party selects approved format")
{
    u32 usable;
    PARAMETRIZE { usable = 0; }
    PARAMETRIZE { usable = 1; }
    PARAMETRIZE { usable = 2; }
    PARAMETRIZE { usable = 6; }
    struct Pokemon saved[PARTY_SIZE];
    struct ScriptContext ctx;
    memcpy(saved, gPlayerParty, sizeof(saved));
    for (u32 i = 0; i < PARTY_SIZE; i++)
    {
        CreateMonWithIVs(&gPlayerParty[i], SPECIES_PIKACHU, 20, 0, OTID_STRUCT_PLAYER_ID, 31);
        if (i >= usable)
        {
            if (i & 1)
            {
                u32 egg = TRUE;
                SetMonData(&gPlayerParty[i], MON_DATA_IS_EGG, &egg);
            }
            else
            {
                u16 hp = 0;
                SetMonData(&gPlayerParty[i], MON_DATA_HP, &hp);
            }
        }
    }
    CalculatePlayerPartyCount();
    gSpecialVar_0x8004 = PARTY_SIZE;
    gSpecialVar_Result = CountPartyAliveNonEggMons_IgnoreVar0x8004Slot();
    EXPECT_EQ(gSpecialVar_Result, usable);
    // Execute the real branch after its verified count-special prefix.
    EXPECT_EQ(TH12_RocketSelectFormat[0], SCR_OP_SETVAR);
    EXPECT_EQ(TH12_RocketSelectFormat[5], SCR_OP_SPECIALVAR);
    EXPECT(RunScriptImmediatelyUntilEffect(SCREFF_V1 | SCREFF_ANY, TH12_RocketSelectFormat + 10, &ctx));
    EXPECT(ctx.data[0] != 0);
    if (usable == 1)
        EXPECT_EQ(ctx.data[0], (u32)TH12_RocketSingleIntro);
    else if (usable >= 2)
        EXPECT_EQ(ctx.data[0], (u32)TH_RocketDuoIntro);
    else
    {
        EXPECT_NE(ctx.data[0], (u32)TH12_RocketSingleIntro);
        EXPECT_NE(ctx.data[0], (u32)TH_RocketDuoIntro);
    }
    memcpy(gPlayerParty, saved, sizeof(saved));
    CalculatePlayerPartyCount();
}

TEST("Three Horizons playtest13 Rocket single handoff does not heal or finish pair")
{
    struct Pokemon saved[PARTY_SIZE], handoff[PARTY_SIZE];
    memcpy(saved, gPlayerParty, sizeof(saved));
    InitEventData();
    CreateMon(&gPlayerParty[0], SPECIES_PIKACHU, 20, 0, OTID_STRUCT_PLAYER_ID);
    u16 hp = 7;
    u32 status = STATUS1_POISON;
    u8 pp = 2;
    SetMonData(&gPlayerParty[0], MON_DATA_HP, &hp);
    SetMonData(&gPlayerParty[0], MON_DATA_STATUS, &status);
    SetMonData(&gPlayerParty[0], MON_DATA_PP1, &pp);
    memcpy(handoff, gPlayerParty, sizeof(handoff));
    FlagSet(TRAINER_FLAGS_START + TRAINER_TH11_JESSIE);
    TH12_CompleteRocketPair();
    EXPECT(!gSpecialVar_Result);
    EXPECT(!FlagGet(FLAG_TH_ROCKET_DUO));
    EXPECT_EQ(memcmp(handoff, gPlayerParty, sizeof(handoff)), 0);
    // James loss, including Continue before retry, restarts both opponents.
    TH12_BeginRocketPair();
    EXPECT(!FlagGet(TRAINER_FLAGS_START + TRAINER_TH11_JESSIE));
    EXPECT(!FlagGet(TRAINER_FLAGS_START + TRAINER_TH11_JAMES));
    EXPECT_EQ(memcmp(handoff, gPlayerParty, sizeof(handoff)), 0);
    FlagSet(TRAINER_FLAGS_START + TRAINER_TH11_JESSIE);
    FlagSet(TRAINER_FLAGS_START + TRAINER_TH11_JAMES);
    TH12_CompleteRocketPair();
    EXPECT(FlagGet(FLAG_TH_ROCKET_DUO));
    TH12_BeginRocketPair();
    EXPECT(FlagGet(TRAINER_FLAGS_START + TRAINER_TH11_JESSIE));
    EXPECT(FlagGet(TRAINER_FLAGS_START + TRAINER_TH11_JAMES));
    EXPECT_EQ(memcmp(handoff, gPlayerParty, sizeof(handoff)), 0);
    memcpy(gPlayerParty, saved, sizeof(saved));
    CalculatePlayerPartyCount();
    InitEventData();
}
TEST("Three Horizons playtest13 Rocket double loss retries complete encounter")
{
    u32 partial;
    PARAMETRIZE { partial = 0; }
    PARAMETRIZE { partial = 1; }
    PARAMETRIZE { partial = 2; }
    InitEventData();
    if (partial & 1) FlagSet(TRAINER_FLAGS_START + TRAINER_TH11_JESSIE);
    if (partial & 2) FlagSet(TRAINER_FLAGS_START + TRAINER_TH11_JAMES);
    TH12_CompleteRocketPair();
    EXPECT(!gSpecialVar_Result);
    EXPECT(!FlagGet(FLAG_TH_ROCKET_DUO));
    TH12_BeginRocketPair();
    EXPECT(!FlagGet(TRAINER_FLAGS_START + TRAINER_TH11_JESSIE));
    EXPECT(!FlagGet(TRAINER_FLAGS_START + TRAINER_TH11_JAMES));
    FlagSet(TRAINER_FLAGS_START + TRAINER_TH11_JESSIE);
    FlagSet(TRAINER_FLAGS_START + TRAINER_TH11_JAMES);
    TH12_CompleteRocketPair();
    EXPECT(FlagGet(FLAG_TH_ROCKET_DUO));
    TH12_BeginRocketPair();
    TH12_CompleteRocketPair();
    EXPECT(FlagGet(FLAG_TH_ROCKET_DUO));
    InitEventData();
}
#endif
