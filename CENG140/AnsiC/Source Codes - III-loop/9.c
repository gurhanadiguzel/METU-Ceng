#include <stdio.h>

/* function main begins program execution */



int i = 0, j = 0;

int main( )
{


do {
 printf("%d ",i+j);
  if((i+j)%2) 
  printf("%d ",i+j);
  
   i++;   
   j++; 
} 
while (i<=j<3);
//while ((i<=j)<3);

  system("pause");
   return 0; /* indicate program ended successfully */
} /* end function main */


