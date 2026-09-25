TH_Journey_Local::
    msgbox TH_Text_JourneyLocal, MSGBOX_NPC
    end

TH_Text_JourneyLocal:
    .string "The path north leads through the forest.\nPEWTER CITY is on the other side.$"

TH_Journey_Tree::
    msgbox TH_Text_JourneyTree, MSGBOX_NPC
    end

TH_Text_JourneyTree:
    .string "This small tree blocks the path.\nThe main trail is still clear.$"

TH_Journey_Sign::
    msgbox TH_Text_JourneySign, MSGBOX_NPC
    end

TH_Text_JourneySign:
    .string "VIRIDIAN CITY - ROUTE 2 - PEWTER CITY\nStay on the trail through the forest.$"

TH_Journey_Closed::
    msgbox TH_Text_JourneyClosed, MSGBOX_NPC
    end

TH_Text_JourneyClosed:
    .string "This building is closed for now.\nYour next challenge is BROCK in PEWTER.$"

TH_Journey_BoundaryEast::
    lockall
    msgbox TH_Text_JourneyEdge
    applymovement OBJ_EVENT_ID_PLAYER, TH_Journey_StepEast
    waitmovement 0
    releaseall
    end
TH_Journey_StepEast:
    walk_right
    step_end

TH_Journey_BoundaryWest::
    lockall
    msgbox TH_Text_JourneyEdge
    applymovement OBJ_EVENT_ID_PLAYER, TH_Journey_StepWest
    waitmovement 0
    releaseall
    end
TH_Journey_StepWest:
    walk_left
    step_end

TH_Text_JourneyEdge:
    .string "This route opens in a later chapter.\nYou can explore as far as BROCK for now.$"

TH_Trainer_RICK::
    trainerbattle_single TRAINER_TH_RICK, TH_Text_RICKIntro, TH_Text_RICKDefeat
    msgbox TH_Text_RICKAfter, MSGBOX_AUTOCLOSE
    end

TH_Text_RICKIntro:
    .string "These bugs are small, but brave!\nLet's see what they can do!$"

TH_Trainer_DOUG::
    trainerbattle_single TRAINER_TH_DOUG, TH_Text_DOUGIntro, TH_Text_DOUGDefeat
    msgbox TH_Text_DOUGAfter, MSGBOX_AUTOCLOSE
    end

TH_Text_DOUGIntro:
    .string "Stay sharp! My bugs know how\nto defend themselves!$"

TH_Trainer_SAMMY::
    trainerbattle_single TRAINER_TH_SAMMY, TH_Text_SAMMYIntro, TH_Text_SAMMYDefeat
    msgbox TH_Text_SAMMYAfter, MSGBOX_AUTOCLOSE
    end

TH_Text_SAMMYIntro:
    .string "You're nearly through the forest.\nOne more battle before you leave?$"

TH_Trainer_ANTHONY::
    trainerbattle_single TRAINER_TH_ANTHONY, TH_Text_ANTHONYIntro, TH_Text_ANTHONYDefeat
    msgbox TH_Text_ANTHONYAfter, MSGBOX_AUTOCLOSE
    end

TH_Text_ANTHONYIntro:
    .string "I've been training under these trees\nall morning. Show me your team!$"

TH_Trainer_CHARLIE::
    trainerbattle_single TRAINER_TH_CHARLIE, TH_Text_CHARLIEIntro, TH_Text_CHARLIEDefeat
    msgbox TH_Text_CHARLIEAfter, MSGBOX_AUTOCLOSE
    end

TH_Text_CHARLIEIntro:
    .string "Hear that buzzing?\nMy partners are eager to battle!$"

TH_Trainer_LIAM::
    trainerbattle_single TRAINER_TH_LIAM, TH_Text_LIAMIntro, TH_Text_LIAMDefeat
    msgbox TH_Text_LIAMAfter, MSGBOX_AUTOCLOSE
    end

TH_Text_LIAMIntro:
    .string "BROCK taught me to stand firm.\nLet's see if you can get past us!$"

TH_Text_TrainerDefeat:
    .string "You and your POKéMON work well together!$"

TH_Text_TrainerAfter:
    .string "I should train a little more.\nGood luck on your journey!$"

TH_Trainer_BROCK::
    trainerbattle_single TRAINER_TH_BROCK, TH_Text_BrockIntro, TH_Text_BrockDefeat, TH_BrockVictory, NO_MUSIC
    goto TH_BrockReward
TH_BrockVictory::
    setflag FLAG_BADGE01_GET
TH_BrockReward:
    goto_if_set FLAG_TH_BROCK_TM, TH_BrockFinished
    giveitem ITEM_TM39
    goto_if_eq VAR_RESULT, FALSE, TH_BrockBagFull
    setflag FLAG_TH_BROCK_TM
TH_BrockFinished:
    msgbox TH_Text_BrockComplete
    release
    end
TH_BrockBagFull:
    msgbox TH_Text_BrockBagFull
    release
    end

TH_Text_BrockIntro:
    .string "I'm BROCK, PEWTER's GYM LEADER.\nMy rock-hard team is ready for you!$"

TH_Text_BrockDefeat:
    .string "Your determination has earned\nyou the BOULDERBADGE!$"

TH_Text_BrockComplete:
    .string "The BOULDERBADGE is yours!\nTake ROCK TOMB as a reminder.\pThe road east leads to MT. MOON.\nCERULEAN and MISTY are beyond it.\pThe caretaker outside has a partner\nwaiting for a patient TRAINER.$"

TH_Text_BrockBagFull:
    .string "You earned the BOULDERBADGE!\nMake room in your BAG for ROCK TOMB,\lthen speak to me again.$"

TH_Journey_Nurse::
    lock
    faceplayer
    msgbox TH_Text_NurseWelcome
    closemessage
    applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterLeft
    waitmovement 0
    hidefollower TRUE
    dofieldeffect FLDEFF_POKECENTER_HEAL
    waitfieldeffect FLDEFF_POKECENTER_HEAL
    applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterDown
    waitmovement 0
    special HealPlayerParty
    special TH_RefreshFollower
    msgbox TH_Text_NurseDone
    release
    end
TH_EventScript_CenterRecovery::
    lockall
    special HealPlayerParty
    special TH_RefreshFollower
    msgbox TH_Text_NurseRecovery
    fadedefaultbgm
    releaseall
    end
TH_Journey_Mart::
    lock
    faceplayer
    msgbox TH_Text_MartWelcome
    pokemart TH_Journey_Shop
    msgbox TH_Text_MartThanks
    release
    end
    .align 2
TH_Journey_Shop:
    .2byte ITEM_POKE_BALL, ITEM_POTION, ITEM_ANTIDOTE, ITEM_PARALYZE_HEAL, ITEM_REPEL, ITEM_SUPER_REPEL, ITEM_ESCAPE_ROPE, ITEM_NONE

TH_Text_NurseWelcome:
    .string "Welcome! Let me help your POKéMON\nrest and recover.$"

TH_Text_NurseDone:
    .string "Your POKéMON are feeling great.\nWe hope to see you again!$"

TH_Text_NurseRecovery:
    .string "You made it back safely.\nYour POKéMON are fully healed.\pRestock and train before trying again.\nYou can do this!$"

TH_Text_MartWelcome:
    .string "Welcome to the POKéMON MART!\nWhat can I get for you?$"

TH_Text_MartThanks:
    .string "Thank you! Come again!$"


@ Individual conversations for the Kanto opening.

TH_Local_ForestNorthGate_0::
    msgbox TH_Local_ForestNorthGate_0Text, MSGBOX_NPC
    end
TH_Local_ForestNorthGate_0Text:
    .string "The forest is behind you!\nPEWTER is just up the road.$"

TH_Local_ForestNorthGate_1::
    msgbox TH_Local_ForestNorthGate_1Text, MSGBOX_NPC
    end
TH_Local_ForestNorthGate_1Text:
    .string "I used to race through these woods.\nNow I stop to listen to the birds.$"

TH_Local_ForestNorthGate_2::
    msgbox TH_Local_ForestNorthGate_2Text, MSGBOX_NPC
    end
TH_Local_ForestNorthGate_2Text:
    .string "A little rest helps after a long walk.\nMy partner agrees.$"

TH_Local_ForestSouthGate_0::
    msgbox TH_Local_ForestSouthGate_0Text, MSGBOX_NPC
    end
TH_Local_ForestSouthGate_0Text:
    .string "Bring ANTIDOTES into the forest.\nSome BUG POKéMON can poison you.$"

TH_Local_ForestSouthGate_1::
    msgbox TH_Local_ForestSouthGate_1Text, MSGBOX_NPC
    end
TH_Local_ForestSouthGate_1Text:
    .string "Watch where the light falls.\nIt makes the leaves look golden.$"

TH_Local_Pewter_0::
    msgbox TH_Local_Pewter_0Text, MSGBOX_NPC
    end
TH_Local_Pewter_0Text:
    .string "The museum has amazing fossils.\nI wonder what they sounded like?$"

TH_Local_Pewter_1::
    msgbox TH_Local_Pewter_1Text, MSGBOX_NPC
    end
TH_Local_Pewter_1Text:
    .string "BROCK trains more than ROCK types.\nWatch out for his ZUBAT!$"

TH_Local_Pewter_2::
    msgbox TH_Local_Pewter_2Text, MSGBOX_NPC
    end
TH_Local_Pewter_2Text:
    .string "This city's stones hold so much\nhistory. I love living here.$"

TH_Local_Pewter_3::
    msgbox TH_Local_Pewter_3Text, MSGBOX_NPC
    end
TH_Local_Pewter_3Text:
    .string "My BUG team grew up in the forest.\nNow we're preparing for the GYM.$"

TH_Local_Pewter_4::
    msgbox TH_Local_Pewter_4Text, MSGBOX_NPC
    end
TH_Local_Pewter_4Text:
    .string "The road east is still being cleared.\nI'm waiting to travel to MT. MOON.$"

TH_Local_Pewter_5::
    msgbox TH_Local_Pewter_5Text, MSGBOX_NPC
    end
TH_Local_Pewter_5Text:
    .string "We're surveying the next route.\nPlease give the workers some room.$"

TH_Local_PewterCenter_0::
    msgbox TH_Local_PewterCenter_0Text, MSGBOX_NPC
    end
TH_Local_PewterCenter_0Text:
    .string "JIGGLYPUFF: Jiggly! Puuuuff!$"

TH_Local_PewterCenter_1::
    msgbox TH_Local_PewterCenter_1Text, MSGBOX_NPC
    end
TH_Local_PewterCenter_1Text:
    .string "I rest here before every GYM visit.\nExperience has taught me that much.$"

TH_Local_PewterCenter_2::
    msgbox TH_Local_PewterCenter_2Text, MSGBOX_NPC
    end
TH_Local_PewterCenter_2Text:
    .string "That JIGGLYPUFF looks ready to sing.\nI'm trying to stay awake!$"

TH_Local_PewterCenter_3::
    msgbox TH_Local_PewterCenter_3Text, MSGBOX_NPC
    end
TH_Local_PewterCenter_3Text:
    .string "Even strong teams need a rest.\nDon't be afraid to come back.$"

TH_Local_PewterCenter_4::
    msgbox TH_Local_PewterCenter_4Text, MSGBOX_NPC
    end
TH_Local_PewterCenter_4Text:
    .string "My friend and I compare our teams.\nWe never agree on a favorite!$"

TH_Local_PewterCenter_5::
    msgbox TH_Local_PewterCenter_5Text, MSGBOX_NPC
    end
TH_Local_PewterCenter_5Text:
    .string "My favorite is whichever POKéMON\nsaved the day in my last battle.$"

TH_Local_PewterGym_0::
    msgbox TH_Local_PewterGym_0Text, MSGBOX_NPC
    end
TH_Local_PewterGym_0Text:
    .string "BROCK has four partners.\nBring a team, not just one trick!$"

TH_Local_PewterMart_0::
    msgbox TH_Local_PewterMart_0Text, MSGBOX_NPC
    end
TH_Local_PewterMart_0Text:
    .string "I always pack a spare POTION.\nIt helps when the trail gets rough.$"

TH_Local_PewterMart_1::
    msgbox TH_Local_PewterMart_1Text, MSGBOX_NPC
    end
TH_Local_PewterMart_1Text:
    .string "ESCAPE ROPE is reusable here.\nKeep one for a quick way outside.$"

TH_Local_ViridianCenter_0::
    msgbox TH_Local_ViridianCenter_0Text, MSGBOX_NPC
    end
TH_Local_ViridianCenter_0Text:
    .string "I watch travelers come and go here.\nEvery journey has its own pace.$"

TH_Local_ViridianCenter_1::
    msgbox TH_Local_ViridianCenter_1Text, MSGBOX_NPC
    end
TH_Local_ViridianCenter_1Text:
    .string "The PC can store your POKéMON.\nYou can swap your team whenever.$"

TH_Local_ViridianCenter_2::
    msgbox TH_Local_ViridianCenter_2Text, MSGBOX_NPC
    end
TH_Local_ViridianCenter_2Text:
    .string "My partner was tired after training.\nJOY made us both feel better.$"

TH_Local_ViridianEntrance_0::
    msgbox TH_Local_ViridianEntrance_0Text, MSGBOX_NPC
    end
TH_Local_ViridianEntrance_0Text:
    .string "Welcome to VIRIDIAN!\nThe CENTER is a good first stop.$"

TH_Local_ViridianEntrance_1::
    msgbox TH_Local_ViridianEntrance_1Text, MSGBOX_NPC
    end
TH_Local_ViridianEntrance_1Text:
    .string "I used to teach people to catch\nPOKéMON. Patience still matters!$"

TH_Local_ViridianEntrance_2::
    msgbox TH_Local_ViridianEntrance_2Text, MSGBOX_NPC
    end
TH_Local_ViridianEntrance_2Text:
    .string "The trees smell lovely after rain.\nTake a moment before rushing off.$"

TH_Local_ViridianEntrance_3::
    msgbox TH_Local_ViridianEntrance_3Text, MSGBOX_NPC
    end
TH_Local_ViridianEntrance_3Text:
    .string "I'm saving up for more POKé BALLS.\nThe forest has so many BUG types!$"

TH_Local_ViridianEntrance_4::
    msgbox TH_Local_ViridianEntrance_4Text, MSGBOX_NPC
    end
TH_Local_ViridianEntrance_4Text:
    .string "The GYM is closed today.\nBROCK in PEWTER is taking challengers.$"

TH_Local_ViridianForest_0::
    msgbox TH_Local_ViridianForest_0Text, MSGBOX_NPC
    end
TH_Local_ViridianForest_0Text:
    .string "Quiet! Listen to all those wings.\nThis forest is full of life.$"

TH_Local_ViridianForest_1::
    msgbox TH_Local_ViridianForest_1Text, MSGBOX_NPC
    end
TH_Local_ViridianForest_1Text:
    .string "I came looking for a PIKACHU.\nNo luck yet, but I'm enjoying the walk.$"

TH_Local_ViridianMart_0::
    msgbox TH_Local_ViridianMart_0Text, MSGBOX_NPC
    end
TH_Local_ViridianMart_0Text:
    .string "The scientist sells training items.\nMints are handy for a new teammate.$"

TH_Text_RICKDefeat:
    .string "Small steps. We'll get stronger!$"
TH_Text_RICKAfter:
    .string "I look for new friends in the grass.\nA good team has to start somewhere.$"

TH_Text_DOUGDefeat:
    .string "Your team broke through!$"
TH_Text_DOUGAfter:
    .string "Hard shells aren't everything.\nI need a better plan.$"

TH_Text_SAMMYDefeat:
    .string "You earned a breather!$"
TH_Text_SAMMYAfter:
    .string "PEWTER is just ahead.\nGood luck with BROCK!$"

TH_Text_ANTHONYDefeat:
    .string "Time for a lunch break!$"
TH_Text_ANTHONYAfter:
    .string "My partner likes the shady spots.\nI guess we have that in common.$"

TH_Text_CHARLIEDefeat:
    .string "That quieted us down!$"
TH_Text_CHARLIEAfter:
    .string "I'll practice a little longer.\nNext time we'll be ready!$"

TH_Text_LIAMDefeat:
    .string "You found a way through!$"
TH_Text_LIAMAfter:
    .string "BROCK's team has a few surprises.\nDon't judge it by the first POKéMON!$"
