TH_CeruleanCenter_MapScripts::
    map_script MAP_SCRIPT_ON_LOAD, TH_CeruleanCenter_CloseFacilities
    map_script MAP_SCRIPT_ON_TRANSITION, TH_CeruleanCenter_Checkpoint
    .byte 0
TH_CeruleanCenter_CloseFacilities:
    setmetatile 1, 6, 729, TRUE
    return
TH_CeruleanCenter_Checkpoint:
    setrespawn HEAL_LOCATION_TH_CERULEAN
    return
