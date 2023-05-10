
#include <stdio.h>

int main( void )
{ 

char s1[] = "Kolay Soru";
char s2[] = "mu acaba";
strcpy(s1,s2);
if(s1 == s2) {
printf(" OK ");
} else {
printf(" NO "); }
if(strcmp(s1,s2) == 0) {
printf(" 0 "); }
if(strcmp(s1,s2) != 0) {
printf(" 1 "); }
printf("\n");

   system("pause");
   return 0; /* indicates successful termination */
} /* end main */

