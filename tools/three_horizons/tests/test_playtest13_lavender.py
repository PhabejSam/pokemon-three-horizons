import json,re,unittest
from tools.three_horizons.tests.test_playtest11_maps import ROOT,map_data,tiles,reachable
from tools.three_horizons.tests.test_playtest13_research import Scene

class Lavender(unittest.TestCase):
 def test_all_interiors_and_connections_are_reciprocal(self):
  town=map_data('TH13_LavenderTown');route=map_data('TH13_Route10')
  self.assertEqual(town['connections'],[dict(map=route['id'],direction='up',offset=0)])
  self.assertIn(dict(map=town['id'],direction='down',offset=0),route['connections'])
  registry=json.loads((ROOT/'data/maps/map_groups.json').read_text())['gMapGroup_ThreeHorizons']
  maps={map_data(n)['id']:map_data(n) for n in registry}
  for n in registry:
   if not n.startswith('TH13_Lavender'):continue
   m=map_data(n)
   for w in m['warp_events']:
    self.assertIn(w['dest_map'],maps)
    back=maps[w['dest_map']]['warp_events'][int(w['dest_warp_id'])]
    self.assertEqual(back['dest_map'],m['id'],(n,w))
  self.assertEqual(len(town['warp_events']),6) # Task40 connects the native Tower door.
  center=map_data('TH13_LavenderTown_PokemonCenter_1F');up=map_data('TH13_LavenderTown_PokemonCenter_2F')
  self.assertEqual(center['warp_events'][3]['dest_map'],up['id'])
  self.assertEqual(len(up['object_events']),3);self.assertEqual(len(up['warp_events']),1)
  self.assertTrue(all(o['script'].startswith('TH13_Center_Attendant') for o in up['object_events']))
  heals=json.loads((ROOT/'src/data/heal_locations.json').read_text())['heal_locations']
  self.assertEqual(heals[-1]['id'],'HEAL_LOCATION_TH13_LAVENDER');self.assertEqual(heals[-1]['map'],center['id'])

 def test_scene_positions_allow_every_door_and_interaction(self):
  m=map_data('TH13_LavenderTown');w,h,c=tiles(m['name']);floor={(i%w,i//w) for i,t in enumerate(c) if not t&0xc00}
  self.assertLessEqual(len(m['object_events'])+2,16)
  added=m['object_events'][3:];self.assertEqual(len(added),5)
  for girlx in range(17,22):
   for girly in range(9,12):
    positions=[(girlx,girly)]+[(o['x'],o['y']) for o in m['object_events'][1:]]
    self.assertEqual(len(positions),len(set(positions)))
    seen=reachable((10,0),floor,set(positions))
    for o in added:
     xy=o['x'],o['y'];self.assertIn(xy,floor)
     self.assertTrue(any(p in seen for p in [(xy[0]+1,xy[1]),(xy[0]-1,xy[1]),(xy[0],xy[1]+1),(xy[0],xy[1]-1)]))
    for door in m['warp_events']:self.assertIn((door['x'],door['y']+1),seen)

 def test_misdreavus_decline_revisit_and_receipts(self):
  m=map_data('TH13_LavenderTown');ghost=next(o for o in m['object_events'] if 'MISDREAVUS' in o['graphics_id'])
  self.assertEqual(ghost['flag'],'FLAG_TH13_PHOTO_LAVENDER')
  for gear in (False,True):
   s=Scene(gear=gear,answer=0)
   s.object_flags={ghost['local_id']:ghost['flag']}
   s.run('TH13_Lavender_Misdreavus')
   self.assertNotIn(ghost['flag'],s.flags, 'Native removeobject must not manufacture a photo receipt')
   self.assertIn('TH_RESEARCH_LAVENDER',s.entries);self.assertFalse(s.photos)
   self.assertIn(ghost['local_id'],s.removed)
   self.assertIn('FLAG_TH13_SCENE_LAVENDER',s.flags)
   s.gear=True;s.answer=1;s.run('TH13_Lavender_Misdreavus')
   self.assertEqual(s.photos,{'TH_PHOTO_LAVENDER'});self.assertEqual(s.flashes,1)
   self.assertIn(ghost['flag'],s.flags)
   s.run('TH13_Lavender_Misdreavus');self.assertEqual(s.flashes,1)
   self.assertEqual(set(s.queued),{'TH_CALL_LAVENDER'})
  source=(ROOT/'data/scripts/three_horizons/chapter13_lavender.inc').read_text()
  self.assertNotRegex(source,r'\b(?:trainerbattle|wildbattle|givemon|giveegg|giveitem)\b')
  self.assertNotRegex(source,r'setvar VAR_TH_RIVAL_PARTNER')

 def test_rival_and_rocket_initial_conversations_once(self):
  for scene,flag in [('Rival','FLAG_TH13_LAVENDER_RIVAL'),('Rockets','FLAG_TH13_ROCKET_CAMEO')]:
   s=Scene();s.run('TH13_Lavender_'+scene);self.assertIn(flag,s.flags)
   first=list(s.messages);s.messages=[];s.run('TH13_Lavender_'+scene)
   self.assertTrue(set(first).isdisjoint(s.messages))
  objects=map_data('TH13_LavenderTown')['object_events']
  rockets=[o for o in objects if o['script']=='TH13_Lavender_Rockets']
  self.assertEqual(len(rockets),3)
  self.assertEqual({o['flag'] for o in rockets},{'FLAG_TH13_ROCKET_CAMEO'})
  self.assertIn('OBJ_EVENT_GFX_TH_JESSIE',{o['graphics_id'] for o in rockets})
  self.assertIn('OBJ_EVENT_GFX_TH_JAMES',{o['graphics_id'] for o in rockets})

 def test_town_services_cries_and_absent_fuji(self):
  source=(ROOT/'data/scripts/three_horizons/chapter13_lavender.inc').read_text()
  for species in ['CUBONE','NIDORINO','PSYDUCK']:self.assertIn('playmoncry SPECIES_'+species,source)
  self.assertNotIn('ITEM_POKE_FLUTE',source)
  house=map_data('TH13_LavenderTown_VolunteerPokemonHouse')
  self.assertEqual(len(house['object_events']),5)
  self.assertFalse(any('Fuji' in o['script'] or o['graphics_id']=='OBJ_EVENT_GFX_MR_FUJI' for o in house['object_events']))
  self.assertEqual(sum(o['script']=='TH_TrainingClerk' for o in map_data('TH13_LavenderTown_Mart')['object_events']),1)

 def test_interior_residents_never_overlap_training_clerk(self):
  for suffix in ['House1','House2','Mart','VolunteerPokemonHouse','PokemonCenter_1F','PokemonCenter_2F']:
   m=map_data('TH13_LavenderTown_'+suffix)
   positions=[(o['x'],o['y']) for o in m['object_events']]
   self.assertEqual(len(positions),len(set(positions)),m['name'])
   if suffix=='Mart':
    clerk=next(o for o in m['object_events'] if o['script']=='TH_TrainingClerk')
    w,h,c=tiles(m['name']);self.assertFalse(c[clerk['y']*w+clerk['x']]&0xc00)
    self.assertEqual(clerk['elevation'],c[clerk['y']*w+clerk['x']]>>12)

if __name__=='__main__':unittest.main()
