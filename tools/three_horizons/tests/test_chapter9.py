import json
import unittest
import struct
from collections import deque
from pathlib import Path

ROOT=Path(__file__).resolve().parents[3]

class Chapter9(unittest.TestCase):
    def test_misty_full_bag_still_checks_chapter_completion(self):
        script=(ROOT/'data/scripts/three_horizons/chapter9.inc').read_text()
        full=script.split('TH_MistyBagFull:')[1].split('TH_ChapterCheck:')[0]
        self.assertIn('call TH_ChapterCheck',full)

    def test_automatic_bridge_battle_selects_the_rival_object(self):
        script=(ROOT/'data/scripts/three_horizons/chapter9.inc').read_text()
        for name in ('Bulbasaur','Charmander','Squirtle','Chikorita','Cyndaquil',
                     'Totodile','Treecko','Torchic','Mudkip'):
            battle=script.split('TH_Rival_BRIDGE_'+name+'::')[1].split('\n\n')[0]
            self.assertIn('trainerbattle_lavaridge LOCALID_TH_CERULEAN_7,',battle)
        entry=script.split('TH_Rival_Bridge::')[1].split('TH_Rival_BRIDGE_Victory::')[0]
        self.assertNotIn('faceplayer',entry)

    def test_route4_has_a_walkable_return_to_mt_moon(self):
        raw=list(struct.unpack('<2160H',(ROOT/'data/layouts/Route4_Frlg/map.bin').read_bytes()))
        # Apply only the two reviewed TH-local stair replacements.
        script=(ROOT/'data/maps/TH_Route4/scripts.inc').read_text()
        for x,tile in [(91,'0x090'),(92,'0x091')]:
            self.assertIn(f'setmetatile {x}, 9, {tile}, FALSE',script)
            raw[9*108+x]=int(tile,16)
        pending=deque([(107,11)]);seen=set(pending)
        while pending:
            x,y=pending.popleft()
            for xx,yy in [(x+1,y),(x-1,y),(x,y+1),(x,y-1)]:
                if 0<=xx<108 and 0<=yy<20 and (xx,yy) not in seen and not raw[yy*108+xx]&0xc00:
                    seen.add((xx,yy));pending.append((xx,yy))
        self.assertIn((32,6),seen)

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
