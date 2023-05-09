from binarytreefunctions import *

def maxDepth(tree):
    if is_empty(tree):
        return 0
    depth1 = maxDepth(left_child(tree))
    depth2 = maxDepth(right_child(tree))
    return max(depth1, depth2) + 1
