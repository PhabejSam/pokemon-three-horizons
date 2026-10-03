#include "global.h"
#include "test/battle.h"
#include "battle_util.h"
#include "battle_ai_util.h"
#include "battle_anim_scripts.h"

#if THREE_HORIZONS
TEST("Three Horizons PT14.1: Hyper Beam preserves core properties")
{
    EXPECT_EQ(GetMovePower(MOVE_HYPER_BEAM), 150);
    EXPECT_EQ(GetMoveType(MOVE_HYPER_BEAM), TYPE_NORMAL);
    EXPECT_EQ(GetMoveAccuracy(MOVE_HYPER_BEAM), 90);
    EXPECT_EQ(GetMovePP(MOVE_HYPER_BEAM), 5);
    EXPECT_EQ(GetMoveTarget(MOVE_HYPER_BEAM), TARGET_SELECTED);
    EXPECT_EQ(GetMoveEffect(MOVE_HYPER_BEAM), EFFECT_HIT);
    EXPECT(MoveHasAdditionalEffectSelf(MOVE_HYPER_BEAM, MOVE_EFFECT_RECHARGE));
    EXPECT_EQ(gMovesInfo[MOVE_HYPER_BEAM].battleAnimScript, gBattleAnimMove_HyperBeam);
}

SINGLE_BATTLE_TEST("Three Horizons PT14.1: Hyper Beam category responds to current stages and ties")
{
    u16 attack=150, special=100;
    enum Move setup=MOVE_CELEBRATE, opposingSetup=MOVE_CELEBRATE;
    bool32 physical=TRUE;
    PARAMETRIZE { attack=150; special=100; }
    PARAMETRIZE { attack=100; special=150; physical=FALSE; }
    PARAMETRIZE { attack=100; special=100; physical=FALSE; }
    PARAMETRIZE { attack=100; special=150; setup=MOVE_SWORDS_DANCE; }
    PARAMETRIZE { setup=MOVE_NASTY_PLOT; physical=FALSE; }
    PARAMETRIZE { opposingSetup=MOVE_CHARM; physical=FALSE; }
    PARAMETRIZE { attack=100; special=150; opposingSetup=MOVE_EERIE_IMPULSE; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { MaxHP(1000); HP(1000); Attack(attack); SpAttack(special); }
        OPPONENT(SPECIES_WOBBUFFET) { MaxHP(1000); HP(1000); Defense(100); SpDefense(100); }
    } WHEN {
        TURN { MOVE(player, setup); MOVE(opponent, opposingSetup); }
        TURN { MOVE(player, MOVE_HYPER_BEAM); MOVE(opponent, physical ? MOVE_COUNTER : MOVE_MIRROR_COAT); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_HYPER_BEAM, player);
        HP_BAR(opponent);
        ANIMATION(ANIM_TYPE_MOVE, physical ? MOVE_COUNTER : MOVE_MIRROR_COAT, opponent);
        HP_BAR(player);
    } THEN {
        SetDynamicMoveCategory(0,1,MOVE_HYPER_BEAM);
        EXPECT_EQ(GetBattleMoveCategory(MOVE_HYPER_BEAM),physical ? DAMAGE_CATEGORY_PHYSICAL : DAMAGE_CATEGORY_SPECIAL);
        SetDynamicMoveCategory(0,1,MOVE_WATER_GUN);
        EXPECT_EQ(GetBattleMoveCategory(MOVE_WATER_GUN),DAMAGE_CATEGORY_SPECIAL);
        SetDynamicMoveCategory(0,1,MOVE_TACKLE);
        EXPECT_EQ(GetBattleMoveCategory(MOVE_TACKLE),DAMAGE_CATEGORY_PHYSICAL);
        SetDynamicMoveCategory(0,1,MOVE_PHOTON_GEYSER);
        EXPECT_EQ(GetBattleMoveCategory(MOVE_PHOTON_GEYSER),physical ? DAMAGE_CATEGORY_PHYSICAL : DAMAGE_CATEGORY_SPECIAL);
    }
}

SINGLE_BATTLE_TEST("Three Horizons PT14.1: natural Gyarados and Alakazam choose appropriate Hyper Beam offense")
{
    enum Species species=SPECIES_GYARADOS;
    bool32 physical=TRUE;
    PARAMETRIZE { species=SPECIES_GYARADOS; }
    PARAMETRIZE { species=SPECIES_ALAKAZAM; physical=FALSE; }
    GIVEN {
        PLAYER(species) { MaxHP(1000); HP(1000); }
        OPPONENT(SPECIES_WOBBUFFET) { MaxHP(1000); HP(1000); }
    } WHEN {
        TURN { MOVE(player,MOVE_HYPER_BEAM); MOVE(opponent,physical ? MOVE_COUNTER : MOVE_MIRROR_COAT); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE,MOVE_HYPER_BEAM,player);
        HP_BAR(opponent);
        ANIMATION(ANIM_TYPE_MOVE,physical ? MOVE_COUNTER : MOVE_MIRROR_COAT,opponent);
        HP_BAR(player);
    }
}

SINGLE_BATTLE_TEST("Three Horizons PT14.1: actual and AI Hyper Beam damage use the selected target defense", s16 damage; s32 aiDamage)
{
    bool32 physical=TRUE;
    u16 defense=100,specialDefense=100;
    PARAMETRIZE { }
    PARAMETRIZE { defense=200; }
    PARAMETRIZE { specialDefense=200; }
    PARAMETRIZE { physical=FALSE; }
    PARAMETRIZE { physical=FALSE; defense=200; }
    PARAMETRIZE { physical=FALSE; specialDefense=200; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Attack(physical ? 150 : 100); SpAttack(physical ? 100 : 150); }
        OPPONENT(SPECIES_WOBBUFFET) { MaxHP(1000); HP(1000); Defense(defense); SpDefense(specialDefense); }
    } WHEN {
        TURN { MOVE(player,MOVE_HYPER_BEAM); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE,MOVE_HYPER_BEAM,player);
        HP_BAR(opponent,captureDamage:&results[i].damage);
    } THEN {
        struct AiCalcValues calc={.move=MOVE_HYPER_BEAM};
        Test_MgbaPrintf("PT141 damage case %u physical %u atk %u spa %u def %u spd %u", i, physical,
            gBattleMons[0].attack, gBattleMons[0].spAttack, gBattleMons[1].defense, gBattleMons[1].spDefense);
        results[i].aiDamage=AI_CalcDamage(&calc,0,1).median;
        Test_MgbaPrintf("PT141 actual %d AI %d", results[i].damage, results[i].aiDamage);
        EXPECT_GT(results[i].aiDamage,0);
        EXPECT_EQ((enum DamageCategory)gBattleStruct->dynamicMoveCategory,DAMAGE_CATEGORY_NONE);
        EXPECT(HasMoveWithCategory(0,physical ? DAMAGE_CATEGORY_PHYSICAL : DAMAGE_CATEGORY_SPECIAL));
        EXPECT(!HasMoveWithCategory(0,physical ? DAMAGE_CATEGORY_SPECIAL : DAMAGE_CATEGORY_PHYSICAL));
        EXPECT(HasOnlyMovesWithCategory(0,physical ? DAMAGE_CATEGORY_PHYSICAL : DAMAGE_CATEGORY_SPECIAL,TRUE));
    } FINALLY {
        EXPECT_GT(results[0].damage,results[1].damage);
        EXPECT_EQ(results[0].damage,results[2].damage);
        EXPECT_EQ(results[3].damage,results[4].damage);
        EXPECT_GT(results[3].damage,results[5].damage);
        EXPECT_GT(results[0].aiDamage,results[1].aiDamage);
        EXPECT_EQ(results[0].aiDamage,results[2].aiDamage);
        EXPECT_EQ(results[3].aiDamage,results[4].aiDamage);
        EXPECT_GT(results[3].aiDamage,results[5].aiDamage);
    }
}

#define RECHARGE_CASES \
    PARAMETRIZE { move=MOVE_HYPER_BEAM; } \
    PARAMETRIZE { move=MOVE_GIGA_IMPACT; } \
    PARAMETRIZE { move=MOVE_BLAST_BURN; } \
    PARAMETRIZE { move=MOVE_HYDRO_CANNON; } \
    PARAMETRIZE { move=MOVE_FRENZY_PLANT; } \
    PARAMETRIZE { move=MOVE_ROCK_WRECKER; } \
    PARAMETRIZE { move=MOVE_ROAR_OF_TIME; } \
    PARAMETRIZE { move=MOVE_PRISMATIC_LASER; } \
    PARAMETRIZE { move=MOVE_METEOR_ASSAULT; } \
    PARAMETRIZE { move=MOVE_ETERNABEAM; }

SINGLE_BATTLE_TEST("Three Horizons PT14.1: every standard recharge move KO allows the next attack")
{
    enum Move move=MOVE_HYPER_BEAM;
    RECHARGE_CASES
    GIVEN {
        ASSUME(MoveHasAdditionalEffectSelf(move,MOVE_EFFECT_RECHARGE));
        PLAYER(SPECIES_WOBBUFFET) { Attack(150); SpAttack(100); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(1); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player,move); SEND_OUT(opponent,1); }
        TURN { MOVE(player,MOVE_TACKLE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE,move,player);
        MESSAGE("The opposing Wobbuffet fainted!");
        NOT MESSAGE("Wobbuffet must recharge!");
        ANIMATION(ANIM_TYPE_MOVE,MOVE_TACKLE,player);
        HP_BAR(opponent);
    }
}

SINGLE_BATTLE_TEST("Three Horizons PT14.1: every standard recharge move on survival requires exactly one recharge")
{
    enum Move move=MOVE_HYPER_BEAM;
    RECHARGE_CASES
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Attack(100); SpAttack(150); }
        OPPONENT(SPECIES_WOBBUFFET) { MaxHP(1000); HP(1000); }
    } WHEN {
        TURN { MOVE(player,move); }
        TURN { SKIP_TURN(player); }
        TURN { MOVE(player,MOVE_TACKLE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE,move,player);
        HP_BAR(opponent);
        MESSAGE("Wobbuffet must recharge!");
        ANIMATION(ANIM_TYPE_MOVE,MOVE_TACKLE,player);
        HP_BAR(opponent);
    }
}
SINGLE_BATTLE_TEST("Three Horizons PT14.1: Special Hyper Beam KO permits switching and the replacement acts")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Attack(100); SpAttack(150); }
        PLAYER(SPECIES_WYNAUT);
        OPPONENT(SPECIES_WOBBUFFET) { HP(1); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player,MOVE_HYPER_BEAM); SEND_OUT(opponent,1); }
        TURN { SWITCH(player,1); }
        TURN { MOVE(player,MOVE_WATER_GUN); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE,MOVE_HYPER_BEAM,player);
        NOT MESSAGE("Wobbuffet must recharge!");
        ANIMATION(ANIM_TYPE_MOVE,MOVE_WATER_GUN,player);
        HP_BAR(opponent);
    }
}

SINGLE_BATTLE_TEST("Three Horizons PT14.1: misses Protect and immunity retain no-hit recharge behavior")
{
    u32 reason=0;
    PARAMETRIZE { reason=0; }
    PARAMETRIZE { reason=1; }
    PARAMETRIZE { reason=2; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(reason==2 ? SPECIES_GASTLY : SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent,reason==1 ? MOVE_PROTECT : MOVE_CELEBRATE); MOVE(player,MOVE_HYPER_BEAM,hit:reason!=0); }
        TURN { MOVE(player,MOVE_WATER_GUN); }
    } SCENE {
        NOT HP_BAR(opponent);
        ANIMATION(ANIM_TYPE_MOVE,MOVE_WATER_GUN,player);
        HP_BAR(opponent);
    }
}

SINGLE_BATTLE_TEST("Three Horizons PT14.1: surviving or broken Substitute still requires recharge")
{
    bool32 breakSub=FALSE;
    PARAMETRIZE { breakSub=FALSE; }
    PARAMETRIZE { breakSub=TRUE; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Attack(150); SpAttack(100); }
        OPPONENT(SPECIES_WOBBUFFET) { MaxHP(breakSub ? 100 : 1000); HP(breakSub ? 100 : 1000); Defense(100); SpDefense(100); }
    } WHEN {
        TURN { MOVE(opponent,MOVE_SUBSTITUTE); MOVE(player,MOVE_HYPER_BEAM); }
        TURN { SKIP_TURN(player); }
        TURN { MOVE(player,MOVE_WATER_GUN); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE,MOVE_SUBSTITUTE,opponent);
        ANIMATION(ANIM_TYPE_MOVE,MOVE_HYPER_BEAM,player);
        if (breakSub) MESSAGE("The opposing Wobbuffet's substitute faded!");
        else NOT MESSAGE("The opposing Wobbuffet's substitute faded!");
        MESSAGE("Wobbuffet must recharge!");
        ANIMATION(ANIM_TYPE_MOVE,MOVE_WATER_GUN,player);
    }
}

SINGLE_BATTLE_TEST("Three Horizons PT14.1: ordinary charging moves still charge before dealing damage")
{
    enum Move move=MOVE_SOLAR_BEAM;
    PARAMETRIZE { move=MOVE_SOLAR_BEAM; }
    PARAMETRIZE { move=MOVE_FLY; }
    PARAMETRIZE { move=MOVE_DIG; }
    PARAMETRIZE { move=MOVE_SKULL_BASH; }
    PARAMETRIZE { move=MOVE_RAZOR_WIND; }
    PARAMETRIZE { move=MOVE_SKY_ATTACK; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { MaxHP(1000); HP(1000); }
    } WHEN {
        TURN { MOVE(player,move); }
        TURN { SKIP_TURN(player); }
        TURN { MOVE(player,MOVE_WATER_GUN); }
    } SCENE {
        NOT HP_BAR(opponent);
        ANIMATION(ANIM_TYPE_MOVE,MOVE_CELEBRATE,opponent);
        ANIMATION(ANIM_TYPE_MOVE,move,player);
        HP_BAR(opponent);
        ANIMATION(ANIM_TYPE_MOVE,MOVE_WATER_GUN,player);
        HP_BAR(opponent);
    }
}

SINGLE_BATTLE_TEST("Three Horizons PT14.1: AI retains recharge drawback unless its existing estimate predicts one-hit KO")
{
    bool32 substitute = FALSE;
    PARAMETRIZE { substitute = FALSE; }
    PARAMETRIZE { substitute = TRUE; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Moves(MOVE_CELEBRATE,MOVE_HYPER_BEAM,MOVE_POUND); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player,MOVE_CELEBRATE); MOVE(opponent, substitute ? MOVE_SUBSTITUTE : MOVE_CELEBRATE); }
    } THEN {
        EXPECT_EQ(CompareMoveEffects(MOVE_HYPER_BEAM,MOVE_POUND,0,1,1),substitute ? MOVE_LOST_COMPARISON : MOVE_NEUTRAL_COMPARISON);
        EXPECT_EQ(CompareMoveEffects(MOVE_HYPER_BEAM,MOVE_POUND,0,1,2),MOVE_LOST_COMPARISON);
        EXPECT_EQ(CompareMoveEffects(MOVE_HYPER_BEAM,MOVE_POUND,0,1,0),MOVE_LOST_COMPARISON);
    }
}
#endif
