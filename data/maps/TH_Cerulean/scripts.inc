TH_Cerulean_MapScripts::
    map_script MAP_SCRIPT_ON_LOAD, TH_Cerulean_CloseFacilities
    .byte 0
TH_Cerulean_CloseFacilities:
    setmetatile 1, 12, 169, TRUE
    return
