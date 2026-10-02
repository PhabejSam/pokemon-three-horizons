# Playtest 14 development handoff — 2026-10-01

Current stage: the owner approved the detailed 21-task plan and serial/inline execution. Tasks 1–2 are implemented with focused host/native checks passing. Task 3 (Route9 Cut / forest presentation) is next. No PT14 release candidate or hardware acceptance is claimed.

Work only in `work/playtest14-celadon`, branch `feature/playtest14-celadon-lavender`, descended from local reviewed Navigator commit `2d85555d74f34f5029c38a3b2db26fb7eb3f99c0`. Original feature and review worktrees contain unrelated untracked/private evidence and remain protected. Native worktree creation returned `Not a git repository` for the task root; the correct nested repository's Git worktree mechanism created this isolated checkout. No remote change occurred.

Canonical Story Bible v1.2 is now stored exactly at `docs/three_horizons/THREE_HORIZONS_STORY_BIBLE.md`. The full owner task was copied privately to `.superpowers/sdd/2026-10-01-playtest14/owner-task.txt`. This is the current bounded scope; do not revive unrelated NURS work or future story chapters.

Private `baseline.json` records original branch/commit/untracked state and protected ROM/package/owner-file hashes. `audit_owner.py` independently validates sectors using the actual baseline ELF and records decoded/private protected state. `owner-baseline/source-copy.eps` is a byte-identical copy of the actual new Lavender battery; originals never become write targets. The cold baseline contains no RAM fixture and opens Tower6F. The report's initial console output had a Windows encoding error after saving its JSON; explicit UTF-8 stdout corrected that audit-tool issue. It was not a game failure or ignored assertion.

Do not run the old PT12 migration script unchanged against this new source: it hardcodes the older source hash. The new final migration gate must use the actual PT13.1 Lavender source and distinct output copies. Native Save must complete in one core invocation before battery export; then launch a new core for cold Continue. Warm serialization only splits same-ROM controller work, never establishes cross-ROM migration.

Portable documented toolchain remains under `C:/Users/phabe/Documents/Codex/pt13-review-tools-20261001` (MSYS2 tools and ARM GNU13.2). The bundled Python is `C:/Users/phabe/.cache/codex-runtimes/codex-primary-runtime/dependencies/python/python.exe`. Serialize build configurations that share generated map headers. Preserve all failed logs and distinguish stale/generated artifacts from authored sources. No dependency installation is needed for this design stage.

Read-only Astra/Ultra audits completed for canon, capacity and maps. Essential conclusions are embedded in the blueprint and verification ledger: appended group76; explicit persistent flag allowlist; recognize a PT14 marker in every migration gate; native reusable TMs; Tower fog currently adds Misty Terrain; mandatory mother's photo needs a missing-Gear path; donor prize/version and reward ordering need adaptation. Route9's entry-edge Cut filter is a source candidate pending actual reproduction. The intermittent hardware Ekans issue remains open.

Independent written-blueprint review identified two wording corrections, now applied: the Ekans hardware failure remains high-severity despite being intermittent/not locally reproducible, and at least one reproduction attempt from an unmodified copy of this supplied battery is mandatory. Additional modified fixtures remain labelled. A fresh cold boot of the same owner source on the exact reviewed Navigator also matches protected payloads; only clock words differ and the packed migration marker remains equal. This is not a new native-save roundtrip or PT14 acceptance.

Implementation must preserve existing maps/IDs/receipts and take an exact allocation/roster manifest through review before product edits. Use source map JSON/layouts/chapter scripts; never patch generated event/header files. Reserve full matrices/ROM builds for planned gates. Do not claim any PT14 system working before its focused and integration evidence exists.

After a passing separate PT14 candidate is packaged, stop for owner RG40XX H/VBA-Next acceptance. No merge, publish, settings changes or next-chapter work.

Documentation verification: the imported canonical source intentionally uses Markdown two-space hard line breaks. Git's broad whitespace check reports those source lines; they are retained to preserve the owner's byte-identical canonical artifact, not silently reformatted. The three newly authored documents are checked separately. Protected ROM/package/save hashes and both prior branch/status snapshots were rechecked unchanged before this documentation checkpoint.

## Approved-blueprint planning checkpoint

The implementation plan fixes 37 appended group76 maps, 38 new trainer identities (157–194), 30 eligible ordinary rematches, 66 explicitly owned flags from the approved 70-bit pool, two 12-slot wild tables and 25 authored stone-evolution rematch slots. The remaining four flags stay undefined/unmodified. It specifies current active TM identities, shop/prize prices, delivery ordering, Rocket/mother/Fuji/Snorlax staging, private test runners and three production-build gates.

Read-only Astra/Ultra map, economy and test-tooling audits supplied the source evidence. Root self-review corrected callback polarity, task references, map registration dependencies, twins shared readiness, offset-test timing, all-box auditing and the inherited warm-state/cold-load distinction. Private audit reports remain under `.superpowers/sdd/2026-10-01-playtest14/`; they are not product code or game-test acceptance. The plan's later whole-branch review remains pending implementation.

The documentation index check initially reported six omitted links: the new plan, four blueprint-stage documents, and the inherited Navigator review plan. This checkpoint adds the links in docs/SUMMARY.md without changing the linked historical/canonical artifacts. Final documentation/preservation results are recorded in PLAYTEST_14_VERIFICATION.md.

Next action after written-plan review: use superpowers:executing-plans, inspect current HEAD/status, begin Task1, and retain local logical commits. No new design request or additional feature is inferred from this planning checkpoint. The unresolved high-severity handheld capture issue remains an investigation requirement; passing local tests must not silently close it.

## Implementation checkpoint — Task 1

PT14 marker is `0xA90E`; every historical migration gate recognizes it. The appended step initializes only the 66 named flags and trainer157–194 once. `chapter14_content.json` and `chapter14_maps.json` now carry approved ownership; maps will be registered in task order. `TH_IsProjectMap` bounds both old group75 and planned group76 without dereferencing maps.

Focused evidence: eight host tests and fifteen native state/layout definitions passed. Behavioral RED and the unchanged-offset baseline were captured first. Existing all-trainer migration expectations now include the newly owned trainer range, then verify earned PT13/PT14 wins survive repeat calls. Full release gates remain pending.

Resume through `.superpowers/sdd/2026-10-01-playtest14-celadon-lavender/progress.md` and the current task brief. The private Windows runner uses `TEST_SRCS` for focused native builds, `CHECK_TOOL_NAMES=patchelf` to bypass only the unavailable Linux launcher, and real normal-audio mGBA with skip-as-failure. The first fresh tool/asset build is complete; use incremental builds. Do not recopy/rebootstrap caches or rerun already completed tasks.

Task2 checkpoint: shared validated unique-item helper, Daisy post-partner gift, later Oak catch-up, initial Daisy direction, and a reproduced native item HOENN→KANTO wording repair. Five host and five native definitions pass. Actual baseline native renderer is retained; candidate visual/cold persistence remains Gate A, new group76 Gate B. Private before inputs document message/preview waits and why a direct cave warp's stale escapeWarp was not treated as a product defect.

Task3 checkpoint: reproduced Route9 connection-entry hide, repaired current-map template ownership, preserved clones/upstream/overlap behavior. Native5 new+3 existing, host4 new+3 existing pass. Native tree metatiles repair north/south clearing and mouth edges without changing any floor/collision/object. Only affected Gear forest-pair art refreshed, all three forest crops verified. GateA owes actual candidate first-entry/Cut/follower/cold and forest frames; static renders are not emulator acceptance.
