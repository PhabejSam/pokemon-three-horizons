#include "global.h"
#include "test/test.h"
#include "three_horizons.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "main.h"
#include "malloc.h"
#include "palette.h"
#include "task.h"
#include "trainer_pokemon_sprites.h"
#include "window.h"
#include "bg.h"

#if THREE_HORIZONS
static void ReturnFromEditor(void) {}

static void PressEditorKey(u16 key)
{
    gMain.newKeys = key;
    gMain.newAndRepeatedKeys = key;
    RunTasks();
    gMain.newKeys = 0;
    gMain.newAndRepeatedKeys = 0;
}

TEST("Three Horizons capture editor confirms or cancels through real input and callbacks")
{
    bool32 confirm;
    PARAMETRIZE(confirm = FALSE);
    PARAMETRIZE(confirm = TRUE);
    struct Pokemon mon, before;
    MainCallback saved = gMain.callback2;
    CreateMonWithIVs(&mon, SPECIES_ARTICUNO, 35, 987654, OTID_STRUCT_PLAYER_ID, 12);
    before = mon;
    EXPECT(TH_OpenCaughtMonEditor(&mon, ReturnFromEditor));
    gMain.callback2(); // Execute the actual window/sprite initialization.
    EXPECT(gMain.callback2 != ReturnFromEditor);
    gPaletteFade.active = FALSE;
    // Cursor begins at Confirm. Move to Shiny, change the preview, then close.
    for (u32 i = 0; i < 6; i++)
        PressEditorKey(DPAD_UP);
    PressEditorKey(DPAD_RIGHT);
    EXPECT_EQ(memcmp(&mon, &before, sizeof(mon)), 0);
    if (confirm)
    {
        for (u32 i = 0; i < 6; i++)
            PressEditorKey(DPAD_DOWN);
        PressEditorKey(A_BUTTON);
    }
    else
        PressEditorKey(B_BUTTON);
    EXPECT(gMain.callback2 == ReturnFromEditor);
    if (confirm)
    {
        EXPECT_EQ(GetMonData(&mon, MON_DATA_IS_SHINY), !GetMonData(&before, MON_DATA_IS_SHINY));
        EXPECT_EQ(GetMonData(&mon, MON_DATA_PERSONALITY), GetMonData(&before, MON_DATA_PERSONALITY));
        EXPECT_EQ(GetMonData(&mon, MON_DATA_LEVEL), 35);
    }
    else
        EXPECT_EQ(memcmp(&mon, &before, sizeof(mon)), 0);
    SetMainCallback2(saved);
}

TEST("Three Horizons capture editor keeps the original when window memory is exhausted")
{
    struct Pokemon mon, before;
    void *blocks[32];
    u32 count = 0;
    MainCallback saved = gMain.callback2;
    CreateMonWithIVs(&mon, SPECIES_MEW, 20, 5555, OTID_STRUCT_PLAYER_ID, 10);
    before = mon;
    // Consume every free heap block, leaving runner-owned allocations intact.
    const struct MemBlock *head = HeapHead(), *block = head;
    do
    {
        if (!block->allocated && block->size && count < ARRAY_COUNT(blocks))
            blocks[count++] = AllocUnchecked(block->size);
        block = block->next;
    } while (block != head);
    EXPECT(TH_OpenCaughtMonEditor(&mon, ReturnFromEditor));
    gMain.callback2();
    EXPECT(gMain.callback2 == ReturnFromEditor);
    EXPECT_EQ(memcmp(&mon, &before, sizeof(mon)), 0);
    for (u32 i = 0; i < count; i++)
        Free(blocks[i]);
    SetMainCallback2(saved);
}

TEST("Three Horizons capture preview handles insufficient sprite memory")
{
    void *blocks[32];
    u32 count = 0;
    const struct MemBlock *head = HeapHead(), *block = head;
    do
    {
        if (!block->allocated && block->size && count < ARRAY_COUNT(blocks))
            blocks[count++] = AllocUnchecked(block->size);
        block = block->next;
    } while (block != head);
    EXPECT_EQ(CreateMonPicSpriteUnchecked(SPECIES_MEW, FALSE, 0, TRUE, 0, 0, 0, SPECIES_MEW), 0xFFFF);
    for (u32 i = 0; i < count; i++)
        Free(blocks[i]);
}

TEST("Three Horizons configured catches survive native party PC and last-slot delivery")
{
    u32 destination;
    PARAMETRIZE(destination = 0); // Party vacancy.
    PARAMETRIZE(destination = 1); // Full party, empty PC.
    PARAMETRIZE(destination = 2); // Full party, last PC slot.
    PARAMETRIZE(destination = 3); // Both full: no overwrite.
    struct Pokemon mon, filler;
    struct THPartnerOptions options;
    struct PokemonStorage *savedStorage = gPokemonStoragePtr;
    gPokemonStoragePtr = AllocZeroed(sizeof(*gPokemonStoragePtr));
    CreateMonWithIVs(&mon, SPECIES_MEW, 25, 12345, OTID_STRUCT_PLAYER_ID, 12);
    CreateMonWithIVs(&filler, SPECIES_ZUBAT, 6, 789, OTID_STRUCT_PLAYER_ID, 5);
    TH_ReadMonOptions(&mon, &options);
    options.shiny = TRUE;
    options.nature = NATURE_TIMID;
    options.ivs[STAT_SPEED] = 31;
    EXPECT(TH_ApplyCaughtMonOptions(&mon, &options));
    for (u32 i = 0; i < PARTY_SIZE; i++)
        gParties[B_TRAINER_PLAYER][i] = filler;
    if (destination == 0)
        ZeroMonData(&gParties[B_TRAINER_PLAYER][5]);
    if (destination >= 2)
        for (u32 box = 0; box < TOTAL_BOXES_COUNT; box++)
            for (u32 slot = 0; slot < IN_BOX_COUNT; slot++)
                gPokemonStoragePtr->boxes[box][slot] = filler.box;
    if (destination == 2)
        ZeroBoxMonAt(TOTAL_BOXES_COUNT - 1, IN_BOX_COUNT - 1);
    u32 result = GiveCapturedMonToPlayer(&mon);
    EXPECT_EQ(result, destination == 0 ? MON_GIVEN_TO_PARTY : destination == 3 ? MON_CANT_GIVE : MON_GIVEN_TO_PC);
    struct BoxPokemon *received = destination == 0 ? &gParties[B_TRAINER_PLAYER][5].box
        : destination == 2 ? GetBoxedMonPtr(TOTAL_BOXES_COUNT - 1, IN_BOX_COUNT - 1) : GetBoxedMonPtr(0, 0);
    if (destination != 3)
    {
        EXPECT_EQ(GetBoxMonData(received, MON_DATA_SPECIES), SPECIES_MEW);
        EXPECT_EQ(GetBoxMonData(received, MON_DATA_IS_SHINY), TRUE);
        EXPECT_EQ(GetBoxMonData(received, MON_DATA_SPEED_IV), 31);
        EXPECT_EQ(GetBoxMonData(received, MON_DATA_HIDDEN_NATURE), NATURE_TIMID);
        EXPECT_EQ(GetBoxMonData(received, MON_DATA_PERSONALITY), 12345);
    }
    u32 caughtCount = 0;
    for (u32 i = 0; i < PARTY_SIZE; i++)
        caughtCount += GetMonData(&gParties[B_TRAINER_PLAYER][i], MON_DATA_SPECIES) == SPECIES_MEW;
    for (u32 box = 0; box < TOTAL_BOXES_COUNT; box++)
        for (u32 slot = 0; slot < IN_BOX_COUNT; slot++)
            caughtCount += GetBoxMonDataAt(box, slot, MON_DATA_SPECIES) == SPECIES_MEW;
    EXPECT_EQ(caughtCount, destination == 3 ? 0 : 1);
    Free(gPokemonStoragePtr);
    gPokemonStoragePtr = savedStorage;
}
#endif
