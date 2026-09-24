TH_ViridianEntrance_MapScripts::
    map_script MAP_SCRIPT_ON_LOAD, TH_ViridianEntrance_CloseDoors
    .byte 0
TH_ViridianEntrance_CloseDoors:
    setmetatile 25, 11, 665, TRUE
    setmetatile 36, 10, 347, TRUE
    setmetatile 25, 18, 665, TRUE
    return
