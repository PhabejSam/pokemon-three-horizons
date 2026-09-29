#include "global.h"
#include "event_data.h"
#include "overworld.h"
#include "palette.h"
#include "script.h"
#include "three_horizons_research.h"
#include "constants/three_horizons.h"
#include "constants/event_objects.h"
#include "constants/maps.h"

#if THREE_HORIZONS
#include "data/three_horizons_research.h"

extern const u8 TH13_ResearchCall_Activation[];
extern const u8 TH13_ResearchCall_Route10[];
extern const u8 TH13_ResearchCall_Lavender[];
static const u8 *const sResearchCallScripts[TH_RESEARCH_CALL_COUNT] = {
    [TH_CALL_ACTIVATION] = TH13_ResearchCall_Activation,
    [TH_CALL_ROUTE10] = TH13_ResearchCall_Route10,
    [TH_CALL_LAVENDER] = TH13_ResearchCall_Lavender,
};

bool32 TH_ResearchTryStartPendingCall(void)
{
    u16 call;
    // The hook runs after priority field input. Never replace an interaction,
    // menu, warp, field move, moving avatar or the script of another scene.
    if (gMain.callback2 != CB2_Overworld || gMain.inBattle
        || gSaveBlock1Ptr->location.mapGroup != MAP_GROUP(MAP_TH12_ROUTE25_SEA_COTTAGE)
        || !FlagGet(FLAG_TH13_GEAR) || ArePlayerFieldControlsLocked()
        || ScriptContext_IsEnabled() || gPaletteFade.active
        || gPlayerAvatar.preventStep || gPlayerAvatar.transitionFlags
        || gPlayerAvatar.tileTransitionState != T_NOT_MOVING
        || gPlayerAvatar.runningState != NOT_MOVING
        || gMain.newKeys || gMain.heldKeys)
        return FALSE;
    call = TH_ResearchNextPendingCall();
    if (call >= ARRAY_COUNT(sResearchCallScripts))
        return FALSE;
    ScriptContext_SetupScript(sResearchCallScripts[call]);
    return TRUE;
}

void TH_ScriptResearchCompleteCall(void)
{
    TH_ResearchCompleteCall(gSpecialVar_0x8004);
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
    if (entry == NULL || FlagGet(entry->flag))
        return FALSE;
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
    for (u32 i = 0; i < ARRAY_COUNT(sCallFlags); i++)
        if (FlagGet(sCallFlags[i][0]) && !TH_ResearchCallDelivered(i))
            return i;
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
