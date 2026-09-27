#include "global.h"
#include "three_horizons.h"
#include "event_data.h"
#include "item.h"
#include "money.h"
#include "random.h"
#include "constants/trainers.h"
#include "constants/three_horizons.h"

#if THREE_HORIZONS
// A partial win is not a completed encounter. Restart both opponents after
// blackout or a save made between attempts; never heal the party here.
void TH12_BeginRocketPair(void)
{
    if (!FlagGet(FLAG_TH_ROCKET_DUO))
    {
        FlagClear(TRAINER_FLAGS_START + TRAINER_TH11_JESSIE);
        FlagClear(TRAINER_FLAGS_START + TRAINER_TH11_JAMES);
    }
}

void TH12_CompleteRocketPair(void)
{
    gSpecialVar_Result = FlagGet(TRAINER_FLAGS_START + TRAINER_TH11_JESSIE)
        && FlagGet(TRAINER_FLAGS_START + TRAINER_TH11_JAMES);
    if (gSpecialVar_Result)
        FlagSet(FLAG_TH_ROCKET_DUO);
}

// Trash cans 1..15 occupy five columns and three rows in the imported gym.
bool32 TH12_AreSwitchesAdjacent(u8 first, u8 second)
{
    if (first < 1 || first > 15 || second < 1 || second > 15)
        return FALSE;
    u32 ax = (first - 1) % 5, ay = (first - 1) / 5;
    u32 bx = (second - 1) % 5, by = (second - 1) / 5;
    return (ax == bx && (ay + 1 == by || by + 1 == ay))
        || (ay == by && (ax + 1 == bx || bx + 1 == ax));
}

void TH12_InitSurgeSwitches(void)
{
    u8 neighbors[4];
    u32 count = 0;
    u8 first = Random() % 15 + 1;
    for (u8 second = 1; second <= 15; second++)
        if (TH12_AreSwitchesAdjacent(first, second))
            neighbors[count++] = second;
    VarSet(VAR_TEMP_3, first);
    VarSet(VAR_TEMP_4, neighbors[Random() % count]);
    VarSet(VAR_TEMP_5, 0);
}

void TH12_CheckSurgeSwitch(void)
{
    if (FlagGet(FLAG_TH12_SURGE_OPEN))
        gSpecialVar_Result = 4;
    else if (VarGet(VAR_TEMP_5) == 0)
    {
        gSpecialVar_Result = gSpecialVar_0x8008 == VarGet(VAR_TEMP_3);
        if (gSpecialVar_Result)
            VarSet(VAR_TEMP_5, 1);
    }
    else if (gSpecialVar_0x8008 == VarGet(VAR_TEMP_4))
    {
        FlagSet(FLAG_TH12_SURGE_OPEN);
        gSpecialVar_Result = 2;
    }
    else
    {
        TH12_InitSurgeSwitches();
        gSpecialVar_Result = 3;
    }
}

void TH_TryGiveChapter12Supplies(void)
{
    gSpecialVar_Result = FALSE;
    if (VarGet(VAR_TH_STAGE) < TH_STAGE_PARTNER)
        return;
    if (!FlagGet(FLAG_TH12_START_MONEY))
    {
        AddMoney(&gSaveBlock1Ptr->money, 2000);
        FlagSet(FLAG_TH12_START_MONEY);
    }
    if (!FlagGet(FLAG_TH12_ULTRA_BALLS))
    {
        if (!AddBagItem(ITEM_ULTRA_BALL, 2))
            return;
        FlagSet(FLAG_TH12_ULTRA_BALLS);
    }
    gSpecialVar_Result = TRUE;
}
#endif
