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

#if THREE_HORIZONS
static void NamingReturned(void) {}

TEST("Three Horizons native nickname scene preserves battle held item state")
{
    MainCallback before1 = gMain.callback1, before2 = gMain.callback2;
    u32 frame;
    AllocateBattleResources();
    SetDefaultFontsPointer();
    gBattleStruct->itemLost[B_TRAINER_OPPONENT_A][0].originalItem = ITEM_POTION;
    StringCopy(gBattleStruct->caughtMonNick, COMPOUND_STRING("RATTATA"));
    gMain.callback1 = NULL;
    DoNamingScreen(NAMING_SCREEN_CAUGHT_MON, gBattleStruct->caughtMonNick,
                   SPECIES_RATTATA, MON_MALE, 12345, NamingReturned);
    for (frame = 0; frame < 1200 && gMain.callback2 != NamingReturned; frame++)
    {
        gMain.newKeys = frame % 20 == 0 ? START_BUTTON : frame % 20 == 10 ? A_BUTTON : 0;
        gMain.heldKeys = gMain.newKeys;
        gMain.newAndRepeatedKeys = gMain.newKeys;
        gMain.callback2();
        MapMusicMain();
        VBlankIntrWait();
        EXPECT_EQ(gBattleStruct->itemLost[B_TRAINER_OPPONENT_A][0].originalItem, ITEM_POTION);
    }
    EXPECT(gMain.callback2 == NamingReturned);
    FreeBattleResources();
    gMain.callback1 = before1;
    SetMainCallback2(before2);
}
#endif
