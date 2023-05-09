#include<stdio.h>
int main( void )
{    
    int c;
    int n=0;
switch (c = 1) {
case 1: n = 0;
case 0: n += 1;
case 2: n = n * 2;
}
	printf("%d", n);
	system("pause");

}
