#include "global.h"
#include "test/test.h"
#include "battle.h"
#include "battle_util2.h"
#include "pokemon.h"
#include "naming_screen.h"
#include "main.h"
#include "palette.h"
#include "text.h"
#include "sound.h"
#include "string_util.h"
#include "sprite.h"
#include "task.h"
#include "bg.h"

#if THREE_HORIZONS
static void NamingReturned(void) {}

TEST("Three Horizons native nickname scene preserves battle held item state")
{
    bool32 fullParty;
    PARAMETRIZE { fullParty=FALSE; }
    PARAMETRIZE { fullParty=TRUE; }
    MainCallback before1 = gMain.callback1, before2 = gMain.callback2;
    struct Pokemon savedParty[PARTY_SIZE];
    memcpy(savedParty,gPlayerParty,sizeof(savedParty));
    memset(gPlayerParty,0,sizeof(savedParty));
    if (fullParty)
        for (u32 i=0;i<PARTY_SIZE;i++)
            CreateMonWithIVs(&gPlayerParty[i],SPECIES_RATTATA,5,123,OTID_STRUCT_PLAYER_ID,12);
    CalculatePlayerPartyCount();
    u32 frame;
    AllocateBattleResources();
    SetDefaultFontsPointer();
    gBattleStruct->itemLost[B_TRAINER_OPPONENT_A][0].originalItem = ITEM_POTION;
    StringCopy(gBattleStruct->caughtMonNick, COMPOUND_STRING("RATTATA"));
    gMain.callback1 = NULL;
    DoNamingScreen(NAMING_SCREEN_CAUGHT_MON, gBattleStruct->caughtMonNick,
                   SPECIES_RATTATA, MON_MALE, 12345, NamingReturned);
    for (frame = 0; frame < 1200 && gMain.callback2 != NamingReturned && gMain.callback2 != BattleMainCB2; frame++)
    {
        gMain.newKeys = frame % 20 == 0 ? START_BUTTON : frame % 20 == 10 ? A_BUTTON : 0;
        gMain.heldKeys = gMain.newKeys;
        gMain.newAndRepeatedKeys = gMain.newKeys;
        gMain.callback2();
        MapMusicMain();
        VBlankIntrWait();
        EXPECT_EQ((u32)gBattleStruct->itemLost[B_TRAINER_OPPONENT_A][0].originalItem, ITEM_POTION);
    }
    // Caught-mon naming returns straight to the battle with party space;
    // full-party naming uses its supplied callback for PC delivery.
    EXPECT(gMain.callback2 == (fullParty ? NamingReturned : BattleMainCB2));
    // A completed naming scene must not leave readers of its freed state alive.
    EXPECT(gMain.vblankCallback == NULL);
    EXPECT(gMain.hblankCallback == NULL);
    for (u32 i = 0; i < NUM_TASKS; i++)
        EXPECT(!gTasks[i].isActive);
    for (u32 i = 0; i < MAX_SPRITES; i++)
        EXPECT(!gSprites[i].inUse);
    for (u32 bg = 1; bg <= 3; bg++)
        EXPECT(GetBgTilemapBuffer(bg) == NULL);
    SetVBlankCallback(NULL);
    ResetTasks();
    ResetSpriteData();
    FreeAllSpritePalettes();
    FreeBattleResources();
    memcpy(gPlayerParty,savedParty,sizeof(savedParty));
    CalculatePlayerPartyCount();
    gMain.callback1 = before1;
    SetMainCallback2(before2);
}
#endif
