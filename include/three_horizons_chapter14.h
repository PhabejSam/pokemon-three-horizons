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

#endif
