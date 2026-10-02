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
    map_script MAP_SCRIPT_ON_FRAME_TABLE, TH_Lab_FirstEntryTable
    .byte 0
TH_Route1_MapScripts::
    .byte 0

    .include "data/scripts/three_horizons/home.inc"
    .include "data/scripts/three_horizons/town.inc"
    .include "data/scripts/three_horizons/lab.inc"
    .include "data/scripts/three_horizons/route.inc"
    .include "data/scripts/three_horizons/ending.inc"
    .include "data/scripts/three_horizons/text.inc"
    .include "data/scripts/three_horizons/chapter13_research.inc"

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

.include "data/scripts/three_horizons/chapter9_locals.inc"
.include "data/scripts/three_horizons/chapter9.inc"
.include "data/scripts/three_horizons/rewards.inc"
.include "data/maps/TH_Route22/scripts.inc"
.include "data/maps/TH_LeagueGate/scripts.inc"
.include "data/maps/TH_Route3/scripts.inc"
.include "data/maps/TH_Route4/scripts.inc"
.include "data/maps/TH_Route4Center/scripts.inc"
.include "data/maps/TH_MtMoon1F/scripts.inc"
.include "data/maps/TH_MtMoonB1F/scripts.inc"
.include "data/maps/TH_MtMoonB2F/scripts.inc"
.include "data/maps/TH_Cerulean/scripts.inc"
.include "data/maps/TH_CeruleanGym/scripts.inc"
.include "data/maps/TH_CeruleanMart/scripts.inc"
.include "data/maps/TH_CeruleanCenter/scripts.inc"
.include "data/maps/TH_CeruleanHouse1/scripts.inc"
.include "data/maps/TH_CeruleanHouse2/scripts.inc"
.include "data/maps/TH_CeruleanHouse3/scripts.inc"
.include "data/maps/TH_CeruleanHouse4/scripts.inc"
.include "data/maps/TH_CeruleanHouse5/scripts.inc"
.include "data/maps/TH_CeruleanBikeShop/scripts.inc"
.include "data/maps/TH_RivalHouse/scripts.inc"
.include "data/maps/TH_ViridianHouse/scripts.inc"
.include "data/maps/TH_ViridianSchool/scripts.inc"
.include "data/maps/TH_ViridianGym/scripts.inc"
.include "data/maps/TH_PewterHouse1/scripts.inc"
.include "data/maps/TH_PewterHouse2/scripts.inc"
.include "data/maps/TH_PewterMuseum1F/scripts.inc"
.include "data/maps/TH_PewterMuseum2F/scripts.inc"

.include "data/scripts/three_horizons/playtest11_story.inc"
.include "data/scripts/three_horizons/playtest11_maps.inc"
.include "data/maps/TH12_Route24/scripts.inc"
.include "data/maps/TH12_Route25/scripts.inc"
.include "data/maps/TH12_Route25_SeaCottage/scripts.inc"
.include "data/scripts/three_horizons/chapter12_bill_trainers.inc"
.include "data/scripts/three_horizons/chapter12_bill.inc"
.include "data/maps/TH12_Route5/scripts.inc"
.include "data/maps/TH12_Route5_SouthEntrance/scripts.inc"
.include "data/maps/TH12_Route6/scripts.inc"
.include "data/maps/TH12_Route6_NorthEntrance/scripts.inc"
.include "data/maps/TH12_UndergroundPath_NorthEntrance/scripts.inc"
.include "data/maps/TH12_UndergroundPath_NorthSouthTunnel/scripts.inc"
.include "data/maps/TH12_UndergroundPath_SouthEntrance/scripts.inc"
.include "data/maps/TH12_VermilionCity/scripts.inc"
.include "data/maps/TH12_VermilionCity_Mart/scripts.inc"
.include "data/maps/TH12_VermilionCity_PokemonCenter_1F/scripts.inc"
.include "data/maps/TH12_VermilionCity_PokemonFanClub/scripts.inc"
.include "data/maps/TH12_VermilionCity_House1/scripts.inc"
.include "data/maps/TH12_VermilionCity_House2/scripts.inc"
.include "data/maps/TH12_VermilionCity_House3/scripts.inc"
.include "data/maps/TH12_SSAnne_1F_Corridor/scripts.inc"
.include "data/maps/TH12_SSAnne_1F_Room1/scripts.inc"
.include "data/maps/TH12_SSAnne_1F_Room2/scripts.inc"
.include "data/maps/TH12_SSAnne_1F_Room3/scripts.inc"
.include "data/maps/TH12_SSAnne_1F_Room4/scripts.inc"
.include "data/maps/TH12_SSAnne_1F_Room5/scripts.inc"
.include "data/maps/TH12_SSAnne_1F_Room6/scripts.inc"
.include "data/maps/TH12_SSAnne_1F_Room7/scripts.inc"
.include "data/maps/TH12_SSAnne_2F_Corridor/scripts.inc"
.include "data/maps/TH12_SSAnne_2F_Room1/scripts.inc"
.include "data/maps/TH12_SSAnne_2F_Room2/scripts.inc"
.include "data/maps/TH12_SSAnne_2F_Room3/scripts.inc"
.include "data/maps/TH12_SSAnne_2F_Room4/scripts.inc"
.include "data/maps/TH12_SSAnne_2F_Room5/scripts.inc"
.include "data/maps/TH12_SSAnne_2F_Room6/scripts.inc"
.include "data/maps/TH12_SSAnne_3F_Corridor/scripts.inc"
.include "data/maps/TH12_SSAnne_B1F_Corridor/scripts.inc"
.include "data/maps/TH12_SSAnne_B1F_Room1/scripts.inc"
.include "data/maps/TH12_SSAnne_B1F_Room2/scripts.inc"
.include "data/maps/TH12_SSAnne_B1F_Room3/scripts.inc"
.include "data/maps/TH12_SSAnne_B1F_Room4/scripts.inc"
.include "data/maps/TH12_SSAnne_B1F_Room5/scripts.inc"
.include "data/maps/TH12_SSAnne_CaptainsOffice/scripts.inc"
.include "data/maps/TH12_SSAnne_Deck/scripts.inc"
.include "data/maps/TH12_SSAnne_Exterior/scripts.inc"
.include "data/maps/TH12_SSAnne_Kitchen/scripts.inc"
.include "data/maps/TH12_VermilionCity_Gym/scripts.inc"
.include "data/scripts/three_horizons/chapter12_locals.inc"
.include "data/scripts/three_horizons/chapter12_vermilion.inc"
.include "data/scripts/three_horizons/chapter12_ship.inc"
.include "data/scripts/three_horizons/chapter12_gym.inc"

.include "data/scripts/three_horizons/chapter12_sightings.inc"

.include "data/maps/TH13_Route5_PokemonDayCare/scripts.inc"
.include "data/scripts/three_horizons/chapter13_routes.inc"
.include "data/maps/TH13_Route11/scripts.inc"
.include "data/maps/TH13_DiglettsCave_SouthEntrance/scripts.inc"
.include "data/maps/TH13_DiglettsCave_B1F/scripts.inc"
.include "data/maps/TH13_DiglettsCave_NorthEntrance/scripts.inc"

.include "data/maps/TH13_Route2_EastBuilding/scripts.inc"
.include "data/scripts/three_horizons/chapter13_route2.inc"

.include "data/maps/TH13_Route2_House/scripts.inc"

    .include "data/maps/TH13_Route9/scripts.inc"

    .include "data/maps/TH13_Route10/scripts.inc"

    .include "data/maps/TH13_RockTunnel_1F/scripts.inc"

    .include "data/maps/TH13_RockTunnel_B1F/scripts.inc"

    .include "data/maps/TH13_Route10_PokemonCenter_1F/scripts.inc"

    .include "data/maps/TH13_ViridianCenter2F/scripts.inc"

    .include "data/maps/TH13_PewterCenter2F/scripts.inc"

    .include "data/maps/TH13_CeruleanCenter2F/scripts.inc"

    .include "data/maps/TH13_Route4Center2F/scripts.inc"

    .include "data/maps/TH13_VermilionCenter2F/scripts.inc"

    .include "data/maps/TH13_Route10_PokemonCenter_2F/scripts.inc"

    .include "data/scripts/three_horizons/chapter13_rock_tunnel.inc"
    .include "data/scripts/three_horizons/chapter13_centers.inc"

    .include "data/maps/TH13_LavenderTown/scripts.inc"

    .include "data/maps/TH13_LavenderTown_PokemonCenter_1F/scripts.inc"

    .include "data/maps/TH13_LavenderTown_Mart/scripts.inc"

    .include "data/maps/TH13_LavenderTown_House1/scripts.inc"

    .include "data/maps/TH13_LavenderTown_House2/scripts.inc"

    .include "data/maps/TH13_LavenderTown_VolunteerPokemonHouse/scripts.inc"

    .include "data/maps/TH13_LavenderTown_PokemonCenter_2F/scripts.inc"

    .include "data/scripts/three_horizons/chapter13_lavender.inc"

    .include "data/maps/TH13_PokemonTower_1F/scripts.inc"

    .include "data/maps/TH13_PokemonTower_2F/scripts.inc"

    .include "data/maps/TH13_PokemonTower_3F/scripts.inc"

    .include "data/maps/TH13_PokemonTower_4F/scripts.inc"

    .include "data/maps/TH13_PokemonTower_5F/scripts.inc"

    .include "data/maps/TH13_PokemonTower_6F/scripts.inc"

    .include "data/scripts/three_horizons/chapter13_tower.inc"

    .include "data/maps/TH14_Route8/scripts.inc"
    .include "data/maps/TH14_Route8_WestEntrance/scripts.inc"
    .include "data/maps/TH14_UndergroundPath_EastEntrance/scripts.inc"
    .include "data/maps/TH14_UndergroundPath_EastWestTunnel/scripts.inc"
    .include "data/maps/TH14_UndergroundPath_WestEntrance/scripts.inc"
    .include "data/maps/TH14_Route7/scripts.inc"
    .include "data/maps/TH14_Route7_EastEntrance/scripts.inc"
    .include "data/scripts/three_horizons/chapter14_travel.inc"

    .include "data/maps/TH14_CeladonCity/scripts.inc"
    .include "data/maps/TH14_CeladonCity_PokemonCenter_1F/scripts.inc"
    .include "data/maps/TH14_CeladonCity_PokemonCenter_2F/scripts.inc"
    .include "data/maps/TH14_CeladonCity_Gym/scripts.inc"
    .include "data/maps/TH14_CeladonCity_DepartmentStore_1F/scripts.inc"
    .include "data/maps/TH14_CeladonCity_DepartmentStore_2F/scripts.inc"
    .include "data/maps/TH14_CeladonCity_DepartmentStore_3F/scripts.inc"
    .include "data/maps/TH14_CeladonCity_DepartmentStore_4F/scripts.inc"
    .include "data/maps/TH14_CeladonCity_DepartmentStore_5F/scripts.inc"
    .include "data/maps/TH14_CeladonCity_DepartmentStore_Elevator/scripts.inc"
    .include "data/maps/TH14_CeladonCity_DepartmentStore_Roof/scripts.inc"
    .include "data/maps/TH14_CeladonCity_Condominiums_1F/scripts.inc"
    .include "data/maps/TH14_CeladonCity_Condominiums_2F/scripts.inc"
    .include "data/maps/TH14_CeladonCity_Condominiums_3F/scripts.inc"
    .include "data/maps/TH14_CeladonCity_Condominiums_Roof/scripts.inc"
    .include "data/maps/TH14_CeladonCity_Condominiums_RoofRoom/scripts.inc"
    .include "data/maps/TH14_CeladonCity_GameCorner/scripts.inc"
    .include "data/maps/TH14_CeladonCity_GameCorner_PrizeRoom/scripts.inc"
    .include "data/maps/TH14_CeladonCity_Restaurant/scripts.inc"
    .include "data/maps/TH14_CeladonCity_Hotel/scripts.inc"
    .include "data/maps/TH14_CeladonCity_House1/scripts.inc"
    .include "data/scripts/three_horizons/chapter14_celadon.inc"

    .include "data/scripts/three_horizons/chapter14_gym.inc"

    .include "data/scripts/three_horizons/chapter14_hideout.inc"
    .include "data/scripts/three_horizons/chapter14_tower.inc"
    .include "data/maps/TH14_RocketHideout_B1F/scripts.inc"
    .include "data/maps/TH14_RocketHideout_B2F/scripts.inc"
    .include "data/maps/TH14_RocketHideout_B3F/scripts.inc"
    .include "data/maps/TH14_RocketHideout_B4F/scripts.inc"
    .include "data/maps/TH14_RocketHideout_Elevator/scripts.inc"

    .include "data/maps/TH14_PokemonTower_7F/scripts.inc"
