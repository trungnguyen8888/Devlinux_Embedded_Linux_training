#!/usr/bin/env python3
# scripts/tree2png_solid.py
import sys, os
from PIL import Image, ImageDraw, ImageFont

SRC = sys.argv[1] if len(sys.argv) > 1 else "tree.txt"
DST = sys.argv[2] if len(sys.argv) > 2 else "doc/images/Tree.png"

FONT_PATH = "/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf"
PT = 22            # font size
MARGIN = 24        # outer margin
OVERLAP = 2        # pixel overlap between lines (try 1–3)

with open(SRC, "r", encoding="utf-8") as f:
    lines = f.read().rstrip("\n").splitlines()

font = ImageFont.truetype(FONT_PATH, PT)

def line_size(s: str):
    tmp = Image.new("RGB", (1,1))
    d = ImageDraw.Draw(tmp)
    l, t, r, b = d.textbbox((0,0), s if s else " ", font=font)
    return (r - l), (b - t)

# measure
widths, heights = zip(*(line_size(x) for x in lines))
line_h = max(heights)
W = max(widths) + MARGIN * 2
H = (line_h * len(lines) - OVERLAP * (len(lines) - 1)) + MARGIN*2

# draw with vertical overlap so │ lines touch
img = Image.new("RGB", (W, H), "white")
draw = ImageDraw.Draw(img)
y = MARGIN
for ln in lines:
    draw.text((MARGIN, y), ln, fill="black", font=font)
    y += line_h - OVERLAP

os.makedirs(os.path.dirname(DST), exist_ok=True)
img.save(DST)
print(f"Wrote {DST}  size={W}x{H}  line_h={line_h}  overlap={OVERLAP}")