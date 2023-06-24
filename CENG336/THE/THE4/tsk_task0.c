#include "common.h"
#include "lcd.h"
/* 
Gürhan ?lhan ADIGÜZEL - 2448025
An?l ?çen             - 2448488
*/
/**********************************************************************
 * ----------------------- Local Variables ----------------------------
 **********************************************************************/
extern char moneyLCD[5];
extern char string_pool[5][16];
extern enum MODE mode;
extern struct ingredient ingredientList[4];
extern char money[2];
extern char catCount;
char ingList[4];
char catCountLCD[1];

char emptyString[16] = "                ";
char counter = 0;


int temp;

void showMoneyLCD() {

    temp = money[0];
    temp *= 256;
    temp += money[1];

    moneyLCD[0] = '0' + (temp / 10000);
    temp %= 10000;
    moneyLCD[1] = '0' + (temp / 1000);
    temp %= 1000;
    moneyLCD[2] = '0' + (temp / 100);
    temp %= 100;
    moneyLCD[3] = '0' + (temp / 10);
    temp %= 10;
    moneyLCD[4] = '0' + (temp);
}

void showLCD() {
    if (mode == ACTIVE) {
        LcdPrintString(emptyString, 0, 0);
        LcdPrintString(emptyString, 0, 1);

        showMoneyLCD();

        LcdPrintString(string_pool[2], 0, 0);
        LcdPrintString(moneyLCD, 11, 0);

        LcdPrintString(string_pool[3], 0, 1);
        catCountLCD[0] = '0' + catCount;
        LcdPrintString(catCountLCD, 3, 1);

        ingList[0] = ingredientList[0].name;
        ingList[1] = ingredientList[1].name;
        ingList[2] = ingredientList[2].name;
        ingList[3] = ingredientList[3].name;
        LcdPrintString(string_pool[4], 8, 1);
        LcdPrintString(ingList, 12, 1);

    }

}

/**********************************************************************
 * ------------------------------ TASK0 -------------------------------
 * 
 * Writes various strings to LCD 
 * 
 **********************************************************************/
TASK(TASK0) {

    SetRelAlarm(ALARM_TSK0, 50, 50);
    LcdPrintString(string_pool[0], 4, 0);
    LcdPrintString(string_pool[1], 6, 1);
    while (1) {
        WaitEvent(ALARM_EVENT);
        ClearEvent(ALARM_EVENT);
        counter++;
        if (counter == 20) {
            ClearLCDScreen();
            showLCD();
            counter = 0;
        }
    }

    TerminateTask();
}

/* End of File : tsk_task0.c */