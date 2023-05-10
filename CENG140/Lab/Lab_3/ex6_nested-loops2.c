/* Example 6: Find these triplets! */

#include <math.h>
#include <stdio.h>
#define LIMIT 25

int main(void) {

	int a, b, c, c_sqr;

	for (a = 1; a < LIMIT; a++) {
		for(b=1+a; b< LIMIT; b++){
			c = a*a+b*b;
			c_sqr = sqrt(c);
			if (c_sqr*c_sqr==c)
				printf("%d %d %d\n", a, b, c_sqr);
		}
	}
	
	return 0;
}
