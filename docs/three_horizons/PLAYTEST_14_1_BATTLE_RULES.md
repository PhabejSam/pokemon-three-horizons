# Three Horizons battle rules — Playtest 14.1

These rules apply to Three Horizons. Upstream Emerald, FireRed and LeafGreen retain their configured mechanics.

## Hyper Beam

Hyper Beam remains Normal type, 150 power, 90 accuracy and 5 PP. Its existing target, animation, sound, contest data and recharge effect are retained.

At use, the game compares the user's current Attack and Sp. Atk after stat stages. Higher Attack selects Physical damage against Defense. Equal or higher Sp. Atk selects Special damage against Sp. Defense. Boosts and reductions can therefore change the selected category. Later damage modifiers keep their normal engine behavior; they do not redefine this comparison.

The move summary retains its base Special category icon, as with the existing dynamic-category architecture. The description explains the adaptive rule. Actual battle and AI damage use the selected category.

Gyarados remains Water/Dragon with its existing base stats. No awakened form or later story content is added.

## Recharge after a knockout

Standard self-recharge attacks skip recharge when their target is knocked out. If the target survives, the user must recharge for one turn. Breaking a Substitute is not a knockout. Misses, immunity and protection keep the existing engine behavior.

This includes Hyper Beam, Giga Impact, Blast Burn, Hydro Cannon, Frenzy Plant, Rock Wrecker, Roar of Time, Prismatic Laser, Meteor Assault and Eternabeam. Inclusion in this rule does not make a move newly obtainable in the current chapter.

Solar Beam, Fly, Dig, Skull Bash, Razor Wind and Sky Attack retain their separate charge-then-attack behavior.

## AI

The AI evaluates Hyper Beam with the same staged-stat category and target defense used for actual damage. Its existing one-hit-KO estimate can remove a recharge drawback when neither a Substitute nor an endurance effect invalidates that estimate. This remains an estimate, not a guarantee: accuracy, damage variation and later battle choices still matter. No new prediction engine or persistent state is introduced.

## Handheld acceptance

Automated and desktop emulator evidence are recorded in [verification](PLAYTEST_14_VERIFICATION.md). RG40XX H/VBA-Next acceptance remains pending. The separate intermittent full-party Ekans capture report remains HIGH / unresolved.
