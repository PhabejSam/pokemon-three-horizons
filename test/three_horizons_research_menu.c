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
static void HoldWithoutFreshPress(u16 keys, u32 count)
{
    for (u32 i = 0; i < count; i++)
    {
        gMain.newKeys = 0; gMain.heldKeys = keys;
        gMain.callback2(); MapMusicMain(); VBlankIntrWait();
    }
    gMain.newKeys = gMain.heldKeys = 0;
}

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
            if (module != 2 && counts[c])
            {
                EXPECT_EQ(TH_TestResearchMenuLevel(), 2);
                EXPECT_EQ(TH_TestResearchMenuRecord(), 0);
                if (module == 1) EXPECT_EQ(TH_TestResearchMenuSubjects(), 1);
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
    { TH_ResearchObserve(TH_ResearchGetPhoto(id)->entryId); TH_ResearchTakePhoto(id); }
    TH_OpenResearchGear(ResearchReturn); ResearchFrames(0, 40);
    Press(DPAD_DOWN); Press(A_BUTTON);
    for (u32 id = 0; id < TH_RESEARCH_PHOTO_COUNT; id++)
    {
        Press(A_BUTTON);
        EXPECT_EQ(TH_TestResearchMenuRecord(), id);
        EXPECT_EQ(TH_TestResearchMenuSubjects(), TH_ResearchGetPhoto(id)->subjectCount + (id == TH_PHOTO_MOTHERS_WATCH));
        HoldWithoutFreshPress(A_BUTTON, 30); // continuation has no fresh A edge
        EXPECT_EQ(TH_TestResearchMenuRecord(), id);
        EXPECT_EQ(TH_TestResearchMenuSubjects(), TH_ResearchGetPhoto(id)->subjectCount + (id == TH_PHOTO_MOTHERS_WATCH));
        Press(DPAD_RIGHT); EXPECT_EQ(TH_TestResearchMenuSubjects(), 0);
        Press(DPAD_RIGHT); EXPECT_EQ(TH_TestResearchMenuSubjects(), 0);
        Press(DPAD_RIGHT); EXPECT_EQ(TH_TestResearchMenuSubjects(), TH_ResearchGetPhoto(id)->subjectCount + (id == TH_PHOTO_MOTHERS_WATCH));
        Press(DPAD_LEFT); EXPECT_EQ(TH_TestResearchMenuSubjects(), 0);
        Press(B_BUTTON);
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
        TH_OpenResearchGear(ResearchReturn); ResearchFrames(0, 40);
        Press(DPAD_DOWN); Press(DPAD_DOWN); Press(A_BUTTON);
        for (u32 contact = 0; contact < 3; contact++)
        {
            EXPECT(TH_ResearchContactReport(contact, call) != NULL);
            EXPECT_LE(GetStringWidth(FONT_SMALL, TH_ResearchContactReport(contact, call), 0), 216);
            if (!TH_ResearchContactAvailable(contact)) continue;
            Press(A_BUTTON); EXPECT_EQ(TH_TestResearchMenuLevel(), 2);
            EXPECT_EQ(TH_TestResearchMenuRecord(), contact);
            Press(B_BUTTON); Press(DPAD_DOWN);
        }
        Press(B_BUTTON); Press(B_BUTTON); ResearchFrames(0, 40);
        EXPECT_EQ(memcmp(saved, gSaveBlock1Ptr->flags, sizeof(saved)), 0);
    }
    EXPECT(TH_ResearchContactReport(3, 0) == NULL);
    EXPECT(TH_ResearchContactReport(0, TH_RESEARCH_CALL_COUNT) == NULL);
    SetVBlankCallback(oldVBlank); gMain.callback1 = old1; SetMainCallback2(old2);
}

TEST("Three Horizons RC2 research contacts follow individual introductions")
{
    InitEventData(); FlagSet(FLAG_TH13_GEAR);
    for (u32 contact = 0; contact < 3; contact++)
    {
        EXPECT(!TH_ResearchContactAvailable(contact));
        EXPECT_EQ(TH_ResearchContactLatestReport(contact), TH_RESEARCH_CALL_NONE);
    }
    TH_ResearchQueueCall(TH_CALL_ACTIVATION); TH_ResearchCompleteCall(TH_CALL_ACTIVATION);
    EXPECT(TH_ResearchContactAvailable(0));
    EXPECT(!TH_ResearchContactAvailable(1)); EXPECT(!TH_ResearchContactAvailable(2));
    TH_ResearchQueueCall(TH_CALL_ELM); TH_ResearchCompleteCall(TH_CALL_ELM);
    EXPECT(TH_ResearchContactAvailable(1)); EXPECT(!TH_ResearchContactAvailable(2));
    EXPECT_EQ(TH_ResearchContactLatestReport(1), TH_CALL_ELM);
    TH_ResearchQueueCall(TH_CALL_BIRCH); TH_ResearchCompleteCall(TH_CALL_BIRCH);
    EXPECT(TH_ResearchContactAvailable(2));
    EXPECT_EQ(TH_ResearchContactLatestReport(2), TH_CALL_BIRCH);
    TH_ResearchQueueCall(TH_CALL_ROUTE10); TH_ResearchCompleteCall(TH_CALL_ROUTE10);
    for (u32 contact = 0; contact < 3; contact++) EXPECT_EQ(TH_ResearchContactLatestReport(contact), TH_CALL_ROUTE10);
    TH_ResearchQueueCall(TH_CALL_LAVENDER); TH_ResearchCompleteCall(TH_CALL_LAVENDER);
    for (u32 contact = 0; contact < 3; contact++) EXPECT_EQ(TH_ResearchContactLatestReport(contact), TH_CALL_LAVENDER);
    EXPECT(!TH_ResearchContactAvailable(3));
}

static u8 ResearchWindowPixel(u32 x, u32 y)
{
    u32 offset = ((y / 8) * 28 + x / 8) * 32 + (y % 8) * 4 + (x % 8) / 2;
    return (gWindows[0].tileData[offset] >> ((x & 1) * 4)) & 15;
}

TEST("Three Horizons Gear visibly moves selection between illustrated module cards")
{
    MainCallback old1 = gMain.callback1, old2 = gMain.callback2;
    IntrCallback oldVBlank = gMain.vblankCallback;
    u8 saved[NUM_FLAG_BYTES];
    gMain.callback1 = NULL; SetDefaultFontsPointer(); InitEventData();
    FlagSet(FLAG_TH13_GEAR);
    memcpy(saved, gSaveBlock1Ptr->flags, sizeof(saved));
    TH_OpenResearchGear(ResearchReturn); ResearchFrames(0, 40);
    // Sample the unprinted right-hand interior of each card. These distinguish
    // real visible selection from an invisible cursor-only state change.
    u8 selected = ResearchWindowPixel(208, 46);
    u8 idle = ResearchWindowPixel(208, 76);
    EXPECT_NE(selected, idle);
    Press(DPAD_DOWN);
    EXPECT_EQ(ResearchWindowPixel(208, 46), idle);
    EXPECT_EQ(ResearchWindowPixel(208, 76), selected);
    Press(DPAD_DOWN); Press(DPAD_DOWN);
    EXPECT_EQ(ResearchWindowPixel(208, 46), selected);
    Press(DPAD_UP);
    EXPECT_EQ(ResearchWindowPixel(208, 106), selected);
    Press(A_BUTTON); EXPECT_EQ(TH_TestResearchMenuLevel(), 1);
    Press(A_BUTTON); EXPECT_EQ(TH_TestResearchMenuLevel(), 1); // empty Calls
    Press(B_BUTTON); Press(B_BUTTON); ResearchFrames(0, 40);
    EXPECT_EQ(memcmp(saved, gSaveBlock1Ptr->flags, sizeof(saved)), 0);
    EXPECT(gMain.callback2 == ResearchReturn);
    SetVBlankCallback(oldVBlank); gMain.callback1 = old1; SetMainCallback2(old2);
}

TEST("Three Horizons RC2 research window pixels retain text and photo cutout")
{
    MainCallback old1 = gMain.callback1, old2 = gMain.callback2;
    IntrCallback oldVBlank = gMain.vblankCallback;
    gMain.callback1 = NULL; SetDefaultFontsPointer(); InitEventData();
    FlagSet(FLAG_TH13_GEAR);
    TH_ResearchObserve(TH_RESEARCH_FOREST_PAIR);
    TH_ResearchTakePhoto(TH_PHOTO_FOREST_PAIR);
    TH_OpenResearchGear(ResearchReturn); ResearchFrames(0, 40);
    u32 foreground = 0;
    for (u32 y = 0; y < 12; y++)
        for (u32 x = 4; x < 120; x++)
            foreground += ResearchWindowPixel(x, y) == 2;
    EXPECT_GT(foreground, 20); // actual glyph pixels, not menu state
    Press(DPAD_DOWN); Press(A_BUTTON); Press(A_BUTTON);
    for (u32 y = 24; y < 120; y++)
        for (u32 x = 0; x < 224; x++) EXPECT_EQ(ResearchWindowPixel(x, y), 0);
    EXPECT_EQ(TH_TestResearchMenuSubjects(), 2);
    Press(B_BUTTON); Press(B_BUTTON); Press(B_BUTTON); ResearchFrames(0, 40);
    SetVBlankCallback(oldVBlank); gMain.callback1 = old1; SetMainCallback2(old2);
}
#endif
