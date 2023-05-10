#include <stdio.h>
#include <math.h>

int main() {
	int  sum;
	int i,j;
	sum=0;

	for (i=1; i<=50; i++){
		printf("%d\n", sqrt(i));
		for (j=2; j <= sqrt(i); j++)
			if (i%j == 0)
				break;
		if (j>sqrt(i)){
			sum += i;
			printf("i = %d\n", i);
		}
	}

	printf("sum = %d\n", sum);

	return 0;
}
