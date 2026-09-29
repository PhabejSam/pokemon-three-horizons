"""Forest optional path, original-map preservation, and one-time receipts."""
import hashlib
import json
import unittest
from tools.three_horizons.tests.test_playtest11_maps import ROOT,map_data,tiles,reachable
from tools.three_horizons.tests.test_playtest13_research import Scene

def pickup(flags,bag,room):
 scene=Scene();pc=scene.labels['TH13_Forest_Cap'];removed=False;result=0
 for _ in range(30):
  op,_,tail=scene.lines[pc].partition(' ');pc+=1;a=[x.strip() for x in tail.split(',')]
  if op=='end':return removed
  if op in ('lockall','releaseall'):continue
  if op=='goto_if_set':
   if a[0] in flags:pc=scene.labels[a[1]]
  elif op=='giveitem':
   assert a==['ITEM_BOTTLE_CAP','1'];result=int(room)
   if room:bag[a[0]]=bag.get(a[0],0)+1
  elif op=='goto_if_eq':
   assert a[:2]==['VAR_RESULT','FALSE']
   if not result:pc=scene.labels[a[2]]
  elif op=='setflag':flags.add(a[0])
  elif op=='removeobject':
   assert a[0]=='VAR_LAST_TALKED';removed=True
  else:raise AssertionError(op)
 raise AssertionError('pickup did not finish')

class ForestClearing(unittest.TestCase):
 def test_reward_full_bag_retry_and_repeat_preserve_old_receipts(self):
  flags={'FLAG_TH12_FOREST_SEEN'};bag={}
  self.assertFalse(pickup(flags,bag,False));self.assertEqual(flags,{'FLAG_TH12_FOREST_SEEN'});self.assertFalse(bag)
  self.assertTrue(pickup(flags,bag,True));self.assertEqual(bag,{'ITEM_BOTTLE_CAP':1})
  self.assertFalse(pickup(flags,bag,True));self.assertEqual(bag,{'ITEM_BOTTLE_CAP':1})
  m=map_data('TH_ViridianForest');items=[o for o in m['object_events'] if o['script']=='TH13_Forest_Cap']
  self.assertEqual(len(items),1);self.assertEqual(items[0]['flag'],'FLAG_TH13_FOREST_RESEARCH_REWARD')
 def test_optional_cut_gate_preserves_every_existing_path_and_exit(self):
  m=map_data('TH_ViridianForest');w,h,a=tiles(m['name']);ow,oh,old=tiles('ViridianForest_Frlg')
  self.assertEqual((w,h),(ow,oh));self.assertNotEqual(m['layout'],'LAYOUT_VIRIDIAN_FOREST')
  oldfloor={(i%w,i//w) for i,t in enumerate(old) if not t&0xc00}
  floor={(i%w,i//w) for i,t in enumerate(a) if not t&0xc00}
  self.assertLessEqual(oldfloor,floor)
  self.assertTrue(all(a[y*w+x]==old[y*w+x] for x,y in oldfloor))
  self.assertEqual(hashlib.sha256(json.dumps(m['warp_events'],sort_keys=True).encode()).hexdigest(),'fd6fdb73615ac8741efd0af336ef072c4e49fec9b5562fc1ce3843b20f1a2945')
  self.assertEqual(hashlib.sha256(json.dumps(m['object_events'][:18],sort_keys=True).encode()).hexdigest(),'e30399dbadc9fef15e7caf326458bfeb5434c1dbed71d4a9d659576985dc5aac')
  self.assertEqual(hashlib.sha256((ROOT/'data/layouts/ViridianForest_Frlg/map.bin').read_bytes()).hexdigest(),'03e8e74fcca81b95b3004baf7eca229d1739440393c8cf490618d30ef099ff8a')
  gate=[o for o in m['object_events'] if o['script']=='TH_Journey_Tree']
  self.assertEqual(len(gate),2)
  gatexy={(o['x'],o['y']) for o in gate};start=(39,34);inside=(30,32)
  self.assertNotIn(inside,reachable(start,floor,gatexy))
  for one in gatexy:self.assertIn(inside,reachable(start,floor,gatexy-{one}))
  for warp in m['warp_events']:self.assertIn((warp['x'],warp['y']),reachable(start,floor,gatexy))
  for o in m['object_events'][18:]:self.assertIn((o['x'],o['y']),floor)

 def test_first_repeat_no_gear_decline_and_photo_are_independent(self):
  legacy={'FLAG_TH12_FOREST_SEEN','FLAG_TH13_SCENE_FOREST_TREECKO','FLAG_TH13_SCENE_FOREST_SHROOMISH'}
  for gear in (False,True):
   for answer in (0,1):
    s=Scene(gear,answer);s.flags=legacy.copy();s.run('TH13_Forest_Pair')
    self.assertIn('TH_RESEARCH_FOREST_PAIR',s.entries)
    self.assertEqual(s.photos,{'TH_PHOTO_FOREST_PAIR'} if gear and answer else set())
    self.assertLessEqual(legacy,s.flags)
    expected={'FLAG_TH13_SCENE_FOREST_PAIR'}
    if gear and answer:expected.add('FLAG_TH13_PHOTO_FOREST_PAIR')
    self.assertEqual(s.flags-legacy,expected)
    s.run('TH13_Forest_Pair')
    self.assertEqual(s.messages.count('TH13_Forest_FirstText'),1)
    self.assertIn('TH13_Forest_RepeatText',s.messages)
    self.assertEqual(s.flashes,int(gear and answer))

if __name__=='__main__':unittest.main()
