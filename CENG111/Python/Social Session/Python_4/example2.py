# EXAMPLE-2

# Write a function named puzzle() which takes 2 argument: an nxm box which includes a letter in each pixel of it (i.e. box[i][j] includes a letter for all i and j), and a string. Your function will search the string in the box by looking at the box from left to right (horizontally) and from up to down (vertically), and will return the initial locations of the string.

# SPECIFICATIONS

# Each nxm box will be given as a list of n elements representing rows, where each of n elements(rows) is also a list consisting of m elements representing the columns.
# e.g. p e n
#      e x b 
#      n a n
# The box above will be represented as [['p', 'e', 'n'], ['e', 'x', 'b'], ['n', 'a', 'n']]
# Your output will be a list where each element is also an another list L such that L will include the location of the first letter of the word (a tuple (i,j) where i is the row id and j is the column id), and one of the characters '-' or '|' to say that whether the word exists horizontally or vertically, respectively. For example, if I'm looking for the word 'pen' in the box given above, then my function must return the following: [[(0,0), '-'], [(0,0), '|']]
# The ordering is important. While searching the word you will first look for the horizontal occurences and after finding all of the horizontal ones, you will look for the vertical occurences. If there are more than 1 horizontal occurence, then the one whose row id is lower than the others must come first (if row ids are equal, apply the same rule with respect to column ids). If there are more than 1 vertical occurence, then the one whose column id is lower than the others must come first (if column ids are equal, apply the same rule with respect to row ids).
# Note that a row or a column may include more than 1 occurence of the string

# You must not import any modules.
# You may use helper functions if you need.
# You must not print anything.
# No erroneous inputs will be tested.
# You may use both recursion and iteration.
# Using global variable is FORBIDDEN.

# HINTS
# You can use .index() or .find() functions to search the word. However you should convert the lists to strings to be able to use those functions.
# You can also use .join() function to convert a list to string, but it is not very necessary.

# Examine the following examples: 

# e.g.
# For the box whose visualization is given above:
# >>> puzzle([['p', 'e', 'n'], ['e', 'x', 'b'], ['n', 'a', 'n']], 'pen')
# [[(0, 0), '-'], [(0, 0), '|']]

# e.g.
# Here is the visualization of a sample box:

# m c a t d x
# b d o g o h
# i o f g g k
# r g o d o g
# d q c a t g

# >>> puzzle([['m', 'c', 'a', 't', 'd', 'x'], ['b', 'd', 'o', 'g', 'o', 'h'], ['i', 'o', 'f', 'g', 'g', 'k'], ['r', 'g', 'o', 'd', 'o', 'g'], ['d', 'q', 'c', 'a', 't', 'g']], 'dog')
# [[(1, 1), '-'], [(3, 3), '-'], [(1, 1), '|'], [(0, 4), '|']]

# e.g.
# Here is the visualization of a sample box:

# y e s n
# y s y o
# n y e s
# o s s n
# o o n o

# >>> puzzle([['y', 'e', 's', 'n'], ['y', 's', 'y', 'o'], ['n', 'y', 'e', 's'], ['o', 's', 's', 'n'], ['o', 'o', 'n', 'o']], 'yes')
# [[(0, 0), '-'], [(2, 1), '-'], [(1, 2), '|']]

# SOLUTION by using both recursion and loop
def puzzle(box, word):
	result, boxRows, boxColumns = [], [], []
	row_id = 0
	for row in box:
		row_in_str = ""
		j = 0
		for letter in row:
			if row_id == 0:
				boxColumns.append("")
			boxColumns[j] = boxColumns[j] + letter
			j = j + 1
			row_in_str = row_in_str + letter
		boxRows.append(row_in_str)
		row_id = row_id + 1
	i = 0
	for row in boxRows:
		result = result + helper(row, word, i, '-')
		i = i + 1
	i = 0
	for column in boxColumns:
		result = result + helper(column, word, i, '|')
		i = i + 1
	return result

def helper(line, word, i, sign):
	ind = line.find(word)
	if ind < 0:
		return []
	if sign == '-':
		return [[(i, ind), '-']] + helper(line[ind+1:], word, i, sign)
	else:
		return [[(ind, i), '|']] + helper(line[ind+1:], word, i, sign)
        