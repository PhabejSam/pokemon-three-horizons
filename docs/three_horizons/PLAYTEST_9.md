# Playtest 9: Pewter to Cerulean

The chapter now continues through Route 3, Route 4, all three Mt. Moon floors,
and Cerulean. Finish by defeating both Misty and the rival at the bridge.
Either order works. Route 22 is an optional detour west of Viridian.
Bill, the rest of Nugget Bridge, and the routes beyond Cerulean are future content.

## Keep your progress

Back up your Playtest 8 ROM and in-game battery save before testing. Use a
**copy** of that save with this ROM; match its base filename to the new ROM
using the emulator's save-location rules. Load with **Continue**, not an old
emulator save state. Existing rival choices stay unchanged. A fresh game is
needed to see the new introduction and random cross-region rival choice.

The save structure and original map numbers are preserved. Automated save
tests are useful evidence, but a complete old-save journey still requires a
playthrough. Keep the original backup until you have saved, fully closed the
emulator, reopened the ROM, and verified your party, items, badges and location.

## Suggested route

1. On a fresh save, choose an outfit, name the rival after his portrait,
   and set the bedroom clock. Visit the lab for the automatic welcome.
2. Choose a starter, including ability/Hidden Ability, nickname, shiny status,
   nature and IVs/EVs. Check the Summary afterward. The rival should choose a
   stronger type from another region and keep that partner after reloads.
3. Visit Route 22, battle the rival, then continue through Brock. Check
   houses, readable signs, item balls and the familiar Forest scene.
4. After Brock, talk to the caretaker outside Pewter Gym. Choose a level-10
   partner from one of the other two regions. Customize and nickname it.
5. Follow Route 3 east. At the Route 4 Center, heal and inspect the
   salesman's golden Magikarp offer. It costs 500, once only: level 5,
   Adamant, six 31 IVs, 252 Attack / 252 Speed / 6 HP EVs, normal ability.
6. Explore all three Mt. Moon floors. Fight the Rockets, defeat the fossil
   researcher, choose one fossil, and find the east exit. Fossil revival is
   planned for a later chapter.
7. Heal in Cerulean. Explore the houses, Mart and Bike Shop. Battle Misty
   and the bridge rival. Misty has Staryu 18, Psyduck 18, Marill 19 and
   Starmie 21. Receive the Cascade Badge and reusable Water Pulse TM.
8. Visit Cerulean's caretaker for the level-15 partner of your remaining
   type and region. If you skipped Pewter's gift, return for it first.
   Route 4 has a small stair passage for the return trip.
9. Save, close the emulator completely, reopen and Continue. Confirm both
   badges, Water Pulse, fossils, gifts and defeated trainers remain correct.

## What to watch closely

| Check | Expected result / useful report |
| --- | --- |
| Losing battles | Return to the correct healing location with healed party. Wild defeats cost no money; trainer defeats retain the existing penalty. New rival/Gym battles remain retryable. |
| Healing with follower enabled | Follower enters its ball during treatment and returns afterward as you move. No need to toggle Options. |
| Gift with six party members | New partner goes to the PC. Full party **and** full PC must leave gift/payment pending. No duplicate on a second conversation. |
| Cancel a gift or purchase | No partner, charge or completed receipt. You can try again. |
| Pickups and fossils | Visible, reachable, disappear only after receiving them; no duplication after reload. A full bag must leave the item waiting. |
| TM with a full bag | Badge stays earned; talk to Misty again after making room for Water Pulse. |
| Area cards | Forest and Mt. Moon illustration on outside entry; no repeat on interior ladders, menus or healing return. Controls and colors recover afterward. |
| Outfits and followers | Check all four directions, walking/running, clock return, building exit, healing, evolution and reload. |
| Capture and nickname | Test Rattata, Pidgey, Weedle and Caterpie; nickname and decline; short and longest allowed names; party and PC delivery; repeated catches; catch-triggered evolution. |
| Evolution | Let one happen during battle; cancel another, then gain a level again. Verify moves, HP, ability and follower afterward. |
| Old save | Opening does not replay; existing rival is retained; new routes and eligible gifts are available. |

For a crash, keep the **entire** error screen and the copied save from before
the encounter. Report ROM filename, map, party, caught species, nickname
choice, whether experience caused evolution, and whether the catch went to
party or PC. The earlier invalid-item capture error is **not yet reproduced
or claimed fixed**. Combusken's reported follower appearance also needs a
full-size screenshot showing facing direction and whether it is shiny.

## New Options

- **Day/Night:** Real time, or Fast (24x: one visual day per real hour).
  Switching preserves the current displayed time. Daily rewards continue
  using real time. Setting the bedroom clock reanchors the display.
- **Shiny Odds:** Normal (base 1/8192), 1/1024, 1/512, or 1/256 for newly
  created wild encounters. Existing party/PC Pokémon never change color.
  Native charm or other bonus rolls can improve the effective odds further.
  Explicit editor choices and the golden Magikarp are independent of this setting.
- Existing experience, auto-run and follower options remain available.

Try changing time modes, waiting, saving/reloading, and suspending/resuming.
Report unexpected lighting or encounter-time jumps. The fast visual clock
does not accelerate berries or other daily timers.

## Regional discoveries and familiar mechanics

Kanto remains the main encounter pool. Rare Chikorita can appear in the
Forest, Charmander on Route 3, and Makuhita in Mt. Moon. Nighttime Forest
encounters include Spinarak and Hoothoot. Aquatic starter habitats will come
with later accessible fishing/Surf areas. The Route 4 aide continues the
professors' research story.

Pidgey evolving at level 18 is intentional. Cancelled evolution can be
offered again on a later level; Everstone prevents it while held. Overworld
poison damage is disabled by the engine's modern configuration. Escape Rope
returns to a dungeon exit, not a Pokémon Center. TMs remain reusable.

## Anbernic RG40XX H

Extract the `.gba` from the ZIP and put it in your installed firmware's GBA
ROM folder. Use the mGBA core if your firmware offers it. No firmware update
or flashing is needed for this test.

Create a new in-game save on the handheld first to identify its save filename
and location, then close the emulator before replacing that save with a
**copy** of your desktop battery save. Depending on firmware/core, it may
use `.sav` or `.srm` and a separate save folder. Do not assume a specific
folder or replace a save while the emulator is running. Desktop save states
are not the transfer format.

Check title controls, sound, real-time clock, both lighting modes, follower
colors, capture/naming, battle evolution and a longer Mt. Moon session.
Save in-game, shut down the handheld fully, turn it back on, and Continue.
Handheld compatibility remains unconfirmed until this run is completed.

## Build and evidence

See [verification record](PLAYTEST_9_VERIFICATION.md) for automated results,
limitations and source identification. The package includes the ROM hash,
build source hash, and this checklist. The scenery title remains the approved
Playtest 8 artwork; illustrated professors and nine starters are not included.
