import numpy as np
import matplotlib.pyplot as plt


def f(n):
    return n * ((n + 1) / n - 1) - 1


def g(n):
    result = f(n) / np.finfo(float).eps

    return result


for n in range(1, 1001):
    if g(n) == 0:
        print(n)

# Using my machine's epsilon, which is approximately 2.220446049250313e-16,
n = np.arange(1, 1001)
plt.plot(n, g(n))
plt.xlabel("n")
plt.ylabel("g(n)")
plt.title("Plot of g(n)")
plt.show()
