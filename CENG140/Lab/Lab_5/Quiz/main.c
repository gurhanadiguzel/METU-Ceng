#include<stdio.h>
void update(int *arr[], int length){
    int *a,b, j;
    a = arr[0];
    for(j =0; j<length; j++) {
        b = *arr[j]%length;
        *(arr[j])= *(a+b);
    } 
}

int main(){

int array[5] = {14,8,6,5,12}; /* you can try different arrays */
int *ptrs[5], i;

for(i=0; i < 5; i++) /* DO NOT REMOVE */
    ptrs[i] = array+i;

update(ptrs, 5); /* call your function here */

for(i=0; i < 5; i++) /* DO NOT REMOVE */
    printf("%d ", *ptrs[i]); 

return 0;
}
        
        /*SOLUTİON*/
/*    int* original_array = arr[0];  
        for (i = 0; i< length; i++) {        
            update the address in arr[i] according to value in *arr[i].
            while updating the address, use original_array pointer as your reference point
            and do pointer arithmetic to do assignment.
            
            arr     => pointer to pointer
            arr[i]  => pointer to an element of the original array
            *arr[i] => value of an element of the original array
        
        arr[i] = original_array + *(arr[i]) % length;  
    }
*/