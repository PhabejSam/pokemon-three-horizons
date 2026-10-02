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
| PT14 behavioral/visual implementation and focused RED/GREEN checks | Tasks 1–3 focused checks PASS; candidate visuals and remaining tasks/gates pending |
| Full PT14 host/native/layout/offset/documentation matrix | NOT RUN |
| New Emerald/FireRed/LeafGreen compatibility builds | NOT RUN |
| Exact PT14 ROM build/hash/feature/compiled/test revisions | NOT AVAILABLE |
| Actual PT13.1 battery → PT14 native Save → cold second Continue | NOT RUN |
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
