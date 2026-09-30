# Playtest 13 — The Road to Lavender

Verified software candidate, 2026-09-29. Exact post-Surge personal-save migration, its normal continuation to the Tower endpoint and back to Lavender, and the separate new-game route through Surge to the endpoint passed. RG40XX H Playtest 13 acceptance remains the owner's separate hardware test. Evidence and test limits are in PLAYTEST_13_VERIFICATION.md.

ROM: `pokemon-three-horizons-playtest-13-road-to-lavender.gba` (unchanged bytes
from the passing CI artifact). SHA-256:
`ad918b00e4476e9db68cb1445206ef1126e8d962be51cd74208442be3ff85077`.

## Prepare a safe test

Keep the Playtest 12 ROM and original battery save together in a backup folder.
Use a separate filename and folder for Playtest 13. Record the candidate ROM's
SHA-256 from its release manifest. Emulator save states are tied to the ROM that
created them: use New Game or an ordinary in-game Save followed by cold Continue.

For continuation, copy the battery `.sav`, rename the copy to match the new ROM's
base filename, start the ROM normally, and choose Continue. Compare party,
nicknames, levels, held items, moves/PP, boxes, money, items, badges and completed
events before walking. Save through the game menu, close the emulator, reopen,
and Continue again. Keep the original copy untouched. Temporary Vs. Seeker
readiness disappearing on Continue is intentional; trainer victories must remain.

The owner's accepted source is the raw 131072-byte VBA-Next EEPROM file
`pokemon-three-horizons-playtest-12-rocket-art.gba.eps`, SHA-256
`be9bbc4722188ce11ad86b6bcc34a89539a4572403cfade3330da75f1ccbadca`.
For desktop mGBA, copy those bytes to
`pokemon-three-horizons-playtest-13-road-to-lavender.sav` beside the new ROM.
Changing the working copy's extension is sufficient; do not convert the contents.
On RG40XX H/VBA-Next, use that core's battery-save directory and naming convention
(the P12 source used `.gba.eps`). Keep the P12 original and its ROM untouched.
The older Cerulean/P11-marked `.sav` files are superseded and are not acceptance
evidence for the owner's post-Surge progress.

For a new game, use a new save filename. Test at normal speed first. Keep separate
battery checkpoints before Brock, Mt. Moon's fossils/Rockets, Misty, Bill, the
ship rival, Surge, Rock Tunnel and the Tower barrier. Use copies for deliberate
losses and alternate choices, then return to the main route.

## Full new-game route: Pallet to the Tower endpoint

1. **Pallet and the laboratory.** Start a new game, choose an outfit/name and
   set the clock. Inspect the desktop, TV, clock and Town Maps. Watch the lab
   arrival: everyone should finish moving and face the speaker. Choose the
   first regional partner, inspect its Summary, and complete the opening rival
   battle. Save, cold Continue, and compare the partner's identity and moves.
2. **Route 1, Viridian and Route 22.** Follow the opening errands and exit
   dialogue. Heal with one Pokémon, then again with three and six as the party
   grows. Inspect Spearow and the Cut tree. Viridian Gym must stay locked at this
   stage. Take Route 22 for the optional rival; use a separate checkpoint to
   lose and retry. The League gate still requires eight badges. Return to town.
3. **Route 2 and Viridian Forest.** Read different signs and talk to trainers.
   Catch several distinct species, including a first Caterpie/Weedle/Pikachu
   when encountered. Let every first-catch Pokédex screen close before naming;
   try a maximum-length name and two Pokémon with the same nickname. Observe
   Treecko and Shroomish; these visible scenes are not catches. Continue north
   to Pewter. The optional Cut clearing is for the later backtrack.
4. **Pewter and Brock.** Try the eastern exit before the badge and check the
   guide. Visit the museum, upstairs and downstairs, its exhibits and greeting.
   Fight Brock, read badge/TM/gift dialogue, collect the next regional partner
   when offered, and speak to the gym guide again. Leave east without a flashing
   or reappearing guide. Check the two martial artists later on Route 4 for
   repeatable Mega Punch/Mega Kick lessons with compatible targets.
5. **Route 3 and Mt. Moon.** Fight trainers, heal at the entrance Center, and
   enter Mt. Moon. Check first catches, poison/confusion, Repel expiry and the
   option to reuse another Repel. Use the first side ladder to visit the three
   Clefairy and Makuhita; repeat the interaction and return by the ladder. Reach
   the fossil researcher from each approach on checkpoint copies: he challenges
   you before taking fossils, then permits both fossils after victory. Test the
   Jessie/James encounter with two conscious, non-Egg Pokémon for doubles. On a
   separate copy use only one eligible Pokémon for consecutive singles; losing
   the second battle must restart the encounter, without a free heal. Meowth
   speaks and does not fight. Leave Mt. Moon, inspect ledges/follower placement,
   and reach Cerulean via Route 4.
6. **Cerulean, bridge and Bill.** Heal, receive the aide's supplies once, and
   visit the Berry Workshop/Trainer Services. Beat Misty and check that her gym
   trainers leave a route to her. Check the police-gated house and regional gift.
   Fight the bridge rival, finish Nugget Bridge, then follow Route 25 to Bill.
   The Misty/rival order can be reversed on another save: neither announces an
   obsolete beta ending. Decline Bill once, then help. Save while he waits inside
   the machine, cold Continue, leave/re-enter, then use the PC. Collect the
   S.S. Ticket once. Fossil revival in Cerulean remains tied to the Misty gate.
7. **Route 5 to Vermilion.** Enter and leave Day Care from both sides. Try the
   Saffron guard, then take the Route 5 underground path to Route 6. Fight Keigo
   and the other ordinary trainers, and reach Vermilion. Heal; collect the
   Vs. Seeker from the Center scientist before Surge. Hear the Fan Club chairman's
   Rapidash story and receive one Bike Voucher. Collect the Old Rod. Return to
   Cerulean's bike shop when convenient: one voucher supplies both Mach and Acro
   Bikes; an old save owning one receives the missing one. Check cancel/repeat.
8. **S.S. Anne and Surge.** Keep the Ticket in the bag. Inspect the ticket
   check and gangway, explore cabins/deck, talk to the regional travelers and
   Marill/Wingull, and visit the healing room. Defeat the rival by the captain's
   stairs and watch him leave visibly. Help the seasick captain and obtain Cut.
   Finish optional ship rooms before leaving after obtaining Cut: the departure
   is one-time, so do not expect to board again. Bring HM01, the Cascade Badge
   and a conscious compatible Pokémon to the gym tree; it need not know Cut.
   Find the two adjacent switches, test a wrong second choice on a copy, then
   defeat Surge. Check the guide and one-time badge/TM receipt. Save in Vermilion.
9. **Diglett's Cave and the Route 2 backtrack.** Talk to the Vermilion scientist
   for Oak's lead. Head east to Route 11 and enter Diglett's Cave. Explore its
   length and leave at Route 2. Bring the Thunder Badge and at least ten distinct
   caught/received species to Oak's aide in the Route 2 passage. Receive Research
   Gear and HM05 Flash. Open Gear from Start, finish the activation call, and
   save/cold Continue. Return through the cave to Vermilion Harbor for the
   Marill/Wingull photo: the partners remain ashore after the ship departs.
   Decline once, return, accept, and confirm a repeat does not add another photo.
   In the nearby Route 2 house, the one-time trade is your Zubat for
   Skarmory: try cancel/wrong target before accepting with a disposable checkpoint.
   Cut back through Viridian Forest for Pinsir/Heracross, a photo and the research
   reward. Revisit earlier sightings now that Gear is available. Return north
   through Pewter, Route 3, Mt. Moon and Route 4 to Cerulean, or retrace the cave
   and the Vermilion/underground route. No Saffron shortcut is required.
10. **Route 9, Route 10 and Rock Tunnel.** Leave Cerulean east using Cut.
    Explore Route 9, ordinary trainers and the Mareep/Nidoran observation. Decline
    its photo once, revisit and accept. Reach Route 10's Center, heal, finish the
    professor update and save. Enter Rock Tunnel with HM05, the Thunder Badge
    and a conscious compatible Pokémon. Use Flash from its party menu while
    all four unrelated moves remain intact. Follow the native ladders through
    both floors; inspect Aron/Geodude and its photo. Optional checks include
    Escape Rope, re-entry, losing to a trainer, and saving in darkness and after
    Flash. Exit to southern Route 10 and continue south to Lavender.
11. **Lavender and Pokémon Tower.** Visit all buildings, heal, inspect Cubone
    and the missing-Fuji setup, and hear the conversation-only rival scene.
    Meet the Rocket trio's single cameo. Approach Misdreavus near the Tower;
    decline a photo, leave/re-enter, then accept and inspect its card. Finish the
    queued professor call. Enter Tower, talk to mourners and the record-taking
    Rocket, and climb floors 1–6. Fight Channelers and test the 5F purified zone.
    Without a Scope, wild ghosts are unidentified and cannot be caught. At the
    upper stairs, encounter the barrier ghost, retreat with Run, and read the
    one-time chapter completion/Celadon lead. Return to town, save, cold Continue,
    and revisit: the upper floor must remain blocked. This is the P13 endpoint.

## Continuation route for a migrated post-Surge Playtest 12 save

1. Follow the battery-copy procedure above. Confirm three badges, your established
   team/boxes and existing Bill, fossil, starter, Ticket and Cut progress. Completed
   one-time battles/gifts must not replay. Do not use the older Cerulean/P11-marked
   backup as a substitute for the exact post-Surge hardware save.
2. In Vermilion, heal and speak to the scientist for the Vs. Seeker and Route 2
   lead. Visit the Fan Club if its voucher is unclaimed. Cerulean's bike shop
   supplies a missing second bike without charging another voucher. Finish any
   reachable ship content before the approved departure; an old save inside the
   ship must retain a safe exit rather than become stranded.
3. Follow new-game steps 9–11 in full: Route 11 → Diglett's Cave → Route 2 aide
   and optional trade → Forest Cut clearing/backtracking → Cerulean → Route 9 →
   Route 10 → Rock Tunnel → Lavender → Tower barrier. Existing witnessed research
   can import as reports; photographs must be taken in P13 and must not be
   invented by migration. Revisit scenes for their optional pictures.
4. Cold Continue after receiving Gear, after a photo, after leaving the ship,
   after a rematch and after the Tower endpoint. Compare protected state again.
   Keep the before/after battery files with the exact ROM hash for the report.

## The 24 repair checks

Use checkpoint copies for alternate outcomes. A pass means the expected behavior
was observed; do not mark a check passed merely because its location was visited.

| Repair | What to verify |
|---|---|
| A Town Maps | Kanto display opens/closes and returns control |
| B TV | Tile remains intact after interaction and room re-entry |
| C Day Care | Both doorway directions return to the correct place |
| D Saffron | Guards block unsupported shortcuts with appropriate dialogue |
| E Pewter guide | Visible before Brock; clean exit afterwards |
| F Bridge rival | Correct loss/retry and progress dialogue in either Misty order |
| G Bill | Machine wait survives Save/Continue and leaving/re-entering |
| H Supplies | Already-received message; partial delivery retries only the remainder |
| I Ticket | Visible guard check; no boarding without Ticket |
| J Gangway | Ship exterior, walking route and follower align |
| K Ship rival | Actual departure after battle; corridor remains usable |
| L Captain | Seasick staging and one-time Cut handoff |
| M Farfetch'd | Visible beside the leek NPC with reachable interaction |
| N Machoke | Correct overworld size; no overlap blocking the room |
| O Gym guides | Brock/Misty/Surge victories acknowledged |
| P Cut text | Short explanation before access; no misleading trail claim |
| Q Cut state | Tree graphics/collision agree after movement, menus, re-entry and cold Continue; follower on/off |
| R Clefairy | Repeat animation returns everyone to valid positions |
| S Fossils | Scientist faces/challenges you; both fossils available only after victory |
| T Rockets | Doubles and one-eligible singles; loss/retry; one completion |
| U Run | Trainer Run rejected without a forced loss or blackout |
| V SELECT | Moves swap with correct PP, disabled/Encore state and battle continuation |
| W First catch | Pokédex transition completes before Yes/No and naming |
| X Departure | One ship departure, no stranded old save or repeat boarding |

## Encounter, research and system checks

Use [the generated encounter guide](PLAYTEST_13_ENCOUNTERS.md) for exact areas,
methods, time bands, levels and weights. Log a finite sample such as 30 encounters
per available table. Missing a rare species in that sample is not automatically
a bug. Check normal and maximum nicknames, duplicate names, full-party PC transfer,
evolution after battle/Candy/item, status damage, PP, and overworld follower return.
Use [the evolution QA](PLAYTEST_13_EVOLUTION_QA.md) for methods and availability;
not every compiled evolution family is obtainable before Lavender.

For every optional photo, test no Gear, No, Yes, repeat, reopening Gear and cold
Continue on copies where applicable. A photo card should depict its subjects and
show location, species, observation and professor note. Pinsir/Heracross,
Mareep/Nidoran and Aron/Geodude should each show both subjects. Calls should wait
for safe field control and finish once, without repeatedly interrupting doors,
battles, menus or healing. An old shared forest report must not invent either
specific observation or a photograph.

Visit accessible Centers upstairs and return by the stairs. Talk to attendants:
no real network session or communication wait should be required. Save upstairs
on a copy and cold Continue. Check day/night, each bike, follower off and a large
follower, and parties of 1/2/3/6. Separately vary usable counts with fainted Pokémon
and Eggs; party count alone is not the Rocket battle-format criterion.

## Reporting and RG40XX H acceptance

Record ROM filename/hash, device/core/version, New Game or battery Continue,
location, checkpoint, exact buttons/actions, party and conscious count, follower,
clock/boost settings, expected/actual result, and a screenshot or short video.
Keep a battery save immediately before a reproducible problem. Never overwrite
the only original save while preparing a report.

The project owner completed P12 on RG40XX H using VBA-Next. P13 needs its own
hardware pass: boot/New Game/Continue, sound, first-catch graphics/naming, both
Rocket formats, healing, Cut/Flash/followers, bikes, Gear/photos/calls, rematches,
Tower endpoint, and repeated in-game saves/cold boots. Desktop mGBA evidence
does not mark these hardware checks passed. gPSP compatibility is not claimed.

## Cerulean continuation check

Test both orders: beat Misty before the bridge rival, then repeat on a separate fixture with the rival defeated first. The second victory acknowledges your progress and points toward Bill; it must not announce a beta endpoint or promise a future bridge opening.

At Nugget Bridge, first lose to the rival. Continue from the Pokémon Center and return for the retry. Win, read the dialogue, and revisit the bridge. Confirm that the rival departs, the path stays open, and the encounter does not repeat after victory. The rival's partner and the existing loss/retry behavior remain unchanged.

Follow the route beyond Nugget Bridge to Bill's cottage, then continue with the full route above.

## Bill and supplies checks

Decline Bill's request once, then agree. After he enters the machine, save normally, close and reopen the ROM, and choose Continue. Leave the cottage and return before using the PC. Bill should still be inside the machine. Activate the PC, finish the rescue, and talk to the restored human Bill for the S.S. Ticket. Repeating the conversation or using the PC again must not duplicate Bill or the ticket. A full Key Items pocket must leave the ticket available for a later retry.

The scientist in Cerulean's Pokémon Center supplies ₽2,000 and two Ultra Balls once. If both were delivered earlier, the next visit explicitly acknowledges that. If a full pocket interrupted delivery, make room and return: only the missing component should be delivered.

## Keigo's approved first battle

Bug Catcher Keigo on Route 6 now uses Kakuna, Beedrill and Butterfree, all level 18.
This is his first-fight roster, separate from the later Vs. Seeker scaling feature.
Check normal experience awards, battle dialogue and the defeated-trainer receipt.
Neighboring trainers retain their previous first-fight teams. Native generation
and the focused actual first battle passed; the complete new-game route also
reached the Tower endpoint. See the verification record for evidence boundaries.

### Vs. Seeker systems acceptance route

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
