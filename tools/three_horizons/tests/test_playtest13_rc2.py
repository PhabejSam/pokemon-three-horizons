"""RC2 owning script checks; native/ROM gates own display and input behavior."""
from pathlib import Path
import re
import json
import hashlib
import unittest
from tools.three_horizons.tests.test_playtest13_research import Scene
from tools.three_horizons.tests.test_playtest13_route2 import visit, HM, GEAR, BADGE, RECEIPT

ROOT = Path(__file__).resolve().parents[3]

class RC2Scripts(unittest.TestCase):
    def test_rc2_migration_recognizes_current_marker_in_every_history_guard(self):
        state = (ROOT/'src/three_horizons_state.c').read_text()
        guards = re.findall(r'if \((version != TH_STATE_VERSION_[^\n]*)\)', state)
        self.assertGreaterEqual(len(guards), 5)
        for guard in guards:
            self.assertIn('TH_STATE_VERSION_13_1', guard)
        clock = (ROOT/'src/three_horizons_clock.c').read_text()
        self.assertIn('TH_STATE_VERSION_CURRENT', clock)

    def test_outdoor_vermilion_has_no_development_boundary(self):
        script = (ROOT/'data/scripts/three_horizons/chapter12_gym.inc').read_text()
        boundary = script.split('TH12_Chapter_EndText:',1)[1]
        self.assertNotRegex(boundary, r'(?i)end of PLAYTEST|chapter ends here|next chapter')

    def test_gear_handoff_is_free_once_and_does_not_invent_photos(self):
        s = Scene(gear=False)
        s.run('TH13_GiveResearchGear')
        self.assertIn(GEAR, s.flags)
        self.assertEqual(s.queued, ['TH_CALL_ACTIVATION'])
        self.assertEqual(s.completed, [('TH_CALL_ACTIVATION', 0)])
        self.assertFalse(s.photos)
        s.run('TH13_GiveResearchGear')
        self.assertEqual(len(s.queued), 1)

    def test_lab_and_vermilion_own_gear_handoff(self):
        scripts = ROOT/'data/scripts/three_horizons'
        lab = (scripts/'lab.inc').read_text().split('TH_OakSendoff:', 1)[1].split('TH_Lab_BagFull:', 1)[0]
        self.assertIn('call TH13_GiveResearchGear', lab)
        self.assertLess(lab.index('call TH13_GiveResearchGear'), lab.index('msgbox TH_Text_OakSendoff'))
        center = (scripts/'chapter12_vermilion.inc').read_text().split('TH13_VsSeekerResearcher::',1)[1].split('TH13_VsSeekerReceived:',1)[0]
        self.assertIn('FLAG_BADGE03_GET', center)
        self.assertIn('call TH13_GiveResearchGear', center)

    def test_route2_flash_does_not_introduce_gear_or_queue_three_professors(self):
        bag, flags = {}, {BADGE}
        _, queue, _ = visit(bag, flags)
        self.assertEqual(bag, {HM: 1})
        self.assertIn(RECEIPT, flags)
        self.assertNotIn(GEAR, flags)
        self.assertEqual(queue, [])

    def test_each_automatic_call_has_one_speaker(self):
        for label in ('Activation', 'Route10', 'Lavender', 'Elm', 'Birch'):
            with self.subTest(call=label):
                s = Scene(); s.run('TH13_ResearchCall_'+label)
                self.assertEqual(len(s.messages), 1)
                self.assertEqual(len(s.completed), 1)

    def test_photo_viewer_uses_large_rom_authored_environment(self):
        source = (ROOT/'src/three_horizons_research_menu.c').read_text()
        self.assertNotIn('static void DrawTerrain', source)
        self.assertIn('TH_RESEARCH_PHOTO_HEIGHT 96', source)
        self.assertIn('charBaseIndex = 2', source)
        self.assertIn('DrawStdFrameWithCustomTileAndPalette', source)
        self.assertTrue((ROOT/'src/data/three_horizons_research_photos.h').exists())

    def test_photo_assets_match_authored_sources_and_fit_hardware_budget(self):
        folder = ROOT/'graphics/three_horizons/research/photos'
        manifest = json.loads((folder/'manifest.json').read_text())
        self.assertEqual([p['id'] for p in manifest], list(range(10)))
        for photo in manifest:
            with self.subTest(photo=photo['name']):
                self.assertEqual((photo['width'], photo['height']), (224, 96))
                source = (ROOT/photo['source_layout']).read_bytes()
                self.assertEqual(hashlib.sha256(source).hexdigest(), photo['source_sha256'])
                for extension, size, digest in [('4bpp', 10752, 'tiles_sha256'), ('gbapal', 32, 'palette_sha256')]:
                    data = (folder/(photo['name']+'.'+extension)).read_bytes()
                    self.assertEqual(len(data), size)
                    self.assertEqual(hashlib.sha256(data).hexdigest(), photo[digest])
        # BG0 UI/frame below char block 2; BG1 crop below screen block 30.
        self.assertLessEqual((512+9)*32, 2*16384)
        self.assertLessEqual(2*16384+(1+336)*32, 30*2048)

    def test_photo_flash_preserves_base_palette_owner(self):
        source = (ROOT/'data/scripts/three_horizons/chapter13_research.inc').read_text()
        photo = re.search(r'TH13_ResearchPhoto::?\n(.*?)(?=\nTH13_ResearchPhoto_Recorded:)', source, re.S).group(1)
        # FadeScreen's software path copies the tinted faded buffer to the base.
        # Native hardware fades preserve both software palette owners.
        self.assertNotRegex(photo, r'(?m)^\s*fadescreen\s+FADE_(?:TO|FROM)_WHITE')
        self.assertRegex(photo, r'fadescreenswapbuffers FADE_TO_WHITE')
        self.assertRegex(photo, r'fadescreenswapbuffers FADE_FROM_WHITE')
        self.assertLess(photo.index('special TH_ScriptBeginPhotoFlash'), photo.index('fadescreenswapbuffers FADE_TO_WHITE'))
        self.assertGreater(photo.index('special TH_ScriptEndPhotoFlash'), photo.index('fadescreenswapbuffers FADE_FROM_WHITE'))

if __name__ == '__main__': unittest.main()
