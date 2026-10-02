# Playtest 14 — Celadon, the Silph Scope, and the Return to Lavender Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Deliver the approved Celadon–Lavender–Snorlax chapter with the reviewed Navigator, earlier repair targets, unchanged battery-save layouts, and a separately packaged candidate for owner hardware acceptance.

**Architecture:** Append a bounded group of 37 maps and ROM-side chapter data; retain old map/layout/entry/trainer IDs and all saved structures. New receipts use an explicit audited flag ledger, with a monotonic migration step. Use existing native battle, item, shop, coin, region-map and photo systems with narrowly scoped Three Horizons adapters.

**Tech Stack:** C, event-script assembly, JSON map/encounter manifests, GBA metatile/4bpp assets, Python unittest/Pillow, ARM GNU 13.2.Rel1, MSYS2 make, repository native mGBA tests and copied libretro mGBA controller tooling.

**Spec:** `docs/superpowers/specs/2026-10-01-playtest14-celadon-lavender-design.md` (owner approved in chat: “approve”). Canon: `docs/three_horizons/THREE_HORIZONS_STORY_BIBLE.md`, Narrative Canon v1.2, SHA-256 `53d09fbead5167252cfe42c9e8097bc6e9d838b6a56c44a5944dfb4f55a81605`.

**Status:** User approved this implementation plan in chat on 2026-10-01. Serial/inline execution with `superpowers:executing-plans` is underway; checked task steps and the execution ledger record verified progress. Independent read-only support may run in parallel. The approved blueprint is not being reopened.

## Global Constraints

- Keep SaveBlock1/SaveBlock2/SaveBlock3/PokémonStorage at **15568/3884/4/34144 bytes** and retain relevant offsets.
- Keep all old map IDs, trainer IDs, flags, item/species IDs, research IDs and photos stable. Append new definitions. Guard new runtime behavior with THREE_HORIZONS; native upstream paths remain unchanged outside this project.
- Research Gear remains exactly Research Log, Field Photos, Calls. No Town Map module or Navigator art redesign.
- Preserve reusable TMs: `I_REUSABLE_TMS == THREE_HORIZONS`; use the 50 active TM definitions, not placeholder TM51–100 enums.
- Current named unused-variable aliases are already owned; this chapter allocates no new persistent variable.
- No multiplayer-required evolution, full later-generation Dex, Saffron/Fuchsia chapter, Birds, regional transition, future revelation, redesigned partner system or new legendary editor.
- No merge, remote release, repository-setting change, or overwrite of existing packages. Work only on `feature/playtest14-celadon-lavender` in this isolated worktree.
- Never modify the supplied battery; use private copies. Source is 131072 bytes with SHA-256 `e94846ce281dc01c245f1fdeabf300b350433fda5a1368924767a3de41536ef2`.
- Existing owner levels, party identity, false receipts and unwitnessed photos remain unchanged; no progress inferred from a screenshot or approximate story position.
- The Ekans crash remains **high-severity, owner-reported intermittent hardware failure, not reproduced locally, with unresolved root cause** until actual evidence establishes otherwise.
- A passing mGBA run is not RG40XX H/VBA-Next acceptance. Stop for that acceptance after packaging.
- Stop and document a demonstrated architectural conflict before weakening any approved requirement; routine coordinates, native copy and test repairs within this plan do not need another design vote.

## Review Focus

1. Existing saves can contain arbitrary bits in newly claimed slots: Task 1 compares every non-owned byte, tests all supported version markers, and repeats migration with newly earned PT14 progress.
2. Reward failure can occur after a boss is defeated or with a full PC: Tasks 2, 10–13 and 17 prove retries without duplicate prizes, lost items, charges or premature disappearance.
3. Two overworld twins reference one trainer identity: Tasks 5 and 8 prove one readiness slot, both interaction paths, unchanged first battle and safe insufficient-party handling.
4. A required photo can meet a player without Gear or an allocation failure: Tasks 14–16 prove a natural Gear handoff, no false photo receipt, loss/retry persistence, palette cleanup and no forced aftermath call.
5. Escape, blackout or a cold restart can interrupt an encounter: Tasks 12–17 and 19 prove loss-safe key/Scope/Flute delivery, mother victory-only resolution, and Snorlax catch-or-win-only removal.

---

## Worktree, file boundaries and checkpoints

Base runtime comes from Navigator production revision `ea393ce3174751c50206e85101b9682c5cfbb0c7`, handed off at `2d85555d74f34f5029c38a3b2db26fb7eb3f99c0`. Blueprint checkpoint is `99f2e1b7510e55df50532258c7ca8cb726c4fd8d`. Re-record HEAD/status before execution; do not reset a newer owner edit. Protected original worktrees are `../three-horizons-opening` and `../research-navigator-review`. Baseline hashes/status live privately in `.superpowers/sdd/2026-10-01-playtest14/baseline.json`.

| Responsibility | Authored files |
| --- | --- |
| State/capacity | `include/constants/three_horizons.h`, `include/constants/opponents.h`, `src/three_horizons_state.c`, `tools/three_horizons/state_manifest.json`, new `tools/three_horizons/chapter14_maps.json`, `chapter14_content.json` |
| Bounded chapter helpers | New `include/three_horizons_chapter14.h`, `src/three_horizons_chapter14.c`; existing `data/specials.inc` registers script-facing helpers |
| Travel/city/maps | `data/maps/map_groups.json`, `data/maps/TH14_*/map.json`, per-map `scripts.inc`, appended `data/layouts/layouts.json`, owned `data/layouts/TH14_*/map.bin`; `src/data/tilesets/three_horizons.h` |
| Story scripts | New `data/scripts/three_horizons/chapter14_{travel,celadon,gym,hideout,tower,snorlax}.inc`, included through the existing `data/scripts/three_horizons/maps.inc` pattern |
| Trainer/encounter data | `src/data/trainers.party`, `src/data/wild_encounters.json`, `src/data/three_horizons_rematches.h`, `src/three_horizons_rematches.c` |
| Services/economy | New `src/data/three_horizons_celadon.h`, `src/three_horizons_celadon.c`; shared shop/coin/gift hooks only where a reproduced delivery defect needs repair |
| Research/photo | Existing `src/three_horizons_research.c`, `src/three_horizons_research_menu.c`, `include/constants/three_horizons_research.h`, `src/data/three_horizons_research.h`, generator `tools/three_horizons/research_photo_art.py`, authored photo assets and generated photo header |
| Verification | Focused `test/three_horizons_playtest14_*.c`, `tools/three_horizons/tests/test_playtest14_*.py`; reviewed existing tests remain in place |
| Release | Existing PT14 verification/development notes plus `PLAYTEST_14.md`, `PLAYTEST_14_HARDWARE_QA.md`, `PLAYTEST_14_ENCOUNTERS.md`, `PLAYTEST_14_TM_AVAILABILITY.md`, updated Gear/rematch docs |

Import geometry with explicitly tracked empty event wrappers only when a later numbered task owns that interaction; do not execute unadapted native donor reward/story scripts. Such wrappers may support intermediate geometry tests, must be listed with their owning task in chapter14_content.json, and are forbidden by the Final accessible-event test. No intermediate ROM is a release candidate. Do not manually patch generated map headers, events or groups. Preserve native donor maps/scripts; new TH wrappers/data receive changes. Each task ends with a focused logical commit of its listed authored files and pertinent evidence summary; never `git add .` or commit private batteries/RAM. Commit messages below are proposed descriptions, not commands to publish.

## Test recipes and evidence rules

All commands run from this worktree. Task 1 also copies/adapts the private Navigator `run-host.py` wrapper to set the portable compiler PATH after Python starts (required by checked mapjson tests). Use UTF-8 mode. Build fresh mapjson and generate TH source before tests requiring generated files. Host Python: `C:/Users/phabe/.cache/codex-runtimes/codex-primary-runtime/dependencies/python/python.exe`. MSYS2 bash: `C:/Users/phabe/Documents/Codex/pt13-review-tools-20261001/msys64/usr/bin/bash.exe`; use `/mingw64/bin:/usr/bin` on its PATH. ARM toolchain: `/c/Users/phabe/Documents/Codex/pt13-review-tools-20261001/arm/arm-gnu-toolchain-13.2.Rel1-mingw-w64-i686-arm-none-eabi`.

- **H(file):** `python -m unittest discover -s tools/three_horizons/tests -p <file> -v`. A test name below belongs to that file's unittest class. Success is zero failures/errors and a nonzero test count.
- **N(prefix,label):** build `make THREE_HORIZONS=1 TEST=1 TOOLCHAIN=<ARM-path> -j8 pokemon-three-horizons-test.elf`, then `python .superpowers/run-pt14-native.py "<prefix>" "<unique-label>" --normal-audio`. Task 1 creates this private adapter from the proven Navigator runner, changing only root/output paths and accepting unique labels. It uses repository `tools/patchelf`, `tools/mgba/mgba-rom-test.exe`, normal audio, strict skip-is-fail and a nonzero-test assertion. Every new native test title begins `Three Horizons PT14 <owner>:`. Do not use `make check` headless for cry/capture acceptance. Focused builds may restrict sources to all `test/*.c` (including `test/test_test_runner.c`) plus relevant battle tests; full integration must remove that override.
- **P(label):** `make THREE_HORIZONS=1 TOOLCHAIN=<ARM-path> -j8`; preserve `.gba`, `.elf`, `.map`, log, source revision and SHA-256 together privately under the unique gate label. No desktop ROM is a build target.
- **V(case):** copied private controller runner launches the identified ROM/core from a copied battery or an explicitly labelled fixture, records inputs/native 240×160 frames and outcome JSON. An initial cold-load test never imports an emulator state; same-ROM warm snapshots can split long controller sessions and must be labelled.
- **L:** native file filters `test/save.c` and `test/three_horizons_playtest14_layout.c`, with normal audio. Task1 creates the offset assertions for Gate A; Task18 reruns them on the final candidate. Assert four struct sizes plus protected offsets, not just a source grep. Baseline anchors from the unchanged structures and exact source-save audit are SaveBlock1: pos0x00, location0x04, playerPartyCount0x234, playerParty0x238, money0x490, coins0x494, registeredItem0x496, pcItems0x498, bag0x560, trainerRematchStepCounter0x9C8, trainerRematches0x9CA, flags0x1270, vars0x139C, dexSeen0x3598, dexCaught0x3619; SaveBlock2: pokedex0x18 and encryptionKey0xAC; PokemonStorage: boxes0x04. Bind each to its actual field name and compile-time offsetof; compare against the baseline ELF if an anchor disagrees, never silently change an expected value.
- **U(build):** serial `make THREE_HORIZONS=0 BUILD=<emerald|firered|leafgreen> TOOLCHAIN=<ARM-path> -j8`. Do not enable THREE_HORIZONS for FR/LG. These configurations share generated headers, so they must not build concurrently.

For a demonstrated behavioral bug, record reproduction → regression → expected behavioral RED → root-cause change → focused GREEN. A compiler error or source-string assertion alone does not prove the old gameplay failed. For new data/features, a missing-data RED is acceptable but must be labelled. Keep failed logs. Visual checks require baseline/candidate frames; source geometry alone is not visual acceptance. Native builds needed for focused tests are allowed; complete production builds occur at Gates A, B and Final, not after every dialogue change. Never sum reruns into an inflated test total.

## Task 1: Allocate chapter state and make migration idempotent

**Files:** state/capacity files above; new `test/three_horizons_playtest14_state.c`, `test/three_horizons_playtest14_layout.c`, `tools/three_horizons/tests/test_playtest14_state.py`; private runner adapter.
**Interfaces:** produces `TH_STATE_VERSION_14 = 0xA90E`, `TH_STATE_VERSION_CURRENT = TH_STATE_VERSION_14`, `TH14_TRAINERS_START/END`, explicit `sTH14OwnedFlags[]`, the Appendix A ledger, and `bool32 TH_IsProjectMap(u8 mapGroup, u8 mapNum)` declared in the chapter14 header. The predicate recognizes group75 indices0–117 and group76 indices0–36; rejects 255/sentinels/out-of-range maps. It never dereferences a claimed map.

- [x] Write `test_pt14_ledger_is_disjoint_and_signed_maps_fit`: assert Appendix A flag IDs are named native-unused aliases, below0x920, not0x021, not in any native flag reset/range owner or trainer defeat range; old IDs/layouts unchanged, group76/index<128, no duplicate allocated trainer identity. Save an immutable baseline of all old maps/layouts from revision2d85555.
- [x] Run H(`test_playtest14_state.py`) and record missing-ledger RED; add native `Three Horizons PT14 state: legacy import touches only owned state` using existing full-block-copy helpers, with PT12/13/13.1/current markers and arbitrary bits in new slots. First run on old source must expose missing PT14 initialization or non-idempotence; preserve the evidence.
- [x] Implement the ledger and migration. Every older version-exclusion predicate must accept PT14; append one PT14 step clearing only the explicit new flag list and trainer157–194 bits. Preserve the low clock bit and all older migrations. A current-version second pass must preserve all newly set receipts. Keep existing PT13 `<0x500` allocation test; add the separate audited PT14 allowlist.
- [x] Add Recipe L's compiler-evaluated offset assertions for the unchanged save fields and one-byte signed warp fields; they must pass on the baseline and are invariants, not invented behavioral RED tests. Add `current_marker_preserves_all_receipts_on_repeated_continue`, `new_game_initializes_only_owned_state`, `cross_group_predicate_is_bounded`, and old flag/variable/party/PC raw-byte invariance. Test discarded/unseen-photo and false ship-departure states as well as positive progress.
- [x] Run H(state), existing H(`test_state_allocations.py`), N(`Three Horizons PT14 state:`,`state-green`); inspect each failure instead of weakening assertions. Full L waits for integration.
- [x] Commit `feat: allocate PT14 state with idempotent migration`; record the exact allocations and fresh counts in verification notes.

## Task 2: Restore Town Map handoffs and verify the native Kanto map

**Files:** new chapter14 helper/header; `data/specials.inc`, `data/scripts/three_horizons/chapter9_locals.inc`, `lab.inc`, `text.inc`, `data/maps/TH_RivalHouse/map.json`; `src/item_use.c`, `src/field_region_map.c`, `src/region_map.c` only if actual native frontend tests expose a defect. Tests: `test/three_horizons_playtest14_town_map.c`, `tools/three_horizons/tests/test_playtest14_town_map.py`.
**Interfaces:** `enum TH14GiftResult {TH14_GIFT_NO_ROOM=0, TH14_GIFT_GIVEN=1, TH14_GIFT_ALREADY_OWNED=2}`; `u8 TH14_TryGiveUniqueItem(u16 itemId, u16 receiptFlag)` accepts only ledger-authored item/receipt pairs, checks bag and PC, gives before setting receipt; script special `void TH14_ScriptGiveUniqueItem(void)` consumes VAR_0x8004 item and VAR_0x8005 receipt, produces VAR_RESULT. Reused by later key/TM/Flute gifts.

- [x] Add `town_map_bag_pc_owned_full_bag_retry`: no duplicate when owned in bag/PC or already delivered; a full bag changes neither receipt nor inventory; retry grants once. Add `town_map_daisy_after_partner_and_oak_catchup` with existing partner stage as Daisy gate, Oak's completed-supplies interaction as catch-up, shared receipt.
- [x] Run focused RED. On copied old ROM capture the current Daisy conversation/map-item absence; do not label an otherwise working native map renderer broken.
- [x] Route `TH_Local_RivalHouse_0` through Daisy's gift after the first partner, keeping friendly pre-partner text. Oak's sendoff points to Daisy; his later supplies-complete conversation offers a missing map. Both use the common transaction. Keep the table map as an inspectable map, not a second item source.
- [x] Exercise actual `ItemUseOutOfBattle_TownMap` → `FieldInitRegionMap` from field and Bag: Kanto assets/title, correct current location label/marker for Pallet, cave, Tower and later Celadon; A/B safely close, no Fly unlock. Existing `GetRegionMapType` already selects Kanto by section: reuse it; repair only a reproduced mismatch. Test repeated open/close and registered-item return path.
- [x] Run H(town_map), N(`Three Horizons PT14 town map:`,`town-map-green`); schedule actual frontend screenshots/cold persistence for Gate A and group76 for Gate B.
- [x] Commit `feat: restore Daisy Town Map and Oak catch-up`.

## Task 3: Repair documented tree presentation and Route 9 entry state

**Files:** `data/layouts/TH13_ViridianForest/map.bin`, `data/maps/TH13_Route9/map.json` or its script only if needed, `src/event_object_movement.c`, `src/overworld.c`; `test/three_horizons_playtest13_cut.c`, new `test/three_horizons_playtest14_cut.c`, `tools/three_horizons/tests/test_playtest14_cut.py`.
**Interfaces:** consumes TH_IsProjectMap for project-wide Cut handling. Existing Cut session/regrowth contract stays unchanged; no new permanent tree flag.

- [x] Reproduce Route9 arrival from Cerulean on an uncut copied save, separately test direct warp and first connection entry. Capture the forest clearing before frames at its north/south crowns and Cut mouth.
- [x] Add `route9_current_map_tree_survives_connection_edge_filter` and `cut_visibility_collision_reload_agree`: uncut x2 tree visible/colliding, correct owner map despite connection edge, Cut removes graphic/collision together, reload obeys existing session lifecycle, no stale FLAG_TEMP_12 from another map. Record behavioral RED.
- [x] Repair only the current-map/connecting-map ownership filter proven responsible; use explicit bounded project-map checks at the existing shared hooks. Restore forest whole-tree metatiles around x27–35/y29–34 and entrance x36–38/y31–32 without moving Pinsir(30,32), Heracross(32,32), researcher(29,34), reward(35,30), Cut(38,31/32), paths or receipts.
- [x] Add host geometry/interaction assertions; run existing native Cut regressions plus N(`Three Horizons PT14 cut:`,`cut-green`) and H(cut).
- [x] At Gate A inspect before/after native frames, first arrival, jump/follower, Cut, leave/re-enter, then cold Continue; if source hypothesis does not reproduce, retain evidence and investigate instead of speculative filter removal.
- [x] Commit `fix: preserve Route9 Cut state and complete forest tree graphics` only for demonstrated repairs.

## Task 4: Improve Flash handoff and Lavender's causal story lead

**Files:** `data/scripts/three_horizons/chapter13_route2.inc`, `chapter13_lavender.inc`, `chapter13_tower.inc`, `data/maps/TH13_LavenderTown/map.json`; tests `test/three_horizons_playtest14_leads.c`, `tools/three_horizons/tests/test_playtest14_leads.py`.
**Interfaces:** preserves existing Flash, rival, cameo and endpoint receipts; no new story flag for rewritten speech.

- [x] Add script-order assertions: Oak/research/Rock Tunnel introduction before successful HM05 grant, field-use explanation afterward; badge3 and10 caught/received species still required, full bag/owned states retry correctly. Run H(leads) for RED.
- [x] Implement the dialogue contract in Appendix C. Lavender rival remains conversation-only on first/repeat; the observer Rocket remains nonbattle. Repeat barrier guidance connects Giovanni's Tower reports, Celadon trio business and Scope. Remove the developer completion sentence without clearing FLAG_TH13_ENDPOINT.
- [x] Place Jessie/James/Meowth on a verified walkable, unobscured three-tile row, using the concrete staging ledger in Appendix C; keep existing cameo hide receipt and all local IDs. Retain a free approach/escape lane and safe follower hiding/restoration during conversation.
- [x] Test full-bag Flash retry/owned HM/no badge/9 vs10 species, conscious compatible non-Egg field use without learned move/free slot; preserve completed rival/cameo on migration. Run existing Flash tests, H(leads), N(`Three Horizons PT14 leads:`,`leads-green`).
- [x] At Gate A capture all speakers unobscured and the first/repeat speech paths with labelled fixtures; the owner save's already completed scene must not replay.
- [x] Commit `fix: clarify Flash handoff and Lavender Celadon leads`.

## Task 5: Extend rematches without changing first battles or save storage

**Files:** `src/three_horizons_rematches.c`, `src/data/three_horizons_rematches.h`, `include/three_horizons_rematches.h`, `src/vs_seeker.c` if needed for visual aliases; existing `test/three_horizons_rematches.c`, new `test/three_horizons_playtest14_rematches.c`, `tools/three_horizons/tests/test_playtest14_rematches.py`.
**Interfaces:** preserve existing full-width trainer-ID registry and map-local readiness API; new `u16 TH14_GetAuthoredRematchEvolution(u16 trainerId, u8 slot, u16 species, u8 scaledLevel, u8 badges)` returns unchanged species unless an exact Appendix B row applies. It runs only while creating a rematch party, after existing level tiers and before current moves/ability/stat generation. Add an explicit trainerId parameter to an internal keyed generator; retain TH13_CreateRematchPartyFromTrainer as a TRAINER_NONE wrapper for existing callers/tests. TH13_TryCreateRematchParty passes its actual u16 ID. Never infer identity from name, class or pointer search.

- [x] Add parameterized threshold tests for every Appendix B override immediately below/at threshold and below/at badge gate; same first battle remains byte-identical. Add ability-slot fallback, evolved learnset, legal species, useful Seen flag, XP/EV and level-clamp checks.
- [x] Record RED for missing authored evolution on appropriate rematches; verify inherited rematch greetings already pass instead of reimplementing reviewed work.
- [x] Implement explicit trainer/slot/species overrides; no random branch, player evolution or broad item-evolution rule. Add all30 new ordinary trainer identities as their maps land: Route8 IDs157–168, Gym169–175 and Hideout178–188. Exclude Erika176, poster guard177, Giovanni189, Jessie190, James191 and disappearing Tower192–194. Hideout key/door prerequisites retain their first-win bits through rematches; a rematch cannot replay a key or door reward.
- [ ] Preserve Route8 Eli/Anne as one ordinary doubles encounter: one registry row and one readiness slot keyed to their shared trainer ID. Both objects resolve that row through an explicit bounded visual alias, never a duplicate persistent slot. Verify doubles-aware first/rematch dispatch and fewer-than-two-usable Pokémon response.
- [x] Run H(rematches), existing capacity suite and N(`Three Horizons PT14 rematches:`,`rematch-green`): high IDs never truncate; aliases only share an explicitly authored identity; no readiness survives map change/Continue/cancel/blackout/completion; defeat flags unchanged; immediate repeat use still allowed; single `!`/double `!!` meanings demonstrated at Gate B.
- [x] Commit `feat: author stone-evolution rematches and shared twins readiness`.

Task5 checkpoint: bounded alias/runtime rules pass; live twin dispatch and30 new registry identities remain map-dependent Tasks8/11/12 and GateB. The Preserve Route8 lifecycle checkbox remains open until those scenes exist.

## Task 6: Make project Tower fog atmospheric only

**Files:** `src/battle_util.c`, `src/battle_main.c`, chapter14 helper/header; new `test/three_horizons_playtest14_fog.c`, `tools/three_horizons/tests/test_playtest14_fog.py`.
**Interfaces:** `bool32 TH14_IsTowerMap(u8 mapGroup, u8 mapNum)` recognizes existing TH Tower1F–6F and new TH14 Tower7F at group76/index33 only. Task1 declares the manifest-checked numeric map index so this helper can be tested before that new map is registered. Used in actual fog initialization and Terrain Pulse's fog-derived preview path.

- [x] Add native `Three Horizons PT14 fog: horizontal Tower fog creates no battle terrain` and `explicit terrain still works`; compare an outside-project fog map retaining current generation behavior. Add move-type/accuracy/stat/damage checks at equal RNG/context, including Terrain Pulse before selection.
- [x] Run native RED to observe the existing automatic Misty Terrain; keep visible field fog in reproduction.
- [x] Guard only automatic fog-to-battle effects on TH Tower maps. Do not remove WEATHER_FOG_HORIZONTAL from maps or suppress terrain intentionally created by a move/ability.
- [x] Run H(fog), N(`Three Horizons PT14 fog:`,`fog-green`); keep upstream compile/runtime counterpart for Final. Gate A/B captures field fog and a battle without a false terrain announcement.
- [x] Commit `fix: keep Three Horizons Tower fog atmospheric`.

## Task 7: Investigate the intermittent full-party capture failure

**Files:** new `test/three_horizons_playtest14_capture.c`; existing capture lifecycle tests; inspect `src/battle_script_commands.c`, `src/battle_main.c`, `src/party_menu.c`, `src/pokedex.c`, `src/pokemon_storage_system.c`, `src/three_horizons_capture.c` and follower restoration sites. Private controller cases and `PLAYTEST_14_VERIFICATION.md` own evidence.
**Interfaces:** preserve existing public capture callbacks; introduce no global workaround unless evidence identifies a defect.

- [x] Starting from an unmodified copy of the actual supplied battery, naturally travel to Route11 and attempt the Ekans → first registration if still unseen → nickname → full-party Add-to-Party route. Record exact source/ROM/core/hash, observed Dex state, prior Gyarados/evolution/follower state, input timings, screenshots and result. No fixture manipulation in this required run.
- [x] Use separate labelled fixtures for first-catch Ekans/Drowzee/control species, maximal nickname, yes-swap first/middle/last slot, cancel-to-PC, full-PC failure, recent evolution, Gyarados lead and follower on/off. Compare all unaffected party/box payloads through save/cold reload; check sprite identity/VRAM/callback restoration.
- [x] If a meaningful defect reproduces, add the smallest behavioral regression and record RED before changing its responsible callback/index/lifetime; use systematic-debugging and retain original failing evidence. Otherwise add only justified coverage and retain high-severity unresolved classification.
- [x] Run related capture suites and N(`Three Horizons PT14 capture:`,`capture-investigation`); no skipped failure or assertion suppression.
- [ ] Repeat the exact candidate route at Final; a clean mGBA run never closes the hardware report.
- [x] Commit `test: cover reported full-party capture lifecycle` (or a root-cause-specific fix message only if established).

## Gate A: Carry-forward systems and save safety

- [x] Build P(`gate-a`); record compiler warnings against the inherited baseline, investigate relevant new warnings.
- [x] Complete Tasks2–7 native visual/controller checks on this identified ROM, including old/candidate forest and trio frames, native Kanto map, Flash order, Route9 first arrival, Gear regression and owner-source capture attempt. Run L once here because migration/structure code changed.
- [x] Cold Continue from an untouched private owner-source copy; compare protected state before movement. Save natively, fully close the core, cold Continue again. Assert new version0xA90E, old story/Dex/party/PC/research intact and new PT14 flags still correctly initialized. This intermediate gate is not final exact-ROM acceptance.
- [x] Checkpoint results. Repair failures before adding the new city. Do not run the complete upstream/full host/native matrix yet.

## Task 8: Open Route 8, the Underground Path and Route 7

**Files:** Appendix A travel maps, their source JSON/scripts/layouts, map group registry, `src/data/tilesets/three_horizons.h`, new chapter14 travel script, existing `maps.inc`; trainer/encounter/rematch data; tests `tools/three_horizons/tests/test_playtest14_travel.py`, `test/three_horizons_playtest14_travel.c`.
**Interfaces:** group `gMapGroup_ThreeHorizons14` at76, map order fixed by Appendix A; appended layouts never renumber existing entries. Use Appendix C's first-party contract and Appendix B's wild-encounter tables, existing Cut/trainer/healing/field contracts and Task5 rematch identity API.

- [x] Add map-contract tests for signed group/index bounds, reciprocal Lavender→Route8→Underground→Route7 travel, return warps, connection offsets, no walk/warp into Saffron, and old group75 maps/layouts unchanged. Assert every imported event maps to an owned script/flag/trainer; no native-story aliases leak in.
- [x] Run H(travel) for absent-route RED. Import only the first seven Appendix A donor footprints and explicit project tilesets; register the group and append maps in fixed order. Omit Route7's west connection until Task9 registers Celadon and adds both connection edges; record this explicit pending edge with ownerTask9. Do not leave an undefined destination in generated maps. Adapt Saffron guards to remain restricted without Tea/global-native progression writes.
- [x] Add authored first trainers/encounters, rematch dispatch and relevant Cut object behavior. Route7's donor has no trainer, so preserve its quiet connecting role rather than inventing a forced battle/research scene. Preserve twins' shared identity and doubled battle as Task5 specifies.
- [x] Run H(travel), map/capacity snapshots and N(`Three Horizons PT14 travel:`,`travel-green`); verify walkable warps/signs/items, no sightline through walls, group75↔76 readiness reset, Call pacing and field transitions using TH_IsProjectMap.
- [x] At Gate B traverse both directions with follower, bicycle where allowed, a trainer approach and the Underground entrances; verify native Town Map markers at each section.
- [x] Commit `feat: connect Lavender to Celadon through Routes8 and7`.

## Task 9: Build Celadon's city and accessible interiors

**Files:** Appendix A Celadon maps/layouts/tilesets, `chapter14_celadon.inc`, heal-location registration matching existing TH Centers, `src/field_specials.c` elevator destination logic if shared, tests `tools/three_horizons/tests/test_playtest14_celadon.py`, `test/three_horizons_playtest14_celadon.c`.
**Interfaces:** all21 city maps use native sections and appended TH IDs; elevators resolve only authored TH floors, not FRLG donor destinations. Center becomes a valid healing/blackout location; upper-floor communication features remain consistent with prior TH Centers, without mandatory multiplayer.

- [x] Add `every_celadon_door_returns_to_city`, `store_elevator_keeps_project_destinations`, `city_has_no_future_chapter_exit`, `celadon_center_sets_valid_heal_location` and object-capacity checks (16 active including player/follower, 64 templates).
- [x] Run H(celadon) for RED; import/retarget the city and20 interiors exactly from Appendix A. Add both Route7↔Celadon edges now and test the complete reciprocal Lavender→Celadon route; clear that pending-edge record. Hideout entrance/poster handlers remain Task12-owned wrappers until its maps exist. Add the seven existing native secondary tileset families; retain recognizable Mansion, department floors, Game/Prize Corner and Gym geometry. Remove donor connections/warps into unapproved chapters and use visible boundaries/native in-world guard text.
- [x] Author distinct local NPC/signs, Center healing and return hooks. Native setworldmapflag/first-visit-preview bookkeeping is omitted (its FRLG aliases are zero under TH); retain existing TH area-name presentation without new flags. Tea/guard, Fly, postgame, trainer-card diploma and native regional-unlock dialogue must not grant unrelated progression. Preserve approved free repeatable Counter/Softboiled tutor semantics as Appendix B defines; no new permanent tutor bits.
- [x] Connect Mansion Eevee delivery through an atomic party-or-PC gift, following Appendix B's ordinary level/configuration policy. Use one delivered/hide receipt; no disappearance on full storage, no nickname/Pokémon identity corruption. Add a full-party and all-boxes-full test.
- [x] GateB controller/visual cases pending; focused H(celadon) and native tests PASS (26 host/10 native definitions). Run H(celadon), N(`Three Horizons PT14 celadon:`,`celadon-green`); exercise every elevator floor/cancel/re-entry, stairs, healing with1/6 Pokémon and blackout restoration at Gate B. Capture native city/interior screens for clipping and object visibility.
- [x] Commit `feat: make Celadon a usable city with safe interiors and services`.

## Task 10: Department Store, coins and Prize Corner transactions

**Files:** new `src/three_horizons_celadon.c`, `src/data/three_horizons_celadon.h`, chapter14 header/specials; `chapter14_celadon.inc`; `src/shop.c`/coin/gift helpers only if focused tests expose a shared defect; tests `test/three_horizons_playtest14_economy.c`, `tools/three_horizons/tests/test_playtest14_economy.py`.
**Interfaces:** `u16 TH14_BuildShopStock(u8 shopId, u16 *items, u16 capacity)` returns the number of items excluding ITEM_NONE. Capacity includes the terminator: zero capacity or NULL writes nothing/returns0; invalid shop or insufficient capacity writes ITEM_NONE at index0 when possible and returns0, never a partial shop. Successful output includes the terminator and no write beyond capacity. The script uses a static buffer sized to maximum authored stock plus1, alive until shop exit. `void TH14_ScriptOpenShop(void)` consumes VAR_0x8004 shopId and invokes existing CreatePokemartMenu only for a nonempty valid list. Prize helpers `u8 TH14_TryBuyItemPrize(u8 prizeId)` and `u8 TH14_TryBuyMonPrize(u8 prizeId)` return `enum TH14PrizeResult {TH14_PRIZE_INVALID=0, TH14_PRIZE_GIVEN=1, TH14_PRIZE_NO_FUNDS=2, TH14_PRIZE_NO_ROOM=3, TH14_PRIZE_ALREADY_OWNED=4}`; these are distinct from TH14GiftResult. Failure never charges; scripts branch explicitly on these values and preserve normal confirmation/nickname flow.

- [x] Encode Appendix B stock, active TM move identities, prices/badge/story gates and coin/prize tables in the content manifest. Add exact table assertions plus `empty_capacity_never_overflows`, `reusable_tm_bag_or_pc_is_not_charged_twice`, `failed_delivery_preserves_money_coins_and_receipts`, `invalid_prize_id_no_side_effects` and `coin_cap_no_wrap`.
- [x] Run focused RED. Reuse native shop quantity/ownership/charge-after-AddBagItem behavior instead of altering global item prices or mechanics. Build explicit TH prize tables because FIRERED/LEAFGREEN donor conditionals do not populate an Emerald TH build.
- [x] Implement Coin Case gift, coin sales/games, selected item/TM/Pokémon prizes and roof drink rewards with delivery-before-cost/receipt ordering. Full-PC/party, cancellation or insufficient coins does not consume coins; roof drink is removed only after its TM delivery succeeds. Native slot games remain replayable; tested return callbacks restore field/control/palettes.
- [x] Run H(economy), N(`Three Horizons PT14 economy:`,`economy-green`). Test below/at every stock gate, repeatable purchases, all supported active-TM mapping, full bag/PC, exactly required coins and capped coin balance. Record prize-species alternate long-range availability obligations without creating future locations.
- [x] At Gate B actually buy a TM, reopen it as already-owned, buy/use coins, play/exit a slot machine, redeem a Pokémon into party and PC, cancel a purchase and verify money/coins after native Save/cold Continue.
- [x] Commit `feat: add staged Celadon shops and transactional prizes`; update `PLAYTEST_14_TM_AVAILABILITY.md` with current sources and deferred coverage obligations.

## Task 11: Erika and fourth-badge rewards

**Files:** `chapter14_gym.inc`, Celadon Gym map/scripts, `src/data/trainers.party`, rematch registry for eligible ordinary Gym trainers, unique-item transaction; tests `test/three_horizons_playtest14_erika.c`, `tools/three_horizons/tests/test_playtest14_erika.py`.
**Interfaces:** Erika uses Appendix C donor-based party and permanent trainer flag; badge4, TM19 Giga Drain delivery receipt and guide/champ text are distinct outcomes. Uses Task2 gift API. Erika is never an ordinary rematch.

- [x] Write `erika_before_or_after_giovanni`, `loss_does_not_grant_badge`, `victory_sets_badge_once_tm_full_bag_retry`, `gym_guide_and_repeat_dialogue_after_win`; unchanged ordinary first parties and valid sightlines are also asserted.
- [x] Run RED; port native Gym identity/cut access and seven ordinary trainers with project IDs. Badge/trainer victory is recorded after success even if the TM pocket cannot accept the reward; Erika repeats only the pending TM handoff. No mandatory Hideout receipt gate.
- [x] Run H(erika), N(`Three Horizons PT14 erika:`,`erika-green`); verify fourth badge changes rematch cap through existing code without changing owner Pokémon levels or earlier parties.
- [x] Capture loss/retry, victory/reward and clean route to Erika at Gate B; test Hideout-first ordering on a separate labelled branch.
- [x] Commit `feat: add Erika and retryable Rainbow Badge rewards`.

## Task 12: Rocket Hideout exploration, lift key and puzzles

**Files:** five Appendix A Hideout maps/layouts, `chapter14_hideout.inc`, trainer/item/hidden-item ledgers and elevator adapters; tests `test/three_horizons_playtest14_hideout.c`, `tools/three_horizons/tests/test_playtest14_hideout.py`.
**Interfaces:** poster switch receipt, lift-key dropped/delivered state and explicit TH elevator destinations; item/hide receipt is shared only when it describes the same successful pickup. Door opening derives from the two appropriate guard defeats, not a spare persistent bit.

- [x] Add tests for poster battle→switch→stairs, spinner stop tiles/follower cleanup, every lift destination and cancel, locked-vs-owned-key access, blackout/re-entry, item pickup full-bag retries and guard-door recomputation on reload.
- [x] Run H(hideout) RED; port recognizable B1F–B4F/elevator geometry and trainer roster. Retarget dynamic warps and scripts to TH maps. Rewrite donor Lift Key ordering so a failed give does not remove its object or consume its retry route.
- [x] Add exactly three optional research records with Appendix C text: distribution comparison, unconfirmed ghost/migration statements, and orders for sightings/evolution/witness notes. They are readable scenery, not required new flags or research modules; the mandatory trio supplies the causal clue too.
- [x] Run H(hideout), N(`Three Horizons PT14 hideout:`,`hideout-green`); count active scene objects with follower and ensure the key/lift cannot strand the player. The poster guard and disappearing upper-Tower story Rockets are not ordinary rematches; persistent first-victory bits remain authoritative.
- [x] At Gate B traverse the entire puzzle/lift route and return, collect representative items, black out to the last valid Center and retry. Preserve native before/after geometry evidence where retargeting alters a visible exit.
- [x] Commit `feat: add Rocket Hideout exploration and safe lift-key progression`.

## Task 13: Jessie, James, Giovanni and the Silph Scope

**Files:** chapter14 Hideout script, scene map/templates, trainer data, chapter14 helper; tests `test/three_horizons_playtest14_rocket.c`, `tools/three_horizons/tests/test_playtest14_rocket.py`.
**Interfaces:** `void TH14_BeginRocketPair(void)` initializes the two Appendix C trainer identities through existing two-opponent battle setup; `void TH14_CompleteRocketPair(void)` records both defeats/story completion only after a win. Scope uses Task2's ITEM_SILPH_SCOPE/receipt pair. Existing Jessie/James art and `monicaccina` attribution are retained.

- [x] Add `trio_requires_two_usable_not_eggs`, `trio_loss_retry_retains_scene`, `trio_win_marks_both_distinct_ids_once`, `trio_never_vs_seeker`, `giovanni_defeat_scope_full_bag_retry` and `scope_return_lead_repeats_without_duplicate`.
- [x] Run RED; implement the mandatory Appendix C staging/conversation. Meowth talks and follows/stages with the pair but is not added to their battle party. With fewer than two conscious usable Pokémon, give an in-world retry message and leave progression unchanged; no forced unwinnable double battle.
- [x] Implement Appendix C trio and Giovanni parties, first/win/loss/repeat text and controlled strategic Giovanni voice. Do not imply he knows the cause. Preserve flee/blackout and follower/control cleanup.
- [x] Award Scope only through successful retryable delivery after Giovanni. On failed delivery the source remains reachable and visible; on success give the explicit return-to-Tower lead. No Erika-dependent gate.
- [x] Run H(rocket), N(`Three Horizons PT14 rocket:`,`rocket-green`); at Gate B show all three speakers, correct two-opponent intro/parties, loss/retry and Giovanni→Scope handoff.
- [x] Commit `feat: complete Celadon Rocket story and Silph Scope reward`.

## Gate B: New city, travel and Rocket content

- [x] Build P(`gate-b`) and run the focused map/economy/Gym/Hideout/rocket/rematch native groups plus relevant host files.
- [x] Perform Tasks8–13 practical traversal/service/battle checks, both Erika/Hideout orders, new-group Town Map and Call pacing, twins' single/dual readiness displays and both interaction paths. Label all fixture-created progress; no fabricated owner acceptance.
- [x] Save in Celadon and Hideout on test copies, close/reopen normally; verify saved mapGroup76/mapNum and elevator state, badge, key, Scope and all earlier research survive. Correct failures before implementing the Tower conclusion.
- [x] Update verification with actual evidence and checkpoint; no full upstream matrix yet.

## Task 14: Append MOTHER'S WATCH art and archive record

**Files:** existing Tower1F map/script and new chapter14 tower script for the Gear contact; research constants/data/menu/source/header, `tools/three_horizons/research_photo_art.py`, `graphics/three_horizons/research/photos/mothers_watch.{png,4bpp,gbapal}`, generated photo header/manifest; `test/three_horizons_playtest14_research.c`, `tools/three_horizons/tests/test_playtest14_research.py`.
**Interfaces:** append `TH_RESEARCH_MOTHERS_WATCH=11` (entry count12), `TH_PHOTO_MOTHERS_WATCH=10` (photo count11); existing IDs/call count5 unchanged. Observation and photo have separate Appendix A flags. `static bool32 DrawObserver(u32 slot,s16 x,s16 y,u8 direction)` in the menu uses the current walking outfit from GetPlayerAvatarGraphicsIdByStateId, GetObjectEventGraphicsInfo and LoadObjectEventPaletteCopy into menu-owned tags, with the existing bounded pose/tile-allocation technique; no field-object mutation or saved image buffer. Produces the `TH14_Tower_GearContact` script wrapping TH13_GiveResearchGear, plus `void TH_ResearchDelayCalls(u8 steps)` in the existing research header/source. This snapshots the current map/position and sets the transient step counter; steps0 clears it. A script special `void TH14_DelayAftermathCalls(void)` invokes it with8. Invoke after the mother scene and after Fuji's return/reward scene has reached its final map, before releasing controls. Existing map-change and cold-load pacing resets remain unchanged; pending/delivered flags and call priority never change.

- [x] Add append-only ID/data tests, `mother_photo_requires_gear_and_observation`, `photo_loss_survives_but_resolution_not_implied`, `archive_read_never_changes_flags_or_dex`, `mother_note_does_not_fake_a_call`, `aftermath_pacing_preserves_pending_calls_and_delays_until_eight_steps`, map-change/cold-load reset controls, and photo/entry-count bounds. Record RED for the absent record/art.
- [x] Extend the existing deterministic native-metatile photo generator with a Tower6F graves/stairs crop and subdued spectral tint. Compose one native Marowak subject and the observer at a respectful distance using Appendix C's composition. The observer consumes a second bounded actor slot (total2<=4), shows the selected current outfit, and uses private menu palette tags. Guard all allocations and clean every tag/sprite on failure and exit; do not use the assert-prone generic object sprite factory as an unchecked shortcut.
- [x] Add `DrawObserver` by sharing the existing pose-copy/resource cleanup path; ordinary Pokémon subject rendering stays unchanged. Do not store a historical outfit in the save. The archive renders the currently selected appearance, consistent with a ROM-authored scene rather than a captured framebuffer.
- [x] Implement TH14_Tower_GearContact at Tower1F(5,11), wrapping existing TH13_GiveResearchGear only when missing, with the Scope-return contextual offer; no old observations/photos are fabricated and equipped players are not interrupted. Add the mother's entry and notes. Before resolution show observed/documented evidence; after Fuji rescue, a mother-specific quiet professor note becomes readable through TH_ResearchProfessorNote. It does not queue/complete any call, and earlier notes keep their existing eligibility.
- [x] Run H(research), N(`Three Horizons PT14 research:`,`mother-photo-green`) and existing menu/palette suites. Check all7 outfits, old/new/empty/first/last archive pages, resource exhaustion recovery and repeated viewing. Native exact-ROM art inspection is mandatory in Task19; source/generated PNG alone is not acceptance.
- [x] Commit `feat: add Mothers Watch to the Research Gear archive`.

## Task 15: Upper Tower, Fuji and the Flute

**Files:** new Tower7F map, existing Tower1F and VolunteerPokemonHouse maps/scripts, `chapter14_tower.inc`, trainer and reward ledger; tests `test/three_horizons_playtest14_fuji.c`, `tools/three_horizons/tests/test_playtest14_fuji.py`.
**Interfaces:** consumes Task14's completed TH14_Tower_GearContact and TH14_DelayAftermathCalls scripts. Fuji-rescued and Flute-delivered receipts are separate; Task2 gives ITEM_POKE_FLUTE. Existing Cubone/memorial locals receive conditional dialogue without new flags.

- [x] Add `gearless_scope_return_gets_real_gear_no_old_photos`, `equipped_return_not_interrupted`, `upper_floor_locked_until_mother_resolved`, `fuji_only_after_upper_rockets`, `fuji_loss_reload_no_duplicate_rescue`, `flute_full_bag_retry`, and `fuji_note_does_not_force_call`.
- [x] Port donor Tower7F stairs/three Rocket trainers and Fuji placement, rewriting all donor warps/flags to TH. Resolve all Gear-contact references through Task14. Tower7F is map index33 and lands here before the mother task opens its stairs; focused fixtures can exercise the upper floor while the ordinary route remains blocked until Task16.
- [x] Stage Fuji's one-time rescue/return home only after required upper Rocket victories. Use compassionate Appendix C dialogue and no future lore. Repeat house interaction gives pending Flute safely, then sleeping-Pokémon guidance; duplicate owned bag/PC cases consume no receipt incorrectly.
- [x] Run H(fuji), N(`Three Horizons PT14 fuji:`,`fuji-green`) and the research focused group; Task16 reruns the linked mother/rescue flow. Test direct anomalous arrival, bag full at rescue and later retry, all old Tower receipts, photo/observation and note states across native Save/cold Continue at Final.
- [x] Commit `feat: rescue Fuji and deliver the Poke Flute safely`.

## Task 16: Reveal, document and resolve Cubone's mother

**Files:** `data/maps/TH13_PokemonTower_6F/{map.json,scripts.inc}`, `chapter13_tower.inc`, new `chapter14_tower.inc`, `src/battle_setup.c` classification, existing ghost tests plus `test/three_horizons_playtest14_mother.c`, `tools/three_horizons/tests/test_playtest14_mother.py`.
**Interfaces:** `TH13_Tower_GhostBarrier` delegates to new `TH14_Tower_MotherBarrier`; existing `StartMarowakBattle` retains its special encounter context. Important polarity: `CB2_EndMarowakBattle` returns VAR_RESULT=FALSE only on B_OUTCOME_WON; TRUE means an unresolved returning result, and loss takes the blackout callback. Ordinary post-Scope ghosts use normal battle flags.

- [x] Add native/script tests for no Scope, missing Gear, observed/no-photo, documented/unresolved, and resolved states. Scope reveals identity before photo; photo is mandatory before battle. Flee, Teleport, Poké Doll, abort and loss cannot set resolved or open stairs. Record RED against old endpoint behavior.
- [x] Reuse the ground-floor free Gear contact/return-with-Scope catch-up implemented in Task14; a sixth-floor missing-Gear anomaly safely directs the player down and never pretends photo success. Already-equipped players are not interrupted.
- [x] Implement the Appendix C sequence: reveal MAROWAK/Cubone's mother, observe, complete respectful shutter/field-flash presentation using existing register snapshot/restore, then call TH_ScriptTakeResearchPhoto and assert success or already-owned before battle. The new mandatory transaction records its photo after presentation, not before it. Failed prerequisites/effect completion return safely for retry. Existing optional photo choice behavior remains unchanged.
- [x] Reuse the native female level30 Serious StartMarowakBattle. Add real GhostBallDodge tests for all configured throwable Ball items including Master Ball, plus a normal wild Marowak catchable control. Do not ban the species or fake a Dex caught bit. On the successful callback set MOTHER_WON, then perform cry/quiet/fade; write MOTHER_RESOLVED only after that sequence completes. An on-load MOTHER_WON-but-not-resolved state resumes the calm/fade without another battle, then open actual stair tile/warp. All non-wins retain the photo but keep the barrier.
- [x] Extend Tower classification for group76/7F; run H(mother), N(`Three Horizons PT14 mother:`,`mother-green`) and `test/battle/ghost.c` including Scope controls. Test follower restoration, ordinary post-Scope capture, loss healing destination and re-entry with photo already owned.
- [x] Commit `feat: resolve the Tower mother through required research and battle`.

## Task 17: Accessible Route 11 gate and retryable Snorlax roadblock

**Files:** `src/data/trade.h`, gate trade scripts and existing trade helpers if required; `data/maps/TH13_Route11/{map.json,scripts.inc}`, two new gate maps and bounded landing map/layout, `chapter14_snorlax.inc`, item/encounter ledger; tests `test/three_horizons_playtest14_snorlax.c`, `tools/three_horizons/tests/test_playtest14_snorlax.py`.
**Interfaces:** the sleeping object uses the single Snorlax-resolved flag; accepted results are B_OUTCOME_CAUGHT or B_OUTCOME_WON only. A native wild-battle callback exposes the actual gBattleOutcome to the script after return; do not reuse the mother's inverted boolean as an outcome enum. New landing map is last in Appendix A, no full Route12 network.

- [x] Add `gate_accessible_without_flute`, `snorlax_blocks_all_walkable_lanes`, `no_flute_interaction_no_battle`, `decline_or_escape_keeps_encounter`, `catch_or_win_opens_actual_footprint`, `blackout_retry_no_premature_hide`, `endpoint_has_visible_barricades_and_return_route`.
- [x] Run RED; remove the outside NPC block and restore gate door warps, registering map indices34,35 and36 in order. Port both gate floors with safe NPC corridors and local dialogue. The upstairs aide gives Itemfinder at30 caught/received species via the unique-item transaction, preserving retries and bag/PC ownership. Explicitly select the FireRed NINA data for THREE_HORIZONS: receive Nidorina for a selected non-Egg Nidorino at the offered Pokémon's level, using the existing native in-game trade sequence. Preserve source OT/PID/IVs/ability/held-item definition, successful-delivery receipt, follower refresh and Skarmory trade; cancel/wrong species/failed trade changes no party/receipt. Test native animation, all nonselected identities and cold persistence; no unapproved full-Dex reward or future-route progression grant. Connect the exact Appendix C landing geometry.
- [x] Implement asleep/Flute offer/wake/battle/outcome branches. Keep the object persistent until an accepted result; temporary battle staging may hide it only transiently, restored on all nonwins. Level30 normal Snorlax is catchable; preserve normal nickname/party-or-PC delivery. A caught-mon delivery failure cannot claim a catch/remove the roadblock without the engine's accepted result.
- [x] Reveal the native Leftovers search/pickup only when its actual footprint is reachable; no duplicate hidden item receipt. Open the short safe onward stretch with visible bridge-maintenance barriers and a return path. No invisible collision text or “Playtest ends here.”
- [x] Run H(snorlax), N(`Three Horizons PT14 snorlax:`,`snorlax-green`); test every returning non-win outcome, loss/retry, catch vs defeat, repeated interaction, field-control/follower and native Save/cold state. Document future alternate Snorlax availability obligation, without adding another encounter now.
- [x] Commit `feat: let Snorlax guard the road beyond Route11`.

## Task 18: Run the complete integration matrix and produce the exact candidate

**Files:** all implemented source/tests; `test/save.c` and Task1's `test/three_horizons_playtest14_layout.c`, verification ledger; private build/test artifacts. No unrelated refactor.
**Interfaces:** produces one immutable candidate `.gba`/`.elf`/`.map` bundle tied to an exact committed feature revision; test revision is recorded separately if it differs.

- [x] Commit the completed feature checkpoint before release builds; verify no product source is uncommitted or generated-only. Rerun Task1's compiler-evaluated offset assertions for the baseline save fields used by migration/decoder (location, party, flags, vars, bag/PC items, encrypted money, Dex, storage), retaining the four native size tests and one-byte signed warp fields. Keep the baseline expectations fixed; a mismatch blocks save compatibility rather than changing the expected value.
- [x] Run `make -C tools/mapjson` and `make THREE_HORIZONS=1 TOOLCHAIN=<ARM-path> generated`; run full host discovery via the private PATH-corrected wrapper. Run `.github/docs_validate/inclusive_summary.py` and the PT14 manifest/coverage validator. Fail on unresolved accessible event placeholders, unsafe donor flags/warps, duplicate receipts, missing content or unsupported TM rows.
- [x] Build the full native test ELF with no source override; run all `Three Horizons` tests with normal audio and strict skip-is-fail. Run `test/save.c` separately plus new offset tests, `test/battle/ghost.c`, Misty Terrain and Misty Surge move/ability suites, and other non-TH-prefixed battle regressions affected by fixes. Report unique groups and parameterized cases separately.
- [x] Run U(emerald), U(firered), U(leafgreen) serially, preserving all logs and relevant warning classifications. Restore TH-generated assets afterward and build P(`final-candidate`). No silent assertion suppression, skip or fallback ROM.
- [x] Record exact source/test/compiled revisions, ROM/ELF/map SHA-256, build flags/toolchain, test totals, four layout sizes and offset result, and each upstream compatibility result. Historical Navigator totals remain labelled historical.
- [x] Rehash protected originals and compare original branch/status snapshots. Investigate unexpected differences; do not reset them away. Advance to Task19 only with a passing integration candidate (the open hardware-only Ekans observation remains explicitly separate).

## Task 19: Actual-owner migration and exact-ROM emulator acceptance

**Files:** private PT14 copy of `audit_owner.py`, emulator `run.py`/`rc2_common.py`, new case drivers and sanitized `PLAYTEST_14_VERIFICATION.md` records.
**Interfaces:** decoder accepts explicit input battery/ELF/ROM/output paths; exports full14-box semantic identity plus raw complete storage. Candidate must be the immutable Task18 ROM, not a subsequent local build.

- [x] Parameterize the owner audit without overwriting its original source-baseline outputs. Validate sectors/checksums/coherent latest generation; use wrap-safe generation ordering for general saves. Extend semantic decoding beyond box0 to all14×30 slots and explicit effective nature/ability/forms/shiny/evolution tracker; retain raw comparisons. Add old/new map-group lookup rather than the former group75-only fixture assumption.
- [x] Assert a brand-new session has no `.bin` before every claimed cold start: the inherited runner otherwise silently imports a warm emulator state. Cold boot the actual unmodified owner battery copy into PT14 normally, without fixtures or movement. Compare party/all boxes, PID/nicknames/IVs/EVs/moves/PP/items, badges/Dex, money/inventory, flags/vars, fossils, trade, HM, research/calls, first-win history and false ship-departure against the decoded baseline. Allow only explicitly owned migration deltas and separately justified engine bookkeeping; assert the packed marker independently of its clock bit.
- [x] Use native Start-menu Save, wait actual success, export flash in that same core invocation, fully terminate it, validate the exported131072-byte sectors, then launch a fresh process/session and Continue. Compare again; a serialized warm state or changed file is not enough. Test repeated Continue with earned PT14 receipts, readiness reset and defeat history unchanged.
- [x] Perform the complete controller route on the exact candidate: Gear/old records → Town Map catch-up → practical earlier repair revisits → Route11 gate/sleeping Snorlax → Lavender → Route8 → Underground → Route7 → Celadon stores/coins/prizes → Erika → Hideout/trio/Giovanni → Scope → Tower identified wild ghosts → mother reveal/photo → Ball rejection → victory/quiet passing → upper Rockets → Fuji/Flute → Route11/wake Snorlax → catch or win → open footprint/short road → native Save/full close/cold Continue. Preserve input logs and native frames at each important scene; compare ending permanent state after the second cold boot. Changes earned during play are explained by the action ledger, not normalized away.
- [x] On separate labelled fixture branches verify reverse Erika/Hideout order, all-full bag/PC delivery retries, missing Gear, mother loss/documented retry/won-pending fade, Snorlax decline/escape/loss/catch/defeat, coins/shop persistence, and all old/new photo pages. Reattempt the owner-source capture scenario on the exact final candidate; retain hardware-only classification if unreproduced.
- [x] Run a fresh-new-game smoke path: title/outfit/options, all starter-choice families through focused cases, guaranteed shiny and IV/EV/nature/ability/gender settings unchanged, starting PC items, Daisy map, first battle, healing, map transition, menus/Gear and native save/Continue. Do not substitute this smoke route for the full new-game walkthrough document or claim a full natural new-game emulator journey unless actually performed.
- [x] Document PASS/FAIL/NOT RUN for every branch. A remaining required emulator acceptance failure blocks “passing candidate”; an unestablished VBA-Next result is PENDING, not PASS. Rehash the owner original unchanged.

## Task 20: Release guides, traceability and final independent review

**Files:** `docs/three_horizons/PLAYTEST_14.md`, `PLAYTEST_14_HARDWARE_QA.md`, `PLAYTEST_14_ENCOUNTERS.md`, `PLAYTEST_14_VERIFICATION.md`, `PLAYTEST_14_TM_AVAILABILITY.md`, `PLAYTEST_14_DEVELOPMENT_NOTES.md`; update `PLAYTEST_13_RESEARCH_GEAR.md`, `PLAYTEST_13_REMATCH_CAPACITY.md` with clearly marked PT14 additions. Do not rewrite historical PT13 evidence as a PT14 pass.
**Interfaces:** every guide names the candidate/hash and distinguishes new game, actual-owner continuation, fixtures and pending hardware work.

- [ ] Write the full new-game beta walkthrough from Pallet through all existing chapters and every new Task19 story stop; carry forward approved PT13 route/order, add Daisy map, encounter/repel/hidden-ability sampling (10% where an HA exists), naming/full-party, trainer first/rematch, Cut/Flash, photo decline vs required mother photo, saves and both chapter orders. Include exact NPC locations/rewards/requirements, reasonable encounter sampling instructions and no statistical guarantee from a handful of encounters.
- [ ] Write the exact supplied-save continuation separately: Tower6F starting position/progress, preserve current over-levelled team, backtrack naturally, use missing-map catch-up and existing Gear/photos, complete the bounded route, save/close/Continue. Explain copying/renaming a battery to the new ROM's expected save name only on a backup; no cross-ROM emulator-state loading and no overwrite of the .eps original.
- [ ] Generate encounter/rematch/TM guides from the tested manifests: exact species/levels/weights, all25 stone overrides, active50 TM source/condition/availability status, prizes and later species obligations. List unavailable future coverage as unimplemented, not as a built route.
- [ ] Write focused hardware QA: migration/cold boot, Navigator/photos, capture monitor, repaired trees, gate/Snorlax, city/elevators/store/GameCorner, Erika, Rocket/trio/Scope, atmospheric fog, required mother photo/noncapture/aftermath, Fuji/Flute, repeated native saves. Include a concise defect-report template: ROM hash/core/version, battery checkpoint, last inputs, expected/actual, reproducibility, screenshot. Avoid asking the owner to repeat every automated case.
- [ ] Fill all53 final-report fields from owner task §47 in the verification document, using actual evidence; include all remaining defects/minors and unresolved hardware issue. Update development notes with exact commits/evidence/output locations and no future-chapter promise.
- [ ] Self-check every blueprint section and owner requirement against Appendix D; request one independent whole-branch Astra/Ultra review under requesting-code-review for save, story, interfaces and regressions. Address actionable findings, rerun affected tests/build/acceptance on the corrected exact candidate, and refresh totals/hashes; do not keep screenshots from an obsolete ROM labelled final.
- [ ] Run documentation/manifest validation and focused guide checks; commit `docs: publish local PT14 verification and playtest guides` (local commit only, not remote publication).

## Task 21: Package privately, report and stop for hardware acceptance

**Files:** new `outputs/playtest-14-celadon-silph-scope-<feature-shortsha>/`, matching ZIP and sanitized evidence; local release manifest, no source gameplay edits.

- [ ] Create a never-overwritten output directory using exact feature revision. Copy the immutable passing candidate to `pokemon-three-horizons-playtest-14-celadon-silph-scope.gba`. Include SHA256 manifest, release/encounter/hardware/TM guides, sanitized verification/evidence and migration instructions. Keep ELF/map privately with the exact candidate rather than exposing owner state.
- [ ] Reject package entries containing `.sav`, `.eps`, warm `.bin` states, raw RAM, private baseline/identity inventories, unrelated screenshots or workspace secrets. Whitelist intended files; verify archive member paths and each packaged hash.
- [ ] Reopen a separate extraction of the packaged ROM with a copied battery for boot/Continue/menu smoke; verify packaged ROM SHA equals the exact tested candidate. Recheck all protected source/save/old ROM/package hashes and original worktree statuses.
- [ ] Report the53 required fields through a concise user summary plus linked verification table; distinguish feature revision, compiled/test revision and later documentation commit. State exactly which emulator acceptance happened and that RG40XX H/VBA-Next remains pending.
- [ ] Stop. No merge, push, release publication, repository changes or next chapter. Keep the isolated branch and private evidence for the owner's hardware findings.


## Appendix A: Exact map, trainer and receipt ledger

For each row, donor files are `data/maps/<donor>/map.json` and `scripts.inc`; new files are `data/maps/<TH14 name>/map.json` and `scripts.inc`. New authored layouts go in `data/layouts/<TH14 name>/map.bin` and `border.bin`, with entries appended to `data/layouts/layouts.json`. Register this exact order as `gMapGroup_ThreeHorizons14` appended to `data/maps/map_groups.json`.

| Index | TH14 name | Donor |
|---:|---|---|
|0|TH14_Route8|Route8_Frlg|
|1|TH14_Route8_WestEntrance|Route8_WestEntrance_Frlg|
|2|TH14_UndergroundPath_EastEntrance|UndergroundPath_EastEntrance_Frlg|
|3|TH14_UndergroundPath_EastWestTunnel|UndergroundPath_EastWestTunnel_Frlg|
|4|TH14_UndergroundPath_WestEntrance|UndergroundPath_WestEntrance_Frlg|
|5|TH14_Route7|Route7_Frlg|
|6|TH14_Route7_EastEntrance|Route7_EastEntrance_Frlg|
|7|TH14_CeladonCity|CeladonCity_Frlg|
|8|TH14_CeladonCity_PokemonCenter_1F|CeladonCity_PokemonCenter_1F_Frlg|
|9|TH14_CeladonCity_PokemonCenter_2F|CeladonCity_PokemonCenter_2F_Frlg|
|10|TH14_CeladonCity_Gym|CeladonCity_Gym_Frlg|
|11|TH14_CeladonCity_DepartmentStore_1F|CeladonCity_DepartmentStore_1F_Frlg|
|12|TH14_CeladonCity_DepartmentStore_2F|CeladonCity_DepartmentStore_2F_Frlg|
|13|TH14_CeladonCity_DepartmentStore_3F|CeladonCity_DepartmentStore_3F_Frlg|
|14|TH14_CeladonCity_DepartmentStore_4F|CeladonCity_DepartmentStore_4F_Frlg|
|15|TH14_CeladonCity_DepartmentStore_5F|CeladonCity_DepartmentStore_5F_Frlg|
|16|TH14_CeladonCity_DepartmentStore_Elevator|CeladonCity_DepartmentStore_Elevator_Frlg|
|17|TH14_CeladonCity_DepartmentStore_Roof|CeladonCity_DepartmentStore_Roof_Frlg|
|18|TH14_CeladonCity_Condominiums_1F|CeladonCity_Condominiums_1F_Frlg|
|19|TH14_CeladonCity_Condominiums_2F|CeladonCity_Condominiums_2F_Frlg|
|20|TH14_CeladonCity_Condominiums_3F|CeladonCity_Condominiums_3F_Frlg|
|21|TH14_CeladonCity_Condominiums_Roof|CeladonCity_Condominiums_Roof_Frlg|
|22|TH14_CeladonCity_Condominiums_RoofRoom|CeladonCity_Condominiums_RoofRoom_Frlg|
|23|TH14_CeladonCity_GameCorner|CeladonCity_GameCorner_Frlg|
|24|TH14_CeladonCity_GameCorner_PrizeRoom|CeladonCity_GameCorner_PrizeRoom_Frlg|
|25|TH14_CeladonCity_Restaurant|CeladonCity_Restaurant_Frlg|
|26|TH14_CeladonCity_Hotel|CeladonCity_Hotel_Frlg|
|27|TH14_CeladonCity_House1|CeladonCity_House1_Frlg|
|28|TH14_RocketHideout_B1F|RocketHideout_B1F_Frlg|
|29|TH14_RocketHideout_B2F|RocketHideout_B2F_Frlg|
|30|TH14_RocketHideout_B3F|RocketHideout_B3F_Frlg|
|31|TH14_RocketHideout_B4F|RocketHideout_B4F_Frlg|
|32|TH14_RocketHideout_Elevator|RocketHideout_Elevator_Frlg|
|33|TH14_PokemonTower_7F|PokemonTower_7F_Frlg|
|34|TH14_Route11_EastEntrance_1F|Route11_EastEntrance_1F_Frlg|
|35|TH14_Route11_EastEntrance_2F|Route11_EastEntrance_2F_Frlg|
|36|TH14_Route12_Landing|Route12_Frlg, bounded crop only|

Current layout registry contains787 entries; append instead of inserting/reordering. To avoid modifying shared native layouts while authoring the new city, give new TH14 layouts their own appended identities even when two donor interiors share a source layout. The exact generated numeric IDs must be verified from the registry/generator rather than guessed from list position.

### Landing and external edges

Concrete landing proposal: crop the24-wide Route12 donor from source y60 through81 inclusive, yielding24x22. Transform source(x,y) to(x,y−60), so Snorlax and the hidden Leftovers move from(14,70) to(14,10). Keep only that Snorlax, the nearby sign rewritten for this landing, and the Leftovers; remove all whole-route trainer objects and outside pickups/warps. Author visible maintenance barricades across the north/south walking exits, leaving a small walkable stretch past Snorlax. Final barrier coordinates must be checked against actual metatile collision and viewed at native resolution; do not infer a correct road opening from JSON alone.

The native Route11 right connection uses offset−60 to Route12; with this crop it becomes offset0 to the landing, whose left connection is offset0 back to `TH13_Route11`. Restore native Route11 gate warps at(58,10) -> new gate warp0 and(65,10) -> new gate warp2; preserve existing Diglett warp index0, append these as indices1/2. Gate warp0/1 returns to old Route11 warp1; gate warp2/3 returns to old Route11 warp2; its staircase links the new second floor. Remove the old roadblock NPC at(58,10). This preserves the two-sided gate and its ordinary corridor.

Other explicit edge work: old Lavender left connection -> TH14_Route8; Route8 east -> old Lavender; Route8 west gate remains restricted; underground reciprocal entrances/tunnel; Route7 west -> Celadon; Route7 east gate remains restricted. Celadon's native west Route16 connection and its Route16 clone object must be removed/replaced by visible in-world restriction. Route7's clone of the Celadon Cut tree must point to the TH14 Celadon object/map. No native Saffron, Route16, Route13, Route12 north-gate or fishing-house destination may survive in reachable TH14 content. Existing Tower6F gains the return-compatible stair warp to new7F.

Do not port the donor Tea reward or guard Tea branches: they open Saffron. Do not activate multiplayer/postgame rooms in Center2F or Mansion dialogue. Elevators need TH14 floor mappings and dynamic-warp destinations; copying floor text alone is insufficient.

### Concrete geometry-derived actor staging

These coordinates were checked against decoded donor/project `map.bin` collision/elevation data and existing object coordinates. They remain proposed authored staging: native-resolution art/occlusion, follower movement, camera and emulator walkthrough validation are still pending.

- **Lavender trio:** keep local IDs6/7/8 and their old scripts/receipt, moving Jessie to(14,18), James to(15,18), Meowth to(16,18). All three are elevation3 walkable cells. Rows17/18 across this street are open; their sprite-top cells on row17 avoid building roofs. Preferred player interaction with James is from(15,17), with follower space at(15,16); both cells are walkable. Face actors upward or toward the interacting player. Preserve `FLAG_TH13_ROCKET_CAMEO`, so an owner who already completed the cameo does not replay it. This is a repositioned optional interaction, not a new auto-reward trigger.
- **Hideout trio:** append local IDs10/11/12 to the nine existing B4F objects. Jessie(17,10), James(19,10), Meowth(21,10), elevation3, initially face down; their sprite-top cells on row9 are floor. Existing doorway throat is exactly x17–18 at y12–13, bounded by walls at x16/19. Put the mandatory conditional coordinate triggers at(17,13) and(18,13), before the player can reach Giovanni. Trigger only while TRIO_DEFEATED is false; the existing door first requires both guard victories. Freeze the follower for choreography and keep the player at the trigger cell. With fewer than two usable Pokemon, give the safe retry explanation and move the player one tile down to(17,14) or(18,14), both clear; the map remains escapable to healing. Loss retries. Victory records both distinct trainer histories and TRIO_DEFEATED, then removes all three actor objects using that same result flag. Nine donor templates plus three actors plus player/follower fit14 simultaneous slots, below16, before accounting for visibility reductions. No new doorway collision receipt is needed.
- **Tower1F missing-Gear contact:** append an aide at(5,11), elevation3, facing right. This and its interaction cells(6,11)/(5,10)/(5,12) are walkable and free of existing TH13 objects. It is outside the central entrance/stair corridor. Use the existing Gear/intro grant transaction only when missing; normal equipped players have optional dialogue. Existing five actors plus contact plus player/follower fit eight.
- **Route12 landing:** crop as above; Snorlax(14,10), Leftovers(14,10), nearby sign(15,9), west connection enters walking row10. Route11 exit(65,10) leads via its eastern outdoor strip to landing(0,10). Use visible maintenance barricade metatiles at(14,6),(15,6) and(14,16),(15,16), which are the two-cell north/south bridge widths. Put read-sign interactions on their approach faces, with maintenance text. Snorlax blocks the only horizontal crossing tile from west: adjacent row9 androw11 atx13 are blocked, so x15 cannot be reached from the gate by walking around it. After resolution(14,10) becomes walkable and opens the bridge north to row7 and south to row15. No invisible boundary or second sleeper is needed. Check actual collision after metatile authoring, camera view of both barricades, follower passage and itemfinder underfoot after resolution.

## Exact trainer ledger

New trainer definitions append to the Three Horizons section in `include/constants/opponents.h`; authored parties append to `src/data/trainers.party`. Keep first parties identical to their stated donor records in `src/data/trainers_frlg.party` unless the detailed plan explicitly authors a boss/trio exception. Local IDs below are current donor object-array positions; preserve those identities or update the manifest and tests deliberately when inserting actors.

| ID | New suffix after TRAINER_TH14_ | Donor trainer | New map/local object |
|---:|---|---|---|
|157|ROUTE8_JULIA|TRAINER_LASS_JULIA|Route8/1|
|158|ROUTE8_RICH|TRAINER_GAMER_RICH|Route8/2|
|159|ROUTE8_GLENN|TRAINER_SUPER_NERD_GLENN|Route8/3|
|160|ROUTE8_PAIGE|TRAINER_LASS_PAIGE|Route8/4|
|161|ROUTE8_LESLIE|TRAINER_SUPER_NERD_LESLIE|Route8/5|
|162|ROUTE8_ANDREA|TRAINER_LASS_ANDREA|Route8/6|
|163|ROUTE8_MEGAN|TRAINER_LASS_MEGAN|Route8/7|
|164|ROUTE8_STAN|TRAINER_GAMER_STAN|Route8/8|
|165|ROUTE8_AIDAN|TRAINER_SUPER_NERD_AIDAN|Route8/9|
|166|ROUTE8_ELI_ANNE|TRAINER_TWINS_ELI_ANNE|Route8/12 canonical;13 second interaction|
|167|ROUTE8_RICARDO|TRAINER_BIKER_RICARDO|Route8/14|
|168|ROUTE8_JAREN|TRAINER_BIKER_JAREN|Route8/15|
|169|GYM_KAY|TRAINER_LASS_KAY|CeladonCity_Gym/1|
|170|GYM_BRIDGET|TRAINER_BEAUTY_BRIDGET|CeladonCity_Gym/2|
|171|GYM_TINA|TRAINER_PICNICKER_TINA|CeladonCity_Gym/3|
|172|GYM_TAMIA|TRAINER_BEAUTY_TAMIA|CeladonCity_Gym/4|
|173|GYM_LORI|TRAINER_BEAUTY_LORI|CeladonCity_Gym/5|
|174|GYM_LISA|TRAINER_LASS_LISA|CeladonCity_Gym/6|
|175|GYM_MARY|TRAINER_COOLTRAINER_MARY|CeladonCity_Gym/8|
|176|ERIKA|TRAINER_LEADER_ERIKA|CeladonCity_Gym/7|
|177|GAME_CORNER_GRUNT|TRAINER_TEAM_ROCKET_GRUNT_7|CeladonCity_GameCorner/11|
|178|HIDEOUT_B1F_GRUNT1|TRAINER_TEAM_ROCKET_GRUNT_8|RocketHideout_B1F/2|
|179|HIDEOUT_B1F_GRUNT2|TRAINER_TEAM_ROCKET_GRUNT_9|RocketHideout_B1F/1|
|180|HIDEOUT_B1F_GRUNT3|TRAINER_TEAM_ROCKET_GRUNT_10|RocketHideout_B1F/4|
|181|HIDEOUT_B1F_GRUNT4|TRAINER_TEAM_ROCKET_GRUNT_11|RocketHideout_B1F/3|
|182|HIDEOUT_B1F_GRUNT5|TRAINER_TEAM_ROCKET_GRUNT_12|RocketHideout_B1F/5|
|183|HIDEOUT_B2F_GRUNT|TRAINER_TEAM_ROCKET_GRUNT_13|RocketHideout_B2F/1|
|184|HIDEOUT_B3F_GRUNT1|TRAINER_TEAM_ROCKET_GRUNT_14|RocketHideout_B3F/2|
|185|HIDEOUT_B3F_GRUNT2|TRAINER_TEAM_ROCKET_GRUNT_15|RocketHideout_B3F/1|
|186|HIDEOUT_B4F_GRUNT1|TRAINER_TEAM_ROCKET_GRUNT_18|RocketHideout_B4F/3, Lift Key|
|187|HIDEOUT_B4F_GRUNT2|TRAINER_TEAM_ROCKET_GRUNT_16|RocketHideout_B4F/6, door|
|188|HIDEOUT_B4F_GRUNT3|TRAINER_TEAM_ROCKET_GRUNT_17|RocketHideout_B4F/5, door|
|189|GIOVANNI|TRAINER_BOSS_GIOVANNI|RocketHideout_B4F/1|
|190|JESSIE|Authored distinct trainer|Mandatory authored Hideout trio encounter|
|191|JAMES|Authored distinct trainer|Same encounter, separate history|
|192|TOWER7F_GRUNT1|TRAINER_TEAM_ROCKET_GRUNT_19|PokemonTower_7F/2|
|193|TOWER7F_GRUNT2|TRAINER_TEAM_ROCKET_GRUNT_20|PokemonTower_7F/3|
|194|TOWER7F_GRUNT3|TRAINER_TEAM_ROCKET_GRUNT_21|PokemonTower_7F/4|

The current Three Horizons last appended trainer is156 (`TRAINER_TH13_POKEMONTOWER_6F_EMILIA`). The original special rival IDs855–863 stay unchanged. Trainer storage capacity remains864; TH14 trainer defeat bits occupy0x59D–0x5C2, disjoint from every PT14 receipt.

### Ordinary rematches and the twins

`data/scripts/trainers_frlg.inc:769–791` uses the SAME `TRAINER_TWINS_ELI_ANNE` for both twins and contains ordinary double-rematch scripts. They must not be silently excluded as bosses. `src/three_horizons_rematches.c`, `TH13_ResolveRematchSlot`, intentionally rejects duplicate(map,trainer) registry entries and duplicate map-local slots.

Use one canonical `sRematchEntries` row `(TRAINER_TH14_ROUTE8_ELI_ANNE, MAP_TH14_ROUTE8, 12)`. Both Eli and Anne interaction scripts consult that same identity/readiness bit and launch `trainerbattle_rematch_double` when ready; retain original first-battle double setup and fewer-than-two-usable check. The explicit visual responder alias from local13 to canonical12 can let both sprites respond without allocating another saved slot. The implementation must test interaction with either twin, one shared defeat history, no duplicated reward, first battle unchanged, inability to begin with fewer than two usable Pokemon, and readiness reset after either entry point. Existing host tests assume `trainerbattle_rematch` only: generalize the command match to single or double without relaxing registry uniqueness.

Preserve ordinary gym-trainer eligibility, as prior ordinary Gym trainers already appear in `src/data/three_horizons_rematches.h`. Erika, Giovanni, Jessie and James are excluded. Ordinary Hideout trainers178–188 retain rematches; poster guard177 and disappearing upper-Tower trainers192–194 are excluded as one-time story encounters. Total new ordinary identities:30. Do not exclude all Rockets by class. A disappearing story NPC's canonical defeat bit can drive on-load visibility without a separate permanent hide flag.

## Exact 70-bit ownership pool and 66 allocations

Approved pool:0x8E5–0x91E(58),0x881–0x887(7),0x88E–0x88F(2),0x8E3(1),0x4F9–0x4FA(2). Define each owner once, as an alias of the corresponding existing `FLAG_UNUSED_0x...`; record exact values in `tools/three_horizons/state_manifest.json`. Do not create two named receipt aliases for one event; identical visibility/delivery reads use the one receipt itself. Tables use `P<n>` as shorthand for `FLAG_TH14_PICKUP_<n>` except P36 andP37, which are named `FLAG_TH14_SILPH_SCOPE` and `FLAG_TH14_LIFT_KEY` instead of also defining numeric aliases.

Each ordinary object pickup sets its receipt and disappears only after successful item delivery. Each hidden item uses that same sole receipt. Full bag leaves it false and retryable. Donor map names in the tables omit `_Frlg`; positions are donor coordinates except the noted crop.

| Flag | Owner | Map and coordinate | Reward |
|---|---|---|---|
|0x8E5|P0|Route8(42,10)|Rawst Berry hidden|
|0x8E6|P1|Route8(38,11)|Lum Berry hidden|
|0x8E7|P2|Route8(42,15)|Leppa Berry hidden|
|0x8E8|P3|Route7(16,15)|Wepear Berry hidden|
|0x8E9|P4|UndergroundPath_EastWestTunnel(7,3)|Potion hidden|
|0x8EA|P5|Tunnel(17,5)|Paralyze Heal hidden|
|0x8EB|P6|Tunnel(31,4)|Awakening hidden|
|0x8EC|P7|Tunnel(45,3)|Burn Heal hidden|
|0x8ED|P8|Tunnel(70,3)|Ice Heal hidden|
|0x8EE|P9|Tunnel(55,2)|Ether hidden|
|0x8EF|P10|Tunnel(62,5)|Antidote hidden|
|0x8F0|P11|CeladonCity(5,3)|Ether ball|
|0x8F1|P12|CeladonCity(55,20)|PP Up hidden|
|0x8F2|P13|GameCorner(2,4)|10 coins hidden|
|0x8F3|P14|GameCorner(3,8)|10 coins hidden|
|0x8F4|P15|GameCorner(2,11)|20 coins hidden|
|0x8F5|P16|GameCorner(6,12)|10 coins hidden|
|0x8F6|P17|GameCorner(9,9)|10 coins hidden|
|0x8F7|P18|GameCorner(8,5)|20 coins hidden|
|0x8F8|P19|GameCorner(10,4)|10 coins hidden|
|0x8F9|P20|GameCorner(13,3)|10 coins hidden|
|0x8FA|P21|GameCorner(15,5)|10 coins hidden|
|0x8FB|P22|GameCorner(17,5)|40 coins hidden|
|0x8FC|P23|GameCorner(15,13)|100 coins hidden|
|0x8FD|P24|GameCorner(12,12)|10 coins hidden|
|0x8FE|P25|RocketHideout_B1F(5,16)|Escape Rope ball|
|0x8FF|P26|B1F(1,22)|Hyper Potion ball|
|0x900|P27|B1F(16,17)|PP Up hidden|
|0x901|P28|RocketHideout_B2F(15,3)|X Speed ball|
|0x902|P29|B2F(2,5)|Moon Stone ball|
|0x903|P30|B2F(5,7)|TM12 ball; active mapping Taunt|
|0x904|P31|B2F(0,14)|Super Potion ball|
|0x905|P32|RocketHideout_B3F(12,12)|Rare Candy ball|
|0x906|P33|B3F(19,14)|TM21 ball; active mapping Frustration|
|0x907|P34|B3F(14,24)|Black Glasses ball|
|0x908|P35|B3F(1,3)|Nugget hidden|
|0x909|FLAG_TH14_SILPH_SCOPE|RocketHideout_B4F(20,5)|Scope delivery AND collected-object receipt|
|0x90A|FLAG_TH14_LIFT_KEY|B4F(3,2)|Lift Key delivery AND collected-object receipt|
|0x90B|P38|B4F(1,6)|TM49 ball; active mapping Snatch|
|0x90C|P39|B4F(4,14)|Max Ether ball|
|0x90D|P40|B4F(6,23)|Calcium ball|
|0x90E|P41|B4F(22,6)|Nest Ball hidden|
|0x90F|P42|B4F(16,6)|Net Ball hidden|
|0x910|P43|PokemonTower_7F(11,4)|Soothe Bell hidden|
|0x911|P44|Route12_Landing(14,10), donor(14,70)|Leftovers hidden, underfoot|

Scope/Lift Key object visibility is two-part logic: remove/hide on map load until their prerequisite trainer is defeated; after prerequisite defeat show while the item receipt is false. Never persist a temporary prerequisite-hide by setting the delivery receipt. Scope prerequisite is trainer189; Lift Key prerequisite is trainer186. Elevator access requires successfully delivered/owned Lift Key. Native donor pre-delivery object removal and pre-delivery lift unlock are unsafe and must be rewritten. B1F barrier derives from trainer182; B4F door derives from trainers187AND188. Giovanni/city-Rocket aftermath derives from trainer189, not a duplicate chapter flag.

All additional symbols below begin `FLAG_TH14_`:

| Flag | Suffix | Exact meaning and writer |
|---|---|---|
|0x912|TOWN_MAP|Daisy or Oak/network catch-up actually delivered the unique Town Map; both locations share one receipt|
|0x913|COIN_CASE|Restaurant actually delivered Coin Case; owned check and retryable full bag|
|0x914|EEVEE|Mansion Eevee successfully entered party or PC; also hides its ball; no separate gift/hide flag|
|0x915|ROOF_FRESH_WATER|Fresh Water exchange successfully delivered TM16 Light Screen|
|0x916|ROOF_SODA_POP|Soda Pop exchange successfully delivered TM20 Safeguard|
|0x917|ROOF_LEMONADE|Lemonade exchange successfully delivered TM33 Reflect|
|0x918|GAMBLER_COINS_10|GameCorner Fisher successfully gives10 coins|
|0x919|GAMBLER_COINS_20_A|GameCorner Scientist successfully gives20 coins|
|0x91A|GAMBLER_COINS_20_B|GameCorner Gentleman successfully gives20 coins|
|0x91B|ERIKA_TM|Erika's TM19 Giga Drain delivered; distinct from existing standard badge4 and trainer176 defeat|
|0x91C|HIDEOUT_POSTER|Poster switch intentionally activated and stairs opened|
|0x91D|TRIO_DEFEATED|Authored double encounter WON, both Jessie190/James191 trainer histories recorded, story scene complete|
|0x91E|OBS_MOTHER|Required prebattle mother observation committed; does not imply photo or victory|
|0x881|PHOTO_MOTHER|MOTHER'S WATCH presentation completed and archive photo owned; actual mandatory transaction only|
|0x882|MOTHER_WON|Mother battle returned B_OUTCOME_WON; allows recovery into pending calm/fade if interrupted|
|0x883|MOTHER_RESOLVED|Calm/recognition/fade completed; stairs open and blocking ghost gone|
|0x884|FUJI_RESCUED|Upper Rockets completed and Fuji rescue completed; controls Tower removal AND house presence|
|0x885|POKE_FLUTE|Fuji's Flute actually delivered; pending delivery remains retryable at home|
|0x886|SNORLAX_RESOLVED|Snorlax caught OR defeated; sole persistent roadblock-hide and binocular aftermath receipt|
|0x887|ITEMFINDER|Route11 gate aide delivered Itemfinder at30 caught/received species; retryable and unique|
|0x88E|NINA_TRADE|Route11 gate native local trade successfully completed; no repeat on decline/failure|

Unassigned approved reserve:0x88F,0x8E3,0x4F9,0x4FA. Leave undefined/unmodified until a named requirement needs one. A pool does not itself authorize resetting unused bits in old batteries.

Extra no-new-bit cases: existing Research Gear grant/intro path and old receipts; badge4 standard flag; repeatable shop/prize transactions and tutors; native menu/coins/money fields; old Lavender cameo/rival receipts; trainer history and barrier state; all new environmental records are repeatable text; quiet later archive note is derived from mother/Fuji state and does not pretend a new professor call occurred. No Tea reward. Do not assign spare flags just to maintain artificial counts.



## Appendix B: Encounter, trainer and economy data

Add exactly two TH14 rows to `src/data/wild_encounters.json` in the Three Horizons encounter group, using new map constants from the map ledger. `land_mons.encounter_rate=21` on both; slot weights are the existing global 12-slot distribution, not new global weights. All min/max levels equal the single level below. No new time-of-day variations or obligatory research event.

| Slot (zero-based) | Weight | Route 8 | Level | Route 7 | Level |
|---|---:|---|---:|---|---:|
| 0 | 20% | Pidgey | 18 | Pidgey | 19 |
| 1 | 20% | Meowth | 18 | Meowth | 17 |
| 2 | 10% | Growlithe | 16 | Oddish | 19 |
| 3 | 10% | Vulpix | 16 | Bellsprout | 19 |
| 4 | 10% | Pidgey | 20 | Meowth | 18 |
| 5 | 10% | Meowth | 20 | Pidgey | 22 |
| 6 | 5% | Ekans | 17 | Growlithe | 18 |
| 7 | 5% | Sandshrew | 17 | Vulpix | 18 |
| 8 | 4% | Growlithe | 17 | Oddish | 22 |
| 9 | 4% | Vulpix | 17 | Bellsprout | 22 |
| 10 | 1% | Ekans | 19 | Growlithe | 20 |
| 11 | 1% | Sandshrew | 19 | Vulpix | 20 |

Totals: Route 8 Pidgey30/Meowth30/Growlithe14/Vulpix14/Ekans6/Sandshrew6; Route 7 Pidgey30/Meowth30/Oddish14/Bellsprout14/Growlithe6/Vulpix6. This merges FRLG version identities at donor-level ranges, gives both stone fire families a meaningful home beside Celadon's stones, and preserves Kanto breathing room. No extra cross-region species are needed to satisfy 'curated ... where appropriate'. Do not copy inaccessible donor water/fishing tables onto these land routes, the Underground, or the bounded Route12 footprint.

Host test: assert exact table, map uniqueness, slot count, weights sum100, valid species/levels, no native donor-row edits; regenerate encounter guide from the same JSON. Native test: force representative rolls/slots and verify the expected species/level, lawful current stats/ability and normal capture. No claim of statistical sampling is needed for deterministic table coverage.

### Rematch implementation interface

Current ownership files:

- `src/three_horizons_rematches.c`: readiness, scaling, generation.
- `src/data/three_horizons_rematches.h`: explicit ordinary registry plus existing general level tiers.
- `include/three_horizons_rematches.h`: public interface.
- `src/data/trainers.party`: TH first parties; `src/data/trainers_frlg.party`: new donor first parties.
- `test/three_horizons_rematches.c`: existing generated-party, clamp, first-battle, registry and readiness checks.

Current `TH13_CreateRematchPartyFromTrainer(party, trainer, highest, badges)` has no trainer ID. Do not infer identity from a name, class, party species or pointer search. Extend the generation path with an explicit `u16 trainerId` in a new keyed internal function; retain the existing function as a `TRAINER_NONE` compatibility wrapper for current callers/tests. `TH13_TryCreateRematchParty` passes its actual ID. A synthetic/unknown ID may use existing level tiers but cannot gain a stone override.

Add ROM rows `{trainerId, partySlot, baseSpecies, evolvedSpecies, minLevel, minBadges}`. `partySlot` is ZERO BASED PARTY index; it is unrelated to map localId/rematch readiness slots. Resolve only after the existing level-offset scaling; require all predicates, including exact original base species. Reject duplicate/conflicting keys in tests. Apply normal level tiers first, then these exact overrides. No change to player evolution, first parties, caps or persistence.

Thresholds: Growlithe→Arcanine and Vulpix→Ninetales at resulting member level >=32 AND badge count >=4. Pikachu→Raichu, Clefairy→Clefable and Jigglypuff→Wigglytuff at member level >=30 AND badge count >=3. The fire threshold follows Celadon elemental-stone access; level30 fairies/electric can develop in the already-supported three-badge rematch cap35. These are authored trainer rules, not claims about player evolution levels.

### Exact override keys (25 rows)

Every row below means one ROM record per listed slot. No other stone, friendship, trade or branched evolution gets an implicit rule.

| Trainer constant | Party slot(s) | Base → result | Level / badges |
|---|---|---|---|
| TRAINER_TH9_LASS_ROBIN | 0 | Jigglypuff → Wigglytuff | 30 / 3 |
| TRAINER_TH9_LASS_IRIS | 0 | Clefairy → Clefable | 30 / 3 |
| TRAINER_TH12_PICNICKER_NANCY | 1 | Pikachu → Raichu | 30 / 3 |
| TRAINER_TH12_GENTLEMAN_THOMAS | 0,1 | Growlithe → Arcanine | 32 / 4 |
| TRAINER_TH12_GENTLEMAN_BROOKS | 0 | Pikachu → Raichu | 30 / 3 |
| TRAINER_TH12_GENTLEMAN_LAMAR | 0 | Growlithe → Arcanine | 32 / 4 |
| TRAINER_TH12_LASS_DAWN | 1 | Pikachu → Raichu | 30 / 3 |
| TRAINER_TH12_SAILOR_DWAYNE | 0,1 | Pikachu → Raichu | 30 / 3 |
| TRAINER_TH12_GENTLEMAN_TUCKER | 0 | Pikachu → Raichu | 30 / 3 |
| TRAINER_TH13_ROUTE11_DARIAN | 0 | Growlithe → Arcanine | 32 / 4 |
| TRAINER_TH13_ROUTE11_DARIAN | 1 | Vulpix → Ninetales | 32 / 4 |
| TRAINER_TH13_ROUTE9_CHRIS | 0 | Growlithe → Arcanine | 32 / 4 |
| TRAINER_TH13_ROUTE10_HEIDI | 0 | Pikachu → Raichu | 30 / 3 |
| TRAINER_TH13_ROUTE10_HEIDI | 1 | Clefairy → Clefable | 30 / 3 |
| TRAINER_TH13_ROCKTUNNEL_1F_LEAH | 1 | Clefairy → Clefable | 30 / 3 |
| TRAINER_TH13_ROCKTUNNEL_B1F_SOFIA | 0 | Jigglypuff → Wigglytuff | 30 / 3 |
| TRAINER_TH14_ROUTE8_JULIA | 0,1 | Clefairy → Clefable | 30 / 3 |
| TRAINER_TH14_ROUTE8_RICH | 0 | Growlithe → Arcanine | 32 / 4 |
| TRAINER_TH14_ROUTE8_RICH | 1 | Vulpix → Ninetales | 32 / 4 |
| TRAINER_TH14_ROUTE8_MEGAN | 4 | Pikachu → Raichu | 30 / 3 |
| TRAINER_TH14_ROUTE8_ELI_ANNE | 0 | Clefairy → Clefable | 30 / 3 |
| TRAINER_TH14_ROUTE8_ELI_ANNE | 1 | Jigglypuff → Wigglytuff | 30 / 3 |

18 existing +7 new slots. Map ledger assigns Julia157, Rich158, Megan163, Eli_Anne166; use constants rather than numbers. Existing ship rows remain supported registry identities even after the ship departs. No Surge, Erika, rival, Jessie/James or Giovanni override. Other new Gym trainers are Grass specialists; do not automatically stone-evolve Gloom/Weepinbell/Exeggcute. Eli/Anne remain one canonical trainer/party identity; their two map graphics cannot create two party overrides or rewards.

### Current data consistency (no species edits needed)

`src/pokemon.c:465` selects `level_up_learnsets/gen_9.h`; do not audit `gen_1.h` just because these are Gen1 species. All five use their native species table, without a TH override. Keep `mon.ability=ABILITY_NONE` and clear moves before `GenerateMonFromTrainerMon`, as current code does. `B_TRAINER_MON_RANDOM_ABILITY=0` in `include/config/battle.h:395` gives deterministic normal FIRST ability, not a hidden ability or random new branch.

| Result | HP/Atk/Def/SpA/SpD/Spe | Expected normal ability | Base EXP | EV yield | Current generated final four moves at these thresholds |
|---|---|---|---:|---|---|
| Arcanine | 90/110/80/100/80/95 | Intimidate | 194 | Atk2 | Leer, Flame Wheel, Take Down, Flamethrower |
| Ninetales | 73/76/75/81/100/100 | Flash Fire | 177 | SpD1, Spe1 | Inferno, Quick Attack, Flamethrower, Tail Whip |
| Raichu | 60/90/55/90/80/110 | Static | 243 | Spe3 | Tail Whip, Double Team, Light Screen, Thunderbolt |
| Clefable | 95/70/73/95/90/60 | Cute Charm | 242 | HP3 | Metronome, Meteor Mash, Moonblast, Life Dew |
| Wigglytuff | 140/70/45/85/50/45 | Cute Charm | 218 | HP3 | Double-Edge, Body Slam, Charm, Play Rough |

Expected moves are based on current ordered level-up lists; assert actual generated moves in native tests before completion. Clefable is Fairy and Wigglytuff Normal/Fairy under current types. Do not reduce species EXP/EV yields to compensate; existing cap and party offsets control farming. Battle code already takes EXP/EVs from actual `faintedSpecies` (`src/battle_script_commands.c:2215,2343`) and Seen from actual enemy mons (`src/battle_main.c:5296`). Exercise these integration paths so evolved-party rendering alone cannot pass.

Boundary tests: each exact row at L-1/L/L+1, badges B-1/B; IDs and slots deliberately mismatched; base species mismatch; no readiness/first battle; badge0/3/4/8 clamp extremes; non-Egg highest; retain relative offsets, party size, IVs/held items and original immutable data. Repeated generation uses same species/moves/ability. Actual battle verifies Seen(result)=true and Caught(result) unchanged, experience increases using result and correct EV increment, including preexisting EXP Share behavior. Table-test all25 rows, not only Darian.

### Store stock and services

New economy implementation ownership proposal: `include/three_horizons_chapter14.h`, `src/three_horizons_celadon.c`, `src/data/three_horizons_celadon.h`, TH14 Celadon scripts and focused `test/three_horizons_playtest14_economy.c`. Use existing `data/specials.inc` registration conventions.

ROM stock rows hold vendor/item/minBadges/requiredFlag, using `ITEM_TM_<MOVE>` identities and flag0 for no story gate. Prices come from existing `GetItemPrice`; do not create global price overrides. A small checked, terminated transient `u16` buffer feeds `CreatePokemartMenu`. It must outlive the menu; never pass a stack array. A TH-only script special can select vendor via `VAR_0x8004`, open the menu, then use the same script-stop/resume lifecycle as `ScrCmd_pokemart`. Existing `CreatePokemartMenu`/`SetShopItemsForSale` merely retain/count the supplied pointer; the dynamic-shop tutorial is not evidence of an active stock filter here. Avoid `.shopCriteriaFunc` changes that would unexpectedly gate other vendors.

### TM clerk (2F)

| Minimum badges | Active item / move | Price |
|---:|---|---:|
| 3 | TM05 Roar / ITEM_TM_ROAR | 1,000 |
| 3 | TM28 Dig / ITEM_TM_DIG | 2,000 |
| 3 | TM31 Brick Break / ITEM_TM_BRICK_BREAK | 3,000 |
| 3 | TM43 Secret Power / ITEM_TM_SECRET_POWER | 3,000 |
| 3 | TM45 Attract / ITEM_TM_ATTRACT | 3,000 |
| 4 | TM15 Hyper Beam / ITEM_TM_HYPER_BEAM | 7,500 |
| 4 | TM17 Protect / ITEM_TM_PROTECT | 3,000 |
| 4 | TM44 Rest / ITEM_TM_REST | 3,000 |

Eight total store TMs at four badges. No Giovanni/Scope gate; Erika/Hideout order remains independent. The shop is open at arrival; ordinary supplies do not gain a new badge gate. Stock tables explicitly encode the TM eligibility stage. No later entries become visible merely because a debug/save fixture has >4 badges. Future stock is documentation-only.

Native shop behavior already handles reusable TMs: `src/shop.c:1024` refuses ownership in bag OR PC, `:1035` restricts important-item quantity to1, `:1150` adds before money deduction. Retain these paths and native 'sold out' feedback. `AddBagItem` itself DOES NOT deduplicate important items, so gifts/prizes need explicit ownership checks too. Do not use purchase flags for store TMs.

### Remaining floors

- 2F supplies, donor stock at current prices: Great Ball600, Super Potion700, Revive2000; Antidote/Paralyze Heal/Awakening/Burn Heal/Ice Heal200 each; Super Repel700. No Ultra Ball expansion, global Repel repricing or existing training-store changes.
- 3F: free repeatable Counter tutor, compatible party mons only, no receipt (consistent with reusable tutor behavior). Native donor `EventScript_CounterTutor` suppresses once-only FLAG_TUTOR_COUNTER when TMs reusable, but still unconditionally calls the misleading 'can only be learned once' warning. Author TH text and call existing `ChooseMonForMoveTutor` with MOVE_COUNTER; do not carry that warning. Cancel, Egg, incompatible, already-knows and full-moves replacement must return safely. Replace mandatory link-trade tutorial promises with project-accurate local dialogue; do not instantiate multiplayer services.
- City Soft-Boiled tutor: retain the donor tutor and native access footprint, same free-repeatable/no-receipt policy and corrected warning as Counter; no new Surf unlock just to reach it. `CeladonCity_Frlg/scripts.inc:27` and `move_tutors_frlg.inc:211` are the donor owners.
- 4F: Poke Doll300, Retro Mail50, Fire/Thunder/Water/Leaf Stone3000 each. Do not add Moon/Linking Cords/future regional evolution items. Preserve current player evolution machinery.
- 5F battle items: X Attack1000, X Defense2000, X Speed1000, X Sp. Atk1000, X Accuracy1000, Guard Spec1500, Dire Hit1000. Vitamins HP Up/Protein/Iron/Calcium/Zinc/Carbos10000 each. Use canonical aliases carefully: old ITEM_X_DEFEND==ITEM_X_DEFENSE; ITEM_X_SPECIAL==ITEM_X_SP_ATK.
- Roof vending: Fresh Water200, Soda Pop300, Lemonade400, matching active `GetItemPrice` rather than donor's outdated hardcoded Lemonade350; show matching prices, add item before charge, no charge on failed delivery.
- Roof drink exchanges: Fresh Water→TM16 Light Screen; Soda Pop→TM20 Safeguard; Lemonade→TM33 Reflect. Three explicit TH once receipts. Confirm drink in bag, reward absent from bag/PC and space; deliver successfully before consuming exactly one drink/committing receipt. Already-owned result consumes no drink and can acknowledge ownership without awarding another. Full bag, cancel or failure leaves gift retryable. Assert preserved other receipts on migration.
- Mansion gift: donor Eevee level25, one receipt/visibility flag, give via party-or-PC before hiding; full storage stays retryable. This is ordinary donor content within approved Mansion, not a new partner customization system. Source: `CeladonCity_Condominiums_RoofRoom_Frlg/scripts.inc`.
- Erika reward: TM19 Giga Drain (`ITEM_TM_GIGA_DRAIN`), badge and separate pending TM receipt. Full bag cannot revoke badge or lose TM; bag/PC already-owned handling must avoid a duplicate. No ordinary rematch for leader.

### Game Corner / Prize Corner

Use TH-specific tables and menus; donor Pokémon scripts are empty under the Emerald TH build because only FIRERED/LEAFGREEN set species/price/level. Do not merely rename donor scripts. Use native slot play interface (`playslotmachine`, `GetRandomSlotMachineId`) and coin UI; preserve native game odds/payout system, no new gambling mechanic or real-money integration.

Coin Case: restaurant handoff, once-only TH receipt; owned in bag OR PC blocks duplicate; full-bag refusal retries. Game menu availability checks actual usable possession consistently, not just an unrelated FRLG receipt. Coin Case is native key-item usage.

Coins: native cap9999 (`include/constants/coins.h`). Buy50 for1000 or500 for10000. Paid bundles require complete capacity and funds, otherwise no coins/money changes; full bundle added before charge. Use widened arithmetic for TH coin helpers, clamp payouts at9999 and reject underflow. Test9999,9998,9950,9949 and9499/9500 as boundary states. Free donor NPC gifts10/20/20 and all12 hidden coin pickups retain distinct ledger receipts; capacity failure cannot silently consume a unique pickup. Existing `AddCoins` has questionable oversized-u16 addition handling; TH call ranges must be checked/widened. Normal slot payouts already fit safe ranges, so do not expand scope into rewriting unrelated coin systems.

### Pokémon prizes (repeatable, FireRed identity)

| Species | Level | Coins | Current optional alternate / future obligation |
|---|---:|---:|---|
| Abra | 9 | 180 | Existing TH12 Route24 levels8/10/12 and Route25 levels9/11/13 |
| Clefairy | 8 | 500 | Existing TH Mt. Moon B2F level10 |
| Dratini | 18 | 2,800 | Document later non-Game-Corner route obligation; no future map now |
| Scyther | 25 | 5,500 | Document alternate long-range availability obligation |
| Porygon | 26 | 9,999 | Document alternate long-range availability obligation |

Do not import version-exclusive Pinsir instead of Dratini: Pinsir already has an authored Forest home, and the five-entry FR identity fits the native menu. Player may decline every prize; none gates story. Ordinary species creation/default legal attributes, no competitive package, forced shiny, hidden ability or extra customization.

Use existing `GiveScriptedMonToPlayer` party/PC semantics (`MON_GIVEN_TO_PARTY`, `MON_GIVEN_TO_PC`, `MON_CANT_GIVE`), retaining nickname and correct PC-transfer messaging. Charge coins only after successful delivery. All-full storage/cancel/insufficient coins changes no party/box/coins/receipt. Prize mons are repeatable purchases, so no persistent per-prize receipt. Caught/Seen use native successful gift behavior; failed delivery cannot mark ownership.

### TM prizes (one reusable ownership, no purchase bits)

| Active TM | Move | Coins |
|---|---|---:|
| TM13 | Ice Beam | 4,000 |
| TM23 | Iron Tail | 3,500 |
| TM24 | Thunderbolt | 4,000 |
| TM30 | Shadow Ball | 4,500 |
| TM35 | Flamethrower | 4,000 |

Use `ITEM_TM_<MOVE>` internally. Check bag OR PC ownership before charge; give first, charge only on success. The donor `TryGivePrize` removes coins before `giveitem` and does not deduplicate reusable TMs; correct the TH path.

### Item prizes (repeatable)

Smoke Ball800; Miracle Seed1000; Charcoal1000; Mystic Water1000; Yellow Flute1600 coins. Donor-based prices; native item behavior. Quantity1 per transaction, exact delivery before charge. No hidden per-item receipt.


## Appendix C: Locked scene, reward and dialogue contracts

**First parties:** all36 donor identities in Appendix A copy their complete corresponding `src/data/trainers_frlg.party` record at base revision2d85555, including species/levels/moves/items/AI, into appended TH records; new name/ID/maps are the only ordinary-trainer changes. Metadata correction: Erika is Female. Erika remains Victreebel29 (Stun Spore/Acid/Poison Powder/Giga Drain), Tangela24 (Poison Powder/Constrict/Ingrain/Giga Drain), Vileplume29 (Sleep Powder/Acid/Stun Spore/Giga Drain), donor IVs0 and Hyper Potion/Full Heal. Giovanni remains Onix25/Rhyhorn24/Kangaskhan29 with donor IVs30 and current generated legal moves; use Rocket-appropriate Suspicious encounter music instead of donor Aqua music. No scaling of these first parties to the owner's level50 team.

**Authored trio:** Jessie190 has Arbok28, Intimidate, Crunch/Acid/Glare/Screech; James191 has Koffing28, Levitate, Sludge/Assurance/Smokescreen/Haze. Each has IVs10 in all six stats, no held item, AI Check Bad Move/Try To Faint, existing TH Jessie/James portrait, Suspicious music, `Multi Party: Half`. Meowth is a speaking scene actor, not a third battle Pokémon. These are the only authored-party exceptions to the donor table. Evolution beyond these current members, Growley and other future companions are not added now.

**Gate trade:** `INGAME_TRADE_NIDORINOA` must select the FireRed NINA record explicitly for THREE_HORIZONS, preserving upstream branches. Offered non-Egg Nidorino becomes Nidorina at the offered level, nickname NINA, OT TURNER/13637, PID0x00eeca15, ability slot0, no held item, donor IVs `{22,25,18,19,22,15}` in native struct order. Use the existing native selection/trade/caught/Seen logic and success-only FLAG_TH14_NINA_TRADE; no multiplayer dependency or extra editor. Aide Itemfinder gate is30 caught/received species, independently retryable; a full later-generation Dex is not enabled.

**Mother field/photo staging:** preserve all existing Tower6F actor IDs; append one scene actor and use the existing barrier approach. Before reveal the ghost remains unidentified; with Scope stage Marowak at(11,16), the player one tile back from the trigger at(11,14), and hide/restore the follower through the scene. No upstairs Cubone actor is invented. Photo crop is Tower6F left4/top11,14×6 metatiles (224×96), with graves/stair recognizable. Native screen photo rectangle starts(8,32); Marowak's center(128,112) faces up, walking-outfit observer center(128,80) faces down. Check feet and crop bounds against actual sprite dimensions. Keep fog subdued and the subjects visible. Adjust only pixel anchors if real rendering requires alignment; preserve composition and actor distance.

After photo capture and battle victory, set MOTHER_WON; play the native Marowak cry and wait for it, pause45 frames without exposition, use the native fading/object-removal presentation, then set MOTHER_RESOLVED and restore the ordinary Tower track/field control. Follower is restored exactly once. A pending-won saved state resumes the calm/fade, not another reward/battle. Fuji rescue changes the later quiet archive note; it does not add a professor call. Existing pending calls are not erased: use Task14's `TH14_DelayAftermathCalls`/`TH_ResearchDelayCalls(u8 steps)` through existing transient pacing/context, invoke with8 after the mother/Fuji scenes so their immediate return to control is quiet; no save field or delivered flag is changed. Apply the delay on the final scene map; test eight movement steps and existing map-change/cold-load resets while preserving normal call priority.

The following is the required narrative copy/beat contract. Reflow into native text pages with measured line width and retained meaning; do not add future revelations. All interaction branches have short repeat text and safe release paths.

| Owner/branch | Copy and ordering |
| --- | --- |
| Daisy, qualified | “My brother is always rushing off! Take a TOWN MAP so you won't lose your way.” → successful item fanfare → “You can open it from your BAG.” Pre-partner remains friendly conversation. |
| Oak catch-up | “Have you picked up DAISY's TOWN MAP? I have a spare for researchers heading farther afield.” → give only if missing. Full bag: ask for space and keep retry available. |
| Flash, qualified | “OAK sent these supplies for your research. Your POKéDEX already records ten species! ROCK TUNNEL lies ahead. This should help you find your way.” → HM05 delivery → explain conscious compatible non-Egg field use, HM kept, no learned move/free slot needed. |
| Lavender rival, first | “Not here. People are grieving. OAK asked us to pay attention to what POKéMON are experiencing, too. I'll keep training. But next time we meet, we're battling!” |
| Lavender rival, repeat | “There will be time for another battle. For now, let's show some respect.” No battle command or receipt reset. |
| Tower observer | “GIOVANNI ordered us to collect unusual sightings, ghost reports and migration notes. I'm on paperwork duty. These reports are going to CELADON.” Repeat: “Our people in CELADON are comparing the reports. They have equipment for things we can't identify.” |
| No-Scope barrier | “A restless presence bars the stairs. A SILPH SCOPE could reveal it. The ROCKET observer is sending ghost reports to CELADON. JESSIE and JAMES are heading there, too.” No developer completion sentence. |
| Distribution record | “A marked distribution map. Unusual sightings are circled beside reports from local habitats.” |
| Unconfirmed report | “GHOST SIGHTINGS / MIGRATION REPORTS. Several accounts are marked UNCONFIRMED.” |
| Orders | “Record rare appearances, abnormal evolution and witness accounts. Send copies for comparison. Do not assume a cause.” |
| Hideout trio | Jessie: “These reports are important TEAM ROCKET business!” James: “Then why am I carrying all the notebooks?” Meowth: “The BOSS compares the sightings before we grab the rare ones! Er… forget you heard that!” Jessie/James obstruct the player; their defeat is comic frustration, not defection or heroism. |
| Trio insufficient party | “Come back with two POKéMON ready to battle!” Step back onto the verified free tile, release controls, no win/history receipt. |
| Giovanni before battle | “Anyone can chase a rare POKéMON. Knowing where it will appear first—that is useful. You have interfered enough.” |
| Scope reward/repeat | “The SILPH SCOPE reveals things ordinary eyes cannot identify. The ghost in POKéMON TOWER may finally be seen.” If bag full the reward stays available. |
| Mother reveal | “The SILPH SCOPE reveals MAROWAK. It is the restless spirit of CUBONE's mother. She still stands watch over the stairs.” → respectful required record/photo → battle. |
| Missing Gear | “OAK's research aide on the ground floor can help you record what the SCOPE reveals.” No false photo/battle completion. |
| Ball rejection | Use native in-world GhostBallDodge/spirit explanation; no developer restriction message. |
| Mother resolution | “MAROWAK's anger begins to fade. Her watch is over.” Let the cry/pause/fade carry the scene; no call or lecture. |
| Mother archive before resolution | “OBSERVED / DOCUMENTED. A mother's spirit remained at the Tower. Her concern for CUBONE seems stronger than the place itself.” No CAUGHT status. |
| Mother archive after Fuji | “OAK: Habitat tells us where a POKéMON lives. This record reminds us that bonds and memory deserve careful study, too.” Quiet note only; no claim that a call was received. |
| Fuji | “The SCOPE helped you see her. You stayed long enough to understand her. Some things are remembered even when we cannot measure them.” Then thanks/reward and “The POKé FLUTE can wake a deeply sleeping POKéMON.” No future-region answers. |
| Snorlax before Flute | “SNORLAX is sleeping soundly. It won't budge.” Footpath remains blocked. |
| Snorlax with Flute | “Play the POKé FLUTE?” Decline leaves everything unchanged; accepted wake plays the native flute/cry and battle. |
| Visible endpoint barricades | “Bridge maintenance ahead. Please keep this section clear.” The opened Snorlax footprint and safe return remain usable; no playtest endpoint text. |

**Manifest contract:** `chapter14_maps.json` contains ordered `{name, donor, group, index, layout, ownerTask}` rows. `chapter14_content.json` contains schemaVersion1 and arrays `receipts` (name,value,kind,writer,reward,coordinate), `trainers` (constant,id,donor,map,localId,rematch,interactionAliases), `encounters`, `shops`, `prizes`, `rematchEvolutions`, `unfinishedInteractions`. It records the exact Appendix A/B values and the authored trio above. The existing `state_manifest.json` keeps its current schema; add allocated flags/pickups/trainers without duplicating aliases. Host checks compare the manifests to compiled/authored sources; final `unfinishedInteractions` must be empty. JSON is a checked data contract, not a substitute for emulator behavior.

## Appendix D: Requirement and gate traceability

| Approved blueprint area / owner requirement | Owning tasks and acceptance |
| --- | --- |
| Canon, protected lineage, actual hardware source, no future story | Header/constraints; Tasks1,19–21; byte-identical Bible and protected hashes |
| Capacity, map-family behavior, explicit flags, migration | Tasks1,8–9,15–18; immutable old IDs and exact owner comparison |
| Reviewed Navigator preserved, exactly3 modules | Tasks14,18–20; old/new archive controller tests |
| Town Map early/catch-up/frontend | Task2, Gates A/B, Task19 |
| Forest visuals and Route9 Cut | Task3, Gate A, Task19 |
| Flash, rival, trio staging, Rocket causal lead | Task4, Gate A, Task19 |
| Rematch greetings/unbeaten/twins/stone tiers | Task5,8,11–12; Gate B/Final, documented thresholds/flags |
| Tower atmospheric fog | Task6, Gates A/Final, explicit terrain controls |
| High-severity intermittent capture | Task7,19; mandatory owner-copy attempt, separate fixtures, hardware monitor |
| Route8/Underground/Route7 | Task8, Gate B, exact route/encounters |
| Complete living Celadon, Mansion, safe elevators/doors | Task9, Gate B, Task19 |
| Department/TM architecture, tutors, coins/prizes | Task10, Gate B, Tasks19–20; all50 active TM coverage document |
| Erika available in either order | Task11, Gate B, Task19 reverse branch |
| Hideout, reports, trio, Giovanni, Scope | Tasks12–13, Gate B, exact route/retry tests |
| Scope wild ghosts, mother photo/noncapture/peaceful resolution | Tasks14–16, Task18 ghost suite, Task19 exact art/battle/fade |
| Missing Gear, upper Rockets, Fuji, Flute | Tasks14–16,19; independent receipts/cold retries |
| Accessible gate, Itemfinder/trade, Snorlax/physical endpoint | Task17,19; accepted outcome and bounded road proof |
| Save compatibility, all supported versions and exact owner | Tasks1,18–19; native Save/full close/second Continue |
| Guides, all53 report fields, separate package, stop | Tasks20–21; remaining hardware and known defects stated |

**Self-review record (planning only):** exact authored paths/interfaces and stage dependencies checked against current source; corrected mother callback polarity, normal-audio runner, all-box decoding, warm-state trap, explicit trade version, map33/34/35 ordering, failed-delivery transaction order and twins slot ownership. No blueprint requirement was intentionally dropped. No product build, new ROM, emulator run or PT14 acceptance is claimed by this document. After owner review confirms this plan, preserve the serial/inline execution method and begin Task1; do not re-review approved design merely to consume another approval.
