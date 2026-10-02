# Playtest 14 — full beta walkthrough

Feature and compiled/test revision: `abdec6f2508bbf2d4f1c104d863e5908281f6f6e`.

ROM: `pokemon-three-horizons-playtest-14-celadon-silph-scope.gba`

SHA-256: `7e9e18bcb30026a47c9e46e187f8a1ba906e431682eb704b48c2ed8fd67a77a7`.

This candidate passed the recorded automated and mGBA checks. RG40XX H/VBA-Next acceptance remains **PENDING**; the intermittent full-party Ekans capture report is **HIGH / unresolved**. Use normal speed first.

## Before starting

Keep the existing ROM and battery untouched. New Game needs a separate blank save;
continuation uses a copy of the existing battery. Never transfer an emulator
save-state between ROM builds. In mGBA, put the copied `.sav` beside the new ROM
with the same base filename, then start the ROM and choose Continue. On the
RG40XX H, use VBA-Next's battery directory and its existing naming convention
(the supplied file uses `.gba.eps`). Disable automatic state resume for this
check. Close the emulator before copying a battery.

The supplied continuation source is
`pokemon-three-horizons-playtest-13-1-road-to-lavender.gba.eps`,131072 bytes,
SHA-256 `e94846ce281dc01c245f1fdeabf300b350433fda5a1368924767a3de41536ef2`.
Do not overwrite it or substitute an older Cerulean save. Back up each new
checkpoint after the game's Save completes and the emulator closes.

Keep checkpoints before fossils/Rockets, Bill, ship departure, Surge, Celadon,
Hideout B4F, mother, Fuji and Snorlax. Alternate loss/cancel tests use copies.
A checkbox is a requested test, not a declaration that you have passed it.

## Opening configuration checks

- [ ] Inspect all three lab displays on separate opening copies: Kanto has
  Bulbasaur/Charmander/Squirtle; Johto Chikorita/Cyndaquil/Totodile; Hoenn
  Treecko/Torchic/Mudkip. Cancel before confirming once; no Pokémon or story
  receipt should be granted. Keep one chosen main playthrough.
- [ ] In the partner editor, compare defaults with Shiny Yes, a chosen nature
  and an available ability. IVs clamp0–31 each; EVs clamp0–252 each and510 total.
  Save/reopen and compare Summary and the IV/EV display. Gender is random;
  there is no gender selector. No partner system was redesigned for PT14.
- [ ] Try a12-character nickname; separately accept the default name. Starter
  gifts after Brock/Misty and rare wild starters remain distinct systems.
- [ ] Bedroom dresser changes among seven outfits. Clock, laptop and TV return
  control. First PC visit puts Macho Brace, six Power items and EXP. Share in
  ITEM STORAGE beside the starting Potion. Withdraw an item and revisit: the
  kit must not duplicate. Bag use controls the party EXP. Share.
- [ ] Open Options, use L/R for the Three Horizons page, and test Auto-run,
  experience rate, follower, clock mode and shiny odds. Choose your preferred
  settings, native Save, close/reopen and compare. Record the settings for
  encounter tests; avoid changing them mid-sample.

## Full new-game beta route

1. **Pallet and the laboratory.** Start a new game, choose an outfit/name and
   set the clock. Inspect the desktop, TV, clock and Town Maps. Watch the lab
   arrival: everyone should finish moving and face the speaker. Choose the
   first regional partner and inspect its Summary. After partner/Pokédex setup,
   Oak gives free Research Gear before you leave the laboratory. Open it from
   Start and check Research Log, Field Photos and Calls; Oak is introduced, while
   Elm/Birch await their own milestones. Complete the opening rival
   battle. Visit Daisy in the house northeast of yours for the Town Map; repeat
   the conversation and inspect the table map. Oak later offers a missing-map
   catch-up. Open the Town Map from Bag and registered Select: it shows Kanto.
   Save, cold Continue, and compare the partner's identity and moves.
2. **Route 1, Viridian and Route 22.** Follow the opening errands and exit
   dialogue. Heal with one Pokémon, then again with three and six as the party
   grows. Inspect Spearow and the Cut tree. Viridian Gym must stay locked at this
   stage. Observe and optionally photograph Route 1's Hoothoot; Elm introduces
   his Johto research after the scene when field controls are safe. Take Route 22 for the optional rival; use a separate checkpoint to
   lose and retry. The League gate still requires eight badges. Return to town.
3. **Route 2 and Viridian Forest.** Read different signs and talk to trainers.
   Catch several distinct species, including a first Caterpie/Weedle/Pikachu
   when encountered. On a first catch, continue holding A or pressing rapidly:
   the completed Pokédex entry must remain visible until input is released,
   then a fresh A/B dismisses it. Test nickname Yes and No separately;
   try a maximum-length name and two Pokémon with the same nickname. Observe
   Treecko and Shroomish; these visible scenes are not catches. Decline a photo
   once, reaccept, then check the card and its details/notes in Gear. Compare
   field brightness before/after every flash. Continue north
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
   Clefairy and Makuhita; photograph them, hear Birch's individual Hoenn call,
   repeat the interaction and return by the ladder. Reach
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
   caught/received species to Oak's aide in the Route 2 passage. Receive HM05
   Flash and research guidance; Gear was already supplied in the lab. Neither
   teaching Flash nor freeing a move slot is needed. Save/cold Continue.
   Return through the cave to Vermilion Harbor for the
   Marill/Wingull photo: the partners remain ashore after the ship departs.
   Decline once, return, accept, and confirm a repeat does not add another photo.
   In the nearby Route 2 house, the one-time trade is your Zubat for
   Skarmory: try cancel/wrong target before accepting with a disposable checkpoint.
   Cut back through Viridian Forest for Pinsir/Heracross, a photo and the research
   reward. Revisit earlier sightings to fill missing photos. Return north
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
    upper stairs, approach the barrier, read the Scope/Celadon lead, and leave
    normally. This pre-Scope barrier does not start a battle. Return to town, save, cold Continue,
    and revisit: the upper floor must remain blocked. In PT14, continue west toward Celadon below. The earlier chapter lead is replaced by the in-world Scope/Rocket lead.

12. **West from Lavender to Celadon.** Exit Lavender west onto Route8.
    Known dialogue issue: the worker still says the west road is closed; this
    line is outdated. The western exit is open; the southern road stays closed.
    Fight its ordinary trainers and test one Vs. Seeker rematch after winning.
    Eli & Anne share one battle history; approach each twin, and try insufficient
    usable party on a checkpoint. The Saffron gate stays restricted. Use Route8's
    underground entrance, traverse the east–west tunnel, exit onto Route7, then
    walk west into Celadon. Read signs and try reciprocal doors. Heal and save.
13. **Explore Celadon.** The scientist and city Rockets currently repeat their
    earlier dialogue after the Scope recovery; this is a known deferred issue.
    Visit the Center, restaurant, hotel, houses, Mansion
    and Department Store. The restaurant supplies the Coin Case once. Enter the
    Mansion from its rear route to the roof room for Eevee Lv25; with six party
    members it goes to the PC. Inspect the front route and safe return. Tour
    Store floors1–5, roof and elevator; select multiple destinations and cancel.
    The third-floor Counter tutor is free/repeatable for compatible Pokémon.
    Soft-Boiled's city tutor retains the native water-access footprint; no Surf
    unlock is added, so it is not a required reachable PT14 lesson.
14. **Shop and prize checks.** On2F, buy a useful supply and inspect the reusable
    TM catalogue. Three badges show Roar/Dig/Brick Break/Secret Power/Attract;
    four additionally show Hyper Beam/Protect/Rest. Scope is not a stock gate.
    Compare money and item counts, cancel once, and try an already-owned TM
    (Bag or PC). On4F inspect Fire/Thunder/Water/Leaf Stones. Roof drinks cost
   200/300/400; give Fresh Water/Soda Pop/Lemonade to the girl for Light Screen/
    Safeguard/Reflect respectively. Full TM pocket must leave drink/reward pending.
    Visit the Game Corner and Prize Corner with Coin Case in Bag; buy coins,
    try a slot machine/cancel, and inspect Pokémon/TM/item counters. Abra Lv9
    costs180 coins; compare coins, party/PC destination and nickname. Consult
    the TM and encounter guides for all prizes. Native Save and cold Continue.
15. **Erika, fourth Gym.** Use Cut to enter the southern Gym, talk to the guide,
    fight trainers and reach Erika. Her first party is Victreebel Lv29,
    Tangela Lv24 and Vileplume Lv29. Victory gives the Rainbow Badge and TM19
    Giga Drain once. Re-talk after victory; if the TM pocket was full, make room
    and retry without replaying the boss. The guide and Gym statues acknowledge
    victory. Revisit2F for the new four-badge stock. Erika can be beaten before
    or after the Hideout; use a separate checkpoint to test the reverse order.
16. **Rocket Hideout.** Defeat the Game Corner poster guard and inspect the
    poster switch. Descend behind it, explore B1F–B4F, collect reachable balls,
    and follow the spinner puzzles to the B4F Lift Key grunt. Talk again after
    beating him so the key is dropped; collect it before using the elevator.
    A full Key Items pocket must leave the drop retryable. Read the three
    optional research records about marked sightings, unconfirmed reports and
    orders to compare evidence without assuming a cause. Test elevator B1F/B4F,
    cancelling and returning safely. Defeat both guards at the boss corridor.
    Bring **two usable non-Egg Pokémon** for Jessie and James's mandatory doubles;
    an insufficient party is stepped safely back for healing. Meowth talks and
    does not battle. Loss leaves the encounter retryable; victory removes the trio.
17. **Giovanni and the Scope.** His first party is Onix Lv25, Rhyhorn Lv24 and
    Kangaskhan Lv29. Defeat him and collect the Silph Scope. A full pocket must
    not lose the reward: make room and collect/re-talk. Repeat dialogue points
    toward the Tower without revealing the cause of the wider phenomenon.
    Save, close, reopen, confirm Scope and defeated history. Return through
    Route7 → underground tunnel → Route8 → Lavender. If Erika was skipped,
    beat her and verify her badge/TM separately; neither order blocks the other.
18. **Return to Pokémon Tower.** Compare ordinary wild encounters before and
    after Scope: identified species now follow normal catch rules. The scripted
    mother is separate. Climb to6F using5F's purified healing zone. Approach the
    upper stair barrier. If Gear is missing, speak to the ground-floor aide
    beside the entrance route (map position5,11), then return. Scope reveals
    Cubone's mother, takes the required **MOTHER'S WATCH** record/photo, and starts
    the Lv30 female Serious Marowak battle. This scene has no optional photo
    decline. Try one ordinary Ball on a checkpoint: it is dodged and no capture
    or caught-Dex credit is awarded. Win to calm her; wait through cry, pause and
    quiet disappearance. No immediate professor call interrupts the moment.
    On a separate copy, lose once: the photo remains but stairs stay blocked
    until a winning retry. Inspect the archive photo, details and later note.
19. **Fuji and the Flute.** Ascend to7F, defeat its three Rockets, and speak to
    Fuji. The rescue returns you to the Volunteer Pokémon House, where his
    thanks and Poké Flute handoff run automatically. If Key Items is full, free
    a slot and talk to him again. Repeat visits give no duplicate. Check Cubone,
    local reactions and the quiet archive note after rescue. Save in the house,
    close completely, Continue and compare the Flute and mother/Fuji progress.
20. **Route11 gate and Snorlax.** Backtrack through Rock Tunnel → Route10 →
    Route9 → Cerulean → Route5 underground → Route6 → Vermilion → Route11.
    Explore the east gate's two floors. The aide gives Itemfinder at30 distinct
    caught/received species, including supported visitors; full-pocket delivery
    retries. The upstairs trade is your Nidorino for NINA the Nidorina; try
    cancel/wrong species on a copy before accepting. Neither service opens the
    full later-generation Dex. Continue through the gate to the sleeper.
    Before Flute it blocks passage. With Flute, decline once, then play it and
    battle Snorlax Lv30. Only capture or victory clears the footprint. Escape,
    loss or blackout must leave a retryable sleeper. Use copies for these outcomes.
    If catching, check first-catch entry, nickname, full-party/PC destination and
    cold persistence. Search its former tile for the one-time Leftovers. Walk
    both short bridge sections, read the visible maintenance barricades and
    return safely. This is the bounded playable end; later Route12, Saffron and
    Fuchsia travel are not implemented. Native Save, close and Continue here.

## Exact supplied-save continuation

1. Copy the131072-byte source named above to this ROM's battery name. Start
   normally and choose Continue. Expected location: **Pokémon Tower6F (11,14)**,
   three badges, existing established team. Compare nicknames/species/levels,
   nature/ability/IVs/EVs, held items/moves, money, Bag/PC items, boxes, Dex and
   earlier fossil/Rocket/ship/gift progress. Keep your existing over-levelled
   team; migration does not scale it down or replace it.
2. Open Gear and inspect your existing observations/photos/Calls. Leave6F
   through the preceding floors and heal in Lavender. The Scope story has not
   yet been completed. You can return west directly for the main chapter, but
   the recommended repair backtrack checks the earlier fixes first.
3. Backtrack naturally north through southern Route10 → Rock Tunnel → northern
   Route10 → Route9 → Cerulean. Use Cut/Flash with your existing HM/badge/compatible
   party checks. Visit Oak in Pallet for a missing Town Map (or Daisy), using
   the existing route through Route4/Mt. Moon/Pewter/Forest. Inspect the Viridian
   clearing and Forest trees. No warp cheat or cross-ROM state is required.
4. Return via Cerulean/Route5 underground/Route6 to Vermilion, or the Route2
   Diglett's Cave connection. Revisit the Flash aide and Vs. Seeker greeting.
   Route11's gate is accessible, but Snorlax stays asleep until Flute. Save a
   repair checkpoint, then retrace Rock Tunnel to Lavender.
5. Follow new-game steps12–20 exactly: Celadon services, Erika/Hideout in either
   order, Scope, mother, Fuji, Flute and Snorlax. The checked natural owner route
   used Erika first. Save/cold Continue after Celadon purchases, Scope, Fuji and
   the opened road. Existing one-time rewards must not replay.
6. Compare each post-save state with what you actually earned. Battles naturally
   change EXP/EVs/HP/PP/friendship; purchases/balls/Repels change inventory and
   money; migration itself must not invent these changes. Keep before/after
   copies for a reproducible report. Do not overwrite the original `.eps`.

## Focused edge cases and encounter sampling

- Use [the generated encounter tables](PLAYTEST_14_ENCOUNTERS.md). Sample30
  encounters per available table for a practical pass, logging species/level,
  method/time, lead level/ability and Repel. A rare species need not appear in
  that sample. The10% HA roll applies only where an HA exists; a few captures
  cannot establish its probability. Wild starters retain ordinary random stats.
- Test one first-catch Dex screen by holding A: release, then make a fresh press.
  Try nickname Yes/No,12 characters, duplicate names, six party members, a
  replacement from first/middle/last position, and cancelling party replacement.
  Check the sent Pokémon in its box before and after a native cold reload.
  **Stop and preserve a checkpoint if corruption/black screen occurs.**
- Ordinary poison should tick after battle under the configured field rules;
  compare visible HP. Distinguish a contact poison applied to the active battler
  from residual damage for a switched-out Pokémon. Confusion may legitimately
  fail to cause self-damage in a small sample.
- Ordinary Vs. Seeker rematches need previous defeat; immediate repeated use is
  allowed. First parties stay authored. Readiness resets on map change/cancel/
  completed rematch/blackout/cold Continue, while defeat history remains. Use
  the [rematch addendum](PLAYTEST_13_REMATCH_CAPACITY.md) for25 stone tiers.
  Bosses/rivals/Jessie/James and story encounters are excluded.
- After cutting a tree, check graphics and collision while walking, opening
  Gear/Bag, changing maps and cold reloading; test follower on/off. Optional
  research can be declined and revisited; the mother photo is the required
  exception. Verify field tint after camera flash and menus.
- To exercise full-pocket/PC failures without cheats, use a disposable mature
  save only if already near capacity. Do not fill420 slots just to repeat
  automated coverage; the hardware checklist prioritizes normal play.

## Evidence and remaining acceptance

The fixture-free owner continuation and focused opening/all-nine choices ran
in mGBA on this exact hash. Full natural new-game Pallet-to-endpoint play is
provided for your beta run; it was not completed by the emulator controller.
Labelled adversarial fixtures are listed separately in
[verification](PLAYTEST_14_VERIFICATION.md). Finish the short
[hardware checklist](PLAYTEST_14_HARDWARE_QA.md) before calling the build accepted
on RG40XX H. The unresolved capture report and future access obligations remain
visible there. No integration or remote publication has occurred.
