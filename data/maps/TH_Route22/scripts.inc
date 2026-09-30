TH_Route22_MapScripts::
    map_script MAP_SCRIPT_ON_LOAD, TH_Route22_HideRival
    .byte 0
TH_Route22_HideRival:
    setflag FLAG_TH_HIDE_CHAPTER_RIVAL
    return
