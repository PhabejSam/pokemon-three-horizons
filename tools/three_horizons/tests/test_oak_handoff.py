import json
import re
import struct
import unittest
from pathlib import Path
from test_rival_scenes import movement

ROOT = Path(__file__).resolve().parents[3]

class OakHandoff(unittest.TestCase):
    def test_every_display_approach_has_a_collision_safe_handoff_and_return(self):
        script = (ROOT/'data/scripts/three_horizons/lab.inc').read_text(encoding='utf8')
        blocks = struct.unpack('<182H', (ROOT/'data/layouts/PalletTown_ProfessorOaksLab_Frlg/map.bin').read_bytes())
        objects = json.loads((ROOT/'data/maps/TH_OaksLab/map.json').read_text())['object_events']
        occupied = {(o['x'], o['y']) for o in objects if o['local_id'] not in ('LOCALID_TH_OAK','LOCALID_TH_ROBIN_LAB')}
        players = set()
        for x in (8,9,10):
            for pos in ((x-1,4),(x+1,4),(x,3),(x,5)):
                if pos not in occupied and not blocks[pos[1]*13+pos[0]] & 0xc00:
                    players.add((x,6) if pos==(x,5) else pos)
        dispatch = re.findall(r'goto_if_ne VAR_0x8008, (\d+), TH_OakCheck\d+\n    goto_if_eq VAR_0x8009, (\d+), TH_OakApproach(\d+)',script)
        self.assertEqual({(int(x),int(y)) for x,y,_ in dispatch},players)
        for x,y,index in dispatch:
            player=(int(x),int(y))
            walk=movement(script,'TH_Movement_OakApproach'+index,(6,3))
            self.assertEqual(abs(walk[-1][0]-player[0])+abs(walk[-1][1]-player[1]),1)
            back=movement(script,'TH_Movement_OakReturn'+index,walk[-1])
            self.assertEqual(back[-1],(6,3))
            for pt in walk+back:
                self.assertNotEqual(pt,player)
                self.assertNotIn(pt,occupied)
                self.assertEqual(blocks[pt[1]*13+pt[0]] & 0xc00,0)
        self.assertIn('call TH_Lab_OakApproach\n    goto TH_OakSupplies',script)
        self.assertIn('msgbox TH_Text_BagFull\n    call TH_Lab_OakReturn',script)

    def test_training_clerk_and_pc_kit_are_reachable_without_a_new_game(self):
        mart=json.loads((ROOT/'data/maps/TH_ViridianMart/map.json').read_text())
        self.assertEqual(sum(o['script']=='TH_TrainingClerk' for o in mart['object_events']),1)
        home=(ROOT/'data/scripts/three_horizons/home.inc').read_text(encoding='utf8')
        self.assertLess(home.index('special TH_ScriptDeliverTrainingKit'),home.index('special PlayerPC'))

    def test_capture_editor_precedes_dex_and_native_delivery(self):
        battle=(ROOT/'src/battle_script_commands.c').read_text()
        fn=battle.split('static void Cmd_trysetcaughtmondexflags(void)\n{',1)[1].split('static void Cmd_displaydexinfo',1)[0]
        self.assertLess(fn.index('TH_OpenCaughtMonEditor'),fn.index('HandleSetPokedexFlag'))
        script=(ROOT/'data/battle_scripts_2.s').read_text()
        flow=script.split('BattleScript_TryPrintCaughtMonInfo:',1)[1].split('BattleScript_SuccessBallThrowEnd::',1)[0]
        self.assertLess(flow.index('setbyte gBattleCommunication, 0'),flow.index('trysetcaughtmondexflags'))
        self.assertLess(flow.index('trysetcaughtmondexflags'),flow.index('trygivecaughtmonnick'))
        self.assertLess(flow.index('trygivecaughtmonnick'),flow.index('givecaughtmon BattleScript'))

if __name__ == '__main__':
    unittest.main()
