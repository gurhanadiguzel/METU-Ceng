import numpy as np
import matplotlib.pyplot as plt

# filename = "shifted_sawtooth_part_a.csv"
# filename = "sine_part_a.csv"
filename = "chirp_part_a.csv"
data = np.loadtxt(filename, delimiter=",")
startIndex = int(data[0])
signalList = data[1:]
# Split the signal into its even and odd parts
coordinate = startIndex
length = len(signalList)
limit = length + startIndex
even = []
odd = []
for i in range(0, length):
    negIndex = -coordinate
    if (negIndex < startIndex or negIndex > limit):
        num = 0
    else:
        num = signalList[i-2*coordinate]
    even.append((signalList[i]+num)/2)
    odd.append((signalList[i]-num)/2)
    coordinate += 1

# Plot the original signal, even part, and odd part
n = np.arange(startIndex, startIndex+len(signalList))
plt.plot(n, signalList, label="Signal Part")
plt.plot(n, odd, label="Odd part")
plt.plot(n, even, label="Even part")
plt.legend()
plt.show()
