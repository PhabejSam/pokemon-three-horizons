TH12_RewardBagFull::
    msgbox TH12_RewardBagFullText
    releaseall
    end
TH12_RewardBagFullText:
    .string "Make room in your BAG, then\ncome back. Your reward will wait!$"

TH12_ClosedFacility::
    msgbox TH12_ClosedFacilityText, MSGBOX_SIGN
    end
TH12_ClosedFacilityText:
    .string "This entrance is closed for now.\nPlease use the main route.$"

TH12_SaffronClosed::
    msgbox TH12_SaffronClosedText, MSGBOX_NPC
    end
TH12_SaffronClosedText:
    .string "SAFFRON is closed to visitors.\nThe UNDERGROUND PATH is open.\pFollow it to travel between\nCERULEAN and VERMILION.$"

@ The inherited door barriers remain in place. Intercept only travel toward
@ SAFFRON, so a player returning from the far half can always leave safely.
TH13_SaffronGuardNorth::
    specialvar VAR_RESULT, GetPlayerFacingDirection
    goto_if_ne VAR_RESULT, DIR_SOUTH, TH13_SaffronGuardEnd
    lockall
    msgbox TH12_SaffronClosedText
    closemessage
    applymovement OBJ_EVENT_ID_PLAYER, TH13_SaffronGuardStepUp
    waitmovement 0
    releaseall
    end

TH13_SaffronGuardSouth::
    specialvar VAR_RESULT, GetPlayerFacingDirection
    goto_if_ne VAR_RESULT, DIR_NORTH, TH13_SaffronGuardEnd
    lockall
    msgbox TH12_SaffronClosedText
    closemessage
    applymovement OBJ_EVENT_ID_PLAYER, TH13_SaffronGuardStepDown
    waitmovement 0
    releaseall
TH13_SaffronGuardEnd:
    end

TH13_SaffronGuardStepUp:
    walk_up
    step_end
TH13_SaffronGuardStepDown:
    walk_down
    step_end

TH12_EastBoundary::
    lockall
    msgbox TH12_EastBoundaryText
    applymovement OBJ_EVENT_ID_PLAYER, TH12_StepLeft
    waitmovement 0
    releaseall
    end
TH12_StepLeft:
    walk_left
    step_end
TH12_EastBoundaryText:
    .string "The road east is closed today.\nExplore VERMILION and the ship first.$"

TH12_Vermilion_OldRod::
    lock
    faceplayer
    goto_if_set FLAG_TH12_OLD_ROD, TH12_OldRod_Already
    checkitem ITEM_OLD_ROD
    goto_if_eq VAR_RESULT, TRUE, TH12_OldRod_Receipt
    msgbox TH12_OldRod_Offer
    giveitem ITEM_OLD_ROD
    goto_if_eq VAR_RESULT, FALSE, TH12_RewardBagFull
TH12_OldRod_Receipt:
    setflag FLAG_TH12_OLD_ROD
TH12_OldRod_Already:
    msgbox TH12_OldRod_Use
    release
    end
TH12_OldRod_Offer:
    .string "A traveler needs a good fishing rod!\nHere, take my spare OLD ROD.$"
TH12_OldRod_Use:
    .string "Face the water and use your OLD ROD.\nPress A when a POKéMON bites!$"

TH12_FanClub_Voucher::
    lock
    faceplayer
    goto_if_set FLAG_TH12_VOUCHER, TH12_Voucher_Already
    goto_if_set FLAG_TH12_BIKE, TH12_Voucher_Already
    checkitem ITEM_BIKE_VOUCHER
    goto_if_eq VAR_RESULT, TRUE, TH12_Voucher_Receipt
    msgbox TH12_Voucher_Story
    giveitem ITEM_BIKE_VOUCHER
    goto_if_eq VAR_RESULT, FALSE, TH12_RewardBagFull
TH12_Voucher_Receipt:
    setflag FLAG_TH12_VOUCHER
TH12_Voucher_Already:
    msgbox TH12_Voucher_Use
    release
    end
TH12_Voucher_Story:
    .string "My RAPIDASH loves the sunrise.\nWe race the first ferry to the pier!\pIt always wins, of course. Then it\nwaits so we can watch the sea.\pSuch speed! Such grace! Yet it\nslows down for its old friend.\pThank you for listening. Take this\nBIKE VOUCHER and find your own pace!$"
TH12_Voucher_Use:
    .string "CERULEAN's bike shop will help you\nfind your pace. Enjoy the journey!$"

TH12_Bike_Redeem::
    lock
    faceplayer
    goto_if_set FLAG_TH12_BIKE, TH13_Bike_Offer
    goto_if_set FLAG_TH13_ACRO, TH13_Bike_Offer
    checkitem ITEM_MACH_BIKE
    goto_if_eq VAR_RESULT, TRUE, TH13_Bike_Offer
    checkitem ITEM_ACRO_BIKE
    goto_if_eq VAR_RESULT, TRUE, TH13_Bike_Offer
    checkitem ITEM_BIKE_VOUCHER
    goto_if_eq VAR_RESULT, FALSE, TH12_Bike_NoVoucher
TH13_Bike_Offer:
    msgbox TH12_Bike_Thanks, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, TH13_Bike_Cancel
    checkitem ITEM_MACH_BIKE
    goto_if_eq VAR_RESULT, TRUE, TH12_Bike_Receipt
    giveitem ITEM_MACH_BIKE
    goto_if_eq VAR_RESULT, FALSE, TH12_RewardBagFull
TH12_Bike_Receipt:
    setflag FLAG_TH12_BIKE
    removeitem ITEM_BIKE_VOUCHER
    checkitem ITEM_ACRO_BIKE
    goto_if_eq VAR_RESULT, TRUE, TH13_Bike_AcroReceipt
    giveitem ITEM_ACRO_BIKE
    goto_if_eq VAR_RESULT, FALSE, TH12_RewardBagFull
TH13_Bike_AcroReceipt:
    setflag FLAG_TH13_ACRO
TH12_Bike_Done:
    msgbox TH12_Bike_Enjoy
    release
    end
TH13_Bike_Cancel:
    msgbox TH13_Bike_CancelText
    release
    end
TH12_Bike_NoVoucher:
    msgbox TH12_Bike_VoucherHint
    release
    end
TH12_Bike_VoucherHint:
    .string "A BIKE VOUCHER gets you both bikes!\nVisit the VERMILION FAN CLUB.$"
TH12_Bike_Thanks:
    .string "MACH for speed, ACRO for tricks!\nOne voucher covers both bikes.\pAlready own one? I'll supply the\nother. Shall I check your bikes?$"
TH12_Bike_Enjoy:
    .string "MACH builds speed on long paths.\nHold B on ACRO to wheelie or hop!\pRegister either in KEY ITEMS.\nDismount before using the other.$"
TH13_Bike_CancelText:
    .string "No rush! Come back whenever\nyou're ready to ride.$"

TH12_Cerulean_CatchUpSupplies::
    lock
    faceplayer
    goto_if_unset FLAG_TH12_START_MONEY, TH13_CatchUpDeliver
    goto_if_set FLAG_TH12_ULTRA_BALLS, TH13_CatchUpAlready
TH13_CatchUpDeliver:
    special TH_TryGiveChapter12Supplies
    goto_if_eq VAR_RESULT, FALSE, TH12_RewardBagFull
    msgbox TH12_CatchUpText
    release
    end
TH13_CatchUpAlready:
    msgbox TH13_CatchUpAlreadyText
    release
    end
TH12_CatchUpText:
    .string "That completes OAK's field supplies:\ntwo ULTRA BALLS and ¥2,000.\pBILL lives beyond NUGGET BRIDGE.\nCompare notes on your sightings!$"
TH13_CatchUpAlreadyText:
    .string "Your ¥2,000 and two ULTRA BALLS\nwere already delivered.\pKeep them handy as you explore.\nBILL lives beyond NUGGET BRIDGE.$"

TH12_Vermilion_Mart::
    lock
    faceplayer
    msgbox TH12_MartWelcome
    pokemart TH12_MartStock
    msgbox TH12_MartGoodbye
    release
    end
    .align 2
TH12_MartStock:
    .2byte ITEM_POKE_BALL, ITEM_GREAT_BALL, ITEM_SUPER_POTION, ITEM_ANTIDOTE
    .2byte ITEM_PARALYZE_HEAL, ITEM_AWAKENING, ITEM_REPEL, ITEM_SUPER_REPEL
    .2byte ITEM_NONE
TH12_MartWelcome:
    .string "Welcome! Stock up before exploring\nthe ship or challenging LT. SURGE.$"
TH12_MartGoodbye:
    .string "Thank you! Have a good journey.$"

TH12_CenterLocal1::
    msgbox TH12_CenterText1, MSGBOX_NPC
    end
TH12_CenterText1:
    .string "The captain teaches CUT. With his\nHM and the CASCADE BADGE, a suitable\lpartner can clear small trees.$"
TH12_CenterLocal2::
    msgbox TH12_CenterText2, MSGBOX_NPC
    end
TH12_CenterText2:
    .string "No need to replace a battle move\nto use CUT outside. Bring a healthy,\lcompatible POKéMON and your HM.$"
TH12_CenterLocal3::
    msgbox TH12_CenterText3, MSGBOX_NPC
    end
TH12_CenterText3:
    .string "Save before sailing! The nurse can\nheal your whole team whenever\lyou return to VERMILION.$"
TH12_CenterLocal4::
    msgbox TH12_CenterText4, MSGBOX_NPC
    end
TH12_CenterText4:
    .string "The harbor is full of stories.\nI wonder which ones BILL can prove!$"

TH13_VsSeekerResearcher::
    lock
    faceplayer
    goto_if_set FLAG_TH13_VS_SEEKER, TH13_VsSeekerAdvice
    checkitem ITEM_VS_SEEKER
    goto_if_eq VAR_RESULT, TRUE, TH13_VsSeekerReceived
    msgbox TH13_VsSeekerGiftText
    giveitem ITEM_VS_SEEKER
    goto_if_eq VAR_RESULT, FALSE, TH12_RewardBagFull
TH13_VsSeekerReceived:
    setflag FLAG_TH13_VS_SEEKER
TH13_VsSeekerAdvice:
    msgbox TH13_VsSeekerAdviceText
    goto_if_unset FLAG_BADGE03_GET, TH13_VsSeekerAdviceEnd
    msgbox TH13_VermilionFlashLeadText
TH13_VsSeekerAdviceEnd:
    release
    end
TH13_VsSeekerGiftText:
    .string "Training together helps everyone!\nTake this VS. SEEKER.\pUse it near Trainers you have beaten\nto invite them to another battle.$"
TH13_VsSeekerAdviceText:
    .string "The VS. SEEKER never needs charging.\nUse it again whenever you like!\pNearby Trainers signal when ready.\nTalk to them for a rematch.\pIt works in caves and buildings too.\nTheir teams grow along with yours.\pGym Leaders and story opponents\nhave their own plans. They will not\lanswer an ordinary rematch call.$"

TH13_VermilionFlashLeadText:
    .string "OAK asked another aide to meet you\non ROUTE 2, beyond DIGLETT'S CAVE.\pHead east to ROUTE 11 for the cave.\nThe aide has supplies for your work.$"
