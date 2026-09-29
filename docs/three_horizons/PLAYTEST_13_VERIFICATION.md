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

## Tasks 4–5 route gate

- Feature `83ac9db6673211bd4c9c39cc7d6a700c563d2519`; compiled/test `467e21c2cff0023d86db7dbe25339a810b7fc8ab`; ROM SHA-256 `cbf76bbdc462f05aa59b907b872e82bb51e658359329cefce9a4a04d2c1a17ad`.
- [GREEN 36520527113](https://github.com/PhabejSam/pokemon-three-horizons/actions/runs/36520527113): native guard dispatch/direction group, both Day Care groups and all four route host checks pass. [Guard native RED 36519995778](https://github.com/PhabejSam/pokemon-three-horizons/actions/runs/36519995778) fails the missing native trigger; [host RED 36519848139](https://github.com/PhabejSam/pokemon-three-horizons/actions/runs/36519848139) fails missing lane coverage.
- The old ROM already blocks Saffron at the closed door. Its defect is silent passage past the guard, reproduced from both sides in all three corridor lanes with walking, B-held movement and cycling. The repair retains those door barriers and adds directional dialogue/turnback. The repaired ROM passes all 18 approaches, one-step retreats and return travel. Followers resume on an adjacent tile after movement; four doorway-adjacent in-game saves cold-load without trapping the player.
- Day Care native entry/exit and immediate reentry pass from all three approach lanes. FRLG mat sides are ordinary floor; the center has the actual south-arrow exit behavior. All three authored warp records are reciprocal. Actual Save/cold Continue inside the new room preserves position/party and allows exit. Deposit, actual Save, cold Continue and withdrawal return the same inspected Pokémon data and charge exactly 100 (17320 → 17220), with the five remaining Pokémon unchanged.
- Full Underground Path traversal passes in both directions using its native stair transitions and separate Route 5/6 doors. The initial runtime harness accidentally reentered a stair while pathing toward the exit; an explicit lower-room waypoint corrected the fixture. No game assertion or failure was suppressed.
- Exact-ROM images/traces and reproduction inputs are in task-workspace `outputs/playtest-13-development/task4-5-route-evidence.zip`, SHA-256 `d469ef6895b91126f4687118647dec80ee6b5dcca546ffd9dd2343f8a71e31fd`. Candidate ROM/ELF retained in `route-candidate` and CI artifact `11013435671`. These focused mGBA core checks do not constitute full-chapter or RG40XX H acceptance.

## Tasks 6–9 interaction gate

- Feature `91c6ace7c13f392972d8da76c5515e1fe0342db8`; compiled/test `e1b18e3273bac5ff8889be7bc56adcca55c10ef4`; ROM SHA-256 `857a59eb78597345260e5812eb746d152907025b5947d8f7dadddd44c5e7d35c`.
- [Grouped GREEN 36524824810](https://github.com/PhabejSam/pokemon-three-horizons/actions/runs/36524824810) passes five native groups (aide receipt routing/rewards, Bill reconstruction, original full-pocket and money-cap controls) and five focused host checks. Guide native/host GREEN: [36522831476](https://github.com/PhabejSam/pokemon-three-horizons/actions/runs/36522831476); bridge dispatch/completion/loss GREEN: [36523338093](https://github.com/PhabejSam/pokemon-three-horizons/actions/runs/36523338093); Bill native/host GREEN: [36523988929](https://github.com/PhabejSam/pokemon-three-horizons/actions/runs/36523988929).
- Guide baseline shows normal connected-map object creation inside the camera at the old authored position, not invalid terrain. Moving the visible guide farther from the seam and placing the badge trigger beside him resolves that presentation. Native and host checks cover every passable lane; exact-ROM checks pass both approaches, badges absent/present and walking/running/cycling. Six unbeaten early-gym trainers still start their correct battles after the three leaders are beaten. A stale temporary-variable parameter is a robustness control, not a demonstrated ordinary museum-exit bypass.
- Actual bridge loss returns to Cerulean Center without awarding victory; a subsequent actual win shows ongoing journey/Bill dialogue, the rival departs, and revisit does not repeat him. Only the intermediate town navigation is relocated by the disposable fixture. Actual Misty victory after the bridge also uses the updated shared progress message. Existing once-only completion receipt and commands remain unchanged.
- P13 Bill lifecycle passes declining help, actual machine entry, native Save/cold Continue, exit/reentry, PC rescue, exactly one human Bill, rescued-state Save/cold Continue, full-pocket rejection with its displayed message, retry granting exactly one ticket, repeat talk and PC notes. An additional real P12 mid-machine battery migration reproduces a scene reset and is being repaired separately; this gate does **not** yet accept that migration case.
- All four aide receipt combinations award only missing supplies. Repeat visits preserve money and quantities and display explicit already-delivered dialogue. Original full-pocket and money-cap controls remain green.
- Runtime fixture corrections: remove a surplus A press that selected Yes in the decline test; capture BattleStart and the ensuing battle in one uninterrupted mGBA call because the core rejected deserializing that precise transition state; use a cold battery for the separate full-bag replay because a continuing emulator state had advanced past ticket receipt. No game assertions were suppressed.
- Source/docs CI caught the missing navigation entry for PLAYTEST_13.md; SUMMARY.md was corrected and the original documentation validator passed.
- Reproduction archive: task-workspace `outputs/playtest-13-development/task6-9-interaction-evidence.zip`, SHA-256 `e032ddf32fd27698d05040cb3f07cd8ca4ef21b8f8af582a3e72f3337f86a8ee`. Includes inspected before/after screenshots, traces, disposable battery fixtures, exact-revision states and scripts. Matching ROM/ELF retained in `interaction-candidate` and CI artifact `11014488352`. These are focused mGBA core checks, not full chapter or RG40XX H acceptance.

## Tasks 10–13 ship gate and Bill migration completion

- Feature `6579e56324adb67baa01f63264578df8c660dfa3`; compiled/test `afbec817eb60d95a99c36c8e07772415f80a1529`; ROM SHA-256 `b6f0667c6e845ba4e1b9dcacdaf7cae5e5e57b9d4bbe2eae28c3bf039acd5cb5`.
- [Grouped GREEN 36529766742](https://github.com/PhabejSam/pokemon-three-horizons/actions/runs/36529766742): two native groups and two focused ship host checks passed. The captain regression first failed on its inappropriate face-player command; the repaired script keeps him facing the bin during sickness and explicitly turns him after help.
- Boarding: all three lanes, walking/cycling, ticket absent/present, departed receipt absent/present (24 crossing cases), four direct-talk cases, rejected retreat and accepted return travel pass. Tickets remain unchanged. The departed receipt is a boundary fixture; Task 25 departure implementation is not claimed here.
- Ship alignment: only the TH boat object's facing changed to the native down-facing pose. The asymmetric right-facing sprite flip was reproduced independently while leaving its anchor/layout/warps unchanged. Both approach sides, Pikachu/Gyarados followers and two enter/exit cycles per case pass. Follower screenshots explicitly move after map load and verify the active follower species.
- Ship rival: all nine partner dispatches start their correct actual battles. Actual wins from all three trigger lanes produce a visible collision-free walking exit to (20,11), then removal. Frame samples and object traces confirm movement before removal. Actual loss returns to the healing location, keeps the encounter unfinished and allows a successful retry. Reloaded corridor does not refight after victory.
- Captain: all three accessible sides, rival unfinished/finished, full TM pocket, failed grant/retry, repeat interaction and already-owned HM01 reconciliation pass. Exactly one HM is retained. Before/after sickness and recovered posture images were inspected.
- The outstanding Task 8 actual P12 mid-machine battery now cold-continues with Bill inside the machine and completes native PC rescue. Its focused migration test had failed before the bounded P12-state import; [migration GREEN 36526680422](https://github.com/PhabejSam/pokemon-three-horizons/actions/runs/36526680422) covers eight migration cases and the existing Bill reentry matrix. No save fields were added.
- Three additional actual P12 battery saves at the new official tile, dock approach and ship exterior cold-continue with identical party/bag data and allow movement. These are disposable emulator fixtures, not the user's unprovided post-Surge hardware save.
- Reproduction archive: task-workspace `outputs/playtest-13-development/task10-13-ship-evidence.zip`, SHA-256 `8166ba27fac3665f8701b9f4c6f97611b0b551e58a377b4f9032d211b7cbc2fb`. Matching candidate/ELF retained in `ship-candidate` and artifact `11016725998`. These are focused mGBA core checks, not full chapter or RG40XX H acceptance.

## Focused locals gate — Tasks 14–17

- Feature `479cd3a647e2743f2548480fcde4eb6ddc478f52`; compiled/test `e848007b15f0842d22e3e6a4319fca76b94d4aaf`; ROM SHA-256 `b0dbef17ffbe54c30ad800151db2d8c7d7c0392ebb361adca54be0e0d8866b61`.
- [GREEN 36530965146](https://github.com/PhabejSam/pokemon-three-horizons/actions/runs/36530965146): badge-dependent guide selection, three prior native field-move groups and the focused local-object host test passed. Guide regression first failed because its message pointer did not change after the correct badge.
- Farfetch’d: normal cry, trainer interaction, door reentry, cycling rejection, actual battery Save/Continue, four active objects including small/large follower. Added species sprite is visible without palette corruption.
- Machoke: existing 32-pixel species art, all four poses, cry, trainer interaction and passage verified with Pikachu/Gyarados. Local ID, position and collision footprint remain unchanged.
- Guides: all three gyms show original advice before their badge and congratulations afterward, including battery Save/Continue. Six existing gym trainers still start the correct actual battles.
- Cut: no HM, no badge, incompatible species, Egg and fainted party all display the same short two-line hint. Eligible party retains the original confirmation; native eligibility tests pass. Captain keeps detailed instruction including the Egg exclusion.
- Before/after images inspected. Reproduction archive `outputs/playtest-13-development/task14-17-locals-evidence.zip`, SHA-256 `dc19768ab1aef0963aa5a728966dc27c66dc8c82f3d0ac857cafbbddfd01097b`; exact candidate/ELF retained in `locals-candidate` and artifact `11016693268`. Focused mGBA core acceptance only; full chapter and RG40XX H acceptance remain separate.


## Focused Tasks 19–20 cave scene acceptance

Feature `6547404a9fc3dbf56e3985a0d5f1c59044946086`; compiled `7c0d93fb9445f003b957541a9b18869c9d58b3c6`; ROM SHA-256 `5b43ffec2a6fdc0760898302aec4f1984ded65ba5a846309d9aeb29c010b0e0a`. CI run 36535422424/job 109298239716 passed nine native groups and eight host checks. The native script tests did not establish full Rocket acceptance: emulator testing subsequently found trainer records forcing doubles during singles, tracked separately in Task 21.

The exact-ROM Clefairy circle returned all four participants to their spaced formation; repeat interaction used the brief stationary hop and survived native Save/cold Continue. Seven researcher approaches aligned correctly and completed actual battles. Loss/whiteout/retry, guarded fossils before victory, independent Dome/Helix rewards, full-bag retry, and native Save/cold Continue passed. Three actual P12 battery fixtures below the stairs, above the stairs, and on the researcher's new tile retained party/bag/position and allowed movement after migration. Screenshots were inspected.

Evidence: `task19-20-cave-evidence.zip`, SHA-256 `c56a29a2a13bd532b22e50597796f765930bf1c4ac4846e0773d1348e70a8a9a`, in the local `outputs/playtest-13-development` release-work folder. These are focused emulator checks, not whole-chapter or hardware acceptance.

## Focused Task 25 S.S. Anne departure acceptance

Feature `e2670835efec6cdd35ae01e25778b5b60f2eff9b`; compiled `1990c965fb3969438413468a802737918aa97565`; ROM SHA-256 `43f975763c447f78a9ca0c8030ec53b5eeb22f30d5a6c5dcfdcff776770b7510`. CI run 36536670772/job 109302190526 passed five ship groups, four state groups, one Bill migration group and sixteen host checks.

All seven incomplete prerequisite combinations retained the normal exit without departure. All three eligible exit lanes displayed the warning, allowed declining, aligned the player for the native sailing sequence, then delivered the player to the safe Vermilion dock and denied boarding. A large Gyarados follower was present for approach and correctly hidden during staging. Ticket/HM quantities were unchanged. Native Save/cold Continue passed inside after declining and outside after departure; reopening the last predeparture battery save retained the docked ship. An impossible departed-inside native save recovered to the dock with the correct town objects and working movement. Native tests cover every old ship-room ID both before and after captain help; P12 saves never auto-depart. Animation and warning screenshots were inspected.

Evidence: `task25-departure-evidence.zip`, SHA-256 `fdbfe363afe4bcd56850f2f80bb7c89d92d27fcba2bdec240bb34a5e8b659d89`, in `outputs/playtest-13-development`. No RG40XX H acceptance claim.


## Focused Task 21 Rocket formats and recovery

The first cave emulator gate exposed a genuine fallback bug: the script chose singles correctly, but Jessie/James trainer records forced `BATTLE_TYPE_DOUBLE`. A new host regression failed on that data, and removing only the two forced-double attributes fixed the cause. The paired script still explicitly creates the two-opponent double battle. Trainer IDs, party species, artwork and credit remain unchanged.

Corrected feature `20c78dd7cd5f072b263789fec50a51b91abfd279`; compiled `bb96e6278bff743df079637f765efc570198f80e`; ROM SHA-256 `33caa5f1310192ba97d07cc993e1113b46debbf2994f880e0932291ef4aa68ee`. CI 36537252805/job 109304022408 passed ten native groups and nine host checks. Exact-ROM runtime verified one usable partner gets Jessie then James as singles, two usable partners get doubles, a six-slot party with only one usable partner gets singles, and all Eggs return safely without starting a battle. HP/status/PP were identical across the singles handoff. Actual Jessie, James, and doubles losses returned safely; retries restarted the complete pair, including cold Continue and both format switches. Completed encounters removed the trio and stayed completed on revisit and cold Continue. Portraits, separate opponent party-ball groups, and dialogue were inspected. Meowth stays a speaking observer.

Evidence: `task21-rocket-evidence.zip`, SHA-256 `21de471f2f228b695aef76ca64d89e07301c7de76670028c7027fe090a3a1868`. This closes focused Rocket emulator acceptance, not RG40XX H acceptance.

## Focused Task 26 Trainer Services checks

Feature 76d34e19d2e97fcfbb298f813194e3720fde7417; compiled/test af8f14945867e819a35a4ec6ea98f3894a81a700. CI run 36538120657/job 109306820300 passed five native groups and three host checks. Native coverage includes all six EV berries at EV 0, 1, 9, 10, 11 and 252, other stats unchanged, recalculation, friendship-only use, cap behavior, prices and once-only kit delivery. Host checks cover exact separated stocks, four city vendors and the live Cerulean workshop/referral. Purchase and consumption UI, persistence, and Lavender placement remain pending the scheduled later map/integration work; this is not complete Task 26 acceptance.


## Task 27 independent roster and level checks

Feature 64974dd502f4b1ad5335bead55366bf0d0aeb407; compiled/test 124d0bb5681baf096db15ccfbf631f31600a759d. CI run 36542246743/job 109320188030 passed the real generated Keigo roster test and two level-policy groups (18 explicit cases plus 90,900 highest-level/original-floor/badge combinations). Keigo uses Kakuna, Beedrill and Butterfree at level 18; native generation supplies valid moves/abilities and level-appropriate stored experience. Ricky and Elijah controls remain unchanged. Actual battle experience awards and full route acceptance remain pending.

Fixture corrections were explicit: a bit-field comparison needed a cast; the engine macro is lowercase max; and native gTrainers is a test-runner dummy table. A shared test-only accessor now reads the existing separately assembled real records. The previous Rocket record-only assertion was insufficient, although its separate host and exact-ROM checks were valid. The strengthened native assertion failed after temporarily restoring forced-double records (1 versus 0), then passed after restoration. No assertion was removed or suppressed.

The pure level helper has no battle hook yet. Unlimited Vs. Seeker, readiness storage, scaled rosters, cleanup, acquisition and full Task 27 acceptance remain pending the required capacity decision documented in PLAYTEST_13_REMATCH_CAPACITY.md. These checks do not constitute a release candidate or hardware acceptance.


### Task 27 approved rematch capacity implementation (verification in progress)

User approval on 2026-09-29 resolves the global-capacity conflict in favor of
map-local readiness. Full-width trainer IDs and authored evolution tiers are ROM
data; the existing 100 rematch bytes contain only temporary 0/1 state. No save
block or permanent trainer-flag layout changes. See
[the capacity decision](PLAYTEST_13_REMATCH_CAPACITY.md).

New-function RED: feature 5a9d574f6a4ec35ac7f56e61ad812f7a28e11494,
compiled ee58c416, run 36578571134/job 109440450710 linked unsuccessfully on the
missing readiness functions. The additional party/Egg/first-fight contracts at
2f738638ec66a2f702d1df511e8c56a72c971399, compiled 445e8284,
run 36579367252/job 109443168972, similarly detected the absent party overlay.
These are new-interface absence checks, not claims of reproduced battle bugs.
The prior exact bb96e627 baseline separately shows the disabled Vs. Seeker.

Host coverage detected the missing registry, rematch scripts, and Vermilion
recipient before each was added. All four focused host checks now pass: 68
shipped ordinary trainers, unique bounded map slots and matching objects, all
68 rematch script paths without one-time rewards, retryable badge-independent
gift and reachable researcher/nurse, plus the approved Keigo first-fight roster.
Final focused checkpoint 9d4eabb8a87ed644f5665f770e04cbee1251e8fa, compiled/test
revision 956240b96df42ecaba25f825699c90bb669dae34, run 36582645946/job
109454553666: all nine native groups and four host checks PASS. Native tests
cover full-width IDs, slot collisions/bounds, stale-map isolation, unchanged
defeat flags/save sizes, repeated no-charge use and native lifecycle resets,
level boundaries plus 90,900 combinations, Egg exclusion, unchanged first
parties, authored tiers and legal generation for all 68 registered teams.
The preceding synthetic-party fixture failed the engine's gender assertion
because it omitted TrainerMon.gender; specifying RANDOM_GENDER corrected the
fixture without weakening the assertion. Emulator acceptance and upstream
compatibility remain at their planned integration gates.

Task 28 source-executed delivery tests first reproduced missing Acro delivery,
lost-item receipt failures, and the unexpanded chairman story. All three host
groups now pass, including full-pocket retry, partial delivery, cancellation,
no-voucher refusal, repeat visits, and simulated reload of bag/receipt state.
The native engine keeps distinct Mach/Acro items; shop dialogue explains speed,
tricks, registration and dismounting before changing bikes. Actual item UI,
cycling/follower behavior and cold battery-save acceptance are still pending
the systems candidate. No bike movement engine change was made.

The 53 ordinary trainers on upcoming approved maps remain required additions to
the same ROM registry. The chapter-wide target remains 121; the current shipped
map count of 68 is not a scope reduction. Integration must re-audit final maps.
The exact post-Surge RG40XX H P12 battery save is still to be supplied by the user;
the older Cerulean/P11-marked save must not satisfy personal-save acceptance.

## Tasks 26–28 exact-ROM emulator acceptance

This record supersedes the pending-UI statements above. Feature
`8fe142c085699973215fdea7ba3165db2ddc9fdf`, compiled/test revision
`682bfdc9d0f04b50c10bd64a3e24dde5604826c0`, ROM SHA-256
`585898475be72ffe62e3c5cbc417c46926fc3cdb7918784080e40e4110c410ec`.
CI 36589418225/job 109478294084 passed the grouped focused tests. Disposable
battery fixtures and the exact matching ROM/ELF were used in mGBA libretro.

- Trainer Services: four city vendors and the Berry Workshop were inspected.
  Both shops passed purchase, cancellation, insufficient-money and full-pocket
  cases. Mint, Capsule, Patch and EV berry use consumed the correct item and
  preserved unrelated identity/stats across cold Continue. Incompatible Capsule
  and ineffective berry did not consume an item. Silver Cap changed only the
  chosen IV; repeat/no-effect and cancelled Gold Cap did not charge; Gold Cap
  maximized all six. A capped Pokémon retained identity and IVs after native PC
  deposit into Box 1 and cold Continue. Lavender placement belongs to Task 39.
- Vs. Seeker: researcher acquisition works before badges, once only, with
  full-pocket retry and cold Continue. Rick's actual rematch used evolved
  Beedrill/Butterfree at level 35; victory and blackout cleared readiness while
  preserving permanent defeat history. Immediate reuse, map changes and cold
  Continue behaved correctly. Ready trainers were exercised on route, forest,
  cave, Gym, bridge, cape and ship maps. Luis's actual rematch returned him to
  the water edge with the walkway clear. An undefeated trainer and a boss-only
  fixture were excluded. Keigo's first battle used the approved level-18 team,
  awarded experience and set its original defeat flag.
- Bikes: new voucher, either existing bike, both bikes and an old receipt with
  missing items all led to exactly one of each native bike. Partial delivery
  retried without duplicate items; cancellation left bag/receipts unchanged.
  Both bikes moved outdoors; Acro B input, registration, switching by dismounting,
  indoor refusal and cold Continue were checked. The inherited follower is
  hidden during cycling and returns when walking. The chairman's four short
  story pages, once-only voucher and repeat dialogue were inspected.

These checks complete the focused shipped-map work for Tasks 26–28. The 53
ordinary trainers on later approved maps and Lavender vendor remain explicit
later-task obligations. Full upstream/save-layout integration, the exact user
post-Surge battery save, and hardware acceptance remain separate gates.

## Task 29 reproduced Rare Candy continuation defect

A level-35 Machoke learned Dual Chop at 36 but initially skipped evolution until
another candy raised it to 37. The move-learning completion handler compared a
move ID with state values 1/2. The new native test reproduced 530 versus 1 on
`ca50909451b1071d2d09dd05f3091ec7b0b9ca7a` (run 36593253105/job
109491518808). Earlier test-fixture compilation errors are not behavioral RED.
The TH-only repair selects the existing learnMoveState field; upstream still
uses its original accessor result. No evolution level or save field changed.

Feature `245e8fc66bb46b9f4e8ff94a98799269535d2f62`, compiled/test revision
`3c48c6e376283000e81068ac5cb2e85fb5b8c8f4`, ROM SHA-256
`168d9c4ad396fb7219291f8fe7f8b0c4ec4d03195b302e8e64aeca4df1b54065`.
Run 36594346912/job 109495283006 passed nine species, 38 starter, four evolution,
five training and nine rematch native groups, plus three species and ten systems
host checks. Exact-ROM evolution UI acceptance is recorded separately after
completion; this automated result alone does not assert it.

Tasks 26–28 evidence archive: `tasks26-28-systems-evidence.zip`, SHA-256 `25aa6f889dadebe3afd6ce92554e5be06fd31af791d011b881f3f3f629c83982`. Archive metadata distinguishes earlier diagnostic failures from passing acceptance captures.

## Task 29 completed focused evolution acceptance

The Bag regression failed with native item type 4 versus required type 1 on
feature `ab5e18bf002cebeea6c586ef642d8f73e57ee1e1`, run 36595798768/job
109500253020. Feature `1aa074c9ef4ab73f90dcec9cf2e098e7e1270e25` enables the
existing item-use configuration only for Three Horizons. Compiled/test revision
`04fb4b295acbd07e82aeb195ec6e078663027e8e`, ROM SHA-256
`0ea5927a03d258807e775189b44d242fa0a6884f09d564fe42ffe4fa21608400`.
Run 36596594503/job 109502979296 passed ten species, 38 starter, four evolution,
five training and nine rematch groups, plus 13 host checks. Native coverage
checks all twelve thematic items' Bag type/callback and sixteen species branches.
The exact ROM evolved Onix to Steelix, consumed one Metal Coat, preserved identity
and showed the evolved follower; cold Continue passed. Incompatible Magikarp
consumed nothing. No later item was added to an early shop or reward.

The preceding exact `3c48c6e3` ROM separately passed all four level-36 evolutions
with one candy, nickname/personality/ability/nature/IV/EV/held-item preservation,
follower and cold Continue. Gyarados Water/Dragon was visually checked. Native
learning prompts taught Dragon Tail 26, Outrage 48 and Earth Power 40; Summary
Relearn taught Earth Power, and Typhlosion's reusable Earthquake TM still worked.
Primeape at 19 uses did not evolve on level-up; at 20, cancellation and next-level
retry worked, including Annihilape follower and cold Continue. Native battle tests
cover actual Rage Fist attempts and Laser Focus's one-attack critical scope.

Evidence: `task29-evolution-evidence.zip`, SHA-256 `921a583af9b7c6d7f0c86ccda40389257e1c979f5d1f67b0a4d4d1b358866e2b`.
Archive metadata distinguishes test-driver diagnostics from accepted results.
Full non-TH controls and final save/hardware gates remain integration work.

## Task 30: Research Gear persistent model

Feature `6d217845d6fd11428235435efcb2e9fc5635223a`; compiled/test revision `4d7af602063ffdc668600ac5117a22af3a4b3c89`. CI run 36599528167 / job 109513012392 passed five native research groups, six native migration/state groups, and four host ownership/map-index checks. The preceding interface test at `efb43b871310ac5ce4c3bc321a166f9f11bcdb88` failed on the missing research functions before implementation.

Eleven stable authored entry IDs, ten photo IDs, and three ordered milestone calls use the reserved Task 1 flags. The compiled ROM tables occupy 396 bytes for entries, 360 for visual compositions, 20 for photo-flag mapping and 12 for call-flag mapping, plus text and executable code. SaveBlock1 remains 15,568 bytes and SaveBlock2 3,884 bytes; there are no saved pixel buffers or new save fields. Final release ROM size is measured at the integration gate.

Invalid entry IDs through 65,535 cannot write state; photo/call boundaries are rejected; repeat observations, captures and calls are idempotent. Calls retain authored priority through saved flag restoration. P12 Hoothoot imports only from the audited scalar value 1. The shared old forest receipt imports a general historical report, not a guessed specific pair. No migration invents a photo or delivered call. These fixtures do not replace the user's exact post-Surge RG40XX H personal-save acceptance.

Task 31's menu, actual photo presentation and native save/Continue validation remain the next gate.

## Task 31: Research Gear native menu gate

Feature `8be5e892d8bf33fa25eebb4b1b163e7df1cd34a0`; compiled/test revision
`b6cd755ced02eb27ed003f0e190b3686270af197`. ROM SHA-256
`dd4f8e8970ba53526abcc4b101c2a7ebd2e7453a32415f94d63b93ae25f1ff2b`.
Run 36602206498/job 109522120044 passed five menu, five research and six
migration/state native groups and four host ownership checks. Artifact
11049997319 ZIP SHA-256 `ed0c042d4b44e9563e3154f78de5d30eb7206992ed89f15aa3df4d2ceffac52d`.
Missing-interface RED was observed at `3b855a6ffd938a7baa64dcb593ef15e6388627f6`.

All ten photo cards were rendered by this exact ROM and inspected at 240×160,
including Pinsir/Heracross, Mareep/Nidoran, Aron/Geodude and Misdreavus. Native
sprite poses share terrain; paired subjects remain visible and face the shared
interaction. Each card has location/species/observation and a second-page professor
note with region/origin. The Moon card shows all four participants. Existing
32×32 overworld assets require at most 2 KiB of OBJ tiles and four palettes.
Only persistent flags identify earned cards; compositions remain in ROM.

Empty modules, all photos and pagination, ordinary save/Continue, and native
menu return after an actual trainer rematch and Cut passed in mGBA. Native tests
cover locked Gear, zero/one/all records, held input, B at each menu level,
sprite/window cleanup, own-state allocation failure, duplicate photo rejection,
and read-only replay of all three professors' three milestone reports. The
movement driver initially tried walking into a tree after closing the menu;
checking an open adjacent tile demonstrated normal controls without a game fix.

Field Yes/No photo-script integration, milestone-call delivery and ship additions
are tested together in Task 32 before the 30–32 group is closed. State-only tests
are not evidence of a completed field photo interaction. Screens and replay
harnesses are retained in the plan workspace's research-after and emulator folders.
These are focused development checks, not final hardware/personal-save acceptance.


## Tasks 31–32 field integration gate

Feature 74ffc703a70241a92ff3a8d7ef4154ce6c183439; compiled 3debc271e2f5100c6f96bd59354f62c74710f633. ROM SHA-256 9509a9dbb024295ff877335abe6a081c694ac905e6cf1796bf33e8d59bd7cb61. CI 36606070131/job109535278809 passed 2 call, 5 menu, 5 research and 6 migration/state native groups plus 5 research host checks. Local ownership 4 and continuity 6 also passed. Missing-interface RED: 901828bae868ff257332bd3395217065bdd2a86d.

Exact-ROM mGBA: old sighting without Gear records observation; declined photo grants nothing; accepted photo flashes briefly and records once; repeat acknowledgement is readable; ordinary save/Continue retains it. Calls queued inside a menu wait, deliver three authored milestones in order, set receipts after their text, survive a pending ordinary save, and do not replay after completion/Continue. All three contact replays are read-only. Native callback guards cover battle, naming, bag, party, load, movement, warp/fade, field-control locks and script activity; these guard tests are not claims of separately playing every full UI workflow.

Ship partners, traveler, deck exit, post-rival captain route and declined/accepted native departure passed with the new scene. Small Pikachu and large Gyarados followers were inspected. Thirty-six source geometry variants cover every deck NPC adjacency and both exits, with nine total objects including player/follower. Test-driver routes into existing barrels were corrected; no map alteration was needed. The captain staircase requires the native rightward stair input. No extra story gate/reward was added.

Evidence archive 	asks30-32-research-evidence.zip SHA-256 644cf0d0dd1a1e616048b7218968573258a14afa61fb533e5193b853b6fef6a0. Synthetic development battery only; final personal P12 migration and RG40XX H acceptance remain outstanding.

### Task 33: Route 11 and Diglett's Cave focused acceptance

Feature `51c12db2ec308d04b99a5c161ac8f4677aec1449`; compiled revision `bfd02e25d26d0825ff9e03f167e33eb7748f3bd7`; ROM SHA-256 `cb839188672a59926593e104aa29aa52f4f35054057fb1a3831a204fc9cd77a1`. CI run 36612294700/job 109556485097 passed nine native rematch groups and eight cave/route host groups. Closed-map-graph and tileset checks also passed. Runtime inspection matched all 92 project map headers to the compiled ELF.

Actual mGBA checks passed: Vermilion–Route 11–south entrance–entire cave–north entrance–Route 2 and reverse; scene/photo and cold battery Continue; three visible items plus hidden Escape Rope, with no duplicate pickup after Continue; reusable Escape Rope returning to Route 11; both bicycles and follower return after dismount; Eddie's original Ekans 21 first battle and full-ID 104 Arbok 35 rematch; rematch readiness clearing without defeat-history loss; ordinary Diglett capture and native PC release without modifying other party/box occupants; cave blackout returning to the visited Vermilion Center and healing.

Eight unforced no-Repel cave samples were Diglett at levels 15–21, including one Hidden Ability. This proves these observed encounters, not a statistical 10% rate or all species sampling; exact weighted-table and existing ability-roll tests provide separate coverage. QA sampling used Run Away to avoid Arena Trap correctly preventing escape. A 60000-step Repel fixture was corrected to 30000 because the high bit denotes Lure. A blackout fixture initially expected Vermilion despite its actual last-heal location being Cerulean; explicitly visiting Vermilion corrected the fixture. No engine behavior was changed for these fixture errors.

Two actual integration defects were reproduced and repaired: omitted map-builder registry entries caused an invalid native transition; adding them exposed missing compiled script includes and cave tileset linkage. Whole-registry, recursive script-closure, and selected-tileset regressions failed before their repairs and passed afterward. Earlier failed candidates are diagnostic evidence only. Capture/release and corrected blackout/Rope component sequences passed; the final combined convenience drivers were not all rerun end-to-end.

Evidence archive: `task33-cave-route-evidence.zip`, SHA-256 `45572c150929461fb00314e7a81ef2ed269a9f5609b53707399a1280d37efad3`. This is focused emulator acceptance, not the final personal-save or RG40XX H gate.

### Task 34: Route 2 aide and Flash focused acceptance

Feature `8daabab28d15ec5f6fc741173d2e78386a903cb9`; compiled `844747e4b0d97570518b6267d3469aba862861c2`; ROM SHA-256 `4c10dd72c3936353bcdd95132495af0348db9e20debeac522d67c8fbacada985`. CI 36616767397/job 109571661915 passed three Flash groups, three existing Cut groups, and three Route 2 host groups. Ten focused cave/registry/graph/tileset checks also passed locally. All 93 compiled project-map pointers matched the exact ELF.

The new native tests first failed at the old Flash unlock/party lookup. After the TH-only unlock, tests cover HM ownership, Thunder Badge, conscious compatible non-Egg user, learned versus unlearned HM, full versus partial move sets, unchanged moves/PP/PP Ups, shared scripted eligibility, and other HMs staying locked. Existing Cut tests remain passing.

Actual mGBA acceptance: both exterior door lanes and both passage directions; aide quota nine rejected, ten/eleven accepted; an obtainable regional species counted as the tenth; pre-Surge denial; full HM pocket giving Gear independently then retrying HM05; previously owned HM05; repeated visits; activation call; ordinary battery Continue retaining both receipts and inventory. Native Flash with four unrelated moves expands the radius from level 7 to 1, retains all party bytes, remains lit after cold Continue/on another dark floor, and returns to normal outdoor lighting. Actual party-menu Cut with four unrelated moves removes the tree with all party bytes unchanged. Before/after screenshots were visually inspected.

The dark-map fixture uses the existing native Granite Cave maps through a QA-only relocation; no Hoenn connection is added to the game. Authored Rock Tunnel traversal is still Task 38. One initial save-driver attempt had not closed the aide's final text and therefore did not save; the driver now waits for dialogue and activation to finish. The complete aide matrix was rerun successfully, including cold Continue. The older diagnostic captures are retained and are not accepted evidence.

Archive `task34-route2-flash-evidence.zip`, SHA-256 `8aa3434798639705f0cf78675d21d388e1fbf6db7c32bf376a01d5deed32f3bc`. No personal battery-save or RG40XX H acceptance is claimed.

### Task 35: Route 2 local trade focused acceptance

Feature `19cccc4b31bf106af4a0fe6bcc0d3c4dcd249d1a`; compiled `742c6d23be698590eed42233af2232b6b9cfaf8a`; ROM SHA-256 `3d04f4b9e41eca41c3aed5d3d933fd2c4f2c3d455dee18b9809f431761671d01`. CI 36621293345/job 109587056547 passed four native groups and four trade host groups. Related aide and map-registry/compiled-script closure checks passed locally. All 94 compiled project-map pointers matched the ELF.

The native selected-name regression failed before repair (wrong party slot, string comparison 22 versus 0). The missing-record tests failed safely before the appended trade existed. Native tests now cover levels 1/37/100, all six selected slots, full and one-member parties, last healthy Pokémon, outgoing held item, unchanged other party bytes, normal ability, and Egg/wrong-species rejection. Three initially unlinked FireRed-only prompt strings were caught by the linker; a dialogue-closure regression failed before TH-local prompts repaired the omission. No warnings/assertions were suppressed.

Actual mGBA checks passed: native house entry and center exit from all three carpet approach positions; No/cancel/wrong species/Egg without inventory or party changes; native animated exchanges with one and six party members; non-leading selected slot; no changed other Pokémon; no extra item returned to the Bag; repeat dialogue without another exchange; ordinary battery Continue; interrupted animation followed by cold Continue restoring the whole pre-trade save. The native carpet's side tiles are decorative, so the initial driver assumption that each directly exits was corrected; the game was unchanged for this fixture issue.

The received Skarmory was inspected in summary, stats/moves, native Pokédex entry and cry screen (playing waveform), and as a follower after movement. Policy: selected Zubat's level and native moves at that level; Keen Eye (normal ability slot 0); Hardy fixed personality 0; IVs 15 each; no held item; nickname SKARMORY; OT REYLEY, ID 28413; native post-trade friendship 70. An outgoing held item travels with Zubat, as the dialogue warns. The receipt is set only after the native exchange returns; no link connection or multiplayer is required. Existing trade IDs 0–12 and save layouts remain unchanged.

Evidence archive `task35-route2-trade-evidence.zip`, SHA-256 `463b041cf87e5efb2d1c4acc0f23c6902faad7d6e0a0626ef7ad747c0298cc3a`. These are focused synthetic-fixture checks, not final personal-save migration or RG40XX H acceptance.

### Task 36: optional forest clearing focused acceptance

Feature `46e5d37510464c04680bc152c9f0edf04ff2700e`; compiled `03eb11d2bdb785a4e564ad5a380cb3f516251828`; ROM SHA-256 `2c016660e94cfdc11c37be15abb3310f0b1e65c1c38759d12c8bf073a4da726d`. CI 36624003946/job 109596214917 passed one native forest migration group, three existing native Cut groups, and three forest host groups. The compiled map-header audit matched all 94 project maps.

The private forest layout preserves every formerly walkable tile, all 18 existing objects, and all six warps. Two Cut bushes guard an optional clearing; either entrance lane is sufficient. The first/repeat Pinsir–Heracross observation and its photo use separate receipts from the earlier forest scenes. The Bottle Cap receipt is set only after successful delivery.

Exact-ROM mGBA passed: first/repeat observation; no Gear; photo No/Yes and no duplicate; large follower and follower disabled; photo card and professor note after reopen and ordinary Continue; full item pocket then retry, one cap and no duplicate after Continue; Cut without HM, without badge, Egg, fainted, incompatible, and valid full-four-unrelated-move party with unchanged moves/PP; entry into the clearing; old forest-layout battery Continue; save inside the clearing; north exit and return. Screens show both subjects facing each other, complete native tree edges, readable dialogue and an unobstructed entrance. The photo card includes location, both species, observation and professor note.

Old-layout Continue regression failed on the original native layout ID, then passed for P12 and prior P13 markers. Only the obsolete forest layout reference and cached map view are refreshed; existing position and defeated-trainer/earlier scene flags remain. A layout change also refreshes object templates, including when the version marker is already P13. Other maps and repeat loads stay unchanged. Save structures do not grow.

Evidence `task36-forest-clearing-evidence.zip`, SHA-256 `68b34517b1ae43c23397f5fbd08b3ebdddfaa46b404d4f3a00b870a8cf0de43b`. The migrated emulator fixture is synthetic, not the user's final personal save. Full new-game backtrack and chapter-wide replay remain at Task 41; RG40XX H acceptance is not claimed.

### Task 37: Route 9 focused acceptance

Feature `85c0efa7fad0864faad0609e2f688ceae4ebbcaf`; compiled `aa2480860ba16c7307824c8fa03b2e9f17b89d2a`; ROM SHA-256 `02c97c2628e57cd3689050953f310427acb1d29a65f0dfcd5b93f4cde3f606f6`. CI 36628267297/job 109610704825 passed nine native rematch groups and five Route 9 host groups. The exact-ROM map audit matched 95 maps. Related rematch/cave host checks passed (17 total), plus two existing encounter checks; all earlier encounter records are unchanged.

Native route geometry, nine trainer positions and first-battle rosters are retained. Full trainer IDs 114–122 join the map-local rematch registry (87 ordinary trainers so far). Mareep occupies one 5% land slot at levels 14–17; other slots retain the native Kanto distribution. The optional Mareep/Nidoran scene now stands on actual grass, with an independent observation/photo receipt and researcher comment. Five pickups have unique receipts.

Exact-ROM mGBA passed day/night first/repeat scene, no Gear, photo No/Yes, large follower, ordinary Continue, photo card/note reopen and cold Continue; west Cerulean connection, Cut entry and reverse return; Alicia's unchanged first party and full-width-ID rematch, victory preserving defeat history, loss returning to the last Center without awarding a defeat receipt; full-bag pickup retry/once; natural full-party capture sent to PC with identity, ability, moves and IVs retained after battery Continue. Native-resolution scene and card images were inspected. East Route 10 traversal follows in Task 38.

The initial undefined FRLG scientist graphic caused a visible link failure; an enum-aware graphic regression was added and the existing scientist graphic used. Before final acceptance, a visual grass mismatch produced a failing native-tile assertion and the three new scene objects were moved onto verified grass. No assertions were suppressed. Evidence `task37-route9-evidence.zip`, SHA-256 `067dad7aad2697ea65ccfe3a4f91385b61a6060ca83387c2f126f85ab9046c5f`. These synthetic emulator checks are not personal-save or RG40XX H acceptance.

### Task 38: Rock Tunnel, Route 10 and Center upstairs

Feature `e6e75e5f35b424194dd16793f0cdcc2b5440ea8a`; compiled `f3e2c9f47b16ca11d61e87cd3c458c45561cfa59`; ROM SHA-256 `77862d1cc607afd5cf22c6b71ab5ad4e973f33d8ee9bb31f6ea9f229a43bab4b`. CI 36630953884/job 109619737198: three native Flash and three Cut groups, seven owning host groups passed; related host checks total 19. Exact compiled map headers matched all 105 registered maps.

Both native cave floors, four reciprocal ladder pairs, both exterior mouths and Route 9/10 connection were traversed forward and back, dark and with native Flash. Flash retained all four unrelated moves and party bytes. Outdoors resets the native darkness state. Native Escape Rope returned safely without consumption. Six natural encounters across both floors matched authored species/level bounds; this small sample is not statistical proof of rare rates. Twenty-one native first trainer rosters and positions remain intact; 108 ordinary rematch trainers are registered so far. Five visible and five hidden pickups have unique receipts; full-bag retry/once and blackout to the new Route 10 Center passed.

All six supported Center upstairs floors passed both stairs, ordinary battery Continue upstairs, three presentation-only attendants and return/healing. The old closed-stair battery fixture now opens safely. Aron/Geodude scene passed day/night, first/repeat, no Gear, photo No/Yes, follower off/large, card/note metadata and cold Continue. Route 10 professor call delivered once with cold/reentry checks. No personal hardware save was used.

A suspected missing player in an enlarged Flash preview was investigated without changing game code: exact before/after sprite tiles and palette matched, and all 180 consecutive native video frames retained the same 78 red player pixels. Original 240x160 frames visibly retain the player. The preview alone was not reliable evidence of a game defect. Earlier traversal failures were fixture route/menu selection errors; corrected component runs and their logs are included, with no claim that the initial aggregate driver passed. Evidence `task38-rock-tunnel-evidence.zip`, SHA-256 `9609a0f8a8a2b9ad1aef7a36c46580502d124bc175a7d47338790f08af64d591`. Full chapter and personal-save/hardware acceptance remain Task 41.

### Task 39: Lavender town and investigation scenes

Feature `3d84185b4047addfc9d3e138d5f9923549430156`; compiled `c64343a0d50786f77ed894078520bb0cc8132aed`; ROM SHA-256 `39ec88f24ff3fb88e32672a93dffb2c49114dfab2692e733005cdfe882af1ed6`. CI 36638722852/job 109645625786: five native research groups, six migration/state groups and six owning host groups passed. Related host checks total 19.

Seven append-only maps add the town and five buildings, including the Center upstairs. All five doors, the Route10 connection and both Center stairs were exercised in both directions. Healing, upstairs ordinary battery Continue, all three non-networking attendants, Mart and Trainer Services, and native name-rater party/cancel were checked. Existing heal entries retain their original bytes; Lavender appends its own checkpoint.

Misdreavus was checked day/night with large, small and disabled followers, from all four sides, after opening/closing menus, after ordinary battery Continue, without Gear, and through declined/revisited/accepted photos. Rival conversation and the single Rocket trio cameo complete once; partner data remains unchanged during each stationary scene. The queued professor update persists once. The photo card and four metadata fields were inspected after cold Continue and reopening. These are synthetic software checks, not the user's exact hardware-save acceptance.

Exact-ROM testing caught a real decline defect: native `removeobject` sets its object flag, which also represented the photo receipt. A regression first failed with native removal semantics; the scene now clears only an unearned receipt after removal while preserving accepted photos. The corrected ROM passed both No/revisit and Yes/persistence. No engine behavior was globally changed. Other initial driver failures were documented fixture assumptions: offscreen objects load on approach, native walking can increase friendship, and a Mart counter must be approached from its walkable side. Byte-for-byte party assertions remain immediately before/after stationary scenes.

Evidence archive `task39-lavender-evidence.zip`, SHA-256 `65abee81c8cfc042d414d488babacff77821ca432fc9b83f268dfb78393a9f18`. Tower access is intentionally connected by Task40; west/south future routes retain natural barriers. Full chapter, exact personal-save and RG40XX H acceptance remain pending.

### Task 40: First Tower sequence and unresolved ghost endpoint

Feature `d929321fa6f0e9d4b739eb0a5a380ce76c4ca506`; compiled `fd984216d432ee9aca5c1b3d4ac3b77b43086e6d`; ROM SHA-256 `2d7e1cb10b771a9d2afbb7214383df2aa311fd5f0213786b6aeb7c682bd944a3`. CI 36641128030/job 109653392425: two Tower classifier groups, five native ghost groups, nine rematch groups and six owning host groups passed; related host total 25 passed.

Six native-layout Tower floors were appended, retaining original first trainer teams, Kanto encounter weights, mourning dialogue, healing zone and local pickups. All 13 trainers completed actual first battles. Four natural encounters (one on each encounter floor) matched native species/level tables and remained unidentified without Scope; these samples do not establish encounter frequencies. An actual Master Ball throw failed to capture the barrier ghost, consumed the ball, and allowed a safe retreat. Native battle tests cover unidentified/identified introductions, prohibited moves and both capture cases.

Exact-ROM traversal walked from the town entrance up all six floors and back to town. Both barrier lanes were exercised twice with small, large and disabled followers. Ordinary battery Continue before and after the endpoint, an out-of-scope debug Scope, Escape Rope return, and a real battle loss were checked. Loss returns to the newly visited Lavender Center, heals and does not falsely award completion. The debug Scope remains blocked and does not reveal the unfinished upper floor. No seventh-floor warp, Fuji rescue, Scope source or resolution reward is included. The completion receipt is one-time; repeat visits retain the unresolved Celadon lead.

The purified zone restores HP/status/PP and works again after leaving/reentering. All eight visible pickups and the hidden mushroom are one-time; a full bag can retry the Elixir. A Rocket's optional record dialogue adds uncertainty without a new research receipt or second Jessie/James cameo. The ROM visibly renders native Tower fog, directional stairs, trainers and ghost battle presentation.

The classifier first failed on cloned TH floors; the repair adds only those floors under THREE_HORIZONS and retains the native seven-floor predicate. Emulator-driver corrections were not game fixes: directional stairs trigger sideways from their actual warp tile; floors alternate stair indices; navigation must avoid scripted barrier coordinates; one-member battle fixtures avoid the native switch prompt; the hidden item must be approached from walkable (8,3), not a gravestone. Initial failing driver logs are retained and are not represented as passing cases.

Evidence archive `task40-tower-evidence.zip`, SHA-256 `bbdce2deb8229685ab61d12acf917f8c8a6ecd0e0091adcdff4bfd18b0bc644a`. Remaining whole-chapter, save-layout, upstream, exact personal-save and RG40XX H gates belong to Task41.

## Task 41 integration gate — 2026-09-29 (in progress)

Feature under integration: `3a7726c7ac5b808e5a79c1ee735f4b61bc319c93`.
Three Horizons CI: 36644694634; upstream CI: 36644694716. These are
integration candidates, not a packaged accepted release.

The first full local host run ran 152 tests and reported five failures. One
was a real upstream-layout leak: the new `LAYOUT_TH13_` forest layout was not
excluded by the generator's older `LAYOUT_TH_` check. All three generator
paths now share a project-layout predicate. The historical native-layout and
map-index hashes were retained. The CI host gate passes with the freshly
compiled generator. The other failures were expectations explicitly superseded
by approved completed work: the full 121 rematches through trainer156, a photo
receipt after accepting the forest scene, and Earth Power40 replacing
Typhlosion's Earthquake40. All unrelated assertions remain.

A new native migration test first failed on the prior implementation:
CI36643484371/job109660956042, `three_horizons_state.c:221`, EXPECT_EQ(1,0).
Old unused defeat bits for newly assigned trainer IDs104–156 could look like
completed first battles. Migration now clears exactly this new range only
when upgrading to P13. Every pre-existing trainer win remains authoritative;
subsequent P13 loads preserve the entire history. This uses existing flag
storage and does not expand a save block or put trainer IDs in rematch bytes.
Native GREEN evidence is still pending the integration run.

The upstream strict compiler also caught deprecated party-array access in the
new cross-mode Tower test. The test now uses `gParties[B_TRAINER_PLAYER]`.
No warning policy, assertion or failing test was disabled.

The final mutation gate runs the three required P13 owners: old Cut temporary
receipt behavior, the old clock version write, and the old trainer RUN/SELECT
configuration. It restores original bytes in `finally`, requires each owning
assertion to fail (a compiler error is not accepted), then requires a passing
restored test. Older mutation recipes remain available through the explicit
`legacy_controls` option; positive regressions from every release remain in
the full run. This follows the approved instruction not to repeat every
historical mutation unnecessarily.

### Bible §35 acceptance accounting

| Required area | Evidence already recorded | Final gate status |
|---|---|---|
| 24 P12 repairs | Tasks1–26 exact-ROM before/after and focused tests; A–X checklist in guide | Final whole-route repeat pending |
| Exact P12 battery migration | Native payload preservation; synthetic P12 batteries | Owner's exact post-Surge file pending; older Cerulean/P11 backup excluded |
| Gear/log/photos/calls persistence and no duplicates | Tasks30–32,36–39 scenes/menu/cold Continue/No/Yes/retry | Final candidate repeat pending |
| Flash/Diglett connection/Skarmory/Forest clearing | Tasks33–36 doors, full-moveset eligibility, trade and scene evidence | Final candidate route pending |
| Route9/Route10/Rock Tunnel | Tasks37–38 first battles/ladder traversal/Flash/scene/items/blackout | Final candidate route pending |
| Lavender/Misdreavus/rival/Rocket cameo | Task39 one-time dialogue, photo decline/revisit and six doors | Final candidate route pending |
| Tower unresolved endpoint | Task40 all six floors, 13 first battles, both ghost lanes, failure/capture/Run/cold/item checks | Final candidate route pending |
| Vs. Seeker | Task27 focused runtime/native; Task40 total121 trainer records | Full native gate pending; readiness resets never alter established defeat flags |
| SELECT/Run | Task22–23 native and actual battle checks | Full native/negative controls pending |
| Cut follower/non-follower/reload | Tasks18,34,36 exact-ROM matrix | Full native/negative controls pending |
| Ship departure/old inside-save recovery | Task25 exact-ROM and P12 battery fixtures | Final candidate migration matrix pending |
| Gyarados/Typhlosion/evolutions | Task29 native tests, actual learning/evolution/Bag item/cold Continue | Effective release macros/save sizes rechecked at integration |
| Native Emerald/FireRed/LeafGreen | Isolated CI builds, immutable native map hashes | Matrix in progress; strict Tower-test compile issue recorded above |
| Full Three Horizons/save regression | All focused gates complete | Integration in progress |
| Full mGBA playthrough | Focused fixtures are not a full uninterrupted new game | Both final routes pending |
| RG40XX H/VBA-Next P13 | No acceptance claim | Separate owner hardware pass |
| Exact revisions/ROM/checksum/export | Each development archive records its own revision/hash | Final packaging waits for all release gates |

The release package must not be marked accepted while any required row above
is pending. A real hardware battery, synthetic fixtures, emulator states and
user-reported P12 hardware success are distinct evidence classes.
