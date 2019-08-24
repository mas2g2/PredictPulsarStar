import csv
import numpy as np
import matplotlib.pyplot as plt

def load_data(filename):
    with open(filename,"r") as f:
        data = list(csv.reader(f))
    data = np.array(data)[1:,:].astype(float)
    return data

class LogisticRegression():
    def __init__(self):
        np.random.seed(1)
        self.theta = 2*np.random.rand(8,1)-1

    def sigmoid(self,x,deriv=False):
        if deriv == False:
            return 1/(np.exp(-x)+1)
        return x*(1-x)

    def g_x(self,x):
        return self.sigmoid(np.dot(x,self.theta))

    def update_weights(self,x,y,learning_rate):
        y = np.reshape(y,(len(y),1))
        N = len(x)
        pred = self.g_x(x)
        grad = np.dot(x.T,np.subtract(pred,y))
        grad /= N
        grad *= learning_rate
        self.theta -= grad

    def predict(self,x):
        pred = self.g_x(x)
        score = pred
        for i in range(len(pred)):
            if pred[i] <= 0.5:
                score[i] = 0
            else:
                score[i] = 1
        return score

    def cost_function(self,x,y):
        cost,pred = np.zeros((len(y),1)),self.g_x(x)
        for i in range(len(x)):
            cost[i] = y[i]*np.log(pred[i]) - (1-y[i])*np.log(1-pred[i])
        return -np.mean(cost)

    def fit(self,x,y,lr=0.001,iters=1000):
        for i in range(iters):
            err = self.cost_function(x,y)
            if i % 100 == 0:
                print("Error: ",err)
            self.update_weights(x,y,lr)

    def score(self,x,y):
        score = self.predict(x)
        count = 0
        for i in range(len(y)):
            if score[i] == y[i]:
                count += 1
        print(count)
        print(len(y))
        return count/len(y)
    def save_weights(self):
        data = ""
        with open("model.txt","w") as f:
            for element in self.theta:
                for i in element:
                    data += str(i)+","
            f.write(data)
            f.close()

    def load_weights(self):
        with open("model.txt","r") as f:
            cont = f.read()
        cont = np.fromstring(cont,dtype='float',sep=',')
        self.theta = cont
"""
trained = True
data = load_data("pulsar_stars.csv")
X,Y = data[:,:-1],data[:,-1]
train_x,train_y,test_x,test_y = X[:14317,:],Y[:14317],X[14317:,:],Y[14317:]
model = LogisticRegression()
if trained == False:
    model.fit(train_x,train_y)
    model.save_weights()
model.load_weights()
print(model.theta)
print("Accuracy : %.3f" % model.score(test_x,test_y))"""
