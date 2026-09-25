import json
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]

class Playtest8(unittest.TestCase):
    def test_regional_displays_survive_two_starter_choices(self):
        script = (ROOT/'data/scripts/three_horizons/lab.inc').read_text()
        self.assertNotIn('removeobject VAR_0x800A', script)
        for flag in (3, 4, 5):
            self.assertNotIn(f'setflag FLAG_TEMP_{flag}', script)

    def test_follower_refresh_is_after_the_handoff(self):
        script = (ROOT/'data/scripts/three_horizons/lab.inc').read_text()
        sendoff = script.split('TH_OakAfterSupplies:', 1)[1].split('TH_Lab_BagFull:', 1)[0]
        self.assertLess(sendoff.index('call TH_Lab_OakReturn'), sendoff.index('special TH_RefreshFollower'))

    def test_center_healing_uses_machine_and_no_indoor_popup(self):
        script = (ROOT/'data/scripts/three_horizons/journey.inc').read_text()
        nurse = script.split('TH_Journey_Nurse::', 1)[1].split('TH_EventScript_CenterRecovery::', 1)[0]
        self.assertIn('dofieldeffect FLDEFF_POKECENTER_HEAL', nurse)
        self.assertIn('waitfieldeffect FLDEFF_POKECENTER_HEAL', nurse)
        for name in ('TH_ViridianCenter', 'TH_PewterCenter'):
            self.assertFalse(json.loads((ROOT/f'data/maps/{name}/map.json').read_text())['show_map_name'])

    def test_npcs_no_longer_share_placeholder(self):
        for path in (ROOT/'data/maps').glob('TH_*/map.json'):
            for obj in json.loads(path.read_text()).get('object_events', []):
                self.assertNotEqual(obj.get('script'), 'TH_Journey_Local', str(path))

if __name__ == '__main__':
    unittest.main()
