def histogram(numbers, bin):
    bins = [[] for i in range(bin)]
    max_number = max(numbers)+1
    min_number = min(numbers)
    factor = float(bin) / (max_number - min_number)
    for number in numbers:
        index = int(factor*(number-min_number))
        bins[index].append(number)
    return bins
