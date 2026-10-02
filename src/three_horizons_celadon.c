#include "global.h"
#include "event_data.h"
#include "pokemon.h"
#include "script_pokemon_util.h"
#include "three_horizons_chapter14.h"
#include "constants/layouts.h"
#include "constants/maps.h"
#include "constants/three_horizons.h"

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
#endif
