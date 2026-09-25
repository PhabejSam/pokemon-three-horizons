TH_Lab_OnLoad::
    setvar VAR_TEMP_7, 1
    clearflag FLAG_TEMP_3
    clearflag FLAG_TEMP_4
    clearflag FLAG_TEMP_5
    clearflag FLAG_TH_HIDE_ROBIN_LAB
    goto_if_ge VAR_TH_STAGE, TH_STAGE_PARTNER, TH_Lab_HideRobin
    end
TH_Lab_HideRobin:
    setflag FLAG_TH_HIDE_ROBIN_LAB
    end
TH_EventScript_Oak::
    setvar VAR_TEMP_6, 0
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
    closemessage
    fadescreen FADE_TO_BLACK
    special TH_ScriptGiveConfiguredStarter
    waitstate
    goto_if_ne VAR_RESULT, TRUE, TH_Lab_GrantFailed
    playfanfare MUS_OBTAIN_ITEM
    msgbox TH_Text_ReceivedPartner
    waitfanfare
    call TH_Lab_RivalCollectPartner
    call TH_Lab_OakApproach
    goto TH_OakSupplies
TH_Lab_AlreadyChosen:
    msgbox TH_Text_DisplayRemaining
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
    call TH_Lab_OakReturn
    special TH_RefreshFollower
    release
    end
TH_Lab_BagFull:
    msgbox TH_Text_BagFull
    call TH_Lab_OakReturn
    special TH_RefreshFollower
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
    goto_if_le VAR_TH_RIVAL_PARTNER, SPECIES_SQUIRTLE, TH_Lab_PickKanto
    goto_if_le VAR_TH_RIVAL_PARTNER, SPECIES_TOTODILE, TH_Lab_PickJohto
    goto TH_Lab_PickHoenn
TH_Lab_PickKanto:
    applymovement LOCALID_TH_ROBIN_LAB, TH_Movement_RivalPickKanto
    waitmovement 0
    setvar VAR_0x800A, LOCALID_TH_DISPLAY_KANTO
    goto TH_Lab_RivalTakeBall
TH_Lab_PickJohto:
    applymovement LOCALID_TH_ROBIN_LAB, TH_Movement_RivalPickJohto
    waitmovement 0
    setvar VAR_0x800A, LOCALID_TH_DISPLAY_JOHTO
    goto TH_Lab_RivalTakeBall
TH_Lab_PickHoenn:
    applymovement LOCALID_TH_ROBIN_LAB, TH_Movement_RivalPickHoenn
    waitmovement 0
    setvar VAR_0x800A, LOCALID_TH_DISPLAY_HOENN
    goto TH_Lab_RivalTakeBall
TH_Lab_RivalTakeBall:
    delay 20
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

TH_Lab_OakApproach:
    closemessage
    setvar VAR_TEMP_6, 0
    getplayerxy VAR_0x8008, VAR_0x8009
    goto_if_ne VAR_0x8008, 7, TH_OakCheck1
    goto_if_eq VAR_0x8009, 4, TH_OakApproach1
TH_OakCheck1:
    goto_if_ne VAR_0x8008, 8, TH_OakCheck2
    goto_if_eq VAR_0x8009, 3, TH_OakApproach2
TH_OakCheck2:
    goto_if_ne VAR_0x8008, 8, TH_OakCheck3
    goto_if_eq VAR_0x8009, 6, TH_OakApproach3
TH_OakCheck3:
    goto_if_ne VAR_0x8008, 9, TH_OakCheck4
    goto_if_eq VAR_0x8009, 3, TH_OakApproach4
TH_OakCheck4:
    goto_if_ne VAR_0x8008, 9, TH_OakCheck5
    goto_if_eq VAR_0x8009, 6, TH_OakApproach5
TH_OakCheck5:
    goto_if_ne VAR_0x8008, 10, TH_OakCheck6
    goto_if_eq VAR_0x8009, 6, TH_OakApproach6
TH_OakCheck6:
    goto_if_ne VAR_0x8008, 11, TH_OakCheck7
    goto_if_eq VAR_0x8009, 4, TH_OakApproach7
TH_OakCheck7:
    goto_if_ne VAR_0x8008, 10, TH_OakCheck8
    goto_if_eq VAR_0x8009, 3, TH_OakApproach8
TH_OakCheck8:
    return
TH_OakApproach8:
    setvar VAR_TEMP_6, 8
    applymovement LOCALID_TH_OAK, TH_Movement_OakApproach8
    waitmovement 0
    applymovement OBJ_EVENT_ID_PLAYER, TH_Movement_PlayerFaceOak8
    waitmovement 0
    return
TH_OakApproach1:
    setvar VAR_TEMP_6, 1
    applymovement LOCALID_TH_OAK, TH_Movement_OakApproach1
    waitmovement 0
    applymovement OBJ_EVENT_ID_PLAYER, TH_Movement_PlayerFaceOak1
    waitmovement 0
    return
TH_OakApproach2:
    setvar VAR_TEMP_6, 2
    applymovement LOCALID_TH_OAK, TH_Movement_OakApproach2
    waitmovement 0
    applymovement OBJ_EVENT_ID_PLAYER, TH_Movement_PlayerFaceOak2
    waitmovement 0
    return
TH_OakApproach3:
    setvar VAR_TEMP_6, 3
    applymovement LOCALID_TH_OAK, TH_Movement_OakApproach3
    waitmovement 0
    applymovement OBJ_EVENT_ID_PLAYER, TH_Movement_PlayerFaceOak3
    waitmovement 0
    return
TH_OakApproach4:
    setvar VAR_TEMP_6, 4
    applymovement LOCALID_TH_OAK, TH_Movement_OakApproach4
    waitmovement 0
    applymovement OBJ_EVENT_ID_PLAYER, TH_Movement_PlayerFaceOak4
    waitmovement 0
    return
TH_OakApproach5:
    setvar VAR_TEMP_6, 5
    applymovement LOCALID_TH_OAK, TH_Movement_OakApproach5
    waitmovement 0
    applymovement OBJ_EVENT_ID_PLAYER, TH_Movement_PlayerFaceOak5
    waitmovement 0
    return
TH_OakApproach6:
    setvar VAR_TEMP_6, 6
    applymovement LOCALID_TH_OAK, TH_Movement_OakApproach6
    waitmovement 0
    applymovement OBJ_EVENT_ID_PLAYER, TH_Movement_PlayerFaceOak6
    waitmovement 0
    return
TH_OakApproach7:
    setvar VAR_TEMP_6, 7
    applymovement LOCALID_TH_OAK, TH_Movement_OakApproach7
    waitmovement 0
    applymovement OBJ_EVENT_ID_PLAYER, TH_Movement_PlayerFaceOak7
    waitmovement 0
    return
TH_Lab_OakReturn:
    closemessage
    goto_if_eq VAR_TEMP_6, 8, TH_OakReturn8
    goto_if_eq VAR_TEMP_6, 1, TH_OakReturn1
    goto_if_eq VAR_TEMP_6, 2, TH_OakReturn2
    goto_if_eq VAR_TEMP_6, 3, TH_OakReturn3
    goto_if_eq VAR_TEMP_6, 4, TH_OakReturn4
    goto_if_eq VAR_TEMP_6, 5, TH_OakReturn5
    goto_if_eq VAR_TEMP_6, 6, TH_OakReturn6
    goto_if_eq VAR_TEMP_6, 7, TH_OakReturn7
    return
TH_OakReturn1:
    applymovement LOCALID_TH_OAK, TH_Movement_OakReturn1
    goto TH_OakReturnDone
TH_OakReturn2:
    applymovement LOCALID_TH_OAK, TH_Movement_OakReturn2
    goto TH_OakReturnDone
TH_OakReturn3:
    applymovement LOCALID_TH_OAK, TH_Movement_OakReturn3
    goto TH_OakReturnDone
TH_OakReturn4:
    applymovement LOCALID_TH_OAK, TH_Movement_OakReturn4
    goto TH_OakReturnDone
TH_OakReturn5:
    applymovement LOCALID_TH_OAK, TH_Movement_OakReturn5
    goto TH_OakReturnDone
TH_OakReturn6:
    applymovement LOCALID_TH_OAK, TH_Movement_OakReturn6
    goto TH_OakReturnDone
TH_OakReturn7:
    applymovement LOCALID_TH_OAK, TH_Movement_OakReturn7
    goto TH_OakReturnDone
TH_OakReturnDone:
    waitmovement 0
    setvar VAR_TEMP_6, 0
    return
TH_OakReturn8:
    applymovement LOCALID_TH_OAK, TH_Movement_OakReturn8
    goto TH_OakReturnDone
TH_Movement_OakApproach8:
    walk_up
    walk_right
    walk_right
    walk_right
    walk_right
    face_down
    step_end
TH_Movement_OakReturn8:
    walk_left
    walk_left
    walk_left
    walk_left
    walk_down
    face_down
    step_end
TH_Movement_PlayerFaceOak8:
    face_up
    step_end
TH_Movement_OakApproach1:
    walk_down
    face_right
    step_end
TH_Movement_OakReturn1:
    walk_up
    face_down
    step_end
TH_Movement_PlayerFaceOak1:
    face_left
    step_end
TH_Movement_OakApproach2:
    walk_up
    walk_right
    walk_right
    face_down
    step_end
TH_Movement_OakReturn2:
    walk_left
    walk_left
    walk_down
    face_down
    step_end
TH_Movement_PlayerFaceOak2:
    face_up
    step_end
TH_Movement_OakApproach3:
    walk_down
    walk_right
    walk_down
    walk_right
    face_down
    step_end
TH_Movement_OakReturn3:
    walk_left
    walk_up
    walk_left
    walk_up
    face_down
    step_end
TH_Movement_PlayerFaceOak3:
    face_up
    step_end
TH_Movement_OakApproach4:
    walk_up
    walk_right
    walk_right
    walk_right
    face_down
    step_end
TH_Movement_OakReturn4:
    walk_left
    walk_left
    walk_left
    walk_down
    face_down
    step_end
TH_Movement_PlayerFaceOak4:
    face_up
    step_end
TH_Movement_OakApproach5:
    walk_down
    walk_right
    walk_down
    walk_right
    walk_right
    face_down
    step_end
TH_Movement_OakReturn5:
    walk_left
    walk_left
    walk_up
    walk_left
    walk_up
    face_down
    step_end
TH_Movement_PlayerFaceOak5:
    face_up
    step_end
TH_Movement_OakApproach6:
    walk_down
    walk_right
    walk_down
    walk_right
    walk_right
    walk_right
    face_down
    step_end
TH_Movement_OakReturn6:
    walk_left
    walk_left
    walk_left
    walk_up
    walk_left
    walk_up
    face_down
    step_end
TH_Movement_PlayerFaceOak6:
    face_up
    step_end
TH_Movement_OakApproach7:
    walk_up
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    walk_down
    face_down
    step_end
TH_Movement_OakReturn7:
    walk_up
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    walk_down
    face_down
    step_end
TH_Movement_PlayerFaceOak7:
    face_up
    step_end

TH_Text_DisplayRemaining:
    .string "The other partners are resting here.\nOAK will help them find trainers, too.$"

TH_Lab_Computer::
    msgbox TH_Text_LabComputer, MSGBOX_SIGN
    end
TH_Text_LabComputer:
    .string "The screen compares POKéMON seen\nin KANTO, JOHTO, and HOENN.$"

TH_Lab_Certificate::
    msgbox TH_Text_LabCertificate, MSGBOX_SIGN
    end
TH_Text_LabCertificate:
    .string "Research awards line the wall.\nOne has a muddy footprint on it!$"

TH_Lab_Books9::
    msgbox TH_Text_LabBooks9, MSGBOX_SIGN
    end
TH_Text_LabBooks9:
    .string "ELM's notes describe how POKéMON\ncare for their Eggs.$"

TH_Lab_Books10::
    msgbox TH_Text_LabBooks10, MSGBOX_SIGN
    end
TH_Text_LabBooks10:
    .string "A field guide to KANTO's habitats.\nThe forest pages are well worn.$"

TH_Lab_Books11::
    msgbox TH_Text_LabBooks11, MSGBOX_SIGN
    end
TH_Text_LabBooks11:
    .string "BIRCH's journal is full of sketches.\nGrass stains cover the margins.$"

TH_Lab_Books12::
    msgbox TH_Text_LabBooks12, MSGBOX_SIGN
    end
TH_Text_LabBooks12:
    .string "Three bookmarks mark three regions.\nThere is still so much to discover.$"

TH_Lab_FirstEntryTable:
    map_script_2 VAR_TEMP_7, 1, TH_Lab_FirstEntry
    .2byte 0
TH_Lab_FirstEntry::
    setvar VAR_TEMP_7, 0
    goto_if_set FLAG_TH_LAB_INTRO, TH_Lab_EntryDone
    goto_if_ge VAR_TH_STAGE, TH_STAGE_PARTNER, TH_Lab_EntryDone
    lockall
    hidefollower TRUE
    applymovement OBJ_EVENT_ID_PLAYER, TH_Lab_IntroApproach
    waitmovement 0
    msgbox TH_Text_JointResearch
    msgbox TH_Text_ElmWelcome
    msgbox TH_Text_BirchWelcome
    msgbox TH_Text_RivalLetsPlayerChoose
    setflag FLAG_TH_LAB_INTRO
    setvar VAR_TEMP_2, 1
    setvar VAR_TH_STAGE, TH_STAGE_INVITED
    releaseall
TH_Lab_EntryDone:
    end
TH_Lab_IntroApproach:
    walk_up
    walk_up
    walk_up
    walk_up
    walk_up
    walk_up
    walk_up
    walk_left
    face_up
    step_end
TH_Text_JointResearch:
    .string "OAK: Welcome, {PLAYER}!\nWe have something to show you.\pPOKéMON from JOHTO and HOENN have\nbeen appearing here in KANTO.\pELM, BIRCH and I are studying how\nthese habitats are changing.$"
TH_Text_ElmWelcome:
    .string "ELM: A partner can help us discover\nwhat brings these POKéMON together.$"
TH_Text_BirchWelcome:
    .string "BIRCH: Take your time. See who\nyou would like by your side!$"
TH_Text_RivalLetsPlayerChoose:
    .string "{RIVAL}: I'll choose first!\nHmm... Actually, this is tough.\pYou go ahead, {PLAYER}.\nI want to meet them all first!$"
