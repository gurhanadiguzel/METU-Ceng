def palindromes(n):
    numbers = []
    for i in range(n):
        # numbers are converted to str to easily get the reverse
        base2 = bin(i)[2:]
        base10 = str(i)
        if base2 == base2[::-1] and base10 == base10[::-1]:
            numbers.append(i)
    return numbers
