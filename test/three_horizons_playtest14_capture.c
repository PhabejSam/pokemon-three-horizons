#include "global.h"
#include "test/test.h"
#include "battle.h"
#include "battle_main.h"
#include "battle_util.h"
#include "battle_util2.h"
#include "battle_controllers.h"
#include "battle_bg.h"
#include "battle_gfx_sfx_util.h"
#include "battle_anim.h"
#include "battle_script_commands.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "party_menu.h"
#include "constants/party_menu.h"
#include "item_use.h"
#include "event_data.h"
#include "main.h"
#include "malloc.h"
#include "palette.h"
#include "sprite.h"
#include "task.h"
#include "text.h"
#include "scanline_effect.h"
#include "sound.h"
#include "string_util.h"

#if THREE_HORIZONS
// Exercise the real givecaughtmon opcode and controller/menu callbacks. Recorded
// wild battle tests skip the preceding Dex/nickname screens; those have separate
// native UI coverage and an unmodified-owner-save emulator route.
static void InitCaptureProbe(enum Species caughtSpecies)
{
    gMain.callback1 = NULL;
    SetVBlankCallback(NULL);
    SetHBlankCallback(NULL);
    ScanlineEffect_Clear();
    ResetTasks();
    ResetSpriteData();
    ResetPaletteFade();
    memset(&gBattleScripting, 0, sizeof(gBattleScripting));
    memset(gBattleCommunication, 0, sizeof(gBattleCommunication));
    memset(gBattleMons, 0, sizeof(gBattleMons));
    gBattleTypeFlags = 0;
    gBattlersCount = 2;
    gBattleControllerExecFlags = 0;
    gAbsentBattlerFlags = 0;
    gBattleOutcome = 0;
    AllocateBattleResources();
    AllocateBattleSpritesData();
    AllocateMonSpritesGfx();
    SetDefaultFontsPointer();
    const u16 species[] = {SPECIES_GYARADOS, SPECIES_SCEPTILE, SPECIES_ANNIHILAPE,
                         SPECIES_FERALIGATR, SPECIES_CHARIZARD, SPECIES_GOLEM};
    for (u32 i = 0; i < PARTY_SIZE; i++)
        CreateMonWithIVs(&gParties[B_TRAINER_PLAYER][i], species[i], 40 + i,
                        123456 + i, OTID_STRUCT_PLAYER_ID, 12 + i);
    CalculatePlayerPartyCount();
    for (u32 i = 0; i < 2; i++)
    {
        gBattlerPositions[i] = i;
        gBattlerPartyIndexes[i] = 0;
        gBattleStruct->battlerPartyOrders[i][0] = 0x01;
        gBattleStruct->battlerPartyOrders[i][1] = 0x23;
        gBattleStruct->battlerPartyOrders[i][2] = 0x45;
    }
    CreateMonWithIVs(GetBattlerMon(1), caughtSpecies, 18, 987654, OTID_STRUCT_PLAYER_ID, 23);
    SetMonData(GetBattlerMon(1), MON_DATA_NICKNAME, COMPOUND_STRING("ABCDEFGHIJKL"));
    for (u32 i = 0; i < 2; i++)
        PokemonToBattleMon(GetBattlerMon(i), &gBattleMons[i]);
    gBattlerAttacker = 0;
    gBattlerTarget = 1;
    gBattleScripting.monCaught = TRUE;
    gSelectedMonPartyId = PARTY_SIZE;
    SetControllerToPlayer(0);
    SetControllerToOpponent(1);
    InitBattleBgsVideo();
    LoadBattleTextboxAndBackground();
    SetMainCallback2(BattleMainCB2);
    SetVBlankCallback(VBlankCB_Battle);
}

static void CaptureFrame(const u8 *command, u16 key)
{
    gMain.newKeys = gMain.newAndRepeatedKeys = gMain.heldKeys = key;
    // Match BattleMainCB1 ordering and controller gating. The selected index is
    // not consumable until the menu restores party order and returns to battle.
    if (gMain.callback2 == BattleMainCB2)
    {
        if (gBattlescriptCurrInstr == command)
            RunBattleScriptCommands();
        for (u32 i = 0; i < gBattlersCount; i++)
            gBattlerControllerFuncs[i](i);
    }
    gMain.callback2();
    MapMusicMain();
    VBlankIntrWait();
}

static void FreeCaptureProbe(void)
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

TEST("Three Horizons PT14 capture: full-party native selector preserves distinct party and PC identities")
{
    enum Species species;
    u32 choice;
    bool32 reordered = FALSE;
    bool32 fullPC = FALSE;
    PARAMETRIZE { species = SPECIES_EKANS; choice = 0; }
    PARAMETRIZE { species = SPECIES_EKANS; choice = 3; }
    PARAMETRIZE { species = SPECIES_EKANS; choice = 5; }
    PARAMETRIZE { species = SPECIES_EKANS; choice = 6; } // B in party selector.
    PARAMETRIZE { species = SPECIES_EKANS; choice = 7; } // No at initial prompt.
    PARAMETRIZE { species = SPECIES_DROWZEE; choice = 0; }
    PARAMETRIZE { species = SPECIES_RATTATA; choice = 3; }
    PARAMETRIZE { species = SPECIES_EKANS; choice = 0; reordered = TRUE; }
    PARAMETRIZE { species = SPECIES_EKANS; choice = 0; fullPC = TRUE; }
    MainCallback old1 = gMain.callback1, old2 = gMain.callback2;
    struct Pokemon oldParty[PARTY_SIZE], before[PARTY_SIZE];
    memcpy(oldParty, gParties[B_TRAINER_PLAYER], sizeof(oldParty));
    // Use native storage, as a real battle does. A duplicate 34KB storage
    // allocation would artificially exhaust the battle/menu graphics heap.
    ResetPokemonStorageSystem();
    u16 oldBox = VarGet(VAR_PC_BOX_TO_SEND_MON);
    VarSet(VAR_PC_BOX_TO_SEND_MON, 0);
    InitCaptureProbe(species);
    if (reordered)
    {
        gBattleStruct->battlerPartyOrders[0][0] = 0x30;
        gBattleStruct->battlerPartyOrders[0][1] = 0x12;
        gBattlerPartyIndexes[0] = 3;
        PokemonToBattleMon(GetBattlerMon(0), &gBattleMons[0]);
    }
    u32 destination = reordered ? 3 : choice;
    memcpy(before, gParties[B_TRAINER_PLAYER], sizeof(before));
    // Protect an occupied PC slot, making slot1 the delivery destination.
    gPokemonStoragePtr->boxes[0][0] = before[2].box;
    // This is a deliberately forced postcapture fault, not a naturally legal
    // full-PC throw (covered below). Failed delivery must not overwrite data.
    if (fullPC)
        for (u32 box = 0; box < TOTAL_BOXES_COUNT; box++)
            for (u32 slot = 0; slot < IN_BOX_COUNT; slot++)
                gPokemonStoragePtr->boxes[box][slot] = before[2].box;
    u8 command[6] = {B_SCR_OP_GIVECAUGHTMON};
    const u8 *end = command + 5;
    memcpy(command + 1, &end, sizeof(end));
    gBattlescriptCurrInstr = command;
    u32 frame;
    for (frame = 0; frame < 1200 && gBattleCommunication[MULTIUSE_STATE] != 2; frame++)
        CaptureFrame(command, frame % 20 ? 0 : A_BUTTON);
    EXPECT_LT(frame, 1200);
    CaptureFrame(command, 0);
    CaptureFrame(command, choice == 7 ? B_BUTTON : A_BUTTON);
    if (choice != 7)
    {
        for (frame = 0; frame < 1200; frame++)
        {
            CaptureFrame(command, 0);
            if (!gPaletteFade.active && FindTaskIdByFunc(Task_HandleChooseMonInput) != TASK_NONE)
                break;
        }
        EXPECT_LT(frame, 1200);
        EXPECT_EQ(gPartyMenu.action, PARTY_ACTION_SEND_MON_TO_BOX);
        // Single layout uses RIGHT to the small slots, then DOWN through them.
        if (choice > 0 && choice < PARTY_SIZE)
        {
            CaptureFrame(command, DPAD_RIGHT);
            CaptureFrame(command, 0);
            for (u32 i = 1; i < choice; i++)
            {
                CaptureFrame(command, DPAD_DOWN);
                CaptureFrame(command, 0);
            }
        }
        if (choice < PARTY_SIZE)
            EXPECT_EQ(gPartyMenu.slotId, choice);
        CaptureFrame(command, choice == 6 ? B_BUTTON : A_BUTTON);
    }
    for (frame = 0; frame < 1800 && gBattlescriptCurrInstr == command; frame++)
        CaptureFrame(command, 0);
    EXPECT_LT(frame, 1800);
    EXPECT(gMain.callback2 == BattleMainCB2);
    EXPECT(!gPaletteFade.active);
    EXPECT_EQ(gBattleControllerExecFlags, 0);
    EXPECT_EQ(gSelectedMonPartyId, PARTY_SIZE);
    struct Pokemon caught = *GetBattlerMon(1);
    for (u32 i = 0; i < PARTY_SIZE; i++)
        EXPECT_EQ(memcmp(&gParties[B_TRAINER_PLAYER][i],
                        !fullPC && i == destination ? &caught : &before[i], sizeof(caught)), 0);
    const struct BoxPokemon empty = {0};
    for (u32 box = 0; box < TOTAL_BOXES_COUNT; box++)
        for (u32 slot = 0; slot < IN_BOX_COUNT; slot++)
        {
            const struct BoxPokemon *expected = &empty;
            if (fullPC || (box == 0 && slot == 0))
                expected = &before[2].box;
            else if (box == 0 && slot == 1)
                expected = destination < PARTY_SIZE ? &before[destination].box : &caught.box;
            EXPECT_EQ(memcmp(GetBoxedMonPtr(box, slot), expected, sizeof(empty)), 0);
        }
    EXPECT_EQ(CalculatePlayerPartyCount(), PARTY_SIZE);
    EXPECT_EQ(gBattleResults.caughtMonSpecies, species);
    EXPECT_EQ(StringCompare(gBattleResults.caughtMonNick, COMPOUND_STRING("ABCDEFGHIJKL")), 0);
    FreeCaptureProbe();
    ResetPokemonStorageSystem();
    VarSet(VAR_PC_BOX_TO_SEND_MON, oldBox);
    memcpy(gParties[B_TRAINER_PLAYER], oldParty, sizeof(oldParty));
    CalculatePlayerPartyCount();
    gMain.callback1 = old1;
    SetMainCallback2(old2);
}

TEST("Three Horizons PT14 capture: full storage rejects a throw and last vacancy permits it")
{
    MainCallback old1 = gMain.callback1, old2 = gMain.callback2;
    struct Pokemon oldParty[PARTY_SIZE];
    memcpy(oldParty, gParties[B_TRAINER_PLAYER], sizeof(oldParty));
    ResetPokemonStorageSystem();
    InitCaptureProbe(SPECIES_EKANS);
    for (u32 box = 0; box < TOTAL_BOXES_COUNT; box++)
        for (u32 slot = 0; slot < IN_BOX_COUNT; slot++)
            gPokemonStoragePtr->boxes[box][slot] = gParties[B_TRAINER_PLAYER][0].box;
    EXPECT(IsPlayerPartyAndPokemonStorageFull());
    EXPECT(!CanThrowBall());
    ZeroBoxMonAt(TOTAL_BOXES_COUNT - 1, IN_BOX_COUNT - 1);
    EXPECT(!IsPlayerPartyAndPokemonStorageFull());
    EXPECT(CanThrowBall());
    FreeCaptureProbe();
    ResetPokemonStorageSystem();
    memcpy(gParties[B_TRAINER_PLAYER], oldParty, sizeof(oldParty));
    CalculatePlayerPartyCount();
    gMain.callback1 = old1;
    SetMainCallback2(old2);
}
#endif
