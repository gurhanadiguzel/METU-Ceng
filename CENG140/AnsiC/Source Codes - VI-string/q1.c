
#include <stdio.h>

int main( void )
{ 
char a[]="abc";
char b[]={'a','b','c','\0'};
char c[]={'a','b','c',0};
char d[]={'a','b','c'};
printf("%d %d %d\n",strlen(a),strlen(b),strlen(c));
printf("%d\n",strlen(strcpy(d,"\0")));
printf("%s\n",d);

   system("pause");
   return 0; /* indicates successful termination */
} /* end main */

