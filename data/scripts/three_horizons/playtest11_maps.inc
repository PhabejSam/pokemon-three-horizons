@ Luis swims up to the pool edge. Both his starting and final squares are water;
@ the single-file walkway at x=9 stays clear before and after the battle.
TH_GymLuis_Approach::
    goto_if_defeated TRAINER_TH9_SWIMMER_MALE_LUIS, TH_Playtest11_MapEnd
    lockall
    applymovement OBJ_EVENT_ID_PLAYER, TH_Playtest11_FaceRight
    applymovement LOCALID_TH_CERULEANGYM_0, TH_GymLuis_SwimLeft
    waitmovement 0
    setvar VAR_LAST_TALKED, LOCALID_TH_CERULEANGYM_0
    goto TH_GymLuis_Battle
TH_GymLuis_Talk::
    lockall
    faceplayer
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
    lockall
    applymovement OBJ_EVENT_ID_PLAYER, TH_Playtest11_FaceRight
    waitmovement 0
    msgbox TH_Local_PewterMuseum1F_0_Text, MSGBOX_DEFAULT
    setvar VAR_TEMP_1, 1
    releaseall
    end
