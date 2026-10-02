# Playtest 14 TM availability — implementation ledger

Task10 candidate sources below implement Appendix B. Focused transaction tests
pass; actual shop/menu presentation and Save/cold Continue acceptance remain
GateB. This is not final release or RG40XX H acceptance. Earlier sources stay
unchanged; the complete chapter-wide TM audit belongs to the final matrix.

All names below use the active move-based item aliases. TMs are reusable.
Bag **or PC** ownership prevents paying for a duplicate store/prize TM. The
Department Store uses native item prices and quantity/ownership handling.

| Source | TM / move | Cost | Requirement |
|---|---|---:|---|
| Department Store2F | TM05 Roar | 1,000 | 3 badges |
| Department Store2F | TM28 Dig | 2,000 | 3 badges |
| Department Store2F | TM31 Brick Break | 3,000 | 3 badges |
| Department Store2F | TM43 Secret Power | 3,000 | 3 badges |
| Department Store2F | TM45 Attract | 3,000 | 3 badges |
| Department Store2F | TM15 Hyper Beam | 7,500 | 4 badges |
| Department Store2F | TM17 Protect | 3,000 | 4 badges |
| Department Store2F | TM44 Rest | 3,000 | 4 badges |
| Prize Corner | TM13 Ice Beam | 4,000 coins | Coin Case in Bag |
| Prize Corner | TM23 Iron Tail | 3,500 coins | Coin Case in Bag |
| Prize Corner | TM24 Thunderbolt | 4,000 coins | Coin Case in Bag |
| Prize Corner | TM30 Shadow Ball | 4,500 coins | Coin Case in Bag |
| Prize Corner | TM35 Flamethrower | 4,000 coins | Coin Case in Bag |
| Department Store roof girl | TM16 Light Screen | 1 Fresh Water | One successful exchange |
| Department Store roof girl | TM20 Safeguard | 1 Soda Pop | One successful exchange |
| Department Store roof girl | TM33 Reflect | 1 Lemonade | One successful exchange |
| Celadon Gym Erika | TM19 Giga Drain | Victory reward | Defeat Erika; retry if TM pocket full |

Roof vending prices are Fresh Water200, Soda Pop300, Lemonade400. Failed TM
delivery consumes no drink and sets no exchange receipt. An already-owned
reward consumes no drink. Store stock has no Scope/Giovanni gate, and earning
more than four badges does not expose future stock. No global item prices,
Repel prices, existing training shops, or later regional evolution items change.

The free repeatable Counter tutor on3F and Soft-Boiled tutor in the city use
the native compatibility/selection/replacement flow. They require no once-only
tutor receipt. Soft-Boiled retains the native access footprint; no new Surf
unlock is supplied.

## Pending chapter and long-range obligations

- Task11 adds Erika's TM19 Giga Drain with a separate retryable reward receipt.
  The badge survives a failed TM delivery. Bag/PC ownership prevents a duplicate.
  Real Gym battle and reward presentation remain GateB acceptance cases.
- Later content must address remaining reusable TM availability. That obligation
  does not authorize adding future stock or maps during Playtest14.
- Pokémon prizes are optional repeatable ordinary gifts: Abra9/180 coins,
  Clefairy8/500, Dratini18/2,800, Scyther25/5,500, Porygon26/9,999.
  Abra already has Route24/25 alternatives, and Clefairy has Mt. Moon B2F.
  Dratini, Scyther and Porygon retain explicit later non-Game-Corner availability
  obligations; no future location is created here. None gates the story.

Authoritative tables: `tools/three_horizons/chapter14_content.json` economy;
ROM tables: `src/data/three_horizons_celadon.h`; native transactions:
`src/three_horizons_celadon.c`. Final release documentation must replace these
intermediate acceptance notes with the exact tested candidate revision.
