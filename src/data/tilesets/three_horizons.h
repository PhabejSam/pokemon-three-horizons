// Native Kanto tilesets used by the Emerald-based Three Horizons journey.
// Asset paths and descriptors mirror the upstream FRLG definitions.
// Existing binaries, palette formats and animation callbacks are reused.

const u16 gMetatileAttributes_Building_Frlg[] = INCBIN_U16("data/tilesets/primary/building_frlg/metatile_attributes.bin");

const u16 gMetatileAttributes_General_Frlg[] = INCBIN_U16("data/tilesets/primary/general_frlg/metatile_attributes.bin");

const u16 gMetatileAttributes_GenericBuilding1[] = INCBIN_U16("data/tilesets/secondary/generic_building_1_frlg/metatile_attributes.bin");

const u16 gMetatileAttributes_Lab_Frlg[] = INCBIN_U16("data/tilesets/secondary/lab_frlg/metatile_attributes.bin");

const u16 gMetatileAttributes_PalletTown[] = INCBIN_U16("data/tilesets/secondary/pallet_town_frlg/metatile_attributes.bin");

const u16 gMetatileAttributes_ViridianCity[] = INCBIN_U16("data/tilesets/secondary/viridian_city_frlg/metatile_attributes.bin");

const u16 gMetatiles_Building_Frlg[] = INCBIN_U16("data/tilesets/primary/building_frlg/metatiles.bin");

const u16 gMetatiles_General_Frlg[] = INCBIN_U16("data/tilesets/primary/general_frlg/metatiles.bin");

const u16 gMetatiles_GenericBuilding1[] = INCBIN_U16("data/tilesets/secondary/generic_building_1_frlg/metatiles.bin");

const u16 gMetatiles_Lab_Frlg[] = INCBIN_U16("data/tilesets/secondary/lab_frlg/metatiles.bin");

const u16 gMetatiles_PalletTown[] = INCBIN_U16("data/tilesets/secondary/pallet_town_frlg/metatiles.bin");

const u16 gMetatiles_ViridianCity[] = INCBIN_U16("data/tilesets/secondary/viridian_city_frlg/metatiles.bin");

const u16 gTilesetPalettes_Building_Frlg[][16] =
{
    INCGFX_U16("data/tilesets/primary/building_frlg/palettes/00.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/primary/building_frlg/palettes/01.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/primary/building_frlg/palettes/02.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/primary/building_frlg/palettes/03.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/primary/building_frlg/palettes/04.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/primary/building_frlg/palettes/05.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/primary/building_frlg/palettes/06.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/primary/building_frlg/palettes/07.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/primary/building_frlg/palettes/08.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/primary/building_frlg/palettes/09.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/primary/building_frlg/palettes/10.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/primary/building_frlg/palettes/11.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/primary/building_frlg/palettes/12.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/primary/building_frlg/palettes/13.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/primary/building_frlg/palettes/14.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/primary/building_frlg/palettes/15.pal", ".gbapal"),
};

const u16 ALIGNED(4) gTilesetPalettes_General_Frlg[][16] =
{
    INCGFX_U16("data/tilesets/primary/general_frlg/palettes/00.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/primary/general_frlg/palettes/01.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/primary/general_frlg/palettes/02.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/primary/general_frlg/palettes/03.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/primary/general_frlg/palettes/04.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/primary/general_frlg/palettes/05.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/primary/general_frlg/palettes/06.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/primary/general_frlg/palettes/07.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/primary/general_frlg/palettes/08.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/primary/general_frlg/palettes/09.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/primary/general_frlg/palettes/10.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/primary/general_frlg/palettes/11.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/primary/general_frlg/palettes/12.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/primary/general_frlg/palettes/13.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/primary/general_frlg/palettes/14.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/primary/general_frlg/palettes/15.pal", ".gbapal"),
};

const u16 gTilesetPalettes_GenericBuilding1[][16] =
{
    INCGFX_U16("data/tilesets/secondary/generic_building_1_frlg/palettes/00.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/generic_building_1_frlg/palettes/01.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/generic_building_1_frlg/palettes/02.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/generic_building_1_frlg/palettes/03.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/generic_building_1_frlg/palettes/04.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/generic_building_1_frlg/palettes/05.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/generic_building_1_frlg/palettes/06.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/generic_building_1_frlg/palettes/07.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/generic_building_1_frlg/palettes/08.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/generic_building_1_frlg/palettes/09.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/generic_building_1_frlg/palettes/10.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/generic_building_1_frlg/palettes/11.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/generic_building_1_frlg/palettes/12.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/generic_building_1_frlg/palettes/13.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/generic_building_1_frlg/palettes/14.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/generic_building_1_frlg/palettes/15.pal", ".gbapal"),
};

const u16 gTilesetPalettes_Lab_Frlg[][16] =
{
    INCGFX_U16("data/tilesets/secondary/lab_frlg/palettes/00.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/lab_frlg/palettes/01.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/lab_frlg/palettes/02.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/lab_frlg/palettes/03.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/lab_frlg/palettes/04.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/lab_frlg/palettes/05.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/lab_frlg/palettes/06.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/lab_frlg/palettes/07.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/lab_frlg/palettes/08.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/lab_frlg/palettes/09.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/lab_frlg/palettes/10.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/lab_frlg/palettes/11.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/lab_frlg/palettes/12.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/lab_frlg/palettes/13.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/lab_frlg/palettes/14.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/lab_frlg/palettes/15.pal", ".gbapal"),
};

const u16 gTilesetPalettes_PalletTown[][16] =
{
    INCGFX_U16("data/tilesets/secondary/pallet_town_frlg/palettes/00.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pallet_town_frlg/palettes/01.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pallet_town_frlg/palettes/02.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pallet_town_frlg/palettes/03.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pallet_town_frlg/palettes/04.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pallet_town_frlg/palettes/05.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pallet_town_frlg/palettes/06.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pallet_town_frlg/palettes/07.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pallet_town_frlg/palettes/08.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pallet_town_frlg/palettes/09.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pallet_town_frlg/palettes/10.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pallet_town_frlg/palettes/11.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pallet_town_frlg/palettes/12.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pallet_town_frlg/palettes/13.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pallet_town_frlg/palettes/14.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pallet_town_frlg/palettes/15.pal", ".gbapal"),
};

const u16 gTilesetPalettes_ViridianCity[][16] =
{
    INCGFX_U16("data/tilesets/secondary/viridian_city_frlg/palettes/00.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/viridian_city_frlg/palettes/01.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/viridian_city_frlg/palettes/02.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/viridian_city_frlg/palettes/03.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/viridian_city_frlg/palettes/04.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/viridian_city_frlg/palettes/05.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/viridian_city_frlg/palettes/06.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/viridian_city_frlg/palettes/07.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/viridian_city_frlg/palettes/08.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/viridian_city_frlg/palettes/09.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/viridian_city_frlg/palettes/10.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/viridian_city_frlg/palettes/11.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/viridian_city_frlg/palettes/12.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/viridian_city_frlg/palettes/13.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/viridian_city_frlg/palettes/14.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/viridian_city_frlg/palettes/15.pal", ".gbapal"),
};

const u32 gTilesetTiles_Building_Frlg[] = INCGFX_U32("data/tilesets/primary/building_frlg/tiles.png", ".4bpp.smol");

const u32 gTilesetTiles_General_Frlg[] = INCGFX_U32("data/tilesets/primary/general_frlg/tiles.png", ".4bpp.smol");

const u32 gTilesetTiles_GenericBuilding1[] = INCGFX_U32("data/tilesets/secondary/generic_building_1_frlg/tiles.png", ".4bpp.fastSmol");

const u32 gTilesetTiles_Lab_Frlg[] = INCGFX_U32("data/tilesets/secondary/lab_frlg/tiles.png", ".4bpp.fastSmol");

const u32 gTilesetTiles_PalletTown[] = INCGFX_U32("data/tilesets/secondary/pallet_town_frlg/tiles.png", ".4bpp.fastSmol");

const u32 gTilesetTiles_ViridianCity[] = INCGFX_U32("data/tilesets/secondary/viridian_city_frlg/tiles.png", ".4bpp.fastSmol");

const struct Tileset gTileset_BuildingFrlg =
{
    .isCompressed = TRUE,
    .isSecondary = FALSE,
    .tiles = gTilesetTiles_Building_Frlg,
    .palettes = gTilesetPalettes_Building_Frlg,
    .metatiles = gMetatiles_Building_Frlg,
    .metatileAttributes = gMetatileAttributes_Building_Frlg,
    .callback = NULL,
};

const struct Tileset gTileset_GenericBuilding1 =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_GenericBuilding1,
    .palettes = gTilesetPalettes_GenericBuilding1,
    .metatiles = gMetatiles_GenericBuilding1,
    .metatileAttributes = gMetatileAttributes_GenericBuilding1,
    .callback = NULL,
};

const struct Tileset gTileset_Lab_Frlg =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Lab_Frlg,
    .palettes = gTilesetPalettes_Lab_Frlg,
    .metatiles = gMetatiles_Lab_Frlg,
    .metatileAttributes = gMetatileAttributes_Lab_Frlg,
    .callback = NULL,
};

const struct Tileset gTileset_General_Frlg =
{
    .isCompressed = TRUE,
    .isSecondary = FALSE,
    .tiles = gTilesetTiles_General_Frlg,
    .palettes = gTilesetPalettes_General_Frlg,
    .metatiles = gMetatiles_General_Frlg,
    .metatileAttributes = gMetatileAttributes_General_Frlg,
    .callback = InitTilesetAnim_General_Frlg,
};

const struct Tileset gTileset_PalletTown =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_PalletTown,
    .palettes = gTilesetPalettes_PalletTown,
    .metatiles = gMetatiles_PalletTown,
    .metatileAttributes = gMetatileAttributes_PalletTown,
    .callback = NULL,
};

const struct Tileset gTileset_ViridianCity =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_ViridianCity,
    .palettes = gTilesetPalettes_ViridianCity,
    .metatiles = gMetatiles_ViridianCity,
    .metatileAttributes = gMetatileAttributes_ViridianCity,
    .callback = NULL,
};

const u32 gTilesetTiles_PokemonCenter_Frlg[] = INCGFX_U32("data/tilesets/secondary/pokemon_center_frlg/tiles.png", ".4bpp.fastSmol");

const u16 gTilesetPalettes_PokemonCenter_Frlg[][16] =
{
    INCGFX_U16("data/tilesets/secondary/pokemon_center_frlg/palettes/00.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pokemon_center_frlg/palettes/01.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pokemon_center_frlg/palettes/02.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pokemon_center_frlg/palettes/03.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pokemon_center_frlg/palettes/04.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pokemon_center_frlg/palettes/05.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pokemon_center_frlg/palettes/06.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pokemon_center_frlg/palettes/07.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pokemon_center_frlg/palettes/08.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pokemon_center_frlg/palettes/09.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pokemon_center_frlg/palettes/10.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pokemon_center_frlg/palettes/11.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pokemon_center_frlg/palettes/12.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pokemon_center_frlg/palettes/13.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pokemon_center_frlg/palettes/14.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pokemon_center_frlg/palettes/15.pal", ".gbapal"),
};

const u16 gMetatiles_PokemonCenter_Frlg[] = INCBIN_U16("data/tilesets/secondary/pokemon_center_frlg/metatiles.bin");

const u16 gMetatileAttributes_PokemonCenter_Frlg[] = INCBIN_U16("data/tilesets/secondary/pokemon_center_frlg/metatile_attributes.bin");

const struct Tileset gTileset_PokemonCenterFrlg =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_PokemonCenter_Frlg,
    .palettes = gTilesetPalettes_PokemonCenter_Frlg,
    .metatiles = gMetatiles_PokemonCenter_Frlg,
    .metatileAttributes = gMetatileAttributes_PokemonCenter_Frlg,
    .callback = NULL,
};

const u32 gTilesetTiles_Mart[] = INCGFX_U32("data/tilesets/secondary/mart_frlg/tiles.png", ".4bpp.fastSmol");

const u16 gTilesetPalettes_Mart[][16] =
{
    INCGFX_U16("data/tilesets/secondary/mart_frlg/palettes/00.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/mart_frlg/palettes/01.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/mart_frlg/palettes/02.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/mart_frlg/palettes/03.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/mart_frlg/palettes/04.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/mart_frlg/palettes/05.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/mart_frlg/palettes/06.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/mart_frlg/palettes/07.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/mart_frlg/palettes/08.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/mart_frlg/palettes/09.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/mart_frlg/palettes/10.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/mart_frlg/palettes/11.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/mart_frlg/palettes/12.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/mart_frlg/palettes/13.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/mart_frlg/palettes/14.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/mart_frlg/palettes/15.pal", ".gbapal"),
};

const u16 gMetatiles_Mart[] = INCBIN_U16("data/tilesets/secondary/mart_frlg/metatiles.bin");

const u16 gMetatileAttributes_Mart[] = INCBIN_U16("data/tilesets/secondary/mart_frlg/metatile_attributes.bin");

const struct Tileset gTileset_Mart =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Mart,
    .palettes = gTilesetPalettes_Mart,
    .metatiles = gMetatiles_Mart,
    .metatileAttributes = gMetatileAttributes_Mart,
    .callback = NULL,
};

const u32 gTilesetTiles_PewterGym[] = INCGFX_U32("data/tilesets/secondary/pewter_gym_frlg/tiles.png", ".4bpp.fastSmol");

const u16 gTilesetPalettes_PewterGym[][16] =
{
    INCGFX_U16("data/tilesets/secondary/pewter_gym_frlg/palettes/00.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pewter_gym_frlg/palettes/01.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pewter_gym_frlg/palettes/02.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pewter_gym_frlg/palettes/03.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pewter_gym_frlg/palettes/04.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pewter_gym_frlg/palettes/05.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pewter_gym_frlg/palettes/06.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pewter_gym_frlg/palettes/07.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pewter_gym_frlg/palettes/08.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pewter_gym_frlg/palettes/09.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pewter_gym_frlg/palettes/10.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pewter_gym_frlg/palettes/11.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pewter_gym_frlg/palettes/12.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pewter_gym_frlg/palettes/13.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pewter_gym_frlg/palettes/14.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pewter_gym_frlg/palettes/15.pal", ".gbapal"),
};

const u16 gMetatiles_PewterGym[] = INCBIN_U16("data/tilesets/secondary/pewter_gym_frlg/metatiles.bin");

const u16 gMetatileAttributes_PewterGym[] = INCBIN_U16("data/tilesets/secondary/pewter_gym_frlg/metatile_attributes.bin");

const struct Tileset gTileset_PewterGym =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_PewterGym,
    .palettes = gTilesetPalettes_PewterGym,
    .metatiles = gMetatiles_PewterGym,
    .metatileAttributes = gMetatileAttributes_PewterGym,
    .callback = NULL,
};

const u32 gTilesetTiles_PewterCity[] = INCGFX_U32("data/tilesets/secondary/pewter_city_frlg/tiles.png", ".4bpp.fastSmol");

const u16 gTilesetPalettes_PewterCity[][16] =
{
    INCGFX_U16("data/tilesets/secondary/pewter_city_frlg/palettes/00.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pewter_city_frlg/palettes/01.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pewter_city_frlg/palettes/02.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pewter_city_frlg/palettes/03.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pewter_city_frlg/palettes/04.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pewter_city_frlg/palettes/05.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pewter_city_frlg/palettes/06.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pewter_city_frlg/palettes/07.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pewter_city_frlg/palettes/08.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pewter_city_frlg/palettes/09.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pewter_city_frlg/palettes/10.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pewter_city_frlg/palettes/11.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pewter_city_frlg/palettes/12.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pewter_city_frlg/palettes/13.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pewter_city_frlg/palettes/14.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pewter_city_frlg/palettes/15.pal", ".gbapal"),
};

const u16 gMetatiles_PewterCity[] = INCBIN_U16("data/tilesets/secondary/pewter_city_frlg/metatiles.bin");

const u16 gMetatileAttributes_PewterCity[] = INCBIN_U16("data/tilesets/secondary/pewter_city_frlg/metatile_attributes.bin");

const struct Tileset gTileset_PewterCity =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_PewterCity,
    .palettes = gTilesetPalettes_PewterCity,
    .metatiles = gMetatiles_PewterCity,
    .metatileAttributes = gMetatileAttributes_PewterCity,
    .callback = NULL,
};

const u32 gTilesetTiles_ViridianForest[] = INCGFX_U32("data/tilesets/secondary/viridian_forest_frlg/tiles.png", ".4bpp.fastSmol");

const u16 gTilesetPalettes_ViridianForest[][16] =
{
    INCGFX_U16("data/tilesets/secondary/viridian_forest_frlg/palettes/00.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/viridian_forest_frlg/palettes/01.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/viridian_forest_frlg/palettes/02.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/viridian_forest_frlg/palettes/03.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/viridian_forest_frlg/palettes/04.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/viridian_forest_frlg/palettes/05.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/viridian_forest_frlg/palettes/06.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/viridian_forest_frlg/palettes/07.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/viridian_forest_frlg/palettes/08.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/viridian_forest_frlg/palettes/09.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/viridian_forest_frlg/palettes/10.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/viridian_forest_frlg/palettes/11.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/viridian_forest_frlg/palettes/12.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/viridian_forest_frlg/palettes/13.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/viridian_forest_frlg/palettes/14.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/viridian_forest_frlg/palettes/15.pal", ".gbapal"),
};

const u16 gMetatiles_ViridianForest[] = INCBIN_U16("data/tilesets/secondary/viridian_forest_frlg/metatiles.bin");

const u16 gMetatileAttributes_ViridianForest[] = INCBIN_U16("data/tilesets/secondary/viridian_forest_frlg/metatile_attributes.bin");

const struct Tileset gTileset_ViridianForest =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_ViridianForest,
    .palettes = gTilesetPalettes_ViridianForest,
    .metatiles = gMetatiles_ViridianForest,
    .metatileAttributes = gMetatileAttributes_ViridianForest,
    .callback = NULL,
};

const u32 gTilesetTiles_GenericBuilding2[] = INCGFX_U32("data/tilesets/secondary/generic_building_2_frlg/tiles.png", ".4bpp.fastSmol");

const u16 gTilesetPalettes_GenericBuilding2[][16] =
{
    INCGFX_U16("data/tilesets/secondary/generic_building_2_frlg/palettes/00.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/generic_building_2_frlg/palettes/01.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/generic_building_2_frlg/palettes/02.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/generic_building_2_frlg/palettes/03.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/generic_building_2_frlg/palettes/04.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/generic_building_2_frlg/palettes/05.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/generic_building_2_frlg/palettes/06.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/generic_building_2_frlg/palettes/07.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/generic_building_2_frlg/palettes/08.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/generic_building_2_frlg/palettes/09.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/generic_building_2_frlg/palettes/10.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/generic_building_2_frlg/palettes/11.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/generic_building_2_frlg/palettes/12.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/generic_building_2_frlg/palettes/13.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/generic_building_2_frlg/palettes/14.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/generic_building_2_frlg/palettes/15.pal", ".gbapal"),
};

const u16 gMetatiles_GenericBuilding2[] = INCBIN_U16("data/tilesets/secondary/generic_building_2_frlg/metatiles.bin");

const u16 gMetatileAttributes_GenericBuilding2[] = INCBIN_U16("data/tilesets/secondary/generic_building_2_frlg/metatile_attributes.bin");

const struct Tileset gTileset_GenericBuilding2 =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_GenericBuilding2,
    .palettes = gTilesetPalettes_GenericBuilding2,
    .metatiles = gMetatiles_GenericBuilding2,
    .metatileAttributes = gMetatileAttributes_GenericBuilding2,
    .callback = NULL,
};

const u32 gTilesetTiles_CeruleanCity[] = INCGFX_U32("data/tilesets/secondary/cerulean_city_frlg/tiles.png", ".4bpp.fastSmol");

const u16 gTilesetPalettes_CeruleanCity[][16] =
{
    INCGFX_U16("data/tilesets/secondary/cerulean_city_frlg/palettes/00.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/cerulean_city_frlg/palettes/01.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/cerulean_city_frlg/palettes/02.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/cerulean_city_frlg/palettes/03.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/cerulean_city_frlg/palettes/04.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/cerulean_city_frlg/palettes/05.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/cerulean_city_frlg/palettes/06.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/cerulean_city_frlg/palettes/07.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/cerulean_city_frlg/palettes/08.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/cerulean_city_frlg/palettes/09.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/cerulean_city_frlg/palettes/10.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/cerulean_city_frlg/palettes/11.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/cerulean_city_frlg/palettes/12.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/cerulean_city_frlg/palettes/13.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/cerulean_city_frlg/palettes/14.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/cerulean_city_frlg/palettes/15.pal", ".gbapal"),
};

const u16 gMetatiles_CeruleanCity[] = INCBIN_U16("data/tilesets/secondary/cerulean_city_frlg/metatiles.bin");

const u16 gMetatileAttributes_CeruleanCity[] = INCBIN_U16("data/tilesets/secondary/cerulean_city_frlg/metatile_attributes.bin");

const struct Tileset gTileset_CeruleanCity =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_CeruleanCity,
    .palettes = gTilesetPalettes_CeruleanCity,
    .metatiles = gMetatiles_CeruleanCity,
    .metatileAttributes = gMetatileAttributes_CeruleanCity,
    .callback = NULL,
};

const u32 gTilesetTiles_Cave_Frlg[] = INCGFX_U32("data/tilesets/secondary/cave_frlg/tiles.png", ".4bpp.fastSmol");

const u16 gTilesetPalettes_Cave_Frlg[][16] =
{
    INCGFX_U16("data/tilesets/secondary/cave_frlg/palettes/00.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/cave_frlg/palettes/01.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/cave_frlg/palettes/02.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/cave_frlg/palettes/03.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/cave_frlg/palettes/04.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/cave_frlg/palettes/05.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/cave_frlg/palettes/06.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/cave_frlg/palettes/07.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/cave_frlg/palettes/08.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/cave_frlg/palettes/09.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/cave_frlg/palettes/10.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/cave_frlg/palettes/11.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/cave_frlg/palettes/12.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/cave_frlg/palettes/13.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/cave_frlg/palettes/14.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/cave_frlg/palettes/15.pal", ".gbapal"),
};

const u16 gMetatiles_Cave_Frlg[] = INCBIN_U16("data/tilesets/secondary/cave_frlg/metatiles.bin");

const u16 gMetatileAttributes_Cave_Frlg[] = INCBIN_U16("data/tilesets/secondary/cave_frlg/metatile_attributes.bin");

const struct Tileset gTileset_Cave_Frlg =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Cave_Frlg,
    .palettes = gTilesetPalettes_Cave_Frlg,
    .metatiles = gMetatiles_Cave_Frlg,
    .metatileAttributes = gMetatileAttributes_Cave_Frlg,
    .callback = NULL,
};

const u32 gTilesetTiles_CeruleanGym[] = INCGFX_U32("data/tilesets/secondary/cerulean_gym_frlg/tiles.png", ".4bpp.fastSmol");

const u16 gTilesetPalettes_CeruleanGym[][16] =
{
    INCGFX_U16("data/tilesets/secondary/cerulean_gym_frlg/palettes/00.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/cerulean_gym_frlg/palettes/01.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/cerulean_gym_frlg/palettes/02.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/cerulean_gym_frlg/palettes/03.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/cerulean_gym_frlg/palettes/04.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/cerulean_gym_frlg/palettes/05.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/cerulean_gym_frlg/palettes/06.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/cerulean_gym_frlg/palettes/07.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/cerulean_gym_frlg/palettes/08.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/cerulean_gym_frlg/palettes/09.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/cerulean_gym_frlg/palettes/10.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/cerulean_gym_frlg/palettes/11.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/cerulean_gym_frlg/palettes/12.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/cerulean_gym_frlg/palettes/13.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/cerulean_gym_frlg/palettes/14.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/cerulean_gym_frlg/palettes/15.pal", ".gbapal"),
};

const u16 gMetatiles_CeruleanGym[] = INCBIN_U16("data/tilesets/secondary/cerulean_gym_frlg/metatiles.bin");

const u16 gMetatileAttributes_CeruleanGym[] = INCBIN_U16("data/tilesets/secondary/cerulean_gym_frlg/metatile_attributes.bin");

const struct Tileset gTileset_CeruleanGym =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_CeruleanGym,
    .palettes = gTilesetPalettes_CeruleanGym,
    .metatiles = gMetatiles_CeruleanGym,
    .metatileAttributes = gMetatileAttributes_CeruleanGym,
    .callback = NULL,
};

const u32 gTilesetTiles_BurgledHouse[] = INCGFX_U32("data/tilesets/secondary/burgled_house_frlg/tiles.png", ".4bpp.fastSmol");

const u16 gTilesetPalettes_BurgledHouse[][16] =
{
    INCGFX_U16("data/tilesets/secondary/burgled_house_frlg/palettes/00.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/burgled_house_frlg/palettes/01.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/burgled_house_frlg/palettes/02.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/burgled_house_frlg/palettes/03.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/burgled_house_frlg/palettes/04.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/burgled_house_frlg/palettes/05.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/burgled_house_frlg/palettes/06.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/burgled_house_frlg/palettes/07.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/burgled_house_frlg/palettes/08.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/burgled_house_frlg/palettes/09.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/burgled_house_frlg/palettes/10.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/burgled_house_frlg/palettes/11.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/burgled_house_frlg/palettes/12.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/burgled_house_frlg/palettes/13.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/burgled_house_frlg/palettes/14.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/burgled_house_frlg/palettes/15.pal", ".gbapal"),
};

const u16 gMetatiles_BurgledHouse[] = INCBIN_U16("data/tilesets/secondary/burgled_house_frlg/metatiles.bin");

const u16 gMetatileAttributes_BurgledHouse[] = INCBIN_U16("data/tilesets/secondary/burgled_house_frlg/metatile_attributes.bin");

const struct Tileset gTileset_BurgledHouse =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_BurgledHouse,
    .palettes = gTilesetPalettes_BurgledHouse,
    .metatiles = gMetatiles_BurgledHouse,
    .metatileAttributes = gMetatileAttributes_BurgledHouse,
    .callback = NULL,
};

const u32 gTilesetTiles_BikeShop_Frlg[] = INCGFX_U32("data/tilesets/secondary/bike_shop_frlg/tiles.png", ".4bpp.fastSmol");

const u16 gTilesetPalettes_BikeShop_Frlg[][16] =
{
    INCGFX_U16("data/tilesets/secondary/bike_shop_frlg/palettes/00.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/bike_shop_frlg/palettes/01.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/bike_shop_frlg/palettes/02.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/bike_shop_frlg/palettes/03.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/bike_shop_frlg/palettes/04.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/bike_shop_frlg/palettes/05.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/bike_shop_frlg/palettes/06.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/bike_shop_frlg/palettes/07.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/bike_shop_frlg/palettes/08.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/bike_shop_frlg/palettes/09.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/bike_shop_frlg/palettes/10.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/bike_shop_frlg/palettes/11.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/bike_shop_frlg/palettes/12.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/bike_shop_frlg/palettes/13.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/bike_shop_frlg/palettes/14.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/bike_shop_frlg/palettes/15.pal", ".gbapal"),
};

const u16 gMetatiles_BikeShop_Frlg[] = INCBIN_U16("data/tilesets/secondary/bike_shop_frlg/metatiles.bin");

const u16 gMetatileAttributes_BikeShop_Frlg[] = INCBIN_U16("data/tilesets/secondary/bike_shop_frlg/metatile_attributes.bin");

const struct Tileset gTileset_BikeShop_Frlg =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_BikeShop_Frlg,
    .palettes = gTilesetPalettes_BikeShop_Frlg,
    .metatiles = gMetatiles_BikeShop_Frlg,
    .metatileAttributes = gMetatileAttributes_BikeShop_Frlg,
    .callback = NULL,
};

const u32 gTilesetTiles_School[] = INCGFX_U32("data/tilesets/secondary/school_frlg/tiles.png", ".4bpp.fastSmol");

const u16 gTilesetPalettes_School[][16] =
{
    INCGFX_U16("data/tilesets/secondary/school_frlg/palettes/00.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/school_frlg/palettes/01.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/school_frlg/palettes/02.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/school_frlg/palettes/03.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/school_frlg/palettes/04.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/school_frlg/palettes/05.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/school_frlg/palettes/06.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/school_frlg/palettes/07.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/school_frlg/palettes/08.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/school_frlg/palettes/09.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/school_frlg/palettes/10.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/school_frlg/palettes/11.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/school_frlg/palettes/12.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/school_frlg/palettes/13.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/school_frlg/palettes/14.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/school_frlg/palettes/15.pal", ".gbapal"),
};

const u16 gMetatiles_School[] = INCBIN_U16("data/tilesets/secondary/school_frlg/metatiles.bin");

const u16 gMetatileAttributes_School[] = INCBIN_U16("data/tilesets/secondary/school_frlg/metatile_attributes.bin");

const struct Tileset gTileset_School =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_School,
    .palettes = gTilesetPalettes_School,
    .metatiles = gMetatiles_School,
    .metatileAttributes = gMetatileAttributes_School,
    .callback = NULL,
};

const u32 gTilesetTiles_ViridianGym[] = INCGFX_U32("data/tilesets/secondary/viridian_gym_frlg/tiles.png", ".4bpp.fastSmol");

const u16 gTilesetPalettes_ViridianGym[][16] =
{
    INCGFX_U16("data/tilesets/secondary/viridian_gym_frlg/palettes/00.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/viridian_gym_frlg/palettes/01.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/viridian_gym_frlg/palettes/02.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/viridian_gym_frlg/palettes/03.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/viridian_gym_frlg/palettes/04.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/viridian_gym_frlg/palettes/05.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/viridian_gym_frlg/palettes/06.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/viridian_gym_frlg/palettes/07.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/viridian_gym_frlg/palettes/08.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/viridian_gym_frlg/palettes/09.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/viridian_gym_frlg/palettes/10.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/viridian_gym_frlg/palettes/11.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/viridian_gym_frlg/palettes/12.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/viridian_gym_frlg/palettes/13.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/viridian_gym_frlg/palettes/14.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/viridian_gym_frlg/palettes/15.pal", ".gbapal"),
};

const u16 gMetatiles_ViridianGym[] = INCBIN_U16("data/tilesets/secondary/viridian_gym_frlg/metatiles.bin");

const u16 gMetatileAttributes_ViridianGym[] = INCBIN_U16("data/tilesets/secondary/viridian_gym_frlg/metatile_attributes.bin");

const struct Tileset gTileset_ViridianGym =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_ViridianGym,
    .palettes = gTilesetPalettes_ViridianGym,
    .metatiles = gMetatiles_ViridianGym,
    .metatileAttributes = gMetatileAttributes_ViridianGym,
    .callback = NULL,
};

const u32 gTilesetTiles_Museum[] = INCGFX_U32("data/tilesets/secondary/museum_frlg/tiles.png", ".4bpp.fastSmol");

const u16 gTilesetPalettes_Museum[][16] =
{
    INCGFX_U16("data/tilesets/secondary/museum_frlg/palettes/00.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/museum_frlg/palettes/01.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/museum_frlg/palettes/02.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/museum_frlg/palettes/03.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/museum_frlg/palettes/04.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/museum_frlg/palettes/05.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/museum_frlg/palettes/06.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/museum_frlg/palettes/07.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/museum_frlg/palettes/08.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/museum_frlg/palettes/09.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/museum_frlg/palettes/10.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/museum_frlg/palettes/11.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/museum_frlg/palettes/12.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/museum_frlg/palettes/13.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/museum_frlg/palettes/14.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/museum_frlg/palettes/15.pal", ".gbapal"),
};

const u16 gMetatiles_Museum[] = INCBIN_U16("data/tilesets/secondary/museum_frlg/metatiles.bin");

const u16 gMetatileAttributes_Museum[] = INCBIN_U16("data/tilesets/secondary/museum_frlg/metatile_attributes.bin");

const struct Tileset gTileset_Museum =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Museum,
    .palettes = gTilesetPalettes_Museum,
    .metatiles = gMetatiles_Museum,
    .metatileAttributes = gMetatileAttributes_Museum,
    .callback = NULL,
};

const u32 gTilesetTiles_SeaCottage[] = INCGFX_U32("data/tilesets/secondary/sea_cottage_frlg/tiles.png", ".4bpp.fastSmol");



const u16 gTilesetPalettes_SeaCottage[][16] =
{
    INCGFX_U16("data/tilesets/secondary/sea_cottage_frlg/palettes/00.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/sea_cottage_frlg/palettes/01.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/sea_cottage_frlg/palettes/02.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/sea_cottage_frlg/palettes/03.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/sea_cottage_frlg/palettes/04.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/sea_cottage_frlg/palettes/05.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/sea_cottage_frlg/palettes/06.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/sea_cottage_frlg/palettes/07.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/sea_cottage_frlg/palettes/08.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/sea_cottage_frlg/palettes/09.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/sea_cottage_frlg/palettes/10.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/sea_cottage_frlg/palettes/11.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/sea_cottage_frlg/palettes/12.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/sea_cottage_frlg/palettes/13.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/sea_cottage_frlg/palettes/14.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/sea_cottage_frlg/palettes/15.pal", ".gbapal"),
};



const u16 gMetatiles_SeaCottage[] = INCBIN_U16("data/tilesets/secondary/sea_cottage_frlg/metatiles.bin");


const u16 gMetatileAttributes_SeaCottage[] = INCBIN_U16("data/tilesets/secondary/sea_cottage_frlg/metatile_attributes.bin");



const struct Tileset gTileset_SeaCottage =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_SeaCottage,
    .palettes = gTilesetPalettes_SeaCottage,
    .metatiles = gMetatiles_SeaCottage,
    .metatileAttributes = gMetatileAttributes_SeaCottage,
    .callback = NULL,
};

const u32 gTilesetTiles_FanClubDaycare[] = INCGFX_U32("data/tilesets/secondary/fan_club_daycare_frlg/tiles.png", ".4bpp.fastSmol");



const u16 gTilesetPalettes_FanClubDaycare[][16] =
{
    INCGFX_U16("data/tilesets/secondary/fan_club_daycare_frlg/palettes/00.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/fan_club_daycare_frlg/palettes/01.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/fan_club_daycare_frlg/palettes/02.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/fan_club_daycare_frlg/palettes/03.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/fan_club_daycare_frlg/palettes/04.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/fan_club_daycare_frlg/palettes/05.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/fan_club_daycare_frlg/palettes/06.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/fan_club_daycare_frlg/palettes/07.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/fan_club_daycare_frlg/palettes/08.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/fan_club_daycare_frlg/palettes/09.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/fan_club_daycare_frlg/palettes/10.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/fan_club_daycare_frlg/palettes/11.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/fan_club_daycare_frlg/palettes/12.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/fan_club_daycare_frlg/palettes/13.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/fan_club_daycare_frlg/palettes/14.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/fan_club_daycare_frlg/palettes/15.pal", ".gbapal"),
};



const u16 gMetatiles_FanClubDaycare[] = INCBIN_U16("data/tilesets/secondary/fan_club_daycare_frlg/metatiles.bin");


const u16 gMetatileAttributes_FanClubDaycare[] = INCBIN_U16("data/tilesets/secondary/fan_club_daycare_frlg/metatile_attributes.bin");



const struct Tileset gTileset_FanClubDaycare =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_FanClubDaycare,
    .palettes = gTilesetPalettes_FanClubDaycare,
    .metatiles = gMetatiles_FanClubDaycare,
    .metatileAttributes = gMetatileAttributes_FanClubDaycare,
    .callback = NULL,
};

const u32 gTilesetTiles_SSAnne[] = INCGFX_U32("data/tilesets/secondary/ss_anne_frlg/tiles.png", ".4bpp.fastSmol");



const u16 gTilesetPalettes_SSAnne[][16] =
{
    INCGFX_U16("data/tilesets/secondary/ss_anne_frlg/palettes/00.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/ss_anne_frlg/palettes/01.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/ss_anne_frlg/palettes/02.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/ss_anne_frlg/palettes/03.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/ss_anne_frlg/palettes/04.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/ss_anne_frlg/palettes/05.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/ss_anne_frlg/palettes/06.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/ss_anne_frlg/palettes/07.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/ss_anne_frlg/palettes/08.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/ss_anne_frlg/palettes/09.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/ss_anne_frlg/palettes/10.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/ss_anne_frlg/palettes/11.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/ss_anne_frlg/palettes/12.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/ss_anne_frlg/palettes/13.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/ss_anne_frlg/palettes/14.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/ss_anne_frlg/palettes/15.pal", ".gbapal"),
};



const u16 gMetatiles_SSAnne[] = INCBIN_U16("data/tilesets/secondary/ss_anne_frlg/metatiles.bin");


const u16 gMetatileAttributes_SSAnne[] = INCBIN_U16("data/tilesets/secondary/ss_anne_frlg/metatile_attributes.bin");



const struct Tileset gTileset_SSAnne =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_SSAnne,
    .palettes = gTilesetPalettes_SSAnne,
    .metatiles = gMetatiles_SSAnne,
    .metatileAttributes = gMetatileAttributes_SSAnne,
    .callback = NULL,
};

const u32 gTilesetTiles_UndergroundPath[] = INCGFX_U32("data/tilesets/secondary/underground_path_frlg/tiles.png", ".4bpp.fastSmol");



const u16 gTilesetPalettes_UndergroundPath[][16] =
{
    INCGFX_U16("data/tilesets/secondary/underground_path_frlg/palettes/00.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/underground_path_frlg/palettes/01.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/underground_path_frlg/palettes/02.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/underground_path_frlg/palettes/03.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/underground_path_frlg/palettes/04.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/underground_path_frlg/palettes/05.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/underground_path_frlg/palettes/06.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/underground_path_frlg/palettes/07.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/underground_path_frlg/palettes/08.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/underground_path_frlg/palettes/09.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/underground_path_frlg/palettes/10.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/underground_path_frlg/palettes/11.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/underground_path_frlg/palettes/12.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/underground_path_frlg/palettes/13.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/underground_path_frlg/palettes/14.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/underground_path_frlg/palettes/15.pal", ".gbapal"),
};



const u16 gMetatiles_UndergroundPath[] = INCBIN_U16("data/tilesets/secondary/underground_path_frlg/metatiles.bin");


const u16 gMetatileAttributes_UndergroundPath[] = INCBIN_U16("data/tilesets/secondary/underground_path_frlg/metatile_attributes.bin");



const struct Tileset gTileset_UndergroundPath =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_UndergroundPath,
    .palettes = gTilesetPalettes_UndergroundPath,
    .metatiles = gMetatiles_UndergroundPath,
    .metatileAttributes = gMetatileAttributes_UndergroundPath,
    .callback = NULL,
};

const u32 gTilesetTiles_VermilionCity[] = INCGFX_U32("data/tilesets/secondary/vermilion_city_frlg/tiles.png", ".4bpp.fastSmol");



const u16 gTilesetPalettes_VermilionCity[][16] =
{
    INCGFX_U16("data/tilesets/secondary/vermilion_city_frlg/palettes/00.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/vermilion_city_frlg/palettes/01.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/vermilion_city_frlg/palettes/02.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/vermilion_city_frlg/palettes/03.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/vermilion_city_frlg/palettes/04.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/vermilion_city_frlg/palettes/05.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/vermilion_city_frlg/palettes/06.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/vermilion_city_frlg/palettes/07.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/vermilion_city_frlg/palettes/08.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/vermilion_city_frlg/palettes/09.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/vermilion_city_frlg/palettes/10.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/vermilion_city_frlg/palettes/11.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/vermilion_city_frlg/palettes/12.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/vermilion_city_frlg/palettes/13.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/vermilion_city_frlg/palettes/14.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/vermilion_city_frlg/palettes/15.pal", ".gbapal"),
};



const u16 gMetatiles_VermilionCity[] = INCBIN_U16("data/tilesets/secondary/vermilion_city_frlg/metatiles.bin");


const u16 gMetatileAttributes_VermilionCity[] = INCBIN_U16("data/tilesets/secondary/vermilion_city_frlg/metatile_attributes.bin");



const struct Tileset gTileset_VermilionCity =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_VermilionCity,
    .palettes = gTilesetPalettes_VermilionCity,
    .metatiles = gMetatiles_VermilionCity,
    .metatileAttributes = gMetatileAttributes_VermilionCity,
    .callback = NULL,
};

const u32 gTilesetTiles_VermilionGym[] = INCGFX_U32("data/tilesets/secondary/vermilion_gym_frlg/tiles.png", ".4bpp.fastSmol");



const u16 gTilesetPalettes_VermilionGym[][16] =
{
    INCGFX_U16("data/tilesets/secondary/vermilion_gym_frlg/palettes/00.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/vermilion_gym_frlg/palettes/01.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/vermilion_gym_frlg/palettes/02.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/vermilion_gym_frlg/palettes/03.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/vermilion_gym_frlg/palettes/04.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/vermilion_gym_frlg/palettes/05.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/vermilion_gym_frlg/palettes/06.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/vermilion_gym_frlg/palettes/07.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/vermilion_gym_frlg/palettes/08.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/vermilion_gym_frlg/palettes/09.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/vermilion_gym_frlg/palettes/10.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/vermilion_gym_frlg/palettes/11.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/vermilion_gym_frlg/palettes/12.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/vermilion_gym_frlg/palettes/13.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/vermilion_gym_frlg/palettes/14.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/vermilion_gym_frlg/palettes/15.pal", ".gbapal"),
};



const u16 gMetatiles_VermilionGym[] = INCBIN_U16("data/tilesets/secondary/vermilion_gym_frlg/metatiles.bin");


const u16 gMetatileAttributes_VermilionGym[] = INCBIN_U16("data/tilesets/secondary/vermilion_gym_frlg/metatile_attributes.bin");



const struct Tileset gTileset_VermilionGym =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_VermilionGym,
    .palettes = gTilesetPalettes_VermilionGym,
    .metatiles = gMetatiles_VermilionGym,
    .metatileAttributes = gMetatileAttributes_VermilionGym,
    .callback = InitTilesetAnim_VermilionGym,
};

// Native FRLG cave assets, selected only by Three Horizons.
const u32 gTilesetTiles_DiglettsCave[] = INCGFX_U32("data/tilesets/secondary/digletts_cave_frlg/tiles.png", ".4bpp.fastSmol");

const u16 gTilesetPalettes_DiglettsCave[][16] =
{
    INCGFX_U16("data/tilesets/secondary/digletts_cave_frlg/palettes/00.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/digletts_cave_frlg/palettes/01.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/digletts_cave_frlg/palettes/02.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/digletts_cave_frlg/palettes/03.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/digletts_cave_frlg/palettes/04.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/digletts_cave_frlg/palettes/05.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/digletts_cave_frlg/palettes/06.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/digletts_cave_frlg/palettes/07.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/digletts_cave_frlg/palettes/08.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/digletts_cave_frlg/palettes/09.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/digletts_cave_frlg/palettes/10.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/digletts_cave_frlg/palettes/11.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/digletts_cave_frlg/palettes/12.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/digletts_cave_frlg/palettes/13.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/digletts_cave_frlg/palettes/14.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/digletts_cave_frlg/palettes/15.pal", ".gbapal"),
};

const u16 gMetatiles_DiglettsCave[] = INCBIN_U16("data/tilesets/secondary/digletts_cave_frlg/metatiles.bin");

const u16 gMetatileAttributes_DiglettsCave[] = INCBIN_U16("data/tilesets/secondary/digletts_cave_frlg/metatile_attributes.bin");

const struct Tileset gTileset_DiglettsCave =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_DiglettsCave,
    .palettes = gTilesetPalettes_DiglettsCave,
    .metatiles = gMetatiles_DiglettsCave,
    .metatileAttributes = gMetatileAttributes_DiglettsCave,
    .callback = NULL,
};

const u32 gTilesetTiles_LavenderTown[] = INCGFX_U32("data/tilesets/secondary/lavender_town_frlg/tiles.png", ".4bpp.fastSmol");

const u16 gTilesetPalettes_LavenderTown[][16] =
{
    INCGFX_U16("data/tilesets/secondary/lavender_town_frlg/palettes/00.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/lavender_town_frlg/palettes/01.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/lavender_town_frlg/palettes/02.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/lavender_town_frlg/palettes/03.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/lavender_town_frlg/palettes/04.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/lavender_town_frlg/palettes/05.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/lavender_town_frlg/palettes/06.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/lavender_town_frlg/palettes/07.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/lavender_town_frlg/palettes/08.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/lavender_town_frlg/palettes/09.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/lavender_town_frlg/palettes/10.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/lavender_town_frlg/palettes/11.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/lavender_town_frlg/palettes/12.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/lavender_town_frlg/palettes/13.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/lavender_town_frlg/palettes/14.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/lavender_town_frlg/palettes/15.pal", ".gbapal"),
};

const u16 gMetatiles_LavenderTown[] = INCBIN_U16("data/tilesets/secondary/lavender_town_frlg/metatiles.bin");

const u16 gMetatileAttributes_LavenderTown[] = INCBIN_U16("data/tilesets/secondary/lavender_town_frlg/metatile_attributes.bin");

const struct Tileset gTileset_LavenderTown =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_LavenderTown,
    .palettes = gTilesetPalettes_LavenderTown,
    .metatiles = gMetatiles_LavenderTown,
    .metatileAttributes = gMetatileAttributes_LavenderTown,
    .callback = NULL,
};

const u32 gTilesetTiles_RockTunnel[] = INCGFX_U32("data/tilesets/secondary/rock_tunnel_frlg/tiles.png", ".4bpp.fastSmol");

const u16 gTilesetPalettes_RockTunnel[][16] =
{
    INCGFX_U16("data/tilesets/secondary/rock_tunnel_frlg/palettes/00.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/rock_tunnel_frlg/palettes/01.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/rock_tunnel_frlg/palettes/02.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/rock_tunnel_frlg/palettes/03.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/rock_tunnel_frlg/palettes/04.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/rock_tunnel_frlg/palettes/05.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/rock_tunnel_frlg/palettes/06.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/rock_tunnel_frlg/palettes/07.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/rock_tunnel_frlg/palettes/08.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/rock_tunnel_frlg/palettes/09.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/rock_tunnel_frlg/palettes/10.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/rock_tunnel_frlg/palettes/11.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/rock_tunnel_frlg/palettes/12.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/rock_tunnel_frlg/palettes/13.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/rock_tunnel_frlg/palettes/14.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/rock_tunnel_frlg/palettes/15.pal", ".gbapal"),
};

const u16 gMetatiles_RockTunnel[] = INCBIN_U16("data/tilesets/secondary/rock_tunnel_frlg/metatiles.bin");

const u16 gMetatileAttributes_RockTunnel[] = INCBIN_U16("data/tilesets/secondary/rock_tunnel_frlg/metatile_attributes.bin");

const struct Tileset gTileset_RockTunnel =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_RockTunnel,
    .palettes = gTilesetPalettes_RockTunnel,
    .metatiles = gMetatiles_RockTunnel,
    .metatileAttributes = gMetatileAttributes_RockTunnel,
    .callback = NULL,
};

const u32 gTilesetTiles_PokemonTower[] = INCGFX_U32("data/tilesets/secondary/pokemon_tower_frlg/tiles.png", ".4bpp.fastSmol");

const u16 gTilesetPalettes_PokemonTower[][16] =
{
    INCGFX_U16("data/tilesets/secondary/pokemon_tower_frlg/palettes/00.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pokemon_tower_frlg/palettes/01.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pokemon_tower_frlg/palettes/02.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pokemon_tower_frlg/palettes/03.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pokemon_tower_frlg/palettes/04.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pokemon_tower_frlg/palettes/05.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pokemon_tower_frlg/palettes/06.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pokemon_tower_frlg/palettes/07.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pokemon_tower_frlg/palettes/08.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pokemon_tower_frlg/palettes/09.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pokemon_tower_frlg/palettes/10.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pokemon_tower_frlg/palettes/11.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pokemon_tower_frlg/palettes/12.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pokemon_tower_frlg/palettes/13.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pokemon_tower_frlg/palettes/14.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/pokemon_tower_frlg/palettes/15.pal", ".gbapal"),
};

const u16 gMetatiles_PokemonTower[] = INCBIN_U16("data/tilesets/secondary/pokemon_tower_frlg/metatiles.bin");

const u16 gMetatileAttributes_PokemonTower[] = INCBIN_U16("data/tilesets/secondary/pokemon_tower_frlg/metatile_attributes.bin");

const struct Tileset gTileset_PokemonTower =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_PokemonTower,
    .palettes = gTilesetPalettes_PokemonTower,
    .metatiles = gMetatiles_PokemonTower,
    .metatileAttributes = gMetatileAttributes_PokemonTower,
    .callback = NULL,
};

const u32 gTilesetTiles_CeladonCity[] = INCGFX_U32("data/tilesets/secondary/celadon_city_frlg/tiles.png", ".4bpp.fastSmol");
const u16 gTilesetPalettes_CeladonCity[][16] = {
    INCGFX_U16("data/tilesets/secondary/celadon_city_frlg/palettes/00.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/celadon_city_frlg/palettes/01.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/celadon_city_frlg/palettes/02.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/celadon_city_frlg/palettes/03.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/celadon_city_frlg/palettes/04.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/celadon_city_frlg/palettes/05.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/celadon_city_frlg/palettes/06.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/celadon_city_frlg/palettes/07.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/celadon_city_frlg/palettes/08.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/celadon_city_frlg/palettes/09.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/celadon_city_frlg/palettes/10.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/celadon_city_frlg/palettes/11.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/celadon_city_frlg/palettes/12.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/celadon_city_frlg/palettes/13.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/celadon_city_frlg/palettes/14.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/celadon_city_frlg/palettes/15.pal", ".gbapal"),
};
const u16 gMetatiles_CeladonCity[] = INCBIN_U16("data/tilesets/secondary/celadon_city_frlg/metatiles.bin");
const u16 gMetatileAttributes_CeladonCity[] = INCBIN_U16("data/tilesets/secondary/celadon_city_frlg/metatile_attributes.bin");
const struct Tileset gTileset_CeladonCity =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_CeladonCity,
    .palettes = gTilesetPalettes_CeladonCity,
    .metatiles = gMetatiles_CeladonCity,
    .metatileAttributes = gMetatileAttributes_CeladonCity,
    .callback = InitTilesetAnim_CeladonCity,
};

const u32 gTilesetTiles_Condominiums[] = INCGFX_U32("data/tilesets/secondary/condominiums_frlg/tiles.png", ".4bpp.fastSmol");
const u16 gTilesetPalettes_Condominiums[][16] = {
    INCGFX_U16("data/tilesets/secondary/condominiums_frlg/palettes/00.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/condominiums_frlg/palettes/01.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/condominiums_frlg/palettes/02.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/condominiums_frlg/palettes/03.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/condominiums_frlg/palettes/04.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/condominiums_frlg/palettes/05.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/condominiums_frlg/palettes/06.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/condominiums_frlg/palettes/07.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/condominiums_frlg/palettes/08.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/condominiums_frlg/palettes/09.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/condominiums_frlg/palettes/10.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/condominiums_frlg/palettes/11.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/condominiums_frlg/palettes/12.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/condominiums_frlg/palettes/13.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/condominiums_frlg/palettes/14.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/condominiums_frlg/palettes/15.pal", ".gbapal"),
};
const u16 gMetatiles_Condominiums[] = INCBIN_U16("data/tilesets/secondary/condominiums_frlg/metatiles.bin");
const u16 gMetatileAttributes_Condominiums[] = INCBIN_U16("data/tilesets/secondary/condominiums_frlg/metatile_attributes.bin");
const struct Tileset gTileset_Condominiums =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Condominiums,
    .palettes = gTilesetPalettes_Condominiums,
    .metatiles = gMetatiles_Condominiums,
    .metatileAttributes = gMetatileAttributes_Condominiums,
    .callback = NULL,
};

const u32 gTilesetTiles_DepartmentStore[] = INCGFX_U32("data/tilesets/secondary/department_store_frlg/tiles.png", ".4bpp.fastSmol");
const u16 gTilesetPalettes_DepartmentStore[][16] = {
    INCGFX_U16("data/tilesets/secondary/department_store_frlg/palettes/00.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/department_store_frlg/palettes/01.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/department_store_frlg/palettes/02.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/department_store_frlg/palettes/03.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/department_store_frlg/palettes/04.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/department_store_frlg/palettes/05.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/department_store_frlg/palettes/06.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/department_store_frlg/palettes/07.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/department_store_frlg/palettes/08.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/department_store_frlg/palettes/09.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/department_store_frlg/palettes/10.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/department_store_frlg/palettes/11.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/department_store_frlg/palettes/12.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/department_store_frlg/palettes/13.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/department_store_frlg/palettes/14.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/department_store_frlg/palettes/15.pal", ".gbapal"),
};
const u16 gMetatiles_DepartmentStore[] = INCBIN_U16("data/tilesets/secondary/department_store_frlg/metatiles.bin");
const u16 gMetatileAttributes_DepartmentStore[] = INCBIN_U16("data/tilesets/secondary/department_store_frlg/metatile_attributes.bin");
const struct Tileset gTileset_DepartmentStore =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_DepartmentStore,
    .palettes = gTilesetPalettes_DepartmentStore,
    .metatiles = gMetatiles_DepartmentStore,
    .metatileAttributes = gMetatileAttributes_DepartmentStore,
    .callback = NULL,
};

const u16 gMetatiles_SilphCo[] = INCBIN_U16("data/tilesets/secondary/silph_co_frlg/metatiles.bin");
const u16 gMetatileAttributes_SilphCo[] = INCBIN_U16("data/tilesets/secondary/silph_co_frlg/metatile_attributes.bin");
const struct Tileset gTileset_SilphCo =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Condominiums,
    .palettes = gTilesetPalettes_Condominiums,
    .metatiles = gMetatiles_SilphCo,
    .metatileAttributes = gMetatileAttributes_SilphCo,
    .callback = InitTilesetAnim_SilphCo,
};

const u32 gTilesetTiles_GameCorner[] = INCGFX_U32("data/tilesets/secondary/game_corner_frlg/tiles.png", ".4bpp.fastSmol");
const u16 gTilesetPalettes_GameCorner[][16] = {
    INCGFX_U16("data/tilesets/secondary/game_corner_frlg/palettes/00.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/game_corner_frlg/palettes/01.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/game_corner_frlg/palettes/02.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/game_corner_frlg/palettes/03.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/game_corner_frlg/palettes/04.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/game_corner_frlg/palettes/05.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/game_corner_frlg/palettes/06.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/game_corner_frlg/palettes/07.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/game_corner_frlg/palettes/08.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/game_corner_frlg/palettes/09.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/game_corner_frlg/palettes/10.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/game_corner_frlg/palettes/11.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/game_corner_frlg/palettes/12.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/game_corner_frlg/palettes/13.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/game_corner_frlg/palettes/14.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/game_corner_frlg/palettes/15.pal", ".gbapal"),
};
const u16 gMetatiles_GameCorner[] = INCBIN_U16("data/tilesets/secondary/game_corner_frlg/metatiles.bin");
const u16 gMetatileAttributes_GameCorner[] = INCBIN_U16("data/tilesets/secondary/game_corner_frlg/metatile_attributes.bin");
const struct Tileset gTileset_GameCorner =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_GameCorner,
    .palettes = gTilesetPalettes_GameCorner,
    .metatiles = gMetatiles_GameCorner,
    .metatileAttributes = gMetatileAttributes_GameCorner,
    .callback = NULL,
};

const u32 gTilesetTiles_CeladonGym[] = INCGFX_U32("data/tilesets/secondary/celadon_gym_frlg/tiles.png", ".4bpp.fastSmol");
const u16 gTilesetPalettes_CeladonGym[][16] = {
    INCGFX_U16("data/tilesets/secondary/celadon_gym_frlg/palettes/00.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/celadon_gym_frlg/palettes/01.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/celadon_gym_frlg/palettes/02.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/celadon_gym_frlg/palettes/03.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/celadon_gym_frlg/palettes/04.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/celadon_gym_frlg/palettes/05.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/celadon_gym_frlg/palettes/06.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/celadon_gym_frlg/palettes/07.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/celadon_gym_frlg/palettes/08.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/celadon_gym_frlg/palettes/09.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/celadon_gym_frlg/palettes/10.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/celadon_gym_frlg/palettes/11.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/celadon_gym_frlg/palettes/12.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/celadon_gym_frlg/palettes/13.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/celadon_gym_frlg/palettes/14.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/celadon_gym_frlg/palettes/15.pal", ".gbapal"),
};
const u16 gMetatiles_CeladonGym[] = INCBIN_U16("data/tilesets/secondary/celadon_gym_frlg/metatiles.bin");
const u16 gMetatileAttributes_CeladonGym[] = INCBIN_U16("data/tilesets/secondary/celadon_gym_frlg/metatile_attributes.bin");
const struct Tileset gTileset_CeladonGym =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_CeladonGym,
    .palettes = gTilesetPalettes_CeladonGym,
    .metatiles = gMetatiles_CeladonGym,
    .metatileAttributes = gMetatileAttributes_CeladonGym,
    .callback = InitTilesetAnim_CeladonGym,
};

const u32 gTilesetTiles_RestaurantHotel[] = INCGFX_U32("data/tilesets/secondary/restaurant_hotel_frlg/tiles.png", ".4bpp.fastSmol");
const u16 gTilesetPalettes_RestaurantHotel[][16] = {
    INCGFX_U16("data/tilesets/secondary/restaurant_hotel_frlg/palettes/00.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/restaurant_hotel_frlg/palettes/01.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/restaurant_hotel_frlg/palettes/02.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/restaurant_hotel_frlg/palettes/03.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/restaurant_hotel_frlg/palettes/04.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/restaurant_hotel_frlg/palettes/05.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/restaurant_hotel_frlg/palettes/06.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/restaurant_hotel_frlg/palettes/07.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/restaurant_hotel_frlg/palettes/08.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/restaurant_hotel_frlg/palettes/09.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/restaurant_hotel_frlg/palettes/10.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/restaurant_hotel_frlg/palettes/11.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/restaurant_hotel_frlg/palettes/12.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/restaurant_hotel_frlg/palettes/13.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/restaurant_hotel_frlg/palettes/14.pal", ".gbapal"),
    INCGFX_U16("data/tilesets/secondary/restaurant_hotel_frlg/palettes/15.pal", ".gbapal"),
};
const u16 gMetatiles_RestaurantHotel[] = INCBIN_U16("data/tilesets/secondary/restaurant_hotel_frlg/metatiles.bin");
const u16 gMetatileAttributes_RestaurantHotel[] = INCBIN_U16("data/tilesets/secondary/restaurant_hotel_frlg/metatile_attributes.bin");
const struct Tileset gTileset_RestaurantHotel =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_RestaurantHotel,
    .palettes = gTilesetPalettes_RestaurantHotel,
    .metatiles = gMetatiles_RestaurantHotel,
    .metatileAttributes = gMetatileAttributes_RestaurantHotel,
    .callback = NULL,
};
