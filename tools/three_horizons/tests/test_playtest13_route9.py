import json,re,unittest
from collections import Counter
from tools.three_horizons.tests.test_playtest11_maps import ROOT,map_data,tiles,reachable
from tools.three_horizons.tests.test_playtest13_research import Scene

class Route9(unittest.TestCase):
 def test_route9_links_and_mareep_rate(self):
  m=map_data('TH13_Route9');city=map_data('TH_Cerulean')
  self.assertEqual(m['layout'],'LAYOUT_ROUTE9')
  self.assertIn(dict(map='MAP_TH_CERULEAN',offset=-10,direction='left'),m['connections'])
  self.assertEqual(city['connections'],[dict(map='MAP_TH_ROUTE4',offset=10,direction='left'),dict(map='MAP_TH12_ROUTE24',offset=12,direction='up'),dict(map='MAP_TH12_ROUTE5',offset=0,direction='down'),dict(map=m['id'],offset=10,direction='right')])
  self.assertFalse(any(x['script']=='TH_ChapterEastBoundary' for x in city['coord_events']))
  group=json.loads((ROOT/'src/data/wild_encounters.json').read_text())['wild_encounter_groups'][0]
  rows=[e for e in group['encounters'] if e.get('map')==m['id']];self.assertEqual(len(rows),1)
  rates=next(x['encounter_rates'] for x in group['fields'] if x['type']=='land_mons');mons=rows[0]['land_mons']['mons']
  self.assertEqual(len(mons),len(rates));self.assertEqual(sum(rates),100)
  totals=Counter()
  for rate,mon in zip(rates,mons):
   self.assertGreater(rate,0);self.assertTrue(11<=mon['min_level']<=mon['max_level']<=17);totals[mon['species']]+=rate
  self.assertEqual(totals.pop('SPECIES_MAREEP'),5)
  self.assertEqual(sum(totals.values()),95)
  self.assertEqual(set(totals),{'SPECIES_RATTATA','SPECIES_SPEAROW','SPECIES_EKANS'})

 def test_nine_first_rosters_and_native_trainer_placements(self):
  m=map_data('TH13_Route9');native=map_data('Route9_Frlg')
  self.assertEqual(len([o for o in m['object_events'] if o['trainer_type']=='TRAINER_TYPE_NORMAL']),9)
  ids=dict(re.findall(r'#define (TRAINER_TH\w+) (\d+)',(ROOT/'include/constants/opponents.h').read_text()))
  old=(ROOT/'src/data/trainers_frlg.party').read_text();new=(ROOT/'src/data/trainers.party').read_text()
  registry=(ROOT/'src/data/three_horizons_rematches.h').read_text()
  for i,(a,b) in enumerate(zip(m['object_events'][:9],native['object_events'][:9])):
   for field in ['x','y','elevation','movement_type','movement_range_x','movement_range_y','trainer_sight_or_berry_tree_id']:self.assertEqual(a[field],b[field])
   name=b['script'].split('_')[-1].upper();tid='TRAINER_TH13_ROUTE9_'+name
   self.assertEqual(int(ids[tid]),114+i)
   self.assertIn('{'+tid+', MAP_TH13_ROUTE9, '+str(i+1)+'}',registry)
   body=re.search(r'=== TRAINER_[A-Z_]*'+name+r' ===\n(.*?)(?=\n===|\Z)',old,re.S)[1].strip()
   actual=re.search(r'=== '+tid+r' ===\n(.*?)(?=\n===|\n#endif|\Z)',new,re.S)[1].strip()
   self.assertEqual(actual,body)

 def test_scene_receipts_camera_decline_repeat(self):
  for gear in (False,True):
   for answer in (0,1):
    s=Scene(gear,answer);s.run('TH13_Route9_Pair');s.run('TH13_Route9_Pair')
    self.assertEqual(s.entries,{'TH_RESEARCH_ROUTE9'})
    self.assertEqual(s.photos,{'TH_PHOTO_ROUTE9'} if gear and answer else set())
    self.assertEqual(s.messages.count('TH13_Route9_FirstText'),1)
    self.assertIn('TH13_Route9_RepeatText',s.messages)
    self.assertEqual(s.flashes,int(gear and answer))

 def test_scene_off_path_pickups_unique_and_cut_entrance(self):
  m=map_data('TH13_Route9');w,h,a=tiles(m['name']);floor={(i%w,i//w) for i,t in enumerate(a) if not t&0xc00}
  additions=m['object_events'][12:];self.assertEqual(len(additions),3)
  occupied={(o['x'],o['y']) for o in m['object_events']}
  self.assertEqual(len(occupied),len(m['object_events']))
  seen=reachable((42,6),floor,occupied)
  for o in additions:
   self.assertIn((o['x'],o['y']),floor)
   self.assertTrue(seen.intersection([(o['x']-1,o['y']),(o['x']+1,o['y']),(o['x'],o['y']-1),(o['x'],o['y']+1)]))
  self.assertEqual(m['object_events'][9]['script'],'TH_Journey_Tree')
  items=m['object_events'][10:12]+[o for o in m['bg_events'] if o['type']=='hidden_item']
  self.assertEqual(len(items),5);flags=[o['flag'] for o in items]
  self.assertEqual(set(flags),{'FLAG_TH13_PICKUP_'+str(i) for i in range(4,9)})
  self.assertEqual(len(set(flags)),len(flags))

if __name__=='__main__':unittest.main()
