#include "global.h"
#include "three_horizons.h"
#include "event_data.h"
#include "item.h"
#include "money.h"
#include "constants/three_horizons.h"

#if THREE_HORIZONS
void TH_TryGiveChapter12Supplies(void)
{
    gSpecialVar_Result = FALSE;
    if (VarGet(VAR_TH_STAGE) < TH_STAGE_PARTNER)
        return;
    if (!FlagGet(FLAG_TH12_START_MONEY))
    {
        AddMoney(&gSaveBlock1Ptr->money, 2000);
        FlagSet(FLAG_TH12_START_MONEY);
    }
    if (!FlagGet(FLAG_TH12_ULTRA_BALLS))
    {
        if (!AddBagItem(ITEM_ULTRA_BALL, 2))
            return;
        FlagSet(FLAG_TH12_ULTRA_BALLS);
    }
    gSpecialVar_Result = TRUE;
}
#endif
