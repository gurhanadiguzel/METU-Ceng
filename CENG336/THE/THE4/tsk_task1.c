#include "common.h"
/* 
Gürhan İlhan ADIGÜZEL - 2448025
Anıl İçen             - 2448488
*/
/**********************************************************************
 * -----------------------     COMMENT      ---------------------------
 Our design is implemented with the basics of RTOS. It is using many 
 RTOS utilities such as ring buffers, tasks and alarms. We used tasks to 
 receive and transmit data. We used ring buffer implementation to read 
 and write to buffers. TASK0 sets the LCD. TASK1 implements receive 
 portion of the code. TASK2 handles the tranmission part. We get the input
 from simulation and receive it in the TASK1. From there, we tried to use
 a priority algorithm made by us. It checks the customer's time limit and
 sort it by incrementally. Then, we toss the ingredients when we do not 
 need the ingredients we have. It is not implemented perfectly due to 
 time limitation of 36 hours only. For the hard level, we used flags to 
 hold transmit data before getting an output from hash function. We used 
 structures to be consistent around the code. We used tasks to hold the 
 50+-20 ms time limitation. Alarms are used to handle the 50 ms time limitation
 in the tasks. With the difficulties we had in the homework process such as,
 MPLAB and picsimlab breaking down consistently, we tried our best to submit 
 the homework. (05.34 AM)
 **********************************************************************/

void patienceTest();
void judgeFunction(struct cat* judge);

/**********************************************************************
 * ----------------------- GLOBAL VARIABLES ---------------------------
 **********************************************************************/
extern enum STATE state;
extern enum MODE mode;
extern char response[30];
char dataSize;
char bufferReceive[30];

struct cat cat1;
struct cat cat2;
struct cat cat3;
struct cat* patienceQueue[3];
struct cat judge;

struct ingredient ingredientList[4];
char money[2];
char cookStatus[6];
char catCount = 0;
int remainingIngCount = 0;

char hash[8];
char hashOutput[16];
char slowCookStatus[5];

char secondIng = 'N';
char checkCondition = 'O';
char tossCount, tossIndex1, tossIndex2;
char tossStatus[4];
char judgeIndex;
char hashFlag = 0;
char tossFlag = 0;
char cookFlag = 0;

char x, y;

/**********************************************************************
 * ----------------------- LOCAL FUNCTIONS ----------------------------
 **********************************************************************/
/* taking proper encoder responses */
void getResponse() {
    dataSize = receiveResponsePop(bufferReceive);
    if (dataSize) {
        if (bufferReceive[0] == 'G' && bufferReceive[1] == 'O') {
            // GO Received! Start the game!
            mode = ACTIVE;
            checkCondition = 'W';
        } else if (bufferReceive[0] == 'R') {
            if (cat1.id != bufferReceive[1]) {
                cat1.id = bufferReceive[1];
                cat1.cooking = 0;
                cat1.ing1 = bufferReceive[2];
                cat1.ing2 = bufferReceive[3];
                cat1.firstIng = 0;
                cat1.secondIng = 0;
            }
            cat1.duration = bufferReceive[4];

            if (cat2.id != bufferReceive[5]) {
                cat2.id = bufferReceive[5];
                cat2.cooking = 0;
                cat2.ing1 = bufferReceive[6];
                cat2.ing2 = bufferReceive[7];
                cat2.firstIng = 0;
                cat2.secondIng = 0;
            }
            cat2.duration = bufferReceive[8];

            if (cat3.id != bufferReceive[9]) {
                cat3.id = bufferReceive[9];
                cat3.cooking = 0;
                cat3.ing1 = bufferReceive[10];
                cat3.ing2 = bufferReceive[11];
                cat3.firstIng = 0;
                cat3.secondIng = 0;
            }
            cat3.duration = bufferReceive[12];

            if (ingredientList[0].name != bufferReceive[13]) {
                ingredientList[0].name = bufferReceive[13];
                ingredientList[0].status = '0';
            }
            if (ingredientList[1].name != bufferReceive[14]) {
                ingredientList[1].name = bufferReceive[14];
                ingredientList[1].status = '0';
            }
            if (ingredientList[2].name != bufferReceive[15]) {
                ingredientList[2].name = bufferReceive[15];
                ingredientList[2].status = '0';
            }
            if (ingredientList[3].name != bufferReceive[16]) {
                ingredientList[3].name = bufferReceive[16];
                ingredientList[3].status = '0';
            }
            money[0] = bufferReceive[17];
            money[1] = bufferReceive[18];

            patienceTest();

            catCount = 0;
            if (cat1.id != 0) catCount++;
            if (cat2.id != 0) catCount++;
            if (cat3.id != 0) catCount++;

            for (x = 0; x < 3; x++) {

                if (patienceQueue[x]->id == 0)continue;

                if (patienceQueue[x]->ing2 == 'J' && patienceQueue[x]->cooking != 1) {
                    judgeFunction(patienceQueue[x]);
                    continue;
                }

                if (patienceQueue[x]->cooking == 1)continue;

                remainingIngCount = 0;
                if (patienceQueue[x]->ing1 != 'N')remainingIngCount++;
                if (patienceQueue[x]->ing2 != 'N')remainingIngCount++;
                secondIng = 'N';

                for (y = 0; y < 4; y++) {
                    if (ingredientList[y].status == 'C')continue;
                    if (ingredientList[y].name == 'N')continue;

                    if (!patienceQueue[x]->firstIng) {
                        if (patienceQueue[x]->ing1 == ingredientList[y].name) {
                            remainingIngCount--;
                            if (remainingIngCount != 0) {
                                secondIng = y;
                                patienceQueue[x]->firstIng = 1;
                                continue;

                            }
                        }
                    }

                    if (!patienceQueue[x]->secondIng) {
                        if (patienceQueue[x]->ing2 == ingredientList[y].name) {
                            remainingIngCount--;
                            if (remainingIngCount != 0) {
                                secondIng = y;
                                patienceQueue[x]->secondIng = 1;
                                continue;
                            }
                        }
                    }

                    if (remainingIngCount == 0) {
                        ingredientList[y].status = 'C';
                        if (secondIng != 'N') {
                            ingredientList[secondIng].status = 'C';
                        }
                        //?????
                        checkCondition = 'R';
                        patienceQueue[x]->cooking = 1;
                        cookStatus[0] = '$';
                        cookStatus[1] = 'C';
                        cookStatus[2] = patienceQueue[x]->id;
                        cookStatus[3] = y;
                        cookStatus[4] = secondIng;
                        cookStatus[5] = ':';
                        cookFlag = 1;
                        break;
                    }
                }
            }
            /* toss the unused ingredients. */
            for (tossIndex1 = 0; tossIndex1 < 4; tossIndex1++) {
                if (ingredientList[tossIndex1].name == 'N')continue;
                tossCount = 0;
                for (tossIndex2 = tossIndex1 + 1; tossIndex2 < 4; tossIndex2++) {
                    if (ingredientList[tossIndex1].name == ingredientList[tossIndex2].name ) {
                        tossCount++;
                    }
                    if (tossCount == 2 && (ingredientList[tossIndex1].status != 'C' && ingredientList[tossIndex1].status != 'S')) {
                        tossStatus[0] = '$';
                        tossStatus[1] = 'T';
                        tossStatus[2] = tossIndex1;
                        tossStatus[3] = ':';
                        checkCondition = 'T';
                        break;
                    }
                }
            }
            /* alternative solution for toss. */
            //            for (tossIndex1 = 0; tossIndex1 < 4; tossIndex1++) {
            //                if (patienceQueue[tossIndex1]->id == 0 || patienceQueue[tossIndex1]->cooking) {
            //                    tossFlag = 0;
            //                    break;
            //                }
            //                tossFlag = 1;
            //
            //
            //            }
            //            if (tossFlag) {
            //                for (tossIndex2 = 0; tossIndex2 < 4; tossIndex2++) {
            //                    if (ingredientList[tossIndex2].name == 'N') {
            //                        tossFlag = 0;
            //                        break;
            //                    }
            //                    tossFlag = 1;
            //                }
            //            }
            //            if(tossFlag) {
            //                tossStatus[0] = '$';
            //                tossStatus[1] = 'T';
            //                tossStatus[2] = 0;
            //                tossStatus[3] = ':';
            //                checkCondition = 'T';
            //            }

        } else if (bufferReceive[0] = 'H') {
            checkCondition = 'H';
            hash[0] = bufferReceive[1];
            hash[1] = bufferReceive[2];
            hash[2] = bufferReceive[3];
            hash[3] = bufferReceive[4];
            hash[4] = bufferReceive[5];
            hash[5] = bufferReceive[6];
            hash[6] = bufferReceive[7];
            hash[7] = bufferReceive[8];
            compute_hash(hash, hashOutput);
            if (hashOutput[0])hashFlag = 1;
        } else if (bufferReceive[0] == 'E') {
            mode = END;
            checkCondition = 'X';

        }
    }
}
 
/* handle with food judge. */
void judgeFunction(struct cat * judge) {
    for (judgeIndex = 0; judgeIndex < 4; judgeIndex++) {
        if (ingredientList[judgeIndex].name != 'N' && ingredientList[judgeIndex].status != 'C') {
            slowCookStatus[0] = '$';
            slowCookStatus[1] = 'S';
            slowCookStatus[2] = judge->id;
            slowCookStatus[3] = judgeIndex;
            slowCookStatus[4] = ':';
            judge->cooking = 1;
            checkCondition = 'S';
            break;
        }
    }
}

/* this is a sorting algorithm according to the patience of customers. */
void patienceTest() {
    if (cat1.duration < cat2.duration) {
        if (cat1.duration < cat3.duration) {
            patienceQueue[0] = &cat1;
            if (cat2.duration < cat3.duration) {
                patienceQueue[1] = &cat2;
                patienceQueue[2] = &cat3;
            } else {
                patienceQueue[1] = &cat3;
                patienceQueue[2] = &cat2;
            }
        } else {
            patienceQueue[0] = &cat3;
            patienceQueue[1] = &cat1;
            patienceQueue[2] = &cat2;
        }


    } else {
        if (cat2.duration < cat3.duration) {
            patienceQueue[0] = &cat2;
            if (cat3.duration < cat1.duration) {

                patienceQueue[1] = &cat3;
                patienceQueue[2] = &cat1;
            } else {
                patienceQueue[1] = &cat1;
                patienceQueue[2] = &cat3;
            }
        } else {
            patienceQueue[0] = &cat3;
            patienceQueue[1] = &cat2;
            patienceQueue[2] = &cat1;
        }
    }

}

/**********************************************************************
 * ------------------------------ TASK1 -------------------------------
 *
 * Basic echo function test. Typing a single char should reply with the same char, 
 * then some chars that alphabetically precede this char. You will need buffers to echo strings.
 *
 **********************************************************************/
/* handling with taking response. */
TASK(TASK1) {
    PIE1bits.RCIE = 1; // enable USART receive interrupt
    SetRelAlarm(ALARM_TSK1, 50, 50); // this is the alarm that triggers receive task
    while (1) {
        WaitEvent(ECHO_EVENT);
        ClearEvent(ECHO_EVENT);
        getResponse();
    }
    TerminateTask();
}

/* End of File : tsk_task1.c */
