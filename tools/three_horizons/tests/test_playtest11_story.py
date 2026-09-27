import json
import re
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]


class Playtest11Story(unittest.TestCase):
    def test_rival_battle_has_separate_player_win_and_loss_text(self):
        s = (ROOT / 'data/scripts/three_horizons/town.inc').read_text(encoding='utf-8')
        battles = re.findall(r'trainerbattle_earlyrival ([^\n]+)', s)
        self.assertEqual(len(battles), 9)
        for call in battles:
            self.assertTrue(call.endswith('TH_Text_BattlePlayerWon, TH_Text_BattlePlayerLost'))

    def test_fossils_have_independent_receipts(self):
        script = (ROOT / 'data/scripts/three_horizons/chapter9.inc').read_text(encoding='utf-8')
        for fossil in ('Dome', 'Helix'):
            body = script.split('TH_Fossil_' + fossil + '::')[1].split('TH_FossilChoose' + fossil + ':')[0]
            self.assertIn('goto_if_set FLAG_TH_FOSSIL_' + fossil.upper() + ',', body)
            self.assertNotIn('goto_if_set FLAG_TH_FOSSIL,', body)

    def test_researcher_cannot_be_bypassed_on_either_stair(self):
        m = json.loads((ROOT / 'data/maps/TH_MtMoonB2F/map.json').read_text())
        guarded = {(e['x'], e['y']) for e in m['coord_events'] if e['script'] == 'TH_FossilResearcherTrigger'}
        self.assertTrue({(13, 12), (14, 12)} <= guarded)

    def test_duo_encounter_keeps_exit_open_for_one_pokemon(self):
        p = ROOT / 'data/scripts/three_horizons/playtest11_story.inc'
        self.assertTrue(p.exists(), 'Duo event not installed')
        s = p.read_text(encoding='utf-8')
        guard = s.split('TH_RocketDuoTrigger::')[1].split('TH_RocketDuoBattle::')[0]
        self.assertIn('CountPartyAliveNonEggMons', guard)
        self.assertIn('TH_RocketDuoNeedTwo', guard)
        decline = s.split('TH_RocketDuoNeedTwo:')[1].split('TH_RocketDuoMeowth::')[0]
        self.assertNotIn('applymovement', decline)
        self.assertIn('releaseall', decline)

    def test_tutors_are_repeatable_and_use_real_move_selection(self):
        m = json.loads((ROOT / 'data/maps/TH_Route4/map.json').read_text())
        s = (ROOT / 'data/scripts/three_horizons/playtest11_story.inc').read_text(encoding='utf-8') if (ROOT / 'data/scripts/three_horizons/playtest11_story.inc').exists() else ''
        for label, move in [('TH_MegaPunchTutor', 'MOVE_MEGA_PUNCH'), ('TH_MegaKickTutor', 'MOVE_MEGA_KICK')]:
            self.assertTrue(any(o['script'] == label for o in m['object_events']))
            body = s.split(label + '::')[1].split('end')[0]
            self.assertIn(move, body)
            self.assertNotIn('setflag', body)
        self.assertIn('special ChooseMonForMoveTutor', s)


if __name__ == '__main__':
    unittest.main()
