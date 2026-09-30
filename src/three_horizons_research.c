#include "global.h"
#include "event_data.h"
#include "overworld.h"
#include "palette.h"
#include "gpu_regs.h"
#include "script.h"
#include "three_horizons_research.h"
#include "constants/three_horizons.h"
#include "constants/event_objects.h"
#include "constants/maps.h"

#if THREE_HORIZONS
#include "data/three_horizons_research.h"

// Hardware fades preserve palette owners but temporarily replace blending and
// window effects. A same-map photograph must restore the complete field state.
static const u8 sPhotoRegisterOffsets[] = {REG_OFFSET_BLDCNT, REG_OFFSET_BLDALPHA, REG_OFFSET_BLDY, REG_OFFSET_WININ, REG_OFFSET_WINOUT};
static EWRAM_DATA u16 sPhotoRegisters[ARRAY_COUNT(sPhotoRegisterOffsets)] = {0};
static EWRAM_DATA bool8 sPhotoFlashActive = FALSE;
void TH_ScriptBeginPhotoFlash(void)
{
    if (sPhotoFlashActive) return;
    for (u32 i = 0; i < ARRAY_COUNT(sPhotoRegisterOffsets); i++)
        sPhotoRegisters[i] = GetGpuReg(sPhotoRegisterOffsets[i]);
    sPhotoFlashActive = TRUE;
}
void TH_ScriptEndPhotoFlash(void)
{
    if (!sPhotoFlashActive) return;
    for (u32 i = 0; i < ARRAY_COUNT(sPhotoRegisterOffsets); i++)
        SetGpuReg(sPhotoRegisterOffsets[i], sPhotoRegisters[i]);
    sPhotoFlashActive = FALSE;
}

extern const u8 TH13_ResearchCall_Activation[];
extern const u8 TH13_ResearchCall_Route10[];
extern const u8 TH13_ResearchCall_Lavender[];
extern const u8 TH13_ResearchCall_Elm[], TH13_ResearchCall_Birch[];
static const u8 *const sResearchCallScripts[TH_RESEARCH_CALL_COUNT] = {
    [TH_CALL_ACTIVATION] = TH13_ResearchCall_Activation,
    [TH_CALL_ROUTE10] = TH13_ResearchCall_Route10,
    [TH_CALL_LAVENDER] = TH13_ResearchCall_Lavender,
    [TH_CALL_ELM] = TH13_ResearchCall_Elm,
    [TH_CALL_BIRCH] = TH13_ResearchCall_Birch,
};

// Pacing is transient. Persistent pending/delivered receipts remain in flags.
static EWRAM_DATA u8 sCallStepsRemaining = 0;
static EWRAM_DATA struct Coords16 sCallLastPos = {0};
static EWRAM_DATA u8 sCallMapGroup = 0, sCallMapNum = 0;
void TH_ResearchResetCallPacing(void) { sCallStepsRemaining = 0; }

bool32 TH_ResearchTryStartPendingCall(void)
{
    u16 call;
    // The hook runs after priority field input. Never replace an interaction,
    // menu, warp, field move, moving avatar or the script of another scene.
    if (gMain.callback2 != CB2_Overworld || gMain.inBattle
        || gSaveBlock1Ptr->location.mapGroup != MAP_GROUP(MAP_TH_PALLET)
        || !FlagGet(FLAG_TH13_GEAR) || ArePlayerFieldControlsLocked()
        || ScriptContext_IsEnabled() || gPaletteFade.active
        || gPlayerAvatar.preventStep || gPlayerAvatar.transitionFlags
        || gPlayerAvatar.tileTransitionState != T_NOT_MOVING
        || gPlayerAvatar.runningState != NOT_MOVING
        || gMain.newKeys || gMain.heldKeys)
        return FALSE;
    if (sCallStepsRemaining)
    {
        if (sCallMapGroup != gSaveBlock1Ptr->location.mapGroup || sCallMapNum != gSaveBlock1Ptr->location.mapNum)
            sCallStepsRemaining = 0;
        else if (sCallLastPos.x != gSaveBlock1Ptr->pos.x || sCallLastPos.y != gSaveBlock1Ptr->pos.y)
        {
            u32 distance = abs(sCallLastPos.x - gSaveBlock1Ptr->pos.x) + abs(sCallLastPos.y - gSaveBlock1Ptr->pos.y);
            sCallLastPos = gSaveBlock1Ptr->pos;
            sCallStepsRemaining = distance >= sCallStepsRemaining ? 0 : sCallStepsRemaining - distance;
        }
        if (sCallStepsRemaining) return FALSE;
    }
    call = TH_ResearchNextPendingCall();
    if (call >= ARRAY_COUNT(sResearchCallScripts))
        return FALSE;
    ScriptContext_SetupScript(sResearchCallScripts[call]);
    return TRUE;
}

void TH_ScriptResearchQueueCall(void)
{
    gSpecialVar_Result = TH_ResearchQueueCall(gSpecialVar_0x8004);
}

void TH_ScriptResearchCompleteCall(void)
{
    bool32 wasPending = TH_ResearchNextPendingCall() == gSpecialVar_0x8004;
    TH_ResearchCompleteCall(gSpecialVar_0x8004);
    if (wasPending)
    {
        sCallStepsRemaining = 8;
        sCallLastPos = gSaveBlock1Ptr->pos;
        sCallMapGroup = gSaveBlock1Ptr->location.mapGroup;
        sCallMapNum = gSaveBlock1Ptr->location.mapNum;
    }
}

const struct THResearchEntry *TH_ResearchGetEntry(u16 entryId)
{
    return entryId < ARRAY_COUNT(sResearchEntries) ? &sResearchEntries[entryId] : NULL;
}

const struct THResearchPhoto *TH_ResearchGetPhoto(u16 photoId)
{
    return photoId < ARRAY_COUNT(sResearchPhotos) ? &sResearchPhotos[photoId] : NULL;
}

bool32 TH_ResearchHasEntry(u16 entryId)
{
    const struct THResearchEntry *entry = TH_ResearchGetEntry(entryId);
    return entry != NULL && FlagGet(entry->flag);
}

bool32 TH_ResearchObserve(u16 entryId)
{
    const struct THResearchEntry *entry = TH_ResearchGetEntry(entryId);
    if (entry == NULL)
        return FALSE;
    // Live interactions can introduce a contact even when an older reliable
    // receipt already imported the observation. They never invent photographs.
    if (FlagGet(FLAG_TH13_GEAR))
    {
        if (entryId == TH_RESEARCH_HOOTHOOT || entryId == TH_RESEARCH_FOREST_PAIR
            || entryId == TH_RESEARCH_CAVE || entryId == TH_RESEARCH_ROUTE9)
            TH_ResearchQueueCall(TH_CALL_ELM);
        if (entryId == TH_RESEARCH_MT_MOON || entryId == TH_RESEARCH_CAVE
            || entryId == TH_RESEARCH_ROCK_TUNNEL)
            TH_ResearchQueueCall(TH_CALL_BIRCH);
    }
    if (FlagGet(entry->flag)) return FALSE;
    FlagSet(entry->flag);
    return TRUE;
}

bool32 TH_ResearchHasPhoto(u16 photoId)
{
    return photoId < ARRAY_COUNT(sPhotoFlags) && FlagGet(sPhotoFlags[photoId]);
}

bool32 TH_ResearchTakePhoto(u16 photoId)
{
    const struct THResearchPhoto *photo = TH_ResearchGetPhoto(photoId);
    if (photo == NULL || !FlagGet(FLAG_TH13_GEAR)
        || !TH_ResearchHasEntry(photo->entryId) || TH_ResearchHasPhoto(photoId))
        return FALSE;
    FlagSet(sPhotoFlags[photoId]);
    return TRUE;
}

bool32 TH_ResearchCallDelivered(u16 callId)
{
    return callId < ARRAY_COUNT(sCallFlags) && FlagGet(sCallFlags[callId][1]);
}

bool32 TH_ResearchQueueCall(u16 callId)
{
    if (callId >= ARRAY_COUNT(sCallFlags) || TH_ResearchCallDelivered(callId)
        || FlagGet(sCallFlags[callId][0]))
        return FALSE;
    FlagSet(sCallFlags[callId][0]);
    return TRUE;
}

u16 TH_ResearchNextPendingCall(void)
{
    // ROM order is priority; a later event never displaces an earlier call.
    static const u8 priority[] = {TH_CALL_ACTIVATION, TH_CALL_ELM, TH_CALL_BIRCH, TH_CALL_ROUTE10, TH_CALL_LAVENDER};
    for (u32 i = 0; i < ARRAY_COUNT(priority); i++)
        if (FlagGet(sCallFlags[priority[i]][0]) && !TH_ResearchCallDelivered(priority[i]))
            return priority[i];
    return TH_RESEARCH_CALL_NONE;
}

void TH_ResearchCompleteCall(u16 callId)
{
    if (callId >= ARRAY_COUNT(sCallFlags) || !FlagGet(sCallFlags[callId][0]))
        return;
    FlagSet(sCallFlags[callId][1]);
    FlagClear(sCallFlags[callId][0]);
}

u16 TH_ResearchEntryCount(void)
{
    u16 count = 0;
    for (u32 i = 0; i < ARRAY_COUNT(sResearchEntries); i++)
        count += TH_ResearchHasEntry(i);
    return count;
}

const u8 *TH_ResearchProfessorNote(u16 entryId)
{
    const struct THResearchEntry *entry = TH_ResearchGetEntry(entryId);
    if (entry == NULL)
        return NULL;
    if (TH_ResearchCallDelivered(TH_CALL_LAVENDER))
        return entry->notes[2];
    if (TH_ResearchCallDelivered(TH_CALL_ROUTE10))
        return entry->notes[1];
    return entry->notes[0];
}
#endif
