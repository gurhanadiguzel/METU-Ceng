def triplets(n):
    result = []
    for a in range(1, n):
        for b in range(1, n):
            # for each a, b < n, compute c such that a^2 + b^2 = c^2
            lhs = a*a + b*b
            sqrt = lhs ** 0.5
            c = int(sqrt)
            triplet = tuple(sorted([a, b, c]))
            # c should be less than n
            # c should be exactly equal to sqrt(a^2+b^2). e.g. 16.0 == 16 but 16.001 != 16
            # duplicate tuples should be avoided
            if c < n and sqrt == c and triplet not in result:
                result.append(tuple(triplet))
    return result
