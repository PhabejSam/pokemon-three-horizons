# Three Horizons landscape title

The scenery was generated with the built-in OpenAI image-generation tool on
2026-09-24 for this project, using the user-approved scenery-only concept.
The original high-resolution file is preserved in the local title-art output
and the title-update download. The build consumes landscape.png (indexed
256x160, with 240x160 visible) and landscape.bin (32x32 text BG tile map).

The Pokemon logo is the existing project asset from
graphics/title_screen/pokemon_logo.png. Its attribution remains with the
upstream game assets. The new scenery is not official Pokemon artwork.

## Generation prompt

Create a new original landscape illustration for the title screen of a
Pokémon fan adventure named Three Horizons. This is a scenery-only concept:
no people and no Pokémon creatures. A welcoming green valley at sunrise,
three layered blue mountain ridges along the horizon, a winding sandy route
leading toward a tiny cozy town with red roofs and a small research lab, a
stream glinting in the valley, and a small red-and-white Poké Ball route
marker in the lower foreground to establish the Pokémon theme. Clean
colorful hand-painted anime game-background illustration, confident simple
silhouettes, restrained texture, warm golden light, adventurous and cozy.
Wide landscape 3:2 composition. Keep the upper half mainly uncluttered soft
sky so a separate game logo can be overlaid there; put the most recognizable
scenery and Poké Ball marker in the lower half. No text, no lettering, no
logo, no border, no watermark. Make shapes readable when reduced to a 240
by 160 pixel handheld screen; do not render as pixel art.

## Conversion and integration

The illustration is resized to 240x160 with Lanczos sampling and indexed to
223 scenery colors. The existing logo uses 32 additional colors; index 0 is
reserved for transparency. The image is padded to 256 pixels for 32 tiles per
row. BG0 tiles occupy VRAM 0x0000-0x9FFF and the map occupies 0xF800-0xFFFF.
Title text and the blinking Start prompt use the native sprite renderer.
The previous cloud/Rayquaza palette animation is excluded from this scene.
The native menu, save-clearing and clock-reset input paths remain available.

The separate professor portraits requested earlier are not part of this
scenery-only title revision.
