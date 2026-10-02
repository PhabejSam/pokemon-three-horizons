TH14_CeladonCity_PokemonCenter_1F_MapScripts::
    map_script MAP_SCRIPT_ON_LOAD, TH14_CeladonCity_PokemonCenter_1F_Stairs
    map_script MAP_SCRIPT_ON_TRANSITION, TH14_CeladonCity_PokemonCenter_1F_Checkpoint
    .byte 0
TH14_CeladonCity_PokemonCenter_1F_Stairs:
    setmetatile 1, 6, 729, FALSE
    return
TH14_CeladonCity_PokemonCenter_1F_Checkpoint::
    setrespawn HEAL_LOCATION_TH14_CELADON
    return
