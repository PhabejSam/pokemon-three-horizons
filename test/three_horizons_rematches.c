#include "global.h"
#include "test/test.h"
#include "data.h"
#include "pokemon.h"
#include "trainer_util.h"
#include "constants/opponents.h"

#if THREE_HORIZONS
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
