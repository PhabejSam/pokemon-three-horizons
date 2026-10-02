# Playtest 14 — Celadon, the Silph Scope, and the Return to Lavender

**Chapter Blueprint / written design for owner review — 2026-10-01.**
This document translates the owner's supplied PT14 scope and approved Narrative Canon v1.2 into a bounded chapter. It is not a claim of implementation or release acceptance. The detailed execution plan follows review of this written design.

## 1. Authority, lineage, and evidence

Authority order: the owner's current PT14 request and explicit corrections; the supplied Story Bible v1.2; this chapter's approved design; the detailed implementation plan. Existing successful behavior remains unless those sources explicitly replace it. Brainstorms, screenshots, old deferred ideas, and donor scripts do not independently authorize features.

- Canonical copy: `docs/three_horizons/THREE_HORIZONS_STORY_BIBLE.md`, copied byte-for-byte from `Pokemon_Three_Horizons_Story_Bible_v1.2.md`. SHA-256: `53d09fbead5167252cfe42c9e8097bc6e9d838b6a56c44a5944dfb4f55a81605`. The attachment text names an extra `(1)` suffix; the actual supplied file has no suffix and is v1.2.
- Isolated branch: `feature/playtest14-celadon-lavender`; directory `work/playtest14-celadon` under this task.
- Base: `2d85555d74f34f5029c38a3b2db26fb7eb3f99c0`, the completed Navigator review. Its runtime feature/production build revision is `ea393ce3174751c50206e85101b9682c5cfbb0c7`; the later commit is documentation.
- Original lineage remains `feature/opening-demo` at `1754893d42d1f41c5b31488cfc952856d8c4d459`. PT14 inherits the reviewed descendant, without merging into either protected working tree.
- Protected RC2 ROM SHA-256: `c08a31c6ac0c3f5fff5a867b9a98b9ee6d246cf39f16c17d748b431a29a003f2`.
- Protected Navigator ROM SHA-256: `537c3ca0185bc34c0e0bc36cdebcae784984cc173ba8ff2fead5f28720537837`.
- Actual new owner battery: `pokemon-three-horizons-playtest-13-1-road-to-lavender.gba.eps`, 131072 bytes, SHA-256 `e94846ce281dc01c245f1fdeabf300b350433fda5a1368924767a3de41536ef2`.
- A copied battery passes checksum/signature validation for both complete 14-sector generations (16 and 17). Generation 17 is newest. Normal cold Continue on the exact older RC2 opens `TH13_PokemonTower_6F`, position `(11,14)`, marker `0xA90C`, three badges. Raw party and all PC storage match the source exactly. This establishes the source baseline, not PT14 migration acceptance.
- Full decoded owner inventory, party attributes, boxes, receipts, variables, and raw comparison material remain private under `.superpowers/sdd/2026-10-01-playtest14/owner-baseline/`. Originals are never emulator output destinations.

The owner reports successful RG40XX H/VBA-Next RC2 testing through the Tower barrier. Record that as owner-reported acceptance of that older build. Do not convert it into PT14 or Navigator hardware acceptance. The full-party Ekans corruption/black-screen report remains a **high-severity, owner-reported intermittent hardware failure, not reproduced locally, with unresolved root cause**.

## 2. Shared design intent and chapter boundaries

The player continues a traditional Kanto journey into Celadon, earns Erika's badge, breaks Rocket's local operation, returns with the Silph Scope, resolves Cubone's mother's story, rescues Fuji, and wakes Snorlax. Research deepens those adventures without displacing them.

Success means the whole bounded arc is playable from both a new game and supported existing batteries; witnessed research, Pokémon identity, rewards, and trainer history survive saving and cold Continue. The chapter receives its own tested ROM and practical hardware checklist. The owner performs the final handheld acceptance.

Explicit exclusions: Saffron's chapter, Fuchsia's chapter, Legendary Birds, regional transitions, Johto, Hoenn, later canonical revelations, full later-generation Dex, multiplayer-required evolution, redesigned partner systems, and additional Research Gear modules. No merge, remote release, repository-setting change, or overwrite of existing packages.

## 3. Chapter Blueprint

| Required element | Chapter treatment |
| --- | --- |
| Story purpose | Celadon shows Rocket asking the same question as the professors for different reasons. Lavender shows that useful technology does not explain away memory, grief, or bonds. |
| Knowledge before | Shipping explains some sightings, but remote adaptation and Lavender's behavior do not fit that explanation completely. The Tower contains unidentified ghosts. Rocket and the trio point toward Celadon. |
| Knowledge after | Rocket independently recognizes a pattern and wants prediction, profit and control. The Scope reveals an existing spirit; emotional attachment and older accounts are evidence worth respecting. The ultimate cause remains unknown. |
| Main Pokémon journey | Route 8 → east–west Underground Path → Route 7 → Celadon exploration, fourth Gym and Hideout → Scope → Tower → Fuji/Flute → Snorlax. |
| Three Horizons mystery contribution | Organized Rocket reports connect sightings, habitats, unusual evolution and ghost testimony. The mother's watch demonstrates that physical habitat alone cannot explain every event. |
| Research moments | Required authored **MOTHER'S WATCH**, recorded before the Marowak battle, with a permanent observation and photo. Existing optional scenes stay optional. No obligatory new research scene on every travel map. |
| Professor involvement | Existing Calls continue correctly. No immediate call interrupts Marowak's passing or Fuji. Later interpretation is a quiet archive note available after resolution; it does not claim a call was received. |
| Aide/local expert | Route 2 aide clearly delivers Oak's requested supplies before explaining Flash. Daisy provides the Town Map, with Oak's network offering missing-map catch-up. Fuji is the immediate human voice for the Tower's emotional meaning. |
| Rocket thread | Environmental records and the mandatory Hideout sequence establish systematic information gathering. Some grunts care only about money and rare Pokémon. Giovanni is strategic, not mystical or omniscient. |
| Jessie/James/Meowth | Their Lavender business leads into a Celadon report-delivery/Hideout assignment. They remain comic, dramatic, loyal criminals; they accidentally expose useful clues. They neither become heroes nor disappear from continuity. |
| Rival thread | Lavender remains conversation-only. Both first and repeat dialogue respect the town's mourning, recognize the player's research, and promise competition another time. |
| Local emotional story | Cubone's deceased mother is protective and angry. The Scope permits recognition; documentation is respectful; a required battle calms her; she passes peacefully. This individual is never a capture reward. |
| Return hooks | Celadon retains shops, prizes and services plus Rocket-aftermath dialogue. Lavender retains Tower/memorial access, the archive, Fuji and changed community/Cubone reactions. |
| Foreshadowing | People can value the same evidence for very different purposes; old accounts should not be dismissed. Do not name or explain the later phenomenon, its cause, or regional answers. |
| Rewards | Erika's fourth badge and TM once; normal exploration items and shop access; Scope; the permanent photo; Fuji's Flute; Snorlax encounter and an open road footprint. |
| End hook | The Flute has opened exploration beyond a familiar sleeping obstacle. The world continues naturally; no developer-facing playtest endpoint message. |

These interpretations follow Story Bible §§8–13, Kanto Chapters 9–10, and §26. Exact dialogue, coordinates, teams, prices, and encounter weights are implementation details under its OPEN DETAIL/provisional-mechanics rules, subject to the concrete constraints below.

## 4. Architecture decision for review

### Recommended: append a new chapter map group; retain saved layouts

The current Three Horizons group is index 75 with **118 maps, indices 0–117**. `struct WarpData` uses signed `s8` group/map fields (`include/global.h`), and `Overworld_GetMapHeaderByGroupAndId` indexes directly (`src/overworld.c`). Only ten further map indices are safe in that group. The chapter needs approximately **37** new maps.

Append `gMapGroup_ThreeHorizons14` as **group 76**, with every new map index below 128. Preserve group 75's complete ordering and every existing layout ID. Append new layouts. Do not change the type or byte size of saved warp fields. Add an explicit shared Three Horizons map-family predicate used by call dispatch, Cut object handling, field features and tests; replace only assumptions that intentionally cover all project maps. Do not broaden unrelated native-map behavior.

Alternatives considered:

1. Keep appending to group 75: simpler registry edit, but invalid signed map numbers would break saved warps. Rejected.
2. Widen/reinterpret warp fields or renumber existing maps: touches old batteries, sentinels and upstream behavior unnecessarily. Rejected.
3. New group 76: preserves old coordinates/IDs and saved structures; requires an audited map-family predicate and cross-group warp tests. Recommended.

This is a demonstrated capacity constraint, not a reason to omit content. Approval of this written design approves the new-group solution; implementation must still stop if allocation or migration tests show another conflict.

### Persistent state without save growth

- Keep SaveBlock1/SaveBlock2/SaveBlock3/PokémonStorage at **15568/3884/4/34144 bytes** and retain relevant offsets.
- Keep all old map IDs, trainer IDs, flags, item/species IDs, research IDs and photos stable. Append new definitions.
- Current named unused-flag scan found 90 unreferenced candidates below the daily-reset boundary. A concrete provisional 70-bit pool is `0x8E5–0x91E` (58), `0x881–0x887` (7), `0x88E–0x88F` (2), `0x8E3` (1), `0x4F9–0x4FA` (2). None may be considered allocated until the plan's receipt-by-receipt ownership ledger and collision test pass. Do not use daily flags `0x920+` for persistence or reclaim the EXP Share's `0x021`.
- The expected budget is roughly 45 donor pickup/hidden-item receipts and 25 chapter/gift/photo/state receipts. Share a pickup's visibility and collected receipt where they describe the same event. Count final exact donors, gifts and state machines before coding; stop if the complete ledger does not fit safely.
- Use explicit flag lists for migration: these pools are **not contiguous as a whole**. Never clear the span between their minimum and maximum.
- This extends the project's allocation policy into audited unused system-range bits, not live system state. Preserve the existing PT13-only `<0x500` assertion; add a separate PT14 allowlist/collision test. The native daily-reset boundary is excluded.
- Existing persistent unused-variable aliases are already allocated. Use tested flag states for this chapter instead of claiming another free variable.
- Approximately 38 new trainer identities, provisionally 157–194, fit the existing trainer-flag capacity. Final roster must preserve all existing IDs and retain distinct identities for Jessie and James.
- Add a new packed version marker (next unused value `0xA90E`) within the existing version mask. Every older migration predicate must recognize it. Current code explicitly excludes only known markers; adding a final branch alone would re-run older migrations and erase progress on later Continue.
- Initialize only PT14-owned flags and newly allocated trainer defeat bits once. Do not infer photos, spirit victory, badge, Scope, Flute or Snorlax results from unrelated old flags.
- Continue safely resets temporary Vs. Seeker readiness, not defeat history. Town Map catch-up is an actual interaction/reward, not fabricated migration ownership.

## 5. Maps, travel and physical endpoint

Adapt existing repository FRLG assets into authored `TH14_` maps and chapter scripts. Native donor presence does not mean playable project content exists. Retain project tileset conventions, followers, field behavior, clocks, healing and healing-location bookkeeping.

Add project secondary-tileset definitions for the existing CeladonCity, Condominiums, DepartmentStore, SilphCo, GameCorner, CeladonGym and RestaurantHotel assets. Author changes in `map.json`, registered layouts and `map.bin`, chapter scripts and source manifests; do not patch generated map headers/events. Elevators need project floor recognition/dynamic destinations; every floor, cancellation, exit and re-entry is a focused check. Respect 16 active-object and 64 saved-template limits while staging followers and the trio.

New-map budget:

| Area | Count and behavior |
| --- | --- |
| Celadon | City plus 20 interiors: Center floors, Gym, Department Store floors/elevator/roof, Mansion floors/roof room, Game Corner/Prize Room, diner/hotel/homes. Every accessible door has a valid return. |
| Rocket Hideout | B1F–B4F and elevator, five maps. Preserve recognizable puzzle/lift structure with audited doors, pickups and trainer visibility. |
| Routes 8 and 7 | Two connected project routes with trainers, signs, items and curated encounters. |
| Saffron gatehouses | West/east interiors, two maps; gates remain restricted. Merely visiting Celadon does not open Saffron. |
| East–west Underground | Two entrances and tunnel, three maps. |
| Route 11 gate | Two floors, reachable before the Flute; native local NPC interactions adapted without later-destination promises becoming live content. |
| Tower 7F | One new upper map reached from the existing sixth floor. Existing floors keep their identifiers and progress. |
| Route 12 landing | One deliberately bounded map around the Route 11 junction and sleeping Snorlax. |

The new Route 12 landing allows approach, viewing and interaction with Snorlax. Before the Flute its actual collision blocks the onward footpath. After catch or victory the footprint is walkable and leads onto a short safe stretch. Clearly visible bridge-maintenance barricades bound the unfinished north/south connections, with in-world maintenance text; no invisible warp, developer endpoint dialogue or accidental donor network into Fuchsia. Returning through the gate is always possible. This is a chapter boundary, not a second replacement Snorlax obstacle.

West Celadon/Cycling Road and Saffron exits likewise must not accidentally expose later native chapters. Port only the services/footprint described here. Donor Tea/guard, Fly, regional-link, multiplayer and postgame behavior must be audited; do not import unrelated progression just because a donor NPC has it.

Every new outdoor route retains ordinary first trainer battles. Optional trainers and rewards cannot become mandatory solely to force research exposition. Erika and Hideout are available in either natural order; Scope requires Giovanni, Tower mother resolution requires Scope, Fuji requires upper-Tower rescue, and Snorlax requires Flute.

## 6. Required retained-content repairs

| Target | Design and focused proof |
| --- | --- |
| Reviewed Navigator | Inherit the reviewed graphical three-card UI, input/cleanup, archive counters and existing authored photographs. Exactly Research Log, Field Photos, Calls. No PokeNav art redesign or fourth Town Map module. Verify old and new records together, pagination, empty states, return to field and cold persistence. |
| Native Town Map | Early Daisy handoff in Pallet through a once-only bag-safe gift. Progressed players missing the item receive it from an appropriate Oak/network interaction. Ownership plus receipt prevents repeats; full bag stays retryable. Use the native Town Map item path with an actual Kanto map, correct project location marker, labels, return callback and no Fly unlock. Test outdoors, indoors, caves and new group76. |
| Viridian clearing | Repair the documented partial upper/lower tree metatiles, including near Cut, without moving the secret scene or replacing its gameplay. Preserve Pinsir/Heracross, follower/Cut access, observation/photo/reward and optional revisit. Native-resolution before/after frames required. |
| Route 9 Cut | Reproduce entry from Cerulean on an uncut copy before editing. Source candidate: `TemplateIsObstacleAndVisibleFromConnectingMap` hides FRLG Cut objects near outdoor entry edges, while the Route9 tree at x=2 shares `FLAG_TEMP_12`. Verify current-map versus connecting-map ownership and initialization. Before Cut it must be visible/colliding; after Cut graphic/object/collision agree; walking away, re-entering, migration and cold reload are deterministic. Do not infer a permanent-world Cut redesign for all other trees. |
| Route 2 Flash aide | Preserve third-badge plus ten caught/received species requirement, full-bag retry, owned/receipt checks and current field rules. Qualified speech first acknowledges Oak's delivery/research milestone and Rock Tunnel, gives HM05, then explains conscious compatible non-Egg use without learning a move or needing a free move slot. |
| Vs. Seeker greeting | Preserve reviewed returning-opponent greeting only for ready previously defeated trainers. First-battle introduction and party remain original; neither a signal nor repeat use marks a first trainer defeated. Verify/document the native single-`!` and double-`!!` meanings from actual behavior. |
| Vs. Seeker evolution | Add explicit, deterministic ROM-side rematch overrides for suitable Growlithe/Arcanine, Vulpix/Ninetales, Pikachu/Raichu, Clefairy/Clefable and Jigglypuff/Wigglytuff slots, and only other justified authored cases. Conditions use scaled level, badge stage and trainer/slot identity. Plan records exact thresholds. No blanket item-evolution policy, random branch, boss rematch, first-party change or player evolution change. Validate moves, ability legality, XP/EV/Seen behavior and low/high clamps. |
| Route 11 east gate | Remove the outside NPC roadblock; let the player explore the gate and reach sleeping Snorlax. Preserve ordinary trainers, bag/PC and follower behavior. Gate NPCs never stand on the required corridor. |
| Lavender rival | Rewrite first/repeat speech as respectful conversation. Preserve completed receipt; never add a battle or replay the intro for the owner. |
| Lavender trio | Stage all three visibly away from building occlusion and follower overlap. Preserve the completed cameo and its Celadon lead; no migrated replay just to show new positions. |
| Early Tower Rocket | Keep a nonbattle observer sending Giovanni's ghost/sighting reports to Celadon. Connect that information to the trio and Scope through unavoidable/repeatable barrier guidance, not a single optional desk. |
| Tower endpoint text | Replace the old Scope-to-unresolved endpoint branch and developer-facing completion sentence. Without Scope retain the meaningful ghost barrier and Celadon lead. |
| Tower fog | `B_OVERWORLD_FOG=GEN_LATEST` currently maps fog to permanent Misty Terrain. Keep atmospheric horizontal fog but suppress this automatic terrain conversion specifically for Three Horizons Tower battle maps, including Terrain Pulse's fog-derived move preview. Do not globally alter fog, other regions, moves, or user-created terrain. Native tests plus battle/field images prove the exception. |

Town Map inspection must include the actual frontend: the native item currently routes through the existing region-map system, so simply awarding the item is insufficient. If the Kanto presentation requires shared changes, guard them to project maps and test upstream builds.

## 7. Celadon: city, Gym and economy

Celadon must be a usable city, not just a corridor to Giovanni. Its Center, Department Store, Mansion, Game Corner, Prize Corner, Gym, homes, signs and NPCs have distinct local functions and appropriate text. Shops remain open after Rocket's defeat; selected NPCs acknowledge the changed atmosphere.

Erika retains a Grass-focused identity and becomes badge four. Port a coherent donor-based trainer roster under new Three Horizons IDs; keep first parties authored and deterministic. Gym trainers may enter ordinary rematches if the approved ordinary-trainer rules permit; Erika never does. Badge, TM and post-win guide behavior are each exactly-once and full-bag-safe. The Hideout is not gated behind her badge, nor is Erika gated behind Giovanni.

### TMs and store stock

Verified current mechanics: `I_REUSABLE_TMS` equals `THREE_HORIZONS` in `include/config/item.h`; `FOREACH_TM` defines 50 active TMs and eight HMs. Preserve reusable TMs. Placeholder item enums up to TM100 do not authorize 100 supported TMs.

Use a small ROM-authored stock table with explicit badge/story eligibility and active TM mapping. Celadon is an early/midgame access hub, not an all-TM shop at four badges. Specialty Game Corner TMs remain another source. Future vendor stages may be described in the availability document; do not instantiate later vendors or rewards now. No new persistent per-TM purchase bit is needed when existing ownership determines access/duplicates.

The implementation plan locks actual stock, prices and gates by move identity against active TM mappings; do not copy numbers from a different game's TM list without checking. Preserve existing Repel pricing, evolution items and global economy unless specifically within new curated stock. Prevent charging for a failed delivery and provide sensible already-owned reusable-TM handling. Define eventual alternative availability as a documented coverage obligation, not a claim that later routes have already been built.

### Game Corner / Prize Corner

Retain recognizable slot/coin/prize identity using the available in-game systems. Explicit TH prize tables are required: donor scripts contain FIRERED/LEAFGREEN-only branches that do not populate an Emerald TH build automatically.

Use the classic Celadon prize identity as the starting design: selected Pokémon, specialty TMs and items. The plan will specify each entry/cost/level. Pokémon delivery supports party or PC safely; cancel, insufficient coins and full storage must not charge or mark a delivery successful. Coin Case handoff is retryable and unique; coin arithmetic clamps; replayable games and purchases survive menus and native saves. No species is permanently lost by declining this optional facility. Record an alternate long-range availability obligation for any exclusive prize species; do not invent future maps to satisfy it in PT14.

Mansion/gift and shopping interactions also preserve full-party/full-PC behavior, nicknames, identity, once-only rewards and project training configuration rules. No new special legendary configuration feature is in this chapter.

## 8. Rocket Hideout and the Scope

Keep the recognizable poster entrance, basement exploration, movement puzzles, lift-key progression, lift destinations and Giovanni encounter. All progress/rewards are receipt-based and retryable after loss, full bag or reload. No object hides before its necessary state/reward succeeds.

Story delivery uses three short optional environmental records plus a mandatory trio beat, so exploration is rewarded but the basic causal lead cannot be missed:

1. A distribution map juxtaposes local habitat/sighting reports.
2. Ghost and migration statements are explicitly unconfirmed.
3. Orders request rare appearances, abnormal evolution and witness reports for comparison.

The trio's assignment supplies a comic glimpse of organized research. Jessie calls it important work, James complains about the notebooks, and Meowth blurts out that Giovanni compares reports before the thefts. They obstruct the player as Rocket members. Retain their approved artwork/attribution and use a safe authored double encounter with a fewer-than-two-usable-Pokémon path. Loss permits a retry; victory marks both distinct trainer histories and the story result once. These are excluded from ordinary rematches.

Giovanni understands the value of predicting rare Pokémon, not the true explanation. A suitable voice is: "Anyone can chase a rare POKéMON. Knowing where it will appear first—that is useful." His defeat closes this local operation, not the entire Rocket organization. Do not mention later-region answers or legendary-regulator theory.

The Scope is awarded through the appropriate post-Giovanni flow, one time and bag-safe. If delivery fails, the item/interaction remains available; defeat cannot strand the player without it. The handoff and repeat guidance explicitly send the player back to Pokémon Tower. Existing Tower trainer, item, research and story receipts are never reset.

## 9. Return to Lavender: the mother's state machine

Wild Tower ghosts before Scope keep their approved unidentified/uncatchable behavior. With Scope, normal Tower encounters are identifiable and follow their ordinary capture rules. The story mother is a separate encounter context even when its species is Marowak.

Reuse the existing native `StartMarowakBattle` path and `BATTLE_TYPE_GHOST` context if tests confirm the required behavior. Existing code retains that flag with Scope, uses `GhostBallDodge` for Balls, and returns successful resolution only for `B_OUTCOME_WON`. Do not create a global Marowak species capture ban. Test all relevant Balls, including Master Ball, without consuming progression or opening stairs. Use the established in-world spirit explanation.

| State | Behavior and persistence |
| --- | --- |
| No Scope | Ghost barrier blocks stairs. Repeat dialogue gives the Celadon/Rocket/Scope lead. No Marowak photo or new resolution receipt. |
| Scope, no documentation | Reveal MAROWAK, identify her as Cubone's deceased mother, stage the respectful observation, display/take **MOTHER'S WATCH**, then begin the required battle. |
| Documented, unresolved | Observation/photo remain permanently available after a loss; retry the confrontation without re-awarding the photo or pretending the spirit already passed. |
| Victory, spirit unresolved | Calm/recognition/quiet fade sequence; write the completion receipt only through the successful resolution path. No immediate professor interruption. |
| Spirit resolved | Stairs remain open; ghost object/trigger no longer blocks. Upper Rockets/Fuji sequence is accessible. Old archive content is unchanged. |
| Fuji rescued, Flute pending | Fuji is available at the appropriate house/interaction and repeats delivery until it succeeds. |
| Flute delivered | No duplicate Flute; normal repeat dialogue and Snorlax clue. |

Do not blindly port the FRLG scene ordering: it identifies the mother after battle, whereas this task requires recognition and the photograph first. Do not treat fleeing, Teleport, Poké Doll, blackout or an aborted battle as victory. Verify callback behavior, loss transport, follower restoration and field control.

### MOTHER'S WATCH composition and archive

Use a ROM-authored environmental image with recognizable Tower graves/stairs, subdued spectral fog, Marowak revealed through the Scope and the player observing at a respectful distance. No trophy framing, capture pose, joke or invented upstairs Cubone presence. Preserve current native image sizing/palette conventions and render the result in the actual Gear.

Current art and subjects are ROM data, while ownership is a flag. Append a new photo/record; never insert IDs ahead of old photos. The existing photo actor table supports Pokémon subjects, so bake the observer into the authored backdrop or add a narrowly bounded runtime observer overlay; neither requires a saved image buffer. The implementation plan picks the smallest verified method compatible with selected player presentation.

The mandatory photo uses a dedicated transaction, not the common optional Yes/No branch. Set the ownership receipt only after the real presentation completes; observation and resolved-spirit receipts remain separate. Save/reload after documentation must keep the image available while preserving an unresolved battle if the player lost. Archive wording is **OBSERVED / DOCUMENTED**, never CAUGHT; it must not fabricate a Dex caught bit.

**Missing-Gear path:** current photo creation requires both Gear and observation, but older players can skip optional Gear handoffs. On returning with the Scope, a ground-floor Tower research contact offers Oak's free Gear before the upper-floor scene if it is missing, using the existing grant/intro transaction without a bag requirement. Present this as equipment to document the investigation. An already-equipped player is not interrupted. The sixth-floor scene also checks the prerequisites and safely directs an anomalous missing-Gear arrival to that contact; it cannot claim a photograph succeeded or open the battle/resolution path after a failed photo operation. Existing unseen photos remain unearned. Test a deliberately Gear-less migrated copy and the ordinary equipped owner copy.

After victory, allow a brief cry/softened stance/silence/fade before control returns. Fuji later explains the immediate meaning: the Scope let the player see her, and staying to understand her mattered. He respects older experience without supplying future lore. Later archive analysis is quiet and conditional, not a forced telephone exposition.

## 10. Fuji, the Flute and Snorlax

Upper-Tower Rockets are appropriate battles; the early observer remains nonbattle. Fuji's rescue and move home happen once and cannot be replayed through a map reload. The Flute is a unique, retryable reward, with a clear sleeping-Pokémon clue.

The Route 11 gate stays accessible before and after rescue. Snorlax remains visibly asleep and interactive until Flute use. With the Flute, its wake sequence starts a catchable encounter. **Catch or defeat** removes the roadblock. Decline, flee, escape item, aborted battle or blackout keep it available. Delay its persistent hide/result receipt until the accepted outcome; the FRLG donor's pre-battle hide/`fought` behavior is insufficient.

After resolution, the actual footprint and short onward path are open. A defeated Snorlax still has a documented alternate species-availability obligation for the finished game. Ordinary Cubone/Marowak availability similarly satisfies collection without capturing this deceased individual. Never enable unapproved later routes merely to supply those alternatives now.

## 11. Save-compatibility contract

Support new games, PT12, PT13, PT13.1, Navigator candidates and the supplied actual Lavender battery. Keep unique copies and clearly distinguish fixture saves from actual-owner migration runs.

Before movement on a new candidate, compare party and all boxes, species/forms, PID/nickname, shiny state, effective nature/ability, IVs/EVs, held items, moves/PP, Annihilape and Rage Fist tracker, money, bag/PC items, badge/Dex flags, research observations/photos/calls/introductions, all relevant variables and story/trainer receipts. Existing levels—including the owner's over-levelled team—are preserved rather than normalized.

Specifically retain fossils/revival, Skarmory trade, Cut/Flash, Vs. Seeker, first-victory history, ship/rival/Tower progress, gifts and reward masks. False old receipts must stay false too; the actual source's absent ship-departure flag must not be fabricated from the owner's other progress. Old declined/unseen photos stay absent.

The version transition is monotonic and idempotent. Test one cold import, an ordinary in-game save, full core shutdown and second cold Continue; then repeat migration/Continue to prove newly earned PT14 receipts are not cleared. For an in-progress Marowak, Scope delivery or Snorlax retry, the same state rules apply.

Engine bookkeeping exclusions must be individually justified. Clock anchors and separately demonstrated random daily lottery differences cannot become a blanket exclusion for story variables; the packed high migration-version bits remain asserted. Preserve raw audit evidence, failed comparisons and explanations.

## 12. Verification strategy and evidence boundaries

Use focused tests during each task and reserve the complete host/native/layout/upstream/build matrix for planned integration gates. Historical 170 host / 222 native / four layout / three upstream Navigator results are a baseline only, never fresh PT14 evidence.

For meaningful behavioral repairs: reproduce where feasible, add the appropriate regression, observe the expected failure, repair the root cause, rerun that focused test. A source assertion alone is insufficient proof of an interactive fix. Visual targets require reproducible native-resolution before/after frames on exact identified ROMs.

Focus ownership:

- Signed map bounds, stable old map/layout IDs, cross-group warp/call/Cut behavior and bounded outward exits.
- Explicit flag/trainer allocations, native struct/offset equality, all supported version transitions and repeated migration.
- Navigator old/new/empty/archive pagination, actual Marowak art, no invented photo receipts and read-only browsing.
- Town Map early/migrated/full-bag/duplicate/control/marker/return/save cases.
- Viridian metatiles, Route9 first connection-entry/Cut/map reload/follower cases, Flash handoff order and gates.
- Vs. Seeker undefeated/ready/multiple trainers, deterministic stone tiers, identity/ability/moves, low/high clamps, no charging, reset rules and unchanged defeat flags.
- Tower fog without automatic Misty Terrain; normal user-created terrain and upstream fog unchanged.
- Routes/city doors, item pickup collisions, shops, reusable TMs, coins/prize failures/party-or-PC delivery, Erika/Hideout in both orders.
- Trio/Giovanni losses/retries, lift/door/key state, once-only Scope and full-bag retry.
- Pre/post-Scope wild ghosts, mother reveal/photo before battle, every non-winning outcome, spirit fade/stairs, Fuji/Flute.
- Snorlax pre-Flute, wake/catch/defeat/escape/loss, footprint/road state and cold persistence.
- Full-party capture lifecycle: first-time Ekans and control species, Dex/nickname/party replacement/cancel-to-PC, first/middle slots, previous Gyarados/evolution/follower contexts and input timing. Perform at least one documented mGBA reproduction attempt starting from an unmodified copy of the supplied owner battery, and record the outcome. Use separately labelled modified fixtures for additional first-catch, evolution, follower and timing variations. No speculative patch or claim of a VBA-Next fix from a passing mGBA run.

Final integration runs all Three Horizons host and native tests, save layouts/offsets, documentation validation, upstream Emerald/FireRed/LeafGreen compatibility builds, and a complete exact-source PT14 ROM. Record warnings as old/new and investigate relevant new warnings; do not suppress assertions, skip failed cases or inflate totals by summing reruns.

Exact-ROM acceptance uses normal cold Continue from the owner's copied Lavender battery and follows: existing party/progress/Gear/photos/calls → Town Map catch-up → repaired earlier locations where practical → Route11 gate/Snorlax → Lavender → Route8/Underground/Route7 → Celadon shops/GameCorner/PrizeCorner → Erika → Hideout/trio/Giovanni → Scope → Tower identified ghosts → mother reveal and real photo → attempted Ball rejection → victory/spirit → upper Rockets → Fuji/Flute → Route11/Snorlax → in-game Save → close core → cold Continue → complete permanent-state comparison. Also verify the reverse Erika/Hideout order with a labelled branch.

mGBA automated controller/visual evidence is identified by exact core and ROM hash. It is not RG40XX H/VBA-Next acceptance. Hardware QA prioritizes actual migration, Navigator, the intermittent catch report, Cut, gate/Snorlax, shops/GameCorner, Hideout/Scope, fog, mother/photo/noncapture, Fuji/Flute and repeated cold saves; it does not ask the owner to repeat every automated edge case.

## 13. Delivery and execution handoff

After written-design review, the detailed plan at `docs/superpowers/plans/2026-10-01-playtest14-celadon-lavender.md` must lock exact map/flag/trainer ledgers, teams/encounters/shop stock, scripted dialogue/staging, test owners, task dependencies and commit/integration gates. Recommended execution is serial/inline for dependent content, with isolated read-only audits where useful. Do not merge until separately authorized.

Logical work sequence for that plan: save/map ownership foundation → carry-forward repairs/native services → travel and living city/economy/Gym → Hideout/trio/Giovanni/Scope → Tower mother's scene/photo/upper rescue → Flute/Snorlax → full integration, actual-owner migration, exact-ROM route, documentation/package. No intermediate task substitutes a smaller endpoint for the required chapter.

Required release files:

- `docs/three_horizons/PLAYTEST_14.md`: complete new-game and exact supplied-save continuation walkthrough.
- `docs/three_horizons/PLAYTEST_14_HARDWARE_QA.md`.
- `docs/three_horizons/PLAYTEST_14_ENCOUNTERS.md`.
- `docs/three_horizons/PLAYTEST_14_VERIFICATION.md`.
- Updated Research Gear/rematch documentation and explicit TM-availability architecture/coverage.

Distinct candidate: `pokemon-three-horizons-playtest-14-celadon-silph-scope.gba`, in a new PT14 output directory/package. Include exact hashes, feature/compiled/test revisions, guides, sanitized evidence and migration instructions. Exclude batteries, raw RAM, local private ledgers and unrelated files. Recheck all protected hashes and original working trees before delivery.

The final report covers all 53 owner-requested fields, using PASS/FAIL/NOT RUN/PENDING rather than implying completion. After the passing candidate is packaged, **stop for owner RG40XX H/VBA-Next hardware acceptance**. Do not publish or continue into the next chapter.

## 14. Review status and demonstrated risks

- Canon audit: no conflict between v1.2 and this bounded arc. Mandatory MOTHER'S WATCH and the uncatchable mother are explicit task requirements.
- Map capacity: demonstrated signed-index limit; new group76 is the recommended solution above, pending owner review of this design.
- State capacity: a safe candidate pool exists; final ledger and global collision scan are mandatory before allocation. No saved-size growth is proposed.
- Migration: existing exclusion predicates would reset prior state if updated incompletely; explicit new-version tests are mandatory.
- Tower fog: confirmed source-level unwanted terrain conversion; fix is scoped to project Tower maps.
- Route9 Cut: source-level root-cause candidate identified; emulator reproduction is still required before claiming a confirmed repair.
- Full-party Ekans hardware issue: high-severity, owner-reported intermittent hardware failure; not reproduced locally; root cause unresolved and no fix claimed here.
- PT14 feature code, fresh full builds/tests, new chapter art, exact-ROM acceptance and hardware acceptance: **not started/not established by this design-stage work**.

If implementation demonstrates a new conflict in any owner-listed stop category—save compatibility, Gear/photos, mother encounter, map/flag capacity, Town Map, gate/Snorlax, rematches, economy/GameCorner or upstream compatibility—record the evidence and stop for the owner before weakening requirements.
