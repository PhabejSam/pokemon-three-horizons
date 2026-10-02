"""Authored handoff routing; native tests own the item/receipt transaction."""
import json
import re
import unittest
from pathlib import Path
ROOT = Path(__file__).resolve().parents[3]

class Handoff:
    def __init__(self, stage, supplies=7, result=1):
        self.lines, self.labels = [], {}
        for p in (ROOT/'data/scripts/three_horizons').glob('*.inc'):
            for raw in p.read_text(encoding='utf-8').splitlines():
                line = raw.split('@',1)[0].strip()
                if not line: continue
                if line.endswith(':'): self.labels[line.rstrip(':')] = len(self.lines)
                else: self.lines.append(line)
        self.vars = {'VAR_TH_STAGE':stage,'VAR_TH_SUPPLY_MASK':supplies}
        self.messages, self.calls = [], []
        self.result = result
    def val(self, x):
        constants={'TH_STAGE_PARTNER':2,'TH_SUPPLIES_COMPLETE':7,'TRUE':1,'FALSE':0}
        return self.vars.get(x, constants.get(x,int(x) if x.isdecimal() else x))
    def run(self,label):
        pc,stack=self.labels[label],[]
        for _ in range(100):
            # Existing supply and map frontend internals have separate coverage.
            if pc in [self.labels[x] for x in ('TH_OakSupplies','TH_EventScript_KantoRegionMap')]: return
            line=self.lines[pc];pc+=1
            op,_,tail=line.partition(' ');a=[x.strip() for x in tail.split(',')]
            if op=='end': return
            if op=='return':
                if not stack: return
                pc=stack.pop()
            elif op in ('goto','call'):
                if op=='call': stack.append(pc)
                pc=self.labels[a[0]]
            elif op.startswith('goto_if_'):
                x,y=self.val(a[0]),self.val(a[1]);kind=op[8:]
                match={'eq':x==y,'ne':x!=y,'ge':x>=y,'lt':x<y}.get(kind)
                if match: pc=self.labels[a[2]]
            elif op=='setvar':self.vars[a[0]]=self.val(a[1])
            elif op=='msgbox':self.messages.append(a[0])
            elif op=='special':
                if a[0]!='TH14_ScriptGiveUniqueItem':raise AssertionError(line)
                self.calls.append((self.vars['VAR_0x8004'],self.vars['VAR_0x8005']))
                self.vars['VAR_RESULT']=self.result
            elif op not in ('lock','faceplayer','release','playfanfare','waitfanfare','closemessage'):
                raise AssertionError(line)
        raise AssertionError('handoff did not terminate')

class TownMap(unittest.TestCase):
    def test_town_map_daisy_after_partner_and_oak_catchup(self):
        for stage in range(5):
            s=Handoff(stage);s.run('TH_Local_RivalHouse_0')
            self.assertEqual(s.calls,[('ITEM_TOWN_MAP','FLAG_TH14_TOWN_MAP')] if stage>=2 else [])
        for supplied in (0,6,7):
            s=Handoff(4,supplied);s.run('TH_EventScript_Oak')
            self.assertEqual(s.calls,[('ITEM_TOWN_MAP','FLAG_TH14_TOWN_MAP')] if supplied==7 else [])
    def test_full_bag_and_already_owned_never_announce_receipt(self):
        for speaker in ('TH_Local_RivalHouse_0','TH_EventScript_Oak'):
            paths=[]
            for result in (0,1,2):
                s=Handoff(4,result=result);s.run(speaker);paths.append(s.messages)
                self.assertEqual(len(s.calls),1)
            self.assertNotEqual(paths[0],paths[1])
            self.assertNotEqual(paths[1],paths[2])
    def test_table_remains_inspection_not_second_item_source(self):
        data=json.loads((ROOT/'data/maps/TH_RivalHouse/map.json').read_text())
        self.assertEqual(data['object_events'][0]['script'],'TH_Local_RivalHouse_0')
        table=Handoff(4);table.run('TH_Local_RivalHouse_1');self.assertFalse(table.calls)
    def test_initial_sendoff_points_to_daisy_without_consuming_gift(self):
        lab=(ROOT/'data/scripts/three_horizons/lab.inc').read_text()
        flow=lab.split('TH_Lab_Confirm:',1)[1].split('TH_Lab_AlreadyChosen:',1)[0]
        self.assertIn('goto TH_OakSupplies',flow)
        self.assertNotIn('TH14_',flow)
        text=(ROOT/'data/scripts/three_horizons/text.inc').read_text().split('TH_Text_OakSendoff::',1)[1].split('\n\n',1)[0]
        self.assertIn('DAISY',text)
        self.assertIn('TOWN MAP',text)
    def test_gift_whitelist_has_only_authored_ledger_pairs(self):
        content=json.loads((ROOT/'tools/three_horizons/chapter14_content.json').read_text())
        pairs=content.get('uniqueItems',[])
        self.assertIn({'item':'ITEM_TOWN_MAP','receipt':'FLAG_TH14_TOWN_MAP'},pairs)
        receipts={row['name'] for row in content['receipts']}
        self.assertTrue(all(p['receipt'] in receipts for p in pairs))
        self.assertEqual(len(pairs),len({p['receipt'] for p in pairs}))

if __name__=='__main__':unittest.main()
