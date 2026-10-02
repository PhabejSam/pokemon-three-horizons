#include "global.h"
#include "test/battle.h"
#include "battle_util.h"
#include "battle_main.h"
#include "field_weather.h"
#include "three_horizons_chapter14.h"
#include "constants/maps.h"

#if THREE_HORIZONS
static void SetFogContext(u16 map, u8 weather)
{
    gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(map);
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(map);
    SetCurrentAndNextWeather(weather);
}

WILD_BATTLE_TEST("Three Horizons PT14 fog: horizontal Tower fog creates no battle terrain")
{
    u16 map = MAP_TH13_POKEMON_TOWER_1F;
    bool32 tower = TRUE;
    PARAMETRIZE { map = MAP_TH13_POKEMON_TOWER_1F; }
    PARAMETRIZE { map = MAP_TH13_POKEMON_TOWER_2F; }
    PARAMETRIZE { map = MAP_TH13_POKEMON_TOWER_3F; }
    PARAMETRIZE { map = MAP_TH13_POKEMON_TOWER_4F; }
    PARAMETRIZE { map = MAP_TH13_POKEMON_TOWER_5F; }
    PARAMETRIZE { map = MAP_TH13_POKEMON_TOWER_6F; }
    PARAMETRIZE { map = (TH14_MAP_GROUP << 8) | TH14_MAP_TOWER_7F; }
    PARAMETRIZE { map = MAP_ROUTE101; tower = FALSE; }
    GIVEN {
        SetFogContext(map, WEATHER_FOG_HORIZONTAL);
        PLAYER(SPECIES_WOBBUFFET) { Item(ITEM_MISTY_SEED); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_CELEBRATE); }
    } SCENE {
        if (tower) NOT MESSAGE("Mist swirls around the battlefield!");
        else MESSAGE("Mist swirls around the battlefield!");
    } THEN {
        EXPECT_EQ(gFieldTimers.terrain, tower ? B_TERRAIN_NONE : B_TERRAIN_MISTY);
        EXPECT_EQ(player->statStages[STAT_SPDEF], DEFAULT_STAT_STAGE + !tower);
        EXPECT_EQ(player->item, tower ? ITEM_MISTY_SEED : ITEM_NONE);
        EXPECT_EQ(CheckDynamicMoveType(&gParties[B_TRAINER_PLAYER][0], MOVE_TERRAIN_PULSE, 0, MON_IN_BATTLE), tower ? TYPE_NORMAL : TYPE_FAIRY);
        EXPECT_EQ(CheckDynamicMoveType(&gParties[B_TRAINER_PLAYER][0], MOVE_TERRAIN_PULSE, 0, MON_OUTSIDE_BATTLE), tower ? TYPE_NORMAL : TYPE_FAIRY);
        EXPECT_EQ(GetCurrentWeather(), WEATHER_FOG_HORIZONTAL);
        EXPECT(!(gBattleWeather & B_WEATHER_FOG));
        SetCurrentAndNextWeather(WEATHER_NONE);
    }
}

WILD_BATTLE_TEST("Three Horizons PT14 fog: damage types accuracy and stats match clear weather", s16 dragonDamage; s16 pulseDamage)
{
    u8 weather = WEATHER_NONE;
    PARAMETRIZE { weather = WEATHER_NONE; }
    PARAMETRIZE { weather = WEATHER_FOG_HORIZONTAL; }
    PARAMETRIZE { weather = WEATHER_FOG_DIAGONAL; }
    GIVEN {
        SetFogContext(MAP_TH13_POKEMON_TOWER_3F, weather);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_DRAGON_CLAW); MOVE(opponent, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_TERRAIN_PULSE); MOVE(opponent, MOVE_CELEBRATE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_DRAGON_CLAW, player);
        HP_BAR(opponent, captureDamage: &results[i].dragonDamage);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TERRAIN_PULSE, player);
        HP_BAR(opponent, captureDamage: &results[i].pulseDamage);
    } THEN {
        EXPECT_EQ(gFieldTimers.terrain, B_TERRAIN_NONE);
        EXPECT_EQ(CheckDynamicMoveType(&gParties[B_TRAINER_PLAYER][0], MOVE_TERRAIN_PULSE, 0, MON_IN_BATTLE), TYPE_NORMAL);
        struct BattleCalcValues cv = {.battlerAtk = 0, .battlerDef = 1, .move = MOVE_HYDRO_PUMP};
        EXPECT_EQ(GetTotalAccuracy(&cv, gBattleWeather), 80);
        for (u32 battler = 0; battler < 2; battler++)
            for (u32 stat = STAT_ATK; stat <= STAT_EVASION; stat++)
                EXPECT_EQ(gBattleMons[battler].statStages[stat], DEFAULT_STAT_STAGE);
        EXPECT_EQ(GetCurrentWeather(), weather);
        SetCurrentAndNextWeather(WEATHER_NONE);
    } FINALLY {
        EXPECT_EQ(results[0].dragonDamage, results[1].dragonDamage);
        EXPECT_EQ(results[0].dragonDamage, results[2].dragonDamage);
        EXPECT_EQ(results[0].pulseDamage, results[1].pulseDamage);
        EXPECT_EQ(results[0].pulseDamage, results[2].pulseDamage);
    }
}

WILD_BATTLE_TEST("Three Horizons PT14 fog: explicit terrain still works from moves and abilities")
{
    bool32 viaAbility = FALSE;
    PARAMETRIZE { viaAbility = FALSE; }
    PARAMETRIZE { viaAbility = TRUE; }
    GIVEN {
        SetFogContext(MAP_TH13_POKEMON_TOWER_6F, WEATHER_FOG_HORIZONTAL);
        PLAYER(SPECIES_TAPU_FINI) { Ability(viaAbility ? ABILITY_MISTY_SURGE : ABILITY_TELEPATHY); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, viaAbility ? MOVE_CELEBRATE : MOVE_MISTY_TERRAIN); MOVE(opponent, MOVE_TOXIC); }
    } THEN {
        EXPECT_EQ(gFieldTimers.terrain, B_TERRAIN_MISTY);
        EXPECT_EQ(player->status1, STATUS1_NONE);
        EXPECT_EQ(CheckDynamicMoveType(&gParties[B_TRAINER_PLAYER][0], MOVE_TERRAIN_PULSE, 0, MON_IN_BATTLE), TYPE_FAIRY);
        EXPECT_EQ(GetCurrentWeather(), WEATHER_FOG_HORIZONTAL);
        SetCurrentAndNextWeather(WEATHER_NONE);
    }
}

// Exercise the public dynamic-type implementation without requiring battle allocation.
TEST("Three Horizons PT14 fog: Terrain Pulse preview respects Tower boundary")
{
    struct Pokemon mon;
    CreateMonWithIVs(&mon, SPECIES_WOBBUFFET, 30, 0, OTID_STRUCT_PLAYER_ID, 31);
    const u16 maps[] = {MAP_TH13_POKEMON_TOWER_1F, MAP_TH13_POKEMON_TOWER_6F,
        (TH14_MAP_GROUP << 8) | TH14_MAP_TOWER_7F, MAP_ROUTE101, MAP_TH13_LAVENDER_TOWN};
    for (u32 i = 0; i < ARRAY_COUNT(maps); i++)
        for (u32 w = 0; w < 3; w++)
        {
            const u8 weather[] = {WEATHER_NONE, WEATHER_FOG_HORIZONTAL, WEATHER_FOG_DIAGONAL};
            SetFogContext(maps[i], weather[w]);
            EXPECT_EQ(GetDynamicMoveType(&mon, MOVE_TERRAIN_PULSE, 0, ABILITY_NONE, HOLD_EFFECT_NONE, MON_OUTSIDE_BATTLE),
                i >= 3 && w != 0 ? TYPE_FAIRY : TYPE_NORMAL);
        }
    SetCurrentAndNextWeather(WEATHER_NONE);
}

TEST("Three Horizons PT14 fog: all map identities are bounded to the seven Tower floors")
{
    const u16 towers[] = {MAP_TH13_POKEMON_TOWER_1F, MAP_TH13_POKEMON_TOWER_2F,
        MAP_TH13_POKEMON_TOWER_3F, MAP_TH13_POKEMON_TOWER_4F, MAP_TH13_POKEMON_TOWER_5F,
        MAP_TH13_POKEMON_TOWER_6F, (TH14_MAP_GROUP << 8) | TH14_MAP_TOWER_7F};
    for (u32 group = 0; group <= 255; group++)
        for (u32 number = 0; number <= 255; number++)
        {
            bool32 expected = FALSE;
            for (u32 floor = 0; floor < ARRAY_COUNT(towers); floor++)
                expected |= ((group << 8) | number) == towers[floor];
            EXPECT_EQ(TH14_IsTowerMap(group, number), expected);
        }
}
#endif
