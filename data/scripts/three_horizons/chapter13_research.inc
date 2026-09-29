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
