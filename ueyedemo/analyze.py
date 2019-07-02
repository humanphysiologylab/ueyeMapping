from PIL import Image
import numpy as np

im = Image.open('12bit.png') # Can be many different formats.
pix = im.load()
data = np.array(pix)
print(im.size)
print(data)
uniques = []
for i in range(im.size[0]):
    print(str(i)+" row done\n")
    for j in range(im.size[1]):
        #print(pix[i, j]/64)
        if pix[i, j] not in uniques:
            uniques.append(pix[i, j])

print(len(uniques))

#pix[x,y] = value  # Set the RGBA Value of the image (tuple)
#im.save('alive_parrot.png')  # Save the modified pixels as .png
