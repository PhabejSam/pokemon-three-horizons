TH12_Forest_Treecko::
    lockall
    playmoncry SPECIES_TREECKO, CRY_MODE_NORMAL
    msgbox TH12_Forest_TreeckoText
    waitmoncry
    setflag FLAG_TH12_FOREST_SEEN
    releaseall
    end
TH12_Forest_Shroomish::
    lockall
    playmoncry SPECIES_SHROOMISH, CRY_MODE_NORMAL
    msgbox TH12_Forest_ShroomishText
    waitmoncry
    setflag FLAG_TH12_FOREST_SEEN
    releaseall
    end
TH12_Forest_TreeckoText:
    .string "TREECKO watches from the trees.\nIt seems at home in this forest!\pBIRCH studies TREECKO in HOENN.\nWhat brought this one to KANTO?$"
TH12_Forest_ShroomishText:
    .string "SHROOMISH sniffs the damp leaves.\nA visitor from HOENN!\pIt is busy exploring its new home.\nYou watch without disturbing it.$"
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
