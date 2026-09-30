# Playtest 8 capture investigation

Baseline: b3916b8. The screenshot is a small preview inside another screenshot.
Visible addresses 080A9763 and 08162C09 resolve to Cmd_givecaughtmon and
GetItemPocket in both Playtest 8 ELFs. The original invalid item value is not
legible enough to report confidently.

The failing path restores the caught opponent's original held item from
gBattleStruct->itemLost. The nickname and original-item fields do not overlap.
The naming buffer has 13 bytes for a 12-character name plus terminator.
No demonstrated root cause or reproducible repair exists yet. Keep the
invalid-item assertion; do not silently replace the invalid item with NONE.

A native naming-scene regression now checks the original item across real
screen callbacks. This covers one lifecycle boundary, not a complete capture
or the user's exact failure. Capture-triggered evolution, first Dex entry and
party/PC replacement remain reproduction targets. The original crash image
and a copied battery save from before the catch would materially improve
diagnosis. No user save has been modified.
