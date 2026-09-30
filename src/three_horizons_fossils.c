#include "global.h"
#include "three_horizons.h"
#include "pokemon.h"
#include "event_data.h"
#include "item.h"
#include "constants/three_horizons.h"
#if THREE_HORIZONS
u8 TH_TryReviveFossil(u16 item)
{
    struct Pokemon mon;
    u16 species;
    if (!FlagGet(FLAG_BADGE02_GET) || !CheckBagHasItem(item, 1))
        return MON_CANT_GIVE;
    if (item == ITEM_DOME_FOSSIL)
        species = SPECIES_KABUTO;
    else if (item == ITEM_HELIX_FOSSIL)
        species = SPECIES_OMANYTE;
    else
        return MON_CANT_GIVE;
    CreateRandomMon(&mon, species, 20);
    u8 result = GiveScriptedMonToPlayer(&mon, PARTY_SIZE);
    if (result != MON_CANT_GIVE)
    {
        RemoveBagItem(item, 1);
        FlagSet(item == ITEM_DOME_FOSSIL ? FLAG_TH12_REVIVED_DOME : FLAG_TH12_REVIVED_HELIX);
    }
    return result;
}

void TH_ScriptReviveFossil(void)
{
    gSpecialVar_Result = TH_TryReviveFossil(gSpecialVar_0x8004);
    gSpecialVar_0x8009 = gSpecialVar_Result;
}
#endif
