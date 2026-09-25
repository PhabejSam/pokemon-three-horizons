# Playtest 7: team building

This update adds the approved training features to the existing journey through Brock. Celadon and new story legendary encounters are not yet playable.

## Changes to try

- Brock has Geodude, Zubat, and Sandshrew at level 12, and Onix at level 14.
- Open the home PC to receive one Macho Brace and each of the six Power items in item storage. The kit works on existing saves and is delivered once. If storage is full, make space and open the home PC again for any undelivered items.
- The scientist in Viridian Mart sells the six EV-reducing berries (100 each), nature Mints (1,000), Bottle Caps (2,000), and Gold Bottle Caps (6,000). The same service will eventually move to Celadon.
- Talk to the scientist to redeem caps. One Bottle Cap maximizes one chosen IV; a Gold Bottle Cap maximizes all six. There is no level requirement. Cancel, a missing cap, an Egg, or already-maxed IVs do not consume an item.
- After successfully catching a legendary or mythical, a preview editor offers nature, shiny appearance, individual IVs and EVs. Confirm applies the choices; Keep original or B keeps your unedited catch. Naming and party/PC transfer follow normally.
- Oak walks over after the rival's partner selection, gives the supplies, and returns to his original position.

Newly caught ordinary Pokemon start with zero EVs; IVs and nature normally vary. Power items add their training bonus to the opponent's natural EV yields. They do not block unwanted EV gains. Mints and the legendary editor set the nature used for battle stats, which the summary now shows; birth identity is retained.

## Beta checklist

1. Back up your in-game save. Continue an existing save and open the home PC. Withdraw training items, leave, reopen it, save and restart: the kit must not duplicate. Repeat in a separate new game.
2. Give each Power item to a Pokemon and check the corresponding IV/EV summary page before and after a battle. Test an EV-reducing berry and a Mint.
3. Redeem a Bottle Cap on one non-maxed IV, then a Gold Bottle Cap on all IVs. Try canceling and selecting a maxed stat; check that you keep your cap. Try a damaged and a fainted Pokemon: the service should not heal them.
4. Check the scientist's menus with an empty bag and a full party. Buy, sell, cancel, and return to the normal Mart clerk.
5. In a new game, try the Oak handoff from each regional starter display, with followers enabled and disabled. Watch for characters walking through objects or failing to release movement control.
6. Battle Brock. Confirm all four team members appear; lose, recover, retry, and win. Check the existing badge and one-time Rock Tomb reward after saving and restarting.
7. When a legendary test encounter is available, test ordinary and shiny previews, legal IV/EV limits, canceling, nicknames, a party vacancy, a full party sent to PC, and a party swap. Verify level, moves, capture ball, and appearance after reloading. Do not use old emulator save states across ROM versions.

## Development rule

Future Gym Leaders will use four Pokemon early, five in the middle gyms, and six late. Occasional partners outside their specialty add variety. Unrelated upstream trainer parties remain unchanged.

## Verification and limits

The packaged build report records exact source, results, output hash, warnings, and manual coverage. Engine tests and source/collision checks are distinct from a full emulator playthrough. No newly written feature should be described as manually playtested unless that run was actually performed.

The original Playtest 6 files and user saves are preserved. Follow the package's save-transfer instructions when using the separately named ROM.

## Continuing a save

With the emulator closed, back up your old `.sav`, then copy it beside the new ROM as `pokemon-three-horizons-playtest-7.sav`. If mGBA uses a custom save folder, put the copy there. Open the new ROM and choose Continue. Keep the originals. Use a separate new game to test Oak's handoff; an already-defeated Brock stays defeated. Use in-game saves instead of older emulator save states.

See [verification details](PLAYTEST_7_VERIFICATION.md) for automated results and remaining manual coverage.
