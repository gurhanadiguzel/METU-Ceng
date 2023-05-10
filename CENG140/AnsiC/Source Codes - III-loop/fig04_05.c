/* Fig. 4.5: fig04_05.c  
   Summation with for */
#include <stdio.h>

/* function main begins program execution */
int main( void )
{
   int sum = 0; /* initialize sum */
   int number; /* number to be added to sum */

   for ( number = 2; number <= 100; number += 2 ) {
      sum += number; /* add number to sum */      
   } /* end for */

   printf( "Sum is %d\n", sum ); /* output sum */
   system("pause");
    
   return 0; /* indicate program ended successfully */
} /* end function main */


