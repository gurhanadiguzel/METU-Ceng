# Write a recursive function named "append_element" which takes two arguments. The first argument is a Python value and the second element is a list of nested lists. The function should append the first argument to each nested list in the second argument.

def append_element(e, lst):
    if not lst:             # notice that the empty list corresponds to False
        return []
    else:
        return [lst[0] + [e]] + append_element(e, lst[1:])
