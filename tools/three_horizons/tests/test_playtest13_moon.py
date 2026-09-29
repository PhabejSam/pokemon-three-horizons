"""The Moon circle closes without overlapping the guest or another dancer."""
import re
import unittest
from tools.three_horizons.tests.test_playtest11_maps import ROOT, map_data, tiles


class Playtest13Moon(unittest.TestCase):
    def test_moon_spacing_and_synchronized_circle(self):
        data = map_data('TH_MtMoonB2F')
        objects = {o['local_id']: o for o in data['object_events']}
        guest = objects['LOCALID_TH12_SIGHT_MAKUHITA']
        center = (guest['x'], guest['y'])
        source = (ROOT / 'data/scripts/three_horizons/chapter12_sightings.inc').read_text()
        width, _, grid = tiles(data['name'])
        paths = []
        for i in (1, 2, 3):
            obj = objects[f'LOCALID_TH12_SIGHT_CLEFAIRY{i}']
            start = (obj['x'], obj['y'])
            self.assertGreaterEqual(abs(start[0]-center[0]) + abs(start[1]-center[1]), 2,
                                    'Stationary Clefairy crowds the 32-pixel guest')
            body = source.split(f'TH12_Moon_Circle{i}:', 1)[1].split('step_end', 1)[0]
            steps = re.findall(r'walk_(up|down|left|right)', body)
            route = [start]
            for step in steps:
                dx, dy = {'up': (0,-1), 'down': (0,1), 'left': (-1,0), 'right': (1,0)}[step]
                x, y = route[-1][0]+dx, route[-1][1]+dy
                self.assertNotEqual((x,y), center)
                self.assertEqual(grid[y*width+x] & 0xC00, 0)
                route.append((x,y))
            self.assertEqual(route[-1], start)
            paths.append(route)
        self.assertEqual(len({len(p) for p in paths}), 1)
        for frame in zip(*paths):
            self.assertEqual(len(set(frame)), 3)


if __name__ == '__main__':
    unittest.main()
