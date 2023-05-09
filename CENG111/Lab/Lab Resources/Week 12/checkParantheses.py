# STACK EXAMPLE

# Define a function named "checkParantheses" which takes a string and returns True if 
# none of the parantheses '(', brackets '[' and braces '{' remain open at the end of 
# the string and they are closed in correct order and False otherwise.
#
# examples:
# >>> checkParantheses('There are many online editors for programming languages (including Python).')
# True
# >>> checkParantheses('(5 + 4) * 7 - [(3 + 2) / 2] % {2 * [-1 / (x - t)]}')
# True
# >>> checkParantheses('{a, b, [c, d}, f]')
# False
# >>> checkParantheses('Use a tool )e.g. a spell-checker to spot errors.')
# False
 
def checkParantheses(s):
    stack = []
    chropen = ['(', '[', '{']
    chrclose = [')', ']', '}']
    i = 0
    for c in s:
        if c in chropen:
            stack.append(c)
        elif c in chrclose:
            if len(stack) == 0:
                return False
            elif chrclose.index(c) != chropen.index(stack.pop()):
                return False
    if len(stack) > 0:
        return False
    return True
