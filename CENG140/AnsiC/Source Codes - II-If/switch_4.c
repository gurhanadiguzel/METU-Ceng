#include<stdio.h>
int main( void )
{    
    int n=0;
    
switch (n++) {
case 0: n += 1;
case 1: n += 2;
case 2: n += 3;
default: printf("--");}

	printf("%d", n);
	system("pause");

}
