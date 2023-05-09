# Write a function named "every" that takes a function and a list as arguments and applies the function to each item in the list and returns a list containing the returning values.

def every(func, lst):
    if len(lst) == 0:
        return []
    return [func(lst[0])] + every(func, lst[1:])
