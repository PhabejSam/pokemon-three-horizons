#ifndef GUARD_THREE_HORIZONS_REMATCHES_H
#define GUARD_THREE_HORIZONS_REMATCHES_H
#include "global.h"
struct Pokemon;
struct Trainer;

struct TH13RematchEntry
{
    u16 trainerId;
    u16 map;
    u8 localId;
};

// Visual responders may share a canonical trainer, never another save slot.
struct TH14RematchAlias
{
    u16 trainerId;
    u16 map;
    u8 localId;
    u8 canonicalLocalId;
};
u16 TH14_ResolveMapTrainer(const struct TH13RematchEntry *entries, u32 count,
    const struct TH14RematchAlias *aliases, u32 aliasCount, u16 map, u8 localId);
u16 TH14_GetAuthoredRematchEvolution(u16 trainerId, u8 slot, u16 species, u8 scaledLevel, u8 badges);

// Readiness is a boolean at localId - 1, never a trainer ID.
s32 TH13_ResolveRematchSlot(const struct TH13RematchEntry *entries, u32 count, u16 map, u16 trainerId);
u16 TH13_GetMapTrainer(u8 localId);
bool32 TH13_MapHasRematchTrainers(void);
bool32 TH13_SetRematchReady(u16 trainerId);
bool32 TH13_IsRematchReady(u16 trainerId);
bool32 TH13_BeginRematch(u16 trainerId);
void TH13_ResetRematches(void);
void TH13_ScriptCheckRematch(void);
bool32 TH13_TryCreateRematchParty(struct Pokemon *party, u16 trainerId);
bool32 TH13_CreateRematchPartyFromTrainer(struct Pokemon *party, const struct Trainer *trainer, u8 highestLevel, u8 badges);
u8 TH13_HighestNonEggPartyLevel(void);
#endif
