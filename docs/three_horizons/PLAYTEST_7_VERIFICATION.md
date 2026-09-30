# Playtest 7 execution ledger

The user approved the design and implementation plan and selected native
execution. Work continued in the existing feature/opening-demo checkout.

## Implementation

- Brock: Geodude 12, Zubat 12, Sandshrew 12, Onix 14. Generated trainer-table
  test and independent ELF inspection cover the roster. The old Playtest 6
  ELF failed the four-member assertion before the new ROM was built.
- One-time kit: per-item saved mask at audited unused Emerald variable 0x409B.
  Successful additions commit their bit immediately. Existing saves use the
  same home PC path; no save structure changed.
- Viridian clerk: native Mart stock and item prices, low-level cap redemption,
  no item consumed for cancel/no effect, fainted/damaged HP preserved.
  Berries, Mints and Power items retain upstream item-effect routines.
- Capture editor: temporary options, exact caught mon retained until Confirm;
  Keep original/B is non-destructive. Classification uses species flags.
- Oak: seven authored routes, collision-tested from every display approach,
  handoff and return before release, including bag-full retries.

## Implementation rulings

1. The capture hook runs in trysetcaughtmondexflags, before Dex registration,
   rather than in givecaughtmon as initially sketched. This ensures chosen
   shiny status is registered before the native Dex, nickname and delivery
   sequence. Native party/PC/swap commands remain unchanged.
2. The battle test runner uses recorded battles, which deliberately bypass the
   interactive catch flow. Direct engine tests instead drive the actual editor
   callbacks and button handler, then test actual native party/PC delivery.
   End-to-end thrown-ball/nickname/party-swap playback remains a manual beta
   test; source-order checks alone are not claimed to cover that lifecycle.
3. Effective nature uses the engine's hidden-nature field. PID, form, ability,
   gender and birth identity remain unchanged. The TH summary displays the
   effective stat nature; the clerk explains Mints.
4. No new story legendary is inserted into the route to Brock. Celadon and
   legendary encounter placement remain future map work, as approved.

## Review and repairs

One independent whole-change review found an important allocation-failure
problem: InitWindows was a checked/asserting wrapper, so the intended recovery
branch was unreachable. Capture initialization now uses InitWindowsUnchecked;
preview creation uses recoverable frame/image allocations and a synchronous
probe for the decoder's exact temporary allocation. Failure closes the editor
without applying changes. Engine tests force window and sprite allocation
failure and check that the original catch survives. Original native picture
creation keeps its checked allocation behavior.

The initial ARM compile also found a nonzero EWRAM initializer for the editor
level. It is now zero-initialized and assigned the actual level at entry.

## Evidence and limits

- Host checks: 19 map/scene checks passed.
- Separate traversal check: the training clerk's approach tile (6,3) is
  reachable from home; both Centers, both Marts, Brock and the return route
  remain reachable under static collision analysis.
- Emerald, FireRed, LeafGreen and release builds passed for final source 24da482.
- Final source, engine results, negative controls, ROM hash and capacity are
  recorded in the packaged BUILD_REPORT.md and verification logs.
- No manual emulator playthrough was performed. Preserve this distinction
  when reporting completed automated checks.
- Previous Playtest 6 ROM and saves remain unchanged. The new package has a
  separate filename and explicit instructions for copying an in-game save.

## Final automated result

Source `24da4828ba7148f6d8a31d7477fdbcedd4e1f044` built successfully in [run 35955045648](https://github.com/PhabejSam/pokemon-three-horizons/actions/runs/35955045648).
41 Three Horizons engine tests and four save tests passed, together with
all five deliberate-defect negative controls and restored positive checks.
The ROM SHA-256 is `19e66ca2b494959ea790224a2550e4cd0c85dcf279f8fb9d035f29c1b898ddcc`.
The separate Playtest 7 package includes source identification, changed files,
logs, inspection results, save-transfer instructions and the beta checklist.

Remaining beta coverage: native held-item/berry/Mint use through the field UI,
Oak's visual timing with followers, and the complete thrown-ball, nickname and
party-swap sequence for a legendary. These were not manually played.
