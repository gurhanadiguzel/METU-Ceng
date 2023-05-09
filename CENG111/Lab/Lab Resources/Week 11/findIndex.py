#Define a function findIndex that returns the index of the first number in list L. If not found, return -1
def findIndex(L):
    i = 0
    index = -1
    while i < len(L):
        if (type(L[i]) == int) or (type(L[i]) == float):
            index = i
            break
        i = i + 1
    return index


print(findIndex(['a',[],(1,2,3),'b', -5, 111, 'c', 0, [5,5,5]]))