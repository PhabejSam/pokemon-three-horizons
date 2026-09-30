# Playtest 13.1 / RC2 — RG40XX H hardware acceptance

Pending owner acceptance on RG40XX H / VBA-Next. Desktop and native automated checks are documented separately. Preserve the original ROM/battery backup, and record the exact RC2 ROM SHA-256 before testing. Use New Game or cold Continue; do not load an old emulator state.

## Priority blockers

- [ ] In Viridian Forest, take one, two and three different authored photos on the same map. Each flash ends at the original brightness; no accumulating tint or black screen.
- [ ] Decline a photo, interact again and accept. Repeating the recorded scene adds no photo and leaves brightness intact.
- [ ] Open and close Gear between photos. Enter/leave a building, change map, save, fully close the core, reopen and Continue. Normal color remains.
- [ ] Repeat photo checks with follower enabled/disabled and at day/night. Weather/shade and follower appearance return correctly.
- [ ] Catch a previously unrecorded Zubat while pressing/holding A through capture. The complete Dex entry remains readable after its cry; release controls, then deliberately press A or B to dismiss.
- [ ] Repeat with rapid B, ordinary input, nickname Yes/No and a full party sending the catch to PC. A repeat catch skips the first-entry registration screen normally.

## Gear and preserved progress

- [ ] New Game: receive Gear once from Oak after partner/Pokédex setup and open it before leaving Pallet.
- [ ] Exact post-Surge PT12 copy: Continue in the correct place with party, boxes, badges, items, money, Pokédex, IVs/EVs, nature, abilities, nicknames and all completed story/reward receipts intact.
- [ ] In Vermilion Center, missing Gear is granted once by the scientist, including with a full bag. Continue onward to Route 11/Diglett's Cave/Route 2.
- [ ] Existing RC1 save: Gear, observations, photos, received calls and Flash remain available. Repeated Continue does not erase or duplicate them.
- [ ] Save under RC2, cold-close, reopen and Continue a second time; compare progress again.
- [ ] Route 2 aide retains Flash's Badge 3/ten-species checks without another Gear introduction.
- [ ] Cut works and tested trees do not immediately regrow. Repeat the Zubat-to-Skarmory trade on a disposable pre-trade save; no multiplayer trading is required.

## Presentation and calls

- [ ] Main Gear menu is bright/readable and ordered Research Log, Field Photos, Calls.
- [ ] Log list/detail, Calls list/report and photo/details/notes fit the screen without clipped text or stray graphics.
- [ ] Forest, Mt. Moon, Harbor, Route 9, Rock Tunnel and Lavender photos show recognizable environments and correctly placed native subjects.
- [ ] Elm introduces Johto research at the early Hoothoot interaction; Birch introduces Hoenn research at Makuhita's gathering (appropriate late-save fallbacks also work).
- [ ] Route 10 delivers one Oak call and Lavender one Elm call. Calls do not interrupt battle, menus, naming, Cut/Flash, movement or existing scenes.
- [ ] No automatic three-professor chain. Reading Calls remains passive and preserves story/reward receipts.
- [ ] Follow the full new-game or continuation route in PLAYTEST_13.md to the existing Tower barrier; no Celadon or Playtest 14 content is included.

For a defect, record the exact ROM hash, starting battery checkpoint, place, held/pressed controls, follower setting, day/night, number of photos and whether cold Continue changes it. Keep screenshots at native resolution where possible.
