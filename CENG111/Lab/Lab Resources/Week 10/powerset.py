#Write a recursive function powerset which takes a set as a Python list and returns its powerset. 
#The order of the elements in the returned list is not important.

#from append_element import append_element

def powerset(lst):
	if not lst:
		return [[]]
	else:
		psRemain = powerset(lst[:-1])
		return psRemain + appendElement(lst[-1], psRemain)


print(powerset([1, 2, 3]))