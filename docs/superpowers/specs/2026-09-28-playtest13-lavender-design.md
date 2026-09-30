# Pokémon: Three Horizons
# Playtest 13 — The Road to Lavender

STATUS:
Approved design specification for implementation planning.

TESTED BASELINE:
Playtest 12 — Rocket Art Update

Feature revision:
f6dc5b36c0ed9ea71b10a93a69af2e0f68d4bcd0

Compiled/test revision:
d8da3c365b74a0bd87099fb4e983e32f8d0e0c03

ROM SHA-256:
2191ebf684fb829cc86d4bc8638a11ee5aa535a9c88dbd47f8b3e96ce38f312d

Primary development branch:
feature/opening-demo

Current game progression before Playtest 13:
Pallet Town → Viridian → Pewter/Brock → Mt. Moon →
Cerulean/Misty → Bill → Vermilion → S.S. Anne → Lt. Surge

Playtest 13 endpoint:
Lavender Town / first Pokémon Tower sequence →
unidentified ghost blocks progression →
Silph Scope required →
Celadon becomes the next lead →
END PLAYTEST 13


==================================================
1. CORE PLAYTEST 13 PURPOSE
==================================================

Playtest 13 has three equally important goals:

1. Repair confirmed Playtest 12 bugs and presentation problems.
2. Expand Kanto from post-Lt. Surge through Route 9, Route 10,
   Rock Tunnel, Lavender Town, and the first Pokémon Tower sequence.
3. Strengthen the central Three Horizons story so Kanto, Johto,
   and Hoenn increasingly feel like parts of one living world.

The chapter's narrative purpose is:

"What began as unusual Pokémon migration now appears to be a
broader ecological phenomenon that cannot be explained by ordinary
travel or shipping alone."

Do NOT reveal the true cause yet.

Oak, Elm, Birch, Bill, Team Rocket, the rival, and the player should
all still be investigating.


==================================================
2. THREE HORIZONS STORY FOUNDATION
==================================================

The opening of the game must more clearly establish the player's
secondary mission.

The player is not simply traveling to collect badges.

Professor Oak, Professor Elm, and Professor Birch have noticed
Pokémon appearing outside their expected regional habitats.

At the beginning of the game, Oak should explain that:

- Elm is observing irregular Pokémon appearances in Johto.
- Birch is observing similar changes in Hoenn.
- Kanto is beginning to show the same pattern.
- The professors do not know the cause.
- Oak wants the player and rival to travel normally, battle,
  explore, and report unusual Pokémon behavior or sightings.
- Every observation could help the three professors understand
  what is happening.

This should remain curious and adventurous at first, not apocalyptic.

The opening should establish:

Trainer journey + field research mission.

Do not rewrite the entire opening structure.
Strengthen existing dialogue and purpose.


==================================================
3. PLAYTEST 12 REQUIRED REPAIRS
==================================================

These are required Playtest 13 repairs, not optional future ideas.

A. REGION / MAP TEXT

- All Kanto Town Map interactions must identify Kanto, not Hoenn.
- Correct rival house map interaction.
- Correct Viridian school/house map interaction.
- Correct S.S. Anne and other Kanto map references.
- Audit all current Kanto map-description scripts for inherited
  Hoenn wording.

B. TV TILE CORRUPTION

Current behavior:
Interacting with TVs can cause the TV tile/object to become a floor
tile until the map reloads.

Required:
- TV remains visually intact.
- TV remains interactable repeatedly.
- No tile replacement or collision changes after dialogue.
- Audit affected Viridian/Vermilion interiors and shared TV scripts.

C. DAY CARE WARP

Current behavior:
Entering the Route 5 Day Care can return the player through the
Underground Path doorway.

Required:
- Day Care entrance and exit use correct reciprocal warps.
- Underground Path entrance remains separate.
- Test entry and exit in both directions and save/reload.

D. SAFFRON GUARDS

Current behavior:
Route 5/6 Saffron guards do not correctly block entry.

Required:
- Guards block Saffron before its intended story unlock.
- Dialogue explains access is restricted.
- Underground Path remains the intended current route.
- No bypass from either Cerulean or Vermilion side.

E. PEWTER / ROUTE 3 GUIDE

Current issues:
- Pre-Brock boundary message can occur independently of the visible guide.
- Guide can visibly pop/fade into existence when approaching from Route 3.
- Movement/visibility looks incorrect when walking, running, or biking.

Required:
- Guide visibly and naturally stops the player before Brock.
- After Brock, guide no longer blocks the route.
- No sprite pop-in or fade artifact from either direction.
- Guide may remain available for post-Brock dialogue.

Unbattled gym trainers should remain battleable after defeating the
Gym Leader unless an existing trainer script specifically requires
otherwise.

F. NUGGET BRIDGE RIVAL DIALOGUE

Current issue:
After the rival battle before Nugget Bridge, dialogue incorrectly
says the chapter is complete / the bridge will open in another
playtest even though the route is already available.

Required:
Replace obsolete beta-boundary dialogue with current story dialogue.

G. BILL MID-SEQUENCE STATE

Current reproduction:
- Bill enters the teleporter.
- Player leaves the cottage before activating the PC.
- Player returns.
- Bill is restored outside as Clefairy with no acknowledgement.
- PC can then be used again and sequence succeeds.

Required:
Persist a safe "Bill experiment in progress" state.

Preferred behavior:
If Bill has entered the machine and player leaves/re-enters:
- Bill remains logically in the machine / experiment-ready state,
  OR
- scene resets explicitly with dialogue explaining he needs to
  restart.

Do not silently reset his position with no story acknowledgement.

Do not duplicate the S.S. Ticket or rescue reward.

H. CERULEAN AIDE SUPPLY DIALOGUE

Playtest 12 correctly prevents duplicate ₽2,000 + two Ultra Balls.

If rewards were already received:
- Aide should explicitly acknowledge that supplies were already
  delivered.
- Do not use wording that makes the player believe another reward
  is pending.

I. S.S. ANNE BOARDING

Current issue:
Sailor can fail to visibly enforce/check the S.S. Ticket.

Required:
- Boarding NPC checks ticket naturally.
- Without ticket: player cannot board and receives clear dialogue.
- With ticket: allow boarding.
- No duplicate ticket consumption unless intentionally designed.
- Preserve Bill reward state.

J. S.S. ANNE EXTERIOR ALIGNMENT

Use attached screenshot:
"SS Anne.png"

Current issue:
Ship is visually offset from the pier/bridge.
The front of the ship aligns where the middle/boarding presentation
should visually sit.

Required:
- Recenter/reposition exterior S.S. Anne relative to pier.
- Gangway/boarding location should visually make sense.
- Preserve valid collision and warps.
- Screenshot-match the improved composition.

K. S.S. ANNE RIVAL EXIT

Use attached screenshot:
"Rival SS Anne.png"

Current behavior:
Rival disappears after post-battle dialogue.

Required:
- Rival physically walks away/off-screen.
- Do not teleport/remove immediately in view.
- Preserve story completion flag and follower restoration.

L. CAPTAIN STAGING

Captain is seasick.

Required:
- Captain should remain oriented toward the trash can / sick posture
  where appropriate rather than snapping into a normal faceplayer
  presentation.
- HM01 Cut remains one-time.
- Repeated interaction must not duplicate HM.

M. FARFETCH'D NPC

Current issue:
Vermilion NPC talks about their Farfetch'd carrying a leek but no
Farfetch'd is visible.

Required:
- Add visible Farfetch'd partner, OR
- rewrite dialogue if map/object limitations make that preferable.

Preferred:
Add Farfetch'd.

N. MACHOKE SCALE

Use attached screenshot:
"Machoke and trainer.png"

Current issue:
Machoke overworld appearance looks disproportionately tiny next to
trainer/player.

Required:
Review overworld sprite dimensions / object presentation and improve
scale while preserving collision.

O. GYM GUIDE DIALOGUE

Gym guide / cheering NPC should have:
- before-leader dialogue
- after-leader victory dialogue

Apply to Lt. Surge and review Brock/Misty equivalents for consistency.

P. CUT EXPLANATION

Current tree interaction is too verbose.

Required:
Short, clear field-use text.

Example intent:
"A small tree blocks the path.
A compatible Pokémon can CUT it."

Do not repeatedly explain the full HM system at every tree.

Q. GLOBAL CUT TREE STATE BUG

This is a high-priority repair.

Observed conditions:

Case 1:
Follower itself is Cut-compatible and performs animation.
Tree rapidly reappears and player cannot pass.

Case 2:
Follower is not Cut-compatible and another compatible party Pokémon
performs field animation.
Tree may visually reappear, but collision can remain passable.

Other observations:
- some cut trees visually regrow while player can initially cross
- after waiting, collision may block again
- Vermilion Gym tree did not reproduce the same behavior

Required:
- Find root cause rather than patching individual maps.
- Cut tree visual state and collision state must remain synchronized.
- Tree should remain removed for appropriate current map/session
  behavior.
- Follower identity must not alter tree collision outcome.
- Test follower compatible/incompatible/off.
- Test multiple Kanto Cut trees.
- Test map exit/re-entry.
- Test save/reload where relevant.
- Do not break upstream non-Three-Horizons behavior.

Use attached screenshot:
"tree regrows but can walk past.png"

R. CLEFAIRY / MAKUHITA REPEAT SCENE

Use attached screenshot:
"clefairy dancing around makuhita.png"

The initial walking/circling scene is liked and should remain.

Spacing:
One Clefairy appears too close to Makuhita; adjust if feasible.

Repeat interaction:
Do NOT attempt the full circle choreography again.

Preferred repeat animation:
- Clefairy twirl/spin in place.
- Makuhita hops/bounces.
- brief friendly dialogue.

S. MT. MOON FOSSIL SCIENTIST

Scientist can initiate dialogue from an awkward stair/offset position.

Required:
- trigger from an appropriate approach location
- player turns toward scientist
- scientist faces player
- no dialogue from visually strange perpendicular position

T. JESSIE / JAMES SINGLE-BATTLE DIALOGUE

Keep current battle logic:
- 2+ usable Pokémon → double battle
- 1 usable Pokémon → Jessie then James singles

Improve single-battle story:
- James must contribute to introductory dialogue.
- Use a very brief recognizable "Prepare for trouble / make it
  double" style callback if desired, then use original Three Horizons
  dialogue.
- After beating Jessie but before James, Jessie must NOT say their
  full plan has failed.
- Create appropriate intermediate Jessie → James transition.
- Losing to James after beating Jessie must restart the pair correctly.
- Preserve no free heal between singles.
- Preserve final blasting-off sequence.

U. TRAINER BATTLE RUN OPTION

Ordinary trainer battles should not offer a normal flee/quit option
that behaves like intentional blackout.

Audit Three Horizons battle settings/scripts.

Do not affect intended escape mechanics for wild battles.

V. SELECT MOVE REARRANGEMENT

Playtest 13 requirement.

While selecting moves in battle:
- SELECT should allow move-order rearrangement.
- Preserve normal move selection.
- No corruption to move PP or battle state.
- Test repeated swaps.

W. FIRST-CATCH POKÉDEX PRESENTATION

Pixel corruption appears improved, but transition from Pokédex entry
to nickname screen feels too abrupt.

Review lifecycle.

Preferred:
- ensure Pokédex entry visibly completes
- preserve normal "data added/registered" presentation
- transition naturally to nickname prompt
- do not reintroduce previous sprite corruption
- repeated-A input must remain safe

X. S.S. ANNE DEPARTURE

Playtest 12 intentionally kept ship docked.

Playtest 13 changes this.

After:
- rival sequence complete
- captain helped
- HM01 obtained

Player should receive clear warning before final departure.

After player leaves under the departure condition:
- S.S. Anne departs
- boarding becomes unavailable
- do not strand player
- optional content warning should be clear before departure

Preserve save compatibility for Playtest 12 saves where ship is still
present.


==================================================
4. RG40XX H HARDWARE VERIFICATION
==================================================

Playtest 12 is now manually completed on:

Device:
Anbernic RG40XX H

Working core:
VBA-Next

Important:
gPSP was not suitable because of Flash/save compatibility.

User successfully completed the current chapter through Lt. Surge,
saved in-game, closed the game, reopened, and Continued.

Update documentation:
Playtest 12 is no longer "RG40XX H untested."

Record it as:
"Full Playtest 12 chapter completed on RG40XX H using VBA-Next by
the project owner/tester."

Do not claim gPSP compatibility.


==================================================
5. TRAINING / CUSTOMIZATION ECONOMY
==================================================

A. TRAINER SERVICES VENDORS

Create a recognizable recurring Trainer Services vendor/network in
major towns.

Primary inventory:
- Nature Mints
- Ability Capsule
- Ability Patch
- Bottle Cap
- Gold Bottle Cap

Do NOT sell:
- Power Bracer
- Power Belt
- Power Lens
- Power Band
- Power Anklet
- Power Weight

These are already supplied from the player's PC and do not need to
be sold.

Do NOT sell EV-reducing berries from this vendor.

Major cities may host this service.

Celadon exception:
Prefer an outdoor specialty stall near the fountain rather than
duplicating a normal indoor vendor inside the Department Store.

If an outdoor stall is technically clean, use it.
Otherwise Celadon may omit the recurring vendor because the
Department Store already serves a major retail function.

B. CERULEAN BERRY WORKSHOP

Make the Berry Workshop functional.

Primary role:
EV management specialist.

Sell:
- Pomeg Berry
- Kelpsy Berry
- Qualot Berry
- Hondew Berry
- Grepa Berry
- Tamato Berry

NPC should clearly explain:
Each berry lowers the corresponding EV stat by up to 10.

Optional later expansion:
friendship/status berries.

Do not overload Playtest 13 with a full berry-growing system.


==================================================
6. VS. SEEKER
==================================================

Add Vs. Seeker during Playtest 13.

Acquisition:
Vermilion Pokémon Center trainer-services / researcher NPC.

Behavior:
- unlimited use
- no charging requirement
- used for trainer rematches
- intended both as player QoL and QA/training utility

Dynamic rematch target:
roughly 10 levels below the player's current highest-level Pokémon.

However:
Implement sensible floors/caps tied to progression so:
- early trainers do not become absurd
- rematch teams do not exceed appropriate chapter limits
- weak early teams evolve/improve naturally where appropriate

The implementation plan must inspect current trainer scaling support before
inventing a new global system.

Playtest 13 QA will use Vs. Seeker heavily for evolution testing.


==================================================
7. BIKE SYSTEM
==================================================

Preferred:
Player ultimately receives both Mach Bike and Acro Bike.

If engine architecture safely supports both as distinct usable items:
implement both.

If not:
implement one Bike Key Item with safe mode switching between
Mach/Acro behavior.

Bike shop should explain differences.

Do not introduce a fragile workaround merely to hold two items.


==================================================
8. LATER-GENERATION EVOLUTION POLICY
==================================================

Three Horizons remains centered on Kanto, Johto, and Hoenn families.

Policy:

- Gen I–III families form the primary regional Pokédex identity.
- Later-generation evolutions of those families are allowed.
- Do not automatically enable the entire Gen IV–IX Pokédex simply because
  pokeemerald-expansion supports it.
- Later evolutions should be intentionally reachable and documented.

Examples that may be allowed:
- Annihilape
- Magnezone
- Rhyperior
- Electivire
- Magmortar
- Porygon-Z
- other natural cross-generation family extensions

Primeape:
Current expansion source includes potential evolution to Annihilape
after Rage Fist use if the cross-evolution configuration is enabled.

Playtest 13 should verify the actual active configuration rather than
assuming it.

Trade evolutions:
Must be obtainable without real multiplayer trading.

Preferred philosophy:
- traditional pure-trade evolutions can use sensible level-based or
  alternative single-player triggers
- trade+held-item evolutions should preferably use their thematic item
  directly or another clear single-player method
- preserve intuitive evolution identity where possible

Examples to audit:
Kadabra → Alakazam
Machoke → Machamp
Graveler → Golem
Haunter → Gengar
Scyther → Scizor
Onix → Steelix
Poliwhirl → Politoed
Slowpoke → Slowking
Seadra → Kingdra
Porygon → Porygon2
Porygon2 → Porygon-Z
Rhydon → Rhyperior
Electabuzz → Electivire
Magmar → Magmortar
Magneton → Magnezone
Primeape → Annihilape

Do not necessarily make every evolution accessible by Lavender.
Audit and document availability/method.

Playtest 13 walkthrough should contain an Evolution & Training QA section.


==================================================
9. SPECIES BALANCE CHANGES
==================================================

A. GYARADOS

Three Horizons typing:
Water / Dragon

Add useful physical Dragon options:
- Dragon Tail
- Outrage

Do not add Dragon Claw merely for coverage; it does not fit the
desired flavor.

Audit:
- rival/trainers using Gyarados
- wild/caught Gyarados
- existing saves
- level-up / relearn / TM behavior

B. TYPHLOSION

Retain:
Fire / Ground

Replace primary level-up Earthquake progression with:
Earth Power

Reason:
Typhlosion is intended primarily as a special attacker.

Earthquake may remain available through a separate compatible method/TM
if appropriate.

Do not remove unrelated approved Playtest 12 starter changes.

C. CHARIZARD

Keep current successful behavior:
Charizard learning Air Slash rather than Wing Attack is approved.

D. LASER FOCUS

Do not "fix" Laser Focus merely because multi-hit Fury Attack can crit
on each hit of the next attack.

Only investigate if critical guarantee persists across multiple separate
attacks/turns beyond intended behavior.


==================================================
10. BACKTRACKING PHILOSOPHY
==================================================

Three Horizons should increasingly reward returning to older areas.

This does NOT mean full map redesigns.

Use:
- badge/HM gated side paths
- small research scenes
- rare items
- shortcuts
- optional trades
- new Research Gear entries
- later Surf/Strength/Fly access

Avoid repeatedly rebuilding entire old maps.

First major Playtest 13 examples:
- Diglett's Cave
- Route 2 Cut area / Flash route
- Viridian Forest optional Cut clearing
- Cerulean Berry Workshop


==================================================
11. VIRIDIAN FOREST CUT CLEARING
==================================================

Add a small optional Cut-access clearing.

Do not redesign the whole forest.

Content:
- one meaningful rare item, preferably Bottle Cap or another useful
  customization resource
- one researcher interaction
- one authored regional-interaction scene
- Research Gear photo/report opportunity

Approved Pokémon scene:
Pinsir + Heracross

Concept:
A Kanto Pinsir and Johto Heracross peacefully share the same clearing.

Researcher observes that they are not displaying strong territorial
conflict.

Field Camera can photograph the scene.

After first scene:
Repeat interaction may use small movement/cry rather than replaying
full staging.


==================================================
12. POST-SURGE ROUTE / FLASH SEQUENCE
==================================================

After Lt. Surge:

Vermilion professor's aide should tell the player:

Professor Oak has asked another aide to meet them beyond Diglett's Cave
on Route 2.

This gives a story reason to backtrack.

Progression:

Vermilion
→ Route 11
→ Diglett's Cave
→ Route 2 south
→ aide building
→ Flash + Research Gear
→ optional Route 2 / Viridian Forest Cut rewards
→ return toward Cerulean
→ Route 9


==================================================
13. DIGLETT'S CAVE
==================================================

Open Diglett's Cave in Playtest 13.

Do not keep the artificial Playtest 12 closure.

Retain Diglett/Dugtrio identity.

Add regional migrants.

Approved additions:
- Phanpy — Johto
- Whismur — Hoenn

Suggested initial encounter philosophy:
Diglett remains dominant.
Regional migrants remain uncommon.

Exact rates may be finalized during implementation after preserving
reasonable overall encounter distribution.

Add miner/researcher dialogue:
Diglett activity has increased recently.
New tunnels/tracks have appeared.
Some tracks do not belong to Diglett.

Do not announce the cause.


==================================================
14. ROUTE 2 CUT AREA
==================================================

Open the previously inaccessible south Pewter/Route 2 facilities after
Cut access.

Include:
- Flash aide building
- trade house
- relevant connecting passage
- Diglett's Cave connectivity

CUSTOM IN-GAME TRADE:

Player gives:
Zubat

Player receives:
Skarmory

Story:
NPC has a friend/contact in Johto who sent the Skarmory while reporting
unusual Pokémon movements.

This optional trade should reinforce that Johto is also experiencing
cross-region activity.

Test:
- normal trade
- canceled trade
- missing Zubat
- party full behavior
- nickname / OT / traded Pokémon handling
- save/reload


==================================================
15. FLASH ACQUISITION
==================================================

Oak's aide on Route 2 provides:

- HM05 Flash
- Research Gear

Suggested requirement:
10 Pokémon registered in Pokédex.

If player does not meet requirement:
- clearly explain requirement
- do not strand player
- nearby Kanto areas contain enough obtainable species

Do not require impossible progression.

Field use of Flash should follow the same Three Horizons HM philosophy:
ownership + compatible conscious non-Egg Pokémon + appropriate gate,
without requiring that Flash occupy a permanent battle move slot,
if compatible with the established HM system.


==================================================
16. RESEARCH GEAR
==================================================

Official system name:
RESEARCH GEAR

Do NOT build a complete Pokégear or PokéNav clone.

Initial Playtest 13 modules:

1. CALLS
   - Professor Oak
   - Professor Elm
   - Professor Birch

2. RESEARCH LOG

3. FIELD CAMERA / RESEARCH PHOTOS

Possible later contacts:
- Rival
- Bill
- Mr. Fuji
- other researchers

Calls are:
- meaningful
- event-driven
- story-focused

Do NOT generate random nuisance calls.

Possible triggers:
- major research sighting
- major town arrival
- Gym milestone
- Rocket clue
- research objective completion


==================================================
17. RESEARCH GEAR INTRODUCTION
==================================================

The Research Gear is intentionally introduced after Surge.

Story logic:

At first:
Oak asks player/rival to observe and report casually.

By Badge 3:
The volume and seriousness of field reports has increased.

Oak, Elm, and Birch need a direct research communication method.

Route 2 aide gives the Research Gear.

First activation:
- Oak contacts player.
- Elm and Birch are introduced as direct research contacts.
- Professors acknowledge the player's previous observations.
- They confirm similar irregular sightings are occurring in Johto and Hoenn.

This should feel like a promotion:
trainer helping Oak → active field researcher for all three professors.


==================================================
18. RESEARCH LOG
==================================================

Research Log tracks authored story observations.

Suggested structure:

Region
Location
Species
Origin
Observation
Research Photo
Professor Note

Initial Kanto entries can include:

- Route 1 — Hoothoot
- Viridian Forest — Treecko / Weedle
- Viridian Forest — Shroomish / Caterpie
- Mt. Moon — Clefairy / Makuhita
- Vermilion Harbor / S.S. Anne — cross-region shipping observations
- Viridian Forest Cut Clearing — Pinsir / Heracross
- Diglett's Cave — Phanpy / Whismur
- Route 9 — Mareep / Nidoran
- Rock Tunnel — Aron / Geodude
- Lavender — Misdreavus anomaly

Older entries may later receive updated professor notes as the mystery develops.

Do not overbuild this into a huge quest journal yet.


==================================================
19. FIELD CAMERA
==================================================

Field Camera works only on authored Research Scenes in Playtest 13.

Do NOT implement free screenshot storage.

Reason:
Actual GBA framebuffer screenshots would consume excessive save/storage space.

Behavior:
At an authored scene:

"A rare interaction is unfolding.
Photograph it?"

YES / NO

YES:
- brief white flash
- camera sound
- unlock a Research Photo entry
- save only a small completion flag/state
- photo/card image remains ROM-side

Example:

FIELD PHOTO
Viridian Forest
Pinsir & Heracross

"Two Bug-type Pokémon from different regions were observed sharing
the same clearing."

Professor note may appear beneath it.

No literal framebuffer image needs to be stored in save data.

System must remain save-compatible.


==================================================
20. ROUTE 9
==================================================

Keep Route 9 primarily recognizable as Kanto.

Do not over-script it.

Add:
- normal trainer progression
- items
- researcher/student
- rare regional migrant
- one authored research scene

Researcher concept:
Oak's encounter data no longer matches previous seasonal distributions.

Approved rare migrant:
Mareep — Johto

Suggested rare rate:
~5%, subject to final balanced table.

Visible scene:
Mareep peacefully grazing/interacting with Nidoran.

Research interpretation:
They are not fighting.
Local Pokémon appear to be adapting to the newcomer.

Camera opportunity:
Yes.

Research Gear entry:
Yes.


==================================================
21. ROUTE 10 / POKÉMON CENTER
==================================================

Route 10 Pokémon Center becomes a research checkpoint.

Oak/Elm/Birch communication should confirm:

- Johto is seeing unusual Kanto species.
- Hoenn reports are also changing.
- The pattern is not one-directional.
- Seasonal migration alone does not explain the rate.

Do not reveal the true mechanism.

Prepare player for Rock Tunnel.


==================================================
22. ROCK TUNNEL
==================================================

Rock Tunnel is the exploration centerpiece of Playtest 13.

Keep the cave unmistakably Kanto-first.

Add uncommon regional Pokémon:
- Aron — Hoenn
- Dunsparce — Johto

Suggested:
~5% each, subject to encounter-table balancing.

Primary visible scene:
Aron + Geodude

Concept:
Aron scrapes/feeds on mineral-rich rock.
Geodude interacts with or investigates the same mineral area.
They coexist rather than immediately fighting.

Researcher/Hiker observation:
"I've never seen an Aron here before...
but it's behaving like it belongs."

Camera opportunity:
Yes.

Research Log:
Yes.

Use Flash meaningfully but do not create unnecessary darkness frustration.


==================================================
23. LAVENDER TOWN ARRIVAL
==================================================

Tone changes here.

Earlier migration scenes were mostly:
curious
beautiful
peaceful
interesting

Lavender should introduce:
uncertainty
unease
emotional consequences

Do not turn the whole game into horror.

Approved regional anomaly:
Misdreavus — Johto

Visible Misdreavus near Pokémon Tower:
- quietly watching
- subtle movement/disappearance
- not automatically battleable
- no obvious trainer
- no clear cargo/travel explanation

This event challenges Bill's shipping-route hypothesis.

Camera opportunity:
Yes, but presentation may be more mysterious than earlier scenes.


==================================================
24. THE STORY HYPOTHESIS SHIFT
==================================================

Prior working theory:
Cross-region Pokémon may be following cargo routes, ships, trainers,
or familiar habitats.

Lavender must introduce evidence that does not fit.

Misdreavus near Pokémon Tower should become one of the first anomalies
that cannot reasonably be attributed to shipping/travel.

Professor interpretation:
"We don't have enough evidence to explain this."

Do NOT replace uncertainty with exposition.


==================================================
25. POKÉMON TOWER
==================================================

Preserve the core Kanto story:

- Cubone
- Marowak
- ghosts
- Team Rocket
- Mr. Fuji
- Silph Scope requirement

Do NOT replace the Kanto story with Three Horizons lore.

Instead:
weave Three Horizons around it.

Rocket involvement:
Some members have orders to document:
- unusual Pokémon
- strange behavior
- ghost reports
- migration data

Not every grunt understands Giovanni's interest.

Some Rockets care only about theft/exploitation.

This creates texture inside Team Rocket.

Player advances until the unidentified ghost blocks further progress.

No Silph Scope yet.

Further progress requires Celadon.


==================================================
26. MR. FUJI
==================================================

Mr. Fuji should eventually provide a different perspective than Oak.

Oak/Bill:
scientific observation

Fuji:
experience, empathy, Pokémon behavior, older wisdom

Fuji should NOT explain the full mystery.

Conceptual worldview:
"Pokémon often sense changes in the world before people do."

This should become more meaningful later in Johto.

Playtest 13 may introduce Fuji indirectly or partially depending on
the natural Pokémon Tower stopping point.


==================================================
27. JESSIE, JAMES & MEOWTH
==================================================

They should remain special rather than appearing constantly.

Playtest 13:
one memorable cameo around Lavender / Pokémon Tower.

Preferred:
- they are investigating strange activity for Team Rocket
- Jessie pretends not to be afraid of ghosts
- James is visibly less confident
- Meowth wants to leave
- humorous but not disruptive to Lavender tone
- no required boss fight in Playtest 13

They leave before a battle.

Set up stronger return for Playtest 14 / Celadon.

Use original Three Horizons dialogue except for any very brief iconic callback.


==================================================
28. RIVAL DEVELOPMENT
==================================================

Rival should evolve beyond appearing only to battle.

Playtest 13 rival scene:
Rival admits they originally believed Oak was mainly giving them an excuse
to travel.

Now they recognize that the reports are real and widespread.

They care about the investigation while remaining competitive.

Battle may still occur.

After battle:
Rival remains narratively involved.
Do not simply disappear from the story.

Long-term:
The rival becomes both:
friendly competitor + fellow investigator.


==================================================
29. PLAYTEST 13 ENDPOINT
==================================================

Player progresses into Pokémon Tower.

An unidentified ghost blocks progress.

Player lacks Silph Scope.

Dialogue/research clues point toward Team Rocket activity in Celadon.

Celadon becomes the next destination.

Display an appropriate Playtest 13 completion message without breaking
diegetic progression.

Do NOT use obsolete "this route opens in another beta" text if the in-world
reason already explains the block.

Desired final feeling:

"We understand more than before,
but the mystery has become larger."


==================================================
30. EVOLUTION & TRAINING QA
==================================================

Playtest 13 walkthrough must include an Evolution & Training QA section.

Use unlimited Vs. Seeker to efficiently test available families.

Track:

- evolution trigger
- level/item/move requirement
- canceled evolution
- learned-on-evolution moves
- type after evolution
- ability persistence
- nature persistence
- IV/EV persistence
- shiny persistence
- follower graphics
- nickname persistence
- save/reload

Priority examples as available:
Primeape → Annihilape
Kadabra → Alakazam
Machoke → Machamp
Graveler → Golem
Haunter → Gengar
Scyther → Scizor
Onix → Steelix
Seadra → Kingdra
Magneton → Magnezone

Do not assume all are reachable by Lavender.


==================================================
31. RESEARCH STORY ARC THROUGH PLAYTEST 15
==================================================

Playtest 13:
Migration/travel hypothesis begins to fail.
Ends at Lavender/Silph Scope requirement.

Playtest 14:
Lavender → Route 8 → Celadon → Erika →
Rocket Game Corner / Hideout →
Silph Scope →
return to Lavender →
Pokémon Tower resolution / Mr. Fuji.

Playtest 15:
Saffron →
Silph Co. →
Giovanni →
deeper scientific evidence →
Sabrina.

Story escalation:

Pallet:
Three-professor collaboration.

Viridian:
first unusual sightings.

Mt. Moon:
cross-region interaction + Rocket surveillance.

Bill:
sightings form a pattern.

S.S. Anne:
travel/shipping theory.

Surge:
phenomenon continues.

Diglett's Cave:
animal behavior/environment changes.

Route 9:
local ecosystems adapt.

Rock Tunnel:
regional species appear comfortable in foreign habitat.

Lavender:
travel explanation no longer sufficient.

Celadon:
Rocket possesses its own data/research.

Silph:
phenomenon produces measurable scientific evidence.

Later Kanto:
clues increasingly point toward Johto.

Johto:
history/tradition reveals the phenomenon may have precedent.

Hoenn:
ecological/natural consequences become the major focus.


==================================================
32. SAVE COMPATIBILITY
==================================================

Preserve Playtest 12 battery saves.

Do not require a New Game for Playtest 13.

Player should be able to:

1. Back up Playtest 12 in-game battery save.
2. Copy it to match Playtest 13 ROM filename.
3. Launch Playtest 13 normally.
4. Choose Continue.
5. Preserve:
   - party
   - boxes
   - IVs/EVs
   - nature
   - abilities
   - nicknames
   - items
   - money
   - badges
   - Pokédex
   - fossil progress
   - Rocket progress
   - rival partner
   - research progress
   - previous rewards

Never require loading an old emulator save state.

Migration must be idempotent.

Do not grow or renumber save structures casually.

Audit flags/vars before allocating Research Gear / photo / chapter state.


==================================================
33. SCREENSHOT EVIDENCE FOR CODEX
==================================================

Use the user's attached Playtest 12 screenshots as explicit visual references.

Files:

- Rival SS Anne.png
- SS Anne.png
- fat person where you have to cut tree to interact.png
- building closed south pewter.png
- tree regrows but can walk past.png
- Trainer randomly appears quickly before entrance to route to mt moon from pewter.png
- clefairy dancing around makuhita.png
- Machoke and trainer.png

Treat screenshots only as references for named issues.

Do not infer unrelated requested changes from background details.


==================================================
34. NON-GOALS FOR PLAYTEST 13
==================================================

Do NOT:

- build Celadon fully
- build Erika
- build Rocket Hideout
- resolve Pokémon Tower
- build Saffron
- build Silph Co.
- build Sabrina
- reveal the cause of the Three Horizons phenomenon
- add every Gen IV–IX Pokémon
- create free-camera screenshot saving
- create a full Pokégear/PokéNav clone
- rebuild all early Kanto maps
- make random professor calls
- require multiplayer trading
- merge unrelated upstream changes
- silently suppress assertions or failing tests
- sacrifice Playtest 12 save compatibility merely to simplify implementation


==================================================
35. RELEASE / ACCEPTANCE REQUIREMENTS
==================================================

Before packaging Playtest 13:

- all required Playtest 12 repair items tested
- save migration tested from exact Playtest 12 battery save
- Research Gear persists through save/reload
- Field Photo flags persist
- photos cannot duplicate/corrupt save
- Calls trigger once where appropriate
- Research Log updates appropriately
- Flash route is accessible
- Diglett's Cave connected
- Skarmory trade tested
- Viridian Forest Cut clearing tested
- Route 9 complete
- Route 10 complete
- Rock Tunnel complete
- Lavender complete through intended Pokémon Tower endpoint
- Misdreavus event tested
- rival scene tested
- Jessie/James cameo tested
- Vs. Seeker tested
- SELECT move rearrangement tested
- Cut-tree follower/non-follower regression tested
- S.S. Anne departure tested
- Gyarados/Typhlosion changes tested
- later-gen evolution configuration audited
- normal Emerald/FireRed/LeafGreen upstream compatibility preserved
- Three Horizons regression suite passes
- save-layout tests pass
- manual mGBA playthrough performed
- RG40XX H Playtest 13 remains a separate user hardware acceptance pass
- ROM checksum and source revision documented

Create:

PLAYTEST_13.md
PLAYTEST_13_ENCOUNTERS.md
PLAYTEST_13_EVOLUTION_QA.md
PLAYTEST_13_VERIFICATION.md

Package the candidate without distributing a commercial Pokémon ROM publicly.

==================================================
36. APPROVED REVIEW ADDENDUM — 2026-09-28
==================================================

Status: USER-APPROVED FOCUSED REVIEW CORRECTION / POLISH ADDENDUM.
This section records the user's review request accompanying attachment
`d48924d2-b888-43c3-bc8a-589accb6382b/Pasted text.txt`.
Historical approved text above is retained unchanged. This addendum clarifies
implementation and acceptance where the plan was inaccurate, and adds only
the four approved polish items below. If implementation wording conflicts
with this addendum, this addendum controls. Unrelated approved design remains
unchanged.

Planning instruction for this correction:
DO NOT IMPLEMENT GAME CODE YET.
DO NOT rebuild or restart repository exploration.
Patch the existing specification/plan only, report the changes, and STOP.
The existing 41-task plan is approved except for these corrections/addenda.

36.1 JESSIE / JAMES — PRESERVE BOTH BATTLE FORMATS

Preserve the existing behavior already approved in section 3.T:
- With 2 or more usable conscious Pokémon, Jessie + James fight together
  in the existing double battle, using Ekans/Koffing and the existing split
  opponent-party presentation.
- With exactly 1 usable conscious Pokémon, Jessie/Ekans is fought first,
  followed by James/Koffing as consecutive singles with no free healing.
- Losing either format allows the appropriate encounter to restart correctly.
- Losing to James after defeating Jessie restarts the single-battle pair.
- Completion occurs only after the full selected encounter is won.
- Keep improved James dialogue, appropriate intermediate single-battle
  dialogue, and the final shared blast-off.
- Meowth remains a speaking noncombatant.
- Do not remove the approved 2+ Pokémon double-battle path.

Acceptance must cover both formats, usable-party thresholds, split opponent
presentation, loss/retry and one-time completion. The single-battle dialogue
repair is not authorization to replace the double-battle path generally.
Plan ownership: Task 21; related battle/release checks in Tasks 22 and 41.

36.2 FLASH / FIELD-USE HM CONVENIENCE

For Three Horizons field-use HMs:
- the player owns the HM;
- the appropriate badge/story gate is satisfied;
- a conscious, non-Egg, compatible party Pokémon exists;
- the Pokémon DOES NOT need to know the HM move;
- the Pokémon DOES NOT need a free move slot.

Flash follows the same established convenience philosophy as Cut. A compatible
Pokémon with four unrelated moves is eligible when ownership/gates are met.
Field use does not require teaching/replacing a move. Verify both Flash and
Cut with full movesets, unknown HM moves, and the normal negative cases for
missing HM/gate, fainted Pokémon, Eggs and incompatible species.
Plan ownership: Task 34 and release acceptance in Task 41.

36.3 RESEARCH PHOTOS MUST HAVE A VISUAL DEPICTION

An unlocked Research Photo card must not degrade into a text-only Research
Log entry. Each card should visibly depict the authored Pokémon interaction
when technically reasonable.

Preferred low-cost implementation: compose existing overworld Pokémon
sprites and scene assets into a small ROM-side framed tableau/card.
Examples requiring visual acceptance:
- Pinsir + Heracross;
- Mareep + Nidoran;
- Aron + Geodude;
- Misdreavus.

The card also retains location, species, short observation and professor note.
Only tiny persistent photo IDs/flags are stored in the save. Composition and
artwork remain ROM-side. Do not store framebuffer screenshots, introduce
free-camera mode, or save image payloads.

If a demonstrated GBA limitation prevents a visual card, document that
specific technical conflict before proposing a reduced representation.
Do not silently substitute text-only cards. Capacity is to be measured during
implementation; no limitation is asserted by this addendum.
Plan ownership: Tasks 30–31, scene/photo acceptance in Tasks 36–39, and Task 41.

36.4 APPROVED PLAYTEST 12 POLISH ADDENDUM

A. S.S. ANNE REGIONAL-WORLDBUILDING
Add a small number of Johto/Hoenn travelers and/or visible partner Pokémon
aboard the ship, using appropriate existing graphics. Keep the ship
uncrowded, preserve routes/interactions, and add no new major event.
Dialogue should reinforce interregional travel and unusual sightings
elsewhere without revealing the cause of the Three Horizons phenomenon.
Plan ownership: Task 32; release acceptance in Task 41.

B. POKÉMON FAN CLUB CHAIRMAN
Expand the Vermilion chairman's Rapidash dialogue before awarding the Bike
Voucher. Keep it charming and memorable without excessive length. Preserve
the one-time voucher behavior, including full-bag retry and repeat visits.
Plan ownership: Task 28; release acceptance in Task 41.

C. BUG CATCHER KEIGO
Review and improve his weak/repetitive team so he feels like a progressed
Bug Catcher at this point of Kanto. The user's suggested direction is evolved
Bug Pokémon such as Kakuna/Beedrill/Butterfree rather than two Weedle plus
Caterpie. This is a direction, not a fixed newly approved exact team/level list.
Keep surrounding-route-appropriate levels and normal EXP balance. This
approved initial-roster polish is distinct from Vs. Seeker rematch scaling.
Plan ownership: Task 27; release acceptance in Task 41.

D. POKÉMON CENTER UPSTAIRS
For currently accessible Three Horizons Kanto Centers where native layouts
and assets allow it cleanly, open the upstairs/link-service floor rather than
leaving stairs/escalators artificially inaccessible. Reuse native assets and
preserve reciprocal stairs/warps and safe save/Continue upstairs.

This is presentation/world completeness only:
- appropriate native-style attendants and NPC dialogue;
- attendants may explain that communication/link services are unavailable
  or not currently offered;
- no real multiplayer trading is required;
- no link-cable infrastructure or networking subsystem is required;
- no communication-wait or link-trade entry point should be exposed by
  presentation-only attendant interactions.

Scope is currently accessible Centers, including those opened by this
chapter, not future-region construction. Record any specific native-layout
or asset limitation instead of silently retaining an arbitrary closure.
Plan ownership: Tasks 38–39; release acceptance in Task 41.

36.5 KEEP THE OTHER APPROVED PLAN DECISIONS

The following remain approved and unchanged:
- conversation-only Lavender rival scene;
- proposed level-36 alternatives for pure trade evolutions;
- thematic-item direct evolution approach;
- native Vs. Seeker adaptation/scaling architecture;
- Research Gear as an unlocked Start-menu feature;
- species remain compiled for save/ID compatibility, with TH availability
  curated rather than globally exposing later-generation families;
- Playtest 13 ends at the unidentified Tower ghost / Silph Scope lead;
- Celadon remains Playtest 14 content.

No task renumbering is needed. The corrected implementation plan retains
41 tasks. Implementation remains stopped until explicitly requested.

## Approved integration correction — 2026-09-29

The user approved the recommended resolution of the demonstrated ship-photo progression conflict. Preserve Research Gear after Surge and irreversible S.S. Anne departure after Cut/final exit. Add a small repeatable Marill/Wingull authored scene at Vermilion Harbor after departure, reusing the existing shipping observation/photo entry and flag. The partners' trainers stayed in Vermilion. Before Gear, the scene records only the observation; after Gear, offer the ordinary Yes/No photo flow. Decline permits retry, success persists and repeats do not duplicate. Keep pier access clear and verify small/large/no follower, cold Continue and normal progression order. No automatic photo grant, early Gear, delayed ship departure or save-block growth. Also repair the cargo-report conversation to record its shipping observation on first and repeat visits independently of Gear; hearing a report never grants a photo.
