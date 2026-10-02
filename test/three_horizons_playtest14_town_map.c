#include "global.h"
#include "test/test.h"
#include "event_data.h"
#include "item.h"
#include "malloc.h"
#include "event_scripts.h"
#include "three_horizons_chapter14.h"
#include "constants/three_horizons.h"

#if THREE_HORIZONS
static void ResetTownMapGift(void)
{
    InitEventData();
    ClearBag();
    memset(gSaveBlock1Ptr->pcItems, 0, sizeof(gSaveBlock1Ptr->pcItems));
}

TEST("Three Horizons PT14 town map: bag PC and receipt prevent duplicate gifts")
{
    u32 owned;
    PARAMETRIZE { owned = 0; }
    PARAMETRIZE { owned = 1; }
    PARAMETRIZE { owned = 2; }
    ResetTownMapGift();
    if (owned == 0) EXPECT(AddBagItem(ITEM_TOWN_MAP, 1));
    if (owned == 1) EXPECT(AddPCItem(ITEM_TOWN_MAP, 1));
    if (owned == 2) FlagSet(FLAG_TH14_TOWN_MAP);
    for (u32 i = 0; i < 3; i++)
        EXPECT_EQ(TH14_TryGiveUniqueItem(ITEM_TOWN_MAP, FLAG_TH14_TOWN_MAP), TH14_GIFT_ALREADY_OWNED);
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_TOWN_MAP), owned == 0);
    EXPECT_EQ(CheckPCHasItem(ITEM_TOWN_MAP, 1), owned == 1);
    EXPECT(!CheckPCHasItem(ITEM_TOWN_MAP, 2));
    EXPECT(FlagGet(FLAG_TH14_TOWN_MAP));
}

TEST("Three Horizons PT14 town map: full bag leaves receipt and inventory retryable")
{
    struct SaveBlock1 *before = Alloc(sizeof(*before));
    EXPECT(before != NULL);
    struct BagPocket *pocket = &gBagPockets[POCKET_KEY_ITEMS];
    ResetTownMapGift();
    for (u32 i = 0; i < pocket->capacity; i++)
        BagPocket_SetSlotItemIdAndCount(pocket, i, ITEM_BICYCLE, 1);
    ASSUME(!CheckBagHasSpace(ITEM_TOWN_MAP, 1));
    memcpy(before, gSaveBlock1Ptr, sizeof(*before));
    EXPECT_EQ(TH14_TryGiveUniqueItem(ITEM_TOWN_MAP, FLAG_TH14_TOWN_MAP), TH14_GIFT_NO_ROOM);
    EXPECT_EQ(memcmp(before, gSaveBlock1Ptr, sizeof(*before)), 0);
    BagPocket_SetSlotItemIdAndCount(pocket, pocket->capacity - 1, ITEM_NONE, 0);
    EXPECT_EQ(TH14_TryGiveUniqueItem(ITEM_TOWN_MAP, FLAG_TH14_TOWN_MAP), TH14_GIFT_GIVEN);
    EXPECT(FlagGet(FLAG_TH14_TOWN_MAP));
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_TOWN_MAP), 1);
    memcpy(before, gSaveBlock1Ptr, sizeof(*before));
    EXPECT_EQ(TH14_TryGiveUniqueItem(ITEM_TOWN_MAP, FLAG_TH14_TOWN_MAP), TH14_GIFT_ALREADY_OWNED);
    EXPECT_EQ(memcmp(before, gSaveBlock1Ptr, sizeof(*before)), 0);
    Free(before);
}

TEST("Three Horizons PT14 town map: unauthored item receipt pairs cannot change save")
{
    u16 item, receipt;
    PARAMETRIZE { item = ITEM_NONE; receipt = FLAG_TH14_TOWN_MAP; }
    PARAMETRIZE { item = ITEM_POTION; receipt = FLAG_TH14_TOWN_MAP; }
    PARAMETRIZE { item = ITEM_TOWN_MAP; receipt = FLAG_BADGE04_GET; }
    PARAMETRIZE { item = ITEM_TOWN_MAP; receipt = FLAG_TH14_SILPH_SCOPE; }
    PARAMETRIZE { item = 0xFFFF; receipt = 0xFFFF; }
    struct SaveBlock1 *before = Alloc(sizeof(*before));
    EXPECT(before != NULL);
    ResetTownMapGift();
    memcpy(before, gSaveBlock1Ptr, sizeof(*before));
    EXPECT_EQ(TH14_TryGiveUniqueItem(item, receipt), TH14_GIFT_NO_ROOM);
    EXPECT_EQ(memcmp(before, gSaveBlock1Ptr, sizeof(*before)), 0);
    Free(before);
}

TEST("Three Horizons PT14 town map: script special returns actual transaction result")
{
    ResetTownMapGift();
    gSpecialVar_0x8004 = ITEM_TOWN_MAP;
    gSpecialVar_0x8005 = FLAG_TH14_TOWN_MAP;
    TH14_ScriptGiveUniqueItem();
    EXPECT_EQ(gSpecialVar_Result, TH14_GIFT_GIVEN);
    EXPECT(FlagGet(FLAG_TH14_TOWN_MAP));
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_TOWN_MAP), 1);
    TH14_ScriptGiveUniqueItem();
    EXPECT_EQ(gSpecialVar_Result, TH14_GIFT_ALREADY_OWNED);
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_TOWN_MAP), 1);
}

extern const u8 TH_EventScript_KantoRegionMap[];
extern const u8 *Test_TH_TownMapScript(void);

TEST("Three Horizons PT14 town map: native item uses Kanto wording only on project maps")
{
    u8 group, map;
    bool32 project;
    PARAMETRIZE { group = 75; map = 0; project = TRUE; }
    PARAMETRIZE { group = 75; map = 117; project = TRUE; }
    PARAMETRIZE { group = 76; map = 0; project = TRUE; }
    PARAMETRIZE { group = 76; map = 36; project = TRUE; }
    PARAMETRIZE { group = 75; map = 118; project = FALSE; }
    PARAMETRIZE { group = 76; map = 37; project = FALSE; }
    PARAMETRIZE { group = 0; map = 0; project = FALSE; }
    const struct WarpData saved = gSaveBlock1Ptr->location;
    gSaveBlock1Ptr->location.mapGroup = group;
    gSaveBlock1Ptr->location.mapNum = map;
    EXPECT_EQ(Test_TH_TownMapScript(), project ? TH_EventScript_KantoRegionMap : EventScript_RegionMap);
    gSaveBlock1Ptr->location = saved;
}
#endif
