#  Write a function named sum_all that sums all the numbers in a nested list. 

def sum_all(lst):
    if len(lst) == 0:
        return 0
    elif type(lst[0]) == list:
        return sum_all(lst[0]) + sum_all(lst[1:])
    else:
        return lst[0] + sum_all(lst[1:])
