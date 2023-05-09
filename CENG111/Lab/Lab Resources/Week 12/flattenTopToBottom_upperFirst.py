# QUEUE EXAMPLE

# In the labs you have seen this question either with the name FlattenTopToBottom() or upperFirst().
# It asks the following:
# It flattens the list according to the depths of the elements.
# It returns a list such that the elements in the first depth come first, and 
# the elements in the second depth come next, and the elements in the third depth come
# the next, and so on.

def upper_first(lst):
    flat_list = []
    queue = lst
    while(queue):
        first = queue.pop(0) # dequeue
        if ( type(first) == list ):
            queue += first # enqueue
        else:
            flat_list += [first]
    return flat_list

print(upper_first([1, 2, [3, [4, 5], 6], 7, [8]]))
#returns: [1, 2, 7, 3, 6, 8, 4, 5]