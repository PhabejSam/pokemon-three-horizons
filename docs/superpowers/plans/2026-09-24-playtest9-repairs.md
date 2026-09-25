# Playtest 9 repair plan

Execution: native, in the existing isolated `feature/opening-demo` worktree.
User specification: the latest Playtest 9 report and its three screenshots.

Goal: fix the capture/nickname crash, rival-loss stall, clipped Options help,
and the rival-introduction/lab approach presentation without changing saved data.

- [x] Exercise the capture with actual Dex/nickname transitions; trace the
  shipped ELF addresses. Preserve the invalid-item assertion. Add regression
  coverage for the demonstrated cause, then repair it and rerun the scenario.
- [x] Trace the early-rival return and departure lifecycle, including a loss
  with followers enabled. Add a bounded regression for the identified stall.
- [x] Keep the second Options page entirely within its native window; verify
  font extents and page switching.
- [x] Walk the player into the lab's open area next to the rival before the
  welcome dialogue; test the complete path against terrain and objects.
- [x] Present Blue in the existing opening's background and dialogue style,
  with entrance/fade and name prompt, instead of the separate white card.
- [x] Run host checks and Linux ROM/engine checks, inspect compiled output,
  and package a repair build with a focused beta checklist and honest limits.

No save-layout changes, assertion suppression, automatic save replacement,
new chapter expansion, or changes to the user's emulator files.

The exact `INVALID ITEM: 4365` assertion is still unconfirmed. Actual nickname
transitions exposed and verified a freed-state callback bug; that concrete
defect is repaired and has a passing regression plus a failing negative control.
The rival-loss comparison used emulator callback traces rather than adding a
source-text test. See [repair evidence and beta guide](../../playtest-9-repair.md)
for the precise runtime coverage and remaining hardware acceptance.
