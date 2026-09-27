#include "global.h"
#include "test/test.h"
#include "battle.h"
#include "battle_interface.h"
#include "battle_gfx_sfx_util.h"
#include "sprite.h"
#include "task.h"
#include "palette.h"
#include "main.h"
#if THREE_HORIZONS
TEST("Three Horizons playtest12 opponents show separate three ball groups on one row")
{
    struct HpAndStatus a[PARTY_SIZE], b[PARTY_SIZE];
    u32 count;
    PARAMETRIZE { count = 1; }
    PARAMETRIZE { count = 3; }
    u32 savedFlags = gBattleTypeFlags;
    SetVBlankCallback(NULL);
    ResetTasks(); ResetSpriteData(); FreeAllSpritePalettes();
    AllocateBattleSpritesData();
    gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_DOUBLE | BATTLE_TYPE_TWO_OPPONENTS;
    gBattlersCount = 4;
    for (u32 i = 0; i < 4; i++) gBattlerPositions[i] = i;
    for (u32 i = 0; i < PARTY_SIZE; i++)
    {
        a[i].hp = i < count ? 20 : HP_EMPTY_SLOT;
        b[i].hp = i < count ? (i == 0 ? 0 : 20) : HP_EMPTY_SLOT;
        a[i].status = b[i].status = 0;
    }
    b[1].status = STATUS1_POISON;
    u8 ta = CreatePartyStatusSummarySprites(1, a, FALSE, TRUE);
    u8 tb = CreatePartyStatusSummarySprites(3, b, FALSE, TRUE);
    for (u32 frame = 0; frame < 180; frame++) AnimateSprites();
    for (u32 i = 0; i < PARTY_SIZE; i++)
    {
        struct Sprite *sa = &gSprites[gTasks[ta].data[3+i]];
        struct Sprite *sb = &gSprites[gTasks[tb].data[3+i]];
        EXPECT_EQ((u32)sa->invisible, i < 3);
        EXPECT_EQ((u32)sb->invisible, i < 3);
        if (i >= 3)
        {
            EXPECT_EQ(sa->y, sb->y);
            EXPECT_EQ(sa->x2, 0); EXPECT_EQ(sb->x2, 0);
            EXPECT_EQ(sb->x - sa->x, 44);
            EXPECT_GE(sa->x, 8); EXPECT_LT(sb->x, 112);
        }
    }
    // Trainer B's fainted first mon is independent of trainer A's healthy one.
    struct Sprite *firstA = &gSprites[gTasks[ta].data[8]];
    struct Sprite *firstB = &gSprites[gTasks[tb].data[8]];
    EXPECT_EQ((u32)firstB->oam.tileNum - (u32)firstA->oam.tileNum, 3);
    Task_HidePartyStatusSummary(ta); Task_HidePartyStatusSummary(tb);
    for (u32 frame = 0; frame < 100; frame++) { RunTasks(); AnimateSprites(); }
    EXPECT(!gTasks[ta].isActive && !gTasks[tb].isActive);
    FreeBattleSpritesData(); ResetSpriteData(); FreeAllSpritePalettes();
    gBattleTypeFlags = savedFlags;
}
#endif
