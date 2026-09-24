TH_Home2F_MapScripts::
    .byte 0
TH_Home1F_MapScripts::
    .byte 0
TH_Pallet_MapScripts::
    map_script MAP_SCRIPT_ON_TRANSITION, TH_Pallet_OnTransition
    map_script MAP_SCRIPT_ON_FRAME_TABLE, TH_Pallet_OnFrame
    .byte 0
TH_OaksLab_MapScripts::
    map_script MAP_SCRIPT_ON_TRANSITION, TH_Lab_OnLoad
    .byte 0
TH_Route1_MapScripts::
    .byte 0

    .include "data/scripts/three_horizons/home.inc"
    .include "data/scripts/three_horizons/town.inc"
    .include "data/scripts/three_horizons/lab.inc"
    .include "data/scripts/three_horizons/route.inc"
    .include "data/scripts/three_horizons/ending.inc"
    .include "data/scripts/three_horizons/text.inc"

.include "data/maps/TH_Route21Shore/scripts.inc"

.include "data/scripts/three_horizons/journey.inc"
.include "data/scripts/three_horizons/training.inc"
.include "data/maps/TH_ViridianEntrance/scripts.inc"
.include "data/maps/TH_Route2/scripts.inc"
.include "data/maps/TH_ForestSouthGate/scripts.inc"
.include "data/maps/TH_ForestNorthGate/scripts.inc"
.include "data/maps/TH_ViridianForest/scripts.inc"
.include "data/maps/TH_Pewter/scripts.inc"
.include "data/maps/TH_PewterGym/scripts.inc"
.include "data/maps/TH_ViridianCenter/scripts.inc"
.include "data/maps/TH_PewterCenter/scripts.inc"
.include "data/maps/TH_ViridianMart/scripts.inc"
.include "data/maps/TH_PewterMart/scripts.inc"
