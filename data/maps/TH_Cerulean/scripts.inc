TH_Cerulean_MapScripts::
    map_script MAP_SCRIPT_ON_LOAD, TH_Cerulean_CloseFacilities
    .byte 0
TH_Cerulean_CloseFacilities:
    setmetatile 1, 12, 169, TRUE
    setflag FLAG_TH_HIDE_CHAPTER_RIVAL
    goto_if_set FLAG_BADGE02_GET, TH_Cerulean_PoliceAside
    setobjectxyperm LOCALID_TH_CERULEAN_0, 30, 12
    return
TH_Cerulean_PoliceAside:
    setobjectxyperm LOCALID_TH_CERULEAN_0, 31, 12
    return
