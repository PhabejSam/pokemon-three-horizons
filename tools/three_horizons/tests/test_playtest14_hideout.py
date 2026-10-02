"""Hideout progression, donor geometry and failure-safe pickup contracts."""
import json
import re
import unittest
from tools.three_horizons.tests.test_playtest11_maps import ROOT, map_data, tiles
from tools.three_horizons.tests.test_playtest14_travel import party

ROWS = json.loads((ROOT/'tools/three_horizons/chapter14_maps.json').read_text())[28:33]
CONTENT = json.loads((ROOT/'tools/three_horizons/chapter14_content.json').read_text())


def chapter():
    path = ROOT/'data/scripts/three_horizons/chapter14_hideout.inc'
    return path.read_text() if path.exists() else ''


def run_pickup(full):
    """Interpret actual pickup control flow, mocking only the Bag/UI boundary.

    On the pre-port baseline this executes the donor's unsafe ordering so that
    a full Bag demonstrates the lost-object/unearned-unlock defect directly.
    """
    text = chapter()
    label = 'TH14_RocketHideout_B4F_EventScript_LiftKey'
    if not text:
        text = (ROOT/'data/maps/RocketHideout_B4F_Frlg/scripts.inc').read_text()
        label = label[5:]
    lines=text.splitlines()
    labels={m[1]:i+1 for i,l in enumerate(lines) if (m:=re.match(r'^(\w+)::?$',l))}
    pc=labels[label]; result=0; flags=set(); removed=False; given=0
    for _ in range(100):
        l=lines[pc].strip();pc+=1
        if not l or l.startswith('@') or l.endswith(':'):continue
        op,_,args=l.partition(' ');a=[x.strip() for x in args.split(',')]
        if op=='end':return flags,removed,given
        if op=='setflag':flags.add(a[0])
        elif op=='removeobject':removed=True
        elif op=='giveitem' or (op=='special' and a[0]=='TH14_ScriptGiveUniqueItem'):
            result=0 if full else 1;given+=result
            if result and op=='special':flags.add('FLAG_TH14_LIFT_KEY')
        elif op=='goto':pc=labels[a[0]]
        elif op=='goto_if_eq':
            if result==({'FALSE':0,'TRUE':1}.get(a[1],int(a[1]) if a[1].isdigit() else a[1])):
                if a[2]=='EventScript_BagIsFull':return flags,removed,given
                pc=labels[a[2]]
        elif op=='goto_if_set':
            if a[0] in flags:pc=labels[a[1]]
        elif op=='goto_if_not_defeated':pass # keyguard has been defeated in this fixture
        elif op not in ('lock','faceplayer','setvar','msgbox','playfanfare','waitfanfare','release','releaseall'):
            raise AssertionError('unhandled pickup instruction: '+l)
    raise AssertionError('pickup did not terminate')


class PosterScene:
    """Run authored branches while substituting battle and visible UI effects."""
    def __init__(self, win=True):
        self.lines=chapter().splitlines()
        self.labels={m[1]:i+1 for i,l in enumerate(self.lines) if (m:=re.match(r'^(\w+)::?$',l))}
        self.flags=set();self.defeated=set();self.tiles={};self.removed=set()
        self.win=win;self.battles=0;self.blackout=False;self.locked=False

    def run(self,label):
        pc=self.labels[label];stack=[]
        for _ in range(200):
            line=self.lines[pc].strip();pc+=1
            if not line or line.startswith('@') or line.endswith(':'):continue
            op,_,rest=line.partition(' ');a=[x.strip() for x in rest.split(',')]
            if op=='end':return
            if op=='return':
                if not stack:return
                pc=stack.pop()
            elif op=='goto':pc=self.labels[a[0]]
            elif op=='call':stack.append(pc);pc=self.labels[a[0]]
            elif op in ('goto_if_set','goto_if_unset'):
                if (a[0] in self.flags)==(op=='goto_if_set'):pc=self.labels[a[1]]
            elif op=='goto_if_not_defeated':
                if a[0] not in self.defeated:pc=self.labels[a[1]]
            elif op in ('call_if_eq','call_if_ne'):
                # Fixture approaches from the south. Movement bodies remain
                # authored and are exercised visually at Gate B.
                if op=='call_if_ne':stack.append(pc);pc=self.labels[a[2]]
            elif op=='trainerbattle_single':
                if a[0] in self.defeated:continue
                self.battles+=1
                if not self.win:self.blackout=True;self.locked=False;return
                self.defeated.add(a[0]);pc=self.labels[a[3]]
            elif op=='setflag':self.flags.add(a[0])
            elif op=='setmetatile':self.tiles[tuple(map(int,a[:2]))]=(a[2],int(a[3]))
            elif op=='removeobject':self.removed.add(a[0])
            elif op in ('lock','lockall'):self.locked=True
            elif op in ('release','releaseall'):self.locked=False
            elif op=='special':assert a[0]=='DrawWholeMapView'
            elif op not in ('msgbox','closemessage','playse','waitse','applymovement','waitmovement'):
                raise AssertionError('unhandled poster instruction: '+line)
        raise AssertionError('poster scene did not terminate')


class Hideout(unittest.TestCase):
    def test_poster_needs_guard_win_then_switch_and_restores_stairs(self):
        guard='TH14_CeladonCity_GameCorner_EventScript_RocketGrunt'
        poster='TH14_CeladonCity_GameCorner_EventScript_Poster'
        load='TH14_HideoutPoster_OnLoad'
        s=PosterScene(win=False);s.run(load);closed=dict(s.tiles)
        s.run(poster);self.assertEqual(s.tiles,closed);self.assertFalse(s.flags)
        s.run(guard);self.assertTrue(s.blackout);self.assertFalse(s.defeated)
        s.run(load);self.assertEqual(s.tiles,closed);self.assertFalse(s.locked)
        s.win=True;s.run(guard);self.assertEqual(len(s.defeated),1)
        self.assertFalse(s.flags);self.assertTrue(s.removed)
        s.run(load);self.assertEqual(s.tiles,closed)
        s.run(poster);opened=dict(s.tiles)
        self.assertNotEqual(opened,closed)
        self.assertEqual(s.flags,{'FLAG_TH14_HIDEOUT_POSTER'})
        self.assertFalse(s.locked)
        for _ in range(3):
            s.tiles.clear();s.run(load);self.assertEqual(s.tiles,opened)
            s.run(poster);self.assertFalse(s.locked)
        self.assertEqual(s.battles,2)

    def test_full_bag_keeps_key_object_and_unlock_unearned(self):
        flags,removed,given=run_pickup(True)
        self.assertEqual((flags,removed,given),(set(),False,0))
        flags,removed,given=run_pickup(False)
        self.assertEqual((flags,removed,given),({'FLAG_TH14_LIFT_KEY'},True,1))

    def test_five_maps_keep_donor_bytes_and_reciprocal_project_warps(self):
        layouts=json.loads((ROOT/'data/layouts/layouts.json').read_text())['layouts']
        groups=json.loads((ROOT/'data/maps/map_groups.json').read_text())['gMapGroup_ThreeHorizons14']
        self.assertEqual(groups[28:33],[r['name'] for r in ROWS])
        maps={map_data(r['name'])['id']:map_data(r['name']) for r in ROWS}
        maps['MAP_TH14_CELADON_CITY_GAME_CORNER']=map_data('TH14_CeladonCity_GameCorner')
        for row in ROWS:
            m=map_data(row['name']);d=map_data(row['donor'])
            own=next(l for l in layouts if l['id']==m['layout'])
            donor=next(l for l in layouts if l['id']==d['layout'])
            for field in ('blockdata_filepath','border_filepath'):
                self.assertTrue(own[field].startswith('data/layouts/TH14_'))
                self.assertEqual((ROOT/own[field]).read_bytes(),(ROOT/donor[field]).read_bytes())
            for w in m['warp_events']:
                if w['dest_map']=='MAP_DYNAMIC':
                    self.assertTrue(m['name'].endswith('Elevator'));continue
                self.assertIn(w['dest_map'],maps)
                target=maps[w['dest_map']]['warp_events'][int(w['dest_warp_id'])]
                self.assertIn(target['dest_map'],(m['id'],'MAP_DYNAMIC'))
        entry=maps['MAP_TH14_CELADON_CITY_GAME_CORNER']['warp_events'][3]
        self.assertEqual(entry['dest_map'],'MAP_TH14_ROCKET_HIDEOUT_B1F')

    def test_trainer_first_parties_and_rematch_inclusions(self):
        records=[r for r in CONTENT['trainers'] if 177<=r['id']<=188]
        self.assertEqual(len(records),12)
        registry=(ROOT/'src/data/three_horizons_rematches.h').read_text()
        source=(ROOT/'src/data/trainers.party').read_text()
        donor=(ROOT/'src/data/trainers_frlg.party').read_text()
        for r in records:
            self.assertEqual(party(source,r['constant']),party(donor,r['donor']))
            self.assertEqual(r['constant'] in registry,r['rematch'])
            obj=map_data(r['map'])['object_events'][r['localId']-1]
            self.assertIn(r['constant'],chapter().split(obj['script']+'::')[1].split('\n\n')[0])

    def test_pickup_receipts_and_no_legacy_state_aliases(self):
        receipts=[r for r in CONTENT['receipts'] if r['writer'] in [x['name'] for x in ROWS]]
        for r in receipts:
            m=map_data(r['writer'])
            objects=m['object_events']+m['bg_events']
            found=[o for o in objects if [o['x'],o['y']]==r['coordinate'] and o.get('flag')==r['name']]
            self.assertEqual(len(found),1,r)
        for token in ('FLAG_HIDE_LIFT_KEY','FLAG_CAN_USE_ROCKET_HIDEOUT_LIFT',
                      'FLAG_HIDE_MISC_KANTO_ROCKETS','VAR_ELEVATOR_FLOOR','setworldmapflag','famechecker'):
            self.assertNotIn(token,chapter())
        self.assertIn({'item':'ITEM_LIFT_KEY','receipt':'FLAG_TH14_LIFT_KEY'},CONTENT['uniqueItems'])

    def test_exactly_three_optional_scenery_records(self):
        records=[]
        for r in ROWS:
            records.extend(b for b in map_data(r['name'])['bg_events'] if 'ResearchRecord' in b.get('script',''))
        self.assertEqual(len(records),3)
        self.assertEqual(len({b['script'] for b in records}),3)
        for b in records:
            block=chapter().split(b['script']+'::')[1].split('\n\n')[0]
            self.assertIn('MSGBOX_SIGN',block)
            self.assertNotIn('setflag',block)
        text=re.sub(r'\\[npl]',' ',''.join(re.findall(r'\.string "(.*?)"',chapter())))
        for phrase in ('A marked distribution map.','GHOST SIGHTINGS / MIGRATION REPORTS.',
                       'Do not assume a cause.'):
            self.assertIn(phrase,text)

    def test_scene_capacity_and_all_script_targets_resolve(self):
        labels=set()
        includes=(ROOT/'data/scripts/three_horizons/maps.inc').read_text()
        for p in (ROOT/'data/scripts/three_horizons').glob('*.inc'):
            labels.update(re.findall(r'^(\w+)::?',p.read_text(),re.M))
        for r in ROWS:
            m=map_data(r['name'])
            self.assertIn('"data/maps/'+r['name']+'/scripts.inc"',includes)
            # All Hideout template objects + player + follower fit, even before
            # visibility pruning; the Game Corner uses native camera culling.
            self.assertLessEqual(len(m['object_events'])+2,16)
            for e in m['object_events']+m['bg_events']:
                if 'script' in e:self.assertIn(e['script'],labels)


if __name__=='__main__':unittest.main()
