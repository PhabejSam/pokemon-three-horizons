#include "global.h"
#include "test/test.h"
#include "three_horizons.h"
#include "event_data.h"
#include "constants/three_horizons.h"
#if THREE_HORIZONS
TEST("Three Horizons playtest12 Surge switches use the five column map grid")
{
    for (u32 a = 0; a <= 16; a++)
        for (u32 b = 0; b <= 16; b++)
        {
            bool32 expected = FALSE;
            if (a >= 1 && a <= 15 && b >= 1 && b <= 15)
            {
                u32 ax = (a - 1) % 5, ay = (a - 1) / 5;
                u32 bx = (b - 1) % 5, by = (b - 1) / 5;
                expected = (ax == bx && (ay + 1 == by || by + 1 == ay))
                    || (ay == by && (ax + 1 == bx || bx + 1 == ax));
            }
            EXPECT_EQ(TH12_AreSwitchesAdjacent(a, b), expected);
        }
}
TEST("Three Horizons playtest12 Surge wrong second resets and success survives entry")
{
    FlagClear(FLAG_TH12_SURGE_OPEN);
    for (u32 i = 0; i < 200; i++)
    {
        TH12_InitSurgeSwitches();
        EXPECT(TH12_AreSwitchesAdjacent(VarGet(VAR_TEMP_3), VarGet(VAR_TEMP_4)));
        EXPECT_EQ(VarGet(VAR_TEMP_5), 0);
    }
    VarSet(VAR_TEMP_3, 5);
    VarSet(VAR_TEMP_4, 10);
    gSpecialVar_0x8008 = 5;
    TH12_CheckSurgeSwitch();
    EXPECT_EQ(gSpecialVar_Result, 1);
    gSpecialVar_0x8008 = 6; // Next numeric ID is across the row boundary.
    TH12_CheckSurgeSwitch();
    EXPECT_EQ(gSpecialVar_Result, 3);
    EXPECT_EQ(VarGet(VAR_TEMP_5), 0);
    EXPECT(!FlagGet(FLAG_TH12_SURGE_OPEN));
    gSpecialVar_0x8008 = VarGet(VAR_TEMP_3);
    TH12_CheckSurgeSwitch();
    EXPECT_EQ(gSpecialVar_Result, 1);
    gSpecialVar_0x8008 = VarGet(VAR_TEMP_4);
    TH12_CheckSurgeSwitch();
    EXPECT_EQ(gSpecialVar_Result, 2);
    EXPECT(FlagGet(FLAG_TH12_SURGE_OPEN));
    TH12_InitSurgeSwitches();
    TH12_CheckSurgeSwitch();
    EXPECT_EQ(gSpecialVar_Result, 4);
    FlagClear(FLAG_TH12_SURGE_OPEN);
}
#endif
