TH_EventScript_Mom::
    lock
    faceplayer
    goto_if_ge VAR_TH_STAGE, TH_STAGE_PARTNER, TH_MomHeal
    msgbox TH_Text_MomMorning
    release
    end
TH_MomHeal:
    msgbox TH_Text_MomRest
    call Common_EventScript_OutOfCenterPartyHeal
    release
    end
TH_EventScript_WhiteoutRecovery::
    lockall
    msgbox TH_Text_MomRecovery
    call Common_EventScript_OutOfCenterPartyHeal
    fadedefaultbgm
    releaseall
    end
TH_EventScript_TV::
    msgbox TH_Text_TV, MSGBOX_SIGN
    end
