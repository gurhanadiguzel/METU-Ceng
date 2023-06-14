import matplotlib.pyplot as plt
import numpy as np


def convolution(signal1, start1, signal2, start2):
    start1 = start1 + (5)

    return start1


filename = "hw2_signal.csv"
data = np.loadtxt(filename, delimiter=",")
startIndex = int(data[0])
signal_h = [1]
signalList = data[1:]
signalShift = 5
finalStart = convolution(signalList, startIndex, signal_h, 5-startIndex)
x = finalStart
m = np.arange(x, x+len(signalList))
n = np.arange(startIndex, startIndex+len(signalList))

plt.stem(n, signalList,  linefmt="b-", markerfmt="bo ", label="x[n]")
plt.stem(m, signalList, linefmt="g-", markerfmt="go ", label="y[n]")
plt.legend()
plt.show()
