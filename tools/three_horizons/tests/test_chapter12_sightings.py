import json
import struct
import unittest
from collections import deque
from pathlib import Path
ROOT=Path(__file__).resolve().parents[3]
def read(p): return json.loads((ROOT/p).read_text())
def mapdata(name):
    m=read(f'data/maps/{name}/map.json')
    l=next(l for l in read('data/layouts/layouts.json')['layouts'] if l['id']==m['layout'])
    w,h=l['width'],l['height']
    return m,w,h,struct.unpack('<'+'H'*(w*h),(ROOT/l['blockdata_filepath']).read_bytes())
class Sightings(unittest.TestCase):
    def test_forest_has_separate_clearings_and_kanto_interactions(self):
        m,_,_,_=mapdata('TH_ViridianForest')
        actors={o['local_id']:o for o in m['object_events']}
        a=actors['LOCALID_TH12_SIGHT_TREECKO']; b=actors['LOCALID_TH12_SIGHT_SHROOMISH']
        self.assertGreaterEqual(abs(a['x']-b['x'])+abs(a['y']-b['y']),12)
        text=(ROOT/'data/scripts/three_horizons/chapter12_sightings.inc').read_text()
        for visitor,local in [('Treecko','WEEDLE'),('Shroomish','CATERPIE')]:
            body=text.split('TH12_Forest_'+visitor+'::')[1].split('    end',1)[0]
            self.assertIn('applymovement LOCALID_TH12_SIGHT_'+local,body)
            self.assertIn('playmoncry SPECIES_'+local,body)
        self.assertTrue(any(o['script']=='TH12_Forest_Aide' for o in m['object_events']))

    def test_sighting_positions_and_paths(self):
        forest,fw,fh,fd=mapdata('TH_ViridianForest')
        moon,w,h,data=mapdata('TH_MtMoonB2F')
        for m,ww,hh,d,count in [(forest,fw,fh,fd,4),(moon,w,h,data,4)]:
            new=[o for o in m['object_events'] if o['local_id'].startswith('LOCALID_TH12_SIGHT_')]
            self.assertEqual(len(new),count)
            self.assertEqual(len({(o['x'],o['y']) for o in m['object_events']}),len(m['object_events']))
            for o in new:self.assertEqual(d[o['y']*ww+o['x']]&0xC00,0)
            # Conservative 23x19 tile viewport plus player and follower.
            for y in range(hh):
                for x in range(ww):
                    nearby=sum(abs(o['x']-x)<=11 and abs(o['y']-y)<=9 for o in m['object_events'])
                    self.assertLessEqual(nearby+2,16,(m['name'],x,y))
        blocked={(o['x'],o['y']) for o in moon['object_events']}
        ring=[(24,29),(25,29),(26,29),(26,30),(26,31),(25,31),(24,31),(24,30)]
        for x,y in ring:self.assertEqual(data[y*w+x]&0xC00,0)
        # This is the screenshot chamber: warp2, Rocket18,27, item30,26.
        self.assertEqual((moon['warp_events'][2]['x'],moon['warp_events'][2]['y']),(17,31))
        pending=deque([(17,31)]);seen=set()
        while pending:
            x,y=pending.popleft()
            if (x,y) in seen:continue
            seen.add((x,y))
            for a,b in [(x+1,y),(x-1,y),(x,y+1),(x,y-1)]:
                if 0<=a<w and 0<=b<h and not data[b*w+a]&0xC00 and (a,b) not in blocked:pending.append((a,b))
        for target in [(18,28),(30,27),(32,30)]:self.assertIn(target,seen)
