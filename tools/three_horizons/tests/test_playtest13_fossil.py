"""Fossil challenge geometry and follower-safe staging on the real cave floor."""
import re
import unittest
from tools.three_horizons.tests.test_playtest11_maps import ROOT, map_data, tiles


class Playtest13Fossil(unittest.TestCase):
    def test_fossil_challenge_faces_player_from_stairs(self):
        data = map_data('TH_MtMoonB2F')
        width, _, grid = tiles(data['name'])
        scientist = next(o for o in data['object_events'] if o['script'] == 'TH_Trainer9_SUPER_NERD_MIGUEL')
        source = (ROOT / 'data/scripts/three_horizons/playtest11_story.inc').read_text()
        lines, labels = [], {}
        for raw in source.splitlines():
            line = raw.split('@', 1)[0].strip()
            if not line:
                continue
            if line.endswith(':'):
                labels[line.rstrip(':')] = len(lines)
            else:
                lines.append(line)
        triggers = [e for e in data['coord_events'] if e['script'] == 'TH_FossilResearcherTrigger']
        self.assertEqual({e['x'] for e in triggers}, {13, 14})
        for trigger in triggers:
            player = (trigger['x'], trigger['y'])
            self.assertEqual(grid[player[1]*width+player[0]], 0x3281,
                             'Introduction starts on the stairs rather than the open floor')
            # Approach from the stairs, either side, or the north (a saved/revisited position).
            for follower in [(player[0], player[1]+1), (player[0]-1, player[1]),
                             (player[0]+1, player[1]), (player[0], player[1]-1)]:
                pos = (scientist['x'], scientist['y'])
                pc = labels['TH_FossilResearcherTrigger']
                hidden = pending = faced = False
                player_direction = None
                variables = {}
                for _ in range(40):
                    op, _, tail = lines[pc].partition(' ')
                    pc += 1
                    args = [a.strip() for a in tail.split(',')]
                    if op in ('goto_if_defeated', 'lockall', 'setvar'):
                        continue
                    if op == 'hidefollower':
                        hidden = args[0] == 'TRUE'
                    elif op == 'getplayerxy':
                        variables[args[0]], variables[args[1]] = player
                    elif op == 'goto_if_eq':
                        if variables[args[0]] == int(args[1]):
                            pc = labels[args[2]]
                    elif op == 'goto':
                        pc = labels[args[0]]
                    elif op == 'applymovement':
                        self.assertEqual(args[0], scientist['local_id'])
                        movement = labels[args[1]]
                        while lines[movement] != 'step_end':
                            dx, dy = {'walk_right': (1,0), 'walk_left': (-1,0)}[lines[movement]]
                            pos = pos[0]+dx, pos[1]+dy
                            self.assertNotEqual(pos, player)
                            self.assertTrue(hidden or pos != follower)
                            self.assertEqual(grid[pos[1]*width+pos[0]], 0x3281)
                            movement += 1
                        pending = True
                    elif op == 'waitmovement':
                        pending = False
                    elif op == 'turnobject':
                        self.assertEqual(args[0], 'LOCALID_PLAYER')
                        player_direction = args[1]
                    elif op == 'faceplayer':
                        faced = True
                    elif op == 'trainerbattle_lavaridge':
                        self.assertFalse(pending)
                        self.assertTrue(faced)
                        self.assertEqual(player_direction, 'DIR_NORTH')
                        self.assertEqual(pos, (player[0], player[1]-1))
                        break
                    else:
                        self.fail('Unmodeled scene command: ' + lines[pc-1])
                else:
                    self.fail('Challenge never starts')
        # Direct talk keeps the standard engine's mutually facing trainer interaction.
        trainers = (ROOT / 'data/scripts/three_horizons/chapter9.inc').read_text()
        direct = trainers.split('TH_Trainer9_SUPER_NERD_MIGUEL::',1)[1].split('TH_Trainer9_SUPER_NERD_MIGUEL_Intro:',1)[0]
        self.assertIn('trainerbattle_single TRAINER_TH9_SUPER_NERD_MIGUEL', direct)
        for name in ('Dome', 'Helix'):
            reward = trainers.split(f'TH_Fossil_{name}::',1)[1].split('\nTH_Fossil_',1)[0]
            self.assertIn('goto_if_defeated TRAINER_TH9_SUPER_NERD_MIGUEL', reward)


if __name__ == '__main__':
    unittest.main()
