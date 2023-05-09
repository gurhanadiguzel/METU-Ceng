def the3N1P(n):
    count = 1
    while n != 1:
        if n % 2 == 0: # even
            n = n / 2
        else: # odd
            n = 3*n + 1
        count += 1
    return count

def max3N1P(n):
    max_number = 0 # the number that produces the longest sequence
    max_length = 0 # the length of the longest sequence
    for i in range(1, n):
        length = the3N1P(i)
        if length > max_length:
            max_length = length
            max_number = i
    return (max_number, max_length)
