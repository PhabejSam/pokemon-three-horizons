#include "global.h"
#include "test/test.h"
#include "event_data.h"
#include "three_horizons_research.h"
#include "constants/three_horizons.h"
#include "constants/species.h"
#include "constants/maps.h"
#include "constants/event_objects.h"
#include "overworld.h"
#include "palette.h"
#include "script.h"
#include "sprite.h"
#include "sound.h"
#include "text.h"
#include "window.h"
#include "malloc.h"
#include "field_player_avatar.h"
#include "event_object_movement.h"

#if THREE_HORIZONS
// Numeric boundary values intentionally make the absent append observable.
TEST("Three Horizons PT14 research: append only mother record and bounds")
{
    EXPECT_EQ(TH_RESEARCH_ENTRY_COUNT, 12);
    EXPECT_EQ(TH_RESEARCH_PHOTO_COUNT, 11);
    EXPECT_EQ(TH_RESEARCH_CALL_COUNT, 5);
    const struct THResearchEntry *entry = TH_ResearchGetEntry(11);
    const struct THResearchPhoto *photo = TH_ResearchGetPhoto(10);
    EXPECT(entry != NULL); EXPECT(photo != NULL);
    if (!entry || !photo) return;
    EXPECT_EQ(entry->flag, FLAG_TH14_OBS_MOTHER);
    EXPECT_EQ(entry->photoId, 10); EXPECT_EQ(photo->entryId, 11);
    EXPECT_EQ(photo->subjectCount, 1);
    EXPECT_EQ(photo->subjects[0].species, SPECIES_MAROWAK);
    EXPECT_EQ(photo->subjects[0].x, 128); EXPECT_EQ(photo->subjects[0].y, 112);
    EXPECT(TH_ResearchGetEntry(12) == NULL); EXPECT(TH_ResearchGetEntry(0xFFFF) == NULL);
    EXPECT(TH_ResearchGetPhoto(11) == NULL); EXPECT(TH_ResearchGetPhoto(0xFFFF) == NULL);
}

TEST("Three Horizons PT14 research: mother photo requires gear and observation")
{
    InitEventData();
    EXPECT(!TH_ResearchTakePhoto(10));
    FlagSet(FLAG_TH13_GEAR); EXPECT(!TH_ResearchTakePhoto(10));
    EXPECT(TH_ResearchObserve(11));
    FlagClear(FLAG_TH13_GEAR); EXPECT(!TH_ResearchTakePhoto(10));
    FlagSet(FLAG_TH13_GEAR); EXPECT(TH_ResearchTakePhoto(10));
    EXPECT(FlagGet(FLAG_TH14_OBS_MOTHER)); EXPECT(FlagGet(FLAG_TH14_PHOTO_MOTHER));
    EXPECT(!TH_ResearchTakePhoto(10));
    EXPECT(!FlagGet(FLAG_TH14_MOTHER_WON)); EXPECT(!FlagGet(FLAG_TH14_MOTHER_RESOLVED));
    EXPECT_EQ(TH_ResearchNextPendingCall(), TH_RESEARCH_CALL_NONE);
}

TEST("Three Horizons PT14 research: photo loss survives but resolution not implied")
{
    u8 flags[NUM_FLAG_BYTES];
    InitEventData(); FlagSet(FLAG_TH13_GEAR);
    EXPECT(TH_ResearchObserve(11)); EXPECT(TH_ResearchTakePhoto(10));
    memcpy(flags, gSaveBlock1Ptr->flags, sizeof(flags));
    InitEventData(); memcpy(gSaveBlock1Ptr->flags, flags, sizeof(flags));
    EXPECT(TH_ResearchHasEntry(11)); EXPECT(TH_ResearchHasPhoto(10));
    EXPECT(!FlagGet(FLAG_TH14_MOTHER_WON)); EXPECT(!FlagGet(FLAG_TH14_MOTHER_RESOLVED));
    EXPECT_EQ(TH_ResearchEntryCount(), 1);
}
TEST("Three Horizons PT14 research: mother note does not fake a call")
{
    u8 flags[NUM_FLAG_BYTES];
    InitEventData(); FlagSet(FLAG_TH13_GEAR);
    TH_ResearchObserve(TH_RESEARCH_MOTHERS_WATCH);
    const struct THResearchEntry *entry = TH_ResearchGetEntry(TH_RESEARCH_MOTHERS_WATCH);
    TH_ResearchQueueCall(TH_CALL_BIRCH);
    FlagSet(FLAG_TH13_CALL_LAVENDER_DELIVERED);
    EXPECT(TH_ResearchProfessorNote(TH_RESEARCH_MOTHERS_WATCH) == entry->notes[0]);
    FlagSet(FLAG_TH14_MOTHER_RESOLVED);
    EXPECT(TH_ResearchProfessorNote(TH_RESEARCH_MOTHERS_WATCH) == entry->notes[0]);
    FlagSet(FLAG_TH14_FUJI_RESCUED);
    memcpy(flags, gSaveBlock1Ptr->flags, sizeof(flags));
    for (u32 i = 0; i < 20; i++)
        EXPECT(TH_ResearchProfessorNote(TH_RESEARCH_MOTHERS_WATCH) == entry->notes[2]);
    EXPECT_EQ(memcmp(flags, gSaveBlock1Ptr->flags, sizeof(flags)), 0);
    EXPECT_EQ(TH_ResearchNextPendingCall(), TH_CALL_BIRCH);
    EXPECT(!TH_ResearchCallDelivered(TH_CALL_BIRCH));
    EXPECT(TH_ResearchProfessorNote(TH_RESEARCH_HOOTHOOT) == TH_ResearchGetEntry(TH_RESEARCH_HOOTHOOT)->notes[2]);
    SetDefaultFontsPointer();
    EXPECT_LE(GetStringWidth(FONT_SMALL, entry->observation, 0), 216);
    EXPECT_LE(GetStringWidth(FONT_SMALL, entry->notes[2], 0), 216);
}

TEST("Three Horizons PT14 research: aftermath pending calls wait eight steps and retain resets")
{
    MainCallback old = gMain.callback2;
    u8 flags[NUM_FLAG_BYTES];
    InitEventData(); FlagSet(FLAG_TH13_GEAR);
    ScriptContext_Init(); UnlockPlayerFieldControls();
    gMain.callback2 = CB2_Overworld; gMain.inBattle = FALSE;
    gMain.newKeys = gMain.heldKeys = 0; gPaletteFade.active = FALSE;
    gPlayerAvatar.preventStep = gPlayerAvatar.transitionFlags = 0;
    gPlayerAvatar.tileTransitionState = T_NOT_MOVING; gPlayerAvatar.runningState = NOT_MOVING;
    gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(MAP_TH13_POKEMON_TOWER_6F);
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(MAP_TH13_POKEMON_TOWER_6F);
    gSaveBlock1Ptr->pos.x = 11; gSaveBlock1Ptr->pos.y = 14;
    TH_ResearchQueueCall(TH_CALL_BIRCH); TH_ResearchQueueCall(TH_CALL_ELM);
    memcpy(flags, gSaveBlock1Ptr->flags, sizeof(flags));
    TH14_DelayAftermathCalls();
    for (u32 i = 0; i < 60; i++) EXPECT(!TH_ResearchTryStartPendingCall());
    for (u32 i = 0; i < 7; i++) { gSaveBlock1Ptr->pos.x++; EXPECT(!TH_ResearchTryStartPendingCall()); }
    gSaveBlock1Ptr->pos.x++;
    EXPECT(TH_ResearchTryStartPendingCall());
    EXPECT_EQ(TH_ResearchNextPendingCall(), TH_CALL_ELM);
    EXPECT_EQ(memcmp(flags, gSaveBlock1Ptr->flags, sizeof(flags)), 0);
    for (u32 reset = 0; reset < 3; reset++)
    {
        ScriptContext_Init(); UnlockPlayerFieldControls(); TH_ResearchDelayCalls(8);
        if (reset == 0) gSaveBlock1Ptr->location.mapNum = MAP_NUM(MAP_TH13_POKEMON_TOWER_1F);
        if (reset == 1) TH_ResearchResetCallPacing(); // existing cold-Continue reset
        if (reset == 2) TH_ResearchDelayCalls(0);
        EXPECT(TH_ResearchTryStartPendingCall());
        EXPECT_EQ(memcmp(flags, gSaveBlock1Ptr->flags, sizeof(flags)), 0);
    }
    ScriptContext_Init(); UnlockPlayerFieldControls(); TH_ResearchResetCallPacing(); gMain.callback2 = old;
}

static void Return(void) {}
static void Frames(u16 keys, u32 count)
{
    for (u32 i = 0; i < count; i++)
    {
        gMain.newKeys = i == 0 ? keys : 0; gMain.heldKeys = keys;
        gMain.callback2(); MapMusicMain(); VBlankIntrWait();
    }
    gMain.newKeys = gMain.heldKeys = 0;
}
static void Press(u16 keys) { Frames(keys, 2); Frames(0, 2); }
static void MotherList(void)
{
    InitEventData(); FlagSet(FLAG_TH13_GEAR); TH_ResearchObserve(TH_RESEARCH_MOTHERS_WATCH);
    TH_ResearchTakePhoto(TH_PHOTO_MOTHERS_WATCH);
    TH_OpenResearchGear(Return); Frames(0, 40); Press(DPAD_DOWN); Press(A_BUTTON);
}
static EWRAM_DATA struct ObjectEvent sFieldObjects[OBJECT_EVENTS_COUNT];
static EWRAM_DATA u8 sSeen[NUM_DEX_FLAG_BYTES], sCaught[NUM_DEX_FLAG_BYTES];

TEST("Three Horizons PT14 research: seven current outfits read without flags dex or field mutation")
{
    MainCallback old1 = gMain.callback1, old2 = gMain.callback2;
    IntrCallback oldVBlank = gMain.vblankCallback;
    u8 flags[NUM_FLAG_BYTES];
    gMain.callback1 = NULL; SetDefaultFontsPointer();
    memcpy(sFieldObjects, gObjectEvents, sizeof(sFieldObjects));
    memcpy(sSeen, gSaveBlock1Ptr->dexSeen, sizeof(sSeen)); memcpy(sCaught, gSaveBlock1Ptr->dexCaught, sizeof(sCaught));
    for (u32 outfit = 0; outfit < TH_OUTFIT_COUNT; outfit++)
    {
        MotherList(); VarSet(VAR_TH_OUTFIT, outfit);
        memcpy(flags, gSaveBlock1Ptr->flags, sizeof(flags));
        const struct ObjectEventGraphicsInfo *info = GetObjectEventGraphicsInfo(GetPlayerAvatarGraphicsIdByStateId(PLAYER_AVATAR_STATE_NORMAL));
        for (u32 repeat = 0; repeat < 3; repeat++)
        {
            Press(A_BUTTON); EXPECT_EQ(TH_TestResearchMenuSubjects(), 2);
            EXPECT_EQ(TH_TestResearchMenuRecord(), TH_PHOTO_MOTHERS_WATCH);
            u32 observer = MAX_SPRITES;
            for (u32 i = 0; i < MAX_SPRITES; i++)
                if (gSprites[i].inUse && gSprites[i].template->paletteTag == 0x101) observer = i;
            EXPECT_LT(observer, MAX_SPRITES);
            EXPECT_EQ(gSprites[observer].x, 128); EXPECT_EQ(gSprites[observer].y, 80);
            EXPECT_EQ((u32)gSprites[observer].oam.shape, (u32)info->oam->shape);
            EXPECT_EQ((u32)gSprites[observer].oam.size, (u32)info->oam->size);
            u32 reference = LoadObjectEventPaletteCopy(info->paletteTag, 0x300);
            EXPECT_NE(reference, 0xFF);
            EXPECT_EQ(memcmp(&gPlttBufferUnfaded[256 + reference * 16], &gPlttBufferUnfaded[256 + gSprites[observer].oam.paletteNum * 16], 32), 0);
            FreeSpritePaletteByTag(0x300);
            // Compare the actual uploaded DOWN-frame pixels, including relative-frame outfits.
            u16 tile = GetSpriteTileStartByTag(0x101);
            EXPECT_EQ(memcmp((void *)(OBJ_VRAM0 + tile * TILE_SIZE_4BPP), info->images[0].data, info->images[0].size), 0);
            Press(A_BUTTON); EXPECT_EQ(TH_TestResearchMenuSubjects(), 0);
            Press(A_BUTTON); EXPECT_EQ(TH_TestResearchMenuSubjects(), 0);
            Press(B_BUTTON);
        }
        Press(B_BUTTON); Press(B_BUTTON); Frames(0, 40);
        EXPECT(gMain.callback2 == Return);
        EXPECT_EQ(memcmp(flags, gSaveBlock1Ptr->flags, sizeof(flags)), 0);
        EXPECT_EQ(memcmp(sSeen, gSaveBlock1Ptr->dexSeen, sizeof(sSeen)), 0);
        EXPECT_EQ(memcmp(sCaught, gSaveBlock1Ptr->dexCaught, sizeof(sCaught)), 0);
        EXPECT_EQ(memcmp(sFieldObjects, gObjectEvents, sizeof(sFieldObjects)), 0);
        for (u32 tag = 0x100; tag < 0x104; tag++)
        { EXPECT_EQ(GetSpriteTileStartByTag(tag), 0xFFFF); EXPECT_EQ(IndexOfSpritePaletteTag(tag), 0xFF); }
    }
    SetVBlankCallback(oldVBlank); gMain.callback1 = old1; SetMainCallback2(old2);
}

static const u8 sExhaustTiles[32256] = {0};
TEST("Three Horizons PT14 research: partial actor resource failures clean menu tags and recover")
{
    MainCallback old1 = gMain.callback1, old2 = gMain.callback2;
    IntrCallback oldVBlank = gMain.vblankCallback;
    gMain.callback1 = NULL; SetDefaultFontsPointer();
    for (u32 mode = 0; mode < 4; mode++)
    {
        void *blocks[128]; u32 count = 0;
        MotherList();
        if (mode == 0) for (u32 i = 0; i < 15; i++) EXPECT_NE(AllocSpritePalette(0x400 + i), 0xFF);
        if (mode == 1) for (u32 i = 0; i < MAX_SPRITES - 1; i++) EXPECT_NE(CreateSpriteUnchecked(&gDummySpriteTemplate, 0, 0, 0), MAX_SPRITES);
        if (mode == 2)
        {
            const struct SpriteSheet sheet = {sExhaustTiles, sizeof(sExhaustTiles), 0x400};
            EXPECT(CanAllocSpriteTiles(sizeof(sExhaustTiles) / TILE_SIZE_4BPP));
            EXPECT_NE(LoadSpriteSheet(&sheet), 0xFFFF);
        }
        if (mode == 3)
        {
            while (count < ARRAY_COUNT(blocks) && (blocks[count] = AllocUnchecked(1024)) != NULL) count++;
            EXPECT_LT(count, ARRAY_COUNT(blocks));
        }
        Press(A_BUTTON); EXPECT(gMain.callback2 == Return);
        for (u32 tag = 0x100; tag < 0x104; tag++)
        { EXPECT_EQ(GetSpriteTileStartByTag(tag), 0xFFFF); EXPECT_EQ(IndexOfSpritePaletteTag(tag), 0xFF); }
        for (u32 i = 0; i < WINDOWS_MAX; i++) EXPECT(gWindows[i].tileData == NULL);
        while (count) Free(blocks[--count]);
        ResetSpriteData(); FreeAllSpritePalettes();
        MotherList(); Press(A_BUTTON); EXPECT_EQ(TH_TestResearchMenuSubjects(), 2);
        Press(B_BUTTON); Press(B_BUTTON); Press(B_BUTTON); Frames(0, 40);
        EXPECT(gMain.callback2 == Return);
    }
    SetVBlankCallback(oldVBlank); gMain.callback1 = old1; SetMainCallback2(old2);
}
#endif
