"""Documented forest edge repair: native art, unchanged access and interactions."""
import hashlib
import json
import unittest
from tools.three_horizons.tests.test_playtest11_maps import map_data, tiles, reachable

class CutGeometry(unittest.TestCase):
    def setUp(self):
        self.w, self.h, self.grid = tiles('TH_ViridianForest')
        _, _, self.before = tiles('ViridianForest_Frlg')
        # Exact pre-PT14 map construction, checked against the shipped baseline.
        for y in range(29, 35):
            for x in range(27, 36): self.before[y*self.w+x] = 0x3001
        for y in (31, 32):
            for x in range(36, 39): self.before[y*self.w+x] = 0x3001

    def row(self, x, y):
        return self.grid[y*self.w+x:y*self.w+x+3]

    def test_north_edges_finish_with_native_trunks_and_bases(self):
        for x, y in [(27,27), (30,27), (33,27), (36,29)]:
            self.assertEqual(self.row(x,y), [0x690,0x6a1,0x692])
            self.assertEqual(self.row(x,y+1), [0x6a3,0x6a4,0x6a5])

    def test_south_crowns_fit_inside_existing_blocked_perimeter(self):
        for x, y in [(27,35), (30,35), (33,35), (36,33)]:
            self.assertEqual(self.row(x,y), [0x401,0x681,0x401])
            self.assertEqual(self.row(x,y+1), [0x688,0x689,0x68a])
            # The following body row must retain its original forest phase.
            self.assertEqual(self.row(x,y+2), [0x690,0x691,0x692])

    def test_only_documented_edge_art_changes_and_all_floor_is_identical(self):
        edge=set()
        for x,y in [(27,27),(30,27),(33,27),(36,29),(27,35),(30,35),(33,35),(36,33)]:
            edge.update((xx,yy) for xx in range(x,x+3) for yy in range(y,y+2))
        for i, (before, after) in enumerate(zip(self.before, self.grid)):
            self.assertEqual(before & 0xfc00, after & 0xfc00, (i%self.w,i//self.w))
            if not before & 0xc00 or (i%self.w,i//self.w) not in edge:
                self.assertEqual(before,after,(i%self.w,i//self.w))

    def test_scene_objects_gate_and_interactions_stay_fixed(self):
        m=map_data('TH_ViridianForest')
        self.assertEqual(hashlib.sha256(json.dumps(m['object_events'],sort_keys=True).encode()).hexdigest(),
            'd377ec6dd1b8a004d888a68255ab709a353b1dcfaeefe89b066e23c2a3014829')
        floor={(i%self.w,i//self.w) for i,t in enumerate(self.grid) if not t&0xc00}
        gates={(38,31),(38,32)}
        self.assertNotIn((30,32),reachable((39,34),floor,gates))
        for gate in gates:
            accessible=reachable((39,34),floor,gates-{gate})
            for xy in [(30,32),(32,32),(29,34),(35,30)]: self.assertIn(xy,accessible)

if __name__=='__main__': unittest.main()
