# Define a function named "sum_binary_tree" which sums all the numbers in a given binary tree.
# examples:
# >>> sum_binary_tree([1, [2, [3, [], []], [4, [], []]], [5, [6, [], []], [7, [], []]]])
# 28
 
def sum_binary_tree(tree):
    if len(tree) == 0:
        return 0
    else:
        return tree[0] + \
            sum_binary_tree(tree[1]) + \
            sum_binary_tree(tree[2])
 
 # Using binarytreefunctions module:
from binarytreefunctions import *
 
def sum_binary_tree2(tree):
    if is_empty(tree):
        return 0
    else:
        return datum(tree) + \
            sum_binary_tree2(left_child(tree)) + \
            sum_binary_tree2(right_child(tree))


print(sum_binary_tree2([1, [2, [3, [], []], [4, [], []]], [5, [6, [], []], [7, [], []]]]))