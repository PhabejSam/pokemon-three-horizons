TH_LeagueGate_MapScripts::
    map_script MAP_SCRIPT_ON_LOAD, TH_LeagueGate_CloseFacilities
    .byte 0
TH_LeagueGate_CloseFacilities:
    setmetatile 7, 1, 657, TRUE
    return
