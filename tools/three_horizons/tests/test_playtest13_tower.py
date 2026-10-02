import json,re,unittest
from tools.three_horizons.tests.test_playtest11_maps import ROOT,map_data,tiles,reachable
from tools.three_horizons.tests.test_playtest14_mother import Scene
class Tower(unittest.TestCase):
 def test_append_only_registry_and_reciprocal_graph(self):
  names=[f'TH13_PokemonTower_{i}F' for i in range(1,7)]
  registry=json.loads((ROOT/'data/maps/map_groups.json').read_text())['gMapGroup_ThreeHorizons']
  self.assertEqual(registry[112:118],names)
  self.assertNotIn('TH13_PokemonTower_7F',registry)
  groups=json.loads((ROOT/'data/maps/map_groups.json').read_text())
  maps={map_data(n)['id']:map_data(n) for n in registry+groups['gMapGroup_ThreeHorizons14']}
  for n in names+['TH13_LavenderTown']:
   m=map_data(n)
   for w in m['warp_events']:
    self.assertIn(w['dest_map'],maps)
    other=maps[w['dest_map']];back=other['warp_events'][int(w['dest_warp_id'])]
    self.assertEqual(back['dest_map'],m['id'],(n,w))
  self.assertEqual(len(maps['MAP_TH13_POKEMON_TOWER_6F']['warp_events']),2)
  self.assertEqual(maps['MAP_TH13_POKEMON_TOWER_6F']['warp_events'][0]['dest_map'],'MAP_TH13_POKEMON_TOWER_5F')
  self.assertEqual(maps['MAP_TH13_POKEMON_TOWER_6F']['warp_events'][1]['dest_map'],'MAP_TH14_POKEMON_TOWER_7F')
 def test_unresolved_endpoint_every_lane_stays_closed_until_pt14_resolution(self):
  m=map_data('TH13_PokemonTower_6F');w,h,c=tiles(m['name'])
  self.assertEqual({(e['x'],e['y']) for e in m['coord_events']},{(11,15),(12,16)})
  for e in m['coord_events']:
   self.assertEqual(e['var'],'VAR_TEMP_1');self.assertEqual(e['var_value'],'0')
   self.assertEqual(e['script'],'TH13_Tower_GhostBarrier')
  script=(ROOT/'data/maps'/m['name']/'scripts.inc').read_text()
  self.assertRegex(script,r'setmetatile 11, 16, \d+, TRUE')
  self.assertIn('setvar VAR_TEMP_1, 0',script)
  floor={(i%w,i//w) for i,t in enumerate(c) if not t&0xc00}
  floor.discard((11,16))
  self.assertNotIn((11,16),reachable((18,10),floor,set()))
  self.assertTrue({(11,14),(12,15)}<=floor)
  source=(ROOT/'data/scripts/three_horizons/chapter13_tower.inc').read_text()
  self.assertNotRegex(source,r'(giveitem|additem) ITEM_(SILPH_SCOPE|POKE_FLUTE)')
  self.assertNotIn('MAP_TH13_POKEMON_TOWER_7F',source)
  self.assertNotRegex(source,r'setflag FLAG_(?:HIDE_)?(?:MR_FUJI|RESCUED|DEFEATED_MAROWAK)')
  current=source+(ROOT/'data/scripts/three_horizons/chapter14_tower.inc').read_text()
  self.assertIn('goto TH14_Tower_MotherBarrier',source)
  self.assertIn('checkitem ITEM_SILPH_SCOPE',current)
  self.assertIn('goto_if_set FLAG_TH13_ENDPOINT',current)
  self.assertEqual(current.count('setflag FLAG_TH13_ENDPOINT'),1)
  self.assertNotRegex(current,r'trainerbattle[^\n]*TRAINER_TH(?:11|14)_(?:JESSIE|JAMES)')
 def test_native_trainers_and_finite_item_receipts(self):
  count=0;flags=[]
  for i in range(1,7):
   m=map_data(f'TH13_PokemonTower_{i}F');native=map_data(f'PokemonTower_{i}F_Frlg')
   old=[o for o in native['object_events'] if o['trainer_type']=='TRAINER_TYPE_NORMAL' and 'Rival' not in o['script']]
   new=[o for o in m['object_events'] if o['trainer_type']=='TRAINER_TYPE_NORMAL']
   self.assertEqual([(o['x'],o['y'],o['movement_type']) for o in new],[(o['x'],o['y'],o['movement_type']) for o in old])
   count+=len(new)
   for o in m['object_events']:
    if 'Item' in o['script']:flags.append(o['flag'])
   for e in m['bg_events']:
    if e['type']=='hidden_item':flags.append(e['flag'])
  self.assertEqual(count,13);self.assertEqual(len(flags),len(set(flags)))
  self.assertTrue(all(f.startswith('FLAG_TH13_PICKUP_') for f in flags))
 def test_no_inherited_rival_or_fuji_resolution(self):
  second=map_data('TH13_PokemonTower_2F')
  self.assertFalse(second['coord_events'])
  self.assertFalse(any('Rival' in o['script'] or 'FUJI' in o['graphics_id'] for o in second['object_events']))
  source=(ROOT/'data/scripts/three_horizons/chapter13_tower.inc').read_text()
  self.assertIn('special HealPlayerParty',source)
  self.assertIn('SILPH SCOPE',source);self.assertIn('CELADON',source)
 def test_no_scope_endpoint_receipt_once_and_old_receipts_survive(self):
  s=Scene(scope=False);s.flags|={'FLAG_BADGE03_GET','FLAG_TH12_BILL_RESCUED'}
  before=set(s.flags)
  for visit in range(3):
   s.run('TH13_Tower_GhostBarrier')
   self.assertEqual(s.flags,before|{'FLAG_TH13_ENDPOINT'})
   self.assertEqual(s.battles,0);self.assertEqual(s.awards,0)
   self.assertIn(('applymovement',['LOCALID_PLAYER','TH14_Mother_StageAbove']),s.trace)
  self.assertEqual(s.trace.count(('msgbox',['TH13_Tower_EndpointText'])),1)
  self.assertEqual(s.trace.count(('msgbox',['TH13_Tower_RepeatText'])),2)
 def test_native_first_parties_and_encounters_are_preserved(self):
  old=(ROOT/'src/data/trainers_frlg.party').read_text();new=(ROOT/'src/data/trainers.party').read_text()
  rematches=(ROOT/'src/data/three_horizons_rematches.h').read_text()
  entries=rematches.split('sRematchEntries[] = {',1)[1].split('};',1)[0]
  self.assertEqual(len(re.findall(r'^    \{TRAINER_(?!TH14_)',entries,re.M)),121)
  self.assertEqual(len(re.findall(r'^    \{TRAINER_TH14_',entries,re.M)),30)
  for i in range(3,7):
   m=map_data(f'TH13_PokemonTower_{i}F')
   for o in m['object_events']:
    if o['trainer_type']!='TRAINER_TYPE_NORMAL':continue
    name=o['script'].split('_')[-1].upper();tid=f'TRAINER_TH13_POKEMONTOWER_{i}F_'+name
    source=re.findall(r'=== TRAINER_[A-Z_]*'+name+r' ===\n(.*?)(?=\n===|\Z)',old,re.S)
    self.assertEqual(len(source),1)
    target=re.search(r'=== '+tid+r' ===\n(.*?)(?=\n===|\n#endif|\Z)',new,re.S)[1]
    self.assertEqual(target.strip(),source[0].strip())
    self.assertIn('{'+tid+', '+m['id']+', ',rematches)
  rows=json.loads((ROOT/'src/data/wild_encounters.json').read_text())['wild_encounter_groups'][0]['encounters']
  for i in range(3,7):
   native=next(e for e in rows if e.get('base_label')==f'sPokemonTower{i}F_FireRed')
   added=[e for e in rows if e.get('map')==f'MAP_TH13_POKEMON_TOWER_{i}F']
   self.assertEqual(len(added),1);self.assertEqual(added[0]['land_mons'],native['land_mons'])
if __name__=='__main__':unittest.main()
