#ifndef GUARD_THREE_HORIZONS_CHAPTER14_H
#define GUARD_THREE_HORIZONS_CHAPTER14_H

#include "global.h"

// ROM-side identity bounds. Existing signed one-byte saved warps stay intact.
#define TH_MAP_GROUP_LEGACY 75
#define TH_MAP_COUNT_LEGACY 118
#define TH14_MAP_GROUP 76
#define TH14_MAP_COUNT 37
#define TH14_MAP_TOWER_7F 33

bool32 TH_IsProjectMap(u8 mapGroup, u8 mapNum);
bool32 TH14_IsTowerMap(u8 mapGroup, u8 mapNum);

enum TH14GiftResult
{
    TH14_GIFT_NO_ROOM = 0,
    TH14_GIFT_GIVEN = 1,
    TH14_GIFT_ALREADY_OWNED = 2,
};

u8 TH14_TryGiveUniqueItem(u16 itemId, u16 receiptFlag);
void TH14_ScriptGiveUniqueItem(void);

#define TH14_EEVEE_ALREADY_GIVEN 3
u16 TH14_GetDeptStoreFloor(void);
u16 TH14_TryGiveEevee(void);
bool32 TH14_IsFrlgPokemonCenterLayout(u16 layoutId);

enum TH14PrizeResult
{
    TH14_PRIZE_INVALID = 0,
    TH14_PRIZE_GIVEN = 1,
    TH14_PRIZE_NO_FUNDS = 2,
    TH14_PRIZE_NO_ROOM = 3,
    TH14_PRIZE_ALREADY_OWNED = 4,
};

u16 TH14_BuildShopStock(u8 shopId, u16 *items, u16 capacity);
void TH14_ScriptOpenShop(void);
u8 TH14_TryBuyItemPrize(u8 prizeId);
u8 TH14_TryBuyMonPrize(u8 prizeId);
u8 TH14_TryBuyCoins(u8 bundleId);
u8 TH14_TryGiveCoins(u8 giftId);
u8 TH14_TryBuyDrink(u8 drinkId);
u8 TH14_TryExchangeDrink(u8 drinkId);
void TH14_ScriptEconomy(void);

bool32 TH14_ShouldSpawnObject(u8 mapGroup, u8 mapNum, u8 localId);
#define TH14_INVALID_FLOOR 0xFFFF
u16 TH14_GetHideoutFloor(void);
bool32 TH14_SelectHideoutFloor(u16 choice);
bool32 TH14_ScriptSelectHideoutFloor(void);

#endif
