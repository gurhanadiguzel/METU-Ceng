# Define a function named "append_depths" which takes a nested list as an argument and 
# returns a new nested list having the same structure but all the items of the list are 
# converted into a tuple which contains the the depth of the item.

#>>> append_depths([1, 2, [1, [2, 3, [1]], 1], 0, 1, 2])
#[(1, 0), (2, 0), [(1, 1), [(2, 2), (3, 2), [(1, 3)]], (1, 1)], (0, 0), (1, 0), (2, 0)]
#>>> append_depths([1, [2, [3, [4, [5, 6], 7]], 8], 9, 10])
#[(1, 0), [(2, 1), [(3, 2), [(4, 3), [(5, 4), (6, 4)], (7, 3)]], (8, 1)], (9, 0), (10, 0)]
#[1,2,3, [], 4,5]	unflatten

from stacknqueue import *

# SOLUTION-1 with stack

def append_depths1(lst):
	result = []
	stack = CreateStack()
	Push((lst, 0, result), stack) # holds (lst, depth, into_which_list_placed) such tuples, the lists and their depths
	
	while IsEmptyStack(stack) == False:
		lst, depth, pointer_lst = Pop(stack)
		for i in range(len(lst)):
			if type(lst[i]) == list:			
				if lst[i+1:]:						# if the rest of the list is not empty
					Push((lst[i+1:], depth, pointer_lst), stack)		# then record the rest of the list
				
				pointer_lst.append([])				# in the next step the nested list elements will be put into this new empty list
				Push((lst[i], depth+1, pointer_lst[-1]), stack)
				break
			else:
				pointer_lst.append((lst[i], depth))
	return result

# SOLUTION-2 with queue

def append_depths2(lst):
	queue = CreateQueue()
	Enqueue((lst, 0), queue) # holds (lst, depth) such tuples, the lists and their depths

	while IsEmptyQueue(queue) == False:
		tpl = Dequeue(queue)	#tpl[0] is a list, tpl[1]
		print(tpl)
		
		for i in range(len(tpl[0])):
			if type(tpl[0][i]) == list: 
				Enqueue((tpl[0][i], tpl[1]+1), queue)
				print(queue)
			else:
				tpl[0][i] = (tpl[0][i], tpl[1])	

	return lst

# SOLUTION-3 neither queue nor stack, just recursion
		
def append_depths(lst):
    return append_depths_helper(lst, 0)

def append_depths_helper(lst, depth):
    newlist = []
    for item in lst:
        if type(item) == list:
            newlist.append(append_depths_helper(item, depth+1))
        else:
            newlist.append((item, depth))
    return newlist

print(append_depths1([1, [2, [3, [4, [5, 6], 7]], 8], 9, 10]))
print(append_depths2([1, [2, [3, [4, [5, 6], 7]], 8], 9, 10]))
print(append_depths([1, [2, [3, [4, [5, 6], 7]], 8], 9, 10]))