#include "global.h"
#include "three_horizons.h"
#include "pokemon.h"
#include "constants/abilities.h"
#if THREE_HORIZONS
static const u16 sStarters[3][3] = {
    {SPECIES_BULBASAUR, SPECIES_CHARMANDER, SPECIES_SQUIRTLE},
    {SPECIES_CHIKORITA, SPECIES_CYNDAQUIL, SPECIES_TOTODILE},
    {SPECIES_TREECKO, SPECIES_TORCHIC, SPECIES_MUDKIP},
};
static s32 StarterIndex(u16 species)
{
    for (u32 i=0;i<9;i++)
        if (sStarters[i/3][i%3] == species) return i;
    return -1;
}
u16 TH_GetRivalCandidate(u16 species, u8 choice)
{
    s32 index=StarterIndex(species);
    if (index<0 || choice>1) return SPECIES_NONE;
    u8 region=index/3;
    u8 other=choice>=region ? choice+1 : choice;
    return sStarters[other][(index%3+1)%3];
}
u16 TH_GetBrockGift(u16 original, u8 choice)
{
    s32 index=StarterIndex(original);
    if (index<0 || choice>1) return SPECIES_NONE;
    u8 region=index/3;
    u8 other=choice>=region ? choice+1 : choice;
    return sStarters[other][index%3==2 ? 1 : 2];
}
u16 TH_GetMistyGift(u16 original, u16 brockGift)
{
    s32 first=StarterIndex(original), second=StarterIndex(brockGift);
    if (first<0 || second<0 || first/3==second/3 || first%3==second%3
        || (brockGift!=TH_GetBrockGift(original,0) && brockGift!=TH_GetBrockGift(original,1)))
        return SPECIES_NONE;
    return sStarters[3-first/3-second/3][3-first%3-second%3];
}
u8 TH_GetAbilityChoices(u16 species, u8 slots[3])
{
    u8 count=0;
    if (species==SPECIES_NONE || species>=NUM_SPECIES) return 0;
    for (u8 i=0;i<NUM_ABILITY_SLOTS;i++)
    {
        u16 ability=GetSpeciesAbility(species,i);
        bool32 duplicate=FALSE;
        for (u8 j=0;j<count;j++)
            if (ability==GetSpeciesAbility(species,slots[j])) duplicate=TRUE;
        if (ability!=ABILITY_NONE && !duplicate) slots[count++]=i;
    }
    return count;
}
bool32 TH_PartnerOptionsValidForSpecies(u16 species, const struct THPartnerOptions *options)
{
    return TH_PartnerOptionsValid(options) && species>SPECIES_NONE && species<NUM_SPECIES
        && options->abilityNum<NUM_ABILITY_SLOTS
        && GetSpeciesAbility(species,options->abilityNum)!=ABILITY_NONE;
}
#endif
