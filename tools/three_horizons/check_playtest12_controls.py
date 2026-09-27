"""Run native regression negative controls in a disposable CI checkout."""
from pathlib import Path
import subprocess

CONTROLS=[
 ('dex','src/reshow_battle_screen.c','THREE_HORIZONS && gBattleScripting.monCaught','FALSE','Three Horizons new catch'),
 ('rocket','src/three_horizons_chapter12.c','&& FlagGet(TRAINER_FLAGS_START + TRAINER_TH11_JAMES)','|| FlagGet(TRAINER_FLAGS_START + TRAINER_TH11_JAMES)','Three Horizons playtest12 Rocket retry'),
 ('cut','src/three_horizons_field_moves.c','return move == FIELD_MOVE_CUT &&','return FALSE &&','Three Horizons playtest12 Cut needs'),
 ('surge','src/three_horizons_chapter12.c','return (ax == bx &&','return (first == second &&','Three Horizons playtest12 Surge switches'),
 ('teams','src/battle_interface.c','bool32 splitOpponentRow = THREE_HORIZONS &&','bool32 splitOpponentRow = FALSE &&','Three Horizons playtest12 opponents show'),
]
def main():
    for name,filename,old,new,test in CONTROLS:
        p=Path(filename);original=p.read_bytes();s=original.decode()
        assert old in s,(name,'control anchor missing')
        log=Path(f'playtest12-{name}-negative.log')
        try:
            p.write_text(s.replace(old,new))
            with log.open('w') as f:
                result=subprocess.run(['make','THREE_HORIZONS=1','check','TESTS='+test,'-j2'],stdout=f,stderr=subprocess.STDOUT)
            text=log.read_text()
            assert result.returncode!=0 and 'FAIL' in text and 'error:' not in text,(name,'expected a failing assertion, not a compiler failure')
            print(name+': negative control detected',flush=True)
        finally:
            p.write_bytes(original)
    subprocess.run(['make','THREE_HORIZONS=1','check','TESTS=Three Horizons playtest12','-j2'],check=True)

if __name__=='__main__':main()
