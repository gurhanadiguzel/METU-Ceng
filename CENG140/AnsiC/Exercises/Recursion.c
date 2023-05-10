#include <stdio.h>
int gcd(int k, int n){
    int G;
    for (int i=1; i<=k && i <= n; i++)
    {
        if( k%i ==0 && n%i ==0)
        {
            G = i;
        }
    }
    printf("Greatest integer is : %d\n", G);
    return 0;
}
int recur_gcd(int k, int n){
    int a;
    if (k==0) return n;
    if (n==0) return k;
    if (k<n){
        a = n%k;
        return recur_gcd(k,a);
    }
    else if (k>n){
        a = k%n;
        return recur_gcd(n,a);
    }
}
int fibonacci(int m){
    int a[m];
    for(int i=1; i<=m; i++)
    {
        if (i==1 ||i ==2){
            a[i] = 1;
        }
        else{
            a[i] = a[i-1]+a[i-2];
        }
    }
    printf("Fibonnacci: %d\n", a[m]);
    return 0;
}
int recaman(int l){
    int a[l];
    a[0]= 0;
    for (int i=1; i<=l;i++){
        if (a[i-1]-i > 0){
            a[i] = a[i-1]-i;
        }
        else{
            a[i] = a[i-1]+i;
        }
        
    }
    printf("Recaman : %d\n", a[l]);
    return 0;

}
int factorial(int n){
    if(n==0)
        return 1;
    else
        return n*factorial(n-1);
}
int main(){
    gcd(192, 72);
    printf("Gcd: %d\n",recur_gcd(192,72));
    fibonacci(5);
    recaman(5);    
    printf("Factorial: %d\n", factorial(10));
    return 0;
}