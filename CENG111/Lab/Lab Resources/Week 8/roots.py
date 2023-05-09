# Write a function named "roots" which returns the roots of a quadratic equation as a tuple. 
# The discriminant is guaranteed to be greater than 0. The function takes three floating 
# point arguments a, b, c which are the constants in the equation: a*x^2 + b*x + c = 0
import math

def roots(a, b, c):
    root1 = (-b + math.sqrt(b*b - 4*a*c)) / (2*a)
    root2 = (-b - math.sqrt(b*b - 4*a*c)) / (2*a)
    return (root1, root2)

print(roots(1,4,4))
