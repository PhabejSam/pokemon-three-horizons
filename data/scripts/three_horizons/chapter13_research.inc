@ Called by an authored, already locked scene; VAR_0x8004 is its photo ID.
@ Declining never calls the capture special and never changes progress.
TH13_ResearchPhoto::
    special TH_ScriptResearchPhotoStatus
    goto_if_eq VAR_RESULT, 0, TH13_ResearchPhoto_End
    goto_if_eq VAR_RESULT, 2, TH13_ResearchPhoto_Recorded
    msgbox TH13_ResearchPhoto_OfferText, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, TH13_ResearchPhoto_End
    closemessage
    special TH_ScriptTakeResearchPhoto
    goto_if_eq VAR_RESULT, FALSE, TH13_ResearchPhoto_End
    playse SE_CLICK
    fadescreen FADE_TO_WHITE
    delay 4
    fadescreen FADE_FROM_WHITE
    msgbox TH13_ResearchPhoto_SavedText
TH13_ResearchPhoto_End:
    return
TH13_ResearchPhoto_Recorded:
    msgbox TH13_ResearchPhoto_RecordedText
    return
TH13_ResearchPhoto_OfferText:
    .string "A rare interaction is unfolding.\nPhotograph it?$"
TH13_ResearchPhoto_SavedText:
    .string "The photo was added to your\nRESEARCH GEAR.$"
TH13_ResearchPhoto_RecordedText:
    .string "You recorded this interaction.\nView it in RESEARCH PHOTOS.$"

@ The field dispatcher chooses one named script. No receipt is written until
@ every message has finished; resetting before that leaves the call pending.
TH13_ResearchCall_Activation::
    lockall
    playse SE_POKENAV_CALL
    waitse
    msgbox TH13_ResearchCall_ActivationOak
    msgbox TH13_ResearchCall_ActivationElm
    msgbox TH13_ResearchCall_ActivationBirch
    setvar VAR_0x8004, TH_CALL_ACTIVATION
    goto TH13_ResearchCall_Finish
TH13_ResearchCall_Route10::
    lockall
    playse SE_POKENAV_CALL
    waitse
    msgbox TH13_ResearchCall_Route10Oak
    msgbox TH13_ResearchCall_Route10Elm
    msgbox TH13_ResearchCall_Route10Birch
    setvar VAR_0x8004, TH_CALL_ROUTE10
    goto TH13_ResearchCall_Finish
TH13_ResearchCall_Lavender::
    lockall
    playse SE_POKENAV_CALL
    waitse
    msgbox TH13_ResearchCall_LavenderOak
    msgbox TH13_ResearchCall_LavenderElm
    msgbox TH13_ResearchCall_LavenderBirch
    setvar VAR_0x8004, TH_CALL_LAVENDER
TH13_ResearchCall_Finish:
    closemessage
    special TH_ScriptResearchCompleteCall
    playse SE_POKENAV_HANG_UP
    releaseall
    end
TH13_ResearchCall_ActivationOak:
    .string "OAK: Your reports have reached us,\n{PLAYER}. Thank you!\pThere is more to compare now.\nYour RESEARCH GEAR will help.\pELM and BIRCH can contact you, too.\nYou're a field researcher for us all!$"
TH13_ResearchCall_ActivationElm:
    .string "ELM: Hello! KANTO POKéMON are\nappearing in unusual JOHTO habitats.\pPlease watch how visitors interact\nwith the POKéMON already there.$"
TH13_ResearchCall_ActivationBirch:
    .string "BIRCH: HOENN's reports are changing,\ntoo. This crosses several regions.\pWe don't know why yet. Record your\nobservations and keep exploring!$"
TH13_ResearchCall_Route10Oak:
    .string "OAK: ROUTE 10 is a good place\nto compare our latest reports.\pThe movement isn't one-way. Prepare\nfor ROCK TUNNEL before continuing.$"
TH13_ResearchCall_Route10Elm:
    .string "ELM: Unusual KANTO sightings\ncontinue here in JOHTO.\pSeasonal migration alone doesn't\nexplain their pace. Keep observing.$"
TH13_ResearchCall_Route10Birch:
    .string "BIRCH: HOENN's pattern is changing.\nBILL's shipping idea is a useful lead.\pShips may explain some visitors,\nbut we must compare every report.$"
TH13_ResearchCall_LavenderOak:
    .string "OAK: MISDREAVUS near the TOWER...\nThat is difficult to explain.\pShipping doesn't account for this\nreport. We need more evidence.$"
TH13_ResearchCall_LavenderElm:
    .string "ELM: MISDREAVUS is known in JOHTO.\nBut that doesn't tell us why one\pis watching POKéMON TOWER.\nPlease be careful, {PLAYER}.$"
TH13_ResearchCall_LavenderBirch:
    .string "BIRCH: Keep your earlier notes.\nThose observations still matter.\pWe don't have enough evidence\nto explain this. Stay careful.$"
