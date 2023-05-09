# Write two functions "even" and "odd" which take an int argument. The function odd should return True if the int is even and False otherwise. The function odd should return True if the int is odd and False otherwise (You cannot use '%' operator in any of the functions you write). This is an example of 'mutual recursion'.

def even(num):
    if n == 0:
        return True
    else:
        return odd(abs(num) - 1)

def odd(num):
    if n == 0:
        return False
    else:
        return even(abs(num) - 1)
