import json
import re
import unittest
from collections import Counter
from tools.three_horizons.tests.test_playtest11_maps import ROOT, map_data, tiles, reachable
from tools.three_horizons.tests.test_playtest13_research import Scene

NAMES = ['TH13_Route11', 'TH13_DiglettsCave_SouthEntrance', 'TH13_DiglettsCave_B1F', 'TH13_DiglettsCave_NorthEntrance']

class CaveRoute(unittest.TestCase):
    def test_build_selects_every_registered_project_map_in_order(self):
        registry = json.loads((ROOT/'data/maps/map_groups.json').read_text())['gMapGroup_ThreeHorizons']
        selected = json.loads((ROOT/'tools/mapjson/three_horizons_maps.json').read_text())['maps']
        self.assertEqual(selected, registry)
        self.assertEqual(len(selected), len(set(selected)))

    def test_selected_maps_link_scripts_and_native_tilesets(self):
        selected=json.loads((ROOT/'tools/mapjson/three_horizons_maps.json').read_text())['maps']
        scripts=(ROOT/'data/scripts/three_horizons/maps.inc').read_text()
        pending=re.findall(r'\.include "([^"]+)"',scripts); seen=set()
        while pending:
            path=pending.pop()
            if path in seen:continue
            seen.add(path);text=(ROOT/path).read_text(encoding='utf-8');scripts+='\n'+text
            pending.extend(re.findall(r'\.include "([^"]+)"',text))
        script_labels=set(re.findall(r'^(\w+)::',scripts,re.M))
        layouts={x['id']:x for x in json.loads((ROOT/'data/layouts/layouts.json').read_text())['layouts']}
        headers=(ROOT/'src/data/tilesets/three_horizons.h').read_text()
        definitions=set(re.findall(r'const struct Tileset (\w+)\s*=',headers))
        for name in selected:
            with self.subTest(map=name):
                self.assertIn(name+'_MapScripts',script_labels)
                layout=layouts[map_data(name)['layout']]
                for field in ('primary_tileset','secondary_tileset'):
                    self.assertIn(layout[field],definitions)

    def test_new_trainer_ids_do_not_alias_any_existing_th_identity(self):
        ids=re.findall(r'#define (TRAINER_TH\w+) (\d+)',(ROOT/'include/constants/opponents.h').read_text())
        values=[int(n) for _,n in ids]
        self.assertEqual(len(values),len(set(values)))
        for name,value in ids:
            if name.startswith('TRAINER_TH13_ROUTE11_'):self.assertGreater(int(value),103)

    def test_trainer_table_replacements_are_exclusive_to_th(self):
        header=(ROOT/'include/constants/opponents.h').read_text()
        ids=dict(re.findall(r'#define (TRAINER_\w+) +(\d+)',header))
        source=(ROOT/'src/data/trainers.party').read_text()
        for enabled in (False,True):
            active=[True]; names=[]
            for line in source.splitlines():
                if line.startswith('#if '):
                    expression=line[4:].strip();self.assertIn(expression,('THREE_HORIZONS','!THREE_HORIZONS'))
                    active.append(active[-1] and (enabled if expression=='THREE_HORIZONS' else not enabled))
                elif line.startswith('#endif'):active.pop()
                elif line.startswith('=== ') and active[-1]:names.append(line.split()[1])
            self.assertEqual(len(active),1)
            values=[ids[n] for n in names]
            self.assertEqual(len(values),len(set(values)),enabled)
            self.assertEqual(sum(n.startswith('TRAINER_TH13_ROUTE11_') for n in names),10 if enabled else 0)

    def test_diglett_cave_connects_vermilion_to_route2(self):
        registry = json.loads((ROOT/'data/maps/map_groups.json').read_text())['gMapGroup_ThreeHorizons']
        for name in NAMES: self.assertIn(name, registry)
        all_maps = {m['id']:m for name in registry for m in [map_data(name)]}
        for name in NAMES:
            m = map_data(name)
            self.assertTrue(m['allow_cycling'])
            for warp in m['warp_events']:
                target = all_maps[warp['dest_map']]
                back = target['warp_events'][int(warp['dest_warp_id'])]
                self.assertEqual(back['dest_map'],m['id'])
            for obj in m['object_events']:
                self.assertTrue(obj['script'].startswith('TH13_'))
                self.assertTrue(obj['flag']=='0' or obj['flag'].startswith('FLAG_TH13_PICKUP_'))
        route=map_data(NAMES[0]); city=map_data('TH12_VermilionCity')
        self.assertEqual(route['connections'],[{'map':city['id'],'offset':-10,'direction':'left'}])
        self.assertIn({'map':route['id'],'offset':10,'direction':'right'},city['connections'])
        self.assertFalse(any(o['script']=='TH12_EastBoundary' for o in city['coord_events']))
        self.assertEqual(len(route['warp_events']),1)
        self.assertEqual(map_data(NAMES[-1])['warp_events'][1]['dest_warp_id'],'4')
        self.assertNotIn('setmetatile 17, 11, 169, TRUE',(ROOT/'data/maps/TH_Route2/scripts.inc').read_text())
        self.assertFalse(any((o['x'],o['y'])==(17,11) and o['script']=='TH_Journey_Closed' for o in map_data('TH_Route2')['bg_events']))
        # Research partners cannot disconnect the long native cave corridor.
        w,h,a=tiles(NAMES[2]);floor={(i%w,i//w) for i,v in enumerate(a) if not v&0xc00}
        objects={(o['x'],o['y']) for o in map_data(NAMES[2])['object_events']}
        seen=reachable((82,71),floor,objects)
        self.assertIn((3,3),seen)
        for x,y in objects:self.assertTrue(seen.intersection(((x-1,y),(x+1,y),(x,y-1),(x,y+1))))

    def test_cave_encounter_weights_and_levels(self):
        group=json.loads((ROOT/'src/data/wild_encounters.json').read_text())['wild_encounter_groups'][0]
        matches=[e for e in group['encounters'] if e['map']=='MAP_TH13_DIGLETTS_CAVE_B1F']
        self.assertEqual(len(matches),1)
        rates=next(f['encounter_rates'] for f in group['fields'] if f['type']=='land_mons')
        mons=matches[0]['land_mons']['mons'];self.assertEqual(len(mons),len(rates))
        totals=Counter()
        for rate,mon in zip(rates,mons):
            totals[mon['species']]+=rate
            self.assertLessEqual(15,mon['min_level']);self.assertLessEqual(mon['min_level'],mon['max_level']);self.assertLessEqual(mon['max_level'],31)
        self.assertEqual(totals,{'SPECIES_DIGLETT':70,'SPECIES_DUGTRIO':10,'SPECIES_PHANPY':10,'SPECIES_WHISMUR':10})

    def test_cave_research_repeat_is_safe(self):
        source=(ROOT/'data/scripts/three_horizons/chapter13_routes.inc').read_text()
        self.assertIn('TH13_Cave_Pair::',source)
        s=Scene(gear=False);s.run('TH13_Cave_Pair');self.assertEqual(s.entries,{'TH_RESEARCH_CAVE'});self.assertFalse(s.photos)
        s.gear=True;s.answer=0;s.run('TH13_Cave_Pair');self.assertFalse(s.photos)
        s.answer=1;s.run('TH13_Cave_Pair');s.run('TH13_Cave_Pair')
        self.assertEqual(s.photos,{'TH_PHOTO_CAVE'});self.assertEqual(s.flashes,1)

    def test_all_ten_native_route_trainers_keep_first_rosters(self):
        path=ROOT/'data/maps/TH13_Route11/map.json';self.assertTrue(path.exists())
        objects=[o for o in map_data(NAMES[0])['object_events'] if o['trainer_type']=='TRAINER_TYPE_NORMAL']
        self.assertEqual(len(objects),10)
        native=(ROOT/'src/data/trainers_frlg.party').read_text();authored=(ROOT/'src/data/trainers.party').read_text()
        for o in objects:
            name=o['script'].split('_')[-1].upper()
            original=re.search(r'=== (TRAINER_[A-Z_]*'+name+r') ===\n(.*?)(?=\n===|\Z)',native,re.S)
            current=re.search(r'=== TRAINER_TH13_ROUTE11_'+name+r' ===\n(.*?)(?=\n===|\n#endif|\Z)',authored,re.S)
            self.assertIsNotNone(original);self.assertIsNotNone(current)
            self.assertEqual(current[1].strip(),original[2].strip())

if __name__=='__main__':unittest.main()
