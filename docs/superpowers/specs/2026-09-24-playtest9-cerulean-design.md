# Three Horizons Playtest 9: the journey to Cerulean

Status: design approved by the user on 2026-09-24; not an implemented ROM.
Baseline: Playtest 8 title build b3916b8dd2096e2460ee9baf29c70deadd9c38a7.
Execution preference retained: native, in this development checkout.

## Purpose and success

Extend the playable journey through Route 22, Route 3, Mt. Moon and Cerulean,
including Misty and the rival encounter south of Nugget Bridge. Keep the cozy
opening and the mystery of Kanto, Johto and Hoenn Pokemon appearing together.
The three professors investigate that change; their involvement must continue
to matter after the starter scene. Preserve existing in-game saves and the
standard upstream build modes. Earlier ROMs and saves remain untouched.

Ship only after the capture/nickname error is reproduced and repaired, or
explicitly report it as unresolved rather than claiming this playtest fixes it.

## Confirmed user choices

- Real-world time with an optional faster day/night cycle.
- Additional testing device: Anbernic RG40XX H; firmware remains unknown.
- Hidden Ability selection in the partner editor.
- The rival chooses a random type-advantaged starter from another region.
- Visible item-ball pickups instead of invisible hidden items.
- A special 500-money shiny Magikarp at the Center before Mt. Moon.
- Additional configurable starters after Brock and Misty, eventually giving
  one Fire, Water and Grass partner from three different regions.
- Keep successful Playtest 8 behavior: follower on first grant, persistent lab
  displays, Oak's handoff, individual NPC dialogue, healing-ball alignment,
  in-battle evolution/cancellation, reusable TMs, and save/reload.

## Delivery approach

Recommended: fix and test capture reliability first; then implement opening
and partner systems; finally connect the full chapter and package one Playtest
9. This gives each stage a testable result without expanding a known crash.
An alternative is a small stability-only download before the chapter, which
gets a repair to the player sooner but requires another installation/playtest.
Rebuilding Kanto from scratch would add map and art risk with no benefit to
these requests; reuse the native Kanto layouts already included in the repo.

## Capture and visual repairs

The provided screenshot contains small previews, rather than the original
crash and Combusken screenshots. The visible stack addresses 0x080A9763 and
0x08162C09 resolve in both Playtest 8 ELFs to Cmd_givecaughtmon and
GetItemPocket. The relevant code restores a caught Pokemon's original held
item. This identifies the failure path, not the cause of the invalid value.
Do not hide the assertion or substitute ITEM_NONE to mask unexplained memory
damage. Trace the original item, caught battler, party index and battle state
across Dex, nickname, catch experience/evolution and party/PC delivery.

Test Rattata, Pidgey, Weedle and Caterpie with naming accepted/declined,
short/maximum-length names, ordinary/held-item encounters, party room/full
party, PC delivery, catch-triggered evolution, and repeat catches. Preserve
the nickname, original trainer, held item, ball, species, ability and stats.
Exercise native callbacks, rather than only calling the final grant function.
Check release confirmation and subsequent PC contents as a separate path.

Inspect Combusken's normal/shiny follower frame dimensions, frame ordering,
palette, transparency and facing directions against the source sheet. Obtain
the original screenshot to distinguish an asset defect from the intended pose.
Hide followers during healing, then restore according to the saved option
and first party slot on success, cancellation and blackout recovery.
Correct player facing before every automatic rival conversation; test Kris
and all other outfits without changing walking/running animations.

## Opening scenes and clock

Before rival naming, show the existing Blue-style portrait with a short
introduction: "This is your rival! ... What was his name again?" Then open
the naming screen. Retain the chosen name on reload.

On the first attempt to leave the bedroom, prompt the player to check/set
the clock. A saved completion flag prevents replay. Existing saves get the
prompt on a later home visit if they never set it; no forced teleport.

Proposed fast mode: one in-game day per real hour (24x), affecting lighting
and encounter time periods. Normal mode follows the configured clock.
Switching modes preserves the current displayed time; saving/reloading and
backwards clock corrections must not jump the date or strand encounters.
Keep real-time daily rewards and timers separate from the fast display clock.
Verify RTC behavior on mGBA and the handheld, including sleep/resume.

On the first lab entry, walk the player a short, collision-checked distance
forward. Oak, Elm and Birch introduce the joint research, then invite the
choice. The rival offers to choose first, hesitates and lets the player go.
Restore control beside the displays. Do not replay this after obtaining the
starter or on an old save. Preserve Oak's existing physical supply handoff.

## Partner choices, ability and names

Extend the existing editor with the species' available normal abilities and
Hidden Ability, showing the actual ability name. Omit unavailable/duplicate
slots. Retain shiny, nature, individual IV/EV preview and legal limits.
Offer a nickname after confirmation for starter and reward partners. Cancel
keeps the species name. Grant only after successful confirmation and delivery.
Apply the same supported ability control to the legendary capture editor,
preserving the captured Pokemon's identity and unrelated properties.

Confirmed rival choice: randomly choose a type-advantaged starter from a
different one of the three regions. For
Torchic, that means Squirtle or Totodile. Pick once and persist it; do not
reroll on map changes, losses or reload. Use that same species/line in the
display scene, dialogue and subsequent teams. Existing saves retain their
already-selected rival partner. The first-partner pool remains the nine
Kanto/Johto/Hoenn starters.

### Additional partners after badges

Outside Pewter Gym, a caretaker explains that two trainers left partners
after struggling against Brock. After the Boulder Badge, choose one of the
two eligible partners; the other remains with the caretaker. No extra fight
against the caretaker is required. Grant once, with the full editor and
nickname option. Proposed gift level: 10.

Follow the user's stated Brock type mapping:

| Original type | Brock reward type |
| --- | --- |
| Fire | Water |
| Grass | Water |
| Water | Fire |

The two options come from the regions other than the original starter's.
For Torchic this is Squirtle/Totodile; for Treecko Squirtle/Totodile; for
Mudkip Charmander/Cyndaquil.

After the Cascade Badge, the Cerulean caretaker offers the starter of the
missing type from the remaining region. For example: Torchic + Squirtle
leads to Chikorita; Torchic + Totodile leads to Bulbasaur. Proposed level: 15.
The third choice is therefore determined by the first two choices. If the
Pewter gift was skipped, explain that it is waiting; permit claiming it later
and returning. Record gift species independently of the current party so
boxing, trading or releasing a partner cannot grant duplicates or change the
reward. With a full party, offer native PC delivery or leave the reward
pending; never consume the reward on a failed delivery.

Plan eventual wild starter habitats across the whole game. For this chapter,
include rare habitat-appropriate sightings/encounters such as Chikorita in
Viridian Forest and Charmander on Route 3. Aquatic starter habitats can be
documented for later accessible fishing/surf areas; do not claim them catchable
before the required access exists. Gifts do not remove those wild encounters.

## Connected chapter

- Route 22 opens west of Viridian with accessible grass, Spearow, Nidoran,
  Mankey and Meowth encounters, visible pickups, and an optional second rival
  battle. The League gate remains badge-locked with clear dialogue.
- Route 3 opens after Brock. Keep terrain and trainer placements coherent,
  individual pre/post-battle dialogue and permanent defeat flags.
- Route 4's Center heals and becomes a valid blackout destination. Its
  salesman gives one level-5 shiny Magikarp for 500: six 31 IVs, 252 Attack,
  252 Speed and 6 HP EVs. Proposed fixed nature: Adamant; normal ability.
  Preview the offer, require confirmation, and charge only after successful
  party/PC delivery. Cancellation, insufficient funds and full storage do
  not charge or mark the purchase complete.
- Connect all three Mt. Moon floors and both exits with native ladder/warp
  placement, ordinary trainers, Team Rocket encounters and the fossil choice.
  Fossil selection is once-only and survives saving; revival is future content.
- Cerulean includes safe healing/blackout, Mart, Gym, accessible houses and
  Bike Shop dialogue appropriate to current progress. Audit earlier Pallet,
  Viridian and Pewter building entrances too; visible doors need working
  interiors and return warps. Future services can be explained inside without
  pretending they are implemented. Native link/online facilities are outside
  this local playtest.
- Rival battle at the south entrance to Nugget Bridge uses the persistent
  regional partner and a modest mixed team. Route 24 beyond the battle, Bill,
  Route 5/9 and later chapters remain clearly marked boundaries in this build.
- Proposed Misty roster: Staryu 18, Psyduck 18, Marill 19, Starmie 21. Four
  Pokemon follows the approved early-Gym rule. Retain Starmie as ace, award
  Cascade Badge and reusable Water Pulse once, and handle bag-full retries.
  Keep modest trainer IVs, no EV maximization or competitive hidden abilities.
- The chapter completes after both Misty and the bridge-entrance rival;
  either battle order must work and free exploration remains available.

## Three-region story, items and area cards

Keep Kanto species as the majority while adding deliberate Johto/Hoenn
encounters and overworld sightings: for example Spinarak in forest at night,
Hoothoot near trees, and Makuhita in Mt. Moon. Give different NPCs concrete
observations about habitat changes; use a professor/aide check-in around
Mt. Moon to connect them with the opening research. Do not turn every NPC
into the same exposition or spoil an unexplained legendary event.

Replace hidden-item events in the playable chapter with visible item balls
on accessible tiles. Avoid NPC/warp overlap. Pickups disappear only when
delivery succeeds, never duplicate after re-entry/save, and remain if the bag
is full. Fossils and other story props can use their appropriate visible art.

Use the existing FireRed area-card art for supported landmarks, starting with
Viridian Forest and Mt. Moon. Show cards on external entry, not every room,
ladder or blackout, and retain normal location labels elsewhere. This does
not require generating new illustration assets.

## Shiny setting

Offer Normal, 1/1024, 1/512 and 1/256 wild encounter odds, with Normal as the
default for existing saves. The current base threshold is 8/65536 (1/8192)
before native bonuses. Label boosted settings as base encounter odds and
document any charm/DexNav bonus interaction. Apply changes only to newly
created wild Pokemon; never change the global shiny interpretation threshold
and accidentally recolor existing party/box Pokemon. Explicit partner editor
choices and guaranteed-shiny Magikarp override the random encounter setting.

## Expected behavior and repository question

Pidgey -> Pidgeotto at level 18 is configured correctly. Cancelled evolution
being offered again on a later level is intentional; Everstone is the durable
opt-out. Overworld poison damage is disabled by the engine's modern setting.
Escape Rope returning to an exit of the current area is intentional, not a
trip to the last Pokemon Center. Preserve these behaviors in this update.

The unprotected-main warning concerns repository workflow, not ROM health.
Recommended protection is pull requests plus the relevant passing checks,
with force-push/deletion disabled. Avoid requiring approval from a second
person if the user is the only maintainer. Repository settings changes are
separate from this design and have not been applied.

## Acceptance and delivery

Preserve map indices and save structures; append new map IDs and audit spare
event flags/vars before allocating them. Do not repurpose existing reward
state. An old Brock save must enter the new chapter and claim eligible gifts
without redoing the opening. A fresh game must play through all new scenes.

Tests cover capture callback lifecycle, all nine original-starter/reward
combinations, reward retries/no duplication, persistent rival choice, ability
legality, shiny stability, time-mode persistence, every map/warp connection,
trainer victory/loss/retry, item-ball bag-full behavior, badge/TM delivery,
follower healing restoration and existing Playtest 8 regression checks.
Compile the demo and upstream modes. Package the source hash, checksum, known
issues, reproducible instructions and a beta checklist with the new ROM.

For RG40XX H, copy the extracted .gba to the firmware's GBA ROM folder and
use the mGBA core if available. Test a copied battery save, not desktop save
states; file extension/location depends on the installed firmware. Keep a
PC backup. Check boot, title controls, RTC/day-night, sound, battle evolution,
followers, a long Mt. Moon session, in-game save, full power-off and Continue.
Do not claim handheld compatibility until the user confirms that playthrough.

References: https://win.anbernic.com/product/439.html and
https://docs.github.com/en/repositories/configuring-branches-and-merges-in-your-repository/managing-protected-branches/about-protected-branches
