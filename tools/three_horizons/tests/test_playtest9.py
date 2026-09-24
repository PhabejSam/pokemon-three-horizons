import json
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]

class Playtest9(unittest.TestCase):
    def test_healing_hides_follower_until_party_is_healed(self):
        script = (ROOT/'data/scripts/three_horizons/journey.inc').read_text()
        nurse = script.split('TH_Journey_Nurse::')[1].split('TH_EventScript_CenterRecovery::')[0]
        self.assertIn('hidefollower TRUE', nurse)
        self.assertLess(nurse.index('hidefollower TRUE'), nurse.index('dofieldeffect'))
        self.assertLess(nurse.index('special HealPlayerParty'), nurse.index('special TH_RefreshFollower'))

    def test_new_chapter_preserves_original_map_order(self):
        maps=json.loads((ROOT/'tools/mapjson/three_horizons_maps.json').read_text())['maps']
        self.assertEqual(maps[:3], ['TH_Home2F','TH_Home1F','TH_Pallet'])
        for name in ('TH_Route22','TH_Route3','TH_Route4','TH_MtMoon1F',
                     'TH_MtMoonB1F','TH_MtMoonB2F','TH_Cerulean','TH_CeruleanGym'):
            self.assertIn(name, maps)

if __name__ == '__main__':
    unittest.main()
