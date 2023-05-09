# alternative implementation of reverse_lists

def reverse_lists2(lst):
    if len(lst) == 0:
        return []
    elif type(lst[-1]) == list:
        return [reverse_lists2(lst[-1])] + reverse_lists2(lst[:-1])
    else:
        return [lst[-1]] + reverse_lists2(lst[:-1])
