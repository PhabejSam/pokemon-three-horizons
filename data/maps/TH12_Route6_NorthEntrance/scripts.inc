TH12_Route6_NorthEntrance_MapScripts::
    map_script MAP_SCRIPT_ON_LOAD, TH12_Route6_NorthEntrance_Closed
    .byte 0
TH12_Route6_NorthEntrance_Closed:
    setvar VAR_TEMP_0, 0
    setmetatile 4, 1, 657, TRUE
    setmetatile 5, 1, 658, TRUE
    return
