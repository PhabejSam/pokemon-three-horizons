TH_Pallet_OnTransition::
    setvar VAR_TEMP_3, 1
    goto TH_Pallet_OnLoad
TH_Pallet_OnLoad::
    clearflag FLAG_TH_HIDE_ROBIN_TOWN
    goto_if_eq VAR_TH_STAGE, TH_STAGE_INVITED, TH_Pallet_HideRobin
    goto_if_ge VAR_TH_STAGE, TH_STAGE_BATTLE_DONE, TH_Pallet_HideRobin
    goto_if_ge VAR_TH_STAGE, TH_STAGE_PARTNER, TH_Pallet_BattlePosition
    setobjectxyperm LOCALID_TH_ROBIN_TOWN, 7, 9
    end
TH_Pallet_HideRobin:
    setflag FLAG_TH_HIDE_ROBIN_TOWN
    end
TH_Pallet_BattlePosition:
    setobjectxyperm LOCALID_TH_ROBIN_TOWN, 17, 14
    end

@ Door exit movement does not generate an ordinary coordinate-step event.
@ Check once after field input resumes; clear before dispatch so other positions
@ and already-completed stages never repeatedly seize player control.
TH_Pallet_OnFrame:
    map_script_2 VAR_TEMP_3, 1, TH_Pallet_CheckDoorScene
    .2byte 0
TH_Pallet_CheckDoorScene::
    setvar VAR_TEMP_3, 0
    getplayerxy VAR_0x8008, VAR_0x8009
    goto_if_eq VAR_TH_STAGE, TH_STAGE_HOME, TH_Pallet_CheckHomeDoor
    goto_if_eq VAR_TH_STAGE, TH_STAGE_PARTNER, TH_Pallet_CheckLabDoor
    end
TH_Pallet_CheckHomeDoor:
    goto_if_ne VAR_0x8008, 6, TH_Pallet_NoDoorScene
    goto_if_eq VAR_0x8009, 8, TH_AutoInvitation
    end
TH_Pallet_CheckLabDoor:
    goto_if_ne VAR_0x8008, 16, TH_Pallet_NoDoorScene
    goto_if_eq VAR_0x8009, 14, TH_AutoFirstBattle
TH_Pallet_NoDoorScene:
    end
TH_AutoInvitation:
    lockall
    hidefollower TRUE
    applymovement LOCALID_TH_ROBIN_TOWN, TH_Movement_RivalGreet
    waitmovement 0
    applymovement OBJ_EVENT_ID_PLAYER, TH_Movement_PlayerFaceRival
    waitmovement 0
    msgbox TH_Text_RobinMorning
    closemessage
    applymovement LOCALID_TH_ROBIN_TOWN, TH_Movement_StepSouth
    waitmovement 0
    goto TH_InvitationLeave
TH_AutoFirstBattle:
    lockall
    hidefollower TRUE
    applymovement LOCALID_TH_ROBIN_TOWN, TH_Movement_RivalFacePlayer
    waitmovement 0
    applymovement OBJ_EVENT_ID_PLAYER, TH_Movement_PlayerFaceRival
    waitmovement 0
    goto TH_EventScript_FirstBattle
TH_Movement_RivalGreet:
    walk_up
    face_left
    step_end
TH_Movement_PlayerFaceRival:
    face_right
    step_end
TH_Movement_RivalFacePlayer:
    face_left
    step_end

TH_EventScript_RobinTown::
    goto_if_eq VAR_TH_STAGE, TH_STAGE_HOME, TH_EventScript_Invitation
    goto_if_eq VAR_TH_STAGE, TH_STAGE_PARTNER, TH_EventScript_FirstBattle
    msgbox TH_Text_RobinGoLab, MSGBOX_NPC
    end
TH_EventScript_Invitation::
    lockall
    goto_if_ne VAR_TH_STAGE, TH_STAGE_HOME, TH_BattleRelease
    msgbox TH_Text_RobinMorning
    closemessage
TH_InvitationLeave:
    getplayerxy VAR_0x8008, VAR_0x8009
    goto_if_eq VAR_0x8008, 8, TH_InvitationStepAround
    applymovement LOCALID_TH_ROBIN_TOWN, TH_Movement_RobinToLab
    goto TH_InvitationDepart
TH_InvitationStepAround:
    applymovement LOCALID_TH_ROBIN_TOWN, TH_Movement_JoeyAroundPlayer
TH_InvitationDepart:
    waitmovement 0
    setvar VAR_TH_STAGE, TH_STAGE_INVITED
    removeobject LOCALID_TH_ROBIN_TOWN
    releaseall
    end
TH_Movement_RobinToLab:
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    walk_down
    walk_down
    walk_down
    walk_down
    walk_down
    walk_right
    walk_right
    walk_right
    walk_right
    walk_up
    step_end

TH_EventScript_RouteGate::
    lockall
    goto_if_lt VAR_TH_STAGE, TH_STAGE_PARTNER, TH_GateLab
    goto_if_lt VAR_TH_STAGE, TH_STAGE_BATTLE_DONE, TH_GateBattle
    goto_if_ne VAR_TH_SUPPLY_MASK, TH_SUPPLIES_COMPLETE, TH_GateSupplies
    releaseall
    end
TH_GateLab:
    msgbox TH_Text_GateLab
    goto TH_GateStepBack
TH_GateBattle:
    msgbox TH_Text_GateBattle
    goto TH_GateStepBack
TH_GateSupplies:
    msgbox TH_Text_GateSupplies
TH_GateStepBack:
    applymovement OBJ_EVENT_ID_PLAYER, TH_Movement_StepSouth
    waitmovement 0
    releaseall
    end
TH_Movement_StepSouth:
    walk_down
    step_end

TH_EventScript_ClosedDoor::
    msgbox TH_Text_ClosedDoor, MSGBOX_SIGN
    end
TH_EventScript_LabSign::
    msgbox TH_Text_LabSign, MSGBOX_SIGN
    end
TH_EventScript_TownSign::
    msgbox TH_Text_TownSign, MSGBOX_SIGN
    end
TH_EventScript_TrainerTips::
    msgbox TH_Text_TrainerTips, MSGBOX_SIGN
    end
TH_EventScript_HomeSign::
    msgbox TH_Text_HomeSign, MSGBOX_SIGN
    end
TH_EventScript_JoeySign::
    msgbox TH_Text_JoeySign, MSGBOX_SIGN
    end

TH_EventScript_FirstBattle::
    lockall
    goto_if_ne VAR_TH_STAGE, TH_STAGE_PARTNER, TH_BattleRelease
    msgbox TH_Text_BeforeBattle
    goto_if_eq VAR_TH_RIVAL_PARTNER, SPECIES_BULBASAUR, TH_BattleBulbasaur
    goto_if_eq VAR_TH_RIVAL_PARTNER, SPECIES_CHARMANDER, TH_BattleCharmander
    goto_if_eq VAR_TH_RIVAL_PARTNER, SPECIES_SQUIRTLE, TH_BattleSquirtle
    goto_if_eq VAR_TH_RIVAL_PARTNER, SPECIES_CHIKORITA, TH_BattleChikorita
    goto_if_eq VAR_TH_RIVAL_PARTNER, SPECIES_CYNDAQUIL, TH_BattleCyndaquil
    goto_if_eq VAR_TH_RIVAL_PARTNER, SPECIES_TOTODILE, TH_BattleTotodile
    goto_if_eq VAR_TH_RIVAL_PARTNER, SPECIES_TREECKO, TH_BattleTreecko
    goto_if_eq VAR_TH_RIVAL_PARTNER, SPECIES_TORCHIC, TH_BattleTorchic
    goto_if_eq VAR_TH_RIVAL_PARTNER, SPECIES_MUDKIP, TH_BattleMudkip
    goto TH_BattleRelease
TH_BattleBulbasaur:
    trainerbattle_earlyrival TRAINER_TH_ROBIN_BULBASAUR, RIVAL_BATTLE_HEAL_AFTER, TH_Text_BattlePlayerLost, TH_Text_BattlePlayerWon
    goto TH_BattleFinished
TH_BattleCharmander:
    trainerbattle_earlyrival TRAINER_TH_ROBIN_CHARMANDER, RIVAL_BATTLE_HEAL_AFTER, TH_Text_BattlePlayerLost, TH_Text_BattlePlayerWon
    goto TH_BattleFinished
TH_BattleSquirtle:
    trainerbattle_earlyrival TRAINER_TH_ROBIN_SQUIRTLE, RIVAL_BATTLE_HEAL_AFTER, TH_Text_BattlePlayerLost, TH_Text_BattlePlayerWon
    goto TH_BattleFinished
TH_BattleChikorita:
    trainerbattle_earlyrival TRAINER_TH_ROBIN_CHIKORITA, RIVAL_BATTLE_HEAL_AFTER, TH_Text_BattlePlayerLost, TH_Text_BattlePlayerWon
    goto TH_BattleFinished
TH_BattleCyndaquil:
    trainerbattle_earlyrival TRAINER_TH_ROBIN_CYNDAQUIL, RIVAL_BATTLE_HEAL_AFTER, TH_Text_BattlePlayerLost, TH_Text_BattlePlayerWon
    goto TH_BattleFinished
TH_BattleTotodile:
    trainerbattle_earlyrival TRAINER_TH_ROBIN_TOTODILE, RIVAL_BATTLE_HEAL_AFTER, TH_Text_BattlePlayerLost, TH_Text_BattlePlayerWon
    goto TH_BattleFinished
TH_BattleTreecko:
    trainerbattle_earlyrival TRAINER_TH_ROBIN_TREECKO, RIVAL_BATTLE_HEAL_AFTER, TH_Text_BattlePlayerLost, TH_Text_BattlePlayerWon
    goto TH_BattleFinished
TH_BattleTorchic:
    trainerbattle_earlyrival TRAINER_TH_ROBIN_TORCHIC, RIVAL_BATTLE_HEAL_AFTER, TH_Text_BattlePlayerLost, TH_Text_BattlePlayerWon
    goto TH_BattleFinished
TH_BattleMudkip:
    trainerbattle_earlyrival TRAINER_TH_ROBIN_MUDKIP, RIVAL_BATTLE_HEAL_AFTER, TH_Text_BattlePlayerLost, TH_Text_BattlePlayerWon
    goto TH_BattleFinished
TH_BattleFinished:
    copyvar VAR_0x8008, VAR_RESULT
    special HealPlayerParty
    special TH_FinishRivalBattle
    goto_if_eq VAR_0x8008, TRUE, TH_BattleEncourage
    msgbox TH_Text_RobinAfterWin
    goto TH_BattleGoodbye
TH_BattleEncourage:
    msgbox TH_Text_RobinAfterLoss
TH_BattleGoodbye:
    msgbox TH_Text_RobinRoute
    closemessage
    getplayerxy VAR_0x8008, VAR_0x8009
    goto_if_eq VAR_0x8009, 15, TH_BattleStepAround
    applymovement LOCALID_TH_ROBIN_TOWN, TH_Movement_JoeyToRoute
    goto TH_BattleDepart
TH_BattleStepAround:
    applymovement LOCALID_TH_ROBIN_TOWN, TH_Movement_JoeyAroundSouth
TH_BattleDepart:
    waitmovement 0
    removeobject LOCALID_TH_ROBIN_TOWN
TH_BattleRelease:
    releaseall
    end

TH_Movement_JoeyToRoute:
    walk_down
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    walk_up
    walk_up
    walk_up
    walk_up
    walk_up
    walk_up
    walk_up
    walk_up
    walk_up
    walk_up
    walk_up
    walk_up
    walk_up
    walk_up
    walk_up
    step_end


TH_Movement_JoeyAroundPlayer:
    walk_down
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    walk_down
    walk_down
    walk_down
    walk_down
    walk_right
    walk_right
    walk_right
    walk_right
    walk_up
    step_end

TH_Movement_JoeyAroundSouth:
    walk_left
    walk_down
    walk_left
    walk_left
    walk_left
    walk_left
    walk_up
    walk_up
    walk_up
    walk_up
    walk_up
    walk_up
    walk_up
    walk_up
    walk_up
    walk_up
    walk_up
    walk_up
    walk_up
    walk_up
    walk_up
    step_end
