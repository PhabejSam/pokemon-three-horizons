"""Exercise mapjson output and the closed demo map graph (stdlib only)."""
import json
import hashlib
import os
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[3]
EXE = ROOT / 'tools/mapjson' / ('mapjson.exe' if os.name == 'nt' else 'mapjson')
NAMES = ('TH_Home2F', 'TH_Home1F', 'TH_Pallet', 'TH_OaksLab', 'TH_Route1', 'TH_ViridianEntrance')


class MapContract(unittest.TestCase):
    def generate(self, mode, version):
        with tempfile.TemporaryDirectory(dir=ROOT, prefix='.th-') as folder:
            out = Path(folder)
            args = [str(EXE), mode, version]
            if mode == 'layouts':
                args += ['data/layouts/layouts.json']
            else:
                args += ['data/maps/map_groups.json']
                for i, path in enumerate(sorted((ROOT / 'data/maps').glob('*/map.json'))):
                    short = out / str(i)
                    short.write_bytes(path.read_bytes())
                    args.append(str(short.relative_to(ROOT)))
            args += [str(out), str(out)]
            run = subprocess.run(args, cwd=ROOT, capture_output=True, text=True)
            self.assertEqual(run.returncode, 0, run.stderr)
            return {p.name: p.read_text() for p in out.iterdir() if p.suffix in ('.h', '.inc')}

    def test_demo_includes_native_kanto_layouts(self):
        """Rejects a mode that omits the bedroom or emits its Emerald format."""
        out = self.generate('layouts', 'three_horizons')
        self.assertIn('PalletTown_PlayersHouse_2F_FRLG_Layout::', out['layouts.inc'])
        self.assertRegex(out['layouts.inc'], r'PalletTown_PlayersHouse_2F_FRLG_Layout::[\s\S]*?\.byte TRUE')

    def test_demo_group_is_selected_only_for_demo(self):
        for version in ('emerald', 'firered', 'three_horizons'):
            out = self.generate('groups', version)
            for name in NAMES:
                line = '\t.4byte ' + name + '\n'
                self.assertEqual(line in out['groups.inc'], version == 'three_horizons', (name, version))

    def test_demo_maps_form_closed_graph(self):
        maps = {}
        for name in NAMES:
            path = ROOT / 'data/maps' / name / 'map.json'
            self.assertTrue(path.exists(), f'Missing demo map: {name}')
            record = json.loads(path.read_text())
            maps[record['id']] = record
        layouts = {x.get('id'): x for x in json.loads((ROOT / 'data/layouts/layouts.json').read_text())['layouts']}
        for record in maps.values():
            layout = layouts[record['layout']]
            for kind in ('object_events', 'warp_events', 'coord_events', 'bg_events'):
                for event in record[kind]:
                    self.assertGreaterEqual(event['x'], 0)
                    self.assertGreaterEqual(event['y'], 0)
                    self.assertLess(event['x'], layout['width'])
                    self.assertLess(event['y'], layout['height'])
            for warp in record['warp_events']:
                self.assertIn(warp['dest_map'], maps)
                self.assertGreaterEqual(int(warp['dest_warp_id']), 0)
                self.assertLess(int(warp['dest_warp_id']), len(maps[warp['dest_map']]['warp_events']))
            for connection in record['connections'] or []:
                self.assertIn(connection['map'], maps)

    def test_generation_does_not_mutate_healing_source(self):
        path = ROOT / 'src/data/heal_locations.json'
        before = path.read_bytes()
        for version in ('emerald', 'firered', 'three_horizons'):
            self.generate('groups', version)
            self.assertEqual(before, path.read_bytes())

    def test_original_map_indices_and_layout_tables_are_preserved(self):
        fixture = json.loads(Path(__file__).with_name('original-map-indices.json').read_text())
        for version, expected in fixture.items():
            layouts = self.generate('layouts', version)['layouts_table.inc']
            self.assertEqual(hashlib.sha256(layouts.encode()).hexdigest(), expected['layouts_sha256'])
            constants = self.generate('groups', version)['map_groups.h']
            indices = '\n'.join(line for line in constants.splitlines()
                                if re.match(r'\s*MAP_\w+\s*=', line) and 'MAP_TH_' not in line)
            self.assertEqual(hashlib.sha256(indices.encode()).hexdigest(), expected['map_indices_sha256'])

    def test_project_manifest_rejects_missing_map(self):
        path = ROOT / 'tools/mapjson/three_horizons_maps.json'
        original = path.read_bytes()
        try:
            path.write_text(json.dumps({'maps': ['TH_Missing']}))
            with tempfile.TemporaryDirectory() as out:
                run = subprocess.run([str(EXE), 'layouts', 'three_horizons',
                                      'data/layouts/layouts.json', out, out],
                                     cwd=ROOT, capture_output=True, text=True)
            self.assertNotEqual(run.returncode, 0)
            self.assertIn('TH_Missing', run.stderr)
        finally:
            path.write_bytes(original)

    def test_windows_line_endings_are_read_without_trailing_nuls(self):
        path = ROOT / 'tools/mapjson/three_horizons_maps.json'
        original = path.read_bytes()
        try:
            path.write_bytes(original.replace(b'\r\n', b'\n').replace(b'\n', b'\r\n'))
            self.generate('layouts', 'three_horizons')
        finally:
            path.write_bytes(original)


if __name__ == '__main__':
    unittest.main()
