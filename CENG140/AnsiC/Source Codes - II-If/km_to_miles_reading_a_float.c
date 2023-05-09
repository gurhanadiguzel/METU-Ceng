// * Converts distance in miles to kilometers.
#include <stdio.h>              /* printf, scanf definitions */
#define KMS_PER_MILE 1.609      /* conversion constant       */

int
main(void)
{
      float miles,  /* input - distance in miles.       */
      // double miles  olursa lf  olarak okunuyor.
      kms;    /* output - distance in kilometers  */      

      /* Get the distance in miles. */
      printf("Enter the distance in miles> ");
      scanf("%f", &miles); 
       
      /* Convert the distance to kilometers. */
      kms = KMS_PER_MILE * miles;

      /* Display the distance in kilometers. */
      printf("That equals %f kilometers.\n", kms);      
      system("pause");
      return (0);
}
/*
Sample Run
Enter the distance in miles> 10.00
That equals 16.090000 kilometers.
*/
