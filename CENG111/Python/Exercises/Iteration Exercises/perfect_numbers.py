def sumofdivisors(n):
    total = 0
    for i in range(1, n):
        if n % i == 0:
            total = total + i
    return total

def perfect_numbers(n):
    numbers = ([], [], [])
    for i in range(1, n):
        sum_divisors = sumofdivisors(i)
        if sum_divisors == i:
            numbers[0].append(i)
        elif sum_divisors > i:
            numbers[1].append(i)
        else:
            numbers[2].append(i)
    return numbers
