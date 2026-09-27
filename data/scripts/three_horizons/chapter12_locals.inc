TH12_Route5_Sign0::
    msgbox TH12_Route5_Sign0_Text, MSGBOX_SIGN
    end
TH12_Route5_Sign0_Text:
	.string "UNDERGROUND PATH\n"
	.string "CERULEAN CITY - VERMILION CITY$"

TH12_Route6_Object0::
    trainerbattle_single TRAINER_TH12_BUG_CATCHER_KEIGO, TH12_Route6_Object0_Intro, TH12_Route6_Object0_Defeat
    msgbox TH12_Route6_Object0_After, MSGBOX_AUTOCLOSE
    end

TH12_Route6_Object0_Intro:
	.string "There aren't many bugs out here.$"

TH12_Route6_Object0_Defeat:
	.string "No!\n"
	.string "You're kidding!$"

TH12_Route6_Object0_After:
	.string "I like bugs, so I'm going back to\n"
	.string "VIRIDIAN FOREST.$"

TH12_Route6_Object1::
    trainerbattle_single TRAINER_TH12_CAMPER_RICKY, TH12_Route6_Object1_Intro, TH12_Route6_Object1_Defeat
    msgbox TH12_Route6_Object1_After, MSGBOX_AUTOCLOSE
    end

TH12_Route6_Object1_Intro:
	.string "Who's there?\n"
	.string "Quit listening in on us!$"

TH12_Route6_Object1_Defeat:
	.string "I just can't win!$"

TH12_Route6_Object1_After:
	.string "Whisper…\n"
	.string "Whisper…$"

TH12_Route6_Object2::
    trainerbattle_single TRAINER_TH12_PICNICKER_NANCY, TH12_Route6_Object2_Intro, TH12_Route6_Object2_Defeat
    msgbox TH12_Route6_Object2_After, MSGBOX_AUTOCLOSE
    end

TH12_Route6_Object2_Intro:
	.string "Excuse me!\n"
	.string "This is a private conversation!$"

TH12_Route6_Object2_Defeat:
	.string "Ugh!\n"
	.string "I hate losing.$"

TH12_Route6_Object2_After:
	.string "Whisper…\n"
	.string "Whisper…$"

TH12_Route6_Object3::
    trainerbattle_single TRAINER_TH12_BUG_CATCHER_ELIJAH, TH12_Route6_Object3_Intro, TH12_Route6_Object3_Defeat
    msgbox TH12_Route6_Object3_After, MSGBOX_AUTOCLOSE
    end

TH12_Route6_Object3_Intro:
	.string "I've never seen you around.\n"
	.string "Are you good?$"

TH12_Route6_Object3_Defeat:
	.string "You're too good!$"

TH12_Route6_Object3_After:
	.string "Are my POKéMON weak?\n"
	.string "Or, am I just bad?\l"
	.string "Which do you think?$"

TH12_Route6_Object4::
    trainerbattle_single TRAINER_TH12_PICNICKER_ISABELLE, TH12_Route6_Object4_Intro, TH12_Route6_Object4_Defeat
    msgbox TH12_Route6_Object4_After, MSGBOX_AUTOCLOSE
    end

TH12_Route6_Object4_Intro:
	.string "Me?\n"
	.string "Well, okay. I'll play!$"

TH12_Route6_Object4_Defeat:
	.string "Things just didn't work…$"

TH12_Route6_Object4_After:
	.string "I want to get stronger.\n"
	.string "What's your secret?$"

TH12_Route6_Object5::
    trainerbattle_single TRAINER_TH12_CAMPER_JEFF, TH12_Route6_Object5_Intro, TH12_Route6_Object5_Defeat
    msgbox TH12_Route6_Object5_After, MSGBOX_AUTOCLOSE
    end

TH12_Route6_Object5_Intro:
	.string "Huh?\n"
	.string "You want to talk to me?$"

TH12_Route6_Object5_Defeat:
	.string "This stinks…\n"
	.string "I couldn't beat your challenge…$"

TH12_Route6_Object5_After:
	.string "I should bring more POKéMON with\n"
	.string "me. I'll feel safer that way.$"

TH12_Route6_Sign0::
    msgbox TH12_Route6_Sign0_Text, MSGBOX_SIGN
    end
TH12_Route6_Sign0_Text:
	.string "UNDERGROUND PATH\n"
	.string "CERULEAN CITY - VERMILION CITY$"

TH12_UndergroundPath_NorthEntrance_Object0::
    msgbox TH12_UndergroundPath_NorthEntrance_Object0_Text, MSGBOX_NPC
    end
TH12_UndergroundPath_NorthEntrance_Object0_Text:
    .string "The tunnel goes under SAFFRON.\nIt comes out near VERMILION!$"

TH12_UndergroundPath_SouthEntrance_Object0::
    msgbox TH12_UndergroundPath_SouthEntrance_Object0_Text, MSGBOX_NPC
    end
TH12_UndergroundPath_SouthEntrance_Object0_Text:
	.string "People often lose things in the\n"
	.string "darkness of the UNDERGROUND PATH.$"

TH12_VermilionCity_Object0::
    msgbox TH12_VermilionCity_Object0_Text, MSGBOX_NPC
    end
TH12_VermilionCity_Object0_Text:
	.string "We're careful about pollution here.\p"
	.string "We've heard GRIMER multiplies in\n"
	.string "toxic sludge.$"

TH12_VermilionCity_Object1::
    msgbox TH12_VermilionCity_Object1_Text, MSGBOX_NPC
    end
TH12_VermilionCity_Object1_Text:
	.string "Did you see the S.S. ANNE moored\n"
	.string "in the harbor?$"

TH12_VermilionCity_Object2::
    msgbox TH12_VermilionCity_Object2_Text, MSGBOX_NPC
    end
TH12_VermilionCity_Object2_Text:
	.string "I'm putting up a building on this\n"
	.string "plot of land. I own it all.\p"
	.string "My POKéMON is tamping the land\n"
	.string "to lay the foundation.$"

TH12_VermilionCity_Object3::
    lock
    faceplayer
    playmoncry SPECIES_MACHOP, CRY_MODE_NORMAL
    msgbox TH12_VermilionCity_Object3_Text
    waitmoncry
    release
    end
TH12_VermilionCity_Object3_Text:
	.string "MACHOP: Guoh! Gogogoh!$"

TH12_VermilionCity_Object4::
    msgbox TH12_VermilionCity_Object4_Text, MSGBOX_NPC
    end
TH12_VermilionCity_Object4_Text:
	.string "The S.S. ANNE is a famous luxury\n"
	.string "cruise ship.\p"
	.string "It visits VERMILION once a year.$"

TH12_VermilionCity_Sign0::
    msgbox TH12_VermilionCity_Sign0_Text, MSGBOX_SIGN
    end
TH12_VermilionCity_Sign0_Text:
	.string "VERMILION CITY\n"
	.string "The Port of Exquisite Sunsets$"

TH12_VermilionCity_Sign1::
    msgbox TH12_VermilionCity_Sign1_Text, MSGBOX_SIGN
    end
TH12_VermilionCity_Sign1_Text:
	.string "POKéMON FAN CLUB\n"
	.string "All POKéMON fans welcome!$"

TH12_VermilionCity_Sign2::
    msgbox TH12_VermilionCity_Sign2_Text, MSGBOX_SIGN
    end
TH12_VermilionCity_Sign2_Text:
	.string "VERMILION CITY POKéMON GYM\n"
	.string "LEADER: LT. SURGE\l"
	.string "The Lightning American!$"

TH12_VermilionCity_Sign3::
    msgbox TH12_VermilionCity_Sign3_Text, MSGBOX_SIGN
    end
TH12_VermilionCity_Sign3_Text:
	.string "VERMILION HARBOR$"

TH12_VermilionCity_Sign4::
    msgbox TH12_VermilionCity_Sign4_Text, MSGBOX_SIGN
    end
TH12_VermilionCity_Sign4_Text:
	.string "NOTICE!\p"
	.string "ROUTE 12 may be blocked off by a\n"
	.string "sleeping POKéMON.\p"
	.string "Detour through ROCK TUNNEL to\n"
	.string "LAVENDER TOWN.\p"
	.string "VERMILION POLICE$"

TH12_VermilionCity_Mart_Object1::
    msgbox TH12_VermilionCity_Mart_Object1_Text, MSGBOX_NPC
    end
TH12_VermilionCity_Mart_Object1_Text:
	.string "I think POKéMON can be good or\n"
	.string "bad. It depends on the TRAINER.$"

TH12_VermilionCity_Mart_Object2::
    msgbox TH12_VermilionCity_Mart_Object2_Text, MSGBOX_NPC
    end
TH12_VermilionCity_Mart_Object2_Text:
	.string "There are wicked people who will\n"
	.string "use POKéMON for criminal acts.\p"
	.string "TEAM ROCKET traffics in rare\n"
	.string "POKéMON, for example.\p"
	.string "They also abandon POKéMON that\n"
	.string "they consider unpopular or useless.\p"
	.string "That's the sort of horrid people\n"
	.string "they are, TEAM ROCKET.$"

TH12_VermilionCity_PokemonCenter_1F_Object1::
    msgbox TH12_VermilionCity_PokemonCenter_1F_Object1_Text, MSGBOX_NPC
    end
TH12_VermilionCity_PokemonCenter_1F_Object1_Text:
	.string "My POKéMON was poisoned!\n"
	.string "It fainted while we were walking!$"

TH12_VermilionCity_PokemonCenter_1F_Object2::
    msgbox TH12_VermilionCity_PokemonCenter_1F_Object2_Text, MSGBOX_NPC
    end
TH12_VermilionCity_PokemonCenter_1F_Object2_Text:
	.string "Even if they are the same level,\n"
	.string "POKéMON can have very different\l"
	.string "stats and abilities.\p"
	.string "A POKéMON raised by a TRAINER is\n"
	.string "stronger than one in the wild.$"

TH12_VermilionCity_PokemonCenter_1F_Object3::
    msgbox TH12_VermilionCity_PokemonCenter_1F_Object3_Text, MSGBOX_NPC
    end
TH12_VermilionCity_PokemonCenter_1F_Object3_Text:
	.string "It is true that a higher-level\n"
	.string "POKéMON will be more powerful…\p"
	.string "But, all POKéMON will have weak\n"
	.string "points against specific types.\p"
	.string "So, there appears to be no\n"
	.string "universally strong POKéMON.$"

TH12_VermilionCity_PokemonCenter_1F_Object4::
    msgbox TH12_VermilionCity_PokemonCenter_1F_Object4_Text, MSGBOX_NPC
    end
TH12_VermilionCity_PokemonCenter_1F_Object4_Text:
    .string "Trainers come from many regions\nto board the S.S. ANNE.\pSome bring POKéMON we have never\nseen in KANTO before!$"

TH12_VermilionCity_PokemonCenter_1F_Object5::
    msgbox TH12_VermilionCity_PokemonCenter_1F_Object5_Text, MSGBOX_NPC
    end
TH12_VermilionCity_PokemonCenter_1F_Object5_Text:
    .string "POKéMON JOURNAL: LT. SURGE\ntrains ELECTRIC types at the GYM.$"

TH12_VermilionCity_PokemonCenter_1F_Object6::
    msgbox TH12_VermilionCity_PokemonCenter_1F_Object6_Text, MSGBOX_NPC
    end
TH12_VermilionCity_PokemonCenter_1F_Object6_Text:
    .string "POKéMON JOURNAL: LT. SURGE\ntrains ELECTRIC types at the GYM.$"

TH12_VermilionCity_PokemonFanClub_Object1::
    msgbox TH12_VermilionCity_PokemonFanClub_Object1_Text, MSGBOX_NPC
    end
TH12_VermilionCity_PokemonFanClub_Object1_Text:
	.string "Our CHAIRMAN is very vocal about\n"
	.string "POKéMON.$"

TH12_VermilionCity_PokemonFanClub_Object2::
    lock
    faceplayer
    playmoncry SPECIES_PIKACHU, CRY_MODE_NORMAL
    msgbox TH12_VermilionCity_PokemonFanClub_Object2_Text
    waitmoncry
    release
    end
TH12_VermilionCity_PokemonFanClub_Object2_Text:
	.string "PIKACHU: Chu! Pikachu!$"

TH12_VermilionCity_PokemonFanClub_Object3::
    lock
    faceplayer
    playmoncry SPECIES_SEEL, CRY_MODE_NORMAL
    msgbox TH12_VermilionCity_PokemonFanClub_Object3_Text
    waitmoncry
    release
    end
TH12_VermilionCity_PokemonFanClub_Object3_Text:
	.string "SEEL: Kyuoo!$"

TH12_VermilionCity_PokemonFanClub_Object4::
    msgbox TH12_VermilionCity_PokemonFanClub_Object4_Text, MSGBOX_NPC
    end
TH12_VermilionCity_PokemonFanClub_Object4_Text:
	.string "I just adore my SEEL!\n"
	.string "It's so lovable!\p"
	.string "It squeals, “Kyuuuh,” when I\n"
	.string "hug it!$"

TH12_VermilionCity_PokemonFanClub_Object5::
    msgbox TH12_VermilionCity_PokemonFanClub_Object5_Text, MSGBOX_NPC
    end
TH12_VermilionCity_PokemonFanClub_Object5_Text:
	.string "Won't you admire my PIKACHU's\n"
	.string "adorable tail?$"

TH12_VermilionCity_PokemonFanClub_Sign0::
    msgbox TH12_VermilionCity_PokemonFanClub_Sign0_Text, MSGBOX_SIGN
    end
TH12_VermilionCity_PokemonFanClub_Sign0_Text:
	.string "Let's all listen politely to other\n"
	.string "TRAINERS!$"

TH12_VermilionCity_PokemonFanClub_Sign1::
    msgbox TH12_VermilionCity_PokemonFanClub_Sign1_Text, MSGBOX_SIGN
    end
TH12_VermilionCity_PokemonFanClub_Sign1_Text:
	.string "If someone brags, brag right back!$"

TH12_VermilionCity_House2_Object0::
    msgbox TH12_VermilionCity_House2_Object0_Text, MSGBOX_NPC
    end
TH12_VermilionCity_House2_Object0_Text:
    .string "My FARFETCH'D carries its leek\neverywhere. A trusty travel partner!$"

TH12_VermilionCity_House3_Object0::
    msgbox TH12_VermilionCity_House3_Object0_Text, MSGBOX_NPC
    end
TH12_VermilionCity_House3_Object0_Text:
	.string "I'm getting my PIDGEY to fly a\n"
	.string "letter to SAFFRON in the north.$"

TH12_VermilionCity_House3_Object1::
    lock
    faceplayer
    playmoncry SPECIES_PIDGEY, CRY_MODE_NORMAL
    msgbox TH12_VermilionCity_House3_Object1_Text
    waitmoncry
    release
    end
TH12_VermilionCity_House3_Object1_Text:
	.string "PIDGEY: Kurukkoo!$"

TH12_Mail::
    msgbox TH12_Mail_Text, MSGBOX_SIGN
    end
TH12_Mail_Text:
    .string "A letter for a friend in SAFFRON.\nIt is waiting for PIDGEY to deliver it.$"

TH12_VermilionCity_House3_Object3::
    msgbox TH12_VermilionCity_House3_Object3_Text, MSGBOX_NPC
    end
TH12_VermilionCity_House3_Object3_Text:
	.string "I want to exchange MAIL with all\n"
	.string "sorts of people.\p"
	.string "I send my PIDGEY to a UNION ROOM\n"
	.string "to exchange MAIL for me.$"

TH12_VermilionCity_House3_Sign0::
    msgbox TH12_VermilionCity_House3_Sign0_Text, MSGBOX_SIGN
    end
TH12_VermilionCity_House3_Sign0_Text:
	.string "Dear PIPPI,\n"
	.string "I hope to see you soon.\p"
	.string "I heard SAFFRON has problems with\n"
	.string "TEAM ROCKET.\p"
	.string "VERMILION appears to be safe.$"

TH12_SSAnne_1F_Corridor_Object0::
    msgbox TH12_SSAnne_1F_Corridor_Object0_Text, MSGBOX_NPC
    end
TH12_SSAnne_1F_Corridor_Object0_Text:
	.string "The passengers are restless from\n"
	.string "this long voyage.\p"
	.string "You might be challenged by the\n"
	.string "more bored ones!$"

TH12_SSAnne_1F_Corridor_Object1::
    msgbox TH12_SSAnne_1F_Corridor_Object1_Text, MSGBOX_NPC
    end
TH12_SSAnne_1F_Corridor_Object1_Text:
	.string "Bonjour!\n"
	.string "I am le waiter on this ship!\p"
	.string "I will be happy to serve you\n"
	.string "anything you please!\p"
	.string "… … …\n"
	.string "Ah! Le strong silent type!$"

TH12_SSAnne_1F_Room1_Object0::
    msgbox TH12_SSAnne_1F_Room1_Object0_Text, MSGBOX_NPC
    end
TH12_SSAnne_1F_Room1_Object0_Text:
	.string "Ssh…!\n"
	.string "I'm a GLOBAL POLICE agent.\p"
	.string "I'm on the trail of TEAM ROCKET.\n"
	.string "They're up to nothing good!$"

TH12_SSAnne_1F_Room2_Object0::
    trainerbattle_single TRAINER_TH12_LASS_ANN, TH12_SSAnne_1F_Room2_Object0_Intro, TH12_SSAnne_1F_Room2_Object0_Defeat
    msgbox TH12_SSAnne_1F_Room2_Object0_After, MSGBOX_AUTOCLOSE
    end

TH12_SSAnne_1F_Room2_Object0_Intro:
	.string "I collected these POKéMON\n"
	.string "from all around the world!$"

TH12_SSAnne_1F_Room2_Object0_Defeat:
	.string "Oh, no!\n"
	.string "I went around the world for these!$"

TH12_SSAnne_1F_Room2_Object0_After:
	.string "You hurt my poor POKéMON!\p"
	.string "I demand that you heal them at a\n"
	.string "POKéMON CENTER!$"

TH12_SSAnne_1F_Room2_Object1::
    trainerbattle_single TRAINER_TH12_YOUNGSTER_TYLER, TH12_SSAnne_1F_Room2_Object1_Intro, TH12_SSAnne_1F_Room2_Object1_Defeat
    msgbox TH12_SSAnne_1F_Room2_Object1_After, MSGBOX_AUTOCLOSE
    end

TH12_SSAnne_1F_Room2_Object1_Intro:
	.string "I love POKéMON!\n"
	.string "Do you?$"

TH12_SSAnne_1F_Room2_Object1_Defeat:
	.string "Wow! \n"
	.string "You're great!$"

TH12_SSAnne_1F_Room2_Object1_After:
	.string "Listen, listen!\n"
	.string "Let me be your friend, okay?\p"
	.string "Then we can trade POKéMON and\n"
	.string "do stuff.$"

TH12_SSAnne_1F_Room2_Object2::
    msgbox TH12_SSAnne_1F_Room2_Object2_Text, MSGBOX_NPC
    end
TH12_SSAnne_1F_Room2_Object2_Text:
	.string "We are cruising around the world,\n"
	.string "my children and I.$"

TH12_SSAnne_1F_Room2_Object3::
    lock
    giveitem ITEM_TM31
    goto_if_eq VAR_RESULT, FALSE, TH12_RewardBagFull
    setflag FLAG_TH12_PICKUP_19
    removeobject VAR_LAST_TALKED
    release
    end

TH12_SSAnne_1F_Room3_Object0::
    msgbox TH12_SSAnne_1F_Room3_Object0_Text, MSGBOX_NPC
    end
TH12_SSAnne_1F_Room3_Object0_Text:
	.string "I always travel with WIGGLYTUFF.\n"
	.string "I never leave home without it.$"

TH12_SSAnne_1F_Room3_Object1::
    lock
    faceplayer
    playmoncry SPECIES_WIGGLYTUFF, CRY_MODE_NORMAL
    msgbox TH12_SSAnne_1F_Room3_Object1_Text
    waitmoncry
    release
    end
TH12_SSAnne_1F_Room3_Object1_Text:
	.string "WIGGLYTUFF: Puup pupuu!$"

TH12_SSAnne_1F_Room3_Object2::
    msgbox TH12_SSAnne_1F_Room3_Object2_Text, MSGBOX_NPC
    end
TH12_SSAnne_1F_Room3_Object2_Text:
	.string "A world cruise is so elegant yet\n"
	.string "cozy!$"

TH12_SSAnne_1F_Room5_Object0::
    trainerbattle_single TRAINER_TH12_GENTLEMAN_ARTHUR, TH12_SSAnne_1F_Room5_Object0_Intro, TH12_SSAnne_1F_Room5_Object0_Defeat
    msgbox TH12_SSAnne_1F_Room5_Object0_After, MSGBOX_AUTOCLOSE
    end

TH12_SSAnne_1F_Room5_Object0_Intro:
	.string "You insolent pup!\n"
	.string "How dare you barge in!$"

TH12_SSAnne_1F_Room5_Object0_Defeat:
	.string "Humph! You rude child!\n"
	.string "You have no sense of courtesy!$"

TH12_SSAnne_1F_Room5_Object0_After:
	.string "I wish to be left alone!\n"
	.string "Get out!$"

TH12_SSAnne_1F_Room6_Object0::
    goto TH12_Ship_Heal
    end
TH12_SSAnne_1F_Room6_Object0_Text:
	.string "You look tired. Would you like to\n"
	.string "take a short rest?$"

TH12_SSAnne_1F_Room7_Object0::
    trainerbattle_single TRAINER_TH12_GENTLEMAN_THOMAS, TH12_SSAnne_1F_Room7_Object0_Intro, TH12_SSAnne_1F_Room7_Object0_Defeat
    msgbox TH12_SSAnne_1F_Room7_Object0_After, MSGBOX_AUTOCLOSE
    end

TH12_SSAnne_1F_Room7_Object0_Intro:
	.string "I am but a solitary traveler…\p"
	.string "My sole companions and friends are\n"
	.string "POKéMON I caught on my journeys…$"

TH12_SSAnne_1F_Room7_Object0_Defeat:
	.string "My, my friends…$"

TH12_SSAnne_1F_Room7_Object0_After:
	.string "You should be nice to friends!$"

TH12_SSAnne_2F_Corridor_Object1::
    msgbox TH12_SSAnne_2F_Corridor_Object1_Text, MSGBOX_NPC
    end
TH12_SSAnne_2F_Corridor_Object1_Text:
	.string "This ship, she is a luxury liner for\n"
	.string "TRAINERS of the world!\p"
	.string "At every port, we hold parties with\n"
	.string "invited TRAINERS.$"

TH12_SSAnne_2F_Room2_Object0::
    trainerbattle_single TRAINER_TH12_FISHERMAN_DALE, TH12_SSAnne_2F_Room2_Object0_Intro, TH12_SSAnne_2F_Room2_Object0_Defeat
    msgbox TH12_SSAnne_2F_Room2_Object0_After, MSGBOX_AUTOCLOSE
    end

TH12_SSAnne_2F_Room2_Object0_Intro:
	.string "Check out what I fished up!$"

TH12_SSAnne_2F_Room2_Object0_Defeat:
	.string "I'm all out!$"

TH12_SSAnne_2F_Room2_Object0_After:
	.string "Party?\p"
	.string "The cruise ship's party should be\n"
	.string "over by now.$"

TH12_SSAnne_2F_Room2_Object1::
    trainerbattle_single TRAINER_TH12_GENTLEMAN_BROOKS, TH12_SSAnne_2F_Room2_Object1_Intro, TH12_SSAnne_2F_Room2_Object1_Defeat
    msgbox TH12_SSAnne_2F_Room2_Object1_After, MSGBOX_AUTOCLOSE
    end

TH12_SSAnne_2F_Room2_Object1_Intro:
	.string "Competing against the young keeps\n"
	.string "me youthful.$"

TH12_SSAnne_2F_Room2_Object1_Defeat:
	.string "Good match!\n"
	.string "Ah, I feel young again!$"

TH12_SSAnne_2F_Room2_Object1_After:
	.string "Fifteen years ago, I would\n"
	.string "have won!$"

TH12_SSAnne_2F_Room2_Object2::
    lock
    giveitem ITEM_STARDUST
    goto_if_eq VAR_RESULT, FALSE, TH12_RewardBagFull
    setflag FLAG_TH12_PICKUP_20
    removeobject VAR_LAST_TALKED
    release
    end

TH12_SSAnne_2F_Room3_Object0::
    msgbox TH12_SSAnne_2F_Room3_Object0_Text, MSGBOX_NPC
    end
TH12_SSAnne_2F_Room3_Object0_Text:
	.string "Ah, yes, I have seen some POKéMON\n"
	.string "ferry people across the water!$"

TH12_SSAnne_2F_Room4_Object0::
    trainerbattle_single TRAINER_TH12_GENTLEMAN_LAMAR, TH12_SSAnne_2F_Room4_Object0_Intro, TH12_SSAnne_2F_Room4_Object0_Defeat
    msgbox TH12_SSAnne_2F_Room4_Object0_After, MSGBOX_AUTOCLOSE
    end

TH12_SSAnne_2F_Room4_Object0_Intro:
	.string "Which do you find more worthy,\n"
	.string "a strong or a rare POKéMON?$"

TH12_SSAnne_2F_Room4_Object0_Defeat:
	.string "I must salute you!$"

TH12_SSAnne_2F_Room4_Object0_After:
	.string "Personally, I prefer strong and\n"
	.string "rare POKéMON.$"

TH12_SSAnne_2F_Room4_Object1::
    trainerbattle_single TRAINER_TH12_LASS_DAWN, TH12_SSAnne_2F_Room4_Object1_Intro, TH12_SSAnne_2F_Room4_Object1_Defeat
    msgbox TH12_SSAnne_2F_Room4_Object1_After, MSGBOX_AUTOCLOSE
    end

TH12_SSAnne_2F_Room4_Object1_Intro:
	.string "I don't believe I saw you at the\n"
	.string "party?$"

TH12_SSAnne_2F_Room4_Object1_Defeat:
	.string "Take it easy!$"

TH12_SSAnne_2F_Room4_Object1_After:
	.string "Oh, I adore your strong POKéMON!\n"
	.string "Oh, how I envy you for them!$"

TH12_SSAnne_2F_Room4_Object2::
    lock
    giveitem ITEM_X_ATTACK
    goto_if_eq VAR_RESULT, FALSE, TH12_RewardBagFull
    setflag FLAG_TH12_PICKUP_21
    removeobject VAR_LAST_TALKED
    release
    end

TH12_SSAnne_2F_Room5_Object0::
    msgbox TH12_SSAnne_2F_Room5_Object0_Text, MSGBOX_NPC
    end
TH12_SSAnne_2F_Room5_Object0_Text:
	.string "Have you gone to the SAFARI ZONE\n"
	.string "in FUCHSIA CITY?\p"
	.string "There are many kinds of rare\n"
	.string "POKéMON.$"

TH12_SSAnne_2F_Room5_Object1::
    msgbox TH12_SSAnne_2F_Room5_Object1_Text, MSGBOX_NPC
    end
TH12_SSAnne_2F_Room5_Object1_Text:
	.string "Me and my daddy think the SAFARI\n"
	.string "ZONE is awesome!\l"
	.string "I wish we could go there again.$"

TH12_SSAnne_2F_Room6_Object0::
    msgbox TH12_SSAnne_2F_Room6_Object0_Text, MSGBOX_NPC
    end
TH12_SSAnne_2F_Room6_Object0_Text:
	.string "I hear many people get seasick.$"

TH12_SSAnne_2F_Room6_Object1::
    msgbox TH12_SSAnne_2F_Room6_Object1_Text, MSGBOX_NPC
    end
TH12_SSAnne_2F_Room6_Object1_Text:
	.string "The CAPTAIN said he's awfully sick.\n"
	.string "He was all pale.$"

TH12_SSAnne_3F_Corridor_Object0::
    msgbox TH12_SSAnne_3F_Corridor_Object0_Text, MSGBOX_NPC
    end
TH12_SSAnne_3F_Corridor_Object0_Text:
	.string "Our CAPTAIN is a sword master.\n"
	.string "He's awesome at using CUT.\p"
	.string "They say he even teaches CUT\n"
	.string "to POKéMON!$"

TH12_SSAnne_B1F_Room1_Object0::
    trainerbattle_single TRAINER_TH12_FISHERMAN_BARNY, TH12_SSAnne_B1F_Room1_Object0_Intro, TH12_SSAnne_B1F_Room1_Object0_Defeat
    msgbox TH12_SSAnne_B1F_Room1_Object0_After, MSGBOX_AUTOCLOSE
    end

TH12_SSAnne_B1F_Room1_Object0_Intro:
	.string "Hello, stranger!\p"
	.string "I can't tell if you're from the seas\n"
	.string "or mountains, but stop and chat.\p"
	.string "All my POKéMON are from the sea.$"

TH12_SSAnne_B1F_Room1_Object0_Defeat:
	.string "Darn!\n"
	.string "I let that one get away!$"

TH12_SSAnne_B1F_Room1_Object0_After:
	.string "I was going to make you my\n"
	.string "assistant, too!$"

TH12_SSAnne_B1F_Room1_Object1::
    trainerbattle_single TRAINER_TH12_SAILOR_PHILLIP, TH12_SSAnne_B1F_Room1_Object1_Intro, TH12_SSAnne_B1F_Room1_Object1_Defeat
    msgbox TH12_SSAnne_B1F_Room1_Object1_After, MSGBOX_AUTOCLOSE
    end

TH12_SSAnne_B1F_Room1_Object1_Intro:
	.string "Matey, you're walking the plank if\n"
	.string "you lose!$"

TH12_SSAnne_B1F_Room1_Object1_Defeat:
	.string "Argh!\n"
	.string "Beaten by a kid!$"

TH12_SSAnne_B1F_Room1_Object1_After:
	.string "When we're out at sea, jellyfish\n"
	.string "POKéMON sometimes drift by.$"

TH12_SSAnne_B1F_Room2_Object0::
    trainerbattle_single TRAINER_TH12_SAILOR_HUEY, TH12_SSAnne_B1F_Room2_Object0_Intro, TH12_SSAnne_B1F_Room2_Object0_Defeat
    msgbox TH12_SSAnne_B1F_Room2_Object0_After, MSGBOX_AUTOCLOSE
    end

TH12_SSAnne_B1F_Room2_Object0_Intro:
	.string "Even us sailors have POKéMON, too!$"

TH12_SSAnne_B1F_Room2_Object0_Defeat:
	.string "Okay, you're not bad.$"

TH12_SSAnne_B1F_Room2_Object0_After:
	.string "We caught all our POKéMON while\n"
	.string "we were out at sea.$"

TH12_SSAnne_B1F_Room2_Object1::
    lock
    giveitem ITEM_TM44
    goto_if_eq VAR_RESULT, FALSE, TH12_RewardBagFull
    setflag FLAG_TH12_PICKUP_23
    removeobject VAR_LAST_TALKED
    release
    end

TH12_SSAnne_B1F_Room3_Object0::
    trainerbattle_single TRAINER_TH12_SAILOR_DYLAN, TH12_SSAnne_B1F_Room3_Object0_Intro, TH12_SSAnne_B1F_Room3_Object0_Defeat
    msgbox TH12_SSAnne_B1F_Room3_Object0_After, MSGBOX_AUTOCLOSE
    end

TH12_SSAnne_B1F_Room3_Object0_Intro:
	.string "I like feisty kids like you!$"

TH12_SSAnne_B1F_Room3_Object0_Defeat:
	.string "Argh!\n"
	.string "Lost it!$"

TH12_SSAnne_B1F_Room3_Object0_After:
	.string "Sea POKéMON live in deep water.\n"
	.string "You'll need a ROD to fish them up!$"

TH12_SSAnne_B1F_Room3_Object1::
    lock
    giveitem ITEM_ETHER
    goto_if_eq VAR_RESULT, FALSE, TH12_RewardBagFull
    setflag FLAG_TH12_PICKUP_24
    removeobject VAR_LAST_TALKED
    release
    end

TH12_SSAnne_B1F_Room4_Object0::
    trainerbattle_single TRAINER_TH12_SAILOR_DUNCAN, TH12_SSAnne_B1F_Room4_Object0_Intro, TH12_SSAnne_B1F_Room4_Object0_Defeat
    msgbox TH12_SSAnne_B1F_Room4_Object0_After, MSGBOX_AUTOCLOSE
    end

TH12_SSAnne_B1F_Room4_Object0_Intro:
	.string "Come on, then!\n"
	.string "My sailor's pride is at stake!$"

TH12_SSAnne_B1F_Room4_Object0_Defeat:
	.string "Your spirit sank me!$"

TH12_SSAnne_B1F_Room4_Object0_After:
	.string "Did you see the FISHING GURU in\n"
	.string "VERMILION CITY?$"

TH12_SSAnne_B1F_Room4_Object1::
    trainerbattle_single TRAINER_TH12_SAILOR_LEONARD, TH12_SSAnne_B1F_Room4_Object1_Intro, TH12_SSAnne_B1F_Room4_Object1_Defeat
    msgbox TH12_SSAnne_B1F_Room4_Object1_After, MSGBOX_AUTOCLOSE
    end

TH12_SSAnne_B1F_Room4_Object1_Intro:
	.string "You know what they say about\n"
	.string "sailors and battling!$"

TH12_SSAnne_B1F_Room4_Object1_Defeat:
	.string "Right!\n"
	.string "Good battle, mate!$"

TH12_SSAnne_B1F_Room4_Object1_After:
	.string "Hahaha!\n"
	.string "Want to be a sailor, mate?$"

TH12_SSAnne_B1F_Room5_Object0::
    msgbox TH12_SSAnne_B1F_Room5_Object0_Text, MSGBOX_NPC
    end
TH12_SSAnne_B1F_Room5_Object0_Text:
	.string "My buddy MACHOKE is super strong!\p"
	.string "He has enough STRENGTH to move\n"
	.string "big rocks!$"

TH12_SSAnne_B1F_Room5_Object1::
    lock
    faceplayer
    playmoncry SPECIES_MACHOKE, CRY_MODE_NORMAL
    msgbox TH12_SSAnne_B1F_Room5_Object1_Text
    waitmoncry
    release
    end
TH12_SSAnne_B1F_Room5_Object1_Text:
	.string "MACHOKE: Gwoh! Goggoh!$"

TH12_SSAnne_B1F_Room5_Object2::
    lock
    giveitem ITEM_SUPER_POTION
    goto_if_eq VAR_RESULT, FALSE, TH12_RewardBagFull
    setflag FLAG_TH12_PICKUP_25
    removeobject VAR_LAST_TALKED
    release
    end

TH12_SSAnne_CaptainsOffice_Sign0::
    msgbox TH12_SSAnne_CaptainsOffice_Sign0_Text, MSGBOX_SIGN
    end
TH12_SSAnne_CaptainsOffice_Sign0_Text:
	.string "How to Conquer Seasickness…\n"
	.string "The CAPTAIN's reading this!$"

TH12_SSAnne_CaptainsOffice_Sign1::
    msgbox TH12_SSAnne_CaptainsOffice_Sign1_Text, MSGBOX_SIGN
    end
TH12_SSAnne_CaptainsOffice_Sign1_Text:
	.string "Yuck!\n"
	.string "Shouldn't have looked!$"

TH12_SSAnne_CaptainsOffice_Sign2::
    msgbox TH12_SSAnne_CaptainsOffice_Sign2_Text, MSGBOX_SIGN
    end
TH12_SSAnne_CaptainsOffice_Sign2_Text:
	.string "How to Conquer Seasickness…\n"
	.string "The CAPTAIN's reading this!$"

TH12_SSAnne_Deck_Object0::
    trainerbattle_single TRAINER_TH12_SAILOR_TREVOR, TH12_SSAnne_Deck_Object0_Intro, TH12_SSAnne_Deck_Object0_Defeat
    msgbox TH12_SSAnne_Deck_Object0_After, MSGBOX_AUTOCLOSE
    end

TH12_SSAnne_Deck_Object0_Intro:
	.string "Ahoy, there!\n"
	.string "Are you seasick?$"

TH12_SSAnne_Deck_Object0_Defeat:
	.string "I was just careless!$"

TH12_SSAnne_Deck_Object0_After:
	.string "My pa said there are 100 kinds of\n"
	.string "POKéMON. I think there are more.$"

TH12_SSAnne_Deck_Object1::
    msgbox TH12_SSAnne_Deck_Object1_Text, MSGBOX_NPC
    end
TH12_SSAnne_Deck_Object1_Text:
	.string "Urf… I feel ill…\p"
	.string "I got seasick, so I stepped out to\n"
	.string "get some air…$"

TH12_SSAnne_Deck_Object2::
    msgbox TH12_SSAnne_Deck_Object2_Text, MSGBOX_NPC
    end
TH12_SSAnne_Deck_Object2_Text:
	.string "Whew!\n"
	.string "Scrubbing decks is hard work!$"

TH12_SSAnne_Deck_Object3::
    trainerbattle_single TRAINER_TH12_SAILOR_EDMOND, TH12_SSAnne_Deck_Object3_Intro, TH12_SSAnne_Deck_Object3_Defeat
    msgbox TH12_SSAnne_Deck_Object3_After, MSGBOX_AUTOCLOSE
    end

TH12_SSAnne_Deck_Object3_Intro:
	.string "Hey, matey!\p"
	.string "Let's do a little jig!$"

TH12_SSAnne_Deck_Object3_Defeat:
	.string "You're impressive!$"

TH12_SSAnne_Deck_Object3_After:
	.string "How many kinds of POKéMON do you\n"
	.string "think there are in this big world?$"

TH12_SSAnne_Deck_Object4::
    msgbox TH12_SSAnne_Deck_Object4_Text, MSGBOX_NPC
    end
TH12_SSAnne_Deck_Object4_Text:
    .string "Enjoy the sea air! We are staying\nin port while the crew investigates\lour unusual cargo stowaways.$"

TH12_Ship_Sailor::
    msgbox TH12_Ship_Sailor_Text, MSGBOX_NPC
    end
TH12_Ship_Sailor_Text:
    .string "Welcome aboard! Our ship will stay\nat port while you explore KANTO.$"

TH12_SSAnne_Kitchen_Object0::
    msgbox TH12_SSAnne_Kitchen_Object0_Text, MSGBOX_NPC
    end
TH12_SSAnne_Kitchen_Object0_Text:
	.string "You, mon petit!\n"
	.string "We're busy here!\l"
	.string "Out of the way!$"

TH12_SSAnne_Kitchen_Object1::
    msgbox TH12_SSAnne_Kitchen_Object1_Text, MSGBOX_NPC
    end
TH12_SSAnne_Kitchen_Object1_Text:
	.string "I saw an odd BERRY in the trash.\n"
	.string "I wonder what that was?$"

TH12_SSAnne_Kitchen_Object2::
    msgbox TH12_SSAnne_Kitchen_Object2_Text, MSGBOX_NPC
    end
TH12_SSAnne_Kitchen_Object2_Text:
	.string "I'm so busy I'm getting dizzy!\n"
	.string "You have to give me room here!$"

TH12_SSAnne_Kitchen_Object3::
    msgbox TH12_SSAnne_Kitchen_Object3_Text, MSGBOX_NPC
    end
TH12_SSAnne_Kitchen_Object3_Text:
    .string "I am le CHEF! Tonight we serve\nfresh vegetables and BERRY tart.\pRecipes from KANTO, JOHTO, and\nHOENN, all at one table!$"

TH12_SSAnne_Kitchen_Object4::
    msgbox TH12_SSAnne_Kitchen_Object4_Text, MSGBOX_NPC
    end
TH12_SSAnne_Kitchen_Object4_Text:
    .string "Fresh berries for the passengers!\nThe red ones are wonderfully sweet.$"

TH12_SSAnne_Kitchen_Object5::
    msgbox TH12_SSAnne_Kitchen_Object5_Text, MSGBOX_NPC
    end
TH12_SSAnne_Kitchen_Object5_Text:
    .string "The captain prefers mild meals.\nRough seas upset his stomach.$"

TH12_SSAnne_Kitchen_Object6::
    msgbox TH12_SSAnne_Kitchen_Object6_Text, MSGBOX_NPC
    end
TH12_SSAnne_Kitchen_Object6_Text:
    .string "These crates came from HOENN.\nWe found tiny footprints on one!$"

TH12_SSAnne_Kitchen_Object7::
    lock
    giveitem ITEM_GREAT_BALL
    goto_if_eq VAR_RESULT, FALSE, TH12_RewardBagFull
    setflag FLAG_TH12_PICKUP_27
    removeobject VAR_LAST_TALKED
    release
    end

TH12_VermilionCity_Gym_Object1::
    trainerbattle_single TRAINER_TH12_ENGINEER_BAILY, TH12_VermilionCity_Gym_Object1_Intro, TH12_VermilionCity_Gym_Object1_Defeat
    msgbox TH12_VermilionCity_Gym_Object1_After, MSGBOX_AUTOCLOSE
    end

TH12_VermilionCity_Gym_Object1_Intro:
	.string "I'm a lightweight, but I'm good\n"
	.string "with electricity!\p"
	.string "That's why I joined this GYM.$"

TH12_VermilionCity_Gym_Object1_Defeat:
	.string "Fried!$"

TH12_VermilionCity_Gym_Object1_After:
	.string "Okay, I'll talk!\p"
	.string "LT. SURGE said he hid door\n"
	.string "switches inside something.$"

TH12_VermilionCity_Gym_Object2::
    trainerbattle_single TRAINER_TH12_SAILOR_DWAYNE, TH12_VermilionCity_Gym_Object2_Intro, TH12_VermilionCity_Gym_Object2_Defeat
    msgbox TH12_VermilionCity_Gym_Object2_After, MSGBOX_AUTOCLOSE
    end

TH12_VermilionCity_Gym_Object2_Intro:
	.string "This is no place for kids!\n"
	.string "Not even if you're good!$"

TH12_VermilionCity_Gym_Object2_Defeat:
	.string "Wow!\n"
	.string "Surprised me!$"

TH12_VermilionCity_Gym_Object2_After:
	.string "LT. SURGE installed the traps in\n"
	.string "the GYM himself.\p"
	.string "He set up double locks everywhere.\n"
	.string "Let me give you a hint.\p"
	.string "When you open the first lock, the\n"
	.string "second lock is right next to it.$"

TH12_VermilionCity_Gym_Object4::
    trainerbattle_single TRAINER_TH12_GENTLEMAN_TUCKER, TH12_VermilionCity_Gym_Object4_Intro, TH12_VermilionCity_Gym_Object4_Defeat
    msgbox TH12_VermilionCity_Gym_Object4_After, MSGBOX_AUTOCLOSE
    end

TH12_VermilionCity_Gym_Object4_Intro:
	.string "When I was in the Army, LT. SURGE\n"
	.string "was my strict CO.\p"
	.string "He was a hard taskmaster.$"

TH12_VermilionCity_Gym_Object4_Defeat:
	.string "Stop!\n"
	.string "You're very good!$"

TH12_VermilionCity_Gym_Object4_After:
	.string "It's not easy opening that door.\p"
	.string "LT. SURGE was always famous for\n"
	.string "his cautious nature in the Army.$"
