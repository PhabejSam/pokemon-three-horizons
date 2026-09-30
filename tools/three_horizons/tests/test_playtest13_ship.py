"""Ship scene contracts against authored commands and native map geometry."""
import re
import unittest
from tools.three_horizons.tests.test_playtest11_maps import ROOT, map_data, tiles

SOURCE = ROOT / 'data/scripts/three_horizons/chapter12_ship.inc'


def commands():
    lines = []
    labels = {}
    for raw in SOURCE.read_text().splitlines():
        line = raw.split('@', 1)[0].strip()
        if not line:
            continue
        if line.endswith(':'):
            labels[line.rstrip(':')] = len(lines)
        else:
            lines.append(line)
    return lines, labels


class Playtest13Ship(unittest.TestCase):
    def test_ship_rival_exits_before_removal(self):
        lines, labels = commands()
        data = map_data('TH12_SSAnne_2F_Corridor')
        width, _, grid = tiles(data['name'])
        rival = data['object_events'][0]
        triggers = [(e['x'], e['y']) for e in data['coord_events']
                    if e['script'] == 'TH12_Ship_RivalTrigger']
        self.assertEqual(triggers, [(30, 6), (31, 6), (32, 6)])
        # Also cover direct interaction from each accessible adjacent tile.
        for player in triggers + [(30, 4), (32, 4), (31, 3), (31, 5)]:
            with self.subTest(player=player):
                pos = (rival['x'], rival['y'])
                pc = labels['TH12_Ship_RivalVictory']
                variables = {}
                pending = False
                removed = refreshed = released = False
                walked = 0
                for _ in range(80):
                    line = lines[pc]
                    pc += 1
                    op, _, tail = line.partition(' ')
                    args = [a.strip() for a in tail.split(',')]
                    if op in ('setflag', 'msgbox', 'closemessage'):
                        continue
                    if op == 'getplayerxy':
                        variables[args[0]], variables[args[1]] = player
                    elif op == 'goto_if_eq':
                        if variables[args[0]] == int(args[1]):
                            pc = labels[args[2]]
                    elif op == 'goto':
                        pc = labels[args[0]]
                    elif op == 'applymovement':
                        self.assertEqual(args[0], rival['local_id'])
                        self.assertFalse(pending)
                        movement_pc = labels[args[1]]
                        while lines[movement_pc] != 'step_end':
                            movement = lines[movement_pc]
                            movement_pc += 1
                            self.assertIn(movement, ('walk_up', 'walk_down', 'walk_left', 'walk_right'))
                            dx, dy = {'walk_up': (0, -1), 'walk_down': (0, 1),
                                      'walk_left': (-1, 0), 'walk_right': (1, 0)}[movement]
                            pos = (pos[0] + dx, pos[1] + dy)
                            self.assertNotEqual(pos, player)
                            self.assertEqual(grid[pos[1] * width + pos[0]] & 0xC00, 0)
                            self.assertEqual(grid[pos[1] * width + pos[0]] >> 12, 3)
                            self.assertNotIn(pos, [(o['x'], o['y']) for o in data['object_events'][1:]])
                            walked += 1
                        pending = True
                    elif op == 'waitmovement':
                        self.assertTrue(pending)
                        pending = False
                    elif op == 'removeobject':
                        self.assertGreater(walked, 0, 'rival disappears without walking')
                        self.assertFalse(pending, 'removal must await the completed walk')
                        self.assertGreater(abs(pos[0] - player[0]), 8, 'rival must leave the camera before removal')
                        removed = True
                    elif op == 'special':
                        self.assertEqual(args[0], 'TH_RefreshFollower')
                        self.assertTrue(removed)
                        refreshed = True
                    elif op == 'releaseall':
                        self.assertTrue(removed and refreshed)
                        released = True
                    elif op == 'end':
                        self.assertTrue(released)
                        break
                    else:
                        self.fail('Unmodeled scene command: ' + line)
                else:
                    self.fail('Scene failed to terminate')

    def test_ship_rival_keeps_all_nine_partner_dispatches(self):
        source = SOURCE.read_text()
        for species in ('BULBASAUR', 'CHARMANDER', 'SQUIRTLE', 'CHIKORITA',
                        'CYNDAQUIL', 'TOTODILE', 'TREECKO', 'TORCHIC', 'MUDKIP'):
            self.assertIn(f'goto_if_eq VAR_TH_RIVAL_PARTNER, SPECIES_{species}, TH12_Ship_Rival_{species}', source)
            self.assertRegex(source, rf'TH12_Ship_Rival_{species}:\s+trainerbattle_no_intro TRAINER_TH12_SHIP_{species}, TH12_Ship_RivalDefeat\s+goto TH12_Ship_RivalVictory')


if __name__ == '__main__':
    unittest.main()
