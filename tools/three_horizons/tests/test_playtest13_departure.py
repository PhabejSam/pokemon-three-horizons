"""Departure staging stays on the existing dock and retains every old exit."""
import re
import unittest
from tools.three_horizons.tests.test_playtest11_maps import ROOT, map_data, tiles


class Playtest13Departure(unittest.TestCase):
    def test_warned_departure_preserves_exits_and_floor_staging(self):
        data = map_data('TH12_SSAnne_Exterior')
        self.assertEqual([(e['x'], e['y'], e['dest_warp_id']) for e in data['warp_events']],
                         [(31,5,'0'), (32,5,'1'), (32,14,'2'), (33,15,'3'), (33,5,'2')])
        triggers = {(e['x'], e['y']) for e in data['coord_events'] if e['script'] == 'TH13_Ship_FinalExit'}
        self.assertEqual(triggers, {(31,6),(32,6),(33,6)})
        width, _, grid = tiles(data['name'])
        source = (ROOT / 'data/scripts/three_horizons/chapter12_ship.inc').read_text()
        walk = source.split('TH13_Ship_ToViewingPoint:',1)[1].split('step_end',1)[0]
        moves = re.findall(r'walk_(up|down|left|right)', walk)
        pos = (32,6)
        for direction in moves:
            dx,dy = {'up':(0,-1),'down':(0,1),'left':(-1,0),'right':(1,0)}[direction]
            pos = pos[0]+dx, pos[1]+dy
            self.assertEqual(grid[pos[1]*width+pos[0]] & 0xC00,0)
        self.assertEqual(pos,(32,13))
        scene = source.split('TH13_Ship_DepartNow:',1)[1].split('TH13_Ship_',1)[0]
        self.assertIn('special DoSSAnneDepartureCutscene',scene)
        self.assertLess(scene.index('waitstate'),scene.index('setflag FLAG_TH13_SHIP_DEPARTED'))
        self.assertIn('warp MAP_TH12_VERMILION_CITY, 23, 32',scene)
        self.assertNotIn('giveitem',scene)
        self.assertNotIn('staying in port',source)
        self.assertNotIn('welcome aboard any time',source.lower())


if __name__ == '__main__':
    unittest.main()
