/* Fig. 4.1: fig04_01.c
   Counter-controlled repetition */
#include <stdio.h>

/* function main begins program execution */
int main( void )
{

int i, k;
k=5/2;
for (i=3;i<=10; i+=2)
{ ++i;
if(k=3&&i%2)
printf("BBB");
else
printf("AAA");
k++;
}



  system("pause");
   return 0; /* indicate program ended successfully */
} /* end function main */


