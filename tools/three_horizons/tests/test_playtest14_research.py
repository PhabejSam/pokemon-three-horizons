"""Append-only Mother archive/art and reachable missing-Gear contact contract."""
import hashlib
import json
import re
import subprocess
import tempfile
from pathlib import Path
import unittest
from tools.three_horizons.tests.test_playtest11_maps import ROOT, map_data, tiles
from tools.three_horizons import research_photo_art as art

class Research(unittest.TestCase):
    def test_photo_png_rebuilds_exact_native_assets(self):
        root=ROOT/'graphics/three_horizons/research/photos'
        with tempfile.TemporaryDirectory() as directory:
            for extension in ('4bpp','gbapal'):
                output=Path(directory)/('mother.'+extension)
                result=subprocess.run([str(ROOT/'tools/gbagfx/gbagfx.exe'),str(root/'mothers_watch.png'),str(output)],capture_output=True,text=True)
                self.assertEqual(result.returncode,0,result.stderr)
                self.assertEqual(output.read_bytes(),(root/('mothers_watch.'+extension)).read_bytes())

    def test_append_only_ids_and_card_counts(self):
        s=(ROOT/'include/constants/three_horizons_research.h').read_text()
        for name,value in [('TH_RESEARCH_FOREST_LEGACY',10),('TH_RESEARCH_MOTHERS_WATCH',11),('TH_RESEARCH_ENTRY_COUNT',12),('TH_PHOTO_MOTHERS_WATCH',10),('TH_RESEARCH_PHOTO_COUNT',11),('TH_RESEARCH_CALL_COUNT',5)]:
            self.assertRegex(s,rf'\b{name}\s*=\s*{value}\b')

    def test_art_uses_approved_native_crop_and_is_reproducible(self):
        self.assertEqual(len(art.SCENES),11)
        self.assertEqual(art.SCENES[-1],('mothers_watch','TH13_PokemonTower_6F',4,11))
        scene,_=art.render_scene('TH13_PokemonTower_6F',4,11)
        tinted=art.spectral_tint(scene)
        self.assertNotEqual(scene.tobytes(),tinted.tobytes())
        tile,pal,_=art.encode(tinted)
        root=ROOT/'graphics/three_horizons/research/photos'
        self.assertEqual(tile,(root/'mothers_watch.4bpp').read_bytes())
        self.assertEqual(pal,(root/'mothers_watch.gbapal').read_bytes())
        manifest=json.loads((root/'manifest.json').read_text())
        self.assertEqual([x['id'] for x in manifest],list(range(11)))
        self.assertEqual(manifest[-1]['tiles_sha256'],hashlib.sha256(tile).hexdigest())

    def test_gear_contact_is_reachable_and_cannot_fabricate_old_records(self):
        m=map_data('TH13_PokemonTower_1F')
        actors=[a for a in m['object_events'] if a['script']=='TH14_Tower_GearContact']
        self.assertEqual(len(actors),1)
        a=actors[0];self.assertEqual((a['x'],a['y']),(5,11))
        self.assertEqual(a['movement_type'],'MOVEMENT_TYPE_FACE_RIGHT')
        w,h,c=tiles('TH13_PokemonTower_1F')
        for x,y in [(5,11),(6,11),(5,10),(5,12)]:self.assertFalse(c[y*w+x]&0xc00)
        self.assertLessEqual(len(m['object_events'])+2,16)
        s=(ROOT/'data/scripts/three_horizons/chapter14_tower.inc').read_text()
        self.assertIn('goto_if_set FLAG_TH13_GEAR',s)
        self.assertIn('checkitem ITEM_SILPH_SCOPE',s)
        self.assertEqual(s.count('call TH13_GiveResearchGear'),1)
        contact=s.split('TH14_Tower_GearContact::',1)[1].split('TH14_Tower7F_Entry::',1)[0]
        self.assertNotRegex(contact,r'(setflag FLAG_TH13_(OBS|PHOTO)|special TH_ScriptResearchObserve)')
        self.assertIn('chapter14_tower.inc',(ROOT/'data/scripts/three_horizons/maps.inc').read_text())

    def test_observer_is_bounded_and_uses_current_native_outfit(self):
        s=(ROOT/'src/three_horizons_research_menu.c').read_text()
        self.assertIn('static bool32 DrawObserver(',s)
        for token in ['GetPlayerAvatarGraphicsIdByStateId(PLAYER_AVATAR_STATE_NORMAL)','LoadObjectEventPaletteCopy','TH_RESEARCH_MAX_SUBJECTS','CreateSpriteUnchecked','CanAllocSpriteTiles']:
            self.assertIn(token,s)
        self.assertNotIn('CreateObjectGraphicsSprite(',s)
        self.assertIn('DrawObserver(photo->subjectCount, 128, 80, DIR_SOUTH)',s)

    def test_aftermath_delay_special_is_registered(self):
        self.assertIn('void TH_ResearchDelayCalls(u8 steps)',(ROOT/'include/three_horizons_research.h').read_text())
        self.assertIn('TH_ResearchDelayCalls(8)',(ROOT/'src/three_horizons_research.c').read_text())
        self.assertIn('def_special TH14_DelayAftermathCalls',(ROOT/'data/specials.inc').read_text())

if __name__=='__main__':unittest.main()
