# a compact alternative implementation for isDivisible. Notice that the result of the comparison is equal to 
# returning value.

def isDivisible(x, y):
    if y == 0:
        return 'Error: division by 0'
    else:
        return (x % y) == 0

