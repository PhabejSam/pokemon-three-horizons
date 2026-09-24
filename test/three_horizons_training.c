#include "global.h"
#include "test/test.h"
#include "three_horizons.h"
#include "pokemon.h"
#include "item.h"
#include "event_data.h"
#include "string_util.h"
#include "constants/three_horizons.h"
#include "constants/items.h"

#if THREE_HORIZONS
TEST("Three Horizons training kit delivers once and retries full storage")
{
    static const u16 items[] = {ITEM_MACHO_BRACE, ITEM_POWER_WEIGHT, ITEM_POWER_BRACER,
        ITEM_POWER_BELT, ITEM_POWER_LENS, ITEM_POWER_BAND, ITEM_POWER_ANKLET};
    struct ItemSlot saved[PC_ITEMS_COUNT];
    u16 savedMask = VarGet(VAR_TH_TRAINING_KIT_MASK);
    memcpy(saved, gSaveBlock1Ptr->pcItems, sizeof(saved));
    memset(gSaveBlock1Ptr->pcItems, 0, sizeof(saved));
    VarSet(VAR_TH_TRAINING_KIT_MASK, 0);
    for (u32 i = 0; i < PC_ITEMS_COUNT - 2; i++)
    {
        gSaveBlock1Ptr->pcItems[i].itemId = ITEM_POTION;
        gSaveBlock1Ptr->pcItems[i].quantity = 999;
    }
    EXPECT_EQ(TH_TryDeliverTrainingKit(), 3);
    memset(gSaveBlock1Ptr->pcItems, 0, sizeof(saved));
    EXPECT_EQ(TH_TryDeliverTrainingKit(), 127);
    EXPECT(!CheckPCHasItem(ITEM_MACHO_BRACE, 1));
    EXPECT(!CheckPCHasItem(ITEM_POWER_WEIGHT, 1));
    for (u32 i = 2; i < ARRAY_COUNT(items); i++)
        EXPECT(CheckPCHasItem(items[i], 1));
    memset(gSaveBlock1Ptr->pcItems, 0, sizeof(saved));
    EXPECT_EQ(TH_TryDeliverTrainingKit(), 127);
    for (u32 i = 0; i < ARRAY_COUNT(items); i++)
        EXPECT(!CheckPCHasItem(items[i], 1));
    memcpy(gSaveBlock1Ptr->pcItems, saved, sizeof(saved));
    VarSet(VAR_TH_TRAINING_KIT_MASK, savedMask);
}

TEST("Three Horizons cap service changes only requested IV and charges once")
{
    struct Pokemon mon, original;
    u8 zero = 0;
    u16 hp = 0;
    CreateMonWithIVs(&mon, SPECIES_BULBASAUR, 5, 12345, OTID_STRUCT_PLAYER_ID, 0);
    SetMonData(&mon, MON_DATA_HP, &hp);
    original = mon;
    EXPECT(AddBagItem(ITEM_BOTTLE_CAP, 1));
    EXPECT(TH_TryImproveIVs(&mon, ITEM_BOTTLE_CAP, STAT_ATK));
    EXPECT_EQ(GetMonData(&mon, MON_DATA_ATK_IV), 31);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_HP_IV), 0);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_HP), 0);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_PERSONALITY), GetMonData(&original, MON_DATA_PERSONALITY));
    EXPECT_EQ(GetMonData(&mon, MON_DATA_LEVEL), 5);
    EXPECT(AddBagItem(ITEM_BOTTLE_CAP, 1));
    EXPECT(!TH_TryImproveIVs(&mon, ITEM_BOTTLE_CAP, STAT_ATK));
    EXPECT(CheckBagHasItem(ITEM_BOTTLE_CAP, 1));
    EXPECT(!TH_TryImproveIVs(&mon, ITEM_BOTTLE_CAP, 6));
    EXPECT(!TH_TryImproveIVs(&mon, ITEM_POTION, STAT_DEF));
    zero = TRUE;
    SetMonData(&mon, MON_DATA_IS_EGG, &zero);
    EXPECT(!TH_TryImproveIVs(&mon, ITEM_BOTTLE_CAP, STAT_DEF));
    RemoveBagItem(ITEM_BOTTLE_CAP, 1);
}

TEST("Three Horizons gold cap maximizes IVs without healing damage")
{
    struct Pokemon mon;
    CreateMonWithIVs(&mon, SPECIES_SANDSHREW, 12, 6789, OTID_STRUCT_PLAYER_ID, 0);
    u16 hp = GetMonData(&mon, MON_DATA_MAX_HP) - 7;
    SetMonData(&mon, MON_DATA_HP, &hp);
    EXPECT(AddBagItem(ITEM_GOLD_BOTTLE_CAP, 1));
    EXPECT(TH_TryImproveIVs(&mon, ITEM_GOLD_BOTTLE_CAP, 0));
    for (u32 i = 0; i < NUM_STATS; i++)
        EXPECT_EQ(GetMonData(&mon, MON_DATA_HP_IV + i), 31);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_MAX_HP) - GetMonData(&mon, MON_DATA_HP), 7);
    EXPECT(!TH_TryImproveIVs(&mon, ITEM_GOLD_BOTTLE_CAP, 0));
}

TEST("Three Horizons training prices share native buy and sell pricing")
{
    EXPECT_EQ(GetItemPrice(ITEM_POMEG_BERRY), 100);
    EXPECT_EQ(GetItemPrice(ITEM_TIMID_MINT), 1000);
    EXPECT_EQ(GetItemPrice(ITEM_BOTTLE_CAP), 2000);
    EXPECT_EQ(GetItemPrice(ITEM_GOLD_BOTTLE_CAP), 6000);
    EXPECT_EQ(TH_GetTrainingItemPrice(ITEM_POTION, 321), 321);
}
#endif
