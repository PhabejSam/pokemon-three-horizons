# Playtest 13 rematch capacity decision

Status: awaiting the user's decision required by implementation-plan conflict 3.

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

## Recommended solution

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
trainer storage arrangement, so implementation of this part is waiting for the
explicit capacity decision. Keigo's approved first-fight roster and pure level
tuning do not depend on this storage choice.
