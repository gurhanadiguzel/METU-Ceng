#include "stdio.h"
#include "stdlib.h"
#include "lab3.h"

int main()
{
    int data[5] = {1, 3, 4, 2, 5};
    Node* head = create_list(data, 5);
    /* You can call your functions here */
    print_list(head);
    return 0;
}