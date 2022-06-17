#tensorflow==2.2, numpy==1.18
import sys
import pandas as pd
import numpy as np
import tensorflow as tf
from tensorflow.keras import models, layers, metrics, losses, optimizers, callbacks
from tensorflow.keras.layers import Lambda, Activation, Input, Embedding, Flatten, Dense, Concatenate
from tensorflow.keras.models import Model
import tensorflow.keras.backend as K
from sklearn.model_selection import train_test_split

class Recommender:
    def __init__(self, train_path, test_path):
        self.train_path = train_path
        self.test_path = test_path
        self.train_data = None
        self.val_data = None
        self.test_data = None
        self.model = None

    def set_data(self):
        header = ['user_id', 'item_id', 'rating', 'timestamp']
        train_data = pd.read_csv(self.train_path, sep='\t', names = header)
        train_data.drop('timestamp', axis=1, inplace=True)
        train_data, val_data = train_test_split(train_data, test_size = 0.01)
        test_data = pd.read_csv(self.test_path, sep='\t', names = header)
        test_data.drop('timestamp', axis=1, inplace = True)

        self.train_data = train_data
        self.val_data = val_data
        self.test_data = test_data

    def make_model(self):
        user_input = Input(shape=[1])
        user_embedding = Embedding(np.maximum(self.train_data.user_id.max() + self.val_data.user_id.max(), self.test_data.user_id.max())+1
        , 10, input_length=1)(user_input)
        user_vec = Flatten()(user_embedding)

        item_input = Input(shape=[1])
        item_embedding = Embedding(np.maximum(self.train_data.item_id.max() + self.val_data.item_id.max(), self.test_data.item_id.max())+1
        , 10, input_length=1)(item_input)
        item_vec = Flatten()(item_embedding)

        conc = Concatenate()([item_vec, user_vec])

        ly1 = Dense(64, activation = 'relu')(conc)
        ly2 = Dense(64, activation = 'relu')(ly1)
        out = Dense(1, activation = 'relu')(ly2)

        model = Model([user_input, item_input], out)
        
        self.model = model

    def train_test(self):
        self.model.compile(optimizer=optimizers.Adam(1e-4)
        , loss=losses.mean_squared_error
        , metrics=[metrics.RootMeanSquaredError()])
        
        self.model.fit([self.train_data.user_id, self.train_data.item_id], self.train_data.rating
        , batch_size=32, validation_data=([self.val_data.user_id, self.val_data.item_id], self.val_data.rating)
        , callbacks=[callbacks.EarlyStopping(patience=3, restore_best_weights=True)], epochs = 100, verbose = 1)

        output = Lambda(lambda x: K.round(x))(self.model.output)
        self.model = Model(self.model.input, output)

        self.model.compile(optimizer = optimizers.Adam(1e-4)
        , loss=losses.mean_squared_error
        , metrics=[metrics.RootMeanSquaredError()])

        self.model.evaluate([self.test_data.user_id, self.test_data.item_id], self.test_data.rating)
        predictions = self.model.predict([self.test_data.user_id, self.test_data.item_id])
        predictions = predictions.astype(np.int64)
        self.test_data.rating = predictions

if __name__ == '__main__':
    train_path = sys.argv[1]
    test_path = sys.argv[2]

    rcm = Recommender(train_path, test_path)
    rcm.set_data()
    rcm.make_model()
    rcm.train_test()
    rcm.test_data.to_csv(train_path+'_prediction.txt', sep='\t', index=False, header = False)