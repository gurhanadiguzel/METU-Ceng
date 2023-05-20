import matplotlib.pyplot as plt


def convolve(signal1: list[float], starting_point1: int,
             signal2: list[float], starting_point2: int) -> (list[float], int):
    # Create starting point and empty result list
    starting_point_result = starting_point1 + starting_point2
    result_signal = [0. for _ in range(len(signal1) + len(signal2) - 1)]

    # Create padded signals (signal2 should be reversed)
    padded_signal1 = [0.] * (len(signal2)-1) + signal1 + [0.] * (len(signal2)-1)
    padded_signal2 = signal2[::-1] + [0.] * (len(padded_signal1) - len(signal2))

    # Apply convolution via shifting signal2
    for idx in range(len(signal1) + len(signal2) - 1):
        #
        result_signal[idx] = sum([value * padded_signal2[idy] for idy, value in enumerate(padded_signal1)])
        # shift signal2
        padded_signal2 = [0] + padded_signal2[:-1]
    return result_signal, starting_point_result


if __name__ == '__main__':
    # Read the signal
    with open('hw2_signal.csv', 'r') as file:
        data = file.read().split(',')
        starting_point = int(data[0])
        hw_signal = list(map(float, data[1:]))

    # Plot the original signal
    plt.stem(list(range(starting_point, starting_point+len(hw_signal))), hw_signal)
    plt.title('Original signal')
    plt.savefig('original_signal.png')
    plt.show()

    # Create delta[n-5]
    delta = [1]
    starting_point_delta = 5

    # Convolve hw_signal with delta[n-5] and plot the result
    result_d, starting_point_result_d = convolve(hw_signal, starting_point, delta, starting_point_delta)

    plt.stem(list(range(starting_point_result_d, starting_point_result_d + len(result_d))), result_d)
    plt.title('Result of the convolution with delta[n-5]')
    plt.savefig('delta_result.png')
    plt.show()

    # Create moving average filters
    starting_point_moving_average = 0
    n_point_moving_average_filter = lambda n: [1/n for _ in range(n)]
    moving_average_3 = n_point_moving_average_filter(3)
    moving_average_5 = n_point_moving_average_filter(5)
    moving_average_10 = n_point_moving_average_filter(10)
    moving_average_20 = n_point_moving_average_filter(20)

    # Convolve hw_signal with 4 different moving average filter and plot the results
    # N = 3
    result_3, starting_point_result_3 = convolve(hw_signal, starting_point,
                                                 moving_average_3, starting_point_moving_average)
    plt.stem(list(range(starting_point_result_3, starting_point_result_3 + len(result_3))), result_3)
    plt.title('Result of the convolution with 3-point moving average')
    plt.savefig('moving_average_3_result.png')
    plt.show()

    # N = 5
    result_5, starting_point_result_5 = convolve(hw_signal, starting_point,
                                                 moving_average_5, starting_point_moving_average)
    plt.stem(list(range(starting_point_result_5, starting_point_result_5 + len(result_5))), result_5)
    plt.title('Result of the convolution with 5-point moving average')
    plt.savefig('moving_average_5_result.png')
    plt.show()

    # N = 10
    result_10, starting_point_result_10 = convolve(hw_signal, starting_point,
                                                   moving_average_10, starting_point_moving_average)
    plt.stem(list(range(starting_point_result_10, starting_point_result_10 + len(result_10))), result_10)
    plt.title('Result of the convolution with 10-point moving average')
    plt.savefig('moving_average_10_result.png')
    plt.show()

    # N = 20
    result_20, starting_point_result_20 = convolve(hw_signal, starting_point,
                                                   moving_average_20, starting_point_moving_average)
    plt.stem(list(range(starting_point_result_20, starting_point_result_20 + len(result_20))), result_20)
    plt.title('Result of the convolution with 20-point moving average')
    plt.savefig('moving_average_20_result.png')
    plt.show()
