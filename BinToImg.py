import numpy as np
from matplotlib import pylab as plt

A = np.fromfile("sequence.bin", dtype = 'int16', sep="")
print("loaded");
B = np.zeros((120,120,2500))
print("reshaped")
length = 2500
for t in range(length):
    if t % 100 == 0:
        print(t, " ms done");
    for i in range(120):
        for j in range(120):
            B[i,j,t] = A[j+i*120+t*14400]
plt.imshow(B[:,:,900])
plt.show()
signal = np.zeros((length))
signal = B[66, 43, :]
uniques = []
for pixel in B[:,:,530].flatten():
    if pixel not in uniques:
        uniques.append(pixel)
print(len(uniques))
plt.hist(B[:,:,530].flatten())
plt.show()
unique_frames = length
for i in range(length-1):
    if False not in (B[:,:,i] == B[:,:,i+1]):
        unique_frames -= 1
print("unique frames: ", unique_frames)
plt.plot(signal)
plt.show()
