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
        # P13 stages both stair lanes on the open floor above the steps.
        self.assertTrue({(13, 10), (14, 10)} <= guarded)

    def test_duo_has_single_fallback_and_requires_both_wins(self):
        s = (ROOT / 'data/scripts/three_horizons/playtest11_story.inc').read_text()
        self.assertIn('setvar VAR_0x8004, PARTY_SIZE\n    specialvar VAR_RESULT, CountPartyAliveNonEggMons_IgnoreVar0x8004Slot', s)
        self.assertIn('TH12_BeginRocketPair', s)
        self.assertIn('TH12_CompleteRocketPair', s)
        self.assertIn('trainerbattle_no_intro TRAINER_TH11_JESSIE', s)
        self.assertIn('trainerbattle_no_intro TRAINER_TH11_JAMES', s)
        self.assertNotIn('goto_if_defeated TRAINER_TH11_JESSIE, TH_RocketDuoVictory', s)
        singles = s.split('TH12_RocketSingles:')[1].split('TH_RocketDuoVictory::')[0]
        self.assertNotIn('HealPlayerParty', singles)
        self.assertNotIn('setflag FLAG_TH_ROCKET_DUO', singles)

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
