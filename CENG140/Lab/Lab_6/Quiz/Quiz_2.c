#include <stdio.h>
#include <stdlib.h>


char** split(char *str, char delimeter) {
    char **arr;
    int i,j,k=0,x=0;
    int len=0,nd=2;
    for(i=0;str[i]!='\0';i++){
        if(str[i]==delimeter)nd++;
    }
    arr=(char**)malloc(nd*sizeof(char*));
    for(i=0;str[i]!='\0';i++){
        len++;
        if(str[i]==delimeter ){
            arr[k]=(char*)malloc((len)*sizeof(char));            
            for(j=0;j<len-1;j++){
                arr[k][j]=str[x];                
                x++;
            }
            x++;
            len=0;
            k++;
        }        
    }
    if (str[i]=='\0'){
        arr[k]=(char*)malloc((len)*sizeof(char)); 
        for(j=0;j<len-1;j++){
                arr[k][j]=str[x];
    
                x++;
        }
        x++;
        len=0;
        k++;              
    }
    arr[nd]=NULL;
    return arr;
}
int main(){
    char *sen="You either die a hero, or you live long enough to see yourself become the villain.";
    char del=' ';
    char **new;
    new=split(sen,del);
    new[2]="come";
    return 0;
}