#include "global.h"
#include "test/test.h"
#include "data.h"
#include "pokemon.h"
#include "trainer_util.h"
#include "three_horizons_helpers.h"
#include "three_horizons.h"
#include "three_horizons_rematches.h"
#include "constants/opponents.h"
#include "constants/maps.h"
#include "constants/trainers.h"

#if THREE_HORIZONS
extern bool32 Test_TH14_CreateRematchParty(struct Pokemon *, const struct Trainer *, u16, u8, u8);
static const struct {
    u16 trainerId; u8 slot; u16 base, evolved; u8 level, badges;
} sExpected[] = {
    {TRAINER_TH9_LASS_ROBIN, 0, SPECIES_JIGGLYPUFF, SPECIES_WIGGLYTUFF, 30, 3},
    {TRAINER_TH9_LASS_IRIS, 0, SPECIES_CLEFAIRY, SPECIES_CLEFABLE, 30, 3},
    {TRAINER_TH12_PICNICKER_NANCY, 1, SPECIES_PIKACHU, SPECIES_RAICHU, 30, 3},
    {TRAINER_TH12_GENTLEMAN_THOMAS, 0, SPECIES_GROWLITHE, SPECIES_ARCANINE, 32, 4},
    {TRAINER_TH12_GENTLEMAN_THOMAS, 1, SPECIES_GROWLITHE, SPECIES_ARCANINE, 32, 4},
    {TRAINER_TH12_GENTLEMAN_BROOKS, 0, SPECIES_PIKACHU, SPECIES_RAICHU, 30, 3},
    {TRAINER_TH12_GENTLEMAN_LAMAR, 0, SPECIES_GROWLITHE, SPECIES_ARCANINE, 32, 4},
    {TRAINER_TH12_LASS_DAWN, 1, SPECIES_PIKACHU, SPECIES_RAICHU, 30, 3},
    {TRAINER_TH12_SAILOR_DWAYNE, 0, SPECIES_PIKACHU, SPECIES_RAICHU, 30, 3},
    {TRAINER_TH12_SAILOR_DWAYNE, 1, SPECIES_PIKACHU, SPECIES_RAICHU, 30, 3},
    {TRAINER_TH12_GENTLEMAN_TUCKER, 0, SPECIES_PIKACHU, SPECIES_RAICHU, 30, 3},
    {TRAINER_TH13_ROUTE11_DARIAN, 0, SPECIES_GROWLITHE, SPECIES_ARCANINE, 32, 4},
    {TRAINER_TH13_ROUTE11_DARIAN, 1, SPECIES_VULPIX, SPECIES_NINETALES, 32, 4},
    {TRAINER_TH13_ROUTE9_CHRIS, 0, SPECIES_GROWLITHE, SPECIES_ARCANINE, 32, 4},
    {TRAINER_TH13_ROUTE10_HEIDI, 0, SPECIES_PIKACHU, SPECIES_RAICHU, 30, 3},
    {TRAINER_TH13_ROUTE10_HEIDI, 1, SPECIES_CLEFAIRY, SPECIES_CLEFABLE, 30, 3},
    {TRAINER_TH13_ROCKTUNNEL_1F_LEAH, 1, SPECIES_CLEFAIRY, SPECIES_CLEFABLE, 30, 3},
    {TRAINER_TH13_ROCKTUNNEL_B1F_SOFIA, 0, SPECIES_JIGGLYPUFF, SPECIES_WIGGLYTUFF, 30, 3},
    {TRAINER_TH14_ROUTE8_JULIA, 0, SPECIES_CLEFAIRY, SPECIES_CLEFABLE, 30, 3},
    {TRAINER_TH14_ROUTE8_JULIA, 1, SPECIES_CLEFAIRY, SPECIES_CLEFABLE, 30, 3},
    {TRAINER_TH14_ROUTE8_RICH, 0, SPECIES_GROWLITHE, SPECIES_ARCANINE, 32, 4},
    {TRAINER_TH14_ROUTE8_RICH, 1, SPECIES_VULPIX, SPECIES_NINETALES, 32, 4},
    {TRAINER_TH14_ROUTE8_MEGAN, 4, SPECIES_PIKACHU, SPECIES_RAICHU, 30, 3},
    {TRAINER_TH14_ROUTE8_ELI_ANNE, 0, SPECIES_CLEFAIRY, SPECIES_CLEFABLE, 30, 3},
    {TRAINER_TH14_ROUTE8_ELI_ANNE, 1, SPECIES_JIGGLYPUFF, SPECIES_WIGGLYTUFF, 30, 3},
};

TEST("Three Horizons PT14 rematches: all 25 exact keys obey both gates and never truncate identities")
{
    for (u32 i = 0; i < ARRAY_COUNT(sExpected); i++)
    {
        for (u32 level = sExpected[i].level - 1; level <= sExpected[i].level + 1; level++)
            for (u32 badges = sExpected[i].badges - 1; badges <= sExpected[i].badges; badges++)
                EXPECT_EQ(TH14_GetAuthoredRematchEvolution(sExpected[i].trainerId, sExpected[i].slot,
                    sExpected[i].base, level, badges),
                    level >= sExpected[i].level && badges >= sExpected[i].badges ? sExpected[i].evolved : sExpected[i].base);
        EXPECT_EQ(TH14_GetAuthoredRematchEvolution(sExpected[i].trainerId + 256, sExpected[i].slot, sExpected[i].base, 100, 8), sExpected[i].base);
        EXPECT_EQ(TH14_GetAuthoredRematchEvolution(TRAINER_NONE, sExpected[i].slot, sExpected[i].base, 100, 8), sExpected[i].base);
        EXPECT_EQ(TH14_GetAuthoredRematchEvolution(TRAINER_TH_BROCK, sExpected[i].slot, sExpected[i].base, 100, 8), sExpected[i].base);
        EXPECT_EQ(TH14_GetAuthoredRematchEvolution(sExpected[i].trainerId, PARTY_SIZE, sExpected[i].base, 100, 8), sExpected[i].base);
        EXPECT_EQ(TH14_GetAuthoredRematchEvolution(sExpected[i].trainerId, sExpected[i].slot, SPECIES_EEVEE, 100, 8), SPECIES_EEVEE);
        EXPECT_EQ(TH14_GetAuthoredRematchEvolution(sExpected[i].trainerId, sExpected[i].slot, sExpected[i].base, 0, 8), sExpected[i].base);
    }
}

static const struct {
    u16 species, ability, moves[4];
} sGenerated[] = {
    {SPECIES_ARCANINE, ABILITY_INTIMIDATE, {MOVE_LEER, MOVE_FLAME_WHEEL, MOVE_TAKE_DOWN, MOVE_FLAMETHROWER}},
    {SPECIES_NINETALES, ABILITY_FLASH_FIRE, {MOVE_INFERNO, MOVE_QUICK_ATTACK, MOVE_FLAMETHROWER, MOVE_TAIL_WHIP}},
    {SPECIES_RAICHU, ABILITY_STATIC, {MOVE_TAIL_WHIP, MOVE_DOUBLE_TEAM, MOVE_LIGHT_SCREEN, MOVE_THUNDERBOLT}},
    {SPECIES_CLEFABLE, ABILITY_CUTE_CHARM, {MOVE_METRONOME, MOVE_METEOR_MASH, MOVE_MOONBLAST, MOVE_LIFE_DEW}},
    {SPECIES_WIGGLYTUFF, ABILITY_CUTE_CHARM, {MOVE_DOUBLE_EDGE, MOVE_BODY_SLAM, MOVE_CHARM, MOVE_PLAY_ROUGH}},
};

TEST("Three Horizons PT14 rematches: exact keyed generation uses evolved moves abilities and retained IVs items")
{
    struct Trainer trainer = *TH_TestGetActualTrainer(TRAINER_TH_RICK);
    struct TrainerMon baseline[PARTY_SIZE], untouched[PARTY_SIZE];
    struct Pokemon party[PARTY_SIZE];
    for (u32 row = 0; row < ARRAY_COUNT(sExpected); row++)
    {
        memset(baseline, 0, sizeof(baseline));
        for (u32 slot = 0; slot < PARTY_SIZE; slot++)
        {
            baseline[slot].species = slot == sExpected[row].slot ? sExpected[row].base : SPECIES_EEVEE;
            baseline[slot].lvl = 5;
            baseline[slot].gender = TRAINER_MON_RANDOM_GENDER;
            baseline[slot].iv = 0x0BADBEEF;
            baseline[slot].heldItem = ITEM_ORAN_BERRY;
            baseline[slot].ability = ABILITY_SHIELD_DUST; // invalid on all five results: must choose legal normal slot.
            baseline[slot].moves[0] = MOVE_TACKLE;
        }
        memcpy(untouched, baseline, sizeof(baseline));
        trainer.party = baseline; trainer.partySize = sExpected[row].slot + 1;
        for (u32 repeat = 0; repeat < 2; repeat++)
        {
            EXPECT(Test_TH14_CreateRematchParty(party, &trainer, sExpected[row].trainerId, sExpected[row].level + 10, sExpected[row].badges));
            struct Pokemon *mon = &party[sExpected[row].slot];
            EXPECT_EQ(GetMonData(mon, MON_DATA_SPECIES), sExpected[row].evolved);
            EXPECT_EQ(GetMonData(mon, MON_DATA_LEVEL), sExpected[row].level);
            EXPECT_EQ(GetMonData(mon, MON_DATA_IVS), 0x0BADBEEF);
            EXPECT_EQ(GetMonData(mon, MON_DATA_HELD_ITEM), ITEM_ORAN_BERRY);
            EXPECT_EQ(GetMonData(mon, MON_DATA_ABILITY_NUM), 0);
            EXPECT_GT(GetMonData(mon, MON_DATA_MAX_HP), 0);
            for (u32 result = 0; result < ARRAY_COUNT(sGenerated); result++)
                if (sGenerated[result].species == sExpected[row].evolved)
                {
                    EXPECT_EQ(GetMonAbility(mon), sGenerated[result].ability);
                    for (u32 move = 0; move < 4; move++)
                        EXPECT_EQ(GetMonData(mon, MON_DATA_MOVE1 + move), sGenerated[result].moves[move]);
                }
            for (u32 slot = trainer.partySize; slot < PARTY_SIZE; slot++)
                EXPECT_EQ(GetMonData(&party[slot], MON_DATA_SPECIES), SPECIES_NONE);
            EXPECT_EQ(memcmp(baseline, untouched, sizeof(baseline)), 0);
        }
        // Unknown identity wrapper never receives a trainer-specific stone rule.
        EXPECT(TH13_CreateRematchPartyFromTrainer(party, &trainer, 100, 8));
        EXPECT_EQ(GetMonData(&party[sExpected[row].slot], MON_DATA_SPECIES), sExpected[row].base);
    }
}

TEST("Three Horizons PT14 rematches: shipped first rosters offsets and unchanged data survive keyed scaling")
{
    struct Pokemon party[PARTY_SIZE];
    struct TrainerMon original[PARTY_SIZE];
    for (u32 row = 0; row < ARRAY_COUNT(sExpected); row++)
    {
        const struct Trainer *trainer = TH_TestGetActualTrainer(sExpected[row].trainerId);
        memcpy(original, trainer->party, trainer->partySize * sizeof(*original));
        EXPECT_EQ(original[sExpected[row].slot].species, sExpected[row].base);
        u8 highest = 1;
        for (u32 slot = 0; slot < trainer->partySize; slot++) highest = max(highest, original[slot].lvl);
        for (u32 badges = 0; badges <= 8; badges++)
        {
            EXPECT(Test_TH14_CreateRematchParty(party, trainer, sExpected[row].trainerId, 255, badges));
            for (u32 slot = 0; slot < trainer->partySize; slot++)
            {
                u8 scaled = max(1, TH13_GetRematchLevel(255, highest, badges) - (highest - original[slot].lvl));
                EXPECT_EQ(GetMonData(&party[slot], MON_DATA_LEVEL), scaled);
                EXPECT_LE(scaled, MAX_LEVEL);
                EXPECT_EQ(GetMonData(&party[slot], MON_DATA_IVS), original[slot].iv);
                EXPECT_EQ(GetMonData(&party[slot], MON_DATA_HELD_ITEM), original[slot].heldItem);
            }
            u8 level = GetMonData(&party[sExpected[row].slot], MON_DATA_LEVEL);
            EXPECT_EQ(GetMonData(&party[sExpected[row].slot], MON_DATA_SPECIES),
                TH14_GetAuthoredRematchEvolution(sExpected[row].trainerId, sExpected[row].slot, sExpected[row].base, level, badges));
            EXPECT_EQ(memcmp(original, trainer->party, trainer->partySize * sizeof(*original)), 0);
        }
    }
}

TEST("Three Horizons PT14 rematches: one explicit twins alias cannot collide escape its map or truncate IDs")
{
    const u16 map = (76 << 8);
    const struct TH13RematchEntry entries[] = {{166, map, 12}, {422, map, 14}, {166, map + 1, 4}};
    struct TH14RematchAlias alias[] = {{166, map, 13, 12}, {166, map, 13, 12}};
    EXPECT_EQ(TH14_ResolveMapTrainer(entries, 3, alias, 1, map, 12), 166);
    EXPECT_EQ(TH14_ResolveMapTrainer(entries, 3, alias, 1, map, 13), 166);
    EXPECT_EQ(TH14_ResolveMapTrainer(entries, 3, alias, 1, map, 14), 422);
    EXPECT_EQ(TH13_ResolveRematchSlot(entries, 3, map, 166), 11);
    EXPECT_EQ(TH13_ResolveRematchSlot(entries, 3, map, 422), 13);
    EXPECT_EQ(TH14_ResolveMapTrainer(entries, 3, alias, 1, map + 1, 13), TRAINER_NONE);
    EXPECT_EQ(TH14_ResolveMapTrainer(entries, 3, alias, 1, map + 1, 4), 166);
    EXPECT_EQ(TH14_ResolveMapTrainer(entries, 3, alias, 2, map, 13), TRAINER_NONE);
    for (u32 local = 0; local <= 255; local++)
        if (local != 12 && local != 13 && local != 14)
            EXPECT_EQ(TH14_ResolveMapTrainer(entries, 3, alias, 1, map, local), TRAINER_NONE);
    alias[0].canonicalLocalId = 14; // points at a different trainer
    EXPECT_EQ(TH14_ResolveMapTrainer(entries, 3, alias, 1, map, 13), TRAINER_NONE);
    alias[0].canonicalLocalId = 0;
    EXPECT_EQ(TH14_ResolveMapTrainer(entries, 3, alias, 1, map, 13), TRAINER_NONE);
    alias[0].canonicalLocalId = 12; alias[0].localId = 14; // collides with full-width422
    EXPECT_EQ(TH14_ResolveMapTrainer(entries, 3, alias, 1, map, 14), TRAINER_NONE);
    alias[0].localId = 13; alias[0].trainerId = 422; // same low byte is not identity
    EXPECT_EQ(TH14_ResolveMapTrainer(entries, 3, alias, 1, map, 13), TRAINER_NONE);
    const struct TH13RematchEntry collision[] = {{166, map, 12}, {422, map, 12}};
    alias[0].trainerId = 166;
    EXPECT_EQ(TH14_ResolveMapTrainer(collision, 2, alias, 1, map, 13), TRAINER_NONE);
    EXPECT_EQ(TH14_ResolveMapTrainer(entries, 0, alias, 1, map, 13), TRAINER_NONE);
}

#include "test/battle.h"
#include "pokedex.h"
#include "constants/three_horizons.h"

AI_SINGLE_BATTLE_TEST("Three Horizons PT14 rematches: evolved trainer KOs award actual XP EV and Seen with EXP Share retained")
{
    u32 row = 0, share = 0;
    PARAMETRIZE { row = 3; share = 0; }
    PARAMETRIZE { row = 3; share = 1; }
    PARAMETRIZE { row = 12; share = 0; }
    PARAMETRIZE { row = 12; share = 1; }
    PARAMETRIZE { row = 2; share = 0; }
    PARAMETRIZE { row = 2; share = 1; }
    PARAMETRIZE { row = 1; share = 0; }
    PARAMETRIZE { row = 1; share = 1; }
    PARAMETRIZE { row = 0; share = 0; }
    PARAMETRIZE { row = 0; share = 1; }
    u16 species = sExpected[row].evolved;
    u8 level = sExpected[row].level;
    GIVEN {
        ResetPokedex();
        if (share) GetSetPokedexFlag(SpeciesToNationalPokedexNum(species), FLAG_SET_CAUGHT);
        if (share) FLAG_SET(I_EXP_SHARE_FLAG);
        VAR_SET(VAR_TH_EXP_RATE, 0);
        AI_FLAGS(0);
        PLAYER(SPECIES_WOBBUFFET) { Level(level); Moves(MOVE_AERIAL_ACE); }
        PLAYER(SPECIES_WOBBUFFET) { Level(level); }
        OPPONENT(species) { Level(level); HP(1); Moves(MOVE_CELEBRATE); }
        struct Trainer trainer = *TH_TestGetActualTrainer(TRAINER_TH_RICK);
        struct TrainerMon members[PARTY_SIZE] = {0};
        struct Pokemon generated[PARTY_SIZE];
        for (u32 slot = 0; slot <= sExpected[row].slot; slot++)
        {
            members[slot].species = slot == sExpected[row].slot ? sExpected[row].base : SPECIES_EEVEE;
            members[slot].lvl = 5;
            members[slot].gender = TRAINER_MON_RANDOM_GENDER;
        }
        trainer.party = members; trainer.partySize = sExpected[row].slot + 1;
        EXPECT(Test_TH14_CreateRematchParty(generated, &trainer, sExpected[row].trainerId, level + 10, sExpected[row].badges));
        OPPONENT_PARTY[0] = generated[sExpected[row].slot];
        u16 hp = 1, move = MOVE_CELEBRATE; u8 pp = 40;
        SetMonData(&OPPONENT_PARTY[0], MON_DATA_HP, &hp);
        for (u32 slot = 0; slot < 4; slot++)
        {
            SetMonData(&OPPONENT_PARTY[0], MON_DATA_MOVE1 + slot, &move);
            SetMonData(&OPPONENT_PARTY[0], MON_DATA_PP1 + slot, &pp);
        }
    } WHEN {
        TURN { MOVE(player, MOVE_AERIAL_ACE); }
    } THEN {
        EXPECT_EQ(gBattleOutcome, B_OUTCOME_WON);
        EXPECT_EQ(GetMonData(&gParties[B_TRAINER_OPPONENT_A][0], MON_DATA_SPECIES), species);
        EXPECT(GetSetPokedexFlag(SpeciesToNationalPokedexNum(species), FLAG_GET_SEEN));
        EXPECT_EQ(GetSetPokedexFlag(SpeciesToNationalPokedexNum(species), FLAG_GET_CAUGHT), share);
        u32 initial = gExperienceTables[gSpeciesInfo[SPECIES_WOBBUFFET].growthRate][level];
        u32 base = gSpeciesInfo[species].expYield * level / 5;
        EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_EXP), initial + base + 1);
        EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][1], MON_DATA_EXP), initial + (share ? base / 2 + 1 : 0));
        const u8 evs[] = {gSpeciesInfo[species].evYield_HP, gSpeciesInfo[species].evYield_Attack,
            gSpeciesInfo[species].evYield_Defense, gSpeciesInfo[species].evYield_Speed,
            gSpeciesInfo[species].evYield_SpAttack, gSpeciesInfo[species].evYield_SpDefense};
        for (u32 stat = 0; stat < ARRAY_COUNT(evs); stat++)
        {
            EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_HP_EV + stat), evs[stat]);
            EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][1], MON_DATA_HP_EV + stat), share ? evs[stat] : 0);
        }
    }
}
#endif
