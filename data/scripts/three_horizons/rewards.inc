TH_BrockCaretaker::
    lock
    faceplayer
    goto_if_ne VAR_TH_BROCK_GIFT, 0, TH_CaretakerThanks
    goto_if_unset FLAG_BADGE01_GET, TH_BrockCaretakerWait
    msgbox TH_Text_BrockCaretaker
    setvar VAR_0x8006, 0
    special TH_ScriptRewardChoices
    bufferspeciesname STR_VAR_1, VAR_0x8007
    bufferspeciesname STR_VAR_2, VAR_0x8008
    dynmultichoice 0, 0, FALSE, 2, 0, DYN_MULTICHOICE_CB_NONE, TH_RewardFirst, TH_RewardSecond
    goto_if_eq VAR_RESULT, MULTI_B_PRESSED, TH_RewardExit
    goto_if_eq VAR_RESULT, 0, TH_BrockFirstChoice
    copyvar VAR_0x8004, VAR_0x8008
    goto TH_RewardCustomize
TH_BrockFirstChoice:
    copyvar VAR_0x8004, VAR_0x8007
    goto TH_RewardCustomize
TH_BrockCaretakerWait:
    msgbox TH_Text_BrockWait
    release
    end
TH_MistyCaretaker::
    lock
    faceplayer
    goto_if_ne VAR_TH_MISTY_GIFT, 0, TH_CaretakerThanks
    goto_if_unset FLAG_BADGE02_GET, TH_MistyCaretakerWait
    goto_if_eq VAR_TH_BROCK_GIFT, 0, TH_MistyNeedsBrockGift
    setvar VAR_0x8006, 1
    special TH_ScriptRewardChoices
    bufferspeciesname STR_VAR_1, VAR_0x8007
    msgbox TH_Text_MistyCaretaker, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, TH_RewardExit
    copyvar VAR_0x8004, VAR_0x8007
TH_RewardCustomize:
    closemessage
    special TH_OpenRewardEditor
    waitstate
    goto_if_eq VAR_RESULT, FALSE, TH_RewardExit
    closemessage
    fadescreen FADE_TO_BLACK
    special TH_ScriptGiveReward
    waitstate
    goto_if_eq VAR_RESULT, FALSE, TH_RewardNoSpace
    special TH_RefreshFollower
    call TH_ReportRewardDestination
TH_RewardExit:
    release
    end
TH_RewardNoSpace:
    msgbox TH_Text_RewardNoSpace
    release
    end
TH_CaretakerThanks:
    msgbox TH_Text_CaretakerThanks
    release
    end
TH_MistyCaretakerWait:
    msgbox TH_Text_MistyWait
    release
    end
TH_MistyNeedsBrockGift:
    msgbox TH_Text_MistyNeedsBrock
    release
    end
TH_MagikarpSalesman::
    lock
    faceplayer
    goto_if_set FLAG_TH_MAGIKARP, TH_CaretakerThanks
    msgbox TH_Text_MagikarpOffer, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, TH_RewardExit
    checkmoney 500
    goto_if_eq VAR_RESULT, FALSE, TH_MagikarpNoMoney
    closemessage
    fadescreen FADE_TO_BLACK
    special TH_ScriptBuyMagikarp
    waitstate
    goto_if_eq VAR_RESULT, FALSE, TH_RewardNoSpace
    special TH_RefreshFollower
    call TH_ReportRewardDestination
    msgbox TH_Text_MagikarpDelivered
    release
    end
TH_MagikarpNoMoney:
    msgbox TH_Text_MagikarpNoMoney
    release
    end
TH_ReportRewardDestination:
    goto_if_eq VAR_0x8009, MON_GIVEN_TO_PC, TH_ReportRewardPC
    msgbox TH_Text_RewardDelivered
    return
TH_ReportRewardPC:
    msgbox TH_Text_RewardPC
    return
TH_Text_RewardPC:
    .string "Your party is full. Your new\npartner was sent to your PC.$"
TH_RewardFirst:
    .string "{STR_VAR_1}$"
TH_RewardSecond:
    .string "{STR_VAR_2}$"
TH_Text_BrockCaretaker:
    .string "Two TRAINERS left their partners\nwith me after struggling with BROCK.\pThese POKéMON deserve another chance.\nYou earned a badge. Will you give\lone a patient, caring home?$"
TH_Text_BrockWait:
    .string "I care for partners whose TRAINERS\ncould not continue their journeys.\pEarn BROCK's badge, then visit again.\nOne of these POKéMON may join you.$"
TH_Text_MistyCaretaker:
    .string "{STR_VAR_1}'s TRAINER left it with me\nafter giving up on the GYM challenge.\pIt still perks up whenever a\nTRAINER comes by. Would you give\lit a fresh start?$"
TH_Text_MistyWait:
    .string "A TRAINER left their partner with\nme when their journey ended here.\pIt deserves someone who will stay\nby its side. Visit after you earn\lMISTY's badge.$"
TH_Text_MistyNeedsBrock:
    .string "First, visit the caretaker outside\nPEWTER GYM and choose a partner.\pThen I can introduce you to one\nfrom the remaining region.$"
TH_Text_RewardDelivered:
    .string "Your new partner joined your party!\nLook after each other out there.$"
TH_Text_RewardNoSpace:
    .string "Your party and PC have no room.\nMake space and visit me again.\lYour reward is still waiting.$"
TH_Text_CaretakerThanks:
    .string "How is your new partner settling in?\nI hope your journey brings you closer.$"
TH_Text_MagikarpOffer:
    .string "Look, young TRAINER! I have a deal.\nThis MAGIKARP is a special golden color!\pStrong potential, trained for Attack\nand Speed, and an Adamant nature.\pJust ¥500 for this Lv. 5 partner.\nInterested?$"
TH_Text_MagikarpNoMoney:
    .string "You need ¥500 for this deal.\nCome back when you have enough.$"
TH_Text_MagikarpDelivered:
    .string "A deal is a deal!\nYour golden MAGIKARP is ready.\pTrain it well. There is more to\nthis POKéMON than meets the eye!$"
