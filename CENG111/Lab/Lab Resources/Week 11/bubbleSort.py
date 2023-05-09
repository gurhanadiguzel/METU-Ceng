# define function bubleSort which has one argument an unsorted list of integers,
# and returns sorted list.
 
def bubbleSort(L):
    swapped = True
    while swapped:
        swapped = False
        for i in range (len(L) - 1):
            if L[i] > L[i+1]:
                L[i], L[i+1] = L[i+1], L[i]
                swapped = True
    return L
 
print (bubbleSort([1, 4, 2, 6, 3, 2, 19, 7]))