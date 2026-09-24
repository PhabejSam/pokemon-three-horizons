#include "global.h"
#include "test/test.h"
#include "three_horizons.h"
#include "pokemon.h"
#include "battle.h"
#include "event_data.h"
#include "item.h"
#include "malloc.h"
#include "main.h"
#include "palette.h"
#include "battle_util2.h"
#include "battle_gfx_sfx_util.h"
#include "text.h"
#include "constants/three_horizons.h"

#if THREE_HORIZONS
static void BattleCallbackForEvolutionTest(void) {}

TEST("Three Horizons native evolution scene returns safely or cancels")
{
    bool32 cancel;
    PARAMETRIZE(cancel = FALSE);
    PARAMETRIZE(cancel = TRUE);
    MainCallback old1 = gMain.callback1, old2 = gMain.callback2;
    u32 frames;
    gBattleTypeFlags = 0;
    gBattlersCount = 2;
    gBattlerPositions[0] = 0;
    gBattlerPositions[1] = 1;
    gBattlerPartyIndexes[0] = gBattlerPartyIndexes[1] = 0;
    gPartiesCount[B_TRAINER_PLAYER] = 1;
    CreateMonWithIVs(&gParties[B_TRAINER_PLAYER][0], SPECIES_METAPOD, 10, 0, OTID_STRUCT_PLAYER_ID, 12);
    CreateMonWithIVs(&gParties[B_TRAINER_OPPONENT_A][0], SPECIES_RATTATA, 5, 0, OTID_STRUCT_PLAYER_ID, 12);
    PokemonToBattleMon(&gParties[B_TRAINER_PLAYER][0], &gBattleMons[0]);
    PokemonToBattleMon(&gParties[B_TRAINER_OPPONENT_A][0], &gBattleMons[1]);
    AllocateBattleResources();
    AllocateBattleSpritesData();
    AllocateMonSpritesGfx();
    SetDefaultFontsPointer();
    gLeveledUpInBattle = 1;
    gMain.callback1 = BattleCallbackForEvolutionTest;
    EXPECT(TH_TryBattleEvolution(0));
    gPaletteFade.active = FALSE;
    EXPECT(TH_TryBattleEvolution(0));
    EXPECT(gMain.callback1 == NULL);
    for (frames = 0; frames < 4000 && gMain.callback2 != BattleMainCB2; frames++)
    {
        gMain.newKeys = cancel ? B_BUTTON : A_BUTTON;
        gMain.heldKeys = gMain.newKeys;
        if (gMain.callback1)
            gMain.callback1();
        gMain.callback2();
        VBlankIntrWait();
    }
    EXPECT_LT(frames, 4000);
    gPaletteFade.active = FALSE;
    if (gMain.callback1)
        gMain.callback1();
    EXPECT(gMain.callback1 == BattleCallbackForEvolutionTest);
    EXPECT(!TH_TryBattleEvolution(0));
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_SPECIES), cancel ? SPECIES_METAPOD : SPECIES_BUTTERFREE);
    EXPECT_EQ(gBattleMons[0].species, cancel ? SPECIES_METAPOD : SPECIES_BUTTERFREE);
    EXPECT_EQ(gLeveledUpInBattle & 1, 0);
    CloseMainBattleScreen();
    FreeMonSpritesGfx();
    FreeBattleResources();
    FreeBattleSpritesData();
    gMain.newKeys = gMain.heldKeys = 0;
    gMain.callback1 = old1;
    SetMainCallback2(old2);
}

TEST("Three Horizons evolution preserves temporary effects and consumes evolution items")
{
    struct Pokemon before;
    u16 species = SPECIES_DRAGALGE, none = ITEM_NONE, item = ITEM_RAZOR_CLAW;
    CreateMonWithIVs(&gParties[B_TRAINER_PLAYER][0], SPECIES_SKRELP, 48, 0, OTID_STRUCT_PLAYER_ID, 12);
    SetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_HELD_ITEM, &item);
    before = gParties[B_TRAINER_PLAYER][0];
    gBattleStruct = AllocZeroed(sizeof(*gBattleStruct));
    gBattlersCount = 2;
    gBattlerPositions[0] = 0;
    gBattlerPositions[1] = 1;
    gBattlerPartyIndexes[0] = 0;
    PokemonToBattleMon(&before, &gBattleMons[0]);
    gBattleMons[0].types[0] = gBattleMons[0].types[1] = TYPE_WATER;
    gBattleMons[0].volatiles.mimickedMoves = 1;
    gBattleMons[0].moves[0] = MOVE_SPLASH;
    gBattleMons[0].pp[0] = 2;
    gBattleMons[0].ppBonuses = 3;
    gBattleStruct->itemLost[B_TRAINER_PLAYER][0].originalItem = item;
    SetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_SPECIES, &species);
    SetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_HELD_ITEM, &none);
    SetMonMoveSlot(&gParties[B_TRAINER_PLAYER][0], MOVE_DRAGON_PULSE, 0);
    CalculateMonStats(&gParties[B_TRAINER_PLAYER][0]);
    TH_SyncEvolvedBattleMon(0, &before);
    EXPECT_EQ(gBattleMons[0].species, SPECIES_DRAGALGE);
    EXPECT_EQ(gBattleMons[0].types[0], TYPE_WATER);
    EXPECT_EQ(gBattleMons[0].types[1], TYPE_WATER);
    EXPECT_EQ(gBattleMons[0].moves[0], MOVE_SPLASH);
    EXPECT_EQ(gBattleMons[0].pp[0], 2);
    EXPECT_EQ(gBattleMons[0].ppBonuses & 3, 3);
    EXPECT_EQ(gBattleMons[0].item, ITEM_NONE);
    EXPECT_EQ(gBattleStruct->itemLost[B_TRAINER_PLAYER][0].originalItem, ITEM_NONE);
    FREE_AND_SET_NULL(gBattleStruct);
}

TEST("Three Horizons midbattle evolution respects level and Everstone")
{
    struct Pokemon mon;
    bool32 canStop = TRUE;
    u16 stone = ITEM_EVERSTONE;
    CreateMonWithIVs(&mon, SPECIES_BULBASAUR, 15, 0, OTID_STRUCT_PLAYER_ID, 12);
    EXPECT_EQ(TH_GetBattleEvolution(&mon, &canStop), SPECIES_NONE);
    CreateMonWithIVs(&mon, SPECIES_BULBASAUR, 16, 0, OTID_STRUCT_PLAYER_ID, 12);
    EXPECT_EQ(TH_GetBattleEvolution(&mon, &canStop), SPECIES_IVYSAUR);
    EXPECT(canStop);
    SetMonData(&mon, MON_DATA_HELD_ITEM, &stone);
    EXPECT_EQ(TH_GetBattleEvolution(&mon, &canStop), SPECIES_NONE);
}

TEST("Three Horizons old training kit receives only the new party Exp Share")
{
    struct ItemSlot saved[PC_ITEMS_COUNT];
    u16 mask = VarGet(VAR_TH_TRAINING_KIT_MASK);
    memcpy(saved, gSaveBlock1Ptr->pcItems, sizeof(saved));
    memset(gSaveBlock1Ptr->pcItems, 0, sizeof(saved));
    VarSet(VAR_TH_TRAINING_KIT_MASK, 127);
    EXPECT_EQ(TH_TryDeliverTrainingKit(), 255);
    EXPECT(CheckPCHasItem(ITEM_EXP_SHARE, 1));
    EXPECT(!CheckPCHasItem(ITEM_MACHO_BRACE, 1));
    EXPECT_EQ(TH_TryDeliverTrainingKit(), 255);
    EXPECT(!CheckPCHasItem(ITEM_EXP_SHARE, 2));
    EXPECT_EQ(GetItemPocket(ITEM_EXP_SHARE), POCKET_KEY_ITEMS);
    EXPECT(GetItemImportance(ITEM_TM39));
    memcpy(gSaveBlock1Ptr->pcItems, saved, sizeof(saved));
    VarSet(VAR_TH_TRAINING_KIT_MASK, mask);
}
#endif
