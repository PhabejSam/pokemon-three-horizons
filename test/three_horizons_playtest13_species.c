#include "global.h"
#include "test/battle.h"
#include "pokemon.h"
#include "three_horizons.h"
#include "string_util.h"

#if THREE_HORIZONS
static bool32 LearnsAt(u16 species, u16 move, u32 level)
{
    const struct LevelUpMove *moves = gSpeciesInfo[species].levelUpLearnset;
    for (u32 i = 0; moves[i].move != LEVEL_UP_MOVE_END; i++)
        if (moves[i].move == move && moves[i].level == level)
            return TRUE;
    return FALSE;
}

TEST("Three Horizons playtest13 Gyarados Water Dragon applies to existing mons")
{
    struct Pokemon mon, before;
    CreateMonWithIVs(&mon, SPECIES_GYARADOS, 50, 123, OTID_STRUCT_PLAYER_ID, 23);
    before = mon;
    PokemonToBattleMon(&mon, &gBattleMons[0]);
    EXPECT_EQ(gBattleMons[0].types[0], TYPE_WATER);
    EXPECT_EQ(gBattleMons[0].types[1], TYPE_DRAGON);
    EXPECT_EQ(memcmp(&mon, &before, sizeof(mon)), 0);
    EXPECT(LearnsAt(SPECIES_GYARADOS, MOVE_DRAGON_TAIL, 26));
    EXPECT(LearnsAt(SPECIES_GYARADOS, MOVE_OUTRAGE, 48));
    EXPECT(!CanLearnTeachableMove(SPECIES_GYARADOS, MOVE_DRAGON_CLAW));
    EXPECT(CanLearnTeachableMove(SPECIES_GYARADOS, MOVE_OUTRAGE));
}

TEST("Three Horizons playtest13 Typhlosion learns Earth Power at forty")
{
    EXPECT(LearnsAt(SPECIES_TYPHLOSION, MOVE_EARTH_POWER, 40));
    EXPECT(!LearnsAt(SPECIES_TYPHLOSION, MOVE_EARTHQUAKE, 40));
    EXPECT(CanLearnTeachableMove(SPECIES_TYPHLOSION, MOVE_EARTHQUAKE));
    EXPECT_EQ(GetSpeciesType(SPECIES_TYPHLOSION, 1), TYPE_GROUND);
    EXPECT(LearnsAt(SPECIES_CHARIZARD, MOVE_AIR_SLASH, 36));
}

TEST("Three Horizons playtest13 pure trade families evolve at thirty six")
{
    const u16 pairs[][2] = {{SPECIES_KADABRA, SPECIES_ALAKAZAM},
        {SPECIES_MACHOKE, SPECIES_MACHAMP}, {SPECIES_GRAVELER, SPECIES_GOLEM},
        {SPECIES_HAUNTER, SPECIES_GENGAR}};
    struct Pokemon mon;
    bool32 canStop = TRUE;
    for (u32 i = 0; i < ARRAY_COUNT(pairs); i++)
    {
        CreateMonWithIVs(&mon, pairs[i][0], 35, 123, OTID_STRUCT_PLAYER_ID, 23);
        EXPECT_EQ(TH_GetBattleEvolution(&mon, &canStop), SPECIES_NONE);
        CreateMonWithIVs(&mon, pairs[i][0], 36, 123, OTID_STRUCT_PLAYER_ID, 23);
        EXPECT_EQ(TH_GetBattleEvolution(&mon, &canStop), pairs[i][1]);
        EXPECT(canStop);
    }
}

TEST("Three Horizons playtest13 thematic items support single player branches")
{
    const u16 pairs[][3] = {
        {SPECIES_SCYTHER, ITEM_METAL_COAT, SPECIES_SCIZOR},
        {SPECIES_ONIX, ITEM_METAL_COAT, SPECIES_STEELIX},
        {SPECIES_POLIWHIRL, ITEM_KINGS_ROCK, SPECIES_POLITOED},
        {SPECIES_POLIWHIRL, ITEM_WATER_STONE, SPECIES_POLIWRATH},
        {SPECIES_SLOWPOKE, ITEM_KINGS_ROCK, SPECIES_SLOWKING},
        {SPECIES_SEADRA, ITEM_DRAGON_SCALE, SPECIES_KINGDRA},
        {SPECIES_PORYGON, ITEM_UPGRADE, SPECIES_PORYGON2},
        {SPECIES_PORYGON2, ITEM_DUBIOUS_DISC, SPECIES_PORYGON_Z},
        {SPECIES_RHYDON, ITEM_PROTECTOR, SPECIES_RHYPERIOR},
        {SPECIES_ELECTABUZZ, ITEM_ELECTIRIZER, SPECIES_ELECTIVIRE},
        {SPECIES_MAGMAR, ITEM_MAGMARIZER, SPECIES_MAGMORTAR},
        {SPECIES_MAGNETON, ITEM_THUNDER_STONE, SPECIES_MAGNEZONE},
        {SPECIES_DUSCLOPS, ITEM_REAPER_CLOTH, SPECIES_DUSKNOIR},
        {SPECIES_CLAMPERL, ITEM_DEEP_SEA_TOOTH, SPECIES_HUNTAIL},
        {SPECIES_CLAMPERL, ITEM_DEEP_SEA_SCALE, SPECIES_GOREBYSS},
        {SPECIES_FEEBAS, ITEM_PRISM_SCALE, SPECIES_MILOTIC},
    };
    struct Pokemon mon, before;
    bool32 canStop = TRUE;
    for (u32 i = 0; i < ARRAY_COUNT(pairs); i++)
    {
        CreateMonWithIVs(&mon, pairs[i][0], 36, 123, OTID_STRUCT_PLAYER_ID, 23);
        before = mon;
        EXPECT_EQ(GetEvolutionTargetSpecies(&mon, EVO_MODE_ITEM_CHECK, pairs[i][1], NULL, &canStop, CHECK_EVO), pairs[i][2]);
        EXPECT_EQ(GetEvolutionTargetSpecies(&mon, EVO_MODE_ITEM_CHECK, ITEM_POTION, NULL, &canStop, CHECK_EVO), SPECIES_NONE);
        EXPECT_EQ(memcmp(&mon, &before, sizeof(mon)), 0);
    }
}

TEST("Three Horizons playtest13 Primeape Rage Fist threshold")
{
    struct Pokemon mon, restored;
    bool32 canStop = TRUE;
    u16 counter = 19;
    CreateMonWithIVs(&mon, SPECIES_PRIMEAPE, 36, 123, OTID_STRUCT_PLAYER_ID, 23);
    SetMonData(&mon, MON_DATA_EVOLUTION_TRACKER, &counter);
    EXPECT_EQ(TH_GetBattleEvolution(&mon, &canStop), SPECIES_NONE);
    counter = 20;
    SetMonData(&mon, MON_DATA_EVOLUTION_TRACKER, &counter);
    restored = mon; // Tracker is in the existing encrypted boxed data.
    EXPECT_EQ(GetMonData(&restored, MON_DATA_EVOLUTION_TRACKER), 20);
    EXPECT_EQ(TH_GetBattleEvolution(&restored, &canStop), SPECIES_ANNIHILAPE);
    EXPECT(canStop);
    EXPECT(LearnsAt(SPECIES_PRIMEAPE, MOVE_RAGE_FIST, 35));
}

SINGLE_BATTLE_TEST("Three Horizons playtest13 Rage Fist attempted uses count through miss and protect")
{
    u32 mode;
    PARAMETRIZE { mode = 0; }
    PARAMETRIZE { mode = 1; }
    PARAMETRIZE { mode = 2; }
    GIVEN {
        PLAYER(SPECIES_PRIMEAPE);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        if (mode == 1)
            TURN { MOVE(opponent, MOVE_PROTECT); MOVE(player, MOVE_RAGE_FIST); }
        else if (mode == 2)
            TURN { MOVE(player, MOVE_RAGE_FIST, hit: FALSE); }
        else
            TURN { MOVE(player, MOVE_RAGE_FIST); }
    } THEN {
        EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_EVOLUTION_TRACKER), 1);
        EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPECIES), SPECIES_PRIMEAPE);
    }
}

SINGLE_BATTLE_TEST("Three Horizons playtest13 Laser Focus covers every hit of only the next attack")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_LASER_FOCUS); }
        TURN { MOVE(player, MOVE_DOUBLE_KICK); }
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_LASER_FOCUS, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_DOUBLE_KICK, player);
        HP_BAR(opponent);
        MESSAGE("A critical hit!");
        HP_BAR(opponent);
        MESSAGE("A critical hit!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        HP_BAR(opponent);
        NOT MESSAGE("A critical hit!");
    }
}
#endif
