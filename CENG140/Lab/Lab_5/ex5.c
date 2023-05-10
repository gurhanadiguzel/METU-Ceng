#include <stdio.h>

void capitalize(char *arr)
{
    int i;
    for (i = 0; arr[i] != '\0'; i++)
    {
        if (arr[i] >= 'a' && arr[i] <= 'z')
            arr[i] -= 32;
    }
}
int main()
{
    char arr[] = "may the 4th be with you";
    printf("%s\n", arr);
    capitalize(arr);
    printf("%s\n", arr);
    return 0;
}
