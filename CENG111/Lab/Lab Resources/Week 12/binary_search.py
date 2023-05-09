# Write a function named binary_search_iterative which takes 4 arguments:
# (1) a list, 
# (2) the left and (3) the right indices of the list in between which the list is searched
# (4) the key to be searched
# Binary search divides the ordered list into 2 almost-equal halves at each step and
# continues to search either from the left or from the right half depending on which half
# the key belongs to.

# >>> binary_search_iterative([1, 2, 3, 5, 7, 8, 10, 15, 20, 62, 80], 0, 10, 7)
# 4

def binary_search_iterative(li, left, right, key):
  while True:
    if left > right:
      return -1
    mid = (left + right) // 2
    if li[mid] == key:
      return mid
    if li[mid] > key:
      right = mid - 1
    else:
      left = mid + 1
print(binary_search_iterative([1, 2, 3, 5, 7, 8, 10, 15, 20, 62, 80], 0, 10, 7))