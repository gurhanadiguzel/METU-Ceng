/* Fig. 4.1: fig04_01.c
   Counter-controlled repetition */
#include <stdio.h>

/* function main begins program execution */
int main( void )
{
int i,j;

for( i=0; i<=2; i++)
for( j=1; j<3; j++)
printf("%d%d",i,j);
printf("%d%d",i,j);

  system("pause");
   return 0; /* indicate program ended successfully */
} /* end function main */


