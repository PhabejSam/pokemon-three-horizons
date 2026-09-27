TH12_Route24_Object1::
    trainerbattle_single TRAINER_TH12_CAMPER_ETHAN, TH12_Route24_Object1_Intro, TH12_Route24_Object1_Defeat
    msgbox TH12_Route24_Object1_After, MSGBOX_AUTOCLOSE
    end

TH12_Route24_Object1_Intro:
	.string "Okay! I'm No. 5!\n"
	.string "I'll stomp you!$"

TH12_Route24_Object1_Defeat:
	.string "Whoa!\n"
	.string "Too much!$"

TH12_Route24_Object1_After:
	.string "I did my best. I have no regrets!$"

TH12_Route24_Object2::
    trainerbattle_single TRAINER_TH12_LASS_RELI, TH12_Route24_Object2_Intro, TH12_Route24_Object2_Defeat
    msgbox TH12_Route24_Object2_After, MSGBOX_AUTOCLOSE
    end

TH12_Route24_Object2_Intro:
	.string "I'm No. 4!\n"
	.string "Getting tired?$"

TH12_Route24_Object2_Defeat:
	.string "I lost, too!$"

TH12_Route24_Object2_After:
	.string "I did my best, so I've no regrets!$"

TH12_Route24_Object3::
    trainerbattle_single TRAINER_TH12_YOUNGSTER_TIMMY, TH12_Route24_Object3_Intro, TH12_Route24_Object3_Defeat
    msgbox TH12_Route24_Object3_After, MSGBOX_AUTOCLOSE
    end

TH12_Route24_Object3_Intro:
	.string "Here's No. 3!\n"
	.string "I won't be easy!$"

TH12_Route24_Object3_Defeat:
	.string "Ow!\n"
	.string "Stomped flat!$"

TH12_Route24_Object3_After:
	.string "I did my best. I have no regrets!$"

TH12_Route24_Object4::
    trainerbattle_single TRAINER_TH12_LASS_ALI, TH12_Route24_Object4_Intro, TH12_Route24_Object4_Defeat
    msgbox TH12_Route24_Object4_After, MSGBOX_AUTOCLOSE
    end

TH12_Route24_Object4_Intro:
	.string "I'm second!\n"
	.string "Now it's serious!$"

TH12_Route24_Object4_Defeat:
	.string "How could I lose?$"

TH12_Route24_Object4_After:
	.string "I did my best. I have no regrets!$"

TH12_Route24_Object5::
    trainerbattle_single TRAINER_TH12_BUG_CATCHER_CALE, TH12_Route24_Object5_Intro, TH12_Route24_Object5_Defeat
    msgbox TH12_Route24_Object5_After, MSGBOX_AUTOCLOSE
    end

TH12_Route24_Object5_Intro:
	.string "People call this the NUGGET\n"
	.string "BRIDGE!\p"
	.string "Beat us five TRAINERS and win\n"
	.string "a fabulous prize!\p"
	.string "Think you got what it takes?$"

TH12_Route24_Object5_Defeat:
	.string "Whoo!\n"
	.string "Good stuff!$"

TH12_Route24_Object5_After:
	.string "I did my best. I have no regrets!$"

TH12_Route24_Object6::
    trainerbattle_single TRAINER_TH12_CAMPER_SHANE, TH12_Route24_Object6_Intro, TH12_Route24_Object6_Defeat
    msgbox TH12_Route24_Object6_After, MSGBOX_AUTOCLOSE
    end

TH12_Route24_Object6_Intro:
	.string "I saw your feat from the grass!$"

TH12_Route24_Object6_Defeat:
	.string "I thought not!$"

TH12_Route24_Object6_After:
	.string "I hid because the people on the\n"
	.string "bridge frightened me.$"

TH12_Route24_Object7::
    lock
    giveitem ITEM_TM45
    goto_if_eq VAR_RESULT, FALSE, TH12_BillSlice_BagFull
    setflag FLAG_TH12_PICKUP_2
    removeobject VAR_LAST_TALKED
    release
    end

TH12_Route25_Object0::
    trainerbattle_single TRAINER_TH12_HIKER_FRANKLIN, TH12_Route25_Object0_Intro, TH12_Route25_Object0_Defeat
    msgbox TH12_Route25_Object0_After, MSGBOX_AUTOCLOSE
    end

TH12_Route25_Object0_Intro:
	.string "I just got down from MT. MOON,\n"
	.string "but I've still got gas in the tank!$"

TH12_Route25_Object0_Defeat:
	.string "You worked hard!$"

TH12_Route25_Object0_After:
	.string "Drat!\n"
	.string "A ZUBAT bit me back in that cave.$"

TH12_Route25_Object1::
    trainerbattle_single TRAINER_TH12_YOUNGSTER_JOEY, TH12_Route25_Object1_Intro, TH12_Route25_Object1_Defeat
    msgbox TH12_Route25_Object1_After, MSGBOX_AUTOCLOSE
    end

TH12_Route25_Object1_Intro:
	.string "Local TRAINERS come here to\n"
	.string "practice.$"

TH12_Route25_Object1_Defeat:
	.string "You're decent.$"

TH12_Route25_Object1_After:
	.string "All POKéMON have weaknesses.\n"
	.string "Even the strongest ones.\p"
	.string "That's why it's best to raise\n"
	.string "POKéMON of different types.$"

TH12_Route25_Object2::
    trainerbattle_single TRAINER_TH12_HIKER_WAYNE, TH12_Route25_Object2_Intro, TH12_Route25_Object2_Defeat
    msgbox TH12_Route25_Object2_After, MSGBOX_AUTOCLOSE
    end

TH12_Route25_Object2_Intro:
	.string "You're going to see BILL?\n"
	.string "First, we battle!$"

TH12_Route25_Object2_Defeat:
	.string "You're something.$"

TH12_Route25_Object2_After:
	.string "The trail below is a shortcut to\n"
	.string "CERULEAN CITY.$"

TH12_Route25_Object3::
    trainerbattle_single TRAINER_TH12_YOUNGSTER_DAN, TH12_Route25_Object3_Intro, TH12_Route25_Object3_Defeat
    msgbox TH12_Route25_Object3_After, MSGBOX_AUTOCLOSE
    end

TH12_Route25_Object3_Intro:
	.string "Dad took me to a great party on\n"
	.string "the S.S. ANNE at VERMILION CITY.$"

TH12_Route25_Object3_Defeat:
	.string "I'm not mad!$"

TH12_Route25_Object3_After:
	.string "On the S.S. ANNE, I saw TRAINERS\n"
	.string "from around the world.$"

TH12_Route25_Object4::
    trainerbattle_single TRAINER_TH12_PICNICKER_KELSEY, TH12_Route25_Object4_Intro, TH12_Route25_Object4_Defeat
    msgbox TH12_Route25_Object4_After, MSGBOX_AUTOCLOSE
    end

TH12_Route25_Object4_Intro:
	.string "Hi!\n"
	.string "My boyfriend is cool!$"

TH12_Route25_Object4_Defeat:
	.string "My conditioning isn't the best…$"

TH12_Route25_Object4_After:
	.string "I wish my boyfriend was as good\n"
	.string "as you.$"

TH12_Route25_Object5::
    trainerbattle_single TRAINER_TH12_HIKER_NOB, TH12_Route25_Object5_Intro, TH12_Route25_Object5_Defeat
    msgbox TH12_Route25_Object5_After, MSGBOX_AUTOCLOSE
    end

TH12_Route25_Object5_Intro:
	.string "I'm off to see a POKéMANIAC's\n"
	.string "collection at the cape.$"

TH12_Route25_Object5_Defeat:
	.string "You done got me, and real good,\n"
	.string "too!$"

TH12_Route25_Object5_After:
	.string "The POKéMANIAC sure lives up to\n"
	.string "his name.\p"
	.string "His collection includes many rare\n"
	.string "species of POKéMON.$"

TH12_Route25_Object6::
    trainerbattle_single TRAINER_TH12_CAMPER_FLINT, TH12_Route25_Object6_Intro, TH12_Route25_Object6_Defeat
    msgbox TH12_Route25_Object6_After, MSGBOX_AUTOCLOSE
    end

TH12_Route25_Object6_Intro:
	.string "I'm a cool guy.\n"
	.string "I've got a girlfriend!$"

TH12_Route25_Object6_Defeat:
	.string "Aww, darn…$"

TH12_Route25_Object6_After:
	.string "Oh, well.\n"
	.string "My girlfriend will cheer me up.$"

TH12_Route25_Object7::
    trainerbattle_single TRAINER_TH12_YOUNGSTER_CHAD, TH12_Route25_Object7_Intro, TH12_Route25_Object7_Defeat
    msgbox TH12_Route25_Object7_After, MSGBOX_AUTOCLOSE
    end

TH12_Route25_Object7_Intro:
	.string "I had this feeling…\n"
	.string "I knew I had to battle you!$"

TH12_Route25_Object7_Defeat:
	.string "I knew I'd lose, too!$"

TH12_Route25_Object7_After:
	.string "If your POKéMON gets confused,\n"
	.string "switch it out.\p"
	.string "That's a good tactic.$"

TH12_Route25_Object8::
    trainerbattle_single TRAINER_TH12_LASS_HALEY, TH12_Route25_Object8_Intro, TH12_Route25_Object8_Defeat
    msgbox TH12_Route25_Object8_After, MSGBOX_AUTOCLOSE
    end

TH12_Route25_Object8_Intro:
	.string "My friend has many cute POKéMON.\n"
	.string "I'm so jealous!$"

TH12_Route25_Object8_Defeat:
	.string "I'm not so jealous!$"

TH12_Route25_Object8_After:
	.string "You came from MT. MOON?\n"
	.string "May I have a CLEFAIRY?$"

TH12_Route25_Object9::
    lock
    giveitem ITEM_TM43
    goto_if_eq VAR_RESULT, FALSE, TH12_BillSlice_BagFull
    setflag FLAG_TH12_PICKUP_4
    removeobject VAR_LAST_TALKED
    release
    end

TH12_Route25_Object11::
    msgbox TH12_Route25_Object11_Text, MSGBOX_NPC
    end
TH12_Route25_Object11_Text:
    .string "We came here to watch the sea.\nBILL studies the POKéMON along it!$"

TH12_Route25_Object12::
    msgbox TH12_Route25_Object12_Text, MSGBOX_NPC
    end
TH12_Route25_Object12_Text:
	.string "Hello, are you here alone?\p"
	.string "If you're out at CERULEAN's cape…\n"
	.string "Well, it should be as a couple.$"

TH12_Route25_Sign0::
    msgbox TH12_Route25_Sign0_Text, MSGBOX_SIGN
    end
TH12_Route25_Sign0_Text:
	.string "SEA COTTAGE\n"
	.string "BILL lives here!$"

TH12_BillSlice_BagFull:
    msgbox TH12_BillSlice_BagFullText
    release
    end
TH12_BillSlice_BagFullText:
    .string "Please make room in your BAG,\nthen speak to me again.$"
