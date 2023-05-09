#include <stdio.h>

float try_btc = 0.0555;
float btc_try = 18.0180;
float try_eth = 0.0833;
float eth_try = 12.0048;
float btc_eth = 1.5001;
float eth_btc = 0.6666;
float money, T , B=0, E=0;
float inc, dec, amount, per1, per2, per3, per4, gain1, gain2, y;
char op, op1, op2, op3, op4, op5, op6;
int x;

int main(){
    scanf(" %c %f", &op, &T);
    while(1){
        scanf(" %c", &op);
        switch(op)
        {
            case 'Q':
                printf("Bye...\n");
                return 0;
                
            case 'R':
                if (B !=0 && E !=0){
                    printf("Our account holds %.2f TRY | %.2f BTC | %.2f ETH.\n", T, B, E);  
                }
                else if (B==0 && E !=0){
                    printf("Our account holds %.2f TRY | %.2f ETH.\n", T, E);
                }
                else if (B!=0 && E ==0){
                    printf("Our account holds %.2f TRY | %.2f BTC.\n", T, B);
                    
                }
                else{
                    printf("Our account holds %.2f TRY.\n", T);
                }
                break;
        
            case 'D':
                scanf(" %c %f", &op1, &inc);
                if (op1 =='B'){
                    B = B + inc;
                    
                }
                else if (op1 =='E'){
                    E = E + inc;
                }
                else if (op1 =='T'){
                    T = T + inc;
                }
                else
                    printf("Error: Operation could not be completed.\n");
                    
                break;
            
            case 'W':
                scanf(" %c %f", &op2, &dec);
                if (op2 =='B'){
                    if (B>=dec){
                    B = B - dec;
                    }
                    else
                        printf("Error: Insufficient funds.\n");
                }
                else if (op2 =='E'){
                    if (E>=dec){
                        E = E - dec;    
                    }
                    else
                        printf("Error: Insufficient funds.\n");
                }
                else if (op2 =='T'){
                    if (T>=dec){
                        T = T - dec;
                    }
                    else
                        printf("Error: Insufficient funds.\n");
                }
                else
                    printf("Error: Operation could not be completed.\n");
                break;
        
            case 'X':
                scanf(" %c %f %c", &op3, &amount, &op4);
                if (op3 == 'T'){
                    if(op4 == 'B'){
                        if(T>=amount){
                            T -= amount;
                            B += amount * try_btc;
                            printf("You have successfully bought %.2f BTC.\n", amount * try_btc);
                        }
                        else{
                            x = T * try_btc;
                            y = x;
                            B += y;
                            T -= y* btc_try;
                            printf("This amount is too much, you have successfully bought %.2f BTC.\n", y);
                        }
                        
                    }
                    else if(op4 =='E'){
                        if(T>=amount){
                            T -= amount;
                            E += amount * try_eth;
                            printf("You have successfully bought %.2f ETH.\n", amount * try_eth);
                            
                        }
                        else{
                            x = T * try_eth;
                            y = x;
                            E += y;
                            T -= y * eth_try;
                            printf("This amount is too much, you have successfully bought %.2f ETH.\n", y);
                        }
                        
                    }
                    else
                        printf("Error: Operation could not be completed.\n");
                }
                else if(op3 == 'B'){
                    if(op4 == 'T'){
                        if(B>=amount){
                            B -= amount;
                            T += amount * btc_try;
                            printf("You have successfully bought %.2f TRY.\n", amount * btc_try);
                            
                        }
                        else{
                            x = B * btc_try;
                            y = x;
                            T += y;
                            B -= y * try_btc;
                            printf("This amount is too much, you have successfully bought %.f TRY.\n", y);
                        }
                        
                    }
                    else if(op4 =='E'){
                        if(B>=amount){
                            B -= amount;
                            E += amount * btc_eth;
                            printf("You have successfully bought %.2f ETH.\n", amount * btc_eth);
                        }
                        else{
                            x = B * btc_eth;
                            y = x;
                            E += y;
                            B -= y * eth_btc;
                            printf("This amount is too much, you have successfully bought %.2f ETH.\n", y);
                        }
                        
                    }
                    else
                        printf("Error: Operation could not be completed.\n");
                }
                else if(op3 =='E'){
                    if(op4 =='T'){
                        if(E>=amount){
                            E -= amount;
                            T += amount * eth_try;
                            printf("You have successfully bought %.2f TRY.\n", amount * eth_try);
                            
                        }
                        else{
                            x = E * eth_try;
                            y = x;
                            T += y;
                            E -= y * try_eth;
                            printf("This amount is too much, you have successfully bought %.2f TRY.\n", y);
                        }
                        
                    }
                    else if(op4 =='B'){
                        if(E>=amount){
                            E -= amount;
                            B += amount * eth_btc;
                            printf("You have successfully bought %.2f BTC.\n", amount * eth_btc);
                        }
                        else{
                            x = E * eth_btc;
                            y = x;
                            B += y;
                            E -= y * btc_eth;
                            printf("This amount is too much, you have successfully bought %.2f BTC.\n", y);
                        }
                        
                    }
                    else
                        printf("Error: Operation could not be completed.\n");
                }        
                else {
                    printf("Error: Operation could not be completed.\n");
                }
                
                break;
            
        
            case 'S':
                scanf(" %f", &amount);
                scanf(" %c %f %f", &op5, &per1, &per2);
                scanf(" %c %f %f", &op6, &per3, &per4);
                gain1 = (((amount - amount * (per1/100))* (1+(per2/100))) * (1 - (per1/100))) - amount;
                gain2 = (((amount - amount * (per3/100))* (1+(per4/100))) * (1 - (per3/100))) - amount;
                if(op5 == 'E' && op6 == 'B')
                {
                    if (gain1> gain2 && gain1>=0)
                    {
                        printf("ETH is better with %.2f TRY gain. Buying it...\n", gain1);
                        T -= amount;
                        E += amount * try_eth;
                    }
                    else if (gain2 > gain1 && gain2>=0)
                    {
                        printf("BTC is better with %.2f TRY gain. Buying it...\n", gain2);
                        T -= amount;
                        B += amount * try_btc;
                    }
                    else
                        printf("Trading currently is not logical.\n");
                }
                else if(op5 == 'B' && op6 == 'E')
                {
                    if (gain1> gain2 && gain1>=0)
                    {
                        printf("BTC is better with %.2f TRY gain. Buying it...\n", gain1);
                        T -= amount;
                        B += amount * try_btc;
                    }
                    else if (gain2 > gain1 && gain2>=0)
                    {
                        printf("ETH is better with %.2f TRY gain. Buying it...\n", gain2);
                        T -= amount;
                        E += amount * try_eth;
                    }
                    else 
                        printf("Trading currently is not logical.\n");
                }
                else 
                    printf("Error: Operation could not be completed.\n");
                
                break;
            
        }
    } 
    return 0;
        /*printf("Error: Operation could not be completed.");*/
       
}