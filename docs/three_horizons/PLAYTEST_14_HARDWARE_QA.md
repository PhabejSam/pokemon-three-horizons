# Playtest 14 — RG40XX H acceptance

Feature and compiled/test revision: `abdec6f2508bbf2d4f1c104d863e5908281f6f6e`.

ROM: `pokemon-three-horizons-playtest-14-celadon-silph-scope.gba`

SHA-256: `7e9e18bcb30026a47c9e46e187f8a1ba906e431682eb704b48c2ed8fd67a77a7`.

This candidate passed the recorded automated and mGBA checks. RG40XX H/VBA-Next acceptance remains **PENDING**; the intermittent full-party Ekans capture report is **HIGH / unresolved**. Use normal speed first.

## Short hardware acceptance run

Use a copied battery and this exact ROM; retain the old ROM/save. Turn off
cross-build state auto-resume. Log the RG40XX H OS/core name/version and any
speed/rewind settings. Start at normal speed. These checks target hardware and
normal play; you do not need to repeat the automated420-slot or all-Ball tests.

| Checkpoint | Check | Expected result | Result / evidence |
|---|---|---|---|
| First Continue | Boot supplied PT13.1 copy normally | Tower6F, three badges, original team/boxes/items/money/earlier progress intact | PENDING owner |
| Native save | Save, fully close core, reopen and Continue | Same earned state, no warm-state dependency | PENDING owner |
| Gear | Research Log/Field Photos/Calls, page/back/wrap, old photos | Three modules; clear text/art, field palettes and controls restored | PENDING owner |
| Capture priority | Route11 Ekans with six party Pokémon, first-catch/nickname/replacement | No corrupt sprite, black screen, lost Pokémon or freeze; party and destination box correct after cold reload | PENDING; HIGH unresolved report |
| Town Map/trees | Daisy/Oak catch-up; Kanto map; Route9 Cut and Viridian/Forest trees | Once-only map; graphics/collision agree before/after menu/map/cold changes, follower on/off | PENDING owner |
| Flash/rematch | Route2 aide, Rock Tunnel Flash, ordinary beaten trainer | Clear supply message; field use with HM/badge/compatible conscious mon; rematch dialogue; first battles unchanged | PENDING owner |
| Gate before Flute | Route11 east gate both floors and sleeper | Gate traversable; sleeping Snorlax blocks road | PENDING owner |
| Celadon | Doors, stairs/elevators, Center, Mansion, restaurant | Correct destinations, safe return, Eevee/Case once-only | PENDING owner |
| Stores/prizes | Buy/cancel, three→four-badge TM stock, drink exchange, coin purchase/prize | Correct charges/rewards, reusable-TM duplicate protection, no dialogue/menu corruption | PENDING owner |
| Erika/Hideout | Main route and useful loss checkpoint | Victory-only badge/rewards; spinner/lift/guards work; two-usable trio doubles; loss retry | PENDING owner |
| Scope | Giovanni, pickup, save/cold | Scope retained, no repeated reward; identified wild ghosts catchable | PENDING owner |
| Mother | Reveal, mandatory photo, try one Ball, win and pause/fade | Spirit uncatchable, photo retained, peaceful disappearance; no immediate call | PENDING owner |
| Mother archive | Front/details/note with your outfit; return to field | Native image readable, correct observer, tint restored | PENDING owner |
| Fuji | Three upper Rockets, rescue warp, home thanks/Flute | Automatic home conversation; once-only Flute; full-pocket retry if encountered | PENDING owner |
| Snorlax | Decline then wake; catch or win; optional flee/loss copy | Only catch/win clears road; failed outcomes retry; former tile/Leftovers and both maintenance barriers work | PENDING owner |
| Ending cold save | Save on opened landing, close/reopen | Party/boxes, badge4, Scope/Flute, mother/Fuji/Snorlax receipts and purchases survive | PENDING owner |

## If the capture issue appears

Do not overwrite the last good battery. Note whether the species was already
seen/caught, whether the nickname screen appeared, chosen replacement slot,
party size and last input. Capture a photo/video if possible. Preserve both
last-good and affected copies with the ROM hash. Report a failure even if a
second attempt works. The mGBA attempt passed; that does **not** close the
owner-reported intermittent RG40XX H/VBA-Next defect.

## Defect report template

- ROM filename and SHA-256:
- Hardware/OS/core/version:
- New game or migrated battery; checkpoint name:
- Map, party size, lead Pokémon, settings (speed/rewind/follower/time):
- Last actions/buttons, including nickname and replacement slot if relevant:
- Expected result:
- Actual result:
- Reproduces ___ out of ___ attempts; does cold Continue change it?
- Screenshot/video and last-good battery copy available:

## Scope and limitations

The [full walkthrough](PLAYTEST_14.md) supplies new-game and exact-owner routes.
The checked emulator route starts from the supplied Tower save; the new-game
emulator test covers the opening and all nine starters, not a full new-game
journey. Adversarial fixtures and automated results are separate in
[verification](PLAYTEST_14_VERIFICATION.md). No handheld pass is recorded yet.
Saffron, extended Route12/Fuchsia, later regions and ultimate story answers
are outside PT14. Surf access is not newly provided. The western boundary and
landing maintenance barricades are deliberate. Dratini/Scyther/Porygon later
non-prize sources and an alternate later Snorlax remain unimplemented obligations.
