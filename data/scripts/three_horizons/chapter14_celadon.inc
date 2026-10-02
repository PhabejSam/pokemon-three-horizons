@ Project-owned Celadon dialogue and services. Deferred bindings are explicit in the content ledger.

TH14_CeladonCity_EventScript_RocketGrunt1::
    msgbox TH14_CeladonCity_EventScript_RocketGrunt1_Text, MSGBOX_NPC
    end

TH14_CeladonCity_EventScript_RocketGrunt1_Text::
    .string "Keep out of TEAM ROCKET's way!$"

TH14_CeladonCity_EventScript_FatMan::
    msgbox TH14_CeladonCity_EventScript_FatMan_Text, MSGBOX_NPC
    end

TH14_CeladonCity_EventScript_FatMan_Text::
    .string "This is my trusted pal, POLIWRATH.\pIt evolved from a POLIWHIRL when\nI used a WATER STONE.$"

TH14_CeladonCity_EventScript_Poliwrath::
    lock
    faceplayer
    playmoncry SPECIES_POLIWRATH, CRY_MODE_NORMAL
    msgbox TH14_CeladonCity_EventScript_Poliwrath_Text
    waitmoncry
    release
    end

TH14_CeladonCity_EventScript_Poliwrath_Text::
    .string "POLIWRATH: Ribi ribit!$"

TH14_CeladonCity_EventScript_LittleGirl::
    msgbox TH14_CeladonCity_EventScript_LittleGirl_Text, MSGBOX_NPC
    end

TH14_CeladonCity_EventScript_LittleGirl_Text::
    .string "I got my KOFFING in CINNABAR.\pIt's usually nice, but it breathes\npoison when it's angry.$"

TH14_CeladonCity_EventScript_Woman::
    msgbox TH14_CeladonCity_EventScript_Woman_Text, MSGBOX_NPC
    end

TH14_CeladonCity_EventScript_Woman_Text::
    .string "CELADON takes pride in its efforts\nto keep the city beautiful.\pThat's why the new GAME CORNER is\nbad for our city's image.$"

TH14_CeladonCity_EventScript_OldMan2::
    msgbox TH14_CeladonCity_EventScript_OldMan2_Text, MSGBOX_NPC
    end

TH14_CeladonCity_EventScript_OldMan2_Text::
    .string "Moan…\nI blew it all at the slots!\pI knew I should have cashed in my\nCOINS for prizes!$"

TH14_CeladonCity_EventScript_SoftboiledTutor::
    lock
    faceplayer
    setvar VAR_0x8005, MOVE_SOFT_BOILED
    msgbox TH14_CeladonCity_EventScript_SoftboiledTutor_Text, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, TH14_TutorDone
    msgbox TH_Tutor11Choose
    special ChooseMonForMoveTutor
    lock
    faceplayer
    msgbox TH_Tutor11Return
    goto TH14_TutorDone

TH14_CeladonCity_EventScript_SoftboiledTutor_Text::
    .string "Would you like a lesson in\nSOFT-BOILED?\pMy lessons are free. Bring any\ncompatible partner, any time.$"

TH14_CeladonCity_EventScript_RocketGrunt2::
    msgbox TH14_CeladonCity_EventScript_RocketGrunt2_Text, MSGBOX_NPC
    end

TH14_CeladonCity_EventScript_RocketGrunt2_Text::
    .string "What are you staring at?\nGet lost, or I'll punch you.$"

TH14_CeladonCity_EventScript_OldMan1::
    msgbox TH14_CeladonCity_EventScript_OldMan1_Text, MSGBOX_NPC
    end

TH14_CeladonCity_EventScript_OldMan1_Text::
    .string "ERIKA's garden is beautiful.\nHer POKéMON help tend the flowers.$"

TH14_CeladonCity_EventScript_Boy::
    msgbox TH14_CeladonCity_EventScript_Boy_Text, MSGBOX_NPC
    end

TH14_CeladonCity_EventScript_Boy_Text::
    .string "The old woman in the MANSION\nlives with her POKéMON.\pThey always look so content!$"

TH14_CeladonCity_EventScript_SilphCoScientist::
    msgbox TH14_CeladonCity_EventScript_SilphCoScientist_Text, MSGBOX_NPC
    end

TH14_CeladonCity_EventScript_SilphCoScientist_Text::
    .string "Oh, what am I to do…\pSomeone stole our SILPH SCOPE.\pThe thief came running this way,\nI'm sure of it.\pBut I lost sight of him!\nWhere'd he go?$"

TH14_CeladonCity_EventScript_TrainerTips2::
    msgbox TH14_CeladonCity_EventScript_TrainerTips2_Text, MSGBOX_SIGN
    end

TH14_CeladonCity_EventScript_TrainerTips2_Text::
    .string "TRAINER TIPS\pGUARD SPEC. protects POKéMON\nfrom status-reduction moves during\lbattle.\pGet your items at the\nCELADON DEPT. STORE!$"

TH14_CeladonCity_EventScript_PrizeExchangeSign::
    msgbox TH14_CeladonCity_EventScript_PrizeExchangeSign_Text, MSGBOX_SIGN
    end

TH14_CeladonCity_EventScript_PrizeExchangeSign_Text::
    .string "COINS exchanged for prizes!\nPRIZE EXCHANGE$"

TH14_CeladonCity_EventScript_GameCornerSign::
    msgbox TH14_CeladonCity_EventScript_GameCornerSign_Text, MSGBOX_SIGN
    end

TH14_CeladonCity_EventScript_GameCornerSign_Text::
    .string "ROCKET GAME CORNER\nThe playground for grown-ups!$"

TH14_CeladonCity_EventScript_CitySign::
    msgbox TH14_CeladonCity_EventScript_CitySign_Text, MSGBOX_SIGN
    end

TH14_CeladonCity_EventScript_CitySign_Text::
    .string "CELADON CITY\nThe City of Rainbow Dreams$"

TH14_CeladonCity_EventScript_MansionSign::
    msgbox TH14_CeladonCity_EventScript_MansionSign_Text, MSGBOX_SIGN
    end

TH14_CeladonCity_EventScript_MansionSign_Text::
    .string "CELADON MANSION$"

TH14_CeladonCity_EventScript_TrainerTips1::
    msgbox TH14_CeladonCity_EventScript_TrainerTips1_Text, MSGBOX_SIGN
    end

TH14_CeladonCity_EventScript_TrainerTips1_Text::
    .string "TRAINER TIPS\pX ACCURACY boosts the accuracy of\ntechniques.\pDIRE HIT jacks up the likelihood\nof critical hits.\pGet your items at the CELADON\nDEPT. STORE!$"

TH14_CeladonCity_EventScript_DeptStoreSign::
    msgbox TH14_CeladonCity_EventScript_DeptStoreSign_Text, MSGBOX_SIGN
    end

TH14_CeladonCity_EventScript_DeptStoreSign_Text::
    .string "Find what you need at the\nCELADON DEPT. STORE!$"

TH14_CeladonCity_EventScript_GymSign::
    msgbox TH14_CeladonCity_EventScript_GymSign_Text, MSGBOX_SIGN
    end

TH14_CeladonCity_EventScript_GymSign_Text::
    .string "CELADON CITY POKéMON GYM\nLEADER: ERIKA\lThe Nature-Loving Princess!$"

TH14_CeladonCity_PokemonCenter_1F_EventScript_Gentleman::
    msgbox TH14_CeladonCity_PokemonCenter_1F_EventScript_Gentleman_Text, MSGBOX_NPC
    end

TH14_CeladonCity_PokemonCenter_1F_EventScript_Gentleman_Text::
    .string "A POKé FLUTE awakens sleeping\nPOKéMON. You know that.\pIt does so with a sound that only\nthey can hear.$"

TH14_CeladonCity_PokemonCenter_1F_EventScript_CooltrainerF::
    msgbox TH14_CeladonCity_PokemonCenter_1F_EventScript_CooltrainerF_Text, MSGBOX_NPC
    end

TH14_CeladonCity_PokemonCenter_1F_EventScript_CooltrainerF_Text::
    .string "I have been cycling all day.\nMy team deserves a rest, too.$"

TH14_CeladonCity_PokemonCenter_1F_EventScript_Youngster::
    msgbox TH14_CeladonCity_PokemonCenter_1F_EventScript_Youngster_Text, MSGBOX_NPC
    end

TH14_CeladonCity_PokemonCenter_1F_EventScript_Youngster_Text::
    .string "The western road is closed.\nI can still ride around the city!$"

TH14_CeladonCity_Gym_EventScript_Kay::
    msgbox TH14_CeladonCity_Gym_EventScript_Kay_Text, MSGBOX_NPC
    end

TH14_CeladonCity_Gym_EventScript_Kay_Text::
    .string "Please wait a moment.\nI will be with you shortly.$"

TH14_CeladonCity_Gym_EventScript_Bridget::
    msgbox TH14_CeladonCity_Gym_EventScript_Bridget_Text, MSGBOX_NPC
    end

TH14_CeladonCity_Gym_EventScript_Bridget_Text::
    .string "Please wait a moment.\nI will be with you shortly.$"

TH14_CeladonCity_Gym_EventScript_Tina::
    msgbox TH14_CeladonCity_Gym_EventScript_Tina_Text, MSGBOX_NPC
    end

TH14_CeladonCity_Gym_EventScript_Tina_Text::
    .string "Please wait a moment.\nI will be with you shortly.$"

TH14_CeladonCity_Gym_EventScript_Tamia::
    msgbox TH14_CeladonCity_Gym_EventScript_Tamia_Text, MSGBOX_NPC
    end

TH14_CeladonCity_Gym_EventScript_Tamia_Text::
    .string "Please wait a moment.\nI will be with you shortly.$"

TH14_CeladonCity_Gym_EventScript_Lori::
    msgbox TH14_CeladonCity_Gym_EventScript_Lori_Text, MSGBOX_NPC
    end

TH14_CeladonCity_Gym_EventScript_Lori_Text::
    .string "Please wait a moment.\nI will be with you shortly.$"

TH14_CeladonCity_Gym_EventScript_Lisa::
    msgbox TH14_CeladonCity_Gym_EventScript_Lisa_Text, MSGBOX_NPC
    end

TH14_CeladonCity_Gym_EventScript_Lisa_Text::
    .string "Please wait a moment.\nI will be with you shortly.$"

TH14_CeladonCity_Gym_EventScript_Erika::
    msgbox TH14_CeladonCity_Gym_EventScript_Erika_Text, MSGBOX_NPC
    end

TH14_CeladonCity_Gym_EventScript_Erika_Text::
    .string "Please wait a moment.\nI will be with you shortly.$"

TH14_CeladonCity_Gym_EventScript_Mary::
    msgbox TH14_CeladonCity_Gym_EventScript_Mary_Text, MSGBOX_NPC
    end

TH14_CeladonCity_Gym_EventScript_Mary_Text::
    .string "Please wait a moment.\nI will be with you shortly.$"

TH14_CeladonCity_Gym_EventScript_GymStatue::
    msgbox TH14_CeladonCity_Gym_EventScript_GymStatue_Text, MSGBOX_NPC
    end

TH14_CeladonCity_Gym_EventScript_GymStatue_Text::
    .string "Please wait a moment.\nI will be with you shortly.$"

TH14_CeladonCity_DepartmentStore_1F_EventScript_Receptionist::
    msgbox TH14_CeladonCity_DepartmentStore_1F_EventScript_Receptionist_Text, MSGBOX_NPC
    end

TH14_CeladonCity_DepartmentStore_1F_EventScript_Receptionist_Text::
    .string "Hello!\nWelcome to CELADON DEPT. STORE.\pThe board on the right describes\nthe store layout.$"

TH14_CeladonCity_DepartmentStore_1F_EventScript_LayoutSign::
    msgbox TH14_CeladonCity_DepartmentStore_1F_EventScript_LayoutSign_Text, MSGBOX_SIGN
    end

TH14_CeladonCity_DepartmentStore_1F_EventScript_LayoutSign_Text::
    .string "1F: SERVICE COUNTER\p2F: TRAINER'S MARKET\p3F: TV GAME SHOP\p4F: WISE MAN GIFTS\p5F: DRUGSTORE\pROOFTOP SQUARE: VENDING MACHINES$"

TH14_CeladonCity_DepartmentStore_1F_EventScript_FloorSign::
    msgbox TH14_CeladonCity_DepartmentStore_1F_EventScript_FloorSign_Text, MSGBOX_SIGN
    end

TH14_CeladonCity_DepartmentStore_1F_EventScript_FloorSign_Text::
    .string "1F: SERVICE COUNTER$"

TH14_CeladonCity_DepartmentStore_2F_EventScript_Lass::
    msgbox TH14_CeladonCity_DepartmentStore_2F_EventScript_Lass_Text, MSGBOX_NPC
    end

TH14_CeladonCity_DepartmentStore_2F_EventScript_Lass_Text::
    .string "For long outings, you should buy\nREVIVE.$"

TH14_CeladonCity_DepartmentStore_2F_EventScript_ClerkItems::
lockall
    faceplayer
    msgbox TH14_EcoWelcome
    closemessage
    setvar VAR_0x8004, 0
    special TH14_ScriptOpenShop
    goto_if_eq VAR_RESULT, 0, TH14_EcoNoStock
    waitstate
    releaseall
    end

TH14_CeladonCity_DepartmentStore_2F_EventScript_ClerkTMs::
lockall
    faceplayer
    msgbox TH14_EcoWelcome
    closemessage
    setvar VAR_0x8004, 1
    special TH14_ScriptOpenShop
    goto_if_eq VAR_RESULT, 0, TH14_EcoNoStock
    waitstate
    releaseall
    end

TH14_CeladonCity_DepartmentStore_2F_EventScript_Woman::
    msgbox TH14_CeladonCity_DepartmentStore_2F_EventScript_Woman_Text, MSGBOX_NPC
    end

TH14_CeladonCity_DepartmentStore_2F_EventScript_Woman_Text::
    .string "TMs can be used again and again.\nCheck which partners can learn them.$"

TH14_CeladonCity_DepartmentStore_2F_EventScript_FloorSign::
    msgbox TH14_CeladonCity_DepartmentStore_2F_EventScript_FloorSign_Text, MSGBOX_SIGN
    end

TH14_CeladonCity_DepartmentStore_2F_EventScript_FloorSign_Text::
    .string "Top-Grade Items for TRAINERS!\p2F: TRAINER'S MARKET$"

TH14_CeladonCity_DepartmentStore_3F_EventScript_CounterTutor::
    lock
    faceplayer
    setvar VAR_0x8005, MOVE_COUNTER
    msgbox TH14_CeladonCity_DepartmentStore_3F_EventScript_CounterTutor_Text, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, TH14_TutorDone
    msgbox TH_Tutor11Choose
    special ChooseMonForMoveTutor
    lock
    faceplayer
    msgbox TH_Tutor11Return
    goto TH14_TutorDone

TH14_CeladonCity_DepartmentStore_3F_EventScript_CounterTutor_Text::
    .string "Would you like a lesson in\nCOUNTER?\pMy lessons are free. Bring any\ncompatible partner, any time.$"

TH14_CeladonCity_DepartmentStore_3F_EventScript_GBAKid1::
    msgbox TH14_CeladonCity_DepartmentStore_3F_EventScript_GBAKid1_Text, MSGBOX_NPC
    end

TH14_CeladonCity_DepartmentStore_3F_EventScript_GBAKid1_Text::
    .string "Captured POKéMON are registered\nwith an ID No. and the OT.\pOT stands for “Original TRAINER” -\nthe TRAINER that caught it first.$"

TH14_CeladonCity_DepartmentStore_3F_EventScript_GBAKid3::
    msgbox TH14_CeladonCity_DepartmentStore_3F_EventScript_GBAKid3_Text, MSGBOX_NPC
    end

TH14_CeladonCity_DepartmentStore_3F_EventScript_GBAKid3_Text::
    .string "I love HAUNTER!\nThat mischievous grin is the best.$"

TH14_CeladonCity_DepartmentStore_3F_EventScript_GBAKid2::
    msgbox TH14_CeladonCity_DepartmentStore_3F_EventScript_GBAKid2_Text, MSGBOX_NPC
    end

TH14_CeladonCity_DepartmentStore_3F_EventScript_GBAKid2_Text::
    .string "I am training my HAUNTER.\nEvery battle helps it grow!$"

TH14_CeladonCity_DepartmentStore_3F_EventScript_LittleGirl::
    msgbox TH14_CeladonCity_DepartmentStore_3F_EventScript_LittleGirl_Text, MSGBOX_NPC
    end

TH14_CeladonCity_DepartmentStore_3F_EventScript_LittleGirl_Text::
    .string "You can identify POKéMON you get\nin trades by their ID Numbers.$"

TH14_CeladonCity_DepartmentStore_3F_EventScript_FloorSign::
    msgbox TH14_CeladonCity_DepartmentStore_3F_EventScript_FloorSign_Text, MSGBOX_SIGN
    end

TH14_CeladonCity_DepartmentStore_3F_EventScript_FloorSign_Text::
    .string "3F: TV GAME SHOP$"

TH14_CeladonCity_DepartmentStore_3F_EventScript_TV1::
    msgbox TH14_CeladonCity_DepartmentStore_3F_EventScript_TV1_Text, MSGBOX_SIGN
    end

TH14_CeladonCity_DepartmentStore_3F_EventScript_TV1_Text::
    .string "An RPG!\nThere's no time for that!$"

TH14_CeladonCity_DepartmentStore_3F_EventScript_TV2::
    msgbox TH14_CeladonCity_DepartmentStore_3F_EventScript_TV2_Text, MSGBOX_SIGN
    end

TH14_CeladonCity_DepartmentStore_3F_EventScript_TV2_Text::
    .string "A sports game!\nDad'll like that!$"

TH14_CeladonCity_DepartmentStore_3F_EventScript_TV3::
    msgbox TH14_CeladonCity_DepartmentStore_3F_EventScript_TV3_Text, MSGBOX_SIGN
    end

TH14_CeladonCity_DepartmentStore_3F_EventScript_TV3_Text::
    .string "A puzzle game!\nLooks addictive!$"

TH14_CeladonCity_DepartmentStore_3F_EventScript_TV4::
    msgbox TH14_CeladonCity_DepartmentStore_3F_EventScript_TV4_Text, MSGBOX_SIGN
    end

TH14_CeladonCity_DepartmentStore_3F_EventScript_TV4_Text::
    .string "A fighting game!\nLooks tough!$"

TH14_CeladonCity_DepartmentStore_3F_EventScript_SuperNES::
    msgbox TH14_CeladonCity_DepartmentStore_3F_EventScript_SuperNES_Text, MSGBOX_SIGN
    end

TH14_CeladonCity_DepartmentStore_3F_EventScript_SuperNES_Text::
    .string "It's a Super NES.$"

TH14_CeladonCity_DepartmentStore_3F_EventScript_Poster::
    msgbox TH14_CeladonCity_DepartmentStore_3F_EventScript_Poster_Text, MSGBOX_SIGN
    end

TH14_CeladonCity_DepartmentStore_3F_EventScript_Poster_Text::
    .string "Red and Green!\nBoth are POKéMON!$"

TH14_CeladonCity_DepartmentStore_4F_EventScript_Man::
    msgbox TH14_CeladonCity_DepartmentStore_4F_EventScript_Man_Text, MSGBOX_NPC
    end

TH14_CeladonCity_DepartmentStore_4F_EventScript_Man_Text::
    .string "I'm getting a present for my\ngirlfriend.\pI guess a POKé DOLL will be it.\nIt's the popular thing.$"

TH14_CeladonCity_DepartmentStore_4F_EventScript_Youngster::
    msgbox TH14_CeladonCity_DepartmentStore_4F_EventScript_Youngster_Text, MSGBOX_NPC
    end

TH14_CeladonCity_DepartmentStore_4F_EventScript_Youngster_Text::
    .string "I heard something useful.\pIf a wild POKéMON appears, you can\ndistract it with a POKé DOLL.\pYou can run away while the wild\nPOKéMON is distracted.$"

TH14_CeladonCity_DepartmentStore_4F_EventScript_Clerk::
lockall
    faceplayer
    msgbox TH14_EcoWelcome
    closemessage
    setvar VAR_0x8004, 2
    special TH14_ScriptOpenShop
    goto_if_eq VAR_RESULT, 0, TH14_EcoNoStock
    waitstate
    releaseall
    end

TH14_CeladonCity_DepartmentStore_4F_EventScript_FloorSign::
    msgbox TH14_CeladonCity_DepartmentStore_4F_EventScript_FloorSign_Text, MSGBOX_SIGN
    end

TH14_CeladonCity_DepartmentStore_4F_EventScript_FloorSign_Text::
    .string "Express yourself with gifts!\n4F: WISE MAN GIFTS\pEvolution Special!\nElement STONES on sale now!$"

TH14_CeladonCity_DepartmentStore_5F_EventScript_Gentleman::
    msgbox TH14_CeladonCity_DepartmentStore_5F_EventScript_Gentleman_Text, MSGBOX_NPC
    end

TH14_CeladonCity_DepartmentStore_5F_EventScript_Gentleman_Text::
    .string "These vitamins help with training.\nEach one develops a different stat.$"

TH14_CeladonCity_DepartmentStore_5F_EventScript_Sailor::
    msgbox TH14_CeladonCity_DepartmentStore_5F_EventScript_Sailor_Text, MSGBOX_NPC
    end

TH14_CeladonCity_DepartmentStore_5F_EventScript_Sailor_Text::
    .string "I'm here for POKéMON stat\nenhancers.\pPROTEIN increases the base ATTACK\npower.\pIRON increases the base DEFENSE\nstat.$"

TH14_CeladonCity_DepartmentStore_5F_EventScript_ClerkXItems::
lockall
    faceplayer
    msgbox TH14_EcoWelcome
    closemessage
    setvar VAR_0x8004, 3
    special TH14_ScriptOpenShop
    goto_if_eq VAR_RESULT, 0, TH14_EcoNoStock
    waitstate
    releaseall
    end

TH14_CeladonCity_DepartmentStore_5F_EventScript_ClerkVitamins::
lockall
    faceplayer
    msgbox TH14_EcoWelcome
    closemessage
    setvar VAR_0x8004, 4
    special TH14_ScriptOpenShop
    goto_if_eq VAR_RESULT, 0, TH14_EcoNoStock
    waitstate
    releaseall
    end

TH14_CeladonCity_DepartmentStore_5F_EventScript_FloorSign::
    msgbox TH14_CeladonCity_DepartmentStore_5F_EventScript_FloorSign_Text, MSGBOX_SIGN
    end

TH14_CeladonCity_DepartmentStore_5F_EventScript_FloorSign_Text::
    .string "5F: DRUGSTORE$"

TH14_CeladonCity_DepartmentStore_Roof_EventScript_CooltrainerM::
    msgbox TH14_CeladonCity_DepartmentStore_Roof_EventScript_CooltrainerM_Text, MSGBOX_NPC
    end

TH14_CeladonCity_DepartmentStore_Roof_EventScript_CooltrainerM_Text::
    .string "My sister is a TRAINER, believe it\nor not.\pBut, she's so immature, she drives\nme nuts!$"

TH14_CeladonCity_DepartmentStore_Roof_EventScript_ThirstyGirl::
lockall
    faceplayer
    setvar VAR_0x8009, 0
    setvar VAR_0x8009, 0
    msgbox TH14_EcoChoose5
    dynmultichoice 12, 0, FALSE, 4, 0, DYN_MULTICHOICE_CB_NONE, TH14_EcoMenu_5_0_0, TH14_EcoMenu_5_0_1, TH14_EcoMenu_5_0_2, TH14_EcoExitText
    goto_if_ge VAR_RESULT, 3, TH14_EcoEnd
    copyvar VAR_0x8005, VAR_RESULT
    msgbox TH14_EcoConfirm, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, TH14_EcoEnd
    setvar VAR_0x8008, 5
    setvar VAR_0x8004, 5
    special TH14_ScriptEconomy
    goto TH14_EcoResult
    end

TH14_CeladonCity_DepartmentStore_Roof_EventScript_FloorSign::
    msgbox TH14_CeladonCity_DepartmentStore_Roof_EventScript_FloorSign_Text, MSGBOX_SIGN
    end

TH14_CeladonCity_DepartmentStore_Roof_EventScript_FloorSign_Text::
    .string "ROOFTOP SQUARE:\nVENDING MACHINES$"

TH14_CeladonCity_DepartmentStore_Roof_EventScript_VendingMachine::
lockall
    setvar VAR_0x8009, 0
    showmoneybox 0, 5
    setvar VAR_0x8009, 2
    msgbox TH14_EcoChoose4
    dynmultichoice 12, 0, FALSE, 4, 0, DYN_MULTICHOICE_CB_NONE, TH14_EcoMenu_4_0_0, TH14_EcoMenu_4_0_1, TH14_EcoMenu_4_0_2, TH14_EcoExitText
    goto_if_ge VAR_RESULT, 3, TH14_EcoEnd
    copyvar VAR_0x8005, VAR_RESULT
    msgbox TH14_EcoConfirm, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, TH14_EcoEnd
    setvar VAR_0x8008, 4
    setvar VAR_0x8004, 4
    special TH14_ScriptEconomy
    goto TH14_EcoResult
    end

TH14_CeladonCity_Condominiums_1F_EventScript_Meowth::
    lock
    faceplayer
    playmoncry SPECIES_MEOWTH, CRY_MODE_NORMAL
    msgbox TH14_CeladonCity_Condominiums_1F_EventScript_Meowth_Text
    waitmoncry
    release
    end

TH14_CeladonCity_Condominiums_1F_EventScript_Meowth_Text::
    .string "MEOWTH: Meow!$"

TH14_CeladonCity_Condominiums_1F_EventScript_Clefairy::
    lock
    faceplayer
    playmoncry SPECIES_CLEFAIRY, CRY_MODE_NORMAL
    msgbox TH14_CeladonCity_Condominiums_1F_EventScript_Clefairy_Text
    waitmoncry
    release
    end

TH14_CeladonCity_Condominiums_1F_EventScript_Clefairy_Text::
    .string "CLEFAIRY: Pi pippippi!$"

TH14_CeladonCity_Condominiums_1F_EventScript_Nidoran::
    lock
    faceplayer
    playmoncry SPECIES_NIDORAN_F, CRY_MODE_NORMAL
    msgbox TH14_CeladonCity_Condominiums_1F_EventScript_Nidoran_Text
    waitmoncry
    release
    end

TH14_CeladonCity_Condominiums_1F_EventScript_Nidoran_Text::
    .string "NIDORAN♀: Kya kyaoo!$"

TH14_CeladonCity_Condominiums_1F_EventScript_TeaWoman::
    msgbox TH14_CeladonCity_Condominiums_1F_EventScript_TeaWoman_Text, MSGBOX_NPC
    end

TH14_CeladonCity_Condominiums_1F_EventScript_TeaWoman_Text::
    .string "My POKéMON keep me company.\nA quiet afternoon suits us all.$"

TH14_CeladonCity_Condominiums_1F_EventScript_SuiteSign::
    msgbox TH14_CeladonCity_Condominiums_1F_EventScript_SuiteSign_Text, MSGBOX_SIGN
    end

TH14_CeladonCity_Condominiums_1F_EventScript_SuiteSign_Text::
    .string "CELADON MANSION\nManager's Suite$"

TH14_CeladonCity_Condominiums_2F_EventScript_PokemonJournalErika::
    msgbox TH14_CeladonCity_Condominiums_2F_EventScript_PokemonJournalErika_Text, MSGBOX_NPC
    end

TH14_CeladonCity_Condominiums_2F_EventScript_PokemonJournalErika_Text::
    .string "POKéMON JOURNAL\pERIKA studies flower arranging.\nHer partners help tend the garden.$"

TH14_CeladonCity_Condominiums_2F_EventScript_MeetingRoomSign::
    msgbox TH14_CeladonCity_Condominiums_2F_EventScript_MeetingRoomSign_Text, MSGBOX_SIGN
    end

TH14_CeladonCity_Condominiums_2F_EventScript_MeetingRoomSign_Text::
    .string "GAME FREAK Meeting Room$"

TH14_CeladonCity_Condominiums_3F_EventScript_Programmer::
    msgbox TH14_CeladonCity_Condominiums_3F_EventScript_Programmer_Text, MSGBOX_NPC
    end

TH14_CeladonCity_Condominiums_3F_EventScript_Programmer_Text::
    .string "Me?\nI'm the programmer!$"

TH14_CeladonCity_Condominiums_3F_EventScript_Designer::
    msgbox TH14_CeladonCity_Condominiums_3F_EventScript_Designer_Text, MSGBOX_NPC
    end

TH14_CeladonCity_Condominiums_3F_EventScript_Designer_Text::
    .string "I design games about POKéMON.\nThere is always something to learn!\pTake your time exploring.\nThe little discoveries matter, too.$"

TH14_CeladonCity_Condominiums_3F_EventScript_GraphicArtist::
    msgbox TH14_CeladonCity_Condominiums_3F_EventScript_GraphicArtist_Text, MSGBOX_NPC
    end

TH14_CeladonCity_Condominiums_3F_EventScript_GraphicArtist_Text::
    .string "I'm the graphic artist!\nI drew you!$"

TH14_CeladonCity_Condominiums_3F_EventScript_Writer::
    msgbox TH14_CeladonCity_Condominiums_3F_EventScript_Writer_Text, MSGBOX_NPC
    end

TH14_CeladonCity_Condominiums_3F_EventScript_Writer_Text::
    .string "I wrote the story!\nIsn't ERIKA cute?\pI like MISTY a lot, too!\nOh, and SABRINA, I like her!$"

TH14_CeladonCity_Condominiums_3F_EventScript_DevelopmentRoomSign::
    msgbox TH14_CeladonCity_Condominiums_3F_EventScript_DevelopmentRoomSign_Text, MSGBOX_SIGN
    end

TH14_CeladonCity_Condominiums_3F_EventScript_DevelopmentRoomSign_Text::
    .string "GAME FREAK Development Room$"

TH14_CeladonCity_Condominiums_3F_EventScript_Computer1::
    msgbox TH14_CeladonCity_Condominiums_3F_EventScript_Computer1_Text, MSGBOX_SIGN
    end

TH14_CeladonCity_Condominiums_3F_EventScript_Computer1_Text::
    .string "It's the game program! Messing with\nit could bug out the game!$"

TH14_CeladonCity_Condominiums_3F_EventScript_Computer2::
    msgbox TH14_CeladonCity_Condominiums_3F_EventScript_Computer2_Text, MSGBOX_SIGN
    end

TH14_CeladonCity_Condominiums_3F_EventScript_Computer2_Text::
    .string "Someone's playing a game instead of\nworking!$"

TH14_CeladonCity_Condominiums_3F_EventScript_Computer3::
    msgbox TH14_CeladonCity_Condominiums_3F_EventScript_Computer3_Text, MSGBOX_SIGN
    end

TH14_CeladonCity_Condominiums_3F_EventScript_Computer3_Text::
    .string "It's the script!\nBetter not look at the ending!$"

TH14_CeladonCity_Condominiums_Roof_EventScript_Sign::
    msgbox TH14_CeladonCity_Condominiums_Roof_EventScript_Sign_Text, MSGBOX_SIGN
    end

TH14_CeladonCity_Condominiums_Roof_EventScript_Sign_Text::
    .string "I KNOW EVERYTHING!$"

TH14_CeladonCity_Condominiums_RoofRoom_EventScript_BlackBelt::
    msgbox TH14_CeladonCity_Condominiums_RoofRoom_EventScript_BlackBelt_Text, MSGBOX_NPC
    end

TH14_CeladonCity_Condominiums_RoofRoom_EventScript_BlackBelt_Text::
    .string "An EEVEE is resting over there.\nIt would make a fine partner.\pGive it time to grow before you\ndecide how it should evolve.$"

TH14_CeladonCity_Condominiums_RoofRoom_EventScript_Blackboard::
    msgbox TH14_CeladonCity_Condominiums_RoofRoom_EventScript_Blackboard_Text, MSGBOX_SIGN
    end

TH14_CeladonCity_Condominiums_RoofRoom_EventScript_Blackboard_Text::
    .string "TRAINER NOTES\pTry different moves in battle.\nThe SUMMARY can help you relearn.\pA partner with four moves can\nreplace one when learning another.$"

TH14_CeladonCity_Condominiums_RoofRoom_EventScript_TMsPamphlet::
    msgbox TH14_CeladonCity_Condominiums_RoofRoom_EventScript_TMsPamphlet_Text, MSGBOX_SIGN
    end

TH14_CeladonCity_Condominiums_RoofRoom_EventScript_TMsPamphlet_Text::
    .string "A pamphlet about TMs.\pA TM can teach a compatible move.\nYou can use it more than once!$"

TH14_CeladonCoinPickup_13::
lockall
    setvar VAR_0x8009, 0
    goto_if_set FLAG_TH14_PICKUP_13, TH14_EcoEnd
    setvar VAR_0x8008, 3
    setvar VAR_0x8004, 3
    setvar VAR_0x8005, 3
    special TH14_ScriptEconomy
    goto TH14_EcoResult
    end

TH14_CeladonCoinPickup_14::
lockall
    setvar VAR_0x8009, 0
    goto_if_set FLAG_TH14_PICKUP_14, TH14_EcoEnd
    setvar VAR_0x8008, 3
    setvar VAR_0x8004, 3
    setvar VAR_0x8005, 4
    special TH14_ScriptEconomy
    goto TH14_EcoResult
    end

TH14_CeladonCoinPickup_15::
lockall
    setvar VAR_0x8009, 0
    goto_if_set FLAG_TH14_PICKUP_15, TH14_EcoEnd
    setvar VAR_0x8008, 3
    setvar VAR_0x8004, 3
    setvar VAR_0x8005, 5
    special TH14_ScriptEconomy
    goto TH14_EcoResult
    end

TH14_CeladonCoinPickup_16::
lockall
    setvar VAR_0x8009, 0
    goto_if_set FLAG_TH14_PICKUP_16, TH14_EcoEnd
    setvar VAR_0x8008, 3
    setvar VAR_0x8004, 3
    setvar VAR_0x8005, 6
    special TH14_ScriptEconomy
    goto TH14_EcoResult
    end

TH14_CeladonCoinPickup_17::
lockall
    setvar VAR_0x8009, 0
    goto_if_set FLAG_TH14_PICKUP_17, TH14_EcoEnd
    setvar VAR_0x8008, 3
    setvar VAR_0x8004, 3
    setvar VAR_0x8005, 7
    special TH14_ScriptEconomy
    goto TH14_EcoResult
    end

TH14_CeladonCoinPickup_18::
lockall
    setvar VAR_0x8009, 0
    goto_if_set FLAG_TH14_PICKUP_18, TH14_EcoEnd
    setvar VAR_0x8008, 3
    setvar VAR_0x8004, 3
    setvar VAR_0x8005, 8
    special TH14_ScriptEconomy
    goto TH14_EcoResult
    end

TH14_CeladonCoinPickup_19::
lockall
    setvar VAR_0x8009, 0
    goto_if_set FLAG_TH14_PICKUP_19, TH14_EcoEnd
    setvar VAR_0x8008, 3
    setvar VAR_0x8004, 3
    setvar VAR_0x8005, 9
    special TH14_ScriptEconomy
    goto TH14_EcoResult
    end

TH14_CeladonCoinPickup_20::
lockall
    setvar VAR_0x8009, 0
    goto_if_set FLAG_TH14_PICKUP_20, TH14_EcoEnd
    setvar VAR_0x8008, 3
    setvar VAR_0x8004, 3
    setvar VAR_0x8005, 10
    special TH14_ScriptEconomy
    goto TH14_EcoResult
    end

TH14_CeladonCoinPickup_21::
lockall
    setvar VAR_0x8009, 0
    goto_if_set FLAG_TH14_PICKUP_21, TH14_EcoEnd
    setvar VAR_0x8008, 3
    setvar VAR_0x8004, 3
    setvar VAR_0x8005, 11
    special TH14_ScriptEconomy
    goto TH14_EcoResult
    end

TH14_CeladonCoinPickup_22::
lockall
    setvar VAR_0x8009, 0
    goto_if_set FLAG_TH14_PICKUP_22, TH14_EcoEnd
    setvar VAR_0x8008, 3
    setvar VAR_0x8004, 3
    setvar VAR_0x8005, 12
    special TH14_ScriptEconomy
    goto TH14_EcoResult
    end

TH14_CeladonCoinPickup_23::
lockall
    setvar VAR_0x8009, 0
    goto_if_set FLAG_TH14_PICKUP_23, TH14_EcoEnd
    setvar VAR_0x8008, 3
    setvar VAR_0x8004, 3
    setvar VAR_0x8005, 13
    special TH14_ScriptEconomy
    goto TH14_EcoResult
    end

TH14_CeladonCoinPickup_24::
lockall
    setvar VAR_0x8009, 0
    goto_if_set FLAG_TH14_PICKUP_24, TH14_EcoEnd
    setvar VAR_0x8008, 3
    setvar VAR_0x8004, 3
    setvar VAR_0x8005, 14
    special TH14_ScriptEconomy
    goto TH14_EcoResult
    end

TH14_CeladonCity_GameCorner_EventScript_InfoClerk::
    msgbox TH14_CeladonCity_GameCorner_EventScript_InfoClerk_Text, MSGBOX_NPC
    end

TH14_CeladonCity_GameCorner_EventScript_InfoClerk_Text::
    .string "Welcome!\pYou can exchange your COINS for\nfabulous prizes next door.$"

TH14_CeladonCity_GameCorner_EventScript_CoinsClerk::
lockall
    faceplayer
    setvar VAR_0x8009, 0
    checkitem ITEM_COIN_CASE, 1
    goto_if_eq VAR_RESULT, FALSE, TH14_EcoNoCase
    showcoinsbox 0, 0
    showmoneybox 0, 5
    setvar VAR_0x8009, 3
    msgbox TH14_EcoChoose2
    dynmultichoice 12, 0, FALSE, 4, 0, DYN_MULTICHOICE_CB_NONE, TH14_EcoMenu_2_0_0, TH14_EcoMenu_2_0_1, TH14_EcoExitText
    goto_if_ge VAR_RESULT, 2, TH14_EcoEnd
    copyvar VAR_0x8005, VAR_RESULT
    msgbox TH14_EcoConfirm, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, TH14_EcoEnd
    setvar VAR_0x8008, 2
    setvar VAR_0x8004, 2
    special TH14_ScriptEconomy
    goto TH14_EcoResult
    end

TH14_CeladonCity_GameCorner_EventScript_BaldingMan::
    msgbox TH14_CeladonCity_GameCorner_EventScript_BaldingMan_Text, MSGBOX_NPC
    end

TH14_CeladonCity_GameCorner_EventScript_BaldingMan_Text::
    .string "Keep this quiet.\pIt's rumored that this place is run\nby TEAM ROCKET.$"

TH14_CeladonCity_GameCorner_EventScript_Woman1::
    msgbox TH14_CeladonCity_GameCorner_EventScript_Woman1_Text, MSGBOX_NPC
    end

TH14_CeladonCity_GameCorner_EventScript_Woman1_Text::
    .string "I think these machines have\ndifferent odds.$"

TH14_CeladonCity_GameCorner_EventScript_Fisher::
lockall
    faceplayer
    setvar VAR_0x8009, 0
    goto_if_set FLAG_TH14_GAMBLER_COINS_10, TH14_CeladonCity_GameCorner_EventScript_Fisher_Repeat
    msgbox TH14_CeladonCity_GameCorner_EventScript_Fisher_Offer
    setvar VAR_0x8008, 3
    setvar VAR_0x8004, 3
    setvar VAR_0x8005, 0
    special TH14_ScriptEconomy
    goto TH14_EcoResult
    end

TH14_CeladonCity_GameCorner_EventScript_GymGuy::
    msgbox TH14_CeladonCity_GameCorner_EventScript_GymGuy_Text, MSGBOX_NPC
    end

TH14_CeladonCity_GameCorner_EventScript_GymGuy_Text::
    .string "Hey!\pYou have better things to do,\nchamp in the making!\pCELADON GYM's LEADER is ERIKA.\pShe is a user of GRASS-type\nPOKéMON, and at one with nature.\pShe might appear docile because of\nher flower arranging…\pBut she's not one to be taken\nlightly!$"

TH14_CeladonCity_GameCorner_EventScript_Woman2::
    msgbox TH14_CeladonCity_GameCorner_EventScript_Woman2_Text, MSGBOX_NPC
    end

TH14_CeladonCity_GameCorner_EventScript_Woman2_Text::
    .string "These slot games…\nWin or lose, it's only by luck.$"

TH14_CeladonCity_GameCorner_EventScript_OldMan::
    msgbox TH14_CeladonCity_GameCorner_EventScript_OldMan_Text, MSGBOX_NPC
    end

TH14_CeladonCity_GameCorner_EventScript_OldMan_Text::
    .string "Games are scary!\nIt's so easy to get hooked!$"

TH14_CeladonCity_GameCorner_EventScript_Scientist::
lockall
    faceplayer
    setvar VAR_0x8009, 0
    goto_if_set FLAG_TH14_GAMBLER_COINS_20_A, TH14_CeladonCity_GameCorner_EventScript_Scientist_Repeat
    msgbox TH14_CeladonCity_GameCorner_EventScript_Scientist_Offer
    setvar VAR_0x8008, 3
    setvar VAR_0x8004, 3
    setvar VAR_0x8005, 1
    special TH14_ScriptEconomy
    goto TH14_EcoResult
    end

TH14_CeladonCity_GameCorner_EventScript_Gentleman::
lockall
    faceplayer
    setvar VAR_0x8009, 0
    goto_if_set FLAG_TH14_GAMBLER_COINS_20_B, TH14_CeladonCity_GameCorner_EventScript_Gentleman_Repeat
    msgbox TH14_CeladonCity_GameCorner_EventScript_Gentleman_Offer
    setvar VAR_0x8008, 3
    setvar VAR_0x8004, 3
    setvar VAR_0x8005, 2
    special TH14_ScriptEconomy
    goto TH14_EcoResult
    end

TH14_CeladonCity_GameCorner_EventScript_RocketGrunt::
    msgbox TH14_CeladonCity_GameCorner_EventScript_RocketGrunt_Text, MSGBOX_NPC
    end

TH14_CeladonCity_GameCorner_EventScript_RocketGrunt_Text::
    .string "Please wait a moment.\nI will be with you shortly.$"

TH14_CeladonCity_GameCorner_EventScript_SlotMachine0::
lockall
    setvar VAR_0x8009, 0
    checkitem ITEM_COIN_CASE, 1
    goto_if_eq VAR_RESULT, FALSE, TH14_EcoNoCase
    msgbox TH14_EcoPlaySlots, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, TH14_EcoEnd
    setfieldeffectargument 0, LOCALID_PLAYER
    setfieldeffectargument 1, MAP_NUM(MAP_TH14_CELADON_CITY_GAME_CORNER)
    setfieldeffectargument 2, MAP_GROUP(MAP_TH14_CELADON_CITY_GAME_CORNER)
    dofieldeffect FLDEFF_SMILEY_FACE_ICON
    waitfieldeffect FLDEFF_SMILEY_FACE_ICON
    specialvar VAR_RESULT, GetRandomSlotMachineId
    playslotmachine VAR_RESULT
    releaseall
    end

TH14_CeladonCity_GameCorner_EventScript_SlotMachine1::
lockall
    setvar VAR_0x8009, 0
    checkitem ITEM_COIN_CASE, 1
    goto_if_eq VAR_RESULT, FALSE, TH14_EcoNoCase
    msgbox TH14_EcoPlaySlots, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, TH14_EcoEnd
    setfieldeffectargument 0, LOCALID_PLAYER
    setfieldeffectargument 1, MAP_NUM(MAP_TH14_CELADON_CITY_GAME_CORNER)
    setfieldeffectargument 2, MAP_GROUP(MAP_TH14_CELADON_CITY_GAME_CORNER)
    dofieldeffect FLDEFF_SMILEY_FACE_ICON
    waitfieldeffect FLDEFF_SMILEY_FACE_ICON
    specialvar VAR_RESULT, GetRandomSlotMachineId
    playslotmachine VAR_RESULT
    releaseall
    end

TH14_CeladonCity_GameCorner_EventScript_SlotMachine2::
lockall
    setvar VAR_0x8009, 0
    checkitem ITEM_COIN_CASE, 1
    goto_if_eq VAR_RESULT, FALSE, TH14_EcoNoCase
    msgbox TH14_EcoPlaySlots, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, TH14_EcoEnd
    setfieldeffectargument 0, LOCALID_PLAYER
    setfieldeffectargument 1, MAP_NUM(MAP_TH14_CELADON_CITY_GAME_CORNER)
    setfieldeffectargument 2, MAP_GROUP(MAP_TH14_CELADON_CITY_GAME_CORNER)
    dofieldeffect FLDEFF_SMILEY_FACE_ICON
    waitfieldeffect FLDEFF_SMILEY_FACE_ICON
    specialvar VAR_RESULT, GetRandomSlotMachineId
    playslotmachine VAR_RESULT
    releaseall
    end

TH14_CeladonCity_GameCorner_EventScript_SlotMachine3::
lockall
    setvar VAR_0x8009, 0
    checkitem ITEM_COIN_CASE, 1
    goto_if_eq VAR_RESULT, FALSE, TH14_EcoNoCase
    msgbox TH14_EcoPlaySlots, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, TH14_EcoEnd
    setfieldeffectargument 0, LOCALID_PLAYER
    setfieldeffectargument 1, MAP_NUM(MAP_TH14_CELADON_CITY_GAME_CORNER)
    setfieldeffectargument 2, MAP_GROUP(MAP_TH14_CELADON_CITY_GAME_CORNER)
    dofieldeffect FLDEFF_SMILEY_FACE_ICON
    waitfieldeffect FLDEFF_SMILEY_FACE_ICON
    specialvar VAR_RESULT, GetRandomSlotMachineId
    playslotmachine VAR_RESULT
    releaseall
    end

TH14_CeladonCity_GameCorner_EventScript_UnusableSlotMachine1::
msgbox TH14_EcoUnusable1, MSGBOX_SIGN
    end

TH14_CeladonCity_GameCorner_EventScript_SlotMachine5::
lockall
    setvar VAR_0x8009, 0
    checkitem ITEM_COIN_CASE, 1
    goto_if_eq VAR_RESULT, FALSE, TH14_EcoNoCase
    msgbox TH14_EcoPlaySlots, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, TH14_EcoEnd
    setfieldeffectargument 0, LOCALID_PLAYER
    setfieldeffectargument 1, MAP_NUM(MAP_TH14_CELADON_CITY_GAME_CORNER)
    setfieldeffectargument 2, MAP_GROUP(MAP_TH14_CELADON_CITY_GAME_CORNER)
    dofieldeffect FLDEFF_SMILEY_FACE_ICON
    waitfieldeffect FLDEFF_SMILEY_FACE_ICON
    specialvar VAR_RESULT, GetRandomSlotMachineId
    playslotmachine VAR_RESULT
    releaseall
    end

TH14_CeladonCity_GameCorner_EventScript_SlotMachine6::
lockall
    setvar VAR_0x8009, 0
    checkitem ITEM_COIN_CASE, 1
    goto_if_eq VAR_RESULT, FALSE, TH14_EcoNoCase
    msgbox TH14_EcoPlaySlots, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, TH14_EcoEnd
    setfieldeffectargument 0, LOCALID_PLAYER
    setfieldeffectargument 1, MAP_NUM(MAP_TH14_CELADON_CITY_GAME_CORNER)
    setfieldeffectargument 2, MAP_GROUP(MAP_TH14_CELADON_CITY_GAME_CORNER)
    dofieldeffect FLDEFF_SMILEY_FACE_ICON
    waitfieldeffect FLDEFF_SMILEY_FACE_ICON
    specialvar VAR_RESULT, GetRandomSlotMachineId
    playslotmachine VAR_RESULT
    releaseall
    end

TH14_CeladonCity_GameCorner_EventScript_SlotMachine7::
lockall
    setvar VAR_0x8009, 0
    checkitem ITEM_COIN_CASE, 1
    goto_if_eq VAR_RESULT, FALSE, TH14_EcoNoCase
    msgbox TH14_EcoPlaySlots, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, TH14_EcoEnd
    setfieldeffectargument 0, LOCALID_PLAYER
    setfieldeffectargument 1, MAP_NUM(MAP_TH14_CELADON_CITY_GAME_CORNER)
    setfieldeffectargument 2, MAP_GROUP(MAP_TH14_CELADON_CITY_GAME_CORNER)
    dofieldeffect FLDEFF_SMILEY_FACE_ICON
    waitfieldeffect FLDEFF_SMILEY_FACE_ICON
    specialvar VAR_RESULT, GetRandomSlotMachineId
    playslotmachine VAR_RESULT
    releaseall
    end

TH14_CeladonCity_GameCorner_EventScript_SlotMachine8::
lockall
    setvar VAR_0x8009, 0
    checkitem ITEM_COIN_CASE, 1
    goto_if_eq VAR_RESULT, FALSE, TH14_EcoNoCase
    msgbox TH14_EcoPlaySlots, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, TH14_EcoEnd
    setfieldeffectargument 0, LOCALID_PLAYER
    setfieldeffectargument 1, MAP_NUM(MAP_TH14_CELADON_CITY_GAME_CORNER)
    setfieldeffectargument 2, MAP_GROUP(MAP_TH14_CELADON_CITY_GAME_CORNER)
    dofieldeffect FLDEFF_SMILEY_FACE_ICON
    waitfieldeffect FLDEFF_SMILEY_FACE_ICON
    specialvar VAR_RESULT, GetRandomSlotMachineId
    playslotmachine VAR_RESULT
    releaseall
    end

TH14_CeladonCity_GameCorner_EventScript_SlotMachine9::
lockall
    setvar VAR_0x8009, 0
    checkitem ITEM_COIN_CASE, 1
    goto_if_eq VAR_RESULT, FALSE, TH14_EcoNoCase
    msgbox TH14_EcoPlaySlots, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, TH14_EcoEnd
    setfieldeffectargument 0, LOCALID_PLAYER
    setfieldeffectargument 1, MAP_NUM(MAP_TH14_CELADON_CITY_GAME_CORNER)
    setfieldeffectargument 2, MAP_GROUP(MAP_TH14_CELADON_CITY_GAME_CORNER)
    dofieldeffect FLDEFF_SMILEY_FACE_ICON
    waitfieldeffect FLDEFF_SMILEY_FACE_ICON
    specialvar VAR_RESULT, GetRandomSlotMachineId
    playslotmachine VAR_RESULT
    releaseall
    end

TH14_CeladonCity_GameCorner_EventScript_SlotMachine10::
lockall
    setvar VAR_0x8009, 0
    checkitem ITEM_COIN_CASE, 1
    goto_if_eq VAR_RESULT, FALSE, TH14_EcoNoCase
    msgbox TH14_EcoPlaySlots, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, TH14_EcoEnd
    setfieldeffectargument 0, LOCALID_PLAYER
    setfieldeffectargument 1, MAP_NUM(MAP_TH14_CELADON_CITY_GAME_CORNER)
    setfieldeffectargument 2, MAP_GROUP(MAP_TH14_CELADON_CITY_GAME_CORNER)
    dofieldeffect FLDEFF_SMILEY_FACE_ICON
    waitfieldeffect FLDEFF_SMILEY_FACE_ICON
    specialvar VAR_RESULT, GetRandomSlotMachineId
    playslotmachine VAR_RESULT
    releaseall
    end

TH14_CeladonCity_GameCorner_EventScript_SlotMachine11::
lockall
    setvar VAR_0x8009, 0
    checkitem ITEM_COIN_CASE, 1
    goto_if_eq VAR_RESULT, FALSE, TH14_EcoNoCase
    msgbox TH14_EcoPlaySlots, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, TH14_EcoEnd
    setfieldeffectargument 0, LOCALID_PLAYER
    setfieldeffectargument 1, MAP_NUM(MAP_TH14_CELADON_CITY_GAME_CORNER)
    setfieldeffectargument 2, MAP_GROUP(MAP_TH14_CELADON_CITY_GAME_CORNER)
    dofieldeffect FLDEFF_SMILEY_FACE_ICON
    waitfieldeffect FLDEFF_SMILEY_FACE_ICON
    specialvar VAR_RESULT, GetRandomSlotMachineId
    playslotmachine VAR_RESULT
    releaseall
    end

TH14_CeladonCity_GameCorner_EventScript_SlotMachine12::
lockall
    setvar VAR_0x8009, 0
    checkitem ITEM_COIN_CASE, 1
    goto_if_eq VAR_RESULT, FALSE, TH14_EcoNoCase
    msgbox TH14_EcoPlaySlots, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, TH14_EcoEnd
    setfieldeffectargument 0, LOCALID_PLAYER
    setfieldeffectargument 1, MAP_NUM(MAP_TH14_CELADON_CITY_GAME_CORNER)
    setfieldeffectargument 2, MAP_GROUP(MAP_TH14_CELADON_CITY_GAME_CORNER)
    dofieldeffect FLDEFF_SMILEY_FACE_ICON
    waitfieldeffect FLDEFF_SMILEY_FACE_ICON
    specialvar VAR_RESULT, GetRandomSlotMachineId
    playslotmachine VAR_RESULT
    releaseall
    end

TH14_CeladonCity_GameCorner_EventScript_SlotMachine13::
lockall
    setvar VAR_0x8009, 0
    checkitem ITEM_COIN_CASE, 1
    goto_if_eq VAR_RESULT, FALSE, TH14_EcoNoCase
    msgbox TH14_EcoPlaySlots, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, TH14_EcoEnd
    setfieldeffectargument 0, LOCALID_PLAYER
    setfieldeffectargument 1, MAP_NUM(MAP_TH14_CELADON_CITY_GAME_CORNER)
    setfieldeffectargument 2, MAP_GROUP(MAP_TH14_CELADON_CITY_GAME_CORNER)
    dofieldeffect FLDEFF_SMILEY_FACE_ICON
    waitfieldeffect FLDEFF_SMILEY_FACE_ICON
    specialvar VAR_RESULT, GetRandomSlotMachineId
    playslotmachine VAR_RESULT
    releaseall
    end

TH14_CeladonCity_GameCorner_EventScript_SlotMachine14::
lockall
    setvar VAR_0x8009, 0
    checkitem ITEM_COIN_CASE, 1
    goto_if_eq VAR_RESULT, FALSE, TH14_EcoNoCase
    msgbox TH14_EcoPlaySlots, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, TH14_EcoEnd
    setfieldeffectargument 0, LOCALID_PLAYER
    setfieldeffectargument 1, MAP_NUM(MAP_TH14_CELADON_CITY_GAME_CORNER)
    setfieldeffectargument 2, MAP_GROUP(MAP_TH14_CELADON_CITY_GAME_CORNER)
    dofieldeffect FLDEFF_SMILEY_FACE_ICON
    waitfieldeffect FLDEFF_SMILEY_FACE_ICON
    specialvar VAR_RESULT, GetRandomSlotMachineId
    playslotmachine VAR_RESULT
    releaseall
    end

TH14_CeladonCity_GameCorner_EventScript_UnusableSlotMachine2::
msgbox TH14_EcoUnusable2, MSGBOX_SIGN
    end

TH14_CeladonCity_GameCorner_EventScript_SlotMachine16::
lockall
    setvar VAR_0x8009, 0
    checkitem ITEM_COIN_CASE, 1
    goto_if_eq VAR_RESULT, FALSE, TH14_EcoNoCase
    msgbox TH14_EcoPlaySlots, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, TH14_EcoEnd
    setfieldeffectargument 0, LOCALID_PLAYER
    setfieldeffectargument 1, MAP_NUM(MAP_TH14_CELADON_CITY_GAME_CORNER)
    setfieldeffectargument 2, MAP_GROUP(MAP_TH14_CELADON_CITY_GAME_CORNER)
    dofieldeffect FLDEFF_SMILEY_FACE_ICON
    waitfieldeffect FLDEFF_SMILEY_FACE_ICON
    specialvar VAR_RESULT, GetRandomSlotMachineId
    playslotmachine VAR_RESULT
    releaseall
    end

TH14_CeladonCity_GameCorner_EventScript_SlotMachine17::
lockall
    setvar VAR_0x8009, 0
    checkitem ITEM_COIN_CASE, 1
    goto_if_eq VAR_RESULT, FALSE, TH14_EcoNoCase
    msgbox TH14_EcoPlaySlots, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, TH14_EcoEnd
    setfieldeffectargument 0, LOCALID_PLAYER
    setfieldeffectargument 1, MAP_NUM(MAP_TH14_CELADON_CITY_GAME_CORNER)
    setfieldeffectargument 2, MAP_GROUP(MAP_TH14_CELADON_CITY_GAME_CORNER)
    dofieldeffect FLDEFF_SMILEY_FACE_ICON
    waitfieldeffect FLDEFF_SMILEY_FACE_ICON
    specialvar VAR_RESULT, GetRandomSlotMachineId
    playslotmachine VAR_RESULT
    releaseall
    end

TH14_CeladonCity_GameCorner_EventScript_UnusableSlotMachine3::
msgbox TH14_EcoUnusable3, MSGBOX_SIGN
    end

TH14_CeladonCity_GameCorner_EventScript_SlotMachine19::
lockall
    setvar VAR_0x8009, 0
    checkitem ITEM_COIN_CASE, 1
    goto_if_eq VAR_RESULT, FALSE, TH14_EcoNoCase
    msgbox TH14_EcoPlaySlots, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, TH14_EcoEnd
    setfieldeffectargument 0, LOCALID_PLAYER
    setfieldeffectargument 1, MAP_NUM(MAP_TH14_CELADON_CITY_GAME_CORNER)
    setfieldeffectargument 2, MAP_GROUP(MAP_TH14_CELADON_CITY_GAME_CORNER)
    dofieldeffect FLDEFF_SMILEY_FACE_ICON
    waitfieldeffect FLDEFF_SMILEY_FACE_ICON
    specialvar VAR_RESULT, GetRandomSlotMachineId
    playslotmachine VAR_RESULT
    releaseall
    end

TH14_CeladonCity_GameCorner_EventScript_SlotMachine20::
lockall
    setvar VAR_0x8009, 0
    checkitem ITEM_COIN_CASE, 1
    goto_if_eq VAR_RESULT, FALSE, TH14_EcoNoCase
    msgbox TH14_EcoPlaySlots, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, TH14_EcoEnd
    setfieldeffectargument 0, LOCALID_PLAYER
    setfieldeffectargument 1, MAP_NUM(MAP_TH14_CELADON_CITY_GAME_CORNER)
    setfieldeffectargument 2, MAP_GROUP(MAP_TH14_CELADON_CITY_GAME_CORNER)
    dofieldeffect FLDEFF_SMILEY_FACE_ICON
    waitfieldeffect FLDEFF_SMILEY_FACE_ICON
    specialvar VAR_RESULT, GetRandomSlotMachineId
    playslotmachine VAR_RESULT
    releaseall
    end

TH14_CeladonCity_GameCorner_EventScript_SlotMachine21::
lockall
    setvar VAR_0x8009, 0
    checkitem ITEM_COIN_CASE, 1
    goto_if_eq VAR_RESULT, FALSE, TH14_EcoNoCase
    msgbox TH14_EcoPlaySlots, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, TH14_EcoEnd
    setfieldeffectargument 0, LOCALID_PLAYER
    setfieldeffectargument 1, MAP_NUM(MAP_TH14_CELADON_CITY_GAME_CORNER)
    setfieldeffectargument 2, MAP_GROUP(MAP_TH14_CELADON_CITY_GAME_CORNER)
    dofieldeffect FLDEFF_SMILEY_FACE_ICON
    waitfieldeffect FLDEFF_SMILEY_FACE_ICON
    specialvar VAR_RESULT, GetRandomSlotMachineId
    playslotmachine VAR_RESULT
    releaseall
    end

TH14_CeladonCity_GameCorner_EventScript_Poster::
    msgbox TH14_CeladonCity_GameCorner_EventScript_Poster_Text, MSGBOX_NPC
    end

TH14_CeladonCity_GameCorner_EventScript_Poster_Text::
    .string "Please wait a moment.\nI will be with you shortly.$"

TH14_CeladonCity_GameCorner_EventScript_PhotoPrinter::
    msgbox TH14_CeladonCity_GameCorner_EventScript_PhotoPrinter_Text, MSGBOX_SIGN
    end

TH14_CeladonCity_GameCorner_EventScript_PhotoPrinter_Text::
    .string "A display of souvenir pictures.\nSome have faded with age.$"

TH14_CeladonCity_GameCorner_PrizeRoom_EventScript_BaldingMan::
    msgbox TH14_CeladonCity_GameCorner_PrizeRoom_EventScript_BaldingMan_Text, MSGBOX_NPC
    end

TH14_CeladonCity_GameCorner_PrizeRoom_EventScript_BaldingMan_Text::
    .string "I sure do fancy that PORYGON!\nBut, it's hard to win at slots!$"

TH14_CeladonCity_GameCorner_PrizeRoom_EventScript_OldMan::
    msgbox TH14_CeladonCity_GameCorner_PrizeRoom_EventScript_OldMan_Text, MSGBOX_NPC
    end

TH14_CeladonCity_GameCorner_PrizeRoom_EventScript_OldMan_Text::
    .string "Gahaha! I raked it in today!\nIf only every day were like this…$"

TH14_CeladonCity_GameCorner_PrizeRoom_EventScript_PrizeClerkMons::
lockall
    faceplayer
    setvar VAR_0x8009, 0
    checkitem ITEM_COIN_CASE, 1
    goto_if_eq VAR_RESULT, FALSE, TH14_EcoNoCase
    showcoinsbox 0, 0
    setvar VAR_0x8009, 1
    msgbox TH14_EcoChoose1
    dynmultichoice 12, 0, FALSE, 4, 0, DYN_MULTICHOICE_CB_NONE, TH14_EcoMenu_1_0_0, TH14_EcoMenu_1_0_1, TH14_EcoMenu_1_0_2, TH14_EcoMenu_1_0_3, TH14_EcoMenu_1_0_4, TH14_EcoExitText
    goto_if_ge VAR_RESULT, 5, TH14_EcoEnd
    copyvar VAR_0x8005, VAR_RESULT
    msgbox TH14_EcoConfirm, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, TH14_EcoEnd
    setvar VAR_0x8008, 1
    setvar VAR_0x8004, 1
    special TH14_ScriptEconomy
    goto TH14_EcoResult
    end

TH14_CeladonCity_GameCorner_PrizeRoom_EventScript_PrizeClerkTMs::
lockall
    faceplayer
    setvar VAR_0x8009, 0
    checkitem ITEM_COIN_CASE, 1
    goto_if_eq VAR_RESULT, FALSE, TH14_EcoNoCase
    showcoinsbox 0, 0
    setvar VAR_0x8009, 1
    msgbox TH14_EcoChoose0
    dynmultichoice 12, 0, FALSE, 4, 0, DYN_MULTICHOICE_CB_NONE, TH14_EcoMenu_0_0_0, TH14_EcoMenu_0_0_1, TH14_EcoMenu_0_0_2, TH14_EcoMenu_0_0_3, TH14_EcoMenu_0_0_4, TH14_EcoExitText
    goto_if_ge VAR_RESULT, 5, TH14_EcoEnd
    copyvar VAR_0x8005, VAR_RESULT
    msgbox TH14_EcoConfirm, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, TH14_EcoEnd
    setvar VAR_0x8008, 0
    setvar VAR_0x8004, 0
    special TH14_ScriptEconomy
    goto TH14_EcoResult
    end

TH14_CeladonCity_GameCorner_PrizeRoom_EventScript_PrizeClerkItems::
lockall
    faceplayer
    setvar VAR_0x8009, 0
    checkitem ITEM_COIN_CASE, 1
    goto_if_eq VAR_RESULT, FALSE, TH14_EcoNoCase
    showcoinsbox 0, 0
    setvar VAR_0x8009, 1
    msgbox TH14_EcoChoose0
    dynmultichoice 12, 0, FALSE, 4, 0, DYN_MULTICHOICE_CB_NONE, TH14_EcoMenu_0_5_0, TH14_EcoMenu_0_5_1, TH14_EcoMenu_0_5_2, TH14_EcoMenu_0_5_3, TH14_EcoMenu_0_5_4, TH14_EcoExitText
    goto_if_ge VAR_RESULT, 5, TH14_EcoEnd
    copyvar VAR_0x8005, VAR_RESULT
    addvar VAR_0x8005, 5
    msgbox TH14_EcoConfirm, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, TH14_EcoEnd
    setvar VAR_0x8008, 0
    setvar VAR_0x8004, 0
    special TH14_ScriptEconomy
    goto TH14_EcoResult
    end

TH14_CeladonCity_Restaurant_EventScript_Chef::
    msgbox TH14_CeladonCity_Restaurant_EventScript_Chef_Text, MSGBOX_NPC
    end

TH14_CeladonCity_Restaurant_EventScript_Chef_Text::
    .string "Hi!\pSorry, but we're taking a break\nright now.$"

TH14_CeladonCity_Restaurant_EventScript_Woman::
    msgbox TH14_CeladonCity_Restaurant_EventScript_Woman_Text, MSGBOX_NPC
    end

TH14_CeladonCity_Restaurant_EventScript_Woman_Text::
    .string "My POKéMON are weak, so I often\nhave to go to the DRUGSTORE.$"

TH14_CeladonCity_Restaurant_EventScript_FatMan::
    msgbox TH14_CeladonCity_Restaurant_EventScript_FatMan_Text, MSGBOX_NPC
    end

TH14_CeladonCity_Restaurant_EventScript_FatMan_Text::
    .string "Munch…\pThe man at that table lost it all\nat the slots.$"

TH14_CeladonCity_Restaurant_EventScript_CoinCaseMan::
lockall
    faceplayer
    msgbox TH14_EcoCaseIntro
    setvar VAR_0x8004, ITEM_COIN_CASE
    setvar VAR_0x8005, FLAG_TH14_COIN_CASE
    special TH14_ScriptGiveUniqueItem
    goto_if_eq VAR_RESULT, 0, TH14_EcoCaseFull
    goto_if_eq VAR_RESULT, 2, TH14_EcoCaseOwned
    playfanfare MUS_OBTAIN_ITEM
    msgbox TH14_EcoCaseReceived
    waitfanfare
    releaseall
    end

TH14_CeladonCity_Restaurant_EventScript_WorkerM::
    msgbox TH14_CeladonCity_Restaurant_EventScript_WorkerM_Text, MSGBOX_NPC
    end

TH14_CeladonCity_Restaurant_EventScript_WorkerM_Text::
    .string "Psst! There's a basement under the\nGAME CORNER, I hear.$"

TH14_CeladonCity_Hotel_EventScript_Receptionist::
    msgbox TH14_CeladonCity_Hotel_EventScript_Receptionist_Text, MSGBOX_NPC
    end

TH14_CeladonCity_Hotel_EventScript_Receptionist_Text::
    .string "POKéMON?\nNo, this is a hotel for people.\pWe're full up, unfortunately.$"

TH14_CeladonCity_Hotel_EventScript_Beauty::
    msgbox TH14_CeladonCity_Hotel_EventScript_Beauty_Text, MSGBOX_NPC
    end

TH14_CeladonCity_Hotel_EventScript_Beauty_Text::
    .string "I'm on vacation with my brother and\nboyfriend.\pCELADON is such a pretty city!$"

TH14_CeladonCity_Hotel_EventScript_BeautyBoyfriend::
    msgbox TH14_CeladonCity_Hotel_EventScript_BeautyBoyfriend_Text, MSGBOX_NPC
    end

TH14_CeladonCity_Hotel_EventScript_BeautyBoyfriend_Text::
    .string "Why?\nWhy did she bring her brother?$"

TH14_CeladonCity_Hotel_EventScript_BeautyBrother::
    msgbox TH14_CeladonCity_Hotel_EventScript_BeautyBrother_Text, MSGBOX_NPC
    end

TH14_CeladonCity_Hotel_EventScript_BeautyBrother_Text::
    .string "Yippee! I'm on vacation!\nMy sis brought me along! Awesome!$"

TH14_CeladonCity_House1_EventScript_RocketChief::
    msgbox TH14_CeladonCity_House1_EventScript_RocketChief_Text, MSGBOX_NPC
    end

TH14_CeladonCity_House1_EventScript_RocketChief_Text::
    .string "Hehehe!\pThe slots just reel in the dough,\nbig-time!$"

TH14_CeladonCity_House1_EventScript_Rocket1::
    msgbox TH14_CeladonCity_House1_EventScript_Rocket1_Text, MSGBOX_NPC
    end

TH14_CeladonCity_House1_EventScript_Rocket1_Text::
    .string "CHIEF! The latest shipment\nrecords are ready for you.$"

TH14_CeladonCity_House1_EventScript_Rocket2::
    msgbox TH14_CeladonCity_House1_EventScript_Rocket2_Text, MSGBOX_NPC
    end

TH14_CeladonCity_House1_EventScript_Rocket2_Text::
    .string "Don't touch the poster at the GAME\nCORNER!\pThere's no secret switch behind it!$"

TH14_TutorDone::
    release
    end
TH14_CeladonEther::
    finditem ITEM_ETHER
    end
TH14_CeladonWestGuard::
    msgbox TH14_CeladonWestText, MSGBOX_NPC
    end
TH14_CeladonWestBoundary::
    specialvar VAR_RESULT, GetPlayerFacingDirection
    goto_if_ne VAR_RESULT, DIR_WEST, TH14_GuardEnd
    lockall
    msgbox TH14_CeladonWestText
    closemessage
    applymovement OBJ_EVENT_ID_PLAYER, TH14_GuardStepRight
    waitmovement 0
    releaseall
    end
TH14_CeladonWestText::
    .string "The western road is closed.\nPlease stay inside CELADON.$"

TH14_EeveeBall::
	lock
	faceplayer
	setvar VAR_TEMP_1, SPECIES_EEVEE
	specialvar VAR_RESULT, TH14_TryGiveEevee
	goto_if_eq VAR_RESULT, 0, TH14_Eevee_GetEeveeParty
	goto_if_eq VAR_RESULT, 1, TH14_Eevee_GetEeveePC
	goto_if_eq VAR_RESULT, 2, Common_EventScript_NoMoreRoomForPokemon
	release
	end

TH14_Eevee_GetEeveeParty::
	removeobject LOCALID_TH14_CELADONCITY_CONDOMINIUMS_ROOFROOM_2
	playfanfare MUS_LEVEL_UP
	message TH14_EeveeObtained
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, SPECIES_EEVEE
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TH14_Eevee_SetGotEevee
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto TH14_Eevee_SetGotEevee
	end

TH14_Eevee_GetEeveePC::
	removeobject LOCALID_TH14_CELADONCITY_CONDOMINIUMS_ROOFROOM_2
	playfanfare MUS_LEVEL_UP
	message TH14_EeveeObtained
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, SPECIES_EEVEE
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TH14_Eevee_TransferEeveeToPC
	call Common_EventScript_NameReceivedBoxMon
	goto TH14_Eevee_TransferEeveeToPC
	end

TH14_Eevee_TransferEeveeToPC::
	call Common_EventScript_TransferredToPC
	goto TH14_Eevee_SetGotEevee
	end

TH14_Eevee_SetGotEevee::
	setflag FLAG_TH14_EEVEE
	release
	end


TH14_EeveeObtained::
    .string "{PLAYER} obtained an EEVEE!$"

TH14_CeladonCity_DepartmentStore_Elevator_EventScript_FloorSelect::
	lockall
	specialvar VAR_0x8005, TH14_GetDeptStoreFloor
	goto_if_eq VAR_0x8005, 0, TH14_DeptElevator_Invalid
	special DrawElevatorCurrentFloorWindow
	message gText_WantWhichFloor
	waitmessage
	switch VAR_0x8005
	case 8, TH14_CeladonCity_DepartmentStore_Elevator_EventScript_FloorSelectFrom5F
	case 7, TH14_CeladonCity_DepartmentStore_Elevator_EventScript_FloorSelectFrom4F
	case 6, TH14_CeladonCity_DepartmentStore_Elevator_EventScript_FloorSelectFrom3F
	case 5, TH14_CeladonCity_DepartmentStore_Elevator_EventScript_FloorSelectFrom2F
	case 4, TH14_CeladonCity_DepartmentStore_Elevator_EventScript_FloorSelectFrom1F
	end

TH14_CeladonCity_DepartmentStore_Elevator_EventScript_FloorSelectFrom5F::
	multichoicedefault 0, 0, MULTI_DEPT_STORE_ELEVATOR, 0, FALSE
	goto TH14_CeladonCity_DepartmentStore_Elevator_EventScript_ChooseFloor
	end

TH14_CeladonCity_DepartmentStore_Elevator_EventScript_FloorSelectFrom4F::
	multichoicedefault 0, 0, MULTI_DEPT_STORE_ELEVATOR, 1, FALSE
	goto TH14_CeladonCity_DepartmentStore_Elevator_EventScript_ChooseFloor
	end

TH14_CeladonCity_DepartmentStore_Elevator_EventScript_FloorSelectFrom3F::
	multichoicedefault 0, 0, MULTI_DEPT_STORE_ELEVATOR, 2, FALSE
	goto TH14_CeladonCity_DepartmentStore_Elevator_EventScript_ChooseFloor
	end

TH14_CeladonCity_DepartmentStore_Elevator_EventScript_FloorSelectFrom2F::
	multichoicedefault 0, 0, MULTI_DEPT_STORE_ELEVATOR, 3, FALSE
	goto TH14_CeladonCity_DepartmentStore_Elevator_EventScript_ChooseFloor
	end

TH14_CeladonCity_DepartmentStore_Elevator_EventScript_FloorSelectFrom1F::
	multichoicedefault 0, 0, MULTI_DEPT_STORE_ELEVATOR, 4, FALSE
	goto TH14_CeladonCity_DepartmentStore_Elevator_EventScript_ChooseFloor
	end

TH14_CeladonCity_DepartmentStore_Elevator_EventScript_ChooseFloor::
	switch VAR_RESULT
	case 0, TH14_CeladonCity_DepartmentStore_Elevator_EventScript_To5F
	case 1, TH14_CeladonCity_DepartmentStore_Elevator_EventScript_To4F
	case 2, TH14_CeladonCity_DepartmentStore_Elevator_EventScript_To3F
	case 3, TH14_CeladonCity_DepartmentStore_Elevator_EventScript_To2F
	case 4, TH14_CeladonCity_DepartmentStore_Elevator_EventScript_To1F
	case 5, TH14_CeladonCity_DepartmentStore_Elevator_EventScript_ExitFloorSelect
	case 127, TH14_CeladonCity_DepartmentStore_Elevator_EventScript_ExitFloorSelect
	end

TH14_CeladonCity_DepartmentStore_Elevator_EventScript_To1F::
	setvar VAR_0x8006, 4
	setdynamicwarp MAP_TH14_CELADON_CITY_DEPARTMENT_STORE_1F, 255, 6, 1
	goto_if_eq VAR_0x8005, 4, TH14_CeladonCity_DepartmentStore_Elevator_EventScript_ExitFloorSelect
	call TH14_CeladonCity_DepartmentStore_Elevator_EventScript_MoveElevator
	goto TH14_CeladonCity_DepartmentStore_Elevator_EventScript_ExitFloorSelect
	end

TH14_CeladonCity_DepartmentStore_Elevator_EventScript_To2F::
	setvar VAR_0x8006, 5
	setdynamicwarp MAP_TH14_CELADON_CITY_DEPARTMENT_STORE_2F, 255, 6, 1
	goto_if_eq VAR_0x8005, 5, TH14_CeladonCity_DepartmentStore_Elevator_EventScript_ExitFloorSelect
	call TH14_CeladonCity_DepartmentStore_Elevator_EventScript_MoveElevator
	goto TH14_CeladonCity_DepartmentStore_Elevator_EventScript_ExitFloorSelect
	end

TH14_CeladonCity_DepartmentStore_Elevator_EventScript_To3F::
	setvar VAR_0x8006, 6
	setdynamicwarp MAP_TH14_CELADON_CITY_DEPARTMENT_STORE_3F, 255, 6, 1
	goto_if_eq VAR_0x8005, 6, TH14_CeladonCity_DepartmentStore_Elevator_EventScript_ExitFloorSelect
	call TH14_CeladonCity_DepartmentStore_Elevator_EventScript_MoveElevator
	goto TH14_CeladonCity_DepartmentStore_Elevator_EventScript_ExitFloorSelect
	end

TH14_CeladonCity_DepartmentStore_Elevator_EventScript_To4F::
	setvar VAR_0x8006, 7
	setdynamicwarp MAP_TH14_CELADON_CITY_DEPARTMENT_STORE_4F, 255, 6, 1
	goto_if_eq VAR_0x8005, 7, TH14_CeladonCity_DepartmentStore_Elevator_EventScript_ExitFloorSelect
	call TH14_CeladonCity_DepartmentStore_Elevator_EventScript_MoveElevator
	goto TH14_CeladonCity_DepartmentStore_Elevator_EventScript_ExitFloorSelect
	end

TH14_CeladonCity_DepartmentStore_Elevator_EventScript_To5F::
	setvar VAR_0x8006, 8
	setdynamicwarp MAP_TH14_CELADON_CITY_DEPARTMENT_STORE_5F, 255, 6, 1
	goto_if_eq VAR_0x8005, 8, TH14_CeladonCity_DepartmentStore_Elevator_EventScript_ExitFloorSelect
	call TH14_CeladonCity_DepartmentStore_Elevator_EventScript_MoveElevator
	goto TH14_CeladonCity_DepartmentStore_Elevator_EventScript_ExitFloorSelect
	end

TH14_CeladonCity_DepartmentStore_Elevator_EventScript_ExitFloorSelect::
	special CloseElevatorCurrentFloorWindow
	releaseall
	end

TH14_CeladonCity_DepartmentStore_Elevator_EventScript_MoveElevator::
	special CloseElevatorCurrentFloorWindow
	closemessage
	waitse
	special AnimateElevator
	waitstate
	return

TH14_DeptElevator_CheckReturn::
    specialvar VAR_RESULT, TH14_GetDeptStoreFloor
    goto_if_ne VAR_RESULT, 0, TH14_DeptElevator_ReturnValid
    setdynamicwarp MAP_TH14_CELADON_CITY_DEPARTMENT_STORE_1F, 255, 6, 1
TH14_DeptElevator_ReturnValid:
    return

TH14_DeptElevator_Invalid:
    releaseall
    end

@ Approved Celadon transaction UI; failed transactions remain retryable.
TH14_EcoNoStock::
msgbox TH14_EcoNoStockText
    releaseall
    end

TH14_EcoWelcome::
    .string "Welcome!\nPlease take your time.$"

TH14_EcoNoStockText::
    .string "Please come back after earning\nmore GYM BADGES.$"

TH14_EcoCaseFull::
msgbox TH14_EcoCaseFullText
    releaseall
    end

TH14_EcoCaseOwned::
msgbox TH14_EcoCaseOwnedText
    releaseall
    end

TH14_EcoCaseIntro::
    .string "I have given up on the slots.\nYou may have my COIN CASE.$"

TH14_EcoCaseReceived::
    .string "{PLAYER} received a COIN CASE!$"

TH14_EcoCaseFullText::
    .string "Please make room in your BAG.\nI will keep it for you.$"

TH14_EcoCaseOwnedText::
    .string "You already have a COIN CASE.\nKeep an eye on your COINS!$"

TH14_EcoMenu_2_0_0::
    .string "50 COINS ¥1000$"

TH14_EcoMenu_2_0_1::
    .string "500 COINS ¥10000$"

TH14_EcoMenu_1_0_0::
    .string "ABRA 180$"

TH14_EcoMenu_1_0_1::
    .string "CLEFAIRY 500$"

TH14_EcoMenu_1_0_2::
    .string "DRATINI 2800$"

TH14_EcoMenu_1_0_3::
    .string "SCYTHER 5500$"

TH14_EcoMenu_1_0_4::
    .string "PORYGON 9999$"

TH14_EcoMenu_0_0_0::
    .string "ICE BEAM 4000$"

TH14_EcoMenu_0_0_1::
    .string "IRON TAIL 3500$"

TH14_EcoMenu_0_0_2::
    .string "THUNDERBOLT 4000$"

TH14_EcoMenu_0_0_3::
    .string "SHADOW BALL 4500$"

TH14_EcoMenu_0_0_4::
    .string "FLAMETHROWER 4000$"

TH14_EcoMenu_0_5_0::
    .string "SMOKE BALL 800$"

TH14_EcoMenu_0_5_1::
    .string "MIRACLE SEED 1000$"

TH14_EcoMenu_0_5_2::
    .string "CHARCOAL 1000$"

TH14_EcoMenu_0_5_3::
    .string "MYSTIC WATER 1000$"

TH14_EcoMenu_0_5_4::
    .string "YELLOW FLUTE 1600$"

TH14_EcoMenu_4_0_0::
    .string "FRESH WATER ¥200$"

TH14_EcoMenu_4_0_1::
    .string "SODA POP ¥300$"

TH14_EcoMenu_4_0_2::
    .string "LEMONADE ¥400$"

TH14_EcoMenu_5_0_0::
    .string "FRESH WATER$"

TH14_EcoMenu_5_0_1::
    .string "SODA POP$"

TH14_EcoMenu_5_0_2::
    .string "LEMONADE$"

TH14_EcoExitText::
    .string "EXIT$"

TH14_EcoChoose0::
    .string "Which prize would you like?\nPrices are in COINS.$"

TH14_EcoChoose1::
    .string "Which POKéMON would you like?\nPrices are in COINS.$"

TH14_EcoChoose2::
    .string "Would you like to buy some COINS?$"

TH14_EcoChoose4::
    .string "Which drink would you like?$"

TH14_EcoChoose5::
    .string "I am thirsty! Would you share\na drink for one of my TMs?$"

TH14_EcoConfirm::
    .string "Is that your choice?$"

TH14_CeladonCity_GameCorner_EventScript_Fisher_Repeat::
msgbox TH14_CeladonCity_GameCorner_EventScript_Fisher_RepeatText
    goto TH14_EcoEnd
    end

TH14_CeladonCity_GameCorner_EventScript_Fisher_Offer::
    .string "Do you want to try the slots?\nHere are 10 COINS to start with.$"

TH14_CeladonCity_GameCorner_EventScript_Fisher_RepeatText::
    .string "Remember to take a break.\nIt is easy to lose track of time.$"

TH14_CeladonCity_GameCorner_EventScript_Scientist_Repeat::
msgbox TH14_CeladonCity_GameCorner_EventScript_Scientist_RepeatText
    goto TH14_EcoEnd
    end

TH14_CeladonCity_GameCorner_EventScript_Scientist_Offer::
    .string "I am saving for a POKéMON prize.\nYou can have these 20 COINS.$"

TH14_CeladonCity_GameCorner_EventScript_Scientist_RepeatText::
    .string "I still need more COINS\nfor the POKéMON I want.$"

TH14_CeladonCity_GameCorner_EventScript_Gentleman_Repeat::
msgbox TH14_CeladonCity_GameCorner_EventScript_Gentleman_RepeatText
    goto TH14_EcoEnd
    end

TH14_CeladonCity_GameCorner_EventScript_Gentleman_Offer::
    .string "Here are 20 COINS.\nWatch the reels closely!$"

TH14_CeladonCity_GameCorner_EventScript_Gentleman_RepeatText::
    .string "Wins come and go.\nKnow when to stop.$"

TH14_EcoPlaySlots::
    .string "It is a slot machine.\nWould you like to play?$"

TH14_EcoUnusable1::
    .string "OUT OF ORDER$"

TH14_EcoUnusable2::
    .string "Someone has left a lunch here.$"

TH14_EcoUnusable3::
    .string "Someone has left their keys here.$"

TH14_EcoResult::
switch VAR_RESULT
    case 1, TH14_EcoSuccess
    case 2, TH14_EcoFunds
    case 3, TH14_EcoRoom
    case 4, TH14_EcoOwned
    goto TH14_EcoNoCase
    end

TH14_EcoSuccess::
    call_if_eq VAR_0x8009, 1, TH14_EcoUpdateCoins
    call_if_eq VAR_0x8009, 3, TH14_EcoUpdateCoins
    call_if_eq VAR_0x8009, 2, TH14_EcoUpdateMoney
    call_if_eq VAR_0x8009, 3, TH14_EcoUpdateMoney
goto_if_eq VAR_0x8008, 1, TH14_EcoMon
    goto_if_eq VAR_0x8008, 2, TH14_EcoCoins
    goto_if_eq VAR_0x8008, 3, TH14_EcoCoins
    bufferitemname STR_VAR_1, VAR_0x8007
    playfanfare MUS_OBTAIN_ITEM
    msgbox TH14_EcoItemReceived
    waitfanfare
    goto TH14_EcoEnd
    end

TH14_EcoCoins::
buffernumberstring STR_VAR_1, VAR_0x8007
    playse SE_SHOP
    msgbox TH14_EcoCoinsReceived
    goto TH14_EcoEnd
    end

TH14_EcoMon::
hidecoinsbox
    setvar VAR_0x8009, 0
    copyvar VAR_TEMP_2, VAR_0x8006
    bufferspeciesname STR_VAR_1, VAR_TEMP_TRANSFERRED_SPECIES
    playfanfare MUS_LEVEL_UP
    message gText_PlayerObtainedTheMon
    waitmessage
    waitfanfare
    msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
    goto_if_eq VAR_TEMP_2, 1, TH14_EcoMonPC
    goto_if_eq VAR_RESULT, NO, TH14_EcoEnd
    call Common_EventScript_GetGiftMonPartySlot
    call Common_EventScript_NameReceivedPartyMon
    goto TH14_EcoEnd
    end

TH14_EcoMonPC::
goto_if_eq VAR_RESULT, NO, TH14_EcoTransferred
    call Common_EventScript_NameReceivedBoxMon
TH14_EcoTransferred:
    call Common_EventScript_TransferredToPC
    goto TH14_EcoEnd
    end

TH14_EcoFunds::
goto_if_eq VAR_0x8008, 5, TH14_EcoDrinkMissing
    msgbox TH14_EcoFundsText
    goto TH14_EcoEnd
    end

TH14_EcoDrinkMissing::
msgbox TH14_EcoDrinkMissingText
    goto TH14_EcoEnd
    end

TH14_EcoRoom::
msgbox TH14_EcoRoomText
    goto TH14_EcoEnd
    end

TH14_EcoOwned::
msgbox TH14_EcoOwnedText
    goto TH14_EcoEnd
    end

TH14_EcoNoCase::
msgbox TH14_EcoNoCaseText
    goto TH14_EcoEnd
    end

TH14_EcoEnd::
call_if_eq VAR_0x8009, 1, TH14_EcoHideCoins
    call_if_eq VAR_0x8009, 3, TH14_EcoHideCoins
    call_if_eq VAR_0x8009, 2, TH14_EcoHideMoney
    call_if_eq VAR_0x8009, 3, TH14_EcoHideMoney
    releaseall
    end

TH14_EcoHideCoins::
hidecoinsbox
    return

TH14_EcoUpdateCoins::
    updatecoinsbox
    return

TH14_EcoUpdateMoney::
    updatemoneybox
    return

TH14_EcoHideMoney::
hidemoneybox
    return

TH14_EcoItemReceived::
    .string "{PLAYER} obtained\n{STR_VAR_1}!$"

TH14_EcoCoinsReceived::
    .string "{PLAYER} received {STR_VAR_1} COINS!$"

TH14_EcoFundsText::
    .string "You do not have enough to pay.\nPlease come back another time.$"

TH14_EcoDrinkMissingText::
    .string "You do not have that drink\nin your BAG.$"

TH14_EcoRoomText::
    .string "There is not enough room.\nPlease make space and try again.$"

TH14_EcoOwnedText::
    .string "You have already received that\nreward. Keep it safe!$"

TH14_EcoNoCaseText::
    .string "You need a COIN CASE\nin your BAG to use COINS.$"
