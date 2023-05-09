from binarytreefunctions import *

def checkMul(tree):
    if is_empty(tree) or isleaf(tree):
        return True
    if (datum(left_child(tree)) * datum(right_child(tree))) == datum(tree):
        return checkMul(left_child(tree)) and checkMul(right_child(tree))
    else:
        return False