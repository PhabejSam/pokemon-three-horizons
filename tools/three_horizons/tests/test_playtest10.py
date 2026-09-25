import json
import re
import struct
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]


class Playtest10(unittest.TestCase):
    def blocks(self, name):
        m = json.loads((ROOT / f'data/maps/{name}/map.json').read_text())
        layouts = json.loads((ROOT / 'data/layouts/layouts.json').read_text())['layouts']
        layout = next(l for l in layouts if l['id'] == m['layout'])
        raw = (ROOT / layout['blockdata_filepath']).read_bytes()
        return m, layout['width'], struct.unpack('<' + str(len(raw)//2) + 'H', raw)

    def test_rival_approach_and_departure_tiles_are_clear(self):
        script = (ROOT / 'data/scripts/three_horizons/chapter9.inc').read_text()
        for name, xs, ys, label, delta, count in [
            ('TH_Route22', [22], range(4, 7), 'TH_RivalApproachFromLeague', (1, 0), 6),
            ('TH_Cerulean', range(22, 25), [0], 'TH_RivalBridgeApproach', (0, 1), 3),
        ]:
            m, width, blocks = self.blocks(name)
            body = script.split(label + ':\n')[1].split('step_end')[0]
            self.assertEqual(int(re.search(r'\.rept (\d+)', body)[1]), count)
            occupied = {(o['x'], o['y']) for o in m['object_events'] if o['graphics_id'] != 'OBJ_EVENT_GFX_BLUE'}
            for x in xs:
                for y in ys:
                    for i in range(count + 1):
                        xx, yy = x + delta[0] * i, y + delta[1] * i
                        self.assertEqual(blocks[yy * width + xx] & 0xc00, 0, (name, xx, yy))
                        self.assertNotIn((xx, yy), occupied)

    def test_gym_trainers_have_clear_lines_to_the_walkway(self):
        m, width, blocks = self.blocks('TH_CeruleanGym')
        for local, dx in [('LOCALID_TH_CERULEANGYM_0', -1), ('LOCALID_TH_CERULEANGYM_1', 1)]:
            o = next(o for o in m['object_events'] if o['local_id'] == local)
            for i in range(3):
                self.assertEqual(blocks[o['y'] * width + o['x'] + dx * i] & 0xc00, 0)

    def test_center_has_no_unconfigured_placeholder_people(self):
        m = json.loads((ROOT / 'data/maps/TH_CeruleanCenter/map.json').read_text())
        self.assertFalse([o for o in m['object_events'] if o['graphics_id'] == '0'])

    def test_obsolete_pewter_demo_hosts_are_removed(self):
        m = json.loads((ROOT / 'data/maps/TH_Pewter/map.json').read_text())
        self.assertFalse([o for o in m['object_events'] if o['local_id'] in ('LOCALID_TH_PEWTER_4', 'LOCALID_TH_PEWTER_6')])

    def test_rewards_report_actual_destination(self):
        s = (ROOT / 'data/scripts/three_horizons/rewards.inc').read_text()
        self.assertNotIn('joined your party or', s)
        self.assertIn('MON_GIVEN_TO_PC', s)

    def test_cerulean_rocket_returns_dig_with_receipt(self):
        s = (ROOT / 'data/scripts/three_horizons/chapter9.inc').read_text()
        rocket = s.split('TH_Trainer9_TEAM_ROCKET_GRUNT_5::')[1].split('TH_Trainer9_TEAM_ROCKET_GRUNT_5_Intro:')[0]
        self.assertIn('giveitem ITEM_TM_DIG', rocket)
        self.assertIn('setflag FLAG_TH_DIG_TM', rocket)
        self.assertLess(rocket.index('goto_if_eq VAR_RESULT, FALSE'), rocket.index('setflag FLAG_TH_DIG_TM'))

    def test_museum_exhibits_describe_exhibits(self):
        s = (ROOT / 'data/scripts/three_horizons/chapter9_locals.inc').read_text()
        museum = s.split('TH_Local_PewterMuseum1F_0::')[1].split('TH_ViridianGym_Attendant::')[0]
        self.assertNotIn('respect this home', museum)


if __name__ == '__main__':
    unittest.main()
