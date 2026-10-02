# Playtest 14 encounter checklist

Source revision: `abdec6f2508bbf2d4f1c104d863e5908281f6f6e`.

ROM SHA-256: `7e9e18bcb30026a47c9e46e187f8a1ba906e431682eb704b48c2ed8fd67a77a7`. mGBA exact-candidate checks passed; RG40XX H/VBA-Next remains pending. New-game and copied-battery continuation use the same tables; labelled forced cases do not establish natural encounter probabilities.

Rates below are shares of encounters, not chances per step. Repels, lead abilities and time settings can affect encounters. Wild starters have ordinary random stats and the same Hidden Ability rules as other wild Pokémon.

Grass/cave encounters and the Old Rod are available in this chapter. Surf, Rock Smash, Good Rod and Super Rod tables are listed as future access only. Visible research-scene Pokémon do not trigger captures.

## How to test encounters

Use a fresh game or ordinary battery Continue in this exact build. Record the area, method, day/night setting, lead level/ability, Repel state and number of encounters. For a practical first pass, sample 30 encounters per available table and log species and levels; stop there and report the sample even if a rare species never appears. A finite sample does not guarantee a rare encounter. Do not use encounter cheats for this check.

A 5% entry is rare, not a promise of one encounter in every 20. Wild Hidden Abilities have a 10% roll when the species has one; ordinary abilities share the other 90%. A small sample cannot verify those percentages.

Tower checks: compare an ordinary encounter before and after receiving the SILPH SCOPE. Before the Scope, the wild ghost is unidentified and cannot be caught. After the Scope, the normal wild species can be caught. The scripted mother spirit is a separate, non-catchable story encounter. Follow the release verification for which progression gates have been accepted.

Regional highlights in the extension include Phanpy/Whismur in Digletts Cave, Mareep on Route 9, and Aron/Dunsparce in Rock Tunnel. Research scenes and photographs are authored observations, not additional wild encounter slots. Consult the tables for exact weights and levels.

## Route 24 — all times — grass / cave

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Oddish | 25% | 12, 13, 14 | |
| Caterpie | 20% | 7 | |
| Weedle | 20% | 7 | |
| Abra | 15% | 8, 10, 12 | |
| Pidgey | 10% | 11 | |
| Totodile | 5% | 10 | |
| Kakuna | 4% | 8 | |
| Metapod | 1% | 8 | |

## Route 24 — all times — Surf — future access

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Tentacool | 100% | 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40 | |

## Route 24 — all times — Old Rod

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Magikarp | 100% | 5 | |

## Route 24 — all times — Good Rod — future access

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Horsea | 60% | 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 | |
| Krabby | 20% | 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 | |
| Magikarp | 20% | 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 | |

## Route 24 — all times — Super Rod — future access

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Horsea | 84% | 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35 | |
| Gyarados | 15% | 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25 | |
| Psyduck | 1% | 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35 | |

## Route 25 — all times — grass / cave

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Oddish | 25% | 12, 13, 14 | |
| Caterpie | 20% | 8 | |
| Weedle | 20% | 8 | |
| Abra | 15% | 9, 11, 13 | |
| Pidgey | 10% | 13 | |
| Squirtle | 5% | 10 | |
| Kakuna | 4% | 9 | |
| Metapod | 1% | 9 | |

## Route 25 — all times — Surf — future access

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Psyduck | 100% | 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40 | |

## Route 25 — all times — Old Rod

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Magikarp | 100% | 5 | |

## Route 25 — all times — Good Rod — future access

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Poliwag | 60% | 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 | |
| Goldeen | 20% | 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 | |
| Magikarp | 20% | 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 | |

## Route 25 — all times — Super Rod — future access

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Poliwag | 40% | 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25 | |
| Poliwhirl | 40% | 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 | |
| Gyarados | 15% | 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25 | |
| Psyduck | 5% | 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35 | |

## Route 5 — all times — grass / cave

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Pidgey | 40% | 13, 15, 16 | |
| Meowth | 35% | 10, 12, 14, 16 | |
| Oddish | 15% | 13, 16 | |
| Bellsprout | 10% | 15 | |

## Route 6 — all times — grass / cave

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Pidgey | 40% | 13, 15, 16 | |
| Meowth | 35% | 10, 12, 14, 16 | |
| Oddish | 15% | 13, 16 | |
| Bellsprout | 10% | 15 | |

## Route 6 — all times — Surf — future access

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Psyduck | 100% | 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40 | |

## Route 6 — all times — Old Rod

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Magikarp | 100% | 5 | |

## Route 6 — all times — Good Rod — future access

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Poliwag | 60% | 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 | |
| Goldeen | 20% | 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 | |
| Magikarp | 20% | 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 | |

## Route 6 — all times — Super Rod — future access

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Poliwag | 40% | 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25 | |
| Poliwhirl | 40% | 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 | |
| Gyarados | 15% | 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25 | |
| Psyduck | 5% | 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35 | |

## Vermilion City — all times — Surf — future access

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Tentacool | 100% | 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40 | |

## Vermilion City — all times — Old Rod

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Magikarp | 100% | 5 | |

## Vermilion City — all times — Good Rod — future access

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Horsea | 60% | 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 | |
| Krabby | 20% | 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 | |
| Magikarp | 20% | 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 | |

## Vermilion City — all times — Super Rod — future access

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Horsea | 44% | 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35 | |
| Shellder | 40% | 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25 | |
| Gyarados | 15% | 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25 | |
| Psyduck | 1% | 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35 | |

## Digletts Cave B1F — all times — grass / cave

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Diglett | 70% | 15, 16, 17, 18, 19, 20, 21, 22 | |
| Dugtrio | 10% | 29, 30, 31 | |
| Phanpy | 10% | 17, 18, 19, 20 | |
| Whismur | 10% | 17, 18, 19, 20 | |

## Pokemon Tower 3F — all times — grass / cave

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Gastly | 90% | 13, 14, 15, 16, 17, 18, 19 | |
| Cubone | 9% | 15, 17 | |
| Haunter | 1% | 20 | |

## Pokemon Tower 4F — all times — grass / cave

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Gastly | 86% | 13, 14, 15, 16, 17, 18, 19 | |
| Cubone | 9% | 15, 17 | |
| Haunter | 5% | 20 | |

## Pokemon Tower 5F — all times — grass / cave

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Gastly | 86% | 13, 14, 15, 16, 17, 18, 19 | |
| Cubone | 9% | 15, 17 | |
| Haunter | 5% | 20 | |

## Pokemon Tower 6F — all times — grass / cave

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Gastly | 85% | 14, 15, 16, 17, 18, 19 | |
| Cubone | 9% | 17, 19 | |
| Haunter | 6% | 21, 23 | |

## Rock Tunnel 1F — all times — grass / cave

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Geodude | 35% | 15, 16, 17 | |
| Zubat | 30% | 15, 16 | |
| Machop | 10% | 16 | |
| Mankey | 10% | 16 | |
| Aron | 5% | 17 | |
| Dunsparce | 5% | 17 | |
| Onix | 5% | 13, 15 | |

## Rock Tunnel B1F — all times — grass / cave

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Geodude | 35% | 15, 16, 17 | |
| Zubat | 30% | 15, 16 | |
| Machop | 10% | 17 | |
| Mankey | 10% | 17 | |
| Aron | 5% | 16 | |
| Dunsparce | 5% | 13 | |
| Onix | 5% | 15, 17 | |

## Rock Tunnel B1F — all times — Rock Smash — future access

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Geodude | 95% | 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 | |
| Graveler | 5% | 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40 | |

## Route 10 — all times — grass / cave

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Voltorb | 40% | 14, 16, 17 | |
| Spearow | 35% | 13, 16, 17 | |
| Ekans | 25% | 11, 13, 15, 17 | |

## Route 10 — all times — Surf — future access

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Tentacool | 100% | 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40 | |

## Route 10 — all times — Old Rod

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Magikarp | 100% | 5 | |

## Route 10 — all times — Good Rod — future access

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Horsea | 60% | 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 | |
| Krabby | 20% | 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 | |
| Magikarp | 20% | 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 | |

## Route 10 — all times — Super Rod — future access

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Horsea | 84% | 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35 | |
| Gyarados | 15% | 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25 | |
| Psyduck | 1% | 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35 | |

## Route 11 — all times — grass / cave

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Ekans | 40% | 12, 14, 15 | |
| Spearow | 35% | 13, 15, 17 | |
| Drowzee | 25% | 11, 13, 15 | |

## Route 11 — all times — Surf — future access

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Tentacool | 100% | 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40 | |

## Route 11 — all times — Old Rod

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Magikarp | 100% | 5 | |

## Route 11 — all times — Good Rod — future access

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Horsea | 60% | 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 | |
| Krabby | 20% | 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 | |
| Magikarp | 20% | 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 | |

## Route 11 — all times — Super Rod — future access

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Horsea | 84% | 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35 | |
| Gyarados | 15% | 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25 | |
| Psyduck | 1% | 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35 | |

## Route 9 — all times — grass / cave

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Rattata | 40% | 14, 16, 17 | |
| Spearow | 30% | 13, 16 | |
| Ekans | 25% | 11, 13, 15, 17 | |
| Mareep | 5% | 14, 15, 16, 17 | |

## Route 7 — all times — grass / cave

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Meowth | 30% | 17, 18 | |
| Pidgey | 30% | 19, 22 | |
| Bellsprout | 14% | 19, 22 | |
| Oddish | 14% | 19, 22 | |
| Growlithe | 6% | 18, 20 | |
| Vulpix | 6% | 18, 20 | |

## Route 8 — all times — grass / cave

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Meowth | 30% | 18, 20 | |
| Pidgey | 30% | 18, 20 | |
| Growlithe | 14% | 16, 17 | |
| Vulpix | 14% | 16, 17 | |
| Ekans | 6% | 17, 19 | |
| Sandshrew | 6% | 17, 19 | |

## Mt Moon 1F — all times — grass / cave

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Zubat | 69% | 7, 8, 9, 10 | |
| Geodude | 20% | 7, 8 | |
| Cyndaquil | 5% | 9 | |
| Paras | 5% | 8 | |
| Makuhita | 1% | 9, 10, 11 | |

## Mt Moon B1F — all times — grass / cave

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Paras | 99% | 5, 6, 7, 8, 9, 10 | |
| Makuhita | 1% | 9, 10, 11 | |

## Mt Moon B2F — all times — grass / cave

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Zubat | 49% | 8, 9, 10, 11 | |
| Geodude | 30% | 9, 10 | |
| Paras | 15% | 10, 12 | |
| Clefairy | 5% | 10 | |
| Makuhita | 1% | 9, 10, 11 | |

## Route 1 — all times — grass / cave

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Pidgey | 50% | 2, 3, 4 | |
| Rattata | 50% | 2, 3, 4 | |

## Route 2 — all times — grass / cave

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Pidgey | 45% | 2, 3, 4, 5 | |
| Rattata | 40% | 2, 3, 4 | |
| Bulbasaur | 5% | 5 | |
| Caterpie | 5% | 4, 5 | |
| Weedle | 5% | 4, 5 | |

## Route 22 — all times — grass / cave

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Spearow | 31% | 3, 4, 5 | |
| Rattata | 20% | 3, 4, 5 | |
| Mankey | 14% | 3, 4, 5 | |
| Nidoran F | 14% | 3, 4, 5 | |
| Nidoran M | 10% | 3, 4, 5 | |
| Meowth | 6% | 3, 4, 5 | |
| Mudkip | 5% | 5 | |

## Route 22 — all times — Surf — future access

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Psyduck | 100% | 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40 | |

## Route 22 — all times — Old Rod

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Magikarp | 100% | 5 | |

## Route 22 — all times — Good Rod — future access

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Poliwag | 60% | 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 | |
| Goldeen | 20% | 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 | |
| Magikarp | 20% | 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 | |

## Route 22 — all times — Super Rod — future access

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Poliwag | 40% | 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25 | |
| Poliwhirl | 40% | 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 | |
| Gyarados | 15% | 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25 | |
| Psyduck | 5% | 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35 | |

## Route 3 — all times — grass / cave

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Spearow | 31% | 6, 7, 8 | |
| Pidgey | 30% | 6, 7 | |
| Nidoran M | 14% | 6, 7 | |
| Mankey | 10% | 7 | |
| Jigglypuff | 9% | 3, 5 | |
| Charmander | 5% | 8 | |
| Nidoran F | 1% | 6 | |

## Route 4 — all times — grass / cave

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Rattata | 35% | 8, 10, 12 | |
| Spearow | 30% | 8, 10 | |
| Ekans | 25% | 6, 8, 10, 12 | |
| Mankey | 5% | 10, 12 | |
| Torchic | 5% | 8 | |

## Route 4 — all times — Surf — future access

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Tentacool | 100% | 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40 | |

## Route 4 — all times — Old Rod

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Magikarp | 100% | 5 | |

## Route 4 — all times — Good Rod — future access

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Horsea | 60% | 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 | |
| Krabby | 20% | 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 | |
| Magikarp | 20% | 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 | |

## Route 4 — all times — Super Rod — future access

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Horsea | 84% | 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35 | |
| Gyarados | 15% | 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25 | |
| Psyduck | 1% | 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35 | |

## Viridian Forest — day / fallback — grass / cave

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Caterpie | 30% | 4, 5 | |
| Weedle | 30% | 4, 5 | |
| Kakuna | 15% | 5, 6 | |
| Metapod | 10% | 5 | |
| Chikorita | 5% | 5 | |
| Pikachu | 5% | 3, 5 | |
| Treecko | 5% | 7 | |

## Viridian Forest — night — grass / cave

| Pokémon | Rate | Levels | Seen / caught |
|---|---:|---|---|
| Caterpie | 30% | 4, 5 | |
| Weedle | 30% | 4, 5 | |
| Kakuna | 10% | 5 | |
| Spinarak | 10% | 5 | |
| Chikorita | 5% | 5 | |
| Hoothoot | 5% | 5, 6 | |
| Pikachu | 5% | 3, 5 | |
| Treecko | 5% | 7 | |

## Gift and prize encounters

Game Corner prizes (Coin Case in Bag): Abra Lv9/180 coins; Clefairy Lv8/500;
Dratini Lv18/2,800; Scyther Lv25/5,500; Porygon Lv26/9,999. They are ordinary
repeatable gifts, with party/PC capacity checks. Mansion roof-room Eevee is Lv25
and once-only. Snorlax on the bounded Route12 landing is Lv30 and resolves only
on capture/victory. The Lv30 mother Marowak is a separate non-catchable spirit.

Abra also has Route24/25 access and Clefairy Mt. Moon B2F. Later non-Game-Corner
sources for Dratini/Scyther/Porygon and an alternate Snorlax opportunity remain
obligations, not implemented future locations. All25 authored trainer stone
overrides and their thresholds are in PLAYTEST_13_REMATCH_CAPACITY.md's PT14
addendum; they do not alter player evolution methods.
