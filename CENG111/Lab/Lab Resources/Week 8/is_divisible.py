# Write a function named "isDivisible" which takes two numbers, x and y, and returns whether x is divisible by y.

def isDivisible(x, y):
    if (x % y) == 0:
        return True
    else:
        return False


# Correct solution (If y is 0, return 'Error: division by 0')
def isDivisible2(x, y):
    if y == 0:
        return 'Error: division by 0'
    else:
        if (x % y) == 0:
            return True
        else:
            return False

