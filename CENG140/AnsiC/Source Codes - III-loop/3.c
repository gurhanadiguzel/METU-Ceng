/* Fig. 4.1: fig04_01.c
   Counter-controlled repetition */
#include <stdio.h>

/* function main begins program execution */
int main( void )
{

int i,j;

for(i=2;i<10;i++) {
 if (i%6==0) break;
 if (i%3==0) continue;

printf("%d",i); }


  system("pause");
   return 0; /* indicate program ended successfully */
} /* end function main */


