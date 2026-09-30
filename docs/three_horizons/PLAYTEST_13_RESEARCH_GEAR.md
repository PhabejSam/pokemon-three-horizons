# Research Gear — Playtest 13.1 / RC2

This guide describes the RC2 implementation under verification. It does not establish release or RG40XX H acceptance; see PLAYTEST_13_VERIFICATION.md for the exact candidate and evidence.

## Receiving Gear

On a new game, Oak explains and enables Gear in the laboratory after your partner and Pokédex are ready. It is free, appears in Start, and does not take a bag slot. Repeating the handoff cannot duplicate anything.

On a migrated post-Surge Playtest 12 save, speak to the scientist in Vermilion Pokémon Center before heading onward. He enables missing Gear even if the bag is full. The existing Vs. Seeker reward remains separate. Existing RC1 Gear stays unlocked.

The Route 2 aide awards HM05 Flash with the Thunder Badge and ten caught species. He no longer introduces Gear. Keep a conscious compatible non-Egg Pokémon and the HM in the bag; teaching Flash or freeing a move slot is unnecessary. Missing badges, quota, item space, owned HM and repeat dialogue keep their existing rules.

## Using the three modules

1. **Research Log:** select a location to read the observed species, interaction, region, origin and photo status. A turns to the professor note; B returns.
2. **Field Photos:** select a recorded scene. Its first page shows a 224×96 miniature of the actual authored map with native overworld Pokémon poses. A opens details, then the professor note, then returns to the image. Left/right also turn pages. B returns.
3. **Calls:** select an introduced professor to read their latest received report. The list names Oak, Elm or Birch and the report topic. Reading is passive and never advances story flags or rewards.

The native window frame, bright background, font and cursor follow GBA menu conventions. Up/down selects rows; lists contain four two-line rows per page. Empty modules explain that nothing is recorded yet. Held input does not repeatedly open or close screens.

## Contact milestones

Oak introduces Gear in person. The Hoothoot interaction on Route 1 introduces Elm's Johto research. The Clefairy/Makuhita gathering in Mt. Moon introduces Birch's Hoenn research. Photographing is optional: the observed live interaction owns the contact milestone.

For older saves that passed those scenes before receiving Gear, the Forest Cut clearing, Diglett's Cave, Route 9 and Rock Tunnel provide appropriate live follow-up opportunities. Merely importing an old observation does not invent a photograph or deliver a new call.

At Route 10, Oak delivers the coordinator update. At Lavender, Elm delivers the Tower follow-up. Other professors' corresponding analysis appears in Calls and notes without additional automatic speeches. Existing RC1 activation receipts preserve the professors you already heard.

Calls wait until ordinary field controls are safe: no battle, naming screen, bag, party menu, script, fade, movement or field move. After one call, another pending call waits for eight tiles of further travel or a map change. Cold Continue clears only this temporary pacing; pending and delivered reports remain saved.

## Photographs and save compatibility

Declining leaves the photo unrecorded. Accepting gives a brief visible flash and stores one receipt. Repeating shows that it is already recorded. Gear never stores emulator screenshots or large saved images: the ten environmental cards and subjects live in ROM. The save stores existing observation/photo flags and four newly owned contact flags, with no save-block growth.

The cards cover Route 1, two early Forest pairs, Mt. Moon, Vermilion Harbor, the Forest Cut clearing, Diglett's Cave, Route 9, Rock Tunnel and Lavender. Harbor partners remain ashore after the ship departs. Photograph earlier sightings when convenient; none requires replaying a completed battle.

The palettes use fifteen opaque map colors plus transparency in one BG bank. Native subject OBJ palettes are separate. This is a miniature of the map, not a full screen capture. The image page prioritizes the environment; readable metadata and notes occupy the following pages.

Keep the original PT12/RC1 ROM and battery files unchanged. Copy the battery to the RC2 filename, boot normally, Continue, compare progress, save through the game, close, reopen and Continue again. Old emulator states are not migration evidence. RG40XX H/VBA-Next uses its EEPROM directory and core naming convention; the owner's original source is a raw 128 KB `.gba.eps` file.
