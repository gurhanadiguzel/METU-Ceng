import matplotlib.pyplot as plt


def draw_even_odd_parts(signal: list[float], starting_index: int) -> None:
    width = abs(starting_index) if abs(starting_index) > abs(starting_index+len(signal)-1) \
                                else abs(starting_index+len(signal)-1)
    original_index = [x for x in range(starting_index, starting_index + len(signal))]
    padded_index = [x for x in range(-width, width + 1)]
    padded_signal = [0 for _ in range(2*width+1)]
    for idx, idy in enumerate(original_index):
        padded_signal[padded_index.index(idy)] = signal[idx]
    time_reversal = padded_signal[::-1]
    even_signal = []
    odd_signal = []

    for idx, value in enumerate(padded_signal):
        even_signal.append(0.5 * (value + time_reversal[idx]))
        odd_signal.append(0.5 * (value - time_reversal[idx]))
    plt.figure(1, layout="constrained")
    plt.subplot(311)
    plt.title("Original signal")
    plt.plot(padded_index, padded_signal, "g-")
    plt.subplot(312)
    plt.title("Even part")
    plt.plot(padded_index, even_signal, "b-")
    plt.subplot(313)
    plt.title("Odd part")
    plt.plot(padded_index, odd_signal, "r-")
    plt.show()


def draw_scaled_shifted_version(signal: list[float], starting_index: int, scale: int, shift: int) -> None:
    width = abs(starting_index) if abs(starting_index) > abs(starting_index + len(signal) - 1) \
                                else abs(starting_index + len(signal) - 1)
    original_index = [x for x in range(starting_index, starting_index + len(signal))]
    padded_index = [x for x in range(-width, width + 1)]
    padded_signal = [0 for _ in range(2 * width + 1)]
    for idx, idy in enumerate(original_index):
        padded_signal[padded_index.index(idy)] = signal[idx]
    scaled_and_shifted_signal = []
    scaled_and_shifted_index = []
    index_transform = lambda x: scale * x + shift
    index = -width - abs(shift)
    while index <= width + abs(shift):
        try:
            scaled_and_shifted_signal.append(padded_signal[padded_index.index(index_transform(index))])
            scaled_and_shifted_index.append(index)
            index += 1
        except ValueError:
            index += 1

    plt.figure(1, layout="constrained")
    plt.subplot(211)
    plt.title("Original signal")
    plt.plot(padded_index, padded_signal, "g-")
    plt.subplot(212)
    plt.title("Scaled and shifted version")
    plt.plot(scaled_and_shifted_index, scaled_and_shifted_signal, "b-")
    plt.show()


if __name__ == '__main__':
    # Signal creation
    # Cosine
    # index = -100
    # signals = [np.sin(t * 2 * np.pi * 0.015) for t in range(index, abs(index)+1)]
    # Sawtooth
    # index = -25
    # t = np.linspace(0, 1, 401)
    # signals = signal.sawtooth(2 * np.pi * 3 * t)
    # index = -250
    # t = np.linspace(0, 10, 501)
    # signals = signal.chirp(t, f0=6, f1=1, t1=10, method='linear')
    # with open("chirp.csv", "w") as file:
    #    file.write(str(index))
    #    for value in signals:
    #        file.write(",")
    #        file.write(str(value))
    #
    # Part A
    # with open('chirp_part_a.csv', 'r') as file:
    #     data = list(map(float, file.read().split(',')))
    # starting_index, initial_signal = int(data[0]), data[1:]
    # draw_even_odd_parts(initial_signal, starting_index)
    #
    # Part B
    with open('chirp_part_b.csv', 'r') as file:
        data = list(map(float, file.read().split(',')))
    starting_index, scale, shift = int(data[0]), int(data[1]), int(data[2])
    initial_signal = data[3:]
    draw_scaled_shifted_version(initial_signal, starting_index, scale, shift)
