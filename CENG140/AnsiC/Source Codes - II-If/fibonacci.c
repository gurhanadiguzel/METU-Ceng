/* Fibonacci Series c language */
/* Displaying Fibonacci sequence up to nth term where n is entered by user. */
#include <stdio.h>
int main()
{
  int count, n, t1=0, t2=1, display=0;
  printf("Enter number of terms: ");
  scanf("%d",&n);
  printf("Fibonacci Series: %d\n%d\n", t1, t2); /* Displaying first two terms */
  count=2;    /* count=2 because first two terms are already displayed. */
  while (count<n)  
  {
      display=t1+t2;
      printf("%d \n",display);
      t1=t2;
      t2=display;
      ++count;
      
  }

  system("pause");
  return 0;
}
