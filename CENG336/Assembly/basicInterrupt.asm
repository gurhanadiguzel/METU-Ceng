#include <xc.inc> ; This will select the correct header automatically

CONFIG WDT = OFF  ; Disable periodic resets by the watchdog timer
    
PSECT resetVec
    goto main

PSECT hiIntVec
    goto highISR
   
PSECT lowIntVec
    btfss INTCON3, INTCON3_INT1IF_POSITION
    retfie         ; only respond to INT1
   
    bcf INTCON3, INTCON3_INT1IF_POSITION ; clear the interrupt flag
   
    movwf 0x03   ; use this for saving the original value of wreg
    movlw 0x30     ; this is the value to compare against

    incf 0x01      ; increment
    cpfslt 0x01    ; if the contents of 0x01 is less than 0x30, skip the next instruction
    clrf 0x01
    movf 0x03, 0   ; restore the wreg

    retfie
   
main:
    movlw 00000110B  ; Corresponding tris bit must be configured as input
    movwf TRISB      ; Program int2/rb2 and int1/rb1 pins as input
    
    clrf 0x01
    movlw 0x30
    movwf 0x02

    movlw 10011000B    ; int2 high, int1 low, enable both, clear both
    movwf INTCON3
   
    clrf RCON
    bsf RCON, RCON_IPEN_POSITION            ; enable priorities

    movlw 0xC0    ; enable interrupts
    movwf INTCON
   
    goto $
   
highISR:
    btfss INTCON3, INTCON3_INT2IF_POSITION
    retfie 1       ; only respond to INT2
   
    bcf INTCON3, INTCON3_INT2IF_POSITION ; clear the interrupt flag

    decfsz 0x02    ; decrement, if the contents of 0x02 is zero skip the next instruction
    retfie 1
   
    movlw 0x30
    movwf 0x02     ; reset the counter back to 0x30

    retfie 1
END