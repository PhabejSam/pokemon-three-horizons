#include "global.h"
#include "test/test.h"
#include "sprite.h"
#include "palette.h"
#include "trainer_pokemon_sprites.h"
#include "pokemon.h"
#include "constants/rgb.h"

#if THREE_HORIZONS
TEST("Three Horizons playtest12 preview owns a weather immune palette")
{
    ResetSpriteData();
    FreeAllSpritePalettes();
    ResetAllPicSprites();
    ResetPaletteFade();
    u16 tag = SPECIES_CHARMANDER | BLEND_IMMUNE_FLAG;
    u16 sprite = CreateMonPicSprite(SPECIES_CHARMANDER, TRUE, 0, TRUE, 192, 59, 0, tag);
    EXPECT_LT(sprite, MAX_SPRITES);
    u8 slot = IndexOfSpritePaletteTag(tag);
    EXPECT_LT(slot, 16);
    EXPECT_EQ((u32)gSprites[sprite].oam.paletteNum, slot);
    struct BlendSettings night = {.blendColor = RGB_BLACK, .coeff = 8};
    BeginTimeOfDayPaletteFade(PALETTES_ALL, 0, 0, 0, &night, &night, 128, RGB_BLACK);
    for (u32 frame = 0; frame < 90; frame++)
        UpdatePaletteFade();
    for (u32 color = 0; color < 16; color++)
        EXPECT_EQ(gPlttBufferFaded[OBJ_PLTT_ID(slot) + color], gPlttBufferUnfaded[OBJ_PLTT_ID(slot) + color]);
    FreeAndDestroyMonPicSprite(sprite);
    EXPECT_EQ(IndexOfSpritePaletteTag(tag), 0xFF);
    ResetPaletteFade();
}
#endif
