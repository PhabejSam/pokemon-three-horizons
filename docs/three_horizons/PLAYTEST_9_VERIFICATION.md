# Playtest 9 verification record

Status: implementation and verification in progress; no final ROM release
has been certified by this document yet.

## Scope and evidence

The chapter adds 26 maps to the existing 17, using native Kanto layouts.
Original map ordering and save structures are retained. New progress uses
audited event variables, flags and TH-only trainer records documented in
`tools/three_horizons/state_manifest.json`. Trainer replacements are guarded
so the standard upstream game modes retain their original records.

Host checks cover the map graph, warp destinations, map generation in
multiple modes, original indices, Oak/rival movement, persistent pickups,
and the terrain return passage on Route 4. They do not constitute an emulator
playthrough. The preceding host run passed 28 tests; final results will be
recorded after integration review.

Native tests cover partner combinations/abilities, clock arithmetic, shiny
identity stability, chapter completion order, full party/PC reward delivery,
and existing palette, battle, evolution, capture and training regressions.
The new naming callback diagnostic exercises the actual nickname screen;
it is not a reproduction of the reported full capture crash.

## Known limits

- The Playtest 8 invalid-item capture assertion is unresolved. See
  [diagnostic notes](CAPTURE_DIAGNOSTIC.md). No assertion is suppressed and
  no invalid held item is silently replaced.
- Combusken's follower report is unconfirmed. No speculative graphic
  alteration has been made.
- Native desktop app automation is unavailable in this session. Fresh-game
  traversal, a copied Playtest 8 save through the complete chapter, all
  visual transitions, and RG40XX H operation remain manual acceptance checks.
- The release keeps the scenery title and existing illustrated/pixel assets;
  it adds no generated professor/nine-starter cover.

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
