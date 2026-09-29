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
Implementation checkpoint ccbc848a1f6304b2965ca73151087cf563b54079 is undergoing
native checks; emulator acceptance remains at the systems integration gate.

The 53 ordinary trainers on upcoming approved maps remain required additions to
the same ROM registry. The chapter-wide target remains 121; the current shipped
map count of 68 is not a scope reduction. Integration must re-audit final maps.
The exact post-Surge RG40XX H P12 battery save is still to be supplied by the user;
the older Cerulean/P11-marked save must not satisfy personal-save acceptance.
