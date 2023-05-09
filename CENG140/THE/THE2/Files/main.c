#include "functions.h"

/*
You will not submit this file, just use for testing your code.
All your implementations should be in functions.c
*/

/*
To compile your code, use "make main"
Then "./main" to run.
If you want to compile again, you need to delete the previous executable.
You may do this by "make clean" or simply "rm main"
*/

int main(){ 

int main(){
    float ***sector_times;
    unsigned int a=0, b=0;
    /*unsigned int *n_drivers1=&a, *n_laps1=&b;    */
    sector_times = create_sector_times(&a,&b);
    printf("%u %u\n",a,b);
    printf("%.2f",sector_times[0][0][2]);
    return 0;
}
int main(){
    unsigned int **CP;
    unsigned int a=0, b=0;
    unsigned int *p_drivers1=&a, *n_races1=&b;    
    CP = create_positions(p_drivers1,n_races1);
    printf("%u %u\n",*p_drivers1,*n_races1);
    printf("%u\n",CP[14][12]);
    return 0;
}

    */
    float ***sector_times, **laptimes;
    unsigned int fastest_lap, **positions;
    unsigned int *n_drivers, *n_laps;
 
    printf("%d %d",*n_drivers,*n_laps);
    sector_times = create_sector_times(n_drivers,n_laps);
   /*
    float ***arr;
    arr=(float***)malloc((*n_drivers)*sizeof(float**));    
    for(i=0;i<*n_drivers;i++){ 
        arr[i]=(float**)malloc((*n_laps)*sizeof(float*));       
        for(j=0;j<*n_laps;j++){
            arr[i][j]=(float*)malloc(n_sector*sizeof(float));                        
            for(k=0;k<n_sector;k++){                
                scanf("%f", &arr[i][j][k]);
            }
        }    
    }
    printf("%.2f",arr[0][0][2]);
    */
    /*
    int **arr2;
    arr2=(int**)malloc((*p_drivers)*sizeof(int*));
    for(i=0;i<*p_drivers;i++){
        arr2[i]=(int*)malloc((*n_races)*sizeof(int));
        for(j=0;j<*n_races;j++){
            scanf("%d",&arr2[i][j]);
        }
    }
    */    
    /*   
    sector_times = create_sector_times(n_drivers,n_laps);
    printf("%.2f\n",sector_times[0][0][0]);
    */
    /*
2 3
22.17 34.85 27.46
20.19 32.48 27.51
23.17 35.10 29.02
25.27 33.65 29.50
24.07 36.47 25.16
19.48 33.17 29.56
    */
    /*
    float sector_times_of_driver[][3]={{22.17,34.85,27.46},{20.19,32.48,27.51},{23.17,35.10,29.02}};
    c= find_driver_fastest_lap(sector_times_of_driver, 3);
    printf("%d\n",c);
    */
    /*
    float arr[6]={10.1,11.1,15.1,12.1,14.1,13.1};
    sorting=selection_sort(arr,6,'D');
    printf("%f",sorting[5]);
    */

    /*  7    
    unsigned int *A, n_drivers=6, n_laps=3;
    float L[][3]={{22.17,34.85,27.46},{20.19,32.48,27.51},{23.17,35.10,29.02},{25.27,33.65,29.50},{24.07,36.47,25.16},{19.48,33.17,29.56}};
    A=find_finishing_positions(L, n_drivers, n_laps);
    printf("A = %u %u %u %u %u %u\n",A[0],A[1],A[2],A[3],A[4],A[5]);
    */
    /* 8
    float lap_times[][3]={{18,21,20},{20,20,22}};
    float *diff;
    diff=find_time_diff(lap_times,2,3,0,1);
    printf("%.f %.f %.f",diff[0],diff[1],diff[2]);
    */
    /* 9
    int i,j,k;
    position_point[10]={25,18,15,12,10,8,6,4,2,1}; 
    unsigned int positions[][4]={{1, 2, 2, 4},{3,1,5,6}};
    unsigned int p_drivers=2, n_races=4;
    unsigned int *r_points,*position_point,sum;
    r_points=(unsigned int*)malloc(p_drivers*sizeof(unsigned int));
    position_point=(unsigned int*)malloc(p_drivers*sizeof(unsigned int));
    for(k=0;k<p_drivers;k++){
        scanf("%u",&position_point[k]);
    }
    for (i=0;i<p_drivers;i++){
        sum=0;
        for(j=0;j<n_races;j++){
            sum+= position_point[positions[i][j]-1];
        }
        r_points[i]= sum;
    }
    printf("%u,%u",r_points[0],r_points[1]);
    return 0;
    */
    /* 10
    unsigned int total_points[]={73,51,21,62,84,35,21,10,22,22}; 
    unsigned int p_drivers=10, id=7;
    int i;
    unsigned int rank=1;
    for (i=0;i<p_drivers;i++){
        if(total_points[i]<total_points[id]){rank++;}
        else if(total_points[i]==total_points[id]){if(i<id){rank++;}}
    }    
    printf("%u",rank);
    return 0;
   */
    return 0;
}
