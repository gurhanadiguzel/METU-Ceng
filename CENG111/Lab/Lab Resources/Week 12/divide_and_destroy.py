# QUEUE EXAMPLE

# Define a function named "divide_and_destroy" that takes a list of integers where 
# each integer is a power of 2. The idea is to divide the integers in the list by 2 
# in each step and make the list empty. The function should return how many iterations 
# it took to destroy the list.
# The function follows the below steps in each iteration;
# - Take the first element of the list, divide it by 2 with integer division,
# - If the results are bigger than 0, add them to the end of the list; do nothing, otherwise.
# Return the number of iterations to make the list empty.


def divide_and_destroy(queue):
    step = 0
    while(queue):
        #print(queue)   # Take out from the comments and observe the queue
        queue = queue[1:] + ([queue[0]//2] if queue[0]//2 > 0 else []) * 2
        step += 1    
    return step

print(divide_and_destroy([10, 25, 12, 7, 18]))
#returns: 99
