#include "global.h"
#include "three_horizons.h"
#include "field_player_avatar.h"
#include "event_object_movement.h"
#include "constants/event_object_movement.h"
#include "constants/trainers.h"
#include "event_data.h"
#include "item.h"
#include "pokemon.h"
#include "script_pokemon_util.h"
#include "constants/items.h"
#include "constants/three_horizons.h"

#if THREE_HORIZONS
u16 TH_GetOutfit(void)
{
    u16 outfit = VarGet(VAR_TH_OUTFIT);
    return outfit < TH_OUTFIT_COUNT ? outfit : TH_OUTFIT_RED;
}

u16 TH_GetTrainerPic(void)
{
    static const u16 pics[] = {TRAINER_PIC_RED, TRAINER_PIC_LEAF, TRAINER_PIC_BRENDAN, TRAINER_PIC_MAY};
    return pics[TH_GetOutfit()];
}

void TH_ChangeOutfit(void)
{
    if (gSpecialVar_0x8004 >= TH_OUTFIT_COUNT)
        return;
    VarSet(VAR_TH_OUTFIT, gSpecialVar_0x8004);
    ObjectEventSetGraphicsId(&gObjectEvents[gPlayerAvatar.objectEventId], GetPlayerAvatarGraphicsIdByStateId(PLAYER_AVATAR_STATE_NORMAL));
    ObjectEventTurn(&gObjectEvents[gPlayerAvatar.objectEventId], gObjectEvents[gPlayerAvatar.objectEventId].facingDirection);
}

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
    VarSet(VAR_TH_OUTFIT, TH_OUTFIT_RED);
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

bool32 TH_PartnerOptionsValid(const struct THPartnerOptions *options)
{
    u32 i, total = 0;
    if (options == NULL || options->nature >= NUM_NATURES || options->shiny > TRUE)
        return FALSE;
    for (i = 0; i < 6; i++)
    {
        if (options->ivs[i] > 31 || options->evs[i] > 252)
            return FALSE;
        total += options->evs[i];
    }
    return total <= 510;
}

bool32 TH_TryGiveConfiguredStarter(u16 species, const struct THPartnerOptions *options)
{
    struct Pokemon mon;
    u32 i;
    bool32 shiny;
    u16 hp, rival = TH_GetRivalStarter(species);
    if (!TH_PartnerOptionsValid(options) || rival == SPECIES_NONE
        || VarGet(VAR_TH_STAGE) != TH_STAGE_INVITED
        || VarGet(VAR_TH_FIRST_PARTNER) != SPECIES_NONE
        || gPartiesCount[B_TRAINER_PLAYER] != 0)
        return FALSE;

    CreateMon(&mon, species, 5,
        GetMonPersonality(species, MON_GENDER_RANDOM, options->nature, RANDOM_UNOWN_LETTER),
        OTID_STRUCT_PLAYER_ID);
    shiny = options->shiny;
    SetMonData(&mon, MON_DATA_IS_SHINY, &shiny);
    for (i = 0; i < 6; i++)
    {
        SetMonData(&mon, MON_DATA_HP_IV + i, &options->ivs[i]);
        SetMonData(&mon, MON_DATA_HP_EV + i, &options->evs[i]);
    }
    GiveMonInitialMoveset(&mon);
    CalculateMonStats(&mon);
    hp = GetMonData(&mon, MON_DATA_MAX_HP);
    SetMonData(&mon, MON_DATA_HP, &hp);
    if (GiveScriptedMonToPlayer(&mon, PARTY_SIZE) != MON_GIVEN_TO_PARTY)
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
