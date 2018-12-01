

#Library Imports 
#-------------------------------------------------

from skimage import color
from skimage import io
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import numpy as np
import scipy.ndimage


#-------------------------------------------------  
#Gaussian/Lap Pyramid function
#-------------------------------------------------
def gaussPyr(arr,numLayers,offset):
    if numLayers == 0:
        return 1
    arr = np.array(arr)
    arrBlur = scipy.ndimage.filters.gaussian_filter(arr,1)

    lap = arr - arrBlur
    plt.imshow(lap, cmap='gray')
    #plt.suptitle('Lap: ' + str(-numLayers))
    fig = plt.gcf()
    DPI = fig.get_dpi()
    fig.set_size_inches((float(len(lap[1,:]))*offset)/float(DPI),(float(len(lap[:,1]))/float(DPI))*offset)
    plt.show()
    
    newLayer = np.delete(arr, list(range(0, arrBlur.shape[0], 2)), axis=0)
    newLayer = np.delete(newLayer, list(range(0, newLayer.shape[1], 2)), axis=1)
    plt.imshow(newLayer, cmap='gray')
    #plt.suptitle('New Image: ' + str(-numLayers))
    fig = plt.gcf()
    DPI = fig.get_dpi()
    fig.set_size_inches((float(len(newLayer[1,:]))*offset)/float(DPI),(float(len(newLayer[:,1]))/float(DPI))*offset)
    plt.show()
    
    return gaussPyr(newLayer,numLayers-1,offset)
    
#-------------------------------------------------   
#Read in image (using skimage to load and convert to greyscale)
#-------------------------------------------------

img = color.rgb2gray(io.imread('/Users/PatrickKevorkian/Desktop/me.jpg'))

#Plot image                                      
#-------------------------------------------------

#The offset just changes the size of the image visualy not pixel wise 
offset = 1 
plt.imshow(img, cmap='gray')
plt.suptitle('Original Image')
fig = plt.gcf()
DPI = fig.get_dpi()
fig.set_size_inches((float(len(img[1,:]))*offset)/float(DPI),(float(len(img[:,1]))/float(DPI))*offset)
plt.show()

#-------------------------------------------------
# Run funbctions


gaussPyr(img,5,offset)





                        



#End prog
#-------------------------------------------------








