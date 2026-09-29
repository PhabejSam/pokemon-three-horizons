#include "global.h"
#include "three_horizons.h"

#if THREE_HORIZONS
u8 TH13_GetRematchLevel(u8 highestLevel, u8 originalHighest, u8 badges)
{
    static const u8 caps[] = {24, 24, 24, 35, 45, 55, 65, 75, 100};
    u32 stage = min(badges, ARRAY_COUNT(caps) - 1);
    s32 floor = max(1, min(originalHighest, MAX_LEVEL));
    s32 cap = max(floor, caps[stage]);
    // Subtract before clamping using a signed value, including parties below 10.
    s32 target = (s32)highestLevel - 10;
    if (target < floor)
        return floor;
    if (target > cap)
        return cap;
    return target;
}
#endif
