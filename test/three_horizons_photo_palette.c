#include "global.h"
#include "test/test.h"
#include "palette.h"
#include "field_weather.h"
#include "gpu_regs.h"
#include "three_horizons_research.h"
#include "constants/field_weather.h"
#include "constants/rgb.h"

#if THREE_HORIZONS
// Full palette snapshots exceed the native test runner's small IWRAM stack.
static EWRAM_DATA u16 sOriginalBase[PLTT_BUFFER_SIZE], sOriginalFaded[PLTT_BUFFER_SIZE];
static EWRAM_DATA u16 sPhotoBase[PLTT_BUFFER_SIZE], sPhotoFaded[PLTT_BUFFER_SIZE];
TEST("Three Horizons RC2 hardware photo flash preserves tinted palettes repeatedly")
{
    u16 tint;
    PARAMETRIZE { tint = 0; } // daylight
    PARAMETRIZE { tint = 3; } // shaded forest
    PARAMETRIZE { tint = 8; } // night tint
    memcpy(sOriginalBase, gPlttBufferUnfaded, sizeof(sOriginalBase));
    memcpy(sOriginalFaded, gPlttBufferFaded, sizeof(sOriginalFaded));
    ResetPaletteFade();
    for (u32 i = 0; i < PLTT_BUFFER_SIZE; i++)
    {
        gPlttBufferUnfaded[i] = RGB(12 + i % 12, 14 + i % 16, 10 + i % 14);
        gPlttBufferFaded[i] = RGB(12 + i % 12 - tint, 14 + i % 16 - tint, 10 + i % 14 - tint);
    }
    memcpy(sPhotoBase, gPlttBufferUnfaded, sizeof(sPhotoBase));
    memcpy(sPhotoFaded, gPlttBufferFaded, sizeof(sPhotoFaded));
    for (u32 photo = 0; photo < 3; photo++)
    {
        const u8 offsets[] = {REG_OFFSET_BLDCNT, REG_OFFSET_BLDALPHA, REG_OFFSET_BLDY, REG_OFFSET_WININ, REG_OFFSET_WINOUT};
        const u16 registers[] = {BLDCNT_TGT2_ALL | BLDCNT_EFFECT_BLEND, 0x070D, 7, 0x1717, 0x1717};
        for (u32 i = 0; i < ARRAY_COUNT(offsets); i++) SetGpuReg(offsets[i], registers[i]);
        TH_ScriptBeginPhotoFlash();
        FadeScreenHardware(FADE_TO_WHITE, 0);
        EXPECT(gPaletteFade.active);
        u32 frame;
        for (frame = 0; frame < 120 && gPaletteFade.active; frame++)
        {
            UpdatePaletteFade();
            TransferPlttBuffer();
        }
        EXPECT_LT(frame, 120);
        FadeScreenHardware(FADE_FROM_WHITE, 0);
        for (frame = 0; frame < 120 && gPaletteFade.active; frame++)
        {
            UpdatePaletteFade();
            TransferPlttBuffer();
        }
        EXPECT_LT(frame, 120);
        TH_ScriptEndPhotoFlash();
        for (u32 i = 0; i < ARRAY_COUNT(offsets); i++) EXPECT_EQ(GetGpuReg(offsets[i]), registers[i]);
        EXPECT_EQ(memcmp(sPhotoBase, gPlttBufferUnfaded, sizeof(sPhotoBase)), 0);
        EXPECT_EQ(memcmp(sPhotoFaded, gPlttBufferFaded, sizeof(sPhotoFaded)), 0);
    }
    memcpy(gPlttBufferUnfaded, sOriginalBase, sizeof(sOriginalBase));
    memcpy(gPlttBufferFaded, sOriginalFaded, sizeof(sOriginalFaded));
    ResetPaletteFade();
}
#endif
