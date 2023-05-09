#include <stdio.h>
#include "recit_4_1.h"


int gcd(int a, int b){
    printf("gcd %d %d\n", a, b);
    if (a>b){
        if(a%b != 0){
            return gcd(b,a%b);
        }
        else{
            return b;
        }
    }
    else {
        if(b%a != 0){
            return gcd(a,b%a);
        }
        else{
            return a;
        }
    }
}

double powerhelper1(int base, int exponent, int call){
    if (exponent == 1){
        return base;
    }
    else if (exponent == 0){
        return 1;
    }
    else if (exponent%2 == 0){
        
        call +=1;
        return powerhelper1(base, exponent/2,call) * powerhelper1(base, exponent/2,call);
    }
    else{
        call +=1;
        return base* powerhelper1(base,exponent-1,call);
    }
}

double powerhelper(int base, int exponent, int call){
    printf("calculate: %d^%d call: %d\n", base, exponent, call);
    if (exponent == 1){
        return base;
    }
    else if (exponent == 0){
        return 1;
    }
    else if (exponent%2 == 0){
        
        call +=1;
        return powerhelper(base, exponent/2,call) * powerhelper1(base, exponent/2,call);
    }
    else{
        call +=1;
        return base* powerhelper(base,exponent-1,call);
    }
}

double power(int base1, int exponent1){
    return powerhelper(base1, exponent1, 1);
}

