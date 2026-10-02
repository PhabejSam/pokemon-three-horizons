"""Execute scene branches, substituting only presentation/battle/service boundaries.
Native counterparts cover compiled callbacks, real flash registers and Ball dispatch.
"""
import re
import unittest
from tools.three_horizons.tests.test_playtest11_maps import ROOT,map_data,tiles

GEAR='FLAG_TH13_GEAR'; OBS='FLAG_TH14_OBS_MOTHER'; PHOTO='FLAG_TH14_PHOTO_MOTHER'
WON='FLAG_TH14_MOTHER_WON'; RESOLVED='FLAG_TH14_MOTHER_RESOLVED'

class Scene:
    def __init__(self,scope=True,gear=True):
        paths=[ROOT/'data/scripts/three_horizons'/n for n in ('chapter13_tower.inc','chapter14_tower.inc')]
        paths += [ROOT/'data/maps/TH13_PokemonTower_6F/scripts.inc']
        self.lines='\n'.join(p.read_text() for p in paths).splitlines()
        self.labels={m[1]:i+1 for i,l in enumerate(self.lines) if (m:=re.match(r'^(\w+)::?$',l))}
        self.flags={GEAR} if gear else set();self.scope=scope;self.vars={};self.trace=[]
        self.outcome='won';self.flash=True;self.capture=True;self.pos=(11,15);self.locked=False
        self.hidden=False;self.refreshed=0;self.presented=False;self.battles=0;self.awards=0;self.tile=709|0xc00
    def run(self,label,stop=None):
        pc=self.labels[label];stack=[]
        def val(s):return self.vars.get(s,{'TRUE':1,'FALSE':0}.get(s,int(s) if s.isdigit() else s))
        for _ in range(450):
            raw=self.lines[pc].split('@',1)[0].strip();pc+=1
            if not raw or raw.endswith(':'):continue
            if stop and raw==stop:return
            op,_,arg=raw.partition(' ');a=[s.strip() for s in arg.split(',')];self.trace.append((op,a))
            if op=='end':return
            if op=='return':
                if not stack:return
                pc=stack.pop()
            elif op=='goto':pc=self.labels[a[0]]
            elif op=='call':stack.append(pc);pc=self.labels[a[0]]
            elif op in ('goto_if_set','goto_if_unset'):
                if (a[0] in self.flags)==(op=='goto_if_set'):pc=self.labels[a[1]]
            elif op in ('goto_if_eq','goto_if_ne'):
                if (val(a[0])==val(a[1]))==(op=='goto_if_eq'):pc=self.labels[a[2]]
            elif op=='setvar':self.vars[a[0]]=val(a[1])
            elif op=='setflag':self.flags.add(a[0])
            elif op=='checkitem':self.vars['VAR_RESULT']=int(self.scope)
            elif op=='getplayerxy':self.vars.update(zip(a,self.pos))
            elif op in ('lock','lockall'):self.locked=True
            elif op in ('release','releaseall'):self.locked=False
            elif op=='hidefollower':self.hidden=True
            elif op=='setmetatile':self.tile=val(a[2]) | (0xc00 if val(a[3]) else 0)
            elif op=='fadescreenswapbuffers':
                if a[0]=='FADE_FROM_WHITE':self.presented=True
            elif op=='special':
                name=a[0]
                if name=='TH_ScriptResearchObserve':
                    if GEAR in self.flags:self.flags.add(OBS)
                elif name=='TH_ScriptResearchPhotoStatus':self.vars['VAR_RESULT']=0 if GEAR not in self.flags or OBS not in self.flags else 2 if PHOTO in self.flags else 1
                elif name=='TH_ScriptBeginPhotoFlash':self.vars['VAR_RESULT']=int(self.flash)
                elif name=='TH_ScriptEndPhotoFlash':self.vars['VAR_RESULT']=int(self.flash and self.presented)
                elif name=='TH_ScriptTakeResearchPhoto':
                    ok=self.capture and self.presented and GEAR in self.flags and OBS in self.flags
                    self.vars['VAR_RESULT']=int(ok)
                    if ok:self.flags.add(PHOTO);self.awards+=1
                elif name=='StartMarowakBattle':
                    self.battles+=1
                    if self.outcome in ('lost','draw','forfeit'):self.locked=False;self.hidden=False;return
                    self.vars['VAR_RESULT']=int(self.outcome!='won')
                elif name=='TH_RefreshFollower':self.hidden=False;self.refreshed+=1
                elif name not in ('TH14_DelayAftermathCalls','DrawWholeMapView'):raise AssertionError(raw)
            elif op not in ('msgbox','closemessage','waitstate','applymovement','waitmovement','setwildbattle','playse','addobject','removeobject','turnobject','playmoncry','waitmoncry','delay','fadescreen','playbgm'):
                raise AssertionError('unhandled '+raw)
        raise AssertionError('unterminated scene')

class Mother(unittest.TestCase):
    def test_no_scope_preserves_prior_receipts_and_gives_repeat_lead(self):
        s=Scene(scope=False);s.flags.add('FLAG_TH13_ROCKET_CAMEO');s.run('TH13_Tower_GhostBarrier');s.run('TH13_Tower_GhostBarrier')
        self.assertEqual(s.flags,{GEAR,'FLAG_TH13_ROCKET_CAMEO','FLAG_TH13_ENDPOINT'})
        self.assertEqual(s.battles,0);self.assertEqual(s.awards,0);self.assertFalse(s.locked);self.assertFalse(s.hidden)
        for label in ('TH13_Tower_EndpointText','TH13_Tower_RepeatText'):self.assertIn(('msgbox',[label]),s.trace)
    def test_missing_gear_and_failed_photo_return_safely(self):
        s=Scene(gear=False);s.run('TH13_Tower_GhostBarrier');self.assertFalse(s.flags);self.assertEqual(s.battles,0)
        self.assertIn(('msgbox',['TH14_Mother_MissingGear']),s.trace);self.assertFalse(s.hidden);self.assertFalse(s.locked)
        for failure in ('flash','capture'):
            s=Scene();setattr(s,failure,False);s.run('TH13_Tower_GhostBarrier')
            self.assertNotIn(PHOTO,s.flags);self.assertNotIn(WON,s.flags);self.assertNotIn(RESOLVED,s.flags);self.assertEqual(s.battles,0)
            self.assertFalse(s.hidden);self.assertFalse(s.locked)
    def test_photo_commits_after_completed_presentation_before_battle(self):
        s=Scene();s.run('TH13_Tower_GhostBarrier')
        def idx(op,arg):return s.trace.index((op,[arg]))
        self.assertLess(idx('msgbox','TH14_Mother_Reveal'),idx('special','TH_ScriptResearchObserve'))
        self.assertLess(idx('fadescreenswapbuffers','FADE_FROM_WHITE'),idx('special','TH_ScriptEndPhotoFlash'))
        self.assertLess(idx('special','TH_ScriptEndPhotoFlash'),idx('special','TH_ScriptTakeResearchPhoto'))
        self.assertLess(idx('special','TH_ScriptTakeResearchPhoto'),idx('special','StartMarowakBattle'))
        self.assertLess(idx('setflag',WON),idx('waitmoncry',''))
        self.assertLess(idx('delay','45'),idx('removeobject','LOCALID_TH14_MOTHER'))
        self.assertLess(idx('fadescreen','FADE_FROM_BLACK'),idx('setflag',RESOLVED))
        self.assertLess(idx('setflag',RESOLVED),idx('special','TH14_DelayAftermathCalls'))
        self.assertEqual(s.awards,1);self.assertEqual(s.refreshed,1);self.assertFalse(s.hidden);self.assertFalse(s.locked)
    def test_every_nonwin_keeps_documented_spirit_unresolved_and_retry_once(self):
        for outcome in ('ran','teleport','doll','abort','caught','lost','draw','forfeit'):
            s=Scene();s.outcome=outcome;s.run('TH13_Tower_GhostBarrier')
            self.assertTrue({OBS,PHOTO}<=s.flags);self.assertNotIn(WON,s.flags);self.assertNotIn(RESOLVED,s.flags)
            self.assertEqual(s.tile,709|0xc00)
            s.outcome='won';s.run('TH13_Tower_GhostBarrier');self.assertIn(RESOLVED,s.flags);self.assertEqual(s.awards,1)
            before=set(s.flags);s.run('TH13_Tower_GhostBarrier');self.assertEqual(s.flags,before);self.assertEqual(s.battles,2)
    def test_pending_won_resumes_aftermath_without_battle_photo_or_fake_call(self):
        s=Scene();s.flags|={OBS,PHOTO,WON};s.run('TH14_Mother_Resume')
        self.assertIn(RESOLVED,s.flags);self.assertEqual((s.battles,s.awards,s.refreshed),(0,0,1))
        self.assertFalse(any('ResearchQueueCall' in str(t) or 'ResearchCompleteCall' in str(t) for t in s.trace))
    def test_resolved_load_opens_native_tile_and_nonresolved_load_blocks(self):
        w,h,t=tiles('TH13_PokemonTower_6F');native=t[16*w+11]&0x3ff
        for resolved in (False,True):
            s=Scene()
            if resolved:s.flags.add(RESOLVED)
            before=set(s.flags);s.run('TH13_PokemonTower_6F_Barrier')
            self.assertEqual(s.flags,before);self.assertEqual(s.tile,native if resolved else 709|0xc00)
            self.assertEqual(s.vars['VAR_TEMP_1'],int(resolved))
    def test_actor_and_resume_contract_preserves_old_local_ids(self):
        m=map_data('TH13_PokemonTower_6F');self.assertEqual(len(m['object_events']),6)
        self.assertEqual([o['local_id'] for o in m['object_events'][:5]],[f'LOCALID_TH13_POKEMONTOWER_6F_{i}' for i in range(1,6)])
        mother=m['object_events'][5];self.assertEqual((mother['x'],mother['y'],mother['flag']),(11,16,'0'))
        self.assertEqual(mother['local_id'],'LOCALID_TH14_MOTHER')
        script=(ROOT/'data/maps/TH13_PokemonTower_6F/scripts.inc').read_text()
        self.assertIn('MAP_SCRIPT_ON_FRAME_TABLE',script);self.assertIn('TH14_Mother_Resume',script)
        self.assertNotIn('CUBONE',str(m['object_events']))
    def test_both_approaches_stage_without_crossing_the_mother_or_walls(self):
        body=(ROOT/'data/scripts/three_horizons/chapter14_tower.inc').read_text()
        w,h,t=tiles('TH13_PokemonTower_6F')
        for start,label in [((11,15),'TH14_Mother_StageAbove'),((12,16),'TH14_Mother_StageRight')]:
            x,y=start
            code=body.split(label+':',1)[1].split('step_end',1)[0]
            for op in re.findall(r'^    (walk_\w+|face_\w+)$',code,re.M):
                if op=='walk_up':y-=1
                elif op=='walk_left':x-=1
                elif op!='face_down':self.fail(op)
                self.assertNotEqual((x,y),(11,16));self.assertFalse(t[y*w+x]&0xc00)
            self.assertEqual((x,y),(11,14))

    def test_all_throwable_balls_covered_and_optional_transaction_unchanged(self):
        source=(ROOT/'src/data/items.h').read_text()
        items=re.findall(r'\[(ITEM_\w+)\]\s*=\s*\{(.*?)\n    \},',source,re.S)
        balls={n for n,b in items if 'EFFECT_ITEM_THROW_BALL' in b}
        self.assertEqual(len(balls),28)
        old=(ROOT/'data/scripts/three_horizons/chapter13_research.inc').read_text().split('TH13_ResearchPhotoSaved:',1)[0]
        self.assertLess(old.index('special TH_ScriptTakeResearchPhoto'),old.index('special TH_ScriptBeginPhotoFlash'))

if __name__=='__main__':unittest.main()
