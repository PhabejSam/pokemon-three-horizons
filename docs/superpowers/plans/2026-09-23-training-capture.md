# Training access and legendary capture rewards implementation plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:executing-plans to implement this plan task-by-task. The user has selected native execution. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Deliver the approved four-Pokemon Brock team, one-time PC training kit, Viridian training service, configurable legendary catches, and Oak's walking handoff in a new playtest ROM.

**Architecture:** Keep every behavior opt-in under THREE_HORIZONS. Put item grants and stat transactions in a small training module; extend the existing partner editor with a distinct capture entry point and explicit return callback. Integrate with the existing capture state machine before party/PC delivery, retaining native storage and nickname handling.

**Tech Stack:** pokeemerald-expansion C, field/battle scripts, map JSON, Python host checks, ARM engine tests, GitHub Actions builds.

**Spec:** `docs/superpowers/specs/2026-09-23-training-capture-design.md` (approved by the user).

**Execution state:** Design and plan approved by the user. Native implementation in progress.

## Global constraints

- Use Geodude level 12, Zubat level 12, Sandshrew level 12, and Onix level 14.
- Future Gym Leaders use 4–6 Pokemon: four early, five middle, six late.
- The training shop is temporarily in Viridian for testing and eventually belongs in Celadon.
- Provide one Macho Brace and one of each Power item in the player's item storage.
- Keep the existing Potion. This is a one-time kit, not a refill on each visit.
- Existing playtest saves receive the same kit when accessing their home PC.
- Do not change the save structure.
- A Bottle Cap sets one selected IV to 31; a Gold Bottle Cap sets all six IVs to 31.
- No late-game or minimum-level requirement.
- Legendary editing allows IVs 0–31 and EVs 0–252, total maximum 510.
- Cancel never releases or deletes the Pokemon.
- Preserve Playtest 6 and the user's saves; do not merge the draft PR.

## Review focus

1. Partial PC storage capacity: grant successful items exactly once, then safely retry undelivered items. Covered in task 2.
2. Stat edits to a fainted or damaged Pokemon: preserve fainted state and valid HP; canceled/no-effect operations consume nothing. Covered in tasks 3 and 4.
3. Full party, party swap, or nearly full PC at capture: edit and deliver the captured Pokemon exactly once, without losing another party member. Covered in task 4.
4. Existing saves and unrelated game builds: no new-game prerequisite, reused flags, altered save layout, or changed standard trainer teams. Covered in tasks 1, 2, and 6.
5. Oak's route after any starter-display approach: avoid the player, remaining balls, professors, and follower; return home before releasing control. Covered in task 5.

## Task 1: Brock's party and gym guideline

**Files:** `src/data/trainers.party`, `test/three_horizons.c`, `docs/three_horizons/PLAYTEST_7.md`.

**Interfaces:** Keep `TRAINER_TH_BROCK`, his existing script, badge and TM flags unchanged. Do not edit generated `src/data/trainers.h` manually.

- [ ] Update the existing assembled-trainer test to expect four species in order and levels 12/12/12/14. Use the actual generated trainer table, not a parallel hand-written fixture:

```c
static const u16 expectedSpecies[] = {
    SPECIES_GEODUDE, SPECIES_ZUBAT, SPECIES_SANDSHREW, SPECIES_ONIX,
};
static const u8 expectedLevels[] = {12, 12, 12, 14};
EXPECT_EQ((u32)trainer->partySize, ARRAY_COUNT(expectedSpecies));
if (trainer->partySize != ARRAY_COUNT(expectedSpecies))
    return; // The size assertion failed; do not read beyond the old party.
for (u32 i = 0; i < trainer->partySize; i++)
{
    EXPECT_EQ(trainer->party[i].species, expectedSpecies[i]);
    EXPECT_EQ(trainer->party[i].lvl, expectedLevels[i]);
}
EXPECT_EQ(trainer->party[3].moves[2], MOVE_ROCK_TOMB);
```

- [ ] Run the focused test against the old party; require the party-size assertion to fail.
- [ ] Add Zubat (Peck, Absorb, Supersonic) and Sandshrew (Scratch, Defense Curl, Sand Attack) between Geodude and Onix. Retain zero specified IVs, no added EVs/items, and existing Geodude/Onix moves.
- [ ] Regenerate trainers and rerun the test. Confirm standard-build Brock remains unchanged and the TH team generates four usable party members.
- [ ] Record the 4/5/6-Pokemon future gym guideline and the expanded first-gym beta checklist. Do not rewrite the historical Playtest 6 guide.

## Task 2: One-time training kit, including existing saves

**Files:** create `src/three_horizons_training.c` and `test/three_horizons_training.c`; modify `include/three_horizons.h`, `include/constants/three_horizons.h`, `data/specials.inc`, `data/scripts/three_horizons/home.inc`.

**Interfaces:**

```c
u16 TH_TryDeliverTrainingKit(void); // returns delivered-item bit mask
void TH_ScriptDeliverTrainingKit(void); // wrapper sets gSpecialVar_Result
```

- [ ] Audit the unused Emerald variable `0x409B` for saved-state aliases, including numeric references and macro definitions. Reserve it as `VAR_TH_TRAINING_KIT_MASK` only under the opt-in behavior. Current exploration found only unused Emerald and FRLG declarations, not active Emerald use.
- [ ] Add engine tests using the real PC inventory APIs: an empty inventory gets all seven items once; withdrawing an item and calling again does not refill it; a nearly full inventory delivers a subset and retries the rest after space is freed. Preserve the Potion and unrelated saved variables.
- [ ] Run the tests before the implementation and record their failure.
- [ ] Implement transactional per-item delivery:

```c
static const u16 items[] = {
    ITEM_MACHO_BRACE, ITEM_POWER_WEIGHT, ITEM_POWER_BRACER,
    ITEM_POWER_BELT, ITEM_POWER_LENS, ITEM_POWER_BAND, ITEM_POWER_ANKLET,
};
u16 mask = VarGet(VAR_TH_TRAINING_KIT_MASK);
for (u32 i = 0; i < ARRAY_COUNT(items); i++)
    if (!(mask & (1 << i)) && AddPCItem(items[i], 1))
    {
        mask |= 1 << i;
        VarSet(VAR_TH_TRAINING_KIT_MASK, mask);
    }
return mask;
```

- [ ] Invoke the wrapper from `TH_EventScript_HomePC` before opening item storage. This serves both new and old saves, avoids changing global PC behavior, and makes the kit available on the first home-PC visit.
- [ ] Add concise PC explanation text for held training items and natural species EV yields. Do not claim that Power items block unwanted EVs.
- [ ] Rerun engine tests and verify the PC script still restores its turn-off effect and player control.

## Task 3: Viridian training shop and cap redemption

**Files:** `src/three_horizons_training.c`, `include/three_horizons.h`, `src/item.c`, `data/specials.inc`, new `data/scripts/three_horizons/training.inc`, its include in the TH script root, `data/maps/TH_ViridianMart/map.json`, `test/three_horizons_training.c`.

**Interfaces:**

```c
u32 TH_GetTrainingItemPrice(u16 itemId, u32 fallback);
bool32 TH_TryImproveIVs(struct Pokemon *mon, u16 itemId, u8 stat);
void TH_ScriptImproveIVs(void);
// Script inputs: VAR_0x8004 party index, VAR_0x8005 cap item,
// VAR_0x8006 stat index. Result TRUE only for a successful paid change.
```

- [ ] Add tests for one-IV and all-IV changes, level-5 eligibility, Egg rejection, missing cap, already-maxed stats, invalid stat index, and metadata retention. Check that only successful changes consume exactly one cap.
- [ ] Test a fainted Pokemon and a partially damaged Pokemon. Record HP/maxHP before editing; afterward zero HP must remain zero, otherwise preserve damage amount and clamp HP to the new valid maximum with a minimum of one.
- [ ] Implement `TH_TryImproveIVs` by validating everything first, copying the Pokemon, editing the copy, recalculating stats, successfully removing one cap, then replacing the original. Never consume a cap before all no-effect/error checks succeed.
- [ ] Set one selected IV or all six to 31 using `SetMonData`. Do not recreate the Pokemon. Preserve all non-target fields.
- [ ] Build the clerk's field script with three choices: Buy supplies, Improve IVs, Training advice. Use `special ChoosePartyMon`; cancel is `VAR_0x8004 >= PARTY_SIZE`. Store the selected party index before other menus use script variables. Show cap type, selected stat, and cost, then require Yes before the mutation wrapper.
- [ ] Add the clerk using an existing reachable NPC position in Viridian Mart. Keep the normal clerk and existing shop functional.
- [ ] Stock Pomeg, Kelpsy, Qualot, Hondew, Grepa, and Tamato berries; all existing useful stat Mints; Bottle Cap and Gold Bottle Cap. Explain that cap use is through the clerk, since caps' native Bag action remains unusable.
- [ ] Route `GetItemPrice` through a THREE_HORIZONS-only helper: berries 100, Mints 1,000, Bottle Cap 2,000, Gold Bottle Cap 6,000; return the original price for every other item. Keeping buy/sell pricing on the same getter avoids a profitable price mismatch.
- [ ] Exercise native berry/Mint/Power-item effects using the engine's actual item/EV routines. Verify native Minted-nature summary display before changing its UI; preserve birth-nature semantics and show the effective stat nature accurately.
- [ ] Rerun training tests and a host check that the clerk, stock, and include labels compile and remain reachable. Document permanent Celadon placement as future content, not a new map in this update.

## Task 4: Legendary capture customization

**Files:** new `src/three_horizons_capture.c`, `test/three_horizons_capture.c`; modify `src/three_horizons_partner.c`, `include/three_horizons.h`, `src/battle_script_commands.c`; add battle integration tests under `test/battle/three_horizons_capture.c`.

**Interfaces:**

```c
bool32 TH_IsConfigurableCapture(u16 species);
void TH_ReadMonOptions(struct Pokemon *mon, struct THPartnerOptions *options);
bool32 TH_ApplyCaughtMonOptions(struct Pokemon *mon,
                              const struct THPartnerOptions *options);
bool32 TH_OpenCaughtMonEditor(struct Pokemon *mon, void (*returnCallback)(void));
```

- [ ] Write tests covering restricted legendaries, sub-legendaries, mythicals, applicable forms, an ordinary species, and invalid species values. Classification uses the existing species flags, not a handful of hard-coded IDs.
- [ ] Write mutation tests using an actual caught-style Pokemon with a non-default level, ball, nickname, original trainer, moves/PP, gender, ability, and held item. Check all unrelated fields survive; reject IV 32, EV 253, and total EV 511 without changing the original. Verify effective nature, shiny toggle, and recalculated stats. No hidden healing effect.
- [ ] Implement these helpers without calling starter-grant functions. For a requested nature, preserve gender, form, and ability as well as capture metadata. Use the engine's nature/hidden-nature fields consistently; summary must display the chosen effective stat nature.
- [ ] Refactor shared editor rendering and input handling into a context with mode, actual Pokemon level, original options, temporary options, target pointer, and completion callback. Keep the field starter entry point and script-resume behavior intact.
- [ ] In capture mode, show the actual level, Confirm changes, and Keep original. Use the actual Pokemon's sprite identity for the preview where needed; changing preview shiny status must not change the underlying catch before confirmation.
- [ ] Implement a full-screen battle-menu lifecycle following existing battle debug/summary menu entry and `ReshowBattleScreenAfterMenu` return. Save/restore callbacks and UI resources deliberately; do not use field `ScriptContext_Enable` for a battle editor. Guard allocation failures by keeping the original catch and returning to the native flow.
- [ ] Add distinct capture states before native `GIVECAUGHTMON_CHECK_PARTY_SIZE`. The initial state tests eligibility and opens the editor once. Set the next state before opening the UI; on return continue to normal party-size checks. If needed preserve zero as a new initial state so native command initialization remains correct. Never reopen on subsequent frames or retries.
- [ ] Verify Pokedex registration ordering relative to the editor. Commit the selected shiny record at the correct point and preserve nickname entry. Do not register the wrong temporary preview or double-award a catch.
- [ ] Exercise successful legendary capture with a party vacancy, full party sent to PC, and full-party swap; verify exactly one delivered Pokemon. Test cancel/default confirmation, failed catch, defeated legendary, ordinary catch, and no storage space. Retain native rejection of captures with no legal storage.
- [ ] Add regression checks showing starter selection still creates level-5 partners and capture editing never writes `VAR_TH_STAGE`, `VAR_TH_FIRST_PARTNER`, or `VAR_TH_RIVAL_PARTNER`.
- [ ] Use engine-controlled test encounters for automated coverage. If emulator beta coverage needs an encounter before Brock, provide clearly labeled opt-in test access only after the main capture flow is verified; do not silently place a story legendary on Route 1.

## Task 5: Oak walks over for the gift

**Files:** `data/scripts/three_horizons/lab.inc`, new `tools/three_horizons/tests/test_oak_handoff.py`; reuse actual lab map/tileset data in host traversal tests.

**Interfaces:** A new `TH_Lab_OakHandoff` subroutine called once after `TH_Lab_RivalCollectPartner`. Existing `TH_OakSupplies` retains duplicate prevention and bag-full retries.

- [ ] Extend the existing real-tile movement-test approach to enumerate every reachable interaction position around the three display balls, including the player's one-step movement in the rival scene. Compute each post-scene player position and assert Oak's path ends adjacent without crossing the player or static objects.
- [ ] Choose authored path variants from Oak's home position (6,3) to each reachable player approach. Prefer staying in the open aisle rather than passing through remaining display balls. Keep the follower hidden during the existing locked scene.
- [ ] Add the handoff subroutine with `closemessage`, `applymovement`, `waitmovement`, and facing actions before the existing grant call. Preserve partial-supply tracking on failure.
- [ ] Return Oak to (6,3), restore his normal facing and follower visibility, then release control on both successful and bag-full paths. Repeated conversations after collection skip the movement. Direct retry conversations do not move Oak through the player.
- [ ] Run traversal tests for every variant and check dialogue widths with the compiled font. Include a manual checklist for each regional starter display and follower enabled/disabled.

## Task 6: Integration, review, build, and beta delivery

**Files:** `.github/workflows/three-horizons-demo.yml`, `docs/three_horizons/PLAYTEST_7.md`, `docs/SUMMARY.md`, workspace packaging/ELF-inspection helpers.

- [ ] Add all newly introduced documentation to SUMMARY. Update verification to inspect the generated four-member Brock party, not the historical two-member Playtest 6 team.
- [ ] Run the full host suite and relevant engine suites on the same source revision:

```sh
make -C tools/mapjson
python3 -m unittest discover -s tools/three_horizons/tests -v
make THREE_HORIZONS=1 -j2 -O all
python3 tools/three_horizons/check_running_elf.py pokemon-three-horizons.elf
make THREE_HORIZONS=1 check TESTS="Three Horizons" -j2
make THREE_HORIZONS=1 check TESTS="test/save.c" -j2
```

- [ ] Keep existing palette, rival-party, and fleeing negative controls. Add focused negative controls for duplicate kit delivery and illegal capture edits, requiring their corresponding tests to fail when the checks are disabled.
- [ ] Verify actual linked records, palette tags, running-frame bounds, text widths, stat limits, item prices, and clerk/Oak paths against the built source/ELF. Repeat only affected checks after a repair.
- [ ] Run standard Emerald/FireRed/LeafGreen compatibility builds. Confirm the opt-in changes do not alter their PC inventories, catch flow, prices, or Brock party.
- [ ] Perform one independent whole-change review per the native execution workflow, focused on the five review concerns above. Fix blocking issues and rerun affected tests. Keep any nonblocking deferred findings explicit.
- [ ] Publish to the existing feature branch and update draft PR #2 with exact source, successful checks, warnings, and manual-test limitations. Do not merge.
- [ ] Package `pokemon-three-horizons-playtest-7.gba`, guide, SHA-256, source commit, changed-file list, credits, and build/test logs into a new output directory and ZIP. Verify the ZIP's ROM hash matches the build artifact. Do not overwrite old ROMs or `.sav` files.
- [ ] Give the user a focused beta checklist: new/old-save PC kit, each training item, no-effect and canceled cap use, all three Oak approaches, four-Pokemon Brock, and legendary customization with party/PC destinations. Clearly state any behavior not manually exercised.

## Plan self-review

All approved requirements map to tasks: Brock/future gym rule (1), PC kit/migration (2), training shop and usable IV improvements (3), exact caught-Pokemon editor and storage safety (4), Oak's physical handoff (5), and reproducible tested delivery (6). The core service functions have distinct responsibilities and do not depend on UI variables. Historical Playtest 6 output and save structures stay unchanged. Native execution remains the user's selected method.
