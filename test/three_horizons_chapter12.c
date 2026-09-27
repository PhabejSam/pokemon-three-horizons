#include "global.h"
#include "test/test.h"
#include "three_horizons.h"
#include "event_data.h"
#include "constants/three_horizons.h"
#include "constants/trainers.h"
#if THREE_HORIZONS
TEST("Three Horizons playtest12 repeated Continue preserves completed earlier chapters")
{
    VarSet(VAR_TH_CLOCK_DISPLAY_HI, 0xA909);
    VarSet(VAR_TH_CLOCK_DISPLAY_LO, 12345);
    VarSet(VAR_TH_CLOCK_MODE, 1);
    VarSet(VAR_TH_SHINY_RATE, 3);
    VarSet(VAR_TH_FIRST_PARTNER, SPECIES_TORCHIC);
    VarSet(VAR_TH_RIVAL_PARTNER, SPECIES_TOTODILE);
    VarSet(VAR_TH_BROCK_GIFT, SPECIES_SQUIRTLE);
    VarSet(VAR_TH_MISTY_GIFT, SPECIES_CHIKORITA);
    FlagSet(FLAG_BADGE01_GET);
    FlagSet(FLAG_BADGE02_GET);
    FlagSet(FLAG_TH_FOSSIL_DOME);
    FlagSet(FLAG_TH_FOSSIL_HELIX);
    FlagSet(FLAG_TH_DIG_TM);
    FlagSet(FLAG_TH_ROCKET_DUO);
    FlagSet(TRAINER_FLAGS_START + TRAINER_TH11_JESSIE);
    FlagSet(TRAINER_FLAGS_START + TRAINER_TH11_JAMES);
    for (u32 pass = 0; pass < 2; pass++)
    {
        TH_MigrateSaveState();
        EXPECT_EQ(VarGet(VAR_TH_CLOCK_DISPLAY_HI), 0xA909);
        EXPECT_EQ(VarGet(VAR_TH_CLOCK_DISPLAY_LO), 12345);
        EXPECT_EQ(VarGet(VAR_TH_CLOCK_MODE), 1);
        EXPECT_EQ(VarGet(VAR_TH_SHINY_RATE), 3);
        EXPECT_EQ(VarGet(VAR_TH_BROCK_GIFT), SPECIES_SQUIRTLE);
        EXPECT_EQ(VarGet(VAR_TH_MISTY_GIFT), SPECIES_CHIKORITA);
        EXPECT(FlagGet(FLAG_BADGE01_GET));
        EXPECT(FlagGet(FLAG_BADGE02_GET));
        EXPECT(FlagGet(FLAG_TH_FOSSIL_DOME));
        EXPECT(FlagGet(FLAG_TH_FOSSIL_HELIX));
        EXPECT(FlagGet(FLAG_TH_DIG_TM));
        EXPECT(FlagGet(FLAG_TH_ROCKET_DUO));
        EXPECT(FlagGet(TRAINER_FLAGS_START + TRAINER_TH11_JESSIE));
        EXPECT(FlagGet(TRAINER_FLAGS_START + TRAINER_TH11_JAMES));
    }
}
#endif
