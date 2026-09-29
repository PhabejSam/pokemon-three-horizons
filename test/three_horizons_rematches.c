#include "global.h"
#include "test/test.h"
#include "data.h"
#include "pokemon.h"
#include "trainer_util.h"
#include "constants/opponents.h"

#if THREE_HORIZONS
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
                EXPECT_LE(actual, MAX(caps[badges], floor));
                EXPECT_LE(actual, MAX_LEVEL);
                previous = actual;
            }
        }
    }
}

TEST("Three Horizons Keigo progressed roster fits route")
{
    static const u16 species[] = {SPECIES_KAKUNA, SPECIES_BEEDRILL, SPECIES_BUTTERFREE};
    const struct Trainer *trainer = GetTrainerStructFromId(TRAINER_TH12_BUG_CATCHER_KEIGO);
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
    const struct TrainerMon *ricky = GetTrainerPartyFromId(TRAINER_TH12_CAMPER_RICKY);
    const struct TrainerMon *elijah = GetTrainerPartyFromId(TRAINER_TH12_BUG_CATCHER_ELIJAH);
    EXPECT_EQ(ricky[0].species, SPECIES_SQUIRTLE);
    EXPECT_EQ(ricky[0].lvl, 19);
    EXPECT_EQ(elijah[0].species, SPECIES_BUTTERFREE);
    EXPECT_EQ(elijah[0].lvl, 21);
}
#endif
