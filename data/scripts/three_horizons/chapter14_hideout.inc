@ PT14 Hideout: project-owned geometry and failure-safe progression.

TH14_RocketHideout_B1F_EventScript_ItemEscapeRope::
	finditem ITEM_ESCAPE_ROPE
	end

TH14_RocketHideout_B1F_EventScript_ItemHyperPotion::
	finditem ITEM_HYPER_POTION
	end

TH14_RocketHideout_B2F_EventScript_ItemXSpeed::
	finditem ITEM_X_SPEED
	end

TH14_RocketHideout_B2F_EventScript_ItemMoonStone::
	finditem ITEM_MOON_STONE
	end

TH14_RocketHideout_B2F_EventScript_ItemTM12::
	finditem ITEM_TM12
	end

TH14_RocketHideout_B2F_EventScript_ItemSuperPotion::
	finditem ITEM_SUPER_POTION
	end

TH14_RocketHideout_B3F_EventScript_ItemRareCandy::
	finditem ITEM_RARE_CANDY
	end

TH14_RocketHideout_B3F_EventScript_ItemTM21::
	finditem ITEM_TM21
	end

TH14_RocketHideout_B3F_EventScript_ItemBlackGlasses::
	finditem ITEM_BLACK_GLASSES
	end

TH14_RocketHideout_B4F_EventScript_ItemTM49::
	finditem ITEM_TM49
	end

TH14_RocketHideout_B4F_EventScript_ItemMaxEther::
	finditem ITEM_MAX_ETHER
	end

TH14_RocketHideout_B4F_EventScript_ItemCalcium::
	finditem ITEM_CALCIUM
	end

TH14_RocketHideout_B1F_EventScript_Grunt1::
    trainerbattle_single TRAINER_TH14_HIDEOUT_B1F_GRUNT1, TH14_RocketHideout_B1F_Text_Grunt1Intro, TH14_RocketHideout_B1F_Text_Grunt1Defeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH14_RocketHideout_B1F_EventScript_Grunt1_Rematch
    msgbox TH14_RocketHideout_B1F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
    end
TH14_RocketHideout_B1F_EventScript_Grunt1_Rematch::
    trainerbattle_rematch TRAINER_TH14_HIDEOUT_B1F_GRUNT1, TH14_RocketHideout_B1F_Text_Grunt1Intro, TH14_RocketHideout_B1F_Text_Grunt1Defeat
    msgbox TH14_RocketHideout_B1F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
    end

TH14_RocketHideout_B1F_Text_Grunt1Intro::
	.string "Who are you?\n"
	.string "How did you get here?$"

TH14_RocketHideout_B1F_Text_Grunt1Defeat::
	.string "Oww!\n"
	.string "Beaten!$"

TH14_RocketHideout_B1F_Text_Grunt1PostBattle::
	.string "Blast it… You're dissing TEAM\n"
	.string "ROCKET, aren't you?$"

TH14_RocketHideout_B1F_EventScript_Grunt2::
    trainerbattle_single TRAINER_TH14_HIDEOUT_B1F_GRUNT2, TH14_RocketHideout_B1F_Text_Grunt2Intro, TH14_RocketHideout_B1F_Text_Grunt2Defeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH14_RocketHideout_B1F_EventScript_Grunt2_Rematch
    msgbox TH14_RocketHideout_B1F_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
    end
TH14_RocketHideout_B1F_EventScript_Grunt2_Rematch::
    trainerbattle_rematch TRAINER_TH14_HIDEOUT_B1F_GRUNT2, TH14_RocketHideout_B1F_Text_Grunt2Intro, TH14_RocketHideout_B1F_Text_Grunt2Defeat
    msgbox TH14_RocketHideout_B1F_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
    end

TH14_RocketHideout_B1F_Text_Grunt2Intro::
	.string "You broke into TEAM ROCKET's\n"
	.string "operation? What nerve!$"

TH14_RocketHideout_B1F_Text_Grunt2Defeat::
	.string "Boom!$"

TH14_RocketHideout_B1F_Text_Grunt2PostBattle::
	.string "You're not going to get away with\n"
	.string "this, brat!$"

TH14_RocketHideout_B1F_EventScript_Grunt3::
    trainerbattle_single TRAINER_TH14_HIDEOUT_B1F_GRUNT3, TH14_RocketHideout_B1F_Text_Grunt3Intro, TH14_RocketHideout_B1F_Text_Grunt3Defeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH14_RocketHideout_B1F_EventScript_Grunt3_Rematch
    msgbox TH14_RocketHideout_B1F_Text_Grunt3PostBattle, MSGBOX_AUTOCLOSE
    end
TH14_RocketHideout_B1F_EventScript_Grunt3_Rematch::
    trainerbattle_rematch TRAINER_TH14_HIDEOUT_B1F_GRUNT3, TH14_RocketHideout_B1F_Text_Grunt3Intro, TH14_RocketHideout_B1F_Text_Grunt3Defeat
    msgbox TH14_RocketHideout_B1F_Text_Grunt3PostBattle, MSGBOX_AUTOCLOSE
    end

TH14_RocketHideout_B1F_Text_Grunt3Intro::
	.string "Intruder alert!$"

TH14_RocketHideout_B1F_Text_Grunt3Defeat::
	.string "I can't do it!$"

TH14_RocketHideout_B1F_Text_Grunt3PostBattle::
	.string "SILPH SCOPE? Humph!\n"
	.string "I don't know where it is.$"

TH14_RocketHideout_B1F_EventScript_Grunt4::
    trainerbattle_single TRAINER_TH14_HIDEOUT_B1F_GRUNT4, TH14_RocketHideout_B1F_Text_Grunt4Intro, TH14_RocketHideout_B1F_Text_Grunt4Defeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH14_RocketHideout_B1F_EventScript_Grunt4_Rematch
    msgbox TH14_RocketHideout_B1F_Text_Grunt4PostBattle, MSGBOX_AUTOCLOSE
    end
TH14_RocketHideout_B1F_EventScript_Grunt4_Rematch::
    trainerbattle_rematch TRAINER_TH14_HIDEOUT_B1F_GRUNT4, TH14_RocketHideout_B1F_Text_Grunt4Intro, TH14_RocketHideout_B1F_Text_Grunt4Defeat
    msgbox TH14_RocketHideout_B1F_Text_Grunt4PostBattle, MSGBOX_AUTOCLOSE
    end

TH14_RocketHideout_B1F_Text_Grunt4Intro::
	.string "Why did you come here?$"

TH14_RocketHideout_B1F_Text_Grunt4Defeat::
	.string "This won't do!$"

TH14_RocketHideout_B1F_Text_Grunt4PostBattle::
	.string "Okay, I'll talk…\n"
	.string "Take the elevator to see my BOSS.$"

TH14_RocketHideout_B1F_EventScript_Grunt5::
    trainerbattle_single TRAINER_TH14_HIDEOUT_B1F_GRUNT5, TH14_RocketHideout_B1F_Text_Grunt5Intro, TH14_RocketHideout_B1F_Text_Grunt5Defeat, TH14_HideoutB1F_Victory
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH14_RocketHideout_B1F_EventScript_Grunt5_Rematch
    msgbox TH14_RocketHideout_B1F_Text_Grunt5PostBattle, MSGBOX_AUTOCLOSE
    end
TH14_RocketHideout_B1F_EventScript_Grunt5_Rematch::
    trainerbattle_rematch TRAINER_TH14_HIDEOUT_B1F_GRUNT5, TH14_RocketHideout_B1F_Text_Grunt5Intro, TH14_RocketHideout_B1F_Text_Grunt5Defeat
    msgbox TH14_RocketHideout_B1F_Text_Grunt5PostBattle, MSGBOX_AUTOCLOSE
    end

TH14_RocketHideout_B1F_Text_Grunt5Intro::
	.string "Are you lost, you little mouse?$"

TH14_RocketHideout_B1F_Text_Grunt5Defeat::
	.string "Why…?$"

TH14_RocketHideout_B1F_Text_Grunt5PostBattle::
	.string "Uh-oh, that ruckus somehow opened\n"
	.string "the door!$"

TH14_RocketHideout_B2F_EventScript_Grunt::
    trainerbattle_single TRAINER_TH14_HIDEOUT_B2F_GRUNT, TH14_RocketHideout_B2F_Text_GruntIntro, TH14_RocketHideout_B2F_Text_GruntDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH14_RocketHideout_B2F_EventScript_Grunt_Rematch
    msgbox TH14_RocketHideout_B2F_Text_GruntPostBattle, MSGBOX_AUTOCLOSE
    end
TH14_RocketHideout_B2F_EventScript_Grunt_Rematch::
    trainerbattle_rematch TRAINER_TH14_HIDEOUT_B2F_GRUNT, TH14_RocketHideout_B2F_Text_GruntIntro, TH14_RocketHideout_B2F_Text_GruntDefeat
    msgbox TH14_RocketHideout_B2F_Text_GruntPostBattle, MSGBOX_AUTOCLOSE
    end

TH14_RocketHideout_B2F_Text_GruntIntro::
	.string "BOSS said you can see ghosts with\n"
	.string "the SILPH SCOPE.$"

TH14_RocketHideout_B2F_Text_GruntDefeat::
	.string "I surrender!$"

TH14_RocketHideout_B2F_Text_GruntPostBattle::
	.string "The TEAM ROCKET HQ has four\n"
	.string "underground floors.\p"
	.string "Think you can reach the BOSS?$"

TH14_RocketHideout_B3F_EventScript_Grunt1::
    trainerbattle_single TRAINER_TH14_HIDEOUT_B3F_GRUNT1, TH14_RocketHideout_B3F_Text_Grunt1Intro, TH14_RocketHideout_B3F_Text_Grunt1Defeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH14_RocketHideout_B3F_EventScript_Grunt1_Rematch
    msgbox TH14_RocketHideout_B3F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
    end
TH14_RocketHideout_B3F_EventScript_Grunt1_Rematch::
    trainerbattle_rematch TRAINER_TH14_HIDEOUT_B3F_GRUNT1, TH14_RocketHideout_B3F_Text_Grunt1Intro, TH14_RocketHideout_B3F_Text_Grunt1Defeat
    msgbox TH14_RocketHideout_B3F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
    end

TH14_RocketHideout_B3F_Text_Grunt1Intro::
	.string "Stop meddling in TEAM ROCKET's\n"
	.string "affairs or else!$"

TH14_RocketHideout_B3F_Text_Grunt1Defeat::
	.string "Oof!\n"
	.string "Taken down!$"

TH14_RocketHideout_B3F_Text_Grunt1PostBattle::
	.string "SILPH SCOPE?\n"
	.string "Oh, that machine the BOSS stole.\p"
	.string "It's here somewhere.$"

TH14_RocketHideout_B3F_EventScript_Grunt2::
    trainerbattle_single TRAINER_TH14_HIDEOUT_B3F_GRUNT2, TH14_RocketHideout_B3F_Text_Grunt2Intro, TH14_RocketHideout_B3F_Text_Grunt2Defeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH14_RocketHideout_B3F_EventScript_Grunt2_Rematch
    msgbox TH14_RocketHideout_B3F_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
    end
TH14_RocketHideout_B3F_EventScript_Grunt2_Rematch::
    trainerbattle_rematch TRAINER_TH14_HIDEOUT_B3F_GRUNT2, TH14_RocketHideout_B3F_Text_Grunt2Intro, TH14_RocketHideout_B3F_Text_Grunt2Defeat
    msgbox TH14_RocketHideout_B3F_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
    end

TH14_RocketHideout_B3F_Text_Grunt2Intro::
	.string "We got word from upstairs that you\n"
	.string "were coming!$"

TH14_RocketHideout_B3F_Text_Grunt2Defeat::
	.string "What?\n"
	.string "I lost? No!$"

TH14_RocketHideout_B3F_Text_Grunt2PostBattle::
	.string "Go ahead and go!\p"
	.string "But you can't run the elevator\n"
	.string "without the LIFT KEY.$"

TH14_RocketHideout_B4F_EventScript_Grunt1::
    trainerbattle_single TRAINER_TH14_HIDEOUT_B4F_GRUNT1, TH14_RocketHideout_B4F_Text_Grunt1Intro, TH14_RocketHideout_B4F_Text_Grunt1Defeat, TH14_HideoutKeyGuard_Victory
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH14_RocketHideout_B4F_EventScript_Grunt1_Rematch
    msgbox TH14_RocketHideout_B4F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
    end
TH14_RocketHideout_B4F_EventScript_Grunt1_Rematch::
    trainerbattle_rematch TRAINER_TH14_HIDEOUT_B4F_GRUNT1, TH14_RocketHideout_B4F_Text_Grunt1Intro, TH14_RocketHideout_B4F_Text_Grunt1Defeat
    msgbox TH14_RocketHideout_B4F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
    end

TH14_RocketHideout_B4F_Text_Grunt1Intro::
	.string "The elevator doesn't work?\n"
	.string "Who has the LIFT KEY?$"

TH14_RocketHideout_B4F_Text_Grunt1Defeat::
	.string "No!$"

TH14_RocketHideout_B4F_Text_Grunt1PostBattle::
	.string "Oh, no!\n"
	.string "I dropped the LIFT KEY!$"

TH14_RocketHideout_B4F_EventScript_Grunt2::
    trainerbattle_single TRAINER_TH14_HIDEOUT_B4F_GRUNT2, TH14_RocketHideout_B4F_Text_Grunt2Intro, TH14_RocketHideout_B4F_Text_Grunt2Defeat, TH14_HideoutB4F_Victory
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH14_RocketHideout_B4F_EventScript_Grunt2_Rematch
    msgbox TH14_RocketHideout_B4F_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
    end
TH14_RocketHideout_B4F_EventScript_Grunt2_Rematch::
    trainerbattle_rematch TRAINER_TH14_HIDEOUT_B4F_GRUNT2, TH14_RocketHideout_B4F_Text_Grunt2Intro, TH14_RocketHideout_B4F_Text_Grunt2Defeat
    msgbox TH14_RocketHideout_B4F_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
    end

TH14_RocketHideout_B4F_Text_Grunt2Intro::
	.string "I know you!\n"
	.string "You ruined our plans at MT. MOON!$"

TH14_RocketHideout_B4F_Text_Grunt2Defeat::
	.string "Burned again!$"

TH14_RocketHideout_B4F_Text_Grunt2PostBattle::
	.string "Do you have something against TEAM\n"
	.string "ROCKET?$"

TH14_RocketHideout_B4F_EventScript_Grunt3::
    trainerbattle_single TRAINER_TH14_HIDEOUT_B4F_GRUNT3, TH14_RocketHideout_B4F_Text_Grunt3Intro, TH14_RocketHideout_B4F_Text_Grunt3Defeat, TH14_HideoutB4F_Victory
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH14_RocketHideout_B4F_EventScript_Grunt3_Rematch
    msgbox TH14_RocketHideout_B4F_Text_Grunt3PostBattle, MSGBOX_AUTOCLOSE
    end
TH14_RocketHideout_B4F_EventScript_Grunt3_Rematch::
    trainerbattle_rematch TRAINER_TH14_HIDEOUT_B4F_GRUNT3, TH14_RocketHideout_B4F_Text_Grunt3Intro, TH14_RocketHideout_B4F_Text_Grunt3Defeat
    msgbox TH14_RocketHideout_B4F_Text_Grunt3PostBattle, MSGBOX_AUTOCLOSE
    end

TH14_RocketHideout_B4F_Text_Grunt3Intro::
	.string "How can you not see the beauty of\n"
	.string "our evil?$"

TH14_RocketHideout_B4F_Text_Grunt3Defeat::
	.string "Ayaya!$"

TH14_RocketHideout_B4F_Text_Grunt3PostBattle::
	.string "BOSS!\n"
	.string "I'm sorry I failed you!$"

TH14_RocketHideout_B1F_OnLoad::
    call TH14_RocketHideout_B1F_UpdateDoor
    end

TH14_RocketHideout_B1F_UpdateDoor::
    goto_if_not_defeated TRAINER_TH14_HIDEOUT_B1F_GRUNT5, TH14_RocketHideout_B1F_SetBarrier
    goto TH14_RocketHideout_B1F_RemoveBarrier

TH14_RocketHideout_B1F_SetBarrier::
	setmetatile 20, 19, METATILE_SilphCo_HideoutBarrier_TopLeft_Floor, 1
	setmetatile 21, 19, METATILE_SilphCo_HideoutBarrier_TopRight_Floor, 1
	setmetatile 20, 20, METATILE_SilphCo_HideoutBarrier_BottomLeft, 1
	setmetatile 21, 20, METATILE_SilphCo_HideoutBarrier_BottomRight, 1
	setmetatile 20, 21, METATILE_SilphCo_HideoutFloor_ShadeFull, 0
	setmetatile 21, 21, METATILE_SilphCo_HideoutFloor_ShadeFull, 0
	return

TH14_RocketHideout_B1F_RemoveBarrier::
	setmetatile 20, 19, METATILE_SilphCo_HideoutFloor_ShadeFull, 0
	setmetatile 21, 19, METATILE_SilphCo_HideoutFloor, 0
	setmetatile 20, 20, METATILE_SilphCo_HideoutFloor_ShadeFull, 0
	setmetatile 21, 20, METATILE_SilphCo_HideoutFloor, 0
	setmetatile 20, 21, METATILE_SilphCo_HideoutFloor_ShadeFull, 0
	setmetatile 21, 21, METATILE_SilphCo_HideoutFloor, 0
	return

TH14_HideoutB1F_Victory::
    call TH14_RocketHideout_B1F_UpdateDoor
    playse SE_UNLOCK
    special DrawWholeMapView
    waitse
    releaseall
    end

TH14_RocketHideout_B4F_OnLoad::
    call TH14_RocketHideout_B4F_UpdateDoor
    end

TH14_RocketHideout_B4F_UpdateDoor::
    goto_if_not_defeated TRAINER_TH14_HIDEOUT_B4F_GRUNT2, TH14_RocketHideout_B4F_SetBarrier
    goto_if_not_defeated TRAINER_TH14_HIDEOUT_B4F_GRUNT3, TH14_RocketHideout_B4F_SetBarrier
    goto TH14_RocketHideout_B4F_RemoveBarrier

TH14_RocketHideout_B4F_SetBarrier::
	setmetatile 17, 12, METATILE_SilphCo_HideoutBarrier_TopLeft_Floor, 1
	setmetatile 18, 12, METATILE_SilphCo_HideoutBarrier_TopRight_Floor, 1
	setmetatile 17, 13, METATILE_SilphCo_HideoutBarrier_BottomLeft, 1
	setmetatile 18, 13, METATILE_SilphCo_HideoutBarrier_BottomRight, 1
	setmetatile 17, 14, METATILE_SilphCo_HideoutFloor_ShadeFull, 0
	setmetatile 18, 14, METATILE_SilphCo_HideoutFloor_ShadeFull, 0
	return

TH14_RocketHideout_B4F_RemoveBarrier::
	setmetatile 17, 12, METATILE_SilphCo_HideoutFloor_ShadeFull, 0
	setmetatile 18, 12, METATILE_SilphCo_HideoutFloor, 0
	setmetatile 17, 13, METATILE_SilphCo_HideoutFloor_ShadeFull, 0
	setmetatile 18, 13, METATILE_SilphCo_HideoutFloor, 0
	setmetatile 17, 14, METATILE_SilphCo_HideoutFloor_ShadeFull, 0
	setmetatile 18, 14, METATILE_SilphCo_HideoutFloor, 0
	return

TH14_HideoutB4F_Victory::
    call TH14_RocketHideout_B4F_UpdateDoor
    playse SE_UNLOCK
    special DrawWholeMapView
    waitse
    releaseall
    end

TH14_RocketHideout_B4F_EventScript_Giovanni::
    msgbox TH14_HideoutPending, MSGBOX_NPC
    end

TH14_RocketHideout_B4F_EventScript_SilphScope::
    msgbox TH14_HideoutPending, MSGBOX_NPC
    end

TH14_HideoutKeyGuard_Victory::
    msgbox TH14_RocketHideout_B4F_Text_Grunt1PostBattle
    goto_if_set FLAG_TH14_LIFT_KEY, TH14_HideoutEnd
    addobject LOCALID_TH14_ROCKETHIDEOUT_B4F_4
    goto TH14_HideoutEnd

TH14_RocketHideout_B4F_EventScript_LiftKey::
    lock
    faceplayer
    goto_if_not_defeated TRAINER_TH14_HIDEOUT_B4F_GRUNT1, TH14_HideoutEnd
    setvar VAR_0x8004, ITEM_LIFT_KEY
    setvar VAR_0x8005, FLAG_TH14_LIFT_KEY
    special TH14_ScriptGiveUniqueItem
    goto_if_eq VAR_RESULT, 0, TH14_HideoutKeyNoRoom
    removeobject LOCALID_TH14_ROCKETHIDEOUT_B4F_4
    goto_if_eq VAR_RESULT, 2, TH14_HideoutEnd
    playfanfare MUS_OBTAIN_ITEM
    msgbox TH14_HideoutKeyReceived
    waitfanfare
    goto TH14_HideoutEnd
TH14_HideoutKeyNoRoom:
    msgbox TH14_HideoutKeyNoRoomText
TH14_HideoutEnd:
    releaseall
    end

TH14_CeladonCity_GameCorner_EventScript_RocketGrunt::
    trainerbattle_single TRAINER_TH14_GAME_CORNER_GRUNT, TH14_HideoutPosterGruntIntro, TH14_HideoutPosterGruntDefeat, TH14_HideoutPosterGruntVictory
    goto TH14_HideoutPosterGruntVictory
TH14_HideoutPosterGruntVictory::
    msgbox TH14_HideoutPosterGruntPost
    closemessage
    call_if_eq VAR_FACING, DIR_WEST, TH14_HideoutPosterGruntExitWest
    call_if_ne VAR_FACING, DIR_WEST, TH14_HideoutPosterGruntExit
    removeobject LOCALID_TH14_CELADONCITY_GAMECORNER_11
    releaseall
    end
TH14_HideoutPosterGruntExitWest:
    applymovement LOCALID_TH14_CELADONCITY_GAMECORNER_11, TH14_HideoutPosterGruntMovementWest
    waitmovement 0
    return
TH14_HideoutPosterGruntExit:
    applymovement LOCALID_TH14_CELADONCITY_GAMECORNER_11, TH14_HideoutPosterGruntMovement
    waitmovement 0
    return
TH14_HideoutPosterGruntMovementWest:
    walk_down
    walk_right
    walk_right
    walk_up
    walk_right
    walk_right
    walk_right
    walk_right
    step_end
TH14_HideoutPosterGruntMovement:
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    step_end

TH14_CeladonCity_GameCorner_EventScript_Poster::
    lockall
    goto_if_not_defeated TRAINER_TH14_GAME_CORNER_GRUNT, TH14_HideoutPosterBlocked
    goto_if_set FLAG_TH14_HIDEOUT_POSTER, TH14_HideoutPosterRepeat
    msgbox TH14_HideoutPosterSwitchText
    setflag FLAG_TH14_HIDEOUT_POSTER
    call TH14_HideoutPoster_Open
    playse SE_UNLOCK
    special DrawWholeMapView
    waitse
    goto TH14_HideoutEnd
TH14_HideoutPosterRepeat:
    msgbox TH14_HideoutPosterOpenText
    goto TH14_HideoutEnd
TH14_HideoutPosterBlocked:
    msgbox TH14_HideoutPosterBlockedText
    goto TH14_HideoutEnd
TH14_HideoutPoster_OnLoad::
    goto_if_set FLAG_TH14_HIDEOUT_POSTER, TH14_HideoutPoster_LoadOpen
    call TH14_HideoutPoster_Close
    end
TH14_HideoutPoster_LoadOpen:
    call TH14_HideoutPoster_Open
    end
TH14_HideoutPoster_Close:
    setmetatile 15, 2, METATILE_GameCorner_Floor_ShadeFull, 0
    setmetatile 16, 2, METATILE_GameCorner_Floor_ShadeFull, 0
    setmetatile 17, 2, METATILE_GameCorner_Floor_ShadeFull, 0
    setmetatile 16, 3, METATILE_GameCorner_PurpleWall_Floor, 1
    setmetatile 17, 3, METATILE_GameCorner_PurpleWall_Floor, 1
    return
TH14_HideoutPoster_Open:
    setmetatile 15, 2, METATILE_GameCorner_Floor_StairsTop, 0
    setmetatile 16, 2, METATILE_GameCorner_StairsTop, 1
    setmetatile 17, 2, METATILE_GameCorner_StairsBottom, 1
    setmetatile 16, 3, METATILE_GameCorner_PurpleWall_StairsTop, 1
    setmetatile 17, 3, METATILE_GameCorner_PurpleWall_stairsBottom, 1
    return

TH14_HideoutElevator_CheckReturn::
    specialvar VAR_RESULT, TH14_GetHideoutFloor
    goto_if_ne VAR_RESULT, 65535, TH14_HideoutElevator_ReturnValid
    setdynamicwarp MAP_TH14_ROCKET_HIDEOUT_B1F, 255, 24, 25
TH14_HideoutElevator_ReturnValid:
    end
TH14_RocketHideout_Elevator_EventScript_FloorSelect::
    lockall
    checkitem ITEM_LIFT_KEY
    goto_if_eq VAR_RESULT, FALSE, TH14_HideoutElevator_NoKey
    specialvar VAR_0x8005, TH14_GetHideoutFloor
    goto_if_eq VAR_0x8005, 65535, TH14_HideoutEnd
    special DrawElevatorCurrentFloorWindow
    message gText_WantWhichFloor
    waitmessage
    goto_if_eq VAR_0x8005, 2, TH14_HideoutElevator_MenuB2F
    goto_if_eq VAR_0x8005, 0, TH14_HideoutElevator_MenuB4F
    multichoicedefault 0, 0, MULTI_ROCKET_HIDEOUT_ELEVATOR, 0, FALSE
    goto TH14_HideoutElevator_Select
TH14_HideoutElevator_MenuB2F:
    multichoicedefault 0, 0, MULTI_ROCKET_HIDEOUT_ELEVATOR, 1, FALSE
    goto TH14_HideoutElevator_Select
TH14_HideoutElevator_MenuB4F:
    multichoicedefault 0, 0, MULTI_ROCKET_HIDEOUT_ELEVATOR, 2, FALSE
TH14_HideoutElevator_Select:
    copyvar VAR_0x8004, VAR_RESULT
    specialvar VAR_RESULT, TH14_ScriptSelectHideoutFloor
    goto_if_eq VAR_RESULT, FALSE, TH14_HideoutElevator_Exit
    goto_if_eq VAR_0x8005, VAR_0x8006, TH14_HideoutElevator_Exit
    special CloseElevatorCurrentFloorWindow
    closemessage
    waitse
    special AnimateElevator
    waitstate
    goto TH14_HideoutEnd
TH14_HideoutElevator_Exit:
    special CloseElevatorCurrentFloorWindow
    goto TH14_HideoutEnd
TH14_HideoutElevator_NoKey:
    msgbox TH14_HideoutElevator_NoKeyText
    goto TH14_HideoutEnd

TH14_HideoutResearchRecord0::
    msgbox TH14_HideoutDistributionText, MSGBOX_SIGN
    end
TH14_HideoutResearchRecord1::
    msgbox TH14_HideoutUnconfirmedText, MSGBOX_SIGN
    end
TH14_HideoutResearchRecord2::
    msgbox TH14_HideoutOrdersText, MSGBOX_SIGN
    end

TH14_HideoutDistributionText:
    .string "A marked distribution map.\pUnusual sightings are circled\nbeside reports from local habitats.$"
TH14_HideoutUnconfirmedText:
    .string "GHOST SIGHTINGS /\nMIGRATION REPORTS.\pSeveral accounts are marked\nUNCONFIRMED.$"
TH14_HideoutOrdersText:
    .string "Record rare appearances, abnormal\nevolution and witness accounts.\pSend copies for comparison.\nDo not assume a cause.$"
TH14_HideoutKeyReceived:
    .string "{PLAYER} obtained the LIFT KEY!$"
TH14_HideoutKeyNoRoomText:
    .string "The BAG is full.\nThe LIFT KEY is still here.$"
TH14_HideoutElevator_NoKeyText:
    .string "It appears to need a key.$"
TH14_HideoutPosterGruntIntro:
    .string "I'm guarding this poster!\nGo away, or else!$"
TH14_HideoutPosterGruntDefeat:
    .string "Dang!$"
TH14_HideoutPosterGruntPost:
    .string "Our hideout might be discovered!\nI'd better tell the BOSS!$"
TH14_HideoutPosterSwitchText:
    .string "Hey! A switch behind the poster!\n{PLAYER} pushed it!$"
TH14_HideoutPosterOpenText:
    .string "The hidden stairs are open.$"
TH14_HideoutPosterBlockedText:
    .string "The ROCKET won't let you\nexamine the poster.$"
TH14_HideoutPending:
    .string "We have business to discuss.$"
