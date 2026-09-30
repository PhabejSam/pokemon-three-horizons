Pokémon: Three Horizons
Playtest 13.1 / RC2 — Research Gear + Hardware Stabilization Pass

Repository:
PhabejSam/pokemon-three-horizons

Development branch:
feature/opening-demo

Current Playtest 13 software candidate:
Feature revision:
24ef1cb7c5bfa264685032427181ce65ed9f889d

Compiled/test revision:
c83e8c08adba9ace2f0c75139915b2ace8cb2f7a

Current ROM:
pokemon-three-horizons-playtest-13-road-to-lavender.gba

Current ROM SHA-256:
ad918b00e4476e9db68cb1445206ef1126e8d962be51cd74208442be3ff85077

The Playtest 13 candidate passed desktop software acceptance, but the project
owner began actual RG40XX H / VBA-Next hardware acceptance and found several
important issues early in the playthrough.

This task is a focused Playtest 13.1 / RC2 stabilization and presentation pass.

DO NOT begin Playtest 14.
DO NOT add Celadon content.
DO NOT expand the story beyond the existing Lavender / Pokémon Tower endpoint.
DO NOT redesign unrelated systems.
DO NOT merge the draft PR.

Preserve all currently passing Playtest 13 work unless this prompt explicitly
changes it.

==================================================
HARDWARE TEST ENVIRONMENT
==================================================

Device:
Anbernic RG40XX H

Core:
VBA-Next

Save method:
raw battery EEPROM file under:

/mnt/data/.vbanext/eeprom/

The PT12 -> PT13 battery migration has now been confirmed to load correctly on
actual hardware.

The project owner is testing from the migrated post-Surge save.

==================================================
CONFIRMED HARDWARE PASSES TO PRESERVE
==================================================

The following already worked correctly during actual RG40XX H testing:

- PT12 -> PT13 battery save migration
- Continue loads correct post-Surge progress
- Cut works in tested areas
- tested Cut trees do not immediately regrow
- Zubat -> Skarmory in-game trade works
- current party/progression carried over correctly

Do not regress these systems.

==================================================
1. RESEARCH PHOTO PALETTE / BLACK-SCREEN BUG
RELEASE BLOCKER
==================================================

Observed on actual RG40XX H / VBA-Next:

- Taking a Research Photo causes the overworld screen to become darker.
- Repeated Research Photos on the same map progressively darken the screen.
- In Viridian Forest, where multiple authored research interactions can be
  photographed, the screen eventually becomes completely black.
- Leaving the area/map restores normal brightness.

This indicates a palette/fade lifecycle problem.

Inspect the full Research Photo flow, including:

TH13_ResearchPhoto

and any palette/fade state used by:

- fadescreen FADE_TO_WHITE
- fadescreen FADE_FROM_WHITE
- camera flash
- Research Gear menu open/close
- follower refresh
- day/night palette state
- map palette restoration

Do NOT simply remove the camera effect unless there is a demonstrated engine
constraint requiring it.

Required behavior:

- brief visible camera flash
- exact original overworld brightness/palette restored afterward
- no cumulative darkening
- no black screen
- multiple photos on the same map are safe
- declining a photo changes nothing
- repeat interactions change nothing
- opening Research Gear after a photo does not affect brightness
- closing Research Gear restores field graphics correctly
- save/Continue does not preserve a bad fade state
- follower visibility/palette remains correct
- day/night tint remains correct

Required regression matrix:

1. first photo
2. second photo on same map
3. third photo on same map
4. decline -> later accept
5. photo -> open Research Gear -> close
6. photo -> enter/exit building
7. photo -> map transition
8. photo -> in-game Save -> cold Continue
9. photos with follower on/off
10. photos during day/night

Viridian Forest must specifically be tested because hardware reproduced the
full-black failure there.

Use exact-ROM visual/emulator evidence in addition to host/static tests.

==================================================
2. OBSOLETE VERMILION CHAPTER-END DIALOGUE
REQUIRED
==================================================

Actual hardware finding:

The outdoor scientist / Oak aide near the Vermilion entrance still says that
the story/chapter ends here.

Current source inspection shows the Vermilion outdoor scientist is still bound
to:

TH12_Chapter_End

This is obsolete in Playtest 13.

Replace this with current progression dialogue.

Suggested role:

Before Surge:
- acknowledge the ongoing investigation
- encourage finishing Vermilion / Surge / ship objectives

After Surge:
- direct the player east toward Route 11
- mention Diglett's Cave / Oak's research network
- no beta/playtest language

Also perform a repository-wide audit of currently accessible Playtest 13 content
for obsolete phrases or scripts equivalent to:

- chapter ends here
- this is the end of the playtest
- opens next playtest
- come back in another build
- future beta boundary

Remove obsolete development-boundary dialogue where real in-world progression
now exists.

Do NOT remove legitimate in-world barriers such as:
- Saffron closure
- Silph Scope ghost barrier
- future Route 12/Snorlax boundary
when they have proper story justification.

==================================================
3. MOVE RESEARCH GEAR EARLIER IN THE STORY
APPROVED DESIGN CHANGE
==================================================

Actual play made the current timing feel wrong.

Three Horizons establishes the player as a field researcher from the beginning.

Several authored research scenes occur before Surge:
- early regional sightings
- Viridian Forest observations
- Mt. Moon interactions
- ship observations

Receiving Research Gear only after Badge 3 makes the feature feel retrofitted and
forces unnatural backtracking just to photograph events the player already saw.

NEW GAME BEHAVIOR:

Professor Oak should give/unlock the Research Gear during the opening laboratory
sequence as part of the original Three Horizons field-research assignment.

Place the handoff at a natural point after:
- partner/Pokédex setup
- Oak explains the unusual cross-region sightings
- before the player begins the normal Kanto journey

Oak's explanation should be concise.

The player should understand:

- you are traveling normally as a Trainer
- Oak, Elm and Birch are comparing unusual Pokémon appearances
- Research Gear records authored observations
- Field Camera works only on unusual research interactions
- Research Log stores findings
- professor communications will become available over time

Do NOT make the opening significantly longer.

Research Gear should feel like a core identity of Three Horizons, not a later
side feature.

==================================================
4. MIGRATED PT12 / EXISTING PT13 SAVE COMPATIBILITY
==================================================

Do NOT break existing saves.

MIGRATED PLAYTEST 12 SAVES:

These saves obviously could not receive Research Gear in Oak's lab.

Provide a bounded catch-up route.

Preferred behavior:

- if a migrated P12 save reaches Vermilion/post-Surge without FLAG_TH13_GEAR,
  the Vermilion Pokémon Center research scientist gives/unlocks Research Gear
  during the continuation route.
- explain briefly that Oak sent upgraded field equipment now that reports are
  becoming more important.
- then direct the player toward Route 11 / Diglett's Cave / Route 2.

Do NOT fabricate photographs from prior versions.

Existing witnessed P12 events may continue importing as Research Log reports
where reliable receipts exist.

Photos must still be captured in Playtest 13+.

EXISTING PLAYTEST 13 SAVES:

Some PT13 saves already obtained Gear from Route 2.

They must remain valid.

- preserve Gear unlock
- preserve observations
- preserve photos
- preserve delivered calls
- no duplicate Gear acquisition
- no duplicate professor initialization
- no duplicate Flash
- no migration reset

Migration must remain idempotent.

==================================================
5. ROUTE 2 AIDE / FLASH HANDOFF REDESIGN
==================================================

Because Research Gear now belongs earlier:

The Oak aide in the Route 2 building south of Diglett's Cave should no longer
introduce Research Gear as though the system begins there.

Primary role should now be:

- recognize the player's existing research role
- check Thunder Badge / Pokédex requirement
- give HM05 Flash
- explain Rock Tunnel field use
- mention ongoing professor research
- point toward the next stage of investigation

Preserve the approved Flash philosophy:

- HM05 owned
- appropriate badge/story gate
- conscious compatible non-Egg Pokémon
- Pokémon does NOT need to know Flash
- Pokémon does NOT need a free move slot

The suggested ten caught/received species requirement may remain for Flash if
current progression testing confirms it is still reasonable.

Dialogue paths must work for:

- New Game player with Gear already unlocked
- migrated PT12 save that got Gear in Vermilion
- existing PT13 save that already got Gear/Flash
- player under ten species
- player without Thunder Badge
- full bag
- previously owned HM05
- repeat interaction

No duplicate rewards.

==================================================
6. PROFESSOR CALL PACING / PRESENTATION REDESIGN
==================================================

Actual hardware feedback:

When Research Gear was first received, Oak, Elm and Birch messages appeared
back-to-back in one sequence.

This felt crowded and unnatural.

Do NOT force three professor speeches consecutively.

New principle:

One meaningful professor communication at a time.

Oak:
- introduces the mission and Research Gear in person in Pallet
- remains the main Kanto coordinator

Elm:
- becomes an active contact at an appropriate Johto-related observation

Birch:
- becomes an active contact at an appropriate Hoenn-related observation

Suggested progression:

Oak:
Opening lab assignment / Gear introduction.

Elm:
After an early Johto-associated observation, or another natural early milestone.

Birch:
After an early Hoenn-associated observation such as Makuhita / another Hoenn
research event.

Route 10:
One concise coordinator call.
Additional professor analysis can become readable in Calls without forcing three
messages consecutively.

Lavender:
Prefer the professor most relevant to the current anomaly.
For Misdreavus, Elm is narratively appropriate.
Oak/Birch commentary can update in the Calls menu without interrupting the player.

Calls remain:
- event-driven
- short
- safe
- non-random
- never mid-battle/menu/warp/field move

Audit the current call dispatcher for unintended hard-coded location restrictions.
A pending call should not require the player to stand in an unrelated specific
map unless that is intentionally authored.

Professor familiarity should build gradually so meeting Elm in Johto and Birch
in Hoenn later has narrative payoff.

==================================================
7. RESEARCH GEAR UI / UX COMPLETE VISUAL REVAMP
APPROVED REQUIREMENT
==================================================

Actual hardware feedback:

The Research Gear and navigation menus visually feel out of place.

They do not feel like Pokémon.

The interface currently feels too custom / fan-made / technical compared with
the rest of the GBA game.

The Research Gear needs a presentational redesign before the full hardware
playthrough continues.

CORE DESIGN GOAL:

The Research Gear should feel like a believable official GBA-era Pokémon feature,
visually related to:

- Pokédex
- Trainer Card
- Pokémon Summary
- FRLG/Emerald menu language

Avoid:
- overly modern app-like UI
- heavy dark panels
- unusual colors that clash with Pokémon
- overly technical dashboard styling
- large blocks of UI that overpower the actual research scenes
- generic placeholder-looking terrain

Favor:
- bright/readable Pokémon-style windows
- clean borders
- classic GBA menu spacing
- modest accent colors
- simple cursor navigation
- familiar Pokémon typography
- minimal clutter

==================================================
8. RESEARCH GEAR MAIN MENU REDESIGN
==================================================

The main Gear menu should be clean and simple.

Recommended modules:

- RESEARCH LOG
- FIELD PHOTOS
- CALLS

Optional fourth module only if already justified:
- FIELD NOTES / MAP NOTES

Do not add unnecessary systems.

The screen should visually resemble a Pokémon device/menu rather than a modern
software interface.

Use native-style window graphics / borders where possible.

Navigation must remain obvious:

A = Open
B = Back
Up/Down = Select

Do not hide basic navigation behind overly custom presentation.

==================================================
9. FIELD PHOTO VIEWER MUST SHOW THE ENVIRONMENT
MAJOR VISUAL REQUIREMENT
==================================================

Current feedback:

The photographs do not sufficiently convey where the picture was actually taken.

The player should be able to look at a Research Photo and immediately feel:

"That was the scene I photographed."

The PHOTO itself should be the primary visual element.

Preferred layout:

--------------------------------
FIELD PHOTO
[ large authored scene image ]

Viridian Forest
Pinsir + Heracross

short observation

A: Details
B: Back
--------------------------------

The environment/photo area should occupy the majority of useful screen space.

Do NOT surround it with large amounts of UI chrome.

==================================================
10. AUTHORED ENVIRONMENTAL PHOTO BACKDROPS
==================================================

Improve the current generic photo tableau system.

Preferred technical approach:

Use ROM-authored miniature scene compositions based on the ACTUAL location.

Where practical:

- reuse real map tiles / metatiles / environmental graphics
- reconstruct a recognizable crop of the actual authored research location
- composite the relevant overworld Pokémon sprites into that environment
- preserve location-specific visual identity

Examples:

Viridian Forest:
- actual forest grass/tree/canopy feel
- Pinsir + Heracross positioned as in their authored clearing

Route 9:
- recognizable grassy Route 9 setting
- Mareep + Nidoran grazing

Rock Tunnel:
- real cave/mineral feel
- Aron + Geodude at a mineral seam

Vermilion Harbor:
- pier/harbor/ocean context
- Marill + Wingull

Lavender:
- town/Tower atmosphere
- Misdreavus near the Tower environment

Mt. Moon:
- cave environment rather than a generic dark rectangle

Do NOT save literal screenshots/framebuffers.

Only store the existing small photo ID/flag.

Photo artwork/backdrop remains ROM-side.

If directly using map tiles is impractical because of VRAM/palette constraints,
build a small authored backdrop that clearly resembles the actual location.

Do NOT fall back to generic colored rectangles unless a specific measured engine
limitation is documented.

==================================================
11. RESEARCH LOG VISUAL REDESIGN
==================================================

Research Log should feel like clean Pokémon field notes.

Each entry should prioritize:

- Location
- Species
- short Observation
- Region/origin
- Photo status
- Professor note

Avoid presenting too much text at once.

Use pagination/details rather than cramming information.

Example feel:

VIRIDIAN FOREST

PINSIR + HERACROSS

Two Bug-type Pokémon from different
regions share the same clearing.

PHOTO: RECORDED

A: Details
B: Back

Professor analysis can live on a second page.

==================================================
12. CALLS MENU VISUAL REDESIGN
==================================================

Calls should feel like a simple Pokémon communication log.

List example:

PROF. OAK
Field Assignment

PROF. ELM
Johto Habitat Report

PROF. BIRCH
Hoenn Migration Notes

Selecting one opens the latest report.

Do NOT make Calls resemble a modern smartphone messaging application.

Keep the presentation simple and consistent with GBA Pokémon.

==================================================
13. RESEARCH GEAR VISUAL ACCEPTANCE TESTS
==================================================

Capture and inspect native-resolution screenshots of:

- Main Research Gear menu
- Research Log list
- Research Log detail
- Calls list
- professor report
- Viridian Forest photo
- Mt. Moon photo
- Vermilion Harbor photo
- Route 9 photo
- Rock Tunnel photo
- Lavender / Misdreavus photo

Acceptance criteria:

- immediately recognizable as Pokémon-style UI
- readable on actual GBA resolution
- no text clipping
- no palette corruption
- photo scene is visually dominant
- environment is recognizable
- subject Pokémon are clearly visible
- navigation is obvious
- menus close cleanly
- overworld graphics restore correctly

==================================================
14. FIRST-CATCH POKÉDEX SCREEN STILL DISMISSES TOO QUICKLY
RELEASE BLOCKER
==================================================

Actual RG40XX H / VBA-Next reproduction:

The player caught a new Zubat.

The Pokédex new-entry screen appeared but exited too quickly before the player
could properly read the newly registered Pokémon information.

The previous mGBA software acceptance does not prove hardware acceptance.

Investigate the input lifecycle again.

Do NOT solve this with only an arbitrary long fixed delay.

Required behavior:

- species registers exactly once
- Pokédex entry completely initializes
- sprite/cry/info fully displays
- held input from capture cannot dismiss it
- rapid input during capture cannot dismiss it
- player gets time to actually see the entry
- dismissal requires a genuinely NEW press after the entry is ready
- nickname prompt happens only after intentional dismissal
- repeat catches still skip new-entry presentation normally
- no graphics corruption
- no black screen

Regression cases:

1. A held from ball animation
2. repeated/rapid A
3. A held through transition
4. B held through transition
5. no input
6. release buttons -> fresh A
7. release buttons -> fresh B
8. new species
9. already caught species
10. nickname Yes
11. nickname No
12. full party -> PC
13. save/cold Continue afterward

For exact-ROM manual testing, specifically confirm that a human observer can
leave the entry sitting onscreen and read it before pressing a fresh button.

==================================================
15. DO NOT REGRESS CUT
==================================================

The owner reports that Cut currently behaves correctly on RG40XX H.

Trees tested so far:
- disappear correctly
- do not immediately regrow
- player can walk through

Retain current Cut lifecycle behavior.

Run existing Cut regressions after Research Gear/photo changes, especially because
palette/follower/map refresh code may interact with field state.

==================================================
16. DO NOT REGRESS ZUBAT -> SKARMORY TRADE
==================================================

The owner successfully caught Zubat and completed the Route 2 Zubat -> Skarmory
trade on RG40XX H.

Preserve:

- Zubat requirement
- Skarmory receipt
- trade animation
- party identity
- OT/nickname behavior
- one-time receipt
- save persistence

==================================================
17. SAVE COMPATIBILITY REQUIREMENTS
==================================================

Must support all of:

A. Playtest 12 -> Playtest 13.1 migration

B. Playtest 13 RC1 -> Playtest 13.1 migration

C. New Game directly on Playtest 13.1

For existing PT13 saves:

Preserve:

- party
- boxes
- species
- IVs
- EVs
- nature
- abilities
- nicknames
- shiny state
- items
- money
- badges
- Pokédex
- Gear unlock
- Research Log
- photos
- professor delivered reports
- Flash
- Vs. Seeker
- ship departure
- Cut state/receipts
- Skarmory trade
- fossils
- rival/story progress

Migration remains idempotent.

Do not enlarge or reorder saved structures merely for UI changes.

==================================================
18. TESTING STRATEGY
==================================================

Use focused regression tests first.

Do NOT repeatedly run the entire upstream matrix after every text/UI edit.

Required focused suites should cover:

- Research photo palette restoration
- repeated photos same map
- Research Gear open/close
- call queue/delivery
- early Gear ownership
- migrated Gear catch-up
- Route 2 Flash handoff
- obsolete dialogue audit
- Pokédex fresh-input lifecycle
- Cut regression
- Skarmory trade regression
- save migration

Then run integration gates:

- all Three Horizons host tests
- all Three Horizons native tests
- save-layout checks
- Emerald compatibility build
- FireRed compatibility build
- LeafGreen compatibility build
- final exact ROM build

Use emulator visual evidence for presentation issues.

Do not claim RG40XX H acceptance from mGBA.

==================================================
19. RELEASE PACKAGE
==================================================

Package this as:

Playtest 13.1 / RC2

Suggested ROM name:

pokemon-three-horizons-playtest-13-1-road-to-lavender.gba

or another clearly versioned PT13 stabilization filename.

Do NOT overwrite the previous RC1 ROM/package.

Update:

PLAYTEST_13.md
PLAYTEST_13_VERIFICATION.md
PLAYTEST_13_EVOLUTION_QA.md only if evolution behavior changes
Research Gear documentation
save migration instructions
hardware acceptance checklist

Explicitly document:

- New Game Gear acquisition
- PT12 migrated Gear catch-up
- existing PT13 migration behavior
- professor call milestones
- Flash acquisition
- Research Photo UI changes
- first-catch Pokédex input behavior

==================================================
20. FINAL REPORT
==================================================

At completion report:

1. Exact feature revision
2. Exact compiled/test revision
3. ROM filename
4. ROM SHA-256
5. Automated test totals
6. Upstream compatibility results
7. PT12 -> PT13.1 migration result
8. PT13 RC1 -> PT13.1 migration result
9. New Game Research Gear acquisition flow
10. Migrated-save Research Gear acquisition flow
11. Exact professor call milestone sequence
12. Photo palette/black-screen regression evidence
13. Research Gear UI screenshots / visual acceptance summary
14. First-catch Pokédex fresh-input evidence
15. Cut regression result
16. Zubat -> Skarmory regression result
17. Remaining hardware-only items
18. Known limitations

==================================================
21. STOP CONDITIONS
==================================================

If implementation discovers a genuine architectural conflict involving:

- save compatibility
- Research Gear early acquisition
- Research Photo VRAM/palette limits
- environmental photo rendering
- call sequencing
- Pokédex lifecycle

STOP and present the measured technical conflict before silently weakening the
approved design.

Do not remove visual Research Photos and replace them with text-only entries.

Do not move Research Gear back to post-Surge without user approval.

Do not begin Playtest 14.

After packaging the Playtest 13.1 / RC2 stabilization candidate, STOP and wait
for the owner's RG40XX H hardware acceptance.