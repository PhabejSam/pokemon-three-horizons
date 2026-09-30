import json, unittest
from pathlib import Path
ROOT=Path(__file__).resolve().parents[3]
PLACEMENTS={
 'MAP_TH_ROUTE2':[('BULBASAUR',5)],
 'MAP_TH_VIRIDIAN_FOREST':[('TREECKO',7),('CHIKORITA',5)],
 'MAP_TH_ROUTE3':[('CHARMANDER',8)],
 'MAP_TH_ROUTE4':[('TORCHIC',8)],
 'MAP_TH_MT_MOON_1F':[('CYNDAQUIL',9)],
 'MAP_TH_ROUTE22':[('MUDKIP',5)],
 'MAP_TH12_ROUTE24':[('TOTODILE',10)],
 'MAP_TH12_ROUTE25':[('SQUIRTLE',10)]}
class Chapter12Encounters(unittest.TestCase):
 def test_starters_are_exactly_five_percent_in_every_available_time_table(self):
  data=json.loads((ROOT/'src/data/wild_encounters.json').read_text())
  group=data['wild_encounter_groups'][0];rates=next(f['encounter_rates'] for f in group['fields'] if f['type']=='land_mons')
  for mid,pairs in PLACEMENTS.items():
   entries=[e for e in group['encounters'] if e['map']==mid]
   self.assertTrue(entries,mid)
   for e in entries:
    mons=e['land_mons']['mons'];self.assertEqual(len(mons),len(rates));self.assertEqual(sum(rates),100)
    for species,level in pairs:
     slots=[(rate,m) for rate,m in zip(rates,mons) if m['species']=='SPECIES_'+species]
     self.assertEqual(sum(rate for rate,m in slots),5,(e['base_label'],species))
     self.assertTrue(all(m['min_level']==m['max_level']==level for _,m in slots))
 def test_cave_rare_rates_and_harbor_old_rod(self):
  es=json.loads((ROOT/'src/data/wild_encounters.json').read_text())['wild_encounter_groups'][0]['encounters']
  rates=[20,20,10,10,10,10,5,5,4,4,1,1]
  for e in es:
   if e['map'].startswith('MAP_TH_MT_MOON'):
    mons=e['land_mons']['mons'];self.assertEqual(sum(w for w,m in zip(rates,mons) if m['species']=='SPECIES_MAKUHITA'),1)
    if e['map']=='MAP_TH_MT_MOON_B2F':self.assertEqual(sum(w for w,m in zip(rates,mons) if m['species']=='SPECIES_CLEFAIRY'),5)
  harbor=[e for e in es if e['map']=='MAP_TH12_VERMILION_CITY'];self.assertTrue(harbor)
  for e in harbor:self.assertEqual(len(e['fishing_mons']['mons']),10)
if __name__=='__main__':unittest.main()
