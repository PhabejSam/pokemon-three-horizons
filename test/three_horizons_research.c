#include "global.h"
#include "test/test.h"
#include "event_data.h"
#include "item.h"
#include "three_horizons.h"
#include "three_horizons_research.h"
#include "constants/three_horizons.h"
#if THREE_HORIZONS
TEST("Three Horizons playtest13 research records persist once")
{
    u8 saved[NUM_FLAG_BYTES];
    InitEventData();
    for (u32 id = 0; id < TH_RESEARCH_ENTRY_COUNT; id++)
    {
        EXPECT(!TH_ResearchHasEntry(id));
        EXPECT(TH_ResearchObserve(id));
        EXPECT(!TH_ResearchObserve(id));
        EXPECT_EQ(TH_ResearchEntryCount(), id + 1);
    }
    // No Gear means no photo; observing a scene does not imply photographing it.
    EXPECT(!TH_ResearchTakePhoto(TH_PHOTO_HOOTHOOT));
    FlagSet(FLAG_TH13_GEAR);
    for (u32 id = 0; id < TH_RESEARCH_PHOTO_COUNT; id++)
    {
        EXPECT(!TH_ResearchHasPhoto(id));
        EXPECT(TH_ResearchTakePhoto(id));
        EXPECT(!TH_ResearchTakePhoto(id));
    }
    memcpy(saved, gSaveBlock1Ptr->flags, sizeof(saved));
    InitEventData();
    memcpy(gSaveBlock1Ptr->flags, saved, sizeof(saved));
    EXPECT_EQ(TH_ResearchEntryCount(), TH_RESEARCH_ENTRY_COUNT);
    for (u32 id = 0; id < TH_RESEARCH_PHOTO_COUNT; id++) EXPECT(TH_ResearchHasPhoto(id));
    EXPECT_EQ(sizeof(struct SaveBlock1), 15568);
    EXPECT_EQ(sizeof(struct SaveBlock2), 3884);
}
TEST("Three Horizons playtest13 invalid research IDs cannot write state")
{
    u8 before[NUM_FLAG_BYTES];
    InitEventData();
    FlagSet(FLAG_TH13_GEAR);
    FlagSet(FLAG_BADGE03_GET);
    memcpy(before, gSaveBlock1Ptr->flags, sizeof(before));
    EXPECT(!TH_ResearchTakePhoto(TH_PHOTO_HOOTHOOT)); // unobserved
    for (u32 id = TH_RESEARCH_ENTRY_COUNT; id <= 0xFFFF; id++)
    {
        EXPECT(!TH_ResearchObserve(id));
        EXPECT(!TH_ResearchHasEntry(id));
        EXPECT(TH_ResearchGetEntry(id) == NULL);
    }
    const u16 bad[] = {TH_RESEARCH_PHOTO_COUNT, 255, 256, 0xFFFF};
    for (u32 i = 0; i < ARRAY_COUNT(bad); i++)
    {
        EXPECT(!TH_ResearchTakePhoto(bad[i]));
        EXPECT(!TH_ResearchHasPhoto(bad[i]));
        EXPECT(TH_ResearchGetPhoto(bad[i]) == NULL);
        EXPECT(!TH_ResearchQueueCall(bad[i]));
        TH_ResearchCompleteCall(bad[i]);
    }
    EXPECT(!TH_ResearchQueueCall(TH_RESEARCH_CALL_COUNT));
    TH_ResearchCompleteCall(TH_RESEARCH_CALL_COUNT);
    EXPECT_EQ(memcmp(before, gSaveBlock1Ptr->flags, sizeof(before)), 0);
}
TEST("Three Horizons playtest13 research calls use persistent authored priority")
{
    u8 saved[NUM_FLAG_BYTES];
    InitEventData();
    EXPECT_EQ(TH_ResearchNextPendingCall(), TH_RESEARCH_CALL_NONE);
    TH_ResearchCompleteCall(TH_CALL_ROUTE10); // not pending: cannot invent completion
    EXPECT(!TH_ResearchCallDelivered(TH_CALL_ROUTE10));
    EXPECT(TH_ResearchQueueCall(TH_CALL_LAVENDER));
    EXPECT(TH_ResearchQueueCall(TH_CALL_ROUTE10));
    EXPECT(TH_ResearchQueueCall(TH_CALL_ACTIVATION));
    EXPECT(TH_ResearchQueueCall(TH_CALL_ELM));
    EXPECT(TH_ResearchQueueCall(TH_CALL_BIRCH));
    EXPECT(!TH_ResearchQueueCall(TH_CALL_ACTIVATION));
    memcpy(saved, gSaveBlock1Ptr->flags, sizeof(saved));
    InitEventData(); memcpy(gSaveBlock1Ptr->flags, saved, sizeof(saved));
    const u16 order[] = {TH_CALL_ACTIVATION, TH_CALL_ELM, TH_CALL_BIRCH, TH_CALL_ROUTE10, TH_CALL_LAVENDER};
    for (u32 i = 0; i < ARRAY_COUNT(order); i++)
    {
        u32 id = order[i];
        EXPECT_EQ(TH_ResearchNextPendingCall(), id);
        TH_ResearchCompleteCall(id);
        EXPECT(TH_ResearchCallDelivered(id));
        EXPECT(!TH_ResearchQueueCall(id));
    }
    EXPECT_EQ(TH_ResearchNextPendingCall(), TH_RESEARCH_CALL_NONE);
}
TEST("Three Horizons RC2 live regional observations introduce contacts without photos")
{
    InitEventData(); TH_ResearchObserve(TH_RESEARCH_HOOTHOOT);
    EXPECT_EQ(TH_ResearchNextPendingCall(), TH_RESEARCH_CALL_NONE);
    FlagSet(FLAG_TH13_GEAR);
    EXPECT(!TH_ResearchObserve(TH_RESEARCH_HOOTHOOT)); // imported/repeated still live
    EXPECT_EQ(TH_ResearchNextPendingCall(), TH_CALL_ELM);
    TH_ResearchCompleteCall(TH_CALL_ELM);
    EXPECT(TH_ResearchObserve(TH_RESEARCH_MT_MOON));
    EXPECT_EQ(TH_ResearchNextPendingCall(), TH_CALL_BIRCH);
    TH_ResearchCompleteCall(TH_CALL_BIRCH);
    TH_ResearchObserve(TH_RESEARCH_CAVE);
    EXPECT_EQ(TH_ResearchNextPendingCall(), TH_RESEARCH_CALL_NONE);
    for (u32 photo = 0; photo < TH_RESEARCH_PHOTO_COUNT; photo++) EXPECT(!TH_ResearchHasPhoto(photo));
}
TEST("Three Horizons playtest13 research migration imports only witnessed observations")
{
    const u16 sightings[] = {0, 1, 2, 3, 0xFFFF};
    for (u32 i = 0; i < ARRAY_COUNT(sightings); i++)
    {
        InitEventData(); ClearBag();
        VarSet(VAR_TH_CLOCK_DISPLAY_HI, TH_STATE_VERSION_12);
        VarSet(VAR_TH_SIGHTING_SEEN, sightings[i]);
        FlagSet(FLAG_TH12_FOREST_SEEN);
        FlagSet(FLAG_TH12_SHIP_STORY);
        TH_MigrateSaveState();
        EXPECT_EQ(TH_ResearchHasEntry(TH_RESEARCH_HOOTHOOT), sightings[i] == 1);
        EXPECT(TH_ResearchHasEntry(TH_RESEARCH_FOREST_LEGACY));
        EXPECT(!TH_ResearchHasEntry(TH_RESEARCH_FOREST_TREECKO));
        EXPECT(!TH_ResearchHasEntry(TH_RESEARCH_FOREST_SHROOMISH));
        EXPECT(!TH_ResearchHasEntry(TH_RESEARCH_MT_MOON));
        EXPECT(TH_ResearchHasEntry(TH_RESEARCH_SHIP));
        EXPECT_EQ(TH_ResearchEntryCount(), 2 + (sightings[i] == 1));
        for (u32 id = 0; id < TH_RESEARCH_PHOTO_COUNT; id++) EXPECT(!TH_ResearchHasPhoto(id));
        EXPECT_EQ(TH_ResearchNextPendingCall(), TH_RESEARCH_CALL_NONE);
        TH_MigrateSaveState(); EXPECT_EQ(TH_ResearchEntryCount(), 2 + (sightings[i] == 1));
    }
}
TEST("Three Horizons playtest13 photo card binds authored tableau and metadata")
{
    InitEventData();
    for (u32 id = 0; id < TH_RESEARCH_ENTRY_COUNT; id++)
    {
        const struct THResearchEntry *entry = TH_ResearchGetEntry(id);
        EXPECT(entry != NULL);
        EXPECT(entry->region && entry->location && entry->species && entry->origin && entry->observation);
        for (u32 note = 0; note < 3; note++) EXPECT(entry->notes[note] != NULL);
        EXPECT(TH_ResearchProfessorNote(id) == entry->notes[0]);
        FlagSet(FLAG_TH13_CALL_ROUTE10_DELIVERED);
        EXPECT(TH_ResearchProfessorNote(id) == entry->notes[id == TH_RESEARCH_MOTHERS_WATCH ? 0 : 1]);
        FlagSet(FLAG_TH13_CALL_LAVENDER_DELIVERED);
        EXPECT(TH_ResearchProfessorNote(id) == entry->notes[id == TH_RESEARCH_MOTHERS_WATCH ? 0 : 2]);
        FlagClear(FLAG_TH13_CALL_ROUTE10_DELIVERED); FlagClear(FLAG_TH13_CALL_LAVENDER_DELIVERED);
    }
    for (u32 id = 0; id < TH_RESEARCH_PHOTO_COUNT; id++)
    {
        const struct THResearchPhoto *photo = TH_ResearchGetPhoto(id);
        EXPECT(photo != NULL);
        EXPECT_EQ(TH_ResearchGetEntry(photo->entryId)->photoId, id);
        EXPECT(photo->subjectCount >= 1 && photo->subjectCount <= TH_RESEARCH_MAX_SUBJECTS);
        for (u32 j = 0; j < photo->subjectCount; j++)
        {
            EXPECT(photo->subjects[j].species > SPECIES_NONE && photo->subjects[j].species < SPECIES_EGG);
            EXPECT(photo->subjects[j].x >= 24 && photo->subjects[j].x <= 216);
            EXPECT(photo->subjects[j].y >= 32 && photo->subjects[j].y <= 112);
        }
    }
    EXPECT_EQ(TH_ResearchGetPhoto(TH_PHOTO_FOREST_PAIR)->subjects[0].species, SPECIES_PINSIR);
    EXPECT_EQ(TH_ResearchGetPhoto(TH_PHOTO_FOREST_PAIR)->subjects[1].species, SPECIES_HERACROSS);
    EXPECT_EQ(TH_ResearchGetPhoto(TH_PHOTO_ROUTE9)->subjects[0].species, SPECIES_MAREEP);
    EXPECT_EQ(TH_ResearchGetPhoto(TH_PHOTO_ROUTE9)->subjects[1].species, SPECIES_NIDORAN_F);
    EXPECT_EQ(TH_ResearchGetPhoto(TH_PHOTO_ROCK_TUNNEL)->subjects[0].species, SPECIES_ARON);
    EXPECT_EQ(TH_ResearchGetPhoto(TH_PHOTO_ROCK_TUNNEL)->subjects[1].species, SPECIES_GEODUDE);
    EXPECT_EQ(TH_ResearchGetPhoto(TH_PHOTO_LAVENDER)->subjects[0].species, SPECIES_MISDREAVUS);
}
#endif
