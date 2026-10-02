# Playtest 14 — all active TM availability

Feature and compiled/test revision: `abdec6f2508bbf2d4f1c104d863e5908281f6f6e`.

ROM: `pokemon-three-horizons-playtest-14-celadon-silph-scope.gba`

SHA-256: `7e9e18bcb30026a47c9e46e187f8a1ba906e431682eb704b48c2ed8fd67a77a7`.

This candidate passed the recorded automated and mGBA checks. RG40XX H/VBA-Next acceptance remains **PENDING**; the intermittent full-party Ekans capture report is **HIGH / unresolved**. Use normal speed first.

All50 active TMs are listed below: **26 obtainable,24 unavailable** through
currently authored chapters. TM51–100 placeholders are excluded. All TMs are
reusable. Prices are money unless marked coins. Store means Celadon Department
Store; prizes require Coin Case in the Bag. A future source is not an invitation
to enter donor maps or add content.

| TM | Active move | Current availability / requirement |
|---|---|---|
| 01 | Focus Punch | Unavailable in PT14; future source unimplemented |
| 02 | Dragon Claw | Unavailable in PT14; future source unimplemented |
| 03 | Water Pulse | Misty victory; retry failed delivery |
| 04 | Calm Mind | Unavailable in PT14; future source unimplemented |
| 05 | Roar | Route4 ball (67,5); Store2F, at least3 badges, 1,000 |
| 06 | Toxic | Unavailable in PT14; future source unimplemented |
| 07 | Hail | Unavailable in PT14; future source unimplemented |
| 08 | Bulk Up | Unavailable in PT14; future source unimplemented |
| 09 | Bullet Seed | Mt. Moon1F ball (11,35) |
| 10 | Hidden Power | Unavailable in PT14; future source unimplemented |
| 11 | Sunny Day | Unavailable in PT14; future source unimplemented |
| 12 | Taunt | Hideout B2F ball (5,7) |
| 13 | Ice Beam | Prize Corner, 4,000 coins |
| 14 | Blizzard | Unavailable in PT14; future source unimplemented |
| 15 | Hyper Beam | Store2F, at least4 badges, 7,500 |
| 16 | Light Screen | Store roof girl, one Fresh Water |
| 17 | Protect | Store2F, at least4 badges, 3,000 |
| 18 | Rain Dance | Unavailable in PT14; future source unimplemented |
| 19 | Giga Drain | Erika victory; separate retryable TM receipt |
| 20 | Safeguard | Store roof girl, one Soda Pop |
| 21 | Frustration | Hideout B3F ball (19,14) |
| 22 | Solar Beam | Unavailable in PT14; future source unimplemented |
| 23 | Iron Tail | Prize Corner, 3,500 coins |
| 24 | Thunderbolt | Prize Corner, 4,000 coins |
| 25 | Thunder | Unavailable in PT14; future source unimplemented |
| 26 | Earthquake | Unavailable in PT14; future source unimplemented |
| 27 | Return | Unavailable in PT14; future source unimplemented |
| 28 | Dig | Cerulean Rocket victory; Store2F, at least3 badges, 2,000 |
| 29 | Psychic | Unavailable in PT14; future source unimplemented |
| 30 | Shadow Ball | Prize Corner, 4,500 coins |
| 31 | Brick Break | S.S. Anne1F Room2 ball (5,7), before departure; Store2F, at least3 badges, 3,000 |
| 32 | Double Team | Unavailable in PT14; future source unimplemented |
| 33 | Reflect | Store roof girl, one Lemonade |
| 34 | Shock Wave | Lt. Surge victory; retry failed delivery |
| 35 | Flamethrower | Prize Corner, 4,000 coins |
| 36 | Sludge Bomb | Unavailable in PT14; future source unimplemented |
| 37 | Sandstorm | Unavailable in PT14; future source unimplemented |
| 38 | Fire Blast | Unavailable in PT14; future source unimplemented |
| 39 | Rock Tomb | Brock victory; retry failed delivery |
| 40 | Aerial Ace | Route9 ball (12,17) |
| 41 | Torment | Unavailable in PT14; future source unimplemented |
| 42 | Facade | Unavailable in PT14; future source unimplemented |
| 43 | Secret Power | Route25 ball (26,2); Store2F, at least3 badges, 3,000 |
| 44 | Rest | S.S. Anne B1F Room2 ball (3,2), before departure; Store2F, at least4 badges, 3,000 |
| 45 | Attract | Route24 ball (11,4); Store2F, at least3 badges, 3,000 |
| 46 | Thief | Mt. Moon B2F ball (35,5) |
| 47 | Steel Wing | Unavailable in PT14; future source unimplemented |
| 48 | Skill Swap | Unavailable in PT14; future source unimplemented |
| 49 | Snatch | Hideout B4F ball (1,6) |
| 50 | Overheat | Unavailable in PT14; future source unimplemented |

Store and prize TMs reject duplicates already in Bag **or PC**. Three-badge stock
has five TMs; four-badge stock adds three. No Scope/Giovanni gate, and more than
four badges adds no future stock. Roof drinks cost Fresh Water200, Soda Pop300,
Lemonade400; failed delivery or an already-owned TM consumes no drink. Erika's
badge remains earned if TM delivery needs retry. Earlier ship pickups can be
missed after departure; Store alternatives cover TM31 and TM44.

Free repeat Counter tutoring is on Store3F. The city's Soft-Boiled tutor retains
its native water-access footprint; no new Surf access is granted. These tutors
are not extra TMs. Existing Repel and training-shop prices remain unchanged.

Pokémon prizes: Abra9/180 coins, Clefairy8/500, Dratini18/2,800,
Scyther25/5,500, Porygon26/9,999. They are optional repeatable ordinary gifts with
capacity checks. Dratini/Scyther/Porygon later non-Game-Corner sources remain
explicit unimplemented obligations. Abra and Clefairy have existing alternatives.

Source audit: active identities in include/constants/tms_hms.h; tested economy
manifest tools/three_horizons/chapter14_content.json and ROM tables
src/data/three_horizons_celadon.h; earlier sources in journey.inc,
chapter9.inc/chapter9_locals.inc, chapter12_bill_trainers.inc/chapter12_locals.inc/
chapter12_gym.inc, chapter13_routes.inc; new rewards in chapter14_gym.inc and
chapter14_hideout.inc. Native Pickup contains no TM source. The final content
validator checks all50 active identities. Exact-candidate purchase, prize,
full-pocket retry and native Save/cold tests passed; full handheld acceptance
remains pending. Follow PLAYTEST_14.md for both new-game and owner continuation;
labelled capacity fixtures are listed separately in verification.
