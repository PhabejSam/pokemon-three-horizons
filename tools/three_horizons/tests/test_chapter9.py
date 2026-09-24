import json
import unittest
from pathlib import Path

ROOT=Path(__file__).resolve().parents[3]

class Chapter9(unittest.TestCase):
    def test_chapter_maps_are_connected_and_owned(self):
        manifest=json.loads((ROOT/'tools/three_horizons/chapter9_maps.json').read_text())
        names=json.loads((ROOT/'tools/mapjson/three_horizons_maps.json').read_text())['maps']
        maps={m['id']:m for n in names for m in [json.loads((ROOT/'data/maps'/n/'map.json').read_text())]}
        graph={key:{w['dest_map'] for w in m['warp_events']} | {c['map'] for c in m['connections'] or []} for key,m in maps.items()}
        for start,end in [('MAP_TH_HOME_2F','MAP_TH_CERULEAN_GYM'),('MAP_TH_CERULEAN_GYM','MAP_TH_HOME_2F')]:
            seen=set();pending=[start]
            while pending:
                node=pending.pop()
                if node not in seen:
                    seen.add(node);pending.extend(graph[node]-seen)
            self.assertIn(end,seen)
        for entry in manifest['maps']:
            m=json.loads((ROOT/'data/maps'/entry['name']/'map.json').read_text())
            for o in m['object_events']:
                self.assertTrue(o['script'].startswith('TH_'),(entry['name'],o))
                self.assertTrue(o['flag']=='0' or o['flag'].startswith('FLAG_TH_'),o)
            self.assertFalse(any(e['type']=='hidden_item' for e in m['bg_events']))

    def test_pickups_have_unique_persistent_receipts(self):
        manifest=json.loads((ROOT/'tools/three_horizons/chapter9_maps.json').read_text())
        pickups=manifest['pickups']
        self.assertGreater(len(pickups),15)
        self.assertEqual(len(pickups),len({p['flag'] for p in pickups}))
        for p in pickups:
            m=json.loads((ROOT/'data/maps'/p['map']/'map.json').read_text())
            self.assertEqual(sum(o['flag']==p['flag'] for o in m['object_events']),1)

if __name__=='__main__': unittest.main()
