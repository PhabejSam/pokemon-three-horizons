#include "three_horizons.h"
#include "global.h"
#include "test/test.h"
#include "event_data.h"
#include "item.h"
#include "pokemon.h"
#include "script.h"
#include "new_game.h"
#include "overworld.h"
#include "fieldmap.h"
#include "field_door.h"
#include "task.h"
#include "constants/metatile_labels.h"
#include "constants/maps.h"

#include "constants/three_horizons.h"
#include "constants/items.h"
#include "data.h"
#include "difficulty.h"
#include "string_util.h"
#include "event_object_movement.h"
#include "region_map.h"
#include "constants/opponents.h"
#include "constants/event_objects.h"

#if THREE_HORIZONS
TEST("Three Horizons assembled rival records have names pictures and correct parties")
{
    static const u16 species[] = {SPECIES_BULBASAUR, SPECIES_CHARMANDER, SPECIES_SQUIRTLE,
        SPECIES_CHIKORITA, SPECIES_CYNDAQUIL, SPECIES_TOTODILE,
        SPECIES_TREECKO, SPECIES_TORCHIC, SPECIES_MUDKIP};
    enum DifficultyLevel saved = GetCurrentDifficultyLevel();
    u32 i, difficulty;
    for (difficulty = DIFFICULTY_EASY; difficulty <= DIFFICULTY_HARD; difficulty++)
    {
        SetCurrentDifficultyLevel(difficulty);
        for (i = 0; i < ARRAY_COUNT(species); i++)
        {
            u16 id = TRAINER_TH_ROBIN_BULBASAUR + i;
            const struct TrainerMon *party = GetTrainerPartyFromId(id);
            EXPECT_EQ(StringCompare(GetTrainerNameFromId(id), COMPOUND_STRING("JOEY")), 0);
            EXPECT_EQ(GetTrainerPicFromId(id), TRAINER_PIC_YOUNGSTER);
            EXPECT_EQ(GetTrainerPartySizeFromId(id), 1);
            EXPECT(party != NULL);
            if (party != NULL)
            {
                EXPECT_EQ(party[0].species, species[i]);
                EXPECT_EQ(party[0].lvl, 5);
            }
        }
    }
    SetCurrentDifficultyLevel(saved);
}

TEST("Three Horizons Oak and Mom have assembled overworld graphics")
{
    static const u16 ids[] = {OBJ_EVENT_GFX_PROF_OAK, OBJ_EVENT_GFX_MOM_FRLG};
    u32 i;
    for (i = 0; i < ARRAY_COUNT(ids); i++)
    {
        const struct ObjectEventGraphicsInfo *gfx = GetObjectEventGraphicsInfo(ids[i]);
        EXPECT(gfx != NULL);
        if (gfx != NULL)
        {
            u8 previousPalette = IndexOfSpritePaletteTag(gfx->paletteTag);
            EXPECT_LT(LoadObjectEventPalette(gfx->paletteTag), 16);
            if (previousPalette == 0xFF)
                FreeSpritePaletteByTag(gfx->paletteTag);
            EXPECT_EQ(gfx->width, 16);
            EXPECT_EQ(gfx->height, 32);
            EXPECT(gfx->images != NULL);
            EXPECT(gfx->anims != NULL);
        }
    }
}

TEST("Three Horizons home and town display Pallet Town in assembled map headers")
{
    u8 name[32];
    const struct MapHeader *map;
    map = Overworld_GetMapHeaderByGroupAndId(MAP_GROUP(MAP_TH_PALLET), MAP_NUM(MAP_TH_PALLET));
    GetMapNameGeneric(name, map->regionMapSectionId);
    EXPECT_EQ(StringCompare(name, COMPOUND_STRING("PALLET TOWN")), 0);
    map = Overworld_GetMapHeaderByGroupAndId(MAP_GROUP(MAP_TH_HOME_2F), MAP_NUM(MAP_TH_HOME_2F));
    GetMapNameGeneric(name, map->regionMapSectionId);
    EXPECT_EQ(StringCompare(name, COMPOUND_STRING("PALLET TOWN")), 0);
}

static void ResetOpening(void)
{
    InitEventData();
    ZeroPlayerPartyMons();
    gPartiesCount[B_TRAINER_PLAYER] = 0;
    ClearBag();
    TH_InitNewGame();
}

TEST("Three Horizons initializes only project progress")
{
    VarSet(VAR_STARTER_MON, 2);
    VarSet(VAR_TH_STAGE, TH_STAGE_COMPLETE);
    VarSet(VAR_TH_FIRST_PARTNER, SPECIES_TREECKO);
    TH_InitNewGame();
    EXPECT_EQ(VarGet(VAR_TH_STAGE), TH_STAGE_HOME);
    EXPECT_EQ(VarGet(VAR_TH_FIRST_PARTNER), SPECIES_NONE);
    EXPECT_EQ(VarGet(VAR_STARTER_MON), 2);
}

TEST("Three Horizons grants all nine partners once with correct rival and level")
{
    static const u16 choices[][2] = {
        {SPECIES_BULBASAUR, SPECIES_CHARMANDER},
        {SPECIES_CHARMANDER, SPECIES_SQUIRTLE},
        {SPECIES_SQUIRTLE, SPECIES_BULBASAUR},
        {SPECIES_CHIKORITA, SPECIES_CYNDAQUIL},
        {SPECIES_CYNDAQUIL, SPECIES_TOTODILE},
        {SPECIES_TOTODILE, SPECIES_CHIKORITA},
        {SPECIES_TREECKO, SPECIES_TORCHIC},
        {SPECIES_TORCHIC, SPECIES_MUDKIP},
        {SPECIES_MUDKIP, SPECIES_TREECKO},
    };
    u32 i;
    for (i = 0; i < ARRAY_COUNT(choices); i++)
    {
        ResetOpening();
        VarSet(VAR_TH_STAGE, TH_STAGE_INVITED);
        EXPECT(TH_TryGiveStarter(choices[i][0]));
        EXPECT_EQ(gPartiesCount[B_TRAINER_PLAYER], 1);
        EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_SPECIES), choices[i][0]);
        EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_LEVEL), 5);
        EXPECT_EQ(VarGet(VAR_TH_RIVAL_PARTNER), choices[i][1]);
        EXPECT_EQ(VarGet(VAR_TH_FIRST_PARTNER), choices[i][0]);
        EXPECT(!TH_TryGiveStarter(SPECIES_MUDKIP));
        EXPECT_EQ(gPartiesCount[B_TRAINER_PLAYER], 1);
    }
}

TEST("Three Horizons rejects invalid, premature and occupied-party grants")
{
    ResetOpening();
    EXPECT(!TH_TryGiveStarter(SPECIES_BULBASAUR));
    VarSet(VAR_TH_STAGE, TH_STAGE_INVITED);
    EXPECT(!TH_TryGiveStarter(SPECIES_NONE));
    EXPECT(!TH_TryGiveStarter(SPECIES_PIDGEY));
    EXPECT(!TH_TryGiveStarter(65535));
    EXPECT_EQ(gPartiesCount[B_TRAINER_PLAYER], 0);
    EXPECT_EQ(VarGet(VAR_TH_STAGE), TH_STAGE_INVITED);
    gPartiesCount[B_TRAINER_PLAYER] = 1;
    EXPECT(!TH_TryGiveStarter(SPECIES_TREECKO));
    gPartiesCount[B_TRAINER_PLAYER] = 0;
}

TEST("Three Horizons rewards are once-only even after spending supplies")
{
    ResetOpening();
    EXPECT(!TH_TryGiveSupplies());
    VarSet(VAR_TH_STAGE, TH_STAGE_INVITED);
    EXPECT(TH_TryGiveStarter(SPECIES_CHIKORITA));
    EXPECT(TH_TryGiveSupplies());
    EXPECT(CheckBagHasItem(ITEM_POKE_BALL, 5));
    EXPECT(!CheckBagHasItem(ITEM_POKE_BALL, 6));
    EXPECT(CheckBagHasItem(ITEM_POTION, 2));
    EXPECT(!CheckBagHasItem(ITEM_POTION, 3));
    EXPECT(RemoveBagItem(ITEM_POKE_BALL, 5));
    EXPECT(TH_TryGiveSupplies());
    EXPECT(!CheckBagHasItem(ITEM_POKE_BALL, 1));
    EXPECT(FlagGet(FLAG_SYS_POKEDEX_GET));
}

TEST("Three Horizons battle completion is monotonic and idempotent")
{
    ResetOpening();
    TH_FinishRivalBattle();
    EXPECT_EQ(VarGet(VAR_TH_STAGE), TH_STAGE_HOME);
    VarSet(VAR_TH_STAGE, TH_STAGE_PARTNER);
    TH_FinishRivalBattle();
    EXPECT_EQ(VarGet(VAR_TH_STAGE), TH_STAGE_BATTLE_DONE);
    TH_FinishRivalBattle();
    EXPECT_EQ(VarGet(VAR_TH_STAGE), TH_STAGE_BATTLE_DONE);
    VarSet(VAR_TH_STAGE, TH_STAGE_COMPLETE);
    TH_FinishRivalBattle();
    EXPECT_EQ(VarGet(VAR_TH_STAGE), TH_STAGE_COMPLETE);
}

TEST("Three Horizons retries partial supplies without duplicating balls")
{
    u32 i;
    ResetOpening();
    VarSet(VAR_TH_STAGE, TH_STAGE_INVITED);
    EXPECT(TH_TryGiveStarter(SPECIES_TOTODILE));
    for (i = 0; i < gBagPockets[GetItemPocket(ITEM_POTION)].capacity; i++)
        EXPECT(AddBagItem(ITEM_POTION, MAX_BAG_ITEM_CAPACITY));
    EXPECT(!TH_TryGiveSupplies());
    EXPECT_EQ(VarGet(VAR_TH_SUPPLY_MASK), TH_SUPPLY_BALLS);
    EXPECT(CheckBagHasItem(ITEM_POKE_BALL, 5));
    EXPECT(RemoveBagItem(ITEM_POTION, 2));
    EXPECT(TH_TryGiveSupplies());
    EXPECT(!CheckBagHasItem(ITEM_POKE_BALL, 6));
    EXPECT_EQ(VarGet(VAR_TH_SUPPLY_MASK), TH_SUPPLIES_COMPLETE);
}

TEST("Three Horizons original partner survives party replacement")
{
    ResetOpening();
    VarSet(VAR_TH_STAGE, TH_STAGE_INVITED);
    EXPECT(TH_TryGiveStarter(SPECIES_MUDKIP));
    ZeroPlayerPartyMons();
    gPartiesCount[B_TRAINER_PLAYER] = 0;
    EXPECT_EQ(VarGet(VAR_TH_FIRST_PARTNER), SPECIES_MUDKIP);
    EXPECT_EQ(VarGet(VAR_TH_RIVAL_PARTNER), SPECIES_TREECKO);
    EXPECT(!TH_TryGiveStarter(SPECIES_CHIKORITA));
}

TEST("Three Horizons map transitions derive Robin visibility from saved progress")
{
    extern const u8 TH_Pallet_OnLoad[];
    extern const u8 TH_Lab_OnLoad[];
    ResetOpening();
    FlagSet(FLAG_TH_HIDE_ROBIN_TOWN);
    RunScriptImmediately(TH_Pallet_OnLoad);
    EXPECT(!FlagGet(FLAG_TH_HIDE_ROBIN_TOWN));
    VarSet(VAR_TH_STAGE, TH_STAGE_INVITED);
    RunScriptImmediately(TH_Pallet_OnLoad);
    EXPECT(FlagGet(FLAG_TH_HIDE_ROBIN_TOWN));
    RunScriptImmediately(TH_Lab_OnLoad);
    EXPECT(!FlagGet(FLAG_TH_HIDE_ROBIN_LAB));
    VarSet(VAR_TH_STAGE, TH_STAGE_PARTNER);
    RunScriptImmediately(TH_Lab_OnLoad);
    EXPECT(FlagGet(FLAG_TH_HIDE_ROBIN_LAB));
    EXPECT_EQ(VarGet(VAR_TH_STAGE), TH_STAGE_PARTNER);
}

TEST("Three Horizons new game starts and recovers at home")
{
    NewGameInitData();
    EXPECT_EQ(gSaveBlock1Ptr->location.mapGroup, MAP_GROUP(MAP_TH_HOME_2F));
    EXPECT_EQ(gSaveBlock1Ptr->location.mapNum, MAP_NUM(MAP_TH_HOME_2F));
    EXPECT_EQ(gSaveBlock1Ptr->lastHealLocation.mapGroup, MAP_GROUP(MAP_TH_HOME_1F));
    EXPECT_EQ(gSaveBlock1Ptr->lastHealLocation.mapNum, MAP_NUM(MAP_TH_HOME_1F));
    EXPECT_EQ(VarGet(VAR_TH_STAGE), TH_STAGE_HOME);
}

TEST("Three Horizons Pallet home and lab doors support opening and closing")
{
    const struct MapHeader savedHeader = gMapHeader;
    const struct BackupMapLayout savedLayout = gBackupMapLayout;
    u16 tiles[] = { METATILE_PalletTown_Door, METATILE_PalletTown_OaksLabDoor };
    u32 i;
    s8 task;
    gMapHeader = *Overworld_GetMapHeaderByGroupAndId(MAP_GROUP(MAP_TH_PALLET), MAP_NUM(MAP_TH_PALLET));
    gBackupMapLayout.width = ARRAY_COUNT(tiles);
    gBackupMapLayout.height = 1;
    gBackupMapLayout.map = tiles;
    for (i = 0; i < ARRAY_COUNT(tiles); i++)
    {
        task = FieldAnimateDoorOpen(i, 0);
        EXPECT_GE(task, 0);
        if (task >= 0)
            DestroyTask(task);
        task = FieldAnimateDoorClose(i, 0);
        EXPECT_GE(task, 0);
        if (task >= 0)
            DestroyTask(task);
    }
    gBackupMapLayout = savedLayout;
    gMapHeader = savedHeader;
}
TEST("Three Horizons customized grants preserve all chosen values and prevent duplicates")
{
    static const u16 species[] = {SPECIES_BULBASAUR, SPECIES_CHARMANDER, SPECIES_SQUIRTLE,
        SPECIES_CHIKORITA, SPECIES_CYNDAQUIL, SPECIES_TOTODILE,
        SPECIES_TREECKO, SPECIES_TORCHIC, SPECIES_MUDKIP};
    struct THPartnerOptions options = {.ivs = {31, 0, 7, 15, 23, 30}, .evs = {252, 0, 0, 6, 252, 0}};
    u32 i, stat, shiny;
    for (i = 0; i < ARRAY_COUNT(species); i++)
    {
        for (shiny = 0; shiny <= 1; shiny++)
        {
            struct Pokemon *mon = &gParties[B_TRAINER_PLAYER][0];
            ResetOpening();
            VarSet(VAR_TH_STAGE, TH_STAGE_INVITED);
            options.nature = i * 2 + shiny;
            options.shiny = shiny;
            EXPECT(TH_TryGiveConfiguredStarter(species[i], &options));
            EXPECT_EQ(gPartiesCount[B_TRAINER_PLAYER], 1);
            EXPECT_EQ(GetMonData(mon, MON_DATA_SPECIES), species[i]);
            EXPECT_EQ(GetMonData(mon, MON_DATA_LEVEL), 5);
            EXPECT_EQ(GetMonData(mon, MON_DATA_IS_SHINY), shiny);
            EXPECT_EQ(GetNature(mon), options.nature);
            EXPECT_EQ(GetMonData(mon, MON_DATA_HIDDEN_NATURE), options.nature);
            EXPECT_EQ(GetMonData(mon, MON_DATA_SANITY_IS_BAD_EGG), FALSE);
            EXPECT_GT(GetMonData(mon, MON_DATA_MOVE1), MOVE_NONE);
            EXPECT_EQ(GetMonData(mon, MON_DATA_HP), GetMonData(mon, MON_DATA_MAX_HP));
            for (stat = 0; stat < 6; stat++)
            {
                EXPECT_EQ(GetMonData(mon, MON_DATA_HP_IV + stat), options.ivs[stat]);
                EXPECT_EQ(GetMonData(mon, MON_DATA_HP_EV + stat), options.evs[stat]);
            }
            EXPECT(!TH_TryGiveConfiguredStarter(species[i], &options));
            EXPECT_EQ(gPartiesCount[B_TRAINER_PLAYER], 1);
            EXPECT_EQ(VarGet(VAR_TH_RIVAL_PARTNER), TH_GetRivalStarter(species[i]));
        }
    }
}

TEST("Three Horizons invalid partner settings never grant or advance the story")
{
    struct THPartnerOptions options = {0};
    ResetOpening();
    EXPECT(!TH_TryGiveConfiguredStarter(SPECIES_TOTODILE, &options));
    VarSet(VAR_TH_STAGE, TH_STAGE_INVITED);
    options.nature = NUM_NATURES;
    EXPECT(!TH_TryGiveConfiguredStarter(SPECIES_TOTODILE, &options));
    options.nature = 0;
    options.ivs[5] = 32;
    EXPECT(!TH_TryGiveConfiguredStarter(SPECIES_TOTODILE, &options));
    options.ivs[5] = 31;
    options.evs[0] = 253;
    EXPECT(!TH_TryGiveConfiguredStarter(SPECIES_TOTODILE, &options));
    options.evs[0] = 252;
    options.evs[1] = 252;
    options.evs[5] = 7;
    EXPECT(!TH_TryGiveConfiguredStarter(SPECIES_TOTODILE, &options));
    EXPECT_EQ(gPartiesCount[B_TRAINER_PLAYER], 0);
    EXPECT_EQ(VarGet(VAR_TH_STAGE), TH_STAGE_INVITED);
    EXPECT_EQ(VarGet(VAR_TH_FIRST_PARTNER), SPECIES_NONE);
    options.evs[5] = 6;
    EXPECT(TH_TryGiveConfiguredStarter(SPECIES_TOTODILE, &options));
}

TEST("Three Horizons every nature can be selected with normal coloration")
{
    struct THPartnerOptions options = {0};
    u32 nature;
    for (nature = 0; nature < NUM_NATURES; nature++)
    {
        ResetOpening();
        VarSet(VAR_TH_STAGE, TH_STAGE_INVITED);
        options.nature = nature;
        EXPECT(TH_TryGiveConfiguredStarter(SPECIES_CHIKORITA, &options));
        EXPECT_EQ(GetNature(&gParties[B_TRAINER_PLAYER][0]), nature);
        EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_IS_SHINY), FALSE);
    }
}
#endif
