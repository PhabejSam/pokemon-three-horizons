#include "global.h"
#include "test/test.h"
#include "three_horizons.h"
#include "event_data.h"
#include "constants/three_horizons.h"
#if THREE_HORIZONS
TEST("Three Horizons revision9 legacy state migration preserves established progress")
{
    VarSet(VAR_TH_STAGE,TH_STAGE_COMPLETE);
    VarSet(VAR_TH_FIRST_PARTNER,SPECIES_TORCHIC);
    VarSet(VAR_TH_RIVAL_PARTNER,SPECIES_TOTODILE);
    VarSet(VAR_TH_TRAINING_KIT_MASK,0x7F);
    FlagSet(FLAG_BADGE01_GET);
    FlagSet(FLAG_SET_WALL_CLOCK);
    VarSet(VAR_TH_BROCK_GIFT,0xFFFF);
    VarSet(VAR_TH_MISTY_GIFT,0xFFFF);
    VarSet(VAR_TH_SHINY_RATE,0xFFFF);
    VarSet(VAR_TH_CLOCK_MODE,0x0101);
    VarSet(VAR_TH_CLOCK_DISPLAY_HI,0xFFFF);
    FlagSet(FLAG_TH_CLOCK_ANCHORED);
    FlagSet(FLAG_TH_MAGIKARP);
    FlagSet(FLAG_TH_PICKUP_0);
    TH_MigrateSaveState();
    EXPECT_EQ(VarGet(VAR_TH_BROCK_GIFT),0);
    EXPECT_EQ(VarGet(VAR_TH_MISTY_GIFT),0);
    EXPECT_EQ(VarGet(VAR_TH_CLOCK_MODE),0);
    EXPECT_EQ(VarGet(VAR_TH_SHINY_RATE),0);
    EXPECT(!FlagGet(FLAG_TH_CLOCK_ANCHORED));
    EXPECT(!FlagGet(FLAG_TH_MAGIKARP));
    EXPECT(!FlagGet(FLAG_TH_PICKUP_0));
    EXPECT_EQ(VarGet(VAR_TH_FIRST_PARTNER),SPECIES_TORCHIC);
    EXPECT_EQ(VarGet(VAR_TH_RIVAL_PARTNER),SPECIES_TOTODILE);
    EXPECT_EQ(VarGet(VAR_TH_STAGE),TH_STAGE_COMPLETE);
    EXPECT_EQ(VarGet(VAR_TH_TRAINING_KIT_MASK),0x7F);
    EXPECT(FlagGet(FLAG_BADGE01_GET));
    EXPECT(FlagGet(FLAG_SET_WALL_CLOCK));
    VarSet(VAR_TH_BROCK_GIFT,SPECIES_SQUIRTLE);
    VarSet(VAR_TH_MISTY_GIFT,SPECIES_CHIKORITA);
    FlagSet(FLAG_TH_MAGIKARP);
    TH_MigrateSaveState();
    EXPECT_EQ(VarGet(VAR_TH_BROCK_GIFT),SPECIES_SQUIRTLE);
    EXPECT_EQ(VarGet(VAR_TH_MISTY_GIFT),SPECIES_CHIKORITA);
    EXPECT(FlagGet(FLAG_TH_MAGIKARP));
}
TEST("Three Horizons revision9 invalid full-width clock mode uses real time")
{
    volatile u16 invalid=0x0101;
    EXPECT_EQ(TH_AdvanceVisualClock(100,200,160,invalid),260);
}
#endif
