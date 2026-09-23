"""Validate the shipped ARM ELF using the sprite engine's frame addressing rules."""
import struct
import sys
from pathlib import Path


def check(path):
    data = Path(path).read_bytes()
    assert data[:5] == b'\x7fELF\x01'
    offset = struct.unpack_from('<I', data, 32)[0]
    size, count = struct.unpack_from('<HH', data, 46)
    sections = [struct.unpack_from('<10I', data, offset + i * size) for i in range(count)]
    symbols = {}
    for section in sections:
        if section[1] != 2:
            continue
        strings = sections[section[6]]
        names = data[strings[4]:strings[4] + strings[5]]
        for entry in range(section[4], section[4] + section[5], section[9]):
            n, address, length = struct.unpack_from('<III', data, entry)
            symbols[names[n:names.find(b'\0', n)].decode()] = (address, length)

    def read(address, length):
        for section in sections:
            if section[1] != 8 and section[3] <= address and address + length <= section[3] + section[5]:
                start = section[4] + address - section[3]
                return data[start:start + length]
        raise AssertionError(f'Unmapped sprite address {address:#x}')

    hoenn = ((12, 9, 13, 9), (14, 10, 15, 10), (16, 11, 17, 11), (16, 11, 17, 11))
    kanto = ((9, 10, 9, 11), (12, 13, 12, 14), (15, 16, 15, 17), (15, 16, 15, 17))
    failures = []
    for outfit in ('Brendan', 'May', 'Red', 'Green', 'THGold', 'THKris', 'THSilver'):
        info = read(symbols['gObjectEventGraphicsInfo_' + outfit + 'Normal'][0], 36)
        animations, images = struct.unpack_from('<II', info, 24)
        base, frame_size, relative = struct.unpack('<IHBx', read(images, 8))
        expected = kanto if outfit in ('Red', 'Green') else hoenn
        for direction, sequence in enumerate(expected):
            animation = struct.unpack('<I', read(animations + (20 + direction) * 4, 4))[0]
            commands = struct.unpack('<4I', read(animation, 16))
            actual = tuple(command & 0xffff for command in commands)
            if actual != sequence:
                failures.append(f'{outfit} direction {direction}: wrong running order {actual}, expected {sequence}')
            for command in commands:
                frame = command & 0xffff
                assert ((command >> 22) & 1) == (direction == 3), outfit
                if relative:
                    pointer, length = base + frame_size * frame, frame_size
                else:
                    pointer, length = struct.unpack('<IH', read(images + frame * 8, 6))
                if outfit.startswith('TH'):
                    asset = 'gObjectEventPic_' + outfit + 'Running'
                    index = frame - 9
                elif outfit in ('Red', 'Green'):
                    asset = 'gObjectEventPic_' + outfit + 'SurfRun'
                    index = frame - 6
                else:
                    asset = 'gObjectEventPic_' + outfit + 'NormalRunning'
                    index = frame
                start, asset_size = symbols[asset]
                if length != 256 or pointer != start + index * 256 or not start <= pointer < pointer + length <= start + asset_size:
                    failures.append(f'{outfit} frame {frame}: image read escapes or mismatches {asset}')
        print(f'Checked {outfit}: four directions, sixteen running frame reads')
    assert not failures, '\n' + '\n'.join(dict.fromkeys(failures))
    print('PASS: all 112 running frame reads use the correct asset and direction')


if __name__ == '__main__':
    check(sys.argv[1])
