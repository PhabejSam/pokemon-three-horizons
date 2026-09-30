"""Dialogue roles and preserved Rocket encounter commands."""
import re
import unittest
from tools.three_horizons.tests.test_playtest11_maps import ROOT


class Playtest13Rocket(unittest.TestCase):
    def test_individual_rocket_records_do_not_force_double_battles(self):
        source = (ROOT / 'src/data/trainers.party').read_text()
        for trainer in ('JESSIE', 'JAMES'):
            block = source.split('=== TRAINER_TH11_' + trainer + ' ===', 1)[1].split('===', 1)[0]
            self.assertNotIn('Double Battle: Yes', block)
        # Their paired script still explicitly starts the two-trainer encounter.
        script = (ROOT / 'data/scripts/three_horizons/playtest11_story.inc').read_text()
        self.assertIn('TH_RocketDuoTooFew, TRUE, TRUE', script)

    def test_james_introduces_singles_and_jessie_hands_over(self):
        source = (ROOT / 'data/scripts/three_horizons/playtest11_story.inc').read_text()
        def dialogue(label):
            return re.search(r'^' + label + r':+\s*\.string "([^"\n]+)"', source, re.M).group(1)
        for label in ('TH12_RocketSingleIntro', 'TH_RocketDuoIntro'):
            text = dialogue(label)
            for speaker in ('JESSIE:', 'JAMES:', 'MEOWTH:'):
                self.assertIn(speaker, text)
        single = source.split('TH12_RocketSingles:',1)[1].split('TH_RocketDuoVictory::',1)[0]
        battles = re.findall(r'trainerbattle_no_intro (\w+), (\w+)', single)
        self.assertEqual([b[0] for b in battles], ['TRAINER_TH11_JESSIE', 'TRAINER_TH11_JAMES'])
        defeat = dialogue(battles[0][1])
        self.assertIn('JAMES', defeat)
        self.assertNotIn('fell apart', defeat)
        self.assertNotIn('HealPlayerParty', single)
        self.assertNotIn('setflag', single)
        self.assertNotIn('CompleteRocketPair', single)
        self.assertIn('msgbox TH12_RocketSingleSecond', single)
        self.assertIn('blasting off again', dialogue('TH_RocketDuoExit'))


if __name__ == '__main__':
    unittest.main()
