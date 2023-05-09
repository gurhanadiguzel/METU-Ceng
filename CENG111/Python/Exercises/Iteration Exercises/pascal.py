def pascal(n):
    triangle = [[1]]
    for i in range(n-1):
        triangle.append([])
        triangle[i+1].append(1)
        for j in range(i):
            triangle[i+1].append(triangle[i][j] + triangle[i][j+1])
        triangle[i+1].append(1)
    return triangle

print(pascal(5))