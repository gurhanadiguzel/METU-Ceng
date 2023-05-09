def mazeHelper(lst,currx, curry):
    '''Takes the maze and the current coordinates of the citizen and returns total count of distinct paths'''
    leny = len(lst)
    lenx = len(lst[0])
    if (curry+1 == leny and currx+1 == lenx):
        return 1
    if (curry+1 < leny and currx+1 < lenx):
        if (lst[curry+1][currx] == "o") and (lst[curry][currx+1] == "o"):
            return mazeHelper(lst,currx,curry+1) + mazeHelper(lst,currx+1,curry)
        if (lst[curry+1][currx] == "o"):
            return mazeHelper(lst,currx,curry+1)
        if (lst[curry][currx+1] == "o"):
            return mazeHelper(lst,currx+1,curry)
        return 0
    if (curry+1 < leny):
        if (lst[curry+1][currx] == "o"):
            return mazeHelper(lst,currx,curry+1)
    if (currx+1 < lenx):
        if (lst[curry][currx+1] == "o"):
            return mazeHelper(lst,currx+1,curry)
    return 0

def maze(lst):
    # Returns distinct path counts.
	result = mazeHelper(lst,0,0)
	return result
