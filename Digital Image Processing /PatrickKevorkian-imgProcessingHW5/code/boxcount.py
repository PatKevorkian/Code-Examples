import numpy as np
import scipy
import scipy.misc
import matplotlib.pyplot as plt
from skimage import color
from skimage import io
from scipy import ndimage
from scipy.ndimage.filters import median_filter


def fractal_dimension(Z, threshold = 0.6):
    # Only for 2d image
    assert(len(Z.shape) == 2)

   
    def boxcount(Z, k):
        S = np.add.reduceat(
            np.add.reduceat(Z, np.arange(0, Z.shape[0], k), axis=0),
                               np.arange(0, Z.shape[1], k), axis=1)

        # We count non-empty (0) and non-full boxes (k*k)
        return len(np.where((S > 0) & (S < k*k))[0])

    #threshold
    Z = (Z < threshold) 
##    
##    # Edge detection
##
##    edge_horizont = ndimage.sobel(Z, 0)
##    edge_vertical = ndimage.sobel(Z, 1)
##    Z = np.hypot(edge_horizont, edge_vertical)

    #median filter
    
    Z = median_filter(Z,16)
    
    #show image

    plt.imshow(Z, cmap='gray')
    plt.show()

    # Minimal dimension of image
    p = min(Z.shape)

    # Greatest power of 2 less than or equal to p
    n = 2**np.floor(np.log(p)/np.log(2))

    # Extract the exponent
    n = int(np.log(n)/np.log(2))

    # Build successive box sizes (from 2**n down to 2**1)
    sizes = 2**np.arange(n, 1, -1)

    # Actual box counting with decreasing size
    counts = []
    for size in sizes:
        counts.append(boxcount(Z, size))

    # Fit the successive log(sizes) with log (counts)
    coeffs = np.polyfit(np.log(sizes), np.log(counts), 1)
    return -coeffs[0]

I = color.rgb2gray(io.imread("/Users/PatrickKevorkian/Desktop/si2.jpg"))


print("Minkowski–Bouligand dimension (computed): ", fractal_dimension(I))










