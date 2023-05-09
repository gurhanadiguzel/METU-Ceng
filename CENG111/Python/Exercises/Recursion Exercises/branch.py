# Write a recursive function named branch that takes as arguments a list of indices and a nested list structure. It should return the item indexed by the first argument. It works like "[]" operator is applied multiple times to the second list. 

def branch(branches, lst):
    if not branches:
        return lst
    else:
        return branch(branches[1:], lst[branches[0]])
