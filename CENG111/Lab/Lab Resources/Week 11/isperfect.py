# define a function called isperfect which takes an integer and returns True
# if the number is perfect, False otherwise.
# A number n is perfect if it is equal to the sum of its proper divisors.
 
def isperfect(n):
    total = 0
    for i in range(1, n):    
        if n % i == 0:
            total = total + i
    return total == n
 
print (isperfect(6))
print (isperfect(10))
print (isperfect(28))