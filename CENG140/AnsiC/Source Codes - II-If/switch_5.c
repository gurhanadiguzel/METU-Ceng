#include<stdio.h>
int main( void )
{    
    
    int a;
    a=3;
    //a=5;
    switch(a) {
    case 2: printf("i");
    break;
    case 3: printf("ii");
    case 4: printf("zz");
    break;
    default: printf("iii");
    }

	system("pause");

}
