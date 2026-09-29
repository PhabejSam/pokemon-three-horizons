# Playtest 13 — The Road to Lavender Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development or superpowers:executing-plans to implement this plan task-by-task, when the user explicitly requests implementation and selects an execution method; the design/plan approval recorded below is already given. Steps use checkbox (`- [ ]`) syntax for tracking. **Current authorization is planning only. STOP AFTER THE PLAN.**

**Goal:** Repair the reported Playtest 12 issues and deliver the approved post-Surge journey through Lavender's first Pokémon Tower sequence, preserving Playtest 12 battery saves.

**Architecture:** Retain the existing opt-in Three Horizons layer, native Kanto assets, field-move framework, trainer generation, and save blocks. Append chapter maps and use audited existing persistent slots for a small authored Research Gear system. Keep scene scripts, research state, research presentation, and rematch policy separate; do not replace the engine or introduce a general quest framework.

**Tech Stack:** C/GBA, assembly event scripts, JSON maps and encounter tables, Python host checks, native battle/save tests, existing Linux CI, mGBA manual acceptance.

**Spec:** [Approved Design Bible](../specs/2026-09-28-playtest13-lavender-design.md), including **§36, Approved Review Addendum — 2026-09-28**. Historical §§1–35 remain byte-for-byte preserved as the original file prefix (original SHA-256 `65c7699beb0e7eba62c7efb50c758ef6145a82f4646351de8efae6ad7d780579`; this is not the checksum of the amended file). The accompanying planning brief supplies workflow and the 24 separate repair-task requirement.

**Review status:** The user approved the existing 41-task plan subject to this focused correction/addendum. The corrected plan retains 41 tasks. This revision is documentation only; the explicit instruction remains **DO NOT IMPLEMENT GAME CODE, DO NOT REBUILD, and STOP after reporting the corrections**. No renewed repository exploration was performed for this review patch.

## Global Constraints

- "Use the existing Three Horizons worktree/branch and preserve the current development history."
- "Preserve Playtest 12 battery saves."
- "Do not require a New Game for Playtest 13."
- "Migration must be idempotent."
- "Audit flags/vars before allocating Research Gear / photo / chapter state."
- "Append map IDs; do not renumber existing maps."
- "Preserve upstream Emerald/FireRed/LeafGreen compatibility."
- "Do not enable the full later-generation Pokédex."
- "No real trading is required."
- "Calls must be event-driven."
- "DO NOT save literal screen captures."
- "Do not implement a free-camera screenshot system."
- "Do not silently remove failing assertions."
- "Do not claim gPSP compatibility."
- "STOP AFTER THE PLAN."
- Rocket encounter: 2+ usable conscious Pokémon use the existing double battle; exactly 1 uses consecutive Jessie/Ekans then James/Koffing singles without healing.
- Field-use HMs require ownership, the badge/story gate and a conscious compatible non-Egg party member; neither knowing the move nor a free move slot is required.
- Research Photos include an authored visual tableau plus metadata; only tiny photo IDs/flags are saved. A demonstrated GBA limitation must be documented before any proposed text-only fallback.

The chapter ends at the unidentified ghost/Silph Scope requirement. Celadon, Erika, Rocket Hideout, Tower resolution, Saffron, Silph Co., Sabrina, and the phenomenon's explanation remain future work. Preserve existing starter gifts, rare starters, 10% eligible wild Hidden Ability behavior, trainers, monicaccina credits/art, and previous repairs unless this Bible explicitly changes them.

## Review Focus

1. **P12 saves with completed or partially claimed rewards, including saves aboard the ship:** preserve every old receipt and escape route; migrating twice or updating the clock must not reset them. Tests: Tasks 1, 8, 25, 41.
2. **Cut with a compatible follower, another party user, or no follower, then refresh/reload:** sprite, object identity, collision, and session regrowth must agree. Tests: Task 18; reused in Tasks 34, 36, 41.
3. **Interruptions at event boundaries:** walking out, blackout, full bag, menu exit, rapid A presses, and cold Continue cannot duplicate gifts/photos/calls or strand controls. Tests: Tasks 8, 10, 24, 30–35, 39–41.
4. **Rematches with unusually low/high parties and nonstandard battles:** no level underflow, illegal evolution/ability/moves, stale rematch state, or changes to bosses/first fights. Tests: Task 27, with Task 23's move-slot cases. Task 21 also covers usable-party counts and retries in both Rocket formats.
5. **Imported Kanto maps and graphics under an Emerald build:** use Kanto interaction behavior, valid TH destinations, stable map indices, and scene-specific collision; do not mistake a source-text assertion for visual or runtime proof. Tests: Tasks 2–6, 11, 14–15, 33–40; upstream matrix in Task 41.

## Inspected baseline and evidence limits

- Repository: `PhabejSam/pokemon-three-horizons`; existing checkout `work/three-horizons-opening`; branch `feature/opening-demo`.
- Local and GitHub PR #2 head inspected: `f49d3bd17a604d4593ad589b330018f5e911ecbc`. PR remains draft and unmerged. Do not reset, rebase, merge, or open another PR for this planning deliverable.
- Tested P12 feature revision: `f6dc5b36c0ed9ea71b10a93a69af2e0f68d4bcd0`; compiled/test revision: `d8da3c365b74a0bd87099fb4e983e32f8d0e0c03`; ROM SHA-256: `2191ebf684fb829cc86d4bc8638a11ee5aa535a9c88dbd47f8b3e96ce38f312d`.
- User reports completing that chapter through Surge on PC/mGBA and Anbernic RG40XX H/VBA-Next, including normal in-game save and Continue. Attribute this to the user; it is P12 evidence, not P13 acceptance. gPSP is not a supported compatibility claim.
- Pre-existing local state: modified `src/data/heal_locations.json` and untracked `.th-bnqjfv2s/`. Preserve both; never stage them incidentally or clear the temporary directory to make status clean.
- This planning pass inspected source, maps, tests, configuration, previous verification documents, and branch state. It did **not** reproduce the reported visual defects in an emulator or run a new build. Runtime root causes remain hypotheses until the task's reproduction step proves them.

### Existing implementation versus the requested behavior

| Area | Observed source | Consequence for implementation |
|---|---|---|
| State/version | `src/three_horizons_state.c` recognizes versions 9–12; `src/three_horizons_clock.c` writes version 12 into the clock's high word | Update both together. A naive new version can enter older migration branches and clear progress. |
| Allocation | P12 owns `0x265..0x2BB`; `0x2BC` begins active engine flags | Do not extend that contiguous range. Select unused slots by repository-wide ownership audit. |
| Bill | `TH12_Bill_OnEntry` clears `FLAG_TEMP_2`; entering the machine sets that temporary flag | Use durable in-progress state and reconstruct objects on entry. |
| Route 5 | TH Day Care doorway currently points back to `MAP_TH12_ROUTE5`, warp 0, the underground doorway | Create a TH Day Care interior with reciprocal warps, preserving outdoor warp indices. |
| Saffron | `TH12_SaffronClosed` is a message script | Dialogue alone is not a traversal gate. Add coordinate/path enforcement for both directions. |
| Ship | Ticket coordinate check exists; boarding NPC only requests ticket; rival is immediately removed; captain calls `faceplayer`; text promises permanent docking | Separate ticket, staging, and departure tasks; explicit P13 supersession of P12 docking tests is required. |
| Cut | `data/scripts/field_move_scripts.inc` uses `VAR_LAST_TALKED` after follower movement and removes the object; `src/fldeff_cut.c` resumes the script after animation | Instrument target identity and refresh lifecycle, compare working Vermilion tree with failing trees; no unproven per-map hide-flag patch. |
| Trainer RUN / SELECT | `B_RUN_TRAINER_BATTLE` is TRUE (whiteout); `B_MOVE_REARRANGEMENT_IN_BATTLE` is GEN_LATEST; existing SELECT handler is gated to pre-Gen4 | Prefer TH-only configuration of native behavior; test slot-dependent state and normal wild escape. |
| Vs. Seeker | `src/vs_seeker.c`, `docs/tutorials/vs_seeker.md` already exist; `I_VS_SEEKER_CHARGING` is 0; native rematch tables have special-trainer index assumptions and 100 fixed saved slots (`MAX_REMATCH_ENTRIES`) | Adapt native scan/response and battle path; bypass charge only for TH. Check table/storage capacity before adding entries. |
| Trainer generation | `CreateNPCTrainerPartyFromTrainer` calls `GenerateMonFromTrainerMon`; entries carry fixed levels | Add a narrow TH rematch overlay before generation, not a new global trainer engine. |
| Bikes | Both key items and `ItemUseOutOfBattle_Bike` exist, including follower handling; shop currently grants Mach only | Preferred two-item approach is supported in principle; prove safe switching/partial delivery. |
| Species | `include/config/species_enabled.h` already enables all generation families and cross-evolutions; Primeape's source has Rage Fist ×20 conditional evolution | Preserve compiled IDs/save dimensions. Restrict TH availability, audit effective release configuration, and prove the move-use counter at runtime. |
| Flash | `TH_FieldMoveUnlocked` currently allows Cut only | Extend Cut's ownership/compatibility policy to Flash: no learned HM move or free move slot is needed; other HMs stay locked. |
| Research | P12 has forest/cave/ship sighting flags and authored scenes; no Research Gear UI | Import only verified historical observations, never invent old photos. |
| Map assets | Native `_Frlg` assets exist for Diglett's Cave, Route 2 facilities, Routes 9/10, Rock Tunnel, Lavender, Tower | Clone into appended TH13 maps; do not route gameplay into unadapted native scripts. |

## Technical conflicts, bounded decisions, and execution gates

These are documented implementation constraints, not changes to the approved design.

1. **Compile-time species restriction versus P12 saves.** Globally disabling generations now can alter species/Dex storage and IDs. Retain the existing compilation configuration and enforce the approved Gen I–III-family availability in TH encounters, gifts, trades, trainer additions, and evolution choices. Audit and record exceptions already present; do not enable new unrelated families. This satisfies the availability rule without a save-format conversion.
2. **Flag capacity.** There is no verified contiguous P13 allocation yet. Task 1 must produce the exact allocation manifest from unused aliases and literal/reference scans. If sufficient genuinely unused space cannot be found, stop that task and present the measured conflict; do not borrow active engine flags or grow save blocks silently. Research uses a bounded set of flags, no saved strings or framebuffers.
3. **Native rematch layout.** Tutorial advice to insert rows before Wally can shift existing rematch indices. Do not follow that blindly. Use a TH-only table within the existing fixed capacity and explicit special-trainer checks, with stable IDs for already shipped content. If the eligible trainer count exceeds capacity, document the count and obtain a decision rather than silently omitting trainers or resizing saves.
4. **New departure rule versus old saves.** P12 completed saves did not have a departure receipt. Initialize them to docked; on their next eligible final exit, show the warning and perform departure. Never auto-depart while loading an old save or while the player is inside. Once departed, repair only an impossible saved-inside state to the safe dock landing; do not globally warp valid saves.
5. **Research Gear access choice.** Use an unlocked `RESEARCH GEAR` entry in the existing Start menu, with Calls, Research Log, and Photos. The aide awards the feature with a durable receipt; this avoids allocating a new global item ID and does not require a PokéNav clone. Field Camera remains an authored-scene prompt. This is presentation wiring within the approved design, not an additional feature.
6. **Balance details left open by the Bible.** Plan defaults: Flash/gear after Surge using the Bible's suggested 10 registered Pokémon; count caught species using the native Pokédex count (not ten party members or ten encounters). The aide states progress and the exact requirement; nearby already-open areas make it achievable, and the player can always return to them. If the reachability audit demonstrates a technical progression conflict, record it before changing the requirement. First activation is delivered once. Diglett's Cave land mix 70% Diglett / 10% Dugtrio / 10% Phanpy / 10% Whismur; Route 9 Mareep 5%; Rock Tunnel Aron 5% and Dunsparce 5% on each floor, retaining Kanto species for remaining slots. Validate slot weights and sensible native levels before committing; document final tables. No random-sampling claim proves exact rates.
7. **Rematch balance defaults.** Eligible ordinary defeated trainers use `clamp(highest non-Egg party level - 10, original strongest level, progression cap)`, with signed arithmetic and cap at least the floor. Proposed caps: before Surge 24, three badges 35, four 45, five 55, six 65, seven 75, eight 100. A team member keeps its original offset from its team's strongest member, minimum level 1. Authored evolution tiers improve teams only when valid at the target level; do not blindly auto-evolve branched species. These numbers are proposed tuning, not values claimed to be in the Bible.
8. **Lavender boundary.** Use the real unidentified-ghost barrier and an appropriate chapter completion notice. Keep the westward Celadon connection as a future extension without accessible unfinished maps or false beta-road dialogue. Record the exact map boundary in the candidate guide; do not build Route 8/Celadon to solve a scope boundary.
9. **Personal save artifact.** The user's exact P12 battery save must be available before release migration acceptance. Locate the correctly named file with the user if necessary, back it up, and work only on a copy. Synthetic fixtures supplement it; they cannot be reported as the user's save. This does not block implementation planning.

## File responsibilities and command conventions

All paths below are relative to the existing repository root. `M(Name)` means exactly `data/maps/Name/map.json` and `data/maps/Name/scripts.inc`; listed new map names are **create**, not claims that files already exist. Layout changes get private TH copies of `map.bin`/`border.bin` plus `data/layouts/layouts.json` registration, never edits to a shared FRLG layout that change upstream games.

| Responsibility | Existing or planned files |
|---|---|
| Persistent ownership/migration | Modify `include/constants/three_horizons.h`, `src/three_horizons_state.c`, `src/three_horizons_clock.c`, `tools/three_horizons/state_manifest.json`, `test/three_horizons_state.c`; extend `tools/three_horizons/tests/test_state_allocations.py` |
| Early repairs | Existing `data/scripts/three_horizons/chapter9_locals.inc`, `chapter9.inc`, `playtest11_maps.inc`, `playtest11_story.inc`, `chapter12_bill.inc`, `chapter12_vermilion.inc`, `chapter12_ship.inc`, `chapter12_locals.inc`, `chapter12_sightings.inc`, `chapter12_gym.inc`; relevant maps listed per task |
| Research state/data | Create `include/three_horizons_research.h`, `src/three_horizons_research.c`, `src/data/three_horizons_research.h`, `test/three_horizons_research.c` |
| Research presentation | Create `src/three_horizons_research_menu.c`; modify `src/start_menu.c`; create `test/three_horizons_research_ui.c` |
| Chapter script integration | Create `data/scripts/three_horizons/chapter13_research.inc`, `chapter13_route2.inc`, `chapter13_routes.inc`, `chapter13_rock_tunnel.inc`, `chapter13_lavender.inc`, `chapter13_tower.inc`; register includes in `data/event_scripts.s` and specials in `data/specials.inc` as needed |
| Map/encounter ownership | Create `tools/three_horizons/chapter13_maps.json`; append `data/maps/map_groups.json` and `tools/mapjson/three_horizons_maps.json`; modify `src/data/wild_encounters.json`, `src/data/heal_locations.json` only for intentional chapter additions after reconciling its pre-existing edit |
| Rematch policy | Create `src/three_horizons_rematches.c`, `src/data/three_horizons_rematches.h`, `test/three_horizons_rematches.c`; narrow hooks in `src/vs_seeker.c`, `src/battle_setup.c`, `include/three_horizons.h` |
| Behavior regressions | Create `test/three_horizons_playtest13_repairs.c`, `test/three_horizons_playtest13_battle.c`, `test/three_horizons_playtest13_scenes.c`; reuse existing field-move, capture, evolution, training tests |
| Host contracts | Create `tools/three_horizons/tests/test_playtest13_repairs.py`, `test_chapter13_maps.py`, `test_chapter13_encounters.py`, `test_chapter13_research.py`; static checks support runtime acceptance, not replace it |
| Release documents | Create `docs/three_horizons/PLAYTEST_13.md`, `PLAYTEST_13_ENCOUNTERS.md`, `PLAYTEST_13_EVOLUTION_QA.md`, `PLAYTEST_13_VERIFICATION.md` |

Use the existing Linux CI for ARM compilation/native execution; the local Windows environment has no established ARM toolchain. Commands here are execution instructions, **not checks run during this planning pass**:

```sh
# Host contracts (mapjson prerequisite where needed)
make -C tools/mapjson
python3 -m unittest discover -s tools/three_horizons/tests -v
# Focused host example
python3 -m unittest discover -s tools/three_horizons/tests -p test_playtest13_repairs.py -v
# Focused new native tests; give every new test this searchable prefix
make THREE_HORIZONS=1 check TESTS="Three Horizons playtest13" -j2
# Integration gates
make THREE_HORIZONS=1 check TESTS="Three Horizons" -j2
make THREE_HORIZONS=1 check TESTS="test/save.c" -j2
make THREE_HORIZONS=1 -j2 -O all
```

Focused test steps below name a test suffix; run `make THREE_HORIZONS=1 check TESTS="Three Horizons playtest13 <suffix>" -j2`. Require at least one test and zero failures, never accept "No tests found". Host checks use the named file with unittest discovery. Before a behavior fix, run its new test against old behavior and record the expected failure; after implementation rerun for PASS. A visual-only task uses a reproducible before/after capture and script build instead of a test that merely repeats its implementation. Commit only that task's intended files after verification; suggested commit subjects are provided. Batch full builds at phase gates, not after every text edit. Keep exact logs/revision and distinguish host, native, manual, and user-hardware evidence.

## Recommended execution order

1. Task 1 establishes immutable baseline, allocation, and migration contracts.
2. Task 18 (global Cut) first among repairs; Tasks 22–24 next for battle/capture regressions. Then complete all remaining Tasks 2–25. Shared script files make serial execution preferable.
3. Tasks 26–29 implement economy, rematches, bikes, and species/evolution policy independently of new story maps.
4. Tasks 30–32 deliver research state, UI, and safe event-driven calls before scenes consume them.
5. Tasks 33–38 open and test the route in travel order; Task 36 is optional in-game, mandatory implementation/acceptance.
6. Tasks 39–40 deliver Lavender/Tower and the precise endpoint.
7. Task 41 performs whole-chapter and save/upstream acceptance and packages the candidate. No release claim before those gates.

Tasks are independently reviewable units. Repair letters A–X below map one-to-one to the Bible; none is silently absorbed or omitted.

## Task 1: Allocate state and preserve P12 migration

**Files:** Persistent files in the responsibility table; `test/save.c` as a reference; create `tools/three_horizons/tests/playtest12-map-indices.json` from the current map list; record the allocation table in `docs/three_horizons/PLAYTEST_13_VERIFICATION.md`.

**Interfaces:** Retain `void TH_MigrateSaveState(void)`. Add `TH_STATE_VERSION_13 = 0xA90A` under the existing `0xFFFE` mask; clock bit 0 remains time data. State consumers use named `FLAG_TH13_*` constants from the audited manifest. Allocate receipts for Bill-in-machine, ship-departed, Acro delivery, Vs. Seeker delivery/engine activity, Flash, Gear, calls, observations, photos, scene completions, pickups, trade, and chapter endpoint. Do not allocate a flag per tree to sidestep Task 18.

- [ ] Snapshot P12 map indices, trainer IDs, save sizes/offsets, species/Dex limits, item IDs, and state manifest. Scan candidate unused aliases **and numeric references**, generated tables, TH and upstream code. Broaden the existing allocation test to include `FLAG_TH12_*` and `FLAG_TH13_*`, not just the `FLAG_TH_*` spelling.
- [ ] Add `migration preserves P12 payload` and `migration remains version13 after clock update`: assert party/box bytes, money/items/badges/Dex, nine rival choices, fossil/Rocket/gift/training receipts, settings, clock low/high data, and existing trainer wins survive; repeat migration produces identical bytes. Test dirty unused slots, versions 9–12, New Game, and current 13.
- [ ] Confirm failures against the current version logic; assign collision-free slots in the manifest before referencing them. Do not assume a contiguous range after P12.
- [ ] Update all historical-version predicates and clock writing together. Initialize only newly owned state once; reconstruct old observations from existing evidence, never old photos. A P12 ship is docked until a witnessed P13 departure. Preserve already-received HM/item receipts.
- [ ] Run allocation, migration, and save-layout tests; require unchanged serialized sizes and old map/trainer IDs. Commit `feat: preserve P12 saves while adding chapter13 state`.

## Task 2 (A): Kanto Town Map interactions

**Files:** `src/field_control_avatar.c`, `data/scripts/flavor_text.inc`, `data/scripts/three_horizons/chapter9_locals.inc`, `chapter12_locals.inc`; inspect `src/region_map.c`. Test `test/three_horizons_playtest13_repairs.c` and host repair contracts.

**Interface:** TH Kanto map interactions return a TH-owned script/text and use native Kanto region-map display; upstream Hoenn interaction remains native.

- [ ] Reproduce at rival house, Viridian school/house, and ship wall maps. Trace metatile-dispatched interaction as well as explicit background events; not all wall interactions appear in map JSON.
- [ ] Add `Kanto map interaction uses current region`, asserting Kanto context yields Kanto map/text and an upstream Hoenn fixture remains Hoenn. Confirm the failing path before changing dispatch/text.
- [ ] Repair at the shared TH boundary, preserving each map's region metadata and correct map graphic. Build scripts and repeat all locations; no test merely searching for the word HOENN.
- [ ] Commit `fix: use Kanto context for TH town maps`.

## Task 3 (B): TV tile survives interaction

**Files:** `src/field_control_avatar.c`, `src/tv.c`, `data/scripts/tv.inc`, `data/scripts/three_horizons/home.inc`, `chapter12_locals.inc`; repair tests.

**Interface:** A TH TV script must leave its metatile ID, collision, and elevation unchanged when closing its dialogue.

- [ ] Capture before/after TV interaction in Viridian and Vermilion. Trace `EventScript_TV`/`TurnOffTVScreen` and compare native tile assumptions against imported Kanto tiles.
- [ ] Add `Kanto TV preserves metatile`: store tile/elevation/collision, execute interaction to completion twice, assert identical values before and after; repeat after map reload.
- [ ] Confirm old failure, then route TH TVs through compatible behavior or correct the demonstrated tile conversion without changing Hoenn TV shows.
- [ ] Run focused test and capture the intact TV after repeated interaction; commit `fix: preserve Kanto television tiles`.

## Task 4 (C): Route 5 Day Care reciprocal warp

**Files:** M(`TH12_Route5`); create M(`TH13_Route5_PokemonDayCare`) from `Route5_PokemonDayCare_Frlg`; chapter13 manifest and map registration files; `chapter13_routes.inc`; host map/repair tests.

**Interface:** Outdoor Day Care warp index 1 remains index 1; it targets the new TH interior. Each interior exit returns to Route 5's Day Care landing, not warp 0.

**Implementation conflict (verified during execution):** Native Route 5 single-Pokémon scripts and specials are FRLG-only; their `SaveBlock1.route5DayCareMon` field does not exist in TH's Emerald-compatible save. Enabling that field would break approved P12 compatibility. Reuse the existing serialized `daycare.mons[0]` through TH-only branches of the five Route 5 specials, and clone only the single-Pokémon script/text into TH ownership. Keep native party safeguards, growth, cost and return behavior; preserve other stored payload and use the existing step increment exactly once. No save expansion or breeding redesign. The outdoor on-load door replacement and closed-facility sign must also be removed along with the self-warp.

- [ ] Add `test_daycare_warps_are_reciprocal`, asserting every door tile/destination index and walkable return location. Confirm current self-warp fails.
- [ ] Clone only the required interior and give it valid TH scripts. Decide no additional Day Care feature redesign; retain native intended facility behavior and test its dialogue without importing unrelated Hoenn progression.
- [ ] Test entering, all exit tiles, cold Continue inside, and immediate re-entry with follower. Commit `fix: connect Route 5 Day Care doors correctly`.

## Task 5 (D): Saffron guards enforce the route

**Files:** M(`TH12_Route5_SouthEntrance`), M(`TH12_Route6_NorthEntrance`), `chapter12_vermilion.inc`; host map tests and native scene tests.

**Interface:** Both guardhouses prevent crossing the closed Saffron side from either approach while the Underground Path remains usable.

- [ ] Add `Saffron guard covers both lanes`, executing approach from each walkable lane in both directions and asserting no Saffron transition or trapped player/follower.
- [ ] Confirm current message-only script permits bypass; add deterministic guard/coordinate enforcement with safe retreat tiles and no endlessly retriggered movement.
- [ ] Walk/run/bike approaches, return from the allowed side, cold-load each doorway, and traverse the Underground Path both ways. Commit `fix: enforce Saffron guardhouse boundaries`.

## Task 6 (E): Pewter guide visibility and pre-Brock blocking

**Files:** M(`TH_Pewter`), M(`TH_Route3`), `playtest11_maps.inc`, existing gate logic in `data/scripts/three_horizons/journey.inc`; repair/scene tests.

**Interface:** `TH_PewterBadgeGuide` remains the guide dialogue entry. Guide has natural visible placement before Brock and no post-Brock road obstruction.

- [ ] Reproduce screenshot pop-in from both directions with walk/run/bike; log object spawn/visibility and trigger coordinates before inferring the cause.
- [ ] Add `Pewter guide cannot be bypassed before Brock`: assert trigger lane coverage and traversable post-Brock path, without forced respawn into the camera. Confirm baseline failure where applicable.
- [ ] Correct placement/trigger lifecycle at its owner. Do not use an invisible NPC teleport as the presentation fix.
- [ ] Capture both approaches and verify undefeated Brock/Misty/Surge gym trainers remain battleable after the leader. Commit `fix: stage Pewter route guide naturally`.

## Task 7 (F): Nugget Bridge rival's obsolete ending

**Files:** Existing bridge rival dialogue in `data/scripts/three_horizons/chapter9.inc` (`TH_Rival_BRIDGE_AfterText` and related old chapter-completion copy); `docs/three_horizons/PLAYTEST_13.md`.

**Interface:** Preserve bridge win/loss, partner, disappearance, and retry state; only the obsolete chapter-ending copy changes.

- [ ] Locate the live post-victory label, replace the old endpoint reference with the ongoing Bill/research journey, and retain the competitive tone.
- [ ] Build scripts; manually check first loss, subsequent win, and revisit for no false chapter completion. Existing bridge behavior tests remain green.
- [ ] Commit `fix: continue bridge rival dialogue beyond Cerulean`.

## Task 8 (G): Bill can wait inside the machine

**Files:** `chapter12_bill.inc`, M(`TH12_Route25_SeaCottage`), state constants/manifest from Task 1; `test/three_horizons_playtest13_scenes.c`; update old host tests that assert the superseded unconditional reset.

**Interface:** `TH12_Bill_OnEntry` reconstructs pre-help, in-machine, and rescued object states using a durable in-machine receipt plus existing rescued/ticket receipts. Temporary visibility flags are derived, not authoritative progress.

- [ ] Add `Bill survives leaving before PC`: enter machine, exit/re-enter, save/Continue, operate PC; assert exactly one human Bill, no Clefairy duplicate, valid PC progression, and one ticket. Include declining help, repeat PC, full bag ticket retry.
- [ ] Demonstrate current `FLAG_TEMP_2` reset failure, then persist machine entry only after entry completes and clear it when rescue completes.
- [ ] Verify interruptions at every released-control boundary, follower refresh, door animation and reciprocal warp. Commit `fix: persist Bill teleporter progress across visits`.

## Task 9 (H): Supplies already received

**Files:** `chapter12_vermilion.inc`, `src/three_horizons_chapter12.c`; existing `test/three_horizons_chapter12.c` and repair tests.

**Interface:** Keep `TH_TryGiveChapter12Supplies(void)` and its separate money/Ultra Ball receipts; dialogue branches on receipt state before claiming a new delivery.

- [ ] Add `aide acknowledges completed supplies`: already-complete visit changes neither money nor inventory; partial delivery retries only the missing component.
- [ ] Preserve the original 2,000 money and two Ultra Balls, including money cap and full pocket behavior. Change completed dialogue to explicit acknowledgment.
- [ ] Run supply tests and check first/repeat dialogue; commit `fix: acknowledge previously delivered Cerulean supplies`.

## Task 10 (I): Visible S.S. Anne ticket enforcement

**Files:** `chapter12_ship.inc`, M(`TH12_VermilionCity`), M(`TH12_SSAnne_Exterior`); scene and host map tests.

**Interface:** Preserve `TH12_Ship_CheckTicket`; add a visible boarding inspection sequence that both talk and crossing paths share. It also consults Task 25's departure receipt.

- [ ] Add `ship boarding requires ticket`: all entry lanes with/without ticket, ticket retained, no extra ticket reward, safe retreat and re-entry. Confirm baseline visible-inspection deficiency separately from existing coordinate enforcement.
- [ ] Route each boarding approach through the official's interaction. Explicitly confirm ticket ownership in dialogue; reject departed ship as well as no ticket.
- [ ] Verify walking/biking/follower and existing-save approach positions. Commit `fix: visibly inspect tickets before ship boarding`.

## Task 11 (J): Ship exterior and gangway alignment

**Files:** M(`TH12_SSAnne_Exterior`), M(`TH12_VermilionCity`); create private `data/layouts/TH12_SSAnne_Exterior/map.bin` and `border.bin` if its existing layout is shared; register in `data/layouts/layouts.json`. Host map tests.

**Interface:** Preserve map/warp IDs. The pier, gangway, visible hull, and boarding landing form one aligned walkable route.

- [ ] Compare the `SS Anne.png` reference with native layout/warp geometry and capture the existing scene. Determine whether the offset is map art, camera, or ship-object placement before editing.
- [ ] Add geometry assertions for warp landing and connected walkable cells; correct only the proven owner. Preserve room connectivity and a safe landing for existing saved coordinates.
- [ ] Capture centered dock/ship with small and large follower, approach from both sides, enter/exit repeatedly, and reserve departed appearance for Task 25. Commit `fix: align S.S. Anne dock and gangway`.

## Task 12 (K): Rival visibly leaves the ship corridor

**Files:** `chapter12_ship.inc`, M(`TH12_SSAnne_2F_Corridor`); scene tests.

**Interface:** `TH12_Ship_RivalVictory` completes dialogue, waits for a collision-valid offscreen walk, then removes the object; existing victory receipt and nine starter dispatches remain intact.

- [ ] Add `ship rival exits before removal`, asserting movement completion precedes removal and control/follower restoration; include both trigger lanes and all rival partners.
- [ ] Confirm current immediate-removal behavior; author an exit path around the player rather than through them. Loss must retain the encounter, victory must not refight on revisit.
- [ ] Capture the walking exit using `Rival SS Anne.png` as the before reference. Commit `fix: give ship rival a visible walking exit`.

## Task 13 (L): Captain's seasick staging

**Files:** `chapter12_ship.inc`, M(`TH12_SSAnne_CaptainsOffice`); existing ship reward tests.

**Interface:** `TH12_Captain_Talk` preserves the sick/trash-can orientation during the sick phase; existing HM01/Cut receipt remains authoritative.

- [ ] Remove only the demonstrated inappropriate face-player behavior during sickness; retain an explicit appropriate orientation after help.
- [ ] Check all accessible interaction sides, rival-unfinished branch, HM bag failure/retry, help completed, and repeat visit. HM01 must be received at most once.
- [ ] Build and capture before/after posture; commit `fix: retain captain seasick staging during dialogue`.

## Task 14 (M): Farfetch'd beside the leek NPC

**Files:** M(`TH12_VermilionCity_House2`), `chapter12_locals.inc` (`TH12_VermilionCity_House2_Object0`); existing species overworld graphics registrations as references.

**Interface:** Add a stable new local object ID for a visible Farfetch'd, with a cry/short Pokémon response, beside the matching NPC.

- [ ] Check on-screen object/palette capacity at the location including large follower and cycling; use the existing species graphic rather than creating unrelated artwork.
- [ ] Place Farfetch'd without blocking access, cuts, warps, or NPC movement. If measured object/palette capacity makes this impossible, record the actual limit and use the Bible's accurate-text fallback; do not silently leave an invisible companion claim.
- [ ] Capture and revisit after save/Continue; commit `fix: show Vermilion leek NPC companion`.

## Task 15 (N): Machoke overworld scale

**Files:** M(`TH12_SSAnne_B1F_Room5`), `chapter12_locals.inc`; inspect `src/data/object_events/object_event_graphics_info.h` and species follower graphics before choosing the existing suitable graphic.

**Interface:** Only the scene's Machoke graphics selection/anchor changes; local ID, interaction, and collision footprint remain stable.

- [ ] Compare native small NPC sprite and existing species graphic against `Machoke and trainer.png`; choose a readable scale without editing every Machoke sprite globally.
- [ ] Validate palette, four facings, floor anchor, bed/table overlap, adjacent trainer interaction, and passage with large/small follower.
- [ ] Save before/after screenshots, build scripts/graphics, commit `fix: size ship Machoke appropriately`.

## Task 16 (O): Gym guides acknowledge victories

**Files:** `chapter12_gym.inc`, `chapter9_locals.inc`; M(`TH_PewterGym`), M(`TH_CeruleanGym`), M(`TH12_VermilionCity_Gym`) as binding references.

**Interface:** Guides select advice or congratulations from their own leader/badge state, with no battle or reward mutation.

- [ ] Add pre-/post-leader dialogue branches for Brock, Misty, Surge. Keep advice accurate and brief; no repeating the Surge puzzle instructions after completion.
- [ ] Build and inspect each guide before win, after win, and after Continue; verify remaining gym trainers still challenge normally.
- [ ] Commit `fix: update gym guide dialogue after victories`.

## Task 17 (P): Short Cut explanation

**Files:** `data/scripts/field_move_scripts.inc`, captain/aide instruction text as needed.

**Interface:** TH `Text_CantCut` gives a short obstruction hint, such as the approved example; detailed HM ownership/badge/conscious-party explanation belongs to first-time instruction.

- [ ] Replace the current multi-page repeated tree explanation with two concise lines that fit the text box. Keep normal Cut confirmation and actual eligibility unchanged.
- [ ] Check blocked tree with no HM, no badge, no compatible mon, Egg-only, fainted compatible mon, and normal eligible party; verify full teaching text remains available from its owner.
- [ ] Build and visually check wrapping; commit `fix: shorten repeated Cut tree explanation`.

## Task 18 (Q): Global Cut object/collision/follower repair

**Files:** `data/scripts/field_move_scripts.inc`, `src/fldeff_cut.c`, `src/follower_npc.c`, `src/follower_helper.c`, `src/event_object_movement.c`, `src/three_horizons.c` follower-refresh owner if implicated; extend `test/three_horizons_field_moves.c`, repair tests. Edit only files demonstrated to own the defect.

**Interface:** Preserve native Cut entry points. The cut target's map/local identity must stay stable through animation and follower refresh; the removed tree's sprite and collision share the same lifecycle. Regrowth on a normal map reload is allowed only when visual and collision agree.

- [ ] Reproduce in at least Viridian, Route 2, and the working Vermilion gym case. For each, test compatible follower, incompatible follower with another party user, follower off, interact versus party-menu Cut. Log `VAR_LAST_TALKED`, object IDs/local IDs, graphics, remove/hide state, collision, and refresh order around the animation.
- [ ] Add `Cut target survives follower animation` and `Cut removal stays visually collision consistent`. Assert the same tree is removed, no invisible obstacle or walk-through visible tree appears after follower refresh, and another tree is unaffected. Save/Continue and leave/re-enter must result in a coherent state, not necessarily permanent removal.
- [ ] Run failing reproduction tests, identify the first incorrect identity/state transition, and fix that shared owner. Do not set permanent flags on individual failing maps or change all trees to decorative tiles.
- [ ] Run the full matrix with walking, cycling, large follower, switching lead after Cut, repeat Cut, and movement through the opened path. Confirm native upstream Cut behavior remains intact.
- [ ] Capture screenshots/video and targeted native evidence; commit `fix: synchronize Cut tree removal with follower refresh`.

## Task 19 (R): Clefairy/Makuhita repeat animation

**Files:** `chapter12_sightings.inc`, M(`TH_MtMoonB2F`); `test/three_horizons_playtest13_scenes.c`.

**Interface:** Existing cave sighting receipt selects the full first circle versus a short repeat response; initial choreography stays approved.

- [ ] Add `Moon sighting repeat keeps formation`: after first completion, repeat does not restart the circle, overlap Makuhita, or move objects into the path; completion receipt remains set.
- [ ] Adjust the close Clefairy's base position and paths together. Repeat uses a brief hop/spin/cry and short text, not a full reenactment.
- [ ] Check `clefairy dancing around makuhita.png`, all approaches, lead/follower variation, and cold re-entry. Commit `fix: shorten repeat Moon sighting and preserve spacing`.

## Task 20 (S): Fossil scientist trigger and facing

**Files:** `playtest11_story.inc`, M(`TH_MtMoonB2F`); scene tests and existing fossil reward tests.

**Interface:** `TH_FossilResearcherTrigger` positions/faces both participants before dialogue from each approach, without changing the two-fossil victory/revival receipts.

- [ ] Add `fossil challenge faces player from stairs`: cover stair entry, side approach and direct talk, asserting mutual facing on floor tiles, no movement through follower, and no fossil access before victory.
- [ ] Correct trigger lane or movement/facing only after recording actual coordinates; retain loss retry and both fossil rewards.
- [ ] Test save/re-entry before/after victory and full-bag reward retry; commit `fix: align fossil researcher challenge staging`.

## Task 21 (T): Jessie/James dialogue with both approved battle formats

**Files:** `playtest11_story.inc`, `src/three_horizons_chapter12.c`; existing `test/three_horizons_playtest12_rocket.c`, `test/three_horizons_playtest12_team_balls.c`, and scene tests. Preserve existing double-battle dispatch and split opponent-party presentation; this correction does not require replacing that machinery.

**Interface:** Preserve the existing encounter dispatcher and the intent of `TH12_BeginRocketPair(void)` / `TH12_CompleteRocketPair(void)`. Select format from usable conscious, non-Egg Pokémon at encounter start: **2 or more → Jessie + James double battle with Ekans/Koffing and the existing split opponent-party presentation; exactly 1 → Jessie/Ekans, then James/Koffing in consecutive singles without free healing.** Zero usable Pokémon must not start an invalid fight. A retry selects the appropriate format for the then-current party; losing either format cannot set completion. In the single fallback, a loss to James clears partial progress so the next single attempt starts with Jessie. Set the shared encounter-complete receipt only after the full selected format is won. Meowth remains a speaking noncombatant in both formats.

- [ ] Give James an introductory contribution in both formats. In the single fallback, revise Jessie's loss into an intermediate handoff rather than a declaration that the whole plan failed; give James his natural challenge. Retain the final shared defeat/blast-off only after the complete encounter is won.
- [ ] Add/run `Rocket usable party selects approved format`: usable counts 0/1/2/6, including six party slots with only one conscious non-Egg. Assert exactly one usable selects singles and 2+ selects the existing double; opponent species and split party/ball presentation remain correct; Meowth is never in either battle party.
- [ ] Add/run `Rocket single handoff does not heal or finish pair`: Jessie win preserves remaining HP/status/PP for James and leaves encounter completion unset; Jessie loss does not skip her; James loss retries the entire single pair; only both wins complete it once.
- [ ] Add/run `Rocket double loss retries complete encounter`: double loss leaves no completion/reward, returning permits the appropriate encounter, double victory completes once, and revisit does not replay a completed fight. Include save/Continue between attempts and switching from one usable Pokémon to two (and vice versa) before retry so stale single/double state cannot skip an opponent.
- [ ] Capture both battle formats and the single handoff/final blast-off; check existing Jessie/James artwork, Meowth speech/staging, split opponent-party presentation and monicaccina credit. Commit `fix: polish Rocket dialogue while preserving both battle formats`.

## Task 22 (U): Trainer RUN does not deliberately whiteout

**Files:** `include/config/battle.h`, existing run handling in `src/battle_main.c` only if configuration is insufficient; `test/three_horizons_playtest13_battle.c`.

**Interface:** For TH ordinary trainer fights, RUN gives the native cannot-run response and continues the fight. Wild running and actual defeat/blackout remain unchanged. No new quit mechanic is introduced.

- [ ] Add `trainer RUN cannot whiteout`, asserting no money loss, warp, win flag, reward, or HP change on attempted RUN; include normal trainer, rival, Rocket double battle, and both Rocket fallback singles. Add wild successful/failed escape controls.
- [ ] Confirm current enabled trainer-running setting reproduces the report; use a TH-only setting to disable it rather than altering general battle outcomes.
- [ ] Run targeted battles and prior loss/retry tests; commit `fix: prevent trainer RUN from causing TH blackouts`.

## Task 23 (V): SELECT rearranges battle moves safely

**Files:** `include/config/battle.h`, `src/battle_controller_player.c`; `test/three_horizons_playtest13_battle.c`, existing move-selection tests as references.

**Interface:** Enable existing pre-Gen4 rearrangement for TH. Move, current PP, PP Ups, party/battle slot state and relevant slot-tracking effects must move together. Preserve native restrictions for transformed/copied moves and special battle modes.

- [ ] Add `SELECT swaps moves and PP`, `SELECT swap preserves disabled and choice slots`, and `SELECT cancel changes nothing`: include empty slot, duplicate moves, zero PP, repeated swaps, doubles, transformed mon, and end-of-battle save/Continue.
- [ ] Confirm disabled selection on old config, enable narrowly, and fix demonstrated state-sync defects if the native handler misses any asserted state. Never reset PP to make the swap work.
- [ ] Visually confirm cursor/hint/description behavior and attack selection after swaps; run existing upstream tests. Commit `feat: enable safe SELECT move rearrangement in TH battles`.

## Task 24 (W): First-catch Dex presentation finishes before naming

**Files:** `src/battle_script_commands.c`, `src/pokedex.c`, `data/battle_scripts_1.s`; existing `test/three_horizons_capture_lifecycle.c`, `test/three_horizons_capture_ui.c` and new battle tests.

**Interface:** Register caught data once; wait for the actual Dex presentation's completion/return callback before restoring the battle/naming scene. No fixed delay as a substitute for lifecycle ownership.

- [ ] Reproduce first catch versus previously caught species with rapid A and normal input. Add `first catch finishes Dex before nickname` covering new/repeat catch, nickname yes/no, maximum nickname, full party to PC, full storage rejection, and configurable legendary editor return.
- [ ] Assert callback order, one caught registration, readable completed entry, one naming prompt, valid graphics/palettes/windows on return, and no input leakage that auto-skips the entry.
- [ ] Fix the observed callback/input owner and run previous black-screen/nickname tests. Capture representative screens and test repeated catches; commit `fix: sequence Dex presentation and nickname lifecycle`.

## Task 25 (X): S.S. Anne departure with safe migration

**Files:** `chapter12_ship.inc`, M(`TH12_SSAnne_Exterior`), M(`TH12_VermilionCity`), `src/three_horizons_state.c`; scene tests, existing ship map contracts, private exterior layout from Task 11.

**Interface:** New `FLAG_TH13_SHIP_DEPARTED` is separate from `FLAG_TH12_SHIP_RIVAL` and `FLAG_TH12_CUT`. Departure eligibility requires rival complete, captain helped/Cut receipt and HM01 obtained. The final exit warns the player, allows staying, then lands them safely on the dock and marks departure. Receipt is not set by simply opening a dialogue.

- [ ] Add `ship final exit warns and departs once`: preconditions independently false/true; decline stays aboard; accept exits and prevents later boarding; no ticket/HM duplication or lost exit warp.
- [ ] Add `P12 ship saves remain safe`: migrate before/after captain, each cabin/corridor/exterior, and outside after old completion; do not auto-depart on load. Test interrupted departure and an impossible departed-inside fixture with a safe dock recovery.
- [ ] Integrate Tasks 10–13 and replace the old permanent-docking promise and corresponding assertions with the approved P13 behavior. Preserve all old map IDs and room exit indices.
- [ ] Manual departure animation/dock acceptance with large follower, re-entry attempts, save/Continue inside and outside. Commit `feat: depart S.S. Anne after the final warned exit`.

## Task 26: Trainer Services and Cerulean Berry Workshop

**Files:** `data/scripts/three_horizons/training.inc`, `src/three_horizons_training.c`, `chapter9_locals.inc`, `chapter12_locals.inc`; M(`TH_ViridianMart`), M(`TH_PewterMart`), M(`TH_CeruleanMart`), M(`TH12_VermilionCity_Mart`), new Lavender Mart; M(`TH_CeruleanHouse5`), the existing workshop (`TH_Local_CeruleanHouse5_0`), and M(`TH_CeruleanHouse4`) for correcting its old Viridian berry referral; `test/three_horizons_training.c`.

**Interface:** Existing `TH_TrainingClerk` is the recognizable recurring service. `TH_TrainingStock` contains mints, Capsule, Patch, Bottle Cap, Gold Bottle Cap only. New `TH13_BerryWorkshop` sells exactly Pomeg/Kelpsy/Qualot/Hondew/Grepa/Tamato and explains corresponding EV reduction up to 10.

- [ ] Use the existing House5 workshop and record each city's vendor position before editing; do not erase established trade/story dialogue or repurpose another house. Update House4's old referral to the Cerulean workshop. Keep the eventual Celadon outdoor specialist as a documented future task only.
- [ ] Add stock membership assertions; native `EV berries reduce matching stat by up to ten` for EV 0, 1, 9, 10, 11, 252, wrong stat unchanged, recalculation and single consumption. Preserve native no-effect rules and explain them accurately.
- [ ] Remove Power items/EV berries from general service stock, keep previous owned items and training-kit gifts, and install recognizable vendors with nonblocking access. Keep existing prices unless the Bible changes them; no full berry-growing feature.
- [ ] Test purchase/cancel/no money/full bag, Capsule/Patch compatibility, mints, one/all-stat caps, party/box persistence. Commit `feat: separate Trainer Services from Cerulean berry workshop`.

## Task 27: Unlimited native Vs. Seeker with TH rematch scaling

**Files:** Rematch policy files in responsibility table; `src/vs_seeker.c`, `include/config/item.h`, `src/battle_setup.c`, `include/constants/rematches.h` only with capacity proof, `src/data/trainers.party`, relevant ordinary-trainer script entries, M(`TH12_VermilionCity_PokemonCenter_1F`), `chapter12_vermilion.inc`.

**Interfaces:** Add `u8 TH13_GetRematchLevel(u8 highestLevel, u8 originalHighest, u8 badges)` and `bool32 TH13_TryCreateRematchParty(struct Pokemon *party, u16 trainerId)`. The latter returns FALSE outside an explicitly active eligible TH rematch; native generation then proceeds unchanged. Table entries map stable base trainer IDs to authored team tiers. Reuse native Vs. Seeker scan/response and trainer battle start/end lifecycle.

- [ ] Audit eligible ordinary trainer count, native `MAX_REMATCH_ENTRIES`, stored rematch element width, indices, special-trainer boundaries, and all entry script formats. Never store trainer IDs wider than the field can hold. Inventory first-fight, boss, scripted rival/Rocket exclusions; exclude scripted one-time scenes, not ordinary trainers arbitrarily.
- [ ] Add `Vs Seeker requires no charge`, `rematch level clamps safely`, and `rematch does not change first battles`. Assertions: repeated immediate use works; no eligible target gives useful text; no unseen trainer becomes a rematch; signed low-level clamp, high-level cap, non-Egg party selection; no boss/rival or original receipt mutation.
- [ ] Add explicit TH enable/no-charge path and post-Surge-independent Vermilion NPC receipt (native five-badge requirement must not delay the approved Vermilion feature). Reset transient rematch movement/state on battle end, map exit, cancellation, and blackout.
- [ ] Implement the stated tuning defaults using existing `TrainerMon`/`GenerateMonFromTrainerMon`, with curated species/ability/moves per tier. Early Caterpie/Rattata teams improve appropriately; no illegal unevolved ability carried into a later species. Reuse generated ordinary-trainer dialogue and reward rules, avoiding one-time story rewards.
- [ ] Test eligible trainers across early routes/forest/Mt. Moon/current chapter, indoor/cave native restrictions and explain any intended location restriction. Check recognition of scripts with commands before `trainerbattle` using `vsseeker_rematchid` where needed; verify upstream item disabled/default behavior unchanged.
- [ ] **Approved polish C — Keigo's first-fight roster:** review Bug Catcher Keigo's current `src/data/trainers.party` entry and the surrounding route levels during this task's scheduled implementation inspection. Replace the weak/repetitive two-Weedle-plus-Caterpie direction with a progressed Bug team, using Kakuna/Beedrill/Butterfree as the user's suggested direction rather than an invented mandatory exact roster. Keep route-appropriate levels, legal moves/abilities and normal EXP calculation/rewards. Add `Keigo progressed roster fits route`: validate the chosen species and surrounding-level envelope, normal EXP behavior and unchanged unrelated first-fight teams. This explicitly approved base-roster change is separate from dynamic rematch scaling; the rematch overlay itself still cannot mutate first battles. Record the final roster in the playtest guide and use it as the rematch baseline.
- [ ] Commit `feat: adapt unlimited Vs Seeker rematches for Three Horizons`.

## Task 28: Both bike types through the existing shop

**Files:** `chapter12_vermilion.inc`, `chapter12_locals.inc`, M(`TH12_VermilionCity_PokemonFanClub`), M(`TH_CeruleanBikeShop`), `src/item_use.c`, `src/bike.c` only for demonstrated issues; scene/repair tests.

**Interface:** Preserve `FLAG_TH12_BIKE` and existing Mach item. Add an independent Acro delivery receipt so P12 owners can collect the missing bike without another voucher. Use existing `ITEM_MACH_BIKE` and `ITEM_ACRO_BIKE`.

- [ ] Add `bike shop completes partial dual delivery`: empty bag, only Mach, only Acro, both, full key pocket, cancel, P12 receipt and missing item; no duplicate voucher charge/item.
- [ ] Deliver both preferred native types and explain speed versus tricks. Test switching registered item and using opposite bike while mounted; only one active avatar mode may remain.
- [ ] Test door dismount, cycling restrictions, rails/hops where accessible, follower cycling and cold save on either bike. Use mode-switch fallback only if these tests demonstrate a concrete engine conflict, and document that conflict first.
- [ ] **Approved polish B — chairman's Rapidash story:** expand the Fan Club chairman's pre-voucher dialogue into a charming, memorable but concise Rapidash account. Preserve the existing one-time Bike Voucher receipt and delivery flow; do not turn repeat visits into another full speech or another voucher. Add `chairman expanded story preserves voucher receipt`: first visit awards one voucher, repeat and cold Continue award none, and a full-bag failed delivery remains retryable without duplicating the reward. Build and check text wrapping/pacing. Use a separate focused commit `polish: expand chairman Rapidash story without repeating voucher` if this dialogue lands before bike changes.
- [ ] Commit `feat: provide Mach and Acro bike access safely`.

## Task 29: Species, evolution methods, and training audit

**Files:** `src/data/pokemon/species_info/gen_1_families.h`, `gen_2_families.h`, `gen_3_families.h`; `src/data/pokemon/level_up_learnsets/three_horizons.h`, `gen_1.h`; `src/data/pokemon/special_movesets.json` for teachable overrides, `tools/learnset_helpers/make_teachables.py` as the generator reference (do not hand-edit generated `src/data/pokemon/teachable_learnsets.h`); `src/pokemon.c`, `src/three_horizons_evolution.c` only for proven runtime defects. Extend `test/three_horizons_starter12.c`, `test/three_horizons_evolution.c`; create `docs/three_horizons/PLAYTEST_13_EVOLUTION_QA.md`.

**Interface:** TH regular Gyarados is Water/Dragon with physical Dragon Tail/Outrage access; no added Dragon Claw solely for coverage. TH Typhlosion remains Fire/Ground and its level-40 primary Ground move becomes Earth Power; keep separately valid Earthquake TM access. Charizard Air Slash and other P12 buffs persist. Existing Pokémon receive species-table behavior without rewriting identity/personality.

- [ ] Audit effective **release** config, not only `include/config/test.h`, which forces species for tests. Document enabled/reachable Gen I–III descendants, species IDs/Dex limits and natural methods; leave global generation switches unchanged.
- [ ] Add `Gyarados Water Dragon applies to existing mons`, `Typhlosion learns Earth Power at forty`, and `Primeape Rage Fist threshold`: 19 uses does not evolve, 20 qualifying uses and the engine's level trigger does; miss/protect/cancel, battle evolution, learned move, follower and save persistence match the actual counter semantics. Document when the level check happens; do not promise evolution on the twentieth button press if the engine checks at level-up.
- [ ] Define a single-player evolution matrix: Kadabra/Machoke/Graveler/Haunter use a TH level alternative (proposed level 36); item-associated trades use their thematic item directly (Metal Coat, King's Rock, Dragon Scale, Upgrade/Dubious Disc, Protector, Electirizer, Magmarizer). Audit branches and native methods for Magnezone and all remaining Gen I–III family descendants, including pre-evolutions where relevant. Use native condition-based evolution data; do not add an unrelated evolution engine. Proposed method/level is clearly recorded before committing.
- [ ] Keep later items/methods out of the early reward pool unless already intended. Mark each method as reachable by Lavender or later; species support does not imply immediate availability.
- [ ] Test evolution/cancel, item failure/consumption, move learning/relearn/TM, correct type, nickname, ability slot, nature, IV/EV/shiny, held item, follower graphic and save/Continue for priority examples. Check Laser Focus boosts one subsequent attack including all its hits; only repair a reproduced extra-attack carryover defect.
- [ ] Run starter/evolution/battle regressions and unchanged upstream species controls; commit `feat: audit family evolutions and tune approved TH species`.

## Task 30: Research Gear's persistent model and authored records

**Files:** New research header/state/data files and tests in responsibility table; Task 1 manifest/migration integration.

**Interfaces:** Define stable `enum THResearchEntryId`, `enum THResearchCallId`, and `enum THResearchPhotoId`. Export `bool32 TH_ResearchObserve(u16 entryId)`, `bool32 TH_ResearchTakePhoto(u16 photoId)`, `bool32 TH_ResearchQueueCall(u16 callId)`, `bool32 TH_ResearchHasEntry(u16 entryId)`, `bool32 TH_ResearchHasPhoto(u16 photoId)`, `u16 TH_ResearchNextPendingCall(void)`, and `void TH_ResearchCompleteCall(u16 callId)`. Invalid IDs return FALSE/no change; no pending call returns `TH_RESEARCH_CALL_NONE`. FALSE for observe/photo also means already recorded. Queue is a bounded pending-bitset with authored priority, not an unbounded allocation.

- [ ] Define ROM-side records with region, location, species/origin, observation, optional photo ID and progression-specific professor note. Initial authored IDs cover Route 1 Hoothoot, both forest sightings, Moon Clefairy/Makuhita, ship records, new forest pair, cave visitors, Route 9 pair, tunnel pair, and Lavender anomaly. Future note variants do not duplicate entries. Every photo ID maps to a ROM-side visual composition descriptor (existing overworld sprite/scene assets, poses and relative positions) plus location/species/observation/professor-note metadata. The descriptor and artwork are ROM data, never new saved image payloads.
- [ ] Add `research records persist once`, `invalid research IDs cannot write state`, and `migration imports only witnessed observations`. Assert repeat operations are idempotent; photo Yes records once, No leaves it unset; IDs at bounds rejected; save/reload preserves flags; recorded entry count cannot exceed the ROM table.
- [ ] Store only audited flags/IDs; use existing specific sighting receipts for historical imports, including `VAR_TH_SIGHTING_SEEN` only after auditing its bit meanings. If an old scene had no reliable receipt, let the player observe it again; do not infer that every visited map's scene was witnessed.
- [ ] Run migration and research tests plus ROM-size/state-footprint report; commit `feat: add compact authored research progress`.

## Task 31: Research Gear menu and authored photo cards

**Files:** `src/three_horizons_research_menu.c`, `include/three_horizons_research.h`, `src/start_menu.c`, `src/data/three_horizons_research.h`, research UI tests; optional small assets under new `graphics/three_horizons/research/` only if native windows/species graphics are insufficient.

**Interfaces:** Export `void TH_OpenResearchGear(MainCallback returnCallback)`; Gear unlock receipt gates the Start-menu entry. Menu calls state APIs from Task 30. Each unlocked Photo is a ROM-authored framed card with a **visible depiction of the photographed Pokémon interaction**, plus location, species, short observation and professor note. Prefer composing existing overworld Pokémon sprites/scene assets into a small tableau with readable poses and relative positions. A text-only log page or a mere species-name list does not satisfy Photos. No screen pixels or composition data are saved; only the photo ID/flag persists. Photo capture special consumes `VAR_0x8004 = photoId`, returns TRUE only for a newly accepted photo.

- [ ] Add `research menu returns cleanly` and `photo prompt cannot duplicate`: zero/one/all records, locked entries, long text, B at every level, held/rapid input, repeated open/close from different maps, all palettes/windows/tasks cleaned up on return.
- [ ] Implement Calls (authored messages/contact updates), Research Log and Photos with pagination/readable GBA text. First-time field photo uses Yes/No, brief white flash and sound, and one persistent unlock; repeated scene offers viewing/brief acknowledgment rather than duplicate capture rewards.
- [ ] Make allocation failure exit safely with no lost controls/state. No arbitrary landscape capture mode, image file saving, or full navigation-device clone.

- [ ] Add `photo card binds authored tableau and metadata`: every unlocked photo ID has valid visual asset references and the four metadata fields; invalid/locked IDs show no unearned card. Render and inspect Pinsir + Heracross, Mareep + Nidoran, Aron + Geodude, and Misdreavus cards at native GBA resolution. Both Pokémon must be visible in pair cards, with placement that represents their authored interaction rather than unrelated icons beside text. Test card pagination, palette/sprite cleanup and reopening after save/Continue; assert persistent state contains only bounded IDs/flags. If measured sprite, palette, VRAM or other GBA limits prevent a visual card, document the exact conflict before proposing any reduction to text; do not silently downgrade the photo requirement.
- [ ] Inspect screen captures at native resolution and test opening after battle, field move and scene. Commit `feat: present Research Gear log calls and photo cards`.

## Task 32: Safe professor calls and opening continuity

**Files:** `chapter13_research.inc`, research state/menu modules; `data/scripts/three_horizons/lab.inc`, `text.inc`, `chapter12_bill.inc`, `chapter12_ship.inc`, `chapter12_locals.inc`; M(`TH12_SSAnne_Deck`), M(`TH12_SSAnne_1F_Room1`) and M(`TH12_SSAnne_1F_Room2`) as the bounded candidate locations for restrained ship additions; `src/overworld.c` only if a minimal safe dispatcher hook is necessary; scene tests.

**Interfaces:** Export `bool32 TH_ResearchTryStartPendingCall(void)`, returning TRUE only after starting an eligible authored script when field controls are safe. Tasks 34/38/39 queue named call IDs at milestone ownership boundaries. A call's completion receipt is set after delivered text; contact menu can replay its report without reenqueuing notification.

- [ ] Add `professor call waits for safe field`: queue during battle, naming, menu, warp, field move and another cutscene; do not interrupt; process once afterward in deterministic authored order. Test save with pending call, rapid re-entry and cancel/review behavior.
- [ ] Write first activation: Oak has received reports; Elm sees Kanto species in Johto; Birch has irregular Hoenn reports; movement is multidirectional and unexplained. Write Route 10's shared checkpoint and Lavender's more uncertain update, with no cause reveal.
- [ ] Strengthen opening's trainer-and-field-research assignment while preserving outfit/naming/lab structure and tutorial flow. Bill's shipping theory remains a reasonable early hypothesis; later observations make it insufficient, not retroactively foolish.
- [ ] Keep calls event-driven, short and non-random. Verify a busy player is never interrupted mid-input and no call replays after successful completion/Continue.
- [ ] **Approved polish A — visible regional ship life:** add a small number of Johto/Hoenn travelers and/or visible partner Pokémon in the bounded existing ship locations listed above. Reuse appropriate native object/species graphics, choose only positions with demonstrated space, and do not overcrowd corridors/cabins or add another major event. Short dialogue reinforces travel between regions and unusual sightings elsewhere without revealing the mystery's cause. Check the scene with small/large follower, all relevant NPC interactions, palette/object capacity, rival/captain paths and Task 25's departure. Record before/after screenshots and confirm no new story gate or repeat reward; commit `polish: add restrained regional travelers aboard S.S. Anne`.
- [ ] Commit `feat: add safe milestone professor research calls`.

## Task 33: Route 11 and Diglett's Cave connections

**Files:** Create M(`TH13_Route11`), M(`TH13_DiglettsCave_SouthEntrance`), M(`TH13_DiglettsCave_B1F`), M(`TH13_DiglettsCave_NorthEntrance`) from matching `_Frlg` assets; modify M(`TH12_VermilionCity`), M(`TH_Route2`), `chapter12_vermilion.inc`; create `chapter13_routes.inc`; chapter13 manifests/map registry, encounter JSON, `src/data/trainers.party` for used native route trainers with stable TH IDs; map/encounter/research tests.

**Interface:** Remove the obsolete Vermilion eastern chapter boundary only when the intended connection is ready. Cave connects Route 11 and Route 2 bidirectionally; Route 12/Snorlax/future branches remain canonically blocked without a beta notice. Ordinary Route 11 content keeps Kanto identity.

- [ ] Add `test_diglett_cave_connects_vermilion_to_route2`, verifying every warp/connection, return landing, no unadapted native scripts, stable old IDs and no accessible unfinished route. Append map registrations; do not regenerate repaired older maps wholesale.
- [ ] Implement dominant Diglett/Dugtrio plus uncommon Phanpy/Whismur using the proposed 70/10/10/10 distribution and native-sensible cave levels. Add miner/researcher increased-digging/unknown-tracks observation; calling it explained migration is forbidden.
- [ ] Add `test_cave_encounter_weights_and_levels` for actual slot aggregation and `cave research repeat is safe`. Export exact table data, including no-Repel cave tests, catch/release and Hidden Ability regression samples without asserting a statistical guarantee from a short run.
- [ ] Play both travel directions with follower/cycling allowed only where maps permit; verify blackout return, Escape Rope, item pickup persistence and trainer approaches. Commit `feat: open Route 11 and Diglett cave research route`.

## Task 34: Route 2 aide, Flash, and Research Gear delivery

**Files:** Create M(`TH13_Route2_EastBuilding`) from `Route2_EastBuilding_Frlg`; M(`TH_Route2`), `chapter13_route2.inc`, `chapter12_vermilion.inc`, `src/three_horizons_field_moves.c`, `data/scripts/field_move_scripts.inc`, new research script specials; extend field-move/scene tests.

**Interface:** Extend `TH_FieldMoveUnlocked(enum FieldMove move)` for Flash when HM05 owned and Surge/Thunder Badge progression met; `TH_CanUseFieldMove` requires a conscious compatible non-Egg party member after HM ownership and the appropriate badge/story gate pass. **The Pokémon does not need to know the HM move and does not need a free move slot.** A full four-move set of unrelated moves remains eligible; using Flash or Cut must not teach/replace a move or consume its PP. Aide gives HM05 and Gear with independent retry-safe receipts, then queues the first activation call. Vermilion aide points there via Diglett's Cave after Surge.

- [ ] Add `Flash requires HM badge and valid user`, testing each ownership/gate/conscious/non-Egg/compatibility condition absent, compatible mon without learned Flash, fainted/Egg/incompatible party, party-menu and scripted use. Add `HM field use accepts full unrelated moveset` for both Flash and Cut: all four slots filled with unrelated moves still succeeds when eligible; learned-HM versus unlearned-HM and full versus partially empty move sets do not alter eligibility; moves, PP and PP Ups are unchanged after use. Other HMs stay locked.
- [ ] Add `Route2 aide partial delivery cannot duplicate`: pre-Surge denial explains progression; caught-species counts 9/10/11 enforce the suggested quota and display progress accurately; post-Surge delivery, full HM pocket, previously owned HM05, Gear already unlocked, interrupted activation and repeat visit. Prove at least ten obtainable species exist in reachable areas and that a below-quota player can leave and return without a softlock.
- [ ] Open the Cut-access facility and replace the obsolete Brock/closed-building copy with location/progression-appropriate text. Reuse Task 18 Cut lifecycle; ensure there is a traversable return route.
- [ ] Verify Flash visibility transition in an actual dark map, map-to-map behavior, menu exit and save/Continue. Commit `feat: award Flash and Research Gear on Route 2`.

## Task 35: Route 2 Zubat–Skarmory trade

**Files:** Create M(`TH13_Route2_House`) from `Route2_House_Frlg`; `chapter13_route2.inc`; adapt `src/trade.c` and `src/data/trade.h` (the existing `sIngameTrades` table); state/trade/scene tests.

**Interface:** One local trade exchanges a selected Zubat for Skarmory, referencing a Johto contact. Reuse native in-game trade machinery, with a TH-specific record/entry that cannot renumber old trades or affect upstream tables.

- [ ] Add `Skarmory trade is atomic`: correct selection, cancel, no Zubat, wrong mon, Egg, full six-member party, last healthy mon considerations, held item handling, and repeat attempt. Full party is a one-for-one exchange, not a gift that silently sends away another mon.
- [ ] Verify offered level/ability/moves and OT/nickname fit the documented native trade policy; preserve all other party slots. Set the receipt only after exchange completes; animation interruption cannot duplicate either mon.
- [ ] Test native trade summary/Dex/cry/follower, save/Continue and no physical link requirement. Commit `feat: add Route 2 Johto Skarmory trade`.

## Task 36: Optional Viridian Forest Cut clearing

**Files:** M(`TH_ViridianForest`), private forest layout if needed, `chapter13_research.inc`, Task 30 ROM data; map/scene/research tests.

**Interface:** A small optional Cut clearing contains a researcher, one rare-item pickup (Bottle Cap default), and peaceful Pinsir/Heracross scene with log/photo IDs. It does not replace or replay earlier forest scenes.

- [ ] Add `forest clearing optional and reward once`: route through forest remains unchanged, clearing requires coherent Cut access, pickup full-bag retry works, no duplicate item/photo, and all exits remain reachable.
- [ ] Author brief first observation/photo opportunity plus short repeat cry/motion; camera/objects return to valid positions with follower on/off. Preserve Treecko/Weedle and Shroomish/Caterpie receipts.

- [ ] Photo acceptance: open the unlocked Pinsir + Heracross card and verify both sprites form the authored interaction tableau, with location/species/short observation/professor note. Repeat after save/Continue under Task 31's visual-card contract.
- [ ] Test on migrated completed-forest save and New Game backtrack, all Cut user cases and save within clearing. Commit `feat: add optional forest research clearing`.

## Task 37: Route 9's ecosystem observation

**Files:** Create M(`TH13_Route9`) from `Route9_Frlg`; modify M(`TH_Cerulean`) east connection/trigger, `chapter13_routes.inc`, map registries, trainer and encounter data, ROM research records; map/encounter/scene tests.

**Interface:** Familiar Kanto route/trainers/items plus research student, rare Mareep, peaceful Mareep/Nidoran scene, photo and observation. Do not duplicate the existing wild-starter system or introduce unrelated regional species.

- [ ] Add `test_route9_links_and_mareep_rate`: exactly 5% aggregate Mareep in the intended land table, no zero-weight/invalid slots, valid level bounds, all old Cerulean exits unchanged.
- [ ] Adapt trainer sight lines and return paths to actual geometry; grant stable new trainer IDs and one-time pickups. Student notices changing encounter distributions without an explanation.

- [ ] Photo acceptance: verify the Mareep + Nidoran card visibly represents their peaceful interaction and retains all four metadata fields; confirm the tableau survives a normal reopen and save/Continue via its photo flag.
- [ ] Play first/repeat scene, decline/accept camera, night/day, route entrance from both sides, full party catch, loss to trainer, item retry, and save/Continue. Commit `feat: add Route 9 research journey`.

## Task 38: Route 10 checkpoint and Rock Tunnel exploration

**Files:** Create M(`TH13_Route10`), M(`TH13_Route10_PokemonCenter_1F`), M(`TH13_RockTunnel_1F`), M(`TH13_RockTunnel_B1F`) from corresponding native assets. Open the native-style upstairs floor with safe reciprocal stairs/warps where the layout/assets allow it cleanly, including M(`TH13_Route10_PokemonCenter_2F`); apply the approved upstairs polish subtask below rather than retaining a discretionary artificial stair block. `chapter13_rock_tunnel.inc`, `chapter13_research.inc`, map/encounter/trainer/heal registries, research records; map/scene/field-move tests.

**Interface:** Center is a valid heal/blackout checkpoint and queues the shared Oak/Elm/Birch update. Tunnel has native exploration identity and useful Flash; each floor includes rare Aron and Dunsparce (5% each), authored Aron/Geodude mineral scene, researcher/hiker comment and photo/log.

- [ ] Add `test_rock_tunnel_ladders_and_exit_graph` for every reciprocal ladder, north/south Route 10 access and Lavender path. Assert no ladder self-loop, isolated floor, unadapted destination or invalid heal point. Preserve canonical route shape rather than wholesale simplification.
- [ ] Add `tunnel Flash and scene preserve movement`: darkness readable but Flash materially helps; map transitions do not leave stale palettes; both floors/scene/camera return safely with large follower. Check Escape Rope and blackout to the last visited Center.
- [ ] Validate encounter slot percentages/levels and Kanto-majority composition; ordinary trainers remain legible and avoidable only as native lanes allow. Aron behaves comfortable in the habitat; professors confirm reports across all three regions without naming a cause.
- [ ] Photo acceptance: verify the Aron + Geodude card visibly represents the mineral scene and includes location/species/short observation/professor note, with only its bounded photo ID/flag persisted.
- [ ] Run map/encounter/Flash tests and a full tunnel traverse with/without Flash, repeat scene, day/night and cold save on each floor. Commit `feat: build Route 10 and Rock Tunnel research chapter`.

- [ ] **Approved polish D — accessible Center upstairs inventory:** during implementation, inspect only the currently playable TH Kanto Centers: M(`TH_ViridianCenter`), M(`TH_PewterCenter`), M(`TH_CeruleanCenter`), M(`TH_Route4Center`), M(`TH12_VermilionCity_PokemonCenter_1F`), the new Route 10 Center and Task 39's Lavender Center. Record each native-layout/asset match. Reuse the corresponding native second-floor assets where cleanly supported; do not expand to future-region Centers. Plan appended TH-owned maps M(`TH13_ViridianCenter2F`), M(`TH13_PewterCenter2F`), M(`TH13_CeruleanCenter2F`), M(`TH13_Route4Center2F`), M(`TH13_VermilionCenter2F`), M(`TH13_Route10_PokemonCenter_2F`) and M(`TH13_LavenderTown_PokemonCenter_2F`) for those supported matches. Preserve existing first-floor map IDs and return warp indices; any unsupported case needs a specific recorded layout/asset limitation, not a blanket artificial closure.
- [ ] **Approved polish D — presentation only:** use short native-style attendant/NPC dialogue explaining that communication/link services are unavailable or not currently offered. Author shared presentation scripts in new `data/scripts/three_horizons/chapter13_centers.inc`; register new maps/scripts in the existing chapter manifests. Do not invoke native link-session matchmaking/trade entry points, create cable/network infrastructure, or require real multiplayer. Leave first-floor healing and reward behavior unchanged.
- [ ] Add `test_center_upstairs_reciprocal_warps` and `Center upstairs returns without link session`: every supported Center's stair/escalator works both ways; save/Continue upstairs returns safely; follower placement and movement remain valid; talking/canceling every attendant cannot enter a communication wait or link trade. Capture upstairs/downstairs presentation and verify ordinary healing after return. Land the existing-Center/Route-10 work here and the Lavender instance with Task 39; commit `polish: open supported Kanto Center upstairs floors`.

## Task 39: Lavender town, Misdreavus, rival and Rocket cameo

**Files:** Create M(`TH13_LavenderTown`), M(`TH13_LavenderTown_PokemonCenter_1F`), M(`TH13_LavenderTown_Mart`), M(`TH13_LavenderTown_House1`), M(`TH13_LavenderTown_House2`), M(`TH13_LavenderTown_VolunteerPokemonHouse`), and M(`TH13_LavenderTown_PokemonCenter_2F`) using Task 38's native-asset and presentation-only contract; document a concrete layout/asset limitation if this floor cannot be opened cleanly. `chapter13_lavender.inc`, map/heal registries, research data and scene tests.

**Interface:** Misdreavus observation, town professor update, rival investigator conversation, and one Jessie/James/Meowth cameo each have distinct durable completion receipts. This plan uses a conversation-only rival scene here (battle is optional in the Bible), preserving the competitive voice and existing rival partner. Tower context is introduced without resolving it.

- [ ] Add `Lavender scenes complete once without trapping`: all arrival directions, day/night, follower types, photo decline/revisit, menu interruptions and Continue; Misdreavus never autostarts a battle or becomes a capturable gift.
- [ ] Stage a visible Misdreavus near the Tower watching quietly, then subtly disappearing. Give a brief photo opportunity before disappearance and a deterministic later observation opportunity if declined; no random timer that makes the record permanently missable.
- [ ] Author a log/photo note that shipping alone cannot explain the sighting, without claiming teleportation or revealing the cause. Keep the town uneasy, not horror-heavy.
- [ ] Rival admits the assignment first seemed like an excuse to travel but now seems real; growth does not erase rivalry. Jessie/James/Meowth investigate, react humorously to ghosts, and leave without a required battle. Use one authored cameo only, original concise dialogue, proper existing art/credit and readable positions.
- [ ] Retain the Cubone/Marowak/Fuji setup and compassionate local dialogue. Fuji may be indirect through residents/notes while absent; no early rescue or canon contradiction. Verify all doors, heal point, Mart/Trainer Services, NPC cries and natural future-region boundaries.
- [ ] Photo/Center acceptance: inspect the Misdreavus visual card and all four metadata fields after save/Continue. Open Lavender's supported native-style upstairs floor using Task 38's contract; test reciprocal stairs, upstairs Continue and non-networking attendant dialogue before marking town completeness passed.
- [ ] Commit `feat: introduce Lavender anomaly and investigator scenes`.

## Task 40: First Tower sequence and Silph Scope endpoint

**Files:** Create M(`TH13_PokemonTower_1F`) through M(`TH13_PokemonTower_6F`) from matching native assets, keeping upper unresolved content inaccessible. Create `chapter13_tower.inc`; register map graph, trainers, encounters and research/call IDs; inspect native ghost handling in `src/battle_setup.c`, `src/battle_main.c`, `src/battle_script_commands.c` before narrow TH hooks. Scene/battle/map tests.

**Interface:** Unidentified ghost at the intended upper progression point prevents passage without Silph Scope. No Silph Scope source or resolved 7F/Fuji reward exists in P13. `FLAG_TH13_CHAPTER_COMPLETE` records witnessing the endpoint once, not Tower resolution. Preserve the native Cubone/Marowak/ghost/Rocket/Fuji framework for P14 continuation.

- [ ] Add `Tower ghost cannot be bypassed`, testing every approach lane, returning/re-entering, Escape Rope, loss, follower/large sprite, and no Scope. Native ghost capture/identification rules must remain correct for the current map IDs; do not assume an `_Frlg` map-name check recognizes cloned TH floors.
- [ ] Adapt floors only through the endpoint, including trainer/ghost/encounter behavior and safe healing/return mechanics as appropriate to the native route. Do not expose placeholder upper warps or a battle victory that accidentally resolves Marowak.
- [ ] Add Rocket observation/record dialogue around canonical events; some grunts investigate strange activity, others do not understand Giovanni's purpose. No second Jessie/James cameo and no early Silph evidence reveal.
- [ ] Add `Tower endpoint preserves future story`: one completion notice and Celadon/Scope lead, no Fuji rescue flag, no Scope grant, no repeated reward, no blocked exit. Scope-in-bag debug fixture must not warp into nonexistent P14 maps; document that this is an out-of-scope state, not normal acquisition.
- [ ] Play the complete first Tower sequence and walk back to town after the barrier. Commit `feat: end Lavender chapter at the unidentified ghost`.

## Task 41: Whole-chapter verification, documentation and candidate package

**Files:** Four required P13 documents; `tools/three_horizons/export_encounters.py`; new `tools/three_horizons/check_playtest13_controls.py` only for focused negative controls; `.github/workflows/three-horizons-demo.yml`; existing upstream workflow. Update P12 hardware-status wording in `docs/three_horizons/PLAYTEST_12_VERIFICATION.md` with a dated user-reported addendum, preserving historical automated evidence.

**Interface:** Candidate release ties exact feature revision, compiled revision, build mode, ROM checksum, test logs and encounter export to one artifact. No public commercial ROM distribution. RG40XX H P13 remains a separate user acceptance pass.

- [ ] Run all host contracts, targeted P13 native tests, full TH regressions, save-layout tests, trainer build-mode regeneration, and upstream Emerald/FireRed/LeafGreen CI. Use isolated clean build outputs for each mode so cached generated data cannot mask a failure. Preserve existing assertions; revise a P12 expectation only when the Bible explicitly supersedes it and record why.
- [ ] Add a small set of meaningful negative controls: reinstate old Cut refresh path, old version write, and old trainer RUN/SELECT configuration in disposable test copies; confirm the owning tests fail, restore, then pass. Do not mutate the working candidate without recovery/verification or rerun every historical mutation unnecessarily.
- [ ] Back up the user's exact P12 battery save, migrate a copy via normal boot/Continue, and compare all protected fields and gameplay receipts before/after. Test save and second cold Continue. Include synthetic pre/post-Bill, ship-inside/outside, full-pocket and partial-reward fixtures. Keep old emulator save states out of compatibility acceptance.
- [ ] Perform two manual routes: migrated post-Surge save to Tower endpoint with Cut backtracking; fresh game through Surge to endpoint with all repaired early scenes. Include 24-repair matrix, first/repeat/cancel/retry, party sizes 1/2/3/6 plus usable-conscious counts (including Eggs/fainted members), both Rocket formats and loss/retry paths, full unrelated four-move sets for Flash/Cut, follower compatible/incompatible/off, maximum names, day/night, bike switches, rematches, status/PP, visual photo tableaus and metadata, calls and cold reload checkpoints. Include restrained ship travelers/partners, the expanded chairman speech with one-time voucher, Keigo's approved improved team, and every supported accessible Center upstairs with safe return and no communication wait.
- [ ] Produce `PLAYTEST_13.md` with actual route, prerequisites, exact battery-save procedure, checkpoints, optional scenes and issue-report template. Produce `PLAYTEST_13_ENCOUNTERS.md` from final tables with method/time/levels/weights, research-scene distinction and which rare encounters are expected by area. Provide finite sampling guidance without promising a rare encounter within N tries.
- [ ] Finish `PLAYTEST_13_EVOLUTION_QA.md` with every audited Gen I–III-family descendant, method, availability-by-Lavender, tests and unresolved factual limits. Finish `PLAYTEST_13_VERIFICATION.md` with all acceptance evidence, failures fixed, outstanding risks, exact P12 provenance, and honest untested items. All release-blocking criteria in Bible §35 must be accounted for.
- [ ] Build/package the exact passing candidate, record SHA-256/source revisions and generated encounter manifest, preserve draft PR history and credits, and provide P13 hardware checklist for RG40XX H/VBA-Next. Do not mark that hardware checklist passed from the P12 report. Commit `docs: record verified Playtest 13 candidate and acceptance guide` after results exist.

## Coverage and planning self-review

| Bible area | Owning tasks |
|---|---|
| Approved scope, Kanto-first mystery, P14/P15 continuity and non-goals | Global constraints, Tasks 32–40 |
| P12 hardware baseline | Baseline section, Task 41 |
| All 24 required repairs A–X | Tasks 2–25 individually |
| Training economy and Berry Workshop | Task 26 |
| Vs. Seeker and evolving rematch teams | Task 27 |
| Mach/Acro functionality | Task 28 |
| Gyarados, Typhlosion, Charizard, family evolutions, Rage Fist, Laser Focus and evolution QA | Task 29 |
| Research Gear, event-driven calls, authored visual photo tableaus and metadata | Tasks 30–32, 36–39, 41 |
| Review addendum: preserve Rocket double + single fallback formats | Tasks 21–22, 41 |
| Review addendum: HM ownership/gate/compatibility, no learned move or free slot | Task 34 (Cut regression included), 41 |
| Review addendum A: restrained regional ship travelers/partners | Task 32, 41 |
| Review addendum B: chairman Rapidash dialogue and one-time voucher | Task 28, 41 |
| Review addendum C: progressed Keigo first-fight team | Task 27, 41 |
| Review addendum D: supported Kanto Center upstairs presentation | Tasks 38–39, 41 |
| Forest Cut clearing and early backtracking | Tasks 18, 34, 36 |
| Diglett's Cave, Route 2 facilities, Flash and Skarmory trade | Tasks 33–35 |
| Route 9/10 and Rock Tunnel | Tasks 37–38 |
| Lavender/Misdreavus/Rocket cameo/rival/Fuji setup | Tasks 39–40 |
| Tower/Scope endpoint with no premature resolution | Task 40 |
| Save migration, maps, upstream compatibility | Tasks 1, 25, 30, 41 |
| Screenshot evidence | Tasks 6, 11–12, 15, 18–20, 34; no unrelated inference |
| Four release documents and all §35 acceptance gates | Tasks 29, 41 |

Self-review completed for coverage, signatures, dependency order, and the five Review Focus conditions. Proposed new file/API names are distinguished from inspected existing code. Numeric state allocation, capacity measurements, visual root causes and personal-save availability are explicit implementation gates; none is represented as already verified. The plan supplies bounded defaults where the Bible allows discretion and does not substitute them for an approved contrary decision.

**Review correction record — 2026-09-28:** Updated provenance/status, global constraints, Review Focus, Task 21 and related Task 22/41 acceptance, Tasks 30–31 and photo-producing Tasks 36–39, Task 34, and polish work in Tasks 27, 28, 32, 38–39. Updated coverage and handoff. The task count remains **41**. Conversation-only Lavender rival, proposed level-36 pure-trade alternatives, thematic-item evolution, native Vs. Seeker/scaling architecture, Start-menu Research Gear, stable compiled species/IDs with curated TH availability, and the ghost/Silph Scope endpoint with Celadon in P14 are unchanged. No new demonstrated technical conflict was discovered during this document-only correction; visual-card capacity and Center asset suitability are future implementation checks, not claimed failures.

**Handoff:** The user has approved the plan with these focused corrections/addenda. Native/inline execution remains the recommendation because tasks share core interfaces; no execution method is being started or changed here. **STOP HERE as explicitly requested: no game-code changes, builds, deployment or PR merge. Wait for the user's explicit instruction to begin implementation; do not ask them to reapprove already approved design decisions.**
