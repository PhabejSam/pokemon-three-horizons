#include "global.h"
#include "test/test.h"
#include "event_data.h"
#include "script.h"
#include "constants/three_horizons.h"

#if THREE_HORIZONS
extern const u8 TH_Local_PewterGym_0[];
extern const u8 TH_Local_CeruleanGym_3[];
extern const u8 TH12_Surge_Guide[];

TEST("Three Horizons playtest13 local gym guide acknowledges its own badge")
{
    const u8 *script;
    u16 badge;
    PARAMETRIZE { script = TH_Local_PewterGym_0; badge = FLAG_BADGE01_GET; }
    PARAMETRIZE { script = TH_Local_CeruleanGym_3; badge = FLAG_BADGE02_GET; }
    PARAMETRIZE { script = TH12_Surge_Guide; badge = FLAG_BADGE03_GET; }
    struct ScriptContext before, after, unrelated;
    InitEventData();
    EXPECT(RunScriptImmediatelyUntilEffect(SCREFF_V1 | SCREFF_ANY, script, &before));
    EXPECT(before.data[0] != 0);
    for (u16 other = FLAG_BADGE01_GET; other <= FLAG_BADGE03_GET; other++)
        if (other != badge) FlagSet(other);
    EXPECT(RunScriptImmediatelyUntilEffect(SCREFF_V1 | SCREFF_ANY, script, &unrelated));
    EXPECT_EQ(before.data[0], unrelated.data[0]);
    FlagSet(badge);
    EXPECT(RunScriptImmediatelyUntilEffect(SCREFF_V1 | SCREFF_ANY, script, &after));
    EXPECT_NE(before.data[0], after.data[0]);
    EXPECT(FlagGet(badge));
}
#endif
