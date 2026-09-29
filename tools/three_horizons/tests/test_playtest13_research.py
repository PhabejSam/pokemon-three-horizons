"""Execute authored research script branches; native tests own the C state API."""
from pathlib import Path
import re
import unittest
from tools.three_horizons.tests.test_playtest11_maps import ROOT, map_data, tiles


class Scene:
    def __init__(self, gear=True, answer=1):
        self.lines, self.labels = [], {}
        for path in (ROOT / 'data/scripts/three_horizons').glob('*.inc'):
            for raw in path.read_text(encoding='utf-8').splitlines():
                line = raw.split('@', 1)[0].strip()
                if not line:
                    continue
                if line.endswith(':'):
                    self.labels[line.rstrip(':')] = len(self.lines)
                else:
                    self.lines.append(line)
        self.gear, self.answer = gear, answer
        self.vars, self.flags, self.entries, self.photos = {}, set(), set(), set()
        self.messages, self.flashes, self.completed = [], 0, []

    def value(self, key):
        if key in ('NO', 'FALSE'): return 0
        if key in ('YES', 'TRUE'): return 1
        if key.startswith('VAR_'): return self.vars.get(key, 0)
        if key.lstrip('-').isdigit(): return int(key)
        return key

    def run(self, start):
        pc, stack = self.labels[start], []
        for _ in range(400):
            line = self.lines[pc]; pc += 1
            op, _, tail = line.partition(' ')
            args = [x.strip() for x in tail.split(',')]
            if op == 'end': return
            if op == 'return':
                if not stack: return
                pc = stack.pop()
            elif op in ('goto', 'call'):
                if op == 'call': stack.append(pc)
                pc = self.labels[args[0]]
            elif op in ('goto_if_eq', 'goto_if_lt', 'goto_if_gt'):
                a, b = self.value(args[0]), self.value(args[1])
                if {'goto_if_eq': a == b, 'goto_if_lt': a < b, 'goto_if_gt': a > b}[op]:
                    pc = self.labels[args[2]]
            elif op in ('goto_if_set', 'goto_if_unset'):
                if (args[0] in self.flags) == (op == 'goto_if_set'):
                    pc = self.labels[args[1]]
            elif op == 'setvar': self.vars[args[0]] = self.value(args[1])
            elif op == 'setflag': self.flags.add(args[0])
            elif op == 'getplayerxy':
                self.vars[args[0]], self.vars[args[1]] = 0, 0
            elif op == 'msgbox':
                self.messages.append(args[0])
                if len(args) > 1 and args[1] == 'MSGBOX_YESNO': self.vars['VAR_RESULT'] = self.answer
            elif op == 'special':
                value = self.vars.get('VAR_0x8004')
                if args[0] == 'TH_ScriptResearchObserve': self.entries.add(value)
                elif args[0] == 'TH_ScriptResearchPhotoStatus':
                    self.vars['VAR_RESULT'] = 0 if not self.gear else (2 if value in self.photos else 1)
                elif args[0] == 'TH_ScriptTakeResearchPhoto':
                    self.vars['VAR_RESULT'] = int(value not in self.photos)
                    self.photos.add(value)
                elif args[0] == 'TH_ScriptResearchCompleteCall':
                    self.completed.append((value, len(self.messages)))
                elif args[0] != 'TH_RefreshFollower': raise AssertionError(line)
            elif op == 'fadescreen' and args[0] == 'FADE_TO_WHITE': self.flashes += 1
            elif op in ('lock', 'lockall', 'release', 'releaseall', 'closemessage', 'hidefollower',
                        'applymovement', 'waitmovement', 'playmoncry', 'waitmoncry', 'faceplayer',
                        'playse', 'waitse', 'delay', 'fadescreen'):
                pass
            else: raise AssertionError(line)
        raise AssertionError('scene did not finish')


class ResearchScripts(unittest.TestCase):
    def test_ship_partner_capacity_and_access(self):
        data = map_data('TH12_SSAnne_Deck')
        objects = data['object_events']
        partners = [o for o in objects if o['script'] in ('TH13_Ship_Marill', 'TH13_Ship_Wingull')]
        self.assertEqual(len(partners), 2)
        self.assertLessEqual(len(objects) + 2, 16) # player and large/small follower
        width, height, grid = tiles(data['name'])
        floor = {(x,y) for y in range(height) for x in range(width)
                 if grid[y*width+x] & 0xc00 == 0 and grid[y*width+x] >> 12 == 3}
        for o in partners:
            self.assertIn((o['x'], o['y']), floor)
            self.assertEqual(o['flag'], '0')
        for sailor_y in (9,10):
            for wander_x in range(5,8):
                for wander_y in range(8,11):
                    positions = [(o['x'],o['y']) for o in objects]
                    positions[0] = (12,sailor_y); positions[3] = (wander_x,wander_y)
                    self.assertEqual(len(positions), len(set(positions)))
                    for entry in [(w['x'],w['y']) for w in data['warp_events']]:
                        seen, queue = {entry}, [entry]
                        for x,y in queue:
                            for p in ((x-1,y),(x+1,y),(x,y-1),(x,y+1)):
                                if p in floor and p not in positions and p not in seen:
                                    seen.add(p); queue.append(p)
                        for x,y in positions:
                            self.assertTrue(seen.intersection(((x-1,y),(x+1,y),(x,y-1),(x,y+1))), (entry,x,y))
                        for w in data['warp_events']: self.assertIn((w['x'],w['y']), seen)

    def test_existing_sightings_record_individually_without_forcing_photos(self):
        scenes = [('TH_EventScript_Hoothoot', 'HOOTHOOT'), ('TH12_Forest_Treecko', 'FOREST_TREECKO'),
                  ('TH12_Forest_Shroomish', 'FOREST_SHROOMISH'), ('TH12_Moon_Gathering', 'MT_MOON')]
        for label, key in scenes:
            with self.subTest(scene=label):
                s = Scene(gear=False); s.run(label)
                self.assertEqual(s.entries, {'TH_RESEARCH_' + key})
                self.assertFalse(s.photos)
                self.assertEqual(s.flashes, 0)
                s.gear = True; s.answer = 0; s.run(label)
                self.assertFalse(s.photos)
                s.answer = 1; s.run(label)
                self.assertEqual(s.photos, {'TH_PHOTO_' + key})
                self.assertEqual(s.flashes, 1)
                s.run(label)
                self.assertEqual(s.flashes, 1)
                self.assertIn('TH13_ResearchPhoto_RecordedText', s.messages)

    def test_calls_complete_after_their_authored_text(self):
        for label, call in [('Activation','ACTIVATION'), ('Route10','ROUTE10'), ('Lavender','LAVENDER')]:
            s = Scene(); s.run('TH13_ResearchCall_' + label)
            self.assertGreaterEqual(len(s.messages), 3)
            self.assertEqual(s.completed, [('TH_CALL_' + call, len(s.messages))])
            self.assertEqual(s.flashes, 0)

    def test_ship_partners_share_observation_without_repeat_rewards(self):
        for label in ('TH13_Ship_Marill', 'TH13_Ship_Wingull'):
            s = Scene(); s.run(label); s.run(label)
            self.assertEqual(s.entries, {'TH_RESEARCH_SHIP'})
            self.assertEqual(s.photos, {'TH_PHOTO_SHIP'})
            self.assertEqual(s.flashes, 1)

    def test_research_text_fits_two_line_dialogue_pages(self):
        paths = ['chapter13_research.inc', 'lab.inc']
        for name in paths:
            text = (ROOT/'data/scripts/three_horizons'/name).read_text(encoding='utf-8')
            for encoded in re.findall(r'\.string "(.*?)"', text):
                for page in encoded.split('\\p'):
                    lines = re.split(r'\\[nl]', page)
                    # Existing scrolling dialogue is allowed; new calls use pages.
                    if name == 'chapter13_research.inc': self.assertLessEqual(len(lines), 2, page)
                    for line in lines:
                        line = re.sub(r'\{PLAYER\}|\{RIVAL\}', 'ABCDEFG', line).rstrip('$')
                        self.assertLessEqual(len(line), 38, line)


if __name__ == '__main__': unittest.main()
