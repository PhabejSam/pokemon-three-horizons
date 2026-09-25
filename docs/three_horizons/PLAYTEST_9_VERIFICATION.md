# Playtest 9 verification record

Status: packaged for beta testing after successful automated verification.
Manual emulator, copied-save and handheld acceptance remain open.

## Scope and evidence

The chapter adds 26 maps to the existing 17, using native Kanto layouts.
Original map ordering and save structures are retained. New progress uses
audited event variables, flags and TH-only trainer records documented in
`tools/three_horizons/state_manifest.json`. Trainer replacements are guarded
so the standard upstream game modes retain their original records.

Host checks cover the map graph, warp destinations, map generation in
multiple modes, original indices, Oak/rival movement, persistent pickups,
and the terrain return passage on Route 4. They do not constitute an emulator
playthrough. The final local host run passed 32 tests in 48.034 seconds.
Final source: `7c4b405499cc7db558f2ef965de7259f8781d417`.

The [demo workflow](https://github.com/PhabejSam/pokemon-three-horizons/actions/runs/36079447695)
passed: clean ROM build, 58/58 Three Horizons engine tests, 4/4 native
save-layout tests, all seven deliberately introduced defect checks, restored
58/58 positive tests, and generated trainer-table checks across build modes.
The [compatibility workflow](https://github.com/PhabejSam/pokemon-three-horizons/actions/runs/36079450324)
passed Emerald, FireRed, LeafGreen, release and documentation jobs. The
broader upstream test job was still running when these results were collected
and is not included in the passing claims.

The package rechecks the ROM checksum and ZIP integrity. Its compiled-data
checks verify all 112 running-frame reads and all 38,400 visible title pixels.
These checks do not replace visual playtesting.

Native tests cover partner combinations/abilities, clock arithmetic, shiny
identity stability, chapter completion order, full party/PC reward delivery,
and existing palette, battle, evolution, capture and training regressions.
The new naming callback diagnostic exercises the actual nickname screen;
it is not a reproduction of the reported full capture crash.

The compiled ROM occupies 27,405,192 ROM bytes before padding to
32 MiB, with 226,752 bytes EWRAM and 28,480 bytes IWRAM. Nonfatal warnings
include PNG `bKGD: invalid index` metadata and the unused legacy
`Task_NewGameBirchSpeech_BoyOrGirl` function. The full build log is retained.

## Known limits

- The Playtest 8 invalid-item capture assertion is unresolved. See
  [diagnostic notes](CAPTURE_DIAGNOSTIC.md). No assertion is suppressed and
  no invalid held item is silently replaced.
- Combusken's follower report is unconfirmed. No speculative graphic
  alteration has been made. Both source sheets contain six 32x32 frames,
  matching their frame tables; normal and shiny palettes have 16 entries.
  Source inspection does not prove the reported runtime pose is correct.
- The bedroom clock reminder currently requires completing time setup;
  a cancel-to-bedroom option is deferred from review.
- Native desktop app automation is unavailable in this session. Fresh-game
  traversal, a copied Playtest 8 save through the complete chapter, all
  visual transitions, and RG40XX H operation remain manual acceptance checks.
- The release keeps the scenery title and existing illustrated/pixel assets;
  it adds no generated professor/nine-starter cover.

## Implementation decisions and review

The existing isolated opening-demo worktree was retained. The available
Windows environment has no Bash, ARM build tools or Git HTTPS helper, so
equivalent PowerShell/Python tracking and connected GitHub branch checkpoints
were used, with native builds/tests in Linux CI. The cost is slower remote
test cycles and a separate local/remote history reconciliation step.
For final synchronization, a project-local Dulwich client fetched the
remote Git objects without changing working files. The local feature branch
was fast-forwarded to the verified checkpoint after comparing staged content;
only documentation and line-ending normalization remained different.

The capture assertion remains visible and unresolved; independent chapter
work continued as allowed by the approved design. The cost is that the
reported capture crash may remain until a reproducible save is available.

Native Route 4's one-way ledge prevented returning for missed gifts. Two
TH-only stair metatiles now permit return without modifying the upstream
layout file. Terrain reachability is tested; the transition still needs
visual beta confirmation.

Desktop emulator automation was unavailable. Source, map rendering, native
engine tests and terrain checks were used, with manual traversal, copied-save
acceptance and RG40XX H operation explicitly left unverified. The cost is that
visual or platform-specific problems may remain despite automated checks.
The planned full native overworld healing fixture was not completed. A host
contract checks hide/effect/heal/refresh order; this cannot prove actual
follower visibility through healing and blackout. Those scenes remain on
the manual acceptance checklist.

Save migration stores its version in the 15 unused high bits of the bounded
visual-seconds high word. This preserves save structure size and uses the
eight audited variables. A wrong marker could repeat migration; repeat-load
and clock-write preservation tests cover that risk. The existing EXP. SHARE
flag is preserved after a broader configuration-header audit caught an alias.

The whole-change review's important findings were bridge-rival object
selection, uninitialized legacy chapter state and truncated clock mode.
They were corrected with targeted regression checks. Misty's full-bag reward
path was also corrected so chapter completion does not wait for TM space.
The reviewer did not establish the capture cause, Combusken appearance,
full traversal or handheld compatibility; these remain open for beta evidence.

Two diagnostic checkpoints stopped at the clean-checkout gate because of
line endings. They are not counted as failed gameplay regressions. Uploaded
source was normalized to LF and explicit deliberate-defect controls added
for migration and clock mode. The cost is additional CI cycles; it does not
justify bypassing the clean-source check.

Deferred minor: the initial bedroom clock reminder has no cancel-to-room
option; completing clock setup is required.

## Reproduce checks

Use the established Linux build dependencies documented by the repository
and the `Three Horizons demo` workflow. From the repository root:

```sh
make -C tools/mapjson
python3 -m unittest discover -s tools/three_horizons/tests -v
make THREE_HORIZONS=1 -j2 -O all
python3 tools/three_horizons/check_running_elf.py pokemon-three-horizons.elf
make THREE_HORIZONS=1 check TESTS="Three Horizons" -j2
make THREE_HORIZONS=1 check TESTS="test/save.c" -j2
python3 .github/docs_validate/inclusive_summary.py
```

The demo workflow also runs the existing deliberate-failure controls and
switches build modes to verify generated trainer tables. The normal CI
workflow builds Emerald, FireRed, LeafGreen and release configurations.
The final artifact's `demo-source-commit.txt` and ROM checksum identify the
exact packaged result; earlier screenshots and results are not evidence
for that revision.
