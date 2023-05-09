from narytreefunctions import *

def checkMul(tree):
    if is_leaf(tree):
        return True
    mul = 1
    for child in children(tree):
        mul *= datum(child)
    if mul != datum(tree):
        return False
    for child in children(tree):
        if not checkMul(child):
            return False
    return True