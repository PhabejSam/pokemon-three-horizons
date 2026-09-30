# Playtest 9 Cerulean Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking. The user has selected native execution; preserve that selection.

**Goal:** Repair the reported Playtest 8 problems and deliver a save-compatible journey through Mt. Moon, Misty and the bridge rival.

**Architecture:** Keep project features behind `THREE_HORIZONS`, reuse native Kanto layouts and the existing partner editor, and append maps without shifting saved identifiers. Implement three independently testable stages: reliability; opening/options/rewards; connected chapter. These share one integration plan because persistent reward, rival and map state must agree across stages.

**Tech Stack:** pokeemerald-expansion C, event assembly, JSON maps/encounters, Python host checks, native engine tests, GNU Make/ARM tools and mGBA.

**Spec:** [Approved design](../specs/2026-09-24-playtest9-cerulean-design.md).

**Status:** Implementation plan prepared for review. No tasks below are implemented by this document. Baseline commit: `b3916b8dd2096e2460ee9baf29c70deadd9c38a7`.

## Global Constraints

- Preserve existing in-game saves and the standard upstream build modes.
- Earlier ROMs and saves remain untouched.
- Preserve map indices and save structures; append new map IDs and audit spare event flags/vars before allocating them.
- Do not repurpose existing reward state.
- Existing saves retain their already-selected rival partner.
- Ship only after the capture/nickname error is reproduced and repaired, or explicitly report it as unresolved rather than claiming this playtest fixes it.
- Keep real-time daily rewards and timers separate from the fast display clock.
- Do not claim handheld compatibility until the user confirms that playthrough.
- Preserve normal poison behavior, reusable TMs, successful evolution/cancellation, title scenery, training kit and legendary customization.
- No merge, branch-protection change, new save layout, wholesale asset redraw or expansion beyond the approved chapter.

## Review Focus

1. Capture experience causes evolution before nickname/delivery: party index, held item and callbacks must still describe the caught opponent (Task 1).
2. An old Brock save has nonzero unused event bytes: new settings need bounded defaults and must not overwrite known flags (Tasks 3, 6, 7).
3. Full party and last/full PC slot during a paid or badge gift: exactly one delivery, no money or reward loss on failure (Task 5).
4. Clock rollback, mode changes and suspend: visual time remains coherent while daily rewards retain real elapsed time (Task 6).
5. Player loses a new rival/Gym battle or returns through a different cave exit: encounters remain retryable, return warps and recovery remain valid (Tasks 8–11).

## Execution and verification conventions

Work in the existing isolated `work/three-horizons-opening` checkout on `feature/opening-demo`. Inspect its status and preserve unrelated edits. Do not create another worktree or replay old map-generation helpers. Read the approved spec along with this plan.

Build/test commands below run from the repository in the established Linux build environment or existing GitHub workflows. Host Python checks can also run with the bundled Windows Python. Do not claim a Linux command ran locally if only CI executed it.

```sh
python3 -m unittest discover -s tools/three_horizons/tests -v
make THREE_HORIZONS=1 check TESTS="Three Horizons" -j2
make THREE_HORIZONS=1 check TESTS="test/save.c" -j2
make THREE_HORIZONS=1 -j2 -O all
python3 tools/three_horizons/check_running_elf.py pokemon-three-horizons.elf
```

For every implementation task: add the specified behavioral regression, demonstrate its relevant failure before the fix, implement the change, rerun that focused test, and inspect the diff. Do not add redundant tests for dialogue wording. Commit each independently verified task using explicit paths; do not stage unrelated files. A diagnostic investigation that cannot reproduce the report must record that outcome instead of inventing a red/green claim.

## Stage A — reliability

### Task 1: Reproduce and repair caught-Pokémon delivery

**Files:** inspect/modify `src/battle_script_commands.c`, `src/battle_main.c`, `src/naming_screen.c`, `src/three_horizons_evolution.c`; create `test/three_horizons_capture_lifecycle.c` and `docs/three_horizons/CAPTURE_DIAGNOSTIC.md`; extend `test/three_horizons_capture_ui.c` only where its real callback harness is reusable.

**Interfaces:** Keep native `Cmd_trygivecaughtmonnick`, `Cmd_givecaughtmon` and `GiveCapturedMonToPlayer` contracts. No public repair API is justified until a cause is reproduced.

- [ ] Record baseline ELF/source hash and reproduce from a copied save or a fresh game. At `Cmd_givecaughtmon`, log caught battler, `gBattlerPartyIndexes`, original/current held item and the `gBattleStruct` address. Watch the original-item field across Dex, naming and catch-triggered evolution. Never log whole save contents.
- [ ] Exercise Rattata/Pidgey/Weedle/Caterpie; no name/short name/maximum name; no held item/berry/nonberry; party vacancy/full party/last PC slot; experience evolution on/off; repeat catches. Include the release-confirmation path separately and inspect PC contents immediately after one accepted release.
- [ ] Turn the reproducing sequence into a native callback regression. Use real naming initialization/input/return and battle delivery, not merely direct `GiveCapturedMonToPlayer` calls. Assert these invariants after delivery:

```c
EXPECT_EQ(GetMonData(received, MON_DATA_SPECIES), expectedSpecies);
EXPECT_EQ(GetMonData(received, MON_DATA_HELD_ITEM), expectedItem);
EXPECT_EQ(GetMonData(received, MON_DATA_PERSONALITY), originalPersonality);
EXPECT_EQ(GetMonData(received, MON_DATA_OT_ID), originalOtId);
EXPECT_EQ(GetMonData(received, MON_DATA_POKEBALL), originalBall);
EXPECT_EQ(StringCompare(receivedNickname, expectedNickname), 0);
```

`received`, expected values and nickname buffers are captured by the fixture before and after the actual sequence. Also verify one occupied destination and no second copy. Inspect the test runner's existing battle-input facilities before choosing its command-driving fixture; add a fixture adapter only if those facilities cannot reach naming.

- [ ] Fix the first demonstrated invalid write or stale identity/callback. Keep the invalid-item assertion. Do not replace bad values with `ITEM_NONE`, remove item restoration or blame the emulator BIOS without evidence.
- [ ] Run the focused capture regression and existing capture/evolution tests. Record reproduction steps and the causal fix, or explicitly document that the report remains unresolved. An unresolved capture report remains a visible release limitation, not an invisible waiver.
- [ ] Commit the verified repair and diagnostic report together.

### Task 2: Healing followers, facing and Combusken inspection

**Files:** `data/scripts/three_horizons/journey.inc`, `town.inc`, `src/three_horizons.c`, `graphics/pokemon/combusken/overworld.png`, `overworldf.png`, `overworld_normal.pal`, `overworld_shiny.pal`; create `test/three_horizons_followers.c`; extend `tools/three_horizons/tests/test_rival_scenes.py`.

**Interfaces:** Existing `TH_RefreshFollower(void)` remains the restoration hook. Hiding during healing must not change `VAR_TH_FOLLOWER_OFF`.

- [ ] Add a native test with follower ON, a first-slot Pokémon, and a healing sequence; assert hidden during `FLDEFF_POKECENTER_HEAL` and restored afterward. Repeat with follower OFF, an empty party, and blackout recovery. Preserve the saved option in every branch.
- [ ] Bracket the existing healing effect with transient hide/refresh, following the existing follower command semantics:

```asm
    hidefollower TRUE
    dofieldeffect FLDEFF_POKECENTER_HEAL
    waitfieldeffect FLDEFF_POKECENTER_HEAL
    special HealPlayerParty
    special TH_RefreshFollower
```

Ensure native hide state is cleared before refreshing if `hidefollower` stores a separate latch. Exercise recovery and early exit as well as normal completion.
- [ ] Walk each automatic rival approach on the map, wait for movement completion, then explicitly face both participants before the first message. Test all seven outfits and interaction from either approach side. Retain existing run frames.
- [ ] Inspect Combusken sheets at native scale in each direction with both palettes and female sheet. Compare frames to graphics dimensions and tile allocation. Repair only a demonstrated indexing/palette/transparency defect; if no defect is reproducible, request the original screenshot and record the limitation. Use image editing tools only if an actual art edit is required.
- [ ] Run follower and rival-path checks; visually verify healing with 1 and 6 party members. Commit this repair separately from new content.

## Stage B — opening, options and partners

### Task 3: Allocate save-safe state and chapter identities

**Files:** `include/constants/three_horizons.h`, `include/constants/opponents.h`, `src/three_horizons.c`; create `tools/three_horizons/state_manifest.json`, `tools/three_horizons/tests/test_state_allocations.py`, `test/three_horizons_state.c`.

**Interfaces:** New symbolic variables: `VAR_TH_BROCK_GIFT`, `VAR_TH_MISTY_GIFT`, `VAR_TH_SHINY_RATE`, `VAR_TH_CLOCK_MODE`, `VAR_TH_CLOCK_REAL_LO`, `VAR_TH_CLOCK_REAL_HI`, `VAR_TH_CLOCK_DISPLAY_LO`, `VAR_TH_CLOCK_DISPLAY_HI`. New flags: lab intro, Magikarp purchase, Misty TM, chapter completion. Use native clock-set and badge flags rather than duplicating them.

- [ ] Audit candidate unused variables `0x409D`, `0x40A1`, `0x40A8`, `0x40B8`, `0x40BB`, `0x40DB`, `0x40DC`, `0x40E5` across scripts and C, including alternate symbolic aliases. Assign the eight variables in the order above only if the audit confirms no runtime use. Record each address, prior name and references in the manifest. Do not use the already allocated `0x40F7–0x40FF` block.
- [ ] Audit unused flags, pick actual free slots, and record ownership in the same manifest. Preserve the exact existing `TH_*` addresses and all 17 map IDs. Flag values equal to zero in imported FRLG aliases are not usable persistent state.
- [ ] Reserve TH-only trainer replacement IDs from unreachable Hoenn entries starting at 8; existing IDs 1–7 and 855–863 stay unchanged. Record every new trainer and replacement in the manifest. Do not increase `MAX_TRAINERS_COUNT` or shift trainer flags.
- [ ] Add a host test checking numeric allocation uniqueness, no use of zero, no overlap with existing TH state and unchanged baseline map indices. Add native initialization tests for fresh games and old saves: invalid new option values select defaults; old rival and gift state are not rerolled/cleared on load.

```c
VarSet(VAR_TH_SHINY_RATE, 0xFFFF);
EXPECT_EQ(TH_GetWildShinyThreshold(), 8);
VarSet(VAR_TH_RIVAL_PARTNER, SPECIES_MUDKIP);
/* Loading a legacy save does not call TH_InitNewGame. */
EXPECT_EQ(VarGet(VAR_TH_RIVAL_PARTNER), SPECIES_MUDKIP);
```

`TH_GetWildShinyThreshold` is defined by Task 7; keep that case with Task 7 until it exists. New-game initialization clears new state; no blanket clearing occurs when continuing a save.
- [ ] Run allocation checks and native save tests; commit the manifest and save-safe declarations.

### Task 4: Ability, nickname and persistent regional rival

**Files:** `include/three_horizons.h`, `src/three_horizons.c`, `src/three_horizons_partner.c`, `src/three_horizons_capture.c`, `src/main_menu.c`, `data/scripts/three_horizons/lab.inc`, `town.inc`; extend `test/three_horizons.c`, `test/three_horizons_capture.c`, `test/three_horizons_capture_ui.c`; create `test/three_horizons_partners.c`.

**Interfaces:** Add `u8 abilityNum` to transient `THPartnerOptions`, not a save structure. Add:

```c
u8 TH_GetAbilityChoices(u16 species, u8 slots[3]);
bool32 TH_PartnerOptionsValidForSpecies(u16 species,
    const struct THPartnerOptions *options);
u16 TH_GetRivalCandidate(u16 playerSpecies, u8 choice);
```

- [ ] Add ability tests for one/two normal slots, Hidden Ability, duplicate ability IDs and unavailable slots. `TH_GetAbilityChoices` returns canonical slot indexes with duplicate names omitted; validation accepts a real supported slot and rejects empty/out-of-range slots. Preserve a captured Pokémon's existing valid slot even if its name duplicates another slot.
- [ ] Initialize/read/apply `abilityNum` in every editor entry/confirm/cancel path. Show ability names, update the preview, preserve personality/OT/ball/HP damage when editing a legendary, and add the ability row without overlapping the Confirm controls. Existing IV0–31 and EV252/510 rules remain.
- [ ] Add a nickname callback after confirming a newly created partner. Hold the pending Pokémon in allocated transient state until naming returns; cancellation retains the species name; commit to party/PC exactly once. Do not reopen the legacy capture editor for an ordinary gift. Failed allocation/delivery leaves reward state unchanged and returns control.
- [ ] Define starter ordering as Grass/Fire/Water within Kanto/Johto/Hoenn. The stronger type mapping is Grass→Fire, Fire→Water, Water→Grass. Candidate region ordering is ascending region index, excluding the player's region:

```c
static const u16 starters[3][3] = {
    {SPECIES_BULBASAUR, SPECIES_CHARMANDER, SPECIES_SQUIRTLE},
    {SPECIES_CHIKORITA, SPECIES_CYNDAQUIL, SPECIES_TOTODILE},
    {SPECIES_TREECKO, SPECIES_TORCHIC, SPECIES_MUDKIP},
};
/* After looking up region/type and validating choice < 2: */
u8 otherRegion = choice >= region ? choice + 1 : choice;
return starters[otherRegion][(type + 1) % 3];
```

- [ ] Keep existing `TH_GetRivalStarter(u16)` usable for pure species validation; random selection occurs once at successful first-partner delivery with `TH_GetRivalCandidate(species, Random() % 2)`. Do not consume randomness whenever the preview redraws. Store in `VAR_TH_RIVAL_PARTNER`; every later scene/team reads that stored species.
- [ ] Test all 18 player/candidate combinations, failed/cancelled grants, save/reload persistence and preservation of a legacy same-region rival. Test fresh naming and legendary callback return after the new ability row.
- [ ] Run partner/capture tests; commit the feature.

### Task 5: Transactional badge gifts and Magikarp

**Files:** create `src/three_horizons_rewards.c`, `test/three_horizons_rewards.c`, `data/scripts/three_horizons/rewards.inc`; modify `include/three_horizons.h`, `src/three_horizons_partner.c`, `data/scripts/three_horizons/maps.inc`, `data/specials.inc` only if script-special wrappers are needed.

**Interfaces:**

```c
enum THReward { TH_REWARD_BROCK, TH_REWARD_MISTY, TH_REWARD_MAGIKARP };
u16 TH_GetBrockGift(u16 original, u8 choice);
u16 TH_GetMistyGift(u16 original, u16 brockGift);
u8 TH_TryDeliverReward(enum THReward reward, struct Pokemon *pending);
```

Return native `MON_GIVEN_TO_PARTY`, `MON_GIVEN_TO_PC`, or `MON_CANT_GIVE`. The delivery function checks eligibility, species, prior receipt and price; applies money/receipt state only after delivery success, with no frame yield between delivery and commit.

- [ ] Write reward tests over all nine starters and both Brock choices. Map original Grass or Fire to Water gift, original Water to Fire gift; exclude original region. Misty returns the unique missing region/type, or `SPECIES_NONE` if no valid Brock receipt exists.

```c
EXPECT_EQ(TH_GetBrockGift(SPECIES_TORCHIC, 0), SPECIES_SQUIRTLE);
EXPECT_EQ(TH_GetBrockGift(SPECIES_TORCHIC, 1), SPECIES_TOTODILE);
EXPECT_EQ(TH_GetMistyGift(SPECIES_TORCHIC, SPECIES_SQUIRTLE), SPECIES_CHIKORITA);
EXPECT_EQ(TH_GetMistyGift(SPECIES_TORCHIC, SPECIES_TOTODILE), SPECIES_BULBASAUR);
EXPECT_EQ(TH_GetMistyGift(SPECIES_TORCHIC, SPECIES_NONE), SPECIES_NONE);
```

- [ ] Use the shared editor/nickname flow for level-10 Brock and level-15 Misty gifts. Persist received species independently of party contents. Skipped Brock gift produces a return-later explanation; releasing or boxing a gift never makes it available twice.
- [ ] Construct Magikarp level5, Adamant, normal ability, shiny, all IV31, EV6HP/252Attack/252Speed. Offer for exactly500, confirm before delivery. Insufficient money, full storage, cancellation or already purchased returns no delivery and no debit. No editable stats for this fixed offer.
- [ ] Test party vacancy, empty PC, last PC slot, full storage, money499/500, retry, save/reload and released gift. Verify the purchased Magikarp's resulting level, nature, ability, IV/EV/shiny properties rather than only its construction inputs.
- [ ] Add unique caretaker/salesman dialogue, including why the extra partners need homes and the third-region goal. Native item/party capacity errors remain visible. Commit after focused reward tests pass.

### Task 6: Real-time and optional fast visual clock

**Files:** create `src/three_horizons_clock.c`, `test/three_horizons_clock.c`; modify `include/three_horizons.h`, `src/rtc.c`, `src/overworld.c` (`UpdateTimeOfDay`), `src/option_menu.c`, `src/three_horizons_options.inc`, `src/three_horizons.c`, `data/scripts/three_horizons/home.inc`, `data/maps/TH_Home2F/map.json`.

**Interfaces:**

```c
u32 TH_AdvanceVisualClock(u32 anchorReal, u32 anchorVisual, u32 now, u8 mode);
void TH_SetClockMode(u8 mode);
u32 TH_GetVisualTimeSeconds(void);
```

Mode0 is real-rate; mode1 is24x. Persist real/visual anchors as two u16 vars each. Calculate with wide intermediates and clamp rollback to zero elapsed; keep real RTC/local offset for berries, daily timers and save timestamps. Mode changes re-anchor at the currently displayed second. Default uninitialized normal mode uses native local time, and invalid mode also falls back to normal.

- [ ] Add deterministic tests before integration:

```c
EXPECT_EQ(TH_AdvanceVisualClock(100, 200, 160, 0), 260);
EXPECT_EQ(TH_AdvanceVisualClock(100, 200, 160, 1), 1640);
EXPECT_EQ(TH_AdvanceVisualClock(100, 200, 90, 1), 200);
```

- [ ] Add mode-switch continuity, midnight rollover, save/reload, long suspend and backwards RTC tests. On rollback, re-anchor real time at the new reading while preserving last valid visual time. Define saturation/wrap handling in the pure helper so a large date correction cannot overflow the multiplier.
- [ ] Route lighting/encounter period decisions through visual hours only. Preserve native daily `gLocalTime` consumers; do not multiply `RtcCalcLocalTime` globally. Explicit clock setting resets visual anchors to the chosen local time.
- [ ] Add a third Options page if needed for readable Clock/Shiny controls; avoid using already occupied task data fields. Stage new-game choices before event-variable reset, as existing EXP/follower options do.
- [ ] Add a bedroom stair trigger that prompts clock setup once and rechecks `FLAG_SET_WALL_CLOCK`. Cancellation stays in the room with control; completion allows passage. Old saves trigger only when visiting home. Test no repeated prompt after save/reload.
- [ ] Run focused clock and save tests; visually check lighting with normal/fast mode. Record handheld RTC as user verification pending. Commit.

### Task 7: Wild shiny odds without recoloring saved Pokémon

**Files:** `src/wild_encounter.c`, `src/pokemon.c` only at the wild-creation boundary if required, `src/three_horizons_options.inc`, `src/option_menu.c`, `src/three_horizons.c`, `include/three_horizons.h`; create `test/three_horizons_shiny.c`.

**Interfaces:** `u16 TH_GetWildShinyThreshold(void)` returns8,64,128,256 for Normal,1/1024,1/512,1/256. Invalid setting returns8. This is a generation probability, not a replacement for the global shiny identity constant.

- [ ] Add deterministic roll-boundary tests and an existing party/box shiny-status snapshot test across all four settings. Include fishing, grass, cave and scripted fixed-shiny rewards; explicit editor choice must not be overridden.
- [ ] Trace native charm/lure/DexNav rolls. Use the configured threshold per native eligible wild roll, then set the generated mon's shiny state through the native data API; retain native roll bonuses and document that they improve the selected base odds. Do not change `SHINY_ODDS` used to interpret existing personalities.

```c
static const u16 thresholds[] = {8, 64, 128, 256};
u16 setting = VarGet(VAR_TH_SHINY_RATE);
return setting < ARRAY_COUNT(thresholds) ? thresholds[setting] : thresholds[0];
```

- [ ] Test bounded defaults, save/new-game staging, trainer parties unaffected and both guaranteed-shiny and explicitly nonshiny partners. Commit after focused tests pass.

### Task 8: Opening scene staging

**Files:** `src/main_menu.c`, `data/scripts/three_horizons/home.inc`, `lab.inc`, `town.inc`, `text.inc`, `maps.inc`, `data/maps/TH_OaksLab/map.json`; extend `tools/three_horizons/tests/test_rival_scenes.py` and native opening tests.

- [ ] Insert existing Blue portrait before rival naming with “This is your rival!” and “What was his name again?” text; clear text windows correctly before each transition. Preserve entered name and blank-name fallback.
- [ ] Add a one-time lab-entry sequence: lock, short walk to a verified empty tile, professors face player, Oak introduces joint research, Elm/Birch add distinct remarks, rival hesitates and lets the player choose. Keep the three professors together without blocking ball access or Oak's supply walk.

```asm
    lockall
    applymovement OBJ_EVENT_ID_PLAYER, TH_Lab_ApproachProfessors
    waitmovement 0
    msgbox TH_Text_JointResearch
    msgbox TH_Text_RivalLetsPlayerChoose
    setflag FLAG_TH_LAB_INTRO
    releaseall
    end
```

Define the movement from the actual entry warp and map collision grid; test destination/release facing, not merely presence of script labels.
- [ ] Gate intro on both the new flag and existing first-partner state, so an old save with a starter never replays it. Keep rival ball approach, persistent displays, supply delivery and follower refresh from the baseline.
- [ ] Test fresh/old save entry, exit/re-entry before choosing, cancellation, and completion with Kris plus one other outfit. Commit.

## Stage C — connected chapter

### Task 9: Append connected maps, interiors and recovery locations

**Files:** create `tools/three_horizons/chapter9_maps.json` and `tools/three_horizons/tests/test_chapter9.py`; create TH map JSONs from the sources below; modify `tools/mapjson/three_horizons_maps.json`, `data/maps/map_groups.json`, `data/layouts/layouts.json`, `src/data/tilesets/three_horizons.h`, `src/data/heal_locations.json`, `data/scripts/three_horizons/maps.inc`, existing TH town maps.

**Map manifest:** append these destinations; each entry records source map, TH name, connections, warp remapping and script ownership. Preserve native collision/layout bytes unless a demonstrated blocked doorway needs a local repair.

| Source map | New TH map |
| --- | --- |
| Route22_Frlg | TH_Route22 |
| Route22_NorthEntrance_Frlg | TH_LeagueGate |
| Route3_Frlg | TH_Route3 |
| Route4_Frlg | TH_Route4 |
| Route4_PokemonCenter_1F_Frlg | TH_Route4Center |
| MtMoon_1F_Frlg / MtMoon_B1F_Frlg / MtMoon_B2F_Frlg | TH_MtMoon1F / TH_MtMoonB1F / TH_MtMoonB2F |
| CeruleanCity_Frlg | TH_Cerulean |
| CeruleanCity_Gym_Frlg / CeruleanCity_Mart_Frlg | TH_CeruleanGym / TH_CeruleanMart |
| CeruleanCity_PokemonCenter_1F_Frlg | TH_CeruleanCenter |
| CeruleanCity_House1_Frlg through House5_Frlg | TH_CeruleanHouse1 through TH_CeruleanHouse5 |
| CeruleanCity_BikeShop_Frlg | TH_CeruleanBikeShop |
| PalletTown_RivalsHouse_Frlg | TH_RivalHouse |
| ViridianCity_House_Frlg / ViridianCity_School_Frlg / ViridianCity_Gym_Frlg | TH_ViridianHouse / TH_ViridianSchool / TH_ViridianGym |
| PewterCity_House1_Frlg / PewterCity_House2_Frlg | TH_PewterHouse1 / TH_PewterHouse2 |
| PewterCity_Museum_1F_Frlg / PewterCity_Museum_2F_Frlg | TH_PewterMuseum1F / TH_PewterMuseum2F |

- [ ] Add graph tests for Home→CeruleanGym and reverse; verify every warp index resolves inside its destination, landing tiles are walkable, and every visible building door has an interior/return warp. Keep native link facilities closed with a clear explanation; no online implementation.
- [ ] Import maps with TH-owned scripts and explicit event mapping. Do not leave native FRLG flag aliases at zero or native Hoenn story callbacks attached. Read `work/build_journey6.py` only for patterns; do not rerun its broad old-stage mutations.
- [ ] Add the Route22 connection and badge-locked League gate, Route3 Brock gate, both MtMoon exits/all ladders and Cerulean boundary blockers. Rival battle occurs on the Cerulean side of the bridge; no need to expose the remaining Route24 map.
- [ ] Add Route4 and Cerulean healing destinations using verified nurse/front-counter coordinates. Test center visit→loss→recovery and indoor/outdoor return, including loss after leaving the opposite cave exit.
- [ ] Provide interior-specific scripts for the older towns and Cerulean. Explain future services indoors; no duplicated generic “forest path” speech. Museum is visitable; fossils cannot be revived in this chapter.
- [ ] Run map host tests and build. Visually traverse every door/ladder in both directions; a graph test alone does not prove terrain passage. Commit map and recovery integration.

### Task 10: Trainers, persistent rivals and Misty

**Files:** `src/data/trainers.party`, `include/constants/opponents.h`, `src/three_horizons.c`, `data/scripts/three_horizons/journey.inc`; create `data/scripts/three_horizons/chapter9.inc`, `test/three_horizons_chapter9.c`; modify new map trainer events and state manifest.

- [ ] Reuse audited unreachable Hoenn trainer IDs from Task3 under TH guards. Give each trainer its own defeat state and pre/post text. Define ordinary Route3/MtMoon/Rocket/Gym teams around native early-Kanto levels, without competitive EV boosts. Verify generated trainer records across all difficulty fallbacks.
- [ ] Add nine variants for each new rival encounter, selected from the saved partner line. Route22 optional battle: Pidgey9 + saved starter10. Bridge battle: Pidgeotto17, Abra16, Rattata15 + saved starter's first evolution18. Use Blue art and player-chosen rival name for every variant. Extend `TH_IsRivalTrainer` to explicit new ranges; do not accidentally rename unrelated trainers between noncontiguous IDs.
- [ ] Route22 retry remains optional after a loss; bridge retry blocks only the north boundary. Use trainer defeat state for victory and a separate chapter completion check; never mark defeated merely for entering the battle script.
- [ ] Define Misty with Staryu18, Psyduck18, Marill19, Starmie21, modest IVs and no EV maximization. Use legal level-appropriate moves and Water Pulse as the signature attack; inspect the generated records, not just `.party` input.

```asm
TH_MistyReward:
    setflag FLAG_BADGE02_GET
    goto_if_set FLAG_TH_MISTY_TM, TH_MistyAfterReward
    giveitem ITEM_TM_WATER_PULSE
    goto_if_eq VAR_RESULT, FALSE, TH_MistyBagFull
    setflag FLAG_TH_MISTY_TM
```

Confirm the native Water Pulse item symbol during implementation. On bag full, badge remains earned and the TM remains pending for the next interaction. Existing reusable-TM configuration remains unchanged.
- [ ] Add tests for trainer loss/retry, no repeated prizes, TM bag-full retry, saved rival species, and Misty/bridge completion in both orders. Completion text fires once after both victories; free exploration continues.
- [ ] Run native chapter/rival tests and trainer regeneration in both build modes. Commit.

### Task 11: Visible pickups, fossils, regional encounters and reward placement

**Files:** new chapter map events; `src/data/wild_encounters.json`; `data/scripts/three_horizons/chapter9.inc`, `rewards.inc`; extend `tools/three_horizons/tests/test_chapter9.py`, `test/three_horizons_rewards.c`.

- [ ] Convert all playable hidden pickups to visible item-ball objects on reachable unoccupied tiles, retaining once-only ownership flags or replacing invalid imported flags with audited TH slots. Remove the corresponding hidden event so both cannot grant the same pickup.

```asm
    giveitem ITEM_POTION
    goto_if_eq VAR_RESULT, FALSE, TH_PickupBagFull
    setflag FLAG_TH_PICKUP_ROUTE3_POTION
    removeobject VAR_LAST_TALKED
```

Use each actual native item's identity rather than changing every pickup to Potion. Manifest records each pickup's map, tile, item and flag. Full bag retains the object; interaction/save/re-entry cannot duplicate it.
- [ ] Implement Rocket trainers and the Super Nerd/fossil choice on MtMoonB2F. Confirm Helix/Dome selection, grant exactly one, preserve the other prop's story state, and leave choice pending on full bag. Test saved selection and repeat interaction.
- [ ] Place Brock caretaker outside Pewter Gym, Misty caretaker in Cerulean and Magikarp salesman inside Route4Center, invoking Task5's delivery flow. Avoid doorway/cutscene occupancy. Verify skipped first gift and later return to the second caretaker.
- [ ] Route22 grass includes Spearow, both Nidoran, Mankey and Meowth. Keep Kanto encounters the majority; add rare Chikorita in Forest, rare Charmander on Route3, night Spinarak and Makuhita in MtMoon. Preserve valid slot weights and level progression; add distinct sightings with local NPC observations.
- [ ] Place an aide check-in near MtMoon: the professors are comparing habitats as Johto/Hoenn species appear in Kanto. Keep dialogue concise and specific. Document aquatic starter habitats as future fishing/surf content, not currently obtainable promises.
- [ ] Test item/fossil delivery with full bag and reward delivery with full storage; validate encounter species/levels/weights and time slots; manually verify object accessibility. Commit.

### Task 12: Landmark entrance illustrations

**Files:** `src/map_preview_screen.c`, `src/overworld.c` (`ShouldRunMapPreview` transition), `src/field_screen_effect.c` (preview fade completion); `graphics/map_preview/viridian_forest/tiles.png`, `tilemap.bin`, `graphics/map_preview/mt_moon/tiles.png`, `tilemap.bin` remain source assets; create `test/three_horizons_area_cards.c`.

- [ ] Trace the native FRLG preview callback, palette restoration and once-per-entry behavior. Enable that route only for TH Forest/MtMoon external entry; no global change to Emerald behavior.
- [ ] Add native tests with previous/current map pairs: south gate→Forest show; north gate→Forest show; Route4→MtMoon1F show; MtMoonB1F→MtMoon1F skip; blackout→Center skip; menu/clock return skip.
- [ ] Confirm buttons, text windows and follower/player palettes after the card. Retain regular map-name popup elsewhere and avoid the formerly empty blackout banner. Commit after visual and callback checks.

### Task 13: Integrated verification and Playtest 9 delivery

**Files:** `.github/workflows/three-horizons-demo.yml`, `docs/three_horizons/PLAYTEST_9.md`, `docs/three_horizons/PLAYTEST_9_VERIFICATION.md`, `docs/SUMMARY.md`; packaged artifacts outside the repo under `outputs/playtest-9/`.

- [ ] Run the complete host, TH engine and native save suites. Retain existing negative controls and add a negative control for the reproduced capture cause if Task1 produces a deterministic regression. Record exact test counts/results and source revision; don't describe source-inspection checks as emulator tests.
- [ ] Build TH demo, normal Emerald, FireRed, release and docs using existing workflows. Confirm switching modes regenerates trainer data without leaving generated tracked changes. Check ROM size and build warnings, then inspect final diff for unintended shared-engine changes.
- [ ] Use a copied Playtest8 Brock battery save to enter the chapter, claim eligible gifts and complete both battle orders. Separately play a fresh game through intro/clock/lab/capture/Forest/Brock/MtMoon/Misty. Exercise capture naming/evolution, each blackout destination and in-game save/full emulator restart. Do not overwrite the user's original save.
- [ ] Review the complete change against the spec, including all reward edge cases and state allocations; follow the native execution skill's final review requirement. Resolve material findings before packaging.
- [ ] Package `pokemon-three-horizons-playtest-9.gba`, checksum, source hash, known issues and tester instructions in `three-horizons-playtest-9.zip`. Preserve prior downloads and keep ELF/logs available for diagnosis. Update the existing draft PR's description and attach it; do not merge.
- [ ] Include handheld instructions for RG40XX H: extracted `.gba`, copied in-game battery save, firmware-specific save extension/location, mGBA core if available, RTC/lighting/audio/evolution/follower checks and full power-off/Continue. Firmware is unknown; do not invent its folder names or recommend flashing it.
- [ ] Report implemented features, verified checks, any unresolved capture/art issue, exact new download and the beta checklist. Separate desktop verification from pending handheld confirmation. Explain branch protection as workflow advice only; no GitHub settings change is included.

## Self-review record

The approved design's capture/visual repairs map to Tasks1–2; save compatibility to3; abilities/nicknames/rival persistence to4; all badge/Magikarp gifts to5; clock to6; odds to7; opening to8; connected maps/interiors to9; battles/badges to10; regional story/pickups/fossils to11; area cards to12; build/testing/handheld delivery to13. Five cross-cutting review risks above have explicit owning tasks. Native execution is already selected. No new illustration generation, additional region construction or repository protection mutation has been silently added.
