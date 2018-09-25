
import sys, math, struct, os
from PIL import Image

colors = []

def color_distance(a, b):
	return math.sqrt((a[0]-b[0])**2 + (a[1]-b[1])**2 + (a[2]-b[2])**2)
	
def nearest_color(color):
	nearest = 0
	
	for i in range(len(colors)):
		if color_distance(color, colors[i]) < color_distance(color, colors[nearest]):
			nearest = i
	
	return nearest

img = Image.open(sys.argv[1]).convert("RGB")
w, h = img.size

# Generate the color table
for y in xrange(h):
	for x in xrange(w):
		color = img.getpixel((x, y))
		
		f = False
		for c in colors:
			if color == c[0]:
				c[1] += 1
				f = True
				
		if not f:
			colors.append([color, 1])
			
colors = [c[0] for c in sorted(colors, key=lambda x: x[1], reverse=True)[:255]]
print colors

buf = chr(len(colors)) + "".join([chr(c[0]/4) + chr(c[1]/4) + chr(c[2]/4) for c in colors])

for y in xrange(h):
	for x in xrange(w):
		color = img.getpixel((x, y))
		buf += chr(nearest_color(color))
	

with open(sys.argv[2], "wb") as out:
	out.write(buf)
