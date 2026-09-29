# Playtest 13 evolution and training QA

Implementation and acceptance are in progress. A method listed here is not a
claim that its Pokémon or required item is already obtainable by Lavender.

## Release configuration and compatibility

The release source, independently of `include/config/test.h`, already sets
`P_GEN_1_POKEMON` through `P_GEN_9_POKEMON`, cross-generation evolutions and
regional forms to TRUE in `include/config/species_enabled.h`. This is inherited
P12 engine support, not a new Playtest 13 roster unlock. That file and the
species-ID/Dex-size configuration remain unchanged. The existing opening also
already calls `EnableNationalPokedex`; this pass does not add a second unlock,
new generation switches, or unrelated later-generation encounters.

Kanto/Johto/Hoenn families and their documented extensions remain the authored
availability policy. Disabling the inherited compilation switches would change
Dex storage and threaten the required P12 save compatibility. Compile-time
support, Dex capacity, and actual encounter/gift availability must therefore be
reported separately. Final integration checks the effective release macros and
all four save-layout sizes again. The test configuration alone is not evidence.

Existing enum identities are retained: Gyarados 130, Typhlosion 157, Magnezone
462, Rhyperior 464, Electivire 466, Magmortar 467, Porygon-Z 474, Annihilape
1370, Farigiraf 1372, Dudunsparce (two-segment) 1373. Species IDs are not always
National Dex numbers. The inherited final species value is 1572, with Egg and
NUM_SPECIES at 1573; inherited National Dex capacity reaches Pecharunt (1025).
No Pokémon identity, personality, nickname, or saved species number is rewritten
to apply the balance changes.

## Approved balance and single-player methods

Implementation choices within the approved plan: pure-trade level alternatives
use level 36; Gyarados gains Dragon Tail at 26 and Outrage at 48, retaining its
other Gen 9 level moves. Typhlosion replaces only its level-40 Earthquake entry
with Earth Power. These choices are recorded before the production checkpoint.
Existing direct-item methods below are retained rather than duplicated.

The native counter regression reproduced a selected Rage Fist being counted
while the Pokémon remained asleep. Three Horizons now excludes actions the
engine marks unable to execute; actual attempts that miss or meet Protect
still count. The upstream condition remains unchanged in non-TH builds.
Outrage coverage comes from the level-48 learnset and relearning, not a new
Outrage tutor or TM.

| Family | Single-player trigger | Availability by Lavender |
|---|---|---|
| Kadabra → Alakazam | Level 36; existing Linking Cord alternative retained | Yes, train an available Abra |
| Machoke → Machamp | Level 36; Linking Cord retained | Yes, Rock Tunnel Machop |
| Graveler → Golem | Level 36; Linking Cord retained | Yes, Mt. Moon Geodude |
| Haunter → Gengar | Level 36; Linking Cord retained | Method verified; Tower ghosts cannot be caught without the unavailable Scope, so Tower alone is not an obtainable source in P13 |
| Scyther → Scizor | Use Metal Coat | Later; no new early item reward |
| Onix → Steelix | Use Metal Coat | Later; no new early item reward |
| Poliwhirl → Politoed | Use King's Rock | Later; Water Stone still gives Poliwrath |
| Slowpoke → Slowking | Use King's Rock | Later; ordinary level-37 Slowbro remains |
| Seadra → Kingdra | Use Dragon Scale | Later |
| Porygon → Porygon2 → Porygon-Z | Use Upgrade, then Dubious Disc | Later |
| Rhydon → Rhyperior | Use Protector | Later |
| Electabuzz → Electivire | Use Electirizer | Later |
| Magmar → Magmortar | Use Magmarizer | Later |
| Magneton → Magnezone | Use Thunder Stone; native New Mauville level condition also remains | Later item availability; no new Kanto magnetic zone |
| Dusclops → Dusknoir | Use Reaper Cloth | Later |
| Clamperl → Huntail / Gorebyss | Use Deep Sea Tooth / Deep Sea Scale | Later; separate branches retained |
| Feebas → Milotic | Use Prism Scale or level with Beauty ≥170 | Later |
| Primeape → Annihilape | Rage Fist use counter ≥20, then a qualifying level check | Yes through training; learns Rage Fist at 35 |

No real multiplayer trade is required by these methods. Native trade entries
remain for upstream compatibility; Three Horizons supplies the level alternative
only in its own species data. Item methods use the engine's ordinary evolution
item flow. A failed target check must not consume an item.

## Other natural family extensions

These are the existing native conditions, not new gifts or encounters. “Later”
means the necessary species/item/location is not promised in this chapter.

| Family extension | Existing method | Chapter status |
|---|---|---|
| Golbat → Crobat | Level with sufficient friendship (release threshold 160) | Early training possible |
| Gloom → Bellossom | Sun Stone | Later item/species access |
| Chansey → Blissey | Friendship level-up | Later species access |
| Eevee → Espeon / Umbreon | Friendship level-up by day / night | Later species access |
| Eevee → Sylveon | Friendship level-up while knowing a Fairy move; evaluated before Espeon/Umbreon | Later species access |
| Eevee → Leafeon / Glaceon | Leaf Stone / Ice Stone; native Hoenn location alternatives retained | Later species/item access |
| Lickitung → Lickilicky | Level while knowing Rollout | Later species access |
| Tangela → Tangrowth | Level while knowing Ancient Power | Later species access |
| Togetic → Togekiss | Shiny Stone | Later item/species access |
| Aipom → Ambipom | Level while knowing Double Hit | Later species access |
| Yanma → Yanmega | Level while knowing Ancient Power | Later species access |
| Murkrow → Honchkrow | Dusk Stone | Later item/species access |
| Misdreavus → Mismagius | Dusk Stone | Later item/species access |
| Gligar → Gliscor | Razor Fang at night, held on level-up or directly used | Later item/species access |
| Sneasel → Weavile | Razor Claw at night, held on level-up or directly used | Later item/species access |
| Piloswine → Mamoswine | Level while knowing Ancient Power | Later species access |
| Kirlia → Gallade | Male Kirlia + Dawn Stone; Gardevoir branch retained | Later item/species access |
| Nosepass → Probopass | Thunder Stone; native New Mauville level condition retained | Later species/item access |
| Roselia → Roserade | Shiny Stone | Later item/species access |
| Snorunt → Froslass | Female Snorunt + Dawn Stone; Glalie branch retained | Later species/item access |
| Scyther → Kleavor | Black Augurite | Later item/species access |
| Girafarig → Farigiraf | Level knowing Twin Beam (learned at 32) | Later species access |
| Dunsparce → Dudunsparce | Level knowing Hyper Drill (32); native personality-based segment branch | Rock Tunnel encounter makes training possible |
| Stantler → Wyrdeer | 20 Psyshield Bash uses, then level | Later: current Stantler level list lacks Psyshield Bash; no chapter claim of reachability |
| Ursaring → Ursaluna | Peat Block at night in Hisui | Later: Kanto does not satisfy the region condition |

## Regional branches and baby stages audited

These rows record the actual compiled conditions. None adds a new encounter,
regional unlock, breeding service or evolution item to the chapter.

| Regional extension | Existing trigger | Available by Lavender |
|---|---|---|
| Galarian Meowth → Perrserker | Level 28 | No prerequisite form source |
| Galarian Farfetch'd → Sirfetch'd | Battle ends after at least 3 critical hits by that Pokémon in that battle | No prerequisite form source |
| Galarian Mr. Mime → Mr. Rime | Level 42 | No prerequisite form source |
| Galarian Corsola → Cursola | Level 38 | No prerequisite form source |
| Galarian Linoone → Obstagoon | Level 35 at night | No prerequisite form source |
| Hisuian Sneasel → Sneasler | Razor Claw held on level-up or used, outside night | No prerequisite form/item source |
| Hisuian Qwilfish → Overqwil | Level knowing Barb Barrage | No prerequisite form source; no invented Strong Style counter |
| Paldean Wooper → Clodsire | Level 20 | No prerequisite form source |
| Mime Jr. → Galarian Mr. Mime | Level knowing Mimic in Galar | No baby source and Kanto fails regional condition |
| Ursaluna Bloodmoon | `EVO_NONE` data marker | Not a player evolution |

| Baby / branch | Existing trigger | Availability limitation |
|---|---|---|
| Pichu → Pikachu | Friendship level-up | No baby gift/breeding source added; Pikachu itself is catchable |
| Cleffa → Clefairy | Friendship level-up | No baby source; Clefairy itself is catchable |
| Igglybuff → Jigglypuff | Friendship level-up | No baby source; Jigglypuff itself is catchable |
| Togepi → Togetic | Friendship level-up | No chapter source |
| Tyrogue → Hitmonlee / Hitmonchan / Hitmontop | Level 20, Attack greater than / less than / equal to Defense | No chapter source; all three stat branches retained |
| Smoochum → Jynx | Level 30 | No chapter source |
| Elekid → Electabuzz | Level 30 | No chapter source |
| Magby → Magmar | Level 30 | No chapter source |
| Azurill → Marill | Friendship level-up | No baby source added |
| Wynaut → Wobbuffet | Level 15 | No chapter source |
| Budew → Roselia | Friendship level-up outside night | No chapter source |
| Chingling → Chimecho | Friendship level-up at night | No chapter source |
| Bonsly → Sudowoodo | Level knowing Mimic | No chapter source |
| Mime Jr. → Mr. Mime | Level knowing Mimic outside Galar | No baby source added |
| Happiny → Chansey | Oval Stone held on level-up or used, outside night | No chapter species/item source |
| Mantyke → Mantine | Level with Remoraid in party | No chapter source |

Friendship means the unchanged release threshold of 160. These conditions were
read from `src/data/pokemon/species_info/gen_1_families.h` through
`gen_3_families.h`; source audit is not an emulator acceptance claim for every
later species. Regional evolutions, Wyrdeer and Ursaluna remain documented
future limitations rather than silently replacing their conditions. Ghosts in
Pokémon Tower cannot supply an early Gastly/Haunter capture without the Scope.
Visible Misdreavus and the other research partners are observations only.

## Battle and persistence acceptance

Automated/runtime results belong in PLAYTEST_13_VERIFICATION.md. Until recorded
there, the following are acceptance steps rather than completed checks.

1. Continue a copied P12 battery save with Gyarados. Inspect Water/Dragon typing,
   personality, full nickname, ability slot, nature, IVs/EVs, held item and shiny
   state. Enter a battle and confirm its types there too. Save and cold Continue.
2. Level a Gyarados through 26 and 48; test Dragon Tail and Outrage, decline one
   learning prompt and recover it through Relearn. Preserve Waterfall, Crunch,
   Dragon Dance and other previous entries. Dragon Claw must not be newly added.
3. Level Typhlosion from 39 to 40: Earth Power is offered. Decline and Relearn it.
   Test Earthquake's separate TM compatibility without claiming an early TM
   reward. Charizard still learns Air Slash on evolution (its level-0 entry).
4. For each level-36 trade family, verify no evolution at 35, evolution at 36,
   B cancellation, subsequent retry at another level, Everstone behavior and
   battle resumption. Check nickname, ability slot, nature, IV/EV/shiny and held
   item before/after; inspect the follower after returning to the field.
5. For item evolutions, test a compatible and incompatible target, item count
   after success/failure, branch identity, move-learning prompts and Save/Continue.
   Use disposable fixtures for later items; do not place them in early shops.
6. For Primeape, inspect the existing encrypted evolution tracker at 19 and 20.
   Test actual Rage Fist attempts, misses and Protect, plus a prevented/cancelled
   action. Record observed engine semantics. Merely selecting a move in a menu
   is not a qualifying use. The TH evolution scene is checked on a level gain,
   not immediately on the twentieth button press. Test cancellation, next-level
   retry, learned moves, follower and an actual cold battery Continue.
7. Use Laser Focus, then a multi-hit attack, then a separate attack on the next
   turn. All hits of the first attack may be guaranteed critical hits. The later
   attack must return to normal critical odds. Only a reproduced carryover defect
   authorizes a repair; a multi-hit attack alone is not evidence of one.

Full release/save/upstream gates and the user's exact post-Surge RG40XX H P12
battery migration remain separate from synthetic fixtures and focused tests.

## Focused evidence recorded during Task 29

On compiled revision `3c48c6e376283000e81068ac5cb2e85fb5b8c8f4`, exact-ROM
mGBA checks passed all four pure-trade families at level 36 with one Rare Candy,
identity preservation, evolved follower and cold Continue. This includes the
Machoke move-learning continuation repair described in the verification report.
Gyarados's Summary visibly shows Water/Dragon; maximum nickname, shiny appearance
and identity persist. Native prompts teach Dragon Tail at 26, Outrage at 48 and
Earth Power at 40; Earth Power also appears and teaches through Summary Relearn.
Primeape's tracker at 19 did not evolve at the next level; 20 allowed evolution.
Cancellation preserved Primeape; the following level evolved Annihilape, whose
follower and cold Continue were checked. The qualifying Rage Fist hit/miss/Protect
and prevented-sleep behavior, plus Laser Focus's one-attack scope, are covered by
native battle tests.

The same emulator pass exposed that the inherited release configuration disabled
using evolution-held items from the Bag, despite valid native evolution tables.
The Metal Coat attempt displayed the cannot-use message. A separate regression
now checks the Bag type and evolution callback for all twelve thematic items.
At that checkpoint item-use acceptance was pending; the subsequent repair and
exact-ROM retest below resolved it. Target-species tests alone were not proof
of usable single-player evolution.

The subsequent item repair is accepted on compiled `04fb4b295acbd07e82aeb195ec6e078663027e8e`:
all twelve thematic Bag callbacks pass natively, Onix evolves with one Metal Coat,
incompatible Magikarp consumes none, and Steelix persists through cold Continue.
`I_USE_EVO_HELD_ITEMS_FROM_BAG` is enabled only when THREE_HORIZONS is enabled.
See the verification report and Task29 archive for exact hashes and evidence.
