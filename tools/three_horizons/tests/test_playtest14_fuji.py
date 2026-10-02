"""Fuji script branches with mocked UI/battle/Bag boundaries; native counterparts
exercise actual reward storage, trainer callbacks and object-spawn gating."""
import json
import re
import unittest
from tools.three_horizons.tests.test_playtest11_maps import ROOT, map_data, tiles
from tools.three_horizons.tests.test_playtest14_travel import party

RESCUED='FLAG_TH14_FUJI_RESCUED'
RESOLVED='FLAG_TH14_MOTHER_RESOLVED'
FLUTE='FLAG_TH14_POKE_FLUTE'
TRAINERS={f'TRAINER_TH14_TOWER7F_GRUNT{i}' for i in range(1,4)}

class Scene:
    def __init__(self):
        paths=['chapter14_tower.inc','chapter13_research.inc','chapter13_tower.inc','chapter13_lavender.inc']
        self.lines='\n'.join((ROOT/'data/scripts/three_horizons'/p).read_text() for p in paths).splitlines()
        self.labels={m[1]:i+1 for i,line in enumerate(self.lines) if (m:=re.match(r'^(\w+)::?$',line))}
        self.flags=set();self.defeated=set();self.items=set();self.vars={};self.messages=[]
        self.full=False;self.gifts=0;self.warps=[];self.delays=[];self.locked=False;self.win=True
        self.calls=[];self.removed=[];self.xy=(0,0)

    def enter_map(self,name,xy):
        # A real DoWarp/CB2_LoadMap discards the old script context. Run the
        # destination's actual load/frame hooks, never the line after `warp`.
        self.xy=xy;self.locked=False
        for key in list(self.vars):
            if key.startswith('VAR_TEMP_'):del self.vars[key]
        source=(ROOT/'data/maps'/name/'scripts.inc').read_text()
        for kind,label in re.findall(r'map_script (MAP_SCRIPT_\w+), (\w+)',source):
            if kind=='MAP_SCRIPT_ON_LOAD':self.run(label)
            elif kind=='MAP_SCRIPT_ON_FRAME_TABLE':
                table=source.split(label+':',1)[1].split('.2byte 0',1)[0]
                for var,value,target in re.findall(r'map_script_2 (\w+), (\d+), (\w+)',table):
                    if self.vars.get(var,0)==int(value):self.run(target)

    def run(self,label):
        pc=self.labels[label];stack=[]
        def value(s):return self.vars.get(s,{'TRUE':1,'FALSE':0}.get(s,int(s) if s.isdigit() else s))
        for _ in range(300):
            line=self.lines[pc].strip();pc+=1
            if not line or line.startswith('@') or line.endswith(':'):continue
            op,_,arg=line.partition(' ');a=[x.strip() for x in arg.split(',')]
            if op=='end':return
            if op=='return':
                if not stack:return
                pc=stack.pop()
            elif op=='goto':pc=self.labels[a[0]]
            elif op=='call':stack.append(pc);pc=self.labels[a[0]]
            elif op in ('goto_if_set','goto_if_unset'):
                if (a[0] in self.flags)==(op=='goto_if_set'):pc=self.labels[a[1]]
            elif op=='goto_if_not_defeated':
                if a[0] not in self.defeated:pc=self.labels[a[1]]
            elif op in ('goto_if_eq','goto_if_ne'):
                if (value(a[0])==value(a[1]))==(op=='goto_if_eq'):pc=self.labels[a[2]]
            elif op=='getplayerxy':self.vars[a[0]],self.vars[a[1]]=self.xy
            elif op=='setvar':self.vars[a[0]]=value(a[1])
            elif op=='setflag':self.flags.add(a[0])
            elif op=='checkitem':self.vars['VAR_RESULT']=int(a[0] in self.items)
            elif op=='msgbox':self.messages.append(a[0])
            elif op in ('lock','lockall'):self.locked=True
            elif op in ('release','releaseall'):self.locked=False
            elif op=='warp':
                self.warps.append(a)
                if a[0]=='MAP_TH13_LAVENDER_TOWN_VOLUNTEER_POKEMON_HOUSE':
                    self.enter_map('TH13_LavenderTown_VolunteerPokemonHouse',tuple(map(int,a[1:])))
                else:self.locked=False
                return
            elif op=='removeobject':self.removed.append(a[0])
            elif op=='trainerbattle_single':
                if a[0] in self.defeated:continue
                if not self.win:self.locked=False;return
                self.defeated.add(a[0]);pc=self.labels[a[3]]
            elif op=='special':
                if a[0]=='TH14_ScriptGiveUniqueItem':
                    item=self.vars['VAR_0x8004'];receipt=self.vars['VAR_0x8005']
                    result=2 if item in self.items or receipt in self.flags else 0 if self.full else 1
                    if result:self.flags.add(receipt)
                    if result==1:self.items.add(item);self.gifts+=1
                    self.vars['VAR_RESULT']=result
                elif a[0]=='TH14_DelayAftermathCalls':self.delays.append(len(self.warps))
                elif a[0] in ('TH_ScriptResearchQueueCall','TH_ScriptResearchCompleteCall'):self.calls.append(a[0])
                elif a[0]!='TH_RefreshFollower':raise AssertionError('unknown special '+line)
            elif op not in ('faceplayer','closemessage','waitstate','hidefollower','applymovement','waitmovement','playfanfare','waitfanfare','playmoncry','waitmoncry'):
                raise AssertionError('unhandled instruction '+line)
        raise AssertionError('scene did not finish')

class Fuji(unittest.TestCase):
    def test_gearless_scope_return_gets_real_gear_no_old_photos(self):
        s=Scene();s.items.add('ITEM_SILPH_SCOPE');s.run('TH14_Tower_GearContact')
        self.assertEqual(s.flags,{'FLAG_TH13_GEAR'})
        self.assertIn('TH14_Tower_GearContact_ScopeOffer',s.messages)
        self.assertEqual(s.calls,['TH_ScriptResearchQueueCall','TH_ScriptResearchCompleteCall'])
        self.assertFalse(s.locked)

    def test_equipped_return_not_interrupted(self):
        s=Scene();s.flags.add('FLAG_TH13_GEAR');s.run('TH14_Tower_GearContact')
        self.assertEqual(s.flags,{'FLAG_TH13_GEAR'});self.assertFalse(s.calls)
        self.assertEqual(s.messages,['TH14_Tower_GearContact_Reminder'])
        self.assertFalse(map_data('TH13_PokemonTower_1F')['coord_events'])

    def test_upper_floor_identity_locked_and_reciprocal_stairs(self):
        m=map_data('TH14_PokemonTower_7F');groups=json.loads((ROOT/'data/maps/map_groups.json').read_text())
        self.assertEqual(groups['gMapGroup_ThreeHorizons14'][33],m['name'])
        self.assertEqual(m['warp_events'][0]['dest_map'],'MAP_TH13_POKEMON_TOWER_6F')
        self.assertEqual(m['warp_events'][0]['dest_warp_id'],'1')
        six=map_data('TH13_PokemonTower_6F')
        self.assertEqual(six['warp_events'][0]['dest_map'],'MAP_TH13_POKEMON_TOWER_5F')
        self.assertEqual(six['warp_events'][1]['dest_map'],m['id'])
        for resolved in (False,True):
            s=Scene()
            if resolved:s.flags.add(RESOLVED)
            s.run('TH14_Tower7F_Entry')
            self.assertEqual(len(s.warps),int(not resolved));self.assertFalse(s.locked)
            if not resolved:self.assertEqual(s.warps[0],['MAP_TH13_POKEMON_TOWER_6F','11','14'])

    def test_fuji_only_after_mother_and_all_upper_rockets(self):
        for resolved in (False,True):
            for mask in range(8):
                s=Scene()
                if resolved:s.flags.add(RESOLVED)
                s.defeated={f'TRAINER_TH14_TOWER7F_GRUNT{i+1}' for i in range(3) if mask&(1<<i)}
                s.run('TH14_Tower_Fuji')
                success=resolved and mask==7
                self.assertEqual(RESCUED in s.flags,success)
                self.assertEqual(len(s.warps),int(success));self.assertEqual(s.gifts,int(success))
                self.assertFalse(s.locked)

    def test_loss_reload_then_rescue_full_bag_retry_is_once(self):
        s=Scene();s.flags.add(RESOLVED);s.win=False
        s.run('TH14_Tower7F_Grunt1');self.assertFalse(s.defeated);self.assertNotIn(RESCUED,s.flags)
        s.win=True
        for i in range(1,4):s.run(f'TH14_Tower7F_Grunt{i}')
        self.assertEqual(s.defeated,TRAINERS)
        s.full=True;s.run('TH14_Tower_Fuji')
        self.assertIn(RESCUED,s.flags);self.assertNotIn(FLUTE,s.flags);self.assertEqual(s.gifts,0)
        self.assertEqual(s.delays,[1]);self.assertFalse(s.calls)
        before=set(s.flags);s.run('TH14_Tower_Fuji');self.assertEqual(s.flags,before);self.assertEqual(len(s.warps),1)
        s.full=False;s.run('TH14_Fuji_Home');self.assertIn(FLUTE,s.flags);self.assertEqual(s.gifts,1)
        for _ in range(3):s.run('TH14_Fuji_Home')
        self.assertEqual(s.gifts,1);self.assertFalse(s.calls);self.assertFalse(s.locked)

    def test_anomalous_home_cannot_award_and_existing_flute_normalizes(self):
        s=Scene();s.run('TH14_Fuji_Home');self.assertFalse(s.items);self.assertFalse(s.flags)
        s.flags.add(RESCUED);s.items.add('ITEM_POKE_FLUTE');s.full=True;s.run('TH14_Fuji_Home')
        self.assertIn(FLUTE,s.flags);self.assertEqual(s.gifts,0)

    def test_fuji_reward_survives_real_warp_context_reset(self):
        s=Scene();s.flags.add(RESOLVED);s.defeated=TRAINERS.copy()
        s.run('TH14_Tower_Fuji')
        self.assertEqual(len(s.warps),1)
        self.assertIn('TH14_Fuji_HomeThanks',s.messages)
        self.assertEqual(s.gifts,1)
        self.assertIn(FLUTE,s.flags)
        self.assertFalse(s.locked)

    def test_home_cold_arrival_retries_pending_reward_once_without_entry_hijack(self):
        for rescued in (False,True):
            for delivered in (False,True):
                for xy in ((3,4),(4,7),(3,5)):
                    s=Scene()
                    if rescued:s.flags.add(RESCUED)
                    if delivered:s.flags.add(FLUTE);s.items.add('ITEM_POKE_FLUTE')
                    s.enter_map('TH13_LavenderTown_VolunteerPokemonHouse',xy)
                    self.assertEqual(s.gifts,int(rescued and not delivered and xy==(3,4)))
                    self.assertFalse(s.locked)
        s=Scene();s.flags.add(RESCUED);s.full=True
        s.enter_map('TH13_LavenderTown_VolunteerPokemonHouse',(3,4))
        self.assertIn('TH14_Fuji_FullBagText',s.messages);self.assertNotIn(FLUTE,s.flags)
        s.full=False;s.run('TH14_Fuji_Home')
        self.assertEqual(s.gifts,1)
        s.enter_map('TH13_LavenderTown_VolunteerPokemonHouse',(3,4))
        self.assertEqual(s.gifts,1)

    def test_cubone_and_memorial_dialogue_tracks_progress_without_writing_flags(self):
        cases=[('TH13_Lavender_Boy',RESCUED,'TH14_Lavender_FujiHomeText'),
               ('TH13_Lavender_VolunteerBoy',RESCUED,'TH14_Lavender_FujiHomeText'),
               ('TH13_Lavender_HouseWoman',RESOLVED,'TH14_Lavender_CuboneCareText'),
               ('TH13_Lavender_CUBONE',RESOLVED,'TH14_Lavender_CuboneQuietText'),
               ('TH13_PokemonTower_1F_EventScript_Channeler',RESOLVED,'TH14_Tower_MemorialQuietText')]
        for label,flag,message in cases:
            for completed in (False,True):
                s=Scene()
                if completed:s.flags.add(flag)
                before=set(s.flags);s.run(label)
                self.assertEqual(message in s.messages,completed)
                self.assertEqual(s.flags,before);self.assertFalse(s.locked)

    def test_native_geometry_parties_receipts_and_compassionate_copy(self):
        m=map_data('TH14_PokemonTower_7F');d=map_data('PokemonTower_7F_Frlg')
        self.assertEqual([(o['x'],o['y'],o['movement_type']) for o in m['object_events']],[(o['x'],o['y'],o['movement_type']) for o in d['object_events']])
        self.assertEqual(m['object_events'][0]['flag'],RESCUED)
        self.assertEqual(m['bg_events'][0]['flag'],'FLAG_TH14_PICKUP_43')
        self.assertLessEqual(len(m['object_events'])+2,16)
        home=map_data('TH13_LavenderTown_VolunteerPokemonHouse');fuji=home['object_events'][-1]
        self.assertEqual((fuji['x'],fuji['y']),(3,3));self.assertEqual(fuji['script'],'TH14_Fuji_Home')
        self.assertEqual([o['local_id'] for o in home['object_events'][:-1]],[f'LOCALID_TH13_LAVENDERTOWN_VOLUNTEERPOKEMONHOUSE_{i}' for i in range(2,7)])
        w,h,c=tiles(home['name']);self.assertFalse(c[4*w+3]&0xc00)
        src=(ROOT/'src/data/trainers.party').read_text();donor=(ROOT/'src/data/trainers_frlg.party').read_text()
        rematch=(ROOT/'src/data/three_horizons_rematches.h').read_text()
        for i in range(1,4):
            name=f'TRAINER_TH14_TOWER7F_GRUNT{i}'
            self.assertEqual(party(src,name),party(donor,f'TRAINER_TEAM_ROCKET_GRUNT_{18+i}').replace('Music: Aqua','Music: Suspicious'))
            self.assertNotIn(name,rematch)
        chapter=(ROOT/'data/scripts/three_horizons/chapter14_tower.inc').read_text()
        for text in ('The SCOPE helped you see her.','You stayed long enough to','when we cannot measure them.','deeply sleeping POKéMON.'):
            self.assertIn(text,chapter.replace('\\n',' ').replace('\\l',' '))
        self.assertNotRegex(chapter,r'(famechecker|FLAG_RESCUED_MR_FUJI|FLAG_HIDE_POKEHOUSE_FUJI|FLAG_HIDE_TOWER_FUJI)')

    def test_reward_fanfare_is_a_defined_native_song(self):
        chapter=(ROOT/'data/scripts/three_horizons/chapter14_tower.inc').read_text()
        songs=set(re.findall(r'^#define (MUS_\w+)\b',(ROOT/'include/constants/songs.h').read_text(),re.M))
        for song in re.findall(r'playfanfare (MUS_\w+)',chapter):self.assertIn(song,songs)

if __name__=='__main__':unittest.main()
