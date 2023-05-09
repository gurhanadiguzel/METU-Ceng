# EXAMPLE-1

# Write a function named "minDepth" which takes a nested list and an element as the arguments. The function must return the minimum depth where the element occurs. If the element is not found in the nested list, the function must return -1.

# HINT: YOU CAN USE MIN() FUNCTION

# SPECIFICATIONS
# You must not import any modules.
# You may use helper functions if you need.
# You must not print anything.
# No erroneous inputs will be tested.
# You may use both recursion and iteration.
# Using global variable is FORBIDDEN.

# >>> minDepth([1,2,3], 1)
# 0
# >>> minDepth([1,2,[3,2]], 2)
# 0
# >>> minDepth([1,7,[3,2]], 2)
# 1
# >>> minDepth([1,7,[3,2], [[[[8]]]]], 8)
# 4
# >>> minDepth([1,7,[3,2,8], [[[[8]]]]], 8)
# 1
# >>> minDepth([1,7,[3,2,8], [[[[8]]]], 8], 8)
# 0

# SOLUTION by using both recursion and iteration
def minDepth(L, element):
    result = minDepthHelper(L, element, 0)
    if result == []:
        return -1
    else:
        return min(result)

def minDepthHelper(L, element, depth):
    result = []
    i = 0
    while i < len(L):
        if type(L[i]) == list:
            result.extend(minDepthHelper(L[i], element, depth+1))
        elif L[i] == element:
            result.append(depth)
        i += 1
    return result