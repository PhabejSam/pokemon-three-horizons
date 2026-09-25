TH_Route2_MapScripts::
    map_script MAP_SCRIPT_ON_LOAD, TH_Route2_CloseDoors
    .byte 0
TH_Route2_CloseDoors:
    setmetatile 17, 11, 169, TRUE
    setmetatile 17, 22, 61, TRUE
    setmetatile 18, 46, 401, TRUE
    setmetatile 18, 41, 377, TRUE
    setmetatile 19, 41, 377, TRUE
    setmetatile 19, 46, 401, TRUE
    return
