from random import choice
from numpy import array, dot, random,all,any,zeros
import matplotlib.pyplot as plt
import pylab


#The first two entries of the NumPy array in each tuple are the two input values. The second element of the tuple is the expected result. And the third entry of the array is the bias which is needed to move the threshold (also known as the decision boundary) up or down as needed by the step function. Here the perceptron is being trained to recognize an OR operation.

training_data = [
                 (array([0,0,1]), 0),
                 (array([0,1,1]), 1),
                 (array([1,0,1]), 1),
                 (array([1,1,1]), 1),
                 ]

#initial weights
w = random.rand(3)
#array of errors
errors = []
#learing rate
learnRate = 0.1
#itterations
n = 100
#theta
threshTheta = 0
#threshold
thresh = lambda x: 0 if (x < threshTheta) else 1


#Then we calculate the dot product of the input and weight vectors. This is our (scalar) result, which we can compare to the expected value. If the expected value is bigger, we need to increase the weights, if it's smaller, we need to decrease them.

for i in xrange(n):
    x, expected = choice(training_data)
    result = dot(w, x)
    error = expected - thresh(result)
    errors.append(error)
    w += learnRate * error * x

#print results

for x, _ in training_data:
    result = dot(x, w)
    print("{}: {} -> {}".format(x[:2], result, thresh(result)))

#plot of the errors
plt.plot(errors)
fig = pylab.gcf()
fig.canvas.set_window_title('Plot of Errors')
axes = plt.gca()
axes.set_xlim([0,30])
plt.show()

#printing weights
print 'Weights and Bias:', w

#plot of the decision boundary
w2,w1,b = w
x = -b / w1
y = -b / w2
d = y
c = -y / x

line_x_coords = array([0, x])
line_y_coords = c * line_x_coords + d
plt.plot(line_x_coords, line_y_coords)
pylab.scatter([0,0,1,1],[0,1,0,1],marker ='o')
fig = pylab.gcf()
fig.canvas.set_window_title('Plot of Decision Boundary and Weights')
plt.plot(w)
pylab.legend(['Boundary', 'Weights'])
plt.show()

#prediciton
i1 = input('Enter feature one: ')
i2 = input('Enter feaure two: ')
input = [i1,i2,1]

#If the result is over the threshold then its a 1 under its a 0
print'Result: ',dot(input,w)
if dot(input,w) > threshTheta:
    print 'Prediction: 1'
elif dot(input,w) < threshTheta:
    print 'Prediction: 0'


