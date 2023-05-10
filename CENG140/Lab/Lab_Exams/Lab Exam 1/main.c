#include <stdio.h>

int main()
{
    int total=0, loan=0, money, money1, money2;
    int P, B, N, tax, monthly=0;
    int  P1, B1, N1, P2, B2, N2, P3, B3, N3;
    int tcostx, tcosty, tcostz, armyc=0, balance;
    float scorex, scorey, scorez;
    char x, y, z, army;
    char op;
    while(1)
    {
        scanf(" %c", &op);
        switch(op){
            case 'K':
                scanf("%d", &money);
                total += money;
                break;
                
            case 'Q':
                printf("Our reign may never end...\n");
                return 0;
                
            case 'R':
                printf("We have %d ducats in our treasury.\n", total);
                break;
                
            case 'L':
                scanf(" %d", &money1);
                total += money1;
                loan += money1;
                break;
                
            case 'P':
                scanf(" %d", &money2);
                total -= money2;
                if( loan -money2 >=0)
                {
                    loan -= money2; 
                }
                else{
                    loan = 0;
                    printf("We have no remaining debts.\n");
                }
                break;
            
            case 'F':
                if (loan == 1 || loan==0){
                    printf("We have %d ducat of remaining loans.\n", loan);
                }
                else{ 
                    printf("We have %d ducats of remaining loans.\n", loan);
                }
                break;
            
            case 'T':
                scanf("%d %d %d", &P, &B, &N);
                tax = 0;
                tax += P*2 + B*5 + N*10;
                monthly += tax;
                if (tax == 1 || tax==0){
                    printf("Our kingdom has %d ducat income.\n", tax);
                }
                else{
                    printf("Our kingdom has %d ducats income.\n", tax);
                }
                break;
                
            case 'A':
                scanf(" %c %d %d %d", &x, &P1, &B1, &N1);
                scanf(" %c %d %d %d", &y, &P2, &B2, &N2);
                scanf(" %c %d %d %d", &z, &P3, &B3, &N3);
                tcostx = P1 + 12*B1;
                tcosty = P2 + 12*B2;
                tcostz = P3 + 12*B3;
                scorex = (float) N1/tcostx;
                scorey = (float) N2/tcosty;
                scorez = (float) N3/tcostz;
                if (scorex >= scorey && scorex >= scorez){
                    printf("Our army will be %c, since its good score of %.4f.\n", x, scorex);
                    army =x;
                }
                else if (scorey > scorex && scorey >= scorez){
                    printf("Our army will be %c, since its good score of %.4f.\n", y, scorey);
                    army = y;
                }
                else if (scorez > scorex && scorez > scorey){
                    printf("Our army will be %c, since its good score of %.4f.\n", z, scorez);
                    army = z;
                }
                break;
            
            case 'C':
                if (army ==x && total >=P1){
                    total -= P1;
                    armyc +=1;
                    if (armyc>1)
                        printf("Our army is stronger now. We have %d armies serving our kingdom.\n", armyc);
                    else
                        printf("Our army is stronger now. We have %d army serving our kingdom.\n", armyc);
                }
                else if (army ==y && total >=P2){
                    total -= P2;
                    armyc +=1;
                    if (armyc>1)
                        printf("Our army is stronger now. We have %d armies serving our kingdom.\n", armyc);
                    else
                        printf("Our army is stronger now. We have %d army serving our kingdom.\n", armyc);
                }
                else if (army ==z && total >=P3){
                    total -= P3;
                    armyc +=1;
                    if (armyc>1)
                        printf("Our army is stronger now. We have %d armies serving our kingdom.\n", armyc);
                    else
                        printf("Our army is stronger now. We have %d army serving our kingdom.\n", armyc);
                }
                else 
                    printf("We can not afford this army for now.\n");
                break;

        }
    }
    return 0;
    
}