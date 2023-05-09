from binarytreefunctions import *

def isbinary(tree):
    if is_empty(tree):
        return True
    if 1 < len(tree) <= 3:
        return isbinary(left_child(tree)) and isbinary(right_child(tree))
    return False
