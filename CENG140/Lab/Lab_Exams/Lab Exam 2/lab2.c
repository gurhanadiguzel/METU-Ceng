#include "stdio.h"
#include "lab2.h"

/* TASK SOLUTIONS */
void print_sentence(char * sentence) {
    int i;
    for(i=0;sentence[i]!='!';i++){
        if(sentence[i]!='_' && sentence[i]!='!'){
            printf("%c",sentence[i]);
        }
    }
    printf("\n");
}

void capital(char * sentence) {
    int i,j=0,k;
    for(i=0;sentence[i]!='!';i++){
        if(sentence[i]=='_'){
            if (sentence[i-j]>='a' && sentence[i-j]<='z'){
                sentence[i-j]-=32;
            }
            else if(j==0&&sentence[i+1]>='a' && sentence[i+1]<='z'){
                sentence[i+1]-=32;
            }
            for(k=i;sentence[k]!='!';k++){
                sentence[k]=sentence[k+1];
                i--;
            } 
        }
        else if(sentence[i]== ' '){
            j=0;
        }
        else{
            j++;
        }
    }  
}

void sortPos(int * arr, int * sortedArr) {
    int i,j,k;
    sortedArr[0]=arr[0];
    for (i=1;arr[i]!=0;i++){
        for(j=0;j<posLen;j++){
            if (arr[i]<sortedArr[j]){
                for(k=posLen-1;k>j;k--){
                    sortedArr[k]=sortedArr[k-1];
                }  
                sortedArr[j]=arr[i];
                break;
            }
            else if(sortedArr[j]==0){
                sortedArr[j]=arr[i];
                break;
            }
        }
    }
    
}

void to_ascii (char * sentence, int * positions, int count, char * ascii_result) {
    int i,j,k,l=0;
    int x,m;
    char y,z;
    for(i=0;positions[i]!=0;i++){
        k=positions[i];
        for(j=0;j<count;j++){
            if(sentence[k]==' '){
              ascii_result[l]=' ';  
            }
            else{
                z = sentence[k];
                x= (int)z;
                for(m=0;x%10>0;m++){
                    y= x%10+'0';
                    /*printf("%d %c\n",x,y);*/
                    ascii_result[l]=y; 
                    l++;
                }
            }
            k++;
        }
    }
    printf("%s",ascii_result);
}

void sos(char map[3][3], int locations[9][2], char labels[9]) {
    int i,k=0;
    int x,y;
    char z;
    for(i=0;i<9;i++){
        x=locations[i][0];
        y=locations[i][1];
        z=labels[i];
        map[x][y]=z;
        if(map[0][0]=='S'&&map[0][1]=='O'&&map[0][2]=='S'){
            if(k%2==0){printf("Player 1 wins the game.\n");}
            else {printf("Player 2 wins the game.\n");}
            break;
        }
        else if(map[0][0]=='S'&&map[1][1]=='O'&&map[2][2]=='S'){
            if(k%2==0){printf("Player 1 wins the game.\n");}
            else {printf("Player 2 wins the game.\n");}
            break;
        }
        else if(map[0][0]=='S'&&map[1][0]=='O'&&map[2][0]=='S'){
            if(k%2==0){printf("Player 1 wins the game.\n");}
            else {printf("Player 2 wins the game.\n");}
            break;
        }
        else if(map[1][0]=='S'&&map[1][1]=='O'&&map[1][2]=='S'){
            if(k%2==0){printf("Player 1 wins the game.\n");}
            else {printf("Player 2 wins the game.\n");}
            break;
        }
        else if(map[2][0]=='S'&&map[2][1]=='O'&&map[2][2]=='S'){
            if(k%2==0){printf("Player 1 wins the game.\n");}
            else {printf("Player 2 wins the game.\n");}
            break;
        }
        else if(map[2][0]=='S'&&map[1][1]=='O'&&map[0][2]=='S'){
            if(k%2==0){printf("Player 1 wins the game.\n");}
            else {printf("Player 2 wins the game.\n");}
            break;
        }
        else if(map[0][1]=='S'&&map[1][1]=='O'&&map[2][1]=='S'){
            if(k%2==0){printf("Player 1 wins the game.\n");}
            else {printf("Player 2 wins the game.\n");}
            break;
        }
        else if(map[0][2]=='S'&&map[1][2]=='O'&&map[2][2]=='S'){
            if(k%2==0){printf("Player 1 wins the game.\n");}
            else {printf("Player 2 wins the game.\n");}
            break;
        }
        else if(i==8){
            printf("Draw Game.\n");
        }
        k++;
    }
    
}
