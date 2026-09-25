TH_Route4Center_MapScripts::
    map_script MAP_SCRIPT_ON_LOAD, TH_Route4Center_CloseFacilities
    map_script MAP_SCRIPT_ON_TRANSITION, TH_Route4Center_Checkpoint
    .byte 0
TH_Route4Center_CloseFacilities:
    setmetatile 1, 6, 729, TRUE
    return
TH_Route4Center_Checkpoint:
    setrespawn HEAL_LOCATION_TH_ROUTE4
    return
