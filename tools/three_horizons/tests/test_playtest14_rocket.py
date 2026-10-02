"""Approved Rocket staging and script branches; native tests cover battle APIs."""
import json
import re
import unittest
from tools.three_horizons.tests.test_playtest11_maps import ROOT, map_data, tiles
from tools.three_horizons.tests.test_playtest14_travel import party

def source():
    return (ROOT/'data/scripts/three_horizons/chapter14_hideout.inc').read_text()

def body(name):
    return re.search(r'^'+name+r'::?\n(.*?)(?=^\w+::?$|\Z)',source(),re.M|re.S)[1]

class Rocket(unittest.TestCase):
    def test_trio_staging_and_mandatory_two_lane_trigger(self):
        m=map_data('TH14_RocketHideout_B4F')
        actors=m['object_events'][9:]
        self.assertEqual([(o['x'],o['y']) for o in actors],[(17,10),(19,10),(21,10)])
        self.assertEqual([o['graphics_id'] for o in actors],['OBJ_EVENT_GFX_TH_JESSIE','OBJ_EVENT_GFX_TH_JAMES','OBJ_EVENT_GFX_MEOWTH'])
        for o in actors:
            self.assertEqual(o['flag'],'FLAG_TH14_TRIO_DEFEATED')
            self.assertEqual(o['trainer_type'],'TRAINER_TYPE_NONE')
        self.assertLessEqual(len(m['object_events'])+2,16)
        self.assertEqual({(e['x'],e['y']) for e in m['coord_events']},{(17,13),(18,13)})
        self.assertTrue(all(e['script']=='TH14_RocketTrioTrigger' for e in m['coord_events']))
        w,h,c=tiles('TH14_RocketHideout_B4F')
        for x,y in [(17,9),(19,9),(21,9),(17,10),(19,10),(21,10),(17,14),(18,14)]:
            self.assertFalse(c[y*w+x]&0xc00,(x,y))

    def test_trio_requires_two_usable_not_eggs_and_retreats_safely(self):
        text=body('TH14_RocketTrioTrigger')
        self.assertIn('goto_if_set FLAG_TH14_TRIO_DEFEATED',text)
        self.assertIn('setvar VAR_0x8004, PARTY_SIZE',text)
        self.assertIn('CountPartyAliveNonEggMons_IgnoreVar0x8004Slot',text)
        self.assertLess(text.index('goto_if_lt VAR_RESULT, 2'),text.index('special TH14_BeginRocketPair'))
        self.assertIn('hidefollower TRUE',text)
        retreat=body('TH14_RocketTrioTooFew')
        self.assertIn('applymovement LOCALID_PLAYER, TH14_RocketTrioRetreat',retreat)
        self.assertIn('goto TH14_RocketTrioRelease',retreat)
        self.assertEqual(body('TH14_RocketTrioRetreat').strip(),'walk_down\n    step_end')
        self.assertIn('special TH_RefreshFollower',body('TH14_RocketTrioRelease'))

    def test_trio_two_distinct_opponents_and_win_only_cleanup(self):
        battle=body('TH14_RocketTrioBattle')
        self.assertIn('TRAINER_TH14_JESSIE',battle);self.assertIn('TRAINER_TH14_JAMES',battle)
        self.assertNotIn('trainerbattle_single',battle)
        win=body('TH14_RocketTrioVictory')
        self.assertLess(win.index('TH14_CompleteRocketPair'),win.index('removeobject'))
        self.assertIn('goto_if_eq VAR_RESULT, FALSE, TH14_RocketTrioRelease',win)
        self.assertEqual(win.count('removeobject'),3)
        registry=(ROOT/'src/data/three_horizons_rematches.h').read_text()
        for name in ('JESSIE','JAMES','GIOVANNI'):
            self.assertNotIn('TRAINER_TH14_'+name,registry)

    def test_authored_parties_preserve_art_and_giovanni_donor(self):
        text=(ROOT/'src/data/trainers.party').read_text()
        donor=party((ROOT/'src/data/trainers_frlg.party').read_text(),'TRAINER_BOSS_GIOVANNI')
        self.assertEqual(party(text,'TRAINER_TH14_GIOVANNI'),donor.replace('Music: Aqua','Music: Suspicious'))
        for name,species,ability,moves in [('JESSIE','Arbok','Intimidate',['Crunch','Acid','Glare','Screech']),('JAMES','Koffing','Levitate',['Sludge','Assurance','Smokescreen','Haze'])]:
            p=party(text,'TRAINER_TH14_'+name)
            self.assertIn('Pic: TH '+name.title(),p)
            self.assertIn('Multi Party: Half',p);self.assertIn('Level: 28',p)
            self.assertIn(species,p);self.assertIn('Ability: '+ability,p)
            for move in moves:self.assertIn('- '+move,p)
            self.assertNotIn('Meowth',p)

    def test_scope_delivery_requires_giovanni_and_repeats_without_duplicate(self):
        text=body('TH14_RocketHideout_B4F_EventScript_SilphScope')
        self.assertLess(text.index('goto_if_not_defeated TRAINER_TH14_GIOVANNI'),text.index('TH14_ScriptGiveUniqueItem'))
        self.assertLess(text.index('goto_if_eq VAR_RESULT, 0'),text.index('removeobject'))
        self.assertIn('goto_if_eq VAR_RESULT, 2, TH14_ScopeLead',text)
        self.assertIn('TH14_ScopeLeadText',body('TH14_ScopeLead'))
        self.assertTrue(any(e.get('script')=='TH14_RocketHideout_B4F_EventScript_SilphScope' and (e['x'],e['y'])==(20,5) for e in map_data('TH14_RocketHideout_B4F')['bg_events']))
        self.assertNotIn('FLAG_BADGE04_GET',source())
        self.assertIn('addobject LOCALID_TH14_ROCKETHIDEOUT_B4F_2',body('TH14_GiovanniVictory'))

    def test_all_speakers_and_return_lead_are_present_no_placeholder(self):
        text=source()
        for word in ('JESSIE:','JAMES:','MEOWTH:','notebooks','ordinary eyes','POKéMON TOWER','Come back with two'):
            self.assertIn(word,text)
        self.assertNotIn('TH14_HideoutPending',text)
        pending=json.loads((ROOT/'tools/three_horizons/chapter14_content.json').read_text())['unfinishedInteractions']
        self.assertFalse(pending)

    def test_scope_script_full_bag_retry_and_repeat_run_actual_branches(self):
        lines=source().splitlines()
        labels={m[1]:i+1 for i,line in enumerate(lines) if (m:=re.match(r'^(\w+)::?$',line))}
        state={'won':False,'full':True,'receipt':False,'quantity':0,'removed':False,'messages':[]}
        def interact():
            pc=labels['TH14_RocketHideout_B4F_EventScript_SilphScope'];result=0
            for _ in range(100):
                line=lines[pc].strip();pc+=1
                if not line or line.startswith('@') or line.endswith(':'):continue
                op,_,args=line.partition(' ');a=[x.strip() for x in args.split(',')]
                if op=='end':return
                if op=='goto':pc=labels[a[0]]
                elif op=='goto_if_not_defeated':
                    if not state['won']:pc=labels[a[1]]
                elif op=='goto_if_eq':
                    if result==int(a[1]):pc=labels[a[2]]
                elif op=='special':
                    self.assertEqual(a[0],'TH14_ScriptGiveUniqueItem')
                    result=2 if state['receipt'] else 0 if state['full'] else 1
                    if result==1:state['quantity']+=1;state['receipt']=True
                elif op=='msgbox':state['messages'].append(a[0])
                elif op=='removeobject':state['removed']=True
                elif op not in ('lockall','setvar','playfanfare','waitfanfare','releaseall'):
                    self.fail('unhandled Scope instruction: '+line)
            self.fail('Scope script did not terminate')
        interact();self.assertEqual(state['quantity'],0);self.assertFalse(state['messages'])
        state['won']=True;interact()
        self.assertFalse(state['receipt']);self.assertFalse(state['removed']);self.assertEqual(state['quantity'],0)
        self.assertEqual(state['messages'],['TH14_ScopeNoRoomText'])
        state['full']=False;state['messages']=[];interact()
        self.assertTrue(state['receipt']);self.assertTrue(state['removed']);self.assertEqual(state['quantity'],1)
        self.assertEqual(state['messages'],['TH14_ScopeReceived','TH14_ScopeLeadText'])
        for _ in range(3):
            state['messages']=[];interact()
            self.assertEqual(state['quantity'],1);self.assertEqual(state['messages'],['TH14_ScopeLeadText'])

if __name__=='__main__':unittest.main()
