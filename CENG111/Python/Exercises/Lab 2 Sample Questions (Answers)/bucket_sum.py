def calculate(current, pool,b1,b2,b3):
	'''Returns the number of all possible bucket combinations for given information lst.'''
	if current > pool:
		return 0
	if current == pool:
		return 1
	res = calculate(current+b1,pool,b1,b2,b3) + calculate(current+b2,pool,b1,b2,b3)  + calculate(current+b3,pool,b1,b2,b3) 
	return res

def bucket_sum(pool, b1, b2, b3):
	return calculate(0,pool, b1, b2, b3)