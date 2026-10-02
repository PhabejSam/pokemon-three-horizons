"""Install this runner's Windows DLLs from a verified local MSYS2 installation.

No downloads, machine PATH changes, ROM writes, or save writes. Validate both
package manifests and PE architectures before copying either dependency.
"""
import argparse
import gzip
import hashlib
import json
from pathlib import Path
import shlex
import shutil
import struct

ROOT = Path(__file__).resolve().parents[2]
DEPENDENCIES = ('libwinpthread-1.dll', 'libepoxy-0.dll')


def sha256(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def pe_machine(path):
    data = path.read_bytes()
    if data[:2] != b'MZ':
        raise ValueError(f'Not a Windows executable: {path}')
    offset = struct.unpack_from('<I', data, 0x3c)[0]
    if data[offset:offset+4] != b'PE\0\0':
        raise ValueError(f'Invalid PE header: {path}')
    return struct.unpack_from('<H', data, offset+4)[0]


def verified_dependency(msys2, name, machine):
    relative = 'mingw64/bin/' + name
    source = msys2 / relative
    digest = sha256(source)
    if pe_machine(source) != machine:
        raise ValueError(f'Architecture mismatch: {source}')
    for package in (msys2/'var/lib/pacman/local').glob('mingw-w64-x86_64-*'):
        files = package/'files'
        if not files.exists() or relative not in files.read_text().splitlines():
            continue
        with gzip.open(package/'mtree', 'rt', encoding='utf-8') as stream:
            for line in stream:
                fields = shlex.split(line)
                if fields and fields[0] == './' + relative:
                    metadata = dict(field.split('=', 1) for field in fields[1:] if '=' in field)
                    if metadata.get('sha256digest') != digest:
                        raise ValueError(f'Installed DLL differs from package manifest: {source}')
                    desc = (package/'desc').read_text()
                    validation = desc.split('%VALIDATION%\n', 1)[1].split('\n\n', 1)[0].splitlines()
                    if not {'sha256', 'pgp'} <= set(validation):
                        raise ValueError(f'Package lacks checksum/signature validation record: {package.name}')
                    return source, {'name': name, 'package': package.name, 'sha256': digest,
                                    'manifest': str(package/'mtree'), 'validation': validation}
        raise ValueError(f'DLL absent from package checksum manifest: {package.name}')
    raise ValueError(f'No installed MSYS2 package owns {source}')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--msys2-root', type=Path, required=True)
    parser.add_argument('--runner', type=Path, default=ROOT/'tools/mgba/mgba-rom-test.exe')
    parser.add_argument('--check', action='store_true', help='Validate without copying')
    args = parser.parse_args()
    runner = args.runner.resolve(strict=True)
    machine = pe_machine(runner)
    if machine != 0x8664:
        raise ValueError('This setup supports the project\'s x86-64 Windows runner only')
    dependencies = [verified_dependency(args.msys2_root.resolve(strict=True), name, machine)
                    for name in DEPENDENCIES]
    for source, record in dependencies:
        target = runner.parent/source.name
        if target.exists() and sha256(target) != record['sha256']:
            raise ValueError(f'Refusing to overwrite a different existing DLL: {target}')
    before = sha256(runner)
    for source, record in dependencies:
        target = runner.parent/source.name
        if not args.check and not target.exists():
            shutil.copyfile(source, target)
        record['destination'] = str(target)
        record['installed'] = target.exists() and sha256(target) == record['sha256']
    assert sha256(runner) == before, 'Runner unexpectedly changed'
    print(json.dumps({'runner': str(runner), 'runner_sha256': before,
                      'check_only': args.check, 'dependencies': [r for _, r in dependencies]}, indent=2))


if __name__ == '__main__':
    main()
