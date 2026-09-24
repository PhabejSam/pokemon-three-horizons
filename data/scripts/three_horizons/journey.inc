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
    trainerbattle_single TRAINER_TH_RICK, TH_Text_RICKIntro, TH_Text_TrainerDefeat
    msgbox TH_Text_TrainerAfter, MSGBOX_AUTOCLOSE
    end

TH_Text_RICKIntro:
    .string "My team is ready!\nLet's have a battle!$"

TH_Trainer_DOUG::
    trainerbattle_single TRAINER_TH_DOUG, TH_Text_DOUGIntro, TH_Text_TrainerDefeat
    msgbox TH_Text_TrainerAfter, MSGBOX_AUTOCLOSE
    end

TH_Text_DOUGIntro:
    .string "My team is ready!\nLet's have a battle!$"

TH_Trainer_SAMMY::
    trainerbattle_single TRAINER_TH_SAMMY, TH_Text_SAMMYIntro, TH_Text_TrainerDefeat
    msgbox TH_Text_TrainerAfter, MSGBOX_AUTOCLOSE
    end

TH_Text_SAMMYIntro:
    .string "My team is ready!\nLet's have a battle!$"

TH_Trainer_ANTHONY::
    trainerbattle_single TRAINER_TH_ANTHONY, TH_Text_ANTHONYIntro, TH_Text_TrainerDefeat
    msgbox TH_Text_TrainerAfter, MSGBOX_AUTOCLOSE
    end

TH_Text_ANTHONYIntro:
    .string "My team is ready!\nLet's have a battle!$"

TH_Trainer_CHARLIE::
    trainerbattle_single TRAINER_TH_CHARLIE, TH_Text_CHARLIEIntro, TH_Text_TrainerDefeat
    msgbox TH_Text_TrainerAfter, MSGBOX_AUTOCLOSE
    end

TH_Text_CHARLIEIntro:
    .string "My team is ready!\nLet's have a battle!$"

TH_Trainer_LIAM::
    trainerbattle_single TRAINER_TH_LIAM, TH_Text_LIAMIntro, TH_Text_TrainerDefeat
    msgbox TH_Text_TrainerAfter, MSGBOX_AUTOCLOSE
    end

TH_Text_LIAMIntro:
    .string "My team is ready!\nLet's have a battle!$"

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
    .string "The BOULDERBADGE is yours!\nTake ROCK TOMB as a reminder.\pYou have completed this playtest.\nThank you for exploring THREE HORIZONS!\pYou can keep training, catching POKéMON,\nand exploring the path back to PALLET.$"

TH_Text_BrockBagFull:
    .string "You earned the BOULDERBADGE!\nMake room in your BAG for ROCK TOMB,\lthen speak to me again.$"

TH_Journey_Nurse::
    lock
    faceplayer
    msgbox TH_Text_NurseWelcome
    special HealPlayerParty
    playfanfare MUS_HEAL
    waitfanfare
    msgbox TH_Text_NurseDone
    release
    end
TH_EventScript_CenterRecovery::
    lockall
    special HealPlayerParty
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
    .2byte ITEM_POKE_BALL, ITEM_POTION, ITEM_ANTIDOTE, ITEM_PARALYZE_HEAL, ITEM_ESCAPE_ROPE, ITEM_NONE

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

