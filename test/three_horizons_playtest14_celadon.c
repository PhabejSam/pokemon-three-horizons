#include "global.h"
#include "test/test.h"
#include "event_data.h"
#include "event_scripts.h"
#include "fieldmap.h"
#include "bg.h"
#include "heal_location.h"
#include "malloc.h"
#include "overworld.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "pokedex.h"
#include "script.h"
#include "three_horizons_chapter14.h"
#include "constants/heal_locations.h"
#include "constants/event_objects.h"
#include "constants/layouts.h"
#include "constants/maps.h"
#include "constants/metatile_behaviors.h"
#include "constants/three_horizons.h"
#include "constants/vars.h"

#if THREE_HORIZONS
TEST("Three Horizons PT14 celadon: all city maps compile with distinct real layouts")
{
    for (u32 map = 7; map <= 27; map++)
    {
        const struct MapHeader *header = Overworld_GetMapHeaderByGroupAndId(TH14_MAP_GROUP, map);
        EXPECT(header != NULL);
        EXPECT(header->mapLayout != NULL);
        EXPECT(header->events != NULL);
        EXPECT(header->mapLayout->width > 0);
        EXPECT(header->mapLayout->height > 0);
        for (u32 prior = 7; prior < map; prior++)
            EXPECT(header->mapLayoutId != Overworld_GetMapHeaderByGroupAndId(TH14_MAP_GROUP, prior)->mapLayoutId);
    }
}

extern const u8 *Test_TH_MetatileScript(u8 behavior);
extern const u8 TH_EventScript_KantoTV[], TH_EventScript_KantoRegionMap[];
extern void TurnOffTVScreen(void);
extern void TurnOnTVScreen(void);

TEST("Three Horizons PT14 celadon: imported house keeps Kanto TV and map behavior across group76")
{
    const struct MapHeader saved = gMapHeader;
    const struct BackupMapLayout layout = gBackupMapLayout;
    u16 *old1 = gOverworldTilemapBuffer_Bg1, *old2 = gOverworldTilemapBuffer_Bg2, *old3 = gOverworldTilemapBuffer_Bg3;
    gOverworldTilemapBuffer_Bg1 = AllocZeroed(BG_SCREEN_SIZE);
    gOverworldTilemapBuffer_Bg2 = AllocZeroed(BG_SCREEN_SIZE);
    gOverworldTilemapBuffer_Bg3 = AllocZeroed(BG_SCREEN_SIZE);
    InitEventData();
    gSaveBlock1Ptr->pos.x = 0; gSaveBlock1Ptr->pos.y = 0;
    gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(MAP_TH14_CELADON_CITY_HOUSE1);
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(MAP_TH14_CELADON_CITY_HOUSE1);
    gMapHeader = *Overworld_GetMapHeaderByGroupAndId(gSaveBlock1Ptr->location.mapGroup, gSaveBlock1Ptr->location.mapNum);
    InitMap();
    EXPECT_EQ(Test_TH_MetatileScript(MB_TELEVISION), TH_EventScript_KantoTV);
    EXPECT_EQ(Test_TH_MetatileScript(MB_REGION_MAP), TH_EventScript_KantoRegionMap);
    bool32 found = FALSE;
    for (u32 y = 0; y < gBackupMapLayout.height; y++)
        for (u32 x = 0; x < gBackupMapLayout.width; x++)
            if (MapGridGetMetatileBehaviorAt(x, y) == MB_TELEVISION)
            {
                u16 entry = gBackupMapLayout.map[y * gBackupMapLayout.width + x];
                found = TRUE;
                TurnOffTVScreen();
                EXPECT_EQ(gBackupMapLayout.map[y * gBackupMapLayout.width + x], entry);
                TurnOnTVScreen();
                EXPECT_EQ(gBackupMapLayout.map[y * gBackupMapLayout.width + x], entry);
            }
    EXPECT(found);
    Free(gOverworldTilemapBuffer_Bg1); Free(gOverworldTilemapBuffer_Bg2); Free(gOverworldTilemapBuffer_Bg3);
    gOverworldTilemapBuffer_Bg1 = old1; gOverworldTilemapBuffer_Bg2 = old2; gOverworldTilemapBuffer_Bg3 = old3;
    gMapHeader = saved; gBackupMapLayout = layout;
}

TEST("Three Horizons PT14 celadon: elevator resolves five authored floors without a persistent floor variable")
{
    const u16 floors[] = {MAP_TH14_CELADON_CITY_DEPARTMENT_STORE_1F,
        MAP_TH14_CELADON_CITY_DEPARTMENT_STORE_2F, MAP_TH14_CELADON_CITY_DEPARTMENT_STORE_3F,
        MAP_TH14_CELADON_CITY_DEPARTMENT_STORE_4F, MAP_TH14_CELADON_CITY_DEPARTMENT_STORE_5F};
    const struct WarpData saved = gSaveBlock1Ptr->dynamicWarp;
    VarSet(VAR_FARAWAY_ISLAND_STEP_COUNTER, 73);
    for (u32 i = 0; i < ARRAY_COUNT(floors); i++)
    {
        gSaveBlock1Ptr->dynamicWarp = (struct WarpData){MAP_GROUP(floors[i]), MAP_NUM(floors[i]), -1, 6, 1};
        struct WarpData before = gSaveBlock1Ptr->dynamicWarp;
        EXPECT_EQ(TH14_GetDeptStoreFloor(), i + 4);
        EXPECT_EQ(VarGet(VAR_FARAWAY_ISLAND_STEP_COUNTER), 73);
        EXPECT_EQ(memcmp(&before, &gSaveBlock1Ptr->dynamicWarp, sizeof(before)), 0);
    }
    gSaveBlock1Ptr->dynamicWarp = saved;
}

TEST("Three Horizons PT14 celadon: elevator rejects foreign maps and nonfloor indices")
{
    const u16 maps[] = {MAP_CELADON_CITY_DEPARTMENT_STORE_1F, MAP_TH14_CELADON_CITY,
        MAP_TH14_CELADON_CITY_DEPARTMENT_STORE_ELEVATOR, MAP_TH14_CELADON_CITY_DEPARTMENT_STORE_ROOF,
        MAP_TH14_ROUTE7, 0xFFFF};
    const struct WarpData saved = gSaveBlock1Ptr->dynamicWarp;
    for (u32 i = 0; i < ARRAY_COUNT(maps); i++)
    {
        gSaveBlock1Ptr->dynamicWarp = (struct WarpData){MAP_GROUP(maps[i]), MAP_NUM(maps[i]), -1, 6, 1};
        struct WarpData before = gSaveBlock1Ptr->dynamicWarp;
        EXPECT_EQ(TH14_GetDeptStoreFloor(), 0);
        EXPECT_EQ(memcmp(&before, &gSaveBlock1Ptr->dynamicWarp, sizeof(before)), 0);
    }
    gSaveBlock1Ptr->dynamicWarp = saved;
}

extern const u8 TH14_CeladonCity_PokemonCenter_1F_Checkpoint[];
TEST("Three Horizons PT14 celadon: native Center checkpoint selects its nurse and safe blackout return")
{
    struct WarpData warp;
    RunScriptImmediately(TH14_CeladonCity_PokemonCenter_1F_Checkpoint);
    const struct HealLocation *location = GetHealLocation(HEAL_LOCATION_TH14_CELADON);
    EXPECT_EQ(location->mapGroup, MAP_GROUP(MAP_TH14_CELADON_CITY_POKEMON_CENTER_1F));
    EXPECT_EQ(location->mapNum, MAP_NUM(MAP_TH14_CELADON_CITY_POKEMON_CENTER_1F));
    EXPECT_EQ(GetHealLocationIndexByMap(location->mapGroup, location->mapNum), HEAL_LOCATION_TH14_CELADON);
    EXPECT_EQ(gSaveBlock1Ptr->lastHealLocation.mapGroup, location->mapGroup);
    EXPECT_EQ(gSaveBlock1Ptr->lastHealLocation.mapNum, location->mapNum);
    SetWhiteoutRespawnWarpAndHealerNPC(&warp);
    EXPECT_EQ(warp.mapGroup, location->mapGroup);
    EXPECT_EQ(warp.mapNum, location->mapNum);
    EXPECT_EQ(warp.x, 7); EXPECT_EQ(warp.y, 4); EXPECT_EQ(warp.warpId, -1);
    EXPECT_EQ(GetHealNpcLocalId(HEAL_LOCATION_TH14_CELADON), LOCALID_TH14_CELADONCITY_POKEMONCENTER_1F_1);
    EXPECT_EQ(gSpecialVar_LastTalked, LOCALID_TH14_CELADONCITY_POKEMONCENTER_1F_1);
    EXPECT_EQ(gSpecialVar_0x800B, LOCALID_TH14_CELADONCITY_POKEMONCENTER_1F_1);
    EXPECT(TH14_IsFrlgPokemonCenterLayout(LAYOUT_POKEMON_CENTER_1F_FRLG));
    EXPECT(TH14_IsFrlgPokemonCenterLayout(LAYOUT_TH14_CELADON_CITY_POKEMON_CENTER_1F));
    EXPECT(!TH14_IsFrlgPokemonCenterLayout(LAYOUT_TH14_CELADON_CITY_GYM));
}

TEST("Three Horizons PT14 celadon: Eevee uses party or PC atomically and full storage stays retryable")
{
    u32 destination;
    PARAMETRIZE { destination = 0; } // last party slot
    PARAMETRIZE { destination = 1; } // first PC slot
    PARAMETRIZE { destination = 2; } // last PC slot
    PARAMETRIZE { destination = 3; } // full party and all boxes
    struct Pokemon filler, partyBefore[PARTY_SIZE];
    struct PokemonStorage *savedStorage = gPokemonStoragePtr;
    gPokemonStoragePtr = AllocZeroed(sizeof(*gPokemonStoragePtr));
    struct PokemonStorage *before = Alloc(sizeof(*before));
    EXPECT(gPokemonStoragePtr != NULL); EXPECT(before != NULL);
    InitEventData();
    CreateMonWithIVs(&filler, SPECIES_ZUBAT, 6, 4567, OTID_STRUCT_PLAYER_ID, 7);
    for (u32 i = 0; i < PARTY_SIZE; i++) gParties[B_TRAINER_PLAYER][i] = filler;
    if (destination == 0) ZeroMonData(&gParties[B_TRAINER_PLAYER][PARTY_SIZE - 1]);
    CalculatePlayerPartyCount();
    if (destination >= 2)
        for (u32 box = 0; box < TOTAL_BOXES_COUNT; box++)
            for (u32 slot = 0; slot < IN_BOX_COUNT; slot++) gPokemonStoragePtr->boxes[box][slot] = filler.box;
    if (destination == 2) ZeroBoxMonAt(TOTAL_BOXES_COUNT - 1, IN_BOX_COUNT - 1);
    memcpy(before, gPokemonStoragePtr, sizeof(*before));
    memcpy(partyBefore, gParties[B_TRAINER_PLAYER], sizeof(partyBefore));
    const struct Pokedex dexBefore = gSaveBlock2Ptr->pokedex;
    u32 result = TH14_TryGiveEevee();
    EXPECT_EQ(result, destination == 0 ? MON_GIVEN_TO_PARTY : destination == 3 ? MON_CANT_GIVE : MON_GIVEN_TO_PC);
    EXPECT_EQ(FlagGet(FLAG_TH14_EEVEE), destination != 3);
    if (destination == 3)
    {
        EXPECT_EQ(memcmp(partyBefore, gParties[B_TRAINER_PLAYER], sizeof(partyBefore)), 0);
        EXPECT_EQ(memcmp(before, gPokemonStoragePtr, sizeof(*before)), 0);
        EXPECT_EQ(memcmp(&dexBefore, &gSaveBlock2Ptr->pokedex, sizeof(dexBefore)), 0);
        ZeroBoxMonAt(0, 0);
        EXPECT_EQ(TH14_TryGiveEevee(), MON_GIVEN_TO_PC);
        EXPECT(FlagGet(FLAG_TH14_EEVEE));
    }
    const u32 box = destination == 2 ? TOTAL_BOXES_COUNT - 1 : 0;
    const u32 slot = destination == 2 ? IN_BOX_COUNT - 1 : 0;
    struct BoxPokemon *gift = destination == 0 ? &gParties[B_TRAINER_PLAYER][PARTY_SIZE - 1].box : GetBoxedMonPtr(box, slot);
    EXPECT_EQ(GetBoxMonData(gift, MON_DATA_SPECIES), SPECIES_EEVEE);
    EXPECT_EQ(GetLevelFromBoxMonExp(gift), 25);
    EXPECT_EQ(GetBoxMonData(gift, MON_DATA_SANITY_IS_BAD_EGG), FALSE);
    if (destination != 0)
    {
        EXPECT_EQ(gSpecialVar_MonBoxId, box);
        EXPECT_EQ(gSpecialVar_MonBoxPos, slot);
        EXPECT_EQ(memcmp(partyBefore, gParties[B_TRAINER_PLAYER], sizeof(partyBefore)), 0);
    }
    memcpy(before, gPokemonStoragePtr, sizeof(*before));
    memcpy(partyBefore, gParties[B_TRAINER_PLAYER], sizeof(partyBefore));
    EXPECT_EQ(TH14_TryGiveEevee(), TH14_EEVEE_ALREADY_GIVEN);
    EXPECT_EQ(memcmp(partyBefore, gParties[B_TRAINER_PLAYER], sizeof(partyBefore)), 0);
    EXPECT_EQ(memcmp(before, gPokemonStoragePtr, sizeof(*before)), 0);
    Free(before); Free(gPokemonStoragePtr); gPokemonStoragePtr = savedStorage;
}
#endif
