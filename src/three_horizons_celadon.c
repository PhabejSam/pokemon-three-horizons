#include "global.h"
#include "event_data.h"
#include "coins.h"
#include "item.h"
#include "money.h"
#include "pokemon.h"
#include "script.h"
#include "script_pokemon_util.h"
#include "shop.h"
#include "three_horizons_chapter14.h"
#include "constants/layouts.h"
#include "constants/maps.h"
#include "constants/three_horizons.h"
#include "constants/coins.h"
#include "constants/vars.h"

#if THREE_HORIZONS
u16 TH14_GetDeptStoreFloor(void)
{
    static const u16 floors[] = {
        MAP_TH14_CELADON_CITY_DEPARTMENT_STORE_1F,
        MAP_TH14_CELADON_CITY_DEPARTMENT_STORE_2F,
        MAP_TH14_CELADON_CITY_DEPARTMENT_STORE_3F,
        MAP_TH14_CELADON_CITY_DEPARTMENT_STORE_4F,
        MAP_TH14_CELADON_CITY_DEPARTMENT_STORE_5F,
    };
    const struct WarpData *warp = &gSaveBlock1Ptr->dynamicWarp;
    for (u32 i = 0; i < ARRAY_COUNT(floors); i++)
        if (warp->mapGroup == MAP_GROUP(floors[i]) && warp->mapNum == MAP_NUM(floors[i]))
            return i + 4; // Native floor-name table uses indices 4..8 for 1F..5F.
    return 0;
}

u16 TH14_TryGiveEevee(void)
{
    if (FlagGet(FLAG_TH14_EEVEE))
        return TH14_EEVEE_ALREADY_GIVEN;
    // Ordinary donor gift generation; no partner customization or forced shiny.
    u32 result = ScriptGiveMon(SPECIES_EEVEE, 25, ITEM_NONE);
    if (result == MON_GIVEN_TO_PARTY || result == MON_GIVEN_TO_PC)
        FlagSet(FLAG_TH14_EEVEE);
    return result;
}

bool32 TH14_IsFrlgPokemonCenterLayout(u16 layoutId)
{
    return layoutId == LAYOUT_POKEMON_CENTER_1F_FRLG
        || layoutId == LAYOUT_TH14_CELADON_CITY_POKEMON_CENTER_1F;
}

#include "data/three_horizons_celadon.h"

// The native shop retains this pointer until it returns to the field.
static EWRAM_DATA u16 sShopItems[TH14_SHOP_CAPACITY] = {0};

static bool32 HasItem(u16 item)
{
    return CheckBagHasItem(item, 1) || CheckPCHasItem(item, 1);
}

static bool32 StockEligible(u32 row, u8 shop, u32 badges)
{
    return sCeladonStock[row].shop == shop && badges >= sCeladonStock[row].badges
        && (!sCeladonStock[row].flag || FlagGet(sCeladonStock[row].flag));
}

u16 TH14_BuildShopStock(u8 shopId, u16 *items, u16 capacity)
{
    u32 badges = 0, count = 0;
    if (!items || !capacity) return 0;
    items[0] = ITEM_NONE;
    if (shopId >= TH14_SHOP_COUNT) return 0;
    for (u32 i = 0; i < 8; i++) badges += FlagGet(FLAG_BADGE01_GET + i) != 0;
    for (u32 i = 0; i < ARRAY_COUNT(sCeladonStock); i++) count += StockEligible(i, shopId, badges);
    if (count + 1 > capacity) return 0;
    count = 0;
    for (u32 i = 0; i < ARRAY_COUNT(sCeladonStock); i++)
        if (StockEligible(i, shopId, badges)) items[count++] = sCeladonStock[i].item;
    items[count] = ITEM_NONE;
    return count;
}

void TH14_ScriptOpenShop(void)
{
    gSpecialVar_Result = 0;
    if (gSpecialVar_0x8004 >= TH14_SHOP_COUNT) return;
    gSpecialVar_Result = TH14_BuildShopStock(gSpecialVar_0x8004, sShopItems, ARRAY_COUNT(sShopItems));
    if (gSpecialVar_Result)
    {
        Script_RequestEffects(SCREFF_V1 | SCREFF_HARDWARE);
        CreatePokemartMenu(sShopItems);
        // The script waits only after a successful open; the native shop's
        // return callback resumes it. Empty/invalid stock never stops control.
    }
}

u8 TH14_TryBuyItemPrize(u8 prizeId)
{
    if (prizeId >= ARRAY_COUNT(sCeladonItemPrizes) || !CheckBagHasItem(ITEM_COIN_CASE, 1)) return TH14_PRIZE_INVALID;
    const u16 item = sCeladonItemPrizes[prizeId].item, cost = sCeladonItemPrizes[prizeId].coins;
    if (sCeladonItemPrizes[prizeId].reusable && HasItem(item)) return TH14_PRIZE_ALREADY_OWNED;
    if (GetCoins() < cost) return TH14_PRIZE_NO_FUNDS;
    if (!AddBagItem(item, 1)) return TH14_PRIZE_NO_ROOM;
    RemoveCoins(cost);
    return TH14_PRIZE_GIVEN;
}

u8 TH14_TryBuyMonPrize(u8 prizeId)
{
    if (prizeId >= ARRAY_COUNT(sCeladonMonPrizes) || !CheckBagHasItem(ITEM_COIN_CASE, 1)) return TH14_PRIZE_INVALID;
    if (GetCoins() < sCeladonMonPrizes[prizeId].coins) return TH14_PRIZE_NO_FUNDS;
    u32 destination = ScriptGiveMon(sCeladonMonPrizes[prizeId].species, sCeladonMonPrizes[prizeId].level, ITEM_NONE);
    if (destination != MON_GIVEN_TO_PARTY && destination != MON_GIVEN_TO_PC) return TH14_PRIZE_NO_ROOM;
    RemoveCoins(sCeladonMonPrizes[prizeId].coins);
    gSpecialVar_0x8006 = destination;
    VarSet(VAR_TEMP_TRANSFERRED_SPECIES, sCeladonMonPrizes[prizeId].species);
    return TH14_PRIZE_GIVEN;
}

u8 TH14_TryBuyCoins(u8 bundleId)
{
    if (bundleId >= ARRAY_COUNT(sCeladonCoinBundles) || !CheckBagHasItem(ITEM_COIN_CASE, 1)) return TH14_PRIZE_INVALID;
    u32 balance = GetCoins(), amount = sCeladonCoinBundles[bundleId].coins;
    if (balance + amount > MAX_COINS) return TH14_PRIZE_NO_ROOM;
    if (!IsEnoughMoney(&gSaveBlock1Ptr->money, sCeladonCoinBundles[bundleId].price)) return TH14_PRIZE_NO_FUNDS;
    SetCoins(balance + amount);
    RemoveMoney(&gSaveBlock1Ptr->money, sCeladonCoinBundles[bundleId].price);
    return TH14_PRIZE_GIVEN;
}

u8 TH14_TryGiveCoins(u8 giftId)
{
    if (giftId >= ARRAY_COUNT(sCeladonCoinGifts) || !CheckBagHasItem(ITEM_COIN_CASE, 1)) return TH14_PRIZE_INVALID;
    if (FlagGet(sCeladonCoinGifts[giftId].flag)) return TH14_PRIZE_ALREADY_OWNED;
    u32 balance = GetCoins(), amount = sCeladonCoinGifts[giftId].coins;
    if (balance + amount > MAX_COINS) return TH14_PRIZE_NO_ROOM;
    SetCoins(balance + amount);
    FlagSet(sCeladonCoinGifts[giftId].flag);
    return TH14_PRIZE_GIVEN;
}

u8 TH14_TryBuyDrink(u8 drinkId)
{
    if (drinkId >= ARRAY_COUNT(sCeladonDrinks)) return TH14_PRIZE_INVALID;
    u16 item = sCeladonDrinks[drinkId].item;
    u32 price = GetItemPrice(item);
    if (!IsEnoughMoney(&gSaveBlock1Ptr->money, price)) return TH14_PRIZE_NO_FUNDS;
    if (!AddBagItem(item, 1)) return TH14_PRIZE_NO_ROOM;
    RemoveMoney(&gSaveBlock1Ptr->money, price);
    return TH14_PRIZE_GIVEN;
}

u8 TH14_TryExchangeDrink(u8 drinkId)
{
    if (drinkId >= ARRAY_COUNT(sCeladonDrinks)) return TH14_PRIZE_INVALID;
    u16 item = sCeladonDrinks[drinkId].item, reward = sCeladonDrinks[drinkId].reward, flag = sCeladonDrinks[drinkId].flag;
    if (FlagGet(flag) || HasItem(reward)) return TH14_PRIZE_ALREADY_OWNED;
    if (!CheckBagHasItem(item, 1)) return TH14_PRIZE_NO_FUNDS;
    if (!AddBagItem(reward, 1)) return TH14_PRIZE_NO_ROOM;
    if (!RemoveBagItem(item, 1))
    {
        RemoveBagItem(reward, 1);
        return TH14_PRIZE_NO_FUNDS;
    }
    FlagSet(flag);
    return TH14_PRIZE_GIVEN;
}

void TH14_ScriptEconomy(void)
{
    const u16 action = gSpecialVar_0x8004, id = gSpecialVar_0x8005;
    gSpecialVar_Result = TH14_PRIZE_INVALID;
    if (id > 255) return; // Do not truncate a script halfword into a valid prize.
    switch (action)
    {
    case 0: gSpecialVar_Result = TH14_TryBuyItemPrize(id); break;
    case 1: gSpecialVar_Result = TH14_TryBuyMonPrize(id); break;
    case 2: gSpecialVar_Result = TH14_TryBuyCoins(id); break;
    case 3: gSpecialVar_Result = TH14_TryGiveCoins(id); break;
    case 4: gSpecialVar_Result = TH14_TryBuyDrink(id); break;
    case 5: gSpecialVar_Result = TH14_TryExchangeDrink(id); break;
    }
    if (gSpecialVar_Result != TH14_PRIZE_GIVEN) return;
    switch (action)
    {
    case 0: gSpecialVar_0x8007 = sCeladonItemPrizes[id].item; break;
    case 1: gSpecialVar_0x8007 = sCeladonMonPrizes[id].species; break;
    case 2: gSpecialVar_0x8007 = sCeladonCoinBundles[id].coins; break;
    case 3: gSpecialVar_0x8007 = sCeladonCoinGifts[id].coins; break;
    case 4: gSpecialVar_0x8007 = sCeladonDrinks[id].item; break;
    case 5: gSpecialVar_0x8007 = sCeladonDrinks[id].reward; break;
    }
}
#endif
