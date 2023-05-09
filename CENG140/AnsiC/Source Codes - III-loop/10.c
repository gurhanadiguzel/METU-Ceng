#include <stdio.h>

/* function main begins program execution */




int main( )
{


int a=0,b=0,c=0,f,g,h;
scanf("%d%d%d",&f, &g, &h);
for (a=g;a<f;a++)
switch(a) {
case 1: c++;break;
default: c += 2;
}

printf("%d\n",c);



  system("pause");
   return 0; /* indicate program ended successfully */
} /* end function main */


