#include "global.h"
#include "test/test.h"
#include "pokemon.h"
#include "battle.h"
#if THREE_HORIZONS
TEST("Three Horizons playtest12 Grovyle approved moves remain learnable")
{
    const struct LevelUpMove *learnset = gSpeciesInfo[SPECIES_GROVYLE].levelUpLearnset;
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 16 && learnset[i].move == MOVE_TWISTER) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 19 && learnset[i].move == MOVE_RAZOR_LEAF) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 34 && learnset[i].move == MOVE_DRAGON_BREATH) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 37 && learnset[i].move == MOVE_LEAF_BLADE) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 45 && learnset[i].move == MOVE_DRAGON_CLAW) found = TRUE;
        EXPECT(found);
    }
}

TEST("Three Horizons playtest12 Sceptile approved moves remain learnable")
{
    const struct LevelUpMove *learnset = gSpeciesInfo[SPECIES_SCEPTILE].levelUpLearnset;
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 1 && learnset[i].move == MOVE_CRUNCH) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 16 && learnset[i].move == MOVE_TWISTER) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 19 && learnset[i].move == MOVE_RAZOR_LEAF) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 34 && learnset[i].move == MOVE_DRAGON_BREATH) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 65 && learnset[i].move == MOVE_FRENZY_PLANT) found = TRUE;
        EXPECT(found);
    }
}

TEST("Three Horizons playtest12 Combusken approved moves remain learnable")
{
    const struct LevelUpMove *learnset = gSpeciesInfo[SPECIES_COMBUSKEN].levelUpLearnset;
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 37 && learnset[i].move == MOVE_BLAZE_KICK) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 41 && learnset[i].move == MOVE_SKY_UPPERCUT) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 55 && learnset[i].move == MOVE_HIGH_JUMP_KICK) found = TRUE;
        EXPECT(found);
    }
}

TEST("Three Horizons playtest12 Blaziken approved moves remain learnable")
{
    const struct LevelUpMove *learnset = gSpeciesInfo[SPECIES_BLAZIKEN].levelUpLearnset;
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 1 && learnset[i].move == MOVE_ROCK_SLIDE) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 65 && learnset[i].move == MOVE_BLAST_BURN) found = TRUE;
        EXPECT(found);
    }
}

TEST("Three Horizons playtest12 Marshtomp approved moves remain learnable")
{
    const struct LevelUpMove *learnset = gSpeciesInfo[SPECIES_MARSHTOMP].levelUpLearnset;
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 37 && learnset[i].move == MOVE_MUDDY_WATER) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 40 && learnset[i].move == MOVE_PROTECT) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 43 && learnset[i].move == MOVE_EARTHQUAKE) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 45 && learnset[i].move == MOVE_HYDRO_PUMP) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 50 && learnset[i].move == MOVE_ENDEAVOR) found = TRUE;
        EXPECT(found);
    }
}

TEST("Three Horizons playtest12 Swampert approved moves remain learnable")
{
    const struct LevelUpMove *learnset = gSpeciesInfo[SPECIES_SWAMPERT].levelUpLearnset;
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 1 && learnset[i].move == MOVE_ICE_BALL) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 28 && learnset[i].move == MOVE_DIG) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 65 && learnset[i].move == MOVE_HYDRO_CANNON) found = TRUE;
        EXPECT(found);
    }
}

TEST("Three Horizons playtest12 Chikorita approved moves remain learnable")
{
    const struct LevelUpMove *learnset = gSpeciesInfo[SPECIES_CHIKORITA].levelUpLearnset;
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 19 && learnset[i].move == MOVE_DRAGON_BREATH) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 21 && learnset[i].move == MOVE_MEGA_DRAIN) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 39 && learnset[i].move == MOVE_OUTRAGE) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 55 && learnset[i].move == MOVE_DRAGON_DANCE) found = TRUE;
        EXPECT(found);
    }
}

TEST("Three Horizons playtest12 Bayleef approved moves remain learnable")
{
    const struct LevelUpMove *learnset = gSpeciesInfo[SPECIES_BAYLEEF].levelUpLearnset;
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 19 && learnset[i].move == MOVE_DRAGON_BREATH) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 21 && learnset[i].move == MOVE_MEGA_DRAIN) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 39 && learnset[i].move == MOVE_OUTRAGE) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 55 && learnset[i].move == MOVE_DRAGON_DANCE) found = TRUE;
        EXPECT(found);
    }
}

TEST("Three Horizons playtest12 Meganium approved moves remain learnable")
{
    const struct LevelUpMove *learnset = gSpeciesInfo[SPECIES_MEGANIUM].levelUpLearnset;
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 1 && learnset[i].move == MOVE_ANCIENT_POWER) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 1 && learnset[i].move == MOVE_GIGA_DRAIN) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 19 && learnset[i].move == MOVE_DRAGON_BREATH) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 21 && learnset[i].move == MOVE_MEGA_DRAIN) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 36 && learnset[i].move == MOVE_PETAL_DANCE) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 39 && learnset[i].move == MOVE_OUTRAGE) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 55 && learnset[i].move == MOVE_DRAGON_DANCE) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 65 && learnset[i].move == MOVE_FRENZY_PLANT) found = TRUE;
        EXPECT(found);
    }
}

TEST("Three Horizons playtest12 Cyndaquil approved moves remain learnable")
{
    const struct LevelUpMove *learnset = gSpeciesInfo[SPECIES_CYNDAQUIL].levelUpLearnset;
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 7 && learnset[i].move == MOVE_EMBER) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 9 && learnset[i].move == MOVE_MUD_SLAP) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 14 && learnset[i].move == MOVE_QUICK_ATTACK) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 16 && learnset[i].move == MOVE_DEFENSE_CURL) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 18 && learnset[i].move == MOVE_DIG) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 28 && learnset[i].move == MOVE_SWIFT) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 32 && learnset[i].move == MOVE_FLAMETHROWER) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 40 && learnset[i].move == MOVE_EARTHQUAKE) found = TRUE;
        EXPECT(found);
    }
}

TEST("Three Horizons playtest12 Quilava approved moves remain learnable")
{
    const struct LevelUpMove *learnset = gSpeciesInfo[SPECIES_QUILAVA].levelUpLearnset;
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 7 && learnset[i].move == MOVE_EMBER) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 9 && learnset[i].move == MOVE_MUD_SLAP) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 14 && learnset[i].move == MOVE_QUICK_ATTACK) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 16 && learnset[i].move == MOVE_DEFENSE_CURL) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 18 && learnset[i].move == MOVE_DIG) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 30 && learnset[i].move == MOVE_SWIFT) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 34 && learnset[i].move == MOVE_FLAMETHROWER) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 40 && learnset[i].move == MOVE_EARTHQUAKE) found = TRUE;
        EXPECT(found);
    }
}

TEST("Three Horizons playtest12 Typhlosion approved moves remain learnable")
{
    const struct LevelUpMove *learnset = gSpeciesInfo[SPECIES_TYPHLOSION].levelUpLearnset;
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 1 && learnset[i].move == MOVE_EXTRASENSORY) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 9 && learnset[i].move == MOVE_MUD_SLAP) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 14 && learnset[i].move == MOVE_QUICK_ATTACK) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 16 && learnset[i].move == MOVE_DEFENSE_CURL) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 18 && learnset[i].move == MOVE_DIG) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 30 && learnset[i].move == MOVE_SWIFT) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 34 && learnset[i].move == MOVE_FLAMETHROWER) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 40 && learnset[i].move == MOVE_EARTHQUAKE) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 65 && learnset[i].move == MOVE_BLAST_BURN) found = TRUE;
        EXPECT(found);
    }
}

TEST("Three Horizons playtest12 Totodile approved moves remain learnable")
{
    const struct LevelUpMove *learnset = gSpeciesInfo[SPECIES_TOTODILE].levelUpLearnset;
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 10 && learnset[i].move == MOVE_PURSUIT) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 40 && learnset[i].move == MOVE_CRUNCH) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 43 && learnset[i].move == MOVE_SCREECH) found = TRUE;
        EXPECT(found);
    }
}

TEST("Three Horizons playtest12 Croconaw approved moves remain learnable")
{
    const struct LevelUpMove *learnset = gSpeciesInfo[SPECIES_CROCONAW].levelUpLearnset;
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 10 && learnset[i].move == MOVE_PURSUIT) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 37 && learnset[i].move == MOVE_SLASH) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 40 && learnset[i].move == MOVE_CRUNCH) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 43 && learnset[i].move == MOVE_SCREECH) found = TRUE;
        EXPECT(found);
    }
}

TEST("Three Horizons playtest12 Feraligatr approved moves remain learnable")
{
    const struct LevelUpMove *learnset = gSpeciesInfo[SPECIES_FERALIGATR].levelUpLearnset;
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 1 && learnset[i].move == MOVE_ROCK_SLIDE) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 10 && learnset[i].move == MOVE_PURSUIT) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 38 && learnset[i].move == MOVE_SLASH) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 40 && learnset[i].move == MOVE_CRUNCH) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 43 && learnset[i].move == MOVE_SCREECH) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 65 && learnset[i].move == MOVE_HYDRO_CANNON) found = TRUE;
        EXPECT(found);
    }
}

TEST("Three Horizons playtest12 Ivysaur approved moves remain learnable")
{
    const struct LevelUpMove *learnset = gSpeciesInfo[SPECIES_IVYSAUR].levelUpLearnset;
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 28 && learnset[i].move == MOVE_MAGNITUDE) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 36 && learnset[i].move == MOVE_GIGA_DRAIN) found = TRUE;
        EXPECT(found);
    }
}

TEST("Three Horizons playtest12 Venusaur approved moves remain learnable")
{
    const struct LevelUpMove *learnset = gSpeciesInfo[SPECIES_VENUSAUR].levelUpLearnset;
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 1 && learnset[i].move == MOVE_ANCIENT_POWER) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 1 && learnset[i].move == MOVE_PETAL_DANCE) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 1 && learnset[i].move == MOVE_MUD_SLAP) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 28 && learnset[i].move == MOVE_MAGNITUDE) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 36 && learnset[i].move == MOVE_GIGA_DRAIN) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 40 && learnset[i].move == MOVE_EARTHQUAKE) found = TRUE;
        EXPECT(found);
    }
}

TEST("Three Horizons playtest12 Charmander approved moves remain learnable")
{
    const struct LevelUpMove *learnset = gSpeciesInfo[SPECIES_CHARMANDER].levelUpLearnset;
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 10 && learnset[i].move == MOVE_SMOKESCREEN) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 13 && learnset[i].move == MOVE_METAL_CLAW) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 16 && learnset[i].move == MOVE_RAGE) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 19 && learnset[i].move == MOVE_DRAGON_RAGE) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 34 && learnset[i].move == MOVE_FLAMETHROWER) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 45 && learnset[i].move == MOVE_DRAGON_CLAW) found = TRUE;
        EXPECT(found);
    }
}

TEST("Three Horizons playtest12 Charmeleon approved moves remain learnable")
{
    const struct LevelUpMove *learnset = gSpeciesInfo[SPECIES_CHARMELEON].levelUpLearnset;
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 1 && learnset[i].move == MOVE_FIRE_SPIN) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 10 && learnset[i].move == MOVE_SMOKESCREEN) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 13 && learnset[i].move == MOVE_METAL_CLAW) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 16 && learnset[i].move == MOVE_RAGE) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 19 && learnset[i].move == MOVE_DRAGON_RAGE) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 22 && learnset[i].move == MOVE_FIRE_PUNCH) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 34 && learnset[i].move == MOVE_FLAMETHROWER) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 45 && learnset[i].move == MOVE_DRAGON_CLAW) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 50 && learnset[i].move == MOVE_OUTRAGE) found = TRUE;
        EXPECT(found);
    }
}

TEST("Three Horizons playtest12 Charizard approved moves remain learnable")
{
    const struct LevelUpMove *learnset = gSpeciesInfo[SPECIES_CHARIZARD].levelUpLearnset;
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 1 && learnset[i].move == MOVE_ANCIENT_POWER) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 1 && learnset[i].move == MOVE_HEAT_WAVE) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 1 && learnset[i].move == MOVE_FIRE_SPIN) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 10 && learnset[i].move == MOVE_SMOKESCREEN) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 13 && learnset[i].move == MOVE_METAL_CLAW) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 16 && learnset[i].move == MOVE_RAGE) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 19 && learnset[i].move == MOVE_DRAGON_RAGE) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 22 && learnset[i].move == MOVE_FIRE_PUNCH) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 34 && learnset[i].move == MOVE_FLAMETHROWER) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 43 && learnset[i].move == MOVE_BODY_SLAM) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 45 && learnset[i].move == MOVE_DRAGON_CLAW) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 50 && learnset[i].move == MOVE_OUTRAGE) found = TRUE;
        EXPECT(found);
    }
}

TEST("Three Horizons playtest12 Squirtle approved moves remain learnable")
{
    const struct LevelUpMove *learnset = gSpeciesInfo[SPECIES_SQUIRTLE].levelUpLearnset;
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 17 && learnset[i].move == MOVE_METAL_CLAW) found = TRUE;
        EXPECT(found);
    }
}

TEST("Three Horizons playtest12 Wartortle approved moves remain learnable")
{
    const struct LevelUpMove *learnset = gSpeciesInfo[SPECIES_WARTORTLE].levelUpLearnset;
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 16 && learnset[i].move == MOVE_METAL_CLAW) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 30 && learnset[i].move == MOVE_IRON_TAIL) found = TRUE;
        EXPECT(found);
    }
}

TEST("Three Horizons playtest12 Blastoise approved moves remain learnable")
{
    const struct LevelUpMove *learnset = gSpeciesInfo[SPECIES_BLASTOISE].levelUpLearnset;
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 1 && learnset[i].move == MOVE_ICE_PUNCH) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 1 && learnset[i].move == MOVE_YAWN) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 16 && learnset[i].move == MOVE_METAL_CLAW) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 30 && learnset[i].move == MOVE_IRON_TAIL) found = TRUE;
        EXPECT(found);
    }
    {
        bool32 found = FALSE;
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
            if (learnset[i].level == 36 && learnset[i].move == MOVE_SPIKE_CANNON) found = TRUE;
        EXPECT(found);
    }
}

TEST("Three Horizons playtest12 Grovyle global types")
{
    EXPECT_EQ(gSpeciesInfo[SPECIES_GROVYLE].types[0], TYPE_GRASS);
    EXPECT_EQ(gSpeciesInfo[SPECIES_GROVYLE].types[1], TYPE_DRAGON);
}
TEST("Three Horizons playtest12 Sceptile global types")
{
    EXPECT_EQ(gSpeciesInfo[SPECIES_SCEPTILE].types[0], TYPE_GRASS);
    EXPECT_EQ(gSpeciesInfo[SPECIES_SCEPTILE].types[1], TYPE_DRAGON);
}
TEST("Three Horizons playtest12 Venusaur global types")
{
    EXPECT_EQ(gSpeciesInfo[SPECIES_VENUSAUR].types[0], TYPE_GRASS);
    EXPECT_EQ(gSpeciesInfo[SPECIES_VENUSAUR].types[1], TYPE_GROUND);
}
TEST("Three Horizons playtest12 Charizard global types")
{
    EXPECT_EQ(gSpeciesInfo[SPECIES_CHARIZARD].types[0], TYPE_FIRE);
    EXPECT_EQ(gSpeciesInfo[SPECIES_CHARIZARD].types[1], TYPE_DRAGON);
}
TEST("Three Horizons playtest12 Blastoise global types")
{
    EXPECT_EQ(gSpeciesInfo[SPECIES_BLASTOISE].types[0], TYPE_WATER);
    EXPECT_EQ(gSpeciesInfo[SPECIES_BLASTOISE].types[1], TYPE_STEEL);
}
TEST("Three Horizons playtest12 Bayleef global types")
{
    EXPECT_EQ(gSpeciesInfo[SPECIES_BAYLEEF].types[0], TYPE_GRASS);
    EXPECT_EQ(gSpeciesInfo[SPECIES_BAYLEEF].types[1], TYPE_DRAGON);
}
TEST("Three Horizons playtest12 Meganium global types")
{
    EXPECT_EQ(gSpeciesInfo[SPECIES_MEGANIUM].types[0], TYPE_GRASS);
    EXPECT_EQ(gSpeciesInfo[SPECIES_MEGANIUM].types[1], TYPE_DRAGON);
}
TEST("Three Horizons playtest12 Quilava global types")
{
    EXPECT_EQ(gSpeciesInfo[SPECIES_QUILAVA].types[0], TYPE_FIRE);
    EXPECT_EQ(gSpeciesInfo[SPECIES_QUILAVA].types[1], TYPE_GROUND);
}
TEST("Three Horizons playtest12 Typhlosion global types")
{
    EXPECT_EQ(gSpeciesInfo[SPECIES_TYPHLOSION].types[0], TYPE_FIRE);
    EXPECT_EQ(gSpeciesInfo[SPECIES_TYPHLOSION].types[1], TYPE_GROUND);
}
TEST("Three Horizons playtest12 Croconaw global types")
{
    EXPECT_EQ(gSpeciesInfo[SPECIES_CROCONAW].types[0], TYPE_WATER);
    EXPECT_EQ(gSpeciesInfo[SPECIES_CROCONAW].types[1], TYPE_DARK);
}
TEST("Three Horizons playtest12 Feraligatr global types")
{
    EXPECT_EQ(gSpeciesInfo[SPECIES_FERALIGATR].types[0], TYPE_WATER);
    EXPECT_EQ(gSpeciesInfo[SPECIES_FERALIGATR].types[1], TYPE_DARK);
}
TEST("Three Horizons playtest12 BLAZE_KICK approved balance")
{
    EXPECT_EQ((u32)gMovesInfo[MOVE_BLAZE_KICK].power, 95);
}
TEST("Three Horizons playtest12 LEAF_BLADE approved balance")
{
    EXPECT_EQ((u32)gMovesInfo[MOVE_LEAF_BLADE].power, 95);
}
TEST("Three Horizons playtest12 MUDDY_WATER approved balance")
{
    EXPECT_EQ((u32)gMovesInfo[MOVE_MUDDY_WATER].power, 95);
    EXPECT_EQ((u32)gMovesInfo[MOVE_MUDDY_WATER].accuracy, 100);
}
TEST("Three Horizons playtest12 SKY_UPPERCUT approved balance")
{
    EXPECT_EQ((u32)gMovesInfo[MOVE_SKY_UPPERCUT].accuracy, 100);
}
#endif
