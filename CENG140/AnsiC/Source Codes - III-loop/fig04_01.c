/* Fig. 4.1: fig04_01.c
   Counter-controlled repetition */
#include <stdio.h>

/* function main begins program execution */
int main( void )
{
   int counter = 1; /* initialization */
   
   while ( counter <= 10 ) { /* repetition condition */
  // while ( 1 ) { /* repetition condition */
      printf ( "%d\n", counter ); /* display counter */
      counter++; /* increment */ 
   } /* end while */
  system("pause");
  return 0; /* indicate program ended successfully */
} /* end function main */


