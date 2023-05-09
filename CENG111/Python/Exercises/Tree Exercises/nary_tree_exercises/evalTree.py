from narytreefunctions import *

def evaltree(tree):
    if is_leaf(tree):
        return datum(tree)
    if datum(tree) == 'a':
        for child in children(tree):
            if not evaltree(child):
                return False
        return True
    if datum(tree) == 'o':
        for child in children(tree):
            if evaltree(child):
                return True
        return False
    if datum(tree) == 'n':
        return not evaltree(tree[1])