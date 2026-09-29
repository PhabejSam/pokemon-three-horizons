#include "global.h"
#include "test/test.h"
#include "event_data.h"
#include "field_control_avatar.h"
#include "fieldmap.h"
#include "item.h"
#include "overworld.h"
#include "script.h"
#include "constants/maps.h"
#include "constants/three_horizons.h"

#if THREE_HORIZONS
TEST("Three Horizons playtest13 ship boarding requires ticket inspection in every lane")
{
    bool32 ticket, departed;
    PARAMETRIZE { ticket = TRUE; departed = FALSE; }
    PARAMETRIZE { ticket = FALSE; departed = FALSE; }
    PARAMETRIZE { ticket = FALSE; departed = TRUE; }
    PARAMETRIZE { ticket = TRUE; departed = TRUE; }
    const struct MapHeader saved = gMapHeader;
    const struct PlayerAvatar avatar = gPlayerAvatar;
    const struct ObjectEvent object = gObjectEvents[0];
    InitEventData();
    ClearBag();
    if (ticket) EXPECT(AddBagItem(ITEM_SS_TICKET, 1));
    if (departed) FlagSet(FLAG_TH13_SHIP_DEPARTED);
    gMapHeader = *Overworld_GetMapHeaderByGroupAndId(MAP_GROUP(MAP_TH12_VERMILION_CITY), MAP_NUM(MAP_TH12_VERMILION_CITY));
    gPlayerAvatar.objectEventId = 0;
    for (u32 x = 22; x <= 24; x++)
    {
        struct MapPosition pos = {.x = x + MAP_OFFSET, .y = 33 + MAP_OFFSET, .elevation = 3};
        const u8 *script = GetCoordEventScriptAtMapPosition(&pos);
        EXPECT(script != NULL);
        // Even ticket holders must see inspection; return travel is free.
        for (u32 direction = DIR_SOUTH; direction <= DIR_EAST; direction++)
        {
            gObjectEvents[0].facingDirection = direction;
            EXPECT_EQ(Script_HasNoEffect(script), direction != DIR_SOUTH);
            EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_SS_TICKET), ticket);
            EXPECT_EQ(FlagGet(FLAG_TH13_SHIP_DEPARTED), departed);
        }
    }
    gMapHeader = saved;
    gPlayerAvatar = avatar;
    gObjectEvents[0] = object;
}
#endif
