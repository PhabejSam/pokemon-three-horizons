#include "global.h"
#include "test/test.h"
#include "palette.h"
#include "field_weather.h"
#include "gpu_regs.h"
#include "constants/field_weather.h"
#include "constants/rgb.h"

#if THREE_HORIZONS
TEST("Three Horizons RC2 hardware photo flash preserves tinted palettes repeatedly")
{
    u16 originalBase[PLTT_BUFFER_SIZE], originalFaded[PLTT_BUFFER_SIZE];
    u16 tint;
    PARAMETRIZE { tint = 0; } // daylight
    PARAMETRIZE { tint = 3; } // shaded forest
    PARAMETRIZE { tint = 8; } // night tint
    memcpy(originalBase, gPlttBufferUnfaded, sizeof(originalBase));
    memcpy(originalFaded, gPlttBufferFaded, sizeof(originalFaded));
    ResetPaletteFade();
    for (u32 i = 0; i < PLTT_BUFFER_SIZE; i++)
    {
        gPlttBufferUnfaded[i] = RGB(12 + i % 12, 14 + i % 16, 10 + i % 14);
        gPlttBufferFaded[i] = RGB(12 + i % 12 - tint, 14 + i % 16 - tint, 10 + i % 14 - tint);
    }
    u16 base[PLTT_BUFFER_SIZE], faded[PLTT_BUFFER_SIZE];
    memcpy(base, gPlttBufferUnfaded, sizeof(base));
    memcpy(faded, gPlttBufferFaded, sizeof(faded));
    for (u32 photo = 0; photo < 3; photo++)
    {
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
        EXPECT_EQ(memcmp(base, gPlttBufferUnfaded, sizeof(base)), 0);
        EXPECT_EQ(memcmp(faded, gPlttBufferFaded, sizeof(faded)), 0);
    }
    memcpy(gPlttBufferUnfaded, originalBase, sizeof(originalBase));
    memcpy(gPlttBufferFaded, originalFaded, sizeof(originalFaded));
    ResetPaletteFade();
}
#endif
