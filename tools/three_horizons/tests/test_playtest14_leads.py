"""Execute the authored handoff branches and preserve map/story contracts."""
import re
import unittest
from tools.three_horizons.tests.test_playtest13_route2 import visit, ROOT, HM, RECEIPT, BADGE
from tools.three_horizons.tests.test_playtest11_maps import map_data,tiles,reachable

def source(name): return (ROOT/'data/scripts/three_horizons'/name).read_text()
def text(body,label):
    rest=body.split(label+':',1)[1].lstrip(':')
    return rest.split('\n',2)[1]

class Story:
    def __init__(self,flags=()):
        self.flags=set(flags);self.messages=[];self.removed=[];self.hidden=0;self.refreshed=0
        self.lines=[];self.labels={}
        for name in ('chapter13_lavender.inc','chapter13_tower.inc'):
            for raw in source(name).splitlines():
                line=raw.split('@',1)[0].strip()
                if line.endswith(':'):self.labels[line.rstrip(':')]=len(self.lines)
                elif line:self.lines.append(line)
    def run(self,label):
        pc=self.labels[label]
        for _ in range(60):
            line=self.lines[pc];pc+=1;op,_,tail=line.partition(' ');a=[x.strip() for x in tail.split(',')]
            if op=='end':return
            if op in ('lock','lockall','faceplayer','release','releaseall','closemessage','fadescreen'):continue
            if op=='goto_if_set':
                if a[0] in self.flags:pc=self.labels[a[1]]
            elif op=='goto':pc=self.labels[a[0]]
            elif op=='msgbox':self.messages.append(a[0])
            elif op=='setflag':self.flags.add(a[0])
            elif op=='removeobject':self.removed.append(a[0])
            elif op=='hidefollower':self.hidden+=1
            elif op=='special':
                assert a[0]=='TH_RefreshFollower';self.refreshed+=1
            else:raise AssertionError(line)
        raise AssertionError('story branch did not terminate')

class Leads(unittest.TestCase):
    def test_flash_intro_precedes_delivery_and_explanation_follows(self):
        trace=[];bag={};flags={BADGE};visit(bag,flags,trace=trace)
        self.assertLess(trace.index(('message','TH14_Route2_DeliveryText')),trace.index(('give',HM,True)))
        self.assertLess(trace.index(('give',HM,True)),trace.index(('message','TH13_Route2_FlashText')))
        intro=text(source('chapter13_route2.inc'),'TH14_Route2_DeliveryText')
        for term in ('OAK','research','ten species','ROCK TUNNEL'):self.assertIn(term,intro)
        explanation=text(source('chapter13_route2.inc'),'TH13_Route2_FlashText')
        for term in ('conscious','Egg','learn','move slot','HM'):self.assertIn(term,explanation)

    def test_flash_failure_owned_receipt_and_gate_paths(self):
        bag={};flags={BADGE};trace=[];visit(bag,flags,room=False,trace=trace)
        self.assertNotIn(RECEIPT,flags);self.assertFalse(bag)
        self.assertNotIn(('message','TH13_Route2_FlashText'),trace)
        visit(bag,flags);self.assertEqual(bag,{HM:1});self.assertIn(RECEIPT,flags)
        for bag,flags in [({HM:1},{BADGE}),({}, {BADGE,RECEIPT})]:
            trace=[];before=dict(bag);visit(bag,flags,trace=trace)
            self.assertEqual(bag,before);self.assertFalse(any(t[0]=='give' for t in trace))
        for flags,count in [(set(),10),({BADGE},9)]:
            bag={};trace=[];visit(bag,flags,caught=count,trace=trace)
            self.assertFalse(bag);self.assertNotIn(('message','TH14_Route2_DeliveryText'),trace)

    def test_rival_is_respectful_conversation_and_completed_paths_do_not_replay(self):
        body=source('chapter13_lavender.inc')
        for term in ('Not here','grieving','OAK','experiencing','battling'):
            self.assertIn(term,text(body,'TH13_Lavender_RivalFirstText'))
        self.assertIn('respect',text(body,'TH13_Lavender_RivalRepeatText'))
        s=Story();s.run('TH13_Lavender_Rival');s.run('TH13_Lavender_Rival')
        self.assertEqual(s.messages,['TH13_Lavender_RivalFirstText','TH13_Lavender_RivalRepeatText'])
        self.assertEqual((s.hidden,s.refreshed),(2,2))
        s=Story(['FLAG_TH13_ROCKET_CAMEO']);s.run('TH13_Lavender_Rockets')
        self.assertFalse(s.messages);self.assertFalse(s.removed);self.assertEqual((s.hidden,s.refreshed),(0,0))
        s=Story();s.run('TH13_Lavender_Rockets')
        self.assertEqual(len(s.removed),3);self.assertEqual((s.hidden,s.refreshed),(1,1))
        self.assertIn('FLAG_TH13_ROCKET_CAMEO',s.flags)

    def test_observer_first_repeat_and_barrier_have_causal_lead(self):
        s=Story();s.run('TH13_Tower_RocketRecord');s.run('TH13_Tower_RocketRecord')
        self.assertEqual(s.messages,['TH13_Tower_RocketText','TH14_Tower_RocketRepeatText'])
        self.assertLessEqual(s.flags,{'FLAG_TEMP_1'})
        body=source('chapter13_tower.inc')
        for label in ('TH13_Tower_EndpointText','TH13_Tower_RepeatText'):
            words=text(body,label)
            for term in ('SILPH SCOPE','GIOVANNI','CELADON','JESSIE','JAMES'):self.assertIn(term,words)
            self.assertNotIn('complete',words)
        for term in ('GIOVANNI','ghost reports','migration','paperwork','CELADON'):
            self.assertIn(term,text(body,'TH13_Tower_RocketText'))
        self.assertIn('equipment',text(body,'TH14_Tower_RocketRepeatText'))
        self.assertIn('setflag FLAG_TH13_ENDPOINT',body)
        self.assertNotIn('clearflag FLAG_TH13_ENDPOINT',body)

    def test_authored_lines_fit_native_normal_font(self):
        font=(ROOT/'src/fonts.c').read_text().split('gFontNormalLatinGlyphWidths[] = {',1)[1].split('};',1)[0]
        widths=list(map(int,re.findall(r'\d+',font)))
        charmap={m[1]:int(m[2],16) for line in (ROOT/'charmap.txt').read_text().splitlines()
            if (m:=re.match(r"'(.)'\s*=\s*([0-9A-F]{2})\b",line))}
        charmap["'"]=0xB4
        labels={
            'chapter13_route2.inc':['TH14_Route2_DeliveryText','TH13_Route2_FlashText'],
            'chapter13_lavender.inc':['TH13_Lavender_RivalFirstText','TH13_Lavender_RivalRepeatText'],
            'chapter13_tower.inc':['TH13_Tower_RocketText','TH14_Tower_RocketRepeatText','TH13_Tower_EndpointText','TH13_Tower_RepeatText']}
        for name,group in labels.items():
            for label in group:
                message=re.search(re.escape(label)+r':\s*\n\s*\.string "(.*?)\$"',source(name)).group(1)
                message=message.replace('{RIVAL}','MMMMMMM')
                for line in re.split(r'\\[npl]',message):
                    self.assertLessEqual(sum(widths[charmap[c]] for c in line),208,(label,line))

    def test_trio_staging_has_clear_headroom_and_access(self):
        m=map_data('TH13_LavenderTown');w,h,a=tiles(m['name'])
        actors=[o for o in m['object_events'] if o['script']=='TH13_Lavender_Rockets']
        self.assertEqual([(o['x'],o['y']) for o in actors],[(14,18),(15,18),(16,18)])
        for i,o in enumerate(actors,6):
            self.assertEqual(o['local_id'],f'LOCALID_TH13_LAVENDERTOWN_{i}')
            self.assertEqual(o['flag'],'FLAG_TH13_ROCKET_CAMEO')
            self.assertEqual(o['elevation'],3);self.assertEqual(o['movement_type'],'MOVEMENT_TYPE_FACE_UP')
        floor={(i%w,i//w) for i,t in enumerate(a) if not t&0xc00}
        for xy in [(14,17),(15,17),(16,17),(15,16)]:self.assertIn(xy,floor)
        objects={(o['x'],o['y']) for o in m['object_events']}
        self.assertIn((15,17),reachable((13,18),floor,objects))
        self.assertIn((17,18),reachable((15,17),floor,objects))

if __name__=='__main__':unittest.main()
