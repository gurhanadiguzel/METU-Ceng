#include <stdio.h>

/* function main begins program execution */
int main( void )
{

int i=1;
int k=5;
while (i <=10-k)
{ 
  ++i;
  printf("%3d",i);
  k+=2; 
}

  system("pause");
  return 0; /* indicate program ended successfully */
} /* end function main */


