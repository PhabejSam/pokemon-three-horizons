TH12_Forest_Treecko::
    lockall
    hidefollower TRUE
    applymovement LOCALID_TH12_SIGHT_TREECKO, TH12_Forest_HopRight
    applymovement LOCALID_TH12_SIGHT_WEEDLE, TH12_Forest_HopLeft
    waitmovement 0
    playmoncry SPECIES_TREECKO, CRY_MODE_NORMAL
    waitmoncry
    playmoncry SPECIES_WEEDLE, CRY_MODE_NORMAL
    msgbox TH12_Forest_TreeckoText
    waitmoncry
    setflag FLAG_TH12_FOREST_SEEN
    special TH_RefreshFollower
    releaseall
    end
TH12_Forest_Shroomish::
    lockall
    hidefollower TRUE
    applymovement LOCALID_TH12_SIGHT_SHROOMISH, TH12_Forest_HopRight
    applymovement LOCALID_TH12_SIGHT_CATERPIE, TH12_Forest_HopLeft
    waitmovement 0
    playmoncry SPECIES_SHROOMISH, CRY_MODE_NORMAL
    waitmoncry
    playmoncry SPECIES_CATERPIE, CRY_MODE_NORMAL
    msgbox TH12_Forest_ShroomishText
    waitmoncry
    setflag FLAG_TH12_FOREST_SEEN
    special TH_RefreshFollower
    releaseall
    end
TH12_Forest_HopRight:
    face_right
    jump_in_place_right
    step_end
TH12_Forest_HopLeft:
    face_left
    jump_in_place_left
    step_end
TH12_Forest_TreeckoText:
    .string "TREECKO and WEEDLE greet each other!\nThey seem curious about one another.\pBIRCH studies TREECKO in HOENN.\nWhat brought this one to KANTO?$"
TH12_Forest_ShroomishText:
    .string "SHROOMISH and CATERPIE bounce\nin greeting among the damp leaves.\pA visitor from HOENN, making\na friend in VIRIDIAN FOREST!$"
TH12_Forest_Aide::
    lock
    faceplayer
    goto_if_set FLAG_TH12_FOREST_SEEN, TH12_Forest_Report
    msgbox TH12_Forest_AideText
    release
    end
TH12_Forest_Report:
    msgbox TH12_Forest_ReportText
    release
    end
TH12_Forest_AideText:
    .string "I'm recording unusual sightings\nfor OAK, ELM and BIRCH.\pLook in the forest clearings!\nSome visitors have made new friends.$"
TH12_Forest_ReportText:
    .string "A visitor from HOENN making friends?\nI'll add your sighting to our notes.\pBILL is comparing reports too.\nWe're still investigating the cause.$"

TH12_Moon_Trigger::
    goto_if_set FLAG_TH12_CAVE_SEEN, TH12_SightingEnd
TH12_Moon_Gathering::
    lockall
    goto_if_set FLAG_TH12_CAVE_SEEN, TH12_Moon_Repeat
    hidefollower TRUE
    @ If directly approached inside their circle, avoid walking into the player.
    getplayerxy VAR_0x8004, VAR_0x8005
    goto_if_lt VAR_0x8004, 24, TH12_Moon_Dance
    goto_if_gt VAR_0x8004, 26, TH12_Moon_Dance
    goto_if_lt VAR_0x8005, 29, TH12_Moon_Dance
    goto_if_gt VAR_0x8005, 31, TH12_Moon_Dance
    goto TH12_Moon_Watch
TH12_Moon_Dance:
    applymovement LOCALID_TH12_SIGHT_CLEFAIRY1, TH12_Moon_Circle1
    applymovement LOCALID_TH12_SIGHT_CLEFAIRY2, TH12_Moon_Circle2
    applymovement LOCALID_TH12_SIGHT_CLEFAIRY3, TH12_Moon_Circle3
    waitmovement 0
TH12_Moon_Watch:
    playmoncry SPECIES_CLEFAIRY, CRY_MODE_NORMAL
    waitmoncry
    applymovement LOCALID_TH12_SIGHT_MAKUHITA, TH12_Moon_Clap
    waitmovement 0
    playmoncry SPECIES_MAKUHITA, CRY_MODE_NORMAL
    msgbox TH12_Moon_FirstText
    waitmoncry
    setflag FLAG_TH12_CAVE_SEEN
    special TH_RefreshFollower
    releaseall
    end
TH12_Moon_Repeat:
    playmoncry SPECIES_MAKUHITA, CRY_MODE_NORMAL
    msgbox TH12_Moon_RepeatText
    waitmoncry
    releaseall
TH12_SightingEnd:
    end
TH12_Moon_FirstText:
    .string "Three CLEFAIRY dance around\na cheerful MAKUHITA!\pA visitor from HOENN, welcomed\nby MT. MOON's own POKéMON.$"
TH12_Moon_RepeatText:
    .string "MAKUHITA sways with the CLEFAIRY.\nThey seem comfortable together.$"
TH12_Moon_Clap:
    jump_in_place_down
    step_end
TH12_Moon_Circle1:
    walk_right
    walk_right
    walk_down
    walk_down
    walk_left
    walk_left
    walk_up
    walk_up
    step_end
TH12_Moon_Circle2:
    walk_down
    walk_left
    walk_left
    walk_up
    walk_up
    walk_right
    walk_right
    walk_down
    step_end
TH12_Moon_Circle3:
    walk_up
    walk_up
    walk_right
    walk_right
    walk_down
    walk_down
    walk_left
    walk_left
    step_end
