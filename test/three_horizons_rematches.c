#include "global.h"
#include "test/test.h"
#include "data.h"
#include "pokemon.h"
#include "trainer_util.h"
#include "constants/opponents.h"
#include "three_horizons_helpers.h"
#include "three_horizons_rematches.h"
#include "event_data.h"
#include "battle_setup.h"
#include "constants/maps.h"
#include "constants/three_horizons.h"

#if THREE_HORIZONS
#include "../src/data/three_horizons_rematches.h"

TEST("Three Horizons all registered rematch parties remain legal at chapter limits")
{
    struct Pokemon party[PARTY_SIZE];
    for (u32 i = 0; i < ARRAY_COUNT(sRematchEntries); i++)
    {
        const struct Trainer *trainer = TH_TestGetActualTrainer(sRematchEntries[i].trainerId);
        EXPECT_EQ(sizeof(sRematchEntries[i].trainerId), 2);
        for (u32 badges = 0; badges <= 8; badges += 4)
        {
            EXPECT(TH13_CreateRematchPartyFromTrainer(party, trainer, 100, badges));
            for (u32 member = 0; member < trainer->partySize; member++)
            {
                u32 species = GetMonData(&party[member], MON_DATA_SPECIES);
                u32 level = GetMonData(&party[member], MON_DATA_LEVEL);
                u32 ability = GetMonAbility(&party[member]);
                EXPECT_GE(level, trainer->party[member].lvl);
                EXPECT_LE(level, 100);
                EXPECT(ability == gSpeciesInfo[species].abilities[0] || ability == gSpeciesInfo[species].abilities[1]);
                EXPECT(GetMonData(&party[member], MON_DATA_MOVE1) != MOVE_NONE);
            }
        }
    }
}

TEST("Three Horizons rematch slots preserve full trainer IDs and reject collisions")
{
    const struct TH13RematchEntry valid[] = {{1, 12, 1}, {257, 12, 2}, {513, 13, 1}};
    const struct TH13RematchEntry collision[] = {{1, 12, 1}, {257, 12, 1}};
    const struct TH13RematchEntry duplicate[] = {{257, 12, 1}, {257, 12, 2}};
    const struct TH13RematchEntry bounds[] = {{1, 12, 0}, {257, 12, MAX_REMATCH_ENTRIES + 1}};
    EXPECT_EQ(TH13_ResolveRematchSlot(valid, 3, 12, 1), 0);
    EXPECT_EQ(TH13_ResolveRematchSlot(valid, 3, 12, 257), 1);
    EXPECT_EQ(TH13_ResolveRematchSlot(valid, 3, 13, 513), 0);
    EXPECT_EQ(TH13_ResolveRematchSlot(valid, 3, 13, 257), -1);
    EXPECT_EQ(TH13_ResolveRematchSlot(collision, 2, 12, 1), -1);
    EXPECT_EQ(TH13_ResolveRematchSlot(collision, 2, 12, 257), -1);
    EXPECT_EQ(TH13_ResolveRematchSlot(duplicate, 2, 12, 257), -1);
    EXPECT_EQ(TH13_ResolveRematchSlot(bounds, 2, 12, 1), -1);
    EXPECT_EQ(TH13_ResolveRematchSlot(bounds, 2, 12, 257), -1);
}

TEST("Three Horizons rematch readiness is temporary map local and preserves defeat history")
{
    InitEventData();
    gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(MAP_TH_VIRIDIAN_FOREST);
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(MAP_TH_VIRIDIAN_FOREST);
    TH13_ResetRematches();
    EXPECT(!TH13_SetRematchReady(TRAINER_TH_RICK));
    SetTrainerFlag(TRAINER_TH_RICK);
    SetTrainerFlag(TRAINER_TH_LIAM);
    u8 flags[sizeof(gSaveBlock1Ptr->flags)];
    memcpy(flags, gSaveBlock1Ptr->flags, sizeof(flags));
    EXPECT(TH13_SetRematchReady(TRAINER_TH_RICK));
    EXPECT(TH13_IsRematchReady(TRAINER_TH_RICK));
    EXPECT(!TH13_IsRematchReady(TRAINER_TH_LIAM));
    EXPECT(!TH13_SetRematchReady(TRAINER_TH_BROCK));
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(MAP_TH_PEWTER_GYM);
    EXPECT(!TH13_IsRematchReady(TRAINER_TH_LIAM));
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(MAP_TH_VIRIDIAN_FOREST);
    EXPECT(!TH13_IsRematchReady(TRAINER_TH_RICK));
    // Immediate repeated use has no charge or badge dependency.
    for (u32 i = 0; i < 3; i++)
    {
        EXPECT(TH13_SetRematchReady(TRAINER_TH_RICK));
        EXPECT(TH13_BeginRematch(TRAINER_TH_RICK));
        TH13_ResetRematches();
        EXPECT(!TH13_IsRematchReady(TRAINER_TH_RICK));
        EXPECT_EQ(memcmp(flags, gSaveBlock1Ptr->flags, sizeof(flags)), 0);
    }
    EXPECT_EQ(sizeof(gSaveBlock1Ptr->trainerRematches), 100);
    EXPECT_EQ(sizeof(struct SaveBlock1), 15568);
    EXPECT_EQ(sizeof(struct SaveBlock2), 3884);
}

TEST("Three Horizons rematch level clamps safely")
{
    static const struct { u8 highest, original, badges, expected; } cases[] = {
        {0, 5, 0, 5}, {1, 5, 0, 5}, {9, 5, 0, 5},
        {10, 5, 0, 5}, {15, 5, 0, 5}, {16, 5, 0, 6},
        {34, 5, 0, 24}, {100, 5, 1, 24}, {100, 5, 2, 24},
        {100, 5, 3, 35}, {100, 5, 4, 45}, {100, 5, 5, 55},
        {100, 5, 6, 65}, {100, 5, 7, 75}, {100, 5, 8, 90},
        {1, 40, 0, 40}, {100, 100, 8, 100}, {35, 18, 3, 25},
    };
    for (u32 i = 0; i < ARRAY_COUNT(cases); i++)
        EXPECT_EQ(TH13_GetRematchLevel(cases[i].highest, cases[i].original, cases[i].badges), cases[i].expected);
}

TEST("Three Horizons rematch party excludes Eggs and leaves first battles untouched")
{
    struct Pokemon saved[PARTY_SIZE], output[PARTY_SIZE], untouched[PARTY_SIZE];
    memcpy(saved, gPlayerParty, sizeof(saved));
    memset(gPlayerParty, 0, sizeof(saved));
    CreateMonWithIVs(&gPlayerParty[0], SPECIES_PIKACHU, 17, 0, OTID_STRUCT_PLAYER_ID, 31);
    CreateMonWithIVs(&gPlayerParty[1], SPECIES_PIKACHU, 100, 0, OTID_STRUCT_PLAYER_ID, 31);
    u32 egg = TRUE;
    SetMonData(&gPlayerParty[1], MON_DATA_IS_EGG, &egg);
    EXPECT_EQ(TH13_HighestNonEggPartyLevel(), 17);
    memset(output, 0x5a, sizeof(output));
    memcpy(untouched, output, sizeof(output));
    TH13_ResetRematches();
    EXPECT(!TH13_TryCreateRematchParty(output, TRAINER_TH_RICK));
    EXPECT_EQ(memcmp(output, untouched, sizeof(output)), 0);
    EXPECT(!TH13_TryCreateRematchParty(output, TRAINER_TH_BROCK));
    EXPECT_EQ(memcmp(output, untouched, sizeof(output)), 0);
    memcpy(gPlayerParty, saved, sizeof(saved));
    CalculatePlayerPartyCount();
}

TEST("Three Horizons authored rematch tiers retain level offsets and legal abilities")
{
    static const struct TrainerMon baseline[] = {
        {.species = SPECIES_CATERPIE, .lvl = 5, .ability = ABILITY_SHIELD_DUST},
        {.species = SPECIES_RATTATA, .lvl = 7, .ability = ABILITY_RUN_AWAY},
        {.species = SPECIES_EEVEE, .lvl = 3, .ability = ABILITY_RUN_AWAY},
    };
    struct Trainer trainer = *TH_TestGetActualTrainer(TRAINER_TH_RICK);
    trainer.party = baseline;
    trainer.partySize = ARRAY_COUNT(baseline);
    struct Pokemon party[PARTY_SIZE];
    EXPECT(TH13_CreateRematchPartyFromTrainer(party, &trainer, 100, 0));
    EXPECT_EQ(GetMonData(&party[0], MON_DATA_LEVEL), 22);
    EXPECT_EQ(GetMonData(&party[1], MON_DATA_LEVEL), 24);
    EXPECT_EQ(GetMonData(&party[2], MON_DATA_LEVEL), 20);
    EXPECT_EQ(GetMonData(&party[0], MON_DATA_SPECIES), SPECIES_BUTTERFREE);
    EXPECT_EQ(GetMonData(&party[1], MON_DATA_SPECIES), SPECIES_RATICATE);
    EXPECT_EQ(GetMonData(&party[2], MON_DATA_SPECIES), SPECIES_EEVEE);
    for (u32 i = 0; i < ARRAY_COUNT(baseline); i++)
    {
        u32 species = GetMonData(&party[i], MON_DATA_SPECIES);
        u32 ability = GetMonAbility(&party[i]);
        EXPECT(ability == gSpeciesInfo[species].abilities[0] || ability == gSpeciesInfo[species].abilities[1]);
        EXPECT(GetMonData(&party[i], MON_DATA_MOVE1) != MOVE_NONE);
    }
    EXPECT_EQ(baseline[0].species, SPECIES_CATERPIE);
    EXPECT_EQ(baseline[0].lvl, 5);
}

TEST("Three Horizons rematch level is monotonic and preserves original floor")
{
    static const u8 caps[] = {24, 24, 24, 35, 45, 55, 65, 75, 100};
    for (u32 badges = 0; badges < ARRAY_COUNT(caps); badges++)
    {
        for (u32 floor = 1; floor <= MAX_LEVEL; floor++)
        {
            u32 previous = floor;
            for (u32 highest = 0; highest <= MAX_LEVEL; highest++)
            {
                u32 actual = TH13_GetRematchLevel(highest, floor, badges);
                EXPECT_GE(actual, previous);
                EXPECT_GE(actual, floor);
                EXPECT_LE(actual, max(caps[badges], floor));
                EXPECT_LE(actual, MAX_LEVEL);
                previous = actual;
            }
        }
    }
}

TEST("Three Horizons Keigo progressed roster fits route")
{
    static const u16 species[] = {SPECIES_KAKUNA, SPECIES_BEEDRILL, SPECIES_BUTTERFREE};
    const struct Trainer *trainer = TH_TestGetActualTrainer(TRAINER_TH12_BUG_CATCHER_KEIGO);
    struct TrainerGenerator generator = {0};
    struct Pokemon mon;
    MakeTrainerGenerator(&generator, trainer);
    EXPECT_EQ((u32)trainer->partySize, ARRAY_COUNT(species));
    for (u32 i = 0; i < ARRAY_COUNT(species); i++)
    {
        EXPECT_EQ(trainer->party[i].species, species[i]);
        EXPECT_EQ(trainer->party[i].lvl, 18);
        GenerateMonFromTrainerMon(&mon, &trainer->party[i], &generator);
        EXPECT_EQ(GetMonData(&mon, MON_DATA_SPECIES), species[i]);
        EXPECT_EQ(GetMonData(&mon, MON_DATA_LEVEL), 18);
        EXPECT_EQ(GetMonData(&mon, MON_DATA_EXP), gExperienceTables[gSpeciesInfo[species[i]].growthRate][18]);
        EXPECT(GetMonData(&mon, MON_DATA_MOVE1) != MOVE_NONE);
        u32 ability = GetMonAbility(&mon);
        EXPECT(ability == gSpeciesInfo[species[i]].abilities[0]
            || ability == gSpeciesInfo[species[i]].abilities[1]);
    }
    // Adjacent route trainers keep their shipped first-fight levels/species.
    const struct TrainerMon *ricky = TH_TestGetActualTrainer(TRAINER_TH12_CAMPER_RICKY)->party;
    const struct TrainerMon *elijah = TH_TestGetActualTrainer(TRAINER_TH12_BUG_CATCHER_ELIJAH)->party;
    EXPECT_EQ(ricky[0].species, SPECIES_SQUIRTLE);
    EXPECT_EQ(ricky[0].lvl, 19);
    EXPECT_EQ(elijah[0].species, SPECIES_BUTTERFREE);
    EXPECT_EQ(elijah[0].lvl, 21);
}
#endif
