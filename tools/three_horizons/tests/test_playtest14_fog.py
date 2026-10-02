import json
import unittest
from pathlib import Path
ROOT=Path(__file__).resolve().parents[3]
class Playtest14Fog(unittest.TestCase):
    def test_tower_visual_weather_and_native_donors_preserved(self):
        for floor in range(3,7):
            data=json.loads((ROOT/f'data/maps/TH13_PokemonTower_{floor}F/map.json').read_text())
            self.assertEqual(data['weather'],'WEATHER_FOG_HORIZONTAL')
        maps=json.loads((ROOT/'tools/three_horizons/chapter14_maps.json').read_text())
        self.assertEqual((maps[33]['name'],maps[33]['group'],maps[33]['index']),('TH14_PokemonTower_7F',76,33))
    def test_only_automatic_fog_paths_consult_tower_boundary(self):
        helper=(ROOT/'src/three_horizons_chapter14.c').read_text()
        self.assertIn('bool32 TH14_IsTowerMap',helper)
        for name in ('src/battle_util.c','src/battle_main.c'):
            code=(ROOT/name).read_text()
            self.assertIn('TH14_IsTowerMap',code)
            self.assertIn('#if THREE_HORIZONS',code)
        # Intentional move/ability terrain remains the native engine's job.
        source=(ROOT/'src/battle_util.c').read_text()
        section=source.split('case FIELD_EFFECT_TRAINER_STATUSES:',1)[1].split('case FIELD_EFFECT_OVERWORLD_TERRAIN:',1)[0]
        self.assertNotIn('TH14_IsTowerMap',section)
if __name__=='__main__':unittest.main()
