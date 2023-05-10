#include <stdio.h>
#include <stdlib.h>

#define INPUT_FILE "myCuteFile.txt"
int main(void){
    FILE *fp;
    char ch[50];
    int a = 0,i,k=0,z=0,sonuc=1,linecount=0;
    fp=fopen(INPUT_FILE, "r");
    fscanf(fp,"%s",ch);  
    
    while(fgets(ch,50,fp) != NULL){
         
        if(linecount%2==1){
        for(i=0;ch[i] == 49 || ch[i] == 48;i++){
            k++;
        }       
        
        /*printf("k: %d\n",k);*/       
       
        for(k,z=0;k>0;k--,z++){
            
            if(ch[k-1]=='1'){                
                for (i = 0; i < z; i++)
                sonuc *=  2;                
                a= a + sonuc ;
                sonuc = 1;            
               /* printf("z: %d k: %d a :%d\n",z,k,a); */
               }            
            }
           
        printf("%d\n",a);
        }
        k=0;
        a=0;
        linecount++;       
       /*printf("%s----------------\n",ch);*/        
    }
    fclose(fp);   
    return 0;
}