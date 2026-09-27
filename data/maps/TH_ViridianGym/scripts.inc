TH_ViridianGym_MapScripts::
    map_script MAP_SCRIPT_ON_LOAD, TH_ViridianGym_EntryAttendant
    .byte 0
TH_ViridianGym_EntryAttendant:
    @ The attendant occupies the left pillar's old space, leaving all exit lanes clear.
    setmetatile 15, 20, 0x281, FALSE
    return
