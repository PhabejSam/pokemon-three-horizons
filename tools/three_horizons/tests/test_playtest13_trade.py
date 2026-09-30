import unittest
import re
from tools.three_horizons.tests.test_playtest11_maps import ROOT,map_data,tiles,reachable
FLAG='FLAG_TH13_SKARMORY_TRADE'

def visit(flags,accept=True,selection=0,species='SPECIES_ZUBAT',egg=False):
 lines=[];labels={}
 for p in (ROOT/'data/scripts/three_horizons').glob('*.inc'):
  for raw in p.read_text(encoding='utf8').splitlines():
   line=raw.split('@',1)[0].strip()
   if line.endswith(':'):labels[line.rstrip(':')]=len(lines)
   elif line:lines.append(line)
 pc=labels['TH13_Route2_Trader'];v={};exchange=[]
 def val(x):
  if x in ('TRUE','YES'):return 1
  if x in ('FALSE','NO'):return 0
  if x=='PARTY_SIZE':return 6
  return v.get(x,x)
 for _ in range(80):
  op,_,tail=lines[pc].partition(' ');pc+=1;a=[x.strip() for x in tail.split(',')]
  if op=='end':return exchange
  if op in ('lock','faceplayer','release','bufferspeciesname'):continue
  if op=='setvar':v[a[0]]=val(a[1])
  elif op=='setflag':flags.add(a[0])
  elif op=='msgbox':
   if len(a)>1 and a[1]=='MSGBOX_YESNO':v['VAR_RESULT']=int(accept)
  elif op=='special':assert a[0]=='TH_RefreshFollower'
  elif op=='goto_if_set':
   if a[0] in flags:pc=labels[a[1]]
  elif op in ('goto_if_eq','goto_if_ge','goto_if_ne'):
   x,y=val(a[0]),val(a[1]);yes=(x==y if op=='goto_if_eq' else x>=y if op=='goto_if_ge' else x!=y)
   if yes:pc=labels[a[2]]
  elif op=='call':
   if a[0]=='EventScript_GetInGameTradeSpeciesInfo':v['VAR_0x8009']='SPECIES_ZUBAT'
   elif a[0]=='EventScript_ChooseMonForInGameTrade':v['VAR_0x8004']=selection
   elif a[0]=='EventScript_GetInGameTradeSpecies':v['VAR_RESULT']='SPECIES_NONE' if egg else species
   elif a[0]=='EventScript_DoInGameTrade':
    assert FLAG not in flags,'Receipt set before successful exchange'
    exchange.append(selection)
   else:raise AssertionError(a)
  else:raise AssertionError(lines[pc-1])
 raise AssertionError('Trade did not return')

class Route2Trade(unittest.TestCase):
 def test_trade_dialogue_is_available_in_th_build(self):
  text=(ROOT/'data/scripts/three_horizons/chapter13_route2.inc').read_text()
  trade=text.split('TH13_Route2_Trader::')[1]
  labels=set(re.findall(r'^(\w+)::?',text,re.M))
  for label in re.findall(r'^\s*msgbox (\w+)',trade,re.M):self.assertIn(label,labels)
 def test_cancel_wrong_egg_no_exchange_or_receipt(self):
  for kwargs in ({'accept':False},{'selection':6},{'selection':7},{'species':'SPECIES_PIDGEY'},{'egg':True}):
   flags=set();self.assertEqual(visit(flags,**kwargs),[]);self.assertFalse(flags)
 def test_full_party_one_slot_and_receipt_after_exchange(self):
  for i in range(6):
   flags=set();self.assertEqual(visit(flags,selection=i),[i]);self.assertEqual(flags,{FLAG})
   self.assertEqual(visit(flags,selection=i),[])
 def test_native_trade_ui_and_safe_house_return(self):
  room=map_data('TH13_Route2_House');route=map_data('TH_Route2')
  self.assertEqual(len(room['warp_events']),3)
  for warp in room['warp_events']:
   self.assertEqual(warp['dest_map'],route['id']);self.assertEqual(route['warp_events'][int(warp['dest_warp_id'])]['dest_map'],room['id'])
  self.assertFalse(any(b['x']==17 and b['y']==22 and b['script']=='TH_Journey_Closed' for b in route['bg_events']))
  w,h,a=tiles(room['name']);floor={(i%w,i//w) for i,v in enumerate(a) if not v&0xc00};objs={(o['x'],o['y']) for o in room['object_events']}
  seen=reachable((4,6),floor,objs);self.assertIn((7,3),seen)
  text=(ROOT/'data/scripts/three_horizons/chapter13_route2.inc').read_text()
  self.assertIn('Any held item travels with ZUBAT',text)
  block=text.split('TH13_Route2_Trader::')[1].split('TH13_Route2_TradeDone:')[0]
  self.assertNotIn('givemon',block);self.assertNotIn('Link',block)

if __name__=='__main__':unittest.main()
