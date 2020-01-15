from keras.models import load_model
import pandas as pd

from tensorflow.keras import backend as K

model = load_model('WindDenseNN.h5')

data = pd.read_csv('nn_representations.csv', usecols = [i for i in range(1,129)], header=None)
actual = pd.read_csv('actual.csv', usecols = [i for i in range(1,8)], header=None)
result = model.predict(data, batch_size=32)


# create a Keras function to get layer[0]
get_layer_output = K.function(inputs = model.layers[0].input, outputs = model.layers[0].output)

# extract output
layer_output = get_layer_output(data)

print(layer_output.shape)
print(layer_output)
