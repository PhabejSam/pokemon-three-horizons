#include "global.h"
#include "three_horizons.h"
#include "pokemon.h"
#include "trainer_pokemon_sprites.h"
#include "window.h"
#include "menu.h"
#include "text.h"
#include "string_util.h"
#include "task.h"
#include "main.h"
#include "script.h"
#include "event_data.h"
#include "bg.h"
#include "sound.h"
#include "constants/songs.h"
#include "palette.h"
#include "gpu_regs.h"
#include "menu_helpers.h"
#include "text_window.h"
#include "scanline_effect.h"
#include "battle.h"
#include "constants/rgb.h"

#if THREE_HORIZONS
// Temporary editor state only: no changes to saved party or progress until grant.
static EWRAM_DATA struct THPartnerOptions sOptions = {0};
static EWRAM_DATA struct THPartnerOptions sDefaults = {0};
static EWRAM_DATA u16 sSpecies = 0;
static EWRAM_DATA u16 sSprite = 0;
static EWRAM_DATA u8 sWindow = 0;
static EWRAM_DATA u8 sPage = 0;
static EWRAM_DATA u8 sCursor = 0;
static EWRAM_DATA bool8 sConfirmed = FALSE;
static EWRAM_DATA struct Pokemon *sCaughtMon = NULL;
static EWRAM_DATA void (*sReturnCallback)(void) = NULL;
static EWRAM_DATA u32 sPreviewPersonality = 0;
static EWRAM_DATA u8 sLevel = 5;
static void CB2_InitCaughtEditor(void);

static const u8 *const sStatNames[] = {
    COMPOUND_STRING("HP"), COMPOUND_STRING("Attack"), COMPOUND_STRING("Defense"),
    COMPOUND_STRING("Sp. Atk"), COMPOUND_STRING("Sp. Def"), COMPOUND_STRING("Speed"),
};
static const u8 sStatOrder[] = {0, 1, 2, 4, 5, 3};
static const u8 *const sMainLabels[] = {
    COMPOUND_STRING("Shiny: "), COMPOUND_STRING("Nature: "),
    COMPOUND_STRING("IVs..."), COMPOUND_STRING("EVs..."),
    COMPOUND_STRING("Restore defaults"), COMPOUND_STRING("Choose partner"), COMPOUND_STRING("Cancel"),
};

static u32 TotalEVs(void)
{
    u32 i, total = 0;
    for (i = 0; i < 6; i++)
        total += sOptions.evs[i];
    return total;
}

static void PrintAt(u8 x, u8 y, const u8 *text)
{
    AddTextPrinterParameterized(sWindow, FONT_SMALL, text, x, y, TEXT_SKIP_DRAW, NULL);
}

static void RefreshPicture(void)
{
    if (sSprite != 0xFFFF)
        FreeAndDestroyMonPicSprite(sSprite);
    sSprite = CreateMonPicSprite(sSpecies, sOptions.shiny, sPreviewPersonality, TRUE, 192, 59, 0, sSpecies);
    if (sSprite < MAX_SPRITES)
    {
        gSprites[sSprite].oam.priority = 0;
        gSprites[sSprite].callback = SpriteCallbackDummy;
    }
}

static void DrawEditor(void)
{
    u32 i;
    u8 line[64];
    FillWindowPixelBuffer(sWindow, PIXEL_FILL(TEXT_COLOR_WHITE));
    StringCopy(line, GetSpeciesName(sSpecies));
    u8 number[4];
    StringAppend(line, COMPOUND_STRING("  Lv."));
    ConvertIntToDecimalStringN(number, sLevel, STR_CONV_MODE_LEFT_ALIGN, 3);
    StringAppend(line, number);
    PrintAt(4, 0, line);
    for (i = 0; i < 7; i++)
    {
        if (sCursor == i)
            PrintAt(0, 18 + i * 14, COMPOUND_STRING(">"));
        if (sPage == 0)
        {
            StringCopy(line, sCaughtMon && i == 5 ? COMPOUND_STRING("Confirm changes")
                : sCaughtMon && i == 6 ? COMPOUND_STRING("Keep original") : sMainLabels[i]);
            if (i == 0)
                StringAppend(line, sOptions.shiny ? COMPOUND_STRING("Yes") : COMPOUND_STRING("No"));
            if (i == 1)
                StringAppend(line, gNaturesInfo[sOptions.nature].name);
            PrintAt(10, 18 + i * 14, line);
        }
        else if (i < 6)
        {
            PrintAt(10, 18 + i * 14, sStatNames[i]);
            ConvertIntToDecimalStringN(line, sPage == 1 ? sOptions.ivs[sStatOrder[i]] : sOptions.evs[sStatOrder[i]], STR_CONV_MODE_RIGHT_ALIGN, 3);
            PrintAt(90, 18 + i * 14, line);
        }
        else
            PrintAt(10, 18 + i * 14, COMPOUND_STRING("Back"));
    }
    PrintAt(154, 90, sPage == 1 ? COMPOUND_STRING("IVs: 0-31") : sPage == 2 ? COMPOUND_STRING("EVs: 0-252") : sCaughtMon ? COMPOUND_STRING("Your catch") : COMPOUND_STRING("Your partner"));
    if (sPage == 2)
    {
        u8 *end = ConvertIntToDecimalStringN(line, TotalEVs(), STR_CONV_MODE_LEFT_ALIGN, 3);
        StringCopy(end, COMPOUND_STRING(" / 510"));
        PrintAt(154, 106, line);
    }
    PrintAt(4, 122, sPage ? COMPOUND_STRING("LEFT/RIGHT: 1   L/R: 10   B: back") : COMPOUND_STRING("LEFT/RIGHT: change   A: select   B: cancel"));
    PutWindowTilemap(sWindow);
    CopyWindowToVram(sWindow, COPYWIN_FULL);
}

static void CloseEditor(u8 taskId, bool32 confirmed)
{
    if (sCaughtMon && confirmed)
        TH_ApplyCaughtMonOptions(sCaughtMon, &sOptions);
    if (!sCaughtMon)
    {
        sConfirmed = confirmed;
        gSpecialVar_Result = confirmed;
    }
    if (sSprite != 0xFFFF)
        FreeAndDestroyMonPicSprite(sSprite);
    sSprite = 0xFFFF;
    if (sWindow != WINDOW_NONE)
    {
        ClearStdWindowAndFrameToTransparent(sWindow, FALSE);
        RemoveWindow(sWindow);
        if (!sCaughtMon)
            CopyWindowToVram(0, COPYWIN_GFX);
    }
    sWindow = WINDOW_NONE;
    DestroyTask(taskId);
    if (sCaughtMon)
    {
        void (*callback)(void) = sReturnCallback;
        sCaughtMon = NULL;
        sReturnCallback = NULL;
        SetVBlankCallback(NULL);
        FreeAllWindowBuffers();
        SetMainCallback2(callback);
    }
    else
    {
        ScheduleBgCopyTilemapToVram(0);
        ScriptContext_Enable();
    }
}

static void Task_PartnerEditor(u8 taskId)
{
    if (sCaughtMon && gPaletteFade.active)
        return;
    s32 delta = 0;
    bool32 changed = FALSE;
    if (sWindow == WINDOW_NONE)
    {
        CloseEditor(taskId, FALSE);
        return;
    }
    if (JOY_NEW(B_BUTTON))
    {
        if (sPage == 0)
        {
            CloseEditor(taskId, FALSE);
            return;
        }
        sCursor = sPage == 1 ? 2 : 3;
        sPage = 0;
        changed = TRUE;
    }
    else if (JOY_REPEAT(DPAD_UP))
    {
        sCursor = (sCursor + 6) % 7;
        changed = TRUE;
    }
    else if (JOY_REPEAT(DPAD_DOWN))
    {
        sCursor = (sCursor + 1) % 7;
        changed = TRUE;
    }
    else if (JOY_NEW(A_BUTTON))
    {
        changed = TRUE;
        if (sPage != 0)
        {
            if (sCursor == 6)
            {
                sCursor = sPage == 1 ? 2 : 3;
                sPage = 0;
            }
        }
        else if (sCursor <= 1)
            delta = 1;
        else if (sCursor <= 3)
        {
            sPage = sCursor - 1;
            sCursor = 0;
        }
        else if (sCursor == 4)
        {
            sOptions = sDefaults;
            RefreshPicture();
        }
        else
        {
            CloseEditor(taskId, sCursor == 5);
            return;
        }
    }
    else if (JOY_REPEAT(DPAD_LEFT | L_BUTTON))
        delta = JOY_REPEAT(L_BUTTON) ? -10 : -1;
    else if (JOY_REPEAT(DPAD_RIGHT | R_BUTTON))
        delta = JOY_REPEAT(R_BUTTON) ? 10 : 1;
    if (delta != 0)
    {
        changed = TRUE;
        if (sPage == 0 && sCursor == 0)
        {
            sOptions.shiny ^= 1;
            RefreshPicture();
        }
        else if (sPage == 0 && sCursor == 1)
            sOptions.nature = (sOptions.nature + (delta > 0 ? 1 : NUM_NATURES - 1)) % NUM_NATURES;
        else if (sPage && sCursor < 6)
        {
            u8 stat = sStatOrder[sCursor];
            u8 *value = sPage == 1 ? &sOptions.ivs[stat] : &sOptions.evs[stat];
            s32 limit = sPage == 1 ? 31 : min(252, 510 - TotalEVs() + *value);
            *value = max(0, min(limit, *value + delta));
        }
    }
    if (changed)
    {
        PlaySE(SE_SELECT);
        DrawEditor();
    }
}

void TH_OpenPartnerEditor(void)
{
    struct Pokemon sample;
    // The calling script closes window 0 first. Reuse its tile range while the
    // editor is open: 1..504 stays below the field's frame graphics at 0x200.
    // The next dialogue redraws window 0 after this window has been removed.
    struct WindowTemplate window = CreateWindowTemplate(0, 1, 1, 28, 18, 15, 1);
    u32 i;
    sCaughtMon = NULL;
    sReturnCallback = NULL;
    sPreviewPersonality = 0;
    sLevel = 5;
    sSpecies = gSpecialVar_0x8004;
    sPage = 0;
    sCursor = 5; // Accepting defaults is one button press.
    sConfirmed = FALSE;
    sSprite = 0xFFFF;
    sWindow = WINDOW_NONE;
    CreateTask(Task_PartnerEditor, 80);
    if (TH_GetRivalStarter(sSpecies) == SPECIES_NONE)
        return;
    CreateRandomMon(&sample, sSpecies, 5);
    sDefaults.nature = GetNature(&sample);
    sDefaults.shiny = FALSE;
    for (i = 0; i < 6; i++)
    {
        sDefaults.ivs[i] = GetMonData(&sample, MON_DATA_HP_IV + i);
        sDefaults.evs[i] = 0;
    }
    sOptions = sDefaults;
    sWindow = AddWindow(&window);
    if (sWindow == WINDOW_NONE)
        return;
    SetStandardWindowBorderStyle(sWindow, FALSE);
    RefreshPicture();
    DrawEditor();
}

void TH_ScriptGiveConfiguredStarter(void)
{
    gSpecialVar_Result = sConfirmed && sSpecies == gSpecialVar_0x8004
        && TH_TryGiveConfiguredStarter(sSpecies, &sOptions);
    sConfirmed = FALSE;
}
static void CB2_CaughtEditor(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

static void VBlankCB_CaughtEditor(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static void CB2_InitCaughtEditor(void)
{
    static const struct BgTemplate bg = {.bg = 0, .charBaseIndex = 0,
        .mapBaseIndex = 31, .screenSize = 0, .paletteMode = 0, .priority = 1, .baseTile = 0};
    static const struct WindowTemplate windows[] = {
        {.bg = 0, .tilemapLeft = 1, .tilemapTop = 1, .width = 28, .height = 18, .paletteNum = 15, .baseBlock = 1},
        DUMMY_WIN_TEMPLATE,
    };
    static const u16 color = RGB_WHITE;
    SetVBlankCallback(NULL);
    ResetVramOamAndBgCntRegs();
    SetGpuReg(REG_OFFSET_DISPCNT, 0);
    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, &bg, 1);
    ResetAllBgsCoordinates();
    CloseMainBattleScreen();
    DeactivateAllTextPrinters();
    ResetPaletteFade();
    ScanlineEffect_Stop();
    ResetTasks();
    ResetSpriteData();
    FreeAllSpritePalettes();
    gReservedSpritePaletteCount = 0;
    sWindow = WINDOW_NONE;
    u8 taskId = CreateTask(Task_PartnerEditor, 80);
    if (!InitWindows(windows))
    {
        CloseEditor(taskId, FALSE);
        return;
    }
    sWindow = 0;
    LoadPalette(&color, BG_PLTT_ID(0), sizeof(color));
    LoadPalette(GetOverworldTextboxPalettePtr(), BG_PLTT_ID(15), PLTT_SIZEOF(8));
    LoadUserWindowBorderGfx(0, STD_WINDOW_BASE_TILE_NUM, BG_PLTT_ID(STD_WINDOW_PALETTE_NUM));
    SetStandardWindowBorderStyle(0, FALSE);
    RefreshPicture();
    DrawEditor();
    ShowBg(0);
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP | DISPCNT_BG0_ON);
    BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
    SetVBlankCallback(VBlankCB_CaughtEditor);
    SetMainCallback2(CB2_CaughtEditor);
}

bool32 TH_OpenCaughtMonEditor(struct Pokemon *mon, void (*returnCallback)(void))
{
    if (mon == NULL || returnCallback == NULL || !TH_IsConfigurableCapture(GetMonData(mon, MON_DATA_SPECIES)))
        return FALSE;
    sCaughtMon = mon;
    sReturnCallback = returnCallback;
    sSpecies = GetMonData(mon, MON_DATA_SPECIES);
    sLevel = GetMonData(mon, MON_DATA_LEVEL);
    sPreviewPersonality = GetMonData(mon, MON_DATA_PERSONALITY);
    TH_ReadMonOptions(mon, &sDefaults);
    sOptions = sDefaults;
    sPage = 0;
    sCursor = 5;
    sSprite = 0xFFFF;
    sWindow = WINDOW_NONE;
    SetMainCallback2(CB2_InitCaughtEditor);
    return TRUE;
}

#endif
