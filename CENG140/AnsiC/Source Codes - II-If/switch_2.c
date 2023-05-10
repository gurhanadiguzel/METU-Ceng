#include<stdio.h>
int main( void )
{    
    int a = 3;
    
    switch( a - 2 ) {
    case 1: printf("a");
    case 2: printf("aa");
    break;
    case 3: printf("aaa");
    case 4: printf("zz");
    break;
    default: printf("aaaa"); }

	system("pause");

}
