#include <stdio.h>

main()
{
   int sum = 17, count = 5;
   double mean;

   mean =  sum / count;
   printf("Value of mean : %f\n", mean );
   
   mean = (double) sum / count;
   printf("Value of mean : %f\n", mean );
   

   mean =  sum / (double) count;
   printf("Value of mean : %f\n", mean );
   
   
  system("pause");
}
