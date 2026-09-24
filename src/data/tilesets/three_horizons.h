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
