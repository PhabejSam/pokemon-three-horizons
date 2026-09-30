#include "global.h"
#include "test/test.h"
#include "three_horizons.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "event_data.h"
#include "malloc.h"
#include "money.h"
#include "constants/three_horizons.h"
#if THREE_HORIZONS
TEST("Three Horizons full storage preserves gift receipts and Magikarp payment")
{
    struct PokemonStorage *savedStorage=gPokemonStoragePtr;
    struct Pokemon savedParty[PARTY_SIZE], mon;
    u32 savedMoney=GetMoney(&gSaveBlock1Ptr->money);
    memcpy(savedParty,gPlayerParty,sizeof(savedParty));
    gPokemonStoragePtr=AllocZeroed(sizeof(*gPokemonStoragePtr));
    EXPECT(gPokemonStoragePtr != NULL);
    CreateMonWithIVs(&mon,SPECIES_MAGIKARP,5,123,OTID_STRUCT_PLAYER_ID,31);
    for (u32 i=0;i<PARTY_SIZE;i++) gPlayerParty[i]=mon;
    for (u32 b=0;b<TOTAL_BOXES_COUNT;b++)
        for (u32 s=0;s<IN_BOX_COUNT;s++) gPokemonStoragePtr->boxes[b][s]=mon.box;
    SetMoney(&gSaveBlock1Ptr->money,500);
    FlagClear(FLAG_TH_MAGIKARP);
    EXPECT_EQ(TH_TryDeliverReward(TH_REWARD_MAGIKARP,&mon),MON_CANT_GIVE);
    EXPECT_EQ(GetMoney(&gSaveBlock1Ptr->money),500);
    EXPECT(!FlagGet(FLAG_TH_MAGIKARP));
    memset(&gPokemonStoragePtr->boxes[0][0],0,sizeof(mon.box));
    EXPECT_EQ(TH_TryDeliverReward(TH_REWARD_MAGIKARP,&mon), MON_GIVEN_TO_PC);
    EXPECT_EQ(GetMoney(&gSaveBlock1Ptr->money),0);
    EXPECT(FlagGet(FLAG_TH_MAGIKARP));
    EXPECT_EQ(TH_TryDeliverReward(TH_REWARD_MAGIKARP,&mon),MON_CANT_GIVE);
    VarSet(VAR_TH_FIRST_PARTNER,SPECIES_TORCHIC);
    VarSet(VAR_TH_BROCK_GIFT,0);
    FlagSet(FLAG_BADGE01_GET);
    CreateMonWithIVs(&mon,SPECIES_SQUIRTLE,10,123,OTID_STRUCT_PLAYER_ID,31);
    EXPECT_EQ(TH_TryDeliverReward(TH_REWARD_BROCK,&mon),MON_CANT_GIVE);
    EXPECT_EQ(VarGet(VAR_TH_BROCK_GIFT),0);
    memset(&gPokemonStoragePtr->boxes[0][1],0,sizeof(mon.box));
    EXPECT_EQ(TH_TryDeliverReward(TH_REWARD_BROCK,&mon), MON_GIVEN_TO_PC);
    EXPECT_EQ(VarGet(VAR_TH_BROCK_GIFT),SPECIES_SQUIRTLE);
    EXPECT_EQ(TH_TryDeliverReward(TH_REWARD_BROCK,&mon),MON_CANT_GIVE);
    Free(gPokemonStoragePtr);
    gPokemonStoragePtr=savedStorage;
    memcpy(gPlayerParty,savedParty,sizeof(savedParty));
    CalculatePlayerPartyCount();
    SetMoney(&gSaveBlock1Ptr->money,savedMoney);
    VarSet(VAR_TH_FIRST_PARTNER,0);
    VarSet(VAR_TH_BROCK_GIFT,0);
    FlagClear(FLAG_TH_MAGIKARP);
    FlagClear(FLAG_BADGE01_GET);
}
#endif
