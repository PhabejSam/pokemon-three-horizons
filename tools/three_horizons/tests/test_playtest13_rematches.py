import re
import unittest
from tools.three_horizons.tests.test_playtest11_maps import ROOT

class Playtest13Rematches(unittest.TestCase):
    def test_keigo_progressed_roster_fits_route(self):
        text = (ROOT/'src/data/trainers.party').read_text()
        record = text.split('=== TRAINER_TH12_BUG_CATCHER_KEIGO ===', 1)[1].split('===', 1)[0]
        species_levels = re.findall(r'^([A-Za-z]+)\nLevel: (\d+)$', record, re.M)
        self.assertEqual(species_levels, [('Kakuna','18'), ('Beedrill','18'), ('Butterfree','18')])
        self.assertEqual(record.count('IVs: 0 HP / 0 Atk / 0 Def / 0 SpA / 0 SpD / 0 Spe'), 3)
        self.assertIn('Double Battle: No', record)
        self.assertNotIn('Ability:', record)  # Native species-appropriate ability.

if __name__ == '__main__':
    unittest.main()
