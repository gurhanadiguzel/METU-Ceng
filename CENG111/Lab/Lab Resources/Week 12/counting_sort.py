# Write a function named counting_sort which sorts the given list whose max value is 
# also given in the function agument. It sorts the list in the increasing order.
# It works as follows:
# First, it finds out the number of occurences of each number (from the range 0 to 
# max_value) in the list. Next, it places each occurence in the increasing order 
# into the result list.

# >>> counting_sort([5, 8, 1, 10, 1, 7, 6, 6, 5, 3, 2])
# [1, 1, 2, 3, 5, 5, 6, 6, 7, 8, 10]

def counting_sort(lst, max_value):
    counter = [0] * (max_value + 1)
    for i in lst:
        counter[i] += 1
    print(counter)
    sorted_lst = []
    for i in range(len(counter)):
        while 0 < counter[i]:
            sorted_lst.append(i)
            counter[i] -= 1
    return sorted_lst

print(counting_sort([5, 8, 1, 10, 1, 7, 6, 6, 5, 3, 2],10))