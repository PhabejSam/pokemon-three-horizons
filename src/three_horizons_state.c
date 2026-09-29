#include "global.h"
#include "three_horizons.h"
#include "event_data.h"
#include "pokedex.h"
#include "item.h"
#include "overworld.h"
#include "load_save.h"
#include "constants/pokedex.h"
#include "constants/three_horizons.h"
#include "constants/trainers.h"
#include "constants/maps.h"
#include "constants/layouts.h"
#if THREE_HORIZONS
void TH_MigrateSaveState(void)
{
    static const u16 variables[] = {VAR_TH_BROCK_GIFT, VAR_TH_MISTY_GIFT,
        VAR_TH_SHINY_RATE, VAR_TH_CLOCK_MODE, VAR_TH_CLOCK_REAL_LO,
        VAR_TH_CLOCK_REAL_HI, VAR_TH_CLOCK_DISPLAY_LO};
    u16 version = VarGet(VAR_TH_CLOCK_DISPLAY_HI) & TH_STATE_VERSION_MASK;
    if (version != TH_STATE_VERSION_9 && version != TH_STATE_VERSION_10 && version != TH_STATE_VERSION_11 && version != TH_STATE_VERSION_12 && version != TH_STATE_VERSION_13)
    {
        // Only this chapter's newly owned state is cleared. Never touch the
        // original partner, rival, trainer flags, badges, clock setup or kit.
        for (u32 i=0;i<ARRAY_COUNT(variables);i++) VarSet(variables[i],0);
        // 0x21 belongs to the existing party EXP. SHARE; preserve it.
        for (u32 flag=FLAG_TH_MAGIKARP;flag<=FLAG_TH_LAB_INTRO;flag++) FlagClear(flag);
        VarSet(VAR_TH_CLOCK_DISPLAY_HI,TH_STATE_VERSION_9);
    }
    if (version != TH_STATE_VERSION_10 && version != TH_STATE_VERSION_11 && version != TH_STATE_VERSION_12 && version != TH_STATE_VERSION_13)
    {
        FlagClear(FLAG_TH_DIG_TM);
        VarSet(VAR_TH_CLOCK_DISPLAY_HI, TH_STATE_VERSION_10 | (VarGet(VAR_TH_CLOCK_DISPLAY_HI) & 1));
    }
    if (version != TH_STATE_VERSION_11 && version != TH_STATE_VERSION_12 && version != TH_STATE_VERSION_13)
    {
        FlagClear(FLAG_TH_ROCKET_DUO);
        FlagClear(TRAINER_FLAGS_START + TRAINER_TH11_JESSIE);
        FlagClear(TRAINER_FLAGS_START + TRAINER_TH11_JAMES);
        VarSet(VAR_TH_CLOCK_DISPLAY_HI, TH_STATE_VERSION_11 | (VarGet(VAR_TH_CLOCK_DISPLAY_HI) & 1));
    }
    if (version != TH_STATE_VERSION_12 && version != TH_STATE_VERSION_13)
    {
        for (u32 flag = TH12_FLAGS_START; flag <= TH12_FLAGS_END; flag++)
            FlagClear(flag);
        for (u32 trainer = TH12_TRAINERS_START; trainer <= TH12_TRAINERS_END; trainer++)
            FlagClear(TRAINER_FLAGS_START + trainer);
        // Older releases did not store revival receipts. In those releases,
        // these species could only be obtained by restoring the collected fossil.
        if (FlagGet(FLAG_TH_FOSSIL_DOME) && GetSetPokedexFlag(NATIONAL_DEX_KABUTO, FLAG_GET_CAUGHT))
            FlagSet(FLAG_TH12_REVIVED_DOME);
        if (FlagGet(FLAG_TH_FOSSIL_HELIX) && GetSetPokedexFlag(NATIONAL_DEX_OMANYTE, FLAG_GET_CAUGHT))
            FlagSet(FLAG_TH12_REVIVED_HELIX);
        VarSet(VAR_TH_CLOCK_DISPLAY_HI, TH_STATE_VERSION_12 | (VarGet(VAR_TH_CLOCK_DISPLAY_HI) & 1));
    }
    if (version != TH_STATE_VERSION_13)
    {
        // These audited unused slots belong only to P13. Old versions may
        // contain arbitrary bits here; initialize them once, never on Continue.
        for (u32 flag = TH13_FLAGS_START; flag <= TH13_FLAGS_END; flag++)
            FlagClear(flag);
        // P12 allowed an in-game save after Bill entered his machine. Import
        // that witnessed scene before Continue clears the map's temp flags.
        // Identical temp bits in another room do not prove Bill's progress.
        if (version == TH_STATE_VERSION_12
            && gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(MAP_TH12_ROUTE25_SEA_COTTAGE)
            && gSaveBlock1Ptr->location.mapNum == MAP_NUM(MAP_TH12_ROUTE25_SEA_COTTAGE)
            && FlagGet(FLAG_TEMP_2) && FlagGet(FLAG_TEMP_3) && FlagGet(FLAG_TEMP_4)
            && !FlagGet(FLAG_TH12_BILL_RESCUED))
            FlagSet(FLAG_TH13_BILL_IN_MACHINE);
        if (VarGet(VAR_TH_SIGHTING_SEEN) == 1)
            FlagSet(FLAG_TH13_OBS_HOOTHOOT);
        // P12 shared one receipt between two forest scenes. It proves a
        // report, not either particular scene and certainly not a photo.
        if (FlagGet(FLAG_TH12_FOREST_SEEN))
            FlagSet(FLAG_TH13_OBS_FOREST_LEGACY);
        if (FlagGet(FLAG_TH12_CAVE_SEEN))
            FlagSet(FLAG_TH13_OBS_MT_MOON);
        if (FlagGet(FLAG_TH12_SHIP_STORY))
            FlagSet(FLAG_TH13_OBS_SHIP);
        if (CheckBagHasItem(ITEM_HM05, 1))
            FlagSet(FLAG_TH13_FLASH);
        if (CheckBagHasItem(ITEM_ACRO_BIKE, 1))
            FlagSet(FLAG_TH13_ACRO);
        if (CheckBagHasItem(ITEM_VS_SEEKER, 1))
            FlagSet(FLAG_TH13_VS_SEEKER);
        // Gear, photos and ship departure require witnessed P13 events.
        VarSet(VAR_TH_CLOCK_DISPLAY_HI, TH_STATE_VERSION_13 | (VarGet(VAR_TH_CLOCK_DISPLAY_HI) & 1));
    }
    // Continue restores the saved layout ID. Replace only the obsolete forest
    // layout, retaining all old paths/coordinates and every progress receipt.
    if (gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(MAP_TH_VIRIDIAN_FOREST)
        && gSaveBlock1Ptr->location.mapNum == MAP_NUM(MAP_TH_VIRIDIAN_FOREST)
        && gSaveBlock1Ptr->mapLayoutId == LAYOUT_VIRIDIAN_FOREST)
    {
        gSaveBlock1Ptr->mapLayoutId = Overworld_GetMapHeaderByGroupAndId(
            MAP_GROUP(MAP_TH_VIRIDIAN_FOREST), MAP_NUM(MAP_TH_VIRIDIAN_FOREST))->mapLayoutId;
        memset(gSaveBlock1Ptr->mapView, 0, sizeof(gSaveBlock1Ptr->mapView));
    }
    if (VarGet(VAR_TH_CLOCK_MODE)>1) VarSet(VAR_TH_CLOCK_MODE,0);
    if (VarGet(VAR_TH_SHINY_RATE)>3) VarSet(VAR_TH_SHINY_RATE,0);
    u16 first=VarGet(VAR_TH_FIRST_PARTNER), brock=VarGet(VAR_TH_BROCK_GIFT);
    if (brock && brock!=TH_GetBrockGift(first,0) && brock!=TH_GetBrockGift(first,1))
        VarSet(VAR_TH_BROCK_GIFT,0);
    u16 misty=VarGet(VAR_TH_MISTY_GIFT);
    if (misty && misty!=TH_GetMistyGift(first,VarGet(VAR_TH_BROCK_GIFT)))
        VarSet(VAR_TH_MISTY_GIFT,0);
    // Only a witnessed P13 departure can make a ship interior impossible.
    // P12's reserved bits were cleared above, so old completed ship saves stay.
    if (FlagGet(FLAG_TH13_SHIP_DEPARTED)
        && gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(MAP_TH12_SSANNE_EXTERIOR)
        && gSaveBlock1Ptr->location.mapNum >= MAP_NUM(MAP_TH12_SSANNE_1F_CORRIDOR)
        && gSaveBlock1Ptr->location.mapNum <= MAP_NUM(MAP_TH12_SSANNE_KITCHEN))
    {
        gSaveBlock1Ptr->location = (struct WarpData){
            .mapGroup = MAP_GROUP(MAP_TH12_VERMILION_CITY),
            .mapNum = MAP_NUM(MAP_TH12_VERMILION_CITY),
            .warpId = WARP_ID_NONE, .x = 23, .y = 32,
        };
        gSaveBlock1Ptr->pos.x = 23;
        gSaveBlock1Ptr->pos.y = 32;
        gSaveBlock1Ptr->mapLayoutId = Overworld_GetMapHeaderByGroupAndId(
            MAP_GROUP(MAP_TH12_VERMILION_CITY), MAP_NUM(MAP_TH12_VERMILION_CITY))->mapLayoutId;
        memset(gSaveBlock1Ptr->mapView, 0, sizeof(gSaveBlock1Ptr->mapView));
        ClearContinueGameWarpStatus();
    }
}
#endif
