# Research Navigator isolated review — 2026-10-01

This review continues RC2 while the owner tests the unchanged release. It is not RG40XX H acceptance or authorization to integrate.

## Source and approval

- Original branch: `feature/opening-demo`, revision `1754893d42d1f41c5b31488cfc952856d8c4d459` (documentation after compiled RC2 `a5d1ac19d0f3c8fb2dd39544a93401367f4e9b87`).
- Isolated branch: `review/research-navigator-2026-10-01`.
- Owner believes the handheld ROM is `pokemon-three-horizons-playtest-13-1-road-to-lavender`; its actual handheld bytes have not been hashed here.
- Original packaged ROM: SHA-256 `c08a31c6ac0c3f5fff5a867b9a98b9ee6d246cf39f16c17d748b431a29a003f2`.
- Original post-Surge PT12 raw battery artifact: `pokemon-three-horizons-playtest-12-rocket-art.gba.eps`, 131072 bytes, SHA-256 `be9bbc4722188ce11ad86b6bcc34a89539a4572403cfade3330da75f1ccbadca`.
- Approved graphical Gear and rematch context request: owner turn `0e209041-7424-4d9e-858a-4cf4736c854b` in **Pokémon Three Horizons CHAT Discussion**, plus the current instruction to finish approved work in isolation.

Research Gear retains exactly **Research Log, Field Photos, Calls**. Existing observations, authored photographs, received professor reports and eligibility remain authoritative. No additional evolution thresholds, Snorlax boundary rules, story content, gender picker or later-generation Dex expansion were inferred.

## Findings and verification ledger

| Priority | Finding | Classification | Evidence / disposition |
| --- | --- | --- | --- |
| High if repeated | Full-party Ekans capture reportedly replaces displayed party with Gyarados, then black screen with audio on VBA-Next | Suspected, unreproduced | Fresh original-RC2 mGBA runs pass swap-first, swap-third and cancellation to PC, including real authored encounters, Dex registration, native save and cold Continue. Capture code remains unchanged. |
| Medium | Windows map generation exceeds process argument limit | Confirmed build defect | Old full-map invocation fails. Response-file regression fails against old tool and passes against repaired tool for Emerald, FireRed and Three Horizons with identical map output. |
| Medium | Windows compiler rejects size_t formatted as long in preproc | Confirmed build defect | `%ld` is wrong on LLP64; `%zu` passes fresh host compilation. No warning/assertion suppression. |
| Low | A response-file input list could retain a deleted map | Confirmed during fresh review, repaired | Actual Make-rule regression RED → GREEN; removed maps disappear and unchanged lists retain their timestamp. |
| Low | Ready rematches repeat a first-meeting greeting | Confirmed, repaired | Original-RC2 Route 6 Elijah reproduces the first-meeting text. Native regression RED → GREEN, including first-battle pointers, both approaching-trainer slots and defeat history. Actual candidate screenshot shows the returning-opponent greeting. |
| Approved unfinished feature | Text-only Gear needs illustrated device presentation | Implemented | Three illustrated module cards, visible selection, archive counters and consistent subsections. Original rendered selection regression RED → candidate GREEN; all eleven observations, ten photo sets and three contacts navigated in mGBA. |
| Medium | New response-file event-constant path indexed a missing directory separator | Found by fresh Astra review, repaired before handoff | Checked-libstdc++ regression aborts on `@.mapjson-inputs` before the fix; direct/response output equality passes in all three map modes afterward. |

Fresh source checks: **170/170 pass**. Native Three Horizons tests: **222/222 groups pass**, including configured partners, shiny/IV/EV/nature/ability behavior, captures, research, rematches and existing chapter regressions. Save-layout checks: **4/4 pass** (SaveBlock1 15568, SaveBlock2 3884, SaveBlock3 4, PokémonStorage 34144 bytes).

Failures were investigated, not waived: the initial missing map executable caused eight host errors; a built-tree ownership check accidentally scanned generated object templates and now distinguishes those from authored scripts while retaining object-ownership checks; three native cry tests were initially run in headless mode, which deliberately disables cries. The complete native suite was rerun with normal audio. Strict skip/failure handling stayed enabled. The Windows serial mGBA runner exercises the repository's real test ELF and assertions; Linux's parallel process launcher is not available here.

The fresh Astra reviewer found one Important issue, corrected with the checked-string regression above, and no Critical or Minor findings. Historical release results are not counted as fresh evidence.

## Exact candidate and fresh acceptance

- Feature/source revision and final compiled revision: `ea393ce3174751c50206e85101b9682c5cfbb0c7`. A later handoff commit changes documentation only.
- ROM: `outputs/research-navigator-review-2026-10-01/pokemon-three-horizons-playtest-13-1-navigator-review.gba`.
- ROM SHA-256: `537c3ca0185bc34c0e0bc36cdebcae784984cc173ba8ff2fead5f28720537837`; 33,554,432 bytes.
- Fresh reviewed production build: PASS. Its bytes match the copied ROM used for every final emulator case; this was checked after the post-review build-tool fix.
- Upstream `THREE_HORIZONS=0` Emerald, FireRed, LeafGreen builds: **all three PASS**; exit codes and ROM hashes are in the package manifest and logs. These are compilation compatibility checks, not complete upstream gameplay acceptance.

| Practical mGBA check | Fresh result | Limits / method |
| --- | --- | --- |
| Ordinary boot, New Game, default Bulbasaur, free lab Gear, Oak-only Calls | PASS | Blank battery; normal controller flow, no story or location fixtures |
| First rival battle, field return, map transition, native Save, cold Continue | PASS | Natural new-game path |
| Illustrated cards, input selection and wrap | PASS | Real renderer/controller; original RC2 visual regression fails, candidate passes |
| All 11 observations/notes, 10 photo fronts/details/notes, three latest Calls | PASS | Disposable all-records fixture; each page visually inspected; existing latest-report policy retained |
| All three empty modules, A on empty list, B return; archive pagination and wrap | PASS | Disposable eligibility fixtures; no invalid entry or clipped text observed |
| Gear browsing preserves party, all boxes, items, money and flags; native Save/cold Continue | PASS | Exact payload comparisons before/after populated and empty browsing |
| Ready rematch greeting | PASS | Route 6 Elijah fixture plus actual Vs. Seeker/input; original RC2 first-meeting text reproduced; final returning-opponent text captured |
| Six-distinct-species Ekans catch, replace first / third / cancel to PC | PASS, all three | Real authored Route 11 encounters; disposable relocation, cleared Ekans Dex receipt and supplied Master Balls; observed changed slots 0 / 2 / none |
| Capture identity, displaced Pokémon, party/storage persistence | PASS, all three | Species/personality/IVs/EVs/nature/ability/nickname/item checks; real native Save and cold Continue |
| Actual owner post-Surge PT12 raw battery → candidate; native Save and second cold Continue | PASS | Unmodified source artifact, no location/progression fixtures; working copies only |

Practical smoke tests use the local mGBA libretro core `0.11-212-7a12d6d`, with scripted controller input and visual inspection of native frames. This is distinct from the owner's VBA-Next handheld core and the mGBA 0.10.5 desktop version shown in earlier screenshots. Core identity/hash is retained in `emulator-core.json`; no claim of testing those other core versions is made.

The personal-save comparison includes raw party and every PC box, decoded identity/options, bag, money, all flags (including badges/receipts), progression variables, map/location, player identity and Dex seen/caught state. The earlier Cerulean backup is not used as acceptance evidence. During comparison, two lottery-number words (`0x404B/C`) differed between independent boots. The unchanged original RC2 reproduces this: daily events seed lottery numbers from `Random()`. Only those two words are normalized for independent-boot cross-ROM comparison; both remain exact in the candidate's native-save/second-Continue comparison. Clock anchors/display values legitimately advance; the packed migration-version bits were separately checked and remain equal. The failed comparison log is preserved rather than erased.

Fresh native tests cover all nine configured starters, shiny on/off, all natures, IV bounds, per-stat/total EV limits, legal ability selection including Hidden Ability, rejection without story advancement, and once-only starting PC training supplies. Production creation still requests random gender; there is no approved gender picker. The natural emulator run uses the default partner; all nine selector/configuration combinations still belong on the owner's manual checklist rather than being described as nine manual playthroughs.

Test provenance: the native test ELF was compiled at `9954a28f74e7a7fa8e3b4fba892d5b0590390904` and the complete native suite was rerun after review. The only subsequent source changes through `ea393ce3174751c50206e85101b9682c5cfbb0c7` are the host `mapjson` bounds repair and its host regression; runtime and native-test sources are identical. Native ROM checksums are retained in `native/reviewed-test-source.json`. Production was freshly rebuilt at the final revision and checked byte-for-byte against the emulator-tested candidate.

Existing warnings were not suppressed: unchanged uses of deprecated `gPlayerPartyPtr`, the unused `GetGameProgressFlags` and `Task_NewGameBirchSpeech_BoyOrGirl` helpers, upstream PNG background metadata, and the bare-metal ELF RWX-segment warning. Build logs retain their full text. No newly changed production source emits a new warning in the reviewed build.

Review rulings: preserve approved Gear content/navigation; leave the unreproduced hardware capture report open; exclude unapproved story/evolution/gender expansion; distinguish generated map templates from authored Cut scripts while retaining map-object checks; use serial Windows mGBA with the same assertions and strict skip policy; retain private evidence/workspace at the owner's request. Consequences are explicit: the hardware issue and unapproved polish/features remain unresolved, and compilation/mGBA evidence does not certify RG40XX H behavior. The private ledger records each ruling and the original failure evidence.

## Changes and scope

- `src/three_horizons_research_menu.c`: graphical presentation required by the owner's Gear request. Existing photo assets, data APIs, input behavior, eligibility, receipt flags and cleanup remain unchanged.
- `src/battle_setup.c`: ready ordinary rematches receive returning-opponent dialogue, as requested; original encounters and bosses retain their existing text.
- `tools/preproc/c_file.cpp`, `tools/mapjson/mapjson.cpp`, `map_data_rules.mk`: demonstrated Windows build repairs, including bounded response-file handling and list updates after map removal.
- Native and host regressions cover the repaired behavior. No save structure, encounter table, partner configuration, capture logic or story implementation was changed.

Open reports: the exact handheld ROM hash and repeatable VBA-Next capture failure remain unavailable. The Route 2 aide's dialogue-order comment and Forest clearing half-tree appearance remain polish notes without an additional implemented design in this review. Stone/item rematch evolution tiers and Route 11/Snorlax boundary changes remain unapproved ideas. Hardware acceptance remains the owner's separate test.

Evidence is retained locally under `.superpowers/sdd/2026-10-01-research-navigator-review/`. Baseline hashes/status are in `baseline.json`; `acceptance/` contains original-RC2 mGBA screenshots, captured RAM and disposable battery copies. Any RAM fixtures are explicitly identified in result JSON files. No owner save is edited.

## Manual play-test checklist

Record the ROM filename/hash, core/version, save origin, exact input sequence and expected/actual result for a failure. Keep a battery backup before testing a separately named candidate. Use ordinary in-game saves and cold Continue; old emulator states do not establish migration or startup compatibility.

### Continue from a copy of the migrated save

- [ ] Confirm map/location, money, badges, party order, nicknames, held items, IVs/EVs, nature and abilities before opening Gear.
- [ ] Inspect representative occupied PC boxes and Dex seen/caught entries; verify previously earned fossils, trade and Rocket/story receipts remain intact.
- [ ] Open Gear, return to field, enter/exit a building and battle once. Check follower and field colors at day and night.
- [ ] Save in-game, close the emulator/core fully, reopen and Continue. Recheck the same party, boxes, rewards and Gear records.

### Gear presentation and controls

- [ ] Home shows exactly three illustrated cards: Research Log, Field Photos, Calls; Up/Down highlight the corresponding card and wrap first/last.
- [ ] A opens the highlighted module; B backs out one level, then returns to field. Reopen repeatedly with no freeze, misplaced follower or progressive darkening.
- [ ] Empty lists show a readable empty message. A does not open a nonexistent entry; B returns safely.
- [ ] With more than four observations/photos, cross each page boundary in both directions and wrap last/first. Selection, number and displayed record agree.
- [ ] Read observations and professor notes with A/Left/Right; check complete, unclipped text and unchanged record eligibility.
- [ ] View every owned photo, its details and professor note. The photograph and its subjects remain intact; switch pages repeatedly and return to field.
- [ ] Calls show only introduced professors, and each contact shows its latest received report. Browsing must not award observations/photos or deliver an unreceived call.
- [ ] Save/cold Continue after browsing. Photographs, observations and reports match the pre-browse state.

### Fresh New Game and custom partner options

- [ ] Start a separately backed-up blank battery through the normal New Game menu. Test a default configuration and a customized configuration.
- [ ] Inspect starting PC items and withdraw them; Exp. Share is present. Save/Continue does not duplicate starting supplies.
- [ ] Choose a partner from each regional selector across separate disposable runs. Check all nine choices; cancel/back out before confirming, then confirm exactly once.
- [ ] Check selected nature, IVs, EV allocation and legal ability against summary. Test IV 0/31, EV 0/252 and the total EV cap; invalid settings must not create a partner or advance the story.
- [ ] Enable guaranteed shiny and verify both battle appearance and summary marker. Confirm the normal choice remains available. Gender currently follows normal creation; no gender selector is added by this review.
- [ ] Oak grants Gear during the approved lab flow; Oak is the only initial contact and unobserved photos remain absent.
- [ ] Complete the first rival battle, inspect rewards, change maps, save and cold Continue. Partner identity/options and rival continuity survive.

### Encounters and full-party capture

- [ ] Carry six visibly different species, with distinctive nicknames/held items. Record their summaries and the first free PC slot.
- [ ] Catch a previously unregistered Ekans on Route 11. Read its Dex entry, decline naming, choose Yes for party replacement, replace the first slot. Check all six party entries; verify the displaced Pokémon in PC.
- [ ] Repeat with a middle slot and a new species/Dex registration. Check the actual chosen slot, caught identity and displaced Pokémon's IVs/EVs/nature/ability/nickname/item.
- [ ] At the swap list press B to cancel replacement; the captured Pokémon goes to PC and party identities remain unchanged.
- [ ] Test direct-to-PC No, a previously caught species, and a max-length nickname. Capture experience/EV awards may legitimately change party stats.
- [ ] After each case return to field, open party/PC, save in-game and cold Continue. If the Gyarados/black-screen symptom returns, preserve the pre-capture battery and exact input/core details for reproduction.
- [ ] Spot-check approved encounter lists by location/time and legal normal/Hidden Abilities. A small sample does not establish a 10% Hidden Ability rate; use a larger recorded sample for distribution testing.

### Ordinary rematches

- [ ] Fight an ordinary trainer for the first time: original intro, party and rewards remain unchanged.
- [ ] Return after victory and use Vs. Seeker; a ready trainer greets you as a returning opponent. Win/lose and verify permanent defeat history remains intact.
- [ ] Use Vs. Seeker immediately again without charging. Check appropriate scaling and authored legal parties for low/high player levels.
- [ ] Leave the map, cancel readiness, blackout and cold Continue. Temporary readiness clears, while first-victory/story flags remain.
- [ ] Bosses, leaders, scripted rivals and Jessie/James remain excluded from ordinary rematches.

## Resume note

Continue from the isolated branch and its plan at `docs/superpowers/plans/2026-10-01-research-navigator-review.md`. Local portable MSYS2/ARM tools are in `C:/Users/phabe/Documents/Codex/pt13-review-tools-20261001`; they are not a system installation. Do not modify the original worktree, ROM or owner battery. Keep implementation commits local and outputs separately named until explicit owner integration approval. The focused review is complete: production and all three compatibility builds, 170 host checks, 222 native groups, four layout checks and the documented candidate emulator gates passed. The fresh whole-branch review finding is repaired. Next action is owner play-testing and a separate explicit integration decision; do not repeat unchanged automated gates merely because the model changes. Reproduce the remaining VBA-Next capture report from a pre-capture battery if it recurs. The last generated map headers are from the LeafGreen compatibility build; the documented THREE_HORIZONS=1 build regenerates its own mode before future work. Private scripts, logs and working battery copies remain in the evidence folder; never substitute them for the owner's current handheld progress.

Original protection check: `feature/opening-demo` remains at `1754893d42d1f41c5b31488cfc952856d8c4d459` with no tracked modifications. The original ROM, original release ZIP and actual post-Surge PT12 EPS hashes match the recorded baseline. All review source commits are local, and unrelated untracked files/private evidence are retained.
