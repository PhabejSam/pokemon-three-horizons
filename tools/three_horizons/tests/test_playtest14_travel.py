"""Locked PT14 travel footprints, owned events and complete donor first parties."""
import json
import re
import subprocess
import tempfile
from pathlib import Path
import unittest
from tools.three_horizons.tests.test_playtest11_maps import ROOT, map_data, tiles, reachable

NAMES = ['TH14_Route8', 'TH14_Route8_WestEntrance', 'TH14_UndergroundPath_EastEntrance',
         'TH14_UndergroundPath_EastWestTunnel', 'TH14_UndergroundPath_WestEntrance',
         'TH14_Route7', 'TH14_Route7_EastEntrance']
SLOTS = [1,2,3,4,5,6,7,8,9,12,14,15]
EXPECTED = {
    'MAP_TH14_ROUTE8': [('PIDGEY',18),('MEOWTH',18),('GROWLITHE',16),('VULPIX',16),('PIDGEY',20),('MEOWTH',20),('EKANS',17),('SANDSHREW',17),('GROWLITHE',17),('VULPIX',17),('EKANS',19),('SANDSHREW',19)],
    'MAP_TH14_ROUTE7': [('PIDGEY',19),('MEOWTH',17),('ODDISH',19),('BELLSPROUT',19),('MEOWTH',18),('PIDGEY',22),('GROWLITHE',18),('VULPIX',18),('ODDISH',22),('BELLSPROUT',22),('GROWLITHE',20),('VULPIX',20)],
}
def source(): return (ROOT/'data/scripts/three_horizons/chapter14_travel.inc').read_text()
def party(text, name): return re.search(r'=== '+name+r' ===\n(.*?)(?=\n===|\n#endif|\Z)',text,re.S)[1].strip()

class Travel(unittest.TestCase):
    def test_build_manifest_and_compiler_select_new_maps_only_for_project(self):
        manifest=json.loads((ROOT/'tools/mapjson/three_horizons_maps.json').read_text())['maps']
        for name in NAMES: self.assertEqual(manifest.count(name),1,name)
        exe=ROOT/'tools/mapjson/mapjson'
        if not exe.exists(): exe=exe.with_suffix('.exe')
        self.assertTrue(exe.exists(), 'build documented mapjson tool before native-map checks')
        with tempfile.TemporaryDirectory(dir=ROOT) as td:
            for version in ('three_horizons','emerald','firered'):
                out=Path(td)/version;out.mkdir()
                result=subprocess.run([str(exe),'layouts',version,'data/layouts/layouts.json',str(out),str(out)],cwd=ROOT,capture_output=True,text=True)
                self.assertEqual(result.returncode,0,result.stderr)
                text=(out/'layouts.inc').read_text()
                for name in NAMES: self.assertEqual(name+'_Layout::' in text,version=='three_horizons',(version,name))

    def test_guide_uses_same_json_slots_for_new_routes(self):
        from tools.three_horizons.export_encounters import render
        text = render('task8-working-tree', playtest=14)
        route8 = text.split('## Route 8 — all times — grass / cave',1)[1].split('## ',1)[0]
        route7 = text.split('## Route 7 — all times — grass / cave',1)[1].split('## ',1)[0]
        self.assertIn('| Growlithe | 14% | 16, 17 |', route8)
        self.assertIn('| Sandshrew | 6% | 17, 19 |', route8)
        self.assertIn('| Bellsprout | 14% | 19, 22 |', route7)
        self.assertIn('| Vulpix | 6% | 18, 20 |', route7)
        self.assertNotIn('Playtest 13 provides no SILPH SCOPE', text)

    def test_append_only_map_ids_and_distinct_layouts(self):
        groups=json.loads((ROOT/'data/maps/map_groups.json').read_text())
        self.assertIn('gMapGroup_ThreeHorizons14',groups, 'approved travel group absent')
        self.assertEqual(groups['group_order'].index('gMapGroup_ThreeHorizons14'),76)
        self.assertEqual(groups['gMapGroup_ThreeHorizons14'][:7],NAMES)
        self.assertTrue(all(i<128 for i,_ in enumerate(groups['gMapGroup_ThreeHorizons14'])))
        layouts=json.loads((ROOT/'data/layouts/layouts.json').read_text())['layouts']
        old=json.loads((ROOT/'tools/three_horizons/tests/playtest13-map-layout-baseline.json').read_text())
        self.assertEqual(layouts[:len(old['layouts'])],old['layouts'])
        self.assertEqual(len({map_data(n)['layout'] for n in NAMES}),7)
        imports=json.loads((ROOT/'tools/three_horizons/chapter14_maps.json').read_text())[:7]
        for n in NAMES:
            layout=next(l for l in layouts if l['id']==map_data(n)['layout'])
            self.assertTrue(layout['blockdata_filepath'].startswith('data/layouts/TH14_'))
            donor=next(r['donor'] for r in imports if r['name']==n)
            original=next(l for l in layouts if l['id']==map_data(donor)['layout'])
            for key in ('blockdata_filepath','border_filepath'):
                self.assertEqual((ROOT/layout[key]).read_bytes(),(ROOT/original[key]).read_bytes(),(n,key))

    def test_connections_return_warps_and_restricted_gates(self):
        maps={map_data(n)['id']:map_data(n) for n in NAMES+['TH13_LavenderTown']}
        self.assertIn(dict(map='MAP_TH14_ROUTE8',offset=0,direction='left'),maps['MAP_TH13_LAVENDER_TOWN']['connections'])
        self.assertIn(dict(map='MAP_TH13_LAVENDER_TOWN',offset=0,direction='right'),maps['MAP_TH14_ROUTE8']['connections'])
        allowed=set(maps)|{'MAP_TH14_CELADON_CITY'}
        for n in NAMES:
            m=map_data(n)
            for c in m['connections'] or []:self.assertIn(c['map'],allowed)
            for w in m['warp_events']:
                self.assertIn(w['dest_map'],maps,n)
                other=maps[w['dest_map']];i=int(w['dest_warp_id'])
                self.assertLess(i,len(other['warp_events']),n)
                self.assertEqual(other['warp_events'][i]['dest_map'],m['id'],(n,w))
            for e in m['coord_events']:self.assertNotIn('VAR_MAP_SCENE_ROUTE5',e.get('var',''))
        visited=set();pending=['MAP_TH13_LAVENDER_TOWN']
        while pending:
            key=pending.pop()
            if key in visited or key not in maps:continue
            visited.add(key);m=maps[key]
            pending += [c['map'] for c in m['connections'] or []]
            pending += [w['dest_map'] for w in m['warp_events']]
        self.assertEqual(visited,set(maps))
        text=source()
        for forbidden in ('ITEM_TEA','FLAG_SYS_TEA','VAR_MAP_SCENE_ROUTE5','MAP_SAFFRON_CITY'):
            self.assertNotIn(forbidden,text)
        for n in ('TH14_Route8_WestEntrance','TH14_Route7_EastEntrance'):
            m=map_data(n);w,h,c=tiles(n);floor={(i%w,i//w) for i,v in enumerate(c) if not v&0xc00}
            start=(10,5) if 'Route8' in n else (2,5)
            triggers={(t['x'],t['y']) for t in m['coord_events']}
            self.assertEqual(triggers,{(6,4),(6,5),(6,6)})
            area=reachable(start,floor,triggers)
            forbidden=(1,5) if 'Route8' in n else (11,5)
            self.assertNotIn(forbidden,area,n)
            self.assertTrue(any((q['x'],q['y']) in area for q in m['warp_events']))

    def test_owned_scripts_hidden_receipts_and_trainer_placement(self):
        text=source();labels=set(re.findall(r'^(\w+):',text,re.M))
        receipts=json.loads((ROOT/'tools/three_horizons/chapter14_content.json').read_text())['receipts']
        wanted={r['name']:r for r in receipts if r['writer'] in NAMES}
        actual={}
        for n in NAMES:
            m=map_data(n);w,h,c=tiles(n)
            for o in m['object_events']:
                if o['type']=='clone':continue  # Task9 owns its registered Celadon target.
                self.assertIn(o['script'],labels|{'TH_Journey_Tree'},(n,o))
                self.assertIn(o['flag'],('0','FLAG_TEMP_12','FLAG_TEMP_13'))
                self.assertFalse(c[o['y']*w+o['x']]&0xc00,(n,o))
            for bg in m['bg_events']:
                if bg['type']=='hidden_item':actual[bg['flag']]=(n,[bg['x'],bg['y']])
                else:self.assertIn(bg['script'],labels)
        self.assertEqual(actual,{name:(r['writer'],r['coordinate']) for name,r in wanted.items()})
        m=map_data(NAMES[0]);donor=map_data('Route8_Frlg')
        for a,b in zip(m['object_events'],donor['object_events']):
            for key in ('x','y','elevation','movement_type','trainer_sight_or_berry_tree_id'):
                self.assertEqual(a[key],b[key])
        self.assertFalse(any(o.get('trainer_type')=='TRAINER_TYPE_NORMAL' for o in map_data('TH14_Route7')['object_events']))

    def test_twelve_complete_first_parties_and_canonical_rematch_rows(self):
        ledger=json.loads((ROOT/'tools/three_horizons/chapter14_content.json').read_text())['trainers'][:12]
        old=(ROOT/'src/data/trainers_frlg.party').read_text();new=(ROOT/'src/data/trainers.party').read_text()
        entries=re.findall(r'\{(TRAINER_TH14_ROUTE8_\w+), MAP_TH14_ROUTE8, (\d+)\}',(ROOT/'src/data/three_horizons_rematches.h').read_text())
        self.assertEqual(len(entries),12)
        self.assertEqual([int(local) for _,local in entries],SLOTS)
        for r in ledger:self.assertEqual(party(new,r['constant']),party(old,r['donor']))
        for trainer,local in entries:self.assertIn(trainer,source())

    def test_twins_both_entrypoints_use_native_double_and_one_identity(self):
        text=source()
        for name in ('Eli','Anne'):
            block=text.split('TH14_Route8_'+name+'::',1)[1].split('\nTH14_',1)[0]
            self.assertIn('trainerbattle_double TRAINER_TH14_ROUTE8_ELI_ANNE,',block)
            rematch=text.split('TH14_Route8_'+name+'_Rematch::',1)[1].split('\nTH14_',1)[0]
            self.assertIn('trainerbattle_rematch_double TRAINER_TH14_ROUTE8_ELI_ANNE,',rematch)
            self.assertIn('NotEnoughMons',rematch)
            for word in ('setflag','giveitem','givemon','addmoney'):self.assertNotIn(word,rematch)
        aliases=(ROOT/'src/data/three_horizons_rematches.h').read_text()
        self.assertIn('{TRAINER_TH14_ROUTE8_ELI_ANNE, MAP_TH14_ROUTE8, 13, 12}',aliases)

    def test_exact_land_tables_and_no_inaccessible_water(self):
        group=json.loads((ROOT/'src/data/wild_encounters.json').read_text())['wild_encounter_groups'][0]
        self.assertEqual(next(f['encounter_rates'] for f in group['fields'] if f['type']=='land_mons'),[20,20,10,10,10,10,5,5,4,4,1,1])
        for map_id,wanted in EXPECTED.items():
            rows=[r for r in group['encounters'] if r['map']==map_id];self.assertEqual(len(rows),1)
            r=rows[0];self.assertEqual(r['land_mons']['encounter_rate'],21)
            self.assertEqual([(m['species'],m['min_level'],m['max_level']) for m in r['land_mons']['mons']], [('SPECIES_'+s,l,l) for s,l in wanted])
            self.assertFalse(set(r)&{'water_mons','fishing_mons','rock_smash_mons'})

if __name__=='__main__':unittest.main()
