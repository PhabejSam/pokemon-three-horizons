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
#endif
