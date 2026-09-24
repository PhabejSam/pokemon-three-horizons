#include "global.h"
#include "test/test.h"
#include "three_horizons.h"
#include "pokemon.h"
#include "battle.h"
#include "event_data.h"
#include "item.h"
#include "constants/three_horizons.h"

#if THREE_HORIZONS
TEST("Three Horizons midbattle evolution respects level and Everstone")
{
    struct Pokemon mon;
    bool32 canStop = TRUE;
    u16 stone = ITEM_EVERSTONE;
    CreateMonWithIVs(&mon, SPECIES_BULBASAUR, 15, 0, OTID_STRUCT_PLAYER_ID, 12);
    EXPECT_EQ(TH_GetBattleEvolution(&mon, &canStop), SPECIES_NONE);
    CreateMonWithIVs(&mon, SPECIES_BULBASAUR, 16, 0, OTID_STRUCT_PLAYER_ID, 12);
    EXPECT_EQ(TH_GetBattleEvolution(&mon, &canStop), SPECIES_IVYSAUR);
    EXPECT(canStop);
    SetMonData(&mon, MON_DATA_HELD_ITEM, &stone);
    EXPECT_EQ(TH_GetBattleEvolution(&mon, &canStop), SPECIES_NONE);
}

TEST("Three Horizons old training kit receives only the new party Exp Share")
{
    struct ItemSlot saved[PC_ITEMS_COUNT];
    u16 mask = VarGet(VAR_TH_TRAINING_KIT_MASK);
    memcpy(saved, gSaveBlock1Ptr->pcItems, sizeof(saved));
    memset(gSaveBlock1Ptr->pcItems, 0, sizeof(saved));
    VarSet(VAR_TH_TRAINING_KIT_MASK, 127);
    EXPECT_EQ(TH_TryDeliverTrainingKit(), 255);
    EXPECT(CheckPCHasItem(ITEM_EXP_SHARE, 1));
    EXPECT(!CheckPCHasItem(ITEM_MACHO_BRACE, 1));
    EXPECT_EQ(TH_TryDeliverTrainingKit(), 255);
    EXPECT(!CheckPCHasItem(ITEM_EXP_SHARE, 2));
    EXPECT_EQ(GetItemPocket(ITEM_EXP_SHARE), POCKET_KEY_ITEMS);
    EXPECT(GetItemImportance(ITEM_TM39));
    memcpy(gSaveBlock1Ptr->pcItems, saved, sizeof(saved));
    VarSet(VAR_TH_TRAINING_KIT_MASK, mask);
}
#endif
