#ifndef GUARD_THREE_HORIZONS_H
#define GUARD_THREE_HORIZONS_H
#include "global.h"

void TH_InitNewGame(void);
u16 TH_GetRivalStarter(u16 playerSpecies);
bool32 TH_TryGiveStarter(u16 playerSpecies);
bool32 TH_TryGiveSupplies(void);
void TH_FinishRivalBattle(void);
void TH_ScriptGiveStarter(void);
void TH_ScriptGiveSupplies(void);
#endif
