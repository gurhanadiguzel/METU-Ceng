#ifndef _DEFINE_H
#define _DEFINE_H

#include "device.h"

#define _XTAL_FREQ   10000000

/***********************************************************************
 * ------------------------ Timer settings -----------------------------
 **********************************************************************/
#define _10MHZ	63055
#define _16MHZ	61768
#define _20MHZ	60768
#define _32MHZ	57768
#define _40MHZ 	55768

/***********************************************************************
 * ----------------------------- Events --------------------------------
 **********************************************************************/
#define ALARM_EVENT       0x80
#define LCD_EVENT         0x01
#define ECHO_EVENT        0x40
#define UPDATE_EVENT      0x02



/***********************************************************************
 * ----------------------------- Alarms --------------------------------
 **********************************************************************/
#define ALARM_TSK0          0       /* Alarm ID (index) in tascdesc.c */
#define LCD_ALARM_ID        1       /* Alarm ID (index) in tascdesc.c */
#define ALARM_TSK1          2       /* Alarm ID (index) in tascdesc.c */
#define ALARM_TSK2          3       /* Alarm ID (index) in tascdesc.c */

/***********************************************************************
 * ---------------------- Task ID & Priorities -------------------------
 **********************************************************************/
#define TASK0_ID            1
#define LCD_ID              5
#define TASK1_ID            2
#define TASK2_ID            3

#define TASK0_PRIO          10
#define LCD_PRIO            10
#define TASK1_PRIO           7
#define TASK2_PRIO           7

/***********************************************************************
 * ---------------------- Global Variables -------------------------
 **********************************************************************/
enum MODE {
    ACTIVE,
    IDLE,
    END,
};

enum STATE {
    RECEIVE,
    WAIT,
};

struct cat {
    char id;
    char ing1;
    char ing2;
    char duration;
    char cooking;
    char firstIng;
    char secondIng;
};

struct ingredient {
    char name;
    char status;
};

/**********************************************************************
 * ----------------------- FUNCTION PROTOTYPES ------------------------
 **********************************************************************/
void transmitCommandPush(char *str, unsigned char size);
void transmitCommand();
unsigned char receiveResponsePop(char* str);
void receiveResponse();

#endif /* _DEFINE_H */


/* End of File : define.h */