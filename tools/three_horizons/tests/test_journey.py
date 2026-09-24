import json
import re
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]

class JourneyContract(unittest.TestCase):
    def test_outfit_palette_tags_do_not_alias_weather(self):
        text = (ROOT / 'include/constants/event_objects.h').read_text()
        tags = re.findall(r'#define OBJ_EVENT_PAL_TAG_TH_\w+ (0x[0-9A-Fa-f]+)', text)
        values = [int(tag, 16) for tag in tags]
        self.assertEqual(len(values), len(set(values)))
        self.assertFalse({0x1200, 0x1201}.intersection(values), 'Weather/shadow palettes collide with outfits')

    def test_brock_is_reachable_in_both_directions_from_home(self):
        names = json.loads((ROOT / 'tools/mapjson/three_horizons_maps.json').read_text())['maps']
        maps = {m['id']: m for n in names for m in [json.loads((ROOT / 'data/maps' / n / 'map.json').read_text())]}
        graph = {key: {w['dest_map'] for w in m['warp_events']} | {c['map'] for c in m['connections'] or []} for key,m in maps.items()}
        for start, end in [('MAP_TH_HOME_2F','MAP_TH_PEWTER_GYM'), ('MAP_TH_PEWTER_GYM','MAP_TH_HOME_2F')]:
            seen=set();pending=[start]
            while pending:
                node=pending.pop()
                if node not in seen:
                    seen.add(node);pending.extend(graph[node]-seen)
            self.assertIn(end, seen)

    def test_centers_have_safe_recovery_and_no_external_warps(self):
        heals=json.loads((ROOT / 'src/data/heal_locations.json').read_text())['heal_locations']
        for city in ('VIRIDIAN','PEWTER'):
            loc=next(h for h in heals if h['id']=='HEAL_LOCATION_TH_'+city)
            self.assertEqual(loc['respawn_map'],'MAP_TH_'+city+'_CENTER')
            self.assertEqual((loc['respawn_x'],loc['respawn_y']),(7,4))

if __name__ == '__main__':
    unittest.main()
