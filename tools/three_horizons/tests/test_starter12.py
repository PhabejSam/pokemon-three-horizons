"""Check approved move requirements, ordering and preservation of unrelated moves."""
import json
import re
import unittest
import importlib.util
import os
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]

def learnset(text, species):
    match = re.search(r's'+species+r'LevelUpLearnset\[\] = \{(.*?)\};', text, re.S)
    if not match:
        return []
    return [(int(level), move) for level, move in re.findall(r'LEVEL_UP_MOVE\(\s*(\d+),\s*(MOVE_\w+)\)', match[1])]

class Starter12(unittest.TestCase):
    def test_teachable_generator_keeps_balanced_family_guards(self):
        spec = importlib.util.spec_from_file_location('teaching_types', ROOT/'tools/learnset_helpers/make_teaching_types.py')
        module = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(module)
        previous = os.getcwd()
        try:
            os.chdir(ROOT)
            entries = module.extract_repo_species_data()
        finally:
            os.chdir(previous)
        depth = 0
        for entry in entries:
            if not isinstance(entry, str):
                continue
            if entry.startswith('#if'):
                depth += 1
            elif entry.startswith('#endif'):
                depth -= 1
                self.assertGreaterEqual(depth, 0, entry)
        self.assertEqual(depth, 0)

    def test_requested_moves_and_unrelated_moves_are_available(self):
        requirements = json.loads((ROOT/'tools/three_horizons/starter12_requirements.json').read_text())
        original = (ROOT/'src/data/pokemon/level_up_learnsets/gen_9.h').read_text()
        new = ROOT/'src/data/pokemon/level_up_learnsets/three_horizons.h'
        active = new.read_text() if new.exists() else original
        for species, entries in requirements.items():
            # Approved P13 Task29 explicitly replaces only Typhlosion's L40
            # Earthquake. Keep the historical P12 requirements file intact.
            replaced = set()
            if new.exists() and species == 'Typhlosion':
                self.assertIn([40, 'MOVE_EARTHQUAKE'], entries)
                entries = [[40, 'MOVE_EARTH_POWER'] if e == [40, 'MOVE_EARTHQUAKE'] else e for e in entries]
                replaced.add('MOVE_EARTHQUAKE')
            actual = learnset(active, ('TH' if new.exists() else '')+species)
            with self.subTest(species=species):
                for entry in entries:
                    self.assertIn(tuple(entry), actual)
                moved = {move for level, move in entries} | replaced
                for old in learnset(original, species):
                    if old[1] not in moved:
                        self.assertIn(old, actual)
                self.assertEqual(sorted(level for level, move in actual), [level for level, move in actual])
                self.assertEqual(len(actual), len(set(actual)))
                self.assertTrue(all(0 <= level <= 100 for level, move in actual))

if __name__ == '__main__': unittest.main()
