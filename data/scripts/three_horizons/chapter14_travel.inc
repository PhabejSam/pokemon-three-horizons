@ Authored PT14 travel. Donor text/first parties remain separate from temporary rematches.

TH14_Route8_Text_AidanIntro::
	.string "You look good at POKéMON, but how\n"
	.string "is your chemistry grade?$"


TH14_Route8_Text_AidanDefeat::
	.string "Ow!\n"
	.string "Meltdown!$"


TH14_Route8_Text_AidanPostBattle::
	.string "I am better at school than this!$"


TH14_Route8_Text_StanIntro::
	.string "All right!\n"
	.string "Let's play a game!$"


TH14_Route8_Text_StanDefeat::
	.string "Drat!\n"
	.string "Came up short!$"


TH14_Route8_Text_StanPostBattle::
	.string "Things didn't work today.$"


TH14_Route8_Text_GlennIntro::
	.string "You should be informed.\n"
	.string "You need strategy to win at this!$"


TH14_Route8_Text_GlennDefeat::
	.string "It's not logical!$"


TH14_Route8_Text_GlennPostBattle::
	.string "Go with GRIMER first…and…\n"
	.string "…and…then…$"


TH14_Route8_Text_PaigeIntro::
	.string "I like NIDORAN, so I collect them!$"


TH14_Route8_Text_PaigeDefeat::
	.string "Why?\n"
	.string "Why??$"


TH14_Route8_Text_PaigePostBattle::
	.string "When POKéMON grow up, they get\n"
	.string "ugly! They shouldn't evolve.$"


TH14_Route8_Text_LeslieIntro::
	.string "School is fun, but so are POKéMON.$"


TH14_Route8_Text_LeslieDefeat::
	.string "You made it clear to me that\n"
	.string "I should stick with school.$"


TH14_Route8_Text_LesliePostBattle::
	.string "I was planning on getting some\n"
	.string "fresh air for a change, but…\p"
	.string "We're stuck here because of the\n"
	.string "gates at SAFFRON.$"


TH14_Route8_Text_AndreaIntro::
	.string "MEOWTH is so cute, meow, meow,\n"
	.string "meow!$"


TH14_Route8_Text_AndreaDefeat::
	.string "Meeeeyow!$"


TH14_Route8_Text_AndreaPostBattle::
	.string "I think PIDGEY and RATTATA are\n"
	.string "cute, too!$"


TH14_Route8_Text_MeganIntro::
	.string "We must look silly standing here\n"
	.string "like this.$"


TH14_Route8_Text_MeganDefeat::
	.string "Look what you did to my poor, cute\n"
	.string "POKéMON!$"


TH14_Route8_Text_MeganPostBattle::
	.string "SAFFRON's gatekeeper won't let us\n"
	.string "go through.\p"
	.string "I know he's doing his job, but I\n"
	.string "think he's mean.$"


TH14_Route8_Text_RichIntro::
	.string "I'm a rambling, gaming dude!$"


TH14_Route8_Text_RichDefeat::
	.string "Missed the big chance!$"


TH14_Route8_Text_RichPostBattle::
	.string "Playing games and POKéMON are like\n"
	.string "eating peanuts! I just can't stop!$"


TH14_Route8_Text_JuliaIntro::
	.string "What's a cute, round, and fluffy\n"
	.string "POKéMON?$"


TH14_Route8_Text_JuliaDefeat::
	.string "Stop!\p"
	.string "Don't be so mean to my CLEFAIRY!$"


TH14_Route8_Text_JuliaPostBattle::
	.string "I read that CLEFAIRY evolves when\n"
	.string "it's exposed to a MOON STONE.\p"
	.string "I read that in a POKéMON JOURNAL.\n"
	.string "I wonder if it's true?$"


TH14_Route8_Text_UndergroundPathSign::
	.string "UNDERGROUND PATH\n"
	.string "CELADON CITY - LAVENDER TOWN$"


TH14_Route8_Text_EliIntro::
	.string "ELI: Twin power is fantastic.\n"
	.string "Did you know?$"


TH14_Route8_Text_EliDefeat::
	.string "ELI: But…\n"
	.string "We used our twin power…$"


TH14_Route8_Text_EliPostBattle::
	.string "ELI: I caught my POKéMON with\n"
	.string "ANNE!$"


TH14_Route8_Text_EliNotEnoughMons::
	.string "ELI: We can't battle if you don't\n"
	.string "have two POKéMON.$"


TH14_Route8_Text_AnneIntro::
	.string "ANNE: We'll shock you with our twin\n"
	.string "power!$"


TH14_Route8_Text_AnneDefeat::
	.string "ANNE: Our twin power…$"


TH14_Route8_Text_AnnePostBattle::
	.string "ANNE: I'm raising POKéMON with\n"
	.string "ELI.$"


TH14_Route8_Text_AnneNotEnoughMons::
	.string "ANNE: Hi, hi! Let's battle!\n"
	.string "But bring two POKéMON.$"


TH14_Route8_Text_RicardoIntro::
	.string "My bike's acting up, man.$"


TH14_Route8_Text_RicardoDefeat::
	.string "Aww, man.\n"
	.string "I'm not into this.$"


TH14_Route8_Text_RicardoPostBattle::
	.string "I got grass caught up in my\n"
	.string "spokes, man.$"


TH14_Route8_Text_JarenIntro::
	.string "Clear the way, or I'll run you\n"
	.string "down!$"


TH14_Route8_Text_JarenDefeat::
	.string "You for real, kid?$"


TH14_Route8_Text_JarenPostBattle::
	.string "Don't think you're all special and\n"
	.string "all just because of this.$"

TH14_Route8_Julia::
    trainerbattle_single TRAINER_TH14_ROUTE8_JULIA, TH14_Route8_Text_JuliaIntro, TH14_Route8_Text_JuliaDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH14_Route8_Julia_Rematch
    msgbox TH14_Route8_Text_JuliaPostBattle, MSGBOX_AUTOCLOSE
    end
TH14_Route8_Julia_Rematch::
    trainerbattle_rematch TRAINER_TH14_ROUTE8_JULIA, TH14_Route8_Text_JuliaIntro, TH14_Route8_Text_JuliaDefeat
    msgbox TH14_Route8_Text_JuliaPostBattle, MSGBOX_AUTOCLOSE
    end

TH14_Route8_Rich::
    trainerbattle_single TRAINER_TH14_ROUTE8_RICH, TH14_Route8_Text_RichIntro, TH14_Route8_Text_RichDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH14_Route8_Rich_Rematch
    msgbox TH14_Route8_Text_RichPostBattle, MSGBOX_AUTOCLOSE
    end
TH14_Route8_Rich_Rematch::
    trainerbattle_rematch TRAINER_TH14_ROUTE8_RICH, TH14_Route8_Text_RichIntro, TH14_Route8_Text_RichDefeat
    msgbox TH14_Route8_Text_RichPostBattle, MSGBOX_AUTOCLOSE
    end

TH14_Route8_Glenn::
    trainerbattle_single TRAINER_TH14_ROUTE8_GLENN, TH14_Route8_Text_GlennIntro, TH14_Route8_Text_GlennDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH14_Route8_Glenn_Rematch
    msgbox TH14_Route8_Text_GlennPostBattle, MSGBOX_AUTOCLOSE
    end
TH14_Route8_Glenn_Rematch::
    trainerbattle_rematch TRAINER_TH14_ROUTE8_GLENN, TH14_Route8_Text_GlennIntro, TH14_Route8_Text_GlennDefeat
    msgbox TH14_Route8_Text_GlennPostBattle, MSGBOX_AUTOCLOSE
    end

TH14_Route8_Paige::
    trainerbattle_single TRAINER_TH14_ROUTE8_PAIGE, TH14_Route8_Text_PaigeIntro, TH14_Route8_Text_PaigeDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH14_Route8_Paige_Rematch
    msgbox TH14_Route8_Text_PaigePostBattle, MSGBOX_AUTOCLOSE
    end
TH14_Route8_Paige_Rematch::
    trainerbattle_rematch TRAINER_TH14_ROUTE8_PAIGE, TH14_Route8_Text_PaigeIntro, TH14_Route8_Text_PaigeDefeat
    msgbox TH14_Route8_Text_PaigePostBattle, MSGBOX_AUTOCLOSE
    end

TH14_Route8_Leslie::
    trainerbattle_single TRAINER_TH14_ROUTE8_LESLIE, TH14_Route8_Text_LeslieIntro, TH14_Route8_Text_LeslieDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH14_Route8_Leslie_Rematch
    msgbox TH14_Route8_Text_LesliePostBattle, MSGBOX_AUTOCLOSE
    end
TH14_Route8_Leslie_Rematch::
    trainerbattle_rematch TRAINER_TH14_ROUTE8_LESLIE, TH14_Route8_Text_LeslieIntro, TH14_Route8_Text_LeslieDefeat
    msgbox TH14_Route8_Text_LesliePostBattle, MSGBOX_AUTOCLOSE
    end

TH14_Route8_Andrea::
    trainerbattle_single TRAINER_TH14_ROUTE8_ANDREA, TH14_Route8_Text_AndreaIntro, TH14_Route8_Text_AndreaDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH14_Route8_Andrea_Rematch
    msgbox TH14_Route8_Text_AndreaPostBattle, MSGBOX_AUTOCLOSE
    end
TH14_Route8_Andrea_Rematch::
    trainerbattle_rematch TRAINER_TH14_ROUTE8_ANDREA, TH14_Route8_Text_AndreaIntro, TH14_Route8_Text_AndreaDefeat
    msgbox TH14_Route8_Text_AndreaPostBattle, MSGBOX_AUTOCLOSE
    end

TH14_Route8_Megan::
    trainerbattle_single TRAINER_TH14_ROUTE8_MEGAN, TH14_Route8_Text_MeganIntro, TH14_Route8_Text_MeganDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH14_Route8_Megan_Rematch
    msgbox TH14_Route8_Text_MeganPostBattle, MSGBOX_AUTOCLOSE
    end
TH14_Route8_Megan_Rematch::
    trainerbattle_rematch TRAINER_TH14_ROUTE8_MEGAN, TH14_Route8_Text_MeganIntro, TH14_Route8_Text_MeganDefeat
    msgbox TH14_Route8_Text_MeganPostBattle, MSGBOX_AUTOCLOSE
    end

TH14_Route8_Stan::
    trainerbattle_single TRAINER_TH14_ROUTE8_STAN, TH14_Route8_Text_StanIntro, TH14_Route8_Text_StanDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH14_Route8_Stan_Rematch
    msgbox TH14_Route8_Text_StanPostBattle, MSGBOX_AUTOCLOSE
    end
TH14_Route8_Stan_Rematch::
    trainerbattle_rematch TRAINER_TH14_ROUTE8_STAN, TH14_Route8_Text_StanIntro, TH14_Route8_Text_StanDefeat
    msgbox TH14_Route8_Text_StanPostBattle, MSGBOX_AUTOCLOSE
    end

TH14_Route8_Aidan::
    trainerbattle_single TRAINER_TH14_ROUTE8_AIDAN, TH14_Route8_Text_AidanIntro, TH14_Route8_Text_AidanDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH14_Route8_Aidan_Rematch
    msgbox TH14_Route8_Text_AidanPostBattle, MSGBOX_AUTOCLOSE
    end
TH14_Route8_Aidan_Rematch::
    trainerbattle_rematch TRAINER_TH14_ROUTE8_AIDAN, TH14_Route8_Text_AidanIntro, TH14_Route8_Text_AidanDefeat
    msgbox TH14_Route8_Text_AidanPostBattle, MSGBOX_AUTOCLOSE
    end

TH14_Route8_Eli::
    trainerbattle_double TRAINER_TH14_ROUTE8_ELI_ANNE, TH14_Route8_Text_EliIntro, TH14_Route8_Text_EliDefeat, TH14_Route8_Text_EliNotEnoughMons
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH14_Route8_Eli_Rematch
    msgbox TH14_Route8_Text_EliPostBattle, MSGBOX_AUTOCLOSE
    end
TH14_Route8_Eli_Rematch::
    trainerbattle_rematch_double TRAINER_TH14_ROUTE8_ELI_ANNE, TH14_Route8_Text_EliIntro, TH14_Route8_Text_EliDefeat, TH14_Route8_Text_EliNotEnoughMons
    msgbox TH14_Route8_Text_EliPostBattle, MSGBOX_AUTOCLOSE
    end

TH14_Route8_Anne::
    trainerbattle_double TRAINER_TH14_ROUTE8_ELI_ANNE, TH14_Route8_Text_AnneIntro, TH14_Route8_Text_AnneDefeat, TH14_Route8_Text_AnneNotEnoughMons
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH14_Route8_Anne_Rematch
    msgbox TH14_Route8_Text_AnnePostBattle, MSGBOX_AUTOCLOSE
    end
TH14_Route8_Anne_Rematch::
    trainerbattle_rematch_double TRAINER_TH14_ROUTE8_ELI_ANNE, TH14_Route8_Text_AnneIntro, TH14_Route8_Text_AnneDefeat, TH14_Route8_Text_AnneNotEnoughMons
    msgbox TH14_Route8_Text_AnnePostBattle, MSGBOX_AUTOCLOSE
    end

TH14_Route8_Ricardo::
    trainerbattle_single TRAINER_TH14_ROUTE8_RICARDO, TH14_Route8_Text_RicardoIntro, TH14_Route8_Text_RicardoDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH14_Route8_Ricardo_Rematch
    msgbox TH14_Route8_Text_RicardoPostBattle, MSGBOX_AUTOCLOSE
    end
TH14_Route8_Ricardo_Rematch::
    trainerbattle_rematch TRAINER_TH14_ROUTE8_RICARDO, TH14_Route8_Text_RicardoIntro, TH14_Route8_Text_RicardoDefeat
    msgbox TH14_Route8_Text_RicardoPostBattle, MSGBOX_AUTOCLOSE
    end

TH14_Route8_Jaren::
    trainerbattle_single TRAINER_TH14_ROUTE8_JAREN, TH14_Route8_Text_JarenIntro, TH14_Route8_Text_JarenDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH14_Route8_Jaren_Rematch
    msgbox TH14_Route8_Text_JarenPostBattle, MSGBOX_AUTOCLOSE
    end
TH14_Route8_Jaren_Rematch::
    trainerbattle_rematch TRAINER_TH14_ROUTE8_JAREN, TH14_Route8_Text_JarenIntro, TH14_Route8_Text_JarenDefeat
    msgbox TH14_Route8_Text_JarenPostBattle, MSGBOX_AUTOCLOSE
    end

TH14_UndergroundSign::
    msgbox TH14_Route8_Text_UndergroundPathSign, MSGBOX_SIGN
    end
TH14_UndergroundEast::
    msgbox TH14_UndergroundEastText, MSGBOX_NPC
    end
TH14_UndergroundWest::
    msgbox TH14_UndergroundWestText, MSGBOX_NPC
    end
TH14_SaffronClosed::
    msgbox TH14_SaffronClosedText, MSGBOX_NPC
    end
TH14_GuardWest::
    specialvar VAR_RESULT, GetPlayerFacingDirection
    goto_if_ne VAR_RESULT, DIR_WEST, TH14_GuardEnd
    lockall
    msgbox TH14_SaffronClosedText
    closemessage
    applymovement OBJ_EVENT_ID_PLAYER, TH14_GuardStepRight
    waitmovement 0
    releaseall
    end
TH14_GuardEast::
    specialvar VAR_RESULT, GetPlayerFacingDirection
    goto_if_ne VAR_RESULT, DIR_EAST, TH14_GuardEnd
    lockall
    msgbox TH14_SaffronClosedText
    closemessage
    applymovement OBJ_EVENT_ID_PLAYER, TH14_GuardStepLeft
    waitmovement 0
    releaseall
TH14_GuardEnd:
    end
TH14_GuardStepRight:
    walk_right
    step_end
TH14_GuardStepLeft:
    walk_left
    step_end
TH14_UndergroundEastText:
    .string "The DEPARTMENT STORE in CELADON\nhas a great selection.\pDo you go there very often?$"
TH14_UndergroundWestText:
    .string "This path goes under SAFFRON.\nIts city gates are still closed.\pThe other end leads to ROUTE 8,\njust west of LAVENDER.$"
TH14_SaffronClosedText:
    .string "SAFFRON is closed to visitors.\nThe UNDERGROUND PATH is open.\pFollow it between LAVENDER\nand CELADON.$"
