#include <stdio.h>
void func(int *p)
{
    (*p)++;
}

int main()
{
    int x = 7;
    func(&x);
    printf("%d", x);
    return 0;
}
