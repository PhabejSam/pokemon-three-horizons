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

TH_EventScript_HomePC::
    lockall
    setvar VAR_0x8004, PC_LOCATION_PLAYER_HOUSE_FRLG
    special DoPCTurnOnEffect
    playse SE_PC_ON
    msgbox gText_PlayerHouseBootPC, MSGBOX_DEFAULT
    special PlayerPC
    setvar VAR_0x8004, PC_LOCATION_PLAYER_HOUSE_FRLG
    playse SE_PC_OFF
    special DoPCTurnOffEffect
    releaseall
    end

TH_EventScript_BedroomSign::
    msgbox TH_Text_BedroomSign, MSGBOX_SIGN
    end
TH_EventScript_Console::
    msgbox TH_Text_Console, MSGBOX_SIGN
    end

TH_EventScript_Kitchen::
    msgbox TH_Text_Kitchen, MSGBOX_SIGN
    end

TH_EventScript_Books::
    msgbox TH_Text_Books, MSGBOX_SIGN
    end

TH_EventScript_Fridge::
    msgbox TH_Text_Fridge, MSGBOX_SIGN
    end

TH_EventScript_Bed::
    msgbox TH_Text_Bed, MSGBOX_SIGN
    end

TH_EventScript_Research::
    msgbox TH_Text_Research, MSGBOX_SIGN
    end

TH_EventScript_Clock::
    lockall
    goto_if_set FLAG_SET_WALL_CLOCK, TH_ClockView
    msgbox TH_Text_ClockStopped, MSGBOX_DEFAULT
    closemessage
    fadescreen FADE_TO_BLACK
    special StartWallClock
    setflag FLAG_SET_WALL_CLOCK
    releaseall
    end
TH_ClockView:
    incrementgamestat GAME_STAT_CHECKED_CLOCK
    fadescreen FADE_TO_BLACK
    special Special_ViewWallClock
    releaseall
    end
TH_Text_ClockStopped:
    .string "A new morning, a new adventure.\nLet's set the time before you go.$"
