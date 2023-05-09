def clist_decompress(clist):
    """
    Decompress a given C-list, returning all the strings it contains in a list.

    clist:  A C-list (nested list), representing a bunch of strings in a
            special, compressed format. Decompress this!
    """
    prefix, sublists = clist[0], clist[1:]  # one elem is guaranteed
    if len(clist) == 1:
        return [prefix]
    strings = []
    for sublist in sublists:
        suffix_strings = clist_decompress(sublist)
        sub_strings = [prefix + s for s in suffix_strings]
        strings.extend(sub_strings)
    return strings

