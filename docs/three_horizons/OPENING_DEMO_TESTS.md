# Opening demo build and acceptance checks

Status: implementation under validation. This document is not a claim that the
playable opening has passed emulator acceptance.

## Build

Use a fresh checkout of `feature/opening-demo` on Ubuntu 24.04. Install the
dependencies documented in `BUILD_BASELINE.md`, then run:

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

- Map-generator tests: seven checks passed locally using a portable Windows host
  compiler; they cover the closed six-map graph, native FRLG layout format,
  unchanged original map indices/layout tables, source preservation, missing map
  rejection and Windows line endings. Linux checks are recorded in Actions logs.
- Engine tests exercise real party grants, level/species/rival mapping, duplicate
  rejection, invalid inputs, partial inventory retries, irreversible progression,
  stored original species, map-transition visibility, and home initialization.
  Result is pending the workflow; compilation alone is not a test pass.
- Save-block size checks and original Emerald/FireRed/LeafGreen/release/test jobs
  are required. Record final results before marking acceptance complete.

## Manual run

Record ROM source commit, checksum and emulator version with each run.

1. Start a new game. Complete naming. Confirm arrival in the bedroom, without
   Emerald's truck sequence. Walk downstairs; talk to Mom and examine the TV.
2. Leave home. Robin's invitation plays once. Reenter/reload and confirm Robin
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
8. Examine Hoothoot at Route 1 (20,16), near the local at (19,16). The first
   observation must not repeat, and it must remain optional.
9. Enter Viridian. Robin's ending must play once. The row-32 boundary must prevent
   further travel from every walkable approach and always restore movement.
10. Save from the **in-game menu**, close the emulator, reopen the ROM and select
    Continue. Verify position, party, gifts, battle completion and ending state.

| Player partner | Robin partner | Win path | Loss path | Interactive choice |
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
- Existing player/rival graphics and Emerald title/naming presentation are
  prototype assets. The expanded town and bespoke character art are later work.
- Native desktop emulator control was unavailable. A bundled headless Windows
  emulator help probe did not return and was stopped; no manual passes are inferred.

Source review: draft PR #2. This demo must remain unmerged until required
validation and review are complete.
