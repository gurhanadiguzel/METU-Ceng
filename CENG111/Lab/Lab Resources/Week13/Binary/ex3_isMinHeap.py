# Write a function named "isMinHeap" which will take a binary tree as argument and
# return True if the tree satisfies the heap property and False otherwise.
#
# examples:
# >>> isMinHeap([1, [], []])
# True
# >>> isMinHeap([1, [2, [], []], [3, [], []]])
# True
# >>> isMinHeap([5, [2, [], []], [3, [], []]])
# False
# >>> isMinHeap([1, [2, [], []], [3, [-1, [], []], [5, [], []]]])
# False
 
from binarytreefunctions import *
def isMinHeap(tree):
    if isleaf(tree):
        return True
    elif leftchild(tree) and (datum(tree) > datum(left_child(tree))):
        return False
    elif rightchild(tree) and (datum(tree) > datum(right_child(tree))):
        return False
    else:
        return isMinHeap(left_child(tree)) and \
                isMinHeap(right_child(tree))