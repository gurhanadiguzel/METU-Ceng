#include<stdio.h>
#define row 25
#define column 25  
int image[row][column];

void print_func(){
    int i,j;
    for (i=0; i<row; i++){
        for(j=0; j<column; j++){
            printf( "%d ", image[i][j]);
        }
        printf("\n");
    }
}

void fill(int x, int y, int ex_color, int new_color){
    if (image[x][y]== new_color);
    else if (image[x][y] == ex_color && (x<row && x>=0 && y>=0 && y<column)){
        /*printf("%d %d a\n",x, y);*/
        image[x][y] = new_color;
        fill(x+1, y, ex_color, new_color);
        fill(x+1, y+1, ex_color, new_color);
        fill(x+1, y-1, ex_color, new_color);
        fill(x, y+1, ex_color, new_color);        
        fill(x, y-1, ex_color, new_color);
        fill(x-1, y, ex_color, new_color);
        fill(x-1, y+1, ex_color, new_color);
        fill(x-1, y-1, ex_color, new_color);
    }
    else;
}

int main(){    
    int x, y, x1, y1, ex_color, new_color;
    int x2, y2, x3, y3, x4, y4, x5, y5;
    int r,c;
    char op;
    for(r=0; r<row; r++){
        for(c=0; c<column; c++){
            scanf("%d",&image[r][c]);
        }    
    }
    scanf(" %c", &op);    
    if(op =='F'){
        scanf("%d %d", &x, &y);
        scanf("%d %d", &x1, &y1);
        /*printf("%d %d\n", x, y);*/
        if(x<row && x>=0 && y<column && y>=0 ){new_color = image[x][y];}
        else if (x<0 && y<0){new_color = 0;}
        else if (x<0 && y>=0 && y<column){new_color = 1;}
        else if (x<0 && y>=column){new_color = 2;}        
        else if (x<row && x>=0 && y>=column){new_color = 3;}
        else if (x>=row && y>=column){new_color = 4;}
        else if (x>=row && y>= 0 && y<column){new_color = 5;}
        else if (x>=row && y<0){new_color = 6;}
        else if (x>=0 && x<row && y<0){new_color = 7;}                 
        ex_color = image[x1][y1];
        /*printf("new %d %d\n", ex_color, new_color);*/
        fill(x1, y1, ex_color, new_color);
        print_func();     
    }
    else if (op == 'P'){
        int xc, yc, xc1, yc1;
        int xp, yp, xp1, yp1;
        int step=0, a, b;            
        scanf("%d %d %d %d", &x2, &y2, &x3, &y3);
        scanf("%d %d %d %d", &x4, &y4, &x5, &y5);        
        if(x2<x3){ 
            xc= x2; 
            xc1=x3;
            if (y2<y3){yc = y2; yc1 = y3;}
            else{yc= y3; yc1 = y2;}
        }
        else if(x3<x2){
            xc =x3;
            xc1 =x2;
            if (y2<y3){yc = y2; yc1 = y3;}
            else{yc= y3; yc1 = y2;}
        }
        else if (x2 ==x3){
            if(y3>y2){xc=x2;xc1=x3;yc=y2;yc1=y3;}
            else if(y2>y3){xc=x3;xc1=x2;yc=y3;yc1=y2;}
            else{xc=x2;xc1=x3;yc=y2;yc1=y3;}
        }
        
        if(x4<x5){ 
            xp= x4; 
            xp1=x5;
            if (y4<y5){yp = y4; yp1 = y5;}
            else{yp= y5; yp1 = y4;}
        }
        else if(x5<x4){
            xp =x5;
            xp1 =x4;
            if (y4<y5){yp = y4; yp1 = y5;}
            else{yp= y5; yp1 = y4;}
        }
        else if (x4==x5){
            if(y5>y4){xp=x4;xp1=x5;yp=y4;yp1=y5;}
            else if(y4>y5){xp=x5;xp1=x4;yp=y5;yp1=y4;}
            else{xp=x4;xp1=x5;yp=y4;yp1=y5;}
        }
        
        /*printf("%d %d %d %d\n",xc, yc, xc1, yc1);*/
        /*printf("%d %d %d %d\n",xp, yp, xp1, yp1);*/
        for(a=xp; a<=xp1; a++){
            int s=yc;
            for(b=yp; b<=yp1; b++){ 
                if(image[a][b] != image[xc][yc]){
                    image[a][b] = image[xc][yc];                    
                    step++;
                }
                yc++;                 
            }
            yc = s;
            xc+=1;
        }
        if (xc<=xc1+1 && yc1>yc){     
            print_func();
            printf("%d\n", step);
        }
        else{
            print_func();
            printf("%d\n", step);
        } 
    }
    else if(op =='R'){
        int x6, y6, x7, y7, x8, y8, x9, y9;
        int deg, step =0, i ,j;
        char dir;
        scanf(" %c %d", &dir, &deg);
        scanf("%d %d %d %d", &x6, &y6, &x7, &y7);
        scanf("%d %d %d %d", &x8, &y8, &x9, &y9);
        /*printf("%c %d\n", dir, deg);*/
        /*printf("%d %d %d %d\n", x6, y6, x7, y7);*/
        /*printf("%d %d %d %d\n", x8, y8, x9, y9);*/
        if(deg == 0){
            for(i=x8; i<=x9;i++){
                int s=y6; 
                for(j=y8;j<=y9; j++){
                    if(image[i][j]!=image[x6][y6]){
                        image[i][j]=image[x6][y6];
                        step++;
                    }
                    y6++;
                }
                y6 =s;
                x6++;
            }
        }        
        else if ((dir =='R' || dir == 'L')&& deg ==180){
            for(i=x8;i<=x9;i++){
                int s = y7;
                for(j=y8;j<=y9;j++){
                    if(image[i][j]!= image[x7][y7]){
                        image[i][j] = image[x7][y7];                        
                        step++;
                    }
                    y7--;
                }
                x7--;
                y7 =s;
            }            
        }
        else if ((dir =='R'&& deg==90) || (dir=='L'&& deg ==270)){
            for(j=y9;j>=y8;j--){
                int s1= y6;
                for(i=x8; i<=x9;i++){
                    if(image[i][j] != image[x6][y6]){
                       image[i][j] = image[x6][y6];                       
                       step++;
                    }
                    y6++;                                                             
                }
                x6++;
                y6=s1;
            }            
        }
        else if ((dir =='L'&& deg==90) || (dir=='R'&& deg ==270)){  
            for(i=x8; i<=x9;i++){
                int s=x6;
                for (j=y8; j<=y9;j++){                    
                    if(image[i][j] != image[x6][y7]){
                        image[i][j] = image[x6][y7];
                        step++;
                    }
                    x6++;
                }
                y7--;
                x6 =s;
            }      
            
        }
        print_func();
        printf("%d\n", step); 
    }      
    return 0;
}