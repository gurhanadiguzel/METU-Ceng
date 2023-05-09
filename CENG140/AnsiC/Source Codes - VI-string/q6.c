
#include <stdio.h>

int main( void )
{ 

char st1[ ]="can you hear the voice?";
char st2[ ]="we must call the police!";
strcpy(st2+8,st1+8);
if(strncmp(st1+7,st2+7,8)==0) printf("%s",st2);
else printf("%s",st1);

   system("pause");
   return 0; /* indicates successful termination */
} /* end main */

