# Define a function named "inorder" which traverses a binary tree in-order.
# examples:
# >>> inorder([1, [2, [], []], [3, [], []]])
# [2, 1, 3]
# >>> inorder([1, [2, [3, [], []], [4, [], []]], [5, [6, [], []], [7, [], []]]])
# [3, 2, 4, 1, 6, 5, 7]
# >>> inorder([1, [2, [], []], [3, [4, [], []], [5, [], []]]])
# [2, 1, 4, 3, 5]
 


from binarytreefunctions import *
 
def inorder(tree):
    if is_empty(tree):
        return []
    elif isleaf(tree):
        return [datum(tree)]
    else:
        return inorder(left_child(tree)) + [datum(tree)] + inorder(right_child(tree))