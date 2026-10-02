#include "global.h"
#include "test/test.h"
#include "pokemon.h"
#include "event_data.h"
#include "item.h"
#include "trade.h"
#include "string_util.h"
#include "three_horizons_chapter14.h"
#include "constants/trade.h"
#include "constants/three_horizons.h"
#include "battle.h"
#include "battle_setup.h"
#include "overworld.h"
#include "fieldmap.h"
#include "script.h"
#include "task.h"
#include "pokedex.h"
#include "text.h"
#include "constants/maps.h"
#if THREE_HORIZONS
u16 GetInGameTradeSpeciesInfo(void);
void CreateInGameTradePokemon(void);
void TH_TestFinishInGameTrade(u8 slot);
void TH14_ConfirmNinaTrade(void);
u8 GetBattleOutcome(void);
u16 GetFrlgPokedexCount(void);
extern const u8 TH14_Snorlax_RecordOutcome[];
TEST("Three Horizons PT14 snorlax: Itemfinder uses the unique owned delivery pair")
{
    InitEventData();ClearBag();memset(gSaveBlock1Ptr->pcItems,0,sizeof(gSaveBlock1Ptr->pcItems));
    EXPECT_EQ(TH14_TryGiveUniqueItem(ITEM_ITEMFINDER,FLAG_TH14_ITEMFINDER),TH14_GIFT_GIVEN);
    EXPECT(FlagGet(FLAG_TH14_ITEMFINDER));EXPECT(CheckBagHasItem(ITEM_ITEMFINDER,1));
    EXPECT_EQ(TH14_TryGiveUniqueItem(ITEM_ITEMFINDER,FLAG_TH14_ITEMFINDER),TH14_GIFT_ALREADY_OWNED);
}
TEST("Three Horizons PT14 snorlax: NINA native trade receives the FireRed identity at the offered level")
{
    for(u32 level=1;level<=100;level+=99)
    {
        ZeroPlayerPartyMons();CreateMonWithIVs(&gParties[B_TRAINER_PLAYER][0],SPECIES_NIDORINO,level,0,OTID_STRUCT_PLAYER_ID,31);
        CalculatePlayerPartyCount();gSpecialVar_0x8004=0;gSpecialVar_0x8005=INGAME_TRADE_NIDORINOA;
        EXPECT_EQ(GetInGameTradeSpeciesInfo(),SPECIES_NIDORINO);
        CreateInGameTradePokemon();TH_TestFinishInGameTrade(0);
        struct Pokemon *mon=&gParties[B_TRAINER_PLAYER][0];
        EXPECT_EQ(GetMonData(mon,MON_DATA_SPECIES),SPECIES_NIDORINA);
        EXPECT_EQ(GetMonData(mon,MON_DATA_LEVEL),level);EXPECT_EQ(GetMonData(mon,MON_DATA_PERSONALITY),0x00eeca15);
        EXPECT_EQ(GetMonData(mon,MON_DATA_OT_ID),13637);EXPECT_EQ(GetMonData(mon,MON_DATA_ABILITY_NUM),0);
        EXPECT_EQ(GetMonData(mon,MON_DATA_HELD_ITEM),ITEM_NONE);
        const u8 ivs[]={22,25,18,19,22,15};
        for(u32 stat=0;stat<6;stat++)EXPECT_EQ(GetMonData(mon,MON_DATA_HP_IV+stat),ivs[stat]);
        u8 name[POKEMON_NAME_BUFFER_SIZE];GetMonData(mon,MON_DATA_NICKNAME,name);EXPECT_EQ(StringCompare(name,COMPOUND_STRING("NINA")),0);
    }
}
TEST("Three Horizons PT14 snorlax: trade delivery signature is slot bounded and preserves every other identity")
{
    for(u32 chosen=0;chosen<PARTY_SIZE;chosen++)
    {
        InitEventData();ZeroPlayerPartyMons();
        for(u32 n=0;n<PARTY_SIZE;n++)CreateMonWithIVs(&gParties[B_TRAINER_PLAYER][n],n==chosen?SPECIES_NIDORINO:SPECIES_PIDGEY,37,123+n,OTID_STRUCT_PLAYER_ID,20);
        CalculatePlayerPartyCount();struct Pokemon before[PARTY_SIZE];memcpy(before,gParties[B_TRAINER_PLAYER],sizeof(before));
        gSpecialVar_0x8004=chosen;gSpecialVar_0x8005=INGAME_TRADE_NIDORINOA;
        TH14_ConfirmNinaTrade();EXPECT_EQ(gSpecialVar_Result,FALSE);
        CreateInGameTradePokemon();TH14_ConfirmNinaTrade();EXPECT_EQ(gSpecialVar_Result,FALSE);
        EXPECT_EQ(memcmp(before,gParties[B_TRAINER_PLAYER],sizeof(before)),0);
        TH_TestFinishInGameTrade(chosen);TH14_ConfirmNinaTrade();EXPECT_EQ(gSpecialVar_Result,TRUE);
        EXPECT(!FlagGet(FLAG_TH14_NINA_TRADE)); // Predicate never awards its own receipt.
        for(u32 n=0;n<PARTY_SIZE;n++)if(n!=chosen)EXPECT_EQ(memcmp(&before[n],&gParties[B_TRAINER_PLAYER][n],sizeof(struct Pokemon)),0);
        gSpecialVar_0x8005=INGAME_TRADE_MR_MIME;TH14_ConfirmNinaTrade();EXPECT_EQ(gSpecialVar_Result,FALSE);
        gSpecialVar_0x8005=INGAME_TRADE_NIDORINOA;gSpecialVar_0x8004=PARTY_SIZE;TH14_ConfirmNinaTrade();EXPECT_EQ(gSpecialVar_Result,FALSE);
        gSpecialVar_0x8004=0xffff;TH14_ConfirmNinaTrade();EXPECT_EQ(gSpecialVar_Result,FALSE);
    }
}
TEST("Three Horizons PT14 snorlax: native normal battle callback preserves all nonwins for retry")
{
    const struct MapHeader header=gMapHeader;const struct BackupMapLayout layout=gBackupMapLayout;
    MainCallback original=gMain.callback2,originalSaved=gMain.savedCallback;
    InitEventData();ResetTasks();
    gSaveBlock1Ptr->location.mapGroup=MAP_GROUP(MAP_TH14_ROUTE12_LANDING);gSaveBlock1Ptr->location.mapNum=MAP_NUM(MAP_TH14_ROUTE12_LANDING);
    gMapHeader=*Overworld_GetMapHeaderByGroupAndId(MAP_GROUP(MAP_TH14_ROUTE12_LANDING),MAP_NUM(MAP_TH14_ROUTE12_LANDING));
    LoadObjEventTemplatesFromHeader();InitMap();
    EXPECT_EQ(gMapHeader.events->objectEventCount,1);
    EXPECT_EQ(gMapHeader.events->objectEvents[0].flagId,FLAG_TH14_SNORLAX_RESOLVED);
    CreateMonWithIVs(&gParties[B_TRAINER_PLAYER][0],SPECIES_WOBBUFFET,40,123,OTID_STRUCT_PLAYER_ID,20);CalculatePlayerPartyCount();
    CreateMonWithIVs(&gParties[B_TRAINER_OPPONENT_A][0],SPECIES_SNORLAX,30,123,OTID_STRUCT_PLAYER_ID,20);
    BattleSetup_StartScriptedWildBattle();MainCallback finish=gMain.savedCallback;ResetTasks();
    EXPECT_EQ(gBattleTypeFlags,0);
    for(u32 result=0;result<=B_OUTCOME_MON_TELEPORTED;result++)
    {
        InitEventData();gBattleOutcome=result;finish();MainCallback selected=gMain.callback2;SetMainCallback2(original);
        bool32 blackout=result==B_OUTCOME_LOST||result==B_OUTCOME_DREW||result==B_OUTCOME_FORFEITED;
        EXPECT_EQ(selected,blackout?CB2_WhiteOut:CB2_ReturnToFieldContinueScriptPlayMapMusic);
        EXPECT(!FlagGet(FLAG_TH14_SNORLAX_RESOLVED));
        gSpecialVar_Result=GetBattleOutcome();EXPECT_EQ(gSpecialVar_Result,result);
        if(!blackout)RunScriptImmediately(TH14_Snorlax_RecordOutcome);
        EXPECT_EQ(FlagGet(FLAG_TH14_SNORLAX_RESOLVED),result==B_OUTCOME_WON||result==B_OUTCOME_CAUGHT);
        EXPECT(!FlagGet(FLAG_TH14_PICKUP_44));EXPECT(!FlagGet(FLAG_TH14_NINA_TRADE));
        ClearTempFieldEventData();InitMap();
        EXPECT_EQ(MapGridGetCollisionAt(14+MAP_OFFSET,10+MAP_OFFSET),0);
        for(u32 y=6;y<=16;y+=10)for(u32 x=14;x<=15;x++)EXPECT(MapGridGetCollisionAt(x+MAP_OFFSET,y+MAP_OFFSET)!=0);
        ScriptContext_Init();UnlockPlayerFieldControls();
    }
    gMain.savedCallback=originalSaved;gMapHeader=header;gBackupMapLayout=layout;
}
TEST("Three Horizons PT14 snorlax: Itemfinder counts owned visitors and full pocket retries with Bag PC ownership")
{
    InitEventData();ResetPokedex();ClearBag();memset(gSaveBlock1Ptr->pcItems,0,sizeof(gSaveBlock1Ptr->pcItems));
    for(u32 dex=1;dex<=29;dex++)GetSetPokedexFlag(dex,FLAG_SET_CAUGHT);
    gSpecialVar_0x8004=1;bool32 enabled=IsNationalPokedexEnabled();GetFrlgPokedexCount();EXPECT_EQ(gSpecialVar_0x8006,29);
    GetSetPokedexFlag(NATIONAL_DEX_TREECKO,FLAG_SET_CAUGHT);GetFrlgPokedexCount();EXPECT_EQ(gSpecialVar_0x8006,30);EXPECT_EQ(IsNationalPokedexEnabled(),enabled);
    struct BagPocket *pocket=&gBagPockets[POCKET_KEY_ITEMS];
    for(u32 n=0;n<pocket->capacity;n++)BagPocket_SetSlotItemIdAndCount(pocket,n,ITEM_BICYCLE,1);
    ASSUME(!CheckBagHasSpace(ITEM_ITEMFINDER,1));
    EXPECT_EQ(TH14_TryGiveUniqueItem(ITEM_ITEMFINDER,FLAG_TH14_ITEMFINDER),TH14_GIFT_NO_ROOM);EXPECT(!FlagGet(FLAG_TH14_ITEMFINDER));
    BagPocket_SetSlotItemIdAndCount(pocket,pocket->capacity-1,ITEM_NONE,0);
    EXPECT_EQ(TH14_TryGiveUniqueItem(ITEM_ITEMFINDER,FLAG_TH14_ITEMFINDER),TH14_GIFT_GIVEN);
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_ITEMFINDER),1);
    FlagClear(FLAG_TH14_ITEMFINDER);EXPECT(RemoveBagItem(ITEM_ITEMFINDER,1));EXPECT(AddPCItem(ITEM_ITEMFINDER,1));
    EXPECT_EQ(TH14_TryGiveUniqueItem(ITEM_ITEMFINDER,FLAG_TH14_ITEMFINDER),TH14_GIFT_ALREADY_OWNED);
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_ITEMFINDER),0);EXPECT(FlagGet(FLAG_TH14_ITEMFINDER));
}
extern const u8 TH14_Gate_RoadText[],TH14_Gate_UpstairsText[],TH14_Gate_ViewAsleep[],TH14_Gate_ViewClear[],TH14_Gate_TunnelText[];
extern const u8 TH14_Gate_ItemfinderOffer[],TH14_Gate_ItemfinderReceived[],TH14_Gate_ItemfinderHelp[],TH14_Gate_ItemfinderNeedMore[],TH14_Gate_ItemfinderNoRoom[];
extern const u8 TH14_Gate_TradeRetry[],TH14_Snorlax_AsleepText[],TH14_Snorlax_Offer[],TH14_Snorlax_RetryText[],TH14_Snorlax_OpenText[],TH14_Landing_RoadText[],TH14_Landing_MaintenanceText[];
extern const u8 TH14_Gate_TradeOffer[],TH14_Gate_TradeThanks[],TH14_Gate_TradeWrongText[],TH14_Gate_TradeDeclineText[],TH14_Gate_TradeDoneText[],TH14_Snorlax_Woke[];
TEST("Three Horizons PT14 snorlax: authored gate and road copy fits the native box")
{
    const u8 *texts[]={TH14_Gate_RoadText,TH14_Gate_UpstairsText,TH14_Gate_ViewAsleep,TH14_Gate_ViewClear,TH14_Gate_TunnelText,TH14_Gate_ItemfinderOffer,TH14_Gate_ItemfinderReceived,TH14_Gate_ItemfinderHelp,TH14_Gate_ItemfinderNeedMore,TH14_Gate_ItemfinderNoRoom,TH14_Gate_TradeRetry,TH14_Snorlax_AsleepText,TH14_Snorlax_Offer,TH14_Snorlax_RetryText,TH14_Snorlax_OpenText,TH14_Landing_RoadText,TH14_Landing_MaintenanceText,TH14_Gate_TradeOffer,TH14_Gate_TradeThanks,TH14_Gate_TradeWrongText,TH14_Gate_TradeDeclineText,TH14_Gate_TradeDoneText,TH14_Snorlax_Woke};
    SetDefaultFontsPointer();
    for(u32 n=0;n<ARRAY_COUNT(texts);n++)
    {
        u8 copy[256];EXPECT_LT(StringLength(texts[n]),sizeof(copy));StringCopy(copy,texts[n]);
        for(u32 p=0;copy[p]!=EOS;p++)if(copy[p]==CHAR_PROMPT_CLEAR||copy[p]==CHAR_PROMPT_SCROLL)copy[p]=CHAR_NEWLINE;
        EXPECT_LE(GetStringWidth(FONT_NORMAL,copy,0),208);
    }
}
#endif

#include "test/battle.h"
#if THREE_HORIZONS
WILD_BATTLE_TEST("Three Horizons PT14 snorlax: normal level thirty encounter is catchable")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_SNORLAX) { Level(30); }
    } WHEN {
        TURN { USE_ITEM(player,ITEM_MASTER_BALL); }
    } THEN {
        EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][1],MON_DATA_SPECIES),SPECIES_SNORLAX);
        EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][1],MON_DATA_LEVEL),30);
        EXPECT_EQ(gBattleOutcome,B_OUTCOME_CAUGHT);
        // Recorded battle tests bypass Dex/nickname UI in BattleScript_TryPrintCaughtMonInfo.
        // Real first-catch Dex, naming and native persistence are Task19 controller checks.
    }
}
#endif
