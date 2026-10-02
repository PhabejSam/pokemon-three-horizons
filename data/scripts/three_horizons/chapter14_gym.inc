@ PT14 Celadon Gym: independent victory, badge and reusable TM receipt.

TH14_CeladonCity_Gym_EventScript_Kay::
    trainerbattle_single TRAINER_TH14_GYM_KAY, TH14_CeladonCity_Gym_Text_KayIntro, TH14_CeladonCity_Gym_Text_KayDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH14_CeladonCity_Gym_EventScript_Kay_Rematch
    msgbox TH14_CeladonCity_Gym_Text_KayPostBattle, MSGBOX_AUTOCLOSE
    end
TH14_CeladonCity_Gym_EventScript_Kay_Rematch::
    trainerbattle_rematch TRAINER_TH14_GYM_KAY, TH14_CeladonCity_Gym_Text_KayIntro, TH14_CeladonCity_Gym_Text_KayDefeat
    msgbox TH14_CeladonCity_Gym_Text_KayPostBattle, MSGBOX_AUTOCLOSE
    end

TH14_CeladonCity_Gym_Text_KayIntro::
	.string "I should tell you about this GYM.\p"
	.string "Only real ladies are allowed in\n"
	.string "here!$"

TH14_CeladonCity_Gym_Text_KayDefeat::
	.string "You're too rough!$"

TH14_CeladonCity_Gym_Text_KayPostBattle::
	.string "Bleaah!\n"
	.string "I hope ERIKA wipes you out!$"

TH14_CeladonCity_Gym_EventScript_Bridget::
    trainerbattle_single TRAINER_TH14_GYM_BRIDGET, TH14_CeladonCity_Gym_Text_BridgetIntro, TH14_CeladonCity_Gym_Text_BridgetDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH14_CeladonCity_Gym_EventScript_Bridget_Rematch
    msgbox TH14_CeladonCity_Gym_Text_BridgetPostBattle, MSGBOX_AUTOCLOSE
    end
TH14_CeladonCity_Gym_EventScript_Bridget_Rematch::
    trainerbattle_rematch TRAINER_TH14_GYM_BRIDGET, TH14_CeladonCity_Gym_Text_BridgetIntro, TH14_CeladonCity_Gym_Text_BridgetDefeat
    msgbox TH14_CeladonCity_Gym_Text_BridgetPostBattle, MSGBOX_AUTOCLOSE
    end

TH14_CeladonCity_Gym_Text_BridgetIntro::
	.string "Oh, welcome.\n"
	.string "I was getting bored.$"

TH14_CeladonCity_Gym_Text_BridgetDefeat::
	.string "My makeup!$"

TH14_CeladonCity_Gym_Text_BridgetPostBattle::
	.string "GRASS-type POKéMON are tough\n"
	.string "against the WATER type.\p"
	.string "They also have an edge on ROCK-\n"
	.string "and GROUND-type POKéMON.$"

TH14_CeladonCity_Gym_EventScript_Tina::
    trainerbattle_single TRAINER_TH14_GYM_TINA, TH14_CeladonCity_Gym_Text_TinaIntro, TH14_CeladonCity_Gym_Text_TinaDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH14_CeladonCity_Gym_EventScript_Tina_Rematch
    msgbox TH14_CeladonCity_Gym_Text_TinaPostBattle, MSGBOX_AUTOCLOSE
    end
TH14_CeladonCity_Gym_EventScript_Tina_Rematch::
    trainerbattle_rematch TRAINER_TH14_GYM_TINA, TH14_CeladonCity_Gym_Text_TinaIntro, TH14_CeladonCity_Gym_Text_TinaDefeat
    msgbox TH14_CeladonCity_Gym_Text_TinaPostBattle, MSGBOX_AUTOCLOSE
    end

TH14_CeladonCity_Gym_Text_TinaIntro::
	.string "…Weren't you peeking in here\n"
	.string "earlier?$"

TH14_CeladonCity_Gym_Text_TinaDefeat::
	.string "You're an eye-opener!$"

TH14_CeladonCity_Gym_Text_TinaPostBattle::
	.string "Oh, you were looking at ERIKA…\n"
	.string "You weren't looking at me…$"

TH14_CeladonCity_Gym_EventScript_Tamia::
    trainerbattle_single TRAINER_TH14_GYM_TAMIA, TH14_CeladonCity_Gym_Text_TamiaIntro, TH14_CeladonCity_Gym_Text_TamiaDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH14_CeladonCity_Gym_EventScript_Tamia_Rematch
    msgbox TH14_CeladonCity_Gym_Text_TamiaPostBattle, MSGBOX_AUTOCLOSE
    end
TH14_CeladonCity_Gym_EventScript_Tamia_Rematch::
    trainerbattle_rematch TRAINER_TH14_GYM_TAMIA, TH14_CeladonCity_Gym_Text_TamiaIntro, TH14_CeladonCity_Gym_Text_TamiaDefeat
    msgbox TH14_CeladonCity_Gym_Text_TamiaPostBattle, MSGBOX_AUTOCLOSE
    end

TH14_CeladonCity_Gym_Text_TamiaIntro::
	.string "Look, look!\n"
	.string "See my POKéMON!\p"
	.string "I like the GRASS type.\n"
	.string "I like how they're easy to raise.$"

TH14_CeladonCity_Gym_Text_TamiaDefeat::
	.string "No!$"

TH14_CeladonCity_Gym_Text_TamiaPostBattle::
	.string "We only use GRASS-type POKéMON at\n"
	.string "our GYM.\p"
	.string "Why? We also use them for making\n"
	.string "flower arrangements!$"

TH14_CeladonCity_Gym_EventScript_Lori::
    trainerbattle_single TRAINER_TH14_GYM_LORI, TH14_CeladonCity_Gym_Text_LoriIntro, TH14_CeladonCity_Gym_Text_LoriDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH14_CeladonCity_Gym_EventScript_Lori_Rematch
    msgbox TH14_CeladonCity_Gym_Text_LoriPostBattle, MSGBOX_AUTOCLOSE
    end
TH14_CeladonCity_Gym_EventScript_Lori_Rematch::
    trainerbattle_rematch TRAINER_TH14_GYM_LORI, TH14_CeladonCity_Gym_Text_LoriIntro, TH14_CeladonCity_Gym_Text_LoriDefeat
    msgbox TH14_CeladonCity_Gym_Text_LoriPostBattle, MSGBOX_AUTOCLOSE
    end

TH14_CeladonCity_Gym_Text_LoriIntro::
	.string "Pleased to meet you.\n"
	.string "My hobby is POKéMON training.$"

TH14_CeladonCity_Gym_Text_LoriDefeat::
	.string "Oh!\n"
	.string "Splendid!$"

TH14_CeladonCity_Gym_Text_LoriPostBattle::
	.string "I have a blind date coming up.\n"
	.string "I have to learn to be polite,\l"
	.string "especially if I have to battle.$"

TH14_CeladonCity_Gym_EventScript_Lisa::
    trainerbattle_single TRAINER_TH14_GYM_LISA, TH14_CeladonCity_Gym_Text_LisaIntro, TH14_CeladonCity_Gym_Text_LisaDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH14_CeladonCity_Gym_EventScript_Lisa_Rematch
    msgbox TH14_CeladonCity_Gym_Text_LisaPostBattle, MSGBOX_AUTOCLOSE
    end
TH14_CeladonCity_Gym_EventScript_Lisa_Rematch::
    trainerbattle_rematch TRAINER_TH14_GYM_LISA, TH14_CeladonCity_Gym_Text_LisaIntro, TH14_CeladonCity_Gym_Text_LisaDefeat
    msgbox TH14_CeladonCity_Gym_Text_LisaPostBattle, MSGBOX_AUTOCLOSE
    end

TH14_CeladonCity_Gym_Text_LisaIntro::
	.string "Oh, hey!\p"
	.string "We don't like BUG- or FIRE-type\n"
	.string "POKéMON in here!$"

TH14_CeladonCity_Gym_Text_LisaDefeat::
	.string "Oh!\n"
	.string "You!$"

TH14_CeladonCity_Gym_Text_LisaPostBattle::
	.string "Our LEADER ERIKA might be quiet,\n"
	.string "but she's famous around here.$"

TH14_CeladonCity_Gym_EventScript_Mary::
    trainerbattle_single TRAINER_TH14_GYM_MARY, TH14_CeladonCity_Gym_Text_MaryIntro, TH14_CeladonCity_Gym_Text_MaryDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH14_CeladonCity_Gym_EventScript_Mary_Rematch
    msgbox TH14_CeladonCity_Gym_Text_MaryPostBattle, MSGBOX_AUTOCLOSE
    end
TH14_CeladonCity_Gym_EventScript_Mary_Rematch::
    trainerbattle_rematch TRAINER_TH14_GYM_MARY, TH14_CeladonCity_Gym_Text_MaryIntro, TH14_CeladonCity_Gym_Text_MaryDefeat
    msgbox TH14_CeladonCity_Gym_Text_MaryPostBattle, MSGBOX_AUTOCLOSE
    end

TH14_CeladonCity_Gym_Text_MaryIntro::
	.string "Welcome to CELADON GYM!\p"
	.string "You'd better not underestimate\n"
	.string "the nice ladies here.$"

TH14_CeladonCity_Gym_Text_MaryDefeat::
	.string "Oh!\n"
	.string "Beaten!$"

TH14_CeladonCity_Gym_Text_MaryPostBattle::
	.string "I didn't bring my best POKéMON.\n"
	.string "Wait until next time!$"

TH14_CeladonCity_Gym_EventScript_Erika::
    trainerbattle_single TRAINER_TH14_ERIKA, TH14_Erika_Intro, TH14_Erika_Defeat, TH14_Erika_Victory, NO_MUSIC
    goto TH14_Erika_Victory

TH14_Erika_Victory::
    goto_if_set FLAG_BADGE04_GET, TH14_Erika_Reward
    setflag FLAG_BADGE04_GET
    playfanfare MUS_OBTAIN_BADGE
    msgbox TH14_Erika_Badge
    waitfanfare
TH14_Erika_Reward::
    goto_if_set FLAG_TH14_ERIKA_TM, TH14_Erika_After
    setvar VAR_0x8004, ITEM_TM19
    setvar VAR_0x8005, FLAG_TH14_ERIKA_TM
    special TH14_ScriptGiveUniqueItem
    goto_if_eq VAR_RESULT, 0, TH14_Erika_NoRoom
    goto_if_eq VAR_RESULT, 2, TH14_Erika_After
    playfanfare MUS_OBTAIN_TMHM
    msgbox TH14_Erika_TMReceived
    waitfanfare
TH14_Erika_After:
    msgbox TH14_Erika_AfterText
    releaseall
    end
TH14_Erika_NoRoom:
    msgbox TH14_Erika_NoRoomText
    releaseall
    end

TH14_CeladonCity_Gym_EventScript_GymStatue::
    lockall
    goto_if_set FLAG_BADGE04_GET, TH14_Erika_StatueWon
    msgbox TH14_Erika_StatueText
    releaseall
    end
TH14_Erika_StatueWon:
    msgbox TH14_Erika_StatueWonText
    releaseall
    end

TH14_Erika_GuideWon::
    msgbox TH14_Erika_GuideWonText, MSGBOX_NPC
    end

TH14_Erika_Intro:
    .string "Hello... Welcome to CELADON GYM.\nMy name is ERIKA.\pI study flower arranging with my\nGRASS-type POKéMON.\pYou wish to challenge us?\nVery well. Let us begin!{PLAY_BGM MUS_RG_ENCOUNTER_GYM_LEADER}$"
TH14_Erika_Defeat:
    .string "Oh! I concede defeat.\nYou are remarkably strong.$"
TH14_Erika_Badge:
    .string "{PLAYER} received the\nRAINBOW BADGE from ERIKA!$"
TH14_Erika_TMReceived:
    .string "{PLAYER} received TM19\nfrom ERIKA!$"
TH14_Erika_AfterText:
    .string "TM19 teaches GIGA DRAIN.\nIt restores HP as it deals damage.\pYour TMs are reusable. May your\npartners continue to flourish!$"
TH14_Erika_NoRoomText:
    .string "Your RAINBOW BADGE is yours.\nPlease make room for my TM,\land come back to see me.$"
TH14_Erika_StatueText:
    .string "CELADON POKéMON GYM\nLEADER: ERIKA\pWINNING TRAINERS:\n{RIVAL}$"
TH14_Erika_StatueWonText:
    .string "CELADON POKéMON GYM\nLEADER: ERIKA\pWINNING TRAINERS:\n{RIVAL}, {PLAYER}$"
TH14_Erika_GuideWonText:
    .string "You beat ERIKA! That RAINBOW\nBADGE shows how much your team\lhas grown, champ!$"
