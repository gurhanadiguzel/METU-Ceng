/*
 * File:   main.c
 *
 * Created on May 16, 2023, 6:07 PM
 */

#include "the3.h"
#include "lcd.h"
#include "adc.h"
#include "pragmas.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define CNT 20
unsigned short CONVERT = 0;

struct player {
    int id;
    int x;
    int y;
    int team;
    int type;
};

struct frisbeeCord {
    int id;
    int x;
    int y;
};

int score0;
int score1;
int tester = 0;
int selectedPlayerId = 0;
int rbFlag[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int timerFlag = 1;
int counter0 = 300;
int counter1 = CNT;
int speed = 1;
int rbPressed = 0;
int steps;
int frisbeeIndex = 0;
int activeMode;

int type = 0;
struct player player1;
struct player player2;
struct player player3;
struct player player4;
struct frisbeeCord frisbeeCord;

void initializePlayer(struct player *p, int playerId, int posX, int posY, int playerTeam, int type) {
    p->id = playerId;
    p->x = posX;
    p->y = posY;
    p->team = playerTeam;
    p->type = type;
}

void initializeFrisbeeCord(struct frisbeeCord *f, int posX, int posY) {
    f->x = posX;
    f->y = posY;
    f->id = 4;
}

void initVariables() {

    initializePlayer(&player1, 0, 3, 2, 0, 3);
    initializePlayer(&player2, 1, 3, 3, 0, 0);
    initializePlayer(&player3, 2, 14, 2, 1, 1);
    initializePlayer(&player4, 3, 14, 3, 1, 1);
    initializeFrisbeeCord(&frisbeeCord, 9, 2);

    LCDAddSpecialCharacter(0, teamA_player);

    LCDGoto(player1.x, player1.y);
    LCDDat(3);

    LCDGoto(player2.x, player2.y);
    LCDDat(0);

    LCDAddSpecialCharacter(1, teamB_player);

    LCDGoto(player3.x, player3.y);
    LCDDat(1);

    LCDGoto(player4.x, player4.y);
    LCDDat(1);

    LCDAddSpecialCharacter(2, frisbee);

    LCDGoto(frisbeeCord.x, frisbeeCord.y);
    LCDDat(2);

    LCDAddSpecialCharacter(3, selected_teamA_player);
    LCDAddSpecialCharacter(4, selected_teamB_player);
    LCDAddSpecialCharacter(5, selected_teamA_player_with_frisbee);
    LCDAddSpecialCharacter(6, selected_teamB_player_with_frisbee);
    LCDAddSpecialCharacter(7, frisbee_target);
}

void initPorts() {
    INTCON = 0; // Clears INTCON.
    TRISA = 0; // Make PORTA output.
    TRISB = 0b11110011; // Make RB0,RB1,RB4,RB5,RB6,RB7 as input.
    TRISC = 0; // Make PORTC output.
    TRISD = 0; // Make PORTD output.
    LATA = 0; // Clears LATA
    LATB = 0; // Clears LATB
    LATC = 0; // Clears LATC
}

void initInterrupts() {
    INTCON = 0b11111000; // Make Global(GIE), Peripheral(PEIE), Timer0(TMR0IE), and RBIE enable.
    INTCON2 = 0b10000101; // Make PORTB and Timer0 change High Priority and PORTB pull-up disable.
    INTCON3 = 0b01001000; // Make INT1IP High Priority, INT1IE enable.
    PIE1bits.TMR1IE = 1; // Timer 1 interrupt is enabled
    PIE1bits.TMR2IE = 1; // Timer 2 interrupt is enabled
}

void initTimer0() {
    TMR0 = 0;
    T0CON = 0b10000011; //  Enable Timer, 16-bit, falling(rising) edge, prescalar 8
    TMR0H = 0XFF;
    TMR0L = 0x67;
}

void initTimer1() {
    TMR1 = 0;
    T1CON = 0b11111001;
    TMR1H = 0x00;
    TMR1L = 0x00;
}

void initTimer2() {
    TMR2 = 0xCC;
    T2CON = 0b01100111;

}

void displayScore(int score) {
    if (score == 0) {
        LATD = 0b0111111;
    } else if (score == 1) {
        LATD = 0b0000110;
    } else if (score == 2) {
        LATD = 0b1011011;
    } else if (score == 3) {
        LATD = 0b1001111;
    } else if (score == 4) {
        LATD = 0b1100110;
    } else if (score == 5) {
        LATD = 0b1101101;
    }
}

void displayDash() {
    LATD = 0b1000000;
}

struct player* getCurrentPlayer() {
    struct player *p;
    switch (selectedPlayerId) {
        case 0:
            p = &player1;
            break;
        case 1:
            p = &player2;
            break;
        case 2:
            p = &player3;
            break;
        case 3:
            p = &player4;
            break;
    }
    return p;
}

void switchPlayer() {
    
    struct player* player = getCurrentPlayer();
    if (player->type != 5 && player->type != 6){
        LCDGoto(player->x, player->y);
        player->type -= 3;
        LCDDat(player->type);

        selectedPlayerId += 1;
        selectedPlayerId %= 4;

        player = getCurrentPlayer();
        LCDGoto(player->x, player->y);
        player->type += 3;

        if(player->x == frisbeeCord.x && player->y == frisbeeCord.y){
            player->type += 2;
        }
        LCDDat(player->type);
    }
}

void showPlayers(){
    LCDGoto(player1.x, player1.y);
    LCDDat(player1.type);
    LCDGoto(player2.x, player2.y);
    LCDDat(player2.type);
    LCDGoto(player3.x, player3.y);
    LCDDat(player3.type);
    LCDGoto(player4.x, player4.y);
    LCDDat(player4.type); 
}

void newDirection(struct player* curPlayer, int direction){
    if (direction == 0 && curPlayer->y < 4) {
        curPlayer->y++;
    }
    if (direction == 1 && curPlayer->x < 16) {
        curPlayer->x++;
    }
    if (direction == 2 && curPlayer->y > 1) {
        curPlayer->y--;
    }
    if (direction == 3 && curPlayer->x > 1) {
        curPlayer->x--;
    }
    if (direction == 4 && curPlayer->x <16 && curPlayer->y < 4) {
        curPlayer->y++;
        curPlayer->x++;     
    }
    if (direction == 5 && curPlayer->x >1 && curPlayer->y < 4) {
        curPlayer->y++;
        curPlayer->x--;
    }
    if (direction == 6 && curPlayer->x <16 && curPlayer->y > 1) {
        curPlayer->y--;
        curPlayer->x++;
    }
    if (direction == 7 && curPlayer->x >1 && curPlayer->y > 1) {
        curPlayer->y--;
        curPlayer->x--;
    }
}

void randomMove(){
    int randomDirection;
    if(player1.id != selectedPlayerId){
        randomDirection = random_generator(8);
        LCDGoto(player1.x,player1.y);
        LCDStr(" ");
        newDirection(&player1, randomDirection);
    }
    if(player2.id != selectedPlayerId){
        randomDirection = random_generator(8);
        LCDGoto(player2.x,player2.y);
        LCDStr(" ");
        newDirection(&player2, randomDirection);
    }
    if(player3.id != selectedPlayerId){
        randomDirection = random_generator(8);
        LCDGoto(player3.x,player3.y);
        LCDStr(" ");
        newDirection(&player3, randomDirection);
    }
    if(player4.id != selectedPlayerId){
        randomDirection = random_generator(8);
        LCDGoto(player4.x,player4.y);
        LCDStr(" ");
        newDirection(&player4, randomDirection);
    }
    showPlayers();
}

void movePlayer(int direction) {
    struct player* curPlayer = getCurrentPlayer();
    LCDGoto(curPlayer->x, curPlayer->y);
    if(activeMode == 0){
        if (curPlayer->type == 5) {
            curPlayer->type = 3;
            LCDDat(2);
        } else if (curPlayer->type == 6) {
            curPlayer->type = 4;
            LCDDat(2);
        } else {
            LCDStr(" ");
        }
    }else{
        LCDStr(" ");
    }

    newDirection(curPlayer, direction);
    
    if(activeMode == 0){
        if (frisbeeCord.x == curPlayer->x && frisbeeCord.y == curPlayer->y && curPlayer->type == 3) {
            curPlayer->type = 5;
        }
        if (frisbeeCord.x == curPlayer->x && frisbeeCord.y == curPlayer->y && curPlayer->type == 4) {
            curPlayer->type = 6;
        }
    }
    showPlayers();
    LCDGoto(curPlayer->x, curPlayer->y);
    LCDDat(curPlayer->type);
}


void showScore() {
    LATAbits.LATA3 = 1;
    displayScore(score0);
    __delay_us(50);
    LATAbits.LATA3 = 0;
    
    LATAbits.LATA4 = 1;
    displayDash();
    __delay_us(50);
    LATAbits.LATA4 = 0;

    LATAbits.LATA5 = 1;
    displayScore(score1);
    __delay_us(50);
    LATAbits.LATA5 = 0;
}

void endGame(int team){
    LCDCmd(LCD_CLEAR);
    char text[15];
    sprintf(text, "Team %d wins.", team);
    LCDGoto(1,1);
    LCDStr (text);
}

void getScore(int team){
    if(team == 0){
        score0 ++;
        if(score0 == 5)
            endGame(0);
    }else{
        score1 ++;
        if(score1 == 5)
            endGame(1);
    }
}

void throwFrisbee() {
    struct player* player = getCurrentPlayer();
    
    if (player->x == frisbeeCord.x && player->y == frisbeeCord.y && activeMode == 0) {
        steps = compute_frisbee_target_and_route(frisbeeCord.x, frisbeeCord.y);
        activeMode = 1;
    }
}

void __interrupt(high_priority) FNC() {
    showScore();
    if (INTCONbits.TMR0IF) { // Timer Interrupt
        if (rbPressed) {
            if (counter0-- == 0) {
                rbPressed = 0;
                counter0 = 300;
            }
        }

        TMR0 = 0;
        TMR0H = 0XFF;
        TMR0L = 0x67;
        INTCONbits.TMR0IF = 0;
    }

    if(PIR1bits.TMR1IF){
        TMR1 =0;
        TMR1H = 0x00;
        TMR1L = 0x00;
        PIR1bits.TMR1IF = 0;
    }

    if (PIR1bits.TMR2IF) {
        PIR1bits.TMR2IF = 0;
        TMR2 = 0xCC;
        if (activeMode) {
            if (counter1 % (CNT/2) == 0) {
                LCDGoto(frisbee_steps[steps - 1][0], frisbee_steps[steps - 1][1]);
                LCDDat(7);
            } else if (counter1 % (CNT/2) == (CNT/4)) {
                LCDGoto(frisbee_steps[steps - 1][0], frisbee_steps[steps - 1][1]);
                LCDStr(" ");
            }
            counter1--;
            if (counter1 == 0) {
                counter1 = CNT*speed;
                if (frisbeeIndex < steps) {
                    
                    LCDGoto(frisbeeCord.x, frisbeeCord.y);
                    LCDStr(" "); 
                    if(frisbeeIndex == 0){
                        struct player* player = getCurrentPlayer();
                        player->type -= 2;
                    }
                    showPlayers();
                    randomMove();
                    frisbeeCord.x = frisbee_steps[frisbeeIndex][0];
                    frisbeeCord.y = frisbee_steps[frisbeeIndex][1];
                    LCDGoto(frisbeeCord.x, frisbeeCord.y);
                    LCDDat(2);
                    frisbeeIndex++;
                }
                if (frisbeeIndex == steps) {
                    struct player* player = getCurrentPlayer();
                    LCDGoto(frisbeeCord.x, frisbeeCord.y);
                    LCDDat(2);
                    activeMode = 0;
                    frisbeeIndex = 0;
                    if (player->x == frisbeeCord.x && player->y == frisbeeCord.y) {
                        player->type += 2;
                        LCDGoto(frisbeeCord.x, frisbeeCord.y);
                        LCDDat(player->type);
                        
                        if (player->team == 0) {
                            getScore(0);
                        } else {
                            getScore(1);
                        }
                    }
                }

            }
        }
    }

    if (INTCONbits.INT0IF && !rbPressed) {
        rbPressed = 1;
        
        if(!PORTBbits.RB0 && !rbFlag[0]){           
            rbFlag[0] = 1;
            throwFrisbee();
        }else if (PORTBbits.RB0 && rbFlag[0]) {
            rbFlag[0] = 0;
        }
        
        INTCONbits.INT0IF = 0;
    }

    if (INTCON3bits.INT1IF && !rbPressed) {
        rbPressed = 1;
        
        if (!PORTBbits.RB1 && !rbFlag[1]) {
            switchPlayer();
            rbFlag[1] = 1;
        } else if (PORTBbits.RB1 && rbFlag[1]) {
            rbFlag[1] = 0;
        }
        
        INTCON3bits.INT1IF = 0;
    }

    if (INTCONbits.RBIF && !rbPressed) {
        
        if (!PORTBbits.RB4 && !rbFlag[4]) {
            rbPressed = 1;
            rbFlag[4] = 1;
            movePlayer(2);
        } else if (PORTBbits.RB4 && rbFlag[4]) {
            rbFlag[4] = 0;
        }
        
        if (!PORTBbits.RB5 &&!rbFlag[5]) {
            rbPressed = 1;
            rbFlag[5] = 1;
            movePlayer(1);
        } else if (PORTBbits.RB5 && rbFlag[5]) {
            rbFlag[5] = 0;
        }

        if (!PORTBbits.RB6 &&!rbFlag[6]) {
            rbPressed = 1;
            rbFlag[6] = 1;
            movePlayer(0);
        } else if (PORTBbits.RB6 && rbFlag[6]) {
            rbFlag[6] = 0;
        }

        if (!PORTBbits.RB7 &&!rbFlag[7]) {
            rbPressed = 1;
            rbFlag[7] = 1;
            movePlayer(3);
        } else if (PORTBbits.RB7 && rbFlag[7]) {
            rbFlag[7] = 0;
        }
        INTCONbits.RBIF = 0;
    }
}

void main(void) {
    initPorts();

    initADC();

    InitLCD();

    initVariables();

    char values[10] = {0};

    initInterrupts();
    initTimer0();
    initTimer1();
    initTimer2();
    
    while (1) {
        
        if (activeMode == 0 && CONVERT != readADCChannel(0)) {
            CONVERT = readADCChannel(0);
            speed = (CONVERT/256)+1;
            counter1 = CNT*speed;
        }

        showScore();
    }

    return;
}
