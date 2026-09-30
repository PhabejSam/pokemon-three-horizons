#include "global.h"
#include "test/test.h"
#include "event_data.h"
#include "field_control_avatar.h"
#include "fieldmap.h"
#include "overworld.h"
#include "script.h"
#include "constants/maps.h"

#if THREE_HORIZONS
TEST("Three Horizons playtest13 Saffron guard covers every lane and permits retreat")
{
    u16 map;
    PARAMETRIZE { map = MAP_TH12_ROUTE5_SOUTH_ENTRANCE; }
    PARAMETRIZE { map = MAP_TH12_ROUTE6_NORTH_ENTRANCE; }
    const struct MapHeader saved = gMapHeader;
    const struct PlayerAvatar avatar = gPlayerAvatar;
    const struct ObjectEvent object = gObjectEvents[0];
    InitEventData();
    gMapHeader = *Overworld_GetMapHeaderByGroupAndId(MAP_GROUP(map), MAP_NUM(map));
    gPlayerAvatar.objectEventId = 0;
    for (u32 x = 3; x <= 5; x++)
    {
        struct MapPosition pos = {.x = x + MAP_OFFSET, .y = 5 + MAP_OFFSET, .elevation = 3};
        const u8 *script = GetCoordEventScriptAtMapPosition(&pos);
        EXPECT(script != NULL);
        for (u32 direction = DIR_SOUTH; direction <= DIR_EAST; direction++)
        {
            gObjectEvents[0].facingDirection = direction;
            u32 blocked = map == MAP_TH12_ROUTE5_SOUTH_ENTRANCE ? DIR_SOUTH : DIR_NORTH;
            EXPECT_EQ(Script_HasNoEffect(script), direction != blocked);
        }
        pos.y--;
        EXPECT_EQ(GetCoordEventScriptAtMapPosition(&pos), NULL);
        pos.y += 2;
        EXPECT_EQ(GetCoordEventScriptAtMapPosition(&pos), NULL);
    }
    gMapHeader = saved;
    gPlayerAvatar = avatar;
    gObjectEvents[0] = object;
}
#endif
