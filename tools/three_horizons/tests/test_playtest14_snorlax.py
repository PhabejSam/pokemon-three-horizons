"""Execute owned script branches with mocked UI/trade/battle boundaries.
Native tests separately exercise compiled trades, outcomes, items and collision.
"""
import json,re,unittest
from tools.three_horizons.tests.test_playtest11_maps import ROOT,map_data,tiles,reachable
NAMES=['TH14_Route11_EastEntrance_1F','TH14_Route11_EastEntrance_2F','TH14_Route12_Landing']
DONE='FLAG_TH14_SNORLAX_RESOLVED'
class Scene:
    def __init__(self):
        self.lines=(ROOT/'data/scripts/three_horizons/chapter14_snorlax.inc').read_text().splitlines()
        self.labels={m[1]:i+1 for i,l in enumerate(self.lines) if (m:=re.match(r'^(\w+)::?$',l))}
        self.flags=set();self.items=set();self.vars={};self.messages=[];self.trace=[]
        self.yes=True;self.outcome=1;self.battles=0;self.refresh=0;self.locked=False;self.removed=[]
        self.slot=0;self.species='SPECIES_NIDORINO';self.trade_ok=True;self.trades=0;self.caught=30;self.full=False
    def run(self,label):
        pc=self.labels[label];stack=[]
        def val(s):return self.vars.get(s,{'TRUE':1,'FALSE':0,'YES':1,'NO':0,'PARTY_SIZE':6,'B_OUTCOME_WON':1,'B_OUTCOME_CAUGHT':7}.get(s,int(s) if s.isdigit() else s))
        for _ in range(250):
            line=self.lines[pc].strip();pc+=1
            if not line or line.startswith('@') or line.endswith(':'):continue
            op,_,arg=line.partition(' ');a=[x.strip() for x in arg.split(',')];self.trace.append(line)
            if op=='end':return
            if op=='return':
                if not stack:return
                pc=stack.pop()
            elif op=='goto':pc=self.labels[a[0]]
            elif op=='call':
                if a[0]=='TH14_Snorlax_Awaken':pass
                elif a[0]=='EventScript_GetInGameTradeSpeciesInfo':self.vars.update(VAR_0x8005='INGAME_TRADE_NIDORINOA',VAR_0x8009='SPECIES_NIDORINO')
                elif a[0]=='EventScript_ChooseMonForInGameTrade':self.vars['VAR_0x8004']=self.slot
                elif a[0]=='EventScript_GetInGameTradeSpecies':self.vars['VAR_RESULT']=self.species
                elif a[0]=='EventScript_DoInGameTrade':self.trades+=int(self.trade_ok)
                else:stack.append(pc);pc=self.labels[a[0]]
            elif op in ('goto_if_set','goto_if_unset'):
                if (a[0] in self.flags)==(op=='goto_if_set'):pc=self.labels[a[1]]
            elif op in ('goto_if_eq','goto_if_ne','goto_if_ge','goto_if_lt'):
                x,y=val(a[0]),val(a[1]);ok=(x==y if op=='goto_if_eq' else x!=y if op=='goto_if_ne' else x>=y if op=='goto_if_ge' else x<y)
                if ok:pc=self.labels[a[2]]
            elif op=='setvar':self.vars[a[0]]=val(a[1])
            elif op=='setflag':self.flags.add(a[0])
            elif op=='checkitem':self.vars['VAR_RESULT']=int(a[0] in self.items)
            elif op=='msgbox':
                self.messages.append(a[0])
                if len(a)>1 and a[1]=='MSGBOX_YESNO':self.vars['VAR_RESULT']=int(self.yes)
            elif op in ('lock','lockall'):self.locked=True
            elif op in ('release','releaseall'):self.locked=False
            elif op=='removeobject':self.removed.append(a[0])
            elif op=='dowildbattle':
                self.battles+=1
                if self.outcome in (2,3,9):self.locked=False;return # native blackout does not return to script
            elif op=='specialvar':
                if a[1]=='GetBattleOutcome':self.vars[a[0]]=self.outcome
                elif a[1]=='GetFrlgPokedexCount':self.vars['VAR_0x8006']=self.caught;self.vars[a[0]]=0
                else:raise AssertionError(line)
            elif op=='special':
                if a[0]=='TH_RefreshFollower':self.refresh+=1
                elif a[0]=='TH14_ConfirmNinaTrade':self.vars['VAR_RESULT']=int(self.trades==1)
                elif a[0]=='TH14_ScriptGiveUniqueItem':
                    item=self.vars['VAR_0x8004'];flag=self.vars['VAR_0x8005'];result=2 if item in self.items or flag in self.flags else 0 if self.full else 1
                    self.vars['VAR_RESULT']=result
                    if result:self.flags.add(flag);self.items.add(item)
                else:raise AssertionError(line)
            elif op not in ('faceplayer','closemessage','hidefollower','setwildbattle','waitse','playmoncry','waitmoncry','delay','playfanfare','waitfanfare','bufferspeciesname','buffernumberstring','fadescreen'):
                raise AssertionError('unhandled '+line)
        raise AssertionError('did not terminate')
class Snorlax(unittest.TestCase):
    def test_gate_accessible_without_flute_and_preserves_route_locals(self):
        route=map_data('TH13_Route11');self.assertEqual(len(route['object_events']),13)
        self.assertEqual([o['local_id'] for o in route['object_events']],[f'LOCALID_TH13_ROUTE11_{i}' for i in range(1,14)])
        self.assertEqual(route['warp_events'][0]['dest_map'],'MAP_TH13_DIGLETTS_CAVE_SOUTH_ENTRANCE')
        self.assertEqual([(w['x'],w['y']) for w in route['warp_events'][1:]],[(58,10),(65,10)])
        groups=json.loads((ROOT/'data/maps/map_groups.json').read_text())['gMapGroup_ThreeHorizons14']
        self.assertEqual(groups[34:],NAMES)
        for n in NAMES:
            self.assertIn(n,json.loads((ROOT/'tools/mapjson/three_horizons_maps.json').read_text())['maps'])
            self.assertIn(f'data/maps/{n}/scripts.inc',(ROOT/'data/scripts/three_horizons/maps.inc').read_text())
        self.assertEqual([w['dest_warp_id'] for w in map_data(NAMES[0])['warp_events']],['1','1','2','2','0'])
        self.assertEqual(map_data(NAMES[1])['warp_events'][0]['dest_warp_id'],'4')
    def test_snorlax_blocks_all_walkable_lanes_and_accepted_outcome_opens_footprint(self):
        w,h,t=tiles(NAMES[2]);self.assertEqual((w,h),(24,22))
        def walk(block):
            seen={(0,10)};todo=[(0,10)]
            for x,y in todo:
                for nx,ny in [(x+1,y),(x-1,y),(x,y+1),(x,y-1)]:
                    if 0<=nx<w and 0<=ny<h and (nx,ny) not in seen and (nx,ny) not in block and t[ny*w+nx]>>12==3 and not t[ny*w+nx]&0xc00:
                        seen.add((nx,ny));todo.append((nx,ny))
            return seen
        before=walk({(14,10)});after=walk(set())
        self.assertNotIn((15,10),before);self.assertIn((14,10),after);self.assertIn((15,7),after);self.assertIn((15,15),after)
        self.assertTrue(all(7<=y<=15 for x,y in after if x>=14))
        for x,y in [(14,6),(15,6),(14,16),(15,16)]:self.assertTrue(t[y*w+x]&0xc00)
        m=map_data(NAMES[2]);self.assertEqual(len(m['object_events']),1)
        o=m['object_events'][0];self.assertEqual((o['x'],o['y'],o['flag']),(14,10,DONE))
        hidden=[b for b in m['bg_events'] if b['type']=='hidden_item'];self.assertEqual(len(hidden),1)
        self.assertEqual((hidden[0]['item'],hidden[0]['flag'],hidden[0]['x'],hidden[0]['y'],hidden[0]['underfoot']),('ITEM_LEFTOVERS','FLAG_TH14_PICKUP_44',14,10,True))
        self.assertFalse(m['warp_events']);self.assertEqual(m['connections'],[{'map':'MAP_TH13_ROUTE11','offset':0,'direction':'left'}])
    def test_no_flute_or_decline_never_starts_battle(self):
        for flute in (False,True):
            s=Scene();s.yes=False
            if flute:s.items.add('ITEM_POKE_FLUTE')
            s.run('TH14_Snorlax');self.assertEqual(s.battles,0);self.assertFalse(s.flags|set(s.removed));self.assertFalse(s.locked)
    def test_every_nonwin_and_blackout_retains_roadblock_and_retry(self):
        for result in [0,2,3,4,5,6,8,9,10]:
            s=Scene();s.items.add('ITEM_POKE_FLUTE');s.outcome=result;s.run('TH14_Snorlax')
            self.assertNotIn(DONE,s.flags);self.assertFalse(s.removed);self.assertFalse(s.locked)
            s.outcome=1;s.run('TH14_Snorlax');self.assertIn(DONE,s.flags);self.assertEqual(s.battles,2)
    def test_catch_or_win_only_commits_after_actual_result_and_repeat_is_inert(self):
        for result in (1,7):
            s=Scene();s.items.add('ITEM_POKE_FLUTE');s.outcome=result;s.run('TH14_Snorlax')
            self.assertEqual(s.flags,{DONE});self.assertEqual(len(s.removed),1);self.assertEqual(s.refresh,1)
            self.assertLess(s.trace.index('specialvar VAR_RESULT, GetBattleOutcome'),s.trace.index('setflag '+DONE))
            s.run('TH14_Snorlax');self.assertEqual(s.battles,1);self.assertFalse(s.locked)
    def test_trade_cancel_wrong_egg_failure_success_and_repeat(self):
        for yes,slot,species,ok in [(False,0,'SPECIES_NIDORINO',True),(True,6,'SPECIES_NIDORINO',True),(True,0,'SPECIES_NONE',True),(True,2,'SPECIES_PIDGEY',True),(True,3,'SPECIES_NIDORINO',False),(True,4,'SPECIES_NIDORINO',True)]:
            s=Scene();s.yes=yes;s.slot=slot;s.species=species;s.trade_ok=ok;s.run('TH14_Gate_Turner')
            expect=yes and slot<6 and species=='SPECIES_NIDORINO' and ok
            self.assertEqual('FLAG_TH14_NINA_TRADE' in s.flags,expect);self.assertEqual(s.trades,int(expect));self.assertFalse(s.locked)
            if expect:s.run('TH14_Gate_Turner');self.assertEqual(s.trades,1)
    def test_itemfinder_all_owned_species_threshold_full_pocket_retry_and_once(self):
        for count in (29,30,31):
            s=Scene();s.caught=count;s.full=True;s.run('TH14_Gate_Aide');self.assertNotIn('FLAG_TH14_ITEMFINDER',s.flags)
            self.assertIn('setvar VAR_0x8004, 1',s.trace)
            s.full=False;s.run('TH14_Gate_Aide');self.assertEqual('FLAG_TH14_ITEMFINDER' in s.flags,count>=30)
            self.assertFalse(s.locked)
    def test_endpoint_visible_barricades_and_flavor_only_binoculars(self):
        source=(ROOT/'data/scripts/three_horizons/chapter14_snorlax.inc').read_text()
        self.assertIn('Bridge maintenance ahead.',source);self.assertNotIn('Playtest ends',source)
        for done in (False,True):
            s=Scene()
            if done:s.flags.add(DONE)
            before=set(s.flags);s.run('TH14_Gate_LeftBinoculars');self.assertEqual(s.flags,before)
            self.assertEqual(s.messages,['TH14_Gate_ViewClear' if done else 'TH14_Gate_ViewAsleep'])
    def test_owned_scene_has_no_unlinked_firered_only_text_or_wake_dependency(self):
        source=(ROOT/'data/scripts/three_horizons/chapter14_snorlax.inc').read_text()
        self.assertNotIn('Trade_Text_',source)
        self.assertNotIn('call EventScript_AwakenSnorlax',source)
if __name__=='__main__':unittest.main()
