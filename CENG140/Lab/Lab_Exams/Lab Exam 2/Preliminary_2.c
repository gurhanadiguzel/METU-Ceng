#include "stdio.h"
/*#include "lab2.h"*/
#define mapWidth 5
#define mapHeight 5
#define prevCount 20
#define nextCount 10

/* TASK SOLUTIONS */

void to_lower(char * sentence){
    int i;
    for(i=0;i<256;i++){
        if(sentence[i]>=65 && sentence[i]<=90){
            sentence[i]+=32; 
        }
    }       
}

void print_sentence(char * sentence){
    int i;
    for(i=0;sentence[i] != '!'; i++){
        printf("%c",sentence[i]);
    }
    printf("\n");
}

void substrings(char * sentence, char * substr, int * arr){
    int i=0,j=0,a=0;
    while(sentence[i]!='!'){
        while(sentence[i]==substr[j]){
            if (substr[j+1]=='!'){
                arr[a]= i-j;
                j=0;
                a++;
            }
            j++;
        }
        i++;
    }    
}
/*
void substrings(char * sentence, char * substr, int * arr){
    int i,j=0,k=0;
    for(i=0;sentence[i]!='!';i++){
        if(substr[j]=='!'){arr[k]=i-j;k++;j=0;}
        else if(sentence[i]==substr[j])j++;
        else j=0;
    }
}
*/

void removeX(char * sentence, int * arr, int count){
    int i,j,x,y;
    y = sizeof(arr)/sizeof(int);
    for(i=0;arr[i]!=0;i++){
        x = arr[i]-(count*i);
        for(j=x;sentence[j] != '!';j++){
            sentence[j]=sentence[j+3];
        }
    }    
}

void addSome(char * sentence, int * arr, char * substr){
    int i,j,x,y,z,k,l,m=0,num=0;
    y = sizeof(substr)/sizeof(char)-1;
    for(i=0;sentence[i]!='!';i++){
           num++; 
    }
    for (z=0;arr[z]!=0;z++){
        l=y*(z+1);
        for(j=num;j>=arr[z];j--){
            sentence[j+l]=sentence[j+y*z];
        }
        for(k=arr[z]+(y*z);substr[m]!='!';k++){
            sentence[k]=substr[m];
            m++;            
        }
        m=0;
    }
}

void battle_ship(char map[mapWidth][mapHeight], int prev_moves[prevCount][2], int next_moves[nextCount][2]){
    int i=0,j,x,y,z,a=0;
    while(prev_moves[i][0]!=-1 && prev_moves[i][1]!= -1){
        x=prev_moves[i][0];
        y=prev_moves[i][1];
        map[x][y]='H';
        i++;
    }
    for(j=0;j<mapHeight;j++){
        for(z=0;z<mapWidth;z++){
            if (map[j][z]=='X'){
                next_moves[a][0]=j;
                next_moves[a][1]=z;
                a++;
            }
        }
    }
    next_moves[a][0]=-1;
    next_moves[a][1]=-1;
    
}
int main(){
    char sentence[256] = "This is the lab exam of CENG140 of Ceng department (in english version)!";

    char substr[10] = "eng!";

    int arr[10] = {0};

    to_lower(sentence);

    substrings(sentence, substr, arr);

    // Content of arr is {25,36,55}

    addSome(sentence, arr, substr);

    print_sentence(sentence);

}

