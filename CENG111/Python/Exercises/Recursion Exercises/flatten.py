# Write a function named flatten that flattens a nested list. 

def flatten(lst):
    if len(lst) == 0:
        return []
    elif type(lst[0]) == list:
        return flatten(lst[0]) + flatten(lst[1:])
    else:
        return [lst[0]] + flatten(lst[1:])
