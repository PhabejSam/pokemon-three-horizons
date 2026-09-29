TH13_Route2_Aide::
    lock
    faceplayer
    goto_if_unset FLAG_BADGE03_GET, TH13_Route2_Badge
    setvar VAR_0x8004, 1
    specialvar VAR_RESULT, GetFrlgPokedexCount
    buffernumberstring STR_VAR_1, VAR_0x8006
    goto_if_lt VAR_0x8006, 10, TH13_Route2_Quota
    goto_if_set FLAG_TH13_GEAR, TH13_Route2_CheckFlash
    setflag FLAG_TH13_GEAR
    msgbox TH13_Route2_GearText
TH13_Route2_CheckFlash:
    setvar VAR_0x8004, TH_CALL_ACTIVATION
    special TH_ScriptResearchQueueCall
    goto_if_set FLAG_TH13_FLASH, TH13_Route2_Complete
    checkitem ITEM_HM05
    goto_if_eq VAR_RESULT, TRUE, TH13_Route2_FlashReceipt
    giveitem ITEM_HM05
    goto_if_eq VAR_RESULT, FALSE, TH12_RewardBagFull
TH13_Route2_FlashReceipt:
    setflag FLAG_TH13_FLASH
TH13_Route2_Complete:
    msgbox TH13_Route2_FlashText
    release
    end
TH13_Route2_Badge:
    msgbox TH13_Route2_BadgeText
    release
    end
TH13_Route2_Quota:
    msgbox TH13_Route2_QuotaText
    release
    end
TH13_Route2_Rocker::
    msgbox TH13_Route2_RockerText, MSGBOX_NPC
    end
TH13_Route2_BadgeText:
    .string "OAK sent supplies for your research.\nFirst, earn the THUNDERBADGE.\pThen bring records of ten species\nyou have caught or received.$"
TH13_Route2_QuotaText:
    .string "Your POKéDEX records {STR_VAR_1} species\nyou have caught or received.\pI need records of at least ten.\nTry the nearby routes and forest!\pYou can return through the cave\nor the passage whenever you like.$"
TH13_Route2_GearText:
    .string "Ten species or more! OAK asked me\nto give you this RESEARCH GEAR.\pOpen it from the START menu.\nIt keeps calls, photos, and reports.\pThe professors will contact you\nonce you're ready to continue.$"
TH13_Route2_FlashText:
    .string "HM05 lets a compatible, healthy\nPOKéMON light caves with FLASH.\pIt need not learn FLASH or replace\na move. Use its party menu.\pYour THUNDERBADGE permits field use.\nKeep the HM with you.$"
TH13_Route2_RockerText:
    .string "The passage connects both sides\nof the building. You can go back.\pBeyond CERULEAN, ROCK TUNNEL is\ndark. FLASH makes the trip easier.$"

TH13_Route2_Trader::
    lock
    faceplayer
    setvar VAR_0x8008, INGAME_TRADE_TH13_SKARMORY
    call EventScript_GetInGameTradeSpeciesInfo
    goto_if_set FLAG_TH13_SKARMORY_TRADE, TH13_Route2_TradeDone
    msgbox TH13_Route2_TradeStory
    msgbox TH13_Route2_TradeOfferText, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, TH13_Route2_TradeDecline
    call EventScript_ChooseMonForInGameTrade
    goto_if_ge VAR_0x8004, PARTY_SIZE, TH13_Route2_TradeDecline
    call EventScript_GetInGameTradeSpecies
    goto_if_ne VAR_RESULT, VAR_0x8009, TH13_Route2_TradeWrong
    call EventScript_DoInGameTrade
    setflag FLAG_TH13_SKARMORY_TRADE
    special TH_RefreshFollower
    msgbox TH13_Route2_TradeThanks
    release
    end
TH13_Route2_TradeDone:
    msgbox TH13_Route2_TradeDoneText
    release
    end
TH13_Route2_TradeDecline:
    msgbox TH13_Route2_TradeDeclineText
    release
    end
TH13_Route2_TradeWrong:
    bufferspeciesname STR_VAR_1, VAR_0x8009
    msgbox TH13_Route2_TradeWrongText
    release
    end
TH13_Route2_TradeScientist::
    msgbox TH13_Route2_TradeScientistText, MSGBOX_NPC
    end
TH13_Route2_TradeStory:
    .string "A friend in JOHTO sent me SKARMORY.\nThey've seen strange arrivals, too.\pI'd like to study a local ZUBAT.\nWould you trade one from your party?\pAny held item travels with ZUBAT.\nTake it off first if you want it.$"
TH13_Route2_TradeThanks:
    .string "Thank you! I'll care for ZUBAT.\nPlease look after SKARMORY for me.$"
TH13_Route2_TradeDoneText:
    .string "ZUBAT is settling in well.\nI hope SKARMORY enjoys your travels!\pMy friend is keeping notes in JOHTO.\nThere is still much we don't know.$"
TH13_Route2_TradeScientistText:
    .string "A healthy, compatible POKéMON can\nhelp with CUT or FLASH.\pKeep the HM and earn its badge.\nIt need not learn the battle move.$"
TH13_Route2_TradeOfferText:
    .string "Would you trade your {STR_VAR_1}\nfor my {STR_VAR_2}?$"
TH13_Route2_TradeDeclineText:
    .string "That's all right. Come back\nif you change your mind.$"
TH13_Route2_TradeWrongText:
    .string "I'm looking for a {STR_VAR_1}.\nLet me know if you find one.$"
