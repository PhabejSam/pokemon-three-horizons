TH_Pewter_MapScripts::
    map_script MAP_SCRIPT_ON_LOAD, TH_Pewter_NewMuseumVisit
    .byte 0
TH_Pewter_NewMuseumVisit:
    setvar VAR_TEMP_2, 0
    clearflag FLAG_TH12_MUSEUM_VISIT
    end
