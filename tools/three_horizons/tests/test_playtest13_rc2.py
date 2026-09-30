"""RC2 owning script checks; native/ROM gates own display and input behavior."""
from pathlib import Path
import re
import unittest

ROOT = Path(__file__).resolve().parents[3]

class RC2Scripts(unittest.TestCase):
    def test_photo_flash_preserves_base_palette_owner(self):
        source = (ROOT/'data/scripts/three_horizons/chapter13_research.inc').read_text()
        photo = re.search(r'TH13_ResearchPhoto::?\n(.*?)(?=\nTH13_ResearchPhoto_Recorded:)', source, re.S).group(1)
        # FadeScreen's software path copies the tinted faded buffer to the base.
        # Native hardware fades preserve both software palette owners.
        self.assertNotRegex(photo, r'(?m)^\s*fadescreen\s+FADE_(?:TO|FROM)_WHITE')
        self.assertRegex(photo, r'fadescreenswapbuffers FADE_TO_WHITE')
        self.assertRegex(photo, r'fadescreenswapbuffers FADE_FROM_WHITE')

if __name__ == '__main__': unittest.main()
