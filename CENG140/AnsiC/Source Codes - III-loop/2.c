/* Fig. 4.1: fig04_01.c
   Counter-controlled repetition */
#include <stdio.h>

/* function main begins program execution */
int main( void )
{


int k=456;
float t=0;
while(k/100>4){
t=t+k/100;
k=k-100;
}
printf("%f",t);



  system("pause");
   return 0; /* indicate program ended successfully */
} /* end function main */


