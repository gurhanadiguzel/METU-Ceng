
#include <stdio.h>

int main( void )
{ 

char e[10],f[10];
strcpy(e,"abc");
strcpy(f,"abd");
if (strcmp(e,f))
printf("%s\n",e);
else
printf("%s\n",f);
f[3]='x';f[4]='\0';
printf("%s\n",strchr(f,'d'));
printf("%s\n",strstr(f,"d"));

   system("pause");
   return 0; /* indicates successful termination */
} /* end main */

