TH12_Surge_OnLoad::
    call_if_set FLAG_TH12_SURGE_OPEN, TH12_Surge_BeamsOff
    return
TH12_Surge_OnEntry::
    special TH12_InitSurgeSwitches
    return

TH12_Surge_BeamsOff::
	setmetatile 3, 6, METATILE_VermilionGym_Beam_Node_TopLeft_Off, 1
	setmetatile 4, 6, METATILE_VermilionGym_Beam_Node_TopLeft_Edge_Off, 0
	setmetatile 5, 6, METATILE_VermilionGym_Floor, 0
	setmetatile 6, 6, METATILE_VermilionGym_Beam_Node_TopRight_Edge_Off, 0
	setmetatile 7, 6, METATILE_VermilionGym_Beam_Node_TopRight_Off, 1
	setmetatile 3, 7, METATILE_VermilionGym_Beam_Node_BottomLeft_Off, 1
	setmetatile 4, 7, METATILE_VermilionGym_Beam_Node_BottomLeft_Edge_Off, 0
	setmetatile 5, 7, METATILE_VermilionGym_Floor, 0
	setmetatile 6, 7, METATILE_VermilionGym_Beam_Node_BottomRight_Edge_Off, 0
	setmetatile 7, 7, METATILE_VermilionGym_Beam_Node_BottomRight_Off, 1
	return

TH12_Surge_BeamsOn::
	setmetatile 3, 6, METATILE_VermilionGym_Beam_Node_TopLeft_On, 1
	setmetatile 4, 6, METATILE_VermilionGym_Beam_Node_TopLeft_Edge_On, 1
	setmetatile 5, 6, METATILE_VermilionGym_Beam_MidTop, 1
	setmetatile 6, 6, METATILE_VermilionGym_Beam_Node_TopRight_Edge_On, 1
	setmetatile 7, 6, METATILE_VermilionGym_Beam_Node_TopRight_On, 1
	setmetatile 3, 7, METATILE_VermilionGym_Beam_Node_BottomLeft_On, 1
	setmetatile 4, 7, METATILE_VermilionGym_Beam_Node_BottomLeft_Edge_On, 1
	setmetatile 5, 7, METATILE_VermilionGym_Beam_MidBottom, 1
	setmetatile 6, 7, METATILE_VermilionGym_Beam_Node_BottomRight_Edge_On, 1
	setmetatile 7, 7, METATILE_VermilionGym_Beam_Node_BottomRight_On, 1
	return

TH12_Surge_BeamsHalf::
	setmetatile 3, 6, METATILE_VermilionGym_Beam_Node_TopLeft_HalfOn, 1
	setmetatile 4, 6, METATILE_VermilionGym_Beam_Node_TopLeft_Edge_HalfOn, 1
	setmetatile 5, 6, METATILE_VermilionGym_Beam_MidTop_HalfOn, 1
	setmetatile 6, 6, METATILE_VermilionGym_Beam_Node_TopRight_Edge_HalfOn, 1
	setmetatile 7, 6, METATILE_VermilionGym_Beam_Node_TopRight_HalfOn, 1
	setmetatile 3, 7, METATILE_VermilionGym_Beam_Node_BottomLeft_HalfOn, 1
	setmetatile 4, 7, METATILE_VermilionGym_Beam_Node_BottomLeft_Edge_HalfOn, 1
	setmetatile 5, 7, METATILE_VermilionGym_Beam_MidBottom_HalfOn, 1
	setmetatile 6, 7, METATILE_VermilionGym_Beam_Node_BottomRight_Edge_HalfOn, 1
	setmetatile 7, 7, METATILE_VermilionGym_Beam_Node_BottomRight_HalfOn, 1
	return

TH12_Surge_Can1::
    lockall
    setvar VAR_0x8008, 1
    goto TH12_Surge_Switch

TH12_Surge_Can2::
    lockall
    setvar VAR_0x8008, 2
    goto TH12_Surge_Switch

TH12_Surge_Can3::
    lockall
    setvar VAR_0x8008, 3
    goto TH12_Surge_Switch

TH12_Surge_Can4::
    lockall
    setvar VAR_0x8008, 4
    goto TH12_Surge_Switch

TH12_Surge_Can5::
    lockall
    setvar VAR_0x8008, 5
    goto TH12_Surge_Switch

TH12_Surge_Can6::
    lockall
    setvar VAR_0x8008, 6
    goto TH12_Surge_Switch

TH12_Surge_Can7::
    lockall
    setvar VAR_0x8008, 7
    goto TH12_Surge_Switch

TH12_Surge_Can8::
    lockall
    setvar VAR_0x8008, 8
    goto TH12_Surge_Switch

TH12_Surge_Can9::
    lockall
    setvar VAR_0x8008, 9
    goto TH12_Surge_Switch

TH12_Surge_Can10::
    lockall
    setvar VAR_0x8008, 10
    goto TH12_Surge_Switch

TH12_Surge_Can11::
    lockall
    setvar VAR_0x8008, 11
    goto TH12_Surge_Switch

TH12_Surge_Can12::
    lockall
    setvar VAR_0x8008, 12
    goto TH12_Surge_Switch

TH12_Surge_Can13::
    lockall
    setvar VAR_0x8008, 13
    goto TH12_Surge_Switch

TH12_Surge_Can14::
    lockall
    setvar VAR_0x8008, 14
    goto TH12_Surge_Switch

TH12_Surge_Can15::
    lockall
    setvar VAR_0x8008, 15
    goto TH12_Surge_Switch
TH12_Surge_Switch::
    special TH12_CheckSurgeSwitch
    goto_if_eq VAR_RESULT, 1, TH12_Surge_First
    goto_if_eq VAR_RESULT, 2, TH12_Surge_Open
    goto_if_eq VAR_RESULT, 3, TH12_Surge_Reset
    goto_if_eq VAR_RESULT, 4, TH12_Surge_AlreadyOpen
    msgbox TH12_Surge_TrashText
    releaseall
    end
TH12_Surge_First:
    call TH12_Surge_BeamsHalf
    special DrawWholeMapView
    playse SE_PIN
    msgbox TH12_Surge_FirstText
    releaseall
    end
TH12_Surge_Open:
    call TH12_Surge_BeamsOff
    special DrawWholeMapView
    playse SE_UNLOCK
    msgbox TH12_Surge_OpenText
    releaseall
    end
TH12_Surge_Reset:
    call TH12_Surge_BeamsOn
    special DrawWholeMapView
    msgbox TH12_Surge_ResetText
    releaseall
    end
TH12_Surge_AlreadyOpen:
    msgbox TH12_Surge_OpenText
    releaseall
    end
TH12_Surge_TrashText:
    .string "Only trash. No switch here.$"
TH12_Surge_FirstText:
    .string "A switch! The first lock opened.\nThe second switch is in a can\ldirectly beside this one.$"
TH12_Surge_ResetText:
    .string "The locks reset!\nThe switches have moved.$"
TH12_Surge_OpenText:
    .string "Both locks are open!$"

TH12_Surge_Guide::
    goto_if_set FLAG_BADGE03_GET, TH13_SurgeGuide_Won
    msgbox TH12_Surge_GuideText, MSGBOX_NPC
    end
TH13_SurgeGuide_Won:
    msgbox TH13_SurgeGuide_WonText, MSGBOX_NPC
    end
TH13_SurgeGuide_WonText:
    .string "You beat LT. SURGE! That's a\nwell-earned THUNDER BADGE!$"
TH12_Surge_GuideText:
    .string "LT. SURGE uses five ELECTRIC types!\nGROUND attacks can help.\pFind a hidden switch, then check\na can directly above, below,\lleft or right of it.$"
TH12_Surge_Pillar::
    msgbox TH12_Surge_PillarText, MSGBOX_SIGN
    end
TH12_Surge_PillarText:
    .string "VERMILION POKéMON GYM\nLEADER: LT. SURGE\lThe Lightning American!$"

TH12_Surge_Battle::
    lock
    faceplayer
    goto_if_set FLAG_BADGE03_GET, TH12_Surge_Reward
    trainerbattle_single TRAINER_TH12_LEADER_SURGE, TH12_Surge_Intro, TH12_Surge_Defeat, TH12_Surge_Reward
    goto TH12_Surge_Reward
TH12_Surge_Reward::
    lockall
    goto_if_set FLAG_BADGE03_GET, TH12_Surge_TM
    setflag FLAG_BADGE03_GET
    setflag FLAG_TH12_SURGE_OPEN
    playfanfare MUS_OBTAIN_BADGE
    msgbox TH12_Surge_BadgeText
    waitfanfare
TH12_Surge_TM:
    goto_if_set FLAG_TH12_SURGE_TM, TH12_Surge_After
    giveitem ITEM_TM34
    goto_if_eq VAR_RESULT, FALSE, TH12_RewardBagFull
    setflag FLAG_TH12_SURGE_TM
TH12_Surge_After:
    msgbox TH12_Surge_AfterText
    releaseall
    end
TH12_Surge_Intro:
    .string "Hey, kid! You made it through my\nsecurity system!\pMy ELECTRIC POKéMON are ready\nto give you a real jolt!"
    .string "\pShow me your team's fighting spirit!$"
TH12_Surge_Defeat:
    .string "Now that is a strong team!\nYou have earned my respect!$"
TH12_Surge_BadgeText:
    .string "{PLAYER} received the\nTHUNDER BADGE from LT. SURGE!$"
TH12_Surge_AfterText:
    .string "TM34 teaches SHOCK WAVE!\nIt will not miss its target.\pYour TMs are reusable. Train hard\nand show every partner some care!$"

TH12_Chapter_End::
    lock
    faceplayer
    goto_if_unset FLAG_BADGE03_GET, TH12_Chapter_NotYet
    goto_if_set FLAG_TH12_COMPLETE, TH12_Chapter_Repeat
    msgbox TH12_Chapter_EndText
    setflag FLAG_TH12_COMPLETE
    release
    end
TH12_Chapter_Repeat:
    msgbox TH12_Chapter_RepeatText
    release
    end
TH12_Chapter_NotYet:
    msgbox TH12_Chapter_NotYetText
    release
    end
TH12_Chapter_NotYetText:
    .string "OAK, ELM and BIRCH sent me to\ncompare reports from the port.\pVisit BILL and the S.S. ANNE, then\ntry VERMILION GYM. Tell me how\lyour third badge challenge goes!$"
TH12_Chapter_EndText:
    .string "Three badges! Your port reports\nhave reached the professors.\pHead east to ROUTE 11. DIGLETT'S\nCAVE leads to OAK's ROUTE 2 aide.\pKeep comparing what you see.\nThere is much we don't understand.$"
TH12_Chapter_RepeatText:
    .string "OAK's network follows your reports.\nTry ROUTE 11 and DIGLETT'S CAVE.\pThe ROUTE 2 aide can help you\nprepare for the road ahead.$"
