"""Check real scripted walk tiles against the native collision map and player."""
import json
from pathlib import Path
import re
import struct
import unittest

ROOT = Path(__file__).resolve().parents[3]

class JoeyPaths(unittest.TestCase):
    def path(self, label, start):
        script = (ROOT / 'data/scripts/three_horizons/town.inc').read_text()
        body = script.split(label + ':\n', 1)[1].split('    step_end', 1)[0]
        x, y = start
        points = []
        for step in re.findall(r'walk_(\w+)', body):
            dx, dy = {'up': (0, -1), 'down': (0, 1), 'left': (-1, 0), 'right': (1, 0)}[step]
            x += dx
            y += dy
            points.append((x, y))
        return points

    def test_invitation_and_battle_exits_do_not_cross_adjacent_player(self):
        blocks = struct.unpack('<480H', (ROOT / 'data/layouts/PalletTown_Frlg/map.bin').read_bytes())
        initial = json.loads((ROOT / 'data/maps/TH_Pallet/map.json').read_text())['object_events'][0]
        self.assertEqual((initial['x'], initial['y']), (7, 9))
        for start, regular, alternative, end, dodge in [
            ((7, 9), 'TH_Movement_RobinToLab', 'TH_Movement_JoeyAroundPlayer', (16, 13), (8, 9)),
            ((17, 14), 'TH_Movement_JoeyToRoute', 'TH_Movement_JoeyAroundSouth', (12, 0), (17, 15)),
        ]:
            for dx, dy in ((0, -1), (0, 1), (-1, 0), (1, 0)):
                player = (start[0] + dx, start[1] + dy)
                path = self.path(alternative if player == dodge else regular, start)
                self.assertNotIn(player, path)
                self.assertEqual(path[-1], end)
                for x, y in path[:-1]:
                    self.assertEqual(blocks[y * 24 + x] & 0xC00, 0, (regular, x, y))

if __name__ == '__main__':
    unittest.main()
