#include "global.h"
#include "test/test.h"
#include "three_horizons.h"
#include "event_data.h"
#include "pokedex.h"
#include "script.h"

#if THREE_HORIZONS
extern u16 GetFrlgPokedexCount(void);
TEST("Three Horizons PT14 leads: Flash quota counts caught species across approved regions")
{
    InitEventData(); ResetPokedex();
    for (u32 n = 1; n <= 9; n++) GetSetPokedexFlag(n, FLAG_SET_CAUGHT);
    gSpecialVar_0x8004 = 1;
    GetFrlgPokedexCount(); EXPECT_EQ(gSpecialVar_0x8006,9);
    GetSetPokedexFlag(NATIONAL_DEX_CYNDAQUIL, FLAG_SET_SEEN);
    GetFrlgPokedexCount(); EXPECT_EQ(gSpecialVar_0x8006,9);
    GetSetPokedexFlag(NATIONAL_DEX_CYNDAQUIL, FLAG_SET_CAUGHT);
    GetFrlgPokedexCount(); EXPECT_EQ(gSpecialVar_0x8006,10);
    // Repeated registration (including a gift already registered) is one species.
    GetSetPokedexFlag(NATIONAL_DEX_CYNDAQUIL, FLAG_SET_CAUGHT);
    GetFrlgPokedexCount(); EXPECT_EQ(gSpecialVar_0x8006,10);
}
TEST("Three Horizons PT14 leads: old Flash rival cameo and endpoint receipts survive migration")
{
    const u16 flags[] = {FLAG_TH13_FLASH, FLAG_TH13_LAVENDER_RIVAL,
        FLAG_TH13_ROCKET_CAMEO, FLAG_TH13_ENDPOINT};
    for (u32 mask = 0; mask < 16; mask++)
    {
        InitEventData(); VarSet(VAR_TH_CLOCK_DISPLAY_HI,0xA90C);
        for (u32 i = 0; i < ARRAY_COUNT(flags); i++)
            if (mask & (1u << i)) FlagSet(flags[i]);
        TH_MigrateSaveState(); TH_MigrateSaveState();
        for (u32 i = 0; i < ARRAY_COUNT(flags); i++)
            EXPECT_EQ(FlagGet(flags[i]),!!(mask & (1u << i)));
    }
}
#endif
