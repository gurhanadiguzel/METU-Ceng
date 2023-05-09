from narytreefunctions import *

def prepend(item, lst):
    if lst == []:
        return []
    return [[item] + lst[0]] + prepend(item, lst[1:])

def paths(tree):
    if is_leaf(tree):
        return [[datum(tree)]]
    path_list = []
    for child in children(tree):
       path_list.extend(prepend(datum(tree), paths(child)))
    return path_list