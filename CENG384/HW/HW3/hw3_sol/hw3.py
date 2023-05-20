import numpy as np
import matplotlib.pyplot as plt
from scipy.signal import sawtooth

resolution = 1000


def fourier_coefficients(f, T, n):
    # Compute the DC component
    a0 = np.sum(f) / T
    x = np.linspace(-T / 2, T / 2, resolution)
    # Compute the coefficients for each harmonic
    an = np.zeros(n)
    bn = np.zeros(n)
    for i in range(1, n + 1):
        an[i - 1] = 2 / T * np.sum(f * np.cos(2 * np.pi * i * x / T))
        bn[i - 1] = 2 / T * np.sum(f * np.sin(2 * np.pi * i * x / T))

    return a0, an, bn


def fourier_series(x, a0, an, bn, T):
    # Compute the Fourier series approximation
    N = len(an)
    s = a0 * np.ones(len(x))
    for i in range(N):
        s += an[i] * np.cos(2 * np.pi * (i + 1) * x / T) + bn[i] * np.sin(2 * np.pi * (i + 1) * x / T)
    return s


def main():
    # Define the different number of harmonics
    n_values = [1, 5, 10, 50, 100]
    # Calculations for square wave
    T = 1
    x = np.linspace(-T / 2, T / 2, resolution)
    f = np.sign(np.sin(2 * np.pi * x))
    for n in n_values:
        a0, an, bn = fourier_coefficients(f, T, n)
        s = fourier_series(x, a0, an, bn, T) / resolution
        plt.plot(x, f, label='Original')
        plt.plot(x, s, label='Fourier series')
        plt.legend()
        plt.title(f"Approximation of Square Wave \n Using First {n} Element of Fourier Series")
        plt.xlabel("Time")
        plt.savefig(f"Approximation of Square Wave \n Using First {n} Element of Fourier Series.png")
        plt.show()

    # Calculations for sawtooth
    T = 1
    x = np.linspace(-T / 2, T / 2, resolution)
    f = sawtooth(2 * np.pi * x)
    for n in n_values:
        a0, an, bn = fourier_coefficients(f, T, n)
        s = fourier_series(x, a0, an, bn, T) / resolution
        plt.plot(x, f, label='Original')
        plt.plot(x, s, label='Fourier series')
        plt.legend()
        plt.title(f"Approximation of Sawtooth \n Using First {n} Element of Fourier Series")
        plt.xlabel("Time")
        plt.savefig(f"Approximation of Sawtooth \n Using First {n} Element of Fourier Series.png")
        plt.show()


if __name__ == '__main__':
    main()
