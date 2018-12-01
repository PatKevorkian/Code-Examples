import math
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from pylab import scatter, show, legend, xlabel, ylabel

#data is scalled
# value in the data
df = pd.read_csv("exam.csv", header=0)
df.insert(0, 'bias', 100)

# clean up data
df.columns = ["bias","test1","test2","admitted"]


# formats the input data into two arrays, one of independant variables
# and one of the dependant variable
X = df[["bias","test1","test2"]]
X = np.array(X)
X = X/100
Y = df["admitted"]
Y = np.array(Y)

pos = np.where(Y == 1)
neg = np.where(Y == 0)
scatter(X[pos, 1], X[pos, 2], marker='o', c='b')
scatter(X[neg, 1], X[neg, 2], marker='x', c='r')
xlabel('Exam 1 score')
ylabel('Exam 2 score')
legend(['Not Admitted', 'Admitted'])
plt.show()

##The sigmoid function adjusts the cost function hypotheses to adjust the algorithm proportionally for worse estimations
def Sigmoid(z):
	G_of_Z = float(1.0 / float((1.0 + math.exp(-1.0*z))))
	return G_of_Z 

##The hypothesis is the linear combination of all the known factors x[i] and their current estimated coefficients theta[i] 
##This hypothesis will be used to calculate each instance of the Cost Function
def Hypothesis(theta, x):
	z = 0
	for i in range(len(theta)):
		z += x[i]*theta[i]
	return Sigmoid(z)

##For each member of the dataset, the result (Y) determines which variation of the cost function is used
##The Y = 0 cost function punishes high probability estimations, and the Y = 1 it punishes low scores
##The "punishment" makes the change in the gradient of ThetaCurrent - Average(CostFunction(Dataset)) greater
def Cost_Function(X,Y,theta,m):
	sumOfErrors = 0
	for i in range(m):
		xi = X[i]
		hi = Hypothesis(theta,xi)
		if Y[i] == 1:
			error = Y[i] * math.log(hi)
		elif Y[i] == 0:
			error = (1-Y[i]) * math.log(1-hi)
		sumOfErrors += error
	const = -1/m
	J = const * sumOfErrors
	
	return J

##This function creates the gradient component for each Theta value 
##The gradient is the partial derivative by Theta of the current value of theta minus 
##a "learning speed factor aplha" times the average of all the cost functions for that theta
##For each Theta there is a cost function calculated for each member of the dataset
def Cost_Function_Derivative(X,Y,theta,j,m,alpha):
	sumErrors = 0
	for i in range(m):
		xi = X[i]
		xij = xi[j]
		hi = Hypothesis(theta,X[i])
		error = (hi - Y[i])*xij
		sumErrors += error
	m = len(Y)
	constant = float(alpha)/float(m)
	J = constant * sumErrors
	return J

##For each theta, the partial differential 
##The gradient, or vector from the current point in Theta-space (each theta value is its own dimension) to the more accurate point, 
##is the vector with each dimensional component being the partial differential for each theta value
def Gradient_Descent(X,Y,theta,m,alpha):
	new_theta = []
	constant = alpha/m
	for j in range(len(theta)):
		CFDerivative = Cost_Function_Derivative(X,Y,theta,j,m,alpha)
		new_theta_value = theta[j] - CFDerivative
		new_theta.append(new_theta_value)
	return new_theta

##The high level function for the LR algorithm which, for a number of steps (num_iters) finds gradients which take 
##the Theta values (coefficients of known factors) from an estimation closer (new_theta) to their "optimum estimation" which is the
##set of values best representing the system in a linear combination model
def Logistic_Regression(X,Y,alpha,theta,num_iters):
	m = len(Y)
	for x in range(num_iters):
		new_theta = Gradient_Descent(X,Y,theta,m,alpha)
		theta = new_theta
		if x % 100 == 0:
			#here the cost function is used to present the final hypothesis of the model in the same form for each gradient-step iteration
			Cost_Function(X,Y,theta,m)
	print ("theta " , theta)
	print ("cost is" , Cost_Function(X,Y,theta,m))
	return theta


#Initial guesses 
initial_theta = [0,0,0]
alpha = 1
iterations = 10000

#Create plot with prob

theta = Logistic_Regression(X,Y,alpha,initial_theta,iterations)

prob = []

for i in range(79):
    prob.append(Sigmoid(np.dot(X[i],theta)))

for i in range(79):
    scatter(np.dot(X[i,:],theta), prob[i],marker='.',c='g')

xlabel('Exam 1 score')
ylabel('Exam 2 score')
legend(['Prob'], loc=2)
plt.ylim(0,1)
plt.show()

predict = [0.0,0.0,0.0]
predict = np.array(predict)
predict[0] = 100
predict[1] = float(input('Enter first exam score: '))
predict[2] = float(input('Enter second exam score: '))
predict = predict/100

print ('Predicted probability for admission is',Sigmoid(np.dot(predict, theta)))

