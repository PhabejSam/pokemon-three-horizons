// The six native Kanto tilesets used by the Emerald-based opening.
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
