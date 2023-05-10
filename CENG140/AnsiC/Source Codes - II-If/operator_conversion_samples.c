int
main(void)
{
int aa=4, bb=3;
 printf(" result is : %d \n", 12 -2 + bb--/2*3%2*4 - 2 ); 
 printf(" result is : %d \n", 12 -2 + (((bb--/2)*3) %2 ) *4 - 2 );

 printf(" %d \n", 15 % -7 );
   
  int s=13;
  printf("s : %d \n", s%2 + --s);
  s=13;
  printf("s : %d \n", s%2 + s);
 
 printf("1 : %d \n", (int)(1.8 + 1.7 + 1.9) );
 printf("2 : %d \n", ((int)1.8 + (int)1.7 + (int)1.9) ); 
 
 printf("3 : %.2f \n", 1.78); 
           
 printf("%d \n", 22/7);
 printf("%d \n", (int)'7'-(int) '6');
 printf("%d \n", (int)'d'-(int) 'a');
 
 float x=10.5;
 float y=7.2;
 int m=5, n=2;
 
 
 
 printf("%f \n", x/(double)m);
 printf("%f \n", x/m); 
 
  printf("(double)n/m :  %f \n", (double)n/m  ); 
  printf("%f \n", (double)n/(int)m  ); 
  
  printf(" (double)(n/m) + y %f \n", (double)(n/m) + y); 
  
  printf("(double)(n/m) %f \n", (double)(n/m)); 


  
  int a=4, b=3;
  a= 4*3-2+b--/2*3%2*4-2;  // first b--/2  is evaluated
  printf("a: %d \n",a--);
   

     
  printf("%07.4f", 22/7.0);

   system("pause");
   return (0);
}

