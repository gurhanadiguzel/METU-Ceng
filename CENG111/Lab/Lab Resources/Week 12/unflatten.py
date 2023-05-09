# STACK AND QUEUE EXAMPLE

#Write a function named "unflatten" which takes a list as an argument and 
#constructs a nested list.

#The format of the argument list is as follows:
#    An integer item indicates a start of a nested list
#    Non-integer items will be the content of the nested list

#For instance,
#[2, 'a', 3, 'b', 'c', 'd']
#is converted to
#['a', ['b', 'c', 'd']]
#    The first number, 2, indicates that the upper list will contain 2 items. 'a' is the first item of this upper list.
#    The number 3 indicates a start of a new sub-list which contains 3 items.

#>>> unflatten([2, 'x', 'y'])
#['x', 'y']
#>>> unflatten([ 3, "a", "b", 3, "t", "y", "u" ])
#['a', 'b', ['t', 'y', 'u']]
#>>> unflatten([ 4, "a", "b", 3, "c", "d", 2, "x", "y", 2, "w" , 3, "t", "y", "u" ])
#['a', 'b', ['c', 'd', ['x', 'y']], ['w', ['t', 'y', 'u']]]

# SOLUTION-1 - by using stacks
def unflatten(queue):
	stack_of_sizes = []	# hold the size of lists
	stack_of_lists = [] # hold the last list independently from the previous ones
	while queue:
		item = queue.pop(0)
		if type(item) == int:
			# we will deal with the new inner list
			stack_of_sizes.append(item)
			stack_of_lists.append([])
		else:
			# we will add an item to the last list in the stack
			while True:
				stack_of_lists[-1].append(item)
				stack_of_sizes[-1] = stack_of_sizes[-1] - 1
				if stack_of_sizes[-1] == 0:		# close the inner list
					stack_of_sizes.pop()
					item = stack_of_lists.pop()
					if stack_of_lists == []:	# this was the root list, return it
						return item				# else: continue to add this list
				else:							
					break						# continue from the next queue item

#SOLUTION-2 - by using just one precious stack
def unflatten2(lst):
    stk = []  # (n, lst)
    for x in lst:
        if type(x) == int:
                stk.append((x, []))  # initial state
        else:
            n, lst = stk.pop()  # update the state
            lst.append(x)
            n -= 1
            while stk and n == 0: # cascade downwards while 0 elements to append
                next_n, next_lst = stk.pop()
                lst = next_lst + [lst]
                n = next_n - 1
            stk.append((n, lst)) # add to list
    _, lst = stk.pop() # the final built element is left, return
    return lst

#SOLUTION-3 - by using recursion only
def unflatten3(lst):
    (processed, result) = unflatten_helper(lst)
    return result

def unflatten_helper(lst):
    if len(lst) == 0:
            return (0, [])
    elif type(lst[0]) == int:
            newlist = []
            i = 0
            j = 1
            while i < lst[0]:
                    if type(lst[j]) == int:
                        (processed, result) = unflatten_helper(lst[j:])
                        newlist.append(result)
                        j += processed
                    else:
                        newlist.append(lst[j])
                        j += 1
                    i += 1
            return (j, newlist)
    else:
            return None
