#include "global.h"
#include "test/test.h"
#include "title_screen.h"
#include "main_menu.h"
#include "main.h"
#include "palette.h"
#include "gpu_regs.h"
#include "sprite.h"
#include "task.h"

#if THREE_HORIZONS
// Catches an unloaded/disabled backdrop, the old palette animation corrupting
// illustration colors, and losing Start/A navigation during title replacement.
TEST("Three Horizons illustrated title stays stable and opens the menu")
{
    u16 key;
    PARAMETRIZE { key = START_BUTTON; }
    PARAMETRIZE { key = A_BUTTON; }
    MainCallback old1 = gMain.callback1, old2 = gMain.callback2;
    u16 palette[256];
    gMain.callback1 = NULL;
    gMain.newKeys = gMain.heldKeys = 0;
    SetMainCallback2(CB2_InitTitleScreen);
    // Follow the actual initialization and fade into the interactive title.
    for (u32 frame = 0; frame < 90; frame++)
    {
        gMain.callback2();
        VBlankIntrWait();
    }
    EXPECT(!gPaletteFade.active);
    EXPECT(GetGpuReg(REG_OFFSET_DISPCNT) & DISPCNT_BG0_ON);
    EXPECT(GetGpuReg(REG_OFFSET_BG0CNT) & BGCNT_256COLOR);
    EXPECT_EQ(((const u16 *)BG_SCREEN_ADDR(31))[19 * 32 + 29], 637);
    memcpy(palette, gPlttBufferUnfaded, sizeof(palette));
    for (u32 frame = 0; frame < 120; frame++)
    {
        gMain.callback2();
        VBlankIntrWait();
    }
    EXPECT_EQ(memcmp(palette, gPlttBufferUnfaded, sizeof(palette)), 0);
    gMain.newKeys = key;
    gMain.callback2();
    gMain.newKeys = 0;
    // A fade also waits for the VBlank palette transfer; clearing only the
    // active flag leaves that transfer pending and cannot finish the callback.
    for (u32 frame = 0; frame < 90 && gMain.callback2 != CB2_InitMainMenu; frame++)
    {
        VBlankIntrWait();
        gMain.callback2();
    }
    EXPECT(gMain.callback2 == CB2_InitMainMenu);
    SetVBlankCallback(NULL);
    ResetTasks();
    ResetSpriteData();
    FreeAllSpritePalettes();
    gMain.callback1 = old1;
    SetMainCallback2(old2);
}
#endif
