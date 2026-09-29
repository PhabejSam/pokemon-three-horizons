import unittest
from tools.three_horizons.export_encounters import render

class EncounterGuide(unittest.TestCase):
    def test_playtest13_includes_extension_and_ghost_limit(self):
        text = render('exact-feature', playtest=13)
        self.assertIn('# Playtest 13 encounter checklist', text)
        self.assertIn('`exact-feature`', text)
        for area in ('Route 9', 'Route 10', 'Route 11', 'Digletts Cave', 'Rock Tunnel', 'Pokemon Tower'):
            self.assertIn(area, text)
        for species in ('Mareep', 'Aron', 'Dunsparce', 'Phanpy', 'Whismur'):
            self.assertIn(species, text)
        self.assertIn('unidentified', text)
        self.assertIn('cannot be caught', text)
        self.assertIn('does not guarantee', text)
        self.assertIn('Visible research-scene', text)

    def test_default_remains_playtest12_without_native_or_future_leak(self):
        text = render('legacy-feature')
        self.assertEqual(text, render('legacy-feature', playtest=12))
        self.assertIn('# Playtest 12 encounter checklist', text)
        self.assertNotIn('Rock Tunnel', text)
        self.assertNotIn('Pokemon Tower', text)
        self.assertNotIn('Petalburg', text)
        self.assertNotIn('Celadon', text)

if __name__ == '__main__':
    unittest.main()
