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
#endif
