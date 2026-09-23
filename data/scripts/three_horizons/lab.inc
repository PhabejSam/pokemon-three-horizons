TH_Lab_OnLoad::
    clearflag FLAG_TH_HIDE_ROBIN_LAB
    goto_if_ge VAR_TH_STAGE, TH_STAGE_PARTNER, TH_Lab_HideRobin
    end
TH_Lab_HideRobin:
    setflag FLAG_TH_HIDE_ROBIN_LAB
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
    bufferspeciesname STR_VAR_1, VAR_0x8004
    msgbox TH_Text_ConfirmPartner, MSGBOX_YESNO
    goto_if_ne VAR_RESULT, YES, TH_Lab_Cancel
    special TH_ScriptGiveStarter
    goto_if_ne VAR_RESULT, TRUE, TH_Lab_GrantFailed
    playfanfare MUS_OBTAIN_ITEM
    msgbox TH_Text_ReceivedPartner
    waitfanfare
    bufferspeciesname STR_VAR_1, VAR_TH_RIVAL_PARTNER
    msgbox TH_Text_RobinChoice
    removeobject LOCALID_TH_ROBIN_LAB
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
