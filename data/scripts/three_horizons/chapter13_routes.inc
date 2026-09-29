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


@ Route 11 retains native first battles, dialogue and ordinary rematch eligibility.
TH13_Route11_Eddie::
    trainerbattle_single TRAINER_TH13_ROUTE11_EDDIE, TH13_Route11_Text_EddieIntro, TH13_Route11_Text_EddieDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH13_Route11_Eddie_Rematch
    msgbox TH13_Route11_Text_EddiePostBattle, MSGBOX_AUTOCLOSE
    end
TH13_Route11_Eddie_Rematch::
    trainerbattle_rematch TRAINER_TH13_ROUTE11_EDDIE, TH13_Route11_Text_EddieIntro, TH13_Route11_Text_EddieDefeat
    msgbox TH13_Route11_Text_EddiePostBattle, MSGBOX_AUTOCLOSE
    end
TH13_Route11_Hugo::
    trainerbattle_single TRAINER_TH13_ROUTE11_HUGO, TH13_Route11_Text_HugoIntro, TH13_Route11_Text_HugoDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH13_Route11_Hugo_Rematch
    msgbox TH13_Route11_Text_HugoPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_Route11_Hugo_Rematch::
    trainerbattle_rematch TRAINER_TH13_ROUTE11_HUGO, TH13_Route11_Text_HugoIntro, TH13_Route11_Text_HugoDefeat
    msgbox TH13_Route11_Text_HugoPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_Route11_Dillon::
    trainerbattle_single TRAINER_TH13_ROUTE11_DILLON, TH13_Route11_Text_DillonIntro, TH13_Route11_Text_DillonDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH13_Route11_Dillon_Rematch
    msgbox TH13_Route11_Text_DillonPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_Route11_Dillon_Rematch::
    trainerbattle_rematch TRAINER_TH13_ROUTE11_DILLON, TH13_Route11_Text_DillonIntro, TH13_Route11_Text_DillonDefeat
    msgbox TH13_Route11_Text_DillonPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_Route11_Dave::
    trainerbattle_single TRAINER_TH13_ROUTE11_DAVE, TH13_Route11_Text_DaveIntro, TH13_Route11_Text_DaveDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH13_Route11_Dave_Rematch
    msgbox TH13_Route11_Text_DavePostBattle, MSGBOX_AUTOCLOSE
    end
TH13_Route11_Dave_Rematch::
    trainerbattle_rematch TRAINER_TH13_ROUTE11_DAVE, TH13_Route11_Text_DaveIntro, TH13_Route11_Text_DaveDefeat
    msgbox TH13_Route11_Text_DavePostBattle, MSGBOX_AUTOCLOSE
    end
TH13_Route11_Jasper::
    trainerbattle_single TRAINER_TH13_ROUTE11_JASPER, TH13_Route11_Text_JasperIntro, TH13_Route11_Text_JasperDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH13_Route11_Jasper_Rematch
    msgbox TH13_Route11_Text_JasperPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_Route11_Jasper_Rematch::
    trainerbattle_rematch TRAINER_TH13_ROUTE11_JASPER, TH13_Route11_Text_JasperIntro, TH13_Route11_Text_JasperDefeat
    msgbox TH13_Route11_Text_JasperPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_Route11_Darian::
    trainerbattle_single TRAINER_TH13_ROUTE11_DARIAN, TH13_Route11_Text_DarianIntro, TH13_Route11_Text_DarianDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH13_Route11_Darian_Rematch
    msgbox TH13_Route11_Text_DarianPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_Route11_Darian_Rematch::
    trainerbattle_rematch TRAINER_TH13_ROUTE11_DARIAN, TH13_Route11_Text_DarianIntro, TH13_Route11_Text_DarianDefeat
    msgbox TH13_Route11_Text_DarianPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_Route11_Braxton::
    trainerbattle_single TRAINER_TH13_ROUTE11_BRAXTON, TH13_Route11_Text_BraxtonIntro, TH13_Route11_Text_BraxtonDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH13_Route11_Braxton_Rematch
    msgbox TH13_Route11_Text_BraxtonPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_Route11_Braxton_Rematch::
    trainerbattle_rematch TRAINER_TH13_ROUTE11_BRAXTON, TH13_Route11_Text_BraxtonIntro, TH13_Route11_Text_BraxtonDefeat
    msgbox TH13_Route11_Text_BraxtonPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_Route11_Yasu::
    trainerbattle_single TRAINER_TH13_ROUTE11_YASU, TH13_Route11_Text_YasuIntro, TH13_Route11_Text_YasuDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH13_Route11_Yasu_Rematch
    msgbox TH13_Route11_Text_YasuPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_Route11_Yasu_Rematch::
    trainerbattle_rematch TRAINER_TH13_ROUTE11_YASU, TH13_Route11_Text_YasuIntro, TH13_Route11_Text_YasuDefeat
    msgbox TH13_Route11_Text_YasuPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_Route11_Dirk::
    trainerbattle_single TRAINER_TH13_ROUTE11_DIRK, TH13_Route11_Text_DirkIntro, TH13_Route11_Text_DirkDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH13_Route11_Dirk_Rematch
    msgbox TH13_Route11_Text_DirkPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_Route11_Dirk_Rematch::
    trainerbattle_rematch TRAINER_TH13_ROUTE11_DIRK, TH13_Route11_Text_DirkIntro, TH13_Route11_Text_DirkDefeat
    msgbox TH13_Route11_Text_DirkPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_Route11_Bernie::
    trainerbattle_single TRAINER_TH13_ROUTE11_BERNIE, TH13_Route11_Text_BernieIntro, TH13_Route11_Text_BernieDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH13_Route11_Bernie_Rematch
    msgbox TH13_Route11_Text_BerniePostBattle, MSGBOX_AUTOCLOSE
    end
TH13_Route11_Bernie_Rematch::
    trainerbattle_rematch TRAINER_TH13_ROUTE11_BERNIE, TH13_Route11_Text_BernieIntro, TH13_Route11_Text_BernieDefeat
    msgbox TH13_Route11_Text_BerniePostBattle, MSGBOX_AUTOCLOSE
    end
TH13_Route11_Item0::
    finditem ITEM_X_DEFENSE
    end
TH13_Route11_Item1::
    finditem ITEM_GREAT_BALL
    end
TH13_Route11_Item2::
    finditem ITEM_AWAKENING
    end


TH13_Route11_EventScript_DiglettsCaveSign::
	msgbox TH13_Route11_Text_DiglettsCave, MSGBOX_SIGN
	end

TH13_Route11_Text_HugoIntro::
	.string "Win, lose, or draw!$"

TH13_Route11_Text_HugoDefeat::
	.string "Atcha!\n"
	.string "Didn't go my way!$"

TH13_Route11_Text_HugoPostBattle::
	.string "POKéMON is life!\n"
	.string "And to live is to play games!$"

TH13_Route11_Text_JasperIntro::
	.string "Competition!\n"
	.string "I can't get enough!$"

TH13_Route11_Text_JasperDefeat::
	.string "I had a chance!$"

TH13_Route11_Text_JasperPostBattle::
	.string "You can't be a coward in the world\n"
	.string "of POKéMON!$"

TH13_Route11_Text_EddieIntro::
	.string "Let's go, but don't cheat!$"

TH13_Route11_Text_EddieDefeat::
	.string "Huh?\n"
	.string "That's not right!$"

TH13_Route11_Text_EddiePostBattle::
	.string "I did my best.\n"
	.string "I have no regrets.$"

TH13_Route11_Text_BraxtonIntro::
	.string "Careful!\n"
	.string "I'm laying down some cables!$"

TH13_Route11_Text_BraxtonDefeat::
	.string "That was electric!$"

TH13_Route11_Text_BraxtonPostBattle::
	.string "Spread the word to save energy!$"

TH13_Route11_Text_DillonIntro::
	.string "I just became a TRAINER.\n"
	.string "But, I think I can win.$"

TH13_Route11_Text_DillonDefeat::
	.string "My POKéMON couldn't win…\n"
	.string "Haven't they grown enough?$"

TH13_Route11_Text_DillonPostBattle::
	.string "What now?\n"
	.string "Leave me alone!$"

TH13_Route11_Text_DirkIntro::
	.string "Fwahaha!\n"
	.string "I have never lost!$"

TH13_Route11_Text_DirkDefeat::
	.string "My first loss!$"

TH13_Route11_Text_DirkPostBattle::
	.string "You were just lucky, that's all.$"

TH13_Route11_Text_DarianIntro::
	.string "I have never won before…$"

TH13_Route11_Text_DarianDefeat::
	.string "I saw this coming…$"

TH13_Route11_Text_DarianPostBattle::
	.string "I was unlucky, as always.$"

TH13_Route11_Text_YasuIntro::
	.string "I'm the best in my class.\n"
	.string "I train every morning.$"

TH13_Route11_Text_YasuDefeat::
	.string "Darn!\n"
	.string "My POKéMON need to be stronger!$"

TH13_Route11_Text_YasuPostBattle::
	.string "There's a fat POKéMON that comes\n"
	.string "down from the mountains.\p"
	.string "I bet it'd be strong if you can\n"
	.string "catch it.$"

TH13_Route11_Text_BernieIntro::
	.string "Watch out for live wires!$"

TH13_Route11_Text_BernieDefeat::
	.string "Whoa!\n"
	.string "You spark plug!$"

TH13_Route11_Text_BerniePostBattle::
	.string "Well, better get back to work.$"

TH13_Route11_Text_DaveIntro::
	.string "I raised my POKéMON carefully.\n"
	.string "They should be ready by now!$"

TH13_Route11_Text_DaveDefeat::
	.string "Bye-bye!\n"
	.string "Thank you, and good-bye!$"

TH13_Route11_Text_DavePostBattle::
	.string "Tch…\n"
	.string "I better go find stronger ones!$"

TH13_Route11_Text_DiglettsCave::
	.string "DIGLETT'S CAVE$"


TH13_Route11_EastGate::
    msgbox TH13_Route11_EastGateText, MSGBOX_NPC
    end
TH13_Route11_EastGateText:
    .string "A sleeping POKéMON is blocking\nROUTE 12 beyond this gate.\pPlease use the western road\nuntil the path is clear.$"
TH13_Cave_Miner::
    msgbox TH13_Cave_MinerText, MSGBOX_NPC
    end
TH13_Cave_MinerText:
    .string "DIGLETT have been digging more\nthan usual lately.\pNew tunnels keep appearing.\nSome tracks aren't DIGLETT tracks.$"
TH13_Cave_Hiker::
    msgbox TH13_Cave_HikerText, MSGBOX_NPC
    end
TH13_Cave_HikerText:
    .string "This tunnel reaches ROUTE 11.\nI saw two unfamiliar POKéMON below.\pWhat brought them here?\nI wish I knew.$"
TH13_Cave_Pair::
    lockall
    playmoncry SPECIES_PHANPY, CRY_MODE_NORMAL
    waitmoncry
    playmoncry SPECIES_WHISMUR, CRY_MODE_NORMAL
    waitmoncry
    msgbox TH13_Cave_PairText
    setvar VAR_0x8004, TH_RESEARCH_CAVE
    special TH_ScriptResearchObserve
    setvar VAR_0x8004, TH_PHOTO_CAVE
    call TH13_ResearchPhoto
    releaseall
    end
TH13_Cave_PairText:
    .string "PHANPY taps the tunnel floor.\nWHISMUR listens to the echoes.\pNeither seems ready to leave\nthis unfamiliar cave.$"

@ Route 9 retains native Kanto first battles and trainer sight lines.
TH13_Route9_Alicia::
    trainerbattle_single TRAINER_TH13_ROUTE9_ALICIA, TH13_Route9_Text_AliciaIntro, TH13_Route9_Text_AliciaDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH13_Route9_Alicia_Rematch
    msgbox TH13_Route9_Text_AliciaPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_Route9_Alicia_Rematch::
    trainerbattle_rematch TRAINER_TH13_ROUTE9_ALICIA, TH13_Route9_Text_AliciaIntro, TH13_Route9_Text_AliciaDefeat
    msgbox TH13_Route9_Text_AliciaPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_Route9_Jeremy::
    trainerbattle_single TRAINER_TH13_ROUTE9_JEREMY, TH13_Route9_Text_JeremyIntro, TH13_Route9_Text_JeremyDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH13_Route9_Jeremy_Rematch
    msgbox TH13_Route9_Text_JeremyPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_Route9_Jeremy_Rematch::
    trainerbattle_rematch TRAINER_TH13_ROUTE9_JEREMY, TH13_Route9_Text_JeremyIntro, TH13_Route9_Text_JeremyDefeat
    msgbox TH13_Route9_Text_JeremyPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_Route9_Alan::
    trainerbattle_single TRAINER_TH13_ROUTE9_ALAN, TH13_Route9_Text_AlanIntro, TH13_Route9_Text_AlanDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH13_Route9_Alan_Rematch
    msgbox TH13_Route9_Text_AlanPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_Route9_Alan_Rematch::
    trainerbattle_rematch TRAINER_TH13_ROUTE9_ALAN, TH13_Route9_Text_AlanIntro, TH13_Route9_Text_AlanDefeat
    msgbox TH13_Route9_Text_AlanPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_Route9_Chris::
    trainerbattle_single TRAINER_TH13_ROUTE9_CHRIS, TH13_Route9_Text_ChrisIntro, TH13_Route9_Text_ChrisDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH13_Route9_Chris_Rematch
    msgbox TH13_Route9_Text_ChrisPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_Route9_Chris_Rematch::
    trainerbattle_rematch TRAINER_TH13_ROUTE9_CHRIS, TH13_Route9_Text_ChrisIntro, TH13_Route9_Text_ChrisDefeat
    msgbox TH13_Route9_Text_ChrisPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_Route9_Brent::
    trainerbattle_single TRAINER_TH13_ROUTE9_BRENT, TH13_Route9_Text_BrentIntro, TH13_Route9_Text_BrentDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH13_Route9_Brent_Rematch
    msgbox TH13_Route9_Text_BrentPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_Route9_Brent_Rematch::
    trainerbattle_rematch TRAINER_TH13_ROUTE9_BRENT, TH13_Route9_Text_BrentIntro, TH13_Route9_Text_BrentDefeat
    msgbox TH13_Route9_Text_BrentPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_Route9_Conner::
    trainerbattle_single TRAINER_TH13_ROUTE9_CONNER, TH13_Route9_Text_ConnerIntro, TH13_Route9_Text_ConnerDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH13_Route9_Conner_Rematch
    msgbox TH13_Route9_Text_ConnerPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_Route9_Conner_Rematch::
    trainerbattle_rematch TRAINER_TH13_ROUTE9_CONNER, TH13_Route9_Text_ConnerIntro, TH13_Route9_Text_ConnerDefeat
    msgbox TH13_Route9_Text_ConnerPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_Route9_Brice::
    trainerbattle_single TRAINER_TH13_ROUTE9_BRICE, TH13_Route9_Text_BriceIntro, TH13_Route9_Text_BriceDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH13_Route9_Brice_Rematch
    msgbox TH13_Route9_Text_BricePostBattle, MSGBOX_AUTOCLOSE
    end
TH13_Route9_Brice_Rematch::
    trainerbattle_rematch TRAINER_TH13_ROUTE9_BRICE, TH13_Route9_Text_BriceIntro, TH13_Route9_Text_BriceDefeat
    msgbox TH13_Route9_Text_BricePostBattle, MSGBOX_AUTOCLOSE
    end
TH13_Route9_Caitlin::
    trainerbattle_single TRAINER_TH13_ROUTE9_CAITLIN, TH13_Route9_Text_CaitlinIntro, TH13_Route9_Text_CaitlinDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH13_Route9_Caitlin_Rematch
    msgbox TH13_Route9_Text_CaitlinPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_Route9_Caitlin_Rematch::
    trainerbattle_rematch TRAINER_TH13_ROUTE9_CAITLIN, TH13_Route9_Text_CaitlinIntro, TH13_Route9_Text_CaitlinDefeat
    msgbox TH13_Route9_Text_CaitlinPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_Route9_Drew::
    trainerbattle_single TRAINER_TH13_ROUTE9_DREW, TH13_Route9_Text_DrewIntro, TH13_Route9_Text_DrewDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH13_Route9_Drew_Rematch
    msgbox TH13_Route9_Text_DrewPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_Route9_Drew_Rematch::
    trainerbattle_rematch TRAINER_TH13_ROUTE9_DREW, TH13_Route9_Text_DrewIntro, TH13_Route9_Text_DrewDefeat
    msgbox TH13_Route9_Text_DrewPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_Route9_Item4::
    finditem ITEM_TM40
    end
TH13_Route9_Item5::
    finditem ITEM_BURN_HEAL
    end


TH13_Route9_EventScript_RouteSign::
	msgbox TH13_Route9_Text_RouteSign, MSGBOX_SIGN
	end

TH13_Route9_Text_AliciaIntro::
	.string "You have POKéMON with you!\n"
	.string "You're mine!$"

TH13_Route9_Text_AliciaDefeat::
	.string "You deceived me…$"

TH13_Route9_Text_AliciaPostBattle::
	.string "The tunnel coming up is pitch-black\n"
	.string "inside.\p"
	.string "You'll need FLASH to get through\n"
	.string "there.$"

TH13_Route9_Text_ChrisIntro::
	.string "Who's that walking there with those\n"
	.string "good-looking POKéMON?$"

TH13_Route9_Text_ChrisDefeat::
	.string "Out like a light!$"

TH13_Route9_Text_ChrisPostBattle::
	.string "Keep walking!$"

TH13_Route9_Text_DrewIntro::
	.string "I'm taking the ROCK TUNNEL to\n"
	.string "go to LAVENDER…$"

TH13_Route9_Text_DrewDefeat::
	.string "Can't measure up…$"

TH13_Route9_Text_DrewPostBattle::
	.string "Are you off to ROCK TUNNEL, too?$"

TH13_Route9_Text_CaitlinIntro::
	.string "Don't you dare patronize me!$"

TH13_Route9_Text_CaitlinDefeat::
	.string "No!\n"
	.string "You're too much.$"

TH13_Route9_Text_CaitlinPostBattle::
	.string "You're obviously talented.\n"
	.string "Good luck to you!$"

TH13_Route9_Text_JeremyIntro::
	.string "Bwahaha!\n"
	.string "Great! I was bored, eh!$"

TH13_Route9_Text_JeremyDefeat::
	.string "Keep it coming, eh!\p"
	.string "Oh wait.\n"
	.string "I'm out of POKéMON!$"

TH13_Route9_Text_JeremyPostBattle::
	.string "You sure had guts standing up to\n"
	.string "me there, eh?$"

TH13_Route9_Text_BriceIntro::
	.string "Hahaha!\n"
	.string "Aren't you a little toughie!$"

TH13_Route9_Text_BriceDefeat::
	.string "What's that?$"

TH13_Route9_Text_BricePostBattle::
	.string "Hahaha!\n"
	.string "Kids should be tough!$"

TH13_Route9_Text_BrentIntro::
	.string "I got up early every day to raise\n"
	.string "my POKéMON from cocoons!$"

TH13_Route9_Text_BrentDefeat::
	.string "WHAT?\p"
	.string "What a total waste of time!$"

TH13_Route9_Text_BrentPostBattle::
	.string "I have to collect more than bugs\n"
	.string "to get stronger…$"

TH13_Route9_Text_AlanIntro::
	.string "Hahahaha!\n"
	.string "Bring it on!$"

TH13_Route9_Text_AlanDefeat::
	.string "Hahahaha!\n"
	.string "You beat me fair!$"

TH13_Route9_Text_AlanPostBattle::
	.string "Hahahaha!\n"
	.string "Us hearty guys always laugh!$"

TH13_Route9_Text_ConnerIntro::
	.string "Go, my super BUG POKéMON!$"

TH13_Route9_Text_ConnerDefeat::
	.string "My bugs…$"

TH13_Route9_Text_ConnerPostBattle::
	.string "If you don't like BUG POKéMON,\n"
	.string "you bug me!$"

TH13_Route9_Text_RouteSign::
	.string "ROUTE 9\n"
	.string "CERULEAN CITY - ROCK TUNNEL$"

