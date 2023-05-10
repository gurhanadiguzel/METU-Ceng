#include <stdio.h>

int main( void )
{
   int n[3][2][2]={0,1,2,3,4,5,6,7,8,9,10,11};        
   int k[2][2]={0,1,2,3};
   
   printf( "n[3][2][2] : %d \n", n[1][1][1]);
   printf( "k[2][2]    : %d \n",  k[1][1]);
   system("pause");
   return 0; /* indicates successful termination */
} /* end main */
