#include <stdio.h>

/* define a structure type struct birthday */
/* declare friendBday to be a variable of this type */
struct birthday{
    int day, month, year;
}friendBday;

int main(void){
/* declare myBday to be of type struct birthday
and initialize it */
/* assign myBday to friendBday */
/* access members of friendBday and print */    
    struct birthday myBday= {22, 04, 2001};
    friendBday = myBday;
    printf("%d %d %d\n",friendBday.day, friendBday.month, friendBday.year);
    return 0;
}