from binarytreefunctions import *

def path_exists(tree, path):
    if len(path) == 0:
        return True
    if is_empty(tree):
        return len(path) == 0
    if datum(tree) == path[0]:
        return path_exists(left_child(tree), path[1:]) or path_exists(right_child(tree), path[1:])
    else:
        return path_exists(left_child(tree), path) or path_exists(right_child(tree), path)
