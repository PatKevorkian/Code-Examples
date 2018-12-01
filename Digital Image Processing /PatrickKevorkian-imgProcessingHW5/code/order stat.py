import numpy as np
import scipy
import scipy.misc
import matplotlib.pyplot as plt
from skimage import color
from skimage import io
from scipy import ndimage
from scipy.ndimage.filters import median_filter

I = color.rgb2gray(io.imread("/Users/PatrickKevorkian/Desktop/me.jpg"))

k=1

data = np.partition(np.asarray(I), k)[k]
print(data)


import collections
a = data
counter=collections.Counter(a)
print(counter)




labels, values = zip(*counter.items())

indexes = np.arange(len(labels))
width = 1

plt.bar(indexes, values, width)
plt.xticks(indexes + width * 0.5, labels)
plt.show()




