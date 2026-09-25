#include "global.h"
#include "three_horizons.h"
#include "event_data.h"
#include "rtc.h"
#include "constants/three_horizons.h"
#if THREE_HORIZONS
EWRAM_DATA bool8 gTHCreatingWildMon = FALSE;
static u32 Read32(u16 low, u16 high)
{
    u32 upper=VarGet(high);
    if (high==VAR_TH_CLOCK_DISPLAY_HI) upper &= 1;
    return VarGet(low) | (upper<<16);
}
static void Write32(u16 low, u16 high, u32 value)
{
    VarSet(low,value);
    VarSet(high,high==VAR_TH_CLOCK_DISPLAY_HI ? TH_STATE_VERSION_9 | ((value>>16)&1) : value>>16);
}
static u32 RealSeconds(void)
{
    RtcCalcLocalTime();
    s32 time=(s32)gLocalTime.days*86400 + gLocalTime.hours*3600 + gLocalTime.minutes*60 + gLocalTime.seconds;
    return time<0 ? 0 : time;
}
u32 TH_AdvanceVisualClock(u32 real, u32 visual, u32 now, u16 mode)
{
    u32 elapsed=now>=real ? now-real : 0;
    // Reduction before multiplication avoids overflow after large RTC changes.
    return (visual%86400 + (elapsed%86400)*(mode==1 ? 24 : 1))%86400;
}
void TH_ResetVisualClock(void)
{
    u32 now=RealSeconds();
    Write32(VAR_TH_CLOCK_REAL_LO,VAR_TH_CLOCK_REAL_HI,now);
    Write32(VAR_TH_CLOCK_DISPLAY_LO,VAR_TH_CLOCK_DISPLAY_HI,now%86400);
    FlagSet(FLAG_TH_CLOCK_ANCHORED);
}
u32 TH_GetVisualTimeSeconds(void)
{
    if (!FlagGet(FLAG_TH_CLOCK_ANCHORED)) TH_ResetVisualClock();
    u32 now=RealSeconds();
    u32 visual=TH_AdvanceVisualClock(Read32(VAR_TH_CLOCK_REAL_LO,VAR_TH_CLOCK_REAL_HI),
        Read32(VAR_TH_CLOCK_DISPLAY_LO,VAR_TH_CLOCK_DISPLAY_HI),now,VarGet(VAR_TH_CLOCK_MODE));
    Write32(VAR_TH_CLOCK_REAL_LO,VAR_TH_CLOCK_REAL_HI,now);
    Write32(VAR_TH_CLOCK_DISPLAY_LO,VAR_TH_CLOCK_DISPLAY_HI,visual);
    return visual;
}
void TH_SetClockMode(u8 mode)
{
    TH_GetVisualTimeSeconds();
    VarSet(VAR_TH_CLOCK_MODE,mode==1);
}
u16 TH_GetWildShinyThreshold(void)
{
    static const u16 rates[]={8,64,128,256};
    u16 rate=VarGet(VAR_TH_SHINY_RATE);
    return rates[rate<ARRAY_COUNT(rates) ? rate : 0];
}
#endif
