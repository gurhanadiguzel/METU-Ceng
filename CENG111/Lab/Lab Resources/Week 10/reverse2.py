# Alternative implementation of reverse function with a better base condition (It works with empty list as well. Try to call previous one with empty list).

def reverse(arg):
    if len(arg) == 0:
        return []
    else:
        return [arg[-1]] + reverse(arg[:-1])
