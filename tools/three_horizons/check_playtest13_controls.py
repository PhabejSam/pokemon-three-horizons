"""Prove three P13 regression owners in a disposable CI checkout, restoring bytes."""
from pathlib import Path
import re
import subprocess

CONTROLS = (
    ('cut', 'src/overworld.c', (
        ('    PrepareThreeHorizonsCutTemplates();', '    ; // P12: no temporary Cut receipts'),
    ), 'Three Horizons playtest13 Cut', (
        # The overlap guard independently protects the player's current tile.
        # This mutant must fail the adjacent-tile refresh owner instead.
        'Cut target remains removed while another tree is unaffected',
    )),
    ('version', 'src/three_horizons_clock.c', (
        ('TH_STATE_VERSION_13 |', 'TH_STATE_VERSION_12 |'),
    ), 'Three Horizons playtest13 state remains version13', (
        'state remains version13 after clock update',
    )),
    ('battle', 'include/config/battle.h', (
        ('B_RUN_TRAINER_BATTLE                FALSE', 'B_RUN_TRAINER_BATTLE                TRUE'),
        ('B_MOVE_REARRANGEMENT_IN_BATTLE  GEN_3', 'B_MOVE_REARRANGEMENT_IN_BATTLE  GEN_LATEST'),
    ), 'test/three_horizons_playtest13_battle.c', (
        'trainer RUN cannot whiteout', 'SELECT swaps moves and PP',
    )),
)

def run(test, log):
    with log.open('w') as stream:
        # The battle file also owns cry/presentation assertions: use the same
        # audio-enabled runner as the full integration gate, never skip them.
        result = subprocess.run(['make', 'THREE_HORIZONS=1',
                                 'pokemon-three-horizons-test.elf',
                                 'TESTS=' + test, '-j2'],
                                stdout=stream, stderr=subprocess.STDOUT)
        if result.returncode == 0:
            result = subprocess.run([
                'tools/mgba-rom-test-hydra/mgba-rom-test-hydra',
                'tools/mgba/mgba-rom-test', 'arm-none-eabi-objcopy',
                'pokemon-three-horizons-test.elf'],
                stdout=stream, stderr=subprocess.STDOUT)
    text = re.sub(r'\x1b\[[0-9;]*m', '', log.read_text())
    assert 'No tests found' not in text, log
    return result.returncode, text

def main():
    for name, filename, replacements, test, failures in CONTROLS:
        path = Path(filename)
        original = path.read_bytes()
        changed = original.decode()
        for old, new in replacements:
            assert changed.count(old) == 1, (name, old)
            changed = changed.replace(old, new)
        try:
            path.write_text(changed)
            code, text = run(test, Path(f'playtest13-{name}-negative.log'))
            assert code != 0 and 'error:' not in text, (name, 'not an assertion failure')
            for failure in failures:
                assert re.search(re.escape(failure) + r'.*FAIL', text), (name, failure)
            print(name + ': owning regression detected old behavior', flush=True)
        finally:
            path.write_bytes(original)
            assert path.read_bytes() == original
        code, text = run(test, Path(f'playtest13-{name}-restored.log'))
        assert code == 0 and 'PASS' in text, (name, 'restored source failed')
        print(name + ': restored source passes', flush=True)

if __name__ == '__main__':
    main()
