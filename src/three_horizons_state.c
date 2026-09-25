#include "global.h"
#include "three_horizons.h"
#include "event_data.h"
#include "constants/three_horizons.h"
#if THREE_HORIZONS
void TH_MigrateSaveState(void)
{
    static const u16 variables[] = {VAR_TH_BROCK_GIFT, VAR_TH_MISTY_GIFT,
        VAR_TH_SHINY_RATE, VAR_TH_CLOCK_MODE, VAR_TH_CLOCK_REAL_LO,
        VAR_TH_CLOCK_REAL_HI, VAR_TH_CLOCK_DISPLAY_LO};
    if ((VarGet(VAR_TH_CLOCK_DISPLAY_HI) & TH_STATE_VERSION_MASK) != TH_STATE_VERSION_9)
    {
        // Only this chapter's newly owned state is cleared. Never touch the
        // original partner, rival, trainer flags, badges, clock setup or kit.
        for (u32 i=0;i<ARRAY_COUNT(variables);i++) VarSet(variables[i],0);
        // 0x21 belongs to the existing party EXP. SHARE; preserve it.
        for (u32 flag=FLAG_TH_MAGIKARP;flag<=FLAG_TH_LAB_INTRO;flag++) FlagClear(flag);
        VarSet(VAR_TH_CLOCK_DISPLAY_HI,TH_STATE_VERSION_9);
    }
    if (VarGet(VAR_TH_CLOCK_MODE)>1) VarSet(VAR_TH_CLOCK_MODE,0);
    if (VarGet(VAR_TH_SHINY_RATE)>3) VarSet(VAR_TH_SHINY_RATE,0);
    u16 first=VarGet(VAR_TH_FIRST_PARTNER), brock=VarGet(VAR_TH_BROCK_GIFT);
    if (brock && brock!=TH_GetBrockGift(first,0) && brock!=TH_GetBrockGift(first,1))
        VarSet(VAR_TH_BROCK_GIFT,0);
    u16 misty=VarGet(VAR_TH_MISTY_GIFT);
    if (misty && misty!=TH_GetMistyGift(first,VarGet(VAR_TH_BROCK_GIFT)))
        VarSet(VAR_TH_MISTY_GIFT,0);
}
#endif
