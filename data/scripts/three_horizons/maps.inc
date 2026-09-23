TH_Home2F_MapScripts::
    .byte 0
TH_Home1F_MapScripts::
    .byte 0
TH_Pallet_MapScripts::
    map_script MAP_SCRIPT_ON_TRANSITION, TH_Pallet_OnTransition
    .byte 0
TH_OaksLab_MapScripts::
    map_script MAP_SCRIPT_ON_TRANSITION, TH_Lab_OnLoad
    .byte 0
TH_Route1_MapScripts::
    .byte 0
TH_ViridianEntrance_MapScripts::
    .byte 0

    .include "data/scripts/three_horizons/home.inc"
    .include "data/scripts/three_horizons/town.inc"
    .include "data/scripts/three_horizons/lab.inc"
    .include "data/scripts/three_horizons/route.inc"
    .include "data/scripts/three_horizons/ending.inc"
    .include "data/scripts/three_horizons/text.inc"

.include "data/maps/TH_Route21Shore/scripts.inc"
