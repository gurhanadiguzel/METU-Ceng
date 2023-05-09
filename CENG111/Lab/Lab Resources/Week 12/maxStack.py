# STACK EXAMPLE

# You have an empty stack and you will be given N queries. Each query has one
# of the 3 types:
#
# 1 x      : Push element x to stack
# 2        : Delete the element on top of the stack
# 3        : Print the maximum element in the stack
#
# Constraints:
# 1 <= N <= 10^5
# 1 <= x <= 10^9
#
#
# Note: You are expected to print the maximum element in constant time.
# Note2: Write a script not a function.

n = int(input())
stk = []
max_stk = [-1]
for i in range(n):
    inp = input().split(' ')
    op = int(inp[0])
    if op == 1:
        num = int(inp[1])
        stk.append(num)
        if num >= max_stk[len(max_stk)-1]:
            max_stk.append(num)
    elif op == 2:
        num = stk.pop()
        if num == max_stk[len(max_stk)-1]:
            max_stk.pop()
    elif op == 3:
        print(max_stk[len(max_stk)-1])
