def nfilter_leq(threshold, nlist):
    """
    Filter out all the values > threshold in the given nested list,
    keeping only values <= threshold. The result should not contain
    any nested empty list, but the result itself can be [].

    threshold:  An integer. The filtering threshold.
    nlist:      A nested list of integers. Return a new, filtered
                nested list without modifying the input one.
    """
    if type(nlist) == list: 
        if nlist:
            filtered_first = nfilter_leq(threshold, nlist[0])
            filtered_rest = nfilter_leq(threshold, nlist[1:])
            if filtered_first == []: # get rid of the first element
                return filtered_rest 
            return [filtered_first] + filtered_rest
    elif nlist <= threshold:
        return nlist
    return []  # either an empty list or value > threshold, to be removed
