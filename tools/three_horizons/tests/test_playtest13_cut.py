import json
import re
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
TREES = {"OBJ_EVENT_GFX_CUTTABLE_TREE", "OBJ_EVENT_GFX_CUTTABLE_TREE_FRLG"}
POOL = {f"FLAG_TEMP_{i:X}" for i in range(0x11, 0x20)}

class CutSessionContract(unittest.TestCase):
    def test_every_chapter_map_fits_the_native_obstacle_session_pool(self):
        names = json.loads((ROOT / "tools/mapjson/three_horizons_maps.json").read_text())["maps"]
        maximum = 0
        for name in names:
            objects = json.loads((ROOT / "data/maps" / name / "map.json").read_text())["object_events"]
            authored = [o["flag"] for o in objects if o.get("flag") in POOL]
            missing = sum(o.get("graphics_id") in TREES and o.get("flag") == "0" for o in objects)
            self.assertEqual(len(authored), len(set(authored)), name)
            self.assertLessEqual(missing + len(authored), len(POOL), name)
            maximum = max(maximum, missing + len(authored))
        self.assertGreater(maximum, 0)

    def test_high_temporary_flags_are_not_used_by_chapter_scripts(self):
        # These engine flags belong to obstacle templates and clear on map exit.
        # A future script use must explicitly reconcile this ownership contract.
        files = list((ROOT / "data/scripts/three_horizons").glob("*.inc"))
        names = json.loads((ROOT / "tools/mapjson/three_horizons_maps.json").read_text())["maps"]
        files += [path for n in names for path in (ROOT / "data/maps" / n).glob("*.inc")]
        for path in files:
            self.assertFalse(set(re.findall(r"\bFLAG_TEMP_[0-9A-F]+\b", path.read_text())) & POOL, str(path))

    def test_authored_obstacle_receipts_are_not_shared_with_other_objects(self):
        names = json.loads((ROOT / "tools/mapjson/three_horizons_maps.json").read_text())["maps"]
        for name in names:
            objects = json.loads((ROOT / "data/maps" / name / "map.json").read_text())["object_events"]
            for obj in objects:
                if obj.get("flag") in POOL:
                    self.assertIn(obj.get("graphics_id"), TREES | {"OBJ_EVENT_GFX_BREAKABLE_ROCK", "OBJ_EVENT_GFX_BREAKABLE_ROCK_FRLG"}, name)

if __name__ == "__main__":
    unittest.main()
