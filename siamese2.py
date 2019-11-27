from __future__ import absolute_import
from __future__ import print_function
import numpy as np
from numpy.random import seed
seed(1)
import random
from keras.models import load_model
from keras.datasets import mnist
from keras.models import Model, Sequential
from keras.layers import Input, Flatten, Dense, Dropout, Lambda, LSTM
from keras.layers.normalization import BatchNormalization
from keras.optimizers import RMSprop,Adam,SGD, Adadelta
from keras import backend as K
from keras.callbacks import ModelCheckpoint
# from keras.models import load_weights
from numpy.random import seed
seed(1)
from tensorflow import set_random_seed
set_random_seed(2)
from random import shuffle
import pandas as pd

result = []
num_classes = 2
epochs = 300
def standardize(data):
        temp = np.copy(data)
        for i in range(data.shape[0]):
            for j in range(data.shape[2]):
                dt = data[i,:,j]
                me = np.mean(dt)
                std = np.std(dt)
                dt = (dt-me)/std
                temp[i,:,j] = dt

        return temp

def normalize(data):

    temp = np.copy(data)
    for i in range(data.shape[0]):
        mx = np.max(data[i])
        mi = np.min(data[i])
        temp[i] = (data[i]-mi)/(mx-mi)

    return temp
yui=0
window = [[100,300],[300,500],[500,700],[700,900],[900,1100],[100,400],[300,600],[500,800],[700,1000],[900,1200],[100,500],[300,700],[500,900]]
for mm in window:

    for gg in range(9):


        gg2 = gg+1


        train_path = 'trd_bin_280303_new'+str(gg)+str(gg2)+'.npy'                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
        train_label_path = 'trl_bin_280303_new'+str(gg)+str(gg2)+'.npy'

        valid_path = 'vad_bin_280303_new'+str(gg)+str(gg2)+'.npy'
        valid_label_path = 'val_bin_280303_new'+str(gg)+str(gg2)+'.npy'

        test_path = 'ted_bin_280303_new'+str(gg)+str(gg2)+'.npy'
        test_label_path = 'tel_bin_280303_new'+str(gg)+str(gg2)+'.npy'


        train = np.load(train_path)
        train = train[:,mm[0]:mm[1],:]
        train_label = np.load(train_label_path)

        valid = np.load(valid_path)
        valid = valid[:,mm[0]:mm[1],:]
        valid_label = np.load(valid_label_path)

        test = np.load(test_path)
        test = test[:,mm[0]:mm[1],:]
        test_label = np.load(test_label_path)


        train = standardize(train)
        test = standardize(test)
        valid = standardize(valid)





        def exponent_neg_manhattan_distance(vects):
            x, y = vects
            return K.exp(-K.sum(K.abs(x-y), axis=1, keepdims=True))


        def eucl_dist_output_shape(shapes):
            shape1, shape2 = shapes
            return (shape1[0], 1)





        def create_pairs(x, digit_indices):

            pairs = []
            labels = []
            positive_pairs = []
            negative_pairs = []

            for i in range(2):
                for j in range(len(digit_indices[i])):
                    for k in range(j+1,len(digit_indices[i])):
                        positive_pairs.append([x[digit_indices[i][j]], x[digit_indices[i][k]]])


            for i in range(2):
                for p in range(len(digit_indices[i])):
                    for j in range(i+1,2):
                        for k in range(len(digit_indices[j])):
                            negative_pairs.append([x[digit_indices[i][p]], x[digit_indices[j][k]]])



            for i in range(10):
                shuffle(negative_pairs)
                shuffle(positive_pairs)
            print(len(positive_pairs), len(negative_pairs))
            pr = []
            for i in range(len(positive_pairs)):
                pr.append([positive_pairs[i], 0])
            for i in range(len(negative_pairs)):
                pr.append([negative_pairs[i], 1])

            for i in range(10):
                shuffle(pr)

            for i in range(len(pr)):
                pairs.append(pr[i][0])
                labels.append(pr[i][1])


            print(len(pairs))
            return np.array(pairs), np.array(labels)



        def compute_accuracy(y_true, y_pred):

            pred = y_pred.ravel() < 0.5
            return np.mean(pred == y_true)





        input_shape = train.shape[1:]

        digit_indices = []
        for i in range(2):
            temp=[]
            digit_indices.append(temp)

        for i in range(train_label.shape[0]):
            for j in range(2):
                if(train_label[i][j]==1):
                    digit_indices[j].append(i)
        tr_pairs, tr_y = create_pairs(train, digit_indices)



        test_data = []
        test_l = []
        for i in range(valid.shape[0]):
            test_data.append(valid[i])
            test_l.append(valid_label[i])
        for i in range(test.shape[0]):
            test_data.append(test[i])
            test_l.append(test_label[i])
        test_data = np.array(test_data)
        test_l = np.array(test_l)

        digit_indices = []
        for i in range(2):
            temp=[]
            digit_indices.append(temp)

        for i in range(test_l.shape[0]):
            for j in range(2):
                if(test_l[i][j]==1):
                    digit_indices[j].append(i)
        te_pairs, te_y = create_pairs(test_data, digit_indices)



        base_network = Sequential([
            LSTM(4,return_sequences=True),
            LSTM(8,return_sequences=True),
            LSTM(16,return_sequences=False),
            # Dropout(0.1),
            BatchNormalization(),
            Dense(8, activation='relu')
        ])

        input_a = Input(shape=input_shape)
        input_b = Input(shape=input_shape)


        processed_a = base_network(input_a)
        processed_b = base_network(input_b)


        distance = Lambda(exponent_neg_manhattan_distance, output_shape=eucl_dist_output_shape)([processed_a, processed_b])
        dense1 = Dense(4,activation='relu')(distance)
        prediction = Dense(1,activation='sigmoid')(dense1)
        model = Model([input_a, input_b], prediction)


        optimizer = Adam(1e-3, decay=1e-7)
#         model = load_model('weights_new_'+str(yui)+'_'+str(gg2)+str(gg)+'.h5')
        model.compile(loss='binary_crossentropy', optimizer=optimizer, metrics=['accuracy'])
        model.summary()

        model.fit([tr_pairs[:, 0], tr_pairs[:, 1]], tr_y,
                  batch_size=128,
                  epochs=epochs,shuffle=True,
                  validation_split = 0.1)

        pred = model.predict([te_pairs[:,0], te_pairs[:,1]])

        ct=0.0
        for i in range(len(pred)):
            if(np.abs(pred[i]-te_y[i])<0.5):
                ct+=1.0
        acc = (ct/len(pred))*100.0
        print(acc)


        pred = model.predict([tr_pairs[:,0], tr_pairs[:,1]])

        ct=0.0
        for i in range(len(pred)):
            if(np.abs(pred[i]-tr_y[i])<0.5):
                ct+=1.0
        acc2 = (ct/len(pred))*100.0
        print(acc2)




        model.save('weights_new_'+str(yui)+'_'+str(gg2)+str(gg)+'.h5')

        py = [3,5,10]
        lis_acc = []
        for k in py:
            pred_label = []
            new_test = []
            new_test_label = []
            for i in range(test.shape[0]):
                new_test.append(test[i])
                new_test_label.append(test_label[i])
            for i in range(valid.shape[0]):
                new_test.append(valid[i])
                new_test_label.append(valid_label[i])
            new_test = np.array(new_test)
            new_test_label = np.array(new_test_label)
            for i in range(new_test.shape[0]):
                ctp = [0]*2
                distance = []

                for j in range(train.shape[0]):
                    t1 = [train[j]]
                    t1 = np.array(t1)
                    t2 = [new_test[i]]
                    t2 = np.array(t2)
                    pred = model.predict([t1, t2])
                    distance.append([pred, train_label[j]])

                distance = sorted(distance, key=lambda s: s[0])

                for j in range(k):
                    ctp[np.argmax(distance[j][1])]+=1

                if(ctp[0]>=ctp[1]):
                    pred_label.append([1,0])
                else:
                    pred_label.append([0,1])

            ct=0.000
            for i in range(new_test.shape[0]):
                ind1 = np.argmax(new_test_label[i])
                ind2 = np.argmax(pred_label[i])

                if(ind1==ind2):
                    ct+=1.0000

            print(ct, new_test.shape[0]) 
            print(gg, gg2, k, 'Accuracy Classifier: ', (ct/new_test.shape[0])*100.0)
            lis_acc.append((ct/new_test.shape[0])*100)
        result.append([str(gg2)+str(gg), acc2, acc, lis_acc[0], lis_acc[1], lis_acc[2]])



    df = pd.DataFrame(result,columns=['Pair','Siamese Train Accuracy', 'Siamese Test Accuracy', 'Classification Accuracy k=3','Classification Accuracy k=5', 'Classification Accuracy k=10'])
    df.to_csv('result_siamese_new{}.csv'.format(yui), sep='\t')
    yui+=1
