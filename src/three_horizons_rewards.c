#include "global.h"
#include "three_horizons.h"
#include "pokemon.h"
#include "event_data.h"
#include "money.h"
#include "constants/three_horizons.h"
#if THREE_HORIZONS
u8 TH_TryDeliverReward(enum THReward reward, struct Pokemon *mon)
{
    u16 first=VarGet(VAR_TH_FIRST_PARTNER), species=GetMonData(mon,MON_DATA_SPECIES);
    if (reward==TH_REWARD_BROCK)
    {
        if (!FlagGet(FLAG_BADGE01_GET) || VarGet(VAR_TH_BROCK_GIFT)
            || (species!=TH_GetBrockGift(first,0) && species!=TH_GetBrockGift(first,1))) return MON_CANT_GIVE;
    }
    else if (reward==TH_REWARD_MISTY)
    {
        if (!FlagGet(FLAG_BADGE02_GET) || VarGet(VAR_TH_MISTY_GIFT)
            || species==SPECIES_NONE || species!=TH_GetMistyGift(first,VarGet(VAR_TH_BROCK_GIFT))) return MON_CANT_GIVE;
    }
    else if (reward==TH_REWARD_MAGIKARP)
    {
        if (FlagGet(FLAG_TH_MAGIKARP) || species!=SPECIES_MAGIKARP || GetMoney(&gSaveBlock1Ptr->money)<500) return MON_CANT_GIVE;
    }
    else return MON_CANT_GIVE;
    u8 result=GiveScriptedMonToPlayer(mon,PARTY_SIZE);
    if (result==MON_CANT_GIVE) return result;
    if (reward==TH_REWARD_BROCK) VarSet(VAR_TH_BROCK_GIFT,species);
    else if (reward==TH_REWARD_MISTY) VarSet(VAR_TH_MISTY_GIFT,species);
    else
    {
        RemoveMoney(&gSaveBlock1Ptr->money,500);
        FlagSet(FLAG_TH_MAGIKARP);
    }
    return result;
}
void TH_ScriptRewardChoices(void)
{
    u16 first=VarGet(VAR_TH_FIRST_PARTNER);
    if (gSpecialVar_0x8006==TH_REWARD_BROCK)
    {
        gSpecialVar_0x8007=TH_GetBrockGift(first,0);
        gSpecialVar_0x8008=TH_GetBrockGift(first,1);
    }
    else gSpecialVar_0x8007=TH_GetMistyGift(first,VarGet(VAR_TH_BROCK_GIFT));
}
#endif
