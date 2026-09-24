TH_Lab_OnLoad::
    clearflag FLAG_TEMP_3
    clearflag FLAG_TEMP_4
    clearflag FLAG_TEMP_5
    clearflag FLAG_TH_HIDE_ROBIN_LAB
    goto_if_ge VAR_TH_STAGE, TH_STAGE_PARTNER, TH_Lab_HideRobin
    end
TH_Lab_HideRobin:
    setflag FLAG_TH_HIDE_ROBIN_LAB
    goto_if_le VAR_TH_FIRST_PARTNER, SPECIES_SQUIRTLE, TH_Lab_HideKantoBall
    goto_if_le VAR_TH_FIRST_PARTNER, SPECIES_TOTODILE, TH_Lab_HideJohtoBall
    setflag FLAG_TEMP_5
    end
TH_Lab_HideKantoBall:
    setflag FLAG_TEMP_3
    end
TH_Lab_HideJohtoBall:
    setflag FLAG_TEMP_4
    end
TH_EventScript_Oak::
    lock
    faceplayer
    goto_if_ge VAR_TH_STAGE, TH_STAGE_PARTNER, TH_OakSupplies
    call TH_Lab_Explain
    msgbox TH_Text_ChooseDisplay
    release
    end
TH_Lab_Explain:
    goto_if_eq VAR_TEMP_2, 1, TH_Lab_Explained
    msgbox TH_Text_OakResearch
    setvar VAR_TEMP_2, 1
    goto_if_ne VAR_TH_STAGE, TH_STAGE_HOME, TH_Lab_Explained
    setvar VAR_TH_STAGE, TH_STAGE_INVITED
TH_Lab_Explained:
    return
TH_EventScript_RobinLab::
    msgbox TH_Text_RobinThinking, MSGBOX_NPC
    end
TH_Lab_KantoMenu::
    lock
    faceplayer
    goto_if_ge VAR_TH_STAGE, TH_STAGE_PARTNER, TH_Lab_AlreadyChosen
    call TH_Lab_Explain
    msgbox TH_Text_KantoDisplay
    dynmultichoice 0, 0, FALSE, 3, 0, DYN_MULTICHOICE_CB_NONE, TH_Text_Bulbasaur, TH_Text_Charmander, TH_Text_Squirtle
    goto_if_eq VAR_RESULT, MULTI_B_PRESSED, TH_Lab_Cancel
    goto_if_eq VAR_RESULT, 0, TH_Lab_SelectBulbasaur
    goto_if_eq VAR_RESULT, 1, TH_Lab_SelectCharmander
    goto_if_eq VAR_RESULT, 2, TH_Lab_SelectSquirtle
    goto TH_Lab_Cancel
TH_Lab_SelectBulbasaur:
    setvar VAR_0x8004, SPECIES_BULBASAUR
    goto TH_Lab_Confirm
TH_Lab_SelectCharmander:
    setvar VAR_0x8004, SPECIES_CHARMANDER
    goto TH_Lab_Confirm
TH_Lab_SelectSquirtle:
    setvar VAR_0x8004, SPECIES_SQUIRTLE
    goto TH_Lab_Confirm
TH_Lab_JohtoMenu::
    lock
    faceplayer
    goto_if_ge VAR_TH_STAGE, TH_STAGE_PARTNER, TH_Lab_AlreadyChosen
    call TH_Lab_Explain
    msgbox TH_Text_JohtoDisplay
    dynmultichoice 0, 0, FALSE, 3, 0, DYN_MULTICHOICE_CB_NONE, TH_Text_Chikorita, TH_Text_Cyndaquil, TH_Text_Totodile
    goto_if_eq VAR_RESULT, MULTI_B_PRESSED, TH_Lab_Cancel
    goto_if_eq VAR_RESULT, 0, TH_Lab_SelectChikorita
    goto_if_eq VAR_RESULT, 1, TH_Lab_SelectCyndaquil
    goto_if_eq VAR_RESULT, 2, TH_Lab_SelectTotodile
    goto TH_Lab_Cancel
TH_Lab_SelectChikorita:
    setvar VAR_0x8004, SPECIES_CHIKORITA
    goto TH_Lab_Confirm
TH_Lab_SelectCyndaquil:
    setvar VAR_0x8004, SPECIES_CYNDAQUIL
    goto TH_Lab_Confirm
TH_Lab_SelectTotodile:
    setvar VAR_0x8004, SPECIES_TOTODILE
    goto TH_Lab_Confirm
TH_Lab_HoennMenu::
    lock
    faceplayer
    goto_if_ge VAR_TH_STAGE, TH_STAGE_PARTNER, TH_Lab_AlreadyChosen
    call TH_Lab_Explain
    msgbox TH_Text_HoennDisplay
    dynmultichoice 0, 0, FALSE, 3, 0, DYN_MULTICHOICE_CB_NONE, TH_Text_Treecko, TH_Text_Torchic, TH_Text_Mudkip
    goto_if_eq VAR_RESULT, MULTI_B_PRESSED, TH_Lab_Cancel
    goto_if_eq VAR_RESULT, 0, TH_Lab_SelectTreecko
    goto_if_eq VAR_RESULT, 1, TH_Lab_SelectTorchic
    goto_if_eq VAR_RESULT, 2, TH_Lab_SelectMudkip
    goto TH_Lab_Cancel
TH_Lab_SelectTreecko:
    setvar VAR_0x8004, SPECIES_TREECKO
    goto TH_Lab_Confirm
TH_Lab_SelectTorchic:
    setvar VAR_0x8004, SPECIES_TORCHIC
    goto TH_Lab_Confirm
TH_Lab_SelectMudkip:
    setvar VAR_0x8004, SPECIES_MUDKIP
    goto TH_Lab_Confirm
TH_Lab_Confirm:
    closemessage
    special TH_OpenPartnerEditor
    waitstate
    goto_if_ne VAR_RESULT, TRUE, TH_Lab_Cancel
    bufferspeciesname STR_VAR_1, VAR_0x8004
    msgbox TH_Text_ConfirmPartner, MSGBOX_YESNO
    goto_if_ne VAR_RESULT, YES, TH_Lab_Cancel
    special TH_ScriptGiveConfiguredStarter
    goto_if_ne VAR_RESULT, TRUE, TH_Lab_GrantFailed
    playfanfare MUS_OBTAIN_ITEM
    msgbox TH_Text_ReceivedPartner
    waitfanfare
    call TH_Lab_RivalCollectPartner
    goto TH_OakSupplies
TH_Lab_AlreadyChosen:
    msgbox TH_Text_AlreadyChosen
    release
    end
TH_Lab_GrantFailed:
    msgbox TH_Text_GrantFailed
    release
    end
TH_Lab_Cancel:
    release
    end
TH_OakSupplies:
    goto_if_eq VAR_TH_SUPPLY_MASK, TH_SUPPLIES_COMPLETE, TH_OakAfterSupplies
    special TH_ScriptGiveSupplies
    goto_if_ne VAR_RESULT, TRUE, TH_Lab_BagFull
    msgbox TH_Text_Supplies
TH_OakAfterSupplies:
    msgbox TH_Text_OakSendoff
    release
    end
TH_Lab_BagFull:
    msgbox TH_Text_BagFull
    release
    end

TH_EventScript_Aide1::
    msgbox TH_Text_Aide1, MSGBOX_NPC
    end
TH_EventScript_Aide2::
    msgbox TH_Text_Aide2, MSGBOX_NPC
    end

@ The player selected from this regional display. Clear its south approach
@ before the rival walks over; his partner remains the species stored at grant.
TH_Lab_RivalCollectPartner:
    lockall
    hidefollower TRUE
    closemessage
    getplayerxy VAR_0x8008, VAR_0x8009
    goto_if_ne VAR_0x8009, 5, TH_Lab_RivalApproach
    applymovement OBJ_EVENT_ID_PLAYER, TH_Movement_PlayerMakeRoom
    waitmovement 0
TH_Lab_RivalApproach:
    goto_if_le VAR_TH_FIRST_PARTNER, SPECIES_SQUIRTLE, TH_Lab_PickKanto
    goto_if_le VAR_TH_FIRST_PARTNER, SPECIES_TOTODILE, TH_Lab_PickJohto
    goto TH_Lab_PickHoenn
TH_Lab_PickKanto:
    applymovement LOCALID_TH_ROBIN_LAB, TH_Movement_RivalPickKanto
    waitmovement 0
    setvar VAR_0x800A, LOCALID_TH_DISPLAY_KANTO
    setflag FLAG_TEMP_3
    goto TH_Lab_RivalTakeBall
TH_Lab_PickJohto:
    applymovement LOCALID_TH_ROBIN_LAB, TH_Movement_RivalPickJohto
    waitmovement 0
    setvar VAR_0x800A, LOCALID_TH_DISPLAY_JOHTO
    setflag FLAG_TEMP_4
    goto TH_Lab_RivalTakeBall
TH_Lab_PickHoenn:
    applymovement LOCALID_TH_ROBIN_LAB, TH_Movement_RivalPickHoenn
    waitmovement 0
    setvar VAR_0x800A, LOCALID_TH_DISPLAY_HOENN
    setflag FLAG_TEMP_5
    goto TH_Lab_RivalTakeBall
TH_Lab_RivalTakeBall:
    delay 20
    removeobject VAR_0x800A
    playfanfare MUS_OBTAIN_ITEM
    waitfanfare
    playmoncry VAR_TH_RIVAL_PARTNER, CRY_MODE_NORMAL
    waitmoncry
    bufferspeciesname STR_VAR_1, VAR_TH_RIVAL_PARTNER
    msgbox TH_Text_RobinChoice
    closemessage
    goto_if_eq VAR_0x800A, LOCALID_TH_DISPLAY_KANTO, TH_Lab_LeaveKanto
    goto_if_eq VAR_0x800A, LOCALID_TH_DISPLAY_JOHTO, TH_Lab_LeaveJohto
    applymovement LOCALID_TH_ROBIN_LAB, TH_Movement_RivalLeaveHoenn
    goto TH_Lab_RivalDepart
TH_Lab_LeaveKanto:
    applymovement LOCALID_TH_ROBIN_LAB, TH_Movement_RivalLeaveKanto
    goto TH_Lab_RivalDepart
TH_Lab_LeaveJohto:
    applymovement LOCALID_TH_ROBIN_LAB, TH_Movement_RivalLeaveJohto
TH_Lab_RivalDepart:
    waitmovement 0
    removeobject LOCALID_TH_ROBIN_LAB
    return
TH_Movement_PlayerMakeRoom:
    walk_down
    face_up
    step_end
TH_Movement_RivalPickKanto:
    walk_right
    walk_right
    walk_right
    walk_right
    face_up
    step_end
TH_Movement_RivalLeaveKanto:
    walk_left
    walk_left
    walk_down
    walk_down
    walk_down
    walk_down
    walk_down
    walk_down
    walk_down
    step_end
TH_Movement_RivalPickJohto:
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    face_up
    step_end
TH_Movement_RivalLeaveJohto:
    walk_left
    walk_left
    walk_left
    walk_down
    walk_down
    walk_down
    walk_down
    walk_down
    walk_down
    walk_down
    step_end
TH_Movement_RivalPickHoenn:
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    face_up
    step_end
TH_Movement_RivalLeaveHoenn:
    walk_left
    walk_left
    walk_left
    walk_left
    walk_down
    walk_down
    walk_down
    walk_down
    walk_down
    walk_down
    walk_down
    step_end

TH_Lab_Elm::
    msgbox TH_Text_Elm, MSGBOX_NPC
    end
TH_Lab_Birch::
    msgbox TH_Text_Birch, MSGBOX_NPC
    end
TH_Text_Elm:
    .string "ELM: Every partnership begins with\ntrust. Take good care of each other!$"
TH_Text_Birch:
    .string "BIRCH: There's so much to discover\nwhen you step outside together!$"
