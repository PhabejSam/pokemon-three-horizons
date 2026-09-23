TH_EventScript_Ending::
    lockall
    goto_if_eq VAR_TH_STAGE, TH_STAGE_COMPLETE, TH_EndingRepeat
    goto_if_ne VAR_TH_STAGE, TH_STAGE_BATTLE_DONE, TH_EndingRelease
    msgbox TH_Text_Ending
    setvar VAR_TH_STAGE, TH_STAGE_COMPLETE
    msgbox TH_Text_DemoComplete
    goto TH_EndingRelease
TH_EndingRepeat:
    msgbox TH_Text_EndingRepeat
TH_EndingRelease:
    releaseall
    end
TH_EventScript_DemoBoundary::
    lockall
    msgbox TH_Text_Boundary
    applymovement OBJ_EVENT_ID_PLAYER, TH_Movement_StepSouth
    waitmovement 0
    releaseall
    end
