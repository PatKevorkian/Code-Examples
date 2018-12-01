import matplotlib.pyplot as plt
import numpy as np
import random
import math



def gradientDescent(x, y, theta, alpha, m, numIterations):
    xTrans = x.transpose()
    prevCost = 0
    for i in range(0, numIterations):
        hypothesis = np.dot(x, theta)
        loss = hypothesis - y
        # avg cost per example
        cost = np.sum(loss ** 2) / (2 * m)
        print("Iteration %d | Cost: %f" % (i, cost))
        # avg gradient per example
        gradient = np.dot(xTrans, loss) / m
        # update theta
        theta = theta - alpha * gradient
        #break when tolerance is met (5 decimal places must be the same)
        if prevCost-cost == 0.000001:
            break
        prevCost = cost
return theta


def genData(numPoints):
    x = np.zeros(shape=(numPoints, 3))
    y = np.zeros(shape=numPoints)

    x[0][0] = 1.0
    x[1][0] = 1.0
    x[2][0] = 1.0
    x[3][0] = 1.0
    x[4][0] = 1.0
    x[5][0] = 1.0


    x[0][1] = 1
    x[1][1] = 2.5
    x[2][1] = 4.5
    x[3][1] = 6.5
    x[4][1] = 8
    x[5][1] = 12

    x[0][2] = 1
    x[1][2] = 6.5
    x[2][2] = 20.25
    x[3][2] = 42.25
    x[4][2] = 64
    x[5][2] = 144


    y[0] = 1
    y[1] = 3.3
    y[2] = 5
    y[3] = 5.5
    y[4] = 6
    y[5] = 5.5

    return x, y

x, y = genData(6)
m, n = np.shape(x)
theta = np.ones(n)
yReg  = np.zeros(shape=m)
numIterations = 100000
alpha = 0.0001
#print "yReg", yReg
#print x
theta = gradientDescent(x, y, theta, alpha, m, numIterations)
print(theta)

#Create plot
plt.scatter(x[:,1],y, color='red')
plt.xlabel("Random X")
plt.ylabel("Random Y")
for i in range(0, m):
    yReg[i] = theta[0] + theta[1] * x[i][1] + theta[2] * x[i][2]
plt.plot (x[:,1], yReg )
plt.show()
