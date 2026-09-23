#include "global.h"
#include "three_horizons.h"
#include "event_data.h"
#include "item.h"
#include "pokemon.h"
#include "script_pokemon_util.h"
#include "constants/items.h"
#include "constants/three_horizons.h"

#if THREE_HORIZONS
static const u16 sStarters[][2] = {
    {SPECIES_BULBASAUR, SPECIES_CHARMANDER},
    {SPECIES_CHARMANDER, SPECIES_SQUIRTLE},
    {SPECIES_SQUIRTLE, SPECIES_BULBASAUR},
    {SPECIES_CHIKORITA, SPECIES_CYNDAQUIL},
    {SPECIES_CYNDAQUIL, SPECIES_TOTODILE},
    {SPECIES_TOTODILE, SPECIES_CHIKORITA},
    {SPECIES_TREECKO, SPECIES_TORCHIC},
    {SPECIES_TORCHIC, SPECIES_MUDKIP},
    {SPECIES_MUDKIP, SPECIES_TREECKO},
};

void TH_InitNewGame(void)
{
    VarSet(VAR_TH_STAGE, TH_STAGE_HOME);
    VarSet(VAR_TH_FIRST_PARTNER, SPECIES_NONE);
    VarSet(VAR_TH_RIVAL_PARTNER, SPECIES_NONE);
    VarSet(VAR_TH_SUPPLY_MASK, 0);
    VarSet(VAR_TH_SIGHTING_SEEN, 0);
}

u16 TH_GetRivalStarter(u16 species)
{
    u32 i;
    for (i = 0; i < ARRAY_COUNT(sStarters); ++i)
        if (sStarters[i][0] == species)
            return sStarters[i][1];
    return SPECIES_NONE;
}

bool32 TH_TryGiveStarter(u16 species)
{
    u16 rival = TH_GetRivalStarter(species);
    if (VarGet(VAR_TH_STAGE) != TH_STAGE_INVITED
        || VarGet(VAR_TH_FIRST_PARTNER) != SPECIES_NONE
        || gPartiesCount[B_TRAINER_PLAYER] != 0
        || rival == SPECIES_NONE)
        return FALSE;
    if (ScriptGiveMon(species, 5, ITEM_NONE) != MON_GIVEN_TO_PARTY)
        return FALSE;
    VarSet(VAR_TH_FIRST_PARTNER, species);
    VarSet(VAR_TH_RIVAL_PARTNER, rival);
    VarSet(VAR_TH_STAGE, TH_STAGE_PARTNER);
    FlagSet(FLAG_SYS_POKEMON_GET);
    return TRUE;
}

bool32 TH_TryGiveSupplies(void)
{
    u16 mask = VarGet(VAR_TH_SUPPLY_MASK);
    if (VarGet(VAR_TH_STAGE) < TH_STAGE_PARTNER)
        return FALSE;
    if (!(mask & TH_SUPPLY_BALLS))
    {
        if (!AddBagItem(ITEM_POKE_BALL, 5))
            return FALSE;
        mask |= TH_SUPPLY_BALLS;
        VarSet(VAR_TH_SUPPLY_MASK, mask);
    }
    if (!(mask & TH_SUPPLY_POTIONS))
    {
        if (!AddBagItem(ITEM_POTION, 2))
            return FALSE;
        mask |= TH_SUPPLY_POTIONS;
        VarSet(VAR_TH_SUPPLY_MASK, mask);
    }
    if (!(mask & TH_SUPPLY_DEX))
    {
        EnableNationalPokedex();
        FlagSet(FLAG_SYS_POKEDEX_GET);
        mask |= TH_SUPPLY_DEX;
        VarSet(VAR_TH_SUPPLY_MASK, mask);
    }
    return mask == TH_SUPPLIES_COMPLETE;
}

void TH_FinishRivalBattle(void)
{
    if (VarGet(VAR_TH_STAGE) == TH_STAGE_PARTNER)
        VarSet(VAR_TH_STAGE, TH_STAGE_BATTLE_DONE);
}

void TH_ScriptGiveStarter(void)
{
    gSpecialVar_Result = TH_TryGiveStarter(gSpecialVar_0x8004);
}

void TH_ScriptGiveSupplies(void)
{
    gSpecialVar_Result = TH_TryGiveSupplies();
}
#endif
