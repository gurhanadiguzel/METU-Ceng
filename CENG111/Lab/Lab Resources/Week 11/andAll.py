#Define a function andAll which takes a list of boolean expressions and return True if all elements of list are True. Note: assume all elements of L are valid booleans.
def andAll(L):
    for x in L:
        if not x:
            result = False
            break            
    else:
        result = True
    return result
 

print(andAll([2 == 2, 3 < 5, 7 != 8]))
print(andAll([2 == 2, 5 > 6, 'a' == 'a']))