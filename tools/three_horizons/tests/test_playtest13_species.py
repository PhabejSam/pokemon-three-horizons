"""Release-source invariants that TESTING's all-species overrides cannot prove."""
import hashlib
import re
import unittest
from tools.three_horizons.tests.test_playtest11_maps import ROOT


class Playtest13Species(unittest.TestCase):
    def test_generated_teachable_conditionals_are_balanced(self):
        from tools.learnset_helpers.make_teaching_types import extract_repo_species_data
        depth = 0
        for entry in extract_repo_species_data():
            if isinstance(entry, str):
                if entry.startswith('#if'):
                    depth += 1
                elif entry.startswith('#endif'):
                    depth -= 1
                    self.assertGreaterEqual(depth, 0, 'Unmatched generated #endif')
        self.assertEqual(depth, 0)

    def test_release_generation_and_species_identity_configuration_is_unchanged(self):
        expected = {
            'include/config/species_enabled.h': '86a829d83a344bf23440a586706bf3c91ccef9a02c145afa0d1844c8824374eb',
            'include/constants/species.h': 'cd07f8773c77b41b9821ac030cbc3e0ef82cc6f0740efc7608afbf5ffe78ceaf',
            'include/constants/pokedex.h': 'f8dfa06feee06729bb33b29b2cf3ccdd267ed3211a7759b3b46b3a9fec978497',
        }
        for path, digest in expected.items():
            with self.subTest(path=path):
                self.assertEqual(hashlib.sha256((ROOT/path).read_text(encoding='utf-8').encode()).hexdigest(), digest)
        config = (ROOT/'include/config/species_enabled.h').read_text()
        self.assertEqual(len(re.findall(r'#define P_GEN_[1-9]_POKEMON\s+TRUE', config)), 9)
        self.assertRegex(config, r'#define P_CROSS_GENERATION_EVOS\s+TRUE')

    def test_species_changes_are_th_only_and_preserve_other_level_moves(self):
        source = (ROOT/'src/data/pokemon/species_info/gen_1_families.h').read_text()
        gyarados = source.split('[SPECIES_GYARADOS] =', 1)[1].split('[SPECIES_GYARADOS_MEGA]', 1)[0]
        self.assertRegex(gyarados, r'#if THREE_HORIZONS\s+\.types = MON_TYPES\(TYPE_WATER, TYPE_DRAGON\),\s+#else\s+\.types = MON_TYPES\(TYPE_WATER, TYPE_FLYING\),\s+#endif')
        th = (ROOT/'src/data/pokemon/level_up_learnsets/three_horizons.h').read_text()
        upstream = (ROOT/'src/data/pokemon/level_up_learnsets/gen_9.h').read_text()
        def moves(text, name):
            section = text.split(name + '[] = {', 1)[1].split('};', 1)[0]
            return {(int(level), move) for level, move in re.findall(r'LEVEL_UP_MOVE\(\s*(\d+), (MOVE_\w+)\)', section)}
        self.assertEqual(moves(th, 'sTHGyaradosLevelUpLearnset') - moves(upstream, 'sGyaradosLevelUpLearnset'),
                         {(26, 'MOVE_DRAGON_TAIL'), (48, 'MOVE_OUTRAGE')})
        self.assertTrue(moves(upstream, 'sGyaradosLevelUpLearnset') <= moves(th, 'sTHGyaradosLevelUpLearnset'))
        for target in ('ALAKAZAM', 'MACHAMP', 'GOLEM', 'GENGAR'):
            self.assertRegex(source, rf'#if THREE_HORIZONS\s+\{{EVO_LEVEL, 36, SPECIES_{target}\}},\s+#endif\s+\{{EVO_TRADE, 0, SPECIES_{target}\}}')


if __name__ == '__main__':
    unittest.main()
