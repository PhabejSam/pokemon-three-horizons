"""Execute the small Living City branches with the existing script harness."""
import re
import unittest
from tools.three_horizons.tests.test_playtest14_fuji import Scene, ROOT

ACTORS=('RocketGrunt1','Woman','RocketGrunt2','SilphCoScientist')
PREFIX='TH14_CeladonCity_EventScript_'

def scene():
    s=Scene()
    s.lines='\n'.join((ROOT/'data/scripts/three_horizons'/n).read_text(encoding='utf-8') for n in ('chapter14_celadon.inc','chapter13_lavender.inc')).splitlines()
    s.labels={m[1]:i+1 for i,line in enumerate(s.lines) if (m:=re.match(r'^(\w+)::?$',line))}
    return s

class Dialogue(unittest.TestCase):
    def test_early_city_reactions_remain_unchanged(self):
        for actor in ACTORS:
            with self.subTest(actor=actor):
                s=scene();s.run(PREFIX+actor)
                self.assertEqual(s.messages,[PREFIX+actor+'_Text'])
                self.assertFalse(s.flags|s.defeated|s.items)

    def test_victory_before_scope_pickup_changes_reactions_without_claiming_ownership(self):
        for actor in ACTORS:
            with self.subTest(actor=actor):
                s=scene();s.defeated={'TRAINER_TH14_GIOVANNI'};s.flags={'FLAG_TH13_GEAR'}
                s.run(PREFIX+actor)
                self.assertEqual(s.messages,[PREFIX+actor+'_After_Text'])
                self.assertEqual(s.defeated,{'TRAINER_TH14_GIOVANNI'})
                self.assertEqual(s.flags,{'FLAG_TH13_GEAR'})
                self.assertFalse(s.items|set(s.vars));self.assertFalse(s.warps+s.removed+s.calls)
                self.assertFalse(s.locked)

    def test_scope_receipt_changes_scientist_only_and_preserves_all_story_state(self):
        for actor in ACTORS:
            with self.subTest(actor=actor):
                s=scene();s.defeated={'TRAINER_TH14_GIOVANNI'}
                s.flags={'FLAG_TH14_SILPH_SCOPE','FLAG_TH13_GEAR'};s.items={'ITEM_SILPH_SCOPE'}
                s.run(PREFIX+actor)
                suffix='_Scope_Text' if actor=='SilphCoScientist' else '_After_Text'
                self.assertEqual(s.messages,[PREFIX+actor+suffix])
                self.assertEqual(s.flags,{'FLAG_TH14_SILPH_SCOPE','FLAG_TH13_GEAR'})
                self.assertEqual(s.items,{'ITEM_SILPH_SCOPE'})
                self.assertEqual(s.defeated,{'TRAINER_TH14_GIOVANNI'})
                self.assertFalse(s.vars or s.warps or s.removed or s.calls or s.gifts)

    def test_lavender_worker_directs_to_open_westward_route_and_restricted_south(self):
        s=scene();s.run('TH13_Lavender_Worker')
        self.assertEqual(s.messages,['TH13_Lavender_WorkerText'])
        text='\n'.join(s.lines[s.labels['TH13_Lavender_WorkerText']:]).split('::',1)[0]
        for word in ('ROUTE 8','CELADON','UNDERGROUND','south'):
            self.assertIn(word,text)
        self.assertNotIn('roads west and south are closed',text)
        self.assertFalse(s.flags or s.vars or s.defeated or s.items)

if __name__=='__main__':unittest.main()
