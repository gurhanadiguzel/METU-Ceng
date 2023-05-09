from narytreefunctions import *

def isSubTree(tree1, tree2):
    if is_leaf(tree1):
        return isleaf(tree2)
    if is_leaf(tree2):
        return tree1 == tree2
    if tree1 == tree2:
        return True
    for child in children(tree2):
        if isSubTree(tree1, child):
            return True
    return False