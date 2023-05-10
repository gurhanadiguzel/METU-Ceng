
#include <stdio.h>

int main( void )
{ 

char str1[20] = "Hello";
char str2[20] = "World!";
strcat(str1, str2);
printf("%d", strlen(str1));

   system("pause");
   return 0; /* indicates successful termination */
} /* end main */

