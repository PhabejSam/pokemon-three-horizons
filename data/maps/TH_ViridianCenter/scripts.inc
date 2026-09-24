TH_ViridianCenter_MapScripts::
    map_script MAP_SCRIPT_ON_LOAD, TH_ViridianCenter_CloseDoors
    map_script MAP_SCRIPT_ON_TRANSITION, TH_ViridianCenter_Checkpoint
    .byte 0
TH_ViridianCenter_CloseDoors:
    setmetatile 1, 6, 729, TRUE
    return
TH_ViridianCenter_Checkpoint:
    setrespawn HEAL_LOCATION_TH_VIRIDIAN
    return
