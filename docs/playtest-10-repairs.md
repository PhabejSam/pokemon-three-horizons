# Playtest 10 — repair pass

This build repairs the existing Pallet-to-Cerulean playtest. The next story
chapter is not included. Keep your previous ROM and saves as backups.

## Move your progress safely

An emulator save state contains the old game's running scripts, graphics and
memory. Renaming it does not upgrade it to a new ROM.

1. Open the original Playtest 8 ROM and load your matching old emulator state.
2. Save through the game's own SAVE menu, then close the emulator normally.
3. Back up that in-game `.sav` file. Copy it beside this ROM with the same
   filename stem. On the handheld, use the save folder for the selected GBA
   emulator/core; it may use `.srm` rather than `.sav`.
4. Start the new ROM from its title screen and choose Continue. Do not load
   the old emulator state or allow an automatic resume state to override it.
5. Check your location, team, badges and items, then save in a new backup slot.

The first normal Continue on this version rebuilds the map's NPCs so removed
characters do not leave stale objects in the save. Persistent rewards remain.

## Changes to check

- Gift and purchased partners now say whether they joined the party or went
  to the PC. A full PC must not consume the reward or the Magikarp payment.
- Newly purchased golden Magikarp has Rattled and evolves into Moxie Gyarados.
  Existing purchases keep their ability; use an Ability Patch to change it.
- Wild Pokémon with a Hidden Ability have a 10% chance of receiving it.
  Normal ability slots share the remaining chance. Species without a Hidden
  Ability keep their normal abilities. Existing caught Pokémon are unchanged.
- The training shop sells Ability Capsules (2,000) and Patches (4,000).
  General marts sell Repels and Super Repels.
- Museum admission is free. Exhibits and residents have appropriate dialogue;
  Nidoran and Slowbro cry when spoken to. The duplicate Brendan objects and
  obsolete Pewter demo hosts are removed.
- Route 3's Oran Berry becomes a Potion; the Route 4 Persim Berry becomes a
  Super Potion; Mt. Moon's duplicate Escape Rope becomes a Super Repel.
  Already collected pickups remain collected.
- Blue approaches from the west on Route 22 and from the north in Cerulean.
  Mt. Moon grunts and Cerulean Gym trainers have corrected sightlines.
- Misty's victory speech and Cascade Badge precede the Water Pulse TM.
  The police officer blocks the robbed house until Misty is defeated.
- The Cerulean Rocket returns Dig immediately after defeat. If the bag is
  full, make space and talk again. A previously defeated Rocket can also give
  this missing reward once after upgrading.
- In-battle evolution restores the track that was playing before evolution,
  including the victory music after the final knockout.
- The Route 4 stair has a complete blocked border around its walkable steps.

## Focused beta route

1. Continue a backed-up in-game save in Pewter. Check the museum, Nidoran and
   caretaker; leave and re-enter town. No demo hosts should flicker back.
2. With six party members, receive an available gift and buy Magikarp. Confirm
   the PC message, nickname, stats and Rattled in Summary. Try these with party
   space on a separate save. Confirm a second conversation cannot duplicate it.
3. Compare golden Magikarp and ordinary Magikarp as followers in daylight.
   The shipped shiny follower already uses the gold palette; night tint can
   make it look orange. Record the time if a color still looks wrong.
4. Test Capsule/Patch changes, a Repel, and a ten-character caught nickname.
   Wild Hidden Abilities are random; a handful of catches cannot establish odds.
5. On a save where each rival is unbeaten, cross the Route 22 upper path and
   Cerulean bridge entrance. Blue should approach, battle, leave and stay gone.
   Test with followers on, and intentionally lose once on a backup.
6. Let a Mt. Moon grunt and each Gym trainer spot you. They should walk along
   clear ground and begin battle without getting stuck against water or walls.
7. Before Misty, inspect the blocked house. Defeat her and check badge-before-TM
   order, then beat the Rocket, receive Dig and speak again to check no duplicate.
8. Evolve during a trainer battle, and after defeating a wild Pokémon. Check
   the next turn or victory music resumes correctly, then save and reload.

For any problem, record the ROM filename, emulator/core, whether you used
Continue or an emulator state, location, party/follower, action and screenshot.
Preserve the in-game save from just before the problem when possible.

## Remaining story work

The requested fossil mini-boss and both restored fossils, Jessie and James,
Route 4 tutors, trade-free evolution rules and full-dex availability audit are
next-stage work. Fossils still use the existing item rules in this repair.
Bill, Vermilion and the S.S. Anne are not open yet.

Poison Point is triggered by contact, not every physical move. Weedle's normal
ability is Shield Dust and its Hidden Ability is Run Away; it does not gain
Poison Point merely by being a Poison type. Poison moves can still inflict poison.
