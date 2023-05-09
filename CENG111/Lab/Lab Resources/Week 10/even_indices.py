# Write a function called "even_indices" that takes a list as its argument and returns a list of the even-numbered indices of the original list.

def even_indices(lst):
    if len(lst) == 0:
        return []
    elif len(lst) % 2 == 0:
        return even_indices(lst[:-1])
    else:
        return even_indices(lst[:-1]) + [lst[-1]]
