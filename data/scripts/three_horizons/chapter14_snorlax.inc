TH14_Gate_Guard1::
    msgbox TH14_Gate_RoadText, MSGBOX_NPC
    end
TH14_Gate_Guard2::
    msgbox TH14_Gate_UpstairsText, MSGBOX_NPC
    end
TH14_Gate_LeftBinoculars::
    lockall
    goto_if_set FLAG_TH14_SNORLAX_RESOLVED, TH14_Gate_ClearView
    msgbox TH14_Gate_ViewAsleep
    releaseall
    end
TH14_Gate_ClearView:
    msgbox TH14_Gate_ViewClear
    releaseall
    end
TH14_Gate_RightBinoculars::
    msgbox TH14_Gate_TunnelText, MSGBOX_SIGN
    end

TH14_Gate_Aide::
    lock
    faceplayer
    goto_if_set FLAG_TH14_ITEMFINDER, TH14_Gate_ItemfinderExplain
    msgbox TH14_Gate_ItemfinderOffer, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, TH14_Gate_Release
    @ Same caught/received count as FLASH; this does not enable the National Dex.
    setvar VAR_0x8004, 1
    specialvar VAR_RESULT, GetFrlgPokedexCount
    goto_if_lt VAR_0x8006, 30, TH14_Gate_ItemfinderQuota
    setvar VAR_0x8004, ITEM_ITEMFINDER
    setvar VAR_0x8005, FLAG_TH14_ITEMFINDER
    special TH14_ScriptGiveUniqueItem
    goto_if_eq VAR_RESULT, 0, TH14_Gate_ItemfinderFull
    goto_if_eq VAR_RESULT, 2, TH14_Gate_ItemfinderExplain
    playfanfare MUS_RG_OBTAIN_KEY_ITEM
    msgbox TH14_Gate_ItemfinderReceived
    waitfanfare
TH14_Gate_ItemfinderExplain:
    msgbox TH14_Gate_ItemfinderHelp
    goto TH14_Gate_Release
TH14_Gate_ItemfinderQuota:
    msgbox TH14_Gate_ItemfinderNeedMore
    goto TH14_Gate_Release
TH14_Gate_ItemfinderFull:
    msgbox TH14_Gate_ItemfinderNoRoom
    goto TH14_Gate_Release

TH14_Gate_Turner::
    lock
    faceplayer
    goto_if_set FLAG_TH14_NINA_TRADE, TH14_Gate_TradeDone
    setvar VAR_0x8008, INGAME_TRADE_NIDORINOA
    call EventScript_GetInGameTradeSpeciesInfo
    msgbox TH14_Gate_TradeOffer, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, TH14_Gate_TradeDeclined
    hidefollower TRUE
    call EventScript_ChooseMonForInGameTrade
    goto_if_ge VAR_0x8004, PARTY_SIZE, TH14_Gate_TradeCancelled
    call EventScript_GetInGameTradeSpecies
    goto_if_ne VAR_RESULT, VAR_0x8009, TH14_Gate_TradeWrong
    call EventScript_DoInGameTrade
    @ Native animation's void return alone is not a delivery receipt.
    special TH14_ConfirmNinaTrade
    goto_if_eq VAR_RESULT, FALSE, TH14_Gate_TradeFailed
    setflag FLAG_TH14_NINA_TRADE
    msgbox TH14_Gate_TradeThanks
    goto TH14_Gate_TradeRestore
TH14_Gate_TradeWrong:
    bufferspeciesname STR_VAR_1, VAR_0x8009
    msgbox TH14_Gate_TradeWrongText
    goto TH14_Gate_TradeRestore
TH14_Gate_TradeCancelled:
    msgbox TH14_Gate_TradeDeclineText
    goto TH14_Gate_TradeRestore
TH14_Gate_TradeFailed:
    msgbox TH14_Gate_TradeRetry
TH14_Gate_TradeRestore:
    closemessage
    special TH_RefreshFollower
    goto TH14_Gate_Release
TH14_Gate_TradeDeclined:
    msgbox TH14_Gate_TradeDeclineText
    goto TH14_Gate_Release
TH14_Gate_TradeDone:
    msgbox TH14_Gate_TradeDoneText
TH14_Gate_Release:
    release
    end

TH14_Snorlax::
    goto_if_set FLAG_TH14_SNORLAX_RESOLVED, TH14_Snorlax_End
    lock
    faceplayer
    checkitem ITEM_POKE_FLUTE
    goto_if_eq VAR_RESULT, FALSE, TH14_Snorlax_Asleep
    msgbox TH14_Snorlax_Offer, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, TH14_Snorlax_Release
    hidefollower TRUE
    call TH14_Snorlax_Awaken
    setwildbattle SPECIES_SNORLAX, 30
    waitse
    playmoncry SPECIES_SNORLAX, CRY_MODE_ENCOUNTER
    delay 40
    waitmoncry
    @ Keep the single persistent object receipt clear throughout battle.
    dowildbattle
    specialvar VAR_RESULT, GetBattleOutcome
    call TH14_Snorlax_RecordOutcome
    goto_if_unset FLAG_TH14_SNORLAX_RESOLVED, TH14_Snorlax_Retry
    fadescreen FADE_TO_BLACK
    removeobject LOCALID_TH14_SNORLAX
    fadescreen FADE_FROM_BLACK
    msgbox TH14_Snorlax_OpenText
    goto TH14_Snorlax_Restore
TH14_Snorlax_RecordOutcome::
    goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, TH14_Snorlax_Resolved
    goto_if_eq VAR_RESULT, B_OUTCOME_WON, TH14_Snorlax_Resolved
    return
TH14_Snorlax_Resolved:
    setflag FLAG_TH14_SNORLAX_RESOLVED
    return
TH14_Snorlax_Retry:
    msgbox TH14_Snorlax_RetryText
TH14_Snorlax_Restore:
    closemessage
    special TH_RefreshFollower
    goto TH14_Snorlax_Release
TH14_Snorlax_Asleep:
    msgbox TH14_Snorlax_AsleepText
TH14_Snorlax_Release:
    release
TH14_Snorlax_End:
    end
TH14_Landing_Sign::
    msgbox TH14_Landing_RoadText, MSGBOX_SIGN
    end
TH14_Landing_Maintenance::
    msgbox TH14_Landing_MaintenanceText, MSGBOX_SIGN
    end

TH14_Gate_RoadText::
    .string "The gate is open, but a SNORLAX\nis sleeping on the road beyond.$"
TH14_Gate_UpstairsText::
    .string "OAK's aide is upstairs.\nThere's a fine view from up there!$"
TH14_Gate_ViewAsleep::
    .string "A big POKéMON is asleep\non the road!$"
TH14_Gate_ViewClear::
    .string "The path is clear now.\nThe water sparkles in the distance.$"
TH14_Gate_TunnelText::
    .string "ROCK TUNNEL links CERULEAN's\nside of KANTO to LAVENDER TOWN.$"
TH14_Gate_ItemfinderOffer::
    .string "OAK left an ITEMFINDER for trainers\nwith records of thirty species\lthey have caught or received.\pMay I check your POKéDEX?$"
TH14_Gate_ItemfinderReceived::
    .string "You received the ITEMFINDER\nfrom OAK's aide!$"
TH14_Gate_ItemfinderHelp::
    .string "Use the ITEMFINDER to detect\nhidden items nearby.\pSometimes a useful item is right\nunder your feet. Keep searching!$"
TH14_Gate_ItemfinderNeedMore::
    .string "Please return with records of\nthirty caught or received species.$"
TH14_Gate_ItemfinderNoRoom::
    .string "Make room in your KEY ITEMS pocket,\nthen come back for the ITEMFINDER.$"
TH14_Gate_TradeRetry::
    .string "The trade hasn't finished.\nWe can try again when you're ready.$"
TH14_Snorlax_AsleepText::
    .string "SNORLAX is sleeping soundly.\nIt won't budge.$"
TH14_Snorlax_Offer::
    .string "Play the POKé FLUTE?$"
TH14_Snorlax_RetryText::
    .string "SNORLAX settles back to sleep.\nIt still blocks the road.$"
TH14_Snorlax_OpenText::
    .string "The footpath is clear now.$"
TH14_Landing_RoadText::
    .string "ROUTE 12\nPlease watch your step on the bridge.$"
TH14_Landing_MaintenanceText::
    .string "Bridge maintenance ahead.\nPlease keep this section clear.$"

@ Same native flute/fanfare/wake sequence, owned here because the FRLG script
@ library is excluded from the TH build.
TH14_Snorlax_Awaken:
    message TH14_Snorlax_Played
    waitmessage
    playfanfare MUS_RG_POKE_FLUTE
    waitfanfare
    msgbox TH14_Snorlax_Woke
    return
TH14_Gate_TradeOffer::
    .string "Would you trade your NIDORINO\nfor my NIDORINA, NINA?$"
TH14_Gate_TradeThanks::
    .string "Hey, thanks!\nI'll take good care of NIDORINO.$"
TH14_Gate_TradeWrongText::
    .string "That's no NIDORINO!\nLet me know if you find one.$"
TH14_Gate_TradeDeclineText::
    .string "Oh, well...\nCome back if you change your mind.$"
TH14_Gate_TradeDoneText::
    .string "Isn't NINA great?\nNIDORINO is settling in well!$"
TH14_Snorlax_Played::
    .string "{PLAYER} played the POKé FLUTE.$"
TH14_Snorlax_Woke::
    .string "SNORLAX woke up!\pIt attacked in a grumpy rage!$"
