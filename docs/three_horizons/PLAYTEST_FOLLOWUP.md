# Opening playtest follow-up: revision 3

The user tested revision 2 in mGBA 0.10.5 and reported persistent introduction
text overlap, a level-2 Zigzagoon replacing Joey's chosen starter, awkward map
edges, missing interactions, and artwork that did not match the native game.
Revision 3 restores native character artwork and fixes these reported causes.

## Changes

- The first-battle initializer also runs for the opening trainer battle. Its
  Emerald rescue setup replaced the correctly generated trainer party with a
  wild Zigzagoon. Limit that replacement to non-trainer battles. The earlier
  generated-header fix remains necessary for valid trainer names and records.
- Joey keeps his name and native Youngster artwork. All nine rival parties
  contain their announced level-5 starter. His Rival-class payout is 300
  (base 15 x level 5 x multiplier 4); the original invalid/generic encounter
  paid 20. This revision deliberately keeps the proper Rival reward.
- The three professor dialogue pages now pause and clear before the next page;
  the intro window is explicitly filled when clearing it.
- The opening skips the boy/girl question and uses native Red by default.
  The bedroom dresser offers Red, Leaf, Brendan, May, or KEEP CURRENT; B cancels.
  Outfit is stored in the previously unused VAR_TH_OUTFIT (0x40FC). Changing
  clothes does not change player identity, story progress, or Pokemon.
- Walking, running, standard bike, Surf, fishing, trainer portrait, and battle
  back artwork use native character assets. Reverse movement-state restoration
  handles the selected outfit and the shared Red/Leaf Surf/Dive graphics.
- The clock is visually reduced to 8 x 8 and raised with a dedicated palette;
  its native set/view interaction remains available.
- A project-owned 24 x 24 Pallet layout closes the pond, adds grass beneath it,
  and gives the southern forest complete treetops. Original Pallet is unchanged.
- Restore the Route 1 sign event. Hoothoot dialogue now describes the grass
  and nearby trees to the left instead of claiming it is against a tree.
- Oak invites the player to meet the partners at the Poke Balls. Two lab aides
  explain care and summary controls without blocking the scripted walking path.
- On Summary's skills page, A cycles Stats -> IVs -> EVs, with numeric IVs.
- The visible title version banner reads THREE HORIZONS. The existing Pokemon
  logo and Rayquaza background remain.

## Limits and manual checks

Four native outfit choices are delivered. Blue, Gold, Silver, Kris, and other
requested characters still need matching player sprite sets. Red and Leaf use
Brendan/May fallback poses for Acro Bike and watering, which are not available
in this opening demo. Generated explorer assets are no longer linked into the
ROM. Pokemon battle sprites are unchanged. The requested illustrated
Oak/Elm/Birch cover is still pending. The demo ends at the Viridian entrance.

Save structures are unchanged, but automated size checks do not establish every
old-save migration. Keep previous ROMs/saves. Use a new game for the intro and
opening acceptance test, then save in-game and restart the new ROM. Do not use
an old emulator save state to judge this revision's code.

Visual acceptance remains outstanding: title banner, all introduction pages,
each outfit in the room and battle, dresser cancel/save/reload, clock reachability,
pond/forest edges, lab movement, sign, Hoothoot text, and every rival approach.
Automated emulator tests are not a manual visual playthrough.

## Verification

Build source: 5ca214543a7cb31a133cb6675dd80cd00502e7ac.

- Nine host checks cover map paths, events, unchanged original layouts, and
  individual map generation under Emerald, FireRed, and Three Horizons modes.
- Twenty Three Horizons engine tests cover starter customization, progression,
  outfits, movement restoration, title text widths, and actual rival setup.
- Four save-size tests check existing structure limits.
- The rival regression is also run with the old overwrite temporarily restored:
  it must fail on Zigzagoon versus the expected starter, then pass with the fix.
- Trainer mode-switch verification checks shared generated-header invalidation.
- Independent ELF inspection checks all nine real trainer records, native asset
  linkage, and all four native back pictures byte-for-byte against source tiles.

The map generator must retain TH layouts for individual map-header lookup even
in non-TH modes: Make prepares those files for all maps. Only the linked layout
tables/constants omit TH layouts in other modes. This preserves original builds.

Build and test results are recorded in the delivered BUILD_REPORT.md and in
[demo run 35827155214](https://github.com/PhabejSam/pokemon-three-horizons/actions/runs/35827155214)
and [compatibility run 35827306436](https://github.com/PhabejSam/pokemon-three-horizons/actions/runs/35827306436).
Nonfatal build warnings include PNG background-index metadata and the unused
boy/girl prompt function in the demo configuration.
