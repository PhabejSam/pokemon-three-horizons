import re,unittest
from tools.three_horizons.tests.test_playtest11_maps import ROOT,map_data,tiles,reachable
BERRIES={'ITEM_'+n+'_BERRY' for n in ('POMEG','KELPSY','QUALOT','HONDEW','GREPA','TAMATO')}
class Playtest13Training(unittest.TestCase):
 def test_service_and_workshop_stocks_are_separate(self):
  s=(ROOT/'data/scripts/three_horizons/training.inc').read_text()
  def stock(label):
   m=re.search(r'^'+label+r':+\n((?:\s*\.2byte[^\n]+\n)+)',s,re.M)
   self.assertIsNotNone(m,label)
   return set(re.findall(r'ITEM_\w+',m.group(1)))-{'ITEM_NONE'}
  service=stock('TH_TrainingStock')
  self.assertFalse(service&BERRIES)
  self.assertFalse(any(x.startswith('ITEM_POWER_') for x in service))
  self.assertEqual(len([x for x in service if x.endswith('_MINT')]),21)
  self.assertEqual({x for x in service if not x.endswith('_MINT')},{'ITEM_ABILITY_CAPSULE','ITEM_ABILITY_PATCH','ITEM_BOTTLE_CAP','ITEM_GOLD_BOTTLE_CAP'})
  self.assertEqual(stock('TH13_BerryStock'),BERRIES)
 def test_recurring_vendors_are_accessible_without_replacing_locals(self):
  for name in ('TH_ViridianMart','TH_PewterMart','TH_CeruleanMart','TH12_VermilionCity_Mart'):
   m=map_data(name);vendors=[o for o in m['object_events'] if o['script']=='TH_TrainingClerk']
   self.assertEqual(len(vendors),1,name)
   v=vendors[0];self.assertEqual((v['x'],v['y']),(6,2));self.assertEqual(v['graphics_id'],'OBJ_EVENT_GFX_SCIENTIST_1')
   w,h,a=tiles(name);floor={(i%w,i//w) for i,t in enumerate(a) if t>>12==3 and not t&0xc00}
   obstacles={(o['x'],o['y']) for o in m['object_events']}
   area=reachable((4,7),floor,obstacles)
   self.assertIn((6,3),area);self.assertIn((4,3),area)
   self.assertEqual(len(m['object_events']),3 if name=='TH_ViridianMart' else 4)
 def test_existing_workshop_and_referral_are_live(self):
  s=(ROOT/'data/scripts/three_horizons/chapter9_locals.inc').read_text()
  workshop=s.split('TH_Local_CeruleanHouse5_0::',1)[1].split('TH_Sign_CeruleanHouse5_0::',1)[0]
  self.assertIn('goto TH13_BerryWorkshop',workshop)
  self.assertNotIn('later chapter',workshop)
  referral=s.split('TH_Local_CeruleanHouse4_0_Text:',1)[1].split('TH_Local_CeruleanHouse5_0::',1)[0]
  self.assertIn('CERULEAN',referral);self.assertNotIn('VIRIDIAN seller',referral)
if __name__=='__main__':unittest.main()

