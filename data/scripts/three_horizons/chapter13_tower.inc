@ Native Tower routes and first trainer parties; unresolved upper barrier.
TH13_PokemonTower_1F_Text_ErectedInMemoryOfDeadMons::
	.string "POKéMON TOWER was erected in the\n"
	.string "memory of POKéMON that died.$"

TH13_PokemonTower_1F_Text_ComeToPayRespectsSon::
	.string "Did you come to pay respects?\p"
	.string "Bless your POKéMON-loving heart,\n"
	.string "son.$"

TH13_PokemonTower_1F_Text_ComeToPayRespectsGirl::
	.string "Did you come to pay respects?\p"
	.string "Bless your POKéMON-loving heart,\n"
	.string "girl.$"

TH13_PokemonTower_1F_Text_CameToPrayForDepartedClefairy::
	.string "I came to pray for my dearly\n"
	.string "departed CLEFAIRY.\p"
	.string "Sniff!\n"
	.string "I'm awash in tears…$"

TH13_PokemonTower_1F_Text_GrowlitheWhyDidYouDie::
	.string "My GROWLITHE…\n"
	.string "Why did you die?$"

TH13_PokemonTower_1F_Text_SenseSpiritsUpToMischief::
	.string "I am a CHANNELER.\p"
	.string "There are spirits up to mischief.\n"
	.string "I sense them high in the TOWER.$"

TH13_PokemonTower_1F_EventScript_WorkerF::
	msgbox TH13_PokemonTower_1F_Text_ErectedInMemoryOfDeadMons, MSGBOX_NPC
	end

TH13_PokemonTower_1F_EventScript_Channeler::
    goto_if_set FLAG_TH14_MOTHER_RESOLVED, TH14_Tower_MemorialQuiet
	msgbox TH13_PokemonTower_1F_Text_SenseSpiritsUpToMischief, MSGBOX_NPC
	end

TH13_PokemonTower_1F_EventScript_Woman1::
	msgbox TH13_PokemonTower_1F_Text_GrowlitheWhyDidYouDie, MSGBOX_NPC
	end

TH13_PokemonTower_1F_EventScript_Woman2::
	lock
	faceplayer
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, TH13_PokemonTower_1F_EventScript_Woman2MalePlayer
	msgbox TH13_PokemonTower_1F_Text_ComeToPayRespectsGirl
	release
	end

TH13_PokemonTower_1F_EventScript_BaldingMan::
	msgbox TH13_PokemonTower_1F_Text_CameToPrayForDepartedClefairy, MSGBOX_NPC
	end

TH14_Tower_MemorialQuiet:
    msgbox TH14_Tower_MemorialQuietText, MSGBOX_NPC
    end
TH14_Tower_MemorialQuietText:
    .string "The restless presence has quieted.\nMay those at rest find peace.$"

TH13_PokemonTower_1F_EventScript_Woman2MalePlayer::
	msgbox TH13_PokemonTower_1F_Text_ComeToPayRespectsSon
	release
	end

TH13_PokemonTower_2F_Text_SilphScopeCouldUnmaskGhosts::
	.string "Even we could not identify the\n"
	.string "wayward ghosts.\p"
	.string "A SILPH SCOPE might be able to\n"
	.string "unmask them.$"

TH13_PokemonTower_2F_EventScript_Channeler::
	msgbox TH13_PokemonTower_2F_Text_SilphScopeCouldUnmaskGhosts, MSGBOX_NPC
	end

TH13_PokemonTower_3F_Patricia::
    trainerbattle_single TRAINER_TH13_POKEMONTOWER_3F_PATRICIA, TH13_PokemonTower_3F_Text_PatriciaIntro, TH13_PokemonTower_3F_Text_PatriciaDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH13_PokemonTower_3F_Patricia_Rematch
    msgbox TH13_PokemonTower_3F_Text_PatriciaPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_PokemonTower_3F_Patricia_Rematch::
    trainerbattle_rematch TRAINER_TH13_POKEMONTOWER_3F_PATRICIA, TH13_PokemonTower_3F_Text_PatriciaIntro, TH13_PokemonTower_3F_Text_PatriciaDefeat
    msgbox TH13_PokemonTower_3F_Text_PatriciaPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_PokemonTower_3F_Carly::
    trainerbattle_single TRAINER_TH13_POKEMONTOWER_3F_CARLY, TH13_PokemonTower_3F_Text_CarlyIntro, TH13_PokemonTower_3F_Text_CarlyDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH13_PokemonTower_3F_Carly_Rematch
    msgbox TH13_PokemonTower_3F_Text_CarlyPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_PokemonTower_3F_Carly_Rematch::
    trainerbattle_rematch TRAINER_TH13_POKEMONTOWER_3F_CARLY, TH13_PokemonTower_3F_Text_CarlyIntro, TH13_PokemonTower_3F_Text_CarlyDefeat
    msgbox TH13_PokemonTower_3F_Text_CarlyPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_PokemonTower_3F_Hope::
    trainerbattle_single TRAINER_TH13_POKEMONTOWER_3F_HOPE, TH13_PokemonTower_3F_Text_HopeIntro, TH13_PokemonTower_3F_Text_HopeDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH13_PokemonTower_3F_Hope_Rematch
    msgbox TH13_PokemonTower_3F_Text_HopePostBattle, MSGBOX_AUTOCLOSE
    end
TH13_PokemonTower_3F_Hope_Rematch::
    trainerbattle_rematch TRAINER_TH13_POKEMONTOWER_3F_HOPE, TH13_PokemonTower_3F_Text_HopeIntro, TH13_PokemonTower_3F_Text_HopeDefeat
    msgbox TH13_PokemonTower_3F_Text_HopePostBattle, MSGBOX_AUTOCLOSE
    end
TH13_PokemonTower_3F_Text_HopeIntro::
	.string "Urrg… Awaa…\n"
	.string "Huhu… Graa…$"

TH13_PokemonTower_3F_Text_HopeDefeat::
	.string "Hwa!\n"
	.string "I'm saved!$"

TH13_PokemonTower_3F_Text_HopePostBattle::
	.string "The ghosts can be identified by\n"
	.string "the SILPH SCOPE.$"

TH13_PokemonTower_3F_Text_CarlyIntro::
	.string "Kekeke…\n"
	.string "Kwaaah!$"

TH13_PokemonTower_3F_Text_CarlyDefeat::
	.string "Hmm?\n"
	.string "What am I doing?$"

TH13_PokemonTower_3F_Text_CarlyPostBattle::
	.string "Sorry!\n"
	.string "I was possessed!$"

TH13_PokemonTower_3F_Text_PatriciaIntro::
	.string "Be gone!\n"
	.string "Malevolent spirit!$"

TH13_PokemonTower_3F_Text_PatriciaDefeat::
	.string "Whew!\n"
	.string "The spirit left!$"

TH13_PokemonTower_3F_Text_PatriciaPostBattle::
	.string "The others above…\n"
	.string "They must have been possessed.$"

TH13_PokemonTower_3F_Item19::
    finditem ITEM_ESCAPE_ROPE
    end
TH13_PokemonTower_4F_Laurel::
    trainerbattle_single TRAINER_TH13_POKEMONTOWER_4F_LAUREL, TH13_PokemonTower_4F_Text_LaurelIntro, TH13_PokemonTower_4F_Text_LaurelDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH13_PokemonTower_4F_Laurel_Rematch
    msgbox TH13_PokemonTower_4F_Text_LaurelPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_PokemonTower_4F_Laurel_Rematch::
    trainerbattle_rematch TRAINER_TH13_POKEMONTOWER_4F_LAUREL, TH13_PokemonTower_4F_Text_LaurelIntro, TH13_PokemonTower_4F_Text_LaurelDefeat
    msgbox TH13_PokemonTower_4F_Text_LaurelPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_PokemonTower_4F_Jody::
    trainerbattle_single TRAINER_TH13_POKEMONTOWER_4F_JODY, TH13_PokemonTower_4F_Text_JodyIntro, TH13_PokemonTower_4F_Text_JodyDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH13_PokemonTower_4F_Jody_Rematch
    msgbox TH13_PokemonTower_4F_Text_JodyPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_PokemonTower_4F_Jody_Rematch::
    trainerbattle_rematch TRAINER_TH13_POKEMONTOWER_4F_JODY, TH13_PokemonTower_4F_Text_JodyIntro, TH13_PokemonTower_4F_Text_JodyDefeat
    msgbox TH13_PokemonTower_4F_Text_JodyPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_PokemonTower_4F_Paula::
    trainerbattle_single TRAINER_TH13_POKEMONTOWER_4F_PAULA, TH13_PokemonTower_4F_Text_PaulaIntro, TH13_PokemonTower_4F_Text_PaulaDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH13_PokemonTower_4F_Paula_Rematch
    msgbox TH13_PokemonTower_4F_Text_PaulaPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_PokemonTower_4F_Paula_Rematch::
    trainerbattle_rematch TRAINER_TH13_POKEMONTOWER_4F_PAULA, TH13_PokemonTower_4F_Text_PaulaIntro, TH13_PokemonTower_4F_Text_PaulaDefeat
    msgbox TH13_PokemonTower_4F_Text_PaulaPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_PokemonTower_4F_Text_PaulaIntro::
	.string "Ghost! No!\n"
	.string "Kwaaah!$"

TH13_PokemonTower_4F_Text_PaulaDefeat::
	.string "Where is the ghost?$"

TH13_PokemonTower_4F_Text_PaulaPostBattle::
	.string "I must have been dreaming…$"

TH13_PokemonTower_4F_Text_LaurelIntro::
	.string "Be cursed with me!\n"
	.string "Kwaaah!$"

TH13_PokemonTower_4F_Text_LaurelDefeat::
	.string "What!$"

TH13_PokemonTower_4F_Text_LaurelPostBattle::
	.string "We can't determine the identity of\n"
	.string "the ghosts…$"

TH13_PokemonTower_4F_Text_JodyIntro::
	.string "Huhuhu…\n"
	.string "Beat me not!$"

TH13_PokemonTower_4F_Text_JodyDefeat::
	.string "Huh?\n"
	.string "Who? What?$"

TH13_PokemonTower_4F_Text_JodyPostBattle::
	.string "May the departed POKéMON rest in\n"
	.string "peace…$"

TH13_PokemonTower_4F_Item20::
    finditem ITEM_ELIXIR
    end
TH13_PokemonTower_4F_Item21::
    finditem ITEM_AWAKENING
    end
TH13_PokemonTower_4F_Item22::
    finditem ITEM_GREAT_BALL
    end
TH13_PokemonTower_5F_Ruth::
    trainerbattle_single TRAINER_TH13_POKEMONTOWER_5F_RUTH, TH13_PokemonTower_5F_Text_RuthIntro, TH13_PokemonTower_5F_Text_RuthDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH13_PokemonTower_5F_Ruth_Rematch
    msgbox TH13_PokemonTower_5F_Text_RuthPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_PokemonTower_5F_Ruth_Rematch::
    trainerbattle_rematch TRAINER_TH13_POKEMONTOWER_5F_RUTH, TH13_PokemonTower_5F_Text_RuthIntro, TH13_PokemonTower_5F_Text_RuthDefeat
    msgbox TH13_PokemonTower_5F_Text_RuthPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_PokemonTower_5F_Tammy::
    trainerbattle_single TRAINER_TH13_POKEMONTOWER_5F_TAMMY, TH13_PokemonTower_5F_Text_TammyIntro, TH13_PokemonTower_5F_Text_TammyDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH13_PokemonTower_5F_Tammy_Rematch
    msgbox TH13_PokemonTower_5F_Text_TammyPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_PokemonTower_5F_Tammy_Rematch::
    trainerbattle_rematch TRAINER_TH13_POKEMONTOWER_5F_TAMMY, TH13_PokemonTower_5F_Text_TammyIntro, TH13_PokemonTower_5F_Text_TammyDefeat
    msgbox TH13_PokemonTower_5F_Text_TammyPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_PokemonTower_5F_Karina::
    trainerbattle_single TRAINER_TH13_POKEMONTOWER_5F_KARINA, TH13_PokemonTower_5F_Text_KarinaIntro, TH13_PokemonTower_5F_Text_KarinaDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH13_PokemonTower_5F_Karina_Rematch
    msgbox TH13_PokemonTower_5F_Text_KarinaPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_PokemonTower_5F_Karina_Rematch::
    trainerbattle_rematch TRAINER_TH13_POKEMONTOWER_5F_KARINA, TH13_PokemonTower_5F_Text_KarinaIntro, TH13_PokemonTower_5F_Text_KarinaDefeat
    msgbox TH13_PokemonTower_5F_Text_KarinaPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_PokemonTower_5F_Janae::
    trainerbattle_single TRAINER_TH13_POKEMONTOWER_5F_JANAE, TH13_PokemonTower_5F_Text_JanaeIntro, TH13_PokemonTower_5F_Text_JanaeDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH13_PokemonTower_5F_Janae_Rematch
    msgbox TH13_PokemonTower_5F_Text_JanaePostBattle, MSGBOX_AUTOCLOSE
    end
TH13_PokemonTower_5F_Janae_Rematch::
    trainerbattle_rematch TRAINER_TH13_POKEMONTOWER_5F_JANAE, TH13_PokemonTower_5F_Text_JanaeIntro, TH13_PokemonTower_5F_Text_JanaeDefeat
    msgbox TH13_PokemonTower_5F_Text_JanaePostBattle, MSGBOX_AUTOCLOSE
    end
TH13_PokemonTower_5F_Text_RestHereInPurifiedSpace::
	.string "Come, child!\n"
	.string "I have purified this space.\l"
	.string "You can rest here.$"

TH13_PokemonTower_5F_Text_TammyIntro::
	.string "Give…me…\n"
	.string "your…all…$"

TH13_PokemonTower_5F_Text_TammyDefeat::
	.string "Gasp!$"

TH13_PokemonTower_5F_Text_TammyPostBattle::
	.string "I was under possession.$"

TH13_PokemonTower_5F_Text_RuthIntro::
	.string "You…shall…\n"
	.string "join…us…$"

TH13_PokemonTower_5F_Text_RuthDefeat::
	.string "What a nightmare!$"

TH13_PokemonTower_5F_Text_RuthPostBattle::
	.string "I was possessed.$"

TH13_PokemonTower_5F_Text_KarinaIntro::
	.string "Zombies!$"

TH13_PokemonTower_5F_Text_KarinaDefeat::
	.string "Ha?$"

TH13_PokemonTower_5F_Text_KarinaPostBattle::
	.string "I regained my senses.$"

TH13_PokemonTower_5F_Text_JanaeIntro::
	.string "Urgah…\n"
	.string "Urff…$"

TH13_PokemonTower_5F_Text_JanaeDefeat::
	.string "Whoo!$"

TH13_PokemonTower_5F_Text_JanaePostBattle::
	.string "I fell to evil spirits despite my\n"
	.string "training in the mountains…$"

TH13_PokemonTower_5F_Text_PurifiedZoneMonsFullyHealed::
	.string "Entered the purified and protected\n"
	.string "zone.\p"
	.string "{PLAYER}'s POKéMON were fully\n"
	.string "healed.$"

TH13_PokemonTower_5F_EventScript_Channeler::
	msgbox TH13_PokemonTower_5F_Text_RestHereInPurifiedSpace, MSGBOX_NPC
	end

TH13_PokemonTower_5F_Item23::
    finditem ITEM_NUGGET
    end
TH13_PokemonTower_5F_Item24::
    finditem ITEM_CLEANSE_TAG
    end
TH13_PokemonTower_5F_EventScript_PurifiedZone::
	lockall
	fadescreen FADE_TO_WHITE
	special HealPlayerParty
	fadescreen FADE_FROM_WHITE
	msgbox TH13_PokemonTower_5F_Text_PurifiedZoneMonsFullyHealed
	setvar VAR_TEMP_1, 1
	releaseall
	end

TH13_PokemonTower_5F_EventScript_ExitPurifiedZone::
	lockall
	setvar VAR_TEMP_1, 0
	releaseall
	end

TH13_PokemonTower_6F_Angelica::
    trainerbattle_single TRAINER_TH13_POKEMONTOWER_6F_ANGELICA, TH13_PokemonTower_6F_Text_AngelicaIntro, TH13_PokemonTower_6F_Text_AngelicaDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH13_PokemonTower_6F_Angelica_Rematch
    msgbox TH13_PokemonTower_6F_Text_AngelicaPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_PokemonTower_6F_Angelica_Rematch::
    trainerbattle_rematch TRAINER_TH13_POKEMONTOWER_6F_ANGELICA, TH13_PokemonTower_6F_Text_AngelicaIntro, TH13_PokemonTower_6F_Text_AngelicaDefeat
    msgbox TH13_PokemonTower_6F_Text_AngelicaPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_PokemonTower_6F_Jennifer::
    trainerbattle_single TRAINER_TH13_POKEMONTOWER_6F_JENNIFER, TH13_PokemonTower_6F_Text_JenniferIntro, TH13_PokemonTower_6F_Text_JenniferDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH13_PokemonTower_6F_Jennifer_Rematch
    msgbox TH13_PokemonTower_6F_Text_JenniferPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_PokemonTower_6F_Jennifer_Rematch::
    trainerbattle_rematch TRAINER_TH13_POKEMONTOWER_6F_JENNIFER, TH13_PokemonTower_6F_Text_JenniferIntro, TH13_PokemonTower_6F_Text_JenniferDefeat
    msgbox TH13_PokemonTower_6F_Text_JenniferPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_PokemonTower_6F_Emilia::
    trainerbattle_single TRAINER_TH13_POKEMONTOWER_6F_EMILIA, TH13_PokemonTower_6F_Text_EmiliaIntro, TH13_PokemonTower_6F_Text_EmiliaDefeat
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_eq VAR_RESULT, TRUE, TH13_PokemonTower_6F_Emilia_Rematch
    msgbox TH13_PokemonTower_6F_Text_EmiliaPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_PokemonTower_6F_Emilia_Rematch::
    trainerbattle_rematch TRAINER_TH13_POKEMONTOWER_6F_EMILIA, TH13_PokemonTower_6F_Text_EmiliaIntro, TH13_PokemonTower_6F_Text_EmiliaDefeat
    msgbox TH13_PokemonTower_6F_Text_EmiliaPostBattle, MSGBOX_AUTOCLOSE
    end
TH13_PokemonTower_6F_Text_AngelicaIntro::
	.string "Give…me…\n"
	.string "blood…$"

TH13_PokemonTower_6F_Text_AngelicaDefeat::
	.string "Groan!$"

TH13_PokemonTower_6F_Text_AngelicaPostBattle::
	.string "I feel anemic and weak…$"

TH13_PokemonTower_6F_Text_EmiliaIntro::
	.string "Urff…\n"
	.string "Kwaah!$"

TH13_PokemonTower_6F_Text_EmiliaDefeat::
	.string "Something fell out!$"

TH13_PokemonTower_6F_Text_EmiliaPostBattle::
	.string "My hair didn't fall out!\n"
	.string "It was a malevolent spirit!$"

TH13_PokemonTower_6F_Text_JenniferIntro::
	.string "Ke…ke…ke…\n"
	.string "ke…ke…ke!$"

TH13_PokemonTower_6F_Text_JenniferDefeat::
	.string "Keee!$"

TH13_PokemonTower_6F_Text_JenniferPostBattle::
	.string "What's going on here?$"

TH13_PokemonTower_6F_Item26::
    finditem ITEM_RARE_CANDY
    end
TH13_PokemonTower_6F_Item27::
    finditem ITEM_X_ACCURACY
    end

TH13_Tower_RocketRecord::
    lock
    faceplayer
    @ Repeat speech is map-local; no new permanent story receipt.
    goto_if_set FLAG_TH13_ENDPOINT, TH14_Tower_RocketRepeat
    goto_if_set FLAG_TEMP_1, TH14_Tower_RocketRepeat
    msgbox TH13_Tower_RocketText
    setflag FLAG_TEMP_1
    release
    end
TH14_Tower_RocketRepeat:
    msgbox TH14_Tower_RocketRepeatText
    release
    end
TH13_Tower_RocketText:
    .string "GIOVANNI ordered us to collect\nunusual sightings, ghost reports\pand migration notes.\nI am on paperwork duty.\pThese reports are going\nto CELADON.$"
TH13_Tower_GhostBarrier::
    goto TH14_Tower_MotherBarrier
TH13_Tower_EndpointText:
    .string "A restless presence bars the stairs.\nA SILPH SCOPE could reveal it.\pGIOVANNI's observer sends ghost\nreports to CELADON.\pJESSIE and JAMES have business\nthere, too.$"
TH13_Tower_RepeatText:
    .string "The presence still bars the stairs.\nA SILPH SCOPE could reveal it.\pGIOVANNI's ghost reports and the\ntrio's business point to CELADON.\pFind out what JESSIE and JAMES\nare doing there.$"

TH14_Tower_RocketRepeatText:
    .string "Our people in CELADON are\ncomparing the reports.\pThey have equipment for things\nwe cannot identify.$"
