#include "global.h"
#include "test/test.h"
#include "coins.h"
#include "event_data.h"
#include "item.h"
#include "malloc.h"
#include "money.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "three_horizons_chapter14.h"
#include "constants/three_horizons.h"
#include "constants/vars.h"

#if THREE_HORIZONS
static void ResetEconomy(void)
{
    InitEventData();
    ClearBag();
    memset(gSaveBlock1Ptr->pcItems, 0, sizeof(gSaveBlock1Ptr->pcItems));
    SetCoins(9999);
    SetMoney(&gSaveBlock1Ptr->money, 50000);
    EXPECT(AddBagItem(ITEM_COIN_CASE, 1));
}

static void FillPocket(u32 pocketId, u16 item)
{
    struct BagPocket *p = &gBagPockets[pocketId];
    for (u32 i = 0; i < p->capacity; i++) BagPocket_SetSlotItemIdAndCount(p, i, item, 1);
}

static const u16 sStock[5][10] = {
    {ITEM_GREAT_BALL, ITEM_SUPER_POTION, ITEM_REVIVE, ITEM_ANTIDOTE, ITEM_PARALYZE_HEAL, ITEM_AWAKENING, ITEM_BURN_HEAL, ITEM_ICE_HEAL, ITEM_SUPER_REPEL},
    {ITEM_TM_ROAR, ITEM_TM_DIG, ITEM_TM_BRICK_BREAK, ITEM_TM_SECRET_POWER, ITEM_TM_ATTRACT, ITEM_TM_HYPER_BEAM, ITEM_TM_PROTECT, ITEM_TM_REST},
    {ITEM_POKE_DOLL, ITEM_RETRO_MAIL, ITEM_FIRE_STONE, ITEM_THUNDER_STONE, ITEM_WATER_STONE, ITEM_LEAF_STONE},
    {ITEM_X_ATTACK, ITEM_X_DEFENSE, ITEM_X_SPEED, ITEM_X_SP_ATK, ITEM_X_ACCURACY, ITEM_GUARD_SPEC, ITEM_DIRE_HIT},
    {ITEM_HP_UP, ITEM_PROTEIN, ITEM_IRON, ITEM_CALCIUM, ITEM_ZINC, ITEM_CARBOS},
};
static const u16 sPrices[5][9] = {
    {600,700,2000,200,200,200,200,200,700},
    {1000,2000,3000,3000,3000,7500,3000,3000},
    {300,50,3000,3000,3000,3000},
    {1000,2000,1000,1000,1000,1500,1000},
    {10000,10000,10000,10000,10000,10000},
};

TEST("Three Horizons PT14 economy: exact stock prices and only approved badge stages")
{
    ResetEconomy();
    for (u32 badges = 0; badges <= 8; badges++)
    {
        if (badges) FlagSet(FLAG_BADGE01_GET + badges - 1);
        for (u32 shop = 0; shop < 5; shop++)
        {
            u16 items[12]; memset(items, 0xA5, sizeof(items));
            u32 count = 0; while (sStock[shop][count]) count++;
            if (shop == 1) count = badges < 3 ? 0 : badges < 4 ? 5 : 8;
            EXPECT_EQ(TH14_BuildShopStock(shop, items, ARRAY_COUNT(items)), count);
            for (u32 i = 0; i < count; i++)
            {
                EXPECT_EQ(items[i], sStock[shop][i]);
                EXPECT_EQ(GetItemPrice(items[i]), sPrices[shop][i]);
            }
            EXPECT_EQ(items[count], ITEM_NONE);
            EXPECT_EQ(items[count + 1], 0xA5A5);
        }
    }
    const u16 moves[] = {MOVE_ROAR,MOVE_DIG,MOVE_BRICK_BREAK,MOVE_SECRET_POWER,MOVE_ATTRACT,MOVE_HYPER_BEAM,MOVE_PROTECT,MOVE_REST};
    for (u32 i = 0; i < ARRAY_COUNT(moves); i++) EXPECT_EQ(GetItemTMHMMoveId(sStock[1][i]), moves[i]);
}

TEST("Three Horizons PT14 economy: empty insufficient and invalid stock buffers never overflow")
{
    ResetEconomy();
    u16 items[12];
    EXPECT_EQ(TH14_BuildShopStock(0, NULL, 100), 0);
    for (u32 cap = 0; cap < 10; cap++)
    {
        memset(items, 0xA5, sizeof(items));
        EXPECT_EQ(TH14_BuildShopStock(0, items, cap), 0);
        EXPECT_EQ(items[0], cap ? ITEM_NONE : 0xA5A5);
        for (u32 i = 1; i < ARRAY_COUNT(items); i++) EXPECT_EQ(items[i], 0xA5A5);
    }
    for (u32 id = 5; id < 256; id++)
    {
        memset(items, 0xA5, sizeof(items));
        EXPECT_EQ(TH14_BuildShopStock(id, items, 12), 0);
        EXPECT_EQ(items[0], ITEM_NONE); EXPECT_EQ(items[1], 0xA5A5);
    }
}

static const u16 sPrizeItems[] = {ITEM_TM_ICE_BEAM,ITEM_TM_IRON_TAIL,ITEM_TM_THUNDERBOLT,ITEM_TM_SHADOW_BALL,ITEM_TM_FLAMETHROWER,ITEM_SMOKE_BALL,ITEM_MIRACLE_SEED,ITEM_CHARCOAL,ITEM_MYSTIC_WATER,ITEM_YELLOW_FLUTE};
static const u16 sPrizeCoins[] = {4000,3500,4000,4500,4000,800,1000,1000,1000,1600};

TEST("Three Horizons PT14 economy: exact item prizes deliver before charge and ordinary items repeat")
{
    for (u32 id = 0; id < ARRAY_COUNT(sPrizeItems); id++)
    {
        ResetEconomy(); SetCoins(sPrizeCoins[id] - 1);
        EXPECT_EQ(TH14_TryBuyItemPrize(id), TH14_PRIZE_NO_FUNDS);
        EXPECT(!CheckBagHasItem(sPrizeItems[id],1)); EXPECT_EQ(GetCoins(),sPrizeCoins[id]-1);
        SetCoins(sPrizeCoins[id]);
        EXPECT_EQ(TH14_TryBuyItemPrize(id), TH14_PRIZE_GIVEN);
        EXPECT(CheckBagHasItem(sPrizeItems[id],1)); EXPECT_EQ(GetCoins(),0);
        SetCoins(sPrizeCoins[id]);
        EXPECT_EQ(TH14_TryBuyItemPrize(id), id < 5 ? TH14_PRIZE_ALREADY_OWNED : TH14_PRIZE_GIVEN);
        EXPECT_EQ(GetCoins(),id < 5 ? sPrizeCoins[id] : 0);
        EXPECT_EQ(CountTotalItemQuantityInBag(sPrizeItems[id]),id < 5 ? 1 : 2);
        EXPECT_EQ(GetMoney(&gSaveBlock1Ptr->money),50000);
    }
}

TEST("Three Horizons PT14 economy: reusable TM bag or PC ownership never charges twice")
{
    for (u32 id = 0; id < 5; id++) for (u32 pc = 0; pc < 2; pc++)
    {
        ResetEconomy();
        EXPECT(pc ? AddPCItem(sPrizeItems[id],1) : AddBagItem(sPrizeItems[id],1));
        EXPECT_EQ(TH14_TryBuyItemPrize(id),TH14_PRIZE_ALREADY_OWNED);
        EXPECT_EQ(GetCoins(),9999);
        EXPECT_EQ(CountTotalItemQuantityInBag(sPrizeItems[id]),!pc);
        EXPECT(!CheckPCHasItem(sPrizeItems[id],2));
    }
}

TEST("Three Horizons PT14 economy: failed item delivery preserves money coins and all receipts")
{
    struct SaveBlock1 *before = Alloc(sizeof(*before)); EXPECT(before != NULL);
    for (u32 id = 0; id < ARRAY_COUNT(sPrizeItems); id++)
    {
        ResetEconomy();
        FillPocket(GetItemPocket(sPrizeItems[id]),id < 5 ? ITEM_TM_RETURN : ITEM_POTION);
        ASSUME(!CheckBagHasSpace(sPrizeItems[id],1));
        memcpy(before,gSaveBlock1Ptr,sizeof(*before));
        EXPECT_EQ(TH14_TryBuyItemPrize(id),TH14_PRIZE_NO_ROOM);
        EXPECT_EQ(memcmp(before,gSaveBlock1Ptr,sizeof(*before)),0);
    }
    Free(before);
}

TEST("Three Horizons PT14 economy: paid coins require complete capacity and exact payment")
{
    const u16 balances[] = {0,9499,9500,9949,9950,9998,9999,65535};
    for (u32 bundle = 0; bundle < 2; bundle++) for (u32 i = 0; i < ARRAY_COUNT(balances); i++)
    {
        ResetEconomy(); SetCoins(balances[i]);
        u32 amount = bundle ? 500 : 50, cost = bundle ? 10000 : 1000;
        SetMoney(&gSaveBlock1Ptr->money,cost);
        bool32 fits = (u32)balances[i] + amount <= 9999;
        EXPECT_EQ(TH14_TryBuyCoins(bundle),fits ? TH14_PRIZE_GIVEN : TH14_PRIZE_NO_ROOM);
        EXPECT_EQ(GetCoins(),balances[i] + (fits ? amount : 0));
        EXPECT_EQ(GetMoney(&gSaveBlock1Ptr->money),fits ? 0 : cost);
    }
    ResetEconomy(); SetCoins(0); SetMoney(&gSaveBlock1Ptr->money,999);
    EXPECT_EQ(TH14_TryBuyCoins(0),TH14_PRIZE_NO_FUNDS); EXPECT_EQ(GetCoins(),0);
    EXPECT_EQ(GetMoney(&gSaveBlock1Ptr->money),999);
}

TEST("Three Horizons PT14 economy: all unique coin gifts retain receipts on capacity failure")
{
    const u16 flags[] = {FLAG_TH14_GAMBLER_COINS_10,FLAG_TH14_GAMBLER_COINS_20_A,FLAG_TH14_GAMBLER_COINS_20_B,
        FLAG_TH14_PICKUP_13,FLAG_TH14_PICKUP_14,FLAG_TH14_PICKUP_15,FLAG_TH14_PICKUP_16,FLAG_TH14_PICKUP_17,FLAG_TH14_PICKUP_18,
        FLAG_TH14_PICKUP_19,FLAG_TH14_PICKUP_20,FLAG_TH14_PICKUP_21,FLAG_TH14_PICKUP_22,FLAG_TH14_PICKUP_23,FLAG_TH14_PICKUP_24};
    const u16 amounts[] = {10,20,20,10,10,20,10,10,20,10,10,10,40,100,10};
    for (u32 id = 0; id < ARRAY_COUNT(flags); id++)
    {
        ResetEconomy(); SetCoins(10000-amounts[id]);
        EXPECT_EQ(TH14_TryGiveCoins(id),TH14_PRIZE_NO_ROOM);
        EXPECT_EQ(GetCoins(),10000-amounts[id]); EXPECT(!FlagGet(flags[id]));
        SetCoins(9999-amounts[id]);
        EXPECT_EQ(TH14_TryGiveCoins(id),TH14_PRIZE_GIVEN);
        EXPECT_EQ(GetCoins(),9999); EXPECT(FlagGet(flags[id]));
        SetCoins(0); EXPECT_EQ(TH14_TryGiveCoins(id),TH14_PRIZE_ALREADY_OWNED); EXPECT_EQ(GetCoins(),0);
    }
}

static const u16 sDrinks[] = {ITEM_FRESH_WATER,ITEM_SODA_POP,ITEM_LEMONADE};
static const u16 sDrinkTMs[] = {ITEM_TM_LIGHT_SCREEN,ITEM_TM_SAFEGUARD,ITEM_TM_REFLECT};
static const u16 sDrinkFlags[] = {FLAG_TH14_ROOF_FRESH_WATER,FLAG_TH14_ROOF_SODA_POP,FLAG_TH14_ROOF_LEMONADE};

TEST("Three Horizons PT14 economy: vending uses active prices and cannot charge on a full bag")
{
    for (u32 id = 0; id < 3; id++)
    {
        ResetEconomy(); u32 price = 200 + 100 * id;
        EXPECT_EQ(GetItemPrice(sDrinks[id]),price); SetMoney(&gSaveBlock1Ptr->money,price-1);
        EXPECT_EQ(TH14_TryBuyDrink(id),TH14_PRIZE_NO_FUNDS);
        EXPECT_EQ(GetMoney(&gSaveBlock1Ptr->money),price-1);
        SetMoney(&gSaveBlock1Ptr->money,price);
        FillPocket(GetItemPocket(sDrinks[id]),ITEM_POTION);
        EXPECT_EQ(TH14_TryBuyDrink(id),TH14_PRIZE_NO_ROOM);
        EXPECT_EQ(GetMoney(&gSaveBlock1Ptr->money),price);
        ClearBag(); EXPECT_EQ(TH14_TryBuyDrink(id),TH14_PRIZE_GIVEN);
        EXPECT(CheckBagHasItem(sDrinks[id],1)); EXPECT_EQ(GetMoney(&gSaveBlock1Ptr->money),0);
    }
}

TEST("Three Horizons PT14 economy: roof exchanges deliver first and preserve drink on failure or ownership")
{
    for (u32 id = 0; id < 3; id++)
    {
        ResetEconomy(); EXPECT_EQ(TH14_TryExchangeDrink(id),TH14_PRIZE_NO_FUNDS);
        EXPECT(AddBagItem(sDrinks[id],2));
        FillPocket(POCKET_TM_HM,ITEM_TM_RETURN);
        EXPECT_EQ(TH14_TryExchangeDrink(id),TH14_PRIZE_NO_ROOM);
        EXPECT(!FlagGet(sDrinkFlags[id])); EXPECT(CheckBagHasItem(sDrinks[id],2));
        FillPocket(POCKET_TM_HM,ITEM_NONE);
        EXPECT_EQ(TH14_TryExchangeDrink(id),TH14_PRIZE_GIVEN);
        EXPECT(FlagGet(sDrinkFlags[id])); EXPECT(CheckBagHasItem(sDrinkTMs[id],1));
        EXPECT_EQ(CountTotalItemQuantityInBag(sDrinks[id]),1);
        EXPECT_EQ(TH14_TryExchangeDrink(id),TH14_PRIZE_ALREADY_OWNED);
        EXPECT_EQ(CountTotalItemQuantityInBag(sDrinks[id]),1);
        ResetEconomy(); EXPECT(AddBagItem(sDrinks[id],2)); EXPECT(AddPCItem(sDrinkTMs[id],1));
        EXPECT_EQ(TH14_TryExchangeDrink(id),TH14_PRIZE_ALREADY_OWNED);
        EXPECT(CheckBagHasItem(sDrinks[id],2)); EXPECT(!CheckBagHasItem(sDrinkTMs[id],1));
    }
}

TEST("Three Horizons PT14 economy: Coin Case unique gift is retryable and recognizes PC ownership")
{
    ResetEconomy(); ClearBag(); FillPocket(POCKET_KEY_ITEMS,ITEM_BICYCLE);
    EXPECT_EQ(TH14_TryGiveUniqueItem(ITEM_COIN_CASE,FLAG_TH14_COIN_CASE),TH14_GIFT_NO_ROOM);
    EXPECT(!FlagGet(FLAG_TH14_COIN_CASE));
    ClearBag(); EXPECT_EQ(TH14_TryGiveUniqueItem(ITEM_COIN_CASE,FLAG_TH14_COIN_CASE),TH14_GIFT_GIVEN);
    EXPECT(FlagGet(FLAG_TH14_COIN_CASE)); EXPECT(CheckBagHasItem(ITEM_COIN_CASE,1));
    ResetEconomy(); ClearBag(); EXPECT(AddPCItem(ITEM_COIN_CASE,1));
    EXPECT_EQ(TH14_TryGiveUniqueItem(ITEM_COIN_CASE,FLAG_TH14_COIN_CASE),TH14_GIFT_ALREADY_OWNED);
    EXPECT(!CheckBagHasItem(ITEM_COIN_CASE,1));
    EXPECT_EQ(TH14_TryBuyCoins(0),TH14_PRIZE_INVALID); // Not usable from PC.
}

TEST("Three Horizons PT14 economy: invalid ids and wide script inputs have no saved side effects")
{
    ResetEconomy();
    struct SaveBlock1 *before = Alloc(sizeof(*before)); EXPECT(before != NULL);
    memcpy(before,gSaveBlock1Ptr,sizeof(*before));
    EXPECT_EQ(TH14_TryBuyItemPrize(10),TH14_PRIZE_INVALID);
    EXPECT_EQ(TH14_TryBuyMonPrize(5),TH14_PRIZE_INVALID);
    EXPECT_EQ(TH14_TryBuyCoins(2),TH14_PRIZE_INVALID);
    EXPECT_EQ(TH14_TryGiveCoins(15),TH14_PRIZE_INVALID);
    EXPECT_EQ(TH14_TryBuyDrink(3),TH14_PRIZE_INVALID);
    EXPECT_EQ(TH14_TryExchangeDrink(255),TH14_PRIZE_INVALID);
    gSpecialVar_0x8004 = 0x100; gSpecialVar_0x8005 = 0; gSpecialVar_Result = 99;
    TH14_ScriptEconomy(); EXPECT_EQ(gSpecialVar_Result,TH14_PRIZE_INVALID);
    gSpecialVar_0x8004 = 0; gSpecialVar_0x8005 = 0x100; gSpecialVar_Result = 99;
    TH14_ScriptEconomy(); EXPECT_EQ(gSpecialVar_Result,TH14_PRIZE_INVALID);
    EXPECT_EQ(memcmp(before,gSaveBlock1Ptr,sizeof(*before)),0); Free(before);
}

TEST("Three Horizons PT14 economy: all five ordinary mon prizes enter party or PC only after payment can succeed")
{
    const u16 species[] = {SPECIES_ABRA,SPECIES_CLEFAIRY,SPECIES_DRATINI,SPECIES_SCYTHER,SPECIES_PORYGON};
    const u16 costs[] = {180,500,2800,5500,9999};
    const u8 levels[] = {9,8,18,25,26};
    struct PokemonStorage *saved = gPokemonStoragePtr;
    gPokemonStoragePtr = AllocZeroed(sizeof(*gPokemonStoragePtr)); EXPECT(gPokemonStoragePtr != NULL);
    struct Pokemon filler; CreateMonWithIVs(&filler,SPECIES_ZUBAT,6,4321,OTID_STRUCT_PLAYER_ID,7);
    for (u32 id = 0; id < 5; id++) for (u32 pc = 0; pc < 2; pc++)
    {
        ResetEconomy(); memset(gPokemonStoragePtr,0,sizeof(*gPokemonStoragePtr));
        for (u32 i = 0; i < PARTY_SIZE; i++) gParties[B_TRAINER_PLAYER][i] = filler;
        if (!pc) ZeroMonData(&gParties[B_TRAINER_PLAYER][5]); CalculatePlayerPartyCount();
        SetCoins(costs[id]-1); EXPECT_EQ(TH14_TryBuyMonPrize(id),TH14_PRIZE_NO_FUNDS);
        EXPECT_EQ(GetCoins(),costs[id]-1);
        EXPECT_EQ(GetBoxMonData(GetBoxedMonPtr(0,0),MON_DATA_SPECIES),SPECIES_NONE);
        SetCoins(costs[id]); EXPECT_EQ(TH14_TryBuyMonPrize(id),TH14_PRIZE_GIVEN); EXPECT_EQ(GetCoins(),0);
        struct BoxPokemon *gift = pc ? GetBoxedMonPtr(0,0) : &gParties[B_TRAINER_PLAYER][5].box;
        EXPECT_EQ(GetBoxMonData(gift,MON_DATA_SPECIES),species[id]);
        EXPECT_EQ(GetLevelFromBoxMonExp(gift),levels[id]); EXPECT_EQ(GetBoxMonData(gift,MON_DATA_SANITY_IS_BAD_EGG),FALSE);
        EXPECT_EQ(gSpecialVar_0x8006,pc ? MON_GIVEN_TO_PC : MON_GIVEN_TO_PARTY);
        EXPECT_EQ(VarGet(VAR_TEMP_TRANSFERRED_SPECIES),species[id]);
        if (pc) { EXPECT_EQ(gSpecialVar_MonBoxId,0); EXPECT_EQ(gSpecialVar_MonBoxPos,0); }
    }
    ResetEconomy();
    for (u32 i = 0; i < PARTY_SIZE; i++) gParties[B_TRAINER_PLAYER][i] = filler;
    CalculatePlayerPartyCount();
    for (u32 box = 0; box < TOTAL_BOXES_COUNT; box++) for (u32 slot = 0; slot < IN_BOX_COUNT; slot++) gPokemonStoragePtr->boxes[box][slot] = filler.box;
    struct PokemonStorage *before = Alloc(sizeof(*before)); EXPECT(before != NULL); memcpy(before,gPokemonStoragePtr,sizeof(*before));
    const struct Pokedex dex = gSaveBlock2Ptr->pokedex;
    EXPECT_EQ(TH14_TryBuyMonPrize(4),TH14_PRIZE_NO_ROOM);
    EXPECT_EQ(GetCoins(),9999); EXPECT_EQ(memcmp(before,gPokemonStoragePtr,sizeof(*before)),0);
    EXPECT_EQ(memcmp(&dex,&gSaveBlock2Ptr->pokedex,sizeof(dex)),0);
    ZeroBoxMonAt(TOTAL_BOXES_COUNT-1,IN_BOX_COUNT-1);
    EXPECT_EQ(TH14_TryBuyMonPrize(4),TH14_PRIZE_GIVEN); EXPECT_EQ(GetCoins(),0);
    EXPECT_EQ(gSpecialVar_MonBoxId,TOTAL_BOXES_COUNT-1); EXPECT_EQ(gSpecialVar_MonBoxPos,IN_BOX_COUNT-1);
    Free(before); Free(gPokemonStoragePtr); gPokemonStoragePtr = saved;
}
#endif
