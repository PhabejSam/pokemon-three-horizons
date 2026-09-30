@ Bridge challengers retain native lanes. The recruiter never occupies the path.
TH12_Bridge_RecruiterTrigger::
    goto_if_defeated TRAINER_TH12_BRIDGE_RECRUITER, TH12_Bill_End
TH12_Bridge_Recruiter::
    lockall
    setvar VAR_LAST_TALKED, LOCALID_TH12_ROUTE24_0
    faceplayer
    goto_if_not_defeated TRAINER_TH12_BUG_CATCHER_CALE, TH12_Bridge_NotReady
    goto_if_not_defeated TRAINER_TH12_LASS_ALI, TH12_Bridge_NotReady
    goto_if_not_defeated TRAINER_TH12_YOUNGSTER_TIMMY, TH12_Bridge_NotReady
    goto_if_not_defeated TRAINER_TH12_LASS_RELI, TH12_Bridge_NotReady
    goto_if_not_defeated TRAINER_TH12_CAMPER_ETHAN, TH12_Bridge_NotReady
    goto_if_set FLAG_TH12_BRIDGE_NUGGET, TH12_Bridge_Offer
    msgbox TH12_Bridge_PrizeText
    giveitem ITEM_NUGGET
    goto_if_eq VAR_RESULT, FALSE, TH12_Bill_BagFull
    setflag FLAG_TH12_BRIDGE_NUGGET
TH12_Bridge_Offer:
    goto_if_defeated TRAINER_TH12_BRIDGE_RECRUITER, TH12_Bridge_After
    msgbox TH12_Bridge_OfferText
    trainerbattle_lavaridge LOCALID_TH12_ROUTE24_0, TRAINER_TH12_BRIDGE_RECRUITER, NULL, TH12_Bridge_DefeatText, TH12_Bridge_After
    end
TH12_Bridge_After:
    msgbox TH12_Bridge_AfterText
    releaseall
    end
TH12_Bridge_NotReady:
    msgbox TH12_Bridge_NotReadyText
    releaseall
    end
TH12_Bridge_PrizeText:
    .string "Five wins on NUGGET BRIDGE!\nYou've earned this prize.$"
TH12_Bridge_OfferText:
    .string "With talent like yours, you could\njoin TEAM ROCKET!\pNot interested? Then let me show\nyou what you're missing!$"
TH12_Bridge_DefeatText:
    .string "All right! You made your point!$"
TH12_Bridge_AfterText:
    .string "You won't join us? Fine.\nI'll have to recruit someone else.$"
TH12_Bridge_NotReadyText:
    .string "Beat all five bridge challengers\nto earn your prize!$"

TH12_Bill_OnEntry::
    goto_if_set FLAG_TH12_BILL_RESCUED, TH12_Bill_EntryDone
    setflag FLAG_TEMP_3
    setobjectxyperm LOCALID_TH12_ROUTE25_SEACOTTAGE_0, 3, 3
    goto_if_set FLAG_TH13_BILL_IN_MACHINE, TH13_Bill_EntryWaiting
    clearflag FLAG_TEMP_4
    clearflag FLAG_TEMP_2
    return
TH13_Bill_EntryWaiting:
    setflag FLAG_TEMP_2
    setflag FLAG_TEMP_4
    return
TH12_Bill_EntryDone:
    clearflag FLAG_TEMP_3
    setflag FLAG_TEMP_4
    clearflag FLAG_TEMP_2
    clearflag FLAG_TH13_BILL_IN_MACHINE
    setobjectxyperm LOCALID_TH12_ROUTE25_SEACOTTAGE_0, 7, 5
    return

TH12_Bill_Rescue::
    lockall
    faceplayer
    msgbox TH12_Bill_HelpText, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, TH12_Bill_Release
    msgbox TH12_Bill_PCInstruction
    closemessage
    hidefollower TRUE
    goto_if_eq VAR_FACING, DIR_SOUTH, TH12_Bill_GoAround
    applymovement LOCALID_TH12_ROUTE25_SEACOTTAGE_1, TH12_Bill_ToMachine
    goto TH12_Bill_EnterMachine
TH12_Bill_GoAround:
    applymovement LOCALID_TH12_ROUTE25_SEACOTTAGE_1, TH12_Bill_AroundPlayer
TH12_Bill_EnterMachine:
    waitmovement 0
    opendoor 10, 3
    waitdooranim
    applymovement LOCALID_TH12_ROUTE25_SEACOTTAGE_1, TH12_Bill_OneUp
    waitmovement 0
    removeobject LOCALID_TH12_ROUTE25_SEACOTTAGE_1
    closedoor 10, 3
    waitdooranim
    setflag FLAG_TH13_BILL_IN_MACHINE
    setflag FLAG_TEMP_2
    special TH_RefreshFollower
    releaseall
    end
TH12_Bill_Computer::
    lockall
    goto_if_set FLAG_TH12_BILL_RESCUED, TH12_Bill_PCNotes
    goto_if_unset FLAG_TH13_BILL_IN_MACHINE, TH12_Bill_PCIdle
    msgbox TH12_Bill_StartText
    closemessage
    hidefollower TRUE
    setvar VAR_0x8004, 0
    special AnimateTeleporterHousing
    delay 60
    playse SE_WARP_IN
    special AnimateTeleporterCable
    waitse
    delay 60
    setvar VAR_0x8004, 1
    special AnimateTeleporterHousing
    delay 60
    opendoor 3, 3
    waitdooranim
    clearflag FLAG_TEMP_3
    addobject LOCALID_TH12_ROUTE25_SEACOTTAGE_0
    applymovement LOCALID_TH12_ROUTE25_SEACOTTAGE_0, TH12_Bill_FromMachine
    waitmovement 0
    closedoor 3, 3
    waitdooranim
    applymovement LOCALID_TH12_ROUTE25_SEACOTTAGE_0, TH12_Bill_ToRoom
    waitmovement 0
    setobjectxyperm LOCALID_TH12_ROUTE25_SEACOTTAGE_0, 7, 5
    clearflag FLAG_TEMP_2
    setflag FLAG_TH12_BILL_RESCUED
    clearflag FLAG_TH13_BILL_IN_MACHINE
    special TH_RefreshFollower
    msgbox TH12_Bill_ThanksText
    releaseall
    end
TH12_Bill_PCIdle:
    msgbox TH12_Bill_PCIdleText
    releaseall
    end
TH12_Bill_PCNotes:
    msgbox TH12_Bill_NotesText
    releaseall
    end
TH12_Bill_Talk::
    lockall
    faceplayer
    goto_if_unset FLAG_TH12_BILL_RESCUED, TH12_Bill_Release
    goto_if_set FLAG_TH12_TICKET, TH12_Bill_Report
    checkitem ITEM_SS_TICKET
    goto_if_eq VAR_RESULT, TRUE, TH12_Bill_TicketOwned
    msgbox TH12_Bill_TicketText
    giveitem ITEM_SS_TICKET
    goto_if_eq VAR_RESULT, FALSE, TH12_Bill_BagFull
TH12_Bill_TicketOwned:
    setflag FLAG_TH12_TICKET
TH12_Bill_Report:
    msgbox TH12_Bill_ReportText
TH12_Bill_Release:
    releaseall
TH12_Bill_End:
    end
TH12_Bill_BagFull:
    msgbox TH12_BillSlice_BagFullText
    releaseall
    end
TH12_Bill_ToMachine:
    walk_up
    walk_up
    step_end
TH12_Bill_AroundPlayer:
    walk_right
    walk_up
    walk_up
    walk_left
    face_up
    step_end
TH12_Bill_OneUp:
    walk_up
    step_end
TH12_Bill_FromMachine:
    walk_down
    step_end
TH12_Bill_ToRoom:
    walk_right
    walk_right
    walk_right
    walk_right
    walk_down
    face_down
    step_end
TH12_Bill_HelpText:
    .string "BILL: Don't be fooled! I'm a person,\nnot a CLEFAIRY!\pMy teleporter mixed up our cells.\nWill you help separate us?$"
TH12_Bill_PCInstruction:
    .string "I'll enter the right teleporter.\nPlease start the program on my PC!$"
TH12_Bill_PCIdleText:
    .string "A cell-separation program is ready.\nBILL needs to enter the machine first.$"
TH12_Bill_StartText:
    .string "{PLAYER} started the\ncell-separation program!$"
TH12_Bill_ThanksText:
    .string "BILL: I'm myself again! Thank you!\nCome over here. I owe you something.$"
TH12_Bill_TicketText:
    .string "BILL: Take my S.S. TICKET!\nThe S.S. ANNE is in VERMILION.\pThere are TRAINERS from many regions\non board. You might learn a lot.$"
TH12_Bill_ReportText:
    .string "BILL: I've compared the professors'\nforest, cave, and coastal reports.\pThe arrivals seem to cluster near\ntravel routes. That's only a theory.\pCould you ask the S.S. ANNE's crew\nwhat they've seen? Shipping records\lmight help us compare the dates.$"
TH12_Bill_NotesText:
    .string "BILL'S RESEARCH\nForest, cave, and coastal sightings.\pThe dates overlap with several ships'\narrivals. A connection is unproven.$"
