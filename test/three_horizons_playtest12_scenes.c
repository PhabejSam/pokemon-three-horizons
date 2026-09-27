#include "global.h"
#include "test/test.h"
#include "sprite.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "field_player_avatar.h"
#include "constants/three_horizons.h"

#if THREE_HORIZONS
extern bool8 MovementAction_FaceUp_Step0(struct ObjectEvent *, struct Sprite *);
extern bool8 MovementAction_FaceDown_Step0(struct ObjectEvent *, struct Sprite *);
extern bool8 MovementAction_FaceLeft_Step0(struct ObjectEvent *, struct Sprite *);
extern bool8 MovementAction_FaceRight_Step0(struct ObjectEvent *, struct Sprite *);

TEST("Three Horizons playtest12 scripted facing ends in a standing pose for every outfit")
{
    static bool8 (*const face[])(struct ObjectEvent *, struct Sprite *) = {
        MovementAction_FaceDown_Step0, MovementAction_FaceUp_Step0,
        MovementAction_FaceLeft_Step0, MovementAction_FaceRight_Step0,
    };
    u16 savedOutfit = VarGet(VAR_TH_OUTFIT);
    ResetSpriteData();
    FreeAllSpritePalettes();
    for (u32 outfit = 0; outfit < TH_OUTFIT_COUNT; outfit++)
    {
        VarSet(VAR_TH_OUTFIT, outfit);
        u16 gfx = GetPlayerAvatarGraphicsIdByStateIdAndGender(PLAYER_AVATAR_STATE_NORMAL, MALE);
        u8 id = CreateObjectGraphicsSprite(gfx, SpriteCallbackDummy, 120, 80, 0);
        EXPECT_LT(id, MAX_SPRITES);
        struct Sprite *sprite = &gSprites[id];
        struct ObjectEvent player = {.isPlayer = TRUE};
        for (u32 direction = DIR_SOUTH; direction <= DIR_EAST; direction++)
        {
            StartSpriteAnim(sprite, GetMoveDirectionAnimNum(direction));
            SeekSpriteAnim(sprite, 1);
            face[direction - DIR_SOUTH](&player, sprite);
            EXPECT_EQ(player.facingDirection, direction);
            EXPECT_EQ(sprite->animNum, GetFaceDirectionAnimNum(direction));
            EXPECT_EQ(sprite->animCmdIndex, 0);
            EXPECT(sprite->animPaused);
        }
        DestroySprite(sprite);
        FreeAllSpritePalettes();
    }
    VarSet(VAR_TH_OUTFIT, savedOutfit);
}
#endif
