# Opening demo build and acceptance checks

Status: source `461a99a737e2113efb63ca61906ec359906e889b` passed the demo build,
8 map/path checks, 16 opening tests, 4 save-size tests and trainer-mode switching
in [run 35821618420](https://github.com/PhabejSam/pokemon-three-horizons/actions/runs/35821618420).
This does not establish manual emulator acceptance.

## Build

Use a fresh checkout of `feature/opening-demo` on Ubuntu 24.04. Install the
dependencies documented in [BUILD_BASELINE.md](../../BUILD_BASELINE.md), then run:

```sh
make -C tools/mapjson
python3 -m unittest discover -s tools/three_horizons/tests -v
make THREE_HORIZONS=1 -j2 -O all
make THREE_HORIZONS=1 check TESTS="Three Horizons" -j2
make THREE_HORIZONS=1 check TESTS="test/save.c" -j2
sha256sum pokemon-three-horizons.gba
```

Output: `pokemon-three-horizons.gba`. The workflow also keeps the ELF, map, logs,
source commit and SHA-256 checksum. Original game targets should be built in
separate checkouts because generated files are shared within a checkout.

Use a **new save**. Keep the tested `pokeemerald.gba` and its save in their original
folder. This demo has a different ROM filename and does not migrate old saves.

## Automated evidence

- Map-generator/path tests: eight checks passed locally using a portable Windows host
  compiler; they cover the closed six-map graph, native FRLG layout format,
  unchanged original map indices/layout tables, source preservation, missing map
  rejection and Windows line endings. Linux checks are recorded in Actions logs.
- Engine tests exercise real party grants, level/species/rival mapping, duplicate
  rejection, invalid inputs, partial inventory retries, irreversible progression,
  stored original species, map-transition visibility, and home initialization.
  All 16 passed in the revision workflow above; compilation alone is not a test pass.
- All four save-size checks and original Emerald/FireRed/LeafGreen/release builds
  passed. The broad upstream test job was still running when this note was updated.
  See [compatibility run 35821621444](https://github.com/PhabejSam/pokemon-three-horizons/actions/runs/35821621444)
  for its final status. Manual acceptance remains open.

## Manual run

Record ROM source commit, checksum and emulator version with each run.

1. Start a new game. Complete naming. Confirm arrival in the bedroom, without
   Emerald's truck sequence. Walk downstairs; talk to Mom and examine the TV.
2. Leave home. Joey's invitation plays once. Reenter/reload and confirm Joey
   does not reappear simultaneously in town and the lab.
3. Visit Oak. Open each regional display; cancel with B and decline a confirmation.
   Confirm neither action adds a Pokémon or changes the chosen-partner state.
4. Confirm one partner. Verify level 5, expected species, Pokédex registration,
   and the rival partner listed below. Verify five Poké Balls and two Potions.
   Talk again, leave/reenter, and reload: there must be no duplicate gifts.
5. Leave the lab. Win or deliberately lose; both paths must heal the player,
   restore movement, unlock Route 1, and keep the battle completed on revisits.
6. Walk all six maps in both directions. Check doors, stairs, ledges, borders,
   palettes, animations, music and text. Check the closed rival-house door.
7. Catch a Route 1 Pokémon, flee, and deliberately lose a wild battle. Recovery
   must return to Mom with story progress intact. Mom must heal on repeat visits.
8. Examine Hoothoot at Route 1 (17,17), near the local at (18,18). The first
   observation must not repeat, and it must remain optional.
9. Enter Viridian. Joey's ending must play once. The row-32 boundary must prevent
   further travel from every walkable approach and always restore movement.
10. Save from the **in-game menu**, close the emulator, reopen the ROM and select
    Continue. Verify position, party, gifts, battle completion and ending state.

| Player partner | Joey partner | Win path | Loss path | Interactive choice |
| --- | --- | --- | --- | --- |
| Bulbasaur | Charmander | Not run | Not run | Not run |
| Charmander | Squirtle | Not run | Not run | Not run |
| Squirtle | Bulbasaur | Not run | Not run | Not run |
| Chikorita | Cyndaquil | Not run | Not run | Not run |
| Cyndaquil | Totodile | Not run | Not run | Not run |
| Totodile | Chikorita | Not run | Not run | Not run |
| Treecko | Torchic | Not run | Not run | Not run |
| Torchic | Mudkip | Not run | Not run | Not run |
| Mudkip | Treecko | Not run | Not run | Not run |

| Cold in-game save checkpoint | Result |
| --- | --- |
| Before choosing a partner | Not run |
| After choosing a partner | Not run |
| After the first battle | Not run |
| After the Viridian ending | Not run |

Automated state tests do not replace these visual/input/save checks. The prior
untouched-ROM smoke test applies only to the baseline ROM.

## Implementation decisions and limits

- Uses six existing Kanto layouts, their native FRLG format, and six scoped
  tilesets within an opt-in Emerald build. Original map indices are preserved.
- Five audited unused Emerald variables hold progress. Map-temporary flags 1 and
  2 hide Robin according to that progress; no new persistent flags are allocated.
- Robin consumes the nine available Emerald trainer slots 855–863 only in the
  demo build. `MAX_TRAINERS_COUNT` and save-block layout remain unchanged; future
  trainer expansion needs a separate capacity design.
- Male player and Joey now use original explorer sprites in the opening.
  Running reuses walking poses; later bike/surf/fishing and female art remain
  upstream. The full professor title illustration is pending. The expanded
  town and travel beyond the Viridian demo boundary remain later milestones.
- Native desktop emulator control was unavailable. A bundled headless Windows
  emulator help probe did not return and was stopped; no manual passes are inferred.

Source review: draft PR #2. This demo must remain unmerged until required
validation and review are complete.

## Playtest revision checks

- Verify the intro identifies Three Horizons and finishes without overlapping
  text. The clock at bedroom (7,1) must set once and then show the time.
- Check the bedroom PC, notice by the stairs, console, books and bed; kitchen,
  living-room furniture and lab research items now have interactions. Mom must
  be visible on the floor and the upper-right chair must be traversable.
- Read the trainer-tips sign left of the lab and inspect the southern shoreline.
- At each display, choose a species to open its preview. Toggle shiny; cycle
  nature; edit all six IVs and EVs. LEFT/RIGHT changes 1; L/R changes 10.
  IVs stop at 31, each EV at 252 and the total at 510. Test Restore defaults,
  B cancel, and declining final confirmation before accepting a partner.
- Choosing Totodile must give Joey a level-5 Chikorita. Confirm his name, new
  portrait and walking exits; test approaches from all adjacent sides.
- Check the male explorer's front, walking, running and battle-back animation.
  Joey must keep his new look in Pallet, the lab and the Viridian endpoint.
- Repeat the in-game save/restart checks on this revision. Previous successful
  saving and smooth wild encounters were reported on source 39d32ee1 only.
