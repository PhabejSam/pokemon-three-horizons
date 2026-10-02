#include "global.h"
#include "three_horizons_chapter14.h"

#if THREE_HORIZONS
bool32 TH_IsProjectMap(u8 mapGroup, u8 mapNum)
{
    return (mapGroup == TH_MAP_GROUP_LEGACY && mapNum < TH_MAP_COUNT_LEGACY)
        || (mapGroup == TH14_MAP_GROUP && mapNum < TH14_MAP_COUNT);
}
#endif
