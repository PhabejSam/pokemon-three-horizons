#include "global.h"
#include "test/battle.h"
#include "three_horizons.h"
#include "battle.h"
#include "battle_anim.h"
#include "battle_bg.h"
#include "battle_script_commands.h"
#include "battle_util2.h"
#include "battle_gfx_sfx_util.h"
#include "pokemon.h"
#include "main.h"
#include "palette.h"
#include "sound.h"
#include "m4a.h"
#include "text.h"
#include "sprite.h"
#include "task.h"
#include "scanline_effect.h"
#include "overworld.h"
#include "constants/maps.h"
#include "constants/songs.h"

#if THREE_HORIZONS
static void BattleCallbackForPlaytest11(void) {}

static void InitPlaytest11Battle(u16 playerSpecies, u16 opponentSpecies, u8 level)
{
    gMain.callback1 = NULL;
    SetVBlankCallback(NULL);
    SetHBlankCallback(NULL);
    ScanlineEffect_Clear();
    ResetTasks();
    ResetSpriteData();
    ResetPaletteFade();
    memset(&gBattleScripting, 0, sizeof(gBattleScripting));
    gBattleTypeFlags = 0;
    gBattlersCount = 2;
    gBattlerPositions[0] = B_POSITION_PLAYER_LEFT;
    gBattlerPositions[1] = B_POSITION_OPPONENT_LEFT;
    gBattlerPartyIndexes[0] = gBattlerPartyIndexes[1] = 0;
    gBattlerAttacker = 0;
    gBattlerTarget = 1;
    gAbsentBattlerFlags = 0;
    gBattleControllerExecFlags = 0;
    gPartiesCount[B_TRAINER_PLAYER] = 1;
    CreateMonWithIVs(&gParties[B_TRAINER_PLAYER][0], playerSpecies, level, 0, OTID_STRUCT_PLAYER_ID, 12);
    CreateMonWithIVs(&gParties[B_TRAINER_OPPONENT_A][0], opponentSpecies, 5, 0, OTID_STRUCT_PLAYER_ID, 12);
    PokemonToBattleMon(&gParties[B_TRAINER_PLAYER][0], &gBattleMons[0]);
    PokemonToBattleMon(&gParties[B_TRAINER_OPPONENT_A][0], &gBattleMons[1]);
    AllocateBattleResources();
    AllocateBattleSpritesData();
    AllocateMonSpritesGfx();
    SetDefaultFontsPointer();
}

static void FreePlaytest11Battle(void)
{
    SetVBlankCallback(NULL);
    SetHBlankCallback(NULL);
    ResetTasks();
    ResetSpriteData();
    FreeAllSpritePalettes();
    CloseMainBattleScreen();
    FreeMonSpritesGfx();
    FreeBattleResources();
    FreeBattleSpritesData();
    gMain.newKeys = gMain.heldKeys = gMain.newAndRepeatedKeys = 0;
}

TEST("Three Horizons evolution returns directly to battle or victory music")
{
    u16 song, species;
    u8 level;
    bool32 cancel;
    PARAMETRIZE { song = MUS_RG_VS_WILD; species = SPECIES_METAPOD; level = 10; cancel = FALSE; }
    PARAMETRIZE { song = MUS_RG_VICTORY_WILD; species = SPECIES_METAPOD; level = 10; cancel = FALSE; }
    PARAMETRIZE { song = MUS_RG_VS_WILD; species = SPECIES_BULBASAUR; level = 16; cancel = FALSE; }
    PARAMETRIZE { song = MUS_RG_VS_WILD; species = SPECIES_METAPOD; level = 10; cancel = TRUE; }
    MainCallback old1 = gMain.callback1, old2 = gMain.callback2;
    bool32 oldDisableMusic = gDisableMusic;
    u8 oldMusicControl = gDisableMapMusicChangeOnMapLoad;
    struct WarpData oldLocation = gSaveBlock1Ptr->location;
    u16 oldSavedMusic = gSaveBlock1Ptr->savedMusic;
    u32 frames, unexpectedSongs = 0;
    InitPlaytest11Battle(species, SPECIES_RATTATA, level);
    gDisableMusic = FALSE;
    gDisableMapMusicChangeOnMapLoad = MUSIC_DISABLE_OFF;
    gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(MAP_TH_PALLET);
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(MAP_TH_PALLET);
    gSaveBlock1Ptr->savedMusic = MUS_RG_PALLET;
    ResetMapMusic();
    PlayBGM(song);
    struct SongHeader *expected = gMPlayInfo_BGM.songHeader;
    gLeveledUpInBattle = 1;
    gMain.callback1 = BattleCallbackForPlaytest11;
    EXPECT(TH_TryBattleEvolution(0));
    gPaletteFade.active = FALSE;
    EXPECT(TH_TryBattleEvolution(0));
    for (frames = 0; frames < 4000 && gMain.callback2 != BattleMainCB2; frames++)
    {
        gMain.newKeys = cancel ? B_BUTTON : A_BUTTON;
        gMain.heldKeys = gMain.newKeys;
        if (gMain.callback1)
            gMain.callback1();
        gMain.callback2();
        MapMusicMain();
        struct SongHeader *actual = gMPlayInfo_BGM.songHeader;
        if (actual != expected && actual != gSongTable[MUS_EVOLUTION].header
            && actual != gSongTable[MUS_EVOLVED].header && actual != gSongTable[MUS_LEVEL_UP].header)
            unexpectedSongs++;
        VBlankIntrWait();
    }
    EXPECT_LT(frames, 4000);
    EXPECT_EQ(unexpectedSongs, 0);
    EXPECT(gMPlayInfo_BGM.songHeader == expected);
    gPaletteFade.active = FALSE;
    if (gMain.callback1)
        gMain.callback1();
    EXPECT(!TH_TryBattleEvolution(0));
    FreePlaytest11Battle();
    gDisableMusic = oldDisableMusic;
    gDisableMapMusicChangeOnMapLoad = oldMusicControl;
    gSaveBlock1Ptr->location = oldLocation;
    gSaveBlock1Ptr->savedMusic = oldSavedMusic;
    gMain.callback1 = old1;
    SetMainCallback2(old2);
}

TEST("Three Horizons new catch restores the battle backdrop before the nickname choice")
{
    u16 species;
    PARAMETRIZE { species = SPECIES_CATERPIE; }
    PARAMETRIZE { species = SPECIES_WEEDLE; }
    PARAMETRIZE { species = SPECIES_PIKACHU; }
    static const u8 command[] = {B_SCR_OP_DISPLAYDEXINFO, B_SCR_OP_END};
    MainCallback old1 = gMain.callback1, old2 = gMain.callback2;
    u32 frames;
    InitPlaytest11Battle(SPECIES_WOBBUFFET, species, 12);
    gBattleScripting.monCaught = TRUE;
    // CB2 runs graphics/tasks only. Battle scripts/controllers live in CB1,
    // which stays suspended while this test drives the Dex command itself.
    SetMainCallback2(BattleMainCB2);
    InitBattleBgsVideo();
    LoadBattleTextboxAndBackground();
    SetVBlankCallback(VBlankCB_Battle);
    memset(gBattleCommunication, 0, sizeof(gBattleCommunication));
    gBattlescriptCurrInstr = command;
    for (frames = 0; frames < 1200 && gBattlescriptCurrInstr == command; frames++)
    {
        gMain.newKeys = frames % 20 == 0 ? A_BUTTON : 0;
        gMain.heldKeys = gMain.newKeys;
        gBattleScriptingCommandsTable[B_SCR_OP_DISPLAYDEXINFO]();
        gMain.callback2();
        VBlankIntrWait();
    }
    EXPECT_LT(frames, 1200);
    EXPECT_EQ(gBattle_BG3_X, 0);
    EXPECT(gBattleAnimBgTileBuffer != NULL);
    EXPECT(gMain.callback2 == BattleMainCB2);
    EXPECT(!gPaletteFade.active);
    FreePlaytest11Battle();
    gMain.callback1 = old1;
    SetMainCallback2(old2);
}

SINGLE_BATTLE_TEST("Three Horizons Poison Point after Quick Attack damages on the same turn")
{
    GIVEN {
        PLAYER(SPECIES_RATTATA) { MaxHP(80); HP(80); }
        OPPONENT(SPECIES_NIDORAN_M) { Ability(ABILITY_POISON_POINT); }
    } WHEN {
        TURN { MOVE(player, MOVE_QUICK_ATTACK, WITH_RNG(RNG_POISON_POINT, TRUE)); MOVE(opponent, MOVE_SPLASH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_QUICK_ATTACK, player);
        ABILITY_POPUP(opponent, ABILITY_POISON_POINT);
        STATUS_ICON(player, poison: TRUE);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SPLASH, opponent);
        HP_BAR(player, damage: 10);
    } THEN {
        EXPECT_EQ(player->hp, 70);
    }
}

TEST("Three Horizons Power Bracer grants eight Attack EVs and stops at 252")
{
    struct Pokemon mon;
    u16 item = ITEM_POWER_BRACER;
    CreateMonWithIVs(&mon, SPECIES_RATTATA, 5, 0, OTID_STRUCT_PLAYER_ID, 12);
    SetMonData(&mon, MON_DATA_HELD_ITEM, &item);
    MonGainEVs(&mon, SPECIES_RATTATA);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_ATK_EV), 8);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_SPEED_EV), 1);
    for (u32 i = 1; i < 32; i++)
        MonGainEVs(&mon, SPECIES_RATTATA);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_ATK_EV), 252);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_SPEED_EV), 32);
}
#endif
