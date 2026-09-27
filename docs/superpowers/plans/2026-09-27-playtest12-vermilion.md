# Playtest 12 Vermilion Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking. Preserve the user's previously selected native execution method.

**Goal:** Deliver a save-compatible Playtest 12 through Bill, Vermilion, the S.S. Anne and Lt. Surge, with the approved repairs, HM convenience, regional story and starter rebalance.

**Architecture:** Keep the existing Three Horizons checkout and reuse native FireRed map layouts with TH-owned events and trainer definitions. Repairs, HM behavior, balance and chapter scenes are independently testable changes within one integration plan because they share persistent state, party compatibility and the release ROM. Append maps and audit new event storage; preserve existing save structures and identifiers.

**Tech Stack:** pokeemerald-expansion C, event assembly, JSON maps/encounters, indexed PNG sprites, Python host checks, native engine tests, GNU Make/ARM build tools, mGBA.

**Spec:** [Approved chapter design](../specs/2026-09-27-playtest12-vermilion-design.md) and [exact starter move requirements](../specs/2026-09-27-playtest12-starter-moves.md).

**Status (2026-09-27):** Approved and implemented as a playable candidate through Surge at feature revision `a1df5843`. Final project CI passed 67 host, 126 native and 4 save tests. The independent final review's two findings were resolved. Task 5's replacement artwork was subsequently sourced from user-approved artist monicaccina; integration verification is in progress, and broad manual acceptance combinations remain unchecked; this plan is not declared fully complete. See [verification and open items](../../three_horizons/PLAYTEST_12_VERIFICATION.md) for actual evidence, build identity and coverage limits. Original product baseline `881bf5c492c91698b198bdb9c2590e7e678d3beb`; design commit `4a918c10c1`.

## Global Constraints

- Preserve the existing normal save, party, boxes, badges and rewards.
- Keep the older release and all user saves untouched.
- Append map IDs; do not renumber the existing 43 maps or grow the save structures.
- Apply only in the Three Horizons build; preserve upstream Emerald/FireRed behavior.
- All nine proposed wild starter encounters are 5%, at the exact locations/levels in the spec.
- Keep all three regional starter gifts and the existing 10% Hidden Ability rule.
- HM field use requires a conscious non-Egg compatible party member, the HM, and its badge/story gate; knowing the move is unnecessary.
- No level cap is added. The S.S. Anne stays docked throughout this playtest.
- Surge: Voltorb 24, Pikachu 24, Magnemite 25, Electrike 25, Raichu 27; Thunder Badge before reusable Shock Wave.
- No silent removal of assertions to hide corruption.
- Native execution remains selected; no merge or unrelated repository/settings changes.
- Handheld compatibility is unverified until the user's RG40XX H run succeeds.

## Review Focus

1. Repeated Continue after upgrading must not clear completed Rocket fights or regrant supplies (Task 1).
2. First-catch Dex entered while evolution/nickname callbacks are pending must preserve graphics and the caught Pokémon (Task 2).
3. Night tint must not reclaim the editor's shiny preview palette during idle frames or cursor movement (Task 3).
4. Losing to James after winning the first sequential fight must restart the pair without trapping the player or skipping the second fight (Task 5).
5. A save on the old Cerulean south ledge or a trainer's approach endpoint must still have an exit (Tasks 8, 10, 12).

## Execution conventions and ownership

Use the existing `work/three-horizons-opening` checkout on `feature/opening-demo`.
Inspect status and attached worktrees before deciding isolation; do not create
another checkout just for its name. Preserve unrelated edits and never run old
map generators across newer repaired maps. Read the spec and plan together.

Commands below run from the repository root. On Windows, use the bundled Python
for host checks. ARM builds/native tests run in the established Linux CI; do not
report them as local tests. Existing workflows are `.github/workflows/three-horizons-demo.yml`
and `.github/workflows/build.yml`. Do not install a replacement toolchain unless
the established path is unavailable.

- Host suite: `python3 -m unittest discover -s tools/three_horizons/tests -v`.
- Native targeted suite: `make THREE_HORIZONS=1 check TESTS="Three Horizons playtest12" -j2`.
- Full TH regression: `make THREE_HORIZONS=1 check TESTS="Three Horizons" -j2`.
- Save regression: `make THREE_HORIZONS=1 check TESTS="test/save.c" -j2`.
- ROM: `make THREE_HORIZONS=1 -j2 -O all`.

For every behavioral task: add the stated failing test, confirm failure against
the old behavior, implement, rerun the targeted checks, and commit that task's
files. Use actual engine/event execution for behavior; text searches alone do
not prove movement, palettes, rewards or callbacks. Small dialogue-only changes
need a script build and visual spot check, not tests that merely repeat strings.
Do not repeatedly rebuild unchanged passing work. Keep a dated evidence log.

## Task 1: Save state and one-time catching supplies

**Files:** Modify `include/constants/three_horizons.h`, `include/three_horizons.h`,
`src/three_horizons_state.c`, `src/three_horizons.c`,
`tools/three_horizons/state_manifest.json`, `data/scripts/three_horizons/lab.inc`.
Create `src/three_horizons_chapter12.c`, `test/three_horizons_chapter12.c`.
Extend `tools/three_horizons/tests/test_state_allocations.py`.

**Interfaces:** Preserve `void TH_MigrateSaveState(void)`.
Add `void TH_TryGiveChapter12Supplies(void)` as a script special; set
`gSpecialVar_Result` to TRUE only when both components are received/already received.
Store separate receipts for the two Ultra Balls and 2,000 money so a failed bag
delivery cannot duplicate money. New `TH_STATE_VERSION_12 = 0xA908` preserves
clock bit 0. All chapter state names/values go into the audited manifest before use.

- [x] Add migration tests for versions 9, 10, 11 and 12: retain party/box hashes,
  badges, gift species, trainer victories, fossil flags, clock low/high bit and
  settings; initialize only new chapter flags. A second migration changes nothing.
- [x] Add supply tests: new opening, upgraded completed opening, full ball pocket,
  money cap, partial delivery, retry and repeat visit. Two balls and 2,000 money
  are awarded at most once; cap behavior follows the native money limit.
- [x] Audit unused flags/vars and trainer ranges. Allocate distinct Bill, ship
  rival, captain, voucher, rod, Surge TM, chapter-end, sighting and receipt state.
  Update version recognition in every earlier migration branch; a version-12
  Continue must not enter the legacy reset branches.
- [x] Implement receipts and opening special; expose the same special to the
  Cerulean aide added in Task 10. Register special in `data/specials.inc`.
- [x] Run allocation, migration and supply checks; save/reload a copied legacy
  fixture twice and compare retained data. Commit the state/supply change.

## Task 2: First-catch Pokédex lifecycle repair

**Files:** Modify `src/battle_script_commands.c`, `src/pokedex.c` only where the
trace identifies the defect; extend `test/three_horizons_capture_ui.c` and
`test/three_horizons_capture_lifecycle.c`. Update the relevant negative control
in `.github/workflows/three-horizons-demo.yml` if its target code changes.

**Interfaces:** Keep `Cmd_displaydexinfo` and `DisplayCaughtMonDexPage` public
contracts; no new save state. Preserve the caught battler, pending nickname and
party/PC delivery contract.

- [ ] Reproduce from the released P11 ROM with first Pidgey and both Nidoran,
  including repeated A. Record frames at Dex creation, first visible page,
  dismissal and nickname yes/no. Trace callbacks, VBlank, task identity, BG/OBJ
  allocations and palette transitions; record the first divergence.
- [ ] Add a native regression named `Three Horizons playtest12 first catch Dex`
  that traverses the real callbacks and checks the visible page before exit,
  valid windows/sprites, and intact caught data afterward. Parametrize party
  room/full, decline/max nickname, first/repeat catch and capture evolution.
- [ ] Repair the demonstrated lifecycle defect; no skipped Dex or forced input
  delays to conceal corruption. Keep the existing successful backdrop repair.
- [ ] Run the new and existing capture suites, including a mutant restoring the
  identified defect. Capture unique screenshot paths from the candidate ROM.
  Commit after the entire transition, not only its ending, passes.

## Task 3: Shiny partner preview stability

**Files:** Modify `src/three_horizons_partner.c`; inspect
`src/trainer_pokemon_sprites.c`, `src/palette.c`, `src/three_horizons_clock.c`
and field tint ownership before changing shared code. Create
`test/three_horizons_partner_preview.c`.

**Interfaces:** Preserve `TH_OpenPartnerEditor`, `TH_OpenRewardEditor` and caught
editor entry points. Sprite/palette lifetime stays local to the editor; saved
partner options are unchanged.

- [ ] Reproduce shiny Charmander gift at daytime/night and with a tinted field
  already loaded. Compare the original starter and both badge gifts.
- [ ] Add `Three Horizons playtest12 shiny preview` checking sprite palette
  contents after every row/page, idle frames, nature/ability edits, defaults,
  cancel/reopen and confirmation; confirm summary/follower shiny agreement.
- [ ] Fix the demonstrated palette ownership/update path and release resources
  on every exit. Do not regenerate a shiny personality merely for cursor moves.
- [ ] Run preview and partner/capture regressions; inspect normal and shiny
  screenshots in both clock modes. Commit the preview repair.

## Task 4: Early scene, facing and dialogue repairs

**Files:** Modify `data/scripts/three_horizons/{home,lab,town,journey,chapter9,
chapter9_locals,playtest11_maps,playtest11_story}.inc`, affected existing TH
`map.json`/`scripts.inc` files and `src/trainer_see.c` only if native facing is
actually defective. Extend `tools/three_horizons/tests/test_rival_scenes.py`,
`test_oak_handoff.py`, `test_playtest11_maps.py`; create
`test/three_horizons_playtest12_scenes.c`.

**Interfaces:** Preserve existing script entry labels and gift/badge flags.
Town map interaction must call the supported region-map UI with field return.
Museum entry detection uses the exterior entry warp, not a flag reset by stairs.

- [ ] Reproduce the player's stuck walk pose and trainer-facing cases; add
  engine checks for final standing animation/facing, including run held during
  scene trigger. Exercise all seven outfits and follower on/off visually.
- [ ] End lab movement before dialogue, face rival/Oak at their respective
  lines, remove empty desk interaction, change sister to “my brother,” and wire
  map interaction independently. Verify region-map open/close repeatedly.
- [ ] Restrict museum greeting to external entry; add Luis' alert before swim.
  Present Brock badge before TM with recoverable bag-full receipt. Correct
  Miguel defeat text and fossil scientist zero/one/two-restored responses.
- [ ] Add the Pewter badge guide with a clear post-Brock path; verify League
  side approaches cannot bypass the eight-badge gate. Check robbed-house Rocket
  text separately instead of assigning the scientist's dialogue to him.
- [ ] Run scene and map checks, including museum stairs/re-entry and every legal
  trainer approach endpoint. Commit repairs with before/after frame evidence.

## Task 5: Jessie/James staging, art and battle fallback

**Files:** Modify `data/scripts/three_horizons/playtest11_story.inc`,
`data/maps/TH_MtMoonB2F/map.json`, `src/data/trainers.party`, existing object/trainer
graphics registration tables and their constants. Create
`graphics/three_horizons/rocket/{jessie,james}/{walking,front}.png`, `CREDITS.md`,
`test/three_horizons_playtest12_rocket.c`; extend host story checks.

**Interfaces:** Retain `FLAG_TH_ROCKET_DUO` as the completed-pair flag. Keep
existing Jessie/James trainer identifiers for save compatibility. Transient
first-win state must not let a loss to James skip either fight on retry.

- [ ] Add event tests: one/two usable members, losing first/second single,
  double loss, reverse arrival, already defeated and reload. Assert both
  victories are required, no free heal, no pass-through, follower restoration.
- [x] Import user-approved monicaccina artwork after the generation service block.
  Verify public reuse permission, preserve the source sheet and artist credit,
  convert all walking facings and separate battle fronts to native palettes.
  Runtime verification follows below.
- [ ] Stage Jessie–Meowth–James in clear tiles facing the player. Temporarily
  hide the follower while staging. Implement double battle for two usable
  party members; back-to-back Ekans/Koffing singles for one.
- [ ] After victory, display the approved blasting-off line and a brief
  disappearance effect, remove the trio together and set completion. Clear
  temporary first-win state on blackout so the pair restarts.
- [ ] Run native/event tests and inspect both approaches and both formats.
  Validate image dimensions/palette counts; commit art and encounter change.

## Task 6: Opponent team balls in one split row

**Files:** Modify `src/battle_interface.c`; create
`test/three_horizons_playtest12_team_balls.c`.

**Interfaces:** Preserve `CreatePartyStatusSummarySprites` call sites. TH
two-opponent battles place the two three-slot groups on the same row with a
gap; each group's data comes from that trainer's party, not duplicated data.

- [ ] Add native assertions for 1+1, 3+3, healthy/fainted/empty slots and sprite
  bounds. Single opponent battles must retain their original arrangement.
- [ ] Adjust creation/animation positions consistently, including entry and
  teardown; do not only move one final frame.
- [ ] Run team-ball tests; inspect Rocket introduction at normal speed and
  confirm labels fit before text advances. Commit the rendering change.

## Task 7: Forgettable HMs and untaught field use

**Files:** Create `src/three_horizons_field_moves.c`,
`test/three_horizons_field_moves.c`. Modify `include/three_horizons.h`,
`include/config/pokemon.h`, `src/party_menu.c`, `src/scrcmd.c`,
`src/field_move.c`, `src/field_player_avatar.c` and TH Cut-tree script binding.

**Interfaces:** Add `bool32 TH_CanUseFieldMove(struct Pokemon *mon, enum FieldMove move)`
and `u8 TH_FindFieldMoveUser(enum FieldMove move)`; return PARTY_SIZE when absent.
These check item ownership, native compatible learnability, conscious/non-Egg
state and chapter gates. Unsupported/not-yet-unlocked HM actions return FALSE.
Non-HM field actions retain native behavior.

- [ ] Add assertions: Cut TRUE only with HM01 + Cascade Badge + compatible live
  non-Egg; knowing Cut is neither required nor sufficient. No item, no badge,
  incompatible, fainted and Egg each return FALSE. Select correct party slot
  with several members; no mutation of their four learned moves.
- [ ] Enable HM forgetting only under TH, including level-up Rock Smash and
  summary/relearn replacement paths. Add a replacement test that actually
  replaces the move, rather than checking the config value.
- [ ] Route party-menu and field interaction checks through the same helper.
  Show the selected Pokémon in the native field animation. Map the intended
  Kanto badge checks explicitly; do not expose later HM actions in this release.
- [ ] Run HM and existing party-menu checks; verify Cut cancellation, tree
  removal, re-entry and follower behavior. Commit the HM change.

## Task 8: Chapter map manifest and Bill route

**Files:** Create `tools/three_horizons/chapter12_maps.json`,
`data/scripts/three_horizons/chapter12_bill.inc`,
`tools/three_horizons/tests/test_chapter12_maps.py`. Modify
`data/maps/map_groups.json`, `tools/mapjson/three_horizons_maps.json`,
`data/scripts/three_horizons/maps.inc`, `src/data/trainers.party`,
`data/maps/TH_Cerulean/{map.json,scripts.inc}` and chapter12 engine tests.

**Map naming contract:** Clone each source named below to `TH12_` plus its source
name with `_Frlg` removed; use map constants generated from those names. Store
source, name, id, layout and script_owner in the manifest. Each cloned map owns
`map.json` and `scripts.inc`; reuse layouts unless a tested collision repair
requires a new TH layout. Preserve source warp-slot ordering but rewrite every
destination to a supported TH map. No executable FRLG scripts may leak through.

**Sources for this task:** `Route24_Frlg`, `Route25_Frlg`,
`Route25_SeaCottage_Frlg`. Later tasks append their maps to the same manifest.
**Interfaces:** `TH12_Bill_Rescue`, `TH12_Bill_Talk`,
`FLAG_TH12_BILL_RESCUED`; ticket delivery is separate from rescue completion.
Existing bridge rival remains owned by the earlier chapter.

- [ ] Snapshot all 43 existing map indices in a new immutable baseline fixture.
  Add manifest checks for unchanged IDs, resolvable scripts, valid warps,
  passable approach endpoints and a return path from every reachable component.
- [ ] Add the bridge sequence/recruiter and Route 25 trainers using levels
  16–21. Test sequential bridge rewards for loss/retry and repeat visits.
- [ ] Implement Bill rescue with a retryable S.S. Ticket grant and the approved
  regional observations. Guard reward flags on actual delivery, not dialogue.
- [ ] Run the host map suite and native Bill reward tests. Walk Cerulean ↔ Bill
  from a legacy save and a fresh chapter state. Commit the connected Bill slice.

## Task 9: Starter types, move buffs and learnsets

**Files:** Modify `src/data/pokemon/species_info/gen_{1,2,3}_families.h`,
`src/data/moves_info.h`, `src/pokemon.c`, `src/data/trainers.party`.
Create `src/data/pokemon/level_up_learnsets/three_horizons.h`,
`test/three_horizons_starter_balance.c`,
`tools/three_horizons/tests/test_starter_balance.py`.

**Interfaces:** TH-only arrays named `sTH<Species>LevelUpLearnset`, selected by
the species data. Include the new header after native learnsets; do not replace
the entire generation's learnset header or affect unrelated species/forms.
Use the approved move appendix as the exact requested entry set.

- [ ] Add data-driven native checks for each approved species type, original
  pre-evolutions, Leaf Blade/Blaze Kick 95, Muddy Water 95/100 and Sky Uppercut
  100 accuracy. Assert unchanged move effects/categories and saved mon fields.
- [ ] Merge requested move levels into native lists, retaining unrelated moves
  and level-1 entries. Check sorted terminated lists, every requested pair,
  canceled evolution access, multiple learns at one level, and Flash Cannon
  retained alongside Blastoise's level-36 Spike Cannon.
- [ ] Gate types and move values with TH; select custom arrays only for approved
  species. Update existing Grovyle/Sceptile rival moves where their level makes
  the Dragon move eligible. No forced replacement of an existing team's moves.
- [ ] Run native balance/relearn tests and inspect existing-save summaries.
  Verify all six Power items add 8 EVs in their named stat while preserving
  the defeated species' yield, per-stat/total caps and Macho Brace behavior.
  Compile upstream modes during integration to prove the changes remain gated.
  Commit the rebalance.

## Task 10: Vermilion travel, services and encounter tables

**Files:** Create `data/scripts/three_horizons/chapter12_vermilion.inc`, new maps
under the Task 8 naming contract and `tools/three_horizons/tests/test_chapter12_encounters.py`.
Modify the chapter manifest/map groups/registry, `src/data/wild_encounters.json`,
`src/data/trainers.party`, `data/maps/TH_Cerulean/{map.json,scripts.inc}`,
Cerulean bike-shop script and `src/three_horizons_chapter12.c`.

**Sources:** Route5_Frlg, Route5_SouthEntrance_Frlg, Route6_Frlg,
Route6_NorthEntrance_Frlg, UndergroundPath_NorthEntrance_Frlg,
UndergroundPath_NorthSouthTunnel_Frlg, UndergroundPath_SouthEntrance_Frlg,
VermilionCity_Frlg, VermilionCity_Mart_Frlg, VermilionCity_PokemonCenter_1F_Frlg,
VermilionCity_PokemonFanClub_Frlg and VermilionCity_House1/2/3_Frlg. Unimplemented
doorways such as daycare or upper floors must have an explicit safe interaction
instead of a warp into an unconverted map.

**Interfaces:** `TH12_Vermilion_OldRod`, `TH12_FanClub_Voucher`,
`TH12_Cerulean_CatchUpSupplies`; independent receipts for rod/voucher/redemption.
Call Task 1 supply special, not a second grant implementation.

- [ ] Test old Cerulean south-ledge positions have a path to a valid return;
  test route gates from each approach, including with the follower behind.
- [ ] Connect routes and underground, safe Saffron/Route11/Diglett boundaries,
  Center heal/blackout, Mart stock and individual local dialogue. Add route
  trainers at 18–23 and ordinary Kanto encounter tables for the new routes.
- [ ] Add Old Rod, voucher and bike redemption; test full bags, revisits,
  already-owned reward and saving between grant/redemption. Place catch-up aide
  where a continuing Cerulean player can reach them without replaying the intro.
- [ ] Install all nine 5% starter placements with exact levels from the spec in
  day/night/fallback tables. Preserve other unique existing species and the
  current Mt. Moon Clefairy 5% / Makuhita 1% rates. Test each method totals 100%
  and each new starter is reachable without Surf before Surge.
- [ ] Walk Cerulean → Vermilion → Cerulean; fish with Old Rod; verify blackout
  returns to the last visited supported Center. Commit the travel/services slice.

## Task 11: S.S. Anne, rival and captain

**Files:** Create `data/scripts/three_horizons/chapter12_ship.inc`; append maps
to chapter manifest/groups/registry. Modify `src/data/trainers.party`,
`src/three_horizons_chapter12.c`, `include/three_horizons.h`, chapter12 tests.

**Sources:** All existing `SSAnne_*_Frlg` maps: Exterior, Deck, Kitchen,
CaptainsOffice, corridors 1F/2F/3F/B1F, rooms 1F 1–7, 2F 1–6, B1F 1–5.
**Interfaces:** `TH12_Ship_Board`, `TH12_Ship_Rival`, `TH12_Captain_Talk`,
`TH12_Ship_Heal`; separate rival-victory and HM-delivery receipts. Rival party
selection consumes `VAR_TH_RIVAL_PARTNER` without rerolling it.

- [ ] Add tests for no-ticket boarding denial, valid ticket entry, every room's
  return warp and deck/captain reachability with trainer approach endpoints.
- [ ] Implement ship trainers/items at 20–25, healing cabin and one coherent
  migration observation scene. Rival has its appropriate evolved original
  partner; loss returns to Center, victory persists, repeat approach is safe.
- [ ] Implement captain interaction and one-time HM01. A full bag leaves the
  reward claimable. Keep boarding available after HM receipt and after Surge.
- [ ] Verify rival branches for all nine original partners, loss/retry, healing,
  every cabin exit, and Cut access with an untaught compatible member.
  Commit the complete ship slice.

## Task 12: Surge puzzle, battle and chapter end

**Files:** Create `data/scripts/three_horizons/chapter12_gym.inc`,
`data/maps/TH12_VermilionCity_Gym/{map.json,scripts.inc}` from
`VermilionCity_Gym_Frlg`, `test/three_horizons_surge.c`; modify manifest/groups,
`src/three_horizons_chapter12.c`, `include/three_horizons.h`, `src/data/trainers.party`.

**Interfaces:** Script entries `TH12_Surge_Switch`, `TH12_Surge_Battle`,
`TH12_Surge_Reward`, `TH12_Chapter_End`. Puzzle helper
`bool32 TH12_AreSwitchesAdjacent(u8 first, u8 second)` uses the actual trash-can
grid, not adjacent numeric IDs. Native badge03 state plus separate TM receipt.

- [ ] Exhaustively test switch choices: second is orthogonally adjacent and in
  bounds; wrong second resets; success opens the barrier; leaving/re-entering
  produces the intended solvable state. Test paths with every trainer endpoint.
- [ ] Implement Cut gate and puzzle; keep entrance/leader paths open after
  trainer movement. Define Surge's exact five species/levels from the spec,
  legal moves and the ordinary loss/retry path.
- [ ] Award badge before reusable Shock Wave, recover bag-full grants and
  prevent repeat rewards. Add the aide's third-badge chapter-ending exchange.
- [ ] Verify loss, victory, fresh reload, barrier state, TM repeat use and safe
  future-route boundaries. Commit the playable chapter endpoint.

## Task 13: Visible migration scenes

**Files:** Create `data/scripts/three_horizons/chapter12_sightings.inc`; modify
`data/maps/TH_ViridianForest/map.json`, `data/maps/TH_MtMoonB2F/map.json`,
their scripts and the relevant Rocket dialogue in `chapter9_locals.inc`.
Extend chapter12 map/scene tests. Verify the screenshot chamber against actual
warp destinations before placing the Mt. Moon objects; change that chamber's
map if the observed first-ladder destination is not B2F.

**Interfaces:** `TH12_Forest_Treecko`, `TH12_Forest_Shroomish`,
`TH12_Moon_Gathering`; independent sighting receipts, never fossil/gift flags.
Bill/ship dialogue from Tasks 8/11 references these reports without requiring them.

- [ ] Identify clear staging tiles and test paths to the chamber's ladder,
  trainer and item with all scene objects present, including follower on/off.
  Check the engine's active-object/sprite budget with all nearby actors visible;
  no story sprite may displace the player, follower, trainer or item object.
- [ ] Add Treecko/Shroomish forest scenes and three Clefairy circling Makuhita.
  Use native species sprites/cries and bounded collision-safe motion. Keep
  Hoothoot, ordinary encounters and the research-only nature of the sightings.
- [ ] Connect Rocket/boss observation dialogue and professor-aide reactions;
  test first/repeat entry and reload without forced capture or story blockage.
- [ ] View the scenes at normal speed, confirm all exits remain usable and
  commit the story slice.

## Task 14: Integrated verification and release

**Files:** Update `.github/workflows/three-horizons-demo.yml` to include new
tests/evidence as needed. Create `docs/three_horizons/PLAYTEST_12.md`,
`PLAYTEST_12_VERIFICATION.md`, `PLAYTEST_12_ENCOUNTERS.md`; adapt the current
encounter export into `tools/three_horizons/export_encounters.py` with a source
revision argument. Package only into a new Playtest 12 output directory.

**Interfaces:** ROM, ELF, map and source hash must come from the same successful
build. Final archive contains ROM, checksum, source revision, continuation guide,
encounter tables, starter reference, verification evidence and known limitations.

- [ ] Run the host suite, all TH native tests, save tests, ROM build and upstream
  compatibility workflows. Fix failures at their owning task; preserve useful
  negative controls instead of deleting checks to obtain green results.
- [ ] Run a copied P11 Cerulean save through Bill, travel, ship, untaught Cut and
  Surge. Check old data, gifts, fossils and Dig remain correct. Save, cold boot
  and Continue twice. Separately run fresh opening and Rocket one/two-member
  paths, including max names, Dex rapid-A and shiny gift previews.
- [ ] Inspect exact-ROM screenshots for all repaired visuals and new scenes.
  Keep unique output names to avoid stale image previews. Reuse no emulator
  state from an older ROM; use normal save files for upgrade testing.
- [x] Perform one independent final review using the preserved native-execution
  workflow. Resolve actionable defects and rerun affected checks only; no
  subagent-per-task expansion unless the user changes the execution method.
- [x] Generate final encounters from the actual packaged source and validate
  totals. Write continuation-first beta steps and optional fresh-game checks.
  Explain Power-item EVs, duplicate nicknames, story vs wild sightings and the
  new types without claiming an unperformed RG40XX H hardware test.
- [ ] Produce a new archive with verified SHA-256 and exact build revision.
  Update the existing draft PR to describe final scope, retain its attachment,
  do not merge. Deliver download links and remaining limitations honestly.

## Coverage self-review

Every approved spec section maps to a task: saved data and supplies (1), capture
display (2), preview (3), early repairs (4), Rocket scene/art (5), ball row (6),
HMs (7), Bill (8), starter balance (9), south route/services/encounters (10), ship
(11), Surge/end (12), visible story (13), evidence/package (14). Review-focus
cases have explicit owning tests. No user-specified feature is deferred merely
to reduce this plan's size; later legendary encounters and future routes remain
outside the approved chapter.
