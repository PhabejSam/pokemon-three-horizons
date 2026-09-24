#include "global.h"
#include "three_horizons.h"
#include "pokemon.h"
#include "item.h"
#include "event_data.h"
#include "constants/items.h"
#include "constants/three_horizons.h"

#if THREE_HORIZONS
u16 TH_TryDeliverTrainingKit(void)
{
    static const u16 items[] = {ITEM_MACHO_BRACE, ITEM_POWER_WEIGHT, ITEM_POWER_BRACER,
        ITEM_POWER_BELT, ITEM_POWER_LENS, ITEM_POWER_BAND, ITEM_POWER_ANKLET};
    u16 mask = VarGet(VAR_TH_TRAINING_KIT_MASK);
    for (u32 i = 0; i < ARRAY_COUNT(items); i++)
        if (!(mask & (1 << i)) && AddPCItem(items[i], 1))
        {
            mask |= 1 << i;
            VarSet(VAR_TH_TRAINING_KIT_MASK, mask);
        }
    return mask;
}

void TH_ScriptDeliverTrainingKit(void)
{
    gSpecialVar_Result = TH_TryDeliverTrainingKit();
}

u32 TH_GetTrainingItemPrice(u16 itemId, u32 fallback)
{
    if (itemId >= ITEM_LONELY_MINT && itemId <= ITEM_SERIOUS_MINT)
        return 1000;
    switch (itemId)
    {
    case ITEM_POMEG_BERRY:
    case ITEM_KELPSY_BERRY:
    case ITEM_QUALOT_BERRY:
    case ITEM_HONDEW_BERRY:
    case ITEM_GREPA_BERRY:
    case ITEM_TAMATO_BERRY:
        return 100;
    case ITEM_BOTTLE_CAP:
        return 2000;
    case ITEM_GOLD_BOTTLE_CAP:
        return 6000;
    default:
        return fallback;
    }
}

void TH_RecalculateWithoutHealing(struct Pokemon *mon, u16 oldHP, u16 oldMaxHP)
{
    u16 hp;
    CalculateMonStats(mon);
    s32 maxHP = GetMonData(mon, MON_DATA_MAX_HP);
    s32 damage = max(0, (s32)oldMaxHP - oldHP);
    hp = oldHP == 0 ? 0 : max(1, min(maxHP, maxHP - damage));
    SetMonData(mon, MON_DATA_HP, &hp);
}

bool32 TH_TryImproveIVs(struct Pokemon *mon, u16 itemId, u8 stat)
{
    struct Pokemon changed;
    bool32 hasChange = FALSE;
    u8 value = 31;
    if (mon == NULL || GetMonData(mon, MON_DATA_SPECIES) == SPECIES_NONE
        || GetMonData(mon, MON_DATA_IS_EGG) || stat >= NUM_STATS
        || (itemId != ITEM_BOTTLE_CAP && itemId != ITEM_GOLD_BOTTLE_CAP)
        || !CheckBagHasItem(itemId, 1))
        return FALSE;
    changed = *mon;
    for (u32 i = 0; i < NUM_STATS; i++)
        if ((itemId == ITEM_GOLD_BOTTLE_CAP || stat == i)
            && GetMonData(mon, MON_DATA_HP_IV + i) < 31)
        {
            SetMonData(&changed, MON_DATA_HP_IV + i, &value);
            hasChange = TRUE;
        }
    if (!hasChange)
        return FALSE;
    TH_RecalculateWithoutHealing(&changed, GetMonData(mon, MON_DATA_HP), GetMonData(mon, MON_DATA_MAX_HP));
    if (!RemoveBagItem(itemId, 1))
        return FALSE;
    *mon = changed;
    return TRUE;
}

void TH_ScriptImproveIVs(void)
{
    gSpecialVar_Result = gSpecialVar_0x8004 < PARTY_SIZE
        && TH_TryImproveIVs(&gParties[B_TRAINER_PLAYER][gSpecialVar_0x8004], gSpecialVar_0x8005, gSpecialVar_0x8006);
}
#endif
