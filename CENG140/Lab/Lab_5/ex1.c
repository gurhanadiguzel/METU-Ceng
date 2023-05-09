#include <stdio.h>

int main() {
	int *ptr1, *ptr2,  m = 100, n ;
	
	/*  Store address of m in ptr1  
	    Store address of n in ptr2  */
	ptr1= &m;
	ptr2= &n;
    
	/*  n = m + 3; 
        do the equivalent operations using pointers */
	*ptr2 = *ptr1 +3;

	/*Print the value addresses and the values */    
	printf("ptr1 address: %p ptr2 address: %p \n", (void*)ptr1, (void*)ptr2);
	printf("*ptr1: %d *ptr2: %d\n", *ptr1, *ptr2);
	printf("m: %d, n: %d\n", m,n);
	
	return 0;
}