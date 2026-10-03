# Playtest 14.1 Stabilization Implementation Plan

> **For agentic workers:** Use superpowers:executing-plans, serial/inline with one final independent review. Preserve private evidence. Checkboxes record actual completion.

**Goal:** Ship a separate PT14.1 hardware candidate with adaptive Hyper Beam, global recharge-on-KO skip, and two bounded dialogue repairs.
**Architecture:** Keep Hyper Beam's EFFECT_HIT and self MOVE_EFFECT_RECHARGE. Add a THREE_HORIZONS-only case to SetDynamicMoveCategory using GetCategoryBasedOnStats. Select GEN_1 for B_SKIP_RECHARGE only in Three Horizons. Reuse Giovanni's defeated flag and the existing Scope receipt for city reactions.
**Tech stack:** existing C/event assembly/native GBA tests/Python; documented ARM GNU13.2/MSYS2/mGBA toolchain.
**Spec:** the user's complete approved PT14.1 request, preserved verbatim in this plan's private `owner-request.txt`; Story Bible remains v1.2. This is the concise plan requested before implementation, not a new chapter design.

## Global constraints

- Baseline feature abdec6f2508bbf2d4f1c104d863e5908281f6f6e; documentation HEAD6511feabc64023c88d66f4d46c559341c4964f95. Preserve PT14 ROM7e9e18bc…a77a7, ZIP8245d4ec…f5edf and original owner battery e94846ce…16ef2.
- Work only in new sibling `work/playtest14-1-stabilization`, branch `feature/playtest14-1-stabilization`. No merge/push, baseline writes, future chapter or speculative capture repair.
- Hyper Beam stays Normal/150/90/5/selected target, existing animation/sound/contest/additional effect. Attack strictly greater selects Physical; equal selects Special. Existing helper compares battle stats after current stages; later damage modifiers retain their usual engine semantics.
- Every standard self recharge move uses the existing KO check; charging moves are separate. THREE_HORIZONS=0 retains current upstream mechanics.
- No new fields/variables/flags, no Story Bible change, no Gyarados stat/type changes. Audit66/70 pool rather than expand it.
- Test focused first; run full gates only after focused green. Preserve failures; never suppress assertions/skips. Hardware capture HIGH/unresolved; stop for hardware after package.

## Review focus

1. Shared category scratch state must reset between moves/AI trials; test Hyper Beam followed by ordinary Special/Physical moves and existing Photon Geyser controls.
2. Current stages, ties and target defenses must affect real damage, not only preview. Test both orientations/reductions and AI damage simulation.
3. Substitute removal is not a KO; miss/Protect/immunity must keep engine behavior. Test actual subsequent turn/switch and charging controls.
4. Giovanni defeat with a still-undelivered Scope must not falsely claim ownership; exercise before/victory/receipt dialogue states without mutating flags.
5. Continued/migrated owner data and normal native Save/cold Continue must stay exact except documented normal bookkeeping; old archive/calls and newly earned chapter progress must survive.

## Task 1: Reproduce and preserve baseline
**Files:** private baseline/toolchain/evidence only. Consumes immutable PT14 revision/package; produces checksum/state baseline and clean production output.
- [x] Verify protected originals/worktrees, record current branch/revisions, and create copied-source test workspace.
- [x] Affected host baseline checks passed across the documented48/11 runs; unchanged production rebuilt successfully and exactly matched PT14 ROM SHA7e9e18bcb30026a47c9e46e187f8a1ba906e431682eb704b48c2ed8fd67a77a7. Full host gate deferred to Task4.
- [x] Record inspected category/recharge/AI interfaces and plan risk review. Shared setter used by resolution and AI damage; additional AI category heuristics require bounded battler-aware handling; no saved state change.

## Task 2: Adaptive Hyper Beam and recharge rule
**Files:** `test/three_horizons_playtest141_battle.c`, `src/battle_util.c`, `include/config/battle.h`, `src/data/moves_info.h`, bounded `src/battle_ai_util.c` if established hit-count scoring supports it.
**Interfaces:** retain `void SetDynamicMoveCategory(enum BattlerId, enum BattlerId, enum Move)`, `enum DamageCategory GetCategoryBasedOnStats(enum BattlerId)` and existing `HandleSetEffectRecharge`.
- [x] Write native tests before code: stage matrix (100/100 tie Special;150/100 Physical;100/150 Special; boost/reduce either stat), real Gyarados/Alakazam, real Defense/Sp.Defense damage, properties/animation/recharge; shared-state reset and AI damage.
- [x] Write parameterized real battle tests for Hyper Beam/Giga Impact/Blast Burn/Hydro Cannon/Frenzy Plant and other standard recharge records: KO permits next attack/switch; survival requires exactly one recharge. Include miss, Protect, immunity, surviving Substitute, Substitute break, and charge-then-attack controls.
- [x] Build focused native ELF and run with normal audio/strict skip-is-fail. Expected RED: missing adaptive category and KO skip; controls already green are recorded as existing behavior.
- [x] Add the TH-only move-ID condition in the shared setter, retain move effect; scope B_SKIP_RECHARGE; fit a two-line description explaining adaptive offense and KO exception. No duplicated stat arithmetic.
- [x] Audit AI: common damage path already invokes setter. Test real simulated damage and category reset. If existing `noOfHitsToKo` safely represents predicted one-hit KO, remove only recharge drawback there for TH; otherwise retain conservative scoring and document. Do not invent a prediction engine.
- [x] Run focused green including Photon Geyser/recharge/charging controls and upstream conditional assertions. Commit `feat: add adaptive Hyper Beam and KO recharge rule for Three Horizons`.

## Task 3: Bounded Living City corrections
**Files:** `chapter13_lavender.inc`, `chapter14_celadon.inc`, `tools/three_horizons/tests/test_playtest141_dialogue.py`; native dialogue/compiled checks if needed.
**Interfaces:** only existing TRAINER_TH14_GIOVANNI defeat and FLAG_TH14_SILPH_SCOPE. No position changes or new receipt.
- [x] Exercise real script branches before/victory-before-pickup/Scope receipt; fail before adding reactions. Assert no state mutation, original early messages, bounded relevant actors only.
- [x] Worker says west Route8 and Underground Path lead to Celadon; south remains under maintenance. Update scientist (victory investigation vs owned Scope), street woman and two street Rockets with short natural aftermath lines. No future-story revelation.
- [x] Run focused host/native dialogue and state checks; commit `fix: update Lavender directions and Celadon Rocket reactions`.

## Task 4: Focused smoke then full integration
**Files:** existing test/build tools; private outputs. Consumes Tasks2–3 committed source.
- [ ] Run a focused production build: copied owner cold Continue/Gear/archive/calls, native Save/full close/reload and targeted battle/menu/description/dialogue evidence. Clearly label adversarial fixtures, never alter original owner file.
- [ ] Once focused gates pass, full TH host suite, full TH native test selection plus all new battle/recharge/charging controls, save-layout/offset checks and documentation validation. Count definitions and parameter cases separately; zero skipped selected tests.
- [ ] Fresh Emerald/FireRed/LeafGreen compatibility builds and exact TH production build; verify expected upstream category/recharge config remains unchanged. Record warnings, revisions and hashes. No source exclusions or repeated unchanged builds.

## Task 5: Exact new-ROM acceptance and final review
**Files:** private exact-ROM evidence; verification/development records.
- [ ] Freeze passing ROM/ELF/map identity; use that ROM for owner initial Continue, complete protected party/boxes/gear/photos/calls/progression audit, native Save, close and second Continue. Also continue a copied earned PT14 Celadon/Tower checkpoint to prove new progress retention.
- [ ] Controller evidence: Physical/Special Hyper Beam, KO/no recharge, survival/recharge, Giga Impact KO, charging control, battle menu/animation/description, worker and city states; native tests own exhaustive edges. Verify no new persistent bits and unchanged canon/Gyarados.
- [ ] One fresh independent whole-patch review; address material defects with RED/GREEN and affected gates, no repeated review loop. Report all limitations; hardware capture still unresolved.

## Task 6: Documentation, separate package, stop
**Files:** PT14 walkthrough/hardware/verification/development docs with explicit14.1 addendum; battle rules document; new versioned output directory and ZIP only.
- [ ] Document exact implementation, AI policy,35 requested report fields, test totals, save/capacity and current limitations. Add four natural Hyper Beam handheld checks without an exhaustive engine checklist.
- [ ] Package `pokemon-three-horizons-playtest-14-1-celadon-silph-scope.gba`, SHA256, guides/migration instructions and sanitized evidence. Whitelist/hash archive; exclude saves/states/RAM/private inventories. Re-extract and cold Continue/Gear smoke.
- [ ] Rehash all protected PT14 artifacts, canon and original battery; preserve other worktree state. Logical local documentation commit. Stop for owner RG40XX H/VBA-Next acceptance; no integration or PT15.

**Plan self-review:** user sections1–13/22 covered by Task2;14–18 by Tasks3–5;19–21 by Tasks1/4/5;23–30 by Tasks4–6. Shared setter avoids animation/recharge effect replacement. Existing AI hit-count estimate may remain conservative; safety cannot be traded for optimistic prediction. All new behavior is compile-time scoped and saves unchanged. No demonstrated architecture conflict in inspection.

