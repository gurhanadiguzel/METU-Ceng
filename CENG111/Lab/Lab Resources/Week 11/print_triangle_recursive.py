# Write a function named triangle which takes an integer n and prints '*'' characters to the screen such that:
# the resulting shape will be triangle consisting of n rows of '*'s and 
# at the i'th row there will be 2n-1 number of characters at total where 
#     2i-1 of them are '*'s in the center of the row and
#     The rest of them is spaces.

def do_n_times(f, n):
    if n > 0:
        f()
        do_n_times(f, n-1)

def print_star():
    print('*', end='')

def print_space():
    print(' ', end='')

def print_triangle_helper(height, current_row):
    if current_row < height:
        do_n_times(print_space, height-current_row-1)
        do_n_times(print_star, current_row*2+1)
        do_n_times(print_space, height-current_row-1)
        print('')
        print_triangle_helper(height, current_row+1)

def print_triangle_recursive(height):
    print_triangle_helper(height, 0)
