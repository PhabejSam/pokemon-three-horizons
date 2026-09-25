"""Check persistent slot ownership independently of map or UI behavior."""
import json
import re
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]

class StateAllocations(unittest.TestCase):
    def test_new_slots_match_manifest_and_preserve_existing_state(self):
        manifest=json.loads((ROOT/'tools/three_horizons/state_manifest.json').read_text())
        header=(ROOT/'include/constants/three_horizons.h').read_text()
        definitions=dict(re.findall(r'^#define\s+(\w+)\s+(\w+)',header,re.M))
        def value(token):
            if token.startswith('FLAG_UNUSED_0x'): return int(token.split('_')[-1],16)
            if token in definitions: return value(definitions[token])
            return int(token,0)
        for category in ('variables','flags','pickups'):
            for name,expected in manifest[category].items():
                expected=int(expected,0) if isinstance(expected,str) else expected
                self.assertEqual(value(name),expected,name)
                self.assertNotEqual(expected,0,name)
        variables=[value(n) for n in definitions if n.startswith('VAR_TH_')]
        flags=[value(n) for n in definitions if n.startswith('FLAG_TH_') and 'HIDE_ROBIN' not in n]
        self.assertEqual(len(variables),len(set(variables)))
        self.assertEqual(len(flags),len(set(flags)))
        for offset,name in enumerate(('STAGE','FIRST_PARTNER','RIVAL_PARTNER','SUPPLY_MASK',
                                    'SIGHTING_SEEN','OUTFIT','EXP_RATE','AUTO_RUN','FOLLOWER_OFF')):
            self.assertEqual(value('VAR_TH_'+name),0x40f7+offset)
        trainers=list(manifest['trainers'].values())
        self.assertEqual(len(trainers),len(set(trainers)))
        self.assertTrue(all(8<=i<855 for i in trainers))

    def test_allocated_native_aliases_have_no_other_runtime_users(self):
        manifest=json.loads((ROOT/'tools/three_horizons/state_manifest.json').read_text())
        aliases={f'VAR_UNUSED_0x{v:04X}' for v in manifest['variables'].values()}
        aliases.update(f'FLAG_UNUSED_0x{(int(v,0) if isinstance(v,str) else v):03X}'
                       for category in ('flags','pickups') for v in manifest[category].values())
        matcher=re.compile(r'\b(?:'+ '|'.join(sorted(aliases)) +r')\b')
        for folder in ('src','data'):
            for path in (ROOT/folder).rglob('*'):
                if path.suffix in ('.c','.h','.inc','.json'):
                    self.assertIsNone(matcher.search(path.read_text(encoding='utf-8')),str(path.relative_to(ROOT)))

if __name__=='__main__': unittest.main()
