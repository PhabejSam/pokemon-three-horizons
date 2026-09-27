# Playtest 12 — continuation and repair checks

Build status: playable candidate through Lt. Surge. See PLAYTEST_12_VERIFICATION.md for the exact tested ROM, evidence and remaining limitations. Jessie and James still use the earlier grunt artwork: the replacement sprite request was blocked by the image service and is not complete.

## Continue your Cerulean save

Back up your original ROM and battery save. Put a copy of the in-game `.sav` beside the new ROM with the same base filename, start the ROM normally, and choose **Continue**. Do not load a Playtest 8–11 emulator state into this build. Starting a new game is also fine; use a separate filename to keep your existing save safe.

1. Check your party, boxes, badges, money and items before moving. The Cerulean Center aide delivers the one-time two Ultra Balls and 2,000 money if you have not received them.
2. Cross Nugget Bridge, finish the five challenges and recruiter, then follow Route 25 to Bill. Help with the machine and collect the S.S. Ticket. Re-enter and check that Bill remains human and the ticket is not duplicated.
3. Go south through Route 5, the underground path and Route 6 to Vermilion. Heal, visit the Fan Club for the Bike Voucher, and collect the Old Rod from the fishing house. The Cerulean bike shop exchanges the voucher for a bike.
4. Board the S.S. Anne. Explore cabins, try a healing room, and hear the shipping report. Fight the rival near the captain; his partner should match the earlier battles. Help the captain and receive HM01 Cut. The ship stays docked.
5. Bring a conscious Pokémon compatible with Cut. With HM01 and the Cascade Badge, use Cut at the gym tree without teaching it or replacing a move. An incompatible, fainted or Egg-only party must not qualify.
6. Solve the two adjacent switches in Lt. Surge’s gym. A wrong second choice resets both; opening both stays open after leaving. Beat his five-Pokémon team and collect the Thunder Badge and reusable Shock Wave TM.
7. Talk to the professor’s aide in Vermilion. Save in-game, close the emulator, start it again and choose Continue twice. Check the badge, TM, ticket, bike, rod, team and completed events again.

## Optional fresh-game repair pass

- Watch the lab arrival in several outfits: the player should finish walking, face the speaker and stand still.
- Catch a first Pidgey, Caterpie, Weedle, Pikachu and both Nidoran. Watch the Pokédex opening **and closing**, then nickname them, including maximum-length names. Try normal button presses and quick repeated A presses.
- Change shiny gift previews through Nature, Ability, IV and EV pages. Check that their colors remain stable, then inspect the received Pokémon.
- Visit the museum, go upstairs and back, leave and re-enter. Check the greeting and Brock’s badge-before-TM presentation.
- Observe Treecko and Shroomish in the forest, and the three Clefairy with Makuhita in the side chamber reached from Mt. Moon’s first ladder along the entry route. Keep the ladder and item route accessible with a follower.
- Challenge Jessie and James with two usable Pokémon, then on a separate save try one usable Pokémon. The latter should require consecutive Ekans and Koffing battles, with no free healing. Lose to James and retry: both battles must restart. Meowth speaks but does not fight.
- Check the two opponents’ ball groups, trainer approach facing, reusable TMs, six Power items and evolution returning to the current battle music.

## Training and names

Duplicate nicknames are allowed; two Rattata can have the same name without sharing their stats or identity. A maximum-length nickname is also valid.

Power items add 8 EVs in their associated stat after an eligible battle, in addition to the defeated species' normal EV yield. For example, Rattata gives 1 Speed EV, while a held Power Lens adds 8 Special Attack EVs. Power Bracer adds Attack, Belt Defense, Lens Special Attack, Band Special Defense, Anklet Speed and Weight HP. The stat cap is 252 and the total cap is 510. Experience speed does not multiply the Power item's base bonus; other configured EV multipliers still apply.

The starter typings and move changes apply throughout the game, including existing teams, rivals and wild catches. The supplied starter reference lists the changes. Wild starters have ordinary capture stats; the three regional gifts remain available. Visible research-scene Pokémon are story characters, separate from the rare wild encounters.

## Report a problem

Record the exact ROM filename, emulator/core and device, whether you used New Game or Continue, where you were, the last action, your team, and whether follower/fast clock/experience boosts were enabled. For a freeze or graphics flash, a short video or screenshot plus a copy of the battery save before the event is especially useful.

Anbernic RG40XX H hardware testing is still a tester task; desktop emulator results do not prove handheld behavior.
