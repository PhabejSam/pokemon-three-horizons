#include "global.h"
#include "three_horizons.h"
#include "event_data.h"
#include "pokedex.h"
#include "constants/pokedex.h"
#include "constants/three_horizons.h"
#include "constants/trainers.h"
#if THREE_HORIZONS
void TH_MigrateSaveState(void)
{
    static const u16 variables[] = {VAR_TH_BROCK_GIFT, VAR_TH_MISTY_GIFT,
        VAR_TH_SHINY_RATE, VAR_TH_CLOCK_MODE, VAR_TH_CLOCK_REAL_LO,
        VAR_TH_CLOCK_REAL_HI, VAR_TH_CLOCK_DISPLAY_LO};
    u16 version = VarGet(VAR_TH_CLOCK_DISPLAY_HI) & TH_STATE_VERSION_MASK;
    if (version != TH_STATE_VERSION_9 && version != TH_STATE_VERSION_10 && version != TH_STATE_VERSION_11 && version != TH_STATE_VERSION_12)
    {
        // Only this chapter's newly owned state is cleared. Never touch the
        // original partner, rival, trainer flags, badges, clock setup or kit.
        for (u32 i=0;i<ARRAY_COUNT(variables);i++) VarSet(variables[i],0);
        // 0x21 belongs to the existing party EXP. SHARE; preserve it.
        for (u32 flag=FLAG_TH_MAGIKARP;flag<=FLAG_TH_LAB_INTRO;flag++) FlagClear(flag);
        VarSet(VAR_TH_CLOCK_DISPLAY_HI,TH_STATE_VERSION_9);
    }
    if (version != TH_STATE_VERSION_10 && version != TH_STATE_VERSION_11 && version != TH_STATE_VERSION_12)
    {
        FlagClear(FLAG_TH_DIG_TM);
        VarSet(VAR_TH_CLOCK_DISPLAY_HI, TH_STATE_VERSION_10 | (VarGet(VAR_TH_CLOCK_DISPLAY_HI) & 1));
    }
    if (version != TH_STATE_VERSION_11 && version != TH_STATE_VERSION_12)
    {
        FlagClear(FLAG_TH_ROCKET_DUO);
        FlagClear(TRAINER_FLAGS_START + TRAINER_TH11_JESSIE);
        FlagClear(TRAINER_FLAGS_START + TRAINER_TH11_JAMES);
        VarSet(VAR_TH_CLOCK_DISPLAY_HI, TH_STATE_VERSION_11 | (VarGet(VAR_TH_CLOCK_DISPLAY_HI) & 1));
    }
    if (version != TH_STATE_VERSION_12)
    {
        for (u32 flag = TH12_FLAGS_START; flag <= TH12_FLAGS_END; flag++)
            FlagClear(flag);
        for (u32 trainer = TH12_TRAINERS_START; trainer <= TH12_TRAINERS_END; trainer++)
            FlagClear(TRAINER_FLAGS_START + trainer);
        // Older releases did not store revival receipts. In those releases,
        // these species could only be obtained by restoring the collected fossil.
        if (FlagGet(FLAG_TH_FOSSIL_DOME) && GetSetPokedexFlag(NATIONAL_DEX_KABUTO, FLAG_GET_CAUGHT))
            FlagSet(FLAG_TH12_REVIVED_DOME);
        if (FlagGet(FLAG_TH_FOSSIL_HELIX) && GetSetPokedexFlag(NATIONAL_DEX_OMANYTE, FLAG_GET_CAUGHT))
            FlagSet(FLAG_TH12_REVIVED_HELIX);
        VarSet(VAR_TH_CLOCK_DISPLAY_HI, TH_STATE_VERSION_12 | (VarGet(VAR_TH_CLOCK_DISPLAY_HI) & 1));
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
