# Write a function named reverse_lists that takes a nested list as an argument and returns the reverse of the list and all the lists inside it. 

def reverse_list(lst):
    if type(lst) != list:
        return lst
    elif len(lst) == 0:
        return []
    else:
        return [reverse_list(lst[-1])] + reverse_list(lst[:-1])

# OR
def reverse_list2(lst):
    if len(lst) == 0:
        return []
    elif type(lst[-1]) == list:
        return [reverse_list2(lst[-1])] + reverse_list2(lst[:-1])
    else:
        return [lst[-1]] + reverse_list2(lst[:-1])
