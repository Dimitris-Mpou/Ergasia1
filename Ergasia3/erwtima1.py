from keras.models import load_model
import tensorflow
import pandas as pd
import numpy as np
from tensorflow import keras
from keras import layers, optimizers, losses, metrics

model = load_model('WindDenseNN.h5')

data = pd.read_csv('nn_representations.csv', usecols = [i for i in range(1,129)], header=None)
actual = pd.read_csv('actual.csv', usecols = [i for i in range(1,8)], header=None)

result = model.predict(data, batch_size=32)

total = 0
for i in range(23988):
	for j in range(7):
		total += abs(actual.iloc[i, j] - result[i, j])
mae = total/(23988*7)
print("MAE = ", mae)

total = 0
for i in range(23988):
	for j in range(7):
		total +=(actual.iloc[i, j] - result[i, j])**2
mse = total/(23988*7)
print("MSE = ", mse)

total = 0
for i in range(23988):
	for j in range(7):
		if actual.iloc[i, j] != 0:
			total += abs((actual.iloc[i, j] - result[i, j]) / actual.iloc[i, j])
mape = 100*total/(23988*7)
print("MAPE = ", mape, " %")

res = pd.DataFrame([['MAE: ', mae,'MAPE: ', mape, '%','MSE: ', mse]])
act = pd.read_csv('actual.csv', header=None)
frames = [res, act]
output = pd.concat(frames)
output.to_csv('predicted.csv', index=False, header=False)

print(output)
