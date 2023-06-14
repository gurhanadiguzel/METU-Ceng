import numpy as np
import matplotlib.pyplot as plt


filename = "shifted_sawtooth_part_b.csv"
# filename = "sine_part_b.csv"
# filename = "chirp_part_b.csv"

data = np.loadtxt(filename, delimiter=",")
startIndex = int(data[0])
a = data[1]
b = data[2]
signalList = data[3:]

n = np.arange(startIndex, startIndex+len(signalList))
start = int(startIndex/a-b)
end = int((startIndex+len(signalList))/a-b)
dimension = len(signalList)/a - (end-start)
newScale = np.arange(start-dimension, end, 1/a)

plt.plot(n, signalList, label="Original signal")
plt.plot(newScale, signalList, label="Shifted and scaled signal")
plt.legend()
plt.show()
