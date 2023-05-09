#include <stdio.h>
int main()
{
	int *p1, *p2, a[5] = {0, 1, 2, 3, 4};
	p1 = &a[0];
	p2 = a + 3;
	printf("%p\n", a);
	printf("%p\n", p1);
	printf("%p\n", p2);
	printf("%p\n", &a[3]);

	printf("%d\n", a[2]);
	printf("%d\n", *(p1 + 2));
	printf("%d\n", *p2);
	printf("%d\n", *(a + 3));
	return 0;
}
