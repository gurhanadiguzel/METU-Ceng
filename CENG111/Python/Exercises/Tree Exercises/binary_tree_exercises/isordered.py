from binarytreefunctions import *

def isordered(tree):
    if is_empty(tree) or isleaf(tree):
        return True
    if datum(left_child(tree)) < datum(tree) < datum(right_child(tree)):
        return isordered(left_child(tree)) and isordered(right_child(tree))
    else:
        return False