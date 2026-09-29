# Playtest 13 — The Road to Lavender

Development checklist; the release candidate and complete walkthrough are not yet approved for acceptance.

## Cerulean continuation check

Test both orders: beat Misty before the bridge rival, then repeat on a separate fixture with the rival defeated first. The second victory acknowledges your progress and points toward Bill; it must not announce a beta endpoint or promise a future bridge opening.

At Nugget Bridge, first lose to the rival. Continue from the Pokémon Center and return for the retry. Win, read the dialogue, and revisit the bridge. Confirm that the rival departs, the path stays open, and the encounter does not repeat after victory. The rival's partner and the existing loss/retry behavior remain unchanged.

Follow the route beyond Nugget Bridge to Bill's cottage. Further Playtest 13 checks will be added as their implementation and verification gates pass.

## Bill and supplies checks

Decline Bill's request once, then agree. After he enters the machine, save normally, close and reopen the ROM, and choose Continue. Leave the cottage and return before using the PC. Bill should still be inside the machine. Activate the PC, finish the rescue, and talk to the restored human Bill for the S.S. Ticket. Repeating the conversation or using the PC again must not duplicate Bill or the ticket. A full Key Items pocket must leave the ticket available for a later retry.

The scientist in Cerulean's Pokémon Center supplies ₽2,000 and two Ultra Balls once. If both were delivered earlier, the next visit explicitly acknowledges that. If a full pocket interrupted delivery, make room and return: only the missing component should be delivered.
