import json
import re
import struct
import unittest
from collections import deque
from itertools import product
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]


def map_data(name):
    return json.loads((ROOT / f'data/maps/{name}/map.json').read_text())


def tiles(name):
    m = map_data(name)
    layout = next(l for l in json.loads((ROOT / 'data/layouts/layouts.json').read_text())['layouts'] if l['id'] == m['layout'])
    raw = (ROOT / layout['blockdata_filepath']).read_bytes()
    a = list(struct.unpack('<' + str(len(raw) // 2) + 'H', raw))
    script = (ROOT / f'data/maps/{name}/scripts.inc').read_text()
    for x, y, tile, solid in re.findall(r'setmetatile (\d+), (\d+), (0x[\da-fA-F]+|\d+), (TRUE|FALSE)', script):
        i = int(y) * layout['width'] + int(x)
        a[i] = (a[i] & 0xf000) | int(tile, 0) | (0xc00 if solid == 'TRUE' else 0)
    return layout['width'], layout['height'], a


def reachable(start, floor, obstacles):
    queue = deque([start])
    seen = {start}
    while queue:
        x, y = queue.popleft()
        for p in ((x-1,y), (x+1,y), (x,y-1), (x,y+1)):
            if p in floor and p not in obstacles and p not in seen:
                queue.append(p)
                seen.add(p)
    return seen


class Playtest11Maps(unittest.TestCase):
    def test_misty_and_exit_reachable_with_every_trainer_approach_endpoint(self):
        m = map_data('TH_CeruleanGym')
        w, h, a = tiles('TH_CeruleanGym')
        # Water has elevation 1 (Luis' pool edge 0); only elevation 3 is floor.
        floor = {(i % w, i // w) for i, v in enumerate(a) if v >> 12 == 3 and not v & 0xc00}
        objects = m['object_events']
        options = []
        for o in objects:
            pos = (o['x'], o['y'])
            endpoints = {pos: []}
            if o['trainer_type'] == 'TRAINER_TYPE_NORMAL':
                dx, dy = {'MOVEMENT_TYPE_FACE_LEFT':(-1,0), 'MOVEMENT_TYPE_FACE_RIGHT':(1,0)}[o['movement_type']]
                for distance in range(1, int(o['trainer_sight_or_berry_tree_id']) + 1):
                    player = (pos[0]+dx*distance,pos[1]+dy*distance)
                    path = [(pos[0]+dx*i,pos[1]+dy*i) for i in range(1,distance)]
                    if player in floor and all(p in floor for p in path):
                        endpoints.setdefault((player[0]-dx,player[1]-dy), []).append(player)
            if o['script'] == 'TH_GymLuis_Talk':
                endpoints[(10,12)] = [(9,12)]
            options.append(endpoints)
        for state in product(*options):
            obstacles = set(state)
            # Test the real player position that produces each endpoint, plus
            # entry/re-entry. Do not place the player in an unreachable pocket
            # behind a trainer approached from the opposite side.
            starts = [(8,17)] + [p for option, pos in zip(options, state) for p in option[pos]]
            for start in starts:
                if start in obstacles:
                    continue
                seen = reachable(start, floor, obstacles)
                self.assertTrue({(7,6),(9,6),(8,7)} & seen, ('Misty blocked', start, state))
                self.assertIn((8,18), seen, ('exit blocked', start, state))

    def test_luis_swims_to_the_edge_without_entering_the_walkway(self):
        m = map_data('TH_CeruleanGym')
        swimmer = m['object_events'][0]
        self.assertEqual(swimmer['graphics_id'], 'OBJ_EVENT_GFX_SWIMMER_M_WATER')
        self.assertEqual((swimmer['x'], swimmer['y']), (11,12))
        self.assertTrue(any((e['x'],e['y'],e['script']) == (9,12,'TH_GymLuis_Approach') for e in m['coord_events']))
        s = (ROOT / 'data/scripts/three_horizons/playtest11_maps.inc').read_text()
        approach = s.split('TH_GymLuis_Approach::')[1].split('TH_GymLuis_Talk::')[0]
        self.assertIn('goto_if_defeated TRAINER_TH9_SWIMMER_MALE_LUIS', approach)
        self.assertIn('setvar VAR_LAST_TALKED, LOCALID_TH_CERULEANGYM_0', approach)
        self.assertIn('applymovement LOCALID_TH_CERULEANGYM_0, TH_GymLuis_SwimLeft', approach)
        swim = s.split('TH_GymLuis_SwimLeft:')[1].split('step_end')[0]
        self.assertEqual(swim.count('walk_left'), 1)
        self.assertNotIn('walk_left 2', swim)

    def test_route4_opening_uses_matching_low_ledge_caps_and_walkable_ground(self):
        w, h, a = tiles('TH_Route4')
        self.assertEqual([a[9*w+x] & 1023 for x in (91,92,93)], [0xb1,0x008,0xb0])
        self.assertEqual(a[9*w+92] & 0xc00, 0)
        floor = {(i%w,i//w) for i,v in enumerate(a) if not v & 0xc00}
        self.assertIn((32,6), reachable((107,11),floor,set()))

    def test_viridian_entrance_closed_but_saved_inside_exit_retained(self):
        town = map_data('TH_ViridianEntrance')
        gym = map_data('TH_ViridianGym')
        self.assertTrue(any((e['x'],e['y'],e['script']) == (36,11,'TH_ViridianGym_ClosedEntrance') for e in town['coord_events']))
        self.assertEqual(town['warp_events'][3]['dest_map'], 'MAP_TH_VIRIDIAN_GYM')
        self.assertEqual({e['dest_warp_id'] for e in gym['warp_events']}, {'3'})
        self.assertFalse(any(o['script'] == 'TH_Pickup_24' for o in gym['object_events']))
        self.assertEqual((gym['object_events'][0]['x'], gym['object_events'][0]['y']), (15,20))
        _,_,blocks = tiles('TH_ViridianGym')
        self.assertEqual(blocks[20*21+15] & 0xc00, 0)

    def test_closed_gym_turns_player_onto_clear_ground(self):
        s = (ROOT / 'data/scripts/three_horizons/playtest11_maps.inc').read_text()
        body = s.split('TH_ViridianGym_ClosedEntrance::')[1].split('releaseall')[0]
        movement = re.search(r'applymovement OBJ_EVENT_ID_PLAYER, (\w+)', body)[1]
        steps = s.split(movement + ':')[1].split('step_end')[0]
        w, h, a = tiles('TH_ViridianEntrance')
        x, y = 36, 11
        for direction in re.findall(r'walk_(left|right|up|down)', steps):
            dx, dy = {'left':(-1,0), 'right':(1,0), 'up':(0,-1), 'down':(0,1)}[direction]
            x, y = x+dx, y+dy
            self.assertEqual(a[y*w+x] & 0xc00, 0, (x,y))
        self.assertNotEqual((x,y),(36,11))

    def test_imported_trainers_keep_native_facing_and_wandering(self):
        for current, native in [('TH_ViridianForest','ViridianForest_Frlg'),('TH_Route3','Route3_Frlg'),('TH_MtMoon1F','MtMoon_1F_Frlg')]:
            original = {(o['x'],o['y']):o for o in map_data(native)['object_events']}
            for o in map_data(current)['object_events']:
                if o['trainer_type'] == 'TRAINER_TYPE_NORMAL':
                    source = original[o['x'],o['y']]
                    for key in ('movement_type','movement_range_x','movement_range_y','trainer_sight_or_berry_tree_id'):
                        self.assertEqual(o[key],source[key],(current,o['local_id'],key))

    def test_museum_greets_visitors_on_all_three_entrance_lanes(self):
        m = map_data('TH_PewterMuseum1F')
        self.assertEqual(m['object_events'][0]['movement_type'], 'MOVEMENT_TYPE_FACE_LEFT')
        self.assertEqual({(e['x'],e['y']) for e in m['coord_events'] if e['script']=='TH_MuseumWelcome'}, {(12,5),(13,5),(14,5)})


if __name__ == '__main__':
    unittest.main()
