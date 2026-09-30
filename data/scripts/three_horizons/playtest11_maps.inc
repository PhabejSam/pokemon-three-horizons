@ Luis swims up to the pool edge. Both his starting and final squares are water;
@ the single-file walkway at x=9 stays clear before and after the battle.
TH_GymLuis_Approach::
    goto_if_defeated TRAINER_TH9_SWIMMER_MALE_LUIS, TH_Playtest11_MapEnd
    lockall
    applymovement LOCALID_TH_CERULEANGYM_0, Common_Movement_ExclamationMark
    waitmovement 0
    waitfieldeffect FLDEFF_EXCLAMATION_MARK_ICON
    applymovement OBJ_EVENT_ID_PLAYER, TH_Playtest11_FaceRight
    applymovement LOCALID_TH_CERULEANGYM_0, TH_GymLuis_SwimLeft
    waitmovement 0
    setvar VAR_LAST_TALKED, LOCALID_TH_CERULEANGYM_0
    goto TH_GymLuis_Battle
TH_GymLuis_Talk::
    vsseeker_rematchid TRAINER_TH9_SWIMMER_MALE_LUIS
    lockall
    faceplayer
    setvar VAR_0x8004, TRAINER_TH9_SWIMMER_MALE_LUIS
    callnative TH13_ScriptCheckRematch
    goto_if_eq VAR_RESULT, TRUE, TH_GymLuis_Rematch
    goto_if_defeated TRAINER_TH9_SWIMMER_MALE_LUIS, TH_GymLuis_After
TH_GymLuis_Battle:
    trainerbattle_lavaridge LOCALID_TH_CERULEANGYM_0, TRAINER_TH9_SWIMMER_MALE_LUIS, TH_Trainer9_SWIMMER_MALE_LUIS_Intro, TH_Trainer9_SWIMMER_MALE_LUIS_Defeat, TH_GymLuis_After
    end
TH_GymLuis_After:
    setobjectxyperm LOCALID_TH_CERULEANGYM_0, 10, 12
    msgbox TH_Trainer9_SWIMMER_MALE_LUIS_After, MSGBOX_DEFAULT
    releaseall
    end
TH_GymLuis_SwimLeft:
    walk_left
    step_end
TH_GymLuis_Rematch::
    trainerbattle_rematch TRAINER_TH9_SWIMMER_MALE_LUIS, TH_Trainer9_SWIMMER_MALE_LUIS_Intro, TH_Trainer9_SWIMMER_MALE_LUIS_Defeat
    msgbox TH_Trainer9_SWIMMER_MALE_LUIS_After, MSGBOX_DEFAULT
    releaseall
    end
TH_Playtest11_FaceRight:
    face_right
    step_end
TH_Playtest11_MapEnd:
    end

@ Keep the original door warp slot so saves already inside can leave safely.
TH_ViridianGym_ClosedEntrance::
    lockall
    msgbox TH_ViridianGym_Locked_Text, MSGBOX_DEFAULT
    closemessage
    applymovement OBJ_EVENT_ID_PLAYER, TH_Playtest11_StepLeft
    waitmovement 0
    releaseall
    end
TH_Playtest11_StepLeft:
    walk_left
    step_end

TH_MuseumWelcome::
    setvar VAR_TEMP_1, 1
    goto_if_set FLAG_TH12_MUSEUM_VISIT, TH_Playtest11_MapEnd
    setflag FLAG_TH12_MUSEUM_VISIT
    lockall
    applymovement OBJ_EVENT_ID_PLAYER, TH_Playtest11_FaceRight
    waitmovement 0
    msgbox TH_Local_PewterMuseum1F_0_Text, MSGBOX_DEFAULT
    releaseall
    end

TH_PewterBadgeGuide::
    lock
    faceplayer
    goto_if_set FLAG_BADGE01_GET, TH_PewterBadgeGuide_Open
    msgbox TH_Route3BadgeGate_Text
    release
    end
TH_PewterBadgeGuide_Open:
    msgbox TH_PewterBadgeGuide_OpenText
    release
    end
TH_PewterBadgeGuide_OpenText:
    .string "That BOULDERBADGE shows you're ready!\nROUTE 3 leads east toward MT. MOON.$"
