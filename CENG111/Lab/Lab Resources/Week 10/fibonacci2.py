# Better implementation of fibonacci function which avoids redundant computations. This is an example of 'tail recursion'.

def fibonacci(n):
	return fibonacci_helper(n, 1, 0)

def fibonacci_helper(n, current, previous):
	if n == 1:
		return current

	elif n > 1:
		return fibonacci_helper(n - 1, previous + current, current)
