#include "global.h"
#include "test/test.h"
#include "three_horizons.h"
#include "pokemon.h"
#include "event_data.h"
#include "item.h"
#include "field_move.h"
#include "party_menu.h"

#if THREE_HORIZONS
TEST("Three Horizons playtest12 Cut needs HM01 badge compatibility and a conscious non Egg")
{
    struct Pokemon mon, before;
    ClearBag();
    FlagClear(FLAG_BADGE02_GET);
    CreateMon(&mon, SPECIES_BULBASAUR, 5, 0, OTID_STRUCT_PLAYER_ID);
    SetMonMoveSlot(&mon, MOVE_TACKLE, 0);
    SetMonMoveSlot(&mon, MOVE_NONE, 1);
    SetMonMoveSlot(&mon, MOVE_NONE, 2);
    SetMonMoveSlot(&mon, MOVE_NONE, 3);
    EXPECT(!TH_CanUseFieldMove(&mon, FIELD_MOVE_CUT));
    EXPECT(AddBagItem(ITEM_HM01, 1));
    EXPECT(!TH_CanUseFieldMove(&mon, FIELD_MOVE_CUT));
    FlagSet(FLAG_BADGE02_GET);
    before = mon;
    EXPECT(TH_CanUseFieldMove(&mon, FIELD_MOVE_CUT));
    EXPECT_EQ(memcmp(&before, &mon, sizeof(mon)), 0);
    EXPECT(!MonKnowsMove(&mon, MOVE_CUT));
    u32 value = 0;
    SetMonData(&mon, MON_DATA_HP, &value);
    EXPECT(!TH_CanUseFieldMove(&mon, FIELD_MOVE_CUT));
    mon = before;
    value = TRUE;
    SetMonData(&mon, MON_DATA_IS_EGG, &value);
    EXPECT(!TH_CanUseFieldMove(&mon, FIELD_MOVE_CUT));
    CreateMon(&mon, SPECIES_MAGIKARP, 5, 0, OTID_STRUCT_PLAYER_ID);
    SetMonMoveSlot(&mon, MOVE_CUT, 0);
    EXPECT(!TH_CanUseFieldMove(&mon, FIELD_MOVE_CUT));
    mon = before;
    ClearBag();
    SetMonMoveSlot(&mon, MOVE_CUT, 0);
    EXPECT(!TH_CanUseFieldMove(&mon, FIELD_MOVE_CUT));
    FlagClear(FLAG_BADGE02_GET);
}

TEST("Three Horizons playtest12 field lookup selects the first eligible party member without teaching moves")
{
    struct Pokemon saved[PARTY_SIZE];
    memcpy(saved, gPlayerParty, sizeof(saved));
    memset(gPlayerParty, 0, sizeof(saved));
    ClearBag();
    AddBagItem(ITEM_HM01, 1);
    FlagSet(FLAG_BADGE02_GET);
    CreateMon(&gPlayerParty[0], SPECIES_MAGIKARP, 5, 0, OTID_STRUCT_PLAYER_ID);
    CreateMon(&gPlayerParty[1], SPECIES_BULBASAUR, 5, 0, OTID_STRUCT_PLAYER_ID);
    CreateMon(&gPlayerParty[2], SPECIES_CHARMANDER, 5, 0, OTID_STRUCT_PLAYER_ID);
    u32 hp = 0;
    SetMonData(&gPlayerParty[1], MON_DATA_HP, &hp);
    EXPECT_EQ(TH_FindFieldMoveUser(FIELD_MOVE_CUT), 2);
    EXPECT(!MonKnowsMove(&gPlayerParty[2], MOVE_CUT));
    EXPECT_EQ(TH_FindFieldMoveUser(FIELD_MOVE_SURF), PARTY_SIZE);
    SetMonData(&gPlayerParty[2], MON_DATA_HP, &hp);
    EXPECT_EQ(TH_FindFieldMoveUser(FIELD_MOVE_CUT), PARTY_SIZE);
    memcpy(gPlayerParty, saved, sizeof(saved));
    CalculatePlayerPartyCount();
    FlagClear(FLAG_BADGE02_GET);
    ClearBag();
}

TEST("Three Horizons playtest12 HM moves can be replaced while other move slots remain intact")
{
    struct Pokemon mon;
    CreateMon(&mon, SPECIES_CHARMANDER, 10, 0, OTID_STRUCT_PLAYER_ID);
    SetMonMoveSlot(&mon, MOVE_ROCK_SMASH, 0);
    SetMonMoveSlot(&mon, MOVE_CUT, 1);
    EXPECT(!CannotForgetMove(MOVE_ROCK_SMASH));
    EXPECT(!CannotForgetMove(MOVE_CUT));
    if (!CannotForgetMove(GetMonData(&mon, MON_DATA_MOVE1)))
        SetMonMoveSlot(&mon, MOVE_EMBER, 0);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_MOVE1), MOVE_EMBER);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_MOVE2), MOVE_CUT);
}
#endif
