#include <stdio.h>
#include <math.h>
int square(){
    int n;
    scanf("%d", &n);
    int len = 2*n-1;
    int min1,min2,min;
      for (int i=1; i <=len; i++) {
          for (int j=1; j<=len; j++) {
            // min diff btn vertical sides
            min1 = i<=len-i ? i -1 : len-i;
            // min diff btn horizontal sides
            min2 = j<=len-j ? j -1: len-j;
            // min diff btn vertical & horizontal sides
            min = min1<=min2 ? min1 : min2;
            printf("%d ",n-min);
          }
          printf("\n");
      }
    return 0;
}
int palindrome(){
   int f,x,y,z=0;
   scanf("%d", &f);
   x = f;
   while(1<=x){
       y = x%10;
       x /= 10;
       z = 10*z+y;
   }
   if (z == f)
        printf("True");
   else
        printf("False");
   return 0;
   
}

int triangunlar(){
    int x;
    scanf("%d", &x);
	for(int i=1; i<=x; i++)
	{
		for (int j=1; j<=i; j++)
		{
			printf("%d", j);
		}
		printf("\n");
	}
	return 0;	
}

int prime(){
    int num,i,ctr,stno,enno;

    printf("Input starting number of range: ");
    scanf("%d",&stno);
    printf("Input ending number of range : ");
    scanf("%d",&enno);
    printf("The prime numbers between %d and %d are : \n",stno,enno);  
    for(num = stno;num<=enno;num++)
       {
         ctr = 0;
         for(i=2;i<=num/2;i++)
            {
             if(num%i==0){
                 ctr++;
                 break;
             }
        }        
         if(ctr==0 && num!= 1)
             printf("%d ",num);
    }
	printf("\n"); 
	return 0;
}

int sum_series() {
    int x, sum=0, y=1;
    scanf("%d", &x);
    for(int i=1; i<=x; i++){
        sum +=y;
        y = y*10 +1;
    }
    printf("%d", sum);
}


