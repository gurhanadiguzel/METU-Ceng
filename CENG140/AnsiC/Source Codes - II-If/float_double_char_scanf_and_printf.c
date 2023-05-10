#include <stdio.h>              /* printf, scanf definitions */
#define KMS_PER_MILE 1.609      /* conversion constant       */

int
main(void)
{     
    int c;
    printf("Enter an integer \n");
    scanf("%d",&c);  
    printf("Integer is =%d  \n \n",c);
       
    float float1;
    printf("Enter a float: \n");
    scanf("%f",&float1);
    printf("Float is =%f   \n \n",float1);    //%f is used for floats instead of %d            
    
    double db1;
    printf("Enter a double: \n"); //seperate lines
    scanf("%lf",&db1);
    printf("double is : %lf \n" ,db1);
    
    char var1;
    printf("Enter character: \n");
    scanf("%c \n",&var1);     
    printf("Character is %c \n",var1);  
           
    system("pause");
    return (0);
}
/*
Sample Run
Enter the distance in miles> 10.00
That equals 16.090000 kilometers.
*/
