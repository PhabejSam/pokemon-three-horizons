@ Optional ground-floor handoff; no earlier observation or photo is invented.
TH14_Tower_GearContact::
    lock
    faceplayer
    goto_if_set FLAG_TH13_GEAR, TH14_Tower_GearContact_Equipped
    checkitem ITEM_SILPH_SCOPE
    goto_if_eq VAR_RESULT, TRUE, TH14_Tower_GearContact_Scope
    msgbox TH14_Tower_GearContact_Offer
    goto TH14_Tower_GearContact_Grant
TH14_Tower_GearContact_Scope:
    msgbox TH14_Tower_GearContact_ScopeOffer
TH14_Tower_GearContact_Grant:
    call TH13_GiveResearchGear
    msgbox TH14_Tower_GearContact_Received
    release
    end
TH14_Tower_GearContact_Equipped:
    msgbox TH14_Tower_GearContact_Reminder
    release
    end
TH14_Tower_GearContact_Offer:
    .string "PROF. OAK left RESEARCH GEAR for\ntrainers studying unusual sightings.\pTake it with you. The Tower's\nrecords deserve careful attention.$"
TH14_Tower_GearContact_ScopeOffer:
    .string "Your SILPH SCOPE can reveal what\nordinary eyes cannot identify.\pTake this RESEARCH GEAR to keep\na careful record of what you see.$"
TH14_Tower_GearContact_Received:
    .string "You received the RESEARCH GEAR!\pOpen it from the START menu.\nObserve with care and respect.$"
TH14_Tower_GearContact_Reminder:
    .string "Keep a careful record.\nThis is a place of remembrance.$"

@ A direct/older anomalous arrival cannot bypass the mother's resolution.
TH14_Tower7F_Entry::
    setvar VAR_TEMP_2, 1
    goto_if_set FLAG_TH14_MOTHER_RESOLVED, TH14_Tower7F_EntryDone
    lockall
    hidefollower TRUE
    warp MAP_TH13_POKEMON_TOWER_6F, 11, 14
    waitstate
    special TH_RefreshFollower
    releaseall
TH14_Tower7F_EntryDone:
    end

@ This pure predicate is shared by the interaction and compiled-script checks.
TH14_Fuji_CanRescue::
    setvar VAR_RESULT, FALSE
    goto_if_unset FLAG_TH14_MOTHER_RESOLVED, TH14_Fuji_CannotRescue
    goto_if_not_defeated TRAINER_TH14_TOWER7F_GRUNT1, TH14_Fuji_CannotRescue
    goto_if_not_defeated TRAINER_TH14_TOWER7F_GRUNT2, TH14_Fuji_CannotRescue
    goto_if_not_defeated TRAINER_TH14_TOWER7F_GRUNT3, TH14_Fuji_CannotRescue
    setvar VAR_RESULT, TRUE
TH14_Fuji_CannotRescue:
    return

TH14_Tower_Fuji::
    lockall
    faceplayer
    goto_if_set FLAG_TH14_FUJI_RESCUED, TH14_Fuji_Release
    call TH14_Fuji_CanRescue
    goto_if_eq VAR_RESULT, FALSE, TH14_Fuji_NotSafe
    msgbox TH14_Fuji_TowerThanks
    closemessage
    setflag FLAG_TH14_FUJI_RESCUED
    hidefollower TRUE
    warp MAP_TH13_LAVENDER_TOWN_VOLUNTEER_POKEMON_HOUSE, 3, 4
    waitstate
    applymovement LOCALID_PLAYER, TH14_Fuji_FaceUp
    waitmovement 0
    msgbox TH14_Fuji_HomeThanks
    goto TH14_Fuji_DeliverFlute
TH14_Fuji_NotSafe:
    msgbox TH14_Fuji_NotSafeText
    goto TH14_Fuji_Release

TH14_Fuji_Home::
    lockall
    faceplayer
    goto_if_unset FLAG_TH14_FUJI_RESCUED, TH14_Fuji_Release
    goto_if_set FLAG_TH14_POKE_FLUTE, TH14_Fuji_FluteHint
    msgbox TH14_Fuji_HomeThanks
TH14_Fuji_DeliverFlute:
    setvar VAR_0x8004, ITEM_POKE_FLUTE
    setvar VAR_0x8005, FLAG_TH14_POKE_FLUTE
    special TH14_ScriptGiveUniqueItem
    goto_if_eq VAR_RESULT, 0, TH14_Fuji_FullBag
    goto_if_eq VAR_RESULT, 2, TH14_Fuji_FluteHint
    playfanfare MUS_RG_OBTAIN_KEY_ITEM
    msgbox TH14_Fuji_FluteReceived
    waitfanfare
TH14_Fuji_FluteHint:
    msgbox TH14_Fuji_FluteHintText
    goto TH14_Fuji_AftermathRelease
TH14_Fuji_FullBag:
    msgbox TH14_Fuji_FullBagText
TH14_Fuji_AftermathRelease:
    @ Snapshot the final home map, after the warp and reward attempt.
    special TH14_DelayAftermathCalls
TH14_Fuji_Release:
    special TH_RefreshFollower
    releaseall
    end
TH14_Fuji_FaceUp:
    face_up
    step_end
TH14_Fuji_TowerThanks::
    .string "MR. FUJI: The SCOPE helped you\nsee her. You stayed long enough to\lunderstand her.\pSome things are remembered even\nwhen we cannot measure them.\pThank you for your kindness.\nPlease come with me to my home.$"
TH14_Fuji_HomeThanks:
    .string "MR. FUJI: CUBONE will still need\ntime and care. We will be here.\pPlease take this POKé FLUTE\nas my thanks.$"
TH14_Fuji_NotSafeText:
    .string "The Tower is not yet safe.\nPlease help those still in danger.$"
TH14_Fuji_FluteReceived:
    .string "{PLAYER} received the POKé FLUTE!$"
TH14_Fuji_FluteHintText:
    .string "The POKé FLUTE can wake a\ndeeply sleeping POKéMON.\pIf a sleeping POKéMON blocks your\nway, play it gently.$"
TH14_Fuji_FullBagText:
    .string "Your Key Items pocket is full.\nI will keep the POKé FLUTE here.\pMake room, then come and see me.$"

TH14_Tower7F_Grunt1::
    trainerbattle_single TRAINER_TH14_TOWER7F_GRUNT1, TH14_Tower7F_Grunt1Intro, TH14_Tower7F_Grunt1Defeat, TH14_Tower7F_Grunt1Won
    msgbox TH14_Tower7F_Grunt1After, MSGBOX_AUTOCLOSE
    end
TH14_Tower7F_Grunt1Won::
    msgbox TH14_Tower7F_Grunt1After
    closemessage
    removeobject LOCALID_TH14_TOWER7F_2
    releaseall
    end
TH14_Tower7F_Grunt2::
    trainerbattle_single TRAINER_TH14_TOWER7F_GRUNT2, TH14_Tower7F_Grunt2Intro, TH14_Tower7F_Grunt2Defeat, TH14_Tower7F_Grunt2Won
    msgbox TH14_Tower7F_Grunt2After, MSGBOX_AUTOCLOSE
    end
TH14_Tower7F_Grunt2Won::
    msgbox TH14_Tower7F_Grunt2After
    closemessage
    removeobject LOCALID_TH14_TOWER7F_3
    releaseall
    end
TH14_Tower7F_Grunt3::
    trainerbattle_single TRAINER_TH14_TOWER7F_GRUNT3, TH14_Tower7F_Grunt3Intro, TH14_Tower7F_Grunt3Defeat, TH14_Tower7F_Grunt3Won
    msgbox TH14_Tower7F_Grunt3After, MSGBOX_AUTOCLOSE
    end
TH14_Tower7F_Grunt3Won::
    msgbox TH14_Tower7F_Grunt3After
    closemessage
    removeobject LOCALID_TH14_TOWER7F_4
    releaseall
    end
TH14_Tower7F_Grunt1Intro:
    .string "What do you want?\nWhy are you here?$"
TH14_Tower7F_Grunt1Defeat:
    .string "I give up!$"
TH14_Tower7F_Grunt1After:
    .string "I'm not going to forget this!$"
TH14_Tower7F_Grunt2Intro:
    .string "This old man keeps telling us\nto leave the POKéMON in peace.\pWe have work to do.\nStay out of it!$"
TH14_Tower7F_Grunt2Defeat:
    .string "Please!\nNo more!$"
TH14_Tower7F_Grunt2After:
    .string "Fine! We're leaving!$"
TH14_Tower7F_Grunt3Intro:
    .string "You're not saving anyone, kid!$"
TH14_Tower7F_Grunt3Defeat:
    .string "Don't fight us ROCKETS!$"
TH14_Tower7F_Grunt3After:
    .string "You're not getting away with this!$"
