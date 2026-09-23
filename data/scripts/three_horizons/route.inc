TH_EventScript_CatchHelp::
    msgbox TH_Text_CatchHelp, MSGBOX_NPC
    end
TH_EventScript_BirdLocal::
    msgbox TH_Text_BirdLocal, MSGBOX_NPC
    end
TH_EventScript_Hoothoot::
    lockall
    goto_if_eq VAR_TH_SIGHTING_SEEN, 1, TH_HoothootRepeat
    playmoncry SPECIES_HOOTHOOT, CRY_MODE_NORMAL
    msgbox TH_Text_HoothootFirst
    waitmoncry
    setvar VAR_TH_SIGHTING_SEEN, 1
    releaseall
    end
TH_HoothootRepeat:
    msgbox TH_Text_HoothootRepeat
    releaseall
    end
