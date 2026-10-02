// Approved Appendix B Celadon stock and transactions. Prices for money
// purchases come from GetItemPrice; no global item-price override.

#define TH14_SHOP_COUNT 5
#define TH14_SHOP_CAPACITY 10

static const struct { u8 shop, badges; u16 item, flag; } sCeladonStock[] =
{
    {0, 0, ITEM_GREAT_BALL, 0},
    {0, 0, ITEM_SUPER_POTION, 0},
    {0, 0, ITEM_REVIVE, 0},
    {0, 0, ITEM_ANTIDOTE, 0},
    {0, 0, ITEM_PARALYZE_HEAL, 0},
    {0, 0, ITEM_AWAKENING, 0},
    {0, 0, ITEM_BURN_HEAL, 0},
    {0, 0, ITEM_ICE_HEAL, 0},
    {0, 0, ITEM_SUPER_REPEL, 0},
    {1, 3, ITEM_TM_ROAR, 0},
    {1, 3, ITEM_TM_DIG, 0},
    {1, 3, ITEM_TM_BRICK_BREAK, 0},
    {1, 3, ITEM_TM_SECRET_POWER, 0},
    {1, 3, ITEM_TM_ATTRACT, 0},
    {1, 4, ITEM_TM_HYPER_BEAM, 0},
    {1, 4, ITEM_TM_PROTECT, 0},
    {1, 4, ITEM_TM_REST, 0},
    {2, 0, ITEM_POKE_DOLL, 0},
    {2, 0, ITEM_RETRO_MAIL, 0},
    {2, 0, ITEM_FIRE_STONE, 0},
    {2, 0, ITEM_THUNDER_STONE, 0},
    {2, 0, ITEM_WATER_STONE, 0},
    {2, 0, ITEM_LEAF_STONE, 0},
    {3, 0, ITEM_X_ATTACK, 0},
    {3, 0, ITEM_X_DEFENSE, 0},
    {3, 0, ITEM_X_SPEED, 0},
    {3, 0, ITEM_X_SP_ATK, 0},
    {3, 0, ITEM_X_ACCURACY, 0},
    {3, 0, ITEM_GUARD_SPEC, 0},
    {3, 0, ITEM_DIRE_HIT, 0},
    {4, 0, ITEM_HP_UP, 0},
    {4, 0, ITEM_PROTEIN, 0},
    {4, 0, ITEM_IRON, 0},
    {4, 0, ITEM_CALCIUM, 0},
    {4, 0, ITEM_ZINC, 0},
    {4, 0, ITEM_CARBOS, 0},
};

static const struct { u16 item, coins; bool8 reusable; } sCeladonItemPrizes[] =
{
    {ITEM_TM_ICE_BEAM, 4000, TRUE},
    {ITEM_TM_IRON_TAIL, 3500, TRUE},
    {ITEM_TM_THUNDERBOLT, 4000, TRUE},
    {ITEM_TM_SHADOW_BALL, 4500, TRUE},
    {ITEM_TM_FLAMETHROWER, 4000, TRUE},
    {ITEM_SMOKE_BALL, 800, FALSE},
    {ITEM_MIRACLE_SEED, 1000, FALSE},
    {ITEM_CHARCOAL, 1000, FALSE},
    {ITEM_MYSTIC_WATER, 1000, FALSE},
    {ITEM_YELLOW_FLUTE, 1600, FALSE},
};

static const struct { u16 species, coins; u8 level; } sCeladonMonPrizes[] =
{
    {SPECIES_ABRA, 180, 9},
    {SPECIES_CLEFAIRY, 500, 8},
    {SPECIES_DRATINI, 2800, 18},
    {SPECIES_SCYTHER, 5500, 25},
    {SPECIES_PORYGON, 9999, 26},
};

static const struct { u16 coins; u32 price; } sCeladonCoinBundles[] =
{
    {50, 1000},
    {500, 10000},
};

static const struct { u16 coins, flag; } sCeladonCoinGifts[] =
{
    {10, FLAG_TH14_GAMBLER_COINS_10},
    {20, FLAG_TH14_GAMBLER_COINS_20_A},
    {20, FLAG_TH14_GAMBLER_COINS_20_B},
    {10, FLAG_TH14_PICKUP_13},
    {10, FLAG_TH14_PICKUP_14},
    {20, FLAG_TH14_PICKUP_15},
    {10, FLAG_TH14_PICKUP_16},
    {10, FLAG_TH14_PICKUP_17},
    {20, FLAG_TH14_PICKUP_18},
    {10, FLAG_TH14_PICKUP_19},
    {10, FLAG_TH14_PICKUP_20},
    {10, FLAG_TH14_PICKUP_21},
    {40, FLAG_TH14_PICKUP_22},
    {100, FLAG_TH14_PICKUP_23},
    {10, FLAG_TH14_PICKUP_24},
};

static const struct { u16 item, reward, flag; } sCeladonDrinks[] =
{
    {ITEM_FRESH_WATER, ITEM_TM_LIGHT_SCREEN, FLAG_TH14_ROOF_FRESH_WATER},
    {ITEM_SODA_POP, ITEM_TM_SAFEGUARD, FLAG_TH14_ROOF_SODA_POP},
    {ITEM_LEMONADE, ITEM_TM_REFLECT, FLAG_TH14_ROOF_LEMONADE},
};
