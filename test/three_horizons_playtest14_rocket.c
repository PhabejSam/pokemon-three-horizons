#include "global.h"
#include "test/test.h"
#include "battle.h"
#include "battle_setup.h"
#include "event_data.h"
#include "item.h"
#include "malloc.h"
#include "pokemon.h"
#include "three_horizons_helpers.h"
#include "three_horizons_chapter14.h"
#include "constants/opponents.h"
#include "constants/three_horizons.h"
#include "overworld.h"
#include "script.h"
#include "trainer_see.h"
#include "three_horizons_rematches.h"
#include "constants/maps.h"

#if THREE_HORIZONS
static void ResetRocket(void)
{
    InitEventData(); ClearBag();
    memset(gSaveBlock1Ptr->pcItems, 0, sizeof(gSaveBlock1Ptr->pcItems));
    TH13_ResetRematches();
    gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(MAP_TH14_ROCKET_HIDEOUT_B4F);
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(MAP_TH14_ROCKET_HIDEOUT_B4F);
    gMapHeader = *Overworld_GetMapHeaderByGroupAndId(TH14_MAP_GROUP, MAP_NUM(MAP_TH14_ROCKET_HIDEOUT_B4F));
}

extern const u8 TH14_RocketTrioBattle[], EventSnippet_DoTrainerBattle[];
extern const u8 EventSnippet_NotEnoughMonsForDoubleBattle[];
void Test_TH14_EndTrainerBattle(void);

static void RocketParty(u32 usable)
{
    memset(gParties[B_TRAINER_PLAYER], 0, sizeof(gParties[B_TRAINER_PLAYER]));
    for (u32 i = 0; i < PARTY_SIZE; i++)
    {
        CreateMonWithIVs(&gParties[B_TRAINER_PLAYER][i], SPECIES_BULBASAUR, 30, 123+i, OTID_STRUCT_PLAYER_ID, 20);
        if (i >= usable)
        {
            u32 value = i % 2 ? 0 : TRUE;
            SetMonData(&gParties[B_TRAINER_PLAYER][i], i % 2 ? MON_DATA_HP : MON_DATA_IS_EGG, &value);
        }
    }
    CalculatePlayerPartyCount();
}

static bool32 RocketHasSnippet(const struct ScriptContext *ctx, const u8 *script)
{
    if (ctx->scriptPtr == script) return TRUE;
    for (u32 i = 0; i < ctx->stackDepth; i++) if (ctx->stack[i] == script) return TRUE;
    return FALSE;
}

static void ConfigureRocket(struct ScriptContext *ctx)
{
    gSpecialVar_LastTalked = 10;
    ctx->scriptPtr = TH14_RocketTrioBattle + TRAINERBATTLE_OPCODE_OFFSET;
    ConfigureTrainerBattle(ctx);
}

TEST("Three Horizons PT14 rocket: compiled pair requires two usable non-eggs and has separate identities")
{
    for (u32 usable = 0; usable <= 2; usable++)
    {
        ResetRocket(); RocketParty(usable);
        struct Pokemon before[PARTY_SIZE];
        memcpy(before, gParties[B_TRAINER_PLAYER], sizeof(before));
        TH14_BeginRocketPair();
        EXPECT_EQ(TRAINER_BATTLE_PARAM.opponentA, TRAINER_TH14_JESSIE);
        EXPECT_EQ(TRAINER_BATTLE_PARAM.opponentB, TRAINER_TH14_JAMES);
        struct ScriptContext ctx = {0}; ConfigureRocket(&ctx);
        EXPECT_EQ(TRAINER_BATTLE_PARAM.opponentA, TRAINER_TH14_JESSIE);
        EXPECT_EQ(TRAINER_BATTLE_PARAM.opponentB, TRAINER_TH14_JAMES);
        EXPECT_EQ((u32)TRAINER_BATTLE_PARAM.objEventLocalIdA, 10);
        EXPECT_EQ((u32)TRAINER_BATTLE_PARAM.objEventLocalIdB, 11);
        EXPECT(TRAINER_BATTLE_PARAM.isDoubleBattle); EXPECT(!TRAINER_BATTLE_PARAM.isRematch);
        EXPECT_EQ(RocketHasSnippet(&ctx, EventSnippet_NotEnoughMonsForDoubleBattle), usable < 2);
        EXPECT_EQ(RocketHasSnippet(&ctx, EventSnippet_DoTrainerBattle), usable == 2);
        if (usable == 2) EXPECT_EQ(gNoOfApproachingTrainers, 2);
        EXPECT_EQ(memcmp(before, gParties[B_TRAINER_PLAYER], sizeof(before)), 0);
        EXPECT(!HasTrainerBeenFought(TRAINER_TH14_JESSIE)); EXPECT(!HasTrainerBeenFought(TRAINER_TH14_JAMES));
        EXPECT(!FlagGet(FLAG_TH14_TRIO_DEFEATED));
        ScriptContext_Init(); UnlockPlayerFieldControls();
    }
}

TEST("Three Horizons PT14 rocket: actual loss retains scene and retry win records both histories once")
{
    MainCallback saved = gMain.callback2;
    ResetRocket(); RocketParty(2);
    SetTrainerFlag(TRAINER_TH14_HIDEOUT_B4F_GRUNT2); SetTrainerFlag(TRAINER_TH14_HIDEOUT_B4F_GRUNT3);
    SetTrainerFlag(TRAINER_TH11_JESSIE); SetTrainerFlag(TRAINER_TH11_JAMES);
    for (u32 attempt = 0; attempt < 2; attempt++)
    {
        TH14_BeginRocketPair(); struct ScriptContext ctx = {0}; ConfigureRocket(&ctx);
        gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_DOUBLE | BATTLE_TYPE_TWO_OPPONENTS;
        gBattleOutcome = attempt ? B_OUTCOME_WON : B_OUTCOME_LOST;
        Test_TH14_EndTrainerBattle(); MainCallback selected = gMain.callback2; SetMainCallback2(saved);
        EXPECT_EQ(selected, attempt ? CB2_ReturnToFieldContinueScriptPlayMapMusic : CB2_WhiteOut);
        TH14_CompleteRocketPair(); EXPECT_EQ(gSpecialVar_Result, attempt);
        EXPECT_EQ(FlagGet(FLAG_TH14_TRIO_DEFEATED), attempt);
        EXPECT_EQ(HasTrainerBeenFought(TRAINER_TH14_JESSIE), attempt);
        EXPECT_EQ(HasTrainerBeenFought(TRAINER_TH14_JAMES), attempt);
        EXPECT(HasTrainerBeenFought(TRAINER_TH11_JESSIE)); EXPECT(HasTrainerBeenFought(TRAINER_TH11_JAMES));
        EXPECT(HasTrainerBeenFought(TRAINER_TH14_HIDEOUT_B4F_GRUNT2)); EXPECT(HasTrainerBeenFought(TRAINER_TH14_HIDEOUT_B4F_GRUNT3));
        EXPECT(!HasTrainerBeenFought(TRAINER_TH14_GIOVANNI)); EXPECT(!FlagGet(FLAG_BADGE04_GET));
        ScriptContext_Init(); UnlockPlayerFieldControls();
    }
    struct SaveBlock1 *before = Alloc(sizeof(*before)); EXPECT(before != NULL);
    memcpy(before, gSaveBlock1Ptr, sizeof(*before));
    TH14_BeginRocketPair(); TH14_CompleteRocketPair(); TH13_ResetRematches(); ClearTempFieldEventData();
    EXPECT_EQ(memcmp(before, gSaveBlock1Ptr, sizeof(*before)), 0); Free(before);
}

TEST("Three Horizons PT14 rocket: partial stale or foreign outcomes never complete trio")
{
    ResetRocket(); RocketParty(2); TH14_BeginRocketPair();
    gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_DOUBLE | BATTLE_TYPE_TWO_OPPONENTS;
    gBattleOutcome = B_OUTCOME_WON;
    SetTrainerFlag(TRAINER_TH14_JESSIE);
    TH14_CompleteRocketPair(); EXPECT(!gSpecialVar_Result); EXPECT(!FlagGet(FLAG_TH14_TRIO_DEFEATED));
    TH14_BeginRocketPair(); EXPECT(!HasTrainerBeenFought(TRAINER_TH14_JESSIE));
    SetTrainerFlag(TRAINER_TH14_JESSIE); SetTrainerFlag(TRAINER_TH14_JAMES);
    for (u32 variant = 0; variant < 4; variant++)
    {
        gBattleOutcome = variant == 0 ? B_OUTCOME_LOST : B_OUTCOME_WON;
        TRAINER_BATTLE_PARAM.opponentB = variant == 1 ? TRAINER_TH11_JAMES : TRAINER_TH14_JAMES;
        TRAINER_BATTLE_PARAM.isRematch = variant == 2;
        gBattleTypeFlags = BATTLE_TYPE_TRAINER | (variant == 3 ? 0 : BATTLE_TYPE_TWO_OPPONENTS);
        TH14_CompleteRocketPair(); EXPECT(!gSpecialVar_Result); EXPECT(!FlagGet(FLAG_TH14_TRIO_DEFEATED));
    }
}

TEST("Three Horizons PT14 rocket: story trio and boss never consume ordinary rematch slots")
{
    ResetRocket();
    for (u32 id = TRAINER_TH14_GIOVANNI; id <= TRAINER_TH14_JAMES; id++)
    {
        SetTrainerFlag(id); EXPECT(!TH13_SetRematchReady(id)); EXPECT(!TH13_IsRematchReady(id));
    }
    const u8 locals[] = {1,10,11,12};
    for (u32 i = 0; i < ARRAY_COUNT(locals); i++) EXPECT_EQ(TH13_GetMapTrainer(locals[i]), TRAINER_NONE);
    for (u32 i = 0; i < MAX_REMATCH_ENTRIES; i++) EXPECT_EQ(gSaveBlock1Ptr->trainerRematches[i], 0);
}

TEST("Three Horizons PT14 rocket: Giovanni victory survives full Scope pocket and retry gives exactly one")
{
    ResetRocket(); SetTrainerFlag(TRAINER_TH14_GIOVANNI);
    struct BagPocket *pocket = &gBagPockets[POCKET_KEY_ITEMS];
    for (u32 i = 0; i < pocket->capacity; i++)
        BagPocket_SetSlotItemIdAndCount(pocket, i, ITEM_BICYCLE, 1);
    ASSUME(!CheckBagHasSpace(ITEM_SILPH_SCOPE, 1));
    struct SaveBlock1 *before = Alloc(sizeof(*before)); EXPECT(before != NULL);
    memcpy(before, gSaveBlock1Ptr, sizeof(*before));
    EXPECT_EQ(TH14_TryGiveUniqueItem(ITEM_SILPH_SCOPE, FLAG_TH14_SILPH_SCOPE), TH14_GIFT_NO_ROOM);
    EXPECT_EQ(memcmp(before, gSaveBlock1Ptr, sizeof(*before)), 0);
    EXPECT(HasTrainerBeenFought(TRAINER_TH14_GIOVANNI)); EXPECT(!FlagGet(FLAG_TH14_SILPH_SCOPE));
    BagPocket_SetSlotItemIdAndCount(pocket, pocket->capacity - 1, ITEM_NONE, 0);
    EXPECT_EQ(TH14_TryGiveUniqueItem(ITEM_SILPH_SCOPE, FLAG_TH14_SILPH_SCOPE), TH14_GIFT_GIVEN);
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_SILPH_SCOPE), 1);
    EXPECT(FlagGet(FLAG_TH14_SILPH_SCOPE));
    memcpy(before, gSaveBlock1Ptr, sizeof(*before));
    for (u32 i = 0; i < 3; i++)
        EXPECT_EQ(TH14_TryGiveUniqueItem(ITEM_SILPH_SCOPE, FLAG_TH14_SILPH_SCOPE), TH14_GIFT_ALREADY_OWNED);
    EXPECT_EQ(memcmp(before, gSaveBlock1Ptr, sizeof(*before)), 0);
    EXPECT(!FlagGet(FLAG_BADGE04_GET)); Free(before);
}

TEST("Three Horizons PT14 rocket: first parties use approved Giovanni and distinct Jessie James identities")
{
    const u16 ids[] = {TRAINER_TH14_GIOVANNI, TRAINER_TH14_JESSIE, TRAINER_TH14_JAMES};
    const u16 species[][3] = {{SPECIES_ONIX,SPECIES_RHYHORN,SPECIES_KANGASKHAN},{SPECIES_ARBOK},{SPECIES_KOFFING}};
    const u8 levels[][3] = {{25,24,29},{28},{28}};
    const u8 sizes[] = {3,1,1};
    for (u32 i = 0; i < 3; i++)
    {
        const struct Trainer *t = TH_TestGetActualTrainer(ids[i]);
        EXPECT_EQ((u32)t->partySize, sizes[i]);
        for (u32 slot = 0; slot < sizes[i]; slot++)
        {
            EXPECT_EQ(t->party[slot].species, species[i][slot]);
            EXPECT_EQ(t->party[slot].lvl, levels[i][slot]);
        }
    }
}
#endif
