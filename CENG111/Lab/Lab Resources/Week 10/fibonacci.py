# Write a function to compute the Nth number of the fibonacci series.

def fibonacci(n):
    if n <= 2:
        return 1
    return fibonacci(n-1) + fibonacci(n-2)
