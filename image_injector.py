#!/usr/bin/env python3
"""image_injector.py <repo> [--check] - write the translated images from translation/images into assets/jp.

Run after `make extract` (extract wipes assets/jp), via `make inject`, before `make`.

For every entry in translation/images/manifest.json with "inject": true it
  1. reads the PNG (the editable source of truth),
  2. converts it to N64 texture bytes (and the 16-colour palette for CI4),
  3. writes those bytes into the extracted segment .bin at the recorded offset.
Nothing changes size, so no segment moves.

Safety: before writing, the bytes currently in the .bin must be either the retail bytes
(hash recorded in the manifest) or already the translated bytes (re-running is harmless);
anything else means the offsets or baserom are wrong and the script stops.
--check only reports what it would do.
"""
import hashlib, json, struct, sys
from pathlib import Path
import numpy as np
from PIL import Image

IMGDIR = 'translated_images'

def sha(b): return hashlib.sha256(b).hexdigest()

def pack_nibbles(n):
    n = n.astype(np.uint8).flatten()
    if len(n) % 2: n = np.append(n, 0)
    return bytes((n[0::2] << 4 | n[1::2]).astype(np.uint8))

def png_to_n64(path, fmt):
    """Returns (image bytes, palette bytes or None). Inverse of how the PNGs were written."""
    im = Image.open(path)
    if fmt == 'i4':
        if im.mode != 'L': sys.exit(f'{path}: expected 8-bit greyscale PNG, got {im.mode}')
        return pack_nibbles(np.array(im) // 17), None
    if fmt == 'ia8':
        if im.mode != 'LA': sys.exit(f'{path}: expected grey+alpha PNG, got {im.mode}')
        a = np.array(im)
        return ((a[..., 0] // 17) << 4 | (a[..., 1] // 17)).astype(np.uint8).tobytes(), None
    if fmt == 'ia4':
        if im.mode != 'LA': sys.exit(f'{path}: expected grey+alpha PNG, got {im.mode}')
        a = np.array(im)
        i3 = np.rint(a[..., 0].astype(float) * 7 / 255).astype(np.uint8)
        return pack_nibbles(i3 << 1 | (a[..., 1] > 127)), None
    if fmt == 'ci4':
        if im.mode != 'P': sys.exit(f'{path}: expected paletted PNG, got {im.mode}')
        pal = im.getpalette(); t = im.info.get('transparency'); al = [255] * 16
        if isinstance(t, int): al[t] = 0
        elif t is not None: al = list(t)
        out = bytearray()
        for k in range(16):
            r, g, b = pal[k * 3:k * 3 + 3]
            v = (round(r * 31 / 255) << 11) | (round(g * 31 / 255) << 6) | (round(b * 31 / 255) << 1) | (1 if al[k] > 127 else 0)
            out += v.to_bytes(2, 'big')
        return pack_nibbles(np.array(im)), bytes(out)
    sys.exit(f'unsupported format {fmt}')

def main():
    args = [a for a in sys.argv[1:] if not a.startswith('--')]
    check = '--check' in sys.argv
    if len(args) != 1: sys.exit('usage: python3 image_injector.py <repo> [--check]')
    repo = Path(args[0]).expanduser().resolve()
    imgdir = repo / IMGDIR
    manifest = json.loads((imgdir / 'manifest.json').read_text())
    files, dirty = {}, set()
    done = skipped = 0
    for e in manifest['images']:
        if not e.get('inject'): skipped += 1; continue
        target = repo / e['target']
        if not target.exists(): sys.exit(f'error: {target} not found - run `make extract` first')
        buf = files.setdefault(target, bytearray(target.read_bytes()))
        data, pal = png_to_n64(imgdir / e['png'], e['format'])
        if len(data) != e['length']: sys.exit(f"error: {e['png']} converts to {len(data)} bytes, expected {e['length']}")
        spans = [(e['offset'], data, e.get('retail_sha256'))]
        if pal is not None: spans.append((e['palette_offset'], pal, e.get('retail_palette_sha256')))
        for off, new, retail in spans:
            cur = bytes(buf[off:off + len(new)])
            if len(cur) != len(new): sys.exit(f'error: {target.name} too small for {e["png"]}')
            if cur != new and retail and sha(cur) != retail:
                sys.exit(f'error: {target.name} @ {off:#x} is neither retail nor translated data ({e["png"]}); wrong baserom or offset?')
            if cur != new: buf[off:off + len(new)] = new; dirty.add(target)
        done += 1
    if not check:
        for t in dirty: t.write_bytes(files[t])
    print(f"[images] {done} images {'checked' if check else 'injected'} into {len(dirty)} file(s); {skipped} skipped (see manifest)")

if __name__ == '__main__':
    main()
