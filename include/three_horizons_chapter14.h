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

#endif
