/* ex04_08.c 
   What does this program print? */
#include <stdio.h>

/* function main begins program execution */
int main( void )
{
   int x; 
   int y;
   int i; 
   int j; 

   /* prompt user for input */
   printf( "Enter two integers in the range 1-20: " );
   scanf( "%d%d", &x, &y ); /* read values for x and y */

   for ( i = 1; i <= y; i++ ) { /* count from 1 to y */
      for ( j = 1; j <= x; j++ ) { /* count from 1 to x */
         printf( "A" ); /* output @ */
      } /* end inner for */
      printf( "\n" ); /* begin new line */
   } /* end outer for */

   system("pause");
   return 0; /* indicate program ended successfully */
} /* end function main */


