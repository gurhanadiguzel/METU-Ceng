from binarytreefunctions import *

def path_has_sum(tree, val):
    if is_empty(tree):
        return val == 0
    if isleaf(tree):
        return val == datum(tree)
    leftsum = path_has_sum(left_child(tree), val) or path_has_sum(left_child(tree), val-datum(tree))
    if leftsum:
        return True
    return path_has_sum(right_child(tree), val) or path_has_sum(right_child(tree), val-datum(tree))
