#include <stdio.h>
#include <math.h>
#include <stdio.h>

int main() {
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    switch(c)
    {
        case 1:
            printf("addittion is : %d", a+b);
			break;
        case 2:
            printf("subtraction is : %d", a-b);
			break;
		case 3:
			printf("multiplication is : %d", a*b);
			break;
		case 4:
			printf("division is : %d", a/b);
			break;
		default:
			printf("Try again.");
    }
    return 0;
}  
