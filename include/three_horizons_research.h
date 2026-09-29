#ifndef GUARD_THREE_HORIZONS_RESEARCH_H
#define GUARD_THREE_HORIZONS_RESEARCH_H
#include "main.h"

#include "constants/three_horizons_research.h"
struct THResearchSubject { u16 species; s16 x, y; u8 direction; };
struct THResearchPhoto {
    u16 entryId;
    u8 backdrop, subjectCount;
    struct THResearchSubject subjects[TH_RESEARCH_MAX_SUBJECTS];
};
struct THResearchEntry {
    const u8 *region, *location, *species, *origin, *observation;
    const u8 *notes[3];
    u16 flag, photoId;
};
#if THREE_HORIZONS
bool32 TH_ResearchObserve(u16 entryId);
bool32 TH_ResearchTakePhoto(u16 photoId);
bool32 TH_ResearchQueueCall(u16 callId);
bool32 TH_ResearchTryStartPendingCall(void);
void TH_ScriptResearchCompleteCall(void);
void TH_ScriptResearchQueueCall(void);
bool32 TH_ResearchHasEntry(u16 entryId);
bool32 TH_ResearchHasPhoto(u16 photoId);
u16 TH_ResearchNextPendingCall(void);
void TH_ResearchCompleteCall(u16 callId);
bool32 TH_ResearchCallDelivered(u16 callId);
u16 TH_ResearchEntryCount(void);
const struct THResearchEntry *TH_ResearchGetEntry(u16 entryId);
const struct THResearchPhoto *TH_ResearchGetPhoto(u16 photoId);
const u8 *TH_ResearchProfessorNote(u16 entryId);
void TH_OpenResearchGear(MainCallback returnCallback);
bool32 TH_ResearchGearUnlocked(void);
bool32 TH_ResearchConfirmPhoto(u16 photoId, bool32 accepted);
const u8 *TH_ResearchContactReport(u16 contact, u16 callId);
void TH_ScriptResearchPhotoStatus(void);
void TH_ScriptTakeResearchPhoto(void);
void TH_ScriptResearchObserve(void);
#if TESTING
u16 TH_TestResearchMenuLevel(void);
u16 TH_TestResearchMenuRecord(void);
u16 TH_TestResearchMenuSubjects(void);
#endif
#endif
#endif
