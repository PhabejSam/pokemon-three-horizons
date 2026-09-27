#include "global.h"
#include "test/test.h"
#include "three_horizons.h"
#include "event_data.h"
#include "pokemon.h"
#include "constants/trainers.h"
#include "constants/three_horizons.h"
#if THREE_HORIZONS
TEST("Three Horizons playtest12 Rocket retry requires both wins without a free heal")
{
    FlagClear(FLAG_TH_ROCKET_DUO);
    CreateMon(&gPlayerParty[0], SPECIES_PIKACHU, 20, USE_RANDOM_IVS, FALSE, 0, OT_ID_PLAYER_ID, 0);
    u16 hp = 1;
    SetMonData(&gPlayerParty[0], MON_DATA_HP, &hp);
    for (u32 wins = 0; wins < 4; wins++)
    {
        FlagClear(TRAINER_FLAGS_START + TRAINER_TH11_JESSIE);
        FlagClear(TRAINER_FLAGS_START + TRAINER_TH11_JAMES);
        if (wins & 1) FlagSet(TRAINER_FLAGS_START + TRAINER_TH11_JESSIE);
        if (wins & 2) FlagSet(TRAINER_FLAGS_START + TRAINER_TH11_JAMES);
        TH12_CompleteRocketPair();
        EXPECT_EQ(gSpecialVar_Result, wins == 3);
        EXPECT_EQ(FlagGet(FLAG_TH_ROCKET_DUO), wins == 3);
        TH12_BeginRocketPair();
        EXPECT_EQ(FlagGet(TRAINER_FLAGS_START + TRAINER_TH11_JESSIE), wins == 3);
        EXPECT_EQ(FlagGet(TRAINER_FLAGS_START + TRAINER_TH11_JAMES), wins == 3);
        EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_HP), 1);
    }
    FlagClear(FLAG_TH_ROCKET_DUO);
    TH12_BeginRocketPair();
}
#endif
