#include "global.h"
#include "test/test.h"
#include "three_horizons.h"
#include "pokemon.h"
#include "event_data.h"
#include "item.h"
#include "field_move.h"
#include "script.h"

#if THREE_HORIZONS
extern bool8 ScrCmd_checkfieldmove(struct ScriptContext *ctx);

TEST("Three Horizons playtest13 Flash requires HM badge and valid user")
{
    struct Pokemon mon, healthy;
    InitEventData(); ClearBag();
    CreateMonWithIVs(&mon, SPECIES_PIKACHU, 20, 0, OTID_STRUCT_PLAYER_ID, 31);
    EXPECT(!TH_FieldMoveUnlocked(FIELD_MOVE_FLASH));
    EXPECT(AddBagItem(ITEM_HM05, 1));
    EXPECT(!TH_CanUseFieldMove(&mon, FIELD_MOVE_FLASH));
    FlagSet(FLAG_BADGE03_GET);
    EXPECT(TH_FieldMoveUnlocked(FIELD_MOVE_FLASH));
    EXPECT(TH_CanUseFieldMove(&mon, FIELD_MOVE_FLASH));
    healthy=mon;
    u32 value=0;
    SetMonData(&mon,MON_DATA_HP,&value);
    EXPECT(!TH_CanUseFieldMove(&mon,FIELD_MOVE_FLASH));
    mon=healthy;value=TRUE;SetMonData(&mon,MON_DATA_IS_EGG,&value);
    EXPECT(!TH_CanUseFieldMove(&mon,FIELD_MOVE_FLASH));
    CreateMonWithIVs(&mon,SPECIES_MAGIKARP,20,0,OTID_STRUCT_PLAYER_ID,31);
    SetMonMoveSlot(&mon,MOVE_FLASH,0);
    EXPECT(!TH_CanUseFieldMove(&mon,FIELD_MOVE_FLASH));
    mon=healthy;ClearBag();
    EXPECT(!TH_CanUseFieldMove(&mon,FIELD_MOVE_FLASH));
    for(u32 i=0;i<FIELD_MOVES_COUNT;i++)
        if(TH_IsHMFieldMove(i) && i!=FIELD_MOVE_CUT && i!=FIELD_MOVE_FLASH)
            EXPECT(!TH_FieldMoveUnlocked(i));
}

TEST("Three Horizons playtest13 HM field use accepts full unrelated moveset without mutation")
{
    struct Pokemon mon,before;
    InitEventData();ClearBag();AddBagItem(ITEM_HM01,1);AddBagItem(ITEM_HM05,1);
    FlagSet(FLAG_BADGE02_GET);FlagSet(FLAG_BADGE03_GET);
    CreateMonWithIVs(&mon,SPECIES_BULBASAUR,20,0,OTID_STRUCT_PLAYER_ID,31);
    const u16 moves[]={MOVE_TACKLE,MOVE_GROWL,MOVE_VINE_WHIP,MOVE_POISON_POWDER};
    for(u32 field=FIELD_MOVE_CUT;field<=FIELD_MOVE_FLASH;field++)
    {
        for(u32 learned=0;learned<2;learned++)for(u32 full=0;full<2;full++)
        {
            for(u32 slot=0;slot<4;slot++)SetMonMoveSlot(&mon,slot==3&&!full?MOVE_NONE:moves[slot],slot);
            if(learned)SetMonMoveSlot(&mon,FieldMove_GetMoveId(field),0);
            u32 bonuses=0x55;SetMonData(&mon,MON_DATA_PP_BONUSES,&bonuses);
            before=mon;
            EXPECT(TH_CanUseFieldMove(&mon,field));
            EXPECT_EQ(memcmp(&before,&mon,sizeof(mon)),0);
        }
    }
}

TEST("Three Horizons playtest13 scripted Flash lookup shares eligibility and preserves party")
{
    struct Pokemon saved[PARTY_SIZE],before[PARTY_SIZE];
    memcpy(saved,gPlayerParty,sizeof(saved));memset(gPlayerParty,0,sizeof(saved));
    InitEventData();ClearBag();AddBagItem(ITEM_HM05,1);FlagSet(FLAG_BADGE03_GET);
    CreateMonWithIVs(&gPlayerParty[0],SPECIES_MAGIKARP,20,0,OTID_STRUCT_PLAYER_ID,31);
    CreateMonWithIVs(&gPlayerParty[1],SPECIES_PIKACHU,20,0,OTID_STRUCT_PLAYER_ID,31);
    for(u32 slot=0;slot<4;slot++)SetMonMoveSlot(&gPlayerParty[1],MOVE_TACKLE,slot);
    memcpy(before,gPlayerParty,sizeof(before));
    const u8 args[]={FIELD_MOVE_FLASH,TRUE};struct ScriptContext ctx={0};ctx.scriptPtr=args;
    ScrCmd_checkfieldmove(&ctx);EXPECT_EQ(gSpecialVar_Result,1);
    EXPECT_EQ(memcmp(before,gPlayerParty,sizeof(before)),0);
    FlagClear(FLAG_BADGE03_GET);ctx.scriptPtr=args;ScrCmd_checkfieldmove(&ctx);EXPECT_EQ(gSpecialVar_Result,PARTY_SIZE);
    memcpy(gPlayerParty,saved,sizeof(saved));CalculatePlayerPartyCount();
}
#endif
