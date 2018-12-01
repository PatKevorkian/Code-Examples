#-------------------------------------------------
##Created by Patrick Kevokian 10/19/17
##Image Processing
##College of Staten Island Fall 2017

#Library Imports 
#-------------------------------------------------
import PIL
from skimage import color
from skimage import io
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import numpy as np
import math
import pandas

#Grid Functions
#-------------------------------------------------

def threeXthreeGrid(r,c,arr):   
    threeXthreeEle =  [ arr[r-1][c-1],arr[r-1][c],arr[r-1][c+1],arr[r][c-1],arr[r][c],arr[r][c+1],arr[r+1][c-1],arr[r+1][c],arr[r+1][c+1] ]
    return threeXthreeEle

def twoXtwoGrid(r,c,arr):
    twoXtwoEle = [arr[r][c],arr[r][c+1],arr[r+1][c],arr[r+1][c+1]]
    return twoXtwoEle

#Filter Functions
#-------------------------------------------------

def Lap(arr,img):
    lapMask = [0,-1,0,-1,4,-1,0,-1,0]
    maskMult = [a*b for a,b in zip(arr,lapMask)]
    sumLap = sum(maskMult)
    return sumLap

#-------------------------------------------------

def medianSmooth(arr):
    sortedAry = sorted(arr)
    medianEle = math.floor((len(arr)/2)+1)-1
    return sortedAry[medianEle]

#-------------------------------------------------

def maxFilter(arr):
    sortedAry = sorted(arr)
    maxEle = len(arr)-1
    return sortedAry[maxEle]

#-------------------------------------------------

def minFilter(arr):
    sortedAry = sorted(arr)
    return sortedAry[0]

#-------------------------------------------------

def robinson(arr,img):
    rob1 = [1,0,0,-1]
    rob1Mult = [a*b for a,b in zip(arr,rob1)]
    sumRob1 = sum(rob1Mult)
    
    rob2 = [0,1,-1,0]
    rob2Mult = [a*b for a,b in zip(arr, rob2)]
    sumRob2 = sum(rob2Mult)
    
    return abs(sumRob1) + abs(sumRob2)

#-------------------------------------------------

def SobelFilter(arr,img):
    sobel1 = [1,0,-1,2,0,-2,1,0,-1]
    sobel1Mult = [a*b for a,b in zip(arr,sobel1)]
    sumSobel1 = sum(sobel1Mult)

    sobel2 = [1,2,1,0,0,0,-1,-2,-1]
    sobel2Mult = [a*b for a,b in zip(arr,sobel2)]
    sumSobel2 = sum(sobel2Mult)

    return abs(sumSobel1) + abs(sumSobel2)
#-------------------------------------------------

def HigBoostLap(arr,img, A):
    HighBoostLapMask = [0,-A,0,-A,4*A+1,-A,0,-A,0]
    lapMaskMult = [a*b for a,b in zip(arr,HighBoostLapMask)]
    sumHighBoostLap = sum(lapMaskMult)
    return sumHighBoostLap

#-------------------------------------------------
   
def prewittsFilter(arr, img):
    prewitt1 = [-1,-1,-1,0,0,0,1,1,1]
    prewitt1Mult = [a*b for a,b in zip(arr,prewitt1)]
    sumPrewitt1 = sum(prewitt1Mult)

    prewitt2 = [-1,0,1,-1,0,1,-1,0,1]
    prewitt2Mult = [a*b for a,b in zip(arr,prewitt2)]
    sumPrewitt2 = sum(prewitt2Mult)

    return abs(sumPrewitt1) + abs(sumPrewitt2)
    
    
#Read in image (using skimage to load and convert to greyscale)
#-------------------------------------------------

img = color.rgb2gray(io.imread('/Users/PatrickKevorkian/Desktop/IMG_1327.jpg'))

#Plot image and show array                                     
#-------------------------------------------------

plt.imshow(img, cmap='gray')
plt.suptitle('Original Image')
plt.show()
print('\n Original Image Array \n')
print(pandas.DataFrame(img))

#Create array of same size as image to hold new image 
#-------------------------------------------------

w, h = len(img[1,:]), len(img[:,1]);
newImage = [[0 for x in range(w)] for y in range(h)] 

#Initi loop vars
#-------------------------------------------------

A= 5 #A is used for high boost lap mask where A >= 1
c = 0
r = 1

#Begin loop: to iterate grid through image array
#This is done col wise moving over then down
#No padding used, filters dont hit very edge of array 
#-------------------------------------------------

while c <= (len(img[:,1]-2)):
    
    c+=1
    limitCol = len(img[:,1])-2
    limitRow = len(img[1,:])-2
    
#-------------------------------------------------
    #Comment and uncomment for grid size

    #gridArr = twoXtwoGrid(r,c,img)
    gridArr = threeXthreeGrid(r,c,img)

#-------------------------------------------------    
    #Comment and uncomment to use desired filter
    
    #newPixVal = maxFilter(gridArr)
    #newPixVal = medianSmooth(gridArr)
    #newPixVal = minFilter(gridArr)
    #newPixVal = Lap(gridArr,img)
    #newPixVal = robinson(gridArr,img)
    #newPixVal = SobelFilter(gridArr,img)
    #newPixVal = HigBoostLap(gridArr,img,A)
    newPixVal = prewittsFilter(gridArr,img)
#-------------------------------------------------
    
    newImage[r][c] = newPixVal
    
    if c == limitCol & r ==limitRow:
        break
    if c == limitCol :
        r+=1
        c=0

#end loop
#-------------------------------------------------

#Show new image
#-------------------------------------------------
plt.imshow(newImage, cmap='gray')
plt.suptitle('New Image')
plt.show()
print(' \n New Image Array \n ')
#pandas formats arrays nicely 
print(pandas.DataFrame(newImage))

#End prog
#-------------------------------------------------








