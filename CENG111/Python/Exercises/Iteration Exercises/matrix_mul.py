def matrix_mul(A, B):
    result = []
    num_rowsA = len(A) # number of rows of A
    num_colsA = len(A[0]) # number of cols of A
    num_colsB = len(B[0]) # number of cols of B
    for i in range(num_rowsA):
        result.append([])
        for j in range(num_colsB):
            result[i].append(0)
            for k in range(num_colsA):
                result[i][j] += A[i][k] * B[k][j]
    return result

"""
[ 1 , 2 , 3 ]        x       [ 7 , 8 , 9 ]        = [18, 24, 30]
[ 4 , 5 , 6 ]        x       [ 4 , 5 , 6 ]        = [54, 69, 84]
[ 7 , 8 , 9 ]        x       [ 1 , 2 , 3 ]        = [90, 114, 138]
"""