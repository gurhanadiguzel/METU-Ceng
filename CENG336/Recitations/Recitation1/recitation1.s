PROCESSOR    18F4620

#include <xc.inc>

; CONFIGURATION (DO NOT EDIT)
CONFIG OSC = HSPLL      ; Oscillator Selection bits (HS oscillator, PLL enabled (Clock Frequency = 4 x FOSC1))
CONFIG FCMEN = OFF      ; Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
CONFIG IESO = OFF       ; Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)
; CONFIG2L
CONFIG PWRT = ON        ; Power-up Timer Enable bit (PWRT enabled)
CONFIG BOREN = OFF      ; Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
CONFIG BORV = 3         ; Brown Out Reset Voltage bits (Minimum setting)
; CONFIG2H
CONFIG WDT = OFF        ; Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
; CONFIG3H
CONFIG PBADEN = OFF     ; PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
CONFIG LPT1OSC = OFF    ; Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
CONFIG MCLRE = ON       ; MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)
; CONFIG4L
CONFIG LVP = OFF        ; Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
CONFIG XINST = OFF      ; Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

; GLOBAL SYMBOLS
; You need to add your variables here if you want to debug them.
GLOBAL var1
GLOBAL var2
GLOBAL var3

; Define space for the variables in RAM
PSECT udata_acs
var1:
    DS 1 
var2:
    DS 1 
var3:
    DS 1 

PSECT resetVec,class=CODE,reloc=2
resetVec:
    goto       main

PSECT CODE
main:
    clrf TRISA ; make PORTA an output
    setf TRISB ; make PORTB an input
    clrf var1 ; var1 = 0
    setf var2 ; var1 = 11111111B = 255
    ; var3 = var2
    movff var2, var3
    ; var3 = 42
    movlw 42
    movwf var3
    ; WREG = var1
    movf var2, W
    movlw 00000111B ; light up RA1, RA2, RA3
    movwf LATA
    call busy_wait
    clrf LATA
    clrf var1
    clrf var2
main_loop:
    call check_buttons
    call metronome_update
    goto main_loop

    
busy_wait:
    ; BUSY WAITING
    ; for(var2 = 255; var1 > 0; var2--) for(var1 = 0; var1 < 256; var1++)
    setf var2 ; var2 = 255
    clrf var1 ; var1 = 0
    outer_loop_start:
	loop_start:
	    incfsz var1 ; var1 += 1; if (var1 == 0) skip next
	    goto loop_start
	decf var2
	bnz outer_loop_start
    ; 8 bit
    ; var1 = 255
    ; var1 = 0
    return

check_buttons:
    btfsc PORTB, 0 ; check RB0
    call rb0_pressed ; we will execute this if RB0 = 1
    return

rb0_pressed:
    return

metronome_update:
    movlw 2
    addwf var1 ; var1 += 2
    bc var1_overflown ; if var1 is overflown
    return ; otherwise return
var1_overflown:
    incf var2
    bc var2_overflown
    return
var2_overflown:
    comf LATA
    return

end resetVec
