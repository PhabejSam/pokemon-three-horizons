#ifndef GUARD_THREE_HORIZONS_RESEARCH_H
#define GUARD_THREE_HORIZONS_RESEARCH_H
#include "main.h"

// Append only: IDs are part of the authored scene/UI contract.
enum THResearchEntryId {
    TH_RESEARCH_HOOTHOOT = 0,
    TH_RESEARCH_FOREST_TREECKO = 1,
    TH_RESEARCH_FOREST_SHROOMISH = 2,
    TH_RESEARCH_MT_MOON = 3,
    TH_RESEARCH_SHIP = 4,
    TH_RESEARCH_FOREST_PAIR = 5,
    TH_RESEARCH_CAVE = 6,
    TH_RESEARCH_ROUTE9 = 7,
    TH_RESEARCH_ROCK_TUNNEL = 8,
    TH_RESEARCH_LAVENDER = 9,
    TH_RESEARCH_FOREST_LEGACY = 10,
    TH_RESEARCH_ENTRY_COUNT = 11,
};
enum THResearchPhotoId {
    TH_PHOTO_HOOTHOOT = 0, TH_PHOTO_FOREST_TREECKO = 1,
    TH_PHOTO_FOREST_SHROOMISH = 2, TH_PHOTO_MT_MOON = 3,
    TH_PHOTO_SHIP = 4, TH_PHOTO_FOREST_PAIR = 5,
    TH_PHOTO_CAVE = 6, TH_PHOTO_ROUTE9 = 7,
    TH_PHOTO_ROCK_TUNNEL = 8, TH_PHOTO_LAVENDER = 9,
    TH_RESEARCH_PHOTO_COUNT = 10, TH_RESEARCH_PHOTO_NONE = 0xFFFF,
};
enum THResearchCallId {
    TH_CALL_ACTIVATION = 0, TH_CALL_ROUTE10 = 1, TH_CALL_LAVENDER = 2,
    TH_RESEARCH_CALL_COUNT = 3, TH_RESEARCH_CALL_NONE = 0xFFFF,
};
enum THResearchBackdrop { TH_BACKDROP_GRASS, TH_BACKDROP_CAVE, TH_BACKDROP_SHIP, TH_BACKDROP_TOWER };
#define TH_RESEARCH_MAX_SUBJECTS 4
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
bool32 TH_ResearchHasEntry(u16 entryId);
bool32 TH_ResearchHasPhoto(u16 photoId);
u16 TH_ResearchNextPendingCall(void);
void TH_ResearchCompleteCall(u16 callId);
bool32 TH_ResearchCallDelivered(u16 callId);
u16 TH_ResearchEntryCount(void);
const struct THResearchEntry *TH_ResearchGetEntry(u16 entryId);
const struct THResearchPhoto *TH_ResearchGetPhoto(u16 photoId);
const u8 *TH_ResearchProfessorNote(u16 entryId);
#endif
#endif
