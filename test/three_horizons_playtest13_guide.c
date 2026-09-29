#include "global.h"
#include "test/test.h"
#include "event_data.h"
#include "field_control_avatar.h"
#include "fieldmap.h"
#include "overworld.h"
#include "script.h"
#include "constants/maps.h"

#if THREE_HORIZONS
extern const u8 TH_Route3BadgeGate[];

TEST("Three Horizons playtest13 Pewter guide cannot be bypassed before Brock")
{
    u32 museum;
    PARAMETRIZE { museum = 0; }
    PARAMETRIZE { museum = 1; }
    const struct MapHeader saved = gMapHeader;
    const struct PlayerAvatar avatar = gPlayerAvatar;
    const struct ObjectEvent object = gObjectEvents[0];
    InitEventData();
    gMapHeader = *Overworld_GetMapHeaderByGroupAndId(MAP_GROUP(MAP_TH_PEWTER), MAP_NUM(MAP_TH_PEWTER));
    gPlayerAvatar.objectEventId = 0;
    gObjectEvents[0].facingDirection = DIR_EAST;
    // TH_MuseumWelcome sets this while the player stays in Pewter.
    VarSet(VAR_TEMP_1, museum);
    u32 lanes = 0;
    for (u32 i = 0; i < gMapHeader.events->coordEventCount; i++)
    {
        const struct CoordEvent *event = &gMapHeader.events->coordEvents[i];
        if (event->script != TH_Route3BadgeGate || event->y < 20 || event->y > 23)
            continue;
        struct MapPosition pos = {.x = event->x + MAP_OFFSET, .y = event->y + MAP_OFFSET, .elevation = 3};
        const u8 *script = GetCoordEventScriptAtMapPosition(&pos);
        EXPECT(script != NULL);
        FlagClear(FLAG_BADGE01_GET);
        EXPECT(!Script_HasNoEffect(script));
        FlagSet(FLAG_BADGE01_GET);
        EXPECT(Script_HasNoEffect(script));
        lanes++;
    }
    EXPECT_EQ(lanes, 4);
    gMapHeader = saved;
    gPlayerAvatar = avatar;
    gObjectEvents[0] = object;
}
#endif
