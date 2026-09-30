# Three Horizons: early training and legendary capture rewards

Status: approved by the user on 2026-09-23. This does not change the delivered Playtest 6 ROM.

## Player intent

Make building a chosen team enjoyable without late-game stat correction becoming a chore. Catching a legendary is the challenge; choosing its stats and shiny appearance is the reward. Keep the opening friendly, make Brock more interesting, and make Oak physically deliver the supplies he announces.

Confirmed choices: Brock uses Sandshrew, not Vulpix. The training shop is temporarily in Viridian for testing and eventually belongs in Celadon. Continue implementing directly in the existing Three Horizons development checkout.

## Brock and future gyms

Use Geodude level 12, Zubat level 12, Sandshrew level 12, and Onix level 14. Retain Onix as the ace with Rock Tomb. Give Zubat modest early moves (Peck, Absorb, Supersonic) and Sandshrew Scratch, Defense Curl, and Sand Attack. Keep current modest IVs, no added EV investment, no held items, and no new healing-item budget. The added party members provide the difficulty increase.

Future Gym Leaders use 4–6 Pokemon: four early, five middle, six late. Their specialty remains recognizable, with occasional off-type partners. This is a design rule for future content, not a replacement of unrelated upstream trainer parties. Existing badge, prize-money, defeat recovery, and one-time TM behavior stay intact.

## Bedroom PC training kit

Provide one Macho Brace and one of each Power item in the player's item storage:

| Item | Training benefit |
| --- | --- |
| Macho Brace | Multiplies EV gains from defeated Pokemon |
| Power Weight | HP EVs |
| Power Bracer | Attack EVs |
| Power Belt | Defense EVs |
| Power Lens | Special Attack EVs |
| Power Band | Special Defense EVs |
| Power Anklet | Speed EVs |

Keep the existing Potion. This is a one-time kit, not a refill on each visit. Existing playtest saves receive the same kit when accessing their home PC. If item storage cannot accept every item, remember only successful deliveries and retry the missing items later. Depositing, withdrawing, reloading, or changing maps must not duplicate the kit. Use audited spare event state without changing the save structure.

Explain that these are reusable held training items. Native item effects remain in use. Newly caught ordinary Pokemon begin with zero EVs, with normal IV/nature generation. Power items add their target EVs to the defeated species' natural yields; they do not suppress other yields. The kit therefore speeds training but does not promise to prevent all unwanted EVs. Keep the existing summary IV/EV pages useful for checking progress.

## Training shop and IV improvement

Place a training clerk in Viridian's existing Mart so the feature is reachable before Brock. Later relocate the same service and stock to Celadon without extending this playtest's map boundary now.

Stock all six EV-reducing berries, the existing battle-nature Mints, Bottle Caps, and Gold Bottle Caps. Use explicit introductory prices: berries 100 each, Mints 1,000 each, Bottle Caps 2,000 each, and Gold Bottle Caps 6,000 each. These prices are provisional balance values for testing.

The clerk redeems a Bottle Cap to set one selected IV to 31; a Gold Bottle Cap sets all six IVs to 31. No late-game or minimum-level requirement. Show the Pokemon, affected stats, and cap cost before confirmation. Consume a cap only when a real change succeeds. Canceling, selecting an Egg, or selecting already-maxed stats must not consume anything. Preserve species, level, experience, ability, gender, moves, original trainer, capture information, held item, shiny state, and unrelated stats. Recalculate battle stats without reviving a fainted Pokemon or causing invalid HP.

Berries and Mints use existing native item behavior. Mints change the effective stat nature; they need not rewrite birth nature. Ensure the summary communicates the nature that affects stats. The clerk explains this distinction. Ordinary captures remain random rather than opening the legendary editor.

## Legendary capture reward

After a successful capture, offer the existing starter-style editor adapted to the actual caught Pokemon. Eligibility uses species classification: restricted legendaries, sub-legendaries, and mythicals, including their applicable forms. Ordinary wild Pokemon, failed throws, fleeing, defeating a legendary, gifts, Eggs, and trainer battles do not trigger it.

The editor must be available before the catch is finally placed in the party or PC. Show the actual species, actual level, and normal/shiny preview. Default to the caught Pokemon's existing values. Allow shiny on/off, nature, individual IVs from 0–31, and EVs from 0–252 with a total maximum of 510.

The player can confirm changes or keep the original catch. Cancel never releases or deletes the Pokemon. Work on temporary options and apply them only after confirmation. Do not generate a replacement level-5 starter or disturb starter progress variables. Keep level, experience, moves/PP, ability, gender, original trainer, capture ball/location, nickname, and other unrelated metadata. Record the chosen appearance consistently in the Pokedex and summary.

Respect the normal naming, party-full, party-swap, and PC-storage flows. A capture is delivered exactly once. Storage-full handling must be resolved safely before offering a catch that cannot be retained. The editor must not run again when opening the summary or loading the save. Existing saved legendaries are not retroactively reopened by this feature.

## Oak's handoff

After starter selection and the rival's pickup scene, Oak walks to an open tile beside the player, faces them, gives the Pokedex and supplies, and delivers his sendoff. Account for all three starter displays and the player's possible approach positions. Temporarily keep the follower clear during movement and restore it afterward. Oak returns to his normal position before releasing movement control.

Keep existing supply tracking: no duplicate Pokedex or item rewards, and a full bag allows later collection. Repeated conversations after the gift should not replay the walk. If supplies remain unclaimed, speaking to Oak directly can complete collection without him walking into the player.

## Verification and delivery

Validate the actual generated Brock party and first-gym recovery/rewards. Test new-game and existing-save PC-kit delivery, partial storage failure, and duplicate prevention. Check native Power item/berry/Mint effects and IV-service confirmation, no-effect, cancel, and inventory consumption paths.

For legendary captures test party space, full party sent to PC, party swap, cancellation, normal and shiny previews, legal stat limits, nickname/capture metadata retention, and save/reload. Include negative cases for ordinary captures and unsuccessful legendary encounters. Check all three starter-display routes for Oak and follower collision.

Build the opt-in Three Horizons ROM and run relevant engine/host checks plus standard-build compatibility checks. Deliver a separately named next-playtest ROM, build report, and focused beta checklist. Preserve Playtest 6 and the user's saves. Explicitly distinguish automated verification from manual emulator coverage.

## Scope boundaries

This work does not build Celadon or new legendary encounters. The reward must be exercised through a controlled test encounter or engine test until a real legendary encounter is available. Any temporary test access must be labeled and must not corrupt normal story progression. No multiplayer/trade guarantee is implied. Do not merge the draft PR as part of this feature.

## Source observations

- `src/player_pc.c` currently initializes item storage with one Potion.
- `src/pokemon.c` zero-initializes newly created Pokemon; training later adds EVs from species yields and held-item effects.
- `src/data/items.h` has the requested held items, berries, Mints, and Bottle Caps, but caps currently use `ItemUseOutOfBattle_CannotUse`.
- `src/party_menu.c` applies Mints through `MON_DATA_HIDDEN_NATURE`.
- `src/three_horizons_partner.c` assumes a level-5 starter and resumes a field script. It cannot be called from capture unchanged.
- `src/battle_script_commands.c` handles capture, party swaps, and PC transfer in a state machine; editor integration must preserve those states.
- `data/scripts/three_horizons/lab.inc` currently grants supplies without moving Oak.

Self-review: the proposal distinguishes native item definitions from working IV services, actual EVs from random IV/nature generation, starter creation from caught-Pokemon editing, and future Celadon placement from the currently playable map. No save-structure expansion or duplicate catch generation is intended.
