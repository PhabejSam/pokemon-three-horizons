#include "global.h"
#include "test/test.h"
#include "three_horizons_research.h"
#include "constants/three_horizons.h"
#include "event_data.h"
#include "malloc.h"
#include "main.h"
#include "sound.h"
#include "sprite.h"
#include "text.h"
#include "window.h"

#if THREE_HORIZONS
static void ResearchReturn(void) {}
static void ResearchFrames(u16 keys, u32 count)
{
    for (u32 i = 0; i < count; i++)
    {
        gMain.newKeys = i == 0 ? keys : 0;
        gMain.heldKeys = keys;
        gMain.callback2();
        MapMusicMain();
        VBlankIntrWait();
    }
    gMain.newKeys = gMain.heldKeys = 0;
}
static void Press(u16 keys) { ResearchFrames(keys, 2); ResearchFrames(0, 2); }

TEST("Three Horizons playtest13 research menu returns cleanly")
{
    MainCallback old1 = gMain.callback1, old2 = gMain.callback2;
    IntrCallback oldVBlank = gMain.vblankCallback;
    const u16 counts[] = {0, 1, TH_RESEARCH_ENTRY_COUNT};
    gMain.callback1 = NULL;
    SetDefaultFontsPointer();
    for (u32 c = 0; c < ARRAY_COUNT(counts); c++)
    {
        InitEventData();
        EXPECT(!TH_ResearchGearUnlocked());
        TH_OpenResearchGear(ResearchReturn);
        EXPECT(gMain.callback2 == ResearchReturn);
        FlagSet(FLAG_TH13_GEAR);
        EXPECT(TH_ResearchGearUnlocked());
        for (u32 id = 0; id < counts[c]; id++)
        {
            TH_ResearchObserve(id);
            TH_ResearchTakePhoto(id);
        }
        for (u32 module = 0; module < 3; module++)
        {
            TH_OpenResearchGear(ResearchReturn);
            ResearchFrames(0, 40);
            EXPECT_EQ(TH_TestResearchMenuLevel(), 0);
            for (u32 i = 0; i < module; i++) Press(DPAD_DOWN);
            Press(A_BUTTON);
            EXPECT_EQ(TH_TestResearchMenuLevel(), 1);
            Press(A_BUTTON);
            if (module != 0 && counts[c])
            {
                EXPECT_EQ(TH_TestResearchMenuLevel(), 2);
                EXPECT_EQ(TH_TestResearchMenuRecord(), 0);
                if (module == 2) EXPECT_EQ(TH_TestResearchMenuSubjects(), 1);
                Press(DPAD_RIGHT);
                Press(B_BUTTON);
            }
            Press(B_BUTTON);
            EXPECT_EQ(TH_TestResearchMenuLevel(), 0);
            ResearchFrames(B_BUTTON, 40); // held B cannot re-enter or double-free
            EXPECT(gMain.callback2 == ResearchReturn);
            for (u32 i = 0; i < MAX_SPRITES; i++) EXPECT(!gSprites[i].inUse);
            for (u32 i = 0; i < WINDOWS_MAX; i++) EXPECT(gWindows[i].tileData == NULL);
            EXPECT_EQ(TH_ResearchEntryCount(), counts[c]);
        }
    }
    SetVBlankCallback(oldVBlank);
    gMain.callback1 = old1; SetMainCallback2(old2);
}

TEST("Three Horizons playtest13 research photo cards paginate with paired subjects")
{
    MainCallback old1 = gMain.callback1, old2 = gMain.callback2;
    IntrCallback oldVBlank = gMain.vblankCallback;
    gMain.callback1 = NULL; SetDefaultFontsPointer(); InitEventData();
    FlagSet(FLAG_TH13_GEAR);
    for (u32 id = 0; id < TH_RESEARCH_PHOTO_COUNT; id++)
    { TH_ResearchObserve(id); TH_ResearchTakePhoto(id); }
    TH_OpenResearchGear(ResearchReturn); ResearchFrames(0, 40);
    Press(DPAD_DOWN); Press(DPAD_DOWN); Press(A_BUTTON);
    for (u32 id = 0; id < TH_RESEARCH_PHOTO_COUNT; id++)
    {
        Press(A_BUTTON);
        EXPECT_EQ(TH_TestResearchMenuRecord(), id);
        EXPECT_EQ(TH_TestResearchMenuSubjects(), TH_ResearchGetPhoto(id)->subjectCount);
        ResearchFrames(A_BUTTON, 30); // held input stays on the same record
        EXPECT_EQ(TH_TestResearchMenuRecord(), id);
        Press(DPAD_RIGHT); Press(DPAD_LEFT); Press(B_BUTTON);
        Press(DPAD_DOWN);
    }
    Press(B_BUTTON); Press(B_BUTTON); ResearchFrames(0, 40);
    EXPECT(gMain.callback2 == ResearchReturn);
    SetVBlankCallback(oldVBlank); gMain.callback1 = old1; SetMainCallback2(old2);
}

TEST("Three Horizons playtest13 research menu allocation failure returns controls")
{
    MainCallback old2 = gMain.callback2;
    void *blocks[128]; u32 count = 0;
    InitEventData(); FlagSet(FLAG_TH13_GEAR);
    while (count < ARRAY_COUNT(blocks) && (blocks[count] = AllocUnchecked(1024)) != NULL) count++;
    EXPECT_LT(count, ARRAY_COUNT(blocks));
    TH_OpenResearchGear(ResearchReturn);
    ResearchFrames(0, 40);
    EXPECT(gMain.callback2 == ResearchReturn);
    EXPECT_EQ(TH_ResearchEntryCount(), 0);
    while (count) Free(blocks[--count]);
    SetMainCallback2(old2);
}

TEST("Three Horizons playtest13 photo prompt cannot duplicate")
{
    InitEventData(); FlagSet(FLAG_TH13_GEAR);
    TH_ResearchObserve(TH_RESEARCH_FOREST_PAIR);
    EXPECT(!TH_ResearchConfirmPhoto(TH_PHOTO_FOREST_PAIR, FALSE));
    EXPECT(!TH_ResearchHasPhoto(TH_PHOTO_FOREST_PAIR));
    EXPECT(TH_ResearchConfirmPhoto(TH_PHOTO_FOREST_PAIR, TRUE));
    EXPECT(!TH_ResearchConfirmPhoto(TH_PHOTO_FOREST_PAIR, TRUE));
    EXPECT(!TH_ResearchConfirmPhoto(0xFFFF, TRUE));
    EXPECT(TH_ResearchHasPhoto(TH_PHOTO_FOREST_PAIR));
}

TEST("Three Horizons playtest13 research contacts replay without changing progress")
{
    MainCallback old1 = gMain.callback1, old2 = gMain.callback2;
    IntrCallback oldVBlank = gMain.vblankCallback;
    u8 saved[NUM_FLAG_BYTES];
    InitEventData(); SetDefaultFontsPointer(); gMain.callback1 = NULL;
    FlagSet(FLAG_TH13_GEAR);
    for (u32 call = 0; call < TH_RESEARCH_CALL_COUNT; call++)
    {
        TH_ResearchQueueCall(call); TH_ResearchCompleteCall(call);
        memcpy(saved, gSaveBlock1Ptr->flags, sizeof(saved));
        TH_OpenResearchGear(ResearchReturn); ResearchFrames(0, 40); Press(A_BUTTON);
        for (u32 contact = 0; contact < 3; contact++)
        {
            EXPECT(TH_ResearchContactReport(contact, call) != NULL);
            EXPECT_LE(GetStringWidth(FONT_SMALL, TH_ResearchContactReport(contact, call), 0), 216);
            Press(A_BUTTON); EXPECT_EQ(TH_TestResearchMenuLevel(), 2);
            EXPECT_EQ(TH_TestResearchMenuRecord(), contact);
            Press(B_BUTTON); Press(DPAD_DOWN);
        }
        Press(B_BUTTON); Press(B_BUTTON); ResearchFrames(0, 40);
        EXPECT_EQ(memcmp(saved, gSaveBlock1Ptr->flags, sizeof(saved)), 0);
    }
    EXPECT(TH_ResearchContactReport(3, 0) == NULL);
    EXPECT(TH_ResearchContactReport(0, 3) == NULL);
    SetVBlankCallback(oldVBlank); gMain.callback1 = old1; SetMainCallback2(old2);
}
#endif
