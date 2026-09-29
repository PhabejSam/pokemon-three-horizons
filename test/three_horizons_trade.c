#include "global.h"
#include "test/test.h"
#include "pokemon.h"
#include "event_data.h"
#include "trade.h"
#include "string_util.h"
#include "constants/trade.h"
#include "constants/three_horizons.h"

#if THREE_HORIZONS
extern u16 GetInGameTradeSpeciesInfo(void);
extern void CreateInGameTradePokemon(void);
extern enum Species GetTradeSpecies(void);
extern u16 TH_TestFindSkarmoryTrade(void);
extern void TH_TestFinishInGameTrade(u8 slot);
extern void TH_TestBufferInGameTradeMonName(void);
#define TEST_SKARMORY_TRADE (INGAME_TRADE_SEEL + 1)

TEST("Three Horizons playtest13 local trade preserves native level identity and normal ability policy")
{
    EXPECT_EQ(TH_TestFindSkarmoryTrade(),TEST_SKARMORY_TRADE);
    struct Pokemon before[PARTY_SIZE];
    for(u32 level=1;level<=100;level+=(level==1?36:63))
    {
        CreateMonWithIVs(&gPlayerParty[2],SPECIES_ZUBAT,level,0,OTID_STRUCT_PLAYER_ID,31);
        memcpy(before,gPlayerParty,sizeof(before));
        gSpecialVar_0x8004=2;gSpecialVar_0x8005=TEST_SKARMORY_TRADE;
        EXPECT_EQ(GetInGameTradeSpeciesInfo(),SPECIES_ZUBAT);
        CreateInGameTradePokemon();
        struct Pokemon *received=&gParties[B_TRAINER_OPPONENT_A][0];
        EXPECT_EQ(GetMonData(received,MON_DATA_SPECIES),SPECIES_SKARMORY);
        EXPECT_EQ(GetMonData(received,MON_DATA_LEVEL),level);
        EXPECT_EQ(GetMonData(received,MON_DATA_ABILITY_NUM),0);
        EXPECT_EQ(GetMonData(received,MON_DATA_HELD_ITEM),ITEM_NONE);
        EXPECT_EQ(GetMonData(received,MON_DATA_OT_ID),28413);
        EXPECT_EQ(GetMonData(received,MON_DATA_HP),GetMonData(received,MON_DATA_MAX_HP));
        EXPECT(GetMonData(received,MON_DATA_MOVE1)!=MOVE_NONE);
        EXPECT_EQ(memcmp(before,gPlayerParty,sizeof(before)),0);
        if(level==100)break;
    }
}

TEST("Three Horizons playtest13 native local trade exchanges one slot even with full or sole healthy party")
{
    EXPECT_EQ(TH_TestFindSkarmoryTrade(),TEST_SKARMORY_TRADE);
    for(u32 count=1;count<=PARTY_SIZE;count+=5)
    for(u32 chosen=0;chosen<count;chosen++)
    {
        ZeroPlayerPartyMons();
        for(u32 i=0;i<count;i++)CreateMonWithIVs(&gPlayerParty[i],i==chosen?SPECIES_ZUBAT:SPECIES_PIDGEY,22,0,OTID_STRUCT_PLAYER_ID,31);
        CalculatePlayerPartyCount();
        u32 item=ITEM_ORAN_BERRY;SetMonData(&gPlayerParty[chosen],MON_DATA_HELD_ITEM,&item);
        u32 hp=0;for(u32 i=0;i<count;i++)if(i!=chosen)SetMonData(&gPlayerParty[i],MON_DATA_HP,&hp);
        struct Pokemon before[PARTY_SIZE];memcpy(before,gPlayerParty,sizeof(before));
        gSpecialVar_0x8004=chosen;gSpecialVar_0x8005=TEST_SKARMORY_TRADE;
        CreateInGameTradePokemon();TH_TestFinishInGameTrade(chosen);
        EXPECT_EQ(gPlayerPartyCount,count);
        EXPECT_EQ(GetMonData(&gPlayerParty[chosen],MON_DATA_SPECIES),SPECIES_SKARMORY);
        EXPECT(GetMonData(&gPlayerParty[chosen],MON_DATA_HP)>0);
        EXPECT_EQ(GetMonData(&gPlayerParty[chosen],MON_DATA_FRIENDSHIP),70);
        EXPECT_EQ(GetMonData(&gParties[B_TRAINER_OPPONENT_A][0],MON_DATA_HELD_ITEM),ITEM_ORAN_BERRY);
        for(u32 i=0;i<PARTY_SIZE;i++)if(i!=chosen)EXPECT_EQ(memcmp(&before[i],&gPlayerParty[i],sizeof(struct Pokemon)),0);
    }
}

TEST("Three Horizons playtest13 trade name buffer uses selected party slot rather than trade record ID")
{
    gSpecialVar_0x8004=2;gSpecialVar_0x8005=INGAME_TRADE_MR_MIME;
    CreateMonWithIVs(&gPlayerParty[4],SPECIES_PIDGEY,22,0,OTID_STRUCT_PLAYER_ID,31);
    SetMonData(&gPlayerParty[4],MON_DATA_NICKNAME,COMPOUND_STRING("WRONG SLOT"));
    CreateMonWithIVs(&gPlayerParty[2],SPECIES_SKARMORY,22,0,OTID_STRUCT_PLAYER_ID,31);
    SetMonData(&gPlayerParty[2],MON_DATA_NICKNAME,COMPOUND_STRING("ABCDEFGHIJKLM"));
    u8 expected[POKEMON_NAME_BUFFER_SIZE];GetMonData(&gPlayerParty[2],MON_DATA_NICKNAME,expected);
    TH_TestBufferInGameTradeMonName();
    EXPECT_EQ(StringCompare(gStringVar1,expected),0);
}

TEST("Three Horizons playtest13 native trade selection rejects Egg and wrong species")
{
    gSpecialVar_0x8004=0;
    CreateMonWithIVs(&gPlayerParty[0],SPECIES_ZUBAT,20,0,OTID_STRUCT_PLAYER_ID,31);
    EXPECT_EQ(GetTradeSpecies(),SPECIES_ZUBAT);
    u32 egg=TRUE;SetMonData(&gPlayerParty[0],MON_DATA_IS_EGG,&egg);
    EXPECT_EQ(GetTradeSpecies(),SPECIES_NONE);
    CreateMonWithIVs(&gPlayerParty[0],SPECIES_PIDGEY,20,0,OTID_STRUCT_PLAYER_ID,31);
    EXPECT(GetTradeSpecies()!=SPECIES_ZUBAT);
}
#endif
