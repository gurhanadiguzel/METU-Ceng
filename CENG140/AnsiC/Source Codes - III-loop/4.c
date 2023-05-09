/* Fig. 4.1: fig04_01.c
   Counter-controlled repetition */
#include <stdio.h>

/* function main begins program execution */
int main( void )
{

int k=5;
int m=10;
while( k > 0 )
{ if( m%3 )
   printf("%3d", m-- );
else
   printf("%3d", --m);

k -= 2;
}
printf("%3d", k);


  system("pause");
   return 0; /* indicate program ended successfully */
} /* end function main */


