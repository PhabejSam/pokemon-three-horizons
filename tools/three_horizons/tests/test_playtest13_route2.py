import json
import unittest
from tools.three_horizons.tests.test_playtest11_maps import ROOT, map_data, tiles, reachable

HM='ITEM_HM05'
RECEIPT='FLAG_TH13_FLASH'
GEAR='FLAG_TH13_GEAR'
BADGE='FLAG_BADGE03_GET'

def visit(bag, flags, caught=10, room=True):
    lines=[]; labels={}
    for p in (ROOT/'data/scripts/three_horizons').glob('*.inc'):
        for raw in p.read_text(encoding='utf-8').splitlines():
            line=raw.split('@',1)[0].strip()
            if line.endswith(':'):labels[line.rstrip(':')]=len(lines)
            elif line:lines.append(line)
    pc=labels['TH13_Route2_Aide'];values={};messages=[];queued=[]
    def val(k):
        if k in ('TRUE','YES'):return 1
        if k in ('FALSE','NO'):return 0
        if k.startswith('VAR_'):return values.get(k,0)
        return int(k) if k.isdecimal() else k
    for _ in range(150):
        op,_,tail=lines[pc].partition(' ');pc+=1;args=[x.strip() for x in tail.split(',')]
        if op=='end':return messages,queued,values
        if op in ('lock','release','releaseall','faceplayer','buffernumberstring'):continue
        if op=='msgbox':messages.append(args[0])
        elif op=='setvar':values[args[0]]=val(args[1])
        elif op=='setflag':flags.add(args[0])
        elif op=='checkitem':values['VAR_RESULT']=int(bool(bag.get(args[0],0)))
        elif op=='giveitem':
            values['VAR_RESULT']=int(room)
            if room:bag[args[0]]=bag.get(args[0],0)+1
        elif op in ('goto_if_eq','goto_if_lt'):
            if (val(args[0])==val(args[1]) if op=='goto_if_eq' else val(args[0])<val(args[1])):pc=labels[args[2]]
        elif op in ('goto_if_set','goto_if_unset'):
            if (args[0] in flags)==(op=='goto_if_set'):pc=labels[args[1]]
        elif op=='goto':pc=labels[args[0]]
        elif op=='specialvar':
            assert args[1]=='GetFrlgPokedexCount' and values['VAR_0x8004']==1
            values['VAR_0x8006']=caught;values[args[0]]=1
        elif op=='special':
            assert args[0]=='TH_ScriptResearchQueueCall'
            queued.append(values['VAR_0x8004'])
        else:raise AssertionError(lines[pc-1])
    raise AssertionError('aide did not return')

class Route2Aide(unittest.TestCase):
    def test_quota_and_badge(self):
        for count in (9,10,11):
            bag={};flags={BADGE};messages,queue,values=visit(bag,flags,count)
            self.assertEqual(values['VAR_0x8006'],count)
            self.assertEqual(bool(bag),count>=10)
            self.assertNotIn(GEAR, flags)
            if count<10:self.assertIn('TH13_Route2_QuotaText',messages)
        bag={};flags=set();messages,queue,_=visit(bag,flags,11)
        self.assertFalse(bag);self.assertFalse(flags);self.assertFalse(queue)
        self.assertIn('TH13_Route2_BadgeText',messages)

    def test_partial_delivery_retries_and_repeats(self):
        for owned in (False,True):
            for gear in (False,True):
                for receipt in (False,True):
                    bag={HM:1} if owned else {};flags={BADGE}|({GEAR} if gear else set())|({RECEIPT} if receipt else set())
                    visit(bag,flags,room=False)
                    self.assertEqual(bag,{HM:1} if owned else {})
                    visit(bag,flags,room=True)
                    self.assertIn(RECEIPT, flags)
                    self.assertEqual(GEAR in flags, gear)
                    # A valid receipt is authoritative: do not duplicate a delivered HM.
                    self.assertEqual(bag.get(HM,0),int(owned or not receipt))
                    before=(dict(bag),set(flags));visit(bag,flags)
                    self.assertEqual((bag,flags),before)

    def test_facility_doors_and_obtainable_quota(self):
        room=map_data('TH13_Route2_EastBuilding');route=map_data('TH_Route2')
        self.assertEqual(len(room['warp_events']),4)
        for w in room['warp_events']:
            self.assertEqual(w['dest_map'],route['id'])
            self.assertEqual(route['warp_events'][int(w['dest_warp_id'])]['dest_map'],room['id'])
        for xy in ((18,41),(19,41),(18,46),(19,46)):
            self.assertFalse(any((b['x'],b['y'])==xy and b['script']=='TH_Journey_Closed' for b in route['bg_events']))
        w,h,a=tiles(room['name']);floor={(i%w,i//w) for i,v in enumerate(a) if not v&0xc00}
        objs={(o['x'],o['y']) for o in room['object_events']}
        for start in ((7,9),(7,2)):
            seen=reachable(start,floor,objs)
            self.assertTrue({(7,9),(7,2)}<=seen)
            self.assertTrue(seen.intersection(((3,6),(5,6),(4,5),(4,7))))
        wild=json.loads((ROOT/'src/data/wild_encounters.json').read_text())['wild_encounter_groups'][0]['encounters']
        accessible={'MAP_TH_ROUTE1','MAP_TH_ROUTE2','MAP_TH_ROUTE22','MAP_TH_VIRIDIAN_FOREST','MAP_TH_ROUTE3','MAP_TH_MT_MOON_1F'}
        species={m['species'] for e in wild if e['map'] in accessible and 'land_mons' in e for m in e['land_mons']['mons']}
        self.assertGreaterEqual(len(species),10)

if __name__=='__main__':unittest.main()
