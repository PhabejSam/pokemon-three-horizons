"""Approved Celadon economy tables and script coverage; runtime tests own transactions."""
import json
import re
import unittest
from tools.three_horizons.tests.test_playtest11_maps import ROOT, map_data


def menu_trace(label, choice=0, confirm=1, has_case=True, result=1, pc=False):
    """Execute authored control branches; native tests separately own delivery."""
    lines=[];labels={}
    for raw in (ROOT/'data/scripts/three_horizons/chapter14_celadon.inc').read_text().splitlines():
        line=raw.split('@',1)[0].strip()
        if line.endswith(':'): labels[line.rstrip(':')]=len(lines)
        elif line: lines.append(line)
    values={'YES':1,'NO':0,'TRUE':1,'FALSE':0};windows=set();calls=[];transactions=[];stack=[]
    def value(token):return values.get(token,int(token) if token.isdigit() else 0)
    pos=labels[label];switch=0
    for _ in range(200):
        line=lines[pos];pos+=1;op,_,tail=line.partition(' ');a=[t.strip() for t in tail.split(',')]
        if op=='end':return transactions,windows,calls
        if op in ('lock','lockall','faceplayer','releaseall','closemessage','waitmessage','waitfanfare','playfanfare','playse','bufferspeciesname','bufferitemname','buffernumberstring','message'):continue
        if op=='setvar':values[a[0]]=value(a[1])
        elif op=='copyvar':values[a[0]]=value(a[1])
        elif op=='addvar':values[a[0]]=value(a[0])+value(a[1])
        elif op=='checkitem':values['VAR_RESULT']=int(has_case)
        elif op=='dynmultichoice':values['VAR_RESULT']=choice
        elif op=='msgbox':
            if len(a)>1 and a[1]=='MSGBOX_YESNO':values['VAR_RESULT']=confirm
        elif op in ('showcoinsbox','showmoneybox'):windows.add(op)
        elif op in ('hidecoinsbox','hidemoneybox'):
            key='showcoinsbox' if op=='hidecoinsbox' else 'showmoneybox'
            assert key in windows,(label,line,windows)
            windows.remove(key)
        elif op in ('updatecoinsbox','updatemoneybox'):
            assert ('showcoinsbox' if op=='updatecoinsbox' else 'showmoneybox') in windows
        elif op=='goto':pos=labels[a[0]]
        elif op in ('goto_if_eq','goto_if_ge'):
            if (value(a[0])==value(a[1]) if op=='goto_if_eq' else value(a[0])>=value(a[1])):pos=labels[a[2]]
        elif op=='call_if_eq':
            if value(a[0])==value(a[1]):stack.append(pos);pos=labels[a[2]]
        elif op=='return':pos=stack.pop()
        elif op=='switch':switch=value(a[0])
        elif op=='case':
            if switch==value(a[0]):pos=labels[a[1]]
        elif op=='special':
            assert a[0]=='TH14_ScriptEconomy',line
            transactions.append((value('VAR_0x8004'),value('VAR_0x8005')))
            values['VAR_RESULT']=result;values['VAR_0x8006']=int(pc)
        elif op=='call':
            assert a[0].startswith('Common_EventScript_'),line
            if 'NameReceived' in a[0]: assert not windows, 'close coin UI before naming frees field windows'
            calls.append(a[0])
        else:raise AssertionError(line)
    raise AssertionError('menu failed to terminate')


class Economy(unittest.TestCase):
    def test_menu_cancel_decline_failures_and_party_pc_cleanup_follow_actual_scripts(self):
        rows=[('GameCorner_EventScript_CoinsClerk',2,2,0),
              ('GameCorner_PrizeRoom_EventScript_PrizeClerkMons',5,1,0),
              ('GameCorner_PrizeRoom_EventScript_PrizeClerkTMs',5,0,0),
              ('GameCorner_PrizeRoom_EventScript_PrizeClerkItems',5,0,5),
              ('DepartmentStore_Roof_EventScript_VendingMachine',3,4,0),
              ('DepartmentStore_Roof_EventScript_ThirstyGirl',3,5,0)]
        for tail,count,action,offset in rows:
            label='TH14_CeladonCity_'+tail
            for choice,confirm in ((127,1),(count,1),(0,0)):
                transactions,windows,_=menu_trace(label,choice,confirm)
                self.assertFalse(transactions);self.assertFalse(windows)
            if action<3:
                transactions,windows,_=menu_trace(label,has_case=False)
                self.assertFalse(transactions);self.assertFalse(windows)
            for choice in range(count):
                for result in range(5):
                    for pc in (False,True) if action==1 and result==1 else (False,):
                        transactions,windows,calls=menu_trace(label,choice,result=result,pc=pc)
                        self.assertEqual(transactions,[(action,choice+offset)])
                        self.assertFalse(windows)
                        if action==1 and result==1:
                            self.assertIn('Common_EventScript_NameReceivedBoxMon' if pc else 'Common_EventScript_NameReceivedPartyMon',calls)
                            self.assertEqual('Common_EventScript_TransferredToPC' in calls,pc)

    def test_money_menu_text_uses_glyph_instead_of_early_string_terminator(self):
        script=(ROOT/'data/scripts/three_horizons/chapter14_celadon.inc').read_text()
        for label,price in [('2_0_0',1000),('2_0_1',10000),('4_0_0',200),('4_0_1',300),('4_0_2',400)]:
            value=re.search(r'TH14_EcoMenu_'+label+r'::\n\s*\.string "([^"]+)"',script)[1]
            self.assertEqual(value.count('$'),1,value)
            self.assertTrue(value.endswith(f'¥{price}$'),value)

    def test_exact_prizes_bundles_and_roof_rewards(self):
        e=json.loads((ROOT/'tools/three_horizons/chapter14_content.json').read_text())['economy']
        self.assertEqual([(r['species'],r['level'],r['coins']) for r in e['monPrizes']],
            [('ABRA',9,180),('CLEFAIRY',8,500),('DRATINI',18,2800),('SCYTHER',25,5500),('PORYGON',26,9999)])
        self.assertEqual([(r['item'],r['coins']) for r in e['itemPrizes']],
            [('TM_ICE_BEAM',4000),('TM_IRON_TAIL',3500),('TM_THUNDERBOLT',4000),('TM_SHADOW_BALL',4500),
             ('TM_FLAMETHROWER',4000),('SMOKE_BALL',800),('MIRACLE_SEED',1000),('CHARCOAL',1000),('MYSTIC_WATER',1000),('YELLOW_FLUTE',1600)])
        self.assertEqual(e['coinBundles'],[[50,1000],[500,10000]])
        self.assertEqual([(r['drink'],r['price'],r['reward']) for r in e['drinks']],
            [('FRESH_WATER',200,'TM_LIGHT_SCREEN'),('SODA_POP',300,'TM_SAFEGUARD'),('LEMONADE',400,'TM_REFLECT')])

    def test_exact_stock_and_only_approved_badge_gates(self):
        e=json.loads((ROOT/'tools/three_horizons/chapter14_content.json').read_text())['economy']
        expected=[
            ['GREAT_BALL','SUPER_POTION','REVIVE','ANTIDOTE','PARALYZE_HEAL','AWAKENING','BURN_HEAL','ICE_HEAL','SUPER_REPEL'],
            ['TM_ROAR','TM_DIG','TM_BRICK_BREAK','TM_SECRET_POWER','TM_ATTRACT','TM_HYPER_BEAM','TM_PROTECT','TM_REST'],
            ['POKE_DOLL','RETRO_MAIL','FIRE_STONE','THUNDER_STONE','WATER_STONE','LEAF_STONE'],
            ['X_ATTACK','X_DEFENSE','X_SPEED','X_SP_ATK','X_ACCURACY','GUARD_SPEC','DIRE_HIT'],
            ['HP_UP','PROTEIN','IRON','CALCIUM','ZINC','CARBOS']]
        self.assertEqual([[r['item'] for r in s['stock']] for s in e['shops']],expected)
        for index,shop in enumerate(e['shops']):
            self.assertEqual(shop['id'],index)
            self.assertEqual([r['minBadges'] for r in shop['stock']], [3]*5+[4]*3 if index==1 else [0]*len(shop['stock']))
            self.assertTrue(all(r['requiredFlag']==0 for r in shop['stock']))

    def test_every_economy_handler_is_bound_and_no_longer_pending(self):
        content=json.loads((ROOT/'tools/three_horizons/chapter14_content.json').read_text())
        self.assertFalse(any(r['ownerTask']==10 for r in content['unfinishedInteractions']))
        script=(ROOT/'data/scripts/three_horizons/chapter14_celadon.inc').read_text()
        for name in ('TH14_CeladonCity_GameCorner','TH14_CeladonCity_GameCorner_PrizeRoom',
                     'TH14_CeladonCity_DepartmentStore_Roof','TH14_CeladonCity_Restaurant'):
            for event in map_data(name)['object_events']+map_data(name)['bg_events']:
                label=event.get('script','')
                if label and 'Rocket' not in label and 'Poster' not in label:
                    body=re.search(r'^'+re.escape(label)+r'::\n(.*?)(?=^\w+::|\Z)',script,re.M|re.S)
                    self.assertIsNotNone(body,label)
                    self.assertNotIn('Please wait a moment',body[0])
        self.assertIn('playslotmachine VAR_RESULT',script)
        self.assertIn('special TH14_ScriptOpenShop',script)
        self.assertIn('special TH14_ScriptEconomy',script)

    def test_all_coin_pickups_have_distinct_authorized_receipts(self):
        e=json.loads((ROOT/'tools/three_horizons/chapter14_content.json').read_text())['economy']
        self.assertEqual([r['coins'] for r in e['coinGifts']],[10,20,20,10,10,20,10,10,20,10,10,10,40,100,10])
        flags=[r['flag'] for r in e['coinGifts']]
        self.assertEqual(len(set(flags)),15)
        self.assertEqual(flags[3:],[f'FLAG_TH14_PICKUP_{i}' for i in range(13,25)])
