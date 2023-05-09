#include <stdio.h>
/* you can add math library */
#include <math.h>

int main()
{
    int i, j, x, y, index, c;
    float distance, D;
    int xcoors[10];
    int ycoors[10];
    /* declare your variables */
    
    for (i=0; i<10; i++){
        scanf("%d ", &xcoors[i]);
    }
    
    for (i=0; i<10; i++){
        scanf("%d ", &ycoors[i]);
    }
    scanf("%d", &x);
    scanf("%d", &y);
     
    /* implement your loop then */
    distance = sqrt((xcoors[0]-x)*(xcoors[0]-x) + (ycoors[0]-y)* (ycoors[0]-y));
    index = 0.0;
    /*printf("%f, %f\n", distance , index);*/
    for (j= 1; j<10; j++){
        D = sqrt((xcoors[j]-x)*(xcoors[j]-x) + (ycoors[j]-y)*(ycoors[j]-y));
        printf("%d, %f\n", j, D);
        if (D < distance){
            distance = D;
            index = j;
        }
    }

    /* print the result */
    
    printf("P = (%d,%d), nearest point index = %d, distance = %f", x, y, index, distance);

    return 0;
}