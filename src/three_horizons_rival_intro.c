#include "global.h"
#include "main.h"
#include "bg.h"
#include "window.h"
#include "menu.h"
#include "text.h"
#include "text_window.h"
#include "palette.h"
#include "gpu_regs.h"
#include "sprite.h"
#include "task.h"
#include "trainer_pokemon_sprites.h"
#include "constants/trainers.h"
#include "constants/rgb.h"
#if THREE_HORIZONS
static EWRAM_DATA MainCallback sNext=NULL;
static EWRAM_DATA u16 sPortrait=0xFFFF;
static void RivalIntroVBlank(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}
static void RivalIntroMain(void)
{
    if (JOY_NEW(A_BUTTON | B_BUTTON))
    {
        if (sPortrait < MAX_SPRITES) FreeAndDestroyTrainerPicSprite(sPortrait);
        FreeAllWindowBuffers();
        SetVBlankCallback(NULL);
        SetMainCallback2(sNext);
        return;
    }
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
    DoScheduledBgTilemapCopiesToVram();
}
void TH_ShowRivalIntroduction(MainCallback next)
{
    static const struct BgTemplate bg={.bg=0,.charBaseIndex=0,.mapBaseIndex=31,.priority=1};
    static const struct WindowTemplate windows[]={
        {.bg=0,.tilemapLeft=1,.tilemapTop=12,.width=28,.height=7,.paletteNum=15,.baseBlock=1},
        DUMMY_WIN_TEMPLATE,
    };
    static const u16 backdrop=RGB(24,28,30);
    sNext=next;
    SetVBlankCallback(NULL);
    SetGpuReg(REG_OFFSET_DISPCNT,0);
    ResetVramOamAndBgCntRegs();
    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0,&bg,1);
    ResetAllBgsCoordinates();
    ResetPaletteFade();
    ResetSpriteData();
    FreeAllSpritePalettes();
    InitWindows(windows);
    DeactivateAllTextPrinters();
    LoadPalette(GetTextWindowPalette(0),BG_PLTT_ID(15),PLTT_SIZE_4BPP);
    LoadPalette(&backdrop,0,sizeof(backdrop));
    FillWindowPixelBuffer(0,PIXEL_FILL(TEXT_COLOR_WHITE));
    AddTextPrinterParameterized(0,FONT_NORMAL,COMPOUND_STRING("This is your rival from PALLET.\nHe dreams of traveling, too.\nNow, what was his name again?"),3,0,TEXT_SKIP_DRAW,NULL);
    PutWindowTilemap(0);
    CopyWindowToVram(0,COPYWIN_FULL);
    sPortrait=CreateTrainerPicSprite(TRAINER_PIC_RIVAL_EARLY_FRLG,TRUE,120,54,0,0xFFFF);
    if (sPortrait<MAX_SPRITES) gSprites[sPortrait].oam.priority=0;
    ShowBg(0);
    SetGpuReg(REG_OFFSET_DISPCNT,DISPCNT_BG0_ON | DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);
    SetVBlankCallback(RivalIntroVBlank);
    SetMainCallback2(RivalIntroMain);
}
#endif
