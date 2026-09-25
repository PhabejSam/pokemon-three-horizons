# Playtest 8 beta checklist

This update polishes the Pallet-to-Brock route. Route 3, Mt. Moon and Cerulean are the next story milestone; they are not open in this build.

## Keep your save

Back up your `.sav` before testing. Copy it beside the new ROM with the same base filename as that ROM, keeping the `.sav` extension. Load through the game's Continue menu. Keep Playtest 7 and its original save separate. A new game is needed to repeat the opening and first partner handoff.

## Highest-priority tests

1. **First follower:** start a new game with followers ON. Choose a starter and finish Oak's handoff. Walk a few steps. Your partner should appear without an Options toggle. Repeat with followers OFF; it should stay hidden.
2. **Remaining partners:** after you and the rival choose, the regional display stays. Interacting with it explains that the other partners remain at the lab. You cannot claim a second starter. Leave and re-enter to check persistence.
3. **Healing:** visit both Viridian and Pewter Centers. Heal with 1, 3, and 6 Pokémon. Watch the machine place and flash that many balls, then confirm HP, status and PP recover. Check the balls align with the tray.
4. **Blackout:** lose to Brock again. Look for a clean fade and recovery with no empty location banner. Retry and check the badge/TM are not granted twice. Wild losses should still heal you without losing money.
5. **EXP. SHARE:** on your existing save, use the home PC's Item Storage. Withdraw the newly supplied EXP. SHARE, then use it in Key Items to turn party sharing ON. Win with one Pokémon while another stays in reserve; both eligible Pokémon should gain experience. Turn it OFF and repeat. Revisit the PC: no duplicate kit should appear. This shares with your party, not Pokémon stored in boxes.
6. **Reusable TM:** teach Rock Tomb to an eligible Pokémon. The TM should remain in the Bag. Teach it to another eligible Pokémon, save, quit and Continue; verify both moves and the TM remain.
7. **Evolution during battle:** use increased EXP if helpful. Bring Caterpie near level 7 or a starter near its evolution level to a trainer who still has another Pokémon. After earning the level, evolution should occur before the fight continues. Check species, sprite, types, HP/max HP, moves and PP in the resumed battle and Summary. Try cancelling with B, an Everstone, and an eligible reserve Pokémon with EXP. SHARE. A cancelled evolution must not immediately repeat at battle end. Then save and reload.

## Presentation and conversation

- The three professors stand together in the lab. Approach the starter table from every accessible side and check Oak can approach and return without getting stuck.
- People in the cities, Centers, gates and shops have individual dialogue. Forest trainers have individual before/after-battle lines. Check spelling and page breaks.
- The lab computer, awards and books have different descriptions.
- The intro professors are closer together and the Rayquaza title layer is removed. **The requested new illustrated mountain/professor/nine-starter cover and illustrated intro portraits are not included:** image generation was rejected by the service. The existing intro characters remain pixel sprites.

## Expected behavior

- Escape Rope is intentionally a free, reusable Key Item. Buying it once marks it sold out because you already own it. It exits an escapable area; it does not heal you or send you to a Center.
- A trainer blocks capture attempts without consuming your ball, matching this engine's enabled modern battle rules.
- Mints change effective nature, not current damage. Bottle Caps edit IVs. Neither is a healing item.
- Brock still uses Geodude, Zubat, Sandshrew and Onix. The AI may send them out in a different order.

For a bug report, include the ROM filename, new game or old save, location, party, options, exact steps, expected behavior, actual behavior and a screenshot if possible. Keep a separate save before testing a suspicious scene.
