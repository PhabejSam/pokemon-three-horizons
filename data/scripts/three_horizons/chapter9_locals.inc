TH_Sign_Route22_0::
    msgbox TH_Sign_Route22_0_Text, MSGBOX_NPC
    end

TH_Sign_Route22_0_Text:
    .string "POKéMON LEAGUE - ROUTE 22$"

TH_Local_LeagueGate_0::
    msgbox TH_Local_LeagueGate_0_Text, MSGBOX_NPC
    end

TH_Local_LeagueGate_0_Text:
    .string "The POKéMON LEAGUE requires all\neight KANTO badges. Keep training!$"

TH_Local_Route3_0::
    msgbox TH_Local_Route3_0_Text, MSGBOX_NPC
    end

TH_Local_Route3_0_Text:
    .string "A tiny CHARMANDER warmed itself\non these rocks this morning.$"

TH_Sign_Route3_0::
    msgbox TH_Sign_Route3_0_Text, MSGBOX_NPC
    end

TH_Sign_Route3_0_Text:
    .string "ROUTE 3 - MT. MOON AHEAD$"

TH_Pickup_0::
    lock
    faceplayer
    goto_if_set FLAG_TH_PICKUP_0, TH_PickupDone
    giveitem ITEM_POTION
    goto_if_eq VAR_RESULT, FALSE, TH_PickupFull
    setflag FLAG_TH_PICKUP_0
    removeobject VAR_LAST_TALKED
    release
    end

TH_Local_Route4_0::
    msgbox TH_Local_Route4_0_Text, MSGBOX_NPC
    end

TH_Local_Route4_0_Text:
    .string "That CENTER is the last rest stop\nbefore MT. MOON. Stock up!$"

TH_Local_Route4_3::
    msgbox TH_Local_Route4_3_Text, MSGBOX_NPC
    end

TH_Local_Route4_3_Text:
    .string "Listen for wings in the cave.\nZUBAT dislike the daylight.$"

TH_Local_Route4_4::
    msgbox TH_Local_Route4_4_Text, MSGBOX_NPC
    end

TH_Local_Route4_4_Text:
    .string "My feet need a break after\nall those rocky paths.$"

TH_Local_Route4_5::
    msgbox TH_Local_Route4_5_Text, MSGBOX_NPC
    end

TH_Local_Route4_5_Text:
    .string "I teach powerful punches. My\nlessons open in a later chapter.$"

TH_Sign_Route4_0::
    msgbox TH_Sign_Route4_0_Text, MSGBOX_NPC
    end

TH_Sign_Route4_0_Text:
    .string "ROUTE 4 - MT. MOON$"

TH_Sign_Route4_1::
    msgbox TH_Sign_Route4_1_Text, MSGBOX_NPC
    end

TH_Sign_Route4_1_Text:
    .string "ROUTE 4 - MT. MOON$"

TH_Pickup_1::
    lock
    faceplayer
    goto_if_set FLAG_TH_PICKUP_1, TH_PickupDone
    giveitem ITEM_TM05
    goto_if_eq VAR_RESULT, FALSE, TH_PickupFull
    setflag FLAG_TH_PICKUP_1
    removeobject VAR_LAST_TALKED
    release
    end

TH_Pickup_2::
    lock
    faceplayer
    goto_if_set FLAG_TH_PICKUP_2, TH_PickupDone
    giveitem ITEM_GREAT_BALL
    goto_if_eq VAR_RESULT, FALSE, TH_PickupFull
    setflag FLAG_TH_PICKUP_2
    removeobject VAR_LAST_TALKED
    release
    end

TH_Pickup_3::
    lock
    faceplayer
    goto_if_set FLAG_TH_PICKUP_3, TH_PickupDone
    giveitem ITEM_SUPER_POTION
    goto_if_eq VAR_RESULT, FALSE, TH_PickupFull
    setflag FLAG_TH_PICKUP_3
    removeobject VAR_LAST_TALKED
    release
    end

TH_Pickup_4::
    lock
    faceplayer
    goto_if_set FLAG_TH_PICKUP_4, TH_PickupDone
    giveitem ITEM_RAZZ_BERRY
    goto_if_eq VAR_RESULT, FALSE, TH_PickupFull
    setflag FLAG_TH_PICKUP_4
    removeobject VAR_LAST_TALKED
    release
    end

TH_Local_Route4Center_2::
    msgbox TH_Local_Route4Center_2_Text, MSGBOX_NPC
    end

TH_Local_Route4Center_2_Text:
    .string "Take a moment to rest.\nThe next route can wait.$"

TH_Local_Route4Center_3::
    msgbox TH_Local_Route4Center_3_Text, MSGBOX_NPC
    end

TH_Local_Route4Center_3_Text:
    .string "Take a moment to rest.\nThe next route can wait.$"

TH_Local_Route4Center_4::
    msgbox TH_Local_Route4Center_4_Text, MSGBOX_NPC
    end

TH_Local_Route4Center_4_Text:
    .string "The cave has several ladders.\nSome lead to useful supplies.$"

TH_Local_Route4Center_5::
    msgbox TH_Local_Route4Center_5_Text, MSGBOX_NPC
    end

TH_Local_Route4Center_5_Text:
    .string "ROCKET uniforms in a cave?\nThat cannot be a good sign.$"

TH_Local_MtMoon1F_13::
    msgbox TH_Local_MtMoon1F_13_Text, MSGBOX_NPC
    end

TH_Local_MtMoon1F_13_Text:
    .string "Watch your step. The ladders\nconnect separate underground paths.$"

TH_Sign_MtMoon1F_0::
    msgbox TH_Sign_MtMoon1F_0_Text, MSGBOX_NPC
    end

TH_Sign_MtMoon1F_0_Text:
    .string "MT. MOON - Watch for ZUBAT!$"

TH_Pickup_5::
    lock
    faceplayer
    goto_if_set FLAG_TH_PICKUP_5, TH_PickupDone
    giveitem ITEM_PARALYZE_HEAL
    goto_if_eq VAR_RESULT, FALSE, TH_PickupFull
    setflag FLAG_TH_PICKUP_5
    removeobject VAR_LAST_TALKED
    release
    end

TH_Pickup_6::
    lock
    faceplayer
    goto_if_set FLAG_TH_PICKUP_6, TH_PickupDone
    giveitem ITEM_TM09
    goto_if_eq VAR_RESULT, FALSE, TH_PickupFull
    setflag FLAG_TH_PICKUP_6
    removeobject VAR_LAST_TALKED
    release
    end

TH_Pickup_7::
    lock
    faceplayer
    goto_if_set FLAG_TH_PICKUP_7, TH_PickupDone
    giveitem ITEM_POTION
    goto_if_eq VAR_RESULT, FALSE, TH_PickupFull
    setflag FLAG_TH_PICKUP_7
    removeobject VAR_LAST_TALKED
    release
    end

TH_Pickup_8::
    lock
    faceplayer
    goto_if_set FLAG_TH_PICKUP_8, TH_PickupDone
    giveitem ITEM_RARE_CANDY
    goto_if_eq VAR_RESULT, FALSE, TH_PickupFull
    setflag FLAG_TH_PICKUP_8
    removeobject VAR_LAST_TALKED
    release
    end

TH_Pickup_9::
    lock
    faceplayer
    goto_if_set FLAG_TH_PICKUP_9, TH_PickupDone
    giveitem ITEM_SUPER_REPEL
    goto_if_eq VAR_RESULT, FALSE, TH_PickupFull
    setflag FLAG_TH_PICKUP_9
    removeobject VAR_LAST_TALKED
    release
    end

TH_Pickup_10::
    lock
    faceplayer
    goto_if_set FLAG_TH_PICKUP_10, TH_PickupDone
    giveitem ITEM_MOON_STONE
    goto_if_eq VAR_RESULT, FALSE, TH_PickupFull
    setflag FLAG_TH_PICKUP_10
    removeobject VAR_LAST_TALKED
    release
    end

TH_Pickup_11::
    lock
    faceplayer
    goto_if_set FLAG_TH_PICKUP_11, TH_PickupDone
    giveitem ITEM_TINY_MUSHROOM
    goto_if_eq VAR_RESULT, FALSE, TH_PickupFull
    setflag FLAG_TH_PICKUP_11
    removeobject VAR_LAST_TALKED
    release
    end

TH_Pickup_12::
    lock
    faceplayer
    goto_if_set FLAG_TH_PICKUP_12, TH_PickupDone
    giveitem ITEM_TINY_MUSHROOM
    goto_if_eq VAR_RESULT, FALSE, TH_PickupFull
    setflag FLAG_TH_PICKUP_12
    removeobject VAR_LAST_TALKED
    release
    end

TH_Pickup_13::
    lock
    faceplayer
    goto_if_set FLAG_TH_PICKUP_13, TH_PickupDone
    giveitem ITEM_TINY_MUSHROOM
    goto_if_eq VAR_RESULT, FALSE, TH_PickupFull
    setflag FLAG_TH_PICKUP_13
    removeobject VAR_LAST_TALKED
    release
    end

TH_Pickup_14::
    lock
    faceplayer
    goto_if_set FLAG_TH_PICKUP_14, TH_PickupDone
    giveitem ITEM_BIG_MUSHROOM
    goto_if_eq VAR_RESULT, FALSE, TH_PickupFull
    setflag FLAG_TH_PICKUP_14
    removeobject VAR_LAST_TALKED
    release
    end

TH_Pickup_15::
    lock
    faceplayer
    goto_if_set FLAG_TH_PICKUP_15, TH_PickupDone
    giveitem ITEM_BIG_MUSHROOM
    goto_if_eq VAR_RESULT, FALSE, TH_PickupFull
    setflag FLAG_TH_PICKUP_15
    removeobject VAR_LAST_TALKED
    release
    end

TH_Pickup_16::
    lock
    faceplayer
    goto_if_set FLAG_TH_PICKUP_16, TH_PickupDone
    giveitem ITEM_BIG_MUSHROOM
    goto_if_eq VAR_RESULT, FALSE, TH_PickupFull
    setflag FLAG_TH_PICKUP_16
    removeobject VAR_LAST_TALKED
    release
    end

TH_Pickup_17::
    lock
    faceplayer
    goto_if_set FLAG_TH_PICKUP_17, TH_PickupDone
    giveitem ITEM_STAR_PIECE
    goto_if_eq VAR_RESULT, FALSE, TH_PickupFull
    setflag FLAG_TH_PICKUP_17
    removeobject VAR_LAST_TALKED
    release
    end

TH_Pickup_18::
    lock
    faceplayer
    goto_if_set FLAG_TH_PICKUP_18, TH_PickupDone
    giveitem ITEM_TM46
    goto_if_eq VAR_RESULT, FALSE, TH_PickupFull
    setflag FLAG_TH_PICKUP_18
    removeobject VAR_LAST_TALKED
    release
    end

TH_Pickup_19::
    lock
    faceplayer
    goto_if_set FLAG_TH_PICKUP_19, TH_PickupDone
    giveitem ITEM_REVIVE
    goto_if_eq VAR_RESULT, FALSE, TH_PickupFull
    setflag FLAG_TH_PICKUP_19
    removeobject VAR_LAST_TALKED
    release
    end

TH_Pickup_20::
    lock
    faceplayer
    goto_if_set FLAG_TH_PICKUP_20, TH_PickupDone
    giveitem ITEM_ANTIDOTE
    goto_if_eq VAR_RESULT, FALSE, TH_PickupFull
    setflag FLAG_TH_PICKUP_20
    removeobject VAR_LAST_TALKED
    release
    end

TH_Pickup_21::
    lock
    faceplayer
    goto_if_set FLAG_TH_PICKUP_21, TH_PickupDone
    giveitem ITEM_MOON_STONE
    goto_if_eq VAR_RESULT, FALSE, TH_PickupFull
    setflag FLAG_TH_PICKUP_21
    removeobject VAR_LAST_TALKED
    release
    end

TH_Pickup_22::
    lock
    faceplayer
    goto_if_set FLAG_TH_PICKUP_22, TH_PickupDone
    giveitem ITEM_ETHER
    goto_if_eq VAR_RESULT, FALSE, TH_PickupFull
    setflag FLAG_TH_PICKUP_22
    removeobject VAR_LAST_TALKED
    release
    end

TH_Local_Cerulean_0::
    msgbox TH_Local_Cerulean_0_Text, MSGBOX_NPC
    end

TH_Local_Cerulean_0_Text:
    .string "The house was robbed. Please keep\nclear while we investigate.$"

TH_Local_Cerulean_2::
    msgbox TH_Local_Cerulean_2_Text, MSGBOX_NPC
    end

TH_Local_Cerulean_2_Text:
    .string "I want to cross NUGGET BRIDGE!\nFirst, I need to train my team.$"

TH_Local_Cerulean_3::
    msgbox TH_Local_Cerulean_3_Text, MSGBOX_NPC
    end

TH_Local_Cerulean_3_Text:
    .string "MISTY trains in that big pool.\nHer battles make quite a splash!$"

TH_Local_Cerulean_4::
    playmoncry SPECIES_SLOWBRO, CRY_MODE_NORMAL
    msgbox TH_Local_Cerulean_4_Text, MSGBOX_NPC
    end

TH_Local_Cerulean_4_Text:
    .string "SLOWBRO: Brooo!$"

TH_Local_Cerulean_5::
    msgbox TH_Local_Cerulean_5_Text, MSGBOX_NPC
    end

TH_Local_Cerulean_5_Text:
    .string "SLOWBRO and I like this quiet spot.\nWe could watch the water all day.$"

TH_Local_Cerulean_6::
    msgbox TH_Local_Cerulean_6_Text, MSGBOX_NPC
    end

TH_Local_Cerulean_6_Text:
    .string "A good team needs more than power.\nI am trying different Abilities.$"

TH_Local_Cerulean_10::
    msgbox TH_Local_Cerulean_10_Text, MSGBOX_NPC
    end

TH_Local_Cerulean_10_Text:
    .string "The bridge is north of town.\nYour rival is waiting nearby.$"

TH_Local_Cerulean_11::
    msgbox TH_Local_Cerulean_11_Text, MSGBOX_NPC
    end

TH_Local_Cerulean_11_Text:
    .string "Take a moment to rest.\nThe next route can wait.$"

TH_Sign_Cerulean_0::
    msgbox TH_Sign_Cerulean_0_Text, MSGBOX_NPC
    end

TH_Sign_Cerulean_0_Text:
    .string "CERULEAN CITY - Flowing with life$"

TH_Sign_Cerulean_1::
    msgbox TH_Sign_Cerulean_1_Text, MSGBOX_NPC
    end

TH_Sign_Cerulean_1_Text:
    .string "CERULEAN CITY - Flowing with life$"

TH_Sign_Cerulean_2::
    msgbox TH_Sign_Cerulean_2_Text, MSGBOX_NPC
    end

TH_Sign_Cerulean_2_Text:
    .string "CERULEAN CITY - Flowing with life$"

TH_Sign_Cerulean_3::
    msgbox TH_Sign_Cerulean_3_Text, MSGBOX_NPC
    end

TH_Sign_Cerulean_3_Text:
    .string "CERULEAN CITY - Flowing with life$"

TH_Sign_Cerulean_5::
    msgbox TH_Sign_Cerulean_5_Text, MSGBOX_NPC
    end

TH_Sign_Cerulean_5_Text:
    .string "CERULEAN CITY - Flowing with life$"

TH_Sign_Cerulean_6::
    msgbox TH_Sign_Cerulean_6_Text, MSGBOX_NPC
    end

TH_Sign_Cerulean_6_Text:
    .string "CERULEAN CITY - Flowing with life$"

TH_Sign_Cerulean_7::
    msgbox TH_Sign_Cerulean_7_Text, MSGBOX_NPC
    end

TH_Sign_Cerulean_7_Text:
    .string "CERULEAN CITY - Flowing with life$"

TH_Pickup_23::
    lock
    faceplayer
    goto_if_set FLAG_TH_PICKUP_23, TH_PickupDone
    giveitem ITEM_RARE_CANDY
    goto_if_eq VAR_RESULT, FALSE, TH_PickupFull
    setflag FLAG_TH_PICKUP_23
    removeobject VAR_LAST_TALKED
    release
    end

TH_Local_CeruleanGym_3::
    msgbox TH_Local_CeruleanGym_3_Text, MSGBOX_NPC
    end

TH_Local_CeruleanGym_3_Text:
    .string "Water moves can strike hard.\nTry Grass or Electric attacks.$"

TH_Sign_CeruleanGym_0::
    msgbox TH_Sign_CeruleanGym_0_Text, MSGBOX_NPC
    end

TH_Sign_CeruleanGym_0_Text:
    .string "CERULEAN GYM - LEADER: MISTY$"

TH_Sign_CeruleanGym_1::
    msgbox TH_Sign_CeruleanGym_1_Text, MSGBOX_NPC
    end

TH_Sign_CeruleanGym_1_Text:
    .string "CERULEAN GYM - LEADER: MISTY$"

TH_Local_CeruleanMart_1::
    msgbox TH_Local_CeruleanMart_1_Text, MSGBOX_NPC
    end

TH_Local_CeruleanMart_1_Text:
    .string "I stock up on REPELS before a\nlong trip through a cave.$"

TH_Local_CeruleanMart_2::
    msgbox TH_Local_CeruleanMart_2_Text, MSGBOX_NPC
    end

TH_Local_CeruleanMart_2_Text:
    .string "ANTIDOTES helped me cross\nVIRIDIAN FOREST safely.$"

TH_Local_CeruleanCenter_1::
    msgbox TH_Local_CeruleanCenter_1_Text, MSGBOX_NPC
    end

TH_Local_CeruleanCenter_1_Text:
    .string "Even experienced TRAINERS rest\ntheir partners after a tough battle.$"

TH_Local_CeruleanCenter_2::
    msgbox TH_Local_CeruleanCenter_2_Text, MSGBOX_NPC
    end

TH_Local_CeruleanCenter_2_Text:
    .string "My team needed a rest after\nclimbing through MT. MOON.$"

TH_Local_CeruleanCenter_3::
    msgbox TH_Local_CeruleanCenter_3_Text, MSGBOX_NPC
    end

TH_Local_CeruleanCenter_3_Text:
    .string "That PC keeps my extra POKéMON\nsafe while I travel.$"

TH_Local_CeruleanCenter_4::
    msgbox TH_Local_CeruleanCenter_4_Text, MSGBOX_NPC
    end

TH_Local_CeruleanCenter_4_Text:
    .string "The northern bridge is famous\nfor its challenging TRAINERS.$"

TH_Local_CeruleanHouse1_0::
    msgbox TH_Local_CeruleanHouse1_0_Text, MSGBOX_NPC
    end

TH_Local_CeruleanHouse1_0_Text:
    .string "Badges record your progress.\nMISTY awards the CASCADEBADGE.$"

TH_Local_CeruleanHouse2_0::
    msgbox TH_Local_CeruleanHouse2_0_Text, MSGBOX_NPC
    end

TH_Local_CeruleanHouse2_0_Text:
    .string "We are repairing the damage.\nThe back path is open again.$"

TH_Local_CeruleanHouse2_1::
    msgbox TH_Local_CeruleanHouse2_1_Text, MSGBOX_NPC
    end

TH_Local_CeruleanHouse2_1_Text:
    .string "Please wipe your shoes. There\nis dust everywhere after repairs.$"

TH_Sign_CeruleanHouse2_0::
    msgbox TH_Sign_CeruleanHouse2_0_Text, MSGBOX_NPC
    end

TH_Sign_CeruleanHouse2_0_Text:
    .string "Please respect this home\nand its residents.$"

TH_Local_CeruleanHouse3_0::
    msgbox TH_Local_CeruleanHouse3_0_Text, MSGBOX_NPC
    end

TH_Local_CeruleanHouse3_0_Text:
    .string "I enjoy comparing POKéMON\nfrom different regions.$"

TH_Local_CeruleanHouse3_1::
    msgbox TH_Local_CeruleanHouse3_1_Text, MSGBOX_NPC
    end

TH_Local_CeruleanHouse3_1_Text:
    .string "A JOHTO visitor described a\ngreen POKéMON with a leaf.$"

TH_Local_CeruleanHouse4_0::
    msgbox TH_Local_CeruleanHouse4_0_Text, MSGBOX_NPC
    end

TH_Local_CeruleanHouse4_0_Text:
    .string "Berries can help POKéMON train.\nThe VIRIDIAN seller has some.$"

TH_Local_CeruleanHouse5_0::
    msgbox TH_Local_CeruleanHouse5_0_Text, MSGBOX_NPC
    end

TH_Local_CeruleanHouse5_0_Text:
    .string "I study berries and their uses.\nMy workshop opens in a later chapter.$"

TH_Sign_CeruleanHouse5_0::
    msgbox TH_Sign_CeruleanHouse5_0_Text, MSGBOX_NPC
    end

TH_Sign_CeruleanHouse5_0_Text:
    .string "Please respect this home\nand its residents.$"

TH_Local_CeruleanBikeShop_0::
    msgbox TH_Local_CeruleanBikeShop_0_Text, MSGBOX_NPC
    end

TH_Local_CeruleanBikeShop_0_Text:
    .string "The bicycles are being serviced.\nSales open in a later chapter.$"

TH_Local_CeruleanBikeShop_1::
    msgbox TH_Local_CeruleanBikeShop_1_Text, MSGBOX_NPC
    end

TH_Local_CeruleanBikeShop_1_Text:
    .string "A bike would make the trip back\nto PALLET much quicker.$"

TH_Local_CeruleanBikeShop_2::
    msgbox TH_Local_CeruleanBikeShop_2_Text, MSGBOX_NPC
    end

TH_Local_CeruleanBikeShop_2_Text:
    .string "The bicycles are being serviced.\nSales open in a later chapter.$"

TH_Sign_CeruleanBikeShop_0::
    msgbox TH_Sign_CeruleanBikeShop_0_Text, MSGBOX_NPC
    end

TH_Sign_CeruleanBikeShop_0_Text:
    .string "Please respect this home\nand its residents.$"

TH_Sign_CeruleanBikeShop_1::
    msgbox TH_Sign_CeruleanBikeShop_1_Text, MSGBOX_NPC
    end

TH_Sign_CeruleanBikeShop_1_Text:
    .string "Please respect this home\nand its residents.$"

TH_Sign_CeruleanBikeShop_2::
    msgbox TH_Sign_CeruleanBikeShop_2_Text, MSGBOX_NPC
    end

TH_Sign_CeruleanBikeShop_2_Text:
    .string "Please respect this home\nand its residents.$"

TH_Sign_CeruleanBikeShop_3::
    msgbox TH_Sign_CeruleanBikeShop_3_Text, MSGBOX_NPC
    end

TH_Sign_CeruleanBikeShop_3_Text:
    .string "Please respect this home\nand its residents.$"

TH_Sign_CeruleanBikeShop_4::
    msgbox TH_Sign_CeruleanBikeShop_4_Text, MSGBOX_NPC
    end

TH_Sign_CeruleanBikeShop_4_Text:
    .string "Please respect this home\nand its residents.$"

TH_Sign_CeruleanBikeShop_5::
    msgbox TH_Sign_CeruleanBikeShop_5_Text, MSGBOX_NPC
    end

TH_Sign_CeruleanBikeShop_5_Text:
    .string "Please respect this home\nand its residents.$"

TH_Sign_CeruleanBikeShop_6::
    msgbox TH_Sign_CeruleanBikeShop_6_Text, MSGBOX_NPC
    end

TH_Sign_CeruleanBikeShop_6_Text:
    .string "Please respect this home\nand its residents.$"

TH_Sign_CeruleanBikeShop_7::
    msgbox TH_Sign_CeruleanBikeShop_7_Text, MSGBOX_NPC
    end

TH_Sign_CeruleanBikeShop_7_Text:
    .string "Please respect this home\nand its residents.$"

TH_Local_RivalHouse_0::
    msgbox TH_Local_RivalHouse_0_Text, MSGBOX_NPC
    end

TH_Local_RivalHouse_0_Text:
    .string "Your rival is always rushing off!\nI hope you two look after each other.$"

TH_Local_RivalHouse_1::
    msgbox TH_Local_RivalHouse_1_Text, MSGBOX_NPC
    end

TH_Local_RivalHouse_1_Text:
    .string "Your rival is always rushing off!\nI hope you two look after each other.$"

TH_Sign_RivalHouse_0::
    msgbox TH_Sign_RivalHouse_0_Text, MSGBOX_NPC
    end

TH_Sign_RivalHouse_0_Text:
    .string "Please respect this home\nand its residents.$"

TH_Sign_RivalHouse_1::
    msgbox TH_Sign_RivalHouse_1_Text, MSGBOX_NPC
    end

TH_Sign_RivalHouse_1_Text:
    .string "Please respect this home\nand its residents.$"

TH_Sign_RivalHouse_2::
    msgbox TH_Sign_RivalHouse_2_Text, MSGBOX_NPC
    end

TH_Sign_RivalHouse_2_Text:
    .string "Please respect this home\nand its residents.$"

TH_Local_ViridianHouse_0::
    msgbox TH_Local_ViridianHouse_0_Text, MSGBOX_NPC
    end

TH_Local_ViridianHouse_0_Text:
    .string "I like quiet mornings in\nVIRIDIAN CITY.$"

TH_Local_ViridianHouse_1::
    msgbox TH_Local_ViridianHouse_1_Text, MSGBOX_NPC
    end

TH_Local_ViridianHouse_1_Text:
    .string "Different regions mean different\nhabitats. What have you spotted?$"

TH_Local_ViridianHouse_2::
    msgbox TH_Local_ViridianHouse_2_Text, MSGBOX_NPC
    end

TH_Local_ViridianHouse_2_Text:
    .string "I like quiet mornings in\nVIRIDIAN CITY.$"

TH_Sign_ViridianHouse_0::
    msgbox TH_Sign_ViridianHouse_0_Text, MSGBOX_NPC
    end

TH_Sign_ViridianHouse_0_Text:
    .string "Please respect this home\nand its residents.$"

TH_Local_ViridianSchool_0::
    msgbox TH_Local_ViridianSchool_0_Text, MSGBOX_NPC
    end

TH_Local_ViridianSchool_0_Text:
    .string "A POKéMON can hold a training\nitem to improve its EV gains.$"

TH_Local_ViridianSchool_1::
    msgbox TH_Local_ViridianSchool_1_Text, MSGBOX_NPC
    end

TH_Local_ViridianSchool_1_Text:
    .string "The SUMMARY screen shows your\nPOKéMON's IVs and EVs.$"

TH_Sign_ViridianSchool_0::
    msgbox TH_Sign_ViridianSchool_0_Text, MSGBOX_NPC
    end

TH_Sign_ViridianSchool_0_Text:
    .string "Please respect this home\nand its residents.$"

TH_Sign_ViridianSchool_1::
    msgbox TH_Sign_ViridianSchool_1_Text, MSGBOX_NPC
    end

TH_Sign_ViridianSchool_1_Text:
    .string "Please respect this home\nand its residents.$"

TH_Sign_ViridianSchool_2::
    msgbox TH_Sign_ViridianSchool_2_Text, MSGBOX_NPC
    end

TH_Sign_ViridianSchool_2_Text:
    .string "Please respect this home\nand its residents.$"

TH_Sign_ViridianSchool_3::
    msgbox TH_Sign_ViridianSchool_3_Text, MSGBOX_NPC
    end

TH_Sign_ViridianSchool_3_Text:
    .string "Please respect this home\nand its residents.$"

TH_Sign_ViridianSchool_4::
    msgbox TH_Sign_ViridianSchool_4_Text, MSGBOX_NPC
    end

TH_Sign_ViridianSchool_4_Text:
    .string "Please respect this home\nand its residents.$"

TH_Sign_ViridianGym_0::
    msgbox TH_Sign_ViridianGym_0_Text, MSGBOX_NPC
    end

TH_Sign_ViridianGym_0_Text:
    .string "Please respect this home\nand its residents.$"

TH_Sign_ViridianGym_1::
    msgbox TH_Sign_ViridianGym_1_Text, MSGBOX_NPC
    end

TH_Sign_ViridianGym_1_Text:
    .string "Please respect this home\nand its residents.$"

TH_Pickup_24::
    lock
    faceplayer
    goto_if_set FLAG_TH_PICKUP_24, TH_PickupDone
    giveitem ITEM_MACHO_BRACE
    goto_if_eq VAR_RESULT, FALSE, TH_PickupFull
    setflag FLAG_TH_PICKUP_24
    removeobject VAR_LAST_TALKED
    release
    end

TH_Local_PewterHouse1_0::
    msgbox TH_Local_PewterHouse1_0_Text, MSGBOX_NPC
    end

TH_Local_PewterHouse1_0_Text:
    .string "Some POKéMON evolve with a\nstone instead of gaining levels.$"

TH_Local_PewterHouse1_1::
    msgbox TH_Local_PewterHouse1_1_Text, MSGBOX_NPC
    end

TH_Local_PewterHouse1_1_Text:
    .string "MOON STONES are sometimes found\ninside MT. MOON.$"

TH_Local_PewterHouse1_2::
    playmoncry SPECIES_NIDORAN_M, CRY_MODE_NORMAL
    msgbox TH_Local_PewterHouse1_2_Text, MSGBOX_NPC
    end

TH_Local_PewterHouse1_2_Text:
    .string "NIDORAN: Nido! Nido!$"

TH_Local_PewterHouse2_0::
    msgbox TH_Local_PewterHouse2_0_Text, MSGBOX_NPC
    end

TH_Local_PewterHouse2_0_Text:
    .string "Every POKéMON has its own\nstrengths. Keep trying new teams.$"

TH_Local_PewterHouse2_1::
    msgbox TH_Local_PewterHouse2_1_Text, MSGBOX_NPC
    end

TH_Local_PewterHouse2_1_Text:
    .string "Your first badge is only\nthe beginning of your journey.$"

TH_Local_PewterMuseum1F_0::
    msgbox TH_Local_PewterMuseum1F_0_Text, MSGBOX_NPC
    end

TH_Local_PewterMuseum1F_0_Text:
    .string "Welcome to the MUSEUM! Admission\nis free. Enjoy the exhibits!$"

TH_Local_PewterMuseum1F_1::
    msgbox TH_Local_PewterMuseum1F_1_Text, MSGBOX_NPC
    end

TH_Local_PewterMuseum1F_1_Text:
    .string "Fossils tell stories from\na world long before ours.$"

TH_Local_PewterMuseum1F_2::
    msgbox TH_Local_PewterMuseum1F_2_Text, MSGBOX_NPC
    end

TH_Local_PewterMuseum1F_2_Text:
    .string "Our colleagues on CINNABAR study\nhow to bring fossils back to life.$"

TH_Local_PewterMuseum1F_3::
    msgbox TH_Local_PewterMuseum1F_3_Text, MSGBOX_NPC
    end

TH_Local_PewterMuseum1F_3_Text:
    .string "A tiny shape is trapped inside\nthis piece of ancient amber.$"

TH_Local_PewterMuseum1F_4::
    msgbox TH_Local_PewterMuseum1F_4_Text, MSGBOX_NPC
    end

TH_Local_PewterMuseum1F_4_Text:
    .string "We brush away rock a grain at a\ntime. Fossils are very delicate.$"

TH_Local_PewterMuseum1F_5::
    msgbox TH_Local_PewterMuseum1F_5_Text, MSGBOX_NPC
    end

TH_Local_PewterMuseum1F_5_Text:
    .string "A fossil can reveal how an ancient\nPOKéMON moved, ate, and lived.$"

TH_Sign_PewterMuseum1F_0::
    msgbox TH_Sign_PewterMuseum1F_0_Text, MSGBOX_NPC
    end

TH_Sign_PewterMuseum1F_0_Text:
    .string "KABUTOPS FOSSIL\nAn ancient seafloor predator.$"

TH_Sign_PewterMuseum1F_1::
    msgbox TH_Sign_PewterMuseum1F_1_Text, MSGBOX_NPC
    end

TH_Sign_PewterMuseum1F_1_Text:
    .string "AERODACTYL FOSSIL\nAn ancient ruler of the skies.$"

TH_Sign_PewterMuseum1F_2::
    msgbox TH_Sign_PewterMuseum1F_2_Text, MSGBOX_NPC
    end

TH_Sign_PewterMuseum1F_2_Text:
    .string "PEWTER MUSEUM\nFossils and natural history.$"

TH_Sign_PewterMuseum1F_3::
    msgbox TH_Sign_PewterMuseum1F_3_Text, MSGBOX_NPC
    end

TH_Sign_PewterMuseum1F_3_Text:
    .string "Please do not touch the specimens.\nEven a small crack can damage them.$"

TH_Local_PewterMuseum2F_0::
    msgbox TH_Local_PewterMuseum2F_0_Text, MSGBOX_NPC
    end

TH_Local_PewterMuseum2F_0_Text:
    .string "We study stones that fell from\nspace. Each one has a story.$"

TH_Local_PewterMuseum2F_1::
    msgbox TH_Local_PewterMuseum2F_1_Text, MSGBOX_NPC
    end

TH_Local_PewterMuseum2F_1_Text:
    .string "That model shows a spacecraft.\nIt makes KANTO seem very small.$"

TH_Local_PewterMuseum2F_2::
    msgbox TH_Local_PewterMuseum2F_2_Text, MSGBOX_NPC
    end

TH_Local_PewterMuseum2F_2_Text:
    .string "I came for the fossils, but\nI stayed for the space exhibit.$"

TH_Local_PewterMuseum2F_3::
    msgbox TH_Local_PewterMuseum2F_3_Text, MSGBOX_NPC
    end

TH_Local_PewterMuseum2F_3_Text:
    .string "Dad, do you think PIKACHU could\ncome to the moon with us?$"

TH_Local_PewterMuseum2F_4::
    msgbox TH_Local_PewterMuseum2F_4_Text, MSGBOX_NPC
    end

TH_Local_PewterMuseum2F_4_Text:
    .string "My daughter loves this exhibit.\nShe dreams bigger every visit.$"

TH_Sign_PewterMuseum2F_0::
    msgbox TH_Sign_PewterMuseum2F_0_Text, MSGBOX_NPC
    end

TH_Sign_PewterMuseum2F_0_Text:
    .string "SPACE EXHIBIT\nA journey beyond our world.$"

TH_Sign_PewterMuseum2F_1::
    msgbox TH_Sign_PewterMuseum2F_1_Text, MSGBOX_NPC
    end

TH_Sign_PewterMuseum2F_1_Text:
    .string "A model of a spacecraft built\nto carry explorers into space.$"

TH_Sign_PewterMuseum2F_2::
    msgbox TH_Sign_PewterMuseum2F_2_Text, MSGBOX_NPC
    end

TH_Sign_PewterMuseum2F_2_Text:
    .string "METEORITE\nA stone that fell from the sky.$"

TH_Sign_PewterMuseum2F_3::
    msgbox TH_Sign_PewterMuseum2F_3_Text, MSGBOX_NPC
    end

TH_Sign_PewterMuseum2F_3_Text:
    .string "The moon, seen through a powerful\ntelescope on a clear night.$"

TH_Sign_PewterMuseum2F_4::
    msgbox TH_Sign_PewterMuseum2F_4_Text, MSGBOX_NPC
    end

TH_Sign_PewterMuseum2F_4_Text:
    .string "A chart showing the paths\nof planets around the sun.$"

TH_Sign_PewterMuseum2F_5::
    msgbox TH_Sign_PewterMuseum2F_5_Text, MSGBOX_NPC
    end

TH_Sign_PewterMuseum2F_5_Text:
    .string "A suit designed to protect\nexplorers in space.$"

TH_Sign_PewterMuseum2F_6::
    msgbox TH_Sign_PewterMuseum2F_6_Text, MSGBOX_NPC
    end

TH_Sign_PewterMuseum2F_6_Text:
    .string "Photographs taken far above\nthe clouds.$"

TH_Sign_PewterMuseum2F_7::
    msgbox TH_Sign_PewterMuseum2F_7_Text, MSGBOX_NPC
    end

TH_Sign_PewterMuseum2F_7_Text:
    .string "What might we discover beyond\nthe next horizon?$"

TH_ViridianGym_Attendant::
    msgbox TH_ViridianGym_Attendant_Text, MSGBOX_NPC
    end

TH_ViridianGym_Attendant_Text:
    .string "The GYM LEADER is away.\nOfficial challenges are closed.$"

TH_RegionalAide::
    msgbox TH_RegionalAide_Text, MSGBOX_NPC
    end

TH_RegionalAide_Text:
    .string "OAK, ELM, and BIRCH asked me to\ncompare the habitats near MT. MOON.\pMAKUHITA tracks in KANTO caves!\nThe regions have more in common\lthan we thought.$"

TH_ChapterClosed::
    msgbox TH_ChapterClosed_Text, MSGBOX_NPC
    end

TH_ChapterClosed_Text:
    .string "This facility opens in a later\nchapter. Please use the main floor.$"

TH_PickupDone::
    release
    end
TH_PickupFull::
    msgbox TH_Text_PickupFull
    release
    end

TH_Text_PickupFull:
    .string "Your BAG is full. Make room\nand this item will still be here.$"

TH_Pickup_25::
    lock
    faceplayer
    goto_if_set FLAG_TH_PICKUP_25, TH_PickupDone
    giveitem ITEM_ETHER
    goto_if_eq VAR_RESULT, FALSE, TH_PickupFull
    setflag FLAG_TH_PICKUP_25
    removeobject VAR_LAST_TALKED
    release
    end

TH_Pickup_26::
    lock
    faceplayer
    goto_if_set FLAG_TH_PICKUP_26, TH_PickupDone
    giveitem ITEM_PARALYZE_HEAL
    goto_if_eq VAR_RESULT, FALSE, TH_PickupFull
    setflag FLAG_TH_PICKUP_26
    removeobject VAR_LAST_TALKED
    release
    end

TH_Pickup_27::
    lock
    faceplayer
    goto_if_set FLAG_TH_PICKUP_27, TH_PickupDone
    giveitem ITEM_POTION
    goto_if_eq VAR_RESULT, FALSE, TH_PickupFull
    setflag FLAG_TH_PICKUP_27
    removeobject VAR_LAST_TALKED
    release
    end

TH_Pickup_28::
    lock
    faceplayer
    goto_if_set FLAG_TH_PICKUP_28, TH_PickupDone
    giveitem ITEM_ANTIDOTE
    goto_if_eq VAR_RESULT, FALSE, TH_PickupFull
    setflag FLAG_TH_PICKUP_28
    removeobject VAR_LAST_TALKED
    release
    end

TH_Pickup_29::
    lock
    faceplayer
    goto_if_set FLAG_TH_PICKUP_29, TH_PickupDone
    giveitem ITEM_POKE_BALL
    goto_if_eq VAR_RESULT, FALSE, TH_PickupFull
    setflag FLAG_TH_PICKUP_29
    removeobject VAR_LAST_TALKED
    release
    end

TH_Pickup_30::
    lock
    faceplayer
    goto_if_set FLAG_TH_PICKUP_30, TH_PickupDone
    giveitem ITEM_ANTIDOTE
    goto_if_eq VAR_RESULT, FALSE, TH_PickupFull
    setflag FLAG_TH_PICKUP_30
    removeobject VAR_LAST_TALKED
    release
    end

TH_Pickup_31::
    lock
    faceplayer
    goto_if_set FLAG_TH_PICKUP_31, TH_PickupDone
    giveitem ITEM_POTION
    goto_if_eq VAR_RESULT, FALSE, TH_PickupFull
    setflag FLAG_TH_PICKUP_31
    removeobject VAR_LAST_TALKED
    release
    end

TH_Pickup_32::
    lock
    faceplayer
    goto_if_set FLAG_TH_PICKUP_32, TH_PickupDone
    giveitem ITEM_POTION
    goto_if_eq VAR_RESULT, FALSE, TH_PickupFull
    setflag FLAG_TH_PICKUP_32
    removeobject VAR_LAST_TALKED
    release
    end

