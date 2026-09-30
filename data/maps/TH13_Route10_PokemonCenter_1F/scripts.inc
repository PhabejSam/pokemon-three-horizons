TH13_Route10_PokemonCenter_1F_MapScripts::
    map_script MAP_SCRIPT_ON_LOAD, TH13_Route10_PokemonCenter_1F_Stairs
    map_script MAP_SCRIPT_ON_TRANSITION, TH13_Route10_PokemonCenter_1F_Checkpoint
    .byte 0
TH13_Route10_PokemonCenter_1F_Stairs:
    setmetatile 1, 6, 729, FALSE
    return
TH13_Route10_PokemonCenter_1F_Checkpoint:
    setrespawn HEAL_LOCATION_TH13_ROUTE10
    setvar VAR_0x8004, TH_CALL_ROUTE10
    special TH_ScriptResearchQueueCall
    return
