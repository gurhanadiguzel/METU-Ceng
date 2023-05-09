def the3N1P(n):
    count = 1
    while n != 1:
        if n % 2 == 0: # even
            n = n / 2
        else: # odd
            n = 3*n + 1
        count += 1
    return count
