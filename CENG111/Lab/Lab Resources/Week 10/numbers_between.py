# Write a function called "numbers_between" which takes two integers and generates an ordered list of the numbers in between them.

def numbers_between(n, m):
    if n == m:
        return [n]
    else:
        return [n] + numbers_between(n+1,m)

# Correct solution
def numbers_between2(n, m):
    if n > m:
        return []
    elif n == m:
        return [n]
    else:
        return [n] + numbers_between(n+1,m)

