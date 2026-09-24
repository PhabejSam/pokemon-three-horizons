TH_PewterCenter_MapScripts::
    map_script MAP_SCRIPT_ON_LOAD, TH_PewterCenter_CloseDoors
    map_script MAP_SCRIPT_ON_TRANSITION, TH_PewterCenter_Checkpoint
    .byte 0
TH_PewterCenter_CloseDoors:
    setmetatile 1, 6, 729, TRUE
    return
TH_PewterCenter_Checkpoint:
    setrespawn HEAL_LOCATION_TH_PEWTER
    return
