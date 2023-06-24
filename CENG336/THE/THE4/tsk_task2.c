#include "common.h"
/* 
Gürhan İlhan ADIGÜZEL - 2448025
Anıl İçen             - 2448488
*/
/**********************************************************************
 * ----------------------- GLOBAL VARIABLES ---------------------------
 **********************************************************************/
char bufferTransmit[30];
extern enum STATE state;
extern enum MODE mode;
extern char response[30];
extern char checkCondition;
extern char cookStatus[6];
extern char tossStatus[4];
extern char hashOutput[16];
extern char slowCookStatus[5];
extern char hashFlag;
extern char cookFlag;

char hashTempIndex;
/**********************************************************************
 * ----------------------- LOCAL FUNCTIONS ----------------------------
 **********************************************************************/
/* it transmits data required from task1. */

void updateCommand() {
    if (mode == ACTIVE) {
        if (checkCondition == 'W') {
            bufferTransmit[0] = '$';
            bufferTransmit[1] = 'W';
            bufferTransmit[2] = ':';
            transmitCommandPush(bufferTransmit, 3);
        } else if (checkCondition == 'R' && cookFlag) {
            bufferTransmit[0] = cookStatus[0];
            bufferTransmit[1] = cookStatus[1];
            bufferTransmit[2] = cookStatus[2];
            bufferTransmit[3] = cookStatus[3];
            bufferTransmit[4] = cookStatus[4];
            bufferTransmit[5] = cookStatus[5];
            transmitCommandPush(bufferTransmit, 6);
            checkCondition = 'W';
            cookFlag =0;
        } else if (checkCondition == 'T') {
            bufferTransmit[0] = tossStatus[0];
            bufferTransmit[1] = tossStatus[1];
            bufferTransmit[2] = tossStatus[2];
            bufferTransmit[3] = tossStatus[3];
            transmitCommandPush(bufferTransmit, 4);
            checkCondition = 'W';
        } else if (checkCondition == 'S') {
            bufferTransmit[0] = slowCookStatus[0];
            bufferTransmit[1] = slowCookStatus[1];
            bufferTransmit[2] = slowCookStatus[2];
            bufferTransmit[3] = slowCookStatus[3];
            bufferTransmit[4] = slowCookStatus[4];

            transmitCommandPush(bufferTransmit, 5);
            checkCondition = 'W';


        } else if (checkCondition == 'H' && hashFlag) {
            bufferTransmit[0] = '$';
            bufferTransmit[1] = 'H';
            bufferTransmit[2] = hashOutput[0];
            bufferTransmit[3] = hashOutput[1];
            bufferTransmit[4] = hashOutput[2];
            bufferTransmit[5] = hashOutput[3];
            bufferTransmit[6] = hashOutput[4];
            bufferTransmit[7] = hashOutput[5];
            bufferTransmit[8] = hashOutput[6];
            bufferTransmit[9] = hashOutput[7];
            bufferTransmit[10] = hashOutput[8];
            bufferTransmit[11] = hashOutput[9];
            bufferTransmit[12] = hashOutput[10];
            bufferTransmit[13] = hashOutput[11];
            bufferTransmit[14] = hashOutput[12];
            bufferTransmit[15] = hashOutput[13];
            bufferTransmit[16] = hashOutput[14];
            bufferTransmit[17] = hashOutput[15];
            bufferTransmit[18] = ':';
            transmitCommandPush(bufferTransmit, 19);
            checkCondition = 'W';
            hashFlag = 0;
            for( hashTempIndex=0; hashTempIndex<16;hashTempIndex++){
                hashOutput[hashTempIndex] = 0;
            }
        }

    }
}

/**********************************************************************
 * ------------------------------ TASK2 -------------------------------
 *
 * Basic echo function test. Typing a single char should reply with the same char, 
 * then some chars that alphabetically precede this char. You will need buffers to echo strings.
 *
 **********************************************************************/
/* handling with sending commands. */

TASK(TASK2) {
    PIE1bits.RCIE = 1; // enable USART receive interrupt
    SetRelAlarm(ALARM_TSK2, 50, 50); // this is the alarm that triggers receive task
    while (1) {
        WaitEvent(UPDATE_EVENT);
        ClearEvent(UPDATE_EVENT);
        updateCommand();
    }
    TerminateTask();
}

/* End of File : tsk_task2.c */
