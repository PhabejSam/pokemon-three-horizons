TH13_LavenderTown_PokemonCenter_1F_MapScripts::
    map_script MAP_SCRIPT_ON_LOAD, TH13_LavenderTown_PokemonCenter_1F_Stairs
    map_script MAP_SCRIPT_ON_TRANSITION, TH13_LavenderTown_PokemonCenter_1F_Checkpoint
    .byte 0
TH13_LavenderTown_PokemonCenter_1F_Stairs:
    setmetatile 1, 6, 729, FALSE
    return
TH13_LavenderTown_PokemonCenter_1F_Checkpoint:
    setrespawn HEAL_LOCATION_TH13_LAVENDER
    return
