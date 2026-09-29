# Playtest 13 — The Road to Lavender

Development checklist; the release candidate and complete walkthrough are not yet approved for acceptance.

## Cerulean continuation check

Test both orders: beat Misty before the bridge rival, then repeat on a separate fixture with the rival defeated first. The second victory acknowledges your progress and points toward Bill; it must not announce a beta endpoint or promise a future bridge opening.

At Nugget Bridge, first lose to the rival. Continue from the Pokémon Center and return for the retry. Win, read the dialogue, and revisit the bridge. Confirm that the rival departs, the path stays open, and the encounter does not repeat after victory. The rival's partner and the existing loss/retry behavior remain unchanged.

Follow the route beyond Nugget Bridge to Bill's cottage. Further Playtest 13 checks will be added as their implementation and verification gates pass.

## Bill and supplies checks

Decline Bill's request once, then agree. After he enters the machine, save normally, close and reopen the ROM, and choose Continue. Leave the cottage and return before using the PC. Bill should still be inside the machine. Activate the PC, finish the rescue, and talk to the restored human Bill for the S.S. Ticket. Repeating the conversation or using the PC again must not duplicate Bill or the ticket. A full Key Items pocket must leave the ticket available for a later retry.

The scientist in Cerulean's Pokémon Center supplies ₽2,000 and two Ultra Balls once. If both were delivered earlier, the next visit explicitly acknowledges that. If a full pocket interrupted delivery, make room and return: only the missing component should be delivered.

## Keigo's approved first battle

Bug Catcher Keigo on Route 6 now uses Kakuna, Beedrill and Butterfree, all level 18.
This is his first-fight roster, separate from the later Vs. Seeker scaling feature.
Check normal experience awards, battle dialogue and the defeated-trainer receipt.
Neighboring trainers retain their previous first-fight teams. Native generation
verification is being completed; the full new-game emulator route remains pending.

### Vs. Seeker systems acceptance route (candidate checks pending)

1. On your first Vermilion visit, talk to the scientist in the Pokémon Center's
   open floor, left of the central Poké Ball pattern. Receive the Vs. Seeker
   before fighting Surge. Talk again: receive advice without a duplicate item.
2. Register it from Key Items. Near an ordinary trainer you previously defeated,
   press SELECT. Watch the trainer's response, then speak to them for a rematch.
   Use it again immediately afterward: no walking or recharging is required.
3. Try an unbeaten ordinary trainer: the first battle must retain its original
   team. Try Brock, Misty, Surge, a rival, or the fossil researcher: none should
   become an ordinary rematch opponent.
4. Repeat with Rick in Viridian Forest, a Route 3 trainer, an ordinary Mt. Moon
   grunt, Luis in Cerulean Gym, a Route 24/25 trainer, and a Route 6 trainer. Ship
   trainers are available while the ship remains docked. Cave and indoor trainer
   locations support the same scan.
5. With a low-level party, verify the rematch never falls below the original
   team's levels. With a strong party, verify the strongest opposing member is
   roughly ten levels below your highest non-Egg, limited to level 24 before
   Surge or 35 at three badges. Early bugs and Rattata can use their authored
   evolved forms. A high-level Egg must not raise the rematch level.
6. Scan, leave the map, and return: readiness must be gone. Scan, save through
   the game menu, close the emulator, and Continue: readiness must also be gone,
   while the trainer still remembers being defeated. Scan again to rematch.
7. Lose a rematch and return from the Pokémon Center: the trainer stays defeated
   and can be invited again. Winning a rematch must not repeat story gifts,
   badges, fossils, or one-time rewards.
8. Use the item with nobody eligible nearby: receive a useful no-target message
   and regain control. Try it again immediately in a valid area.

The disappearance of temporary readiness after Continue is intentional. It does
not reset trainer victories or story progress. Full capacity and tuning details
are in [the rematch decision](PLAYTEST_13_REMATCH_CAPACITY.md).
