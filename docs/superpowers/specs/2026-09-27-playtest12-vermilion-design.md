# Pokémon Three Horizons — Playtest 12 design

Status: approved by the user on 2026-09-27; no Playtest 12 ROM has been built.
Baseline: Playtest 11, commit `881bf5c492c91698b198bdb9c2590e7e678d3beb`.

## Intended result

Continue from the player's Cerulean Pokémon Center save through Bill, Vermilion,
the S.S. Anne and Lt. Surge. Repair the reported presentation and progression
issues, make the regional migration mystery visible, and apply the requested
starter rebalance. A fresh opening replay remains optional for testing older
scenes. Preserve the existing normal save, party, boxes, badges and rewards.

Confirmed by the user: alternate starter typings and move buffs apply to all
members of those species, including existing Pokémon and opposing trainers.
Keep all three regional starter gifts and add rare wild starters in Kanto.
The detailed route, encounter locations and Surge team below are approved
implementation choices, not claims that these features already exist.

## Delivery choice

Recommended: one complete release, with internal checkpoints for repairs,
chapter progression, and rebalance. This avoids another mandatory early-game
replay while keeping each change independently testable. A repairs-only release
would arrive earlier but require another installation before new content.
Rebuilding Kanto's maps would add unnecessary layout risk; use the existing
FireRed map assets with Three Horizons events and trainers.

## The new playable chapter

1. **Cerulean → Route 24 → Route 25 → Bill.** Preserve the completed Cerulean
   rival flag. Add the Nugget Bridge challenge, its Rocket recruiter, route
   trainers, items and Bill's cottage. Bill's rescue grants the S.S. Ticket once.
   Loss, full bag and interrupted dialogue must leave rewards recoverable.
2. **Cerulean → Route 5 → Underground Path → Route 6 → Vermilion.** The existing
   Misty/robbed-house progression remains. The south ledge leads into a connected,
   escapable route. Saffron gates explain their closure; blocked future routes
   stop the player before one-way drops. All paths have a return route.
3. **Vermilion.** Provide the Center, Mart, Fan Club, fishing house and relevant
   homes, with individual dialogue. The fishing house grants the Old Rod once;
   the Fan Club grants the Bike Voucher once, redeemable at the Cerulean shop.
   Route 11's entrance has a clearly marked chapter boundary; Diglett's Cave
   onward progression is closed safely for this release.
4. **S.S. Anne.** Ticket checked at boarding; explorable cabins, kitchen, deck,
   corridors, trainers, items and a healing cabin. Rival keeps the established
   starter, evolves it appropriately, and can be retried after a loss. Helping
   the captain grants HM01 Cut once. The ship stays docked throughout this
   playtest so optional trainers/items remain accessible.
5. **Vermilion Gym.** Cut access obeys the HM rules below. Keep the two-switch
   trash-can puzzle with valid adjacent second switches. Gym trainers cannot
   permanently block a route. Lt. Surge uses five Pokémon: Voltorb Lv24,
   Pikachu Lv24, Magnemite Lv25, Electrike Lv25, Raichu Lv27. Use legal moves
   emphasizing speed/status and Electric attacks, with moderate coverage rather
   than a team designed to defeat every Ground answer. Award Thunder Badge
   before reusable Shock Wave. Loss/retry and save/reload preserve progression.
6. **Chapter end.** A professor's aide acknowledges the third badge and the
   accumulated sightings, then gives a clear end-of-playtest message. Routes
   beyond the supported chapter remain safely gated without stranding players.

Route trainers progress roughly from levels 16–21 around Bill, 18–23 on the
Vermilion approach, and 20–25 aboard ship. The EXP multiplier remains the
player's choice; balance is assessed at normal experience. No level cap is added.

## Regional migration story

The professors are investigating a pattern, not announcing its cause yet.
These scenes add evidence along the journey without forcing players to capture
rare wild encounters to advance.

- **Viridian Forest:** retain Hoothoot; add visible Treecko and Shroomish in
  separate clearings. Brief movement and species cries show them interacting
  with Kanto Pokémon. An aide records unusual sightings.
- **Mt. Moon first-ladder chamber:** three Clefairy circle a Makuhita in the open
  area from the screenshot. Keep the ladder, trainer and item routes clear.
  The nearby Rocket's post-battle dialogue says the boss ordered observations
  of these arrivals. These are story sprites, not forced gift captures; Makuhita
  remains a wild encounter and the scene does not overwrite the fossil flags.
- **Bill:** his observations connect forest, cave and coastal reports; he asks
  the player to compare them with shipping records in Vermilion. A scientist's
  working theory is marked as a theory, not a resolved explanation.
- **S.S. Anne:** sailors report Pokémon appearing away from their expected
  habitats. One short passenger/crew scene advances the mystery. The captain's
  rescue and rival battle still carry the main ship progression.
- **Lt. Surge aftermath:** Electrike's presence reinforces the same mystery;
  the aide points toward the next investigation without opening unfinished maps.

No new legendary encounter or additional mandatory Rocket boss fight is added
to this chapter. Later Jessie/James team evolutions remain future content.

## Playtest 11 repair requirements

| Report | Required behavior and verification |
|---|---|
| Gift shiny preview changes when navigating | The preview retains the selected palette across every row, nature/ability change, IV/EV page, cancellation and reopening. Compare a fresh starter and both later gifts, day and night. Inspect palette ownership/fades; do not rewrite correctly saved shiny data to mask a preview defect. |
| Broken first-catch Pokédex | Capture and inspect the entire Dex opening, page, exit and nickname transition, with normal and repeated A presses. Include Pidgey, both Nidoran, party room/full, first/repeat catches and capture-triggered evolution. Preserve nickname, item, ability and caught Pokémon integrity. A visible final nickname backdrop alone is insufficient proof. |
| Lab arrival/facing | Finish walking and return to a standing frame before Oak speaks. Face the rival for his exchange and Oak for the supply handoff. Test multiple player outfits and follower settings. |
| Empty desk | Remove dialogue from the empty desktop. Retain the actual laptop interaction; do not describe a book or journal with no visible object. |
| Rival's sister/map | Sister says “my brother.” The map opens the supported region-map display with a functioning return path; it never shares her dialogue script. |
| Museum repeat greeting | Greet once on external entry; returning downstairs does not greet again. Leaving the museum and entering for a new visit may greet again. |
| Brock rewards | Badge presentation precedes TM explanation and receipt. Bag-full retries cannot duplicate either reward. |
| Approaching trainers | Player faces the approaching trainer once movement ends. Preserve intentional line-of-sight and water/land restrictions. Luis shows an alert before swimming to the pool edge. |
| Miguel/fossil scientist | Defeat line explicitly allows both fossils. Cerulean scientist recognizes zero/one/two restorations and gives completion dialogue after both. Check the robbed-house Rocket separately so dialogue fixes attach to the correct actor. |
| Cerulean south trap | Connect the expanded route and verify a return on both sides of every ledge. Closed branch checks occur before an irreversible step. Include loading an old save already beyond the old boundary. |
| Pewter route gate | A guide explains Brock's badge requirement and turns the player back before the closed route. After Brock, the guide cannot obstruct the route. |

The museum currently uses a map-temporary greeting marker; changing floors
resets it. That explains the repeated welcome. The Dex and shiny-preview causes
are not confirmed yet and require reproduction before selecting a repair.

Duplicate nicknames are valid. The reported Power Lens result is also correct:
Rattata yields 1 Speed EV, and Power Lens adds 8 Special Attack EVs. Keep the
current bonus, caps and valid multipliers. Include a short training explanation
in the guide and verify each Power item rather than reducing the intended bonus.
The League guard's front trigger is acceptable provided no approach bypasses
the badge check. Preserve all user-confirmed successful Playtest 11 behavior.

## Jessie, James and Meowth

- Add recognizable Jessie/James overworld and battle sprites, with the correct
  hair, white uniforms and red R. Generic grunts are not the completed result.
  Check transparency, palettes, all used facing frames and sprite dimensions.
- Stage the trio as **Jessie — Meowth — James**, facing the player. Normalize
  the scene for entry from either direction and temporarily clear the follower
  from the staging area. Never teleport the player onto an occupied tile.
- With two usable Pokémon: the existing Ekans/Koffing double battle. With one:
  Jessie/Ekans followed by James/Koffing as back-to-back singles. Do not let the
  player pass because only one Pokémon is available. A loss in either single
  returns to the last healing location and retries the pair from the beginning;
  no completed-scene flag until both are beaten. No free heal between singles.
- Display the opponents' team balls in one row, in two groups with a visible
  gap. Each group has three slots (six total), showing that trainer's actual
  healthy/fainted/empty slots. Verify the existing one-Pokémon-per-trainer case
  and larger supported parties. Preserve ordinary single battle layouts.
- After defeat: “Team Rocket's blasting off again!” with a brief departure
  effect, then remove all three together. No short walk ending in unexplained
  disappearance. Preserve Meowth's human speech; he is not a battle participant.
- Old saves which missed the newly added encounter can still complete it on
  return. Restored fossils and earned badges are never removed or reset.

## HM quality of life

Any learned HM can be forgotten through normal move replacement/relearning,
including Rock Smash learned by level-up. For field use, check a conscious,
non-Egg compatible party Pokémon, the corresponding HM in the bag, and its
badge/story requirement. The Pokémon need not know the move. Keep normal field
animations and a clear message when a requirement is missing.

For this chapter, Cut requires HM01 and the Cascade Badge. Audit the remaining
HM field-action entry points using their intended Kanto gates, but do not
unlock Surf, Fly, Strength or later routes in Playtest 12. Carrying an eligible
Pokémon is distinct from owning that HM. Compatibility, not current typing
alone, determines eligibility. Test taught and untaught Cut, no HM, no badge,
no compatible party member, fainted-only compatibility and cancellation.

## Starter rebalance

Apply only in the Three Horizons build; preserve upstream Emerald/FireRed
behavior. Existing Pokémon change type through their species data without
resetting their nature, IVs, EVs, ability, shiny status or known moves.

| Species | Resulting type |
|---|---|
| Grovyle, Sceptile | Grass/Dragon |
| Venusaur | Grass/Ground; Bulbasaur and Ivysaur retain Grass/Poison |
| Charizard | Fire/Dragon |
| Blastoise | Water/Steel |
| Bayleef, Meganium | Grass/Dragon |
| Quilava, Typhlosion | Fire/Ground |
| Croconaw, Feraligatr | Water/Dark |

Leaf Blade and Blaze Kick become 95 power. Muddy Water becomes 95 power and
100 accuracy. Sky Uppercut becomes 100 accuracy. Preserve current effects,
categories and other properties unless expressly changed by this request;
“retain Legacy buffs” does not authorize inventing unspecified external changes.

Apply the exact requested move/level entries in the companion
`2026-09-27-playtest12-starter-moves.md`. Where an entry replaces the learning
level of a move already present, move it to the requested level. Keep unrelated
existing moves, keep the explicitly requested level-1 relearn entries, and
retain Blastoise's Flash Cannon alongside Spike Cannon at Lv36. Validate
multiple moves at the same level and canceled evolution. Do not forcibly
overwrite an existing Pokémon's four moves; the Relearn menu offers eligible
new entries. Grovyle/Sceptile rivals use appropriate Dragon moves.

Oak gives two Ultra Balls in addition to existing supplies and an additional
2,000 starting money, once. For upgraded saves that already received the
opening supplies, a Cerulean aide provides this same one-time catch-up bonus.
A new save cannot receive the bonus a second time from that aide.

### Proposed rare wild starter placements

Each row is a 5% grass/cave encounter, available at all times at that location.
Reserve or replace suitable common slots while retaining every existing unique
species somewhere in its area. Keep Mt. Moon's Clefairy and Makuhita rates.

| Starter | Location | Level |
|---|---|---:|
| Bulbasaur | Route 2 grass | 5 |
| Treecko | Viridian Forest | 7 |
| Chikorita | Viridian Forest | 5 |
| Charmander | Route 3 grass | 8 |
| Torchic | Route 4 grass | 8 |
| Cyndaquil | Mt. Moon 1F | 9 |
| Mudkip | Route 22 grass near water | 5 |
| Totodile | Route 24 grass near water | 10 |
| Squirtle | Route 25 grass near the coast | 10 |

These are Kanto adaptations of the supplied Hoenn locations, reachable before
Lt. Surge without Surf. Wild starters use ordinary capture rules and the
existing 10% Hidden Ability roll when applicable. They do not open the gift
customization screen. The three regional gifts keep their current selection,
customization and reward rules. Generate the release encounter guide directly
from the final data, including day/night and rod tables, and distinguish story
sprites, gifts and random encounters.

## Implementation boundaries and save handling

Extend the existing Three Horizons script modules with separate Bill,
Vermilion/ship and Gym progression files. Use chapter-specific trainers and
events, sharing the native battle and field engines. Append map IDs and audit
unused flags/variables; do not renumber the existing 43 maps or grow the save
structures. Keep new reward flags separate from existing fossil/gift state.

Migration must be idempotent. An old save after Misty can leave the Center and
play the new chapter. Preserve a defeated rival, collected fossils, both
revivals, reusable TMs and gift selections. New flags start unclaimed; checking
for already-owned critical rewards prevents duplicate grants where needed.
Keep the older release and all user saves untouched. Copy a normal battery
save to the new ROM's matching name and choose Continue. Do not use a save-state
slot from another ROM version.

Shared engine changes must be narrowly gated or demonstrated safe for upstream
builds. No silent removal of assertions to hide corruption. The shiny editor,
Dex lifecycle, team-ball rendering and field-HM eligibility remain distinct
changes so failures can be isolated.

## Acceptance and release evidence

- Fresh game: full path through Surge, with loss/retry for new mandatory fights,
  correct challenge facing, rewards, field use, and no permanent blockers.
- Upgraded Cerulean save: Bill → ship → Cut → Surge without replaying Pallet,
  with all previous party, boxes, badges, rewards and story flags preserved.
- One-Pokémon and two-Pokémon Rocket paths, loss to the second single opponent,
  reverse entry, departure effect, follower restoration, and no pass-through.
- Record screenshots of the entire first-catch Dex sequence and shiny editor,
  not just the final successful state. Use both slow and repeated A input.
- Test all nine starter lines' requested types, move levels, relearn behavior,
  evolution cancellation, existing moves and rival variants. Validate encounter
  distributions sum to 100% per method/time and reachability of every new table.
- Validate map connections, ladders, indoor returns, ledges, chapter gates,
  trainer approach squares, ship boarding, Gym switch combinations and all
  item/reward retry paths. Compare team-ball status against actual parties.
- Run relevant automated regressions and compile Three Horizons plus upstream
  compatibility builds. Perform emulator walkthroughs against the packaged ROM,
  then record its checksum/source revision and limitations honestly.
- Package Playtest 12 with a continuation-first guide, encounter tables, starter
  change reference, verification log and targeted optional opening checks.
  Handheld testing remains a separate user check on the RG40XX H: boot, RTC,
  sound, longer sessions, in-game save, full power-off and Continue.

## Suggested beta route after delivery

Start with a copy of the normal Cerulean save. Check party types and Relearn,
visit the aide for the catch-up supplies, complete Bill, travel south, explore
Vermilion and the ship, obtain Cut without teaching it, and beat Surge. Save,
close the emulator completely and Continue. On a separate optional fresh run,
check lab posing, first-catch Dex frames, museum re-entry, Brock's reward order,
forest sightings and the one-Pokémon Rocket encounter. Record the release name,
location, preceding action and screenshot for any failure.
