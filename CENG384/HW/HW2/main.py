import matplotlib.pyplot as plt

file = open("hw2_signal.csv", "r")
# file = open("test.csv", "r")

args = file.read().split(',')
si = args[0]
vs = args[1:]

si = int(si)
for i in range(0, len(vs)):
    vs[i] = float(vs[i])


def plotConvolution(valuesX, startingIndexX, valuesH, startingIndexH):
    valuesH.reverse()
    reversedIndexH = -(startingIndexH + len(valuesH) - 1)

    endX = startingIndexX + len(valuesX)

    valuesY = []

    for n in range(startingIndexX, startingIndexX + len(valuesX)):
        shiftedH = reversedIndexH + n
        endH = shiftedH + len(valuesH)

        start = startingIndexX if startingIndexX > shiftedH else shiftedH
        end = endX if endX < endH else endH

        total = 0

        if (start <= end):
            for index in range(start, end):
                xIndex = index - startingIndexX
                hIndex = index - shiftedH

                total += valuesX[xIndex] * valuesH[hIndex]

        valuesY.append(total)

    timeAxis = range(startingIndexX, startingIndexX+len(valuesX))

    plt.stem(timeAxis, valuesY, linefmt='b-', markerfmt='go', label='y[n]')
    plt.legend()
    plt.show()


# plotConvolution(vs, si, [1], 5)
# plotConvolution(vs, si, [0.33, 0.33, 0.33], 0)
# plotConvolution(vs, si, [0.2, 0.2, 0.2, 0.2, 0.2], 0)
# plotConvolution(vs, si, [0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1], 0)
plotConvolution(vs, si, [0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05,
                0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05], 0)
