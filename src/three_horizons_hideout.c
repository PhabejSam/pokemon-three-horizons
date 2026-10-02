#include "global.h"
#include "battle_setup.h"
#include "event_data.h"
#include "item.h"
#include "overworld.h"
#include "three_horizons_chapter14.h"
#include "constants/maps.h"
#include "constants/opponents.h"
#include "constants/three_horizons.h"

#if THREE_HORIZONS
bool32 TH14_ShouldSpawnObject(u8 mapGroup, u8 mapNum, u8 localId)
{
    if (mapGroup != TH14_MAP_GROUP) return TRUE;
    if (mapNum == MAP_NUM(MAP_TH14_CELADON_CITY_GAME_CORNER) && localId == 11)
        return !HasTrainerBeenFought(TRAINER_TH14_GAME_CORNER_GRUNT);
    if (mapNum == MAP_NUM(MAP_TH14_ROCKET_HIDEOUT_B4F))
    {
        if (localId == 4)
            return HasTrainerBeenFought(TRAINER_TH14_HIDEOUT_B4F_GRUNT1)
                && !FlagGet(FLAG_TH14_LIFT_KEY);
        if (localId == 2)
            return HasTrainerBeenFought(TRAINER_TH14_GIOVANNI)
                && !FlagGet(FLAG_TH14_SILPH_SCOPE);
        if (localId == 1)
            return !HasTrainerBeenFought(TRAINER_TH14_GIOVANNI);
    }
    return TRUE;
}

static const struct
{
    u16 map;
    u8 displayFloor;
    s8 x, y;
} sHideoutFloors[] = {
    {MAP_TH14_ROCKET_HIDEOUT_B1F, 3, 24, 25},
    {MAP_TH14_ROCKET_HIDEOUT_B2F, 2, 28, 16},
    {MAP_TH14_ROCKET_HIDEOUT_B4F, 0, 20, 23},
};

u16 TH14_GetHideoutFloor(void)
{
    const struct WarpData *warp = &gSaveBlock1Ptr->dynamicWarp;
    for (u32 i = 0; i < ARRAY_COUNT(sHideoutFloors); i++)
        if (warp->mapGroup == MAP_GROUP(sHideoutFloors[i].map)
         && warp->mapNum == MAP_NUM(sHideoutFloors[i].map))
            return sHideoutFloors[i].displayFloor;
    // B4F is zero in the native floor-name table, so zero cannot mean invalid.
    return TH14_INVALID_FLOOR;
}

bool32 TH14_SelectHideoutFloor(u16 choice)
{
    if (choice >= ARRAY_COUNT(sHideoutFloors) || !CheckBagHasItem(ITEM_LIFT_KEY, 1)
     || TH14_GetHideoutFloor() == TH14_INVALID_FLOOR)
        return FALSE;
    SetDynamicWarpWithCoords(0, MAP_GROUP(sHideoutFloors[choice].map),
        MAP_NUM(sHideoutFloors[choice].map), -1,
        sHideoutFloors[choice].x, sHideoutFloors[choice].y);
    return TRUE;
}

bool32 TH14_ScriptSelectHideoutFloor(void)
{
    u16 previous = TH14_GetHideoutFloor();
    if (!TH14_SelectHideoutFloor(gSpecialVar_0x8004)) return FALSE;
    gSpecialVar_0x8005 = previous;
    gSpecialVar_0x8006 = TH14_GetHideoutFloor();
    return TRUE;
}
#endif
