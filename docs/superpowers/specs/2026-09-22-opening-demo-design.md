# Pokémon: Three Horizons — Opening Demo Design

Status: Approved by the user, including the demo defaults below.

## Purpose

Create a cozy, approximately 15–20 minute first adventure from Pallet Town to the
entrance of Viridian City. The player should care about home, their first Pokémon,
and their childhood friend before the larger mystery becomes urgent.

The long-term game connects Kanto, Johto, and Hoenn through one story. This demo
introduces that connection through the professors' research exchange and one
unusual sighting. It does not attempt to build all three regions.

## Approved creative decisions

- Keep Pallet Town recognizable and refreshed. An expanded, reimagined town is
  a later milestone.
- Start in the player's home, visit Oak, choose a starter, battle the rival,
  explore Route 1, and finish at Viridian City's entrance.
- Offer all nine first partners from Generations 1–3.
- The rival is an original childhood friend: warm, fiercely competitive,
  playful, occasionally jealous, and loyal when help is needed.
- Begin with everyday life and subtle clues. The early mystery is interesting,
  not threatening.
- Win or lose, the first battle advances the story.
- A Hoothoot resting in a Route 1 tree supplies the first unusual sighting.

## Approved defaults for this demo

These defaults were included in the written design approved by the user.

- Rival's name: Robin. Dialogue uses the name without gendered pronouns. Name
  customization and a bespoke visual design are later work. Reuse a generic
  existing trainer appearance for this prototype; do not present Robin as Blue.
- Both starters begin at level 5 with their existing engine-defined moves.
  Leave species stats, abilities, evolution rules, and global battle balance alone.
- Use three clearly labeled research displays: Kanto, Johto, and Hoenn.
  Each opens a three-species choice with a confirmation before receiving a Pokémon.
  The player can back out and inspect another display.
- The rival chooses the starter with the type advantage from the same regional
  trio. This is a deterministic rule, not a difficulty mode.
- Oak supplies a research Pokédex capable of recording all nine starters, five
  Poké Balls, and two Potions before the player leaves for Route 1.
- Route 1 uses Pidgey and Rattata at levels 2–4. Hoothoot is an observation event,
  not a forced battle or gift.
- The route contains helpful NPCs and optional wild battles. The rival battle
  is the only required trainer battle in this demo.
- After the endpoint scene, allow saving and walking back through the completed
  area. Clearly marked demo boundaries block further exploration without looping
  the ending or trapping the player.

Starter choices and rival partners:

| Player | Rival |
| --- | --- |
| Bulbasaur | Charmander |
| Charmander | Squirtle |
| Squirtle | Bulbasaur |
| Chikorita | Cyndaquil |
| Cyndaquil | Totodile |
| Totodile | Chikorita |
| Treecko | Torchic |
| Torchic | Mudkip |
| Mudkip | Treecko |

## Opening scenes

### 1. Home

A new game starts in the player's bedroom. Downstairs, Mom reminds the player
about Oak's invitation and offers an affectionate send-off. The television can
be examined for a short report about the three-region research exchange.
Watching it is optional; Oak explains the essential information later.

Example tone: "You've checked your bag three times. Go on—Oak's waiting."

### 2. A friend at the door

Robin meets the player just outside the house. Robin claims the player is late,
then admits to having arrived early. The scene establishes excitement and nerves
without insulting the player. Robin invites the player to the lab and walks
ahead along a short, reliable scripted path.

Example tone: "You're late! ...Okay, I'm early. I couldn't sleep."

### 3. Oak's research exchange

Oak explains that Elm studies Pokémon development and Birch studies habitats.
The professors have exchanged first-partner Pokémon while comparing observations
from their regions. Oak invites the player to choose carefully.

The three displays make all nine Pokémon available before the choice is final.
Canceling or declining a confirmation gives nothing and leaves the choice open.
A confirmed choice grants exactly one Pokémon and permanently records the
first-partner species. Returning to a display afterward cannot grant another.

Robin chooses afterward. Their hesitation makes them feel excited rather than
omniscient. Oak gives both trainers a simple purpose: travel, learn, and notice
what is happening around them.

### 4. First friendly battle

The battle takes place outside the lab. Robin uses one level-5 starter.
A victory produces cheerful admiration with a trace of disappointment; a loss
produces excited celebration followed by encouragement.

Both outcomes finish the scene, heal the player's party, and unlock Route 1.
Losing must not strand the player in the standard early-game recovery sequence.
A return visit must not retrigger the battle or repeat the supply gifts.
Mom remains a repeatable healing option after the player receives a partner.

### 5. Route 1

The route encourages walking, talking, and trying ordinary Pokémon catches.
A helpful NPC explains catching briefly without a mandatory long tutorial.
The player can return home or to the lab.

Near an accessible tree, the player notices a resting Hoothoot. A nearby local
comments that they do not usually see one here. The scene is brief and calm.
Record that the sighting occurred so crossing the trigger again does not repeat
the scene. The Hoothoot can remain visible and examinable.

Do not require a real-world time setting or day/night system for this event.

### 6. Viridian entrance

Robin waits at the entrance. The closing conversation looks forward to the
journey and reinforces the friendship. It does not introduce an emergency,
villain, legendary Pokémon, or second rival.

Show a brief demo-complete message, restore normal control, and allow an in-game
save. Subsequent visits use a short repeat line instead of replaying the ending.
Accessible doors and route exits must remain within the playable demo boundary.

## Progress and save behavior

Store progress in persistent event variables and flags, using audited unused
identifiers. Do not change the save-block format for this demo.

The main sequence advances through home, invitation, partner chosen, battle
finished, and demo complete. Record the Hoothoot sighting separately. Store the
player's first-partner species and the rival's partner species separately from
the current party position.

Rewards and scenes are one-time events. Menus can be canceled safely. Save/load
must preserve the chosen partner, battle completion, sighting, rewards, and ending.
Every cutscene must release movement and input locks when it finishes.

Route 1 remains inaccessible before the opening battle is resolved. Afterward,
wild-battle defeat returns the player to a valid healing location within the
demo and preserves story progress.

Use a new save for this demo. Preserve the user's tested baseline ROM and save;
migration of existing Emerald saves is outside this milestone. Future demo
builds must state save compatibility explicitly.

## Technical findings and integration approach

Inspected source: pokeemerald-expansion baseline
`c93efe865f20eafd6b48751d13b14c087c330880`.

The repository contains Pallet, Oak's lab, Route 1, and Viridian source maps.
However, `tools/mapjson/mapjson.cpp` filters maps by build region, and layouts
also have version-specific handling. The Emerald build does not simply include
the Kanto opening. `src/new_game.c` selects different spawn and initialization
paths under `IS_FRLG`.

The original `src/starter_choose.c` uses three entries, and legacy
`VAR_STARTER_MON` consumers expect those indices. Do not expand that array to
nine or reinterpret the existing variable globally.

Use an isolated Three Horizons build configuration based on the Emerald engine.
Keep existing Emerald, FireRed, and LeafGreen build behavior available. Adapt the
required Kanto map/layout assets into a scoped demo map set and use project-owned
events instead of executing the old Oak/Blue progression.

The first implementation checkpoint must prove that this configuration can
render the bedroom, town, lab, Route 1, and endpoint, with valid collision, warps,
music, and healing destinations. Inspect tileset and layout formats explicitly;
a successful source build is not proof that a reused map renders correctly.
Keep map-selection changes opt-in and avoid renumbering existing map groups.

Build the nine-choice flow around separate project-owned species records and
existing menu/party-grant facilities. A custom graphical nine-ball screen is
not needed for this milestone.

Likely implementation areas: project configuration/build selection; map and layout
registration; new-game initialization; project event scripts and constants;
starter menus; the rival trainer; Route 1 encounter data; and an automated demo
build. The implementation plan must assign exact files and verified identifiers
after the written design is approved.

## Validation and completion criteria

- Clean demo build succeeds and produces a separately named ROM and build log.
- Existing upstream build targets still compile after shared code changes.
- A new game begins at the intended home, with correct maps and no Emerald truck
  sequence or inherited Oak/Blue scene appearing unexpectedly.
- Each of the nine starters can be selected in a fresh run; species, level,
  Pokédex registration, rival choice, and one-time rewards are correct.
- Cancel, back, and confirmation paths never duplicate a Pokémon or item.
- Both first-battle outcomes continue, heal the player, and remain complete
  after leaving the map or reloading.
- Route 1 encounters can be fought and caught. A wild-battle defeat recovers
  within the demo without losing story progress.
- The Hoothoot event occurs once, works without time configuration, and cannot
  leave movement locked.
- The endpoint occurs once and leaves saving and backtracking available.
- Test in-game save, emulator close, reopen, and Continue before starter choice,
  after starter choice, after the rival battle, and after the endpoint.
- A full playthrough has readable text, no broken warps or collisions, and no
  routes into unfinished content.
- Automated checks cover starter mapping and persistent progression where the
  existing test facilities support them; emulator checks cover presentation,
  walking, and save/reload. Neither substitutes for the other.

The existing unmodified ROM has passed compilation. The user separately reports
successful boot, in-game saving, reopening, and loading. Those results establish
the baseline only; the new demo must pass its own checks.

## Later milestones

Expanded Pallet Town; custom rival artwork; the rest of Viridian and the road
to Pewter; longer rival development; second-rival concepts; travel between regions;
full regional progression; difficulty options; and additional quality-of-life
changes are later design work.
