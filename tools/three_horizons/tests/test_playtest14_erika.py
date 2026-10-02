"""Erika's independent battle/reward paths and exact donor Gym boundaries."""
import json
import re
import unittest
from tools.three_horizons.tests.test_playtest11_maps import ROOT, map_data, tiles, reachable
from tools.three_horizons.tests.test_playtest14_travel import party

GYM = 'TH14_CeladonCity_Gym'
PREFIX = GYM + '_EventScript_'
BADGE = 'FLAG_BADGE04_GET'
RECEIPT = 'FLAG_TH14_ERIKA_TM'
TRAINER = 'TRAINER_TH14_ERIKA'


def chapter():
    files = ['chapter14_celadon.inc', 'chapter14_gym.inc']
    return '\n'.join((ROOT/'data/scripts/three_horizons'/f).read_text()
                     for f in files if (ROOT/'data/scripts/three_horizons'/f).exists())


class ErikaScript:
    """Execute authored control flow, substituting only battle/UI/transaction boundaries.

    Native tests cover the actual gift and battle configuration. A battle loss
    leaves the script for blackout, matching the engine's normal trainer path.
    Unknown instructions fail instead of silently passing over a new effect.
    """
    def __init__(self, flags=(), defeated=False, win=True, gift=1):
        self.lines = chapter().splitlines()
        self.labels = {m[1]: i+1 for i,line in enumerate(self.lines)
                       if (m := re.match(r'^(\w+)::?$', line))}
        self.flags = set(flags); self.defeated = defeated; self.win = win; self.gift = gift
        self.vars = {}; self.messages = []; self.calls = []; self.battles = 0
        self.badges = 0; self.locked = False; self.blackout = False

    def value(self, s):
        if s == 'TRUE': return 1
        if s == 'FALSE': return 0
        return self.vars.get(s, int(s) if s.isdecimal() else s)

    def run(self, label):
        pc = self.labels[label]
        for _ in range(200):
            line = self.lines[pc].strip(); pc += 1
            if not line or line.startswith('@') or line.endswith(':'): continue
            op, _, rest = line.partition(' '); args = [a.strip() for a in rest.split(',')]
            if op == 'end': return
            if op == 'goto': pc = self.labels[args[0]]
            elif op in ('goto_if_set', 'goto_if_unset'):
                if (args[0] in self.flags) == (op == 'goto_if_set'): pc = self.labels[args[1]]
            elif op in ('goto_if_eq','goto_if_ne'):
                if (self.value(args[0]) == self.value(args[1])) == (op == 'goto_if_eq'): pc = self.labels[args[2]]
            elif op == 'setvar': self.vars[args[0]] = self.value(args[1])
            elif op == 'setflag':
                self.flags.add(args[0]); self.badges += args[0] == BADGE
            elif op == 'trainerbattle_single':
                assert args[0] == TRAINER
                if self.defeated: continue
                self.battles += 1
                if not self.win:
                    self.blackout = True; self.locked = False; return
                self.defeated = True; pc = self.labels[args[3]]
            elif op == 'special':
                assert args[0] == 'TH14_ScriptGiveUniqueItem'
                self.calls.append((self.vars['VAR_0x8004'], self.vars['VAR_0x8005']))
                self.vars['VAR_RESULT'] = self.gift
                if self.gift: self.flags.add(RECEIPT)
            elif op == 'msgbox': self.messages.append(args[0])
            elif op in ('lock', 'lockall'): self.locked = True
            elif op in ('release', 'releaseall'): self.locked = False
            elif op not in ('faceplayer','playfanfare','waitfanfare','closemessage'):
                raise AssertionError('unhandled script command: ' + line)
        raise AssertionError('script did not terminate')


class Erika(unittest.TestCase):
    def test_erika_before_or_after_giovanni(self):
        outcomes=[]
        for scope in (False, True):
            s=ErikaScript(flags=['FLAG_TH14_SILPH_SCOPE'] if scope else [])
            s.run(PREFIX+'Erika')
            self.assertEqual(s.battles,1); self.assertTrue(s.defeated)
            self.assertIn(BADGE,s.flags); self.assertIn(RECEIPT,s.flags)
            self.assertFalse(s.locked)
            outcomes.append((s.messages,s.calls,s.badges))
        self.assertEqual(*outcomes)

    def test_loss_does_not_grant_badge(self):
        s=ErikaScript(win=False); s.run(PREFIX+'Erika')
        self.assertTrue(s.blackout); self.assertFalse(s.defeated)
        self.assertNotIn(BADGE,s.flags); self.assertNotIn(RECEIPT,s.flags)
        self.assertFalse(s.calls); self.assertEqual(s.badges,0)

    def test_victory_sets_badge_once_tm_full_bag_retry(self):
        s=ErikaScript(gift=0); s.run(PREFIX+'Erika')
        self.assertIn(BADGE,s.flags); self.assertNotIn(RECEIPT,s.flags)
        self.assertTrue(s.defeated); self.assertFalse(s.locked)
        s.gift=1; s.run(PREFIX+'Erika')
        self.assertIn(RECEIPT,s.flags)
        self.assertEqual(s.battles,1); self.assertEqual(s.badges,1)
        self.assertEqual(s.calls,[('ITEM_TM19','FLAG_TH14_ERIKA_TM')]*2)
        s.run(PREFIX+'Erika'); self.assertEqual(len(s.calls),2)
        self.assertEqual(s.badges,1); self.assertFalse(s.locked)
        # Owned in Bag/PC is a separate result, never a false new-receipt fanfare.
        owned=ErikaScript(gift=2); owned.run(PREFIX+'Erika')
        self.assertIn(RECEIPT,owned.flags)
        self.assertNotEqual(s.messages[:],owned.messages)

    def test_gym_guide_and_repeat_dialogue_after_win(self):
        for label in (PREFIX+'GymStatue','TH14_CeladonCity_GameCorner_EventScript_GymGuy'):
            before=ErikaScript(); before.run(label)
            after=ErikaScript(flags=[BADGE]); after.run(label)
            self.assertNotEqual(before.messages,after.messages,label)
            self.assertFalse(before.calls or after.calls)
            self.assertFalse(before.locked or after.locked)
        s=ErikaScript(flags=[BADGE,RECEIPT],defeated=True);s.run(PREFIX+'Erika')
        self.assertEqual(s.battles,0);self.assertFalse(s.calls)
        self.assertEqual(s.badges,0)

    def test_all_eight_authored_parties_and_seven_ordinary_rematches(self):
        content=json.loads((ROOT/'tools/three_horizons/chapter14_content.json').read_text())
        rows=[r for r in content['trainers'] if r['map']==GYM]
        self.assertEqual(len(rows),8)
        donor=(ROOT/'src/data/trainers_frlg.party').read_text()
        current=(ROOT/'src/data/trainers.party').read_text()
        registry=(ROOT/'src/data/three_horizons_rematches.h').read_text()
        for row in rows:
            expected=party(donor,row['donor'])
            if row['constant']==TRAINER: expected=expected.replace('Gender: Male','Gender: Female')
            self.assertEqual(party(current,row['constant']),expected)
            record='{'+row['constant']+', MAP_TH14_CELADON_CITY_GYM, '+str(row['localId'])+'}'
            self.assertEqual(record in registry,row['rematch'])
        self.assertNotIn(TRAINER+',',registry)
        self.assertFalse(any(r['ownerTask']==11 for r in content['unfinishedInteractions']))
        self.assertIn({'item':'ITEM_TM19','receipt':RECEIPT},content['uniqueItems'])

    def test_donor_sightlines_cut_access_and_owned_script_bindings(self):
        m=map_data(GYM); d=map_data('CeladonCity_Gym_Frlg')
        w,h,blocks=tiles(GYM)
        labels=set(re.findall(r'^(\w+):',chapter(),re.M))
        for i,(a,b) in enumerate(zip(m['object_events'],d['object_events'])):
            for k in ('x','y','elevation','movement_type','trainer_type','trainer_sight_or_berry_tree_id'):
                self.assertEqual(a[k],b[k],(i,k))
            self.assertIn(a['script'],labels|{'TH_Journey_Tree'})
            self.assertFalse(blocks[a['y']*w+a['x']]&0xc00)
            if a['trainer_type']=='TRAINER_TYPE_NORMAL':
                dx,dy={'MOVEMENT_TYPE_FACE_DOWN':(0,1),'MOVEMENT_TYPE_FACE_LEFT':(-1,0),'MOVEMENT_TYPE_FACE_RIGHT':(1,0)}[a['movement_type']]
                x,y=a['x']+dx,a['y']+dy
                self.assertTrue(0<=x<w and 0<=y<h)
                self.assertFalse(blocks[y*w+x]&0xc00,(i,'first sightline tile'))
        self.assertEqual(len(m['object_events']),11)
        # Seven ordinary trainers + leader + three Cut trees: room for player/follower.
        self.assertEqual([o['flag'] for o in m['object_events'][8:]],['FLAG_TEMP_12','FLAG_TEMP_13','FLAG_TEMP_14'])
        text=chapter().split('@ PT14 Celadon Gym',1)[-1]
        for forbidden in ('set_gym_trainers_frlg','FLAG_DEFEATED_ERIKA','FLAG_GOT_TM19_FROM_ERIKA'):
            self.assertNotIn(forbidden,text)


if __name__=='__main__': unittest.main()
