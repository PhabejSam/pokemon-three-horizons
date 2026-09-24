TH_Pewter_MapScripts::
    map_script MAP_SCRIPT_ON_LOAD, TH_Pewter_CloseDoors
    .byte 0
TH_Pewter_CloseDoors:
    setmetatile 17, 6, 691, TRUE
    setmetatile 25, 4, 718, TRUE
    setmetatile 33, 11, 718, TRUE
    setmetatile 9, 30, 718, TRUE
    return
