from binarytreefunctions import *

def increasing_path(tree):
    if is_empty(tree):
        return True
    if isleaf(tree):
        return True
    if not is_empty(left_child(tree)):
        if datum(tree) <= datum(left_child(tree)):
            return increasing_path(left_child(tree))
    if not is_empty(right_child(tree)):
        if datum(tree) <= datum(right_child(tree)):
            return increasing_path(right_child(tree))
    return False