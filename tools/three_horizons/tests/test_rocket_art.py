"""Asset/registration checks: 4bpp limits and stable saved graphics IDs."""
import json
import struct
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]


class RocketArt(unittest.TestCase):
    def test_assets_fit_native_tiles_and_palette(self):
        for character in ('jessie', 'james'):
            for kind, expected in [('walking', (144, 32)), ('front', (64, 64))]:
                with self.subTest(character=character, kind=kind):
                    data = (ROOT / f'graphics/three_horizons/rocket/{character}/{kind}.png').read_bytes()
                    self.assertEqual(data[:8], b'\x89PNG\r\n\x1a\n')
                    width, height, depth, color = struct.unpack('>IIBB', data[16:26])
                    self.assertEqual((width, height), expected)
                    self.assertEqual((depth, color), (4, 3))
                    offset = 8
                    chunks = {}
                    while offset < len(data):
                        length = struct.unpack('>I', data[offset:offset + 4])[0]
                        chunks[data[offset + 4:offset + 8]] = data[offset + 8:offset + 8 + length]
                        offset += length + 12
                    self.assertEqual(len(chunks[b'PLTE']), 16 * 3)
                    self.assertEqual(chunks[b'tRNS'], b'\x00')

    def test_only_duo_actors_use_dedicated_art(self):
        moon = json.loads((ROOT / 'data/maps/TH_MtMoonB2F/map.json').read_text())
        actors = {o['local_id']: o for o in moon['object_events']}
        for character in ('JESSIE', 'JAMES'):
            self.assertEqual(actors['LOCALID_TH_' + character]['graphics_id'], 'OBJ_EVENT_GFX_TH_' + character)
        trainers = (ROOT / 'src/data/trainers.party').read_text()
        for name in ('Jessie', 'James'):
            body = trainers.split('=== TRAINER_TH11_' + name.upper() + ' ===')[1].split('===')[0]
            self.assertIn('Pic: TH ' + name, body)

    def test_reused_slots_are_not_used_by_any_map(self):
        constants = (ROOT / 'include/constants/event_objects.h').read_text()
        for character, slot in [('JESSIE', 'NATU'), ('JAMES', 'MAGNEMITE')]:
            self.assertIn(f'#define OBJ_EVENT_GFX_TH_{character} OBJ_EVENT_GFX_UNUSED_{slot}_DOLL', constants)
        for path in (ROOT / 'data/maps').glob('*/map.json'):
            for obj in json.loads(path.read_text()).get('object_events', []):
                self.assertNotIn(obj['graphics_id'], ('OBJ_EVENT_GFX_UNUSED_NATU_DOLL', 'OBJ_EVENT_GFX_UNUSED_MAGNEMITE_DOLL'), str(path))


if __name__ == '__main__':
    unittest.main()
