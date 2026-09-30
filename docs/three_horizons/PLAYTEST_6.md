# Playtest 6: the road to Brock

This opt-in Three Horizons build extends the opening through Viridian City,
Route 2, Viridian Forest, Pewter City and Brock's gym. Both cities have a
working Pokémon Center and Mart. Side routes, extra buildings and upstairs
multiplayer rooms remain closed in this playtest.

## Changes

- Gold and the field-effect shadows now have separate palette identifiers.
- Oak, Elm and Birch appear together in the opening and the Pallet lab.
- The early rival can defeat the player; Emerald's wild rescue AI can no
  longer make a trainer flee at low player HP.
- Wild defeats heal at Mom or the most recently entered Center without
  removing money. Trainer defeats retain their usual penalty. The first
  rival retains the introductory battle's recovery behavior.
- Brock uses his native FireRed Geodude (12) and Onix (14). Victory awards
  the first badge and TM39 Rock Tomb. A full bag allows the TM to be collected
  later; repeat conversations do not award it again.

## Save compatibility

Existing Three Horizons map indices and save structures are unchanged.
The old Viridian demo-complete stage does not block the new route. Reused
trainer slots 1–7 belong to unreachable Hoenn trainers and are replaced only
in the opt-in build. The nine existing rival IDs are unchanged. The new TM
reward uses audited unused Emerald flag 0x20.

Keep a backup of your `.sav`. Copy it alongside the new ROM using the same
base filename to continue. Use the in-game save and Continue, rather than an
emulator save state created with a different ROM. Start a separate new game
to see the revised introduction without overwriting your existing save.

## Targeted playtest

1. With Gold selected, visit the clock, go downstairs, enter and leave a
   building, and check both the outfit and follower shadows.
2. Start a separate new game and check all three professors throughout the
   introduction, name entry and confirmation screens.
3. Lose the first rival battle; confirm a proper defeat and recovery.
4. Note your money, lose to a wild Pokémon, and confirm it stays unchanged.
   Repeat after visiting each new Center and confirm the correct return point.
5. Travel through the forest, battle trainers, use the shops and heal.
6. Lose to Brock, return and win. Check the badge and TM, save, restart and
   speak to Brock again. Rewards should not duplicate.

## Build and verification

Use the existing Three Horizons workflow or `make THREE_HORIZONS=1 -j2 all`.
Run `python3 -m unittest discover -s tools/three_horizons/tests -v`, then
`make THREE_HORIZONS=1 check TESTS="Three Horizons" -j2` and the save tests.
The workflow additionally reinstates the original palette and AI defects
and requires the corresponding regressions to fail.

Build results and the exact ROM hash are recorded in the packaged playtest
guide once verification completes. Automated tests do not replace the
manual checks above.
