#include "global.h"
#include "three_horizons.h"
#include "pokemon.h"

#if THREE_HORIZONS
bool32 TH_IsConfigurableCapture(u16 species)
{
    return species > SPECIES_NONE && species < NUM_SPECIES
        && (gSpeciesInfo[species].isRestrictedLegendary
            || gSpeciesInfo[species].isSubLegendary || gSpeciesInfo[species].isMythical);
}

void TH_ReadMonOptions(struct Pokemon *mon, struct THPartnerOptions *options)
{
    options->nature = GetMonData(mon, MON_DATA_HIDDEN_NATURE);
    options->shiny = GetMonData(mon, MON_DATA_IS_SHINY);
    for (u32 i = 0; i < NUM_STATS; i++)
    {
        options->ivs[i] = GetMonData(mon, MON_DATA_HP_IV + i);
        options->evs[i] = GetMonData(mon, MON_DATA_HP_EV + i);
    }
}

bool32 TH_ApplyCaughtMonOptions(struct Pokemon *mon, const struct THPartnerOptions *options)
{
    struct Pokemon changed;
    bool32 shiny;
    if (mon == NULL || !TH_IsConfigurableCapture(GetMonData(mon, MON_DATA_SPECIES))
        || GetMonData(mon, MON_DATA_IS_EGG) || !TH_PartnerOptionsValid(options))
        return FALSE;
    changed = *mon;
    shiny = options->shiny;
    SetMonData(&changed, MON_DATA_IS_SHINY, &shiny);
    // Effective nature is independent of PID, gender, form and ability.
    SetMonData(&changed, MON_DATA_HIDDEN_NATURE, &options->nature);
    for (u32 i = 0; i < NUM_STATS; i++)
    {
        SetMonData(&changed, MON_DATA_HP_IV + i, &options->ivs[i]);
        SetMonData(&changed, MON_DATA_HP_EV + i, &options->evs[i]);
    }
    TH_RecalculateWithoutHealing(&changed, GetMonData(mon, MON_DATA_HP), GetMonData(mon, MON_DATA_MAX_HP));
    *mon = changed;
    return TRUE;
}
#endif
