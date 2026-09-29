@ Native single-Pokemon Kanto Day Care, using the compatible TH save adapter.
TH13_Daycare_EventScript_DaycareMan::
	lock
	faceplayer
	showmoneybox 0, 0
	specialvar VAR_RESULT, IsThereMonInRoute5Daycare
	goto_if_eq VAR_RESULT, TRUE, TH13_Daycare_EventScript_CheckOnMon
	msgbox TH13_Daycare_Text_WantMeToRaiseMon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, TH13_Daycare_EventScript_TryGiveMon
	msgbox TH13_Daycare_Text_ComeAgain
	goto TH13_Daycare_EventScript_CloseMoneyBox
	end

TH13_Daycare_EventScript_TryGiveMon::
	specialvar VAR_RESULT, CountPartyNonEggMons
	goto_if_eq VAR_RESULT, 1, TH13_Daycare_EventScript_OnlyOneMonInParty
	msgbox TH13_Daycare_Text_WhichMonShouldIRaise
	fadescreen FADE_TO_BLACK
	hidemoneybox
	special ChooseSendDaycareMon
	showmoneybox 0, 0
	goto_if_ge VAR_0x8004, PARTY_SIZE, TH13_Daycare_EventScript_ComeAgain
	specialvar VAR_RESULT, CountPartyAliveNonEggMons_IgnoreVar0x8004Slot
	goto_if_eq VAR_RESULT, 0, TH13_Daycare_EventScript_OnlyOneAliveMonInParty
	specialvar VAR_0x8005, GetSelectedMonNicknameAndSpecies
	msgbox TH13_Daycare_Text_LookAfterMonForAWhile
	waitse
	playmoncry VAR_0x8005, CRY_MODE_NORMAL
	msgbox TH13_Daycare_Text_ComeSeeMeInAWhile
	waitmoncry
	special PutMonInRoute5Daycare
	callnative UpdateFollowingPokemon
	incrementgamestat GAME_STAT_USED_DAYCARE
	goto TH13_Daycare_EventScript_CloseMoneyBox
	end

TH13_Daycare_EventScript_ComeAgain::
	msgbox TH13_Daycare_Text_ComeAnytimeYouLike
	goto TH13_Daycare_EventScript_CloseMoneyBox
	end

TH13_Daycare_EventScript_OnlyOneMonInParty::
	msgbox TH13_Daycare_Text_OnlyHaveOneMonWithYou
	goto TH13_Daycare_EventScript_CloseMoneyBox
	end

TH13_Daycare_EventScript_OnlyOneAliveMonInParty::
	msgbox TH13_Daycare_Text_WhatWillYouBattleWith
	goto TH13_Daycare_EventScript_CloseMoneyBox
	end

TH13_Daycare_EventScript_CheckOnMon::
	setvar VAR_0x8004, 0
	specialvar VAR_RESULT, GetNumLevelsGainedForRoute5DaycareMon
	call_if_ne VAR_RESULT, 0, TH13_Daycare_EventScript_MonHasGrownByXLevels
	call_if_eq VAR_RESULT, 0, TH13_Daycare_EventScript_NotEnoughTime
	special GetCostToWithdrawRoute5DaycareMon
	msgbox TH13_Daycare_Text_OweMeXForMonsReturn, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, TH13_Daycare_EventScript_TryRetrieveMon
	goto TH13_Daycare_EventScript_ComeAgain
	end

TH13_Daycare_EventScript_MonHasGrownByXLevels::
	msgbox TH13_Daycare_Text_MonHasGrownByXLevels
	return

TH13_Daycare_EventScript_NotEnoughTime::
	msgbox TH13_Daycare_Text_MonNeedsToSpendMoreTime
	return

TH13_Daycare_EventScript_TryRetrieveMon::
	specialvar VAR_RESULT, CalculatePlayerPartyCount
	goto_if_eq VAR_RESULT, PARTY_SIZE, TH13_Daycare_EventScript_NoRoomInParty
	specialvar VAR_RESULT, IsEnoughForCostInVar0x8005
	goto_if_eq VAR_RESULT, TRUE, TH13_Daycare_EventScript_RetrieveMon
	msgbox TH13_Daycare_Text_DontHaveEnoughMoney
	goto TH13_Daycare_EventScript_CloseMoneyBox
	end

TH13_Daycare_EventScript_RetrieveMon::
	setvar VAR_0x8004, 0
	specialvar VAR_RESULT, TakePokemonFromRoute5Daycare
	special SubtractMoneyFromVar0x8005
	updatemoneybox
	copyvar VAR_0x8008, VAR_RESULT
	getpartysize
	subvar VAR_RESULT, 1
	bufferpartymonnick STR_VAR_1, VAR_RESULT
	copyvar VAR_RESULT, VAR_0x8008
	msgbox TH13_Daycare_Text_ThankYouHeresMon
	textcolor NPC_TEXT_COLOR_NEUTRAL
	waitse
	playmoncry VAR_RESULT, CRY_MODE_NORMAL
	msgbox TH13_Daycare_Text_PlayerGotMonBack
	call EventScript_RestorePrevTextColor
	waitmoncry
	goto TH13_Daycare_EventScript_CloseMoneyBox
	end

TH13_Daycare_EventScript_NoRoomInParty::
	msgbox TH13_Daycare_Text_YouveGotNoRoomForIt
	goto TH13_Daycare_EventScript_CloseMoneyBox
	end

TH13_Daycare_EventScript_CloseMoneyBox::
	hidemoneybox
	release
	end

TH13_Daycare_Text_WantMeToRaiseMon::
	.string "I run the DAY-CARE service.\p"
	.string "Would you like me to raise one of\n"
	.string "your POKéMON?$"

TH13_Daycare_Text_ComeAgain::
	.string "Come again.$"

TH13_Daycare_Text_WhichMonShouldIRaise::
	.string "Which POKéMON should I raise?$"

TH13_Daycare_Text_ComeAnytimeYouLike::
	.string "Fine.\n"
	.string "Come anytime you like.$"

TH13_Daycare_Text_LookAfterMonForAWhile::
	.string "Fine, I'll look after your\n"
	.string "{STR_VAR_1} for a while.$"

TH13_Daycare_Text_ComeSeeMeInAWhile::
	.string "Come see me in a while.$"

TH13_Daycare_Text_MonNeedsToSpendMoreTime::
	.string "You're back already?\p"
	.string "Your {STR_VAR_1} needs to spend\n"
	.string "some more time with me.$"

TH13_Daycare_Text_OweMeXForMonsReturn::
	.string "You owe me ¥{STR_VAR_2} for the return\n"
	.string "of this POKéMON.$"

TH13_Daycare_Text_ThankYouHeresMon::
	.string "Thank you!\n"
	.string "Here's your POKéMON.$"

TH13_Daycare_Text_PlayerGotMonBack::
	.string "{PLAYER} got {STR_VAR_1} back\n"
	.string "from the DAY-CARE MAN.$"

TH13_Daycare_Text_OnlyHaveOneMonWithYou::
	.string "Oh? You only have one POKéMON\n"
	.string "with you.$"

TH13_Daycare_Text_WhatWillYouBattleWith::
	.string "If you leave me that POKéMON,\n"
	.string "what will you battle with?$"

TH13_Daycare_Text_MonHasGrownByXLevels::
	.string "Your {STR_VAR_1} has grown a lot.\n"
	.string "Yes, quite a lot, I'd say.\p"
	.string "Let me see…\n"
	.string "By level, it's grown by {STR_VAR_2}.\p"
	.string "Aren't I great?$"

TH13_Daycare_Text_YouveGotNoRoomForIt::
	.string "You can't take this POKéMON back\n"
	.string "if you've got no room for it.$"

TH13_Daycare_Text_DontHaveEnoughMoney::
	.string "You don't have enough money.$"

