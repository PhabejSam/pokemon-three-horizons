"""Check approved move requirements, ordering and preservation of unrelated moves."""
import json
import re
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]

def learnset(text, species):
    match = re.search(r's'+species+r'LevelUpLearnset\[\] = \{(.*?)\};', text, re.S)
    if not match:
        return []
    return [(int(level), move) for level, move in re.findall(r'LEVEL_UP_MOVE\(\s*(\d+),\s*(MOVE_\w+)\)', match[1])]

class Starter12(unittest.TestCase):
    def test_requested_moves_and_unrelated_moves_are_available(self):
        requirements = json.loads((ROOT/'tools/three_horizons/starter12_requirements.json').read_text())
        original = (ROOT/'src/data/pokemon/level_up_learnsets/gen_9.h').read_text()
        new = ROOT/'src/data/pokemon/level_up_learnsets/three_horizons.h'
        active = new.read_text() if new.exists() else original
        for species, entries in requirements.items():
            actual = learnset(active, ('TH' if new.exists() else '')+species)
            with self.subTest(species=species):
                for entry in entries:
                    self.assertIn(tuple(entry), actual)
                moved = {move for level, move in entries}
                for old in learnset(original, species):
                    if old[1] not in moved:
                        self.assertIn(old, actual)
                self.assertEqual(sorted(level for level, move in actual), [level for level, move in actual])
                self.assertEqual(len(actual), len(set(actual)))
                self.assertTrue(all(0 <= level <= 100 for level, move in actual))

if __name__ == '__main__': unittest.main()
