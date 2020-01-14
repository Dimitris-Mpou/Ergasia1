from keras.models import load_model
import pandas as pd

model = load_model('WindDenseNN.h5')
model.summary()

data = pd.read_csv('nn_representations.csv', usecols = [i for i in range(1,129)], header=None)
actual = pd.read_csv('actual.csv', usecols = [i for i in range(1,8)], header=None)

result = model.predict(data, batch_size=100)

#print(result.shape)print(result)print(data.iloc[0, 0])print(result[0 , 0])print(actual.iloc[0, 0])

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
