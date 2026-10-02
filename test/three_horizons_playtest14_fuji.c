#include "global.h"
#include "test/test.h"
#include "event_data.h"
#include "item.h"
#include "malloc.h"
#include "battle.h"
#include "overworld.h"
#include "script.h"
#include "text.h"
#include "string_util.h"
#include "three_horizons_research.h"
#include "battle_setup.h"
#include "three_horizons_chapter14.h"
#include "three_horizons_helpers.h"
#include "three_horizons_rematches.h"
#include "constants/maps.h"
#include "constants/opponents.h"
#include "constants/three_horizons.h"

#if THREE_HORIZONS
extern const u8 TH14_Fuji_CanRescue[], TH14_Fuji_TowerThanks[], TH13_GiveResearchGear[];
extern const u8 TH14_Tower7F_Grunt1[], TH14_Tower7F_Grunt2[], TH14_Tower7F_Grunt3[];
extern const u8 TH14_Fuji_HomeLoad[], TH14_Fuji_CanResumeHome[];
void Test_TH14_EndTrainerBattle(void);

TEST("Three Horizons PT14 fuji: destination handoff only resumes pending rescue at authored arrival")
{
    const s16 positions[][2] = {{3,4},{4,7},{3,5},{2,4}};
    for (u32 state = 0; state < 4; state++)
    {
        for (u32 i = 0; i < ARRAY_COUNT(positions); i++)
        {
            InitEventData();
            if (state & 1) FlagSet(FLAG_TH14_FUJI_RESCUED);
            if (state & 2) FlagSet(FLAG_TH14_POKE_FLUTE);
            gSaveBlock1Ptr->pos.x = positions[i][0];
            gSaveBlock1Ptr->pos.y = positions[i][1];
            u8 flags[NUM_FLAG_BYTES]; memcpy(flags, gSaveBlock1Ptr->flags, sizeof(flags));
            VarSet(VAR_TEMP_1, 1);
            RunScriptImmediately(TH14_Fuji_HomeLoad);
            EXPECT_EQ(VarGet(VAR_TEMP_1), 0);
            RunScriptImmediately(TH14_Fuji_CanResumeHome);
            EXPECT_EQ(gSpecialVar_Result, state == 1 && i == 0);
            EXPECT_EQ(memcmp(flags, gSaveBlock1Ptr->flags, sizeof(flags)), 0);
        }
    }
}

TEST("Three Horizons PT14 fuji: compiled rescue predicate requires mother and every upper trainer")
{
    for (u32 state = 0; state < 16; state++)
    {
        InitEventData();
        if (state & 8) FlagSet(FLAG_TH14_MOTHER_RESOLVED);
        for (u32 i = 0; i < 3; i++) if (state & (1 << i)) SetTrainerFlag(TRAINER_TH14_TOWER7F_GRUNT1+i);
        u8 flags[NUM_FLAG_BYTES]; memcpy(flags, gSaveBlock1Ptr->flags, sizeof(flags));
        RunScriptImmediately(TH14_Fuji_CanRescue);
        EXPECT_EQ(gSpecialVar_Result, state == 15);
        EXPECT_EQ(memcmp(flags, gSaveBlock1Ptr->flags, sizeof(flags)), 0);
    }
    // GetStringWidth ignores prompt-clear/scroll instead of breaking lines.
    // Normalize those real dialogue line boundaries in this test-only copy.
    u8 text[512];
    EXPECT_LT(StringLength(TH14_Fuji_TowerThanks), sizeof(text));
    StringCopy(text, TH14_Fuji_TowerThanks);
    for (u32 i = 0; text[i] != EOS; i++)
        if (text[i] == CHAR_PROMPT_CLEAR || text[i] == CHAR_PROMPT_SCROLL) text[i] = CHAR_NEWLINE;
    SetDefaultFontsPointer(); EXPECT_LE(GetStringWidth(FONT_NORMAL, text, 0), 208);
}

TEST("Three Horizons PT14 fuji: actual upper trainer loss retry and reload cannot rescue prematurely")
{
    MainCallback saved = gMain.callback2;
    const u8 *scripts[] = {TH14_Tower7F_Grunt1,TH14_Tower7F_Grunt2,TH14_Tower7F_Grunt3};
    InitEventData(); FlagSet(FLAG_TH14_MOTHER_RESOLVED); FlagSet(FLAG_TH14_PHOTO_MOTHER);
    SetTrainerFlag(TRAINER_TH13_POKEMONTOWER_6F_EMILIA);
    gSaveBlock1Ptr->location.mapGroup = TH14_MAP_GROUP;
    gSaveBlock1Ptr->location.mapNum = TH14_MAP_TOWER_7F;
    gMapHeader = *Overworld_GetMapHeaderByGroupAndId(TH14_MAP_GROUP, TH14_MAP_TOWER_7F);
    for (u32 i = 0; i < 3; i++)
    {
        for (u32 win = 0; win < 2; win++)
        {
            gSpecialVar_LastTalked = i + 2;
            struct ScriptContext ctx = {0}; ctx.scriptPtr = scripts[i] + TRAINERBATTLE_OPCODE_OFFSET;
            ConfigureTrainerBattle(&ctx);
            EXPECT_EQ(TRAINER_BATTLE_PARAM.opponentA, TRAINER_TH14_TOWER7F_GRUNT1+i);
            EXPECT(!TRAINER_BATTLE_PARAM.isRematch);
            gBattleTypeFlags = BATTLE_TYPE_TRAINER; gBattleOutcome = win ? B_OUTCOME_WON : B_OUTCOME_LOST;
            Test_TH14_EndTrainerBattle(); MainCallback selected = gMain.callback2; SetMainCallback2(saved);
            EXPECT_EQ(selected, win ? CB2_ReturnToFieldContinueScriptPlayMapMusic : CB2_WhiteOut);
            EXPECT_EQ(HasTrainerBeenFought(TRAINER_TH14_TOWER7F_GRUNT1+i), win);
            ClearTempFieldEventData(); RunScriptImmediately(TH14_Fuji_CanRescue);
            EXPECT_EQ(gSpecialVar_Result, win && i == 2);
            EXPECT(!FlagGet(FLAG_TH14_FUJI_RESCUED)); EXPECT(!FlagGet(FLAG_TH14_POKE_FLUTE));
            EXPECT(FlagGet(FLAG_TH14_PHOTO_MOTHER)); EXPECT(HasTrainerBeenFought(TRAINER_TH13_POKEMONTOWER_6F_EMILIA));
            ScriptContext_Init(); UnlockPlayerFieldControls();
        }
    }
}

TEST("Three Horizons PT14 fuji: real Gear grant cannot manufacture past photos and equipped repeat is inert")
{
    InitEventData(); RunScriptImmediately(TH13_GiveResearchGear);
    EXPECT(FlagGet(FLAG_TH13_GEAR)); EXPECT(TH_ResearchCallDelivered(TH_CALL_ACTIVATION));
    EXPECT_EQ(TH_ResearchNextPendingCall(), TH_RESEARCH_CALL_NONE);
    for (u32 i = 0; i < TH_RESEARCH_ENTRY_COUNT; i++) EXPECT(!TH_ResearchHasEntry(i));
    for (u32 i = 0; i < TH_RESEARCH_PHOTO_COUNT; i++) EXPECT(!TH_ResearchHasPhoto(i));
    u8 flags[NUM_FLAG_BYTES]; memcpy(flags, gSaveBlock1Ptr->flags, sizeof(flags));
    RunScriptImmediately(TH13_GiveResearchGear);
    EXPECT_EQ(memcmp(flags, gSaveBlock1Ptr->flags, sizeof(flags)), 0);
    TH_ResearchResetCallPacing();
}

TEST("Three Horizons PT14 fuji: full Flute pocket retry and owned Bag PC avoid duplicates")
{
    InitEventData(); ClearBag();
    memset(gSaveBlock1Ptr->pcItems, 0, sizeof(gSaveBlock1Ptr->pcItems));
    FlagSet(FLAG_TH14_FUJI_RESCUED);
    struct BagPocket *pocket = &gBagPockets[POCKET_KEY_ITEMS];
    for (u32 i = 0; i < pocket->capacity; i++) BagPocket_SetSlotItemIdAndCount(pocket, i, ITEM_BICYCLE, 1);
    ASSUME(!CheckBagHasSpace(ITEM_POKE_FLUTE, 1));
    struct SaveBlock1 *before = Alloc(sizeof(*before));
    EXPECT(before != NULL); memcpy(before, gSaveBlock1Ptr, sizeof(*before));
    EXPECT_EQ(TH14_TryGiveUniqueItem(ITEM_POKE_FLUTE, FLAG_TH14_POKE_FLUTE), TH14_GIFT_NO_ROOM);
    EXPECT_EQ(memcmp(before, gSaveBlock1Ptr, sizeof(*before)), 0);
    BagPocket_SetSlotItemIdAndCount(pocket, pocket->capacity - 1, ITEM_NONE, 0);
    EXPECT_EQ(TH14_TryGiveUniqueItem(ITEM_POKE_FLUTE, FLAG_TH14_POKE_FLUTE), TH14_GIFT_GIVEN);
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_POKE_FLUTE), 1);
    EXPECT(FlagGet(FLAG_TH14_POKE_FLUTE)); EXPECT(FlagGet(FLAG_TH14_FUJI_RESCUED));
    for (u32 where = 0; where < 2; where++)
    {
        FlagClear(FLAG_TH14_POKE_FLUTE);
        if (where) { EXPECT(RemoveBagItem(ITEM_POKE_FLUTE, 1)); EXPECT(AddPCItem(ITEM_POKE_FLUTE, 1)); }
        EXPECT_EQ(TH14_TryGiveUniqueItem(ITEM_POKE_FLUTE, FLAG_TH14_POKE_FLUTE), TH14_GIFT_ALREADY_OWNED);
        EXPECT(FlagGet(FLAG_TH14_POKE_FLUTE));
        EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_POKE_FLUTE), where ? 0 : 1);
    }
    memcpy(before, gSaveBlock1Ptr, sizeof(*before));
    EXPECT_EQ(TH14_TryGiveUniqueItem(ITEM_POKE_FLUTE, FLAG_TH14_ITEMFINDER), TH14_GIFT_NO_ROOM);
    EXPECT_EQ(memcmp(before, gSaveBlock1Ptr, sizeof(*before)), 0); Free(before);
}

TEST("Three Horizons PT14 fuji: home and defeated Rockets spawn only from authoritative receipts")
{
    InitEventData();
    EXPECT(!TH14_ShouldSpawnObject(MAP_GROUP(MAP_TH13_LAVENDER_TOWN_VOLUNTEER_POKEMON_HOUSE), MAP_NUM(MAP_TH13_LAVENDER_TOWN_VOLUNTEER_POKEMON_HOUSE), 6));
    FlagSet(FLAG_TH14_FUJI_RESCUED);
    EXPECT(TH14_ShouldSpawnObject(MAP_GROUP(MAP_TH13_LAVENDER_TOWN_VOLUNTEER_POKEMON_HOUSE), MAP_NUM(MAP_TH13_LAVENDER_TOWN_VOLUNTEER_POKEMON_HOUSE), 6));
    for (u32 i = 0; i < 3; i++)
    {
        EXPECT(TH14_ShouldSpawnObject(TH14_MAP_GROUP, TH14_MAP_TOWER_7F, 2+i));
        SetTrainerFlag(TRAINER_TH14_TOWER7F_GRUNT1+i);
        EXPECT(!TH14_ShouldSpawnObject(TH14_MAP_GROUP, TH14_MAP_TOWER_7F, 2+i));
        EXPECT(!TH13_SetRematchReady(TRAINER_TH14_TOWER7F_GRUNT1+i));
        EXPECT(HasTrainerBeenFought(TRAINER_TH14_TOWER7F_GRUNT1+i));
    }
    EXPECT(TH14_ShouldSpawnObject(MAP_GROUP(MAP_LAVENDER_TOWN_VOLUNTEER_POKEMON_HOUSE), MAP_NUM(MAP_LAVENDER_TOWN_VOLUNTEER_POKEMON_HOUSE), 6));
}

TEST("Three Horizons PT14 fuji: upper Rocket first parties preserve donor roster")
{
    const u16 species[3][4] = {{SPECIES_ZUBAT,SPECIES_ZUBAT,SPECIES_GOLBAT},{SPECIES_KOFFING,SPECIES_DROWZEE},{SPECIES_ZUBAT,SPECIES_RATTATA,SPECIES_RATICATE,SPECIES_ZUBAT}};
    const u8 sizes[] = {3,2,4}, levels[] = {25,26,23};
    for (u32 i = 0; i < 3; i++)
    {
        const struct Trainer *t = TH_TestGetActualTrainer(TRAINER_TH14_TOWER7F_GRUNT1+i);
        EXPECT_EQ((u32)t->partySize, sizes[i]);
        for (u32 slot = 0; slot < sizes[i] && slot < t->partySize; slot++)
        { EXPECT_EQ(t->party[slot].species, species[i][slot]); EXPECT_EQ(t->party[slot].lvl, levels[i]); }
    }
}
#endif
