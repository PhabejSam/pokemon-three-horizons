#include "global.h"
#include "test/test.h"
#include "daycare.h"
#include "event_data.h"
#include "party_menu.h"
#include "pokemon.h"
#include "constants/items.h"

#if THREE_HORIZONS
extern void PutMonInRoute5Daycare(void);
extern bool8 IsThereMonInRoute5Daycare(void);
extern u8 GetNumLevelsGainedForRoute5DaycareMon(void);
extern void GetCostToWithdrawRoute5DaycareMon(void);
extern u16 TakePokemonFromRoute5Daycare(void);

TEST("Three Horizons playtest13 Daycare deposit growth and return")
{
    InitEventData();
    ZeroPlayerPartyMons();
    memset(&gSaveBlock1Ptr->daycare, 0, sizeof(gSaveBlock1Ptr->daycare));
    CreateMon(&gParties[B_TRAINER_PLAYER][0], SPECIES_PIKACHU, 10, 20, TRUE, 12345, OT_ID_PLAYER_ID, 0);
    CreateMon(&gParties[B_TRAINER_PLAYER][1], SPECIES_MAGIKARP, 5, 20, TRUE, 67890, OT_ID_PLAYER_ID, 0);
    u16 item = ITEM_ORAN_BERRY;
    SetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_HELD_ITEM, &item);
    CalculatePlayerPartyCount();
    gPartyMenu.slotId = 0;
    EXPECT_EQ(IsThereMonInRoute5Daycare(), FALSE);
    PutMonInRoute5Daycare();
    EXPECT_EQ(IsThereMonInRoute5Daycare(), TRUE);
    EXPECT_EQ(CalculatePlayerPartyCount(), 1);
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_SPECIES), SPECIES_MAGIKARP);
    EXPECT_EQ(GetBoxMonData(&gSaveBlock1Ptr->daycare.mons[0].mon, MON_DATA_PERSONALITY), 12345);
    EXPECT_EQ(GetNumLevelsGainedForRoute5DaycareMon(), 0);
    GetCostToWithdrawRoute5DaycareMon();
    EXPECT_EQ(gSpecialVar_0x8005, 100);
    // One real overworld step completes exactly the next level's experience.
    u32 growth = gSpeciesInfo[SPECIES_PIKACHU].growthRate;
    gSaveBlock1Ptr->daycare.mons[0].steps = gExperienceTables[growth][11] - gExperienceTables[growth][10] - 1;
    IncrementDaycareSteps();
    EXPECT_EQ(GetNumLevelsGainedForRoute5DaycareMon(), 1);
    GetCostToWithdrawRoute5DaycareMon();
    EXPECT_EQ(gSpecialVar_0x8005, 200);
    EXPECT_EQ(TakePokemonFromRoute5Daycare(), SPECIES_PIKACHU);
    EXPECT_EQ(CalculatePlayerPartyCount(), 2);
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][1], MON_DATA_LEVEL), 11);
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][1], MON_DATA_PERSONALITY), 12345);
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][1], MON_DATA_HELD_ITEM), ITEM_ORAN_BERRY);
    EXPECT_EQ(IsThereMonInRoute5Daycare(), FALSE);
}

TEST("Three Horizons playtest13 Daycare reads existing serialized storage")
{
    ZeroPlayerPartyMons();
    memset(&gSaveBlock1Ptr->daycare, 0, sizeof(gSaveBlock1Ptr->daycare));
    struct Pokemon saved;
    CreateMon(&saved, SPECIES_PIKACHU, 10, 20, TRUE, 11223, OT_ID_PLAYER_ID, 0);
    gSaveBlock1Ptr->daycare.mons[0].mon = saved.box;
    CreateMon(&saved, SPECIES_MAGIKARP, 5, 20, TRUE, 99887, OT_ID_PLAYER_ID, 0);
    gSaveBlock1Ptr->daycare.mons[1].mon = saved.box;
    gSaveBlock1Ptr->daycare.mons[1].steps = 42;
    struct DaycareMon untouched = gSaveBlock1Ptr->daycare.mons[1];
    EXPECT_EQ(IsThereMonInRoute5Daycare(), TRUE);
    EXPECT_EQ(TakePokemonFromRoute5Daycare(), SPECIES_PIKACHU);
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_PERSONALITY), 11223);
    EXPECT_EQ(memcmp(&untouched, &gSaveBlock1Ptr->daycare.mons[1], sizeof(untouched)), 0);
}
#endif
