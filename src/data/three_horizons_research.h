// Authored descriptions and tableaux stay in ROM. Save data contains flags only.
static const struct THResearchEntry sResearchEntries[TH_RESEARCH_ENTRY_COUNT] = {
    [TH_RESEARCH_HOOTHOOT] = {
        .region = COMPOUND_STRING("KANTO"), .location = COMPOUND_STRING("Route 1"),
        .species = COMPOUND_STRING("Hoothoot"), .origin = COMPOUND_STRING("JOHTO"),
        .observation = COMPOUND_STRING("A visitor calls from a Kanto tree."),
        .notes = {COMPOUND_STRING("OAK: One sighting is a start.\nRecord where it feels at home."), COMPOUND_STRING("ELM: Reports now cross regions.\nTheir pace is unusual."), COMPOUND_STRING("OAK: The Tower report leaves\nour shipping idea unresolved.")},
        .flag = FLAG_TH13_OBS_HOOTHOOT, .photoId = TH_PHOTO_HOOTHOOT,
    },
    [TH_RESEARCH_FOREST_TREECKO] = {
        .region = COMPOUND_STRING("KANTO"), .location = COMPOUND_STRING("Viridian Forest"),
        .species = COMPOUND_STRING("Treecko / Weedle"), .origin = COMPOUND_STRING("HOENN / KANTO"),
        .observation = COMPOUND_STRING("The two greet each other\namong familiar forest leaves."),
        .notes = {COMPOUND_STRING("BIRCH: Treecko seems curious,\nnot displaced by the local life."), COMPOUND_STRING("ELM: Reports now cross regions.\nTheir pace is unusual."), COMPOUND_STRING("OAK: The Tower report leaves\nour shipping idea unresolved.")},
        .flag = FLAG_TH13_OBS_FOREST_TREECKO, .photoId = TH_PHOTO_FOREST_TREECKO,
    },
    [TH_RESEARCH_FOREST_SHROOMISH] = {
        .region = COMPOUND_STRING("KANTO"), .location = COMPOUND_STRING("Viridian Forest"),
        .species = COMPOUND_STRING("Shroomish / Caterpie"), .origin = COMPOUND_STRING("HOENN / KANTO"),
        .observation = COMPOUND_STRING("They bounce in greeting\namong the damp leaves."),
        .notes = {COMPOUND_STRING("BIRCH: A shared habitat may\nhelp them settle together."), COMPOUND_STRING("ELM: Reports now cross regions.\nTheir pace is unusual."), COMPOUND_STRING("OAK: The Tower report leaves\nour shipping idea unresolved.")},
        .flag = FLAG_TH13_OBS_FOREST_SHROOMISH, .photoId = TH_PHOTO_FOREST_SHROOMISH,
    },
    [TH_RESEARCH_MT_MOON] = {
        .region = COMPOUND_STRING("KANTO"), .location = COMPOUND_STRING("Mt. Moon"),
        .species = COMPOUND_STRING("Clefairy / Makuhita"), .origin = COMPOUND_STRING("KANTO / HOENN"),
        .observation = COMPOUND_STRING("Clefairy circle their visitor\nin a welcoming dance."),
        .notes = {COMPOUND_STRING("BIRCH: Makuhita is being\nwelcomed by the local group."), COMPOUND_STRING("ELM: Reports now cross regions.\nTheir pace is unusual."), COMPOUND_STRING("OAK: The Tower report leaves\nour shipping idea unresolved.")},
        .flag = FLAG_TH13_OBS_MT_MOON, .photoId = TH_PHOTO_MT_MOON,
    },
    [TH_RESEARCH_SHIP] = {
        .region = COMPOUND_STRING("KANTO"), .location = COMPOUND_STRING("Vermilion Harbor"),
        .species = COMPOUND_STRING("Regional travelers"), .origin = COMPOUND_STRING("JOHTO / HOENN"),
        .observation = COMPOUND_STRING("Cargo and passengers cross\nthe sea to Kanto."),
        .notes = {COMPOUND_STRING("OAK: Shipping is a reasonable\nlead. It is not yet an answer."), COMPOUND_STRING("ELM: Reports now cross regions.\nTheir pace is unusual."), COMPOUND_STRING("OAK: The Tower report leaves\nour shipping idea unresolved.")},
        .flag = FLAG_TH13_OBS_SHIP, .photoId = TH_PHOTO_SHIP,
    },
    [TH_RESEARCH_FOREST_PAIR] = {
        .region = COMPOUND_STRING("KANTO"), .location = COMPOUND_STRING("Forest Cut Clearing"),
        .species = COMPOUND_STRING("Pinsir / Heracross"), .origin = COMPOUND_STRING("KANTO / JOHTO"),
        .observation = COMPOUND_STRING("They peacefully share\nthe same forest clearing."),
        .notes = {COMPOUND_STRING("ELM: Neither seems eager\nto drive the other away."), COMPOUND_STRING("ELM: Reports now cross regions.\nTheir pace is unusual."), COMPOUND_STRING("OAK: The Tower report leaves\nour shipping idea unresolved.")},
        .flag = FLAG_TH13_OBS_FOREST_PAIR, .photoId = TH_PHOTO_FOREST_PAIR,
    },
    [TH_RESEARCH_CAVE] = {
        .region = COMPOUND_STRING("KANTO"), .location = COMPOUND_STRING("Diglett's Cave"),
        .species = COMPOUND_STRING("Phanpy / Whismur"), .origin = COMPOUND_STRING("JOHTO / HOENN"),
        .observation = COMPOUND_STRING("New tracks cross the tunnels\nused by Diglett."),
        .notes = {COMPOUND_STRING("OAK: Compare these tracks\nwith the changing tunnel paths."), COMPOUND_STRING("ELM: Reports now cross regions.\nTheir pace is unusual."), COMPOUND_STRING("OAK: The Tower report leaves\nour shipping idea unresolved.")},
        .flag = FLAG_TH13_OBS_CAVE, .photoId = TH_PHOTO_CAVE,
    },
    [TH_RESEARCH_ROUTE9] = {
        .region = COMPOUND_STRING("KANTO"), .location = COMPOUND_STRING("Route 9"),
        .species = COMPOUND_STRING("Mareep / Nidoran"), .origin = COMPOUND_STRING("JOHTO / KANTO"),
        .observation = COMPOUND_STRING("The pair graze peacefully.\nLocal life is adapting."),
        .notes = {COMPOUND_STRING("ELM: The distribution no longer\nmatches old seasonal records."), COMPOUND_STRING("ELM: Reports now cross regions.\nTheir pace is unusual."), COMPOUND_STRING("OAK: The Tower report leaves\nour shipping idea unresolved.")},
        .flag = FLAG_TH13_OBS_ROUTE9, .photoId = TH_PHOTO_ROUTE9,
    },
    [TH_RESEARCH_ROCK_TUNNEL] = {
        .region = COMPOUND_STRING("KANTO"), .location = COMPOUND_STRING("Rock Tunnel"),
        .species = COMPOUND_STRING("Aron / Geodude"), .origin = COMPOUND_STRING("HOENN / KANTO"),
        .observation = COMPOUND_STRING("Aron feeds on mineral rock.\nGeodude investigates nearby."),
        .notes = {COMPOUND_STRING("BIRCH: They share a mineral\npatch without a territorial fight."), COMPOUND_STRING("ELM: Reports now cross regions.\nTheir pace is unusual."), COMPOUND_STRING("OAK: The Tower report leaves\nour shipping idea unresolved.")},
        .flag = FLAG_TH13_OBS_ROCK_TUNNEL, .photoId = TH_PHOTO_ROCK_TUNNEL,
    },
    [TH_RESEARCH_LAVENDER] = {
        .region = COMPOUND_STRING("KANTO"), .location = COMPOUND_STRING("Lavender Town"),
        .species = COMPOUND_STRING("Misdreavus"), .origin = COMPOUND_STRING("JOHTO"),
        .observation = COMPOUND_STRING("Its presence near the Tower\ndoes not fit the shipping lead."),
        .notes = {COMPOUND_STRING("OAK: Keep careful notes.\nWe do not have an explanation."), COMPOUND_STRING("ELM: Reports now cross regions.\nTheir pace is unusual."), COMPOUND_STRING("OAK: The Tower report leaves\nour shipping idea unresolved.")},
        .flag = FLAG_TH13_OBS_LAVENDER, .photoId = TH_PHOTO_LAVENDER,
    },
    [TH_RESEARCH_FOREST_LEGACY] = {
        .region = COMPOUND_STRING("KANTO"), .location = COMPOUND_STRING("Viridian Forest"),
        .species = COMPOUND_STRING("Earlier forest report"), .origin = COMPOUND_STRING("REGIONAL VISITOR"),
        .observation = COMPOUND_STRING("An earlier report was recorded.\nThe exact pair was not stored."),
        .notes = {COMPOUND_STRING("OAK: Revisit the forest to\nidentify each interaction."), COMPOUND_STRING("OAK: Revisit the forest to\nidentify each interaction."), COMPOUND_STRING("OAK: Revisit the forest to\nidentify each interaction.")},
        .flag = FLAG_TH13_OBS_FOREST_LEGACY, .photoId = TH_RESEARCH_PHOTO_NONE,
    },
    [TH_RESEARCH_MOTHERS_WATCH] = {
        .region = COMPOUND_STRING("KANTO"), .location = COMPOUND_STRING("Pokemon Tower"),
        .species = COMPOUND_STRING("MOTHER'S WATCH"), .origin = COMPOUND_STRING("KANTO"),
        .observation = COMPOUND_STRING("A mother's spirit remained at the\nTower. Her concern for CUBONE seems\nstronger than the place itself."),
        .notes = {COMPOUND_STRING("OAK: Her concern for CUBONE seems\nstronger than the place itself."),
                  COMPOUND_STRING("OAK: Her concern for CUBONE seems\nstronger than the place itself."),
                  COMPOUND_STRING("OAK: Habitat tells us where a\nPOKéMON lives. This record reminds\nus that bonds and memory deserve\ncareful study, too.")},
        .flag = FLAG_TH14_OBS_MOTHER, .photoId = TH_PHOTO_MOTHERS_WATCH,
    },
};
static const struct THResearchPhoto sResearchPhotos[TH_RESEARCH_PHOTO_COUNT] = {
    [TH_PHOTO_HOOTHOOT] = {TH_RESEARCH_HOOTHOOT, TH_BACKDROP_GRASS, 1, {
        {SPECIES_HOOTHOOT, 128, 80, DIR_SOUTH},
    }},
    [TH_PHOTO_FOREST_TREECKO] = {TH_RESEARCH_FOREST_TREECKO, TH_BACKDROP_GRASS, 2, {
        {SPECIES_TREECKO, 112, 80, DIR_EAST},
        {SPECIES_WEEDLE, 144, 80, DIR_WEST},
    }},
    [TH_PHOTO_FOREST_SHROOMISH] = {TH_RESEARCH_FOREST_SHROOMISH, TH_BACKDROP_GRASS, 2, {
        {SPECIES_SHROOMISH, 112, 80, DIR_EAST},
        {SPECIES_CATERPIE, 144, 80, DIR_WEST},
    }},
    [TH_PHOTO_MT_MOON] = {TH_RESEARCH_MT_MOON, TH_BACKDROP_CAVE, 4, {
        {SPECIES_MAKUHITA, 112, 80, DIR_SOUTH},
        {SPECIES_CLEFAIRY, 96, 64, DIR_EAST},
        {SPECIES_CLEFAIRY, 144, 80, DIR_WEST},
        {SPECIES_CLEFAIRY, 96, 96, DIR_SOUTH},
    }},
    [TH_PHOTO_SHIP] = {TH_RESEARCH_SHIP, TH_BACKDROP_SHIP, 2, {
        {SPECIES_MARILL, 112, 80, DIR_EAST},
        {SPECIES_WINGULL, 144, 80, DIR_WEST},
    }},
    [TH_PHOTO_FOREST_PAIR] = {TH_RESEARCH_FOREST_PAIR, TH_BACKDROP_GRASS, 2, {
        {SPECIES_PINSIR, 112, 80, DIR_EAST},
        {SPECIES_HERACROSS, 144, 80, DIR_WEST},
    }},
    [TH_PHOTO_CAVE] = {TH_RESEARCH_CAVE, TH_BACKDROP_CAVE, 2, {
        {SPECIES_PHANPY, 112, 80, DIR_EAST},
        {SPECIES_WHISMUR, 144, 80, DIR_WEST},
    }},
    [TH_PHOTO_ROUTE9] = {TH_RESEARCH_ROUTE9, TH_BACKDROP_GRASS, 2, {
        {SPECIES_MAREEP, 112, 80, DIR_EAST},
        {SPECIES_NIDORAN_F, 144, 80, DIR_WEST},
    }},
    [TH_PHOTO_ROCK_TUNNEL] = {TH_RESEARCH_ROCK_TUNNEL, TH_BACKDROP_CAVE, 2, {
        {SPECIES_ARON, 112, 80, DIR_EAST},
        {SPECIES_GEODUDE, 144, 96, DIR_WEST},
    }},
    [TH_PHOTO_LAVENDER] = {TH_RESEARCH_LAVENDER, TH_BACKDROP_TOWER, 1, {
        {SPECIES_MISDREAVUS, 176, 112, DIR_SOUTH},
    }},
    [TH_PHOTO_MOTHERS_WATCH] = {TH_RESEARCH_MOTHERS_WATCH, TH_BACKDROP_TOWER, 1, {
        {SPECIES_MAROWAK, 128, 112, DIR_NORTH},
    }},
};
static const u16 sPhotoFlags[TH_RESEARCH_PHOTO_COUNT] = {
    [TH_PHOTO_HOOTHOOT] = FLAG_TH13_PHOTO_HOOTHOOT,
    [TH_PHOTO_FOREST_TREECKO] = FLAG_TH13_PHOTO_FOREST_TREECKO,
    [TH_PHOTO_FOREST_SHROOMISH] = FLAG_TH13_PHOTO_FOREST_SHROOMISH,
    [TH_PHOTO_MT_MOON] = FLAG_TH13_PHOTO_MT_MOON,
    [TH_PHOTO_SHIP] = FLAG_TH13_PHOTO_SHIP,
    [TH_PHOTO_FOREST_PAIR] = FLAG_TH13_PHOTO_FOREST_PAIR,
    [TH_PHOTO_CAVE] = FLAG_TH13_PHOTO_CAVE,
    [TH_PHOTO_ROUTE9] = FLAG_TH13_PHOTO_ROUTE9,
    [TH_PHOTO_ROCK_TUNNEL] = FLAG_TH13_PHOTO_ROCK_TUNNEL,
    [TH_PHOTO_LAVENDER] = FLAG_TH13_PHOTO_LAVENDER,
    [TH_PHOTO_MOTHERS_WATCH] = FLAG_TH14_PHOTO_MOTHER,
};
static const u16 sCallFlags[TH_RESEARCH_CALL_COUNT][2] = {
    [TH_CALL_ACTIVATION] = {FLAG_TH13_CALL_ACTIVATION_PENDING, FLAG_TH13_CALL_ACTIVATION_DELIVERED},
    [TH_CALL_ROUTE10] = {FLAG_TH13_CALL_ROUTE10_PENDING, FLAG_TH13_CALL_ROUTE10_DELIVERED},
    [TH_CALL_LAVENDER] = {FLAG_TH13_CALL_LAVENDER_PENDING, FLAG_TH13_CALL_LAVENDER_DELIVERED},
    [TH_CALL_ELM] = {FLAG_TH13_CALL_ELM_PENDING, FLAG_TH13_CALL_ELM_DELIVERED},
    [TH_CALL_BIRCH] = {FLAG_TH13_CALL_BIRCH_PENDING, FLAG_TH13_CALL_BIRCH_DELIVERED},
};
STATIC_ASSERT(ARRAY_COUNT(sPhotoFlags) == ARRAY_COUNT(sResearchPhotos), ResearchPhotoFlagsMatchCards);
