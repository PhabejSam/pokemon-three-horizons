#include "global.h"
#include "test/battle.h"
#include "battle_ai_util.h"

#if THREE_HORIZONS
AI_SINGLE_BATTLE_TEST("Three Horizons first rival can attack a low HP player instead of fleeing")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_FIRST_BATTLE);
        PLAYER(SPECIES_BULBASAUR) { HP(1); Moves(MOVE_SPLASH); Speed(1); }
        OPPONENT(SPECIES_CHARMANDER) { Moves(MOVE_SCRATCH); Speed(100); }
    } WHEN {
        TURN { MOVE(player, MOVE_SPLASH); EXPECT_MOVE(opponent, MOVE_SCRATCH); }
    } SCENE {
        MESSAGE("Foe Charmander used Scratch!");
        HP_BAR(player, hp: 0);
        MESSAGE("Bulbasaur fainted!");
    }
}
#endif
