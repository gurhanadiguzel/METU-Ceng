from narytreefunctions import *

def max_sum(tree):
    if tree == []:
        return 0
    if is_leaf(tree):
        return datum(tree)
    maximum = -1
    for child in children(tree):
        sum = max_sum(child)
        if sum > maximum:
            maximum = sum
    return maximum + datum(tree)
