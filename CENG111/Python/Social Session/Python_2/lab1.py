# EXAMPLE-4 (Nihil, Lesson-3, Chapter-5)

# Write a function named "process_vector" which performs the following operations on 3-d vectors:
#
#    scalar multiplication
#    magnitude
#    normalization
#
# The first argument is a string specifying the operation: "SM", "M" or "N"
#
#    SM: returns the scalar multiplication of two vectors
#    M: returns magnitude of a vector
#    N: returns the normalized version of a vector
#
# The second argument is a list containing one or two vector(s) depending on the type of the operation. A vector is represented a tuple: (x, y, z). E.g. (2.0, 3.0, 7.0).

def process_vector(operation, vectors):
    if operation == "SM":
        return scalarmulti(vectors[0], vectors[1])
    elif operation == "M":
        return magnitude(vectors[0])
    elif operation == "N": 
        return normalize(vectors[0])

def scalarmulti(v1, v2):
    return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2]

def magnitude(vector):
    return (vector[0]**2 + vector[1]**2 + vector[2]**2)**(0.5)

def normalize(vector):
    length = magnitude(vector)
    return (vector[0]/length, vector[1]/length, vector[2]/length)

print( process_vector("SM", [(3.0, 4.0, 5.0), (2.0, 4.0, 6.0)]) )
print( process_vector("M", [(2.0, 7.0, 8.0)]) )