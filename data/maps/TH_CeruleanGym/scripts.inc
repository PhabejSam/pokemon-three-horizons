TH_CeruleanGym_MapScripts::
    map_script MAP_SCRIPT_ON_LOAD, TH_CeruleanGym_PlaceLuis
    .byte 0
TH_CeruleanGym_PlaceLuis:
    goto_if_defeated TRAINER_TH9_SWIMMER_MALE_LUIS, TH_CeruleanGym_LuisAtEdge
    setobjectxyperm LOCALID_TH_CERULEANGYM_0, 11, 12
    return
TH_CeruleanGym_LuisAtEdge:
    setobjectxyperm LOCALID_TH_CERULEANGYM_0, 10, 12
    return
