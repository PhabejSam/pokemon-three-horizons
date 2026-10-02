#include "global.h"
#include "pokemon_storage_system.h"
#include "test/test.h"

#if THREE_HORIZONS
TEST("Three Horizons PT14 layout: battery fields retain baseline offsets")
{
    EXPECT_EQ(offsetof(struct SaveBlock1, pos), 0x00);
    EXPECT_EQ(offsetof(struct SaveBlock1, location), 0x04);
    EXPECT_EQ(offsetof(struct SaveBlock1, playerPartyCount), 0x234);
    EXPECT_EQ(offsetof(struct SaveBlock1, playerParty), 0x238);
    EXPECT_EQ(offsetof(struct SaveBlock1, money), 0x490);
    EXPECT_EQ(offsetof(struct SaveBlock1, coins), 0x494);
    EXPECT_EQ(offsetof(struct SaveBlock1, registeredItem), 0x496);
    EXPECT_EQ(offsetof(struct SaveBlock1, pcItems), 0x498);
    EXPECT_EQ(offsetof(struct SaveBlock1, bag), 0x560);
    EXPECT_EQ(offsetof(struct SaveBlock1, trainerRematchStepCounter), 0x9C8);
    EXPECT_EQ(offsetof(struct SaveBlock1, trainerRematches), 0x9CA);
    EXPECT_EQ(offsetof(struct SaveBlock1, flags), 0x1270);
    EXPECT_EQ(offsetof(struct SaveBlock1, vars), 0x139C);
    EXPECT_EQ(offsetof(struct SaveBlock1, dexSeen), 0x3598);
    EXPECT_EQ(offsetof(struct SaveBlock1, dexCaught), 0x3619);
    EXPECT_EQ(offsetof(struct SaveBlock2, pokedex), 0x18);
    EXPECT_EQ(offsetof(struct SaveBlock2, encryptionKey), 0xAC);
    EXPECT_EQ(offsetof(struct PokemonStorage, boxes), 4);
    EXPECT_EQ(sizeof(((struct WarpData *)0)->mapGroup), 1);
    EXPECT_EQ(sizeof(((struct WarpData *)0)->mapNum), 1);
    EXPECT(((struct WarpData){.mapGroup = -1}).mapGroup < 0);
    EXPECT(((struct WarpData){.mapNum = -1}).mapNum < 0);
}
#endif
