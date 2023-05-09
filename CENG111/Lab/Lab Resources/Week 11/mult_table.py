# Write a function which prints the multiplication table from 1 to n (including n).
def mult_table(n):
	for i in range(1,n+1):
	    for j in range(1,n+1):
	        print (i, "x", j, "=", i*j)
print(mult_table(5))