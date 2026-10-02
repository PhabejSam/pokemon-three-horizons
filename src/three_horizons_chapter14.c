#include "global.h"
#include "event_data.h"
#include "item.h"
#include "three_horizons_chapter14.h"
#include "constants/three_horizons.h"
#include "constants/maps.h"
#include "battle.h"
#include "battle_setup.h"
#include "constants/opponents.h"

#if THREE_HORIZONS
bool32 TH_IsProjectMap(u8 mapGroup, u8 mapNum)
{
    return (mapGroup == TH_MAP_GROUP_LEGACY && mapNum < TH_MAP_COUNT_LEGACY)
        || (mapGroup == TH14_MAP_GROUP && mapNum < TH14_MAP_COUNT);
}

bool32 TH14_IsTowerMap(u8 mapGroup, u8 mapNum)
{
    return (mapGroup == MAP_GROUP(MAP_TH13_POKEMON_TOWER_1F)
            && mapNum >= MAP_NUM(MAP_TH13_POKEMON_TOWER_1F)
            && mapNum <= MAP_NUM(MAP_TH13_POKEMON_TOWER_6F))
        || (mapGroup == TH14_MAP_GROUP && mapNum == TH14_MAP_TOWER_7F);
}

static const struct
{
    u16 item;
    u16 receipt;
} sUniqueItems[] =
{
    {ITEM_TOWN_MAP, FLAG_TH14_TOWN_MAP},
    {ITEM_COIN_CASE, FLAG_TH14_COIN_CASE},
    {ITEM_TM19, FLAG_TH14_ERIKA_TM},
    {ITEM_LIFT_KEY, FLAG_TH14_LIFT_KEY},
    {ITEM_SILPH_SCOPE, FLAG_TH14_SILPH_SCOPE},
    {ITEM_POKE_FLUTE, FLAG_TH14_POKE_FLUTE},
};

u8 TH14_TryGiveUniqueItem(u16 itemId, u16 receiptFlag)
{
    u32 i;
    // Validate both fields before any item lookup or saved-flag access.
    for (i = 0; i < ARRAY_COUNT(sUniqueItems); i++)
        if (sUniqueItems[i].item == itemId && sUniqueItems[i].receipt == receiptFlag)
            break;
    if (i == ARRAY_COUNT(sUniqueItems))
        return TH14_GIFT_NO_ROOM;
    if (FlagGet(receiptFlag) || CheckBagHasItem(itemId, 1) || CheckPCHasItem(itemId, 1))
    {
        FlagSet(receiptFlag);
        return TH14_GIFT_ALREADY_OWNED;
    }
    if (!AddBagItem(itemId, 1))
        return TH14_GIFT_NO_ROOM;
    FlagSet(receiptFlag);
    return TH14_GIFT_GIVEN;
}

void TH14_ScriptGiveUniqueItem(void)
{
    gSpecialVar_Result = TH14_TryGiveUniqueItem(gSpecialVar_0x8004, gSpecialVar_0x8005);
}

void TH14_BeginRocketPair(void)
{
    if (FlagGet(FLAG_TH14_TRIO_DEFEATED))
        return;
    // A partial attempt is not a victory. The script checks two usable mons
    // first; restarting the pair never heals or changes the player's party.
    ClearTrainerFlag(TRAINER_TH14_JESSIE);
    ClearTrainerFlag(TRAINER_TH14_JAMES);
    InitTrainerBattleParameter();
    TRAINER_BATTLE_PARAM.opponentA = TRAINER_TH14_JESSIE;
    TRAINER_BATTLE_PARAM.opponentB = TRAINER_TH14_JAMES;
    TRAINER_BATTLE_PARAM.objEventLocalIdA = 10;
    TRAINER_BATTLE_PARAM.objEventLocalIdB = 11;
    TRAINER_BATTLE_PARAM.isDoubleBattle = TRUE;
    // The following trainerbattle command supplies text and continuation
    // pointers through the engine's existing two-opponent configuration.
}

void TH14_CompleteRocketPair(void)
{
    gSpecialVar_Result = gBattleOutcome == B_OUTCOME_WON
        && TRAINER_BATTLE_PARAM.opponentA == TRAINER_TH14_JESSIE
        && TRAINER_BATTLE_PARAM.opponentB == TRAINER_TH14_JAMES
        && !TRAINER_BATTLE_PARAM.isRematch
        && (gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS)
        && HasTrainerBeenFought(TRAINER_TH14_JESSIE)
        && HasTrainerBeenFought(TRAINER_TH14_JAMES);
    if (gSpecialVar_Result)
        FlagSet(FLAG_TH14_TRIO_DEFEATED);
}
#endif
