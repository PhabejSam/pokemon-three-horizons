#include "global.h"
#include "test/test.h"
#include "event_data.h"
#include "item.h"
#include "pokemon.h"
#include "constants/maps.h"

extern bool8 TH_TestTowerGhostCheck(u16 mapGroup, u16 mapNum);

TEST("Three Horizons playtest13 tower map classification preserves native scope behavior")
{
    InitEventData(); ClearBag();
    // Existing native seven-floor behavior remains authoritative upstream.
    const u16 native[] = {MAP_NUM(MAP_POKEMON_TOWER_1F), MAP_NUM(MAP_POKEMON_TOWER_2F),
        MAP_NUM(MAP_POKEMON_TOWER_3F), MAP_NUM(MAP_POKEMON_TOWER_4F),
        MAP_NUM(MAP_POKEMON_TOWER_5F), MAP_NUM(MAP_POKEMON_TOWER_6F), MAP_NUM(MAP_POKEMON_TOWER_7F)};
    for (u32 scope=0; scope<2; scope++)
    {
        if (scope) EXPECT(AddBagItem(ITEM_SILPH_SCOPE,1));
        for (u32 i=0;i<ARRAY_COUNT(native);i++)
            EXPECT_EQ(TH_TestTowerGhostCheck(MAP_GROUP(MAP_POKEMON_TOWER_1F),native[i]),!scope);
        // These are the append-only registry indices; host test ties each to its map ID.
        for (u16 i=112;i<=117;i++)
            EXPECT_EQ(TH_TestTowerGhostCheck(75,i),THREE_HORIZONS && !scope);
        EXPECT(!TH_TestTowerGhostCheck(75,105)); // Lavender town
        EXPECT(!TH_TestTowerGhostCheck(75,118)); // no P13 7F
        EXPECT(!TH_TestTowerGhostCheck(74,112));
    }
    ClearBag();
}

TEST("Three Horizons playtest13 ghost scope lookup does not modify progress")
{
    u8 flags[sizeof(gSaveBlock1Ptr->flags)];
    struct Pokemon party[PARTY_SIZE];
    memcpy(flags,gSaveBlock1Ptr->flags,sizeof(flags));
    memcpy(party,gPlayerParty,sizeof(party));
    for (u16 group=74;group<=76;group++)
        for (u16 map=104;map<=119;map++) TH_TestTowerGhostCheck(group,map);
    EXPECT_EQ(memcmp(flags,gSaveBlock1Ptr->flags,sizeof(flags)),0);
    EXPECT_EQ(memcmp(party,gPlayerParty,sizeof(party)),0);
}
