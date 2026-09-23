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

extern u8 gTHPendingRivalName[PLAYER_NAME_LENGTH + 1];
const u8 *TH_GetRivalName(void);
void TH_SetRivalName(const u8 *name);
bool32 TH_IsRivalTrainer(u16 trainerId);
bool32 TH_WantsToRun(u16 heldKeys);
u32 TH_ApplyExpRate(u32 experience);
u16 TH_GetOutfit(void);
u16 TH_GetTrainerPic(void);
void TH_ChangeOutfit(void);
void TH_InitNewGame(void);
void TH_StageNewGameOptions(void);
u16 TH_GetRivalStarter(u16 playerSpecies);
bool32 TH_TryGiveStarter(u16 playerSpecies);
bool32 TH_TryGiveSupplies(void);
void TH_FinishRivalBattle(void);
void TH_ScriptGiveStarter(void);
void TH_ScriptGiveSupplies(void);
#endif
