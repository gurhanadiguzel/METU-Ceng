# alternative implementation of roots function with a helper defined in global scope.
import math
def discriminant(a, b, c):
    return math.sqrt(b*b - 4*a*c)
 
def roots(a, b, c):
    root1 = (-b + discriminant(a, b, c)) / (2*a)
    root2 = (-b - discriminant(a, b, c)) / (2*a)
    return (root1, root2)
