#include "global.h"
#include "test/test.h"
#include "battle.h"
#include "battle_main.h"
#include "battle_util.h"
#include "battle_util2.h"
#include "battle_scripts.h"
#include "battle_setup.h"
#include "pokemon.h"
#include "event_data.h"
#include "main.h"
#include "constants/trainers.h"
#include "battle_controllers.h"
#include "battle_bg.h"
#include "battle_gfx_sfx_util.h"
#include "battle_anim.h"
#include "palette.h"
#include "sprite.h"
#include "task.h"
#include "text.h"
#include "scanline_effect.h"
#include "pokedex.h"
#include "battle_script_commands.h"
#include "sound.h"
#include "string_util.h"

#if THREE_HORIZONS
extern bool32 Test_TH_ChooseRunAction(void);

static void InitRunProbe(u32 flags)
{
    gBattleTypeFlags = flags;
    gBattlersCount = flags & BATTLE_TYPE_DOUBLE ? 4 : 2;
    gBattleControllerExecFlags = 0;
    gAbsentBattlerFlags = 0;
    gBattleOutcome = 0;
    gCurrentTurnActionNumber = 0;
    memset(gBattleMons, 0, sizeof(gBattleMons));
    memset(gProtectStructs, 0, sizeof(gProtectStructs));
    memset(gChosenActionByBattler, 0, sizeof(gChosenActionByBattler));
    memset(gSelectionBattleScripts, 0, sizeof(gSelectionBattleScripts));
    gBattlescriptCurrInstr = NULL;
    for (u32 i = 0; i < gBattlersCount; i++)
    {
        gBattlerPositions[i] = i;
        gBattleMons[i].species = SPECIES_RATTATA;
        gBattleMons[i].hp = 30;
        gBattleMons[i].maxHP = 40;
        gBattleMons[i].speed = 20;
        gBattleMons[i].types[0] = gBattleMons[i].types[1] = TYPE_NORMAL;
    }
    AllocateBattleResources();
}

TEST("Three Horizons playtest13 trainer RUN cannot whiteout")
{
    u16 trainer;
    bool32 doubles;
    PARAMETRIZE { trainer = TRAINER_TH9_BUG_CATCHER_JAMES; doubles = FALSE; }
    PARAMETRIZE { trainer = TRAINER_TH9_BRIDGE_BULBASAUR; doubles = FALSE; }
    PARAMETRIZE { trainer = TRAINER_TH11_JESSIE; doubles = TRUE; }
    PARAMETRIZE { trainer = TRAINER_TH11_JESSIE; doubles = FALSE; }
    PARAMETRIZE { trainer = TRAINER_TH11_JAMES; doubles = FALSE; }
    TrainerBattleParameter oldParams = gTrainerBattleParameter;
    void (*oldBattleMain)(void) = gBattleMainFunc;
    MainCallback oldCallback = gMain.callback2;
    InitRunProbe(BATTLE_TYPE_TRAINER | (doubles ? BATTLE_TYPE_DOUBLE | BATTLE_TYPE_TWO_OPPONENTS : 0));
    TRAINER_BATTLE_PARAM.opponentA = trainer;
    TRAINER_BATTLE_PARAM.opponentB = doubles ? TRAINER_TH11_JAMES : 0;
    TRAINER_BATTLE_PARAM.isDoubleBattle = doubles;
    u32 money = gSaveBlock1Ptr->money;
    struct WarpData location = gSaveBlock1Ptr->location;
    struct Coords16 pos = gSaveBlock1Ptr->pos;
    u8 flags[sizeof(gSaveBlock1Ptr->flags)];
    struct Bag bag = gSaveBlock1Ptr->bag;
    struct Pokemon party[PARTY_SIZE];
    struct BattlePokemon battlers[MAX_BATTLERS_COUNT];
    memcpy(flags, gSaveBlock1Ptr->flags, sizeof(flags));
    memcpy(party, gParties[B_TRAINER_PLAYER], sizeof(party));
    memcpy(battlers, gBattleMons, sizeof(battlers));
    bool32 returnedToActionSelection = Test_TH_ChooseRunAction();
    EXPECT(returnedToActionSelection);
    EXPECT(gBattlescriptCurrInstr == BattleScript_PrintCantRunFromTrainer);
    EXPECT(gSelectionBattleScripts[0] == NULL);
    EXPECT(!CanPlayerForfeitNormalTrainerBattle());
    EXPECT_EQ(gBattleOutcome, 0);
    EXPECT_EQ(gCurrentTurnActionNumber, 0);
    EXPECT_EQ(gSaveBlock1Ptr->money, money);
    EXPECT_EQ(memcmp(&location, &gSaveBlock1Ptr->location, sizeof(location)), 0);
    EXPECT_EQ(memcmp(&pos, &gSaveBlock1Ptr->pos, sizeof(pos)), 0);
    EXPECT_EQ(memcmp(flags, gSaveBlock1Ptr->flags, sizeof(flags)), 0);
    EXPECT_EQ(memcmp(&bag, &gSaveBlock1Ptr->bag, sizeof(bag)), 0);
    EXPECT_EQ(memcmp(party, gParties[B_TRAINER_PLAYER], sizeof(party)), 0);
    EXPECT_EQ(memcmp(battlers, gBattleMons, sizeof(battlers)), 0);
    EXPECT(gMain.callback2 == oldCallback);
    FreeBattleResources();
    gTrainerBattleParameter = oldParams;
    gBattleMainFunc = oldBattleMain;
}

TEST("Three Horizons playtest13 trainer RUN leaves wild escape unchanged")
{
    bool32 succeeds;
    PARAMETRIZE { succeeds = TRUE; }
    PARAMETRIZE { succeeds = FALSE; }
    InitRunProbe(0);
    // The slow case has a zero first-attempt threshold, independent of RNG.
    gBattleMons[0].speed = succeeds ? 1000 : 1;
    gBattleMons[1].speed = 1000;
    FlagClear(WE_FLAG_NO_RUNNING);
    EXPECT_EQ(IsRunningFromBattleImpossible(0), BATTLE_RUN_SUCCESS);
    bool32 escaped = TryRunFromBattle(0);
    EXPECT_EQ(escaped, succeeds);
    EXPECT_EQ(gBattleOutcome, succeeds ? B_OUTCOME_RAN : 0);
    EXPECT_EQ(gCurrentTurnActionNumber, succeeds ? gBattlersCount : 0);
    EXPECT_EQ(gBattleMons[0].hp, 30);
    EXPECT_EQ(gBattleMons[1].hp, 30);
    FreeBattleResources();
}

static struct ChooseMoveStruct *InitMoveProbe(u32 battler, bool32 duplicate, bool32 transformed)
{
    gMain.callback1 = NULL;
    SetVBlankCallback(NULL);
    SetHBlankCallback(NULL);
    ScanlineEffect_Clear();
    ResetTasks();
    ResetSpriteData();
    ResetPaletteFade();
    memset(&gBattleScripting, 0, sizeof(gBattleScripting));
    InitRunProbe(battler == 2 ? BATTLE_TYPE_DOUBLE : 0);
    AllocateBattleSpritesData();
    AllocateMonSpritesGfx();
    SetDefaultFontsPointer();
    for (u32 i = 0; i < gBattlersCount; i++)
    {
        gBattlerPartyIndexes[i] = i / 2;
        CreateMonWithIVs(GetBattlerMon(i), SPECIES_RATTATA, 20, 123 + i, OTID_STRUCT_PLAYER_ID, 12);
        PokemonToBattleMon(GetBattlerMon(i), &gBattleMons[i]);
    }
    enum Move moves[] = {MOVE_TACKLE, duplicate ? MOVE_TACKLE : MOVE_GROWL, MOVE_TAIL_WHIP, MOVE_NONE};
    u8 pp[] = {0, 3, 5, 0};
    u8 bonuses = 1 | (2 << 2) | (3 << 4);
    for (u32 i = 0; i < MAX_MON_MOVES; i++)
    {
        SetMonData(GetBattlerMon(battler), MON_DATA_MOVE1 + i, &moves[i]);
        SetMonData(GetBattlerMon(battler), MON_DATA_PP1 + i, &pp[i]);
    }
    SetMonData(GetBattlerMon(battler), MON_DATA_PP_BONUSES, &bonuses);
    PokemonToBattleMon(GetBattlerMon(battler), &gBattleMons[battler]);
    gBattleMons[battler].volatiles.transformed = transformed;
    struct ChooseMoveStruct *info = (void *)&gBattleResources->bufferA[battler][4];
    memset(info, 0, sizeof(*info));
    info->species = SPECIES_RATTATA;
    info->monTypes[0] = info->monTypes[1] = TYPE_NORMAL;
    for (u32 i = 0; i < MAX_MON_MOVES; i++)
    {
        info->moves[i] = moves[i];
        info->currentPP[i] = pp[i];
        info->maxPP[i] = CalculatePPWithBonus(moves[i], bonuses, i);
    }
    gMoveSelectionCursor[battler] = 0;
    gNumberOfMovesToChoose = 3;
    gBattlerControllerFuncs[battler] = HandleInputChooseMove;
    InitBattleBgsVideo();
    LoadBattleTextboxAndBackground();
    gMain.newKeys = gMain.heldKeys = gMain.newAndRepeatedKeys = 0;
    return info;
}

static void MoveProbeKey(u32 battler, u16 key)
{
    gMain.newKeys = gMain.newAndRepeatedKeys = key;
    gBattlerControllerFuncs[battler](battler);
    gMain.newKeys = gMain.newAndRepeatedKeys = 0;
}

static void FreeMoveProbe(void)
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

TEST("Three Horizons playtest13 SELECT swaps moves and PP")
{
    u32 battler;
    bool32 duplicate, transformed;
    PARAMETRIZE { battler = 0; duplicate = FALSE; transformed = FALSE; }
    PARAMETRIZE { battler = 2; duplicate = FALSE; transformed = FALSE; }
    PARAMETRIZE { battler = 0; duplicate = TRUE; transformed = FALSE; }
    PARAMETRIZE { battler = 0; duplicate = FALSE; transformed = TRUE; }
    struct ChooseMoveStruct *info = InitMoveProbe(battler, duplicate, transformed);
    struct ChooseMoveStruct original = *info;
    struct Pokemon party = *GetBattlerMon(battler);
    struct BattlePokemon opponent = gBattleMons[1];
    u8 ppBonuses = gBattleMons[battler].ppBonuses;
    for (u32 round = 0; round < 4; round++)
    {
        gMoveSelectionCursor[battler] = 0;
        MoveProbeKey(battler, SELECT_BUTTON);
        EXPECT(gBattlerControllerFuncs[battler] == HandleMoveSwitching);
        EXPECT_EQ(gMultiUsePlayerCursor, 1);
        // The trailing empty fourth slot must remain unselectable.
        MoveProbeKey(battler, DPAD_DOWN);
        EXPECT_EQ(gMultiUsePlayerCursor, 1);
        MoveProbeKey(battler, A_BUTTON);
        EXPECT(gBattlerControllerFuncs[battler] == HandleInputChooseMove);
        for (u32 i = 0; i < MAX_MON_MOVES; i++)
        {
            u32 source = (round % 2 == 0 && i < 2) ? i ^ 1 : i;
            EXPECT_EQ(info->moves[i], original.moves[source]);
            EXPECT_EQ(info->currentPP[i], original.currentPP[source]);
            EXPECT_EQ(info->maxPP[i], original.maxPP[source]);
            EXPECT_EQ(gBattleMons[battler].moves[i], original.moves[source]);
            EXPECT_EQ(gBattleMons[battler].pp[i], original.currentPP[source]);
            EXPECT_EQ((gBattleMons[battler].ppBonuses >> (i * 2)) & 3, (ppBonuses >> (source * 2)) & 3);
            if (!transformed)
            {
                EXPECT_EQ(GetMonData(GetBattlerMon(battler), MON_DATA_MOVE1 + i), original.moves[source]);
                EXPECT_EQ(GetMonData(GetBattlerMon(battler), MON_DATA_PP1 + i), original.currentPP[source]);
                EXPECT_EQ((GetMonData(GetBattlerMon(battler), MON_DATA_PP_BONUSES) >> (i * 2)) & 3, (ppBonuses >> (source * 2)) & 3);
            }
        }
        if (transformed)
            EXPECT_EQ(memcmp(&party, GetBattlerMon(battler), sizeof(party)), 0);
        EXPECT_EQ(memcmp(&opponent, &gBattleMons[1], sizeof(opponent)), 0);
    }
    FreeMoveProbe();
}

TEST("Three Horizons playtest13 SELECT swap preserves disabled and choice slots")
{
    InitMoveProbe(0, FALSE, FALSE);
    gBattleMons[0].volatiles.disabledMove = MOVE_GROWL;
    gBattleStruct->choicedMove[0] = MOVE_TACKLE;
    gBattleMons[0].volatiles.encoredMove = MOVE_GROWL;
    gBattleMons[0].volatiles.encoredMovePos = 1;
    gBattleMons[0].volatiles.mimickedMoves = 1 << 1;
    gBattleMons[0].volatiles.usedMoves = (1 << 1) | (1 << 2);
    // Drive the native swap directly to test state even with SELECT disabled.
    gMultiUsePlayerCursor = 1;
    gBattlerControllerFuncs[0] = HandleMoveSwitching;
    MoveProbeKey(0, A_BUTTON);
    EXPECT_EQ((u32)gBattleMons[0].volatiles.disabledMove, MOVE_GROWL);
    EXPECT_EQ(gBattleStruct->choicedMove[0], MOVE_TACKLE);
    EXPECT_EQ((u32)gBattleMons[0].volatiles.mimickedMoves, 1 << 0);
    EXPECT_EQ((u32)gBattleMons[0].volatiles.encoredMove, MOVE_GROWL);
    EXPECT_EQ((u32)gBattleMons[0].volatiles.encoredMovePos, 0);
    EXPECT_EQ((u32)gBattleMons[0].volatiles.usedMoves, (1 << 0) | (1 << 2));
    gMoveSelectionCursor[0] = 0;
    gMultiUsePlayerCursor = 1;
    gBattlerControllerFuncs[0] = HandleMoveSwitching;
    MoveProbeKey(0, A_BUTTON);
    EXPECT_EQ((u32)gBattleMons[0].volatiles.mimickedMoves, 1 << 1);
    EXPECT_EQ((u32)gBattleMons[0].volatiles.encoredMovePos, 1);
    EXPECT_EQ((u32)gBattleMons[0].volatiles.usedMoves, (1 << 1) | (1 << 2));
    EXPECT_EQ((u32)gBattleMons[0].volatiles.disabledMove, MOVE_GROWL);
    EXPECT_EQ(gBattleStruct->choicedMove[0], MOVE_TACKLE);
    FreeMoveProbe();
}

TEST("Three Horizons playtest13 SELECT moves Encore slot with its move")
{
    InitMoveProbe(0, FALSE, FALSE);
    gBattleMons[0].volatiles.encoredMove = MOVE_GROWL;
    gBattleMons[0].volatiles.encoredMovePos = 1;
    gMultiUsePlayerCursor = 1;
    gBattlerControllerFuncs[0] = HandleMoveSwitching;
    MoveProbeKey(0, A_BUTTON);
    EXPECT_EQ((u32)gBattleMons[0].volatiles.encoredMove, MOVE_GROWL);
    EXPECT_EQ((u32)gBattleMons[0].volatiles.encoredMovePos, 0);
    FreeMoveProbe();
}

TEST("Three Horizons playtest13 SELECT moves Last Resort history with its move")
{
    InitMoveProbe(0, FALSE, FALSE);
    gBattleMons[0].volatiles.usedMoves = (1 << 1) | (1 << 2);
    gMultiUsePlayerCursor = 1;
    gBattlerControllerFuncs[0] = HandleMoveSwitching;
    MoveProbeKey(0, A_BUTTON);
    EXPECT_EQ((u32)gBattleMons[0].volatiles.usedMoves, (1 << 0) | (1 << 2));
    FreeMoveProbe();
}

TEST("Three Horizons playtest13 SELECT cancel changes nothing")
{
    struct ChooseMoveStruct *info = InitMoveProbe(0, FALSE, FALSE);
    struct ChooseMoveStruct original = *info;
    struct Pokemon party = *GetBattlerMon(0);
    struct BattlePokemon mon = gBattleMons[0];
    gMultiUsePlayerCursor = 1;
    gBattlerControllerFuncs[0] = HandleMoveSwitching;
    MoveProbeKey(0, B_BUTTON);
    EXPECT(gBattlerControllerFuncs[0] == HandleInputChooseMove);
    EXPECT_EQ(memcmp(info, &original, sizeof(original)), 0);
    EXPECT_EQ(memcmp(&party, GetBattlerMon(0), sizeof(party)), 0);
    EXPECT_EQ(memcmp(&mon, &gBattleMons[0], sizeof(mon)), 0);
    FreeMoveProbe();
}

TEST("Three Horizons playtest13 SELECT preserves native entry restrictions")
{
    u32 restriction;
    PARAMETRIZE { restriction = 0; } // Link battle.
    PARAMETRIZE { restriction = 1; } // Z preview.
    PARAMETRIZE { restriction = 2; } // Description open.
    PARAMETRIZE { restriction = 3; } // Only one move.
    InitMoveProbe(0, FALSE, FALSE);
    if (restriction == 0) gBattleTypeFlags |= BATTLE_TYPE_LINK;
    if (restriction == 1) gBattleStruct->zmove.viewing = TRUE;
    if (restriction == 2) gBattleStruct->descriptionSubmenu = TRUE;
    if (restriction == 3) gNumberOfMovesToChoose = 1;
    MoveProbeKey(0, SELECT_BUTTON);
    EXPECT(gBattlerControllerFuncs[0] == HandleInputChooseMove);
    FreeMoveProbe();
}

extern void Task_HandleCaughtMonPageInput(u8 taskId);

static const u8 sDexProbeCommand[] = {B_SCR_OP_DISPLAYDEXINFO, B_SCR_OP_END};
static const u8 sNicknameProbeCommand[] = {B_SCR_OP_TRYGIVECAUGHTMONNICK, B_SCR_OP_END};

static void CatchProbeFrame(const u8 *command, u16 newKeys, u16 heldKeys)
{
    gMain.newKeys = gMain.newAndRepeatedKeys = newKeys;
    gMain.heldKeys = heldKeys;
    if (gBattlescriptCurrInstr == command)
        gBattleScriptingCommandsTable[command[0]]();
    gMain.callback2();
    MapMusicMain();
    VBlankIntrWait();
}

static u8 InitDexProbe(enum Species species)
{
    Test_MgbaPrintf("Dex offsets seen=%d caught=%d bytes=%d", (u32)__builtin_offsetof(struct SaveBlock1, dexSeen), (u32)__builtin_offsetof(struct SaveBlock1, dexCaught), (u32)NUM_DEX_FLAG_BYTES);
    InitMoveProbe(0, FALSE, FALSE);
    CreateMonWithIVs(GetBattlerMon(1), species, 5, 9876, OTID_STRUCT_PLAYER_ID, 12);
    PokemonToBattleMon(GetBattlerMon(1), &gBattleMons[1]);
    gBattlerAttacker = 0;
    gBattlerTarget = 1;
    gBattleScripting.monCaught = TRUE;
    memset(gBattleCommunication, 0, sizeof(gBattleCommunication));
    SetMainCallback2(BattleMainCB2);
    SetVBlankCallback(VBlankCB_Battle);
    gBattlescriptCurrInstr = sDexProbeCommand;
    u32 frame;
    for (frame = 0; frame < 1200; frame++)
    {
        CatchProbeFrame(sDexProbeCommand, 0, 0);
        if (FindTaskIdByFunc(Task_HandleCaughtMonPageInput) != TASK_NONE)
            break;
    }
    EXPECT_LT(frame, 1200);
    EXPECT(!gPaletteFade.active);
    EXPECT(GetBgTilemapBuffer(2) != NULL);
    EXPECT(GetBgTilemapBuffer(3) != NULL);
    // The cry channel can start on the VBlank after the task switches input owner.
    for (frame = 0; frame < 60 && !IsCryPlaying(); frame++)
        CatchProbeFrame(sDexProbeCommand, 0, 0);
    EXPECT_LT(frame, 60);
    EXPECT(IsCryPlaying());
    return FindTaskIdByFunc(Task_HandleCaughtMonPageInput);
}

TEST("Three Horizons playtest13 first catch rapid Zubat input cannot dismiss after cry")
{
    MainCallback old1 = gMain.callback1, old2 = gMain.callback2;
    u8 dexTask = InitDexProbe(SPECIES_ZUBAT);
    u32 frame;
    for (frame = 0; frame < 1200 && (FuncIsActiveTask(Task_DuckBGMForPokemonCry) || IsCryPlaying()); frame++)
        CatchProbeFrame(sDexProbeCommand, frame % 2 ? 0 : A_BUTTON, frame % 2 ? 0 : A_BUTTON);
    EXPECT_LT(frame, 1200);
    // Continue the capture's rapid pressing beyond presentation completion.
    // A single released frame between presses is not intentional readiness.
    for (frame = 0; frame < 120; frame++)
    {
        u16 key = frame % 2 ? A_BUTTON : 0;
        CatchProbeFrame(sDexProbeCommand, key, key);
        EXPECT(gTasks[dexTask].func == Task_HandleCaughtMonPageInput);
        EXPECT(gBattlescriptCurrInstr == sDexProbeCommand);
    }
    for (frame = 0; frame < 16; frame++) CatchProbeFrame(sDexProbeCommand, 0, 0);
    CatchProbeFrame(sDexProbeCommand, A_BUTTON, A_BUTTON);
    for (frame = 0; frame < 1200 && gBattlescriptCurrInstr == sDexProbeCommand; frame++)
        CatchProbeFrame(sDexProbeCommand, 0, 0);
    EXPECT_LT(frame, 1200);
    FreeMoveProbe();
    gMain.callback1 = old1;
    SetMainCallback2(old2);
}

TEST("Three Horizons playtest13 first catch finishes Dex before nickname")
{
    enum Species species;
    bool32 rapid;
    PARAMETRIZE { species = SPECIES_CATERPIE; rapid = TRUE; }
    PARAMETRIZE { species = SPECIES_WEEDLE; rapid = TRUE; }
    PARAMETRIZE { species = SPECIES_PIKACHU; rapid = TRUE; }
    PARAMETRIZE { species = SPECIES_CATERPIE; rapid = FALSE; }
    MainCallback old1 = gMain.callback1, old2 = gMain.callback2;
    u8 dexTask = InitDexProbe(species);
    u32 frame;
    // A new input during the actual cry must not skip the presentation.
    for (frame = 0; frame < 1200 && FuncIsActiveTask(Task_DuckBGMForPokemonCry); frame++)
    {
        u16 key = rapid && !(frame % 2) ? A_BUTTON : 0;
        CatchProbeFrame(sDexProbeCommand, key, key);
        EXPECT(gTasks[dexTask].func == Task_HandleCaughtMonPageInput);
        EXPECT(gBattlescriptCurrInstr == sDexProbeCommand);
    }
    EXPECT_LT(frame, 1200);
    for (frame = 0; frame < 16; frame++) CatchProbeFrame(sDexProbeCommand, 0, 0);
    CatchProbeFrame(sDexProbeCommand, A_BUTTON, A_BUTTON);
    for (frame = 0; frame < 1200 && gBattlescriptCurrInstr == sDexProbeCommand; frame++)
        CatchProbeFrame(sDexProbeCommand, 0, 0);
    EXPECT_LT(frame, 1200);
    EXPECT(gMain.callback2 == BattleMainCB2);
    EXPECT(!gPaletteFade.active);
    EXPECT(gBattleAnimBgTileBuffer != NULL);
    EXPECT_EQ(gBattle_BG3_X, 0);
    // The returned scene accepts one fresh nickname choice, with no A leakage.
    memset(gBattleCommunication, 0, sizeof(gBattleCommunication));
    gBattlescriptCurrInstr = sNicknameProbeCommand;
    CatchProbeFrame(sNicknameProbeCommand, 0, 0);
    CatchProbeFrame(sNicknameProbeCommand, 0, A_BUTTON);
    EXPECT_EQ(gBattleCommunication[MULTIUSE_STATE], 1);
    EXPECT(gBattlescriptCurrInstr == sNicknameProbeCommand);
    CatchProbeFrame(sNicknameProbeCommand, B_BUTTON, B_BUTTON);
    CatchProbeFrame(sNicknameProbeCommand, 0, 0);
    EXPECT(gBattlescriptCurrInstr == sNicknameProbeCommand + 1);
    FreeMoveProbe();
    gMain.callback1 = old1;
    SetMainCallback2(old2);
}

TEST("Three Horizons playtest13 first catch requires fresh input after presentation")
{
    u16 held, fresh;
    PARAMETRIZE { held = A_BUTTON; fresh = A_BUTTON; }
    PARAMETRIZE { held = B_BUTTON; fresh = B_BUTTON; }
    PARAMETRIZE { held = A_BUTTON; fresh = B_BUTTON; }
    MainCallback old1 = gMain.callback1, old2 = gMain.callback2;
    u8 dexTask = InitDexProbe(SPECIES_ZUBAT);
    u32 frame;
    for (frame = 0; frame < 1200 && FuncIsActiveTask(Task_DuckBGMForPokemonCry); frame++)
        CatchProbeFrame(sDexProbeCommand, 0, held);
    EXPECT_LT(frame, 1200);
    // Even a new press on the completion boundary must wait for a release.
    CatchProbeFrame(sDexProbeCommand, held, held);
    EXPECT(gTasks[dexTask].func == Task_HandleCaughtMonPageInput);
    // No input leaves the fully initialized entry readable indefinitely.
    for (frame = 0; frame < 120; frame++)
    {
        CatchProbeFrame(sDexProbeCommand, 0, 0);
        EXPECT(gTasks[dexTask].func == Task_HandleCaughtMonPageInput);
    }
    CatchProbeFrame(sDexProbeCommand, fresh, fresh);
    for (frame = 0; frame < 1200 && gBattlescriptCurrInstr == sDexProbeCommand; frame++)
        CatchProbeFrame(sDexProbeCommand, 0, 0);
    EXPECT_LT(frame, 1200);
    FreeMoveProbe();
    gMain.callback1 = old1;
    SetMainCallback2(old2);
}

TEST("Three Horizons playtest13 first catch registers once and repeat skips Dex")
{
    enum Species species;
    PARAMETRIZE { species = SPECIES_CATERPIE; }
    PARAMETRIZE { species = SPECIES_WEEDLE; }
    PARAMETRIZE { species = SPECIES_PIKACHU; }
    PARAMETRIZE { species = SPECIES_ZUBAT; }
    MainCallback old1 = gMain.callback1, old2 = gMain.callback2;
    InitMoveProbe(0, FALSE, FALSE);
    CreateMonWithIVs(GetBattlerMon(1), species, 5, 9876, OTID_STRUCT_PLAYER_ID, 12);
    PokemonToBattleMon(GetBattlerMon(1), &gBattleMons[1]);
    gBattleScripting.monCaught = TRUE;
    u32 dex = SpeciesToNationalPokedexNum(species), offset = (dex - 1) / 8;
    u8 oldCaught = gSaveBlock1Ptr->dexCaught[offset];
    u8 oldSeen = gSaveBlock1Ptr->dexSeen[offset];
    gSaveBlock1Ptr->dexCaught[offset] &= ~(1 << ((dex - 1) % 8));
    u32 before = GetNationalPokedexCount(FLAG_GET_CAUGHT);
    u8 command[6] = {B_SCR_OP_TRYSETCAUGHTMONDEXFLAGS};
    const u8 *repeat = sNicknameProbeCommand;
    memcpy(command + 1, &repeat, sizeof(repeat));
    gBattlescriptCurrInstr = command;
    gBattleScriptingCommandsTable[command[0]]();
    EXPECT(gBattlescriptCurrInstr == command + 5);
    EXPECT_EQ(GetNationalPokedexCount(FLAG_GET_CAUGHT), before + 1);
    EXPECT(GetSetPokedexFlag(dex, FLAG_GET_CAUGHT));
    // Repeat capture follows the native skip pointer, with no second registration.
    gBattlescriptCurrInstr = command;
    gBattleScriptingCommandsTable[command[0]]();
    EXPECT(gBattlescriptCurrInstr == repeat);
    EXPECT_EQ(GetNationalPokedexCount(FLAG_GET_CAUGHT), before + 1);
    EXPECT_EQ(FindTaskIdByFunc(Task_HandleCaughtMonPageInput), TASK_NONE);
    gSaveBlock1Ptr->dexCaught[offset] = oldCaught;
    gSaveBlock1Ptr->dexSeen[offset] = oldSeen;
    FreeMoveProbe();
    gMain.callback1 = old1;
    SetMainCallback2(old2);
}

TEST("Three Horizons playtest13 first catch nickname accepts max name with party or PC return")
{
    bool32 fullParty;
    PARAMETRIZE { fullParty = FALSE; }
    PARAMETRIZE { fullParty = TRUE; }
    MainCallback old1 = gMain.callback1, old2 = gMain.callback2;
    InitMoveProbe(0, FALSE, FALSE);
    for (u32 i = 1; i < PARTY_SIZE; i++)
    {
        if (fullParty)
            CreateMonWithIVs(&gParties[B_TRAINER_PLAYER][i], SPECIES_RATTATA, 5, 100 + i, OTID_STRUCT_PLAYER_ID, 12);
        else
            ZeroMonData(&gParties[B_TRAINER_PLAYER][i]);
    }
    CalculatePlayerPartyCount();
    gBattlerTarget = 1;
    gBattleScripting.monCaught = TRUE;
    SetMonData(GetBattlerMon(1), MON_DATA_NICKNAME, COMPOUND_STRING("ABCDEFGHIJKL"));
    memset(gBattleCommunication, 0, sizeof(gBattleCommunication));
    SetMainCallback2(BattleMainCB2);
    SetVBlankCallback(VBlankCB_Battle);
    gBattlescriptCurrInstr = sNicknameProbeCommand;
    CatchProbeFrame(sNicknameProbeCommand, 0, 0);
    EXPECT_EQ(gBattleCommunication[MULTIUSE_STATE], 1);
    CatchProbeFrame(sNicknameProbeCommand, A_BUTTON, A_BUTTON);
    EXPECT_EQ(gBattleCommunication[MULTIUSE_STATE], 2);
    u32 frame;
    for (frame = 0; frame < 1200 && gBattleCommunication[MULTIUSE_STATE] != 3; frame++)
        CatchProbeFrame(sNicknameProbeCommand, 0, 0);
    EXPECT_LT(frame, 1200);
    // Accept the existing maximum-length name through the real naming UI.
    for (frame = 0; frame < 1800 && gBattlescriptCurrInstr == sNicknameProbeCommand; frame++)
    {
        u16 key = frame % 40 == 0 ? START_BUTTON : frame % 40 == 20 ? A_BUTTON : 0;
        CatchProbeFrame(sNicknameProbeCommand, key, key);
    }
    EXPECT_LT(frame, 1800);
    EXPECT(gMain.callback2 == BattleMainCB2);
    EXPECT(!gPaletteFade.active);
    u8 nickname[POKEMON_NAME_LENGTH + 1];
    GetMonData(GetBattlerMon(1), MON_DATA_NICKNAME, nickname);
    EXPECT_EQ(StringCompare(nickname, COMPOUND_STRING("ABCDEFGHIJKL")), 0);
    EXPECT_EQ(CalculatePlayerPartyCount(), fullParty ? PARTY_SIZE : 1);
    FreeMoveProbe();
    gMain.callback1 = old1;
    SetMainCallback2(old2);
}

TEST("Three Horizons playtest13 first catch editor returns before registering")
{
    bool32 confirm;
    PARAMETRIZE { confirm = FALSE; }
    PARAMETRIZE { confirm = TRUE; }
    MainCallback old1 = gMain.callback1, old2 = gMain.callback2;
    InitMoveProbe(0, FALSE, FALSE);
    CreateMonWithIVs(GetBattlerMon(1), SPECIES_ARTICUNO, 35, 9876, OTID_STRUCT_PLAYER_ID, 12);
    PokemonToBattleMon(GetBattlerMon(1), &gBattleMons[1]);
    gBattleScripting.monCaught = TRUE;
    gBattlerTarget = 1;
    u32 dex = SpeciesToNationalPokedexNum(SPECIES_ARTICUNO), offset = (dex - 1) / 8;
    u8 oldCaught = gSaveBlock1Ptr->dexCaught[offset];
    u8 oldSeen = gSaveBlock1Ptr->dexSeen[offset];
    gSaveBlock1Ptr->dexCaught[offset] &= ~(1 << ((dex - 1) % 8));
    u32 before = GetNationalPokedexCount(FLAG_GET_CAUGHT);
    struct Pokemon original = *GetBattlerMon(1);
    u8 command[6] = {B_SCR_OP_TRYSETCAUGHTMONDEXFLAGS};
    const u8 *repeat = sNicknameProbeCommand;
    memcpy(command + 1, &repeat, sizeof(repeat));
    memset(gBattleCommunication, 0, sizeof(gBattleCommunication));
    SetMainCallback2(BattleMainCB2);
    SetVBlankCallback(VBlankCB_Battle);
    gBattlescriptCurrInstr = command;
    u32 frame;
    for (frame = 0; frame < 1200; frame++)
    {
        CatchProbeFrame(command, 0, 0);
        EXPECT_EQ(GetNationalPokedexCount(FLAG_GET_CAUGHT), before);
        if (gBattleCommunication[0] == 2 && !gPaletteFade.active)
            break;
    }
    EXPECT_LT(frame, 1200);
    EXPECT(gMain.callback2 != BattleMainCB2);
    EXPECT(gBattlescriptCurrInstr == command);
    // Confirm defaults or cancel: both must return to the battle before registration.
    CatchProbeFrame(command, confirm ? A_BUTTON : B_BUTTON, confirm ? A_BUTTON : B_BUTTON);
    for (frame = 0; frame < 1200 && gBattlescriptCurrInstr == command; frame++)
        CatchProbeFrame(command, 0, 0);
    EXPECT_LT(frame, 1200);
    EXPECT(gMain.callback2 == BattleMainCB2);
    EXPECT(!gPaletteFade.active);
    EXPECT(gBattlescriptCurrInstr == command + 5);
    EXPECT_EQ(GetNationalPokedexCount(FLAG_GET_CAUGHT), before + 1);
    EXPECT_EQ(GetMonData(GetBattlerMon(1), MON_DATA_PERSONALITY), GetMonData(&original, MON_DATA_PERSONALITY));
    EXPECT_EQ(GetMonData(GetBattlerMon(1), MON_DATA_SPECIES), SPECIES_ARTICUNO);
    EXPECT_EQ(GetMonData(GetBattlerMon(1), MON_DATA_LEVEL), 35);
    gSaveBlock1Ptr->dexCaught[offset] = oldCaught;
    gSaveBlock1Ptr->dexSeen[offset] = oldSeen;
    FreeMoveProbe();
    gMain.callback1 = old1;
    SetMainCallback2(old2);
}
#endif
