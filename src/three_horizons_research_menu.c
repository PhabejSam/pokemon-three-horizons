#include "global.h"
#include "three_horizons_research.h"
#include "constants/three_horizons.h"
#include "constants/rgb.h"
#include "constants/songs.h"
#include "bg.h"
#include "decompress.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "gpu_regs.h"
#include "malloc.h"
#include "menu.h"
#include "palette.h"
#include "pokemon.h"
#include "sound.h"
#include "sprite.h"
#include "string_util.h"
#include "text.h"
#include "text_window.h"
#include "window.h"

#if THREE_HORIZONS
#define RESEARCH_TAG 0x100
#define ROWS_PER_PAGE 4
#define TH_RESEARCH_PHOTO_HEIGHT 96
#define TH_RESEARCH_PHOTO_TILES (28 * TH_RESEARCH_PHOTO_HEIGHT / 8)
#define RESEARCH_FRAME_BASE 512
#include "data/three_horizons_research_photos.h"
struct ResearchMenu {
    MainCallback returnCallback;
    u16 tilemap[32 * 32];
    u16 photoTilemap[32 * 32];
    struct SpriteTemplate templates[TH_RESEARCH_MAX_SUBJECTS];
    u8 spriteIds[TH_RESEARCH_MAX_SUBJECTS];
    u16 records[TH_RESEARCH_ENTRY_COUNT];
    u8 level, module, cursor, count, page, subjects;
    bool8 closing;
};
static EWRAM_DATA struct ResearchMenu *sResearchMenu = NULL;
static void ResearchMain(void);
static void ResearchInit(void);
static bool32 ResearchDraw(void);
static const struct BgTemplate sResearchBg[] = {
    {.bg = 0, .charBaseIndex = 0, .mapBaseIndex = 31, .priority = 0},
    {.bg = 1, .charBaseIndex = 2, .mapBaseIndex = 30, .priority = 1},
};
static const struct WindowTemplate sResearchWindows[] = {
    {.bg = 0, .tilemapLeft = 1, .tilemapTop = 1, .width = 28, .height = 18, .paletteNum = 0, .baseBlock = 1},
    DUMMY_WIN_TEMPLATE,
};
static const u16 sResearchPalette[16] = {
    RGB(23, 27, 31), RGB(31, 31, 31), RGB(4, 4, 6), RGB(22, 23, 25),
    RGB(20, 26, 17), RGB(9, 17, 11), RGB(21, 19, 14), RGB(13, 12, 10),
    RGB(25, 21, 13), RGB(17, 13, 8), RGB(16, 17, 22), RGB(10, 11, 16),
    RGB(17, 20, 15), RGB(27, 29, 23), RGB(15, 20, 21), RGB(31, 31, 31),
};
enum {MODULE_LOG, MODULE_PHOTOS, MODULE_CALLS};
static const u8 *const sModules[] = {COMPOUND_STRING("RESEARCH LOG"), COMPOUND_STRING("FIELD PHOTOS"), COMPOUND_STRING("CALLS")};
static const u8 *const sContacts[] = {COMPOUND_STRING("PROF. OAK"), COMPOUND_STRING("PROF. ELM"), COMPOUND_STRING("PROF. BIRCH")};
static const u8 *const sReportTitles[] = {COMPOUND_STRING("Field Assignment"), COMPOUND_STRING("Johto Habitat Report"), COMPOUND_STRING("Hoenn Migration Notes")};
static const u8 *const sContactReports[TH_RESEARCH_CALL_COUNT][3] = {
    {
        COMPOUND_STRING("Your field work has helped us.\nKeep notes on unfamiliar visitors.\nELM and BIRCH will help us compare\nwhat is happening in each region."),
        COMPOUND_STRING("Kanto POKéMON are appearing\nin unusual places in Johto, too.\nPlease record how they interact\nwith the POKéMON already there."),
        COMPOUND_STRING("Hoenn's reports are changing.\nThis movement crosses regions.\nYour observations will help us\ncompare their new habitats."),
    }, {
        COMPOUND_STRING("Our reports point in more than\none direction. Keep observing.\nPrepare for Rock Tunnel before\nyou continue from Route 10."),
        COMPOUND_STRING("Johto's unusual Kanto sightings\ncontinue. Seasonal migration alone\ndoes not explain their pace.\nWe need more careful records."),
        COMPOUND_STRING("Hoenn's pattern is changing too.\nShips may explain some visitors,\nbut we cannot assume that they\nexplain every new report."),
    }, {
        COMPOUND_STRING("Misdreavus near the Tower leaves\nour shipping idea unresolved.\nWe do not have enough evidence\nto explain this. Stay careful."),
        COMPOUND_STRING("The Lavender report is unusual.\nWe know Misdreavus in Johto, but\nthat does not tell us why one\nis watching Pokémon Tower."),
        COMPOUND_STRING("Keep the earlier habitat notes.\nAn unanswered report does not\nerase them. We need to compare\nwhat fits and what remains unclear."),
    },
};

const u8 *TH_ResearchContactReport(u16 contact, u16 callId)
{
    if (callId == TH_CALL_ELM || callId == TH_CALL_BIRCH) callId = TH_CALL_ACTIVATION;
    return contact < 3 && callId < TH_RESEARCH_CALL_COUNT ? sContactReports[callId][contact] : NULL;
}

bool32 TH_ResearchGearUnlocked(void) { return FlagGet(FLAG_TH13_GEAR); }
bool32 TH_ResearchConfirmPhoto(u16 photoId, bool32 accepted) { return accepted && TH_ResearchTakePhoto(photoId); }

bool32 TH_ResearchContactAvailable(u16 contact)
{
    if (contact == 0) return TH_ResearchCallDelivered(TH_CALL_ACTIVATION);
    if (contact == 1) return TH_ResearchCallDelivered(TH_CALL_ELM) || TH_ResearchCallDelivered(TH_CALL_LAVENDER);
    if (contact == 2) return TH_ResearchCallDelivered(TH_CALL_BIRCH);
    return FALSE;
}

u16 TH_ResearchContactLatestReport(u16 contact)
{
    if (!TH_ResearchContactAvailable(contact)) return TH_RESEARCH_CALL_NONE;
    if (TH_ResearchCallDelivered(TH_CALL_LAVENDER)) return TH_CALL_LAVENDER;
    if (TH_ResearchCallDelivered(TH_CALL_ROUTE10)) return TH_CALL_ROUTE10;
    return contact == 1 ? TH_CALL_ELM : contact == 2 ? TH_CALL_BIRCH : TH_CALL_ACTIVATION;
}

static void ClearSubjects(void)
{
    for (u32 i = 0; i < TH_RESEARCH_MAX_SUBJECTS; i++)
    {
        if (sResearchMenu->spriteIds[i] != SPRITE_NONE)
            DestroySprite(&gSprites[sResearchMenu->spriteIds[i]]);
        sResearchMenu->spriteIds[i] = SPRITE_NONE;
        FreeSpriteTilesByTag(RESEARCH_TAG + i);
        FreeSpritePaletteByTag(RESEARCH_TAG + i);
    }
    sResearchMenu->subjects = 0;
}

static void ResearchClose(void)
{
    MainCallback callback = sResearchMenu->returnCallback;
    SetVBlankCallback(NULL);
    ClearSubjects();
    ClearScheduledBgCopiesToVram();
    DeactivateAllTextPrinters();
    FreeAllWindowBuffers();
    UnsetBgTilemapBuffer(0);
    UnsetBgTilemapBuffer(1);
    Free(sResearchMenu);
    sResearchMenu = NULL;
    SetMainCallback2(callback);
}

void TH_OpenResearchGear(MainCallback returnCallback)
{
    if (sResearchMenu != NULL)
        return;
    if (!TH_ResearchGearUnlocked() || (sResearchMenu = AllocZeroedUnchecked(sizeof(*sResearchMenu))) == NULL)
    {
        SetMainCallback2(returnCallback);
        return;
    }
    sResearchMenu->returnCallback = returnCallback;
    memset(sResearchMenu->spriteIds, SPRITE_NONE, sizeof(sResearchMenu->spriteIds));
    SetVBlankCallback(NULL);
    SetMainCallback2(ResearchInit);
}

static void ResearchVBlank(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static void ResearchInit(void)
{
    SetGpuReg(REG_OFFSET_DISPCNT, 0);
    CpuFill16(0, (void *)VRAM, TILE_SIZE_4BPP);
    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, sResearchBg, ARRAY_COUNT(sResearchBg));
    SetBgTilemapBuffer(0, sResearchMenu->tilemap);
    SetBgTilemapBuffer(1, sResearchMenu->photoTilemap);
    ChangeBgX(0, 0, BG_COORD_SET); ChangeBgY(0, 0, BG_COORD_SET);
    ChangeBgX(1, 0, BG_COORD_SET); ChangeBgY(1, 0, BG_COORD_SET);
    ResetSpriteData(); FreeAllSpritePalettes();
    ResetPaletteFade();
    ClearScheduledBgCopiesToVram();
    DeactivateAllTextPrinters();
    if (!InitWindowsUnchecked(sResearchWindows))
    {
        ResearchClose();
        return;
    }
    LoadPalette(sResearchPalette, 0, sizeof(sResearchPalette));
    LoadUserWindowBorderGfx(0, RESEARCH_FRAME_BASE, BG_PLTT_ID(15));
    ResearchDraw();
    SetGpuReg(REG_OFFSET_BLDCNT, 0);
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);
    ShowBg(0);
    BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
    SetVBlankCallback(ResearchVBlank);
    SetMainCallback2(ResearchMain);
}

static void Print(u16 x, u16 y, const u8 *text)
{
    static const u8 colors[] = {1, 2, 3};
    AddTextPrinterParameterized3(0, FONT_SMALL, x, y, colors, TEXT_SKIP_DRAW, text);
}

static u16 CurrentRecord(void)
{
    return sResearchMenu->cursor < sResearchMenu->count ? sResearchMenu->records[sResearchMenu->cursor] : 0xFFFF;
}

static void BuildRecords(void)
{
    sResearchMenu->count = 0;
    if (sResearchMenu->module == MODULE_CALLS)
    {
        for (u32 i = 0; i < ARRAY_COUNT(sContacts); i++)
            if (TH_ResearchContactAvailable(i)) sResearchMenu->records[sResearchMenu->count++] = i;
    }
    else
    {
        u32 limit = sResearchMenu->module == MODULE_LOG ? TH_RESEARCH_ENTRY_COUNT : TH_RESEARCH_PHOTO_COUNT;
        for (u32 i = 0; i < limit; i++)
            if (sResearchMenu->module == MODULE_LOG ? TH_ResearchHasEntry(i) : TH_ResearchHasPhoto(i))
                sResearchMenu->records[sResearchMenu->count++] = i;
    }
}

// Extract one native overworld pose, not a saved framebuffer or a front icon.
static bool32 DrawSubject(u32 slot, const struct THResearchSubject *subject)
{
    const struct ObjectEventGraphicsInfo *info = SpeciesToGraphicsInfo(subject->species, FALSE, FALSE);
    struct SpriteTemplate *template = &sResearchMenu->templates[slot];
    struct AnimFrameCmd pose = info->anims[GetFaceDirectionAnimNum(subject->direction)][0].frame;
    struct SpriteSheet sheet = {.size = info->size, .tag = RESEARCH_TAG + slot};
    struct SpritePalette palette = {.tag = RESEARCH_TAG + slot};
    void *buffer = NULL;
    if (info->compressed)
    {
        u32 size = GetDecompressedDataSize(info->images[0].data);
        if ((pose.imageValue + 1) * info->size > size || (buffer = AllocUnchecked(size)) == NULL)
            return FALSE;
        DecompressDataWithHeaderWram(info->images[0].data, buffer);
        sheet.data = (u8 *)buffer + pose.imageValue * info->size;
    }
    else if (info->images[0].relativeFrames)
        sheet.data = (u8 *)info->images[0].data + pose.imageValue * info->size;
    else
        sheet.data = info->images[pose.imageValue].data;
    if (!CanAllocSpriteTiles(sheet.size / TILE_SIZE_4BPP))
    {
        Free(buffer);
        return FALSE;
    }
    LoadSpriteSheet(&sheet);
    Free(buffer);
    palette.data = gSpeciesInfo[subject->species].overworldPalette;
    if (palette.data == NULL) palette.data = GetMonSpritePalFromSpecies(subject->species, FALSE, FALSE);
    if (LoadSpritePalette(&palette) == 0xFF) return FALSE;
    template->tileTag = sheet.tag;
    template->paletteTag = palette.tag;
    template->oam = info->oam;
    template->anims = gDummySpriteAnimTable;
    template->affineAnims = gDummySpriteAffineAnimTable;
    template->callback = SpriteCallbackDummy;
    u32 id = CreateSpriteUnchecked(template, subject->x, subject->y, slot);
    if (id == MAX_SPRITES) return FALSE;
    sResearchMenu->spriteIds[slot] = id;
    gSprites[id].oam.priority = 0;
    gSprites[id].animBeginning = FALSE;
    gSprites[id].animPaused = TRUE;
    SetSpriteOamFlipBits(&gSprites[id], pose.hFlip, pose.vFlip);
    sResearchMenu->subjects++;
    return TRUE;
}

static void DrawPhotoBackdrop(u16 photoId)
{
    static const u32 blankTile[8] = {0};
    const struct THResearchBackdropArt *art = &sResearchBackdropArt[photoId];
    LoadBgTiles(1, blankTile, sizeof(blankTile), 0);
    LoadBgTiles(1, art->tiles, TH_RESEARCH_PHOTO_TILES * TILE_SIZE_4BPP, 1);
    LoadPalette(art->palette, BG_PLTT_ID(1), PLTT_SIZE_4BPP);
    memset(sResearchMenu->photoTilemap, 0, sizeof(sResearchMenu->photoTilemap));
    for (u32 y = 0; y < TH_RESEARCH_PHOTO_HEIGHT / 8; y++)
        for (u32 x = 0; x < 28; x++)
            sResearchMenu->photoTilemap[(y + 4) * 32 + x + 1] = (y * 28 + x + 1) | (1 << 12);
    // Transparent window pixels reveal only the authored image beneath it.
    FillWindowPixelRect(0, PIXEL_FILL(0), 0, 24, 224, TH_RESEARCH_PHOTO_HEIGHT);
    CopyBgTilemapBufferToVram(1);
    ShowBg(1);
}

static bool32 ResearchDraw(void)
{
    ClearSubjects();
    HideBg(1);
    FillWindowPixelBuffer(0, PIXEL_FILL(1));
    if (sResearchMenu->level == 0)
    {
        Print(4, 0, COMPOUND_STRING("RESEARCH GEAR"));
        Print(4, 18, COMPOUND_STRING("Kanto field research"));
        for (u32 i = 0; i < ARRAY_COUNT(sModules); i++)
        {
            Print(18, 44 + i * 24, sModules[i]);
            if (i == sResearchMenu->module) Print(4, 44 + i * 24, COMPOUND_STRING(">"));
        }
        Print(4, 132, COMPOUND_STRING("A: Open    B: Return"));
    }
    else if (sResearchMenu->level == 1)
    {
        Print(4, 0, sModules[sResearchMenu->module]);
        if (sResearchMenu->count == 0)
            Print(4, 34, COMPOUND_STRING("Nothing recorded yet.\nKeep observing during your travels."));
        else
        {
            u8 number[8];
            ConvertIntToDecimalStringN(number, sResearchMenu->cursor + 1, STR_CONV_MODE_LEFT_ALIGN, 2);
            Print(4, 15, number); Print(22, 15, COMPOUND_STRING("of"));
            ConvertIntToDecimalStringN(number, sResearchMenu->count, STR_CONV_MODE_LEFT_ALIGN, 2); Print(40, 15, number);
            u32 first = sResearchMenu->cursor / ROWS_PER_PAGE * ROWS_PER_PAGE;
            for (u32 i = first; i < min(first + ROWS_PER_PAGE, sResearchMenu->count); i++)
            {
                u16 id = sResearchMenu->records[i];
                const struct THResearchPhoto *photo = sResearchMenu->module == MODULE_PHOTOS ? TH_ResearchGetPhoto(id) : NULL;
                const struct THResearchEntry *entry = sResearchMenu->module == MODULE_CALLS ? NULL : TH_ResearchGetEntry(photo ? photo->entryId : id);
                u32 y = 34 + (i - first) * 24;
                Print(18, y, entry ? entry->location : sContacts[id]);
                Print(18, y + 12, entry ? entry->species : sReportTitles[id]);
                if (i == sResearchMenu->cursor) Print(4, y, COMPOUND_STRING(">"));
            }
        }
        Print(4, 132, COMPOUND_STRING("Up/Down: Select   A: Read   B: Back"));
    }
    else if (sResearchMenu->module == MODULE_CALLS)
    {
        u16 report = TH_ResearchContactLatestReport(CurrentRecord());
        Print(4, 0, sContacts[CurrentRecord()]);
        Print(4, 14, sReportTitles[CurrentRecord()]);
        Print(4, 32, TH_ResearchContactReport(CurrentRecord(), report));
        Print(4, 132, COMPOUND_STRING("Latest received report    B: Back"));
    }
    else
    {
        u16 id = CurrentRecord();
        const struct THResearchPhoto *photo = sResearchMenu->module == MODULE_PHOTOS ? TH_ResearchGetPhoto(id) : NULL;
        const struct THResearchEntry *entry = TH_ResearchGetEntry(photo ? photo->entryId : id);
        if (entry == NULL) return FALSE;
        Print(4, 0, photo ? COMPOUND_STRING("FIELD PHOTO") : COMPOUND_STRING("FIELD OBSERVATION"));
        Print(4, 12, entry->location);
        if (sResearchMenu->page == (photo ? 2 : 1))
        {
            Print(4, 36, COMPOUND_STRING("PROFESSOR NOTE"));
            Print(4, 56, TH_ResearchProfessorNote(photo ? photo->entryId : id));
            Print(4, 104, COMPOUND_STRING("Region:")); Print(50, 104, entry->region);
            Print(4, 116, COMPOUND_STRING("Origin:")); Print(50, 116, entry->origin);
        }
        else if (photo && !sResearchMenu->page)
        {
            DrawPhotoBackdrop(id);
            for (u32 i = 0; i < photo->subjectCount; i++)
                if (!DrawSubject(i, &photo->subjects[i])) return FALSE;
            Print(4, 120, entry->species);
        }
        else
        {
            Print(4, 34, entry->species);
            Print(4, 54, entry->observation);
            Print(4, 88, COMPOUND_STRING("Region:")); Print(50, 88, entry->region);
            Print(4, 102, COMPOUND_STRING("Origin:")); Print(50, 102, entry->origin);
            Print(4, 118, entry->photoId != TH_RESEARCH_PHOTO_NONE && TH_ResearchHasPhoto(entry->photoId) ? COMPOUND_STRING("Photo: recorded") : COMPOUND_STRING("Photo: not recorded"));
        }
        Print(4, 132, photo ? (sResearchMenu->page == 0 ? COMPOUND_STRING("A: Details    B: Back") : sResearchMenu->page == 1 ? COMPOUND_STRING("A: Professor note    B: Back") : COMPOUND_STRING("A: Photo    B: Back")) : COMPOUND_STRING("A: Turn page    B: Back"));
    }
    DrawStdFrameWithCustomTileAndPalette(0, FALSE, RESEARCH_FRAME_BASE, 15);
    PutWindowTilemap(0); CopyWindowToVram(0, COPYWIN_FULL);
    return TRUE;
}

static void ResearchMain(void)
{
    if (!gPaletteFade.active)
    {
        if (sResearchMenu->closing) { ResearchClose(); return; }
        u16 keys = gMain.newKeys;
        bool32 redraw = FALSE;
        if (keys & B_BUTTON)
        {
            if (sResearchMenu->level)
            { sResearchMenu->level--; sResearchMenu->page = 0; redraw = TRUE; }
            else
            {
                sResearchMenu->closing = TRUE;
                BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
            }
        }
        else if (sResearchMenu->level < 2 && (keys & (DPAD_UP | DPAD_DOWN)))
        {
            u8 *cursor = sResearchMenu->level == 0 ? &sResearchMenu->module : &sResearchMenu->cursor;
            u32 count = sResearchMenu->level == 0 ? ARRAY_COUNT(sModules) : sResearchMenu->count;
            if (count)
            { *cursor = (keys & DPAD_UP) ? (*cursor ? *cursor - 1 : count - 1) : (*cursor + 1) % count; redraw = TRUE; }
        }
        else if (sResearchMenu->level == 2 && sResearchMenu->module != MODULE_CALLS && (keys & (A_BUTTON | DPAD_LEFT | DPAD_RIGHT)))
        {
            u32 pages = sResearchMenu->module == MODULE_PHOTOS ? 3 : 2;
            sResearchMenu->page = (sResearchMenu->page + (keys & DPAD_LEFT ? pages - 1 : 1)) % pages;
            redraw = TRUE;
        }
        else if (keys & A_BUTTON)
        {
            if (sResearchMenu->level == 0)
            { BuildRecords(); sResearchMenu->cursor = 0; sResearchMenu->level = 1; redraw = TRUE; }
            else if (sResearchMenu->level == 1 && sResearchMenu->count)
            { sResearchMenu->level = 2; sResearchMenu->page = 0; redraw = TRUE; }
        }
        if (redraw)
        {
            PlaySE(SE_SELECT);
            if (!ResearchDraw()) { ResearchClose(); return; }
        }
    }
    AnimateSprites(); BuildOamBuffer(); UpdatePaletteFade(); DoScheduledBgTilemapCopiesToVram();
}

void TH_ScriptResearchPhotoStatus(void)
{
    const struct THResearchPhoto *photo = TH_ResearchGetPhoto(gSpecialVar_0x8004);
    gSpecialVar_Result = photo && TH_ResearchGearUnlocked() && TH_ResearchHasEntry(photo->entryId)
        ? (TH_ResearchHasPhoto(gSpecialVar_0x8004) ? 2 : 1) : 0;
}
void TH_ScriptTakeResearchPhoto(void) { gSpecialVar_Result = TH_ResearchConfirmPhoto(gSpecialVar_0x8004, TRUE); }
void TH_ScriptResearchObserve(void) { gSpecialVar_Result = TH_ResearchObserve(gSpecialVar_0x8004); }
#if TESTING
u16 TH_TestResearchMenuLevel(void) { return sResearchMenu ? sResearchMenu->level : 0xFFFF; }
u16 TH_TestResearchMenuRecord(void) { return sResearchMenu ? CurrentRecord() : 0xFFFF; }
u16 TH_TestResearchMenuSubjects(void) { return sResearchMenu ? sResearchMenu->subjects : 0; }
#endif
#endif
