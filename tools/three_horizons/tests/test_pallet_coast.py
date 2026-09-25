"""The demo must preserve Pallet's original coast and native southern neighbor."""
import json
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[3]

class PalletCoast(unittest.TestCase):
    def test_pallet_keeps_original_tiles_and_route21_connection(self):
        town = json.loads((ROOT/'data/maps/TH_Pallet/map.json').read_text())
        layouts = json.loads((ROOT/'data/layouts/layouts.json').read_text())['layouts']
        layout = next(l for l in layouts if l['id'] == town['layout'])
        self.assertEqual((layout['width'], layout['height']), (24, 20))
        self.assertEqual((ROOT/layout['blockdata_filepath']).read_bytes(),
                         (ROOT/'data/layouts/PalletTown_Frlg/map.bin').read_bytes())
        south = next(c for c in town['connections'] if c['direction'] == 'down')
        self.assertEqual(south['map'], 'MAP_TH_ROUTE21_SHORE')
        self.assertEqual(south['offset'], 0)
        shore = json.loads((ROOT/'data/maps/TH_Route21Shore/map.json').read_text())
        self.assertEqual(shore['layout'], 'LAYOUT_ROUTE21_NORTH')
        self.assertIn({'map': 'MAP_TH_PALLET', 'offset': 0, 'direction': 'up'}, shore['connections'])

if __name__ == '__main__':
    unittest.main()
