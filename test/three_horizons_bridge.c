#include "global.h"
#include "test/test.h"
#include "battle_setup.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "field_player_avatar.h"
#include "constants/maps.h"
#if THREE_HORIZONS
extern const u8 TH_Rival_BRIDGE_Bulbasaur[];
extern const u8 TH_Rival_BRIDGE_Charmander[];
extern const u8 TH_Rival_BRIDGE_Squirtle[];
extern const u8 TH_Rival_BRIDGE_Chikorita[];
extern const u8 TH_Rival_BRIDGE_Cyndaquil[];
extern const u8 TH_Rival_BRIDGE_Totodile[];
extern const u8 TH_Rival_BRIDGE_Treecko[];
extern const u8 TH_Rival_BRIDGE_Torchic[];
extern const u8 TH_Rival_BRIDGE_Mudkip[];
TEST("Three Horizons bridge coordinate battles select Blue through native parameters")
{
    static const u8 *const scripts[]={TH_Rival_BRIDGE_Bulbasaur,TH_Rival_BRIDGE_Charmander,
        TH_Rival_BRIDGE_Squirtle,TH_Rival_BRIDGE_Chikorita,TH_Rival_BRIDGE_Cyndaquil,
        TH_Rival_BRIDGE_Totodile,TH_Rival_BRIDGE_Treecko,TH_Rival_BRIDGE_Torchic,TH_Rival_BRIDGE_Mudkip};
    struct ObjectEvent savedObjects[OBJECT_EVENTS_COUNT];
    memcpy(savedObjects,gObjectEvents,sizeof(savedObjects));
    TrainerBattleParameter savedParams=gTrainerBattleParameter;
    u8 savedSelected=gSelectedObjectEvent;
    memset(gObjectEvents,0,sizeof(savedObjects));
    u8 rival=(gPlayerAvatar.objectEventId+1)%OBJECT_EVENTS_COUNT;
    gObjectEvents[rival].active=TRUE;
    gObjectEvents[rival].localId=7;
    gObjectEvents[rival].mapNum=gSaveBlock1Ptr->location.mapNum;
    gObjectEvents[rival].mapGroup=gSaveBlock1Ptr->location.mapGroup;
    for (u32 i=0;i<ARRAY_COUNT(scripts);i++)
    {
        memcpy(&gTrainerBattleParameter,scripts[i]+TRAINERBATTLE_OPCODE_OFFSET,sizeof(gTrainerBattleParameter));
        EXPECT_EQ(TRAINER_BATTLE_PARAM.objEventLocalIdA,7);
        gSelectedObjectEvent=gPlayerAvatar.objectEventId;
        SetMapVarsToTrainerA();
        EXPECT_EQ(gSelectedObjectEvent,rival);
        EXPECT_EQ(gSpecialVar_LastTalked,7);
    }
    memcpy(gObjectEvents,savedObjects,sizeof(savedObjects));
    gTrainerBattleParameter=savedParams;
    gSelectedObjectEvent=savedSelected;
}
#endif
