

#include <stdio.h>
 
int main()
{
  int c, n, fact = 1;
 
  printf("Enter a number to calculate it's factorial\n");
  scanf("%d", &n);
 
   for (c = 1; c <= n; c++)
{    fact = fact * c;
  printf("fact %d = \n",  fact);
}
    
  printf("Factorial of %d = %d\n", n, fact);
  
  system("pause");
  return 0;
}
