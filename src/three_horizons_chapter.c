#include "global.h"
#include "three_horizons.h"
#include "event_data.h"
#include "constants/three_horizons.h"
#include "constants/region_map_sections.h"
#if THREE_HORIZONS
bool32 TH_ShouldShowAreaCard(u16 previous, u16 current)
{
    return previous != current && (current == MAPSEC_VIRIDIAN_FOREST || current == MAPSEC_MT_MOON);
}
bool32 TH_TryCompleteChapter(void)
{
    if (FlagGet(FLAG_TH_CHAPTER_COMPLETE) || !FlagGet(FLAG_BADGE02_GET) || !FlagGet(FLAG_TH_BRIDGE_RIVAL))
        return FALSE;
    FlagSet(FLAG_TH_CHAPTER_COMPLETE);
    return TRUE;
}
void TH_ScriptCheckChapter(void)
{
    gSpecialVar_Result=TH_TryCompleteChapter();
}
#endif
