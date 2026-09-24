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
    copyvar VAR_0x8009, VAR_TH_TRAINING_KIT_MASK
    special TH_ScriptDeliverTrainingKit
    goto_if_eq VAR_0x8009, VAR_TH_TRAINING_KIT_MASK, TH_HomePC_Open
    msgbox TH_Text_TrainingKit
TH_HomePC_Open:
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

TH_EventScript_Dresser::
    lockall
    msgbox TH_Text_Dresser
    closemessage
    dynmultichoice 0, 0, FALSE, 8, 0, DYN_MULTICHOICE_CB_NONE, TH_Text_OutfitRed, TH_Text_OutfitLeaf, TH_Text_OutfitBrendan, TH_Text_OutfitMay, TH_Text_OutfitGold, TH_Text_OutfitKris, TH_Text_OutfitSilver, TH_Text_OutfitCancel
    goto_if_ge VAR_RESULT, TH_OUTFIT_COUNT, TH_DresserDone
    copyvar VAR_0x8004, VAR_RESULT
    closemessage
    fadescreen FADE_TO_BLACK
    special TH_ChangeOutfit
    fadescreen FADE_FROM_BLACK
TH_DresserDone:
    releaseall
    end

TH_Text_TrainingKit:
    .string "Your training kit is in ITEM STORAGE.\nPower items help train specific stats.\pThe EXP. SHARE helps your whole party.\nWithdraw it, then turn it on in the BAG.\pBattles still give their usual EVs.\nYou can turn the EXP. SHARE off anytime.$"
