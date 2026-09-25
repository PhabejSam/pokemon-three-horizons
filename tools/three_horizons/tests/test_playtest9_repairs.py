"""Check the playable lab approach against the actual collision map."""
import json
import struct
import unittest
from test_rival_scenes import ROOT, movement


class Playtest9Repairs(unittest.TestCase):
    def test_lab_welcome_reaches_rival(self):
        script = (ROOT / 'data/scripts/three_horizons/lab.inc').read_text()
        path = movement(script, 'TH_Lab_IntroApproach', (6, 12))
        objects = json.loads((ROOT / 'data/maps/TH_OaksLab/map.json').read_text())['object_events']
        occupied = {(o['x'], o['y']) for o in objects}
        blocks = struct.unpack('<182H', (ROOT / 'data/layouts/PalletTown_ProfessorOaksLab_Frlg/map.bin').read_bytes())
        self.assertEqual(path[-1], (5, 5))
        for x, y in path:
            self.assertNotIn((x, y), occupied)
            self.assertEqual(blocks[y * 13 + x] & 0xc00, 0)

