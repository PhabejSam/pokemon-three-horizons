import json
import unittest
from pathlib import Path

from tools.three_horizons.tests.test_playtest11_maps import map_data, tiles, reachable

ROOT = Path(__file__).resolve().parents[3]


class Playtest13Repairs(unittest.TestCase):
    def test_ship_official_is_on_dock_and_all_lanes_have_safe_retreats(self):
        data = map_data('TH12_VermilionCity')
        width, _, grid = tiles(data['name'])
        official = next(o for o in data['object_events'] if o['script'] == 'TH12_Ship_Board')
        # The documented boarding official is currently obscured by the pier
        # pillar, whose entry has collision bits set and a different elevation.
        tile = grid[official['y'] * width + official['x']]
        self.assertEqual(tile & 0xC00, 0)
        self.assertEqual(tile >> 12, official['elevation'])
        triggers = {(e['x'], e['y']) for e in data['coord_events']
                    if e['script'] == 'TH12_Ship_CheckTicket'}
        self.assertEqual(triggers, {(22, 33), (23, 33), (24, 33)})
        occupied = {(o['x'], o['y']) for o in data['object_events']}
        for x, y in triggers:
            self.assertNotIn((x, y), occupied)
            self.assertNotIn((x, y - 1), occupied)
            self.assertEqual(grid[(y - 1) * width + x] & 0xC00, 0)
            self.assertLessEqual(abs(x-official['x']) + abs(y-official['y']), 4)
            self.assertTrue(any(w['x'] == x and w['y'] == y + 1
                                and w['dest_map'] == 'MAP_TH12_SSANNE_EXTERIOR'
                                for w in data['warp_events']))

    def test_pewter_guide_is_outside_connection_camera_and_gate_covers_route(self):
        data = map_data('TH_Pewter')
        width, height, grid = tiles('TH_Pewter')
        guide = next(o for o in data['object_events'] if o['script'] == 'TH_PewterBadgeGuide')
        # The adjacent-map objects load at the connection. Keep the guide
        # beyond the visible half-screen then, rather than teleporting him.
        self.assertGreater((width - 1) - guide['x'], 8)
        floor = {(i % width, i // width) for i, value in enumerate(grid)
                 if value >> 12 == 3 and not value & 0xC00}
        self.assertIn((guide['x'], guide['y']), floor)
        objects = {(o['x'], o['y']) for o in data['object_events']}
        gate = {(e['x'], e['y']) for e in data['coord_events'] if e['script'] == 'TH_Route3BadgeGate'}
        exits = {(width - 1, y) for y in range(height)} & floor
        self.assertTrue(exits)
        self.assertFalse(reachable((37, 21), floor, objects | gate) & exits)
        self.assertTrue(exits <= reachable((37, 21), floor, objects))
        for x, y in gate & floor:
            self.assertLessEqual(abs(x-guide['x']) + abs(y-guide['y']), 5)

    def test_saffron_guards_cover_walkable_lanes_and_safe_retreats(self):
        for name, retreat_y, allowed_map in (
                ('TH12_Route5_SouthEntrance', 4, 'MAP_TH12_ROUTE5'),
                ('TH12_Route6_NorthEntrance', 6, 'MAP_TH12_ROUTE6')):
            data = map_data(name)
            width, _, grid = tiles(name)
            occupied = {(e['x'], e['y']) for e in data['object_events']}
            # Native guardhouse corridor; counter/background tiles elsewhere
            # cannot be classified from their collision bits alone.
            lanes = [3, 4, 5]
            self.assertEqual(sorted((e['x'], e['y']) for e in data['coord_events']),
                             [(x, 5) for x in lanes])
            for x in lanes:
                self.assertEqual(grid[5 * width + x] & 0xC00, 0)
                self.assertEqual(grid[retreat_y * width + x] & 0xC00, 0)
                self.assertNotIn((x, retreat_y), occupied)
            self.assertIn(allowed_map, [w['dest_map'] for w in data['warp_events']])
            self.assertFalse(any(w['dest_map'] == 'MAP_SAFFRON_CITY' for w in data['warp_events']))

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
