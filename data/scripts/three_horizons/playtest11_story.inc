TH_FossilResearcherTrigger::
    goto_if_defeated TRAINER_TH9_SUPER_NERD_MIGUEL, TH_Story11End
    lockall
    hidefollower TRUE
    setvar VAR_LAST_TALKED, LOCALID_TH_MTMOONB2F_2
    getplayerxy VAR_0x8004, VAR_0x8005
    goto_if_eq VAR_0x8004, 13, TH13_FossilResearcherFacing
    applymovement LOCALID_TH_MTMOONB2F_2, TH13_FossilResearcherRight
    waitmovement 0
TH13_FossilResearcherFacing:
    turnobject LOCALID_PLAYER, DIR_NORTH
    faceplayer
    trainerbattle_lavaridge LOCALID_TH_MTMOONB2F_2, TRAINER_TH9_SUPER_NERD_MIGUEL, TH_Trainer9_SUPER_NERD_MIGUEL_Intro, TH_Trainer9_SUPER_NERD_MIGUEL_Defeat, TH_FossilResearcherVictory
    releaseall
    end
TH_FossilResearcherVictory:
    msgbox TH_Trainer9_SUPER_NERD_MIGUEL_After
    special TH_RefreshFollower
    releaseall
    end
TH13_FossilResearcherRight:
    walk_right
    step_end
TH_Story11End:
    end

TH_RocketDuoTrigger::
    goto_if_set FLAG_TH_ROCKET_DUO, TH_Story11End
    lockall
    goto_if_defeated TRAINER_TH9_SUPER_NERD_MIGUEL, TH_RocketDuoReady
    msgbox TH_RocketDuoWaiting
    releaseall
    end
TH_RocketDuoReady:
    hidefollower TRUE
    special TH12_BeginRocketPair
    applymovement LOCALID_TH_JESSIE, Common_Movement_FacePlayer
    applymovement LOCALID_TH_JAMES, Common_Movement_FacePlayer
    applymovement LOCALID_TH_ROCKET_MEOWTH, Common_Movement_FacePlayer
    waitmovement 0
TH12_RocketSelectFormat::
    setvar VAR_0x8004, PARTY_SIZE
    specialvar VAR_RESULT, CountPartyAliveNonEggMons_IgnoreVar0x8004Slot
    goto_if_eq VAR_RESULT, 0, TH13_RocketNoUsable
    goto_if_lt VAR_RESULT, 2, TH12_RocketSingles
    msgbox TH_RocketDuoIntro
    setvar VAR_LAST_TALKED, LOCALID_TH_JESSIE
    closemessage
TH_RocketDuoBattle::
    trainerbattle LOCALID_TH_JESSIE, TRAINER_TH11_JESSIE, NULL, TH_JessieDefeat, TH_RocketDuoVictory, LOCALID_TH_JAMES, TRAINER_TH11_JAMES, NULL, TH_JamesDefeat, NULL, NULL, TH_RocketDuoTooFew, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE
    goto TH_RocketDuoVictory
TH12_RocketSingles:
    msgbox TH12_RocketSingleIntro
    closemessage
    trainerbattle_no_intro TRAINER_TH11_JESSIE, TH13_JessieSingleDefeat
    msgbox TH12_RocketSingleSecond
    closemessage
    trainerbattle_no_intro TRAINER_TH11_JAMES, TH_JamesDefeat
    goto TH_RocketDuoVictory
TH_RocketDuoVictory::
    lockall
    special TH12_CompleteRocketPair
    goto_if_eq VAR_RESULT, FALSE, TH12_RocketRelease
    msgbox TH_RocketDuoExit
    closemessage
    playse SE_M_JUMP_KICK
    applymovement LOCALID_TH_JESSIE, TH12_RocketBlastOff
    applymovement LOCALID_TH_JAMES, TH12_RocketBlastOff
    applymovement LOCALID_TH_ROCKET_MEOWTH, TH12_RocketBlastOff
    waitmovement 0
    removeobject LOCALID_TH_JESSIE
    removeobject LOCALID_TH_JAMES
    removeobject LOCALID_TH_ROCKET_MEOWTH
TH12_RocketRelease:
    special TH_RefreshFollower
    releaseall
    end
TH13_RocketNoUsable:
    msgbox TH13_RocketNoUsableText
    goto TH12_RocketRelease
TH13_RocketNoUsableText:
    .string "JAMES: No partner can battle?\nCome back when one is ready!$"
TH12_RocketBlastOff:
    jump_in_place_up
    set_invisible
    delay_4
    set_visible
    delay_4
    set_invisible
    step_end
TH12_RocketSingleIntro::
    .string "JESSIE: Prepare for trouble!\nThose fossils are coming with us!\pJAMES: Make it double! Only one\npartner? We'll take turns, then!\pMEOWTH: No breaks between battles!\nI'll keep an eye on those fossils!$"
TH13_JessieSingleDefeat:
    .string "JAMES! Pick up where I left off!$"
TH12_RocketSingleSecond:
    .string "JAMES: Leave it to me, JESSIE!\nKOFFING, the fossils are at stake!$"
TH_RocketDuoMeowth::
    lock
    faceplayer
    msgbox TH_MeowthTalk
    release
    end
TH_RocketDuoWaiting:
    .string "JESSIE: That researcher is guarding\nsomething valuable.\pJAMES: We are simply waiting for\nan opportunity!$"
TH_RocketDuoIntro::
    .string "JESSIE: Hold it! Those fossils\nwould make quite a prize!\pJAMES: Two of us, two of your\nPOKéMON. A double battle!\pMEOWTH: And I will supervise!\nWhat? Never heard a MEOWTH talk?$"
TH_JessieDefeat:
    .string "Our perfect plan fell apart!$"
TH_JamesDefeat:
    .string "Perhaps we should try a new plan!$"
TH_RocketDuoExit:
    .string "JESSIE: Not again!\nJAMES: Hold on, MEOWTH!\pTEAM ROCKET's blasting off again!$"
TH_RocketDuoTooFew:
    .string "JAMES: Bring two POKéMON that\ncan battle. We fight as a team!\pMEOWTH: Go on, get ready.\nWe will be waiting right here!$"
TH_MeowthTalk:
    .string "MEOWTH: Yep, I can talk!\nTry not to look so surprised.\pJESSIE and JAMES handle the battles.\nI handle the brilliant ideas!$"

TH_MegaPunchTutor::
    lock
    faceplayer
    setvar VAR_0x8005, MOVE_MEGA_PUNCH
    msgbox TH_MegaPunchOffer, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, TH_Tutor11Done
    goto TH_Tutor11Teach
    end
TH_MegaKickTutor::
    lock
    faceplayer
    setvar VAR_0x8005, MOVE_MEGA_KICK
    msgbox TH_MegaKickOffer, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, TH_Tutor11Done
TH_Tutor11Teach:
    msgbox TH_Tutor11Choose
    special ChooseMonForMoveTutor
    lock
    faceplayer
    msgbox TH_Tutor11Return
TH_Tutor11Done:
    release
    end
TH_MegaPunchOffer:
    .string "A focused fist can break through!\nShall I teach MEGA PUNCH?\pMy lessons are free. Bring any\ncompatible partner, any time.$"
TH_MegaKickOffer:
    .string "Put your whole spirit into a kick!\nShall I teach MEGA KICK?\pNo fee, and no limit on lessons.\nEvery partner deserves to learn.$"
TH_Tutor11Choose:
    .string "Choose a POKéMON for the lesson.$"
TH_Tutor11Return:
    .string "Come back whenever another\npartner is ready to train!$"

TH_FossilReviver::
    lock
    faceplayer
    goto_if_unset FLAG_BADGE02_GET, TH_FossilReviveWait
    checkitem ITEM_DOME_FOSSIL, 1
    goto_if_eq VAR_RESULT, FALSE, TH_FossilReviveTryHelix
    msgbox TH_ReviveDomeOffer, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, TH_FossilReviveTryHelix
    setvar VAR_0x8004, ITEM_DOME_FOSSIL
    bufferspeciesname STR_VAR_1, SPECIES_KABUTO
    goto TH_FossilReviveGive
TH_FossilReviveTryHelix:
    checkitem ITEM_HELIX_FOSSIL, 1
    goto_if_eq VAR_RESULT, FALSE, TH_FossilReviveNoFossil
    msgbox TH_ReviveHelixOffer, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, TH_FossilReviveEnd
    setvar VAR_0x8004, ITEM_HELIX_FOSSIL
    bufferspeciesname STR_VAR_1, SPECIES_OMANYTE
TH_FossilReviveGive:
    special TH_ScriptReviveFossil
    goto_if_eq VAR_RESULT, MON_CANT_GIVE, TH_FossilReviveFull
    msgbox TH_FossilReviveSuccess
    special TH_RefreshFollower
    call TH_ReportRewardDestination
    release
    end
TH_FossilReviveFull:
    msgbox TH_FossilReviveFullText
    release
    end
TH_FossilReviveWait:
    msgbox TH_FossilReviveWaitText
    release
    end
TH_FossilReviveNoFossil:
    goto_if_set FLAG_TH12_REVIVED_DOME, TH12_Fossil_DomeRestored
    goto_if_set FLAG_TH12_REVIVED_HELIX, TH12_Fossil_OneRestored
    msgbox TH_FossilReviveNoFossilText
    goto TH_FossilReviveEnd
TH12_Fossil_DomeRestored:
    goto_if_set FLAG_TH12_REVIVED_HELIX, TH12_Fossil_BothRestored
TH12_Fossil_OneRestored:
    msgbox TH12_Fossil_OneText
    goto TH_FossilReviveEnd
TH12_Fossil_BothRestored:
    msgbox TH12_Fossil_BothText
TH_FossilReviveEnd:
    release
    end
TH_ReviveDomeOffer:
    .string "Your DOME FOSSIL contains KABUTO!\nShall I restore it for you?\pRestoration is free. Your revived\npartner will be Lv. 20.$"
TH_ReviveHelixOffer:
    .string "Your HELIX FOSSIL contains OMANYTE!\nShall I restore it for you?\pRestoration is free. Your revived\npartner will be Lv. 20.$"
TH_FossilReviveSuccess:
    .string "Restoration is complete!\n{STR_VAR_1} is alive again!$"
TH_FossilReviveFullText:
    .string "Please make room in your party\nor PC. Your fossil is still safe.$"
TH_FossilReviveWaitText:
    .string "I restore ancient POKéMON\nfrom the fossils of MT. MOON.\pEarn MISTY's CASCADEBADGE, then\nbring me your DOME or HELIX FOSSIL.\lI can restore both, free of charge!$"
TH_FossilReviveNoFossilText:
    .string "Bring a DOME or HELIX FOSSIL\nfrom MT. MOON for restoration.\pMy colleague there can help you\nfind both after you battle him.$"
TH12_Fossil_OneText:
    .string "One ancient partner has a new life!\nBring the other fossil when you find it.$"
TH12_Fossil_BothText:
    .string "Both fossils have been restored!\nKABUTO and OMANYTE live again.\pThank you for giving these ancient\nPOKéMON a place on your journey.$"
