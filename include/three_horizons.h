#ifndef GUARD_THREE_HORIZONS_H
#define GUARD_THREE_HORIZONS_H
#include "global.h"

struct THPartnerOptions
{
    u8 nature;
    bool8 shiny;
    u8 ivs[6];
    u8 evs[6];
};
bool32 TH_PartnerOptionsValid(const struct THPartnerOptions *options);
bool32 TH_TryGiveConfiguredStarter(u16 species, const struct THPartnerOptions *options);
void TH_OpenPartnerEditor(void);
void TH_ScriptGiveConfiguredStarter(void);

void TH_InitNewGame(void);
u16 TH_GetRivalStarter(u16 playerSpecies);
bool32 TH_TryGiveStarter(u16 playerSpecies);
bool32 TH_TryGiveSupplies(void);
void TH_FinishRivalBattle(void);
void TH_ScriptGiveStarter(void);
void TH_ScriptGiveSupplies(void);
#endif
