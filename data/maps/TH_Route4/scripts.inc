TH_Route4_MapScripts::
    map_script MAP_SCRIPT_ON_LOAD, TH_Route4_ReturnSteps
    .byte 0
TH_Route4_ReturnSteps:
    setmetatile 91, 9, 0x090, FALSE
    setmetatile 92, 9, 0x091, FALSE
    return
