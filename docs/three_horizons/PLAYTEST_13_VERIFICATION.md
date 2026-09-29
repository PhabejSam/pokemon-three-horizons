# Playtest 13 verification — implementation in progress

No release or hardware acceptance is claimed by this working record.

## Baseline

- P12 feature: `f6dc5b36c0ed9ea71b10a93a69af2e0f68d4bcd0`.
- P12 compiled/test: `d8da3c365b74a0bd87099fb4e983e32f8d0e0c03`.
- P12 ROM SHA-256: `2191ebf684fb829cc86d4bc8638a11ee5aa535a9c88dbd47f8b3e96ce38f312d`.
- P13 implementation starts from `f49d3bd17a604d4593ad589b330018f5e911ecbc`.
- Personal battery-save backup: `ThreeHorizons_PT12_RG40XXH_FINAL_BACKUP.sav`, 131088 bytes, SHA-256 `2bac4d587f965215c6a008d06825bfd46ca8ec5a77a247d7b53211111ecf8c8c`. Original preserved; testing uses a copy. Its actual state marker is Playtest 11 (0xA907), in Cerulean, despite its filename. The actual post-Surge P12 save has been requested; personal P12 migration acceptance is pending.
- Existing native layout expectations: SaveBlock1 15568, SaveBlock2 3884, SaveBlock3 4, PokemonStorage 34144 bytes. All four native size checks passed at the Task 1 gate; they will run again at final integration.
- P12 map index snapshot: `tools/three_horizons/tests/playtest12-map-indices.json`.

## State ownership audit

The exact assignments below are existing unused Emerald event slots. They are not an extension of P12's range into the active engine flags at 0x2BC. Repository-wide alias search and all numeric references were examined: numeric matches represent species IDs, graphics/animation values, weights, prices, test frame limits, structure offsets and tool metadata; none consumes these slots as an Emerald event flag. Native FRLG flags use their separate game configuration; all TH migration code remains compile-gated. No daily, trainer, special or temporary flags are allocated.

| Receipt | Flag |
|---|---|
| `FLAG_TH13_BILL_IN_MACHINE` | `0x493` |
| `FLAG_TH13_SHIP_DEPARTED` | `0x494` |
| `FLAG_TH13_ACRO` | `0x495` |
| `FLAG_TH13_VS_SEEKER` | `0x496` |
| `FLAG_TH13_VS_SEEKER_ACTIVE` | `0x497` |
| `FLAG_TH13_FLASH` | `0x498` |
| `FLAG_TH13_GEAR` | `0x499` |
| `FLAG_TH13_SKARMORY_TRADE` | `0x49A` |
| `FLAG_TH13_ENDPOINT` | `0x49B` |
| `FLAG_TH13_LAVENDER_RIVAL` | `0x49C` |
| `FLAG_TH13_ROCKET_CAMEO` | `0x49D` |
| `FLAG_TH13_FOREST_RESEARCH_REWARD` | `0x49E` |
| `FLAG_TH13_OBS_HOOTHOOT` | `0x49F` |
| `FLAG_TH13_OBS_FOREST_TREECKO` | `0x4A0` |
| `FLAG_TH13_OBS_FOREST_SHROOMISH` | `0x4A1` |
| `FLAG_TH13_OBS_MT_MOON` | `0x4A2` |
| `FLAG_TH13_OBS_SHIP` | `0x4A3` |
| `FLAG_TH13_OBS_FOREST_PAIR` | `0x4A4` |
| `FLAG_TH13_OBS_CAVE` | `0x4A5` |
| `FLAG_TH13_OBS_ROUTE9` | `0x4A6` |
| `FLAG_TH13_OBS_ROCK_TUNNEL` | `0x4A7` |
| `FLAG_TH13_OBS_LAVENDER` | `0x4A8` |
| `FLAG_TH13_OBS_FOREST_LEGACY` | `0x4A9` |
| `FLAG_TH13_PHOTO_HOOTHOOT` | `0x4AA` |
| `FLAG_TH13_PHOTO_FOREST_TREECKO` | `0x4AB` |
| `FLAG_TH13_PHOTO_FOREST_SHROOMISH` | `0x4AC` |
| `FLAG_TH13_PHOTO_MT_MOON` | `0x4AD` |
| `FLAG_TH13_PHOTO_SHIP` | `0x4AE` |
| `FLAG_TH13_PHOTO_FOREST_PAIR` | `0x4AF` |
| `FLAG_TH13_PHOTO_CAVE` | `0x4B0` |
| `FLAG_TH13_PHOTO_ROUTE9` | `0x4B1` |
| `FLAG_TH13_PHOTO_ROCK_TUNNEL` | `0x4B2` |
| `FLAG_TH13_PHOTO_LAVENDER` | `0x4B3` |
| `FLAG_TH13_SCENE_HOOTHOOT` | `0x4B4` |
| `FLAG_TH13_SCENE_FOREST_TREECKO` | `0x4B5` |
| `FLAG_TH13_SCENE_FOREST_SHROOMISH` | `0x4B6` |
| `FLAG_TH13_SCENE_MT_MOON` | `0x4B7` |
| `FLAG_TH13_SCENE_SHIP` | `0x4B8` |
| `FLAG_TH13_SCENE_FOREST_PAIR` | `0x4B9` |
| `FLAG_TH13_SCENE_CAVE` | `0x4BA` |
| `FLAG_TH13_SCENE_ROUTE9` | `0x4BB` |
| `FLAG_TH13_SCENE_ROCK_TUNNEL` | `0x4BC` |
| `FLAG_TH13_SCENE_LAVENDER` | `0x4BD` |
| `FLAG_TH13_CALL_ACTIVATION_PENDING` | `0x4BE` |
| `FLAG_TH13_CALL_ACTIVATION_DELIVERED` | `0x4BF` |
| `FLAG_TH13_CALL_ROUTE10_PENDING` | `0x4C0` |
| `FLAG_TH13_CALL_ROUTE10_DELIVERED` | `0x4C1` |
| `FLAG_TH13_CALL_LAVENDER_PENDING` | `0x4C2` |
| `FLAG_TH13_CALL_LAVENDER_DELIVERED` | `0x4C3` |
| `FLAG_TH13_PICKUP_0` | `0x4C4` |
| `FLAG_TH13_PICKUP_1` | `0x4C5` |
| `FLAG_TH13_PICKUP_2` | `0x4C6` |
| `FLAG_TH13_PICKUP_3` | `0x4C7` |
| `FLAG_TH13_PICKUP_4` | `0x4C8` |
| `FLAG_TH13_PICKUP_5` | `0x4C9` |
| `FLAG_TH13_PICKUP_6` | `0x4CA` |
| `FLAG_TH13_PICKUP_7` | `0x4CB` |
| `FLAG_TH13_PICKUP_8` | `0x4CC` |
| `FLAG_TH13_PICKUP_9` | `0x4CD` |
| `FLAG_TH13_PICKUP_10` | `0x4CE` |
| `FLAG_TH13_PICKUP_11` | `0x4CF` |
| `FLAG_TH13_PICKUP_12` | `0x4D0` |
| `FLAG_TH13_PICKUP_13` | `0x4D1` |
| `FLAG_TH13_PICKUP_14` | `0x4D2` |
| `FLAG_TH13_PICKUP_15` | `0x4D3` |
| `FLAG_TH13_PICKUP_16` | `0x4D4` |
| `FLAG_TH13_PICKUP_17` | `0x4D5` |
| `FLAG_TH13_PICKUP_18` | `0x4D6` |
| `FLAG_TH13_PICKUP_19` | `0x4D7` |
| `FLAG_TH13_PICKUP_20` | `0x4D8` |
| `FLAG_TH13_PICKUP_21` | `0x4D9` |
| `FLAG_TH13_PICKUP_22` | `0x4DA` |
| `FLAG_TH13_PICKUP_23` | `0x4DB` |
| `FLAG_TH13_PICKUP_24` | `0x4DC` |
| `FLAG_TH13_PICKUP_25` | `0x4DD` |
| `FLAG_TH13_PICKUP_26` | `0x4DE` |
| `FLAG_TH13_PICKUP_27` | `0x4DF` |
| `FLAG_TH13_PICKUP_28` | `0x4E0` |
| `FLAG_TH13_PICKUP_29` | `0x4E1` |
| `FLAG_TH13_PICKUP_30` | `0x4E2` |
| `FLAG_TH13_PICKUP_31` | `0x4E3` |
| `FLAG_TH13_PICKUP_32` | `0x4E4` |
| `FLAG_TH13_PICKUP_33` | `0x4E5` |
| `FLAG_TH13_PICKUP_34` | `0x4E6` |
| `FLAG_TH13_PICKUP_35` | `0x4E7` |
| `FLAG_TH13_PICKUP_36` | `0x4E8` |
| `FLAG_TH13_PICKUP_37` | `0x4E9` |
| `FLAG_TH13_PICKUP_38` | `0x4EA` |
| `FLAG_TH13_PICKUP_39` | `0x4EB` |

## Task evidence

- Allocation RED: new ownership test failed with 0 P13 receipts; unchanged P12 indices and previous allocation checks passed.
- Native initial RED checkpoint: `7b80ad6bc87546d1b79f43587f314f29d4e0ba50`; two expected clock-version failures observed.
- Expanded negative controls: all four state regressions failed against exact baseline `f49d3bd17a604d4593ad589b330018f5e911ecbc` in run 36501183839.
- Task 1 GREEN: feature `c862c43e2053c634735f3273fc5a52ab69fe00aa`; compiled/test `2bad584adb4570df243a6c20dff6f784c9a021ad`; [CI evidence](https://github.com/PhabejSam/pokemon-three-horizons/actions/runs/36501183839). Four host ownership/index contracts, four new native state tests (nine starter cases and six versions), four legacy checks and four save-layout checks passed. Two unrelated native discovery ASSUME exclusions in `change_type_on_item.c` are retained in the log; no selected test failed.
- Task 18 baseline: exact P12 ROM/ELF, copied synthetic post-Surge save, 18 mGBA cases (Viridian/Route 2/Vermilion × compatible/incompatible/off follower × interaction/party-menu Cut). The correct local tree ID survives animation and is removed; Viridian and Route 2 respawn on camera refresh with flag ID 0, whereas Vermilion's native temporary hide flag prevents respawn. A one-tile step reproduces the player overlapping the reappeared tree. Cycling repeats the same defect. Correcting the shared template owner and current-version Continue removes both cases.
- Documentation-index failure was corrected by adding the approved plan and Bible to `docs/SUMMARY.md`.

## Integration and acceptance

Pending: full project regression, final save-layout recheck, three upstream game builds, personal-save migration/Continue, mGBA visual acceptance, release packaging and user RG40XX H acceptance. A focused run does not substitute for these gates.

## Task 18 Cut verification checkpoint

- Feature: `78b476ba8095a4845f42ba0285dcd31acce23b2e`; compiled/test: `37ac9acb99e5a928760dcc62e566bfbce3eff709`.
- ROM SHA-256: `4ae63001d15ce23140b4e16878575b542afe415211878ba4e5eb56439fda7063` (development verification candidate, not the final Playtest 13 release).
- [CI run 36503585012](https://github.com/PhabejSam/pokemon-three-horizons/actions/runs/36503585012): three native regressions fail against the preceding object lifecycle and pass with the repair; three existing field-move tests and three host ownership/capacity checks pass. Two unrelated discovery ASSUME exclusions remain visible.
- Exact-ROM mGBA core evidence: 36 cases, three locations × two Cut entry methods × three follower modes × walking/cycling. Every trace observes the original target removed, and no target respawns on camera refresh. Six additional Gyarados walking/cycling cases traverse the opened tile successfully.
- All three locations pass native party-menu lead switching after Cut, genuine door exit/re-entry regrowth and repeat Cut, and a complete in-game Save followed by cold Continue on the cleared tile. A P12 battery save on Vermilion's cleared tree tile also migrates without an overlapping tree.
- Reproduction inputs use a copied post-Surge fixture and task-owned QA party/position setup. No emulator state is transferred between ROM revisions; battery Continue creates each revision's base state. This is focused emulator evidence, not whole-chapter desktop or RG40XX H acceptance.
- Local reproducible captures, traces and harness: `outputs/playtest-13-development/task18-cut-evidence.zip` in the task workspace. CI artifact `11007126589` contains the exact candidate ROM/ELF and native logs.
- Upstream code paths remain guarded out of this TH-only repair; complete Emerald/FireRed/LeafGreen compilation is reserved for the approved integration gate.

## Task 22 trainer RUN checkpoint

- Feature `a2e234d015bcd291b3c0d35dfa27da4a8eb7d97c`; compiled/test `7db900004d0fc1f89004ad1bef48ef586d29ad7f`.
- [CI run 36507024347](https://github.com/PhabejSam/pokemon-three-horizons/actions/runs/36507024347): two new native tests pass across five trainer and two wild cases; prior rival loss and Rocket retry tests also pass. The preceding test checkpoint fails the trainer response assertion while wild controls pass.
- Exact prior-ROM mGBA reproduction: selecting RUN and confirming quit in Rick's trainer battle reduced money from 17320 to 15808 and warped to Cerulean Center. The TH-only setting now selects the native cannot-run script and returns to action selection, preserving money, HP, bag, flags, location and callback. Actual defeat behavior is unchanged.
- Focused compilation uses the native runner and root TH suites; full upstream sources remain required at integration. No complete ROM was built for this config-only task.

## Task 23 SELECT native checkpoint

- Feature `423d35337626b0ac574bcf984a1e2694142742aa`; compiled/test `c3c04b50ca34d65900f4f3827b0612d8c97c9076`.
- [CI run 36508937808](https://github.com/PhabejSam/pokemon-three-horizons/actions/runs/36508937808): six new native groups pass, including repeated swaps, PP/PP Ups, zero PP, duplicate moves, trailing-empty-slot bounds, doubles, transformed party protection, cancel, native entry restrictions and slot-dependent effects. The old implementation fails SELECT entry, Mimic, Encore and Last Resort assertions; cancellation/restriction controls pass before and after.
- Related upstream suites pass: Encore 18, Disable 1, Mimic 3, Last Resort 11, Choice Band/Specs/Scarf 3 each (42 total), no selected skips. These are focused TH-mode battle tests; they are not the final upstream-game build matrix.
- Exact old-ROM SELECT captures and deterministic reproduction are retained. The grouped candidate below passes native cursor/cancel/repeated-swap presentation and actual use of the moved Bite in Rick's battle. After victory, an in-game Save and cold battery Continue preserve the entire fixture party, including move order, PP and PP bonuses. Native parameter tests cover nonzero PP bonuses and doubles.

## Tasks 23–24 battle/capture visual gate

- Feature `091e6d70035de3782a008f9b11a9bc6c7f293c47`; compiled/test `7d8daad72536d2c1ee2c4566fdb47804d389b064`; development ROM SHA-256 `dd1906bdf7a474ffeb9d5ca27948619815a3a3e090e2f04d134f9f3a856cdd8e`.
- [CI run 36511983073](https://github.com/PhabejSam/pokemon-three-horizons/actions/runs/36511983073): five new capture groups and six previous capture regression groups pass. Cases cover Caterpie, Weedle, Pikachu, rapid/normal input, one registration, repeat catches, nickname yes/no, maximum names, full party/PC, full storage rejection, and configurable legendary editor return. Actual cry lifecycle tests use the native runner with normal audio; headless mode disables cries and is unsuitable for this test.
- Behavioral RED at [run 36511314487](https://github.com/PhabejSam/pokemon-three-horizons/actions/runs/36511314487): early-dismissal and fresh-input-boundary assertions fail with the preceding implementation; registration and nickname controls pass. Earlier fixture setup failures are retained, not reported as behavioral RED.
- Exact-ROM baseline reproduces dismissal of Rattata's first entry while its cry task is active. Candidate Pidgey registration stays readable after the same early input and 600 held-A frames; release and a fresh press return to intact battle graphics and one nickname prompt. Normal-input and repeat-catch presentation also pass visual inspection.
- These are focused mGBA core fixtures using disposable copies of a synthetic P12 battery save. No emulator state crosses ROM revisions. Whole-chapter manual acceptance, personal-save acceptance and RG40XX H acceptance remain separate gates.
- Reproducible screenshots, traces, harness and logs: task workspace `outputs/playtest-13-development/task23-24-battle-capture-evidence.zip`, SHA-256 `f69e42fb9cffbdc7ad1f53d5a415c1136ffff70d18720e7aeeffe0d5e2cd5e07`. Exact ROM/ELF and native logs are also retained in CI artifact `11010206302`.
- Matching emulator states, synthetic battery input and mGBA core are retained in `outputs/playtest-13-development/task23-24-reproduction-inputs.zip`, SHA-256 `3810e0e42fbb86d66ffeecdf7d7da257122d12e10fbd4eaf6cc75ad674158e0d`. States are revision-specific and must never be loaded into another candidate.

## Task 2 Kanto map checkpoint

- Feature `102f2e44c5b23d0a70f22bf42d0d02fb9499b45b`; compiled/test `0cd7c70890fd7c5a97c9d415edd0047f8beea418`.
- [RED run 36513991378](https://github.com/PhabejSam/pokemon-three-horizons/actions/runs/36513991378) fails the actual field-map title assertion; Hoenn control passes. [GREEN run 36514520623](https://github.com/PhabejSam/pokemon-three-horizons/actions/runs/36514520623) passes both groups across four Kanto fixtures and the upstream Hoenn fixture.
- Exact prior-ROM reproduction shows Kanto graphics with a HOENN title in the rival's house, and HOENN description/title at the Viridian school and S.S. Anne captain's wall maps. Metatile dispatch and the explicit rival-house object now share a TH-owned Kanto script; native graphic selection and map metadata are preserved. The field title uses the same region metadata as the graphic in TH builds; other game builds retain their prior implementation.
- Audited Hoenn references in research dialogue, regional starter displays, travelers and cargo are intentional. Viridian's Spearow house has a name sign rather than the reported school wall map; no extra interaction is invented.
- Repaired visual acceptance passes in the grouped Tasks 2–3 candidate below.

## Tasks 2–3 Kanto interior gate

- Feature `20ae52749ed23fdfb2ed396445b00b9385bc0e2a`; compiled/test `438b7ee777ccf5ebcfa6abee4ceb578cf0f35fa3`; ROM SHA-256 `2e12a283956e74f0c1599dc1859339209fdd0205d7a1b63b3c42f96ce2e0e967`.
- [CI 36516885791](https://github.com/PhabejSam/pokemon-three-horizons/actions/runs/36516885791) passes four native groups, including both TV fixtures, repeated conversion/reloads, Kanto map metadata/title/dispatch and ordinary Hoenn controls. [TV RED 36516023753](https://github.com/PhabejSam/pokemon-three-horizons/actions/runs/36516023753) reproduces tile entry 1077 becoming 3074; three controls pass. Earlier fixture include/link failures are not behavioral RED.
- Exact-ROM mGBA core checks: rival house, Viridian school and captain's office display KANTO with the correct map and location. Viridian/Vermilion TVs retain their complete tile entries after two interactions on each of two map loads; dialogue remains available. Images and traces were inspected. The guard uses TH ownership and actual imported FRLG layout format; ordinary Hoenn TV shows retain their conversion.
- Reproduction archive in task workspace: `outputs/playtest-13-development/task2-3-interior-evidence.zip`, SHA-256 `5d85dad5d1a155b88a02e55fac0236f480ab486ce4089299cd79430794c6c534`. Includes screenshots, traces, revision-specific states, synthetic battery fixture and mGBA harness. Matching ROM/ELF retained in `interior-candidate` and CI artifact `11011208934`. No personal save was modified. Full chapter and hardware acceptance remain pending.

## Task 4 Day Care native checkpoint

- Feature `04ac491f65b2eb89bb5c51091e9cd4bc7fe0c243`; compiled/test `0f1a08b1f277fe7862c3a8b46fa5cd4c563e08a0`.
- [Native RED 36518322746](https://github.com/PhabejSam/pokemon-three-horizons/actions/runs/36518322746) fails both deposited and preexisting storage visibility. [GREEN 36518881259](https://github.com/PhabejSam/pokemon-three-horizons/actions/runs/36518881259) passes two native groups and three host checks: deposit, party compaction, experience/fees, return identity/item, preexisting slot recognition, untouched second slot, reciprocal map exits and TH-only map selection. Earlier CreateMon fixture signature failure is not behavioral RED.
- Existing TH save storage is reused; the absent FRLG-only storage field is not added. The technical conflict and bounded adapter are documented in Task 4 of the plan. All P12 map indices remain unchanged; the new interior is appended at index 87. Existing upstream game map groups exclude TH13 maps.
- Runtime doorway, dialogue and cold-save acceptance remain pending the grouped Tasks 4–5 route gate. No ROM was built for this native checkpoint.
