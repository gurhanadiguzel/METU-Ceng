#include<stdio.h>
int main( void )
{
  int a=21, b=9;
  int m= -1;

  if (a>20)
      if (b<10)
        if (a>=30)
          m =4;
        else
          m=0;
      else
        m=1;
  else
     m=2;
     
     printf("%d\n",m);
	
	
	if (0.11) printf("\n It is true when (0.11)");
	
	
	
	int x=6, y=3, A=3, B=5, C=7;
if (x <A && y >B)
if (y >0)
printf("A");
else printf("B");
else if (y>C || x >0)
printf("C");



 a = 4;
if(a == 4)
printf("a1");
else
printf("a2");
printf("a3");
printf("a4"); 


a = 9;
b = 3;
if( !a <= 4 )
b = 5;
a = 1;
printf("a=%d b=%d\n", a, b); 




a = 9;
b = 3;
if( !a <= 4 )
{
b = 5;
a = 1;
}
printf("a=%d b=%d\n", a, b); 



printf("a=%d b=%d\n", !a, !b); 




int z=9;
z=z-4;
if( z<9 || ++z>4 ) z=z+2;
printf(" %d ", z);





	system("pause");
	return 0;
}
