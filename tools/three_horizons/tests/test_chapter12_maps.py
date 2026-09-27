import json
import re
import unittest
from pathlib import Path

ROOT=Path(__file__).resolve().parents[3]
def read(path): return json.loads((ROOT/path).read_text())

class Chapter12Maps(unittest.TestCase):
    def test_hiding_bill_clefairy_does_not_complete_rescue(self):
        m=read('data/maps/TH12_Route25_SeaCottage/map.json')
        self.assertEqual(m['object_events'][1]['flag'],'FLAG_TEMP_4')
        text=(ROOT/'data/scripts/three_horizons/chapter12_bill.inc').read_text()
        entry=text.split('TH12_Bill_OnEntry::')[1].split('TH12_Bill_Rescue::')[0]
        self.assertIn('clearflag FLAG_TEMP_4',entry)
        self.assertIn('setflag FLAG_TEMP_4',entry)
        rescue=text.split('TH12_Bill_Rescue::')[1].split('TH12_Bill_Computer::')[0]
        self.assertNotIn('setflag FLAG_TH12_BILL_RESCUED',rescue)

    def test_bill_human_is_hidden_until_teleporter_release(self):
        m=read('data/maps/TH12_Route25_SeaCottage/map.json')
        self.assertEqual(m['object_events'][0]['flag'], 'FLAG_TEMP_3')
        text=(ROOT/'data/scripts/three_horizons/chapter12_bill.inc').read_text()
        entry=text.split('TH12_Bill_OnEntry::')[1].split('TH12_Bill_Rescue::')[0]
        self.assertIn('setflag FLAG_TEMP_3',entry)
        self.assertIn('TH12_Bill_EntryDone:\n    clearflag FLAG_TEMP_3',entry)
        self.assertIn('clearflag FLAG_TEMP_3\n    addobject LOCALID_TH12_ROUTE25_SEACOTTAGE_0',text)

    def test_vermilion_and_every_ship_room_are_connected_to_cerulean(self):
        names=read('tools/mapjson/three_horizons_maps.json')['maps']
        expected=['TH12_Route5','TH12_Route6','TH12_UndergroundPath_NorthSouthTunnel','TH12_VermilionCity']
        expected += ['TH12_'+p.name.removesuffix('_Frlg') for p in (ROOT/'data/maps').glob('SSAnne_*_Frlg')]
        expected += ['TH12_VermilionCity_Gym']
        for name in expected: self.assertIn(name,names)
        maps={read(f'data/maps/{n}/map.json')['id']:read(f'data/maps/{n}/map.json') for n in names}
        def reachable(start):
            seen=set(); pending=[start]
            while pending:
                node=pending.pop()
                if node in seen: continue
                seen.add(node)
                m=maps[node]
                pending.extend([c['map'] for c in m['connections'] or []]+[w['dest_map'] for w in m['warp_events']])
            return seen
        outward=reachable('MAP_TH_CERULEAN')
        for name in expected:
            mid=read(f'data/maps/{name}/map.json')['id']
            self.assertIn(mid,outward)
            self.assertIn('MAP_TH_CERULEAN',reachable(mid))

    def test_ship_rival_stands_on_floor_and_covers_captain_approaches(self):
        import struct
        m=read('data/maps/TH12_SSAnne_2F_Corridor/map.json')
        layout=next(l for l in read('data/layouts/layouts.json')['layouts'] if l['id']==m['layout'])
        w=layout['width']; data=struct.unpack('<'+'H'*(w*layout['height']),(ROOT/layout['blockdata_filepath']).read_bytes())
        rival=m['object_events'][0]
        self.assertEqual(data[rival['y']*w+rival['x']] & 0xC00,0)
        triggers={(e['x'],e['y']) for e in m['coord_events'] if e['script']=='TH12_Ship_RivalTrigger'}
        self.assertTrue({(30,6),(31,6),(32,6)} <= triggers)

    def test_bill_exit_does_not_walk_through_desk_or_computer_user(self):
        import struct
        m=read('data/maps/TH12_Route25_SeaCottage/map.json')
        l=next(l for l in read('data/layouts/layouts.json')['layouts'] if l['id']==m['layout'])
        w=l['width'];d=struct.unpack('<'+'H'*(w*l['height']),(ROOT/l['blockdata_filepath']).read_bytes())
        text=(ROOT/'data/scripts/three_horizons/chapter12_bill.inc').read_text()
        x,y=3,3
        for label in ['TH12_Bill_FromMachine','TH12_Bill_ToRoom']:
            body=text.split(label+':\n')[1].split('    step_end')[0]
            for step in re.findall(r'walk_(\w+)',body):
                dx,dy={'up':(0,-1),'down':(0,1),'left':(-1,0),'right':(1,0)}[step];x+=dx;y+=dy
                self.assertEqual(d[y*w+x]&0xC00,0,(x,y))
                self.assertNotEqual((x,y),(4,6))
        self.assertEqual((x,y),(7,5))

    def test_surge_remains_reachable_after_trainer_approaches(self):
        from itertools import product
        from tools.three_horizons.tests.test_playtest11_maps import tiles,reachable
        m=read('data/maps/TH12_VermilionCity_Gym/map.json')
        w,h,data=tiles(m['name'])
        floor={(i%w,i//w) for i,v in enumerate(data) if not v&0xC00}
        floor.update((x,y) for x in (4,5,6) for y in (6,7))
        options=[]
        directions={'MOVEMENT_TYPE_FACE_LEFT':[(-1,0)],'MOVEMENT_TYPE_LOOK_AROUND':[(1,0),(-1,0),(0,1),(0,-1)]}
        for o in m['object_events']:
            pos=(o['x'],o['y']);ends={pos:[]}
            if o['trainer_type']=='TRAINER_TYPE_NORMAL':
                for dx,dy in directions[o['movement_type']]:
                    for distance in range(1,int(o['trainer_sight_or_berry_tree_id'])+1):
                        player=(pos[0]+dx*distance,pos[1]+dy*distance)
                        if all((pos[0]+dx*i,pos[1]+dy*i) in floor for i in range(1,distance+1)):
                            ends.setdefault((player[0]-dx,player[1]-dy),[]).append(player)
            options.append(ends)
        entry=(m['warp_events'][0]['x'],m['warp_events'][0]['y']-1)
        for state in product(*options):
            obstacles=set(state)
            if len(obstacles)!=len(state):continue
            starts=[entry]+[p for options_,end in zip(options,state) for p in options_[end]]
            for start in starts:
                if start in obstacles:continue
                reached=reachable(start,floor,obstacles)
                self.assertIn((5,3),reached,(start,state))
                self.assertIn(entry,reached,(start,state))

    def test_old_map_numbers_and_new_map_ownership(self):
        baseline=read('tools/three_horizons/tests/playtest11-map-indices.json')
        names=read('tools/mapjson/three_horizons_maps.json')['maps']
        self.assertEqual(names[:len(baseline)],baseline)
        entries=read('tools/three_horizons/chapter12_maps.json')['maps']
        self.assertGreaterEqual(len(entries),3)
        self.assertEqual(len(names),len(set(names)))
        maps={read(f'data/maps/{n}/map.json')['id']:read(f'data/maps/{n}/map.json') for n in names}
        scripts='\n'.join(p.read_text() for p in (ROOT/'data/scripts/three_horizons').glob('*.inc'))
        scripts+='\n'+'\n'.join(p.read_text() for n in names if (p:=ROOT/f'data/maps/{n}/scripts.inc').exists())
        labels=set(re.findall(r'^(\w+)::?',scripts,re.M))
        for entry in entries:
            m=maps[entry['id']]
            self.assertEqual(m['layout'],entry['layout'])
            self.assertIn(m['name'],names)
            for obj in m['object_events']+m['coord_events']+m['bg_events']:
                if 'script' in obj:
                    self.assertIn(obj['script'], labels, (m['name'],obj['script']))
            for warp in m['warp_events']:
                self.assertIn(warp['dest_map'],maps,m['name'])
                self.assertLess(int(warp['dest_warp_id']),len(maps[warp['dest_map']]['warp_events']))
            for connection in m['connections'] or []:
                self.assertIn(connection['map'],maps)

    def test_cerulean_bridge_and_bill_have_two_way_connections(self):
        names=['TH_Cerulean','TH12_Route24','TH12_Route25','TH12_Route25_SeaCottage']
        maps={n:read(f'data/maps/{n}/map.json') for n in names}
        for first,second in zip(names,names[1:]):
            for a,b in ((first,second),(second,first)):
                exits={c['map'] for c in maps[a]['connections'] or []}|{w['dest_map'] for w in maps[a]['warp_events']}
                self.assertIn(maps[b]['id'],exits)
        self.assertFalse(any(e['script']=='TH_ChapterNorthBoundary' for e in maps['TH_Cerulean']['coord_events']))

if __name__=='__main__': unittest.main()
