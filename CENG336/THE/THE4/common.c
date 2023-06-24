#include "common.h"
#include "lcd.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* 
Gürhan İlhan ADIGÜZEL - 2448025
Anıl İçen             - 2448488
*/

void transmitCommand();
void receiveResponse();
void transmitCommandPush(char *str, unsigned char size);
unsigned char receiveResponsePop(char* str);

/**********************************************************************
 * ----------------------- GLOBAL VARIABLES ---------------------------
 **********************************************************************/
enum STATE state = WAIT;
enum MODE mode = IDLE;
char response[30];
char command[30];
char responsePopIndex = 0;
char responsePushIndex = 0;
char commandPushIndex = 0;
char commandPopIndex = 0;
char flag = 0;
unsigned char i = 0, j = 0;

/**********************************************************************
 * ----------------------- GLOBAL FUNCTIONS ---------------------------
 **********************************************************************/
/* these functions are handling with responses with ring buffering.*/
void transmitCommandPush(char *str, unsigned char size) {
    flag = 1;
    j = 0;
    while (j < size) {
        command[commandPushIndex] = str[j];
        commandPushIndex = (commandPushIndex + 1) % 30;
        j++;

    }
    flag = 0;
    if (size > 0) {
        TXREG = command[commandPopIndex];
        commandPopIndex = (commandPopIndex + 1) % 30;
    }

}

void transmitCommand() {

    if (commandPopIndex != commandPushIndex && !flag) {
        TXREG = command[commandPopIndex];
        commandPopIndex = (commandPopIndex + 1) % 30;
    } else {
        PIR1bits.TXIF = 0;
        //        TXSTAbits.TXEN = 0; // disable transmission, nothing to push.
    }
}

unsigned char receiveResponsePop(char* str) {
    i = 0;
    while (response[responsePopIndex] != '$' && responsePopIndex != responsePushIndex) {
        responsePopIndex = (responsePopIndex + 1) % 30;
    }
    if (responsePopIndex == responsePushIndex) {
        return 0; // garbage
    }

    responsePopIndex = (responsePopIndex + 1) % 30; // skip $

    while (response[responsePopIndex] != ':' && responsePopIndex != responsePushIndex) {
        str[i] = response[responsePopIndex];
        i++;
        responsePopIndex = (responsePopIndex + 1) % 30;
    }

    if (responsePopIndex == responsePushIndex) return 0;

    responsePopIndex = (responsePopIndex + 1) % 30; // skip :

    return i;

}

/* Invoked when receive interrupt occurs; meaning that data is received */
void receiveResponse() {

    unsigned char rcvValue = RCREG;

    if (state == WAIT && rcvValue == '$') {
        response[responsePushIndex] = rcvValue;
        responsePushIndex = (responsePushIndex + 1) % 30;
        state = RECEIVE;
    } else if (state == RECEIVE && rcvValue != ':') {
        response[responsePushIndex] = rcvValue;
        responsePushIndex = (responsePushIndex + 1) % 30;
    } else if (state == RECEIVE && rcvValue == ':') {
        response[responsePushIndex] = rcvValue;
        responsePushIndex = (responsePushIndex + 1) % 30;
        state = WAIT;
    }

}
char hexDigits[] = "0123456789abcdef";

void compute_hash(unsigned char *inp, unsigned char *out) {
    unsigned long hash_L;
    unsigned long hash_H;
    unsigned long tmp, tmp_L, tmp_H;
    unsigned char c, *cp;
    unsigned int i;
    char j;

    cp = inp;
    for (i = 0; i < 200; i++) {
        hash_L = 5381;
        hash_H = 0;
        while ((c = *cp++)) {
            // hash_HL << 5 //
            tmp_H = (hash_H << 5) + ((hash_L & 0xF8000000) >> 27);
            tmp_L = hash_L << 5;
            // tmp_HL + hash_HL //
            tmp = hash_L + tmp_L;
            if ((tmp < hash_L) || (tmp < tmp_L)) // 4 byte unsigned int overflow !
                tmp_H += 1;
            tmp_L = tmp;
            tmp_H = hash_H + tmp_H;
            // tmp_HL + c //
            tmp = tmp_L + c;
            if ((tmp < c) || (tmp < tmp_L)) // 4 byte unsigned int overflow !
                tmp_H += 1;
            tmp_L = tmp;
            // update hash_HL with tmp_HL //
            hash_L = tmp_L;
            hash_H = tmp_H;
        }

        //write hex values of each byte
        for (j = 7; j >= 0; j--) {
            out[j] = hexDigits[hash_H & 0xF];
            hash_H >>= 4;
        }
        for (j = 15; j >= 8; j--) {
            out[j] = hexDigits[hash_L & 0xF];
            hash_L >>= 4;
        }
        out[16] = '\0';
        //repeat algo for new str
        cp = out;

    }
}
