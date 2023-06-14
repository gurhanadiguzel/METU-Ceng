import numpy as np
import matplotlib.pyplot as plt
from scipy.io import wavfile


def fft(x):
    N = len(x)

    if N <= 1:
        return x

    even = fft(x[0::2])
    odd = fft(x[1::2])

    factor = np.exp(-2j * np.pi * np.arange(N) / N)
    return np.concatenate([even + factor[:N//2] * odd, even + factor[N//2:] * odd])


def fft_freq(length, sampling_rate):
    bins1 = np.arange(0, length/2, 1)
    bins2 = np.arange(-length/2, 0, 1)
    return np.concatenate((bins1, bins2)) / (sampling_rate * length)


def ifft(X):
    N = len(X)
    X_conj = np.conj(X)
    x = fft(X_conj) / N
    return np.conj(x)


def freq_domain_encoder(x):
    n = int(len(x) / 2)
    return np.concatenate((x[n-1::-1], x[:n-1:-1]))


def freq_domain_decoder(x):
    return freq_domain_encoder(x)


sample_rate, signal = wavfile.read('sound.wav')
signal = np.concatenate((signal, np.zeros(int(2 ** np.ceil(np.log2(len(signal))))-len(signal))))

freq_domain_signal = fft(signal)
np_freq_domain = np.fft.fft(signal)

for idx, value in enumerate(freq_domain_signal):
    if np.abs(value - np_freq_domain[idx]) > 10e-8:
        print(value, "--------", np_freq_domain[idx])

encoded_signal = freq_domain_encoder(freq_domain_signal)
decoded_signal = freq_domain_decoder(encoded_signal)
freq_bins = fft_freq(np_freq_domain.shape[-1], 1 / sample_rate)

plt.figure(1, layout='constrained')
plt.subplot(411)
plt.title("Fourier domain magnitude of encoded signal")
plt.plot(freq_bins, np.abs(encoded_signal))

plt.subplot(412)
plt.title('Time domain plot of encoded signal')
plt.plot(ifft(encoded_signal))

plt.subplot(413)
plt.title("Fourier domain magnitude of decoded signal")
plt.plot(freq_bins, np.abs(decoded_signal))

plt.subplot(414)
plt.title('Time domain of decoded signal')
plt.plot(ifft(decoded_signal))
plt.savefig('plots.png')
plt.show()

wavfile.write('decoded.wav', sample_rate, ifft(decoded_signal).astype(np.int16))
wavfile.write('encoded.wav', sample_rate, ifft(encoded_signal).astype(np.int16))

print(freq_domain_encoder([1, 2, 3, 4, 5, 6, 7, 8]))
