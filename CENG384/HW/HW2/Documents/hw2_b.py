import matplotlib.pyplot as plt
import numpy as np

#########################
# def conv(signal1, start1, signal2, start2):
#    return np.convolve(signal1, signal2)
#######################


def convolution(signal1, start1, signal2, start2):
    len_x = len(signal1)
    len_h = len(signal2)
    len_y = len_x+len_h+1
    y = np.zeros(len_y)
    for n in range(len_y):
        for k in range(len_x):
            if n - k >= 0 and n - k < len_h:
                y[n] += signal1[k] * signal2[n - k]

    return y


filename = "hw2_signal.csv"
data = np.loadtxt(filename, delimiter=",")
startIndex = int(data[0])
signalList = data[1:]
N = 20  # will change
h = []
len_x = len(signalList)
for i in range(0, len_x):
    if (0 <= i+startIndex and i+startIndex <= N-1):
        h.append(1/N)
    else:
        h.append(0)
lst = convolution(signalList, startIndex, h, startIndex)
n = np.arange(startIndex, startIndex+len(signalList)*2+1)
plt.stem(n, lst, linefmt='b-', markerfmt='bo', label="y[n]")
plt.legend()
plt.show()
