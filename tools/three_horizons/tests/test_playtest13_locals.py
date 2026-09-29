"""Bounded scene geometry and interaction contracts for the local polish pass."""
import unittest
from collections import deque
from tools.three_horizons.tests.test_playtest11_maps import ROOT, map_data, tiles


class Playtest13Locals(unittest.TestCase):
    def test_farfetchd_companion_has_reachable_floor_and_cry(self):
        data = map_data('TH12_VermilionCity_House2')
        birds = [o for o in data['object_events'] if o['graphics_id'] == 'OBJ_EVENT_GFX_SPECIES(FARFETCHD)']
        self.assertEqual(len(birds), 1, 'Leek companion is mentioned but invisible')
        bird = birds[0]
        human = data['object_events'][0]
        self.assertEqual(human['local_id'], 'LOCALID_TH12_VERMILIONCITY_HOUSE2_0')
        self.assertEqual(abs(bird['x'] - human['x']) + abs(bird['y'] - human['y']), 1)
        self.assertNotEqual(bird['local_id'], human['local_id'])
        width, height, grid = tiles(data['name'])
        occupied = {(o['x'], o['y']) for o in data['object_events']}
        self.assertEqual(grid[bird['y'] * width + bird['x']] & 0xC00, 0)
        self.assertEqual(grid[bird['y'] * width + bird['x']] >> 12, bird['elevation'])
        visited = set()
        queue = deque([(4, 6)])
        while queue:
            x, y = queue.popleft()
            if (x, y) in visited or (x, y) in occupied:
                continue
            if not (0 <= x < width and 0 <= y < height) or grid[y * width + x] & 0xC00:
                continue
            visited.add((x, y))
            queue.extend([(x+1, y), (x-1, y), (x, y+1), (x, y-1)])
        for obj in (bird, human):
            self.assertTrue(any(abs(x-obj['x']) + abs(y-obj['y']) == 1 for x, y in visited))
        for warp in data['warp_events']:
            self.assertIn((warp['x'], warp['y']), visited)
        source = (ROOT / 'data/scripts/three_horizons/chapter12_locals.inc').read_text()
        body = source.split(bird['script'] + '::', 1)[1].split('\n\n', 1)[0]
        self.assertIn('playmoncry SPECIES_FARFETCHD, CRY_MODE_NORMAL', body)
        self.assertIn('waitmoncry', body)
        self.assertLessEqual(len(data['object_events']) + 2, 16)


if __name__ == '__main__':
    unittest.main()
