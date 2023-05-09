# Write a function named "flatten" that flattens a nested list.
from stacknqueue import *

def flatten(lst):
    stk = CreateStack()
    Push([lst], stk)
    flat = []
    while IsEmptyStack(stk) == False:
        top = Pop(stk)
        print(top)
        if type(top) == list:
            # can also append one by one in a reversed loop
            for i in top[::-1]:
                #print(stk)
                Push(i, stk)
        else:
                flat.append(top)
    return flat

print(flatten([1, 2, [3, [4, 5], 6], 7, [8]]))
