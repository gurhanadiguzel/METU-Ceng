#include <stdio.h>
#include <stdlib.h>


char* pile(char* str1, char* str2) {
    int len1=0,len2=0;
    int i,j;
    int x=0,y=0,z=0;
    char *sen;
    for(i=0;str1[i]!='\0';i++){if(str1[i]!=' '){len1++;}}
    for(j=0;str2[j]!='\0';j++){if(str2[j]!=' '){len2++;}}
    sen=(char*)malloc((len1+len2)*sizeof(char));
    while(z<len1+len2){
        if(str1[x]!='\0'){
            if(str1[x]==' '){x++;}
            if(str1[x]!=' '){
                sen[z]=str1[x];
                z++;
            }
            x++;
        }
        if(str2[y]!='\0'){
            if(str2[y]==' '){y++;}
            if(str2[y]!=' '){
                sen[z]=str2[y];
                z++;
            }
            y++;
        }
    }
    return sen;
}

int main(){
    char *a="11 1";
    char *b="222 2222";
    char *c;
    c=pile(a,b);
    printf("%s",c);
    return 0;
}