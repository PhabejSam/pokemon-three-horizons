TH12_Ship_Board::
    msgbox TH12_Ship_BoardText, MSGBOX_NPC
    end
TH12_Ship_BoardText:
    .string "Welcome to the S.S. ANNE!\nPlease have your S.S. TICKET ready.$"
TH12_Ship_CheckTicket::
    checkitem ITEM_SS_TICKET
    goto_if_eq VAR_RESULT, TRUE, TH12_Ship_End
    lockall
    msgbox TH12_Ship_NoTicket
    applymovement OBJ_EVENT_ID_PLAYER, TH12_Ship_StepUp
    waitmovement 0
    releaseall
TH12_Ship_End:
    end
TH12_Ship_StepUp:
    walk_up
    step_end
TH12_Ship_NoTicket:
    .string "A S.S. TICKET is required to board.\nBILL might be able to help you.$"

TH12_Ship_Heal::
    lock
    faceplayer
    msgbox TH12_Ship_HealOffer, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, TH12_Ship_HealEnd
    closemessage
    hidefollower TRUE
    fadescreen FADE_TO_BLACK
    special HealPlayerParty
    playfanfare MUS_HEAL
    waitfanfare
    fadescreen FADE_FROM_BLACK
    special TH_RefreshFollower
    msgbox TH12_Ship_HealDone
TH12_Ship_HealEnd:
    release
    end
TH12_Ship_HealOffer:
    .string "This cabin is quiet. Would you\nand your POKéMON like to rest?$"
TH12_Ship_HealDone:
    .string "Everyone looks refreshed!\nEnjoy the rest of your visit.$"

TH12_Captain_Talk::
    lock
    faceplayer
    goto_if_set FLAG_TH12_CUT, TH12_Captain_Already
    goto_if_unset FLAG_TH12_SHIP_RIVAL, TH12_Captain_Wait
    checkitem ITEM_HM01
    goto_if_eq VAR_RESULT, TRUE, TH12_Captain_Receipt
    msgbox TH12_Captain_Sick
    closemessage
    playse SE_USE_ITEM
    delay 45
    msgbox TH12_Captain_Thanks
    giveitem ITEM_HM01
    goto_if_eq VAR_RESULT, FALSE, TH12_RewardBagFull
TH12_Captain_Receipt:
    setflag FLAG_TH12_CUT
TH12_Captain_Already:
    msgbox TH12_Captain_Use
    release
    end
TH12_Captain_Wait:
    msgbox TH12_Captain_WaitText
    release
    end
TH12_Captain_WaitText:
    .string "Your friend is waiting outside.\nPlease settle your battle first.$"
TH12_Captain_Sick:
    .string "Urgh… I am terribly seasick.\p{PLAYER} gently rubbed the\nCAPTAIN's back.$"
TH12_Captain_Thanks:
    .string "Thank you! I feel much better!\nLet me share my CUT technique.$"
TH12_Captain_Use:
    .string "Carry HM01 and your CASCADE BADGE.\nA healthy, compatible POKéMON can\lCUT small trees without learning it.\pOur ship is staying in port.\nYou are welcome aboard any time!$"

TH12_Ship_Snorlax::
    lock
    faceplayer
    msgbox TH12_Ship_SnorlaxText
    showmonpic SPECIES_SNORLAX, 10, 3
    waitbuttonpress
    hidemonpic
    release
    end
TH12_Ship_SnorlaxText:
    .string "I saw a POKéMON sleeping by a road.\nIt looked just like this SNORLAX!$"

TH12_Ship_Observation::
    lock
    faceplayer
    goto_if_set FLAG_TH12_SHIP_STORY, TH12_Ship_ObservationAgain
    msgbox TH12_Ship_ObservationText
    setflag FLAG_TH12_SHIP_STORY
    release
    end
TH12_Ship_ObservationAgain:
    msgbox TH12_Ship_ObservationRepeat
    release
    end
TH12_Ship_ObservationText:
    .string "I keep the ship's cargo records.\nJOHTO and HOENN berries arrive here\lalmost every week.\pWe found leaf prints on the crates,\nand tiny POKéMON tracks on deck.\pBILL thinks some travelers followed\nthe shipments into KANTO.\pForests and caves offer familiar\nhomes, even across a different sea.$"
TH12_Ship_ObservationRepeat:
    .string "Tell the professors what you see.\nA single sighting is a clue; many\lreports can reveal a migration.$"

TH12_Ship_RivalTrigger::
    goto_if_set FLAG_TH12_SHIP_RIVAL, TH12_Ship_End
TH12_Ship_Rival::
    lockall
    goto_if_set FLAG_TH12_SHIP_RIVAL, TH12_Ship_RivalDone
    hidefollower TRUE
    setvar VAR_LAST_TALKED, LOCALID_TH12_SSANNE_2F_CORRIDOR_0
    applymovement LOCALID_TH12_SSANNE_2F_CORRIDOR_0, Common_Movement_FacePlayer
    waitmovement 0
    msgbox TH12_Ship_RivalIntro
    closemessage
    goto_if_eq VAR_TH_RIVAL_PARTNER, SPECIES_BULBASAUR, TH12_Ship_Rival_BULBASAUR
    goto_if_eq VAR_TH_RIVAL_PARTNER, SPECIES_CHARMANDER, TH12_Ship_Rival_CHARMANDER
    goto_if_eq VAR_TH_RIVAL_PARTNER, SPECIES_SQUIRTLE, TH12_Ship_Rival_SQUIRTLE
    goto_if_eq VAR_TH_RIVAL_PARTNER, SPECIES_CHIKORITA, TH12_Ship_Rival_CHIKORITA
    goto_if_eq VAR_TH_RIVAL_PARTNER, SPECIES_CYNDAQUIL, TH12_Ship_Rival_CYNDAQUIL
    goto_if_eq VAR_TH_RIVAL_PARTNER, SPECIES_TOTODILE, TH12_Ship_Rival_TOTODILE
    goto_if_eq VAR_TH_RIVAL_PARTNER, SPECIES_TREECKO, TH12_Ship_Rival_TREECKO
    goto_if_eq VAR_TH_RIVAL_PARTNER, SPECIES_TORCHIC, TH12_Ship_Rival_TORCHIC
    goto_if_eq VAR_TH_RIVAL_PARTNER, SPECIES_MUDKIP, TH12_Ship_Rival_MUDKIP
    goto TH12_Ship_RivalDone
TH12_Ship_Rival_BULBASAUR:
    trainerbattle_no_intro TRAINER_TH12_SHIP_BULBASAUR, TH12_Ship_RivalDefeat
    goto TH12_Ship_RivalVictory
TH12_Ship_Rival_CHARMANDER:
    trainerbattle_no_intro TRAINER_TH12_SHIP_CHARMANDER, TH12_Ship_RivalDefeat
    goto TH12_Ship_RivalVictory
TH12_Ship_Rival_SQUIRTLE:
    trainerbattle_no_intro TRAINER_TH12_SHIP_SQUIRTLE, TH12_Ship_RivalDefeat
    goto TH12_Ship_RivalVictory
TH12_Ship_Rival_CHIKORITA:
    trainerbattle_no_intro TRAINER_TH12_SHIP_CHIKORITA, TH12_Ship_RivalDefeat
    goto TH12_Ship_RivalVictory
TH12_Ship_Rival_CYNDAQUIL:
    trainerbattle_no_intro TRAINER_TH12_SHIP_CYNDAQUIL, TH12_Ship_RivalDefeat
    goto TH12_Ship_RivalVictory
TH12_Ship_Rival_TOTODILE:
    trainerbattle_no_intro TRAINER_TH12_SHIP_TOTODILE, TH12_Ship_RivalDefeat
    goto TH12_Ship_RivalVictory
TH12_Ship_Rival_TREECKO:
    trainerbattle_no_intro TRAINER_TH12_SHIP_TREECKO, TH12_Ship_RivalDefeat
    goto TH12_Ship_RivalVictory
TH12_Ship_Rival_TORCHIC:
    trainerbattle_no_intro TRAINER_TH12_SHIP_TORCHIC, TH12_Ship_RivalDefeat
    goto TH12_Ship_RivalVictory
TH12_Ship_Rival_MUDKIP:
    trainerbattle_no_intro TRAINER_TH12_SHIP_MUDKIP, TH12_Ship_RivalDefeat
    goto TH12_Ship_RivalVictory
TH12_Ship_RivalVictory:
    setflag FLAG_TH12_SHIP_RIVAL
    msgbox TH12_Ship_RivalAfter
    closemessage
    removeobject LOCALID_TH12_SSANNE_2F_CORRIDOR_0
TH12_Ship_RivalDone:
    special TH_RefreshFollower
    releaseall
    end
TH12_Ship_RivalIntro:
    .string "{RIVAL}: You made it aboard!\nMy partner and I have been training.\pShow me what your team can do!$"
TH12_Ship_RivalDefeat:
    .string "You have really improved!$"
TH12_Ship_RivalAfter:
    .string "{RIVAL}: I heard the captain knows\nCUT. That should help you reach\lLT. SURGE's GYM.\pI will keep training my partner.\nYou had better keep up!$"
