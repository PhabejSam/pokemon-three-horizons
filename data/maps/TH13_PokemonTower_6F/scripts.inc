TH13_PokemonTower_6F_MapScripts::
    map_script MAP_SCRIPT_ON_LOAD, TH13_PokemonTower_6F_Barrier
    map_script MAP_SCRIPT_ON_FRAME_TABLE, TH14_Mother_FrameTable
    .byte 0
TH13_PokemonTower_6F_Barrier::
    setvar VAR_TEMP_2, 0
    goto_if_set FLAG_TH14_MOTHER_RESOLVED, TH14_Mother_OpenStairs
    setmetatile 11, 16, 709, TRUE
    setvar VAR_TEMP_1, 0
    return
TH14_Mother_OpenStairs::
    setmetatile 11, 16, 709, FALSE
    setvar VAR_TEMP_1, 1
    return
TH14_Mother_FrameTable:
    map_script_2 VAR_TEMP_2, 0, TH14_Mother_Resume
    .2byte 0
