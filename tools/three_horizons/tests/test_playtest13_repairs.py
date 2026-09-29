import json
import unittest
from pathlib import Path

from tools.three_horizons.tests.test_playtest11_maps import map_data, tiles

ROOT = Path(__file__).resolve().parents[3]


class Playtest13Repairs(unittest.TestCase):
    def test_daycare_warps_are_reciprocal(self):
        outside = map_data('TH12_Route5')
        doorway = outside['warp_events'][1]
        self.assertEqual((doorway['x'], doorway['y']), (23, 25))
        self.assertEqual(doorway['dest_map'], 'MAP_TH13_ROUTE5_POKEMON_DAY_CARE')
        self.assertEqual(int(doorway['dest_warp_id']), 1)
        inside = map_data('TH13_Route5_PokemonDayCare')
        self.assertEqual([(w['x'], w['y']) for w in inside['warp_events']], [(3, 7), (4, 7), (5, 7)])
        for exit in inside['warp_events']:
            self.assertEqual(exit['dest_map'], outside['id'])
            self.assertEqual(int(exit['dest_warp_id']), 1)
        underground = outside['warp_events'][0]
        self.assertEqual((underground['x'], underground['y']), (31, 31))
        self.assertEqual(underground['dest_map'], 'MAP_TH12_UNDERGROUND_PATH_NORTH_ENTRANCE')
        self.assertEqual(int(underground['dest_warp_id']), 1)
        width, _, data = tiles('TH12_Route5')
        self.assertEqual(data[26 * width + 23] & 0xC00, 0)
        self.assertFalse(any((e['x'], e['y']) == (23, 25) for e in outside['bg_events']))
        self.assertNotIn('setmetatile 23, 25, 664', (ROOT/'data/maps/TH12_Route5/scripts.inc').read_text())
        width, _, data = tiles(inside['name'])
        for x in (3, 4, 5):
            self.assertEqual(data[6 * width + x] & 0xC00, 0)

    def test_daycare_is_appended_without_reindexing_p12(self):
        names = json.loads((ROOT/'tools/mapjson/three_horizons_maps.json').read_text())['maps']
        baseline = json.loads((ROOT/'tools/three_horizons/tests/playtest12-map-indices.json').read_text())
        old_th = [name for name, index in baseline.items() if index[0] == 75]
        old_th.sort(key=lambda name: baseline[name][1])
        self.assertEqual(names[:len(old_th)], old_th)
        self.assertIn('TH13_Route5_PokemonDayCare', names[len(old_th):])

    def test_daycare_map_is_selected_only_for_th(self):
        from tools.three_horizons.tests.test_map_contract import MapContract
        generator = MapContract()
        for version in ('emerald', 'firered', 'three_horizons'):
            result = generator.generate('groups', version)
            self.assertEqual('\t.4byte TH13_Route5_PokemonDayCare\n' in result['groups.inc'],
                             version == 'three_horizons', version)


if __name__ == '__main__':
    unittest.main()
