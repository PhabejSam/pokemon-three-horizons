#include "global.h"
#include "test/test.h"
#include "three_horizons.h"
#include "pokemon.h"
#include "event_data.h"
#include "constants/three_horizons.h"
#include "constants/items.h"
#include "constants/moves.h"

#if THREE_HORIZONS
TEST("Three Horizons capture rewards include legendary and mythical species only")
{
    EXPECT(TH_IsConfigurableCapture(SPECIES_ARTICUNO));
    EXPECT(TH_IsConfigurableCapture(SPECIES_MEWTWO));
    EXPECT(TH_IsConfigurableCapture(SPECIES_MEW));
    EXPECT(TH_IsConfigurableCapture(SPECIES_DEOXYS));
    EXPECT(!TH_IsConfigurableCapture(SPECIES_ZUBAT));
    EXPECT(!TH_IsConfigurableCapture(SPECIES_NONE));
    EXPECT(!TH_IsConfigurableCapture(NUM_SPECIES));
}

TEST("Three Horizons caught Pokemon retain identity while legal stats change")
{
    struct Pokemon mon, before;
    struct THPartnerOptions options;
    u16 move = MOVE_ICE_BEAM, item = ITEM_ORAN_BERRY, ball = BALL_ULTRA;
    u16 stage = VarGet(VAR_TH_STAGE);
    CreateMonWithIVs(&mon, SPECIES_ARTICUNO, 35, 987654, OTID_STRUCT_PLAYER_ID, 12);
    SetMonData(&mon, MON_DATA_MOVE1, &move);
    SetMonData(&mon, MON_DATA_HELD_ITEM, &item);
    SetMonData(&mon, MON_DATA_POKEBALL, &ball);
    before = mon;
    TH_ReadMonOptions(&mon, &options);
    options.nature = NATURE_TIMID;
    options.shiny = TRUE;
    options.ivs[STAT_ATK] = 0;
    options.ivs[STAT_SPEED] = 31;
    options.evs[STAT_SPATK] = 252;
    options.evs[STAT_SPEED] = 252;
    options.evs[STAT_HP] = 6;
    EXPECT(TH_ApplyCaughtMonOptions(&mon, &options));
    EXPECT_EQ(GetMonData(&mon, MON_DATA_LEVEL), 35);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_EXP), GetMonData(&before, MON_DATA_EXP));
    EXPECT_EQ(GetMonData(&mon, MON_DATA_PERSONALITY), GetMonData(&before, MON_DATA_PERSONALITY));
    EXPECT_EQ(GetMonData(&mon, MON_DATA_OT_ID), GetMonData(&before, MON_DATA_OT_ID));
    EXPECT_EQ(GetMonData(&mon, MON_DATA_MOVE1), MOVE_ICE_BEAM);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_HELD_ITEM), ITEM_ORAN_BERRY);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_POKEBALL), BALL_ULTRA);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_HIDDEN_NATURE), NATURE_TIMID);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_IS_SHINY), TRUE);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_ATK_IV), 0);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_SPEED_EV), 252);
    EXPECT_EQ(VarGet(VAR_TH_STAGE), stage);
    before = mon;
    options.evs[STAT_HP] = 7;
    EXPECT(!TH_ApplyCaughtMonOptions(&mon, &options));
    EXPECT_EQ(memcmp(&mon, &before, sizeof(mon)), 0);
    options.evs[STAT_HP] = 6;
    options.ivs[STAT_DEF] = 32;
    EXPECT(!TH_ApplyCaughtMonOptions(&mon, &options));
    EXPECT_EQ(memcmp(&mon, &before, sizeof(mon)), 0);
    options.ivs[STAT_DEF] = 0;
    options.evs[STAT_HP] = 253;
    EXPECT(!TH_ApplyCaughtMonOptions(&mon, &options));
    EXPECT_EQ(memcmp(&mon, &before, sizeof(mon)), 0);
}
#endif
