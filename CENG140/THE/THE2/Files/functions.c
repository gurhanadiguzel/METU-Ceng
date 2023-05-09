#include <stdlib.h>
#include <stdio.h>
#define n_sector 3

float*** create_sector_times(unsigned int* n_drivers, unsigned int* n_laps){
    int i,j,k;
    unsigned int d,l;
    float ***arr1;
    scanf("%u",&d);
    scanf("%u",&l);
    *n_drivers=d;
    *n_laps=l;
    /*printf("%u %u\n",*n_drivers,*n_laps);*/
    arr1=(float***)malloc((*n_drivers)*sizeof(float**));    
    for(i=0;i<*n_drivers;i++){ 
        arr1[i]=(float**)malloc((*n_laps)*sizeof(float*));       
        for(j=0;j<*n_laps;j++){
            arr1[i][j]=(float*)malloc(n_sector*sizeof(float));                        
            for(k=0;k<n_sector;k++){                
                scanf("%f", &arr1[i][j][k]);
            }
        }    
    }
    return arr1;
}

unsigned int** create_positions(unsigned int* p_drivers, unsigned int* n_races){
    int i,j;
    unsigned int **arr2 ,d, r;
    scanf("%u",&d);
    scanf("%u",&r);
    *p_drivers=d;
    *n_races=r;
    arr2=(unsigned int**)malloc((*p_drivers)*sizeof(unsigned int*));
    for(i=0;i<*p_drivers;i++){
        arr2[i]=(unsigned int*)malloc((*n_races)*sizeof(unsigned int));
        for(j=0;j<*n_races;j++){
            scanf("%u",&arr2[i][j]);
        }
    }
    return arr2;
}

float** calculate_lap_times(float*** sector_times, unsigned int n_drivers, unsigned int n_laps){
    int i,j,k;
    float **arr3,sum;
    arr3=(float**)malloc((n_drivers)*sizeof(float*));
    for(i=0;i<n_drivers;i++){
        arr3[i]=(float*)malloc((n_laps)*sizeof(float));
        for(j=0;j<n_laps;j++){
           sum=0;
           for(k=0;k<n_sector;k++){
               sum+=sector_times[i][j][k];
           }
           arr3[i][j]=sum; 
        }
    }
    return arr3;
}

unsigned int find_fastest_lap(float** lap_times, unsigned int n_drivers, unsigned int n_laps){
    int i,j;
    float smallest =lap_times[0][0];
    unsigned int index=0;
    for(i=0;i<n_drivers;i++){
        for(j=0;j<n_laps;j++){
            if(lap_times[i][j]<smallest){
                smallest=lap_times[i][j];
                index = (unsigned int)i;
            }
        }
    }
    return index;
}

unsigned int find_driver_fastest_lap(float** sector_times_of_driver, unsigned int n_laps){
    int i,j,k;
    float fastest=0,lap;
    unsigned int f_lap=0;
    for(i=0;i<n_sector;i++){
        fastest+=sector_times_of_driver[0][i];
    }
    for(j=1;j<n_laps;j++){
        lap=0;
        for(k=0;k<n_sector;k++){
            lap+=sector_times_of_driver[j][k];
        }
        if(lap<fastest){f_lap=(unsigned int)j;fastest=lap;}
    }
    return f_lap;
}

float* selection_sort(float* arr, unsigned int len, char ord){
    int i,j;
    int smallest,biggest;
    float temp;
    float *sorted=arr;
    if(ord=='A'){
        for(i=0;i<len;i++){
            smallest=i;
            for(j=i;j<len;j++){
                if(sorted[j]<sorted[smallest]){
                    smallest=j;                
                }
            }
            /*printf("%d\n",smallest);*/
            temp= sorted[i];
            sorted[i]=sorted[smallest];
            sorted[smallest]=temp;
        }
    }
    else if(ord=='D'){
        for(i=0;i<len;i++){
            biggest=i;
            for(j=i;j<len;j++){
                if(sorted[j]>sorted[biggest]){
                    biggest=j;
                }
            }
            temp=sorted[i];
            sorted[i]=sorted[biggest];
            sorted[biggest]=temp;
        }
    }
    return sorted;
}

unsigned int* find_finishing_positions(float **lap_times, unsigned int n_drivers, unsigned int n_laps){
    int i,j;
    int x=0,y,z,w;
    int k, l=0;
    unsigned int pos=1, pos1=1;
    unsigned int *positions,*id_list;
    float *lap_sums,sum,min,max,last=0;
    positions=(unsigned int*)malloc(n_drivers*sizeof(unsigned int));
    lap_sums=(float*)malloc(n_drivers*sizeof(float));
    id_list=(unsigned int*)malloc(n_drivers*sizeof(unsigned int));
    for(i=0;i<n_drivers;i++){
        sum=0;
        for(j=0;j<n_laps;j++){
            sum+=lap_times[i][j];
        }
        lap_sums[i]=sum;
    }
    /*printf("%f %f %f %f %f %f \n",lap_sums[0],lap_sums[1],lap_sums[2],lap_sums[3],lap_sums[4],lap_sums[5]);*/
    max=lap_sums[0];
    for(w=0;w<n_drivers;w++){if(lap_sums[w]>max){max=lap_sums[w];}}
    while(x<n_drivers){
        min=max;
        for(y=0;y<n_drivers;y++){            
            if(lap_sums[y]>last && lap_sums[y]<=min){min=lap_sums[y];}
        }
        for(z=0;z<n_drivers;z++){
            if(lap_sums[z]==min){id_list[z]=pos1;last=min;pos1++;x++;}
        }        
    }
    /*printf("%u %u %u %u %u %u\n",id_list[0],id_list[1],id_list[2],id_list[3],id_list[4],id_list[5]);*/
    while(l<n_drivers){
        for(k=0;k<n_drivers;k++){
            /*printf("%u %u\n",id_list[k],pos);*/
            if(id_list[k]==pos){positions[l]=k;pos++;l++;}
        }
    }
    return positions;
}

float* find_time_diff(float** lap_times, unsigned int n_drivers, unsigned int n_laps, unsigned int driver1, unsigned int driver2){
    int i;
    float *diff,s=0;
    diff=(float*)malloc(n_laps*sizeof(float));
    for(i=0;i<n_laps;i++){
        diff[i]=lap_times[driver1][i]-lap_times[driver2][i]+s;
        s=diff[i];
    }
    return diff;
}

unsigned int* calculate_total_points(unsigned int** positions, unsigned int p_drivers, unsigned int n_races){
    int i,j,k;
    unsigned int *r_points,*position_point,sum;
    r_points=(unsigned int*)malloc(p_drivers*sizeof(unsigned int));
    position_point=(unsigned int*)malloc(p_drivers*sizeof(unsigned int));
    for(k=0;k<p_drivers;k++){
        scanf("%u",&position_point[k]);
    }
    for(i=0;i<p_drivers;i++){
        sum=0;
        for(j=0;j<n_races;j++){
            sum+= position_point[positions[i][j]-1];
        }
        r_points[i]= sum;
    }
    return r_points;
}

unsigned int find_season_ranking(unsigned int* total_points, unsigned int p_drivers, unsigned int id){
    int i;
    unsigned int rank=1;
    for (i=0;i<p_drivers;i++){
        if(total_points[i]>total_points[id]){rank++;}
        else if(total_points[i]==total_points[id]){if(i<id){rank++;}}
    }
    return rank;
}