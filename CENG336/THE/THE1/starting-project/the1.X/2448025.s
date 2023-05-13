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
GLOBAL barLength
GLOBAL barUsing 
GLOBAL temp
GLOBAL speed
GLOBAL position
GLOBAL isRB0Set
GLOBAL isRB1Set
GLOBAL isRB2Set
GLOBAL isRB3Set
GLOBAL isRB4Set
    
; Define space for the variables in RAM
PSECT udata_acs
var1:
    DS 1 
var2:
    DS 1 
var3:
    DS 1    
barLength:
    DS 1
barUsing: 
    DS 1
speed: 
    DS 1
temp:	
    DS 1
position:
    DS 1
isRB0Set:
    DS 1    
isRB1Set:
    DS 1
isRB2Set:
    DS 1
isRB3Set:
    DS 1
isRB4Set:
    DS 1

PSECT resetVec,class=CODE,reloc=2
resetVec:
    goto       main

PSECT CODE
main:
    clrf TRISA	; make PORTA an output
    setf TRISB	; make PORTB an input
    ; Set variables 0
    clrf speed	
    clrf temp
    clrf position
    clrf isRB0Set
    clrf isRB1Set
    clrf isRB2Set
    clrf isRB3Set
    clrf isRB4Set
    movlw 4	; set bar length 4
    movwf barLength
    ; Initialize
    movlw 7 ; light up RA1, RA2, RA3
    movwf LATA
    call wait1000
    clrf LATA
    clrf var1
    clrf var2
    
main_loop:
    movff barLength, barUsing 
    call metronomeUpdate
    goto main_loop
    
metronomeUpdate:
    movf barUsing, W
    cpfsgt barLength	;f,a compare f with WREG, Skip >
    call turnOn_ra1
    call turnOn_ra0
    btfss speed, 0  
    call wait250
    call wait250
    

    
    movf barUsing, W

    
    cpfsgt barLength	;f,a compare f with WREG, Skip >
    call turnOff_ra1
    call turnOff_ra0
    btfss speed, 0
    call wait250
    call wait250

    decf barUsing
    bnz metronomeUpdate
    return

turnOn_ra0:
    bsf LATA, 0
    return
turnOn_ra1:   
    bsf LATA, 1
    return
turnOn_ra2:
    bsf LATA,2
    return
turnOff_ra0:
    bcf LATA, 0
    return
turnOff_ra1:
    bcf LATA, 1
    return
turnOff_ra2:
    bcf LATA, 2
    return
    
wait250:
    movlw 2 
    movwf var3
    movlw 100
    setf var2 ; var2 = 255    
    waitLoop: ; for(var3=2; var1 > 0; var3--) 
	waitLoop1: ; for(var2=255; var1 > 0; var2--) 
	    call checkButtons
	    movwf var1
	    waitLoop2: ; for(var1 =0; var1<256; var1++)
		incfsz var1 ;var1 += 1: if(var1 == 0) skip next
		goto waitLoop2	
	    decf var2
	    bnz waitLoop1
	decf var3
	bnz waitLoop
    return
    
wait1000:
    call wait250
    call wait250
    call wait250
    call wait250
    return

checkButtons:
    btfsc PORTB, 0 ; check RB0
	call rb0Pressed ; we will execute this if RB0 = 1
	
    btfsc PORTB, 1 ; check RB1
	call rb1Pressed ; we will execute this if RB1 = 1
	
    btfsc PORTB, 2 ; check RB2+
	call rb2Pressed ; we will execute this if RB2 = 1
	
    btfsc PORTB, 3 ; check RB3+
	call rb3Pressed ; we will execute this if RB3 = 1
	
    btfsc PORTB, 4 ; check RB4+
	call rb4Pressed ; we will execute this if RB4 = 1
	
    btfsc isRB0Set,0 ; check RB0 released
	call pause
	
    btfsc isRB1Set,0 ; check RB1 released
	call speedUp
	
    btfsc isRB2Set,0 ; check RB2 released
	call resetBar
	
    btfsc isRB3Set,0 ; check RB3 released
	call decreaseBar

    btfsc isRB4Set,0 ; check RB4 released
	call increaseBar

    return

rb0Pressed:
    bsf isRB0Set, 0
    return
    
pause:
    movff LATA, temp
    btfss PORTB, 0 ; check RB0
    call rb0Released ; we will execute this if RB0 = 1
    return

resume:
    btfsc PORTB, 0 ; check RB0
    goto resume
    clrf LATA
    movff temp, LATA; we will execute this if RB0 = 1
    return
    
rb0Released: 
    bcf isRB0Set, 0  
    movlw 4
    movwf LATA
    btfss PORTB, 0 ; check RB0
    goto rb0Released
    btfsc PORTB, 0 ; check RB0
    goto resume
    return
    
rb1Pressed:
    bsf isRB1Set, 0
    return
    
speedUp:
    btfss PORTB, 1 ; check RB1
    call rb1Released ; we will execute this if RB0 = 1
    return

rb1Released:
    bcf isRB1Set, 0
    comf speed
    return
    
rb2Pressed:
    bsf isRB2Set, 0
    return

resetBar:
    btfss PORTB, 2 ; check RB2
    call rb2Released ; we will execute this if RB2 = 1
    return

rb2Released: ;6.1
    bcf isRB2Set, 0
    movff barLength, temp
    movf barUsing, W
    subwf temp
    movlw 4	; WREG  = 4
    cpfsgt temp ; temp > WREG
    goto notOverflow
    movwf barUsing
    movwf barLength	; barLength = 4
    return

notOverflow:
    subfwb temp ; temp = WREG - temp
    movff temp, barUsing
    movwf barLength	; barLength = 4
    return 
    
rb3Pressed:
    bsf isRB3Set, 0
    return

decreaseBar:
    btfss PORTB, 3 ; check RB3
    call rb3Released ; we will execute this if RB3 = 1
    return
    
rb3Released:
    bcf isRB3Set, 0
    decf barUsing
    decf barLength
    return   
    
rb4Pressed:
    bsf isRB4Set, 0
    return

increaseBar:
    btfss PORTB, 4 ; check RB4
    call rb4Released ; we will execute this if RB4 = 1
    return
    
rb4Released:
    bcf isRB4Set, 0
    incf barUsing
    incf barLength
    return

end resetVec

