@ Native Kanto first parties, ladders and trainer sight lines.
TH13_Route10_Carol::
    trainerbattle_single TRAINER_TH13_ROUTE10_CAROL, TH13_Route10_Text_CarolIntro, TH13_Route10_Text_CarolDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH13_Route10_Carol_Rematch
    msgbox TH13_Route10_Text_CarolPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_Route10_Carol_Rematch::
    trainerbattle_rematch TRAINER_TH13_ROUTE10_CAROL, TH13_Route10_Text_CarolIntro, TH13_Route10_Text_CarolDefeat
    msgbox TH13_Route10_Text_CarolPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_Route10_Clark::
    trainerbattle_single TRAINER_TH13_ROUTE10_CLARK, TH13_Route10_Text_ClarkIntro, TH13_Route10_Text_ClarkDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH13_Route10_Clark_Rematch
    msgbox TH13_Route10_Text_ClarkPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_Route10_Clark_Rematch::
    trainerbattle_rematch TRAINER_TH13_ROUTE10_CLARK, TH13_Route10_Text_ClarkIntro, TH13_Route10_Text_ClarkDefeat
    msgbox TH13_Route10_Text_ClarkPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_Route10_Herman::
    trainerbattle_single TRAINER_TH13_ROUTE10_HERMAN, TH13_Route10_Text_HermanIntro, TH13_Route10_Text_HermanDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH13_Route10_Herman_Rematch
    msgbox TH13_Route10_Text_HermanPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_Route10_Herman_Rematch::
    trainerbattle_rematch TRAINER_TH13_ROUTE10_HERMAN, TH13_Route10_Text_HermanIntro, TH13_Route10_Text_HermanDefeat
    msgbox TH13_Route10_Text_HermanPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_Route10_Trent::
    trainerbattle_single TRAINER_TH13_ROUTE10_TRENT, TH13_Route10_Text_TrentIntro, TH13_Route10_Text_TrentDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH13_Route10_Trent_Rematch
    msgbox TH13_Route10_Text_TrentPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_Route10_Trent_Rematch::
    trainerbattle_rematch TRAINER_TH13_ROUTE10_TRENT, TH13_Route10_Text_TrentIntro, TH13_Route10_Text_TrentDefeat
    msgbox TH13_Route10_Text_TrentPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_Route10_Mark::
    trainerbattle_single TRAINER_TH13_ROUTE10_MARK, TH13_Route10_Text_MarkIntro, TH13_Route10_Text_MarkDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH13_Route10_Mark_Rematch
    msgbox TH13_Route10_Text_MarkPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_Route10_Mark_Rematch::
    trainerbattle_rematch TRAINER_TH13_ROUTE10_MARK, TH13_Route10_Text_MarkIntro, TH13_Route10_Text_MarkDefeat
    msgbox TH13_Route10_Text_MarkPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_Route10_Heidi::
    trainerbattle_single TRAINER_TH13_ROUTE10_HEIDI, TH13_Route10_Text_HeidiIntro, TH13_Route10_Text_HeidiDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH13_Route10_Heidi_Rematch
    msgbox TH13_Route10_Text_HeidiPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_Route10_Heidi_Rematch::
    trainerbattle_rematch TRAINER_TH13_ROUTE10_HEIDI, TH13_Route10_Text_HeidiIntro, TH13_Route10_Text_HeidiDefeat
    msgbox TH13_Route10_Text_HeidiPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_Route10_Text_MarkIntro::
	.string "Wow, you came all the way here?\n"
	.string "Maybe you're a POKéMANIAC, too?\l"
	.string "Want to see my collection?$"

TH13_Route10_Text_MarkDefeat::
	.string "Humph.\n"
	.string "I'm not angry!$"

TH13_Route10_Text_MarkPostBattle::
	.string "I have more rare POKéMON at home!$"

TH13_Route10_Text_ClarkIntro::
	.string "Ha-hahah-ah-ha!$"

TH13_Route10_Text_ClarkDefeat::
	.string "Ha-haha!\n"
	.string "Not laughing!\l"
	.string "Ha-hay fever! Haha-ha-choo!$"

TH13_Route10_Text_ClarkPostBattle::
	.string "Haha-ha-choo!\n"
	.string "Ha-choo!\l"
	.string "Snort! Snivel!$"

TH13_Route10_Text_HermanIntro::
	.string "Hi, kid!\n"
	.string "Want to see my POKéMON?$"

TH13_Route10_Text_HermanDefeat::
	.string "Oh, no!\n"
	.string "My POKéMON!$"

TH13_Route10_Text_HermanPostBattle::
	.string "I don't like you.\n"
	.string "I don't like anyone better than me!$"

TH13_Route10_Text_HeidiIntro::
	.string "I've been out at a POKéMON GYM\n"
	.string "a few times.\p"
	.string "…But I always lose.$"

TH13_Route10_Text_HeidiDefeat::
	.string "Ohh!\n"
	.string "After all my training!$"

TH13_Route10_Text_HeidiPostBattle::
	.string "I noticed some POKéMANIACS\n"
	.string "prowling around.\p"
	.string "Can you imagine? Them?\n"
	.string "Up here in the mountains?$"

TH13_Route10_Text_TrentIntro::
	.string "Ah!\n"
	.string "This mountain air is delicious!$"

TH13_Route10_Text_TrentDefeat::
	.string "That cleared my head!$"

TH13_Route10_Text_TrentPostBattle::
	.string "I feel bloated on mountain air!$"

TH13_Route10_Text_CarolIntro::
	.string "I'm feeling a bit faint.\n"
	.string "I haven't hiked in some time.$"

TH13_Route10_Text_CarolDefeat::
	.string "I'm too tired.\n"
	.string "I wasn't up for it.$"

TH13_Route10_Text_CarolPostBattle::
	.string "The POKéMON here in the mountains\n"
	.string "are so chunky…\p"
	.string "I wish there were pink POKéMON\n"
	.string "with a floral pattern!$"

TH13_Route10_Text_RockTunnelDetourToLavender::
	.string "ROCK TUNNEL\n"
	.string "Detour to LAVENDER TOWN$"

TH13_Route10_Text_RockTunnel::
	.string "ROCK TUNNEL$"

TH13_Route10_Text_PowerPlant::
	.string "POWER PLANT$"

TH13_Route10_EventScript_SouthRockTunnelSign::
	msgbox TH13_Route10_Text_RockTunnel, MSGBOX_SIGN
	end

TH13_Route10_EventScript_PowerPlantSign::
	msgbox TH13_Route10_Text_PowerPlant, MSGBOX_SIGN
	end

TH13_Route10_EventScript_NorthRockTunnelSign::
	msgbox TH13_Route10_Text_RockTunnelDetourToLavender, MSGBOX_SIGN
	end

TH13_RockTunnel_1F_Dana::
    trainerbattle_single TRAINER_TH13_ROCKTUNNEL_1F_DANA, TH13_RockTunnel_1F_Text_DanaIntro, TH13_RockTunnel_1F_Text_DanaDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH13_RockTunnel_1F_Dana_Rematch
    msgbox TH13_RockTunnel_1F_Text_DanaPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_RockTunnel_1F_Dana_Rematch::
    trainerbattle_rematch TRAINER_TH13_ROCKTUNNEL_1F_DANA, TH13_RockTunnel_1F_Text_DanaIntro, TH13_RockTunnel_1F_Text_DanaDefeat
    msgbox TH13_RockTunnel_1F_Text_DanaPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_RockTunnel_1F_Ariana::
    trainerbattle_single TRAINER_TH13_ROCKTUNNEL_1F_ARIANA, TH13_RockTunnel_1F_Text_ArianaIntro, TH13_RockTunnel_1F_Text_ArianaDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH13_RockTunnel_1F_Ariana_Rematch
    msgbox TH13_RockTunnel_1F_Text_ArianaPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_RockTunnel_1F_Ariana_Rematch::
    trainerbattle_rematch TRAINER_TH13_ROCKTUNNEL_1F_ARIANA, TH13_RockTunnel_1F_Text_ArianaIntro, TH13_RockTunnel_1F_Text_ArianaDefeat
    msgbox TH13_RockTunnel_1F_Text_ArianaPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_RockTunnel_1F_Leah::
    trainerbattle_single TRAINER_TH13_ROCKTUNNEL_1F_LEAH, TH13_RockTunnel_1F_Text_LeahIntro, TH13_RockTunnel_1F_Text_LeahDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH13_RockTunnel_1F_Leah_Rematch
    msgbox TH13_RockTunnel_1F_Text_LeahPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_RockTunnel_1F_Leah_Rematch::
    trainerbattle_rematch TRAINER_TH13_ROCKTUNNEL_1F_LEAH, TH13_RockTunnel_1F_Text_LeahIntro, TH13_RockTunnel_1F_Text_LeahDefeat
    msgbox TH13_RockTunnel_1F_Text_LeahPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_RockTunnel_1F_Lucas::
    trainerbattle_single TRAINER_TH13_ROCKTUNNEL_1F_LUCAS, TH13_RockTunnel_1F_Text_LucasIntro, TH13_RockTunnel_1F_Text_LucasDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH13_RockTunnel_1F_Lucas_Rematch
    msgbox TH13_RockTunnel_1F_Text_LucasPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_RockTunnel_1F_Lucas_Rematch::
    trainerbattle_rematch TRAINER_TH13_ROCKTUNNEL_1F_LUCAS, TH13_RockTunnel_1F_Text_LucasIntro, TH13_RockTunnel_1F_Text_LucasDefeat
    msgbox TH13_RockTunnel_1F_Text_LucasPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_RockTunnel_1F_Oliver::
    trainerbattle_single TRAINER_TH13_ROCKTUNNEL_1F_OLIVER, TH13_RockTunnel_1F_Text_OliverIntro, TH13_RockTunnel_1F_Text_OliverDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH13_RockTunnel_1F_Oliver_Rematch
    msgbox TH13_RockTunnel_1F_Text_OliverPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_RockTunnel_1F_Oliver_Rematch::
    trainerbattle_rematch TRAINER_TH13_ROCKTUNNEL_1F_OLIVER, TH13_RockTunnel_1F_Text_OliverIntro, TH13_RockTunnel_1F_Text_OliverDefeat
    msgbox TH13_RockTunnel_1F_Text_OliverPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_RockTunnel_1F_Lenny::
    trainerbattle_single TRAINER_TH13_ROCKTUNNEL_1F_LENNY, TH13_RockTunnel_1F_Text_LennyIntro, TH13_RockTunnel_1F_Text_LennyDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH13_RockTunnel_1F_Lenny_Rematch
    msgbox TH13_RockTunnel_1F_Text_LennyPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_RockTunnel_1F_Lenny_Rematch::
    trainerbattle_rematch TRAINER_TH13_ROCKTUNNEL_1F_LENNY, TH13_RockTunnel_1F_Text_LennyIntro, TH13_RockTunnel_1F_Text_LennyDefeat
    msgbox TH13_RockTunnel_1F_Text_LennyPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_RockTunnel_1F_Ashton::
    trainerbattle_single TRAINER_TH13_ROCKTUNNEL_1F_ASHTON, TH13_RockTunnel_1F_Text_AshtonIntro, TH13_RockTunnel_1F_Text_AshtonDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH13_RockTunnel_1F_Ashton_Rematch
    msgbox TH13_RockTunnel_1F_Text_AshtonPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_RockTunnel_1F_Ashton_Rematch::
    trainerbattle_rematch TRAINER_TH13_ROCKTUNNEL_1F_ASHTON, TH13_RockTunnel_1F_Text_AshtonIntro, TH13_RockTunnel_1F_Text_AshtonDefeat
    msgbox TH13_RockTunnel_1F_Text_AshtonPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_RockTunnel_1F_Text_LennyIntro::
	.string "This tunnel goes a long way, kid!$"

TH13_RockTunnel_1F_Text_LennyDefeat::
	.string "Doh!\n"
	.string "You win!$"

TH13_RockTunnel_1F_Text_LennyPostBattle::
	.string "Watch for ONIX.\n"
	.string "They appear only occasionally.\p"
	.string "High-level ones can put the\n"
	.string "squeeze on you!$"

TH13_RockTunnel_1F_Text_OliverIntro::
	.string "Hmm.\n"
	.string "Maybe I'm lost in here…$"

TH13_RockTunnel_1F_Text_OliverDefeat::
	.string "Ease up!\n"
	.string "What am I doing?\l"
	.string "Which way is out?$"

TH13_RockTunnel_1F_Text_OliverPostBattle::
	.string "That sleeping POKéMON on ROUTE 12\n"
	.string "forced me to take this detour.$"

TH13_RockTunnel_1F_Text_LucasIntro::
	.string "Outsiders like you need to show me\n"
	.string "some respect!$"

TH13_RockTunnel_1F_Text_LucasDefeat::
	.string "I give!$"

TH13_RockTunnel_1F_Text_LucasPostBattle::
	.string "You're talented enough to hike!$"

TH13_RockTunnel_1F_Text_AshtonIntro::
	.string "POKéMON fight!\n"
	.string "Ready, go!$"

TH13_RockTunnel_1F_Text_AshtonDefeat::
	.string "Game over!$"

TH13_RockTunnel_1F_Text_AshtonPostBattle::
	.string "Oh well, I'll get a ZUBAT as I go!$"

TH13_RockTunnel_1F_Text_LeahIntro::
	.string "Eek!\p"
	.string "Don't try anything funny in the\n"
	.string "dark!$"

TH13_RockTunnel_1F_Text_LeahDefeat::
	.string "It was too dark…$"

TH13_RockTunnel_1F_Text_LeahPostBattle::
	.string "I saw a MACHOP in this tunnel.$"

TH13_RockTunnel_1F_Text_DanaIntro::
	.string "I came this far looking for wild\n"
	.string "POKéMON.$"

TH13_RockTunnel_1F_Text_DanaDefeat::
	.string "I'm out of POKéMON!$"

TH13_RockTunnel_1F_Text_DanaPostBattle::
	.string "You looked cute and harmless.\n"
	.string "Was I ever wrong!$"

TH13_RockTunnel_1F_Text_ArianaIntro::
	.string "You have POKéMON!\n"
	.string "Let's start!$"

TH13_RockTunnel_1F_Text_ArianaDefeat::
	.string "You play hard!$"

TH13_RockTunnel_1F_Text_ArianaPostBattle::
	.string "Whew!\n"
	.string "I'm all sweaty now.$"

TH13_RockTunnel_1F_Text_RouteSign::
	.string "ROCK TUNNEL\n"
	.string "CERULEAN CITY - LAVENDER TOWN$"

TH13_RockTunnel_1F_EventScript_RouteSign::
	msgbox TH13_RockTunnel_1F_Text_RouteSign, MSGBOX_SIGN
	end

TH13_RockTunnel_B1F_Cooper::
    trainerbattle_single TRAINER_TH13_ROCKTUNNEL_B1F_COOPER, TH13_RockTunnel_B1F_Text_CooperIntro, TH13_RockTunnel_B1F_Text_CooperDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH13_RockTunnel_B1F_Cooper_Rematch
    msgbox TH13_RockTunnel_B1F_Text_CooperPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_RockTunnel_B1F_Cooper_Rematch::
    trainerbattle_rematch TRAINER_TH13_ROCKTUNNEL_B1F_COOPER, TH13_RockTunnel_B1F_Text_CooperIntro, TH13_RockTunnel_B1F_Text_CooperDefeat
    msgbox TH13_RockTunnel_B1F_Text_CooperPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_RockTunnel_B1F_Dudley::
    trainerbattle_single TRAINER_TH13_ROCKTUNNEL_B1F_DUDLEY, TH13_RockTunnel_B1F_Text_DudleyIntro, TH13_RockTunnel_B1F_Text_DudleyDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH13_RockTunnel_B1F_Dudley_Rematch
    msgbox TH13_RockTunnel_B1F_Text_DudleyPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_RockTunnel_B1F_Dudley_Rematch::
    trainerbattle_rematch TRAINER_TH13_ROCKTUNNEL_B1F_DUDLEY, TH13_RockTunnel_B1F_Text_DudleyIntro, TH13_RockTunnel_B1F_Text_DudleyDefeat
    msgbox TH13_RockTunnel_B1F_Text_DudleyPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_RockTunnel_B1F_Sofia::
    trainerbattle_single TRAINER_TH13_ROCKTUNNEL_B1F_SOFIA, TH13_RockTunnel_B1F_Text_SofiaIntro, TH13_RockTunnel_B1F_Text_SofiaDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH13_RockTunnel_B1F_Sofia_Rematch
    msgbox TH13_RockTunnel_B1F_Text_SofiaPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_RockTunnel_B1F_Sofia_Rematch::
    trainerbattle_rematch TRAINER_TH13_ROCKTUNNEL_B1F_SOFIA, TH13_RockTunnel_B1F_Text_SofiaIntro, TH13_RockTunnel_B1F_Text_SofiaDefeat
    msgbox TH13_RockTunnel_B1F_Text_SofiaPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_RockTunnel_B1F_Allen::
    trainerbattle_single TRAINER_TH13_ROCKTUNNEL_B1F_ALLEN, TH13_RockTunnel_B1F_Text_AllenIntro, TH13_RockTunnel_B1F_Text_AllenDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH13_RockTunnel_B1F_Allen_Rematch
    msgbox TH13_RockTunnel_B1F_Text_AllenPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_RockTunnel_B1F_Allen_Rematch::
    trainerbattle_rematch TRAINER_TH13_ROCKTUNNEL_B1F_ALLEN, TH13_RockTunnel_B1F_Text_AllenIntro, TH13_RockTunnel_B1F_Text_AllenDefeat
    msgbox TH13_RockTunnel_B1F_Text_AllenPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_RockTunnel_B1F_Eric::
    trainerbattle_single TRAINER_TH13_ROCKTUNNEL_B1F_ERIC, TH13_RockTunnel_B1F_Text_EricIntro, TH13_RockTunnel_B1F_Text_EricDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH13_RockTunnel_B1F_Eric_Rematch
    msgbox TH13_RockTunnel_B1F_Text_EricPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_RockTunnel_B1F_Eric_Rematch::
    trainerbattle_rematch TRAINER_TH13_ROCKTUNNEL_B1F_ERIC, TH13_RockTunnel_B1F_Text_EricIntro, TH13_RockTunnel_B1F_Text_EricDefeat
    msgbox TH13_RockTunnel_B1F_Text_EricPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_RockTunnel_B1F_Steve::
    trainerbattle_single TRAINER_TH13_ROCKTUNNEL_B1F_STEVE, TH13_RockTunnel_B1F_Text_SteveIntro, TH13_RockTunnel_B1F_Text_SteveDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH13_RockTunnel_B1F_Steve_Rematch
    msgbox TH13_RockTunnel_B1F_Text_StevePostBattle, MSGBOX_AUTOCLOSE
    end
TH13_RockTunnel_B1F_Steve_Rematch::
    trainerbattle_rematch TRAINER_TH13_ROCKTUNNEL_B1F_STEVE, TH13_RockTunnel_B1F_Text_SteveIntro, TH13_RockTunnel_B1F_Text_SteveDefeat
    msgbox TH13_RockTunnel_B1F_Text_StevePostBattle, MSGBOX_AUTOCLOSE
    end
TH13_RockTunnel_B1F_Martha::
    trainerbattle_single TRAINER_TH13_ROCKTUNNEL_B1F_MARTHA, TH13_RockTunnel_B1F_Text_MarthaIntro, TH13_RockTunnel_B1F_Text_MarthaDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH13_RockTunnel_B1F_Martha_Rematch
    msgbox TH13_RockTunnel_B1F_Text_MarthaPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_RockTunnel_B1F_Martha_Rematch::
    trainerbattle_rematch TRAINER_TH13_ROCKTUNNEL_B1F_MARTHA, TH13_RockTunnel_B1F_Text_MarthaIntro, TH13_RockTunnel_B1F_Text_MarthaDefeat
    msgbox TH13_RockTunnel_B1F_Text_MarthaPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_RockTunnel_B1F_Winston::
    trainerbattle_single TRAINER_TH13_ROCKTUNNEL_B1F_WINSTON, TH13_RockTunnel_B1F_Text_WinstonIntro, TH13_RockTunnel_B1F_Text_WinstonDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH13_RockTunnel_B1F_Winston_Rematch
    msgbox TH13_RockTunnel_B1F_Text_WinstonPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_RockTunnel_B1F_Winston_Rematch::
    trainerbattle_rematch TRAINER_TH13_ROCKTUNNEL_B1F_WINSTON, TH13_RockTunnel_B1F_Text_WinstonIntro, TH13_RockTunnel_B1F_Text_WinstonDefeat
    msgbox TH13_RockTunnel_B1F_Text_WinstonPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_RockTunnel_B1F_Text_SofiaIntro::
	.string "Do you know how you can avoid\n"
	.string "getting lost in the mountains?\p"
	.string "You can bend twigs as trail\n"
	.string "markers.$"

TH13_RockTunnel_B1F_Text_SofiaDefeat::
	.string "Ohhh!\n"
	.string "I did my best!$"

TH13_RockTunnel_B1F_Text_SofiaPostBattle::
	.string "I want to go home!$"

TH13_RockTunnel_B1F_Text_DudleyIntro::
	.string "Hahaha!\n"
	.string "Can you beat my power?$"

TH13_RockTunnel_B1F_Text_DudleyDefeat::
	.string "Oops!\n"
	.string "Outmuscled!$"

TH13_RockTunnel_B1F_Text_DudleyPostBattle::
	.string "I go for power because I hate\n"
	.string "thinking.$"

TH13_RockTunnel_B1F_Text_CooperIntro::
	.string "You have a POKéDEX?\n"
	.string "I want one, too.$"

TH13_RockTunnel_B1F_Text_CooperDefeat::
	.string "Shoot!\n"
	.string "I am so jealous!$"

TH13_RockTunnel_B1F_Text_CooperPostBattle::
	.string "When you finish your POKéDEX,\n"
	.string "can I have it?$"

TH13_RockTunnel_B1F_Text_SteveIntro::
	.string "Um… Do you know about POKéMON\n"
	.string "cosplay?$"

TH13_RockTunnel_B1F_Text_SteveDefeat::
	.string "Well, that's that.$"

TH13_RockTunnel_B1F_Text_StevePostBattle::
	.string "POKéMON cosplay is dressing up as\n"
	.string "POKéMON for fun.\p"
	.string "CLEFAIRY is a favorite.$"

TH13_RockTunnel_B1F_Text_AllenIntro::
	.string "My POKéMON techniques will leave\n"
	.string "you crying!$"

TH13_RockTunnel_B1F_Text_AllenDefeat::
	.string "I give!\n"
	.string "You're a better technician!$"

TH13_RockTunnel_B1F_Text_AllenPostBattle::
	.string "In mountains, you'll often find\n"
	.string "ROCK-type POKéMON.$"

TH13_RockTunnel_B1F_Text_MarthaIntro::
	.string "I don't often come here, but I will\n"
	.string "battle you.$"

TH13_RockTunnel_B1F_Text_MarthaDefeat::
	.string "Oh!\n"
	.string "I lost!$"

TH13_RockTunnel_B1F_Text_MarthaPostBattle::
	.string "I like tiny POKéMON.\n"
	.string "Big ones are too scary!$"

TH13_RockTunnel_B1F_Text_EricIntro::
	.string "Hit me with your best shot!$"

TH13_RockTunnel_B1F_Text_EricDefeat::
	.string "Fired away!$"

TH13_RockTunnel_B1F_Text_EricPostBattle::
	.string "I'll raise my POKéMON to beat\n"
	.string "yours, kid.$"

TH13_RockTunnel_B1F_Text_WinstonIntro::
	.string "I draw illustrations of POKéMON\n"
	.string "when I'm home.$"

TH13_RockTunnel_B1F_Text_WinstonDefeat::
	.string "Whew…\n"
	.string "I'm exhausted…$"

TH13_RockTunnel_B1F_Text_WinstonPostBattle::
	.string "I'm an artist, not a fighter.\n"
	.string "I'll go home to draw.$"

TH13_RockTunnel_1F_Item14::
    finditem ITEM_REPEL
    end
TH13_RockTunnel_1F_Item15::
    finditem ITEM_PEARL
    end
TH13_RockTunnel_1F_Item16::
    finditem ITEM_ESCAPE_ROPE
    end
TH13_RockTunnel_B1F_Item17::
    finditem ITEM_REVIVE
    end
TH13_RockTunnel_B1F_Item18::
    finditem ITEM_MAX_ETHER
    end
