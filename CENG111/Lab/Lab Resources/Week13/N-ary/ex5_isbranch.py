# Write a function named "isbranch" which will take two *n-ary* trees as arguments and
# find if the first tree is a branch of the second tree. The procedure will
# return True if it is a branch and False if it is not. In order to be a branch,
# all nodes until the leaves must be the same and leaves of the first tree
# must be also leaves for the second tree.
# >>> isbranch([1, [2], [3]], [4, [5], [6, [7, [1], [3]], [1, [2], [3]]]])
# True
# >>> isbranch([1, [2], [3]], [4, [5], [6, [7, [1], [3]], [10]]])
# False
# >>> isbranch([1, [2], [3], [4]], [1, [2], [3], [4, [5]]])
# False
# >>> isbranch([1, [2], [3]], [0, [1, [2], [3]], [4], [5]])
# True
 
from narytreefunctions import *
 
def isbranch(tree1, tree2):
    if len(tree2) == 0:
        return False
    elif tree1 == tree2:
        return True
    else:
        for e in children(tree2):
            if isbranch(tree1, e):
                return True
        return False
