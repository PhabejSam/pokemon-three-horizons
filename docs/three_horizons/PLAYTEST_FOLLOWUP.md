# Opening playtest follow-up: revision 4

The user successfully tested revision 3 saving/loading, starter customization,
IV/EV summary cycling, outfits, rival starter selection/reward/exit, signs and
Hoothoot dialogue. This revision builds on that accepted opening with a classic
Blue rival and naming, seven outfit choices, the native Pallet coastline,
running options, followers, selectable experience rates and battle information.

No save-block fields were added. New options use audited unused event variables
0x40FD–0x40FF; the rival name uses 0x404E, 0x4083, 0x408B and 0x4091. These join
existing progress/outfit reservations 0x40F7–0x40FC. Original outfit values retain
their meaning. The map additions and behavior are gated by THREE_HORIZONS.

## Player guide

Open `pokemon-three-horizons-playtest-4.gba` in mGBA. Start a **New Game** to
try the rival naming screen and full opening. Prior ROMs and saves are untouched.
Use the in-game save menu; don't transfer emulator save states between builds.

## New controls

- **Options → L or R → page 2:** Auto-run ON/OFF, Experience 1×/2×/4×/8×,
  and Follower ON/OFF. B or SAVE AND EXIT applies changes. Save your game to
  retain them after closing the emulator.
- Running shoes work from the start. Normally hold B to run; with Auto-run ON,
  hold B to walk. Terrain and scripted movement still apply their normal rules.
- The follower is the Pokémon in **party slot 1**. Eggs, fainted Pokémon, and
  an empty first slot do not follow. The existing engine may hide followers
  during scripts or where their size is unsuitable. The default is ON.
- Move names use **green = super-effective**, **amber = resisted**,
  **red = immune**, **dark = neutral**, and **blue = status move**.
  The selected move also shows a numerical effectiveness label such as 2×,
  ½×, or 0×. Status moves show `--`. Types appear during move selection.

## What to try

1. Name your player, then name the rival. The rival uses classic Blue graphics;
   BLUE is the default name. Check the entered name in dialogue and battle.
2. At the bedroom dresser, try **Red, Leaf, Brendan, May, Gold, Kris, Silver**.
   Walk and run in all directions, change floors, and check the battle back pose.
   KEEP CURRENT or B cancels. Read the revised bookshelf text.
3. Walk to Pallet's southern inlet. The water now continues toward Route 21;
   there is no artificial pond bottom crossing the forest. Surf and Cinnabar
   are not unlocked in this opening demo.
4. Choose a partner and check its customization and summary IV/EV pages as
   before. Check its follower after leaving the lab, changing party order,
   toggling the option, and healing a fainted lead Pokémon.
5. Battle your rival. Choosing Mudkip gives the rival Treecko; the reward is
   still ₽300. Check colored moves, types, the entered rival name, and his exit.
6. Set EXP to **4× or 8×** and fight wild Pokémon to test leveling and evolution.
   Mudkip and Treecko first evolve at level 16. Check the evolution animation,
   new moves, summary, follower appearance, and save/load afterward.
7. Save in-game, close mGBA, reopen this ROM, and Continue. Check your outfit,
   rival name, options, party, and progress. Reach the Viridian entrance.

## Where the moves come from

The engine uses its **Generation 9 level-up tables**, not original Emerald's
Generation 3 tables. These tables were not changed for this revision.

| Pokémon | Early level-up moves |
| --- | --- |
| Treecko | Pound/Leer at 1, Leafage at 3, Quick Attack at 6, Mega Drain at 9 |
| Mudkip | Tackle/Growl at 1, Water Gun at 3, Rock Smash at 6, Rock Throw at 9 |

Source: `src/data/pokemon/level_up_learnsets/gen_9.h`, selected by
`P_LVL_UP_LEARNSETS = GEN_LATEST`. Leafage receives Treecko's same-type bonus
and is super-effective against Mudkip. Chosen natures, IVs, and EVs can also
change damage substantially. This is not a custom boosted Leafage move.

## Remaining scope and artwork limits

- The story still ends at Viridian's entrance. This revision supports testing
  leveling/evolution while the opening is polished; it does not add the next city.
- Blue is available as the rival, not as a dresser outfit. A matching playable
  Blue back-picture and full action set are still needed.
- Silver reuses walking frames when running. His future bike, Surf, fishing,
  and field-action poses use Gold fallbacks; these actions are outside this demo.
- Gold/Kris watering poses and Red/Leaf Acro Bike/watering poses retain source
  fallbacks. They need further work before those activities become playable.
- The title banner reads THREE HORIZONS but still uses Rayquaza. The earlier
  requested Oak/Elm/Birch title illustration remains unfinished.
- The automated checks do not replace a visual emulator playthrough. In
  particular, please check option text, outfit motion, follower collisions,
  rival naming, battle colors, and the coastline in this build.

See BUILD_REPORT.md for exact build evidence and OUTFIT_CREDITS.md for art sources.

## Build evidence

Successful ROM build from source `2169b1465c1d4cd2135605edf84323d302978209`.
Output: `pokemon-three-horizons-playtest-4.gba` (32 MiB). SHA-256: `dee955fba1be9801819df000568deb216bb90e73b2295e36ea23f15b9648b6c1`.

## Verification

- Ten host checks passed for map bounds, connections, paths and build-mode generation.
- Twenty-six Three Horizons engine tests passed, plus four save-size tests.
- Tests cover all nine starter choices, actual rival party initialization,
  seven outfits and movement restoration, customization, EXP rates, follower
  slot/option/fainting behavior, rival name persistence, and title-screen options.
- Evolution checks verify the nine starters' first evolution destinations;
  they do not establish that all evolution animations or later evolutions work.
- The negative first-battle check fails with the original Zigzagoon overwrite
  restored, then passes after restoring the fix.
- Shared trainer headers regenerate correctly when switching build modes.
- Independent compiled-ROM inspection verifies the nine level-5 rival records,
  Blue's graphics and seven back pictures against the source indexed pixels.
- No manual visual emulator playthrough was performed for this revision.

[Build, tests and logs](https://github.com/PhabejSam/pokemon-three-horizons/actions/runs/35907772273).
See COMPATIBILITY.md for separately checked upstream build results.

## Reproduce

Use Ubuntu 24.04 with build-essential, binutils-arm-none-eabi,
gcc-arm-none-eabi, libnewlib-arm-none-eabi, libpng-dev, pkg-config, Python 3 and Git.
Check out the source commit above, then run:

```sh
make -C tools/mapjson
python3 -m unittest discover -s tools/three_horizons/tests -v
make THREE_HORIZONS=1 -j2 -O all
make THREE_HORIZONS=1 check TESTS="Three Horizons" -j2
make THREE_HORIZONS=1 check TESTS="test/save.c" -j2
```

The original output is `pokemon-three-horizons.gba`; the delivered copy is
renamed to keep earlier playtests separate. Exact versions and test/build logs
are in `verification/`. CHANGED_FILES.txt lists files changed since playtest 3.

## Limits

Save structures are unchanged; size tests cannot guarantee every old-save case.
Earlier ROMs and saves were not modified. Start a new game to test rival naming.
Use ordinary in-game saves, not old emulator save states, across ROM revisions.

The opening still ends at Viridian. Pallet uses the original layout and southern
Route 21 connection, but Surf/Cinnabar are not unlocked. Seven outfits are
available; playable Blue and complete Silver action sprites remain unfinished.
The title says THREE HORIZONS with Rayquaza; the three-professor illustration
remains pending. Pokémon learnsets and battle sprites are unchanged. See the
guide and art credits for controls, moveset sources and pose fallbacks.

## Build capacity and warnings

```text
EWRAM:      226476 B       256 KB     86.39%
IWRAM:       28384 B        32 KB     86.62%
ROM:    27197520 B        32 MB     81.05%
```

Nonfatal warnings retained in the build log:

- `libpng warning: bKGD: invalid index`
- `libpng warning: iCCP: known incorrect sRGB profile`
- `src/main_menu.c:1535:13: warning: 'Task_NewGameBirchSpeech_BoyOrGirl' defined but not used [-Wunused-function]`

## Compatibility

Source: 2169b1465c1d4cd2135605edf84323d302978209.

[Compatibility workflow](https://github.com/PhabejSam/pokemon-three-horizons/actions/runs/35907775647).

Checked September 23, 2026, at approximately 19:25 UTC:

- Emerald ROM: passed.
- FireRed ROM: passed.
- LeafGreen ROM: passed.
- Release build: passed.
- Documentation validation: passed.
- Full upstream test suite: still running when this package was prepared.

The separate Three Horizons workflow completed successfully, including the
26 opening tests, four save-size checks, ten host checks, the negative/positive
first-battle regression and trainer generation across build modes.
