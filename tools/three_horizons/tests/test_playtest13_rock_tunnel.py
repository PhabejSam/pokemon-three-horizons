import json,re,unittest
from collections import Counter
from tools.three_horizons.tests.test_playtest11_maps import ROOT,map_data,tiles,reachable
from tools.three_horizons.tests.test_playtest13_research import Scene

CENTERS=[('TH_ViridianCenter','TH13_ViridianCenter2F'),('TH_PewterCenter','TH13_PewterCenter2F'),('TH_CeruleanCenter','TH13_CeruleanCenter2F'),('TH_Route4Center','TH13_Route4Center2F'),('TH12_VermilionCity_PokemonCenter_1F','TH13_VermilionCenter2F'),('TH13_Route10_PokemonCenter_1F','TH13_Route10_PokemonCenter_2F')]
class TunnelChapter(unittest.TestCase):
 def test_center_upstairs_reciprocal_warps_without_link_services(self):
  shared=(ROOT/'data/scripts/three_horizons/chapter13_centers.inc').read_text()
  for first,second in CENTERS:
   a,b=map_data(first),map_data(second)
   self.assertEqual(a['layout'],'LAYOUT_POKEMON_CENTER_1F_FRLG')
   self.assertEqual(b['layout'],'LAYOUT_POKEMON_CENTER_2F_FRLG')
   self.assertEqual(a['warp_events'][3],dict(x=1,y=6,elevation=4,dest_map=b['id'],dest_warp_id='0'))
   self.assertEqual(b['warp_events'],[dict(x=1,y=6,elevation=4,dest_map=a['id'],dest_warp_id='3')])
   w,h,cells=tiles(first);self.assertEqual(cells[6*w+1],0x42d9)
   source=(ROOT/'data/maps'/first/'scripts.inc').read_text()
   self.assertIn('setmetatile 1, 6, 729, FALSE',source)
   self.assertFalse(any((e['x'],e['y'])==(1,6) for e in a['bg_events']))
   self.assertEqual(len(b['object_events']),3)
   for obj in b['object_events']:
    self.assertEqual(obj['flag'],'0');self.assertIn(obj['script']+'::',shared)
   self.assertIsNone(b['connections'])
  self.assertNotRegex(shared,r'(?i)special.*(link|union|trade)|call.*(CableClub|UnionRoom)|warp.*(TRADE|UNION)|waitstate')

 def test_rock_tunnel_ladders_and_exit_graph(self):
  names=['TH13_Route10','TH13_Route10_PokemonCenter_1F','TH13_RockTunnel_1F','TH13_RockTunnel_B1F']
  registry=json.loads((ROOT/'data/maps/map_groups.json').read_text())['gMapGroup_ThreeHorizons']
  allmaps={m['id']:m for n in registry for m in [map_data(n)]}
  for name in names:
   m=map_data(name)
   for i,warp in enumerate(m['warp_events']):
    target=allmaps[warp['dest_map']];back=target['warp_events'][int(warp['dest_warp_id'])]
    self.assertEqual(back['dest_map'],m['id'])
    self.assertNotEqual((m['id'],i),(warp['dest_map'],int(warp['dest_warp_id'])))
  route=map_data(names[0]);r9=map_data('TH13_Route9')
  self.assertIn(dict(map=r9['id'],offset=0,direction='left'),route['connections'])
  self.assertIn(dict(map=route['id'],offset=0,direction='right'),r9['connections'])
  for name in names[2:]:
   m=map_data(name);self.assertTrue(m['requires_flash']);self.assertTrue(m['allow_escaping'])
   self.assertEqual([(w['x'],w['y']) for w in m['warp_events']],[(w['x'],w['y']) for w in map_data(name.replace('TH13_','')+'_Frlg')['warp_events']])
  # Each disconnected native floor section must contain >=2 transition endpoints.
  for name in names[2:]:
   m=map_data(name);w,h,cells=tiles(name);floor={(i%w,i//w) for i,t in enumerate(cells) if not t&0xc00}
   block={(o['x'],o['y']) for o in m['object_events']}
   endpoints={(x['x'],x['y']) for x in m['warp_events']}
   for end in endpoints:
    seen=reachable(end,floor,block)
    self.assertGreaterEqual(len(endpoints&seen),2,(name,end))

 def test_tunnel_encounters_are_ninety_percent_kanto(self):
  g=json.loads((ROOT/'src/data/wild_encounters.json').read_text())['wild_encounter_groups'][0]
  rates=next(f['encounter_rates'] for f in g['fields'] if f['type']=='land_mons')
  for mapid in ['MAP_TH13_ROCK_TUNNEL_1F','MAP_TH13_ROCK_TUNNEL_B1F']:
   e=[e for e in g['encounters'] if e.get('map')==mapid];self.assertEqual(len(e),1)
   mons=e[0]['land_mons']['mons'];self.assertEqual(len(mons),len(rates));totals=Counter()
   for weight,mon in zip(rates,mons):
    self.assertGreater(weight,0);self.assertTrue(10<=mon['min_level']<=mon['max_level']<=30);totals[mon['species']]+=weight
   self.assertEqual(totals.pop('SPECIES_ARON'),5);self.assertEqual(totals.pop('SPECIES_DUNSPARCE'),5)
   self.assertEqual(sum(totals.values()),90)
   self.assertLessEqual(set(totals),{'SPECIES_ZUBAT','SPECIES_GEODUDE','SPECIES_MACHOP','SPECIES_MANKEY','SPECIES_ONIX'})

 def test_items_graphics_and_scripts_use_valid_project_references(self):
  constants=(ROOT/'include/constants/event_objects.h').read_text()
  defined=set(re.findall(r'^(?:#define |\s+)(OBJ_EVENT_GFX_\w+)',constants,re.M))
  scripts='\n'.join(p.read_text(encoding='utf8') for p in (ROOT/'data/scripts/three_horizons').glob('*.inc'))
  labels=set(re.findall(r'^(\w+)::',scripts,re.M));pickups=[]
  for name in ['TH13_Route10','TH13_RockTunnel_1F','TH13_RockTunnel_B1F']:
   m=map_data(name)
   for obj in m['object_events']:
    self.assertIn(obj['graphics_id'].split('(')[0],defined)
    self.assertIn(obj['script'],labels|{'EventScript_RockSmash'})
    if obj['graphics_id'].startswith('OBJ_EVENT_GFX_ITEM_BALL'):pickups.append(obj)
   pickups.extend(o for o in m['bg_events'] if o['type']=='hidden_item')
  self.assertEqual(len(pickups),10)
  self.assertEqual({o['flag'] for o in pickups},{'FLAG_TH13_PICKUP_'+str(i) for i in range(9,19)})

 def test_twenty_one_native_first_rosters_and_placements_unchanged(self):
  ids=dict(re.findall(r'#define (TRAINER_TH\w+) (\d+)',(ROOT/'include/constants/opponents.h').read_text()))
  old=(ROOT/'src/data/trainers_frlg.party').read_text();new=(ROOT/'src/data/trainers.party').read_text()
  registry=(ROOT/'src/data/three_horizons_rematches.h').read_text()
  for name,start,count in [('Route10',123,6),('RockTunnel_1F',129,7),('RockTunnel_B1F',136,8)]:
   m=map_data('TH13_'+name);native=map_data(name+'_Frlg')
   actual=[o for o in m['object_events'] if o['trainer_type']=='TRAINER_TYPE_NORMAL']
   original=[o for o in native['object_events'] if o['trainer_type']=='TRAINER_TYPE_NORMAL'];self.assertEqual(len(actual),count)
   for i,(a,b) in enumerate(zip(actual,original)):
    for field in ['x','y','elevation','movement_type','movement_range_x','movement_range_y','trainer_sight_or_berry_tree_id']:self.assertEqual(a[field],b[field])
    trainer=b['script'].split('_')[-1].upper();tid='TRAINER_TH13_'+name.upper()+'_'+trainer
    self.assertEqual(int(ids[tid]),start+i);self.assertIn('{'+tid+', '+m['id']+', '+str(i+1)+'}',registry)
    body=re.search(r'=== TRAINER_[A-Z_]*'+trainer+r' ===\n(.*?)(?=\n===|\Z)',old,re.S)[1].strip()
    actualbody=re.search(r'=== '+tid+r' ===\n(.*?)(?=\n===|\n#endif|\Z)',new,re.S)[1].strip();self.assertEqual(actualbody,body)

 def test_research_scene_is_optional_repeatable_and_photo_once(self):
  for gear in (False,True):
   for answer in (0,1):
    s=Scene(gear,answer);s.run('TH13_RockTunnel_Pair');s.run('TH13_RockTunnel_Pair')
    self.assertEqual(s.entries,{'TH_RESEARCH_ROCK_TUNNEL'})
    self.assertEqual(s.photos,{'TH_PHOTO_ROCK_TUNNEL'} if gear and answer else set())
    self.assertEqual(s.flashes,int(gear and answer))
    self.assertEqual(s.messages.count('TH13_RockTunnel_FirstText'),1)

 def test_route10_heal_and_shared_research_call(self):
  data=json.loads((ROOT/'src/data/heal_locations.json').read_text())
  records=next(v for v in data.values() if isinstance(v,list))
  entries=[e for e in records if e['id']=='HEAL_LOCATION_TH13_ROUTE10'];self.assertEqual(len(entries),1)
  e=entries[0];m=map_data('TH13_Route10_PokemonCenter_1F')
  self.assertEqual(e['map'],m['id']);self.assertEqual(e['respawn_map'],m['id'])
  self.assertIn(e['respawn_npc'],[o['local_id'] for o in m['object_events']])
  script=(ROOT/'data/maps/TH13_Route10_PokemonCenter_1F/scripts.inc').read_text()
  self.assertIn('setrespawn HEAL_LOCATION_TH13_ROUTE10',script)
  self.assertIn('TH_CALL_ROUTE10',script);self.assertIn('TH_ScriptResearchQueueCall',script)

if __name__=='__main__':unittest.main()
