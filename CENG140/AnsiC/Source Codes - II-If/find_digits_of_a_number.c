#include <iostream>
int main()
{
    using namespace std;
    int num, rem, sum=0; //Declaring variables    
    
      printf("Enter a number :  ");
      scanf("%d", &num); 
      
    //cin>>num;
    //Loop to calculate the sum of the digits of the given number.
    while(num!=0)
    {
        rem=num%10;
        cout << rem << endl;
        num=num/10;
        sum=sum+rem;
    }
     printf("Sum of the digits is %d \n", sum);     
    system("pause");
}
