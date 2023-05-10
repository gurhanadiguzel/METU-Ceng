#include <stdio.h>

int main()
{
    char a1;
    int b1, c1, d1;
    printf("Gİr:");
    scanf("%s %d %d %d", &a1, &b1, &c1, &d1);
    if (a1 == 'N') 
    {
        c1 = c1 - 1;
        printf("%d %d", b1, c1);
    }
    else if (a1 =='S') 
    {
        c1 = c1 + 1;
        if (c1 < d1)
            printf("%d %d", b1, c1);
        else
            printf("%d %d", b1, c1 - 1);
    }
    else if (a1 == 'W') 
    {
        b1 = b1 - 1;
        printf("%d %d", b1, c1);
    }
    else if (a1 == 'E') 
    {
        b1 = b1 + 1;
        if (b1 < d1)
            printf("%d %d", b1, c1);
        else
            printf("%d %d", b1 - 1, c1);
    }
    return 0;
}