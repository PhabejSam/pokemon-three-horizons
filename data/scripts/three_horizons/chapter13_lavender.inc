@ Lavender: optional observations and one story cameo, no resolution.
TH13_Lavender_Girl::
    msgbox TH13_Lavender_GirlText, MSGBOX_NPC
    end
TH13_Lavender_GirlText:
    .string "Sometimes I hear cries from the tower.\nI hope the POKéMON there find peace.$"
TH13_Lavender_Worker::
    msgbox TH13_Lavender_WorkerText, MSGBOX_NPC
    end
TH13_Lavender_WorkerText:
    .string "The roads west and south are closed\nwhile workers check them.\pThe northern road to ROCK TUNNEL\nis still open.$"
TH13_Lavender_Boy::
    msgbox TH13_Lavender_BoyText, MSGBOX_NPC
    end
TH13_Lavender_BoyText:
    .string "MR. FUJI looks after lonely POKéMON.\nHe went to the tower and has not\lcome home. We are worried.$"
TH13_Lavender_ScopeNotice::
    msgbox TH13_Lavender_ScopeNoticeText, MSGBOX_NPC
    end
TH13_Lavender_ScopeNoticeText:
    .string "A SILPH SCOPE can identify spirits.\nAsk about SILPH equipment in\lCELADON CITY.$"
TH13_Lavender_TownSign::
    msgbox TH13_Lavender_TownSignText, MSGBOX_NPC
    end
TH13_Lavender_TownSignText:
    .string "LAVENDER TOWN\nA resting place for POKéMON.$"
TH13_Lavender_TowerSign::
    msgbox TH13_Lavender_TowerSignText, MSGBOX_NPC
    end
TH13_Lavender_TowerSignText:
    .string "POKéMON TOWER\nPlease respect those at rest.$"
TH13_Lavender_VolunteerSign::
    msgbox TH13_Lavender_VolunteerSignText, MSGBOX_NPC
    end
TH13_Lavender_VolunteerSignText:
    .string "LAVENDER VOLUNTEER POKéMON HOUSE\nA home for POKéMON in need.$"
TH13_Lavender_CenterMan::
    msgbox TH13_Lavender_CenterManText, MSGBOX_NPC
    end
TH13_Lavender_CenterManText:
    .string "The tower is a place of remembrance.\nGo gently. Many people are grieving.$"
TH13_Lavender_CenterLass::
    msgbox TH13_Lavender_CenterLassText, MSGBOX_NPC
    end
TH13_Lavender_CenterLassText:
    .string "CUBONE misses its mother.\nThe people here are caring for it.$"
TH13_Lavender_CenterBoy::
    msgbox TH13_Lavender_CenterBoyText, MSGBOX_NPC
    end
TH13_Lavender_CenterBoyText:
    .string "MR. FUJI says POKéMON often sense\nchanges before people do.\pHe listens before making a guess.$"
TH13_Lavender_HouseWoman::
    msgbox TH13_Lavender_HouseWomanText, MSGBOX_NPC
    end
TH13_Lavender_HouseWomanText:
    .string "TEAM ROCKET took CUBONE's mother.\nIt cries for her every night.\pWe cannot replace her. But we can\nmake sure CUBONE is not alone.$"
TH13_Lavender_VolunteerBoy::
    msgbox TH13_Lavender_VolunteerBoyText, MSGBOX_NPC
    end
TH13_Lavender_VolunteerBoyText:
    .string "MR. FUJI went to calm a troubled\nspirit in the tower.\pWe are keeping his POKéMON company\nuntil he comes home.$"
TH13_Lavender_VolunteerYoungster::
    msgbox TH13_Lavender_VolunteerYoungsterText, MSGBOX_NPC
    end
TH13_Lavender_VolunteerYoungsterText:
    .string "These POKéMON were abandoned.\nMR. FUJI gave them a safe home.$"
TH13_Lavender_VolunteerGirl::
    msgbox TH13_Lavender_VolunteerGirlText, MSGBOX_NPC
    end
TH13_Lavender_VolunteerGirlText:
    .string "I help feed the POKéMON here.\nSmall kindnesses matter, too.$"
TH13_Lavender_Magazine::
    msgbox TH13_Lavender_MagazineText, MSGBOX_NPC
    end
TH13_Lavender_MagazineText:
    .string "A well-read POKéMON magazine.\nSomeone has marked an article\labout caring for lonely POKéMON.$"
TH13_Lavender_Books::
    msgbox TH13_Lavender_BooksText, MSGBOX_NPC
    end
TH13_Lavender_BooksText:
    .string "Books about POKéMON behavior.\nA note reads: Listen carefully\lbefore deciding what they need.$"
TH13_Lavender_MartWelcome::
    msgbox TH13_Lavender_MartWelcomeText, MSGBOX_NPC
    end
TH13_Lavender_MartWelcomeText:
    .string "Welcome! Prepare carefully before\nexploring POKéMON TOWER.$"
TH13_Lavender_MartGoodbye::
    msgbox TH13_Lavender_MartGoodbyeText, MSGBOX_NPC
    end
TH13_Lavender_MartGoodbyeText:
    .string "Thank you. Take care of your team.$"
TH13_Lavender_MartTip::
    msgbox TH13_Lavender_MartTipText, MSGBOX_NPC
    end
TH13_Lavender_MartTipText:
    .string "A healthy team helps on a long climb.\nBring medicine for status problems.$"
TH13_Lavender_CUBONE::
    lock
    faceplayer
    playmoncry SPECIES_CUBONE, CRY_MODE_NORMAL
    msgbox TH13_Lavender_CUBONEText
    waitmoncry
    release
    end
TH13_Lavender_CUBONEText:
    .string "CUBONE: Cuuu...$"
TH13_Lavender_NIDORINO::
    lock
    faceplayer
    playmoncry SPECIES_NIDORINO, CRY_MODE_NORMAL
    msgbox TH13_Lavender_NIDORINOText
    waitmoncry
    release
    end
TH13_Lavender_NIDORINOText:
    .string "NIDORINO: Nido!$"
TH13_Lavender_PSYDUCK::
    lock
    faceplayer
    playmoncry SPECIES_PSYDUCK, CRY_MODE_NORMAL
    msgbox TH13_Lavender_PSYDUCKText
    waitmoncry
    release
    end
TH13_Lavender_PSYDUCKText:
    .string "PSYDUCK: Psy?$"
TH13_LavenderTown_House2_EventScript_NameRater::
	lock
	faceplayer
	msgbox TH13_LavenderTown_House2_Text_WantMeToRateNicknames, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, TH13_LavenderTown_House2_EventScript_ChooseMon
	goto_if_eq VAR_RESULT, NO, TH13_LavenderTown_House2_EventScript_DontRateNickname
	end

TH13_LavenderTown_House2_EventScript_ChooseMon::
	msgbox TH13_LavenderTown_House2_Text_CritiqueWhichMonsNickname
	special ChoosePartyMon
	goto_if_lt VAR_0x8004, PARTY_SIZE, TH13_LavenderTown_House2_EventScript_CheckCanRateMon
	goto_if_ge VAR_0x8004, PARTY_SIZE, TH13_LavenderTown_House2_EventScript_DontRateNickname
	end

TH13_LavenderTown_House2_EventScript_DontRateNickname::
	msgbox TH13_LavenderTown_House2_Text_ISeeComeVisitAgain
	release
	end

TH13_LavenderTown_House2_EventScript_CheckCanRateMon::
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_EGG, TH13_LavenderTown_House2_EventScript_CantNicknameEgg
	special BufferMonNickname
	special IsMonOTIDNotPlayers
	goto_if_eq VAR_RESULT, TRUE, TH13_LavenderTown_House2_EventScript_CantNicknameTradeMon
	specialvar VAR_RESULT, MonOTNameNotPlayer
	special BufferMonNickname
	goto_if_eq VAR_RESULT, TRUE, TH13_LavenderTown_House2_EventScript_CantNicknameTradeMon
	msgbox TH13_LavenderTown_House2_Text_GiveItANicerName, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, TH13_LavenderTown_House2_EventScript_ChooseNewNickname
	goto_if_eq VAR_RESULT, NO, TH13_LavenderTown_House2_EventScript_DontRateNickname
	end

TH13_LavenderTown_House2_EventScript_CantNicknameEgg::
	msgbox TH13_LavenderTown_House2_Text_ThatIsMerelyAnEgg
	release
	end

TH13_LavenderTown_House2_EventScript_CantNicknameTradeMon::
	msgbox TH13_LavenderTown_House2_Text_TrulyImpeccableName
	release
	end

TH13_LavenderTown_House2_EventScript_ChooseNewNickname::
	msgbox TH13_LavenderTown_House2_Text_WhatShallNewNicknameBe
	call Common_EventScript_NameReceivedPartyMon
	specialvar VAR_RESULT, TryPutNameRaterShowOnTheAir
	special BufferMonNickname
	goto_if_eq VAR_RESULT, TRUE, TH13_LavenderTown_House2_EventScript_ChoseNewNickname
	msgbox TH13_LavenderTown_House2_Text_FromNowOnShallBeKnownAsSameName
	release
	end

TH13_LavenderTown_House2_EventScript_ChoseNewNickname::
	msgbox TH13_LavenderTown_House2_Text_FromNowOnShallBeKnownAsName
	release
	end

TH13_LavenderTown_House2_Text_WantMeToRateNicknames::
	.string "Hello, hello!\n"
	.string "I am the official NAME RATER!\p"
	.string "Want me to rate the nicknames of\n"
	.string "your POKéMON?$"

TH13_LavenderTown_House2_Text_CritiqueWhichMonsNickname::
	.string "Which POKéMON's nickname should\n"
	.string "I critique?$"

TH13_LavenderTown_House2_Text_GiveItANicerName::
	.string "{STR_VAR_1}, is it?\n"
	.string "That is a decent nickname!\p"
	.string "But, would you like me to give it\n"
	.string "a nicer name?\p"
	.string "How about it?$"

TH13_LavenderTown_House2_Text_WhatShallNewNicknameBe::
	.string "Ah, good. Then, what shall the new\n"
	.string "nickname be?$"

TH13_LavenderTown_House2_Text_FromNowOnShallBeKnownAsName::
	.string "Done! From now on, this POKéMON\n"
	.string "shall be known as {STR_VAR_1}!\p"
	.string "It is a better name than before!\n"
	.string "How fortunate for you!$"

TH13_LavenderTown_House2_Text_ISeeComeVisitAgain::
	.string "I see.\n"
	.string "Do come visit again.$"

TH13_LavenderTown_House2_Text_FromNowOnShallBeKnownAsSameName::
	.string "Done! From now on, this POKéMON\n"
	.string "shall be known as {STR_VAR_1}!\p"
	.string "It looks no different from before,\n"
	.string "and yet, this is vastly superior!\p"
	.string "How fortunate for you!$"

TH13_LavenderTown_House2_Text_TrulyImpeccableName::
	.string "{STR_VAR_1}, is it?\n"
	.string "That is a truly impeccable name!\p"
	.string "Take good care of {STR_VAR_1}!$"

TH13_LavenderTown_House2_Text_ThatIsMerelyAnEgg::
	.string "Now, now.\n"
	.string "That is merely an EGG!$"


TH13_Lavender_Mart::
    lock
    faceplayer
    msgbox TH13_Lavender_MartWelcomeText
    pokemart TH13_Lavender_Stock
    msgbox TH13_Lavender_MartGoodbyeText
    release
    end
    .align 2
TH13_Lavender_Stock:
    .2byte ITEM_POKE_BALL, ITEM_GREAT_BALL, ITEM_SUPER_POTION, ITEM_REVIVE
    .2byte ITEM_ANTIDOTE, ITEM_PARALYZE_HEAL, ITEM_AWAKENING
    .2byte ITEM_BURN_HEAL, ITEM_ICE_HEAL, ITEM_ESCAPE_ROPE
    .2byte ITEM_REPEL, ITEM_SUPER_REPEL, ITEM_NONE

TH13_Lavender_Misdreavus::
    lockall
    hidefollower
    playmoncry SPECIES_MISDREAVUS, CRY_MODE_NORMAL
    waitmoncry
    goto_if_set FLAG_TH13_SCENE_LAVENDER, TH13_Lavender_GhostRepeat
    msgbox TH13_Lavender_GhostFirstText
    setflag FLAG_TH13_SCENE_LAVENDER
    goto TH13_Lavender_GhostRecord
TH13_Lavender_GhostRepeat:
    msgbox TH13_Lavender_GhostRepeatText
TH13_Lavender_GhostRecord:
    setvar VAR_0x8004, TH_RESEARCH_LAVENDER
    special TH_ScriptResearchObserve
    setvar VAR_0x8004, TH_PHOTO_LAVENDER
    call TH13_ResearchPhoto
    closemessage
    applymovement LOCALID_TH13_LAVENDERTOWN_4, TH13_Lavender_GhostVanish
    waitmovement 0
    goto_if_set FLAG_TH13_PHOTO_LAVENDER, TH13_Lavender_GhostPhotographed
    @ Native removeobject sets its map flag. Undo only the unearned photo bit.
    removeobject LOCALID_TH13_LAVENDERTOWN_4
    clearflag FLAG_TH13_PHOTO_LAVENDER
    goto TH13_Lavender_GhostGone
TH13_Lavender_GhostPhotographed:
    removeobject LOCALID_TH13_LAVENDERTOWN_4
TH13_Lavender_GhostGone:
    msgbox TH13_Lavender_GhostGoneText
    setvar VAR_0x8004, TH_CALL_LAVENDER
    special TH_ScriptResearchQueueCall
    special TH_RefreshFollower
    releaseall
    end
TH13_Lavender_GhostVanish:
    walk_in_place_slow_up
    delay_16
    set_invisible
    step_end
TH13_Lavender_GhostFirstText:
    .string "MISDREAVUS watches the tower.\nThere is no TRAINER nearby.\pIt turns quietly toward you.\nFor a moment, it holds your gaze.$"
TH13_Lavender_GhostRepeatText:
    .string "MISDREAVUS is watching the tower\nagain. It seems to recognize you.$"
TH13_Lavender_GhostGoneText:
    .string "It fades from sight.\nThe town is quiet again.\pThis sighting does not fit neatly\nwith BILL's shipping-route idea.$"

TH13_Lavender_Rival::
    lockall
    faceplayer
    hidefollower
    goto_if_set FLAG_TH13_LAVENDER_RIVAL, TH13_Lavender_RivalRepeat
    msgbox TH13_Lavender_RivalFirstText
    setflag FLAG_TH13_LAVENDER_RIVAL
    goto TH13_Lavender_RivalEnd
TH13_Lavender_RivalRepeat:
    msgbox TH13_Lavender_RivalRepeatText
TH13_Lavender_RivalEnd:
    special TH_RefreshFollower
    releaseall
    end
TH13_Lavender_RivalFirstText:
    .string "{RIVAL}: Not here. People are\ngrieving.\pOAK asked us to pay attention\nto what POKéMON are experiencing, too.\pI will keep training. But next time\nwe meet, we are battling!$"
TH13_Lavender_RivalRepeatText:
    .string "{RIVAL}: There will be time\nfor another battle.\pFor now, let us show some respect.$"

TH13_Lavender_Rockets::
    lockall
    goto_if_set FLAG_TH13_ROCKET_CAMEO, TH13_Lavender_RocketsEnd
    hidefollower
    msgbox TH13_Lavender_RocketsText
    closemessage
    fadescreen FADE_TO_BLACK
    setflag FLAG_TH13_ROCKET_CAMEO
    removeobject LOCALID_TH13_LAVENDERTOWN_6
    removeobject LOCALID_TH13_LAVENDERTOWN_7
    removeobject LOCALID_TH13_LAVENDERTOWN_8
    fadescreen FADE_FROM_BLACK
    special TH_RefreshFollower
TH13_Lavender_RocketsEnd:
    releaseall
    end
TH13_Lavender_RocketsText:
    .string "JESSIE: Orders say to record unusual\nPOKéMON. Ghosts don't frighten me!\pJAMES: Excellent. You can hold the\nnotebook. My hands are shaking.\pMEOWTH: My report says we should\nleave before something reports US!\pJESSIE: A strategic withdrawal.\nWe have business in CELADON anyway!$"
