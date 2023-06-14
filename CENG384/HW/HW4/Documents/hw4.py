import numpy as np
import matplotlib.pyplot as plt
from scipy.io import wavfile

def fft(signal):
    N = len(signal)
    if (N <= 1):
        return signal
    even = fft(signal[::2])
    odd = fft(signal[1::2])
    T = [np.exp(-2j * np.pi * i / N) * odd[i] for i in range(N // 2)]
    return [even[i] + T[i] for i in range(N // 2)] + [even[i] - T[i] for i in range(N // 2)]

def ifft(signal):
    N = len(signal)
    conjugate_signal = np.conjugate(signal)
    fft_signal = fft(conjugate_signal)
    return np.conjugate(fft_signal) / N

# Read the encoded audio file
sample_rate, encoded_signal = wavfile.read('encoded.wav')

# Perform FFT on the encoded signal
encoded_data = fft(encoded_signal)

# Split the FFT into positive and negative frequencies
positive_freq = encoded_data[:len(encoded_data)//2]
negative_freq = encoded_data[len(encoded_data)//2:]

# Reverse the positive and negative frequency parts
reversed_positive_freq = positive_freq[::-1]
reversed_negative_freq = negative_freq[::-1]

# Concatenate the reversed positive and negative frequencies
reversed_fft = np.concatenate((reversed_positive_freq, reversed_negative_freq))

# Perform IFFT on the reversed FFT
decoded_data = ifft(reversed_fft).real

# Convert the decoded signal to integer type
decoded_data = np.int16(decoded_data)

# Save the decoded audio as "decoded.wav" file
wavfile.write('decoded.wav', sample_rate, decoded_data)

plt.figure(figsize=(10, 6))
plt.subplot(2, 1, 1)
plt.magnitude_spectrum(encoded_data, Fs=sample_rate, scale='dB')
plt.title('Encoded Signal')
plt.subplot(2, 1, 2)
plt.magnitude_spectrum(decoded_data, Fs=sample_rate, scale='dB')
plt.title('Decoded Signal')
plt.tight_layout()
plt.show()

plt.figure(figsize=(10, 6))
plt.subplot(2, 1, 1)
plt.plot(encoded_data)
plt.title('Encoded Signal')
plt.subplot(2, 1, 2)
plt.plot(decoded_data)
plt.title('Decoded Signal')
plt.tight_layout()
plt.show()
