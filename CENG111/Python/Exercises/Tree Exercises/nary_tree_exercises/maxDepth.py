from narytreefunctions import *

def maxDepth(tree):
    if is_leaf(tree):
        return 1
    maximum = 0
    for child in children(tree):
        depth = maxDepth(child)
        if depth > maximum:
            maximum = depth
    return maximum + 1