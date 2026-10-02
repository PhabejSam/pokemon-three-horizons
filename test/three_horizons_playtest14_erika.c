#include "global.h"
#include "test/test.h"
#include "event_data.h"
#include "item.h"
#include "malloc.h"
#include "battle_setup.h"
#include "battle.h"
#include "main.h"
#include "overworld.h"
#include "script.h"
#include "trainer_see.h"
#include "trainer_util.h"
#include "data.h"
#include "pokemon.h"
#include "three_horizons_helpers.h"
#include "three_horizons_chapter14.h"
#include "three_horizons_rematches.h"
#include "constants/three_horizons.h"
#include "constants/opponents.h"
#include "constants/maps.h"

#if THREE_HORIZONS
static void ResetErika(void)
{
    InitEventData(); ClearBag(); TH13_ResetRematches();
    memset(gSaveBlock1Ptr->pcItems, 0, sizeof(gSaveBlock1Ptr->pcItems));
}

TEST("Three Horizons PT14 erika: full TM pocket preserves badge win and retryable reward")
{
    bool32 scope;
    PARAMETRIZE { scope = FALSE; }
    PARAMETRIZE { scope = TRUE; }
    ResetErika();
    if (scope) FlagSet(FLAG_TH14_SILPH_SCOPE);
    SetTrainerFlag(TRAINER_TH14_ERIKA); FlagSet(FLAG_BADGE04_GET);
    struct BagPocket *pocket = &gBagPockets[POCKET_TM_HM];
    for (u32 i = 0; i < pocket->capacity; i++)
        BagPocket_SetSlotItemIdAndCount(pocket, i, ITEM_TM01, 1);
    ASSUME(!CheckBagHasSpace(ITEM_TM19, 1));
    struct SaveBlock1 *before = Alloc(sizeof(*before)); EXPECT(before != NULL);
    memcpy(before, gSaveBlock1Ptr, sizeof(*before));
    EXPECT_EQ(TH14_TryGiveUniqueItem(ITEM_TM19, FLAG_TH14_ERIKA_TM), TH14_GIFT_NO_ROOM);
    EXPECT_EQ(memcmp(before, gSaveBlock1Ptr, sizeof(*before)), 0);
    EXPECT(FlagGet(FLAG_BADGE04_GET)); EXPECT(HasTrainerBeenFought(TRAINER_TH14_ERIKA));
    EXPECT(!FlagGet(FLAG_TH14_ERIKA_TM));
    BagPocket_SetSlotItemIdAndCount(pocket, pocket->capacity - 1, ITEM_NONE, 0);
    EXPECT_EQ(TH14_TryGiveUniqueItem(ITEM_TM19, FLAG_TH14_ERIKA_TM), TH14_GIFT_GIVEN);
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_TM19), 1);
    EXPECT(FlagGet(FLAG_TH14_ERIKA_TM));
    memcpy(before, gSaveBlock1Ptr, sizeof(*before));
    for (u32 i = 0; i < 3; i++)
        EXPECT_EQ(TH14_TryGiveUniqueItem(ITEM_TM19, FLAG_TH14_ERIKA_TM), TH14_GIFT_ALREADY_OWNED);
    EXPECT_EQ(memcmp(before, gSaveBlock1Ptr, sizeof(*before)), 0);
    Free(before);
}

TEST("Three Horizons PT14 erika: Bag PC and receipt each prevent a duplicate reusable TM")
{
    u32 owned;
    PARAMETRIZE { owned = 0; }
    PARAMETRIZE { owned = 1; }
    PARAMETRIZE { owned = 2; }
    ResetErika();
    if (owned == 0) EXPECT(AddBagItem(ITEM_TM19, 1));
    if (owned == 1) EXPECT(AddPCItem(ITEM_TM19, 1));
    if (owned == 2) FlagSet(FLAG_TH14_ERIKA_TM);
    gSpecialVar_0x8004 = ITEM_TM19; gSpecialVar_0x8005 = FLAG_TH14_ERIKA_TM;
    TH14_ScriptGiveUniqueItem();
    EXPECT_EQ(gSpecialVar_Result, TH14_GIFT_ALREADY_OWNED);
    EXPECT(FlagGet(FLAG_TH14_ERIKA_TM));
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_TM19), owned == 0);
    EXPECT_EQ(CheckPCHasItem(ITEM_TM19, 1), owned == 1);
    EXPECT(!FlagGet(FLAG_BADGE04_GET)); EXPECT(!HasTrainerBeenFought(TRAINER_TH14_ERIKA));
}

TEST("Three Horizons PT14 erika: seven ordinary Gym identities are eligible but leader never is")
{
    static const u8 localIds[] = {1,2,3,4,5,6,8};
    ResetErika();
    gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(MAP_TH14_CELADON_CITY_GYM);
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(MAP_TH14_CELADON_CITY_GYM);
    for (u32 i = 0; i < ARRAY_COUNT(localIds); i++)
    {
        u16 trainer = TRAINER_TH14_GYM_KAY + i;
        EXPECT_EQ(TH13_GetMapTrainer(localIds[i]), trainer);
        EXPECT(!TH13_SetRematchReady(trainer));
        SetTrainerFlag(trainer); EXPECT(TH13_SetRematchReady(trainer));
        EXPECT(TH13_IsRematchReady(trainer));
    }
    EXPECT_EQ(TH13_GetMapTrainer(7), 0);
    SetTrainerFlag(TRAINER_TH14_ERIKA); EXPECT(!TH13_SetRematchReady(TRAINER_TH14_ERIKA));
    TH13_ResetRematches();
    for (u32 i = 0; i < ARRAY_COUNT(localIds); i++)
        EXPECT(HasTrainerBeenFought(TRAINER_TH14_GYM_KAY + i));
    EXPECT(HasTrainerBeenFought(TRAINER_TH14_ERIKA));
}
extern const u8 TH14_CeladonCity_Gym_EventScript_Erika[], TH14_Erika_Victory[];
extern const u8 TH14_CeladonCity_GameCorner_EventScript_GymGuy[];
extern const u8 EventSnippet_DoTrainerBattle[], EventSnippet_GotoPostBattleScript[], EventSnippet_EndTrainerBattle[];
extern void Test_TH14_EndTrainerBattle(void);
extern bool32 Test_TH14_CreateRematchParty(struct Pokemon *, const struct Trainer *, u16, u8, u8);

static void SetErikaMap(void)
{
    gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(MAP_TH14_CELADON_CITY_GYM);
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(MAP_TH14_CELADON_CITY_GYM);
    gMapHeader = *Overworld_GetMapHeaderByGroupAndId(MAP_GROUP(MAP_TH14_CELADON_CITY_GYM), MAP_NUM(MAP_TH14_CELADON_CITY_GYM));
    gNoOfApproachingTrainers = 0; gApproachingTrainerId = 0; gSpecialVar_LastTalked = 7;
}

static bool32 ContainsSnippet(struct ScriptContext *ctx, const u8 *ptr)
{
    if (ctx->scriptPtr == ptr) return TRUE;
    for (u32 i = 0; i < ctx->stackDepth; i++) if (ctx->stack[i] == ptr) return TRUE;
    return FALSE;
}

TEST("Three Horizons PT14 erika: compiled first battle and repeat paths ignore Giovanni order")
{
    for (u32 scope = 0; scope < 2; scope++)
        for (u32 defeated = 0; defeated < 2; defeated++)
        {
            ResetErika(); SetErikaMap();
            if (scope) FlagSet(FLAG_TH14_SILPH_SCOPE);
            if (defeated) SetTrainerFlag(TRAINER_TH14_ERIKA);
            struct ScriptContext ctx = {0};
            ctx.scriptPtr = TH14_CeladonCity_Gym_EventScript_Erika + TRAINERBATTLE_OPCODE_OFFSET;
            ConfigureTrainerBattle(&ctx);
            EXPECT_EQ(TRAINER_BATTLE_PARAM.opponentA, TRAINER_TH14_ERIKA);
            EXPECT(!TRAINER_BATTLE_PARAM.isDoubleBattle); EXPECT(!TRAINER_BATTLE_PARAM.isRematch);
            EXPECT_EQ(ContainsSnippet(&ctx, EventSnippet_DoTrainerBattle), !defeated);
            EXPECT_EQ(ContainsSnippet(&ctx, EventSnippet_GotoPostBattleScript), defeated);
            EXPECT_EQ(ContainsSnippet(&ctx, EventSnippet_EndTrainerBattle), !defeated);
            EXPECT_EQ(BattleSetup_GetTrainerPostBattleScript(), TH14_Erika_Victory);
            EXPECT_EQ(HasTrainerBeenFought(TRAINER_TH14_ERIKA), defeated);
            EXPECT(!FlagGet(FLAG_BADGE04_GET)); EXPECT(!FlagGet(FLAG_TH14_ERIKA_TM));
            ScriptContext_Init(); UnlockPlayerFieldControls();
        }
}

TEST("Three Horizons PT14 erika: real field completion records wins and sends losses to blackout")
{
    u8 outcome;
    PARAMETRIZE { outcome = B_OUTCOME_WON; }
    PARAMETRIZE { outcome = B_OUTCOME_LOST; }
    MainCallback saved = gMain.callback2;
    ResetErika(); SetErikaMap();
    struct ScriptContext ctx = {0};
    ctx.scriptPtr = TH14_CeladonCity_Gym_EventScript_Erika + TRAINERBATTLE_OPCODE_OFFSET;
    ConfigureTrainerBattle(&ctx);
    gBattleTypeFlags = BATTLE_TYPE_TRAINER;
    gBattleOutcome = outcome;
    Test_TH14_EndTrainerBattle();
    MainCallback selected = gMain.callback2;
    SetMainCallback2(saved); // Never run field/blackout callbacks inside the test runner.
    EXPECT_EQ(selected, outcome == B_OUTCOME_WON ? CB2_ReturnToFieldContinueScriptPlayMapMusic : CB2_WhiteOut);
    EXPECT_EQ(HasTrainerBeenFought(TRAINER_TH14_ERIKA), outcome == B_OUTCOME_WON);
    EXPECT(!FlagGet(FLAG_BADGE04_GET)); EXPECT(!FlagGet(FLAG_TH14_ERIKA_TM));
    if (outcome == B_OUTCOME_WON)
    {
        EXPECT(RunScriptImmediatelyUntilEffect(SCREFF_V1 | SCREFF_HARDWARE | SCREFF_TRAINERBATTLE,
            TH14_Erika_Victory, &ctx));
        EXPECT(FlagGet(FLAG_BADGE04_GET)); EXPECT(!FlagGet(FLAG_TH14_ERIKA_TM));
    }
    ScriptContext_Init(); UnlockPlayerFieldControls();
}

TEST("Three Horizons PT14 erika: compiled victory preserves prior badges and permanent history on repeat")
{
    ResetErika(); SetErikaMap();
    FlagSet(FLAG_BADGE01_GET); FlagSet(FLAG_BADGE02_GET); FlagSet(FLAG_BADGE03_GET);
    SetTrainerFlag(TRAINER_TH14_ERIKA);
    SetTrainerFlag(TRAINER_TH14_GYM_KAY);
    struct ScriptContext ctx;
    EXPECT(RunScriptImmediatelyUntilEffect(SCREFF_V1 | SCREFF_HARDWARE | SCREFF_TRAINERBATTLE,
        TH14_Erika_Victory, &ctx));
    for (u32 b = FLAG_BADGE01_GET; b <= FLAG_BADGE04_GET; b++) EXPECT(FlagGet(b));
    for (u32 b = FLAG_BADGE05_GET; b <= FLAG_BADGE08_GET; b++) EXPECT(!FlagGet(b));
    EXPECT(!FlagGet(FLAG_TH14_ERIKA_TM));
    EXPECT_EQ(TH14_TryGiveUniqueItem(ITEM_TM19, FLAG_TH14_ERIKA_TM), TH14_GIFT_GIVEN);
    struct SaveBlock1 *before = Alloc(sizeof(*before)); EXPECT(before != NULL);
    memcpy(before, gSaveBlock1Ptr, sizeof(*before));
    EXPECT(RunScriptImmediatelyUntilEffect(SCREFF_V1 | SCREFF_HARDWARE | SCREFF_TRAINERBATTLE,
        TH14_Erika_Victory, &ctx));
    TH13_ResetRematches(); ClearTempFieldEventData();
    EXPECT_EQ(memcmp(before, gSaveBlock1Ptr, sizeof(*before)), 0);
    EXPECT(HasTrainerBeenFought(TRAINER_TH14_ERIKA)); EXPECT(HasTrainerBeenFought(TRAINER_TH14_GYM_KAY));
    Free(before);
}

TEST("Three Horizons PT14 erika: compiled guide changes only for Rainbow Badge")
{
    struct ScriptContext before, unrelated, after;
    ResetErika();
    EXPECT(RunScriptImmediatelyUntilEffect(SCREFF_V1 | SCREFF_ANY,
        TH14_CeladonCity_GameCorner_EventScript_GymGuy, &before));
    EXPECT_NE(before.data[0], 0);
    FlagSet(FLAG_BADGE01_GET); FlagSet(FLAG_BADGE02_GET); FlagSet(FLAG_BADGE03_GET);
    FlagSet(FLAG_TH14_SILPH_SCOPE);
    EXPECT(RunScriptImmediatelyUntilEffect(SCREFF_V1 | SCREFF_ANY,
        TH14_CeladonCity_GameCorner_EventScript_GymGuy, &unrelated));
    EXPECT_EQ(before.data[0], unrelated.data[0]);
    FlagSet(FLAG_BADGE04_GET);
    EXPECT(RunScriptImmediatelyUntilEffect(SCREFF_V1 | SCREFF_ANY,
        TH14_CeladonCity_GameCorner_EventScript_GymGuy, &after));
    EXPECT_NE(before.data[0], after.data[0]);
}

TEST("Three Horizons PT14 erika: fourth badge raises ordinary cap without changing first rosters or player")
{
    ResetErika();
    struct Pokemon generated[PARTY_SIZE], player[PARTY_SIZE];
    memcpy(player, gParties[B_TRAINER_PLAYER], sizeof(player));
    for (u16 id = TRAINER_TH14_GYM_KAY; id <= TRAINER_TH14_GYM_MARY; id++)
    {
        const struct Trainer *trainer = TH_TestGetActualTrainer(id);
        struct TrainerMon first[PARTY_SIZE];
        memcpy(first, trainer->party, trainer->partySize * sizeof(*first));
        u8 highest = 1;
        for (u32 slot = 0; slot < trainer->partySize; slot++) highest = max(highest, first[slot].lvl);
        for (u32 badges = 3; badges <= 4; badges++)
        {
            EXPECT(Test_TH14_CreateRematchParty(generated, trainer, id, 100, badges));
            u8 cap = badges == 3 ? 35 : 45;
            EXPECT_EQ(TH13_GetRematchLevel(100, highest, badges), cap);
            for (u32 slot = 0; slot < trainer->partySize; slot++)
                EXPECT_EQ(GetMonData(&generated[slot], MON_DATA_LEVEL), cap - (highest - first[slot].lvl));
            EXPECT_EQ(memcmp(first, trainer->party, trainer->partySize * sizeof(*first)), 0);
            EXPECT_EQ(memcmp(player, gParties[B_TRAINER_PLAYER], sizeof(player)), 0);
        }
    }
    const struct Trainer *erika = TH_TestGetActualTrainer(TRAINER_TH14_ERIKA);
    EXPECT_EQ((u32)erika->partySize, 3);
    EXPECT_EQ(erika->party[0].species, SPECIES_VICTREEBEL); EXPECT_EQ(erika->party[0].lvl, 29);
    EXPECT_EQ(erika->party[1].species, SPECIES_TANGELA); EXPECT_EQ(erika->party[1].lvl, 24);
    EXPECT_EQ(erika->party[2].species, SPECIES_VILEPLUME); EXPECT_EQ(erika->party[2].lvl, 29);
}

#endif
