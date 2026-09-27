# Playtest 12 candidate — verification record

Date: 2026-09-27. This is a playable candidate, not completion of every approved acceptance item. Replacement Jessie/James graphics remain blocked; the earlier grunt sprites are still visible.

## Build identity

- Feature revision: `a1df584321ba6cd319d7fdb8c694e3bb7f3116e8`.
- Exact compiled revision: `5c324f07cd554ca29a0b3bd3bae02f06cbce6d4e` (GitHub's temporary PR test merge, not a merge of the user's draft PR).
- ROM SHA-256: `6a5c169db77439f93c53c3e435a411251be7b6e62f386e3332e36acda8232336`.
- Successful Three Horizons workflow: https://github.com/PhabejSam/pokemon-three-horizons/actions/runs/36348904906
- Artifact: `10941896753`. ROM, ELF, map, environment log and source revision all come from that artifact.
- ROM and artifact archive hashes were independently recomputed after download.
- No earlier release or original user save was overwritten. No battery save or emulator state is distributed in this package.

## Automated verification

Linux CI rebuilt the map generator, then passed all **67 host checks**, **126 Three Horizons native engine tests**, and **4 save-layout tests**. The final workflow also passed trainer regeneration between build modes, existing migration/clock/nickname/capture/palette/evolution regression controls, and all five new negative controls (Dex darkness, Cut eligibility, Rocket completion, compact team rows, Surge adjacency). Negative controls deliberately restore a defect and must fail before the repaired implementation is checked again.

Coverage includes repeated migration from versions 9–12, supply receipts with full bags/money caps, starter species/move assertions, all six Power items and EV caps, seven player outfits' standing animation, palette ownership, party-only Rocket eligibility, both-victory completion, Cut compatibility/gates, all switch adjacency cases and randomized switch pairs. It does not imply every route or visual combination was played manually.

Upstream compatibility: Emerald, FireRed, LeafGreen, release builds, the complete upstream test job, documentation validation and the combined build gate all passed for the feature revision. Confirmed 2026-09-27 21:05 UTC at https://github.com/PhabejSam/pokemon-three-horizons/actions/runs/36348904912 . The upstream suite reported 5,397 passes, 9 expected failures, 16 known failures and 421 TODO entries (5,843 total); the job passed under its existing expectations. These are separate from the 126 project tests, all of which passed.

## Emulator evidence

Tests used the mGBA libretro core with the corresponding ROM/ELF. Each build started from a battery save or New Game; emulator states were only reused within the same exact ROM. Fixtures relocated the player through the native map loader or configured a party to reach focused cases. This is desktop verification, not RG40XX H hardware verification.

| Area | Executed check | Build checkpoint |
|---|---|---|
| Existing save | Original P11 Cerulean battery save loaded, saved and cold-loaded twice; party's 600 bytes, first six checked box slots, bag and money preserved. Final ROM independently rechecked these against the P11 baseline. | 3180e249; final a1df5843 |
| Dex display | Reproduced the P11 stale sprite fragments; captured 220 rapid-A frames across fixed first-catch Dex exit, battle restoration and nickname question. Maximum-length Spearow nickname completed with valid caught data. | 3180e249 |
| Shiny preview | Outdoor shiny Charmander stayed gold after Nature changes and 180 idle frames; selected shiny data retained. | 8c54869 |
| Fresh opening | New Game, rival naming and clock setup; normal walk into lab; player stands facing professors and rival at their lines; partner editor; Oak approaches; received 2 Ultra Balls and 2,000 money once (total 5,000). | 3180e249 |
| Bill | Initial Clefairy, PC sequence, human exit, ticket receipt, normal exit/re-entry and repeat talk; one ticket and completed rescue retained. | cba94c46 |
| Rocket double | Trio stages facing player; two three-slot opponent groups on one row; ordinary six-slot player row; Ekans/Koffing battle won, all three depart, control restored. | cba94c46 |
| Rocket singles | One usable party member with boxed Pokémon correctly triggers Ekans followed by Koffing; both victories complete the scene. Controlled low-HP James loss returns to Center; returning starts again with Jessie/Ekans. | 02104ccd |
| Ship | Normal ticket boarding, corridors/stairs, rival battle, captain and one-time HM01; repeat talk did not duplicate HM01. | 3180e249 |
| Cut | Cut tree removed with HM01/Cascade and compatible party but no known Cut move. Final failure text explains requirements. | 3180e249; final a1df5843 |
| Surge | Normal team solved adjacent switches and defeated the five-member team. Badge, one TM34 and open puzzle persisted through actual save/cold Continue; final ROM checked them again. | 3180e249; final a1df5843 |
| Reusable TM | On the final ROM, taught the same Shock Wave TM to Nidoking and Nidoqueen. Both move lists contain Shock Wave, party checksums remain valid and TM34 quantity remains one. | final a1df5843 |
| Chapter end | Vermilion aide's ending exchange completed after badge three. | 3180e249 |
| Cave sighting | Three Clefairy/Makuhita scene played; follower restored; route back to ladder remained usable. | 3180e249 |
| Forest | Final Treecko/Weedle and Shroomish/Caterpie clearings interacted correctly; aide report and follower return checked. | final a1df5843 |

The checkpoints above identify feature commits; their artifact `demo-source-commit.txt` records the corresponding CI test-merge revision. The final package contains only the final ROM. Runtime experiments and patched test parties were never written into that ROM or the original user save.

## Independent review

One independent final review examined the implementation and ran 13 focused host checks. Its two findings were fixed in a1df5843: give forest visitors separate clearings with Kanto partners/aide reactions, and explain untaught Cut requirements in-game. The reviewer also explored 90 ship trainer endpoints/player states and 192 gym combinations without finding an unavoidable mandatory path blockage. The parent separately fixed Bill's temporary hide/completion flag collision, real-ROM multi-party row defaults, and PC Pokémon incorrectly counting toward Rocket double eligibility. A second review was not commissioned.

## Open items and test limits

- **Jessie/James artwork is unfinished.** The image service rejected generation with `moderation_blocked` (request `3793f4d7-9db3-4c49-9696-6bd459cc15cb`). No replacement image was produced or integrated. The old grunt artwork is not represented as fulfilling this requirement. A source-asset question remains pending.
- **RG40XX H is untested here.** Its emulator/core, real-time clock and flash-save behavior need the user's device run.
- Exhaustive manual testing of every first-catch species, full-party capture/evolution combination, all outfits/follower settings, every shiny-editor row at both gifts/day/night, all nine ship rival branches, reverse Rocket approaches and all loss/bag-full paths was not completed. The native/source tests cover portions of these cases; those checks are not substituted for missing visual evidence.
- This candidate ends after Surge and the Vermilion aide. Later routes and later Jessie/James teams are not part of this chapter.

## Upgrade instructions

Back up the old ROM and battery `.sav`. Copy that `.sav` to match the candidate ROM's base filename, launch the ROM normally and choose Continue. Never load an older build's emulator state. A new game is fine with a separate filename. The supplied guide starts with the Cerulean continuation route; retain your original save for comparison.
