import os
os.environ["THEANO_FLAGS"]="device=gpu,floatX=float32"
import numpy as np
import theano
from keras.models import Sequential
from keras.layers.core import Dense, Dropout, Activation
from keras.layers import  advanced_activations
from keras.optimizers import SGD, Adam, RMSprop
from keras.regularizers import l2, activity_l2
from keras.constraints import maxnorm
from generateData import generateData
from scipy import io, stats
from keras import backend as K
import theano.tensor as T
import random

def generateData(train_x, p, sigma, n=1):
    #print p 
    #print sigma 
    a,b = train_x.shape
    #print np.count_nonzero(train_x)
    aa = a*n
    
    train = np.asarray(np.zeros((aa,b)))
    idx_all = np.asarray(np.zeros((aa,b)))

    # Generate nullification rate according to gussian distribution 
    RFN_rates = np.random.normal(p, 0.00001, a) # use the expectation of training nullification rates as testing nullification rate
    l = np.where(RFN_rates<0)
    RFN_rates[l] = 0
    l = np.where(RFN_rates>1)
    RFN_rates[l] = 1 

    idx = []
    for k in range(b):
        idx.append(k)
    idx = np.asarray((idx))

    # random feature nullification 
    for i in range(n):        
        for j in range(a):
            idx1 = np.copy(idx)
            random.shuffle(idx1)
            p1 = RFN_rates[j]
            b1 = int(round(p1*b))
            idx2 = idx1[0:b1]
            k = np.copy(train_x[j,])
            k[idx2] = 0
            train[i*a+j,] = k
            idx_all[i*a+j,] = idx1

    data = [train, idx_all, RFN_rates]
    return data
    
def dropinput(p,sigma,n):
    train=io.loadmat('train.mat')
    X_train=train['train_x']
    Y_train=train['train_y']
    print np.count_nonzero(X_train)
   
    test=io.loadmat('testall.mat')
    X_test_original=test['test_x']
    Y_test=test['test_y'] 
    print np.count_nonzero(X_test_original)

    train=generateData(X_train,p,sigma,n)
    X_train=train[0]
    #rfn_rate=train[2]
    #print rfn_rate
    print np.count_nonzero(X_train)

    a=np.copy(Y_train)    
    for i in range(n-1):
        Y_train=np.row_stack((Y_train,a))
    print Y_train.shape

    test_drop=generateData(X_test_original, p, sigma)
    X_test = test_drop[0]
    idx_droped = test_drop[1]
    print idx_droped.shape
    print np.count_nonzero(X_test)

    print ('strat construcing DNN')
    print ('**************************')
    
    batch_size=100
    nb_classes=10
    nb_epoch=50
    
    model = Sequential()
    
    model.add(Dense(784,input_shape=(784,),init='he_normal',))
    model.add(Activation('relu'))
    model.add(Dropout(0.25))
    #model.add(advanced_activations.LeakyReLU(0.5))
    #activity_regularizer=activity_l2(0.01)
    #W_constraint=maxnorm(2)
    
    model.add(Dense(784,init='he_normal'))
    model.add(Activation('relu'))
    model.add(Dropout(0.25))
    #model.add(advanced_activations.LeakyReLU(0.01))
    #activity_regularizer=activity_l2(0.01)
    #W_constraint=maxnorm(2)
    
    model.add(Dense(784,init='he_normal'))
    model.add(Activation('relu'))
    model.add(Dropout(0.250))
    #model.add(advanced_activations.LeakyReLU(0.01))
    #activity_regularizer=activity_l2(0.01)
    #W_constraint=maxnorm(2)
    
    model.add(Dense(10,init='he_normal'))
    model.add(Activation('softmax'))
    
    model.summary()
   
    model.compile(loss='categorical_crossentropy',optimizer=RMSprop(), metrics=['accuracy'])
    model.fit(X_train, Y_train, batch_size=batch_size, nb_epoch=nb_epoch, verbose=1, validation_data=(X_test,Y_test))
    
    #model_name='MNIST_RFN_accuracy_'+str(int(p*100))+'.h5'
    #model.save(model_name)

    print '**************************** Test legitimate test data **********************'
    score = model.evaluate(X_test, Y_test, verbose=0)
    print score[1]
    
if __name__=="__main__":
    sigma=
    p=
    dropinput(p, sigma, 1)    
    