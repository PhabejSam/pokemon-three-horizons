#include "global.h"
#include "pokedex.h"
#include "test/battle.h"
#include "test/overworld_script.h"

GHOST_BATTLE_TEST("Ghost battle: Player cannot use select moves")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Moves(MOVE_CONFUSION, MOVE_WATER_GUN, MOVE_THUNDERSHOCK, MOVE_EMBER); }
        OPPONENT(SPECIES_MAROWAK);
    } WHEN {
        TURN { MOVE(player, MOVE_CONFUSION); }
        TURN { MOVE(player, MOVE_WATER_GUN); }
        TURN { MOVE(player, MOVE_THUNDERSHOCK); }
        TURN { MOVE(player, MOVE_EMBER); }
    } SCENE {
        NOT ANIMATION(ANIM_TYPE_MOVE, MOVE_CONFUSION, player);
        MESSAGE("Wobbuffet is too scared to move!");
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_MON_SCARED, player);
        MESSAGE("GHOST: Get out…… Get out……");
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_GHOST_GET_OUT, opponent);

        NOT ANIMATION(ANIM_TYPE_MOVE, MOVE_WATER_GUN, player);
        MESSAGE("Wobbuffet is too scared to move!");
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_MON_SCARED, player);
        MESSAGE("GHOST: Get out…… Get out……");
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_GHOST_GET_OUT, opponent);

        NOT ANIMATION(ANIM_TYPE_MOVE, MOVE_THUNDERSHOCK, player);
        MESSAGE("Wobbuffet is too scared to move!");
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_MON_SCARED, player);
        MESSAGE("GHOST: Get out…… Get out……");
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_GHOST_GET_OUT, opponent);

        NOT ANIMATION(ANIM_TYPE_MOVE, MOVE_EMBER, player);
        MESSAGE("Wobbuffet is too scared to move!");
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_MON_SCARED, player);
        MESSAGE("GHOST: Get out…… Get out……");
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_GHOST_GET_OUT, opponent);
    }
}

GHOST_BATTLE_TEST("Ghost battle: Intro plays correctly (no Silph Scope)")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_MAROWAK);
    } WHEN {
        TURN {}
    } SCENE {
        MESSAGE("The GHOST appeared! Darn! The GHOST can't be ID'd!");
        MESSAGE("Go! Wobbuffet!");
    }
}

GHOST_BATTLE_TEST("Ghost battle: Intro plays correctly (with Silph Scope)")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_MAROWAK);
        GIVE_PLAYER_ITEM(ITEM_SILPH_SCOPE, 1);
    } WHEN {
        TURN {}
    } SCENE {
        MESSAGE("The GHOST appeared!");
        MESSAGE("SILPH SCOPE unveiled the GHOST's identity!");
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_SILPH_SCOPED, opponent);
        MESSAGE("The GHOST was MAROWAK!");
        MESSAGE("Go! Wobbuffet!");
    }
}

GHOST_BATTLE_TEST("Ghost battle: player cannot capture ghost (no Silph Scope)")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_MAROWAK);
    } WHEN {
        TURN { USE_ITEM(player, ITEM_POKE_BALL, WITH_RNG(RNG_BALLTHROW_SHAKE, MAX_u16)); }
        TURN { USE_ITEM(player, ITEM_MASTER_BALL); }
    } SCENE {
        MESSAGE("You used Poké Ball!");
        MESSAGE("It dodged your thrown Poké Ball! This Pokémon can't be caught!");
        MESSAGE("You used Master Ball!");
        MESSAGE("It dodged your thrown Poké Ball! This Pokémon can't be caught!");
    }
}

GHOST_BATTLE_TEST("Ghost battle: player cannot capture ghost (Marowak)")
{
    RUN_OVERWORLD_SCRIPT(
        additem ITEM_SILPH_SCOPE;
    );

    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_MAROWAK);
    } WHEN {
        TURN { USE_ITEM(player, ITEM_POKE_BALL, WITH_RNG(RNG_BALLTHROW_SHAKE, MAX_u16)); }
        TURN { USE_ITEM(player, ITEM_MASTER_BALL); }
    } SCENE {
        MESSAGE("You used Poké Ball!");
        MESSAGE("It dodged your thrown Poké Ball! This Pokémon can't be caught!");
        MESSAGE("You used Master Ball!");
        MESSAGE("It dodged your thrown Poké Ball! This Pokémon can't be caught!");
    }
}


GHOST_BATTLE_TEST("Ghost battle: scoped mother dodges every configured throwable Ball")
{
    enum Item item = ITEM_NONE;
    for (enum Item ball = ITEM_POKE_BALL; ball <= ITEM_CHERISH_BALL; ball++)
        PARAMETRIZE { item = ball; }
    PARAMETRIZE { item = ITEM_STRANGE_BALL; }
    GIVEN {
        GIVE_PLAYER_ITEM(ITEM_SILPH_SCOPE, 1);
        GIVE_PLAYER_ITEM(item, 1);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_MAROWAK);
    } WHEN {
        TURN { USE_ITEM(player, item, WITH_RNG(RNG_BALLTHROW_SHAKE, 0)); }
    } SCENE {
        MESSAGE("It dodged your thrown Poké Ball! This Pokémon can't be caught!");
    } THEN {
        // The runner stops unfinished recorded battles with B after the turn.
        // BattleMainCB2 reports that teardown as PLAYER_TELEPORTED, not CAUGHT.
        EXPECT_EQ(gBattleOutcome, B_OUTCOME_PLAYER_TELEPORTED);
        EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][1], MON_DATA_SPECIES), SPECIES_NONE);
        EXPECT(!GetSetPokedexFlag(NATIONAL_DEX_MAROWAK, FLAG_GET_CAUGHT));
    }
}

WILD_BATTLE_TEST("Ghost battle: normal wild Marowak remains catchable with Scope")
{
    GIVEN {
        GIVE_PLAYER_ITEM(ITEM_SILPH_SCOPE, 1);
        GIVE_PLAYER_ITEM(ITEM_MASTER_BALL, 1);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_MAROWAK);
    } WHEN {
        TURN { USE_ITEM(player, ITEM_MASTER_BALL); }
    } THEN {
        EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][1], MON_DATA_SPECIES), SPECIES_MAROWAK);
        EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][1], MON_DATA_POKEBALL), BALL_MASTER);
    }
}
