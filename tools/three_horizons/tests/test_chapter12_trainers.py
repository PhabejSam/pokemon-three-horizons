import re,unittest
from pathlib import Path
ROOT=Path(__file__).resolve().parents[3]
class TrainerAllocation(unittest.TestCase):
    def test_chapter_slots_do_not_override_native_trainers_in_same_build(self):
        h=(ROOT/'include/constants/opponents.h').read_text()
        ids={n:int(v) for n,v in re.findall(r'^#define (TRAINER_\w+)\s+(\d+)\s*$',h,re.M)}
        new={ids[n] for n in ids if n.startswith('TRAINER_TH12_')}
        stack=[]
        for line in (ROOT/'src/data/trainers.party').read_text().splitlines():
            if line.startswith('#if'):stack.append(line.strip())
            elif line.startswith('#endif'):stack.pop()
            elif line.startswith('=== TRAINER_'):
                name=line.split()[1]
                if ids.get(name) in new and not name.startswith('TRAINER_TH'):
                    self.assertIn('#if !THREE_HORIZONS',stack,name)

    def test_rocket_duo_uses_half_parties_for_three_slot_groups(self):
        source=(ROOT/'src/data/trainers.party').read_text()
        for name in ('JESSIE','JAMES'):
            block=source.split('=== TRAINER_TH11_'+name+' ===',1)[1].split('===',1)[0]
            self.assertIn('Multi Party: Half',block,name)
