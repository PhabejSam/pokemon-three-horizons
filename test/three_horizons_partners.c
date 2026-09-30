#include "global.h"
#include "test/test.h"
#include "three_horizons.h"
#include "pokemon.h"
#include "event_data.h"
#include "constants/three_horizons.h"
#if THREE_HORIZONS
TEST("Three Horizons reward partners complete three regions and types")
{
    static const u16 starters[] = {SPECIES_BULBASAUR, SPECIES_CHARMANDER, SPECIES_SQUIRTLE,
        SPECIES_CHIKORITA, SPECIES_CYNDAQUIL, SPECIES_TOTODILE,
        SPECIES_TREECKO, SPECIES_TORCHIC, SPECIES_MUDKIP};
    for (u32 i=0; i<9; i++)
        for (u32 choice=0; choice<2; choice++)
        {
            u16 brock=TH_GetBrockGift(starters[i], choice);
            u16 misty=TH_GetMistyGift(starters[i], brock);
            EXPECT(brock != SPECIES_NONE && misty != SPECIES_NONE);
            EXPECT(brock != starters[i] && misty != starters[i] && brock != misty);
            EXPECT(GetSpeciesType(brock,0) != GetSpeciesType(starters[i],0));
            EXPECT(GetSpeciesType(misty,0) != GetSpeciesType(starters[i],0));
            EXPECT(GetSpeciesType(misty,0) != GetSpeciesType(brock,0));
            u32 b=0,m=0;
            for (;b<9 && starters[b]!=brock;b++);
            for (;m<9 && starters[m]!=misty;m++);
            EXPECT(b<9 && m<9);
            EXPECT(b/3 != i/3 && m/3 != i/3 && b/3 != m/3);
            u16 rival=TH_GetRivalCandidate(starters[i],choice);
            u32 ri=0;
            for (;ri<9 && starters[ri]!=rival;ri++);
            EXPECT(ri<9 && ri/3 != i/3);
            EXPECT_EQ(ri%3,(i%3+1)%3);
        }
    EXPECT_EQ(TH_GetMistyGift(SPECIES_TORCHIC,SPECIES_SQUIRTLE),SPECIES_CHIKORITA);
    EXPECT_EQ(TH_GetMistyGift(SPECIES_TORCHIC,SPECIES_TOTODILE),SPECIES_BULBASAUR);
    EXPECT_EQ(TH_GetMistyGift(SPECIES_TORCHIC,SPECIES_NONE),SPECIES_NONE);
}
TEST("Three Horizons clock advances only visual time at the selected rate")
{
    EXPECT_EQ(TH_AdvanceVisualClock(100,200,160,0),260);
    EXPECT_EQ(TH_AdvanceVisualClock(100,200,160,1),1640);
    EXPECT_EQ(TH_AdvanceVisualClock(100,200,90,1),200);
    EXPECT_EQ(TH_AdvanceVisualClock(100,86390,101,1),14);
}
TEST("Three Horizons shiny options leave existing Pokemon unchanged")
{
    struct Pokemon mon;
    CreateMonWithIVs(&mon,SPECIES_RATTATA,5,123,OTID_STRUCT_PLAYER_ID,12);
    bool32 shiny=GetMonData(&mon,MON_DATA_IS_SHINY);
    static const u16 odds[]={8,64,128,256};
    for (u32 i=0;i<4;i++)
    {
        VarSet(VAR_TH_SHINY_RATE,i);
        EXPECT_EQ(TH_GetWildShinyThreshold(),odds[i]);
        EXPECT_EQ(GetMonData(&mon,MON_DATA_IS_SHINY),shiny);
    }
    VarSet(VAR_TH_SHINY_RATE,0xFFFF);
    EXPECT_EQ(TH_GetWildShinyThreshold(),8);
    VarSet(VAR_TH_SHINY_RATE,0);
}
#endif
