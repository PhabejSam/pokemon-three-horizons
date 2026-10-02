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
