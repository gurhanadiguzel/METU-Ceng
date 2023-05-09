from binarytreefunctions import *

def build(tree):
    if len(tree) == 1:
        return datum(tree)
    if datum(tree) == 'string':
        return build(left_child(tree)) + build(right_child(tree))
    else: # 'list'
        return [build(left_child(tree))] + [build(right_child(tree))]