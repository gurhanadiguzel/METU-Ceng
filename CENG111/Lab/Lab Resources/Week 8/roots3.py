# alternative implementation of roots function with a helper function defined in local scope.
import math

def roots(a, b, c):
    def discriminant():
        return math.sqrt(b*b - 4*a*c)
    root1 = (-b + discriminant()) / (2*a)
    root2 = (-b - discriminant()) / (2*a)
    return (root1, root2)
