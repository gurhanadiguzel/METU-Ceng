#Define a function findNumberIndices that returns list of indices of numbers in list L.
def findNumberIndices(L):
    result = []
    i = 0
    while i < len(L):
        if (type(L[i]) != int) and (type(L[i]) != float):
            i = i + 1
            continue
        result.append(i)
        i = i + 1
    return result

print(findNumberIndices([1, 'a', 3, 'b', 3.2]))