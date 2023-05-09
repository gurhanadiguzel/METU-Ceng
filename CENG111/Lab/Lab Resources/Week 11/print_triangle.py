# Write a function named triangle which takes an integer n and prints '*'' characters to the screen such that:
# the resulting shape will be triangle consisting of n rows of '*'s and 
# at the i'th row there will be 2n-1 number of characters at total where 
#     2i-1 of them are '*'s in the center of the row and
#     The rest of them is spaces.

def triangle(h):
   for i in range(h):
       for j in range(h-i-1):
           print (' ', end="")
       for j in range(2*i+1):
           print ('*', end="")
       for j in range(h-i-1):
           print (' ', end="")
       print ('')

print(triangle(5))


'''

e.g. triangle(5) gives the following:
        *         
      * * *       
    * * * * *     
  * * * * * * *   
* * * * * * * * *

'''