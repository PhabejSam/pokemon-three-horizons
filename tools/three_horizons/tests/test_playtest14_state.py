"""PT14 save ownership and immutable map/layout identity contracts."""
import json
import re
import subprocess
import tempfile
import unittest
from pathlib import Path
ROOT = Path(__file__).resolve().parents[3]
# Approved receipt values, independent of the production ledger.
EXPECTED = {'FLAG_TH14_PICKUP_0': 2277, 'FLAG_TH14_PICKUP_1': 2278, 'FLAG_TH14_PICKUP_2': 2279, 'FLAG_TH14_PICKUP_3': 2280, 'FLAG_TH14_PICKUP_4': 2281, 'FLAG_TH14_PICKUP_5': 2282, 'FLAG_TH14_PICKUP_6': 2283, 'FLAG_TH14_PICKUP_7': 2284, 'FLAG_TH14_PICKUP_8': 2285, 'FLAG_TH14_PICKUP_9': 2286, 'FLAG_TH14_PICKUP_10': 2287, 'FLAG_TH14_PICKUP_11': 2288, 'FLAG_TH14_PICKUP_12': 2289, 'FLAG_TH14_PICKUP_13': 2290, 'FLAG_TH14_PICKUP_14': 2291, 'FLAG_TH14_PICKUP_15': 2292, 'FLAG_TH14_PICKUP_16': 2293, 'FLAG_TH14_PICKUP_17': 2294, 'FLAG_TH14_PICKUP_18': 2295, 'FLAG_TH14_PICKUP_19': 2296, 'FLAG_TH14_PICKUP_20': 2297, 'FLAG_TH14_PICKUP_21': 2298, 'FLAG_TH14_PICKUP_22': 2299, 'FLAG_TH14_PICKUP_23': 2300, 'FLAG_TH14_PICKUP_24': 2301, 'FLAG_TH14_PICKUP_25': 2302, 'FLAG_TH14_PICKUP_26': 2303, 'FLAG_TH14_PICKUP_27': 2304, 'FLAG_TH14_PICKUP_28': 2305, 'FLAG_TH14_PICKUP_29': 2306, 'FLAG_TH14_PICKUP_30': 2307, 'FLAG_TH14_PICKUP_31': 2308, 'FLAG_TH14_PICKUP_32': 2309, 'FLAG_TH14_PICKUP_33': 2310, 'FLAG_TH14_PICKUP_34': 2311, 'FLAG_TH14_PICKUP_35': 2312, 'FLAG_TH14_SILPH_SCOPE': 2313, 'FLAG_TH14_LIFT_KEY': 2314, 'FLAG_TH14_PICKUP_38': 2315, 'FLAG_TH14_PICKUP_39': 2316, 'FLAG_TH14_PICKUP_40': 2317, 'FLAG_TH14_PICKUP_41': 2318, 'FLAG_TH14_PICKUP_42': 2319, 'FLAG_TH14_PICKUP_43': 2320, 'FLAG_TH14_PICKUP_44': 2321, 'FLAG_TH14_TOWN_MAP': 2322, 'FLAG_TH14_COIN_CASE': 2323, 'FLAG_TH14_EEVEE': 2324, 'FLAG_TH14_ROOF_FRESH_WATER': 2325, 'FLAG_TH14_ROOF_SODA_POP': 2326, 'FLAG_TH14_ROOF_LEMONADE': 2327, 'FLAG_TH14_GAMBLER_COINS_10': 2328, 'FLAG_TH14_GAMBLER_COINS_20_A': 2329, 'FLAG_TH14_GAMBLER_COINS_20_B': 2330, 'FLAG_TH14_ERIKA_TM': 2331, 'FLAG_TH14_HIDEOUT_POSTER': 2332, 'FLAG_TH14_TRIO_DEFEATED': 2333, 'FLAG_TH14_OBS_MOTHER': 2334, 'FLAG_TH14_PHOTO_MOTHER': 2177, 'FLAG_TH14_MOTHER_WON': 2178, 'FLAG_TH14_MOTHER_RESOLVED': 2179, 'FLAG_TH14_FUJI_RESCUED': 2180, 'FLAG_TH14_POKE_FLUTE': 2181, 'FLAG_TH14_SNORLAX_RESOLVED': 2182, 'FLAG_TH14_ITEMFINDER': 2183, 'FLAG_TH14_NINA_TRADE': 2190}

class Playtest14State(unittest.TestCase):
    def test_pt14_ledger_is_disjoint_and_signed_maps_fit(self):
        path = ROOT/'tools/three_horizons/chapter14_content.json'
        self.assertTrue(path.is_file(), 'PT14 ownership ledger is missing')
        content = json.loads(path.read_text(encoding='utf-8'))
        receipts = {r['name']: r['value'] for r in content['receipts']}
        self.assertEqual(receipts, EXPECTED)
        self.assertEqual(len(set(receipts.values())), 66)
        state = json.loads((ROOT/'tools/three_horizons/state_manifest.json').read_text())
        all_flags = {**state['flags'], **state['pickups']}
        all_flags = {n:int(v,0) if isinstance(v,str) else v for n,v in all_flags.items()}
        self.assertEqual({n:v for n,v in all_flags.items() if n.startswith('FLAG_TH14_')},EXPECTED)
        self.assertEqual(len(all_flags),len(set(all_flags.values())))
        for n,v in receipts.items():
            self.assertLess(v,0x920,n)
            self.assertFalse(0x500<=v<0x860,n)
            self.assertNotEqual(v,0x21,n)
        self.assertTrue({0x88f,0x8e3,0x4f9,0x4fa}.isdisjoint(receipts.values()))
        trainers = content['trainers']
        self.assertEqual([r['id'] for r in trainers],list(range(157,195)))
        self.assertEqual(len({r['constant'] for r in trainers}),38)
        self.assertEqual({r['constant']:r['id'] for r in trainers},
                         {n:v for n,v in state['trainers'].items() if n.startswith('TRAINER_TH14_')})
        maps = json.loads((ROOT/'tools/three_horizons/chapter14_maps.json').read_text())
        self.assertEqual([m['index'] for m in maps],list(range(37)))
        self.assertEqual(len({m['name'] for m in maps}),37)
        self.assertTrue(all(m['group']==76 and m['index']<128 for m in maps))

    def test_native_compiler_resolves_unused_aliases_and_trainer_bounds(self):
        header = (ROOT/'include/constants/three_horizons.h').read_text()
        for name,value in EXPECTED.items():
            self.assertIsNotNone(re.search(rf'^#define {name} FLAG_UNUSED_0x{value:03X}\b',header,re.M),name)
        lines = ['#include "constants/flags.h"','#include "constants/three_horizons.h"']
        for name,value in EXPECTED.items():
            lines.append(f'_Static_assert({name} == {value}, "{name}");')
        lines += ['_Static_assert(TRAINER_FLAGS_START == 0x500, "trainer start");',
                  '_Static_assert(SYSTEM_FLAGS == 0x860, "trainer capacity");',
                  '_Static_assert(DAILY_FLAGS_START == 0x920, "daily boundary");',
                  '_Static_assert(TH_STATE_VERSION_14 == 0xA90E, "marker");',
                  '_Static_assert(TH14_TRAINERS_START == 157 && TH14_TRAINERS_END == 194, "trainer range");']
        with tempfile.TemporaryDirectory(dir=ROOT) as td:
            src=Path(td)/'ownership.c'; obj=Path(td)/'ownership.o'
            src.write_text('\n'.join(lines),encoding='utf-8')
            result=subprocess.run(['gcc','-std=c11','-DTHREE_HORIZONS=1','-DIS_FRLG=0',
                '-I',str(ROOT/'include'),'-c',str(src),'-o',str(obj)],capture_output=True,text=True)
            self.assertEqual(result.returncode,0,result.stdout+result.stderr)

    def test_old_map_and_layout_ids_never_move(self):
        old=json.loads((ROOT/'tools/three_horizons/tests/playtest13-map-layout-baseline.json').read_text())
        groups=json.loads((ROOT/'data/maps/map_groups.json').read_text())
        actual={name:[gi,mi] for gi,g in enumerate(groups['group_order']) for mi,name in enumerate(groups[g])}
        for name,identity in old['maps'].items(): self.assertEqual(actual.get(name),identity,name)
        current=json.loads((ROOT/'data/layouts/layouts.json').read_text())['layouts']
        self.assertEqual(current[:len(old['layouts'])],old['layouts'])

    def test_claimed_flags_are_not_native_reset_ranges(self):
        native=(ROOT/'include/constants/flags.h').read_text()
        for name,value in EXPECTED.items():
            self.assertRegex(native,rf'FLAG_UNUSED_0x{value:03X}\s+',name)
        # Runtime reset APIs are exercised in the native state tests; never use
        # broad SYSTEM_FLAGS clearing just because the allocations live there.
        self.assertTrue(set(EXPECTED.values()).isdisjoint(range(0,0x20)))

if __name__ == '__main__': unittest.main()
