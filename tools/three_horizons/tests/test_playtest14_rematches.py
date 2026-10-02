"""Approved trainer/slot contracts; no source-wide stone evolution shortcut."""
import hashlib
import json
import re
import unittest
from pathlib import Path
ROOT = Path(__file__).resolve().parents[3]
EXPECTED = json.loads((Path(__file__).with_name('playtest14-rematch-contract.json')).read_text())

class Playtest14Rematches(unittest.TestCase):
    def test_exact_25_evolution_keys_and_manifest(self):
        source = (ROOT/'src/data/three_horizons_rematches.h').read_text()
        pattern = r'\{(TRAINER_\w+), (\d+), (SPECIES_\w+), (SPECIES_\w+), (\d+), (\d+)\}'
        rows = [dict(zip(('trainerId','partySlot','baseSpecies','evolvedSpecies','minLevel','minBadges'),
                (a,int(b),c,d,int(e),int(f)))) for a,b,c,d,e,f in re.findall(pattern,source)]
        self.assertEqual(rows,EXPECTED)
        self.assertEqual(len({(r['trainerId'],r['partySlot']) for r in rows}),25)
        content = json.loads((ROOT/'tools/three_horizons/chapter14_content.json').read_text())
        self.assertEqual(content['rematchEvolutions'],EXPECTED)

    def test_existing_first_parties_byte_identical(self):
        baseline = json.loads((Path(__file__).with_name('playtest13-first-parties-baseline.json')).read_text())
        source = (ROOT/'src/data/trainers.party').read_text()
        # The immutable snapshot includes the trailing #endif in the last old
        # record. Remove ONLY new records to reconstruct that original boundary.
        source = re.sub(r'^=== TRAINER_TH14_\w+ ===\n.*?(?=^=== |^#endif|\Z)', '', source, flags=re.M|re.S)
        current = {a:hashlib.sha256(b.encode()).hexdigest()
            for a,b in re.findall(r'^=== (TRAINER_TH\w+) ===\n(.*?)(?=^=== |\Z)',source,re.M|re.S)}
        self.assertGreaterEqual(len(baseline),156)
        for name,digest in baseline.items(): self.assertEqual(current.get(name),digest,name)

    def test_one_bounded_twins_alias_is_map_scoped(self):
        source = (ROOT/'src/data/three_horizons_rematches.h').read_text()
        self.assertTrue('sRematchAliases[] = {' in source, 'missing bounded alias table')
        aliases = source.split('sRematchAliases[] = {',1)[1].split('};',1)[0]
        self.assertRegex(aliases,r'\{TRAINER_TH14_ROUTE8_ELI_ANNE, MAP_TH14_ROUTE8, 13, 12\}')
        self.assertEqual(aliases.count('TRAINER_TH14_ROUTE8_ELI_ANNE'),1)
        maps = json.loads((ROOT/'tools/three_horizons/chapter14_maps.json').read_text())
        self.assertEqual((maps[0]['name'],maps[0]['group'],maps[0]['index']),('TH14_Route8',76,0))
        # Explicit identity data, never infer a trainer from class/name.
        code = (ROOT/'src/three_horizons_rematches.c').read_text()
        self.assertIn('TH14_ResolveMapTrainer',code)
        self.assertIn('CreateRematchParty(party, GetTrainerStructFromId(trainerId), trainerId,',code)
        self.assertIn('CreateRematchParty(party, trainer, TRAINER_NONE,',code)

    def test_reset_and_upstream_guards_remain_connected(self):
        for path in ('src/three_horizons_rematches.c','src/vs_seeker.c'):
            self.assertIn('#if THREE_HORIZONS',(ROOT/path).read_text())
        for path in ('src/overworld.c','src/battle_setup.c','src/item_use.c'):
            self.assertIn('TH13_ResetRematches()', (ROOT/path).read_text())
        rematches=(ROOT/'src/three_horizons_rematches.c').read_text()
        self.assertNotIn('SetTrainerFlag(',rematches)
        self.assertNotIn('ClearTrainerFlag(',rematches)
        self.assertIn('gSaveBlock1Ptr->trainerRematches[slot] = 1;',rematches)

if __name__ == '__main__': unittest.main()
