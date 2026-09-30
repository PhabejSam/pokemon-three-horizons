TH12_Route5_SouthEntrance_MapScripts::
    map_script MAP_SCRIPT_ON_LOAD, TH12_Route5_SouthEntrance_Closed
    .byte 0
TH12_Route5_SouthEntrance_Closed:
    setvar VAR_TEMP_0, 0
    setmetatile 3, 9, 716, TRUE
    setmetatile 4, 9, 710, TRUE
    return
