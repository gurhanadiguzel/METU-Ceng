#Define factorial(n) function without using recursion
def factorial(n):
    result = 1
    for i in range(2, n+1):
        result = result * i
    return result
