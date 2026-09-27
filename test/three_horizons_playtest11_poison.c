#include "global.h"
#include "test/battle.h"

#if THREE_HORIZONS
SINGLE_BATTLE_TEST("Three Horizons Poison Point after Quick Attack damages on the same turn")
{
    GIVEN {
        PLAYER(SPECIES_RATTATA) { MaxHP(80); HP(80); }
        OPPONENT(SPECIES_NIDORAN_M) { Ability(ABILITY_POISON_POINT); }
    } WHEN {
        TURN { MOVE(player, MOVE_QUICK_ATTACK, WITH_RNG(RNG_POISON_POINT, TRUE)); MOVE(opponent, MOVE_SPLASH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_QUICK_ATTACK, player);
        ABILITY_POPUP(opponent, ABILITY_POISON_POINT);
        STATUS_ICON(player, poison: TRUE);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SPLASH, opponent);
        HP_BAR(player, damage: 10);
    } THEN {
        EXPECT_EQ(player->hp, 70);
    }
}
#endif
