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
