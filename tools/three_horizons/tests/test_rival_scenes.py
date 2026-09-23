"""Scene contract and real tile collision checks, including every ball approach."""
import json
from pathlib import Path
import re
import struct
import unittest

ROOT = Path(__file__).resolve().parents[3]


def movement(script, name, start):
    assert name + ':\n' in script, 'Missing scene movement ' + name
    body = script.split(name + ':\n', 1)[1].split('    step_end', 1)[0]
    x, y = start
    result = []
    for direction in re.findall(r'walk_(up|down|left|right)\b', body):
        dx, dy = {'up': (0, -1), 'down': (0, 1), 'left': (-1, 0), 'right': (1, 0)}[direction]
        x, y = x + dx, y + dy
        result.append((x, y))
    return result


class RivalScenes(unittest.TestCase):
    def test_doors_dispatch_without_a_player_step_and_do_not_replay(self):
        maps = (ROOT / 'data/scripts/three_horizons/maps.inc').read_text()
        town = (ROOT / 'data/scripts/three_horizons/town.inc').read_text()
        self.assertIn('map_script MAP_SCRIPT_ON_FRAME_TABLE, TH_Pallet_OnFrame', maps)
        self.assertIn('map_script_2 VAR_TEMP_3, 1, TH_Pallet_CheckDoorScene', town)
        body = town.split('TH_Pallet_CheckDoorScene::\n')[1].split('TH_EventScript_RobinTown::')[0]
        self.assertLess(body.index('setvar VAR_TEMP_3, 0'), body.index('getplayerxy'))
        self.assertIn('TH_STAGE_HOME, TH_Pallet_CheckHomeDoor', body)
        self.assertIn('TH_STAGE_PARTNER, TH_Pallet_CheckLabDoor', body)
        for pos in ('VAR_0x8008, 6', 'VAR_0x8009, 8', 'VAR_0x8008, 16', 'VAR_0x8009, 14'):
            self.assertIn(pos, body)
        self.assertEqual(movement(town, 'TH_Movement_RivalGreet', (7, 9)), [(7, 8)])
        blocks = struct.unpack('<480H', (ROOT / 'data/layouts/PalletTown_Frlg/map.bin').read_bytes())
        self.assertEqual(blocks[8 * 24 + 7] & 0xc00, 0)
        self.assertIn('face_left', town.split('TH_Movement_RivalGreet:\n')[1].split('step_end')[0])

    def test_rival_collects_from_each_region_without_crossing_player_or_furniture(self):
        lab = (ROOT / 'data/scripts/three_horizons/lab.inc').read_text()
        blocks = struct.unpack('<182H', (ROOT / 'data/layouts/PalletTown_ProfessorOaksLab_Frlg/map.bin').read_bytes())
        objects = json.loads((ROOT / 'data/maps/TH_OaksLab/map.json').read_text())['object_events']
        occupied = {(o['x'], o['y']) for o in objects if o['local_id'] != 'LOCALID_TH_ROBIN_LAB'}
        for region, x in (('Kanto', 8), ('Johto', 9), ('Hoenn', 10)):
            approach = movement(lab, 'TH_Movement_RivalPick' + region, (4, 5))
            leave = movement(lab, 'TH_Movement_RivalLeave' + region, (x, 5))
            self.assertEqual(approach[-1], (x, 5))
            self.assertEqual(leave[-1], (6, 12))
            # Every accessible interaction position around this ball; south steps aside.
            for player in ((x - 1, 4), (x + 1, 4), (x, 3), (x, 5)):
                if blocks[player[1] * 13 + player[0]] & 0xc00 or player in occupied:
                    continue
                final_player = (x, 6) if player == (x, 5) else player
                for point in approach + leave:
                    self.assertNotEqual(point, final_player)
                    self.assertNotIn(point, occupied)
                    self.assertEqual(blocks[point[1] * 13 + point[0]] & 0xc00, 0)
            pickup = lab.split('TH_Lab_Pick' + region + ':\n')[1].split('TH_Lab_', 1)[0]
            self.assertIn('TH_Movement_RivalPick' + region, pickup)
        confirm = lab.split('TH_Lab_Confirm:\n')[1].split('TH_Lab_AlreadyChosen:')[0]
        self.assertIn('call TH_Lab_RivalCollectPartner', confirm)
        collection = lab.split('TH_Lab_RivalCollectPartner:\n')[1]
        self.assertIn('hidefollower TRUE', collection)
        self.assertIn('removeobject VAR_0x800A', collection)
        self.assertIn('playfanfare MUS_OBTAIN_ITEM', collection)
        self.assertIn('playmoncry VAR_TH_RIVAL_PARTNER', collection)


if __name__ == '__main__':
    unittest.main()
