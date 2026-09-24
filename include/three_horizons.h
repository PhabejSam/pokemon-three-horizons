#ifndef GUARD_THREE_HORIZONS_H
#define GUARD_THREE_HORIZONS_H
#include "global.h"
struct Pokemon;
u16 TH_GetBattleEvolution(struct Pokemon *mon, bool32 *canStop);
bool32 TH_TryBattleEvolution(u32 partyId);
void TH_SyncEvolvedBattleMon(u32 partyId, struct Pokemon *before);
void TH_RefreshFollower(void);

u16 TH_TryDeliverTrainingKit(void);
void TH_ScriptDeliverTrainingKit(void);
u32 TH_GetTrainingItemPrice(u16 itemId, u32 fallback);
bool32 TH_TryImproveIVs(struct Pokemon *mon, u16 itemId, u8 stat);
void TH_ScriptImproveIVs(void);
void TH_RecalculateWithoutHealing(struct Pokemon *mon, u16 oldHP, u16 oldMaxHP);

struct THPartnerOptions
{
    u8 nature;
    bool8 shiny;
    u8 ivs[6];
    u8 evs[6];
};
bool32 TH_PartnerOptionsValid(const struct THPartnerOptions *options);
bool32 TH_IsConfigurableCapture(u16 species);
void TH_ReadMonOptions(struct Pokemon *mon, struct THPartnerOptions *options);
bool32 TH_ApplyCaughtMonOptions(struct Pokemon *mon, const struct THPartnerOptions *options);
bool32 TH_OpenCaughtMonEditor(struct Pokemon *mon, void (*returnCallback)(void));
bool32 TH_TryGiveConfiguredStarter(u16 species, const struct THPartnerOptions *options);
void TH_OpenPartnerEditor(void);
void TH_ScriptGiveConfiguredStarter(void);

extern u8 gTHPendingRivalName[PLAYER_NAME_LENGTH + 1];
const u8 *TH_GetRivalName(void);
void TH_SetRivalName(const u8 *name);
bool32 TH_IsRivalTrainer(u16 trainerId);
bool32 TH_WantsToRun(u16 heldKeys);
u32 TH_ApplyExpRate(u32 experience);
u32 TH_GetWhiteoutMoneyLoss(u32 money, u32 battleFlags);
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
