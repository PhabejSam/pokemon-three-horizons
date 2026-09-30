"""Convert monicaccina's approved sheet to native GBA tiles (requires Pillow).

Only layout/palette conversion is performed; no generated replacement art.
Run from any directory. Provenance is in graphics/three_horizons/rocket/README.md.
"""
from pathlib import Path
from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
ASSETS = ROOT / 'graphics/three_horizons/rocket'


def indexed(image):
    # Train a 15-color palette on visible pixels only, reserving index 0 for
    # transparency. No dithering: source pixels retain crisp boundaries.
    visible = [p[:3] for p in image.getdata() if p[3]]
    strip = Image.new('RGB', (len(visible), 1))
    strip.putdata(visible)
    quantized = strip.quantize(colors=15, method=Image.Quantize.MEDIANCUT)
    palette = quantized.getpalette()[:45]
    result = image.convert('RGB').quantize(palette=quantized, dither=Image.Dither.NONE)
    result.putdata([v + 1 if p[3] else 0 for v, p in zip(result.getdata(), image.getdata())])
    result.putpalette([0, 0, 0] + palette)
    result.info['transparency'] = 0
    return result


def main():
    original = Image.open(ASSETS / 'monicaccina-original.png').convert('RGBA')
    assert original.size == (155, 66)
    # Source rows: south, north, west. Columns: idle, first step, second step.
    # Standard engine order: S/N/W idle, S steps, N steps, W steps.
    order = [(0, 0), (1, 0), (2, 0), (0, 1), (0, 2), (1, 1), (1, 2), (2, 1), (2, 2)]
    for name, source_x, portrait_box in [('james', 0, (96, 0, 124, 56)), ('jessie', 48, (124, 0, 155, 56))]:
        dest = ASSETS / name
        dest.mkdir(parents=True, exist_ok=True)
        walking = Image.new('RGBA', (144, 32))
        for i, (row, col) in enumerate(order):
            frame = original.crop((source_x + col * 16, row * 22, source_x + col * 16 + 16, row * 22 + 22))
            # Match the standard NPC foot baseline while retaining the source's
            # one-pixel bobbing and offsets between each walking frame.
            walking.paste(frame, (16 * i, 7))
        front = Image.new('RGBA', (64, 64))
        portrait = original.crop(portrait_box)
        front.paste(portrait, ((64 - portrait.width) // 2, 64 - portrait.height))
        indexed(walking).save(dest / 'walking.png', bits=4)
        indexed(front).save(dest / 'front.png', bits=4)
        print(name, '9 walking frames and battle portrait converted')


if __name__ == '__main__':
    main()
