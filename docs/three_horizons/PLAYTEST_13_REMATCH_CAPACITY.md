# Playtest 13 rematch capacity decision

Status: approved by the user on 2026-09-29; all 121 ordinary trainers are implemented. Focused checks and final software integration pass on feature `24ef1cb7c5bfa264685032427181ce65ed9f889d`. The exact post-Surge personal battery also passes migration with unchanged save layout and defeat history. RG40XX H Playtest 13 hardware acceptance remains separate.

The existing save contains 100 one-byte `trainerRematches` entries. Its size and
offset must remain unchanged for Playtest 12 battery saves. A trainer ID must not
be truncated into one of these bytes.

## Audited scope

| Ordinary trainers | Count |
|---|---:|
| Already shipped Three Horizons maps | 68 |
| Route 11 native template | 10 |
| Route 9 native template | 9 |
| Route 10 native template | 6 |
| Rock Tunnel 1F native template | 7 |
| Rock Tunnel B1F native template | 8 |
| Tower 3F–6F native templates | 13 |
| Total planned ordinary trainers | **121** |

The shipped count starts with 72 distinct direct trainer scripts, excludes Brock,
Misty, Surge, the fossil researcher and the robbed-house story grunt, then adds
Luis, whose trainer battle is behind a wrapper script. Rival encounters, the
Nugget Bridge recruiter and the scripted Jessie/James scene are not ordinary
rematches. Ordinary Mt. Moon grunts and Tower Channelers are not excluded merely
because they belong to those classes. New-map counts must be checked against the
final authored maps during integration.

## Approved solution

Use the existing bytes only for temporary readiness on the currently loaded map.
Keep full-width trainer IDs and authored roster tiers in ROM data. Store readiness
values, never trainer IDs, in the save bytes. Resolve a checked map-local slot for
each eligible trainer, with explicit bounds checks and automated capacity checks
for every authored map. Clear temporary readiness on map exit, cancellation,
battle completion, blackout and cold Continue. Existing permanent defeated-trainer
flags remain authoritative and unchanged.

The native Vs. Seeker scan, response animation and battle lifecycle remain in use.
All hooks are confined to Three Horizons; upstream rematch tables and their
special-trainer boundaries remain unchanged. Native indoor restrictions require a
Three Horizons eligibility check so the approved ordinary cave and indoor trainers
are supported. Locations without an eligible target must return useful dialogue.

This supports every planned ordinary trainer without growing save blocks or
silently dropping trainers. It changes the plan's assumed one-global-slot-per-
trainer storage arrangement. The user explicitly approved this capacity decision.
Temporary readiness resets on Continue without erasing permanent defeat history.

## Implementation contract

The ROM registry stores `u16` trainer and map IDs plus the map object's local ID.
A readiness slot is `localId - 1`, only after verifying the ID is in 1–100 and
unique on that map. Duplicate trainer identities or duplicate local slots are
rejected. The save byte contains only 0 or 1. A RAM map identity prevents stale
bytes from resolving to a trainer on another map, in addition to explicit reset
hooks at map load and cold Continue.

All 68 shipped ordinary trainers are registered, including Luis's swimming script,
ordinary Mt. Moon grunts, Gym trainers, and ship cabin/deck trainers. The remaining
53 planned trainers are now also registered on their authored maps.
Bosses, scripted rivals, Jessie/James, the fossil researcher, the robbed-house
grunt, and the Nugget Bridge recruiter remain excluded.

The native scan and response emote are retained. Three Horizons resumes authored
idle movement afterwards, without persisting rematch-only NPC coordinates or
movement into a battery save. A new scan replaces readiness immediately; there
is no charge or five-badge check. Caves and buildings support eligible trainers.
An empty scan uses the native no-trainers message.

Balance: strongest team member targets highest non-Egg party level minus ten,
with the original strongest level as the floor. Badge caps are 24 before Surge,
35 with three badges, then 45/55/65/75/100. A cap cannot be below the original
floor. Other members preserve their original level offsets, minimum level one.
Evolution improvements use explicit ROM-authored species tiers, never arbitrary
branch selection. First fights continue to use their original records; Keigo's
separately approved first-fight roster is Kakuna/Beedrill/Butterfree at level 18.

The user's actual post-Surge RG40XX H VBA-Next battery,
`pokemon-three-horizons-playtest-12-rocket-art.gba.eps`, passed first migration,
ordinary Save and second cold Continue on the final integration candidate.
Readiness reset safely and permanent defeat history remained unchanged. The
older Cerulean/Playtest-11-marked backups are superseded for personal acceptance.

## Focused acceptance

Nine native groups and four host checks pass for the 68 shipped trainers,
including full-width IDs, collisions/bounds, stale-map isolation, level clamps,
first-battle preservation, defeat flags, unchanged save sizes and legal parties.
Exact-ROM mGBA checks also cover rematch win/loss, immediate reuse, map change,
cold Continue, indoor/cave/ship readiness, Luis's clear postbattle path, and
boss/unseen exclusions. See PLAYTEST_13_VERIFICATION.md for revisions and limits.
The remaining 53 trainers have been added with their maps; Task40's nine native
rematch groups pass with all 121 records. Integration at feature `24ef1cb7`
passed the full 155 host contracts, 212 Three Horizons native tests, all four
save-layout checks, and upstream Emerald/FireRed/LeafGreen builds and native
tests. Ten synthetic battery cases also confirmed readiness is cleared without
altering old trainer defeat history. Exact personal post-Surge migration also
passed; the complete chapter routes remain pending. See PLAYTEST_13_VERIFICATION.md
for source/ROM hashes, protected comparisons and the separate hardware gate.


## Route 11 addition (Task 33)

Ten native Route 11 ordinary trainers use new full-width ROM IDs 104–113 and local readiness slots 0–9. The roster now contains 78 ordinary trainers; 43 approved trainers remain for Route 9, Route 10, Rock Tunnel and Pokémon Tower. Existing ship-rival IDs 94–102 and Surge ID 103 remain unchanged and excluded. A cross-table uniqueness check verifies both TH and upstream configurations; no saved trainer IDs or save structures were resized. Final 121-trainer coverage remains an integration gate.

## PT14 addendum — exact candidate, 2026-10-02

Feature and compiled/test revision: `abdec6f2508bbf2d4f1c104d863e5908281f6f6e`.

ROM: `pokemon-three-horizons-playtest-14-celadon-silph-scope.gba`

SHA-256: `7e9e18bcb30026a47c9e46e187f8a1ba906e431682eb704b48c2ed8fd67a77a7`.

This candidate passed the recorded automated and mGBA checks. RG40XX H/VBA-Next acceptance remains **PENDING**; the intermittent full-party Ekans capture report is **HIGH / unresolved**. Use normal speed first.

The map-local readiness architecture is preserved: full-width trainer IDs and
authored parties/tiers remain in ROM; existing byte slots carry only bounded
transient readiness. No save growth, ID truncation or map-local aliasing.
Permanent first-defeat flags remain authoritative. Map exit/change, cancellation,
completed rematch, blackout and cold Continue clear readiness without erasing
trainer/story history. Repeated immediate use needs no charge. Bosses, Leaders,
scripted rivals, Jessie/James, poster guard and upper Tower Rockets are excluded.

PT14 adds30 ordinary trainer identities (12 Route8,7 Gym,11 Hideout) to the121
existing entries. Route8 twins share one canonical slot; either actor routes to
the same identity, with a safe insufficient-party guard. First battle parties
are unchanged. Scaling remains clamped and lower/higher levels tested. Losing
or cancelling must not fabricate a first victory. Before a rematch, trainers
use their rematch greeting; undefeated trainers still use the first-battle path.

All25 stone overrides below are generated from the tested chapter14_content.json
manifest. Both level **and** badge thresholds must be met for the exact trainer,
party slot and base species. They are trainer-only; player evolution methods
remain unchanged. Source slots are zero-based; this table adds1 for readability.

| Trainer constant | Party slot (1-based) | Base → rematch species | Minimum individual level | Minimum badges |
|---|---:|---|---:|---:|
| TRAINER_TH9_LASS_ROBIN | 1 | Jigglypuff → Wigglytuff | 30 | 3 |
| TRAINER_TH9_LASS_IRIS | 1 | Clefairy → Clefable | 30 | 3 |
| TRAINER_TH12_PICNICKER_NANCY | 2 | Pikachu → Raichu | 30 | 3 |
| TRAINER_TH12_GENTLEMAN_THOMAS | 1 | Growlithe → Arcanine | 32 | 4 |
| TRAINER_TH12_GENTLEMAN_THOMAS | 2 | Growlithe → Arcanine | 32 | 4 |
| TRAINER_TH12_GENTLEMAN_BROOKS | 1 | Pikachu → Raichu | 30 | 3 |
| TRAINER_TH12_GENTLEMAN_LAMAR | 1 | Growlithe → Arcanine | 32 | 4 |
| TRAINER_TH12_LASS_DAWN | 2 | Pikachu → Raichu | 30 | 3 |
| TRAINER_TH12_SAILOR_DWAYNE | 1 | Pikachu → Raichu | 30 | 3 |
| TRAINER_TH12_SAILOR_DWAYNE | 2 | Pikachu → Raichu | 30 | 3 |
| TRAINER_TH12_GENTLEMAN_TUCKER | 1 | Pikachu → Raichu | 30 | 3 |
| TRAINER_TH13_ROUTE11_DARIAN | 1 | Growlithe → Arcanine | 32 | 4 |
| TRAINER_TH13_ROUTE11_DARIAN | 2 | Vulpix → Ninetales | 32 | 4 |
| TRAINER_TH13_ROUTE9_CHRIS | 1 | Growlithe → Arcanine | 32 | 4 |
| TRAINER_TH13_ROUTE10_HEIDI | 1 | Pikachu → Raichu | 30 | 3 |
| TRAINER_TH13_ROUTE10_HEIDI | 2 | Clefairy → Clefable | 30 | 3 |
| TRAINER_TH13_ROCKTUNNEL_1F_LEAH | 2 | Clefairy → Clefable | 30 | 3 |
| TRAINER_TH13_ROCKTUNNEL_B1F_SOFIA | 1 | Jigglypuff → Wigglytuff | 30 | 3 |
| TRAINER_TH14_ROUTE8_JULIA | 1 | Clefairy → Clefable | 30 | 3 |
| TRAINER_TH14_ROUTE8_JULIA | 2 | Clefairy → Clefable | 30 | 3 |
| TRAINER_TH14_ROUTE8_RICH | 1 | Growlithe → Arcanine | 32 | 4 |
| TRAINER_TH14_ROUTE8_RICH | 2 | Vulpix → Ninetales | 32 | 4 |
| TRAINER_TH14_ROUTE8_MEGAN | 5 | Pikachu → Raichu | 30 | 3 |
| TRAINER_TH14_ROUTE8_ELI_ANNE | 1 | Clefairy → Clefable | 30 | 3 |
| TRAINER_TH14_ROUTE8_ELI_ANNE | 2 | Jigglypuff → Wigglytuff | 30 | 3 |

Native tests prove all25 mappings, threshold negatives, low/high scaling,
first-party preservation, defeat-history stability, map-change cleanup and
upstream fallback. The exact-owner route and labelled twin/rematch tests have
separate evidence in PLAYTEST_14_VERIFICATION.md. New-game and copied-battery
routes use the same architecture; cold Continue intentionally clears readiness.
Ship rematch entries remain authored, but ship departure restricts later access.
