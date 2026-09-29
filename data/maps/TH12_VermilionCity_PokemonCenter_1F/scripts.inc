TH12_VermilionCity_PokemonCenter_1F_MapScripts::
    map_script MAP_SCRIPT_ON_LOAD, TH12_VermilionCity_PokemonCenter_1F_Closed
    map_script MAP_SCRIPT_ON_TRANSITION, TH12_VermilionCity_PokemonCenter_1F_Checkpoint
    .byte 0
TH12_VermilionCity_PokemonCenter_1F_Closed:
    setmetatile 1, 6, 729, FALSE
    return
TH12_VermilionCity_PokemonCenter_1F_Checkpoint:
    setrespawn HEAL_LOCATION_TH12_VERMILION
    return
