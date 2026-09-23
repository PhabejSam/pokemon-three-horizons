# Opening playtest follow-up

User evidence: mGBA 0.10.5, opening ROM source
39d32ee1d98ca2785ed69327b781698572cdee59. Totodile playthrough reached
the Viridian endpoint. Wild encounters ran without reported lag. The user
saved through the in-game menu and reloaded successfully after restarting.
This does not establish every starter/outcome or revision save compatibility.

## Confirmed defects and changes under verification

- Invalid rival name assertion, question-mark trainer and level-2 Zigzagoon:
  the parse-time `generated` submake used THREE_HORIZONS=0 despite the parent
  build using 1. Direct inspection of the delivered ELF found all nine rival
  records zero-filled in all three difficulty tables (52-byte records).
  Pass the preprocessing configuration explicitly and invalidate shared
  generated trainer headers when its flags change. Tests inspect the compiled
  names, pictures, parties and levels; a mode-switch check exercises regeneration.
- Oak and Mom: their graphics, frames and descriptors were FRLG-only even though
  the demo uses them under Emerald. Include just these assets for the demo.
- Bedroom intro: the final message lacked the upstream page-clearing behavior.
  Clear its window explicitly before printing the new message.
- Home PC, upstairs notice, console, brown trainer-tip sign and house signs:
  missing background events. Connect them; use the existing player item PC and
  the correct native FRLG PC animation tiles. Add responses to reachable home
  and lab furnishings.
- Living-room top-right chair: Mom occupied that tile while her graphics were
  missing. Move her to the floor beside the table.
- Rename the visible rival to Joey. Keep internal IDs and saved progress stable.
  Walk to the lab/exit/route before hiding his object.
- Hoothoot: relocate from the middle of tall grass to the ground beside trees,
  with the local observer nearby.
- Southern inlet: close the former Route 21 opening with native shoreline
  metatiles on the project map only. Existing original layouts remain unchanged.

## Still needs visual acceptance or new feature work

- Reported Littleroot label: the delivered Pallet and bedroom headers contain
  section 88 (Pallet Town). Added a test of their actual displayed names.
  The precise screen showing Littleroot has not yet been identified.
- Southern forest/border appearance, furniture reachability, text clearing and
  Joey's walking routes need another emulator playthrough, including approaching
  Joey from different sides.
- Bedroom clock: added a visible clock at (7,1), using the native set/view clock
  interfaces without triggering Emerald's moving-in story.
- Starter preview and optional shiny/nature/individual IV/EV editing are
  implemented. Limits: IV 0-31, EV 0-252 per stat and 510 total. Includes
  cancel/defaults and final confirmation. Settings stay temporary until grant.
  Grant tests passed for all nine species, both colors, and all 25 natures.
- Original player and Joey: user selected young explorers with distinct outfits.
  The male player's walking/running, front portrait and battle back sprite,
  plus Joey's walking/battle sprites, now use original generated explorer art.
  Art was packed into native dimensions and 16-color palettes. Running currently
  reuses walking poses. Female avatar, bike/surf/fishing and other later-game
  poses remain upstream; these are outside the present opening route.
- Three Horizons title with Oak, Elm, Birch and nine starters: requested and
  pending. The image service rejected generation; no title artwork was delivered.
  Intro dialogue now names Three Horizons and the ROM header says POKEMON 3HZ.
- Pokémon art sharpness: no Pokémon sprites have been altered. Display scaling
  and filtering should be evaluated separately from any sprite replacement.

## Validation status

Source `461a99a737e2113efb63ca61906ec359906e889b` passed its demo build,
8 map/path checks, 16 opening engine tests, 4 save-size checks and trainer-mode
switching in [run 35821618420](https://github.com/PhabejSam/pokemon-three-horizons/actions/runs/35821618420).
The ROM SHA-256 is `2eaf6bd62098560068c703c5b8595b4f396933a51fc7d904ccef1d95e48c9dc2`.
Direct ELF inspection confirms Joey's nine named level-5 starter records and
required graphics. Original Emerald/FireRed/LeafGreen/release builds passed;
the broad upstream test job was still running at this update. User acceptance
is still required. The previous ROM/save are preserved; the new playtest copy
has the distinct filename `pokemon-three-horizons-playtest-2.gba`.

Test harness note: battle unit tests substitute synthetic `gTrainers`, so the
project's trainer regression includes the real generated trainer header in a
separate table. Graphics tests initialize sprite palette allocation, and map
scripts receive actual object templates before changing permanent positions.
The generator configuration stamp is shared across build modes because the
generated trainer headers are shared too.
