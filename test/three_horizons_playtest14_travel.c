#include "global.h"
#include "test/test.h"
#include "test/battle.h"
#include "overworld.h"
#include "event_data.h"
#include "pokemon.h"
#include "data.h"
#include "trainer_util.h"
#include "three_horizons_helpers.h"
#include "pokedex.h"
#include "random.h"
#include "wild_encounter.h"
#include "battle_setup.h"
#include "trainer_see.h"
#include "palette.h"
#include "script.h"
#include "three_horizons_chapter14.h"
#include "three_horizons_rematches.h"
#include "three_horizons_research.h"
#include "constants/maps.h"
#include "constants/opponents.h"
#include "constants/three_horizons.h"
#include "constants/trainers.h"

#if THREE_HORIZONS
static void TravelMap(u16 map)
{
    gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(map);
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(map);
    gMapHeader = *Overworld_GetMapHeaderByGroupAndId(MAP_GROUP(map), MAP_NUM(map));
}

extern const u8 TH14_Route8_Eli[], TH14_Route8_Anne[];
extern const u8 TH14_Route8_Eli_Rematch[], TH14_Route8_Anne_Rematch[];
extern const u8 EventSnippet_DoTrainerBattle[], EventSnippet_DoRematchTrainerBattle[];
extern const u8 EventSnippet_NotEnoughMonsForDoubleBattle[];
static bool32 HasSnippet(const struct ScriptContext *ctx, const u8 *script)
{
    if (ctx->scriptPtr == script) return TRUE;
    for (u32 i = 0; i < ctx->stackDepth; i++)
        if (ctx->stack[i] == script) return TRUE;
    return FALSE;
}

TEST("Three Horizons PT14 travel: both twins configure first and rematch doubles with the two-usable-mon guard")
{
    const u8 *scripts[] = {TH14_Route8_Eli, TH14_Route8_Anne,
        TH14_Route8_Eli_Rematch, TH14_Route8_Anne_Rematch};
    const struct Trainer *twins = TH_TestGetActualTrainer(TRAINER_TH14_ROUTE8_ELI_ANNE);
    EXPECT_EQ((u32)twins->battleType, TRAINER_BATTLE_TYPE_DOUBLES);
    EXPECT_EQ((u32)twins->partySize, 2);
    for (u32 entry = 0; entry < ARRAY_COUNT(scripts); entry++)
        for (u32 usable = 0; usable <= 2; usable++)
        {
            InitEventData(); TH13_ResetRematches(); TravelMap(MAP_TH14_ROUTE8);
            memset(gParties[B_TRAINER_PLAYER], 0, sizeof(gParties[B_TRAINER_PLAYER]));
            for (u32 i = 0; i < usable; i++)
                CreateMonWithIVs(&gParties[B_TRAINER_PLAYER][i], SPECIES_BULBASAUR, 30, 123 + i, OTID_STRUCT_PLAYER_ID, 20);
            // A full party can still contain fewer than two usable battlers.
            for (u32 i = usable; i < PARTY_SIZE; i++)
            {
                CreateMonWithIVs(&gParties[B_TRAINER_PLAYER][i], SPECIES_BULBASAUR, 30, 123 + i, OTID_STRUCT_PLAYER_ID, 20);
                u32 value = i % 2 ? 0 : TRUE;
                SetMonData(&gParties[B_TRAINER_PLAYER][i], i % 2 ? MON_DATA_HP : MON_DATA_IS_EGG, &value);
            }
            CalculatePlayerPartyCount();
            gApproachingTrainerId = 0; gNoOfApproachingTrainers = 0;
            gSpecialVar_LastTalked = entry % 2 ? 13 : 12;
            if (entry >= 2)
            {
                SetTrainerFlag(TRAINER_TH14_ROUTE8_ELI_ANNE);
                EXPECT(TH13_SetRematchReady(TRAINER_TH14_ROUTE8_ELI_ANNE));
            }
            struct ScriptContext ctx = {0};
            struct Pokemon before[PARTY_SIZE];
            memcpy(before, gParties[B_TRAINER_PLAYER], sizeof(before));
            ctx.scriptPtr = scripts[entry] + TRAINERBATTLE_OPCODE_OFFSET;
            ConfigureTrainerBattle(&ctx);
            EXPECT_EQ(TRAINER_BATTLE_PARAM.opponentA, TRAINER_TH14_ROUTE8_ELI_ANNE);
            EXPECT(TRAINER_BATTLE_PARAM.isDoubleBattle);
            EXPECT_EQ((u32)TRAINER_BATTLE_PARAM.isRematch, entry >= 2);
            EXPECT_EQ(HasSnippet(&ctx, EventSnippet_NotEnoughMonsForDoubleBattle), usable < 2);
            EXPECT_EQ(HasSnippet(&ctx, EventSnippet_DoTrainerBattle), usable == 2 && entry < 2);
            EXPECT_EQ(HasSnippet(&ctx, EventSnippet_DoRematchTrainerBattle), usable == 2 && entry >= 2);
            EXPECT_EQ(HasTrainerBeenFought(TRAINER_TH14_ROUTE8_ELI_ANNE), entry >= 2);
            EXPECT_EQ(memcmp(before, gParties[B_TRAINER_PLAYER], sizeof(before)), 0);
            EXPECT_EQ(TH13_IsRematchReady(TRAINER_TH14_ROUTE8_ELI_ANNE), entry >= 2);
            ScriptContext_Init(); UnlockPlayerFieldControls();
        }
    TH13_ResetRematches();
}

TEST("Three Horizons PT14 travel: compiled travel maps have owned reciprocal warps and bounded layouts")
{
    static const u8 dimensions[][2] = {{72,20},{13,9},{13,10},{80,7},{13,10},{24,20},{13,9}};
    for (u32 index = 0; index < 7; index++)
    {
        const struct MapHeader *map = Overworld_GetMapHeaderByGroupAndId(TH14_MAP_GROUP, index);
        EXPECT(map != NULL);
        EXPECT(map->events != NULL);
        EXPECT(TH_IsProjectMap(TH14_MAP_GROUP, index));
        EXPECT_EQ(map->mapLayout->width, dimensions[index][0]);
        EXPECT_EQ(map->mapLayout->height, dimensions[index][1]);
        for (u32 i = 0; i < map->events->warpCount; i++)
        {
            const struct WarpEvent *warp = &map->events->warps[i];
            EXPECT_EQ(warp->mapGroup, TH14_MAP_GROUP);
            EXPECT_LT(warp->mapNum, TH14_MAP_COUNT);
            EXPECT_GE(warp->x, 0); EXPECT_LT(warp->x, map->mapLayout->width);
            EXPECT_GE(warp->y, 0); EXPECT_LT(warp->y, map->mapLayout->height);
            const struct MapHeader *dest = Overworld_GetMapHeaderByGroupAndId(warp->mapGroup, warp->mapNum);
            EXPECT_LT(warp->warpId, dest->events->warpCount);
            const struct WarpEvent *back = &dest->events->warps[warp->warpId];
            EXPECT_EQ(back->mapGroup, TH14_MAP_GROUP);
            EXPECT_EQ(back->mapNum, index);
        }
    }
}

TEST("Three Horizons PT14 travel: twins share one readiness slot and group changes retain only defeat history")
{
    InitEventData(); TH13_ResetRematches(); TravelMap(MAP_TH14_ROUTE8);
    EXPECT(!TH13_SetRematchReady(TRAINER_TH14_ROUTE8_ELI_ANNE));
    SetTrainerFlag(TRAINER_TH14_ROUTE8_ELI_ANNE);
    SetTrainerFlag(TRAINER_TH13_ROUTE11_DARIAN);
    EXPECT_EQ(TH13_GetMapTrainer(12), TRAINER_TH14_ROUTE8_ELI_ANNE);
    EXPECT_EQ(TH13_GetMapTrainer(13), TRAINER_TH14_ROUTE8_ELI_ANNE);
    EXPECT(TH13_SetRematchReady(TH13_GetMapTrainer(13)));
    EXPECT(TH13_IsRematchReady(TH13_GetMapTrainer(12)));
    for (u32 i = 0; i < MAX_REMATCH_ENTRIES; i++)
        EXPECT_EQ(gSaveBlock1Ptr->trainerRematches[i], i == 11);
    TravelMap(MAP_TH13_ROUTE11);
    EXPECT(!TH13_IsRematchReady(TRAINER_TH13_ROUTE11_DARIAN));
    EXPECT(TH13_SetRematchReady(TRAINER_TH13_ROUTE11_DARIAN));
    TravelMap(MAP_TH14_ROUTE8);
    EXPECT(!TH13_IsRematchReady(TRAINER_TH14_ROUTE8_ELI_ANNE));
    EXPECT(HasTrainerBeenFought(TRAINER_TH14_ROUTE8_ELI_ANNE));
    EXPECT(HasTrainerBeenFought(TRAINER_TH13_ROUTE11_DARIAN));
    EXPECT(TH13_SetRematchReady(TRAINER_TH14_ROUTE8_ELI_ANNE));
    TravelMap(MAP_TH14_ROUTE7);
    EXPECT(!TH13_MapHasRematchTrainers());
    EXPECT(!TH13_IsRematchReady(TRAINER_TH14_ROUTE8_ELI_ANNE));
    EXPECT_EQ(TH13_GetMapTrainer(13), TRAINER_NONE);
    TH13_ResetRematches();
}

TEST("Three Horizons PT14 travel: pending calls follow both project groups with safe input and pacing")
{
    MainCallback old = gMain.callback2;
    InitEventData(); TH_ResearchResetCallPacing(); ScriptContext_Init(); UnlockPlayerFieldControls();
    gMain.callback2 = CB2_Overworld; gMain.inBattle = FALSE;
    gMain.newKeys = gMain.heldKeys = 0; gPaletteFade.active = FALSE;
    gPlayerAvatar.preventStep = gPlayerAvatar.transitionFlags = 0;
    gPlayerAvatar.tileTransitionState = T_NOT_MOVING;
    gPlayerAvatar.runningState = NOT_MOVING;
    FlagSet(FLAG_TH13_GEAR); TravelMap(MAP_TH13_LAVENDER_TOWN);
    EXPECT(TH_ResearchQueueCall(TH_CALL_ELM)); EXPECT(TH_ResearchQueueCall(TH_CALL_BIRCH));
    EXPECT(TH_ResearchTryStartPendingCall());
    gSpecialVar_0x8004 = TH_CALL_ELM; TH_ScriptResearchCompleteCall();
    ScriptContext_Init(); UnlockPlayerFieldControls();
    EXPECT(!TH_ResearchTryStartPendingCall());
    TravelMap(MAP_TH14_ROUTE8);
    gMain.heldKeys = DPAD_LEFT;
    EXPECT(!TH_ResearchTryStartPendingCall());
    gMain.heldKeys = 0;
    EXPECT(TH_ResearchTryStartPendingCall());
    EXPECT(TH_ResearchCallDelivered(TH_CALL_ELM));
    EXPECT(!TH_ResearchCallDelivered(TH_CALL_BIRCH));
    gSpecialVar_0x8004 = TH_CALL_BIRCH; TH_ScriptResearchCompleteCall();
    ScriptContext_Init(); UnlockPlayerFieldControls();
    EXPECT(TH_ResearchQueueCall(TH_CALL_ROUTE10));
    for (u32 frame = 0; frame < 60; frame++) EXPECT(!TH_ResearchTryStartPendingCall());
    gSaveBlock1Ptr->pos.x += 8;
    EXPECT(TH_ResearchTryStartPendingCall());
    ScriptContext_Init(); UnlockPlayerFieldControls(); TH_ResearchResetCallPacing();
    // Upstream and out-of-range groups never start a project call.
    gSaveBlock1Ptr->location.mapGroup = 0;
    EXPECT(!TH_ResearchTryStartPendingCall());
    gSaveBlock1Ptr->location.mapGroup = TH14_MAP_GROUP;
    gSaveBlock1Ptr->location.mapNum = 127;
    EXPECT(!TH_ResearchTryStartPendingCall());
    gMain.callback2 = old;
}

static const struct { u16 species; u8 level; } sWild[2][12] = {
    {{SPECIES_PIDGEY,18},{SPECIES_MEOWTH,18},{SPECIES_GROWLITHE,16},{SPECIES_VULPIX,16},
     {SPECIES_PIDGEY,20},{SPECIES_MEOWTH,20},{SPECIES_EKANS,17},{SPECIES_SANDSHREW,17},
     {SPECIES_GROWLITHE,17},{SPECIES_VULPIX,17},{SPECIES_EKANS,19},{SPECIES_SANDSHREW,19}},
    {{SPECIES_PIDGEY,19},{SPECIES_MEOWTH,17},{SPECIES_ODDISH,19},{SPECIES_BELLSPROUT,19},
     {SPECIES_MEOWTH,18},{SPECIES_PIDGEY,22},{SPECIES_GROWLITHE,18},{SPECIES_VULPIX,18},
     {SPECIES_ODDISH,22},{SPECIES_BELLSPROUT,22},{SPECIES_GROWLITHE,20},{SPECIES_VULPIX,20}},
};

static void GenerateRouteWildMon(u32 route, u32 slot)
{
    TravelMap(route ? MAP_TH14_ROUTE7 : MAP_TH14_ROUTE8);
    VarSet(VAR_REPEL_STEP_COUNT, 0);
    u16 header = GetCurrentMapWildMonHeaderId();
    EXPECT_NE(header, HEADER_NONE);
    const struct WildEncounterTypes *types = &gWildMonHeaders[header].encounterTypes[TIME_OF_DAY_DEFAULT];
    EXPECT(types->landMonsInfo != NULL);
    EXPECT_EQ(types->landMonsInfo->encounterRate, 21);
    EXPECT(types->waterMonsInfo == NULL);
    EXPECT(types->fishingMonsInfo == NULL);
    EXPECT_EQ(types->landMonsInfo->wildPokemon[slot].species, sWild[route][slot].species);
    EXPECT_EQ(GetMonAbility(&gParties[B_TRAINER_PLAYER][0]), ABILITY_OVERGROW);
    // Select a seed for a particular native weighted slot; reseed before the
    // production generator. Overgrow lead has no encounter-selection override.
    u32 seed;
    for (seed = 0; seed < 65536; seed++)
    {
        SeedRng(seed);
        if (ChooseWildMonIndex_Land() == slot) break;
    }
    EXPECT_LT(seed, 65536);
    SeedRng(seed);
    rng_value_t selected = gRngValue;
    EXPECT_EQ(ChooseWildMonIndex_Land(), slot);
    gRngValue = selected;
    EXPECT(TryGenerateWildMon(types->landMonsInfo, WILD_AREA_LAND, 0));
    struct Pokemon *mon = &gParties[B_TRAINER_OPPONENT_A][0];
    u16 species = GetMonData(mon, MON_DATA_SPECIES);
    EXPECT_EQ(species, sWild[route][slot].species);
    EXPECT_EQ(GetMonData(mon, MON_DATA_LEVEL), sWild[route][slot].level);
    EXPECT_GT(GetMonData(mon, MON_DATA_MAX_HP), 0);
    u16 ability = GetMonAbility(mon);
    EXPECT(ability != ABILITY_NONE);
    EXPECT(ability == gSpeciesInfo[species].abilities[0] || ability == gSpeciesInfo[species].abilities[1] || ability == gSpeciesInfo[species].abilities[2]);
    EXPECT_NE(GetMonData(mon, MON_DATA_MOVE1), MOVE_NONE);
    for (u32 stat = 0; stat < 6; stat++)
    {
        EXPECT_LE(GetMonData(mon, MON_DATA_HP_IV + stat), 31);
        EXPECT_EQ(GetMonData(mon, MON_DATA_HP_EV + stat), 0);
    }
}

WILD_BATTLE_TEST("Three Horizons PT14 travel: all authored land slots generate legal Pokemon and permit normal capture")
{
    u32 route = 0, slot = 0;
    for (u32 r = 0; r < 2; r++)
        for (u32 s = 0; s < 12; s++)
            PARAMETRIZE { route = r; slot = s; }
    GIVEN {
        PLAYER(SPECIES_BULBASAUR) { Ability(ABILITY_OVERGROW); Level(30); }
        OPPONENT(sWild[route][slot].species) { Level(sWild[route][slot].level); }
        // GIVEN builds recorded parties; the field generator reads live parties.
        // Capture the actual generated mon, including its randomized legal data.
        memcpy(gParties[B_TRAINER_PLAYER], PLAYER_PARTY, sizeof(gParties[B_TRAINER_PLAYER]));
        CalculatePlayerPartyCount();
        // A previous parameter can leave VBlankCB_Battle installed while GIVEN
        // clears RECORDED. Suspend that battle callback for this field fixture
        // so it cannot advance the seed; restore it before the actual battle.
        IntrCallback oldVBlank = gMain.vblankCallback;
        SetVBlankCallback(NULL);
        GenerateRouteWildMon(route, slot);
        SetVBlankCallback(oldVBlank);
        memcpy(&OPPONENT_PARTY[0], &gParties[B_TRAINER_OPPONENT_A][0], sizeof(struct Pokemon));
    } WHEN {
        TURN { USE_ITEM(player, ITEM_MASTER_BALL); MOVE(opponent, moveSlot: 0); }
    } THEN {
        EXPECT_EQ(gBattleOutcome, B_OUTCOME_CAUGHT);
        EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][1], MON_DATA_SPECIES), sWild[route][slot].species);
        EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][1], MON_DATA_LEVEL), sWild[route][slot].level);
    }
}
#endif
