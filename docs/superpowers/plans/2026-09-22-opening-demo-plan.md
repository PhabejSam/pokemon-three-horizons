# Three Horizons Opening Demo Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Deliver the approved cozy Pallet–Route 1–Viridian entrance demo as a separately named GBA ROM.

**Architecture:** Add an opt-in Emerald-based project configuration, a six-map project-owned event set, and a small persistent progression module. Reuse existing Kanto layouts in their native FRLG format; preserve the map-layout runtime flag and the original upstream build paths. Keep first-partner species separate from the legacy three-starter index.

**Tech Stack:** C, GBA event assembly, JSON map data, the existing C++ map generator, Python standard-library checks, GNU Make, ARM GCC, Ubuntu GitHub Actions, mGBA.

**Spec:** [Approved opening design](../specs/2026-09-22-opening-demo-design.md). The user approved the complete written design, including Robin, level 5, regional displays, and same-region type-advantage rival choices.

## Global constraints

- Keep Pallet Town recognizable and refreshed. An expanded, reimagined town is a later milestone.
- Offer all nine first partners from Generations 1–3.
- Win or lose, the first battle advances the story.
- Do not change the save-block format for this demo.
- Preserve the user's tested baseline ROM and save.
- Keep existing Emerald, FireRed, and LeafGreen build behavior available.
- Do not expand the legacy starter array to nine or reinterpret `VAR_STARTER_MON` globally.
- Do not require a real-world time setting or day/night system for the Hoothoot event.
- The demo requires a fresh save. No migration or overwriting of the user's baseline save.
- No global species/stat/move/ability/evolution changes, expanded town, second rival, or interregional travel in this milestone.

## Execution context

The working repository is currently on local branch `design/opening-demo`.
Setup PR #1 exists separately and must not be merged automatically.
Start implementation in a dedicated branch/worktree descended from this approved
planning work. Check the current branch and uncommitted changes before creating it.

Local Windows has no WSL/build toolchain. Use the verified Ubuntu 24.04 GitHub
runner for builds. A Windows-native Python runtime is available for host checks.
Do not install WSL, restart Windows, or replace the baseline ROM as part of this plan.

Dependency command for a fresh Linux runner:

```bash
sudo apt-get update
sudo apt-get install -y --no-install-recommends build-essential git \
  binutils-arm-none-eabi gcc-arm-none-eabi libnewlib-arm-none-eabi \
  libpng-dev pkg-config python3
```

Use independent checkouts for different build configurations because generated
map headers and encounter headers share source-tree locations.

## Evidence that informed the plan

- `src/fieldmap.c` selects metatile interpretation and palette limits from
  `MapLayout.isFrlg`; `include/global.fieldmap.h` has both attribute formats.
  Preserve this existing support rather than converting metatile binaries.
- `tools/mapjson/mapjson.cpp` currently filters by region/layout version.
  Its rejected-map entries preserve slots. Extend selection without compacting IDs.
- `data/event_scripts.s` puts the stock Kanto events under `.if IS_FRLG`.
  The demo needs its own script includes under its project option.
- `src/new_game.c` selects the start warp and resets based on `IS_FRLG`.
  Add a project-specific branch, not a global change to that macro.
- `trainerbattle_earlyrival` and `RIVAL_BATTLE_HEAL_AFTER` already support
  continuing after a first-battle loss; inspect both outcome paths before using them.
- `dynmultichoice` provides cancelable script-local menus; no global menu-table
  redesign is needed.
- `src/data/heal_locations.json` is rewritten by existing map generation.
  Audit generated differences and preserve the source NPC identifiers across builds.

## Review focus

1. Crossing maps or saving midway through the opening must not duplicate gifts or replay battles.
2. FRLG layouts must render, collide, animate, and heal correctly under the Emerald engine.
3. Moving across an endpoint, blocked door, or route boundary must always restore player control.
4. Switching build modes must not reuse generated data from another mode or change original map IDs.
5. A valid save reload must preserve the original partner even after party reordering, evolving, or boxing.

Tasks below include automated checks where feasible and explicit emulator checks
for behavior that host assertions cannot establish.

## File ownership and interfaces

| Files | Responsibility |
| --- | --- |
| `Makefile`, `map_data_rules.mk`, `include/config/three_horizons.h`, `include/config/general.h` | Opt-in build, distinct output/object paths, project macro |
| `tools/mapjson/mapjson.cpp`, `tools/mapjson/three_horizons_maps.json` | Select Hoenn baseline plus exactly six project maps and their required layouts |
| `data/maps/map_groups.json`, six `data/maps/TH_*/map.json` files | Append project map group; project warps, objects, connections, triggers |
| `data/event_scripts.s`, `data/scripts/three_horizons/*.inc` | Home, town, lab, route, endpoint, text, repeatable recovery |
| `include/constants/three_horizons.h`, `include/three_horizons.h`, `src/three_horizons.c`, `data/specials.inc` | State, species mapping, atomic starter/supplies functions, script wrappers |
| `src/new_game.c`, `src/main_menu.c`, `src/data/heal_locations.json` | Project spawn, neutral character-creation text, valid recovery location |
| `src/data/trainers.party` | Nine Robin first-battle entries, appended without changing existing IDs |
| `src/data/wild_encounters.json` | Project Route 1 encounter entry only |
| `test/three_horizons.c`, `tools/three_horizons/tests/test_map_contract.py` | Runtime state/party tests and real map-generation contract tests |
| `.github/workflows/three-horizons-demo.yml` | Build and retain the demo, tests, version record, checksum |
| `docs/three_horizons/OPENING_DEMO_TESTS.md`, `docs/SUMMARY.md` | Reproducible acceptance checklist and recorded results |

### Map inventory

Create these six maps by copying source map metadata and then replacing ALL
event lists and script labels with project-owned entries. Reuse the source's
layout ID, graphics, music, dimensions, FRLG border fields, and terrain.

| New folder / constant | Source folder |
| --- | --- |
| `TH_Home2F` / `MAP_TH_HOME_2F` | `PalletTown_PlayersHouse_2F_Frlg` |
| `TH_Home1F` / `MAP_TH_HOME_1F` | `PalletTown_PlayersHouse_1F_Frlg` |
| `TH_Pallet` / `MAP_TH_PALLET` | `PalletTown_Frlg` |
| `TH_OaksLab` / `MAP_TH_OAKS_LAB` | `PalletTown_ProfessorOaksLab_Frlg` |
| `TH_Route1` / `MAP_TH_ROUTE1` | `Route1_Frlg` |
| `TH_ViridianEntrance` / `MAP_TH_VIRIDIAN_ENTRANCE` | `ViridianCity_Frlg` |

Append `gMapGroup_ThreeHorizons` to `group_order`; do not insert into existing
groups. Derive required layout IDs from these six source JSON records so the
Home1F layout identifier is not guessed.

Retain only reciprocal route connections: Pallet north to Route 1 (offset 0);
Route 1 south to Pallet (0), north to Viridian (-12); Viridian south to Route 1
(12). Remove Pallet's southern sea connection and Viridian's north/west exits.

Retain the house staircase and house/lab door pairs, remapping their destinations.
Disable the rival-house door with an explicit closed-door message; do not retain
a warp into its stock event set. Viridian is accessible only in its southern
entrance strip: place a visible boundary and coordinate guard at row 32 of the
48×40 layout. No interior door or other exit is accessible. Verify the boundary
visually and from every walkable approach; use project-owned layout copies if
a collision edit is required, without editing shared original binaries.

### Persistent identifiers

At planning time these Emerald slots were declared unused, with no gameplay
references found. Re-audit the named and raw IDs at implementation start.

```c
#define VAR_TH_STAGE           0x40F7
#define VAR_TH_FIRST_PARTNER   0x40F8
#define VAR_TH_RIVAL_PARTNER   0x40F9
#define VAR_TH_SUPPLY_MASK     0x40FA
#define VAR_TH_SIGHTING_SEEN   0x40FB

#define TH_STAGE_HOME          0
#define TH_STAGE_INVITED       1
#define TH_STAGE_PARTNER       2
#define TH_STAGE_BATTLE_DONE   3
#define TH_STAGE_COMPLETE      4

#define TH_SUPPLY_BALLS        1
#define TH_SUPPLY_POTIONS      2
#define TH_SUPPLY_DEX          4
#define TH_SUPPLIES_COMPLETE   7
```

Alias/replace those unused declarations in `include/constants/vars.h` for
clarity; do not allocate extra SaveBlock fields. FRLG has its own variable
namespace, so all project code/events/tests are guarded by `THREE_HORIZONS`.
No new general event flags are required; map-object visibility is derived from
the saved stage on map entry.

Public project functions, all declared in `include/three_horizons.h`:

```c
void TH_InitNewGame(void);
u16 TH_GetRivalStarter(u16 playerSpecies);   // SPECIES_NONE for invalid input
bool32 TH_TryGiveStarter(u16 playerSpecies); // TRUE only on the first valid grant
bool32 TH_TryGiveSupplies(void);            // TRUE once all required supplies exist
void TH_FinishRivalBattle(void);            // advances PARTNER only; idempotent
void TH_ScriptGiveStarter(void);            // reads 0x8004; result TRUE/FALSE
void TH_ScriptGiveSupplies(void);           // result TRUE/FALSE
```

`TH_InitNewGame` zeros only the five project vars after upstream new-game
initialization. Never call it when loading an existing save.
`TH_FinishRivalBattle` does not downgrade COMPLETE or advance HOME/INVITED.
The Hoothoot flag is independent of the main stage.

---

## Task 1 — Isolated build and map selection

**Files:** build/config/mapjson files above; six map JSON files; map group list;
`tools/three_horizons/tests/test_map_contract.py`.
**Consumes:** existing map/layout formats and the inventory above.
**Produces:** `make THREE_HORIZONS=1`, six valid MAP_TH constants, and native-format layouts.

- [ ] Save pre-change generated constants/layout tables for the three original
  modes using separate checkouts. Capture map-group and layout indices, including
  null slots. They are the regression oracle for host tests.

```bash
make -C tools/mapjson
make generated
cp include/constants/map_groups.h /tmp/emerald-map-groups-before.h
cp include/constants/layouts.h /tmp/emerald-layouts-before.h
```

- [ ] Add real generator tests. Use `unittest`, temporary output directories,
  and `subprocess.run(..., check=True)`; test the tool, not a copied selection
  algorithm. Before the extension, the three_horizons mode must fail as unsupported.

The manifest is a JSON object with a `maps` array containing the six TH folder
names. Required extra layouts are read from those map files. The tests assert:

```python
self.assertEqual(set(manifest["maps"]), {
    "TH_Home2F", "TH_Home1F", "TH_Pallet",
    "TH_OaksLab", "TH_Route1", "TH_ViridianEntrance",
})
for record in project_maps:
    for warp in record["warp_events"]:
        self.assertIn(warp["dest_map"], project_ids)
    for connection in record["connections"] or []:
        self.assertIn(connection["map"], project_ids)
    self.assertNotIn("Blue", json.dumps(record))
self.assertEqual(original_indices_before, original_indices_after)
```

Use separate tests for invalid/missing manifest map names, missing layouts,
out-of-bounds warp IDs, and preservation of FRLG border dimensions/format.

- [ ] Add the build option after upstream game selection and before names/object
  directories are computed. Reject the option combined with FireRed/LeafGreen.

```make
THREE_HORIZONS ?= 0
ifeq ($(THREE_HORIZONS),1)
  ifneq ($(GAME_VERSION),EMERALD)
    $(error THREE_HORIZONS requires GAME_VERSION=EMERALD)
  endif
  BUILD_NAME := three-horizons
  MAP_VERSION := three_horizons
endif
```

After the upstream FILE_NAME assignment, override it to `pokemon-three-horizons`
only when enabled. After CPPFLAGS is defined, append
`-DTHREE_HORIZONS=$(THREE_HORIZONS)`. In the config header, default the macro to
0 only when undefined. Include that header from `config/general.h`.
The custom object directory must differ from the default Emerald directory.

- [ ] Extend mapjson to accept `three_horizons`. For this mode, include original
  Hoenn maps plus the manifest maps; reject other Kanto maps. For existing modes,
  exclude TH folders and otherwise preserve current selection exactly.
  Use the same predicate in header, connection, event, and group generation.
  Include Emerald layouts plus precisely the six referenced FRLG layouts;
  use existing `layout_version` to emit `isFrlg`, border width/height, and
  attribute interpretation. Do not relabel FRLG layouts as Emerald.
  Pass MAP_VERSION consistently to map generation rather than hardcoding it.
  Fail clearly when a selected map or required layout does not exist.

- [ ] Define each TH map's script table and temporary no-op event body in the
  project script include so this checkpoint can link without stock Kanto scripts:

```asm
TH_Home2F_MapScripts::
    .byte 0
TH_EventScript_MapCheck::
    end
```

Generate equivalent map tables for the other five named maps. These no-op
events are an intermediate checkpoint only and are replaced in Tasks 3–5.

- [ ] Run the host tests and clean builds for the opt-in and original modes,
  each in its own checkout. Record exit codes and compare original generated IDs.

```bash
python3 -m unittest discover -s tools/three_horizons/tests -v
make THREE_HORIZONS=1 -j2 -O all
test -s pokemon-three-horizons.gba
```

- [ ] Commit the isolated build/map selection only after those checks pass.

## Task 2 — Spawn, recovery, and map-only playable checkpoint

**Files:** `src/new_game.c`, `src/main_menu.c`,
`src/data/heal_locations.json`, project constants/module/header, TH map JSON,
`data/scripts/three_horizons/maps.inc`, `data/event_scripts.s`.
**Consumes:** Task 1 map constants and layouts.
**Produces:** a new game that can traverse all six maps and recover at home.

- [ ] Add the new project initializer and test that it zeros project vars without
  changing unrelated event state. Define the public APIs above before consumers
  reference them. Use the runtime test framework already shown in `test/script.c`.

- [ ] Add a THREE_HORIZONS branch before the `IS_FRLG` test in the new-game warp:

```c
#if THREE_HORIZONS
    SetWarpDestination(MAP_GROUP(MAP_TH_HOME_2F),
                       MAP_NUM(MAP_TH_HOME_2F), WARP_ID_NONE, 6, 6);
#else
    if (IS_FRLG)
        SetWarpDestination(MAP_GROUP(MAP_PALLET_TOWN_PLAYERS_HOUSE_2F), MAP_NUM(MAP_PALLET_TOWN_PLAYERS_HOUSE_2F), WARP_ID_NONE, 6, 6);
    else
        SetWarpDestination(MAP_GROUP(MAP_INSIDE_OF_TRUCK), MAP_NUM(MAP_INSIDE_OF_TRUCK), WARP_ID_NONE, -1, -1);
#endif
```

Use a preprocessor guard so non-project builds never reference project map constants.
Keep normal player naming/gender selection. In the custom configuration,
replace the final Birch intro text about the existing Emerald story with a
neutral first-day invitation; preserve upstream intro text in other modes.
Do not run the Emerald truck, clock, father, or Oak/Blue story triggers on TH maps.

- [ ] Append `HEAL_LOCATION_TH_HOME`, pointing to MAP_TH_HOME_1F with Mom's
  valid local ID and a clear standing tile. Reuse the source Pallet recovery
  coordinates (respawn 8,5), then verify them in-game. Set it after new-game
  initialization via `SetLastHealLocationWarp`.
  Register `LOCALID_TH_MOM` in the new Home1F object data. Audit
  mapjson's heal-location cleanup so other build modes cannot erase this
  source identifier; test generated output from fresh inputs in each mode.

- [ ] Add an explicit project include in `data/event_scripts.s`:

```asm
#if THREE_HORIZONS
    .include "data/scripts/three_horizons/maps.inc"
#endif
```

Include project constants from this assembly unit. Do not enable the whole
`.if IS_FRLG` block.

- [ ] Emulator checkpoint: walk bedroom → downstairs → Pallet → lab → Pallet
  → Route 1 → Viridian strip and back. Inspect FRLG palettes, doors, grass,
  ledges, border tiles, movement, and music. Capture map screenshots in task
  outputs. Explicitly check every retained warp in both directions.
  Fix format/boundary errors before implementing story events.

- [ ] Commit only when the map checkpoint is visibly playable. If native-format
  reuse reveals a missing engine path, diagnose that path and record the minimal
  fix; do not swap the entire game to FireRed to bypass the problem.

## Task 3 — Persistent starter choice and one-time supplies

**Files:** project module/header/constants, `data/specials.inc`,
`data/scripts/three_horizons/lab.inc`, lab JSON,
`test/three_horizons.c`.
**Consumes:** stage IDs and valid lab map.
**Produces:** exactly one of nine partners and persistent, retry-safe supplies.

- [ ] Write failing tests against the real module: all nine choices, invalid
  species, duplicate choice, occupied party, cancel/decline, and supply retries.
  Initialize/restore the fixture's real party, bag, and event variables around
  each mutating test. Example assertion sequence:

```c
EXPECT(TH_TryGiveStarter(SPECIES_CHIKORITA));
EXPECT_EQ(VarGet(VAR_TH_FIRST_PARTNER), SPECIES_CHIKORITA);
EXPECT_EQ(VarGet(VAR_TH_RIVAL_PARTNER), SPECIES_CYNDAQUIL);
EXPECT_EQ(gPartiesCount[B_TRAINER_PLAYER], 1);
EXPECT(!TH_TryGiveStarter(SPECIES_MUDKIP));
EXPECT_EQ(gPartiesCount[B_TRAINER_PLAYER], 1);
```

Also test `SPECIES_NONE`, `SPECIES_PIDGEY`, the largest u16 value, and each
regional boundary. The grant must not advance the stage on invalid/error input.

- [ ] Implement the actual species mapping, independently of party ordering:

```c
static const u16 sTHStarters[] = {
    SPECIES_BULBASAUR, SPECIES_CHARMANDER, SPECIES_SQUIRTLE,
    SPECIES_CHIKORITA, SPECIES_CYNDAQUIL, SPECIES_TOTODILE,
    SPECIES_TREECKO, SPECIES_TORCHIC, SPECIES_MUDKIP,
};
static const u16 sTHRivals[] = {
    SPECIES_CHARMANDER, SPECIES_SQUIRTLE, SPECIES_BULBASAUR,
    SPECIES_CYNDAQUIL, SPECIES_TOTODILE, SPECIES_CHIKORITA,
    SPECIES_TORCHIC, SPECIES_MUDKIP, SPECIES_TREECKO,
};
u16 TH_GetRivalStarter(u16 species)
{
    u32 i;
    for (i = 0; i < ARRAY_COUNT(sTHStarters); ++i)
        if (sTHStarters[i] == species)
            return sTHRivals[i];
    return SPECIES_NONE;
}
```

`TH_TryGiveStarter` requires INVITED, an empty party, and a valid mapping.
Call existing `ScriptGiveMon(species, 5, ITEM_NONE)`; only commit first/rival
species and PARTNER after MON_GIVEN_TO_PARTY. Set FLAG_SYS_POKEMON_GET.
Do not send a first partner to the PC or change existing starter functions.

- [ ] Implement supply delivery as three idempotent operations tracked by the
  mask. Grant five balls, then two potions, then the research Dex. Set each bit
  only after its actual operation succeeds. If an item insertion fails, retain
  completed bits and allow retry; never repeat a completed quantity.
  Enable the National Pokédex through the existing helper and set
  FLAG_SYS_POKEDEX_GET. Keep the starter's normal caught/seen registration.
  Return TRUE only when the mask is 7.

- [ ] Add script wrappers to `data/specials.inc` under the project guard.
  Keep the low-level boolean functions callable by tests.
  Use script-local menu labels; this example is the complete Kanto list:

```asm
TH_Lab_KantoMenu::
    lock
    faceplayer
    dynmultichoice 0, 0, FALSE, 3, 0, DYN_MULTICHOICE_CB_NONE, TH_Text_Bulbasaur, TH_Text_Charmander, TH_Text_Squirtle
    goto_if_eq VAR_RESULT, MULTI_B_PRESSED, TH_Lab_Cancel
    @ Dispatch index 0/1/2 to explicit SPECIES constants, never to saved legacy indices.
```

Define analogous Johto and Hoenn lists using the approved trios. Common
confirmation text names the selected Pokémon, uses Yes/No, and calls
TH_ScriptGiveStarter only on Yes. Cancel/No returns to browsing with no mutation.
If the partner already exists, display the repeat line and do not open a grant menu.
Every exit uses `release` or `releaseall` as appropriate.

- [ ] Test actual text/menu cancellation in mGBA, including B at each level and
  leaving/reentering the lab. Verify all nine first partners using separate saves.
  Save/reload after a confirmed choice and after rewards. Check correct Dex entries.

```bash
make THREE_HORIZONS=1 check TESTS="Three Horizons" -j2
make THREE_HORIZONS=1 -j2 -O all
```

- [ ] Commit the starter and supply flow after both automated and visual checks.

## Task 4 — Cozy introduction and Robin's battle

**Files:** `data/scripts/three_horizons/home.inc`, `town.inc`, `lab.inc`,
`text.inc`; home/town/lab map JSON; `src/data/trainers.party`;
project module; `test/three_horizons.c`.
**Consumes:** starter state, supply mask, and mapping.
**Produces:** the approved scenes and a battle that advances after either outcome.

- [ ] Write progression tests: HOME cannot finish the battle; PARTNER advances
  to BATTLE_DONE; repeated completion is unchanged; COMPLETE is never downgraded.
  Confirm legacy VAR_STARTER_MON retains its previous value in every project test.

- [ ] Implement home, TV, and invitation scenes. Use the approved dialogue tone:
  Mom: "You've checked your bag three times. Go on—Oak's waiting."
  Robin: "You're late! ...Okay, I'm early. I couldn't sleep."
  TV summarizes the three-region research exchange in two short text boxes.
  Stage INVITED is set before control returns after Robin's first conversation.

  Add Robin's short walk toward the lab after the fixed house-exit encounter.
  Derive object visibility from stage on every map entry. No global follower
  system. If the player approaches Oak without the invitation event, Oak supplies
  the missing invitation context and advances to INVITED, preventing a sequence lock.

- [ ] Position the three lab displays using the existing three Poké Ball object
  sites. Label them Kanto/Johto/Hoenn and bind them to Task 3 menus. Oak explains
  Elm, Birch, and the research purpose before the player can commit a starter.
  After choosing, finish Robin's response and supply delivery before directing
  the player outside.

- [ ] Append nine Robin trainer entries, one per possible rival species.
  Use the existing trainer format and a generic Youngster presentation. Example:

```text
=== TRAINER_TH_ROBIN_CHARMANDER ===
Name: ROBIN
Class: Youngster
Pic: Youngster
Gender: Male
Music: Male
AI: Check Bad Move

Charmander
Level: 5
IVs: 0 HP / 0 Atk / 0 Def / 0 SpA / 0 SpD / 0 Spe
```

The format's gender field controls trainer metadata; story dialogue remains
gender-neutral as designed. Use default level-up moves, no held items, no EVs,
no battle gimmicks. Generate the other eight entries with their explicit species
and stable TRAINER_TH_ROBIN_* identifiers; do not edit any existing trainer entry.

- [ ] At the lab exit, select the appropriate trainer by saved rival species.
  Use the established early-rival battle path:

```asm
    trainerbattle_earlyrival TRAINER_TH_ROBIN_CHARMANDER, RIVAL_BATTLE_HEAL_AFTER, TH_Text_RobinLost, TH_Text_RobinWon
    @ Capture VAR_RESULT immediately: TRUE means the player lost.
```

Each species branch rejoins one completion handler. Show the correct reaction,
heal both outcomes explicitly via the established party-heal routine, call
TH_FinishRivalBattle, and release control. Prevent replay by the saved stage,
not by winning alone. Check supplies are complete before unlocking Route 1.

- [ ] Guard every walkable Pallet north exit before BATTLE_DONE. At the existing
  two exit tiles (12,1 and 13,1), explain the next objective and move the player
  one tile south. Verify no bypass from a map edge, no movement lock, and no
  repeated trigger when already standing on a guard tile.

- [ ] In mGBA, deliberately win and lose each first-battle branch across the nine
  choices. Verify correct Robin species, healing, normal control, and no early
  whiteout redirect. Reenter town/lab and reload a save after each outcome.
  Mom's interaction must heal repeatedly after PARTNER without replaying gifts.

- [ ] Commit when the home-to-route progression passes.

## Task 5 — Route encounters, Hoothoot, and endpoint

**Files:** `src/data/wild_encounters.json`, route/endpoint JSON,
`data/scripts/three_horizons/route.inc`, `ending.inc`, `text.inc`;
map contract tests and project runtime tests.
**Consumes:** BATTLE_DONE and independent sighting state.
**Produces:** a catchable route, one-time clue, safe endpoint/backtracking.

- [ ] Add one encounter record for MAP_TH_ROUTE1. Use the engine's 12 land slots
  and standard rates. Assign six alternating slots per species; every slot uses
  min_level 2 and max_level 4. Existing encounter records are unchanged.

```python
mons = [
    {"min_level": 2, "max_level": 4,
     "species": "SPECIES_PIDGEY" if i % 2 == 0 else "SPECIES_RATTATA"}
    for i in range(12)
]
```

Test that only these species appear, levels stay 2–4, and this record exists only
when its project map is valid. If the encounter generator does not already filter
invalid maps, add project-map filtering without editing other encounter tables.

- [ ] Retain two friendly route NPC locations from the source map: (6,28) and
  (19,16). Replace their stock scripts with concise catching guidance and the
  unusual-sighting observation. No parcel quest or added trainer battle.
  Place Hoothoot next to an accessible tree, using the existing species overworld
  graphics mechanism; visually confirm the tile is suitable before committing.
  Its sprite and trigger positions must be recorded in the map JSON and the QA
  checklist, with no collision blocking the return route.

- [ ] Make the first Hoothoot interaction/nearby approach set
  VAR_TH_SIGHTING_SEEN only after the short observation concludes. Repeated
  interaction uses a quiet repeat line. Both branches restore control.
  It is not a battle, gift, clock check, or requirement to reach the endpoint.

```asm
TH_EventScript_Hoothoot::
    lockall
    goto_if_eq VAR_TH_SIGHTING_SEEN, 1, TH_HoothootRepeat
    msgbox TH_Text_HoothootFirst
    setvar VAR_TH_SIGHTING_SEEN, 1
    releaseall
    end
TH_HoothootRepeat:
    msgbox TH_Text_HoothootRepeat
    releaseall
    end
```

- [ ] Place Robin on the southern approach to Viridian. First conversation at
  BATTLE_DONE delivers the approved warm ending, sets COMPLETE, and releases
  control. Later visits show one short line. The row-32 boundary remains
  accessible from the south and never replays the ending. No warp or connection
  can leave the six-map set.

- [ ] Exercise catches, fleeing, empty balls, wild defeat, home healing,
  Hoothoot repeat/skip, endpoint repeat, and backtracking.
  Save → close emulator → reopen → Continue after sighting and endpoint.
  Test party rearrangement/boxing/evolution with a disposable test fixture to
  verify the stored first-partner species remains the original species.

- [ ] Commit when a complete new-game run reaches the endpoint without debugging
  shortcuts and remains playable after a cold save reload.

## Task 6 — Package and verify the playable demo

**Files:** `.github/workflows/three-horizons-demo.yml`,
`docs/three_horizons/OPENING_DEMO_TESTS.md`, `docs/SUMMARY.md`.
**Consumes:** completed opening and test tools.
**Produces:** downloadable ROM, log, checksum, source commit, and honest QA report.

- [ ] Add a workflow on the implementation branch/PR and manual dispatch,
  pinned to Ubuntu 24.04, contents:read, no cached game objects. Check out the
  actual feature commit; do not reuse the fixed baseline checkout SHA.
  Use the existing baseline dependency list, then execute:

```bash
set -o pipefail
python3 -m unittest discover -s tools/three_horizons/tests -v
make THREE_HORIZONS=1 check TESTS="Three Horizons" -j2 2>&1 | tee demo-tests.log
make THREE_HORIZONS=1 -j2 -O all 2>&1 | tee demo-build.log
test -s pokemon-three-horizons.gba
sha256sum pokemon-three-horizons.gba > pokemon-three-horizons.gba.sha256
git rev-parse HEAD > demo-source-commit.txt
git diff --exit-code
```

Save package/compiler versions. Upload ROM, ELF, map, checksums, both logs,
source commit, and QA report. On failure upload diagnostic logs but do not
publish a successful-build claim.

- [ ] Run unchanged upstream Emerald, FireRed, LeafGreen, release, and test
  jobs from independent checkouts. Do not bypass failing upstream checks.
  Compare the old modes' map IDs and layout slot ordering against Task 1's
  oracle; the appended project group must not reorder any existing content.
  Run the documentation validator after registering both planning and QA pages.

- [ ] Create the QA table with rows for nine starter choices and win/loss
  outcomes, plus four cold-save checkpoints: before choice, after choice,
  after battle, and after endpoint. Record tested commit, emulator version,
  result, and evidence. Use "not run" for missing evidence, never inferred passes.
  Automated tests cannot establish readable graphics, valid walking, or actual
  emulator cold-save behavior.

- [ ] Download the successful artifact to a new outputs/demo-opening directory.
  Verify archive/ROM hashes. Open the final playable artifact in mGBA for the
  visible checks when computer-use support permits it; otherwise ask the user
  to perform the clearly enumerated manual checks and keep those rows unverified.
  Never overwrite the baseline ROM or its save.

- [ ] Complete independent code review under the selected execution workflow.
  Fix material findings, rerun affected checks, and retain the branch as a draft
  PR until required validation is complete. Do not merge automatically.

- [ ] Deliver the ROM link, source/PR link, concise changes, test results,
  warnings, and new-save requirement. State any unrun visual tests explicitly.

## Self-review and handoff

Coverage: Tasks 1–2 establish the separate build, maps, initialization, and
recovery; Task 3 covers nine choices and persistence; Task 4 covers home, Robin,
battle outcomes, and gates; Task 5 covers route, clue, boundary, and ending;
Task 6 covers compatibility, artifact evidence, and cold-save acceptance.

Do not interpret this plan as proof that the demo works. No gameplay code was
written while preparing it. Build and emulator evidence must be collected during
execution.

Recommended execution: **Native**, implementing these dependent tasks sequentially
in this task, with an independent final review. Subagent-driven execution is an
alternative if the user prefers a separate implementer/reviewer cycle for each
task. Review this plan and choose the execution method before starting.
