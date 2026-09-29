TH12_Ship_Board::
    lockall
    faceplayer
    call TH13_Ship_InspectTicket
    releaseall
    end
TH12_Ship_CheckTicket::
    specialvar VAR_RESULT, GetPlayerFacingDirection
    goto_if_ne VAR_RESULT, DIR_SOUTH, TH12_Ship_End
    lockall
    setvar VAR_LAST_TALKED, LOCALID_TH12_VERMILIONCITY_5
    faceplayer
    call TH13_Ship_InspectTicket
    goto_if_eq VAR_RESULT, TRUE, TH13_Ship_Release
    closemessage
    applymovement OBJ_EVENT_ID_PLAYER, TH12_Ship_StepUp
    waitmovement 0
TH13_Ship_Release:
    releaseall
TH12_Ship_End:
    end
TH13_Ship_InspectTicket:
    goto_if_set FLAG_TH13_SHIP_DEPARTED, TH13_Ship_Departed
    checkitem ITEM_SS_TICKET
    goto_if_eq VAR_RESULT, FALSE, TH13_Ship_RejectTicket
    msgbox TH13_Ship_TicketAcceptedText
    setvar VAR_RESULT, TRUE
    return
TH13_Ship_RejectTicket:
    msgbox TH12_Ship_NoTicket
    setvar VAR_RESULT, FALSE
    return
TH13_Ship_Departed:
    msgbox TH13_Ship_DepartedText
    setvar VAR_RESULT, FALSE
    return
TH13_Ship_TicketAcceptedText:
    .string "SAILOR: May I see your S.S. TICKET?\nYes, everything is in order!\pWelcome aboard the S.S. ANNE!\nPlease keep your ticket with you.$"
TH13_Ship_DepartedText:
    .string "SAILOR: The S.S. ANNE has sailed.\nBoarding is now closed.$"
TH12_Ship_StepUp:
    walk_up
    step_end
TH12_Ship_NoTicket:
    .string "A S.S. TICKET is required to board.\nBILL might be able to help you.$"

TH13_Ship_FinalExit::
    specialvar VAR_RESULT, GetPlayerFacingDirection
    goto_if_ne VAR_RESULT, DIR_NORTH, TH12_Ship_End
    goto_if_unset FLAG_TH12_SHIP_RIVAL, TH12_Ship_End
    goto_if_unset FLAG_TH12_CUT, TH12_Ship_End
    checkitem ITEM_HM01
    goto_if_eq VAR_RESULT, FALSE, TH12_Ship_End
    goto_if_set FLAG_TH13_SHIP_DEPARTED, TH12_Ship_End
    lockall
    msgbox TH13_Ship_FinalWarning, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, TH13_Ship_Stay
    closemessage
    hidefollower TRUE
    getplayerxy VAR_0x8004, VAR_0x8005
    goto_if_eq VAR_0x8004, 31, TH13_Ship_AlignRight
    goto_if_eq VAR_0x8004, 33, TH13_Ship_AlignLeft
    goto TH13_Ship_ViewDeparture
TH13_Ship_AlignRight:
    applymovement LOCALID_PLAYER, TH13_Ship_OneRight
    waitmovement 0
    goto TH13_Ship_ViewDeparture
TH13_Ship_AlignLeft:
    applymovement LOCALID_PLAYER, TH13_Ship_OneLeft
    waitmovement 0
TH13_Ship_ViewDeparture:
    applymovement LOCALID_PLAYER, TH13_Ship_ToViewingPoint
    waitmovement 0
TH13_Ship_DepartNow:
    fadenewbgm MUS_RG_SURF
    delay 50
    special DoSSAnneDepartureCutscene
    waitstate
    setflag FLAG_TH13_SHIP_DEPARTED
    removeobject LOCALID_TH12_SSANNE_EXTERIOR_0
    warp MAP_TH12_VERMILION_CITY, 23, 32
    waitstate
    special TH_RefreshFollower
    releaseall
    end
TH13_Ship_Stay:
    closemessage
    applymovement LOCALID_PLAYER, TH13_Ship_OneDown
    waitmovement 0
    releaseall
    end
TH13_Ship_OneRight:
    walk_right
    step_end
TH13_Ship_OneLeft:
    walk_left
    step_end
TH13_Ship_OneDown:
    walk_down
    step_end
TH13_Ship_ToViewingPoint:
    walk_down
    walk_down
    walk_down
    walk_down
    walk_down
    walk_down
    walk_down
    step_end
TH13_Ship_FinalWarning:
    .string "The S.S. ANNE will sail when you\nleave. Boarding will close.\pFinish any optional visits first.\nLeave now?$"

TH12_Ship_Heal::
    lock
    faceplayer
    msgbox TH12_Ship_HealOffer, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, TH12_Ship_HealEnd
    closemessage
    hidefollower TRUE
    fadescreen FADE_TO_BLACK
    special HealPlayerParty
    playfanfare MUS_HEAL
    waitfanfare
    fadescreen FADE_FROM_BLACK
    special TH_RefreshFollower
    msgbox TH12_Ship_HealDone
TH12_Ship_HealEnd:
    release
    end
TH12_Ship_HealOffer:
    .string "This cabin is quiet. Would you\nand your POKéMON like to rest?$"
TH12_Ship_HealDone:
    .string "Everyone looks refreshed!\nEnjoy the rest of your visit.$"

TH12_Captain_Talk::
    lock
    goto_if_set FLAG_TH12_CUT, TH12_Captain_Already
    turnobject LOCALID_TH12_SSANNE_CAPTAINSOFFICE_0, DIR_NORTH
    goto_if_unset FLAG_TH12_SHIP_RIVAL, TH12_Captain_Wait
    checkitem ITEM_HM01
    goto_if_eq VAR_RESULT, TRUE, TH12_Captain_Receipt
    msgbox TH12_Captain_Sick
    closemessage
    playse SE_USE_ITEM
    delay 45
    faceplayer
    msgbox TH12_Captain_Thanks
    giveitem ITEM_HM01
    goto_if_eq VAR_RESULT, FALSE, TH12_RewardBagFull
TH12_Captain_Receipt:
    setflag FLAG_TH12_CUT
TH12_Captain_Already:
    faceplayer
    msgbox TH12_Captain_Use
    release
    end
TH12_Captain_Wait:
    msgbox TH12_Captain_WaitText
    release
    end
TH12_Captain_WaitText:
    .string "Your friend is waiting outside.\nPlease settle your battle first.$"
TH12_Captain_Sick:
    .string "Urgh… I am terribly seasick.\p{PLAYER} gently rubbed the\nCAPTAIN's back.$"
TH12_Captain_Thanks:
    .string "Thank you! I feel much better!\nLet me share my CUT technique.$"
TH12_Captain_Use:
    .string "Carry HM01 and your CASCADE BADGE.\nA healthy, compatible POKéMON can\lCUT small trees without learning it.\pEGGS cannot help with field moves.\pWe will sail when you leave. Finish\nyour visits before the final exit!$"

TH12_Ship_Snorlax::
    lock
    faceplayer
    msgbox TH12_Ship_SnorlaxText
    showmonpic SPECIES_SNORLAX, 10, 3
    waitbuttonpress
    hidemonpic
    release
    end
TH12_Ship_SnorlaxText:
    .string "I saw a POKéMON sleeping by a road.\nIt looked just like this SNORLAX!$"

TH12_Ship_Observation::
    lock
    faceplayer
    setvar VAR_0x8004, TH_RESEARCH_SHIP
    special TH_ScriptResearchObserve
    goto_if_set FLAG_TH12_SHIP_STORY, TH12_Ship_ObservationAgain
    msgbox TH12_Ship_ObservationText
    setflag FLAG_TH12_SHIP_STORY
    release
    end
TH12_Ship_ObservationAgain:
    msgbox TH12_Ship_ObservationRepeat
    release
    end
TH12_Ship_ObservationText:
    .string "I keep the ship's cargo records.\nJOHTO and HOENN berries arrive here\lalmost every week.\pWe found leaf prints on the crates,\nand tiny POKéMON tracks on deck.\pBILL thinks some travelers followed\nthe shipments into KANTO.\pForests and caves offer familiar\nhomes, even across a different sea.$"
TH12_Ship_ObservationRepeat:
    .string "Tell the professors what you see.\nA single sighting is a clue; many\lreports can reveal a migration.$"

TH12_Ship_RivalTrigger::
    goto_if_set FLAG_TH12_SHIP_RIVAL, TH12_Ship_End
TH12_Ship_Rival::
    lockall
    goto_if_set FLAG_TH12_SHIP_RIVAL, TH12_Ship_RivalDone
    hidefollower TRUE
    setvar VAR_LAST_TALKED, LOCALID_TH12_SSANNE_2F_CORRIDOR_0
    applymovement LOCALID_TH12_SSANNE_2F_CORRIDOR_0, Common_Movement_FacePlayer
    waitmovement 0
    msgbox TH12_Ship_RivalIntro
    closemessage
    goto_if_eq VAR_TH_RIVAL_PARTNER, SPECIES_BULBASAUR, TH12_Ship_Rival_BULBASAUR
    goto_if_eq VAR_TH_RIVAL_PARTNER, SPECIES_CHARMANDER, TH12_Ship_Rival_CHARMANDER
    goto_if_eq VAR_TH_RIVAL_PARTNER, SPECIES_SQUIRTLE, TH12_Ship_Rival_SQUIRTLE
    goto_if_eq VAR_TH_RIVAL_PARTNER, SPECIES_CHIKORITA, TH12_Ship_Rival_CHIKORITA
    goto_if_eq VAR_TH_RIVAL_PARTNER, SPECIES_CYNDAQUIL, TH12_Ship_Rival_CYNDAQUIL
    goto_if_eq VAR_TH_RIVAL_PARTNER, SPECIES_TOTODILE, TH12_Ship_Rival_TOTODILE
    goto_if_eq VAR_TH_RIVAL_PARTNER, SPECIES_TREECKO, TH12_Ship_Rival_TREECKO
    goto_if_eq VAR_TH_RIVAL_PARTNER, SPECIES_TORCHIC, TH12_Ship_Rival_TORCHIC
    goto_if_eq VAR_TH_RIVAL_PARTNER, SPECIES_MUDKIP, TH12_Ship_Rival_MUDKIP
    goto TH12_Ship_RivalDone
TH12_Ship_Rival_BULBASAUR:
    trainerbattle_no_intro TRAINER_TH12_SHIP_BULBASAUR, TH12_Ship_RivalDefeat
    goto TH12_Ship_RivalVictory
TH12_Ship_Rival_CHARMANDER:
    trainerbattle_no_intro TRAINER_TH12_SHIP_CHARMANDER, TH12_Ship_RivalDefeat
    goto TH12_Ship_RivalVictory
TH12_Ship_Rival_SQUIRTLE:
    trainerbattle_no_intro TRAINER_TH12_SHIP_SQUIRTLE, TH12_Ship_RivalDefeat
    goto TH12_Ship_RivalVictory
TH12_Ship_Rival_CHIKORITA:
    trainerbattle_no_intro TRAINER_TH12_SHIP_CHIKORITA, TH12_Ship_RivalDefeat
    goto TH12_Ship_RivalVictory
TH12_Ship_Rival_CYNDAQUIL:
    trainerbattle_no_intro TRAINER_TH12_SHIP_CYNDAQUIL, TH12_Ship_RivalDefeat
    goto TH12_Ship_RivalVictory
TH12_Ship_Rival_TOTODILE:
    trainerbattle_no_intro TRAINER_TH12_SHIP_TOTODILE, TH12_Ship_RivalDefeat
    goto TH12_Ship_RivalVictory
TH12_Ship_Rival_TREECKO:
    trainerbattle_no_intro TRAINER_TH12_SHIP_TREECKO, TH12_Ship_RivalDefeat
    goto TH12_Ship_RivalVictory
TH12_Ship_Rival_TORCHIC:
    trainerbattle_no_intro TRAINER_TH12_SHIP_TORCHIC, TH12_Ship_RivalDefeat
    goto TH12_Ship_RivalVictory
TH12_Ship_Rival_MUDKIP:
    trainerbattle_no_intro TRAINER_TH12_SHIP_MUDKIP, TH12_Ship_RivalDefeat
    goto TH12_Ship_RivalVictory
TH12_Ship_RivalVictory:
    setflag FLAG_TH12_SHIP_RIVAL
    msgbox TH12_Ship_RivalAfter
    closemessage
    getplayerxy VAR_0x8004, VAR_0x8005
    goto_if_eq VAR_0x8004, 32, TH13_Ship_RivalExitLeft
    applymovement LOCALID_TH12_SSANNE_2F_CORRIDOR_0, TH13_Ship_RivalWalkRight
    goto TH13_Ship_RivalExitWait
TH13_Ship_RivalExitLeft:
    applymovement LOCALID_TH12_SSANNE_2F_CORRIDOR_0, TH13_Ship_RivalWalkLeft
TH13_Ship_RivalExitWait:
    waitmovement 0
    removeobject LOCALID_TH12_SSANNE_2F_CORRIDOR_0
TH12_Ship_RivalDone:
    special TH_RefreshFollower
    releaseall
    end
TH13_Ship_RivalWalkRight:
    walk_right
    walk_down
    walk_down
    walk_down
    walk_down
    walk_down
    walk_down
    walk_down
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    step_end
TH13_Ship_RivalWalkLeft:
    walk_left
    walk_down
    walk_down
    walk_down
    walk_down
    walk_down
    walk_down
    walk_down
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    step_end
TH12_Ship_RivalIntro:
    .string "{RIVAL}: You made it aboard!\nMy partner and I have been training.\pShow me what your team can do!$"
TH12_Ship_RivalDefeat:
    .string "You have really improved!$"
TH12_Ship_RivalAfter:
    .string "{RIVAL}: I heard the captain knows\nCUT. That should help you reach\lLT. SURGE's GYM.\pI will keep training my partner.\nYou had better keep up!$"

TH13_Ship_Marill::
    lockall
    playmoncry SPECIES_MARILL, CRY_MODE_NORMAL
    goto TH13_Ship_Partners
TH13_Ship_Wingull::
    lockall
    playmoncry SPECIES_WINGULL, CRY_MODE_NORMAL
TH13_Ship_Partners:
    msgbox TH13_Ship_PartnersText
    waitmoncry
    setvar VAR_0x8004, TH_RESEARCH_SHIP
    special TH_ScriptResearchObserve
    setvar VAR_0x8004, TH_PHOTO_SHIP
    call TH13_ResearchPhoto
    releaseall
    end
TH13_Ship_PartnersText:
    .string "MARILL and WINGULL enjoy the breeze.\nTheir trainers met on this voyage.\pTravel brings POKéMON from\ndifferent regions together.$"

@ The partners' trainers disembarked in Vermilion. A later visit with Gear
@ can record this live scene even though the S.S. Anne has sailed.
TH13_Harbor_OnLoad::
    setflag FLAG_TEMP_11
    goto_if_unset FLAG_TH13_SHIP_DEPARTED, TH13_Harbor_LoadDone
    clearflag FLAG_TEMP_11
TH13_Harbor_LoadDone:
    return
TH13_Harbor_Marill::
    lockall
    goto_if_unset FLAG_TH13_SHIP_DEPARTED, TH13_Harbor_End
    playmoncry SPECIES_MARILL, CRY_MODE_NORMAL
    goto TH13_Harbor_Partners
TH13_Harbor_Wingull::
    lockall
    goto_if_unset FLAG_TH13_SHIP_DEPARTED, TH13_Harbor_End
    playmoncry SPECIES_WINGULL, CRY_MODE_NORMAL
TH13_Harbor_Partners:
    msgbox TH13_Harbor_PartnersText
    waitmoncry
    setvar VAR_0x8004, TH_RESEARCH_SHIP
    special TH_ScriptResearchObserve
    setvar VAR_0x8004, TH_PHOTO_SHIP
    call TH13_ResearchPhoto
TH13_Harbor_End:
    releaseall
    end
TH13_Harbor_PartnersText:
    .string "MARILL and WINGULL share the breeze.\nTheir trainers stayed in VERMILION.\pThe ship has sailed, but these\ntravelers are enjoying KANTO.$"
