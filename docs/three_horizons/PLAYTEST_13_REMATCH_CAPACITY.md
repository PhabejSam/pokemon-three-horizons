# Playtest 13 rematch capacity decision

Status: approved by the user on 2026-09-29; all 121 ordinary trainers are implemented. Focused checks pass; final integration and hardware acceptance are tracked separately.

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

The user's exact post-Surge RG40XX H Playtest 12 battery save remains required
for the final personal-save acceptance gate. The older Cerulean/Playtest-11-marked
save is not evidence of that acceptance.

## Focused acceptance

Nine native groups and four host checks pass for the 68 shipped trainers,
including full-width IDs, collisions/bounds, stale-map isolation, level clamps,
first-battle preservation, defeat flags, unchanged save sizes and legal parties.
Exact-ROM mGBA checks also cover rematch win/loss, immediate reuse, map change,
cold Continue, indoor/cave/ship readiness, Luis's clear postbattle path, and
boss/unseen exclusions. See PLAYTEST_13_VERIFICATION.md for revisions and limits.
The remaining 53 trainers have been added with their maps; Task40's nine native
rematch groups pass with all 121 records. The final coverage audit and non-TH
runtime controls remain integration requirements.


## Route 11 addition (Task 33)

Ten native Route 11 ordinary trainers use new full-width ROM IDs 104–113 and local readiness slots 0–9. The roster now contains 78 ordinary trainers; 43 approved trainers remain for Route 9, Route 10, Rock Tunnel and Pokémon Tower. Existing ship-rival IDs 94–102 and Surge ID 103 remain unchanged and excluded. A cross-table uniqueness check verifies both TH and upstream configurations; no saved trainer IDs or save structures were resized. Final 121-trainer coverage remains an integration gate.
