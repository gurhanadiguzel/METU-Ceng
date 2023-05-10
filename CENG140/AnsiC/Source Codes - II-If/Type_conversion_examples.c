#include <stdio.h>
#include <stdlib.h>// for type conversions


int main( void )
{     
  float a = 5.75;	 int b = a;	  
  printf("Value of int b : %d\n", b );  
  printf("Value of double a : %f\n", a ); 
  
  printf( "Integer division : \%d \n", (3/2) );
  printf( "Float result : \%f \n", (float) 3/2 ); 

  printf( "Sample expression result : \%f \n", (36/(4 * 2) * 2 * 2 - 20) ); 

  printf( "Welcome to \%d \n", (36/(4 * 2) * 2 * 2 - 20) );   
  printf("%5.2f\n", -99.888);
       
  char c ='A';  int x = (int)c;
  printf("char value of x is : %c\n", x );
  printf("integer value of x is : %d\n", x );
        
  x=7;  int y;  y=5;  float z;  z=x/y;
  printf("float value of z1  is : %f\n", z);  
    
  x=7;   y=5;    z = (float)x/y;	
  printf("float value of z2  is : %f\n", z);    

  int sum = 17, count = 5; 
  double mean = (double) sum / count; 
  printf("Value of mean 1  : %f\n", mean );

  int i = 17;   c = 'c'; // ascii value of 'c'  is 99 
  sum = i + c; 
  printf("Value of sum : %d\n", sum ); 

  int aa; double bb; printf("%d %.2f", aa=5+3/2, bb=5+3/2);

  system("pause");
} /* end function main */
