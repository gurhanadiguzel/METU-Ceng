import numpy as np
import matplotlib.pyplot as plt

def fourierCoefficients(signal, period, n):
    # Compute DC component
    dc = np.mean(signal)

    # Compute Omega0 
    omega_0 =(2 * np.pi)/ period

    t = np.linspace(-0.5, 0.5, 1000, endpoint=False)

    # Compute Fourier series coefficients for cosine components
    cos_coeffs = np.zeros(n)
    for i in range(1, n+1):
        cos_coeffs[i-1] = 2*np.sum(signal*np.cos(i*omega_0*t)) / len(signal)
    
    # Compute Fourier series coefficients for sine components
    sin_coeffs = np.zeros(n)
    for i in range(1, n+1):
        sin_coeffs[i-1] = 2*np.sum(signal*np.sin(i*omega_0*t)) / len(signal)

    return dc, cos_coeffs, sin_coeffs

def fourierApproximation(coeffs, period, t):
    dc, cos_coeffs, sin_coeffs = coeffs
    omega_0 =(2 * np.pi)/ period
    signal = dc + np.sum([a*np.cos(k*omega_0*t) + b*np.sin(k*omega_0*t) 
                          for k, (a, b) in enumerate(zip(cos_coeffs, sin_coeffs), start=1)], axis=0)
    return signal


def square_wave(time):
    if (time < 0):  return -1
    else:  return 1
       

def sawtooth_wave(time):
    if (time < 0): return 1 + 2*time
        
    else: return -1 + 2*time
        
    

n_points = 1000
time = np.linspace(-0.5, 0.5, n_points, endpoint=False)
signal = np.zeros(n_points)

# Generate the square wave function
signal = np.array([square_wave(i) for i in time])

# Generate the sawtooth signal
#signal = np.array([sawtooth_wave(i) for i in time])

# Compute the Fourier Series coefficients of the square wave function
period = 1
n_coeffs = [1, 5, 10, 50, 100]
coeffs = [fourierCoefficients(signal, period, n) for n in n_coeffs]

# Generate the approximated functions using the Fourier Series coefficients
signals = [fourierApproximation(coeffs[i], period, time) for i in range(len(n_coeffs))]

# Plot the original and approximated functions
plt.figure(figsize=(8, 6))
plt.plot(time, signal, label='Original')
colors = ['r', 'g', 'b', 'm', 'y']

for i in range(len(n_coeffs)):
    plt.plot(time, signals[i], label=f'n={n_coeffs[i]}', color=colors[i])

plt.legend()
plt.title('Approximation of Square Wave Function using Fourier Series')
plt.xlabel('Time')
plt.ylabel('Amplitude')
plt.show()
