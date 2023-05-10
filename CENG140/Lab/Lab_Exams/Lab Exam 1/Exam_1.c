#include <stdio.h>

#define try_btc 0.0555
#define btc_try 18.0180
#define try_eth 0.0833
#define eth_try 12.0048
#define btc_eth 1.5001
#define eth_btc 0.6666

int main()
{
    char opcode,currency1,currency2;
    float TRY=0,BTC=0,ETH=0,amount,bought,gain1,gain2;
    int loss_percentage1,loss_percentage2,expected_gain1,expected_gain2;
    while(opcode!='Q'){
        scanf(" %c",&opcode);
        switch(opcode){
            case 'T':
                scanf("%f",&TRY);
                break;
            case 'R':
                printf("Our account holds %.2f TRY",TRY);
                if(BTC)
                    printf(" | %.2f BTC",BTC);
                if(ETH)
                    printf(" | %.2f ETH",ETH);
                printf(".\n");
                break;
            case 'D':
                scanf(" %c %f",&currency2,&amount);
                switch(currency2){
                    case 'T':
                        TRY+=amount;
                        break;
                    case 'B':
                        BTC+=amount;
                        break;
                    case 'E':
                        ETH+=amount;
                        break;
                    default:
                        printf("Error: Operation could not be completed.\n");
                }
                break;
            case 'W':
                scanf(" %c %f",&currency1,&amount);
                switch(currency1){
                    case 'T':
                        amount>TRY?printf("Error: Insufficient funds.\n"):(TRY-=amount);
                        break;
                    case 'B':
                        amount>BTC?printf("Error: Insufficient funds.\n"):(BTC-=amount);
                        break;
                    case 'E':
                        amount>ETH?printf("Error: Insufficient funds.\n"):(ETH-=amount);
                        break;
                    default:
                        printf("Error: Operation could not be completed.\n");
                }
                break;
            case 'Q':
                printf("Bye...\n");
                return 0;
            case 'X':
                bought=0;
                scanf(" %c %f %c",&currency1,&amount,&currency2);
                switch(currency2){
                    case 'T':
                        switch(currency1){
                            case 'B':
                                if(amount>BTC){
                                    bought=(int)(BTC*btc_try);
                                    BTC-=bought*try_btc;
                                    printf("This amount is too much, you have successfully bought %.2f TRY.\n",bought);
                                }
                                else{
                                    bought=amount*btc_try;
                                    BTC-=amount;
                                    printf("You have successfully bought %.2f TRY.\n",bought);
                                }
                                break;
                            case 'E':
                                 if(amount>ETH){
                                    bought=(int)(ETH*eth_try);
                                    ETH-=bought*try_eth;
                                    printf("This amount is too much, you have successfully bought %.2f TRY.\n",bought);
                                }
                                else{
                                    bought=amount*eth_try;
                                    ETH-=amount;
                                    printf("You have successfully bought %.2f TRY.\n",bought);
                                }
                                break;
                            default:
                                printf("Error: Operation could not be completed.\n");
                        }
                        TRY+=bought;
                        break;
                    case 'B':
                        switch(currency1){
                            case 'T':
                                if(amount>TRY){
                                    bought=(int)(TRY*try_btc);
                                    TRY-=bought*btc_try;
                                    printf("This amount is too much, you have successfully bought %.2f BTC.\n",bought);
                                }
                                else{
                                    bought=amount*try_btc;
                                    TRY-=amount;
                                    printf("You have successfully bought %.2f BTC.\n",bought);
                                }
                                break;
                            case 'E':
                                if(amount>ETH){
                                    bought=(int)(ETH*eth_btc);
                                    ETH-=bought*btc_eth;
                                    printf("This amount is too much, you have successfully bought %.2f BTC.\n",bought);
                                }
                                else{
                                    bought=amount*eth_btc;
                                    ETH-=amount;
                                    printf("You have successfully bought %.2f BTC.\n",bought);
                                }
                                break;
                            default:
                                printf("Error: Operation could not be completed.\n");
                        }
                        BTC+=bought;
                        break;
                    case 'E':
                        switch(currency1){
                            case 'B':
                                if(amount>BTC){
                                    bought=(int)(BTC*btc_eth);
                                    BTC-=bought*eth_btc;
                                    printf("This amount is too much, you have successfully bought %.2f ETH.\n",bought);
                                }
                                else{
                                    bought=amount*btc_eth;;
                                    BTC-=amount;
                                    printf("You have successfully bought %.2f ETH.\n",bought);
                                }
                                break;
                            case 'T':
                                if(amount>TRY){
                                    bought=(int)(TRY*try_eth);
                                    TRY-=bought*eth_try;
                                    printf("This amount is too much, you have successfully bought %.2f ETH.\n",bought);
                                }
                                else{
                                    bought=amount*try_eth;
                                    TRY-=amount;
                                    printf("You have successfully bought %.2f ETH.\n",bought);
                                }
                                break;
                            default:
                                printf("Error: Operation could not be completed.\n");
                        }
                        ETH+=bought;
                        break;
                    default:
                        printf("Error: Operation could not be completed.\n");
                }
                break;
            case 'S':
                scanf("%f %c %d %d %c %d %d",&amount,&currency1,&loss_percentage1,&expected_gain1,&currency2,&loss_percentage2,&expected_gain2);
                gain1=((1+expected_gain1*0.01)*(1-loss_percentage1*0.01)*(1-loss_percentage1*0.01)-1);
                gain2=((1+expected_gain2*0.01)*(1-loss_percentage2*0.01)*(1-loss_percentage2*0.01)-1);
                if(gain1<0 && gain2<0)
                    printf("Trading currently is not logical.\n");
                else if(gain1>gain2){
                        if(currency1=='B' && currency2=='E'){
                            printf("BTC is better with %.2f TRY gain. Buying it...\n",gain1*amount);
                            TRY-=amount;
                            BTC+=amount*try_btc;
                        }
                        else if(currency1=='E' && currency2=='B'){
                            printf("ETH is better with %.2f TRY gain. Buying it...\n",gain1*amount);
                            TRY-=amount;
                            ETH+=amount*try_eth;
                        }
                        else
                            printf("Error: Operation could not be completed.\n");
                    }
                else
                    if(currency1=='B' && currency2=='E'){
                        printf("ETH is better with %.2f TRY gain. Buying it...\n",gain2*amount);
                        TRY-=amount;
                        ETH+=amount*try_eth;
                    }
                    else if(currency1=='E' && currency2=='B'){
                        printf("BTC is better with %.2f TRY gain. Buying it...\n",gain2*amount);
                        TRY-=amount;
                        BTC+=amount*try_btc;
                    }
                    else
                        printf("Error: Operation could not be completed.\n");
                break;
            default:
                printf("Error: Operation could not be completed.\n");
                }
        }
    }