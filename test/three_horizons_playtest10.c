#include "global.h"
#include "test/test.h"
#include "three_horizons.h"
#include "pokemon.h"
#include "wild_encounter.h"
#include "event_data.h"
#include "battle_setup.h"
#include "constants/three_horizons.h"
#if THREE_HORIZONS
extern const u8 TH_Trainer9_TEAM_ROCKET_GRUNT_5[];
extern const u8 TH_RocketDigReward[];
TEST("Three Horizons Cerulean Rocket awards Dig immediately after victory")
{
    TrainerBattleParameter params;
    memcpy(&params, TH_Trainer9_TEAM_ROCKET_GRUNT_5 + TRAINERBATTLE_OPCODE_OFFSET, sizeof(params));
    EXPECT(params.params.continueScript);
    EXPECT_EQ(params.params.battleScriptRetAddrA, TH_RocketDigReward);
}

TEST("Three Horizons wild Hidden Ability occupies exactly ten percent of rolls")
{
    struct Pokemon mon;
    u32 hidden = 0;
    for (u32 roll = 0; roll < 100; roll++)
    {
        CreateRandomMon(&mon, SPECIES_RATTATA, 5);
        u8 normal = roll % 2;
        SetMonData(&mon, MON_DATA_ABILITY_NUM, &normal);
        TH_ApplyWildHiddenAbility(&mon, roll);
        u32 slot = GetMonData(&mon, MON_DATA_ABILITY_NUM);
        hidden += slot == 2;
        if (roll >= 10) EXPECT_EQ(slot, normal);
    }
    EXPECT_EQ(hidden, 10);
    CreateRandomMon(&mon, SPECIES_METAPOD, 7);
    TH_ApplyWildHiddenAbility(&mon, 0);
    EXPECT_EQ(GetMonAbility(&mon), ABILITY_SHED_SKIN);
}
TEST("Three Horizons wild encounter creation includes normal and Hidden Abilities")
{
    u32 slots[3] = {0};
    for (u32 i = 0; i < 500; i++)
    {
        CreateWildMon(SPECIES_RATTATA, 5);
        slots[GetMonData(&gEnemyParty[0], MON_DATA_ABILITY_NUM)]++;
    }
    EXPECT(slots[0] > 100);
    EXPECT(slots[1] > 100);
    EXPECT(slots[2] > 15);
    EXPECT(slots[2] < 100);
}
TEST("Three Horizons golden Magikarp retains Hidden Ability through evolution")
{
    struct Pokemon mon;
    TH_CreateGoldenMagikarp(&mon);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_LEVEL), 5);
    EXPECT_EQ(GetNature(&mon), NATURE_ADAMANT);
    EXPECT_EQ(GetMonAbility(&mon), ABILITY_RATTLED);
    EXPECT(GetMonData(&mon, MON_DATA_IS_SHINY));
    EXPECT_EQ(GetMonData(&mon, MON_DATA_ATK_EV), 252);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_SPEED_EV), 252);
    u16 species = SPECIES_GYARADOS;
    SetMonData(&mon, MON_DATA_SPECIES, &species);
    EXPECT_EQ(GetMonAbility(&mon), ABILITY_MOXIE);
    EXPECT(GetMonData(&mon, MON_DATA_IS_SHINY));
}
TEST("Three Horizons Playtest 9 upgrade preserves receipts and initializes Dig once")
{
    VarSet(VAR_TH_CLOCK_DISPLAY_HI, TH_STATE_VERSION_9 | 1);
    VarSet(VAR_TH_FIRST_PARTNER, SPECIES_TORCHIC);
    VarSet(VAR_TH_BROCK_GIFT, SPECIES_SQUIRTLE);
    FlagSet(FLAG_TH_MAGIKARP);
    FlagSet(FLAG_TH_PICKUP_1);
    FlagSet(FLAG_TH_DIG_TM);
    TH_MigrateSaveState();
    EXPECT_EQ(VarGet(VAR_TH_BROCK_GIFT), SPECIES_SQUIRTLE);
    EXPECT(FlagGet(FLAG_TH_MAGIKARP));
    EXPECT(FlagGet(FLAG_TH_PICKUP_1));
    EXPECT(!FlagGet(FLAG_TH_DIG_TM));
    EXPECT_EQ(VarGet(VAR_TH_CLOCK_DISPLAY_HI), TH_STATE_VERSION_10 | 1);
    FlagSet(FLAG_TH_DIG_TM);
    TH_ResetVisualClock();
    TH_MigrateSaveState();
    EXPECT(FlagGet(FLAG_TH_DIG_TM));
}
#endif
