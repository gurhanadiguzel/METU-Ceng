def lis(numbers):
    i = 0
    longest = 1
    max_longest = 1
    while i < len(numbers)-1:
        if numbers[i] <= numbers[i+1]:
            longest += 1
        else:
            if longest > max_longest:
                max_longest = longest
            longest = 1
        i += 1
        if longest > max_longest:
            max_longest = longest
    return max_longest
