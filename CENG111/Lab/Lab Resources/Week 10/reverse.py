# Write a recursive function reverse that returns the reverse of a list.

def reverse(arg):
    if len(arg) == 1:
        return arg
    else:
        return [arg[-1]] + reverse(arg[:-1])
