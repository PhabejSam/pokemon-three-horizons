#include "global.h"
#include "event_data.h"
#include "item.h"
#include "three_horizons_chapter14.h"
#include "constants/three_horizons.h"
#include "constants/maps.h"

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
#endif
