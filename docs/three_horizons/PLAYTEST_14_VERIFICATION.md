# Playtest 14 verification ledger

**2026-10-02: approved plan in serial/inline execution. Tasks 1–2 foundations verified; no PT14 release candidate exists yet.**

The owner requested Celadon → Silph Scope → return to Lavender → mother's Marowak/photo → Fuji/Flute → Route11 Snorlax, with the carry-forward repairs in the chapter blueprint. Full implementation/build/acceptance fields remain pending until their respective gates. Do not use this document as release acceptance.

## Sources and preservation

| Artifact | Verified SHA-256 |
| --- | --- |
| Supplied Story Bible v1.2; repository copy is byte-identical | `53d09fbead5167252cfe42c9e8097bc6e9d838b6a56c44a5944dfb4f55a81605` |
| Actual new RG40XX H/VBA-Next PT13.1 Lavender battery, 131072 bytes | `e94846ce281dc01c245f1fdeabf300b350433fda5a1368924767a3de41536ef2` |
| Protected original RC2 ROM | `c08a31c6ac0c3f5fff5a867b9a98b9ee6d246cf39f16c17d748b431a29a003f2` |
| Protected original RC2 package | `88d06493f2c127f8ffce87f6aeafc9ca10164e9fb7749edbf9bd3166bb02d42b` |
| Protected reviewed Navigator ROM | `537c3ca0185bc34c0e0bc36cdebcae784984cc173ba8ff2fead5f28720537837` |
| Protected reviewed Navigator package | `143636dca51ebc610d709696e9f96960334b033c1920a07479f140758c98c0b7` |

The original hardware battery is read-only source material. Only a verified private copy was supplied to the emulator. Its `.eps` extension describes raw battery storage here, not an emulator state. The actual handheld ROM bytes have not been independently retrieved; the locally tested baseline is the exact hashed RC2 package above.

The owner now reports successful RC2 hardware progression to the Tower barrier. That updates the historical RC2 status, but it is owner-reported evidence and does not certify Navigator or PT14. The intermittent full-party Ekans/Gyarados/black-screen issue remains unresolved.

## Fresh source-battery baseline

- Both ordinary Emerald save slots contain all 14 expected valid sector IDs with correct signature/checksum and coherent counters. Generations 16 and 17 are valid; 17 is newest.
- Checksums use the layout table extracted from the exact RC2 ELF/ROM, not assumed vanilla offsets or lengths.
- Normal cold boot/Continue opens `TH13_PokemonTower_6F`, saved position `(11,14)`, version marker `0xA90C`, badges 1–3 set and 4–8 unset.
- Six party members and eleven occupied PC positions are present. Raw party and all PC-storage bytes match the source after Continue. Checksums for decoded boxed Pokémon are valid. Existing levels and attributes are retained as evidence, not normalized.
- Private audit records player name, every party species/level/move/held item and identity/configuration, complete bag/money, box occupancy/contents, raw storage, flags/variables, research receipts, HM01/HM05, Vs. Seeker, trade/fossil/Rocket/rival/Tower/gift state. Source money is 28,106; raw Dex bit counts are 82 seen / 35 caught (not a claim of a manually inspected Dex screen).
- The source includes Gear, nine photo receipts and received professor reports, with the ship photo absent. The absent ship-departure receipt stays absent; migration must not fabricate it from other progress.
- Emulator: local mGBA libretro `0.11-212-7a12d6d`, scripted ordinary controller input, exact source ROM identified above. The resulting native 240×160 Tower frame was visually inspected.
- No imported emulator state or RAM fixture was used for this cold baseline. No in-game save was performed in this preflight; native Save/close/reopen belongs to the new-candidate gate.
- A second independent cold boot on the exact reviewed Navigator ROM also preserves raw/decoded party, all PC storage, bag, money, flags, location, identity, Dex and story variables. Only three clock-related words differ; the packed version bits remain identical. Both native Tower frames were inspected. This is source-to-reviewed-base compatibility evidence, not PT14 migration or a native-save roundtrip.
- Private evidence: `.superpowers/sdd/2026-10-01-playtest14/owner-baseline/`; original/copy hashes and protected working-tree snapshots: `baseline.json` in its parent. Do not package or commit battery/RAM contents.

## Findings and decisions to carry into implementation

| Priority | Finding | Evidence class / required action |
| --- | --- | --- |
| Architectural | 118 maps occupy group75; signed saved map indices leave only ten safe slots while this chapter needs about37 | Confirmed source/registry constraint. Owner-approved appended group76; plan fixes 37 maps with stable old IDs/layouts and explicit map-family predicates. |
| Architectural | PT13's unused flag range is occupied; all named unused persistent variables are already allocated | Confirmed source audit. Approved70-bit pool; plan assigns66 explicit owners, leaving4 untouched. Compiled ownership/collision tests still required. No save growth. |
| High if implemented incorrectly | Old migration predicates do not recognize a future marker | Confirmed source risk. Update every historical gate and test repeated PT14 Continue before advancing a marker. |
| High | Mandatory photo requires Gear; optional earlier handoffs can be skipped | Confirmed prerequisite gap. Natural free Tower catch-up and explicit photo-success checks required; no fabricated receipt. |
| Medium | Tower's fog activates Misty Terrain | Confirmed source behavior. Make Tower fog atmospheric while preserving explicit move terrain and upstream behavior; cover Terrain Pulse preview. |
| Medium | New Game Corner prize branches would remain unset under Emerald if donor code were copied verbatim | Confirmed source gap. Explicit TH inventory/species/cost/level tables and safe coin delivery transaction. |
| Medium | Donor Lift Key/Scope scripts hide or mark rewards before delivery succeeds | Confirmed donor-order defect. Reorder adapted transactions; full-bag retry tests. |
| Medium | Donor Snorlax hides before battle and considers fleeing a completed encounter | Confirmed donor incompatibility. PT14 resolves only catch/victory; other outcomes retryable. |
| Medium | Route9 entry-edge Cut filtering can hide the current map's tree | Strong source-level cause candidate, not yet emulator-reproduced. Add first-entry reproduction before repair. |
| High | Full-party Ekans causes corrupt Gyarados display and black screen on hardware | Owner-reported intermittent hardware failure; not reproduced locally; root cause unresolved. A documented reproduction attempt from an unmodified copy of the supplied battery is mandatory; prior passing mGBA controls do not resolve it. |
| Low | Forest partial trees and Lavender trio occlusion | Documented visual targets; render exact before/after emulator evidence. |

TMs already are reusable in Three Horizons. Keep that mechanic; design progression-aware access/catalogue stock. The existing active set is 50 TMs plus 8 HMs in a 64-slot machine pocket. Research photos reside in ROM with persisted ownership flags; append the mother's record without changing saved structure sizes.

## Gate status

| Gate | Current status |
| --- | --- |
| Owner source checksum/size/sector inspection | PASS |
| Exact older-RC2 cold Continue baseline and raw party/storage equality | PASS |
| Same owner source cold-loaded on reviewed Navigator; protected payload comparison | PASS; clock-only differences, no PT14 or save-roundtrip claim |
| Canonical v1.2 copy and independent source/canon/capacity/map audits | Completed; written design approved in chat |
| Detailed implementation plan | APPROVED by user; serial/inline execution underway |
| PT14 behavioral/visual implementation and focused RED/GREEN checks | Tasks 1–7 focused checks and Gate A PASS; Tasks8–21 and later gates pending |
| Full PT14 host/native/layout/offset/documentation matrix | NOT RUN |
| New Emerald/FireRed/LeafGreen compatibility builds | NOT RUN |
| Exact PT14 ROM build/hash/feature/compiled/test revisions | Intermediate Gate A b187ec5336 candidate below; final candidate pending |
| Actual PT13.1 battery → PT14 native Save → cold second Continue | PASS on Gate A candidate; Final exact-ROM route still pending |
| PT12/PT13/Navigator/NewGame compatibility | Pending new candidate; earlier results are historical only |
| Exact-ROM full bounded chapter route | NOT RUN |
| PT14 RG40XX H/VBA-Next acceptance | PENDING OWNER HARDWARE TEST after packaging |

Do not inflate the current totals using Navigator's historical 170 host / 222 native / four layout / three compatibility builds. Upstream FireRed/LeafGreen checks use `THREE_HORIZONS=0`; the TH game itself builds on Emerald. This document must be updated with exact failing/passing evidence, limitations and all 53 requested completion fields at release.

## Planning checkpoint validation

The new plan contains21 ordered tasks, Gate A for carry-forward/save safety, Gate B for travel/city/Rocket content, and Final integration/exact-ROM owner migration/package gates. It includes source-specific map/trainer/flag/economy ledgers and explicit requirement traceability. Planning audits and documentation validation are not gameplay tests; no new host/native gameplay suite, build or emulator session was run for this documentation checkpoint.

- Planning-ledger/preservation audit: PASS, 78 checks. Verified21 sequential tasks;37 unique ordered maps with actual donor files;38 trainer identities with36 donor records;66 noncolliding receipt values within the70-bit pool; four untouched reserves;25 distinct rematch trainer/party-slot keys; and two12-slot encounter tables totaling100% each.
- Repository documentation-index validator: PASS after adding six omitted links (five PT14/canon documents and one inherited Navigator plan). The initial failure was retained as a documentation defect and corrected; no assertion was suppressed.
- Whitespace check for changed authored documents: PASS. Canonical Bible bytes remain unchanged.
- Protected artifacts: all six original ROM/package/Bible/battery sizes and SHA-256 values match baseline; the two earlier worktrees retain identical branch, commit and short-status snapshots. The repository canonical copy still matches the supplied Bible exactly.
- Evidence: private `.superpowers/sdd/2026-10-01-playtest14/planning-document-checks.json`. These checks validate the written plan and preservation only. Product, migration and hardware acceptance gates above remain pending.

## Task 1 — state ownership and migration

- Allocated exactly 66 explicit native-unused persistent flags, 38 trainer identities (157–194), and a ROM-side ledger for 37 planned group76 maps. No save structure, old map identity or old layout definition changed. Four reserved flags remain untouched.
- Before repair, the native old-code run failed all three state test definitions: legacy/new-game migration stopped at the old marker, and treating a PT14 save as unknown reset protected progress. The separate compiler-evaluated offset baseline passed.
- After repair: new host allocation suite **4/4**, existing allocation suite **4/4**, and the focused native state/layout set **15/15 test definitions** passed with normal audio and strict skip-as-failure. Five of these definitions cover PT14; parameter combinations are not counted as extra tests. Evidence: private execution `state-host-green-01.log`, `state-existing-host-green-01.log`, `native/state-green-01.*`, `native/state-combined-green-01.*`.
- Native coverage includes old even/odd version markers, current-marker repeated migration, raw SaveBlock1/SaveBlock2/party/all-box invariance against explicitly permitted initialization, negative and positive ship/photo receipts, all 65,536 map-group/index pairs, and actual temporary/daily flag reset APIs.
- Fresh local tools and the focused test ELF built successfully. Windows uses the repository's serial mGBA runner because the Linux Hydra launcher requires unavailable POSIX headers; no tests or assertions were removed. Initial tool/bootstrap failures are retained separately and are not counted as behavioral RED.
- Existing converter metadata, old party-alias deprecation and test-ELF RWX link warnings remain recorded. The new test uses the current party API. Full save-size/layout matrix, upstream builds, owner-battery roundtrip and hardware acceptance remain pending their planned gates.

## Task 2 — Town Map

- Daisy gives the Town Map after the first partner; Oak's initial sendoff points to her. A later supplies-complete Oak interaction offers the same once-only missing-map catch-up. The table still opens its inspectable map. Bag/PC ownership and the shared receipt prevent duplicate gifts; no-room leaves inventory/receipt unchanged and retryable. Only explicitly authored item/receipt pairs are accepted.
- Baseline reproduction used the exact reviewed Navigator ROM and a private battery copy, followed by clearly labelled position/item fixtures. Daisy's generic conversation and absent item were captured. The native renderer already shows Kanto correctly in Pallet, Tower and a cave entered through its real doorway (Route4 entrance marker); Bag Use and registered Select both open, and A/B return to field. No Fly permission was added.
- Confirmed additional presentation defect: native Town Map item introduction said HOENN although the renderer displayed Kanto. The real script-selection regression failed before repair; item use now routes only bounded project maps to the existing Kanto inspection script. Upstream/invalid-map routing retains the original script. No renderer/artwork rewrite.
- Focused results: **5/5 host tests and 5/5 native definitions PASS**, normal audio, strict skip-as-failure. Evidence `town-map-host-red.log`, `native/town-map-routing-red-02.*`, `native/town-map-green-01.*`; baseline frames/inputs in private `town-map-before/` and `town-map-native-before/`.
- Two initial native fixtures exhausted stack space by copying entire save blocks locally; checked heap snapshots repaired the fixtures without weakening assertions. Rerunning with old script selection then produced exactly the intended one failure and four passes. Early controller waits also needed the map's opening message/entrance preview to complete; those are recorded sequencing corrections, not game failures.
- Gate A still owes candidate handoff/full-bag/PC/first-partner/continued-save screenshots and native-save persistence, repeated Bag/registered open-close in old project locations. Gate B adds actual Celadon/group76. These are explicit deferred integration checks, not completed visual acceptance.

## Task 3 — Cut ownership and forest tree edges

- Old Navigator ROM reproduction: direct Route9 arrival retained the uncut tree and blocked movement; normal entry from Cerulean incorrectly set `FLAG_TEMP_12` and allowed crossing. A previous-map stale-flag case reproduced the same problem. Exact ROM/source hashes, inputs and before frames are retained privately under execution `cut-before-02/`.
- Native RED confirmed both the initial hide and failed regrowth. The repaired ownership check exempts only the current bounded project map's ordinary templates from the connecting-map edge filter. Clones and upstream map ownership retain that filter; player-overlap protection and transient regrowth remain. Both shared Cut hooks now use bounded project-map recognition.
- Focused native results: **5 new plus 3 inherited definitions PASS**; host geometry/interaction checks **4 new plus 3 inherited PASS**. Initial upstream fixture setup incorrectly referenced a donor map absent from the Three Horizons ROM; the corrected control uses registered upstream identity with real tree geometry. Full upstream ROM builds remain integration gates. No assertion was suppressed.
- Forest north edges now finish in native trunks/bases; south crowns fit within existing blocked cells. All floor words, collision/elevation bits, objects, receipts and optional Cut reachability remain identical. Three forest Gear crop/source records were verified; only the affected forest-pair image/palette changed. Static reconstruction is inspected, but **candidate emulator before/after and follower/cold-reload acceptance remain Gate A**.
- Presentation ruling: native grass/topper artwork retains the old blocked perimeter, including grass-looking corners. This avoids moving paths or shifting the whole forest grid; Gate A must assess those corners in actual play.

## Task 4 — Flash and Lavender leads

- Qualified Flash delivery now explains Oak's research supplies and Rock Tunnel before HM05, followed by the conscious, compatible, non-Egg field-use instructions. Badge three, ten caught/received species, inventory/full-bag retry, existing receipt and no learned move/free slot requirements remain.
- Lavender rival speech is respectful and conversation-only. The Tower observer names Giovanni's ghost/migration reports and Celadon equipment; both barrier messages connect Scope, Giovanni and Jessie/James. The old endpoint receipt remains, with no developer chapter-completion sentence.
- Jessie/James/Meowth retain IDs6/7/8, approved art/scripts and their existing hide receipt; their new positions are(14,18)/(15,18)/(16,18), facing up. Host checks verify floor/headroom, escape access and follower lifecycle. Existing completed cameo never replays.
- Focused results: **6 new + 9 inherited host tests, 2 new + 3 inherited native definitions PASS**. Native controls verify nine-versus-ten cross-region caught counts, seen-only exclusion, all16 combinations of preserved Flash/rival/cameo/endpoint receipts, and existing Flash eligibility/party invariance. Dialogue lines measure at most201px in the native normal font with a seven-letter rival name.
- Host RED recorded missing handoff speech, old rival/repeat guidance and old trio placement before editing. Old-ROM before frames and exact fixture/input/hash record live privately in `leads-before-04/`; initial wait-helper calls supplied the wrong argument order and are retained as controller errors. Actual candidate first/repeat/full-bag/continued-scene and all-speaker visibility checks remain **Gate A**.
- Repeat observer wording uses Tower2F's otherwise-unused `FLAG_TEMP_1` per visit, or the already-existing endpoint receipt for progressed saves. No new permanent story flag is allocated; leaving before the barrier can cause the longer introduction to be heard again.

### Task 5 — authored rematch evolutions

- Darian's old generator reproduced Growlithe at the approved level32/four-badge threshold; native RED retained privately. Exact keyed generation now applies all25 approved trainer/party-slot rows, with full-width IDs and both level/badge gates. Existing first-party records are protected by an immutable SHA-256 fixture; the unkeyed compatibility API retains its original behavior.
- Eight host tests and fifteen native test definitions passed, including every row below/at/above its threshold, mismatched ID/slot/base, generated final moves/normal ability/IV/item/offset preservation, legacy capacity/readiness/greeting checks, and ten actual trainer battles across all five results with EXP Share on/off. Actual EXP, all six EV fields, Seen and unchanged Caught were asserted after natural victory. Normal audio and strict skip-as-failure were used.
- Eli/Anne's explicit map-local visual alias shares canonical local12 from local13, with bounds, identity and collision checks. It cannot resolve until the canonical eligible map row exists. No trainer ID is stored in readiness bytes; save layouts and permanent defeat flags remain unchanged.
- Dependency gate: the30 new ordinary map rows land with Tasks8/11/12. The future Route8 alias currently uses the approved reserved group76/index0, checked against the map ledger. Both twins' live first/rematch/fewer-than-two dispatch, shared defeat/reward lifecycle and visual `!`/`!!` remain Task8/GateB acceptance. This checkpoint does not claim those future scenes were played.

### Task 6 — atmospheric Tower fog

- Native RED reproduced the automatic Misty Terrain announcement, terrain state and Fairy Terrain Pulse preview; explicit move/ability terrain already worked. The repair bounds only automatic overworld-fog effects to the existing six TH Tower floors and appended group76/index33. All65536 map identities are checked.
- Two host tests and five native definitions pass. Actual battles compare clear/horizontal/diagonal fog at identical fixture/RNG context: Dragon Claw/Terrain Pulse damage, dynamic type, accuracy calculation and stat stages agree. Misty Seed remains held/inactive in Tower fog; the outside-project fog control retains Misty Terrain, Fairy preview and seed activation. Explicit Misty Terrain and Misty Surge remain effective. The current native runtime uses Gen9 fog configuration; the source also guards the Gen4 automatic fog-weather path, without claiming a separate Gen4-config execution.
- Tower map weather is unchanged. Native-resolution field fog/battle screenshots on the identified production candidate remain GateA (new7F at GateB); upstream build/runtime counterparts remain Final. No save data changed.

### Task 7 — intermittent full-party capture investigation

- **The reported RG40XX H/VBA-Next corruption/black screen remains HIGH severity and unresolved.** No corresponding defect reproduced in these local mGBA runs; no speculative production capture change was made. Gate A and Final must repeat the candidate route, and passing mGBA results do not establish handheld acceptance.
- Required natural attempt completed from an untouched private copy of the actual owner battery: 131072 bytes, SHA-256 `e94846ce281dc01c245f1fdeabf300b350433fda5a1368924767a3de41536ef2`. The original was rehashed unchanged. Reviewed Navigator ROM SHA-256 `537c3ca0185bc34c0e0bc36cdebcae784984cc173ba8ff2fead5f28720537837`; mGBA libretro DLL SHA-256 `674089194b419b02f0c2eeedb263170e116e2bab85e901323f3dc53bb660c3e7`. This is an identified local baseline, not proof of the exact ROM/core installed on the handheld.
- Cold Continue in Tower6F, then ordinary travel down the Tower, back through Rock Tunnel, Route9, Cerulean, the Underground Path and Vermilion to Route11. Two previously undefeated Tower trainers were fought naturally; Golem reached level39. The owner's existing shiny Gyarados led with the follower enabled. No RAM fixture or imported emulator state altered this required journey. Input timing, all intermediate frames and natural battle/repel actions are retained in private execution `capture-natural-before/actions.jsonl`.
- A naturally encountered male level12 Ekans was caught using an existing Great Ball. Ekans was already Seen but not Caught, so its first registration/page was displayed. The actual naming screen accepted the maximum12-character nickname `Aaaaaaaaaaaa`; Yes opened the native full-party selector, and choosing the first slot sent Gyarados to box1/slot12. Dex, nickname, caught sprite, party icons and restored field were visually inspected. Native Save and a newly created core's cold Continue preserved all600 party bytes, all34144 PC bytes, bag and money exactly against the post-save state.
- All five retained boxed party records and every pre-existing PC record were unchanged by delivery. The sole retained-party cache change was Annihilape's Attack149→150: the capture raised Attack EV35→36, and the ordinary end-of-battle stat recalculation crossed a rounding threshold (level49, base115, IV31, Adamant). Its80-byte identity payload was identical. PP restoration on PC delivery and player-OT assignment to the caught Pokémon are intentional native behavior, not corruption.
- Four separately labelled modified fixtures passed real encounter/first-Dex/nickname/native selector/save/cold-Continue checks: Drowzee replacing middle slot with follower off; Ekans replacing last slot with follower on; Spearow cancel-to-PC; and Ekans replacing first slot immediately after an actual Rare Candy-triggered Magikarp19→20→Gyarados evolution. Evolution itself, caught sprites, selector icons and cold field frames were inspected. Each retained all unaffected boxed records and all pre-existing PC records, then exact full party/storage bytes over cold reload. These fixtures added a Master Ball/cleared target Caught status and used explicit map/party preparation; they are not the natural owner-source reproduction.
- Focused native result: **15 distinct test definitions PASS**, normal audio and strict skip-as-failure:2 PT14 capture definitions plus13 inherited capture/configuration/lifecycle/Dex/naming definitions. The PT14 selector definition exercises nine cases: first/middle/last replacement, B cancel, prompt No, Drowzee/control species, nonidentity party order and a separately labelled forced postcapture PC-full fault. Another definition tests natural full-party/full-PC throw rejection and the last-vacancy control. Existing first-Dex probes now include Ekans and Drowzee with rapid/slow inputs. Parameter cases and reruns are not counted as extra definitions.
- Native coverage runs the real give-caught-mon opcode, controller gating, party-menu input/fade/return and identity/storage assertions. Recorded wild-battle tests skip the Dex/nickname UI and were not substituted for this lifecycle. Initial new fixture allocation failures exhausted the graphics heap; using native initialized storage corrected the harness without weakening assertions. Those setup failures are not behavioral RED. The private controller's duplicate static-symbol lookup was also corrected before the modified-fixture run, with failed logs retained.
- Evidence: private execution `native/capture-investigation-04.*`, `native/capture-related-*.{json,log}`, `capture-natural-before/`, and the four `capture-fixture-*/` directories. Save/RAM payloads remain private. Current results establish baseline controls and test coverage only; no PT14 release-ROM or hardware closure claim is made.


## Gate A — carry-forward systems and owner-save safety

**Intermediate gate PASS**, compiled/feature revision `b187ec5336c095b9741afdaeeaa1d1f79b05305f`. Private candidate `gate-a-candidate/pokemon-three-horizons.gba`, SHA-256 `f4bc18faa19714d1abb2c53a721548e8d87882521089cb0899b2b9ae82650fca`. This is a separately preserved integration build, not the final release or the owner's existing ROM. Production build succeeded; ROM footprint27,749,632 bytes. Eight compiler diagnostics and two RWX linker diagnostics have inherited source/configuration causes relative to2d85555; no new warning site found. This comparison audited unchanged source sites/linker settings, without rebuilding the baseline.

- Normal-audio native layout check: **4 save definitions + 1 PT14 offset definition PASS**, strict skip-as-failure. This does not add reruns to earlier totals. Full host/native/upstream matrix remains Final.
- Candidate Town Map: Daisy's post-partner gift, pre-partner restriction, Oak continued-save catch-up, repeated ownership, full-pocket retry, PC-owned exclusion and native-save persistence passed. Native Kanto map repeatedly opened/closed from Bag/registered Select in Pallet/Tower and after ordinary cave entry, with correct entrance labels.
- Candidate Cut/forest: first connection entry is blocked by the uncut Route9 tree, normal Cut allows crossing, leaving/re-entering regrows it, and cold Continue still blocks. A stale previous-map TEMP12 does not hide it. Follower positions were checked before/after crossing and cold load; the fixture-free owner journey also crossed both Route9 ledges and the tree. Same-lighting old/candidate forest north/south/mouth frames and the affected Gear photo were visually inspected; collision footprint remains unchanged.
- Candidate story: Flash introduction precedes HM delivery, repeat does not duplicate, full TM pocket leaves delivery retryable, then free-slot retry succeeds. First/repeat rival and observer text, all three unobscured Lavender speakers, and first/repeat post-ghost Scope/Giovanni/Celadon guidance were captured/inspected. The owner's completed cameo receipt stayed set and all three actors remained absent. First barrier fixture sets the existing endpoint receipt and restores follower/control after pushback.
- Candidate Tower fog remains visible in the field. Its actual ghost battle had no automatic terrain/timer state. Explicit-terrain/outside-map behavioral controls remain the Task6 native results; no upstream runtime claim is substituted.
- Research Gear labelled all-records fixture passed all11 log records,10 photo fronts/details/notes, three contacts, both list-wrap directions, home selection and field return. Menu use changed none of the protected payload, and native Save/new-core cold Continue retained it. All10 photo fronts and representative other pages were visually inspected. No new PT14 mother record exists yet; that belongs to Task14.
- Exact owner source `e94846ce…36ef2` cold-loaded into Tower6F without a fixture. Before movement, all600 party bytes, all34144 PC bytes, decoded bag/money/coins, old permanent flags, Dex, inventory/registration, identities and unrelated story variables matched the identified old-ROM cold baseline. All66 new receipts and trainer157–194 defeat bits were clear. Native Save, core destruction, fresh-core boot and second Continue preserved protected data and marker `(version & 0xFFFE) == 0xA90E`.
- Normalized differences are documented narrowly: save encryption key changes, native time/playtime/warp materialization, and the daily lottery pair. The source is day4; both independent first Continues advance to day5. The unchanged lottery routine uses RTC-seeded RNG, so those first-load values differ. The pair stays exactly64612/21981 across PT14 Save→second Continue. Decoded coins are0 in all four snapshots. No general story-variable exclusion was used.
- Required **candidate natural capture attempt PASS**: untouched owner-copy Continue→owned Escape Rope→Lavender→Rock Tunnel→Route9/Cerulean→Underground→Vermilion→Route11. Ordinary repel prompts were answered; no RAM fixture altered this journey. Male level12 Ekans was caught on the second existing Great Ball, first Caught registration displayed, maximum12-character `Aaaaaaaaaaaa` entered, first party slot chosen, Gyarados delivered to box1/slot12, and Ekans follower restored. All unaffected boxed party identities and pre-existing PC records remained exact. Native Save→fresh cold Continue preserved full party/PC/bag/money bytes. This run had the owner's Gyarados lead/follower on and no recent evolution.
- **Hardware capture report remains HIGH/unresolved.** Four modified capture/evolution fixtures from Task7 are explicitly old-ROM controls, not claimed as candidate fixtures. Candidate native coverage and this ordinary owner-copy attempt passed; the exact Final candidate route and owner RG40XX H/VBA-Next acceptance are still required.

Evidence is private under execution `gate-a-{candidate,owner,town,oak,map,forest-day,cut,leads,flash-02,fog,gear,natural-capture}/`, `native/gate-a-save-*.{json,log}`, build log and `gate-a-results.json`. Every scene records ROM/core identity and labels modifications. Harness mistakes (wrong Flash pocket, unknown first-barrier fixture name, expected Route11 index typo) were preserved, corrected and rechecked; unknown fixture kinds now fail explicitly. They are not product defects and no product assertion was suppressed. Gate A closes the earlier Task2–4/6 visual deferrals; Task5 new-map doubles/rematch scenes remain Tasks8/11/12 and Gate B.

## Windows native-runner runtime repair — 2026-10-02

The direct diagnostic launch outside the private wrapper failed at Windows loader startup: `libwinpthread-1.dll` was unavailable. That launch ran no tests and is not counted as a pass. Previous wrapper runs supplied MSYS2 on PATH and produced actual native result records; their PASS/FAIL results remain valid.

The runner also imports `libepoxy-0.dll`. Both x86-64 libraries were copied beside the isolated runner from the existing project MSYS2 toolchain after validating their installed package SHA-256 manifests and recorded SHA-256/PGP package validation. No DLL download, global PATH change, runner executable replacement, owner ROM write or owner-save write occurred. The new repeatable setup command is documented in `tools/mgba/README.md`; it rejects architecture mismatches and different existing DLLs.

- Runner SHA-256 unchanged: `84c7f1babecf563722224d462a889f7f6d34ab11bcfa6b6160eef569b5f2608a`.
- libwinpthread package: `mingw-w64-x86_64-libwinpthread-14.0.0.r426.g4564ee4b5-1`; DLL SHA-256 `72bf8802de3a99d28f0bc2db9a11f281a9f9f3fa83dab2bc67e69fac3bd3d9c0`.
- libepoxy package: `mingw-w64-x86_64-libepoxy-1.5.10-7`; DLL SHA-256 `8e7d48294d79eb5b1f44cd7c2a637239d8ddcdabaedea12bf9fb7ca919d1a37a`.
- Rerun with only Windows System32 on the runner's PATH, normal audio, skip-as-failure: SaveBlock1/2/3, PokemonStorage and PT14 field-offset checks **5 PASS**; travel maps, calls, twins dispatch and readiness **4 PASS**.
- The initial encounter/capture rerun **executed and failed** the slot2 expected-Growlithe assertion; it was not blocked by a DLL. The separate fixture correction and subsequent passing rerun are recorded below. The diagnostic logging build was not a release candidate.
- Evidence: private `windows-runtime-before.json`, `windows-runtime-installed.json` and native `runtime-saveblocks-01`, `runtime-storage-01`, `runtime-layout-01`, `travel-diagnostic-01` logs/reports.

## Task 8 — Route 8, Underground Path and Route 7

Seven appended group76 maps now connect reciprocally from Lavender through the east-west Underground Path to Route7. Their layouts retain exact donor block/border bytes and old map/layout IDs remain unchanged. The two Saffron gatehouses block the complete passage without Tea/native-story state. Twelve complete donor first parties, eleven owned hidden pickups, two exact 12-slot land tables and twelve ordinary rematch identities are authored. The twins use one canonical trainer/party/readiness identity from either object; first battles and rematches both retain the two-usable-Pokemon double-battle guard.

Behavioral RED reproduced the group75-only call guard, rematch-double encoding, and mapjson's rejection of the new prefix. The bounded project-map helper, TH-only double macro correction and compiler/manifest integration repair those paths. Upstream double encoding is preserved; mapjson host checks cover project/Emerald/FireRed selection, while complete upstream builds remain the Final gate.

**Focused result: 27 host checks and 15 native definitions PASS**, normal audio, skip-as-failure, with only Windows System32 on the runner PATH. Native definitions comprise travel5, keyed rematches5, full registered-rematch1 and inherited calls4. The travel capture definition executes all24 authored slot cases through real generation and capture, checking species, level, legal data and retained caught identity. Recorded battle tests do not substitute for first-Dex/nickname UI or hardware acceptance.

The initial capture failures exposed fixture assumptions, not evidence for a production encounter repair. GIVEN uses recorded parties while field generation reads live parties; the fixture now initializes the live lead and captures the actual generated opponent. It explicitly uses an existing move instead of requesting an implicit fifth Celebrate. Finally, the previous parameter's `VBlankCB_Battle` remained installed after the next GIVEN cleared RECORDED, advancing RNG despite the separate main VBlank test guard. Temporarily suspending/restoring that callback only around field generation makes the seeded fixture deterministic. All species/stat/capture assertions remain; production RNG and `wild_encounter.c` are unchanged. Temporary instrumentation was removed before the passing build. Earlier failed logs remain preserved.

Evidence: private `travel-build-07.log`, `task8-verification-01.log`, and `native/travel-task-done-*-20261002-052033.{json,log}`. Test build succeeded with the same two inherited RWX linker diagnostics. The diagnostic-format ELF was only an investigation artifact, never the passing test/release artifact.

Pending by plan: Task9 registers both Route7/Celadon connection edges and the off-map Cut clone. GateB must still demonstrate candidate travel in both directions, follower/bicycle behavior, trainer approach, Underground entrances and native Town Map markers. No new production ROM or hardware acceptance is claimed here.
