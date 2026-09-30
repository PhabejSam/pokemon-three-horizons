# Playtest 8 verification notes

The user authorized the playtest fixes and explicitly selected evolution
during battle. Work continued inline in the existing feature/opening-demo
checkout. No save structure or existing map index changed.

## Implementation

- Regional displays remain after both starter choices. The stage check still
  prevents another starter grant. Follower refresh runs after Oak's handoff,
  including the retry path when the player's Bag was full.
- Oak, Elm and Birch stand together. Moving Birch opened an eighth approach
  tile; the new Oak approach/return path is included in collision checks.
- Centers run the native healing field effect with the FRLG machine graphics.
  Their indoor map-name popups are disabled. NPCs, lab objects and trainers
  now have individual conversation labels and text.
- Reusable TMs and the native Gen6 party EXP. SHARE are enabled only for
  Three Horizons. Persistent Emerald flag 0x21 was audited as unused. Old
  kit masks of 127 receive only the new eighth item and become 255.
- Evolution pauses the experience command after level-up/move learning,
  suspends the battle's first callback, runs the native evolution scene,
  then rebuilds the battle screen before resuming. B cancellation and
  Everstone are honored. Reserve Pokémon use the same flow. Temporary
  types, abilities, Mimic/Transform, PP, Power Trick and consumed held items
  are preserved or updated as appropriate. No link/frontier/partner battle
  evolution is enabled by this change.

## Review and repairs

An independent whole-change review found that the battle's first callback
would continue running during evolution. It is now suspended through the
scene and graphics rebuild. Follow-up review findings about temporary moves,
type/ability changes and consumed held-item restoration were also repaired.
The native evolution scene queues map music, so that queue is reset before
restoring battle music.

The ARM test compile caught an assertion macro applied directly to a bit
field; the test now casts the value. Compatibility builds caught the
Emerald-only EXP. SHARE flag name in other build modes; preprocessing now
isolates that setting to Three Horizons.

## Scope of verification

- 23 host map/scene checks passed, including all eight Oak handoff routes.
- The native evolution test drives actual scene callbacks and frame updates
  for confirm/cancel with active/reserve Pokémon. It checks evolved species,
  callback restoration, cleared repeat-prompt bit and map-music cleanup.
- Additional engine tests check Everstone, level eligibility, temporary
  effects, evolution-item consumption, old-save kit delivery and native
  reusable-TM/Key-Item properties.
- Compiled-ROM inspection, source revision, final test totals, checksum and
  workflow links are recorded in the packaged BUILD_REPORT.md.
- Standard Emerald, FireRed, LeafGreen, release and documentation checks
  passed for source 11a72349db9120076bd6ab5c840cf7113edfe449. The broader
  upstream test job is tracked separately from those compatibility builds.

## Remaining manual coverage and artwork

No manual emulator playthrough was performed. Check the complete transition
from an earned level through evolution to the next opponent, move learning,
HP/status/PP, EXP. SHARE on/off behavior and save/reload. Also check first
follower timing, healing-ball alignment/count, blackout fading and object
dialogue visually. See PLAYTEST_8.md for the player-facing checklist.

The image service rejected the requested mountain/professor/nine-starter
cover generation. It was not retried or bypassed. Illustrated intro portraits
and the new cover remain unfinished. Existing pixel professors are closer
together, and the title's Rayquaza layer is hidden; these are the only art
presentation changes claimed for this playtest.

The playable route still ends after Brock. Route 3, Mt. Moon and
Cerulean/Misty are the next proposed content milestone after this polish
passes beta testing. Existing ROMs and saves remain separate and unchanged.

## Final result

Source `11a72349db9120076bd6ab5c840cf7113edfe449` passed
[the demo workflow](https://github.com/PhabejSam/pokemon-three-horizons/actions/runs/35964804288):
45 Three Horizons engine tests, four save tests, all five deliberate-defect
negative controls and restored positive checks. The separate package's ROM
hash matches the downloaded build:
`e58d54081de7480fccc0987496d0268965990d6506db95a0ca6817f8d1df0560`.
Compiled checks confirm dialogue widths, palette tags, Brock's four-member
party and all 112 running-frame reads. The package includes the ROM, guide,
build report, changed-file list, credits and original verification logs.
