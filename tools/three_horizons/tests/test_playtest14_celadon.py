"""Celadon's registered doors, project ownership and bounded service footprint."""
import json
import re
import os
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest
from tools.three_horizons.tests.test_playtest11_maps import ROOT, map_data, tiles, reachable

ROWS = json.loads((ROOT/'tools/three_horizons/chapter14_maps.json').read_text())[7:28]
NAMES = [r['name'] for r in ROWS]
CITY = 'MAP_TH14_CELADON_CITY'


def chapter():
    return (ROOT/'data/scripts/three_horizons/chapter14_celadon.inc').read_text()


class Celadon(unittest.TestCase):
    def test_manifest_edits_invalidate_generated_map_and_layout_tables(self):
        # A real incremental link failed with all 21 new layout symbols absent:
        # mapjson reads this manifest, but make had not tracked it as an input.
        make=shutil.which('make')
        self.assertIsNotNone(make, 'GNU make is required for the incremental dependency regression')
        with tempfile.TemporaryDirectory(dir=ROOT, prefix='.th-') as folder:
            out=Path(folder)
            for name in ('data/layouts/layouts.json','data/maps/map_groups.json',
                         'tools/mapjson/three_horizons_maps.json','.map_version','mapjson-probe',
                         'data/layouts/layouts.inc','data/maps/groups.inc'):
                path=out/name; path.parent.mkdir(parents=True,exist_ok=True)
                path.write_text('')
                os.utime(path,(1000,1000))
            for version in ('three_horizons','emerald','firered'):
                run=subprocess.run([make,'-n','-s','-f',str(ROOT/'map_data_rules.mk'),
                    '-o','.map_version','-W','tools/mapjson/three_horizons_maps.json',
                    'data/layouts/layouts.inc','data/maps/groups.inc','OS=posix',
                    'DATA_ASM_SUBDIR=data','DATA_SRC_SUBDIR=src/data',
                    'MAPJSON=mapjson-probe','MAP_VERSION='+version],
                    cwd=out,capture_output=True,text=True)
                self.assertEqual(run.returncode,0,run.stderr)
                for command in ('mapjson-probe layouts','mapjson-probe groups'):
                    self.assertEqual(command in run.stdout,version=='three_horizons',run.stdout)

    def test_city_and_twenty_interiors_keep_appended_identity(self):
        groups = json.loads((ROOT/'data/maps/map_groups.json').read_text())
        self.assertEqual(groups['gMapGroup_ThreeHorizons14'][7:28], NAMES)
        layouts = json.loads((ROOT/'data/layouts/layouts.json').read_text())['layouts']
        for r in ROWS:
            m = map_data(r['name']); donor = map_data(r['donor'])
            self.assertEqual(m['region_map_section'], donor['region_map_section'])
            l = next(l for l in layouts if l['id'] == m['layout'])
            d = next(l for l in layouts if l['id'] == donor['layout'])
            self.assertEqual((l['width'], l['height']), (d['width'], d['height']))
            self.assertTrue(l['blockdata_filepath'].startswith('data/layouts/TH14_'))
            self.assertEqual((ROOT/l['border_filepath']).read_bytes(), (ROOT/d['border_filepath']).read_bytes())

    def test_compiler_manifest_and_script_targets_are_present(self):
        manifest=json.loads((ROOT/'tools/mapjson/three_horizons_maps.json').read_text())['maps']
        self.assertTrue(set(NAMES) <= set(manifest))
        labels=set()
        for path in (ROOT/'data/scripts/three_horizons').glob('*.inc'):
            labels.update(re.findall(r'^(\w+):',path.read_text(),re.M))
        for name in NAMES:
            for event in map_data(name)['object_events']+map_data(name)['bg_events']:
                if 'script' in event: self.assertIn(event['script'],labels,(name,event))

    def test_every_celadon_door_returns_to_city(self):
        maps = {map_data(n)['id']: map_data(n) for n in NAMES}
        graph = {}
        for key, m in maps.items():
            graph[key] = set()
            for warp in m['warp_events']:
                dest = warp['dest_map']
                if dest == 'MAP_DYNAMIC':
                    self.assertTrue(m['name'].endswith('_Elevator'))
                    graph[key].update(f'MAP_TH14_CELADON_CITY_DEPARTMENT_STORE_{i}F' for i in range(1, 6))
                    continue
                # Task12 later appends the project Hideout behind its poster.
                if dest == 'MAP_TH14_ROCKET_HIDEOUT_B1F':
                    continue
                self.assertIn(dest, maps, (key, warp))
                self.assertLess(int(warp['dest_warp_id']), len(maps[dest]['warp_events']))
                graph[key].add(dest)
        for key in maps:
            visited=set();todo=[key]
            while todo:
                current=todo.pop()
                if current in visited: continue
                visited.add(current);todo.extend(graph[current]-visited)
            self.assertIn(CITY, visited, key)
        for warp in maps[CITY]['warp_events']:
            self.assertIn(CITY, graph[warp['dest_map']], warp)

    def test_city_has_no_future_chapter_exit(self):
        city=map_data('TH14_CeladonCity'); route=map_data('TH14_Route7')
        self.assertEqual(city['connections'], [{'map':'MAP_TH14_ROUTE7','offset':10,'direction':'right'}])
        self.assertIn({'map':CITY,'offset':-10,'direction':'left'}, route['connections'])
        clones=[o for o in route['object_events'] if o['type']=='clone']
        self.assertEqual(len(clones),1)
        self.assertEqual(clones[0]['target_map'],CITY)
        self.assertFalse(any(o['type']=='clone' and o.get('target_map')=='MAP_ROUTE16' for o in city['object_events']))
        text=chapter()
        for forbidden in ('ITEM_TEA','FLAG_SYS_TEA','MAP_ROUTE16','MAP_SAFFRON','setworldmapflag','FLAG_SYS_NATIONAL_DEX'):
            self.assertNotIn(forbidden,text)

    def test_west_boundary_is_visible_and_spans_every_walkable_lane(self):
        m=map_data('TH14_CeladonCity');w,h,c=tiles(m['name'])
        triggers={(e['x'],e['y']) for e in m['coord_events'] if e['script']=='TH14_CeladonWestBoundary'}
        self.assertEqual(triggers,{(3,22),(3,23),(3,24)})
        self.assertTrue(any(o['script']=='TH14_CeladonWestGuard' and (o['x'],o['y'])==(2,23) for o in m['object_events']))
        floor={(i%w,i//w) for i,v in enumerate(c) if not v&0xc00}
        area=reachable((4,23),floor,triggers)
        self.assertFalse(any((0,y) in area for y in range(h)))

    def test_lavender_to_celadon_route_is_reciprocal(self):
        names=['TH13_LavenderTown']+[r['name'] for r in json.loads((ROOT/'tools/three_horizons/chapter14_maps.json').read_text())[:8]]
        maps={map_data(n)['id']:map_data(n) for n in names}
        def connections(key):
            m=maps[key]
            return {e['map'] for e in m['connections'] or []}|{e['dest_map'] for e in m['warp_events']}
        for start,dest in [('MAP_TH13_LAVENDER_TOWN',CITY),(CITY,'MAP_TH13_LAVENDER_TOWN')]:
            visited=set();todo=[start]
            while todo:
                key=todo.pop()
                if key in visited or key not in maps:continue
                visited.add(key);todo.extend(connections(key)-visited)
            self.assertIn(dest,visited)

    def test_store_elevator_keeps_project_destinations(self):
        elevator=map_data('TH14_CeladonCity_DepartmentStore_Elevator')
        self.assertTrue(elevator['warp_events'])
        self.assertTrue(all(w['dest_map']=='MAP_DYNAMIC' for w in elevator['warp_events']))
        text=chapter()
        destinations=re.findall(r'setdynamicwarp (MAP_TH14_CELADON_CITY_DEPARTMENT_STORE_[1-5]F), 255, 6, 1',text)
        self.assertEqual(set(destinations),{f'MAP_TH14_CELADON_CITY_DEPARTMENT_STORE_{i}F' for i in range(1,6)})
        self.assertNotIn('VAR_ELEVATOR_FLOOR',text)  # aliases a native persistent variable
        for i in range(1,6):
            m=map_data(f'TH14_CeladonCity_DepartmentStore_{i}F')
            self.assertTrue(any(w['dest_map']==elevator['id'] for w in m['warp_events']))

    def test_celadon_center_sets_valid_heal_location(self):
        name='TH14_CeladonCity_PokemonCenter_1F'
        script=(ROOT/f'data/maps/{name}/scripts.inc').read_text()
        self.assertIn('setrespawn HEAL_LOCATION_TH14_CELADON',script)
        for name in ('TH14_CeladonCity_PokemonCenter_1F','TH14_CeladonCity_PokemonCenter_2F'):
            m=map_data(name)
            self.assertTrue(all(w['dest_map'].startswith('MAP_TH14_CELADON') for w in m['warp_events']))
            self.assertTrue(all('CableClub' not in o['script'] and 'MysteryGift' not in o['script'] for o in m['object_events']))

    def test_native_services_and_retryable_gift_have_owners(self):
        source=(ROOT/'src/three_horizons_celadon.c').read_text()
        for function in ('TH14_GetDeptStoreFloor', 'TH14_TryGiveEevee', 'TH14_IsFrlgPokemonCenterLayout'):
            self.assertIn(function, source)
        self.assertNotIn('VAR_ELEVATOR_FLOOR', source)
        text=chapter()
        self.assertIn('specialvar VAR_RESULT, TH14_TryGiveEevee', text)
        self.assertIn('MOVE_COUNTER', text)
        self.assertIn('MOVE_SOFT_BOILED', text)
        self.assertNotIn('FLAG_TUTOR_', text)

    def test_event_ownership_and_visible_object_capacity(self):
        receipts=json.loads((ROOT/'tools/three_horizons/chapter14_content.json').read_text())['receipts']
        owned={r['name'] for r in receipts}
        for name in NAMES:
            m=map_data(name);w,h,_=tiles(name)
            self.assertLessEqual(len(m['object_events']),64)
            for o in m['object_events']:
                if o['type']=='clone':
                    self.assertTrue(o['target_map'].startswith('MAP_TH14_'));continue
                self.assertTrue(o['script'].startswith(('TH14_','TH13_Center_','TH_Journey_')),(name,o))
                self.assertIn(o['flag'],owned|{'0','FLAG_TEMP_12','FLAG_TEMP_13','FLAG_TEMP_14'})
            for e in m['bg_events']:
                if e['type']=='hidden_item': self.assertIn(e['flag'],owned)
                else: self.assertTrue(e['script'].startswith(('TH14_','TH_Journey_')),(name,e))
            # Conservative viewport plus each object's authored movement range;
            # reserve two of sixteen sprites for the player and follower.
            for y in range(h):
                for x in range(w):
                    visible=sum(abs(o['x']-x)<=9+o.get('movement_range_x',0) and
                                abs(o['y']-y)<=7+o.get('movement_range_y',0)
                                for o in m['object_events'])
                    self.assertLessEqual(visible,14,(name,x,y,visible))


if __name__=='__main__':unittest.main()
