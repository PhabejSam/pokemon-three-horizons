#include "global.h"
#include "test/test.h"
#include "three_horizons.h"
#include "event_data.h"
#include "pokemon.h"
#include "constants/three_horizons.h"
#include "constants/region_map_sections.h"
#if THREE_HORIZONS
TEST("Three Horizons chapter finishes once with victories in either order")
{
    for (u32 first=0;first<2;first++)
    {
        FlagClear(FLAG_BADGE02_GET);
        FlagClear(FLAG_TH_BRIDGE_RIVAL);
        FlagClear(FLAG_TH_CHAPTER_COMPLETE);
        EXPECT(!TH_TryCompleteChapter());
        FlagSet(first ? FLAG_TH_BRIDGE_RIVAL : FLAG_BADGE02_GET);
        EXPECT(!TH_TryCompleteChapter());
        FlagSet(first ? FLAG_BADGE02_GET : FLAG_TH_BRIDGE_RIVAL);
        EXPECT(TH_TryCompleteChapter());
        EXPECT(!TH_TryCompleteChapter());
    }
    FlagClear(FLAG_BADGE02_GET);
    FlagClear(FLAG_TH_BRIDGE_RIVAL);
    FlagClear(FLAG_TH_CHAPTER_COMPLETE);
}
TEST("Three Horizons area cards show only on external landmark entry")
{
    EXPECT(TH_ShouldShowAreaCard(MAPSEC_ROUTE_2,MAPSEC_VIRIDIAN_FOREST));
    EXPECT(TH_ShouldShowAreaCard(MAPSEC_ROUTE_4,MAPSEC_MT_MOON));
    EXPECT(!TH_ShouldShowAreaCard(MAPSEC_MT_MOON,MAPSEC_MT_MOON));
    EXPECT(!TH_ShouldShowAreaCard(MAPSEC_VIRIDIAN_FOREST,MAPSEC_VIRIDIAN_FOREST));
    EXPECT(!TH_ShouldShowAreaCard(MAPSEC_MT_MOON,MAPSEC_CERULEAN_CITY));
    EXPECT(!TH_ShouldShowAreaCard(MAPSEC_PALLET_TOWN,MAPSEC_PALLET_TOWN));
}
TEST("Three Horizons species ability picker includes distinct hidden abilities")
{
    u8 slots[3];
    struct THPartnerOptions options={0};
    EXPECT_EQ(TH_GetAbilityChoices(SPECIES_BULBASAUR,slots),2);
    EXPECT_EQ(slots[0],0);
    EXPECT_EQ(slots[1],2);
    options.abilityNum=2;
    EXPECT(TH_PartnerOptionsValidForSpecies(SPECIES_BULBASAUR,&options));
    struct Pokemon mon;
    EXPECT(TH_CreateConfiguredPartner(&mon,SPECIES_BULBASAUR,5,&options));
    EXPECT_EQ(GetMonData(&mon,MON_DATA_ABILITY_NUM),2);
    options.abilityNum=3;
    EXPECT(!TH_PartnerOptionsValidForSpecies(SPECIES_BULBASAUR,&options));
}
#endif
