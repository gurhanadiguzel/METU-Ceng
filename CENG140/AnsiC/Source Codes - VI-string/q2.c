
#include <stdio.h>

int main( void )
{ 


char e[10],f[10];
e[0]='a';e[1]='b';e[2]='\0';
strcat(e,"c");
printf("%d\n",strlen(e));
printf("%s\n",e);
strcpy(f,e);
f[2]='d';
printf("%d\n",strlen(f));
printf("%s\n",f);

   system("pause");
   return 0; /* indicates successful termination */
} /* end main */

