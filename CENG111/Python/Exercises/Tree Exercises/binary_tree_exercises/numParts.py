from binarytreefunctions import *

def numParts(n):
    if n == 1:
        return [1]
    if n % 2 == 0: # even
    	return [n, numParts(n//2), numParts(n//2)]
    else: # odd
        return [n, numParts((n-1)//2+1), numParts((n-1)//2)]