import re
import json
import unittest
from tools.three_horizons.tests.test_playtest11_maps import ROOT, tiles, reachable

class Playtest13Rematches(unittest.TestCase):
    def test_vermilion_receipt_is_retryable_and_not_badge_gated(self):
        data = json.loads((ROOT/'data/maps/TH12_VermilionCity_PokemonCenter_1F/map.json').read_text())
        self.assertEqual(sum(o['script'] == 'TH13_VsSeekerResearcher' for o in data['object_events']), 1)
        w, h, cells = tiles('TH12_VermilionCity_PokemonCenter_1F')
        floor = {(i%w,i//w) for i,v in enumerate(cells) if v >> 12 == 3 and not v & 0xc00}
        obstacles = {(o['x'],o['y']) for o in data['object_events']}
        area = reachable((7,8), floor, obstacles)
        self.assertIn((5,7), area)
        self.assertIn((7,4), area)  # Reach the nurse across her counter at y=3.
        source = (ROOT/'data/scripts/three_horizons/chapter12_vermilion.inc').read_text()
        section = source.split('TH13_VsSeekerResearcher::', 1)[1]
        self.assertNotIn('FLAG_BADGE', section)
        self.assertIn('giveitem ITEM_VS_SEEKER', section)
        self.assertIn('goto_if_eq VAR_RESULT, FALSE, TH12_RewardBagFull', section)
        self.assertLess(section.index('goto_if_eq VAR_RESULT, FALSE'), section.index('setflag FLAG_TH13_VS_SEEKER'))

    def test_map_local_registry_covers_all_shipped_ordinary_trainers(self):
        text = (ROOT/'src/data/three_horizons_rematches.h').read_text()
        entries = re.findall(r'\{(TRAINER_TH\w+), (MAP_TH\w+), (\d+)\}', text)
        ids = dict(re.findall(r'#define (TRAINER_TH\w+) (\d+)', (ROOT/'include/constants/opponents.h').read_text()))
        expected = (set(range(1, 32)) - {7, 24, 29}) | (set(range(53, 94)) - {68}) | set(range(94,104))
        self.assertEqual({int(ids[t]) for t, m, l in entries}, expected)
        self.assertEqual(len(entries), 78)
        maps = {d['id']: d for p in (ROOT/'data/maps').glob('TH*/map.json') for d in [json.loads(p.read_text())]}
        sources = '\n'.join(p.read_text() for p in (ROOT/'data/scripts/three_horizons').glob('*.inc'))
        seen = set()
        for trainer, map_id, local in entries:
            self.assertTrue(1 <= int(local) <= 100)
            self.assertNotIn((map_id, local), seen)
            seen.add((map_id, local))
            objects = [o for i, o in enumerate(maps[map_id]['object_events'], 1) if str(i) == local]
            self.assertEqual(len(objects), 1)
            block = re.search(r'^'+re.escape(objects[0]['script'])+r':+\n(.*?)(?=^\w+:|\Z)', sources, re.M|re.S)
            self.assertIsNotNone(block)
            self.assertIn(trainer, block.group(1))

    def test_every_registered_trainer_has_rematch_script_without_story_rewards(self):
        entries = re.findall(r'\{(TRAINER_TH\w+), (MAP_TH\w+), (\d+)\}', (ROOT/'src/data/three_horizons_rematches.h').read_text())
        sources = '\n'.join(p.read_text() for p in (ROOT/'data/scripts/three_horizons').glob('*.inc'))
        for trainer, _, _ in entries:
            self.assertRegex(sources, r'trainerbattle_rematch '+trainer+r',')
        blocks = re.findall(r'^TH\w+_Rematch:+\n(.*?)(?=^\w+:|\Z)', sources, re.M|re.S)
        self.assertEqual(len(blocks), 78)
        for block in blocks:
            for one_time_command in ('giveitem', 'givemon', 'setflag', 'setvar', 'addmoney'):
                self.assertNotIn(one_time_command, block)

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
