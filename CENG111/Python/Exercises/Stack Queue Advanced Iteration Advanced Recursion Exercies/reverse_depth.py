# Define a function named "reverse_depth" which takes a nested list as an argument and 
# returns the reversed form of it with top-down manner. That is, the inner an element is 
# in the given list, the outer it will be in the reversed form. 
# For example, if a list is the inner-most list in given nested list, its elements will be 
# the outer-most position in the new list.

# The given list contains only one list in its elements and this list is the last of the 
# given element. The inner lists has the same property with the given main list.

#>>> reverse_depth([1, [2, [3, [4]]]])
#[4, [3, [2, [1]]]]
#>>> reverse_depth([3, 4, 5, [2, [1, [5, 2]]]])
#[5, 2, [1, [2, [3, 4, 5]]]]

# SOLUTION-1 with stacks

from stacknqueue import *

def reverse_depth(lst):
    stack_lists = CreateStack()
    Push(lst, stack_lists)
    stack_by_depth = CreateStack()

    while IsEmptyStack(stack_lists) == False:
        current_lst = Pop(stack_lists)
        same_level_elements = []
        for i in current_lst:
            if type(i) == list:
                Push(i, stack_lists)
                Push(same_level_elements, stack_by_depth)
                break
            else:
                same_level_elements.append(i)
        else:
            if same_level_elements:
                Push(same_level_elements, stack_by_depth)
                
    output_lst = []
    current_level = output_lst
    while IsEmptyStack(stack_by_depth) == False:
        same_level_elements = Pop(stack_by_depth)
        current_level.append(same_level_elements)
        current_level = current_level[-1]

    return output_lst[0]

   
# SOLUTION-2 (not using abstract data types)
def reverse_depth2(l):
    templist = []

    for i in l:
        if type(i) == int:
            templist += [i]
        else:
            templist = reverse_depth_helper(templist, i)

    return templist

def reverse_depth_helper (prev,l):
    templist = []
    for i in l:
        if type(i) == int:
            templist += [i]
        else:
            templist += [prev]
            return reverse_depth_helper(templist, i)
    templist += [prev]
    return templist


print(reverse_depth2([1, [2, [3, [4]]]]))
#[4, [3, [2, [1]]]]
print(reverse_depth([3, 4, 5, [2, [1, [5, 2]]]]))
#[5, 2, [1, [2, [3, 4, 5]]]]