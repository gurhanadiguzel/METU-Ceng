# alternative implementation for isDivisible function with elif keyword

def isDivisible(x, y):
    if y == 0:
        return 'Error: division by 0'
    elif (x % y) == 0:
        return True
    else:
        return False
