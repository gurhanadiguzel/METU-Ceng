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
GLOBAL isPaused
GLOBAL speed 
GLOBAL barLength
GLOBAL beat
GLOBAL num1
GLOBAL num2
GLOBAL rbFlag
    
; Define space for the variables in RAM
PSECT udata_acs
isPaused:
    DS 1 
speed: 
    DS 1
barLength:
    DS 1
beat:
    DS 1
num1:
    DS 1
num2:
    DS 1
rbFlag:
    DS 1

    
PSECT CODE
org 0x0000
    goto main
  
org 0x0008
    goto HighInterruptService
  
HighInterruptService:    
    ; WREG, STATUS and BSR registers are automatically saved to shadow registers
    ; They can be restored with retfie 1 command
    ; Check each interrupt flag. If it matches, go to its interrupt handler
    nop
    btfsc   INTCON, 0	; Check RBIF interrupt, skip if clear
    call    buttonInterrupt ;
    
    btfsc   INTCON, 2	; Check TMR0IF interrupt, skip if clear
    call    timer0_interrupt
    
    btfsc   PIR1, 0	; Check TMR1IF interrupt, skip if clear
    call    timer1Interrupt
    
    retfie  1		; No match
    
buttonInterrupt:
    movf    PORTB, W	    ; Moves portb to W
    xorwf   rbFlag, W	    ; Checks whether PORTB and rbFlag changed recently
    btfsc   WREG, 4	        ; Check RB4 is pressed, skip if not 
    call    pauseButton	    ; Calls pause function
    
    movf    PORTB, W	    ; Moves portb to W
    xorwf   rbFlag, W	    ; Checks whether PORTB and rbFlag changed recently
    btfsc   WREG, 5	        ; Check RB5 is pressed, skip if not
    call    increaseButton  ; Calls increase function
    
    movf    PORTB, W	    ; Moves portb to W
    xorwf   rbFlag, W	    ; Checks whether PORTB and rbFlag changed recently
    btfsc   WREG, 6	        ; Check RB6 is pressed, skip if not
    call    decreaseButton  ; Calls decrease function
    
    movf    PORTB, W	    ; Moves portb to W
    xorwf   rbFlag, W	    ; Checks whether PORTB and rbFlag changed recently
    btfsc   WREG, 7	        ; Check RB7 is pressed, skip if not
    call    resetButton	    ; Calls reset function
    
    bcf	    INTCON, 0	    ; Clear RBIF interrupt clear
    retfie  1 
    

timer0_interrupt:
    bcf	    INTCON, 2		        ; Clear Timer0 flag
    call    loadTimer0ForInterrupt  ; Calls load timer. loadTimer loads the timer to the according speed.
    btfsc   isPaused, 0		        ; Stop if paused
    retfie  1       
    
    movf    barLength, 0    ; BarLength to WREG
    cpfslt  beat	        ; Beat > WREG
    goto    resetBeat	    ; If beat is greater than barlength (edge case: barLength is decreased when beat was at the last bar)
    cpfseq  beat	        ; Checks if beat is equal to barLength. If equal, skips to resetBeat.
    goto    increaseBeat    ; If it is not equal to barLength goes to increaseBeat function.
    
    resetBeat:
	movlw	1   
	movwf	beat	; Loads 1 to beat.
	movlw	3	
	movwf	LATC	; Rc0, rc1 lights up by loading 3 LATC
	movlw	0xE7	; Initiates timer by loading E790 value. 
	movwf	TMR1H
	movlw	0x90
	movwf	TMR1L
	movlw	11111001B   
	movwf	T1CON       ;Bit8: Initiates timer1. 16 Bit enabled. 
                        ;Bit7: Clock is derived from Timer1 oscillator.
                        ;Bit5-4: 1:8 prescale value
                        ;Bit3: Timer1 oscillator is enabled
                        ;Bit2: Timer1 synchronize external clock input
                        ;Bit1: Internal clock set
                        ;Bit0: Enables timer1

	bsf	PIE1, 0	; Timer1 Interrupt enabled 
	retfie 	1
	
    increaseBeat:
	incf	beat    ; Increases beat
	movlw	1	    
	movwf	LATC    ; Rc0 lights up
	movlw	0xE7	; Init timer1 by loading E790 to Timer1
	movwf	TMR1H   
	movlw	0x90
	movwf	TMR1L
	movlw	11111001B
	movwf	T1CON   ;Bit8: Initiates timer1. 16 Bit enabled. 
                        ;Bit7: Clock is derived from Timer1 oscillator.
                        ;Bit5-4: 1:8 prescale value
                        ;Bit3: Timer1 oscillator is enabled
                        ;Bit2: Timer1 synchronize external clock input
                        ;Bit1: Internal clock set
                        ;Bit0: Enables timer1

	bsf	PIE1, 0 ; Timer1 Interrupt enabled 
	retfie	1

timer1Interrupt:
    bcf	    PIR1, 0	; Clear Timer1 flag
    bcf	    T1CON, 0	; Disable Timer1 (only timer0 inits timer1)
    clrf    LATC	; Turn off the RC lights
    retfie  1
    
timer2Interrupt:
    bcf     PIR1, 1     ; Clear Timer2 flag
    bcf     T2CON, 2    ; Disable timer 2
    comf    LATA            
    retfie  1

initVariables:
                        ; Initiates variables
    clrf    isPaused    ; Clears isPaused
    clrf    speed       ; Clears speed    
    clrf    barLength   ; Clears barLength
    clrf    rbFlag      ; Clears rbFlag
    
    movlw   1
    movwf   isPaused	; Initially system in paused state
    movlw   6
    movwf   speed	; Initially system speed is 6
    movlw   4
    movwf   barLength	; Initially system barLength is 4
    movlw   1
    movwf   beat	; Initially beat value is 1
    
    return
    
initPorts:
    clrf    INTCON  ; Clears INTCON
    clrf    TRISA   ; Make PORTA is output
    setf    TRISB   ; Make PORTB is input
    clrf    TRISC   ; Make PORTC is output
    clrf    TRISD   ; Make PORTD is output
    clrf    LATA    ; Clears LATA
    clrf    LATD    ; Clears LATD
    movlw   00000011B
    movwf   LATC    ; Set RC0 and RC1 light up.
    
    return
    
initInterrupts:
    movlw   11101000B	
    movwf   INTCON	; Make Global(GIE),Peripheral(PEIE),Timer0(TMR0IE) and RBIE enable.
    movlw   10000101B
    movwf   INTCON2	; Make PORTB and Timer0 change High Priority and PORTB pull-up disable.
    bcf	    RCON, 7	; Make Interrupt Priority(IPEN) disable.
    return
    
initTimer0:
    clrf    TMR0	; TMR0 = 0 
    movlw   10000011B	; 		
    movwf   T0CON	; Enable timer, 16-bit operation, falling(rising) edge, select prescaler 8
    call    loadTimer0ForInitializing	
    return

initTimer1:
    clrf    TMR1	; TMR1 = 0
    movlw   11111001B	; 16-bit, T1RUN, T1OSCEN, TMR1ON
    movwf   T1CON
    movlw   0xE7
    movwf   TMR1H
    movlw   0xA0
    movwf   TMR1L	; Make Initial value E7A0
    bsf	    PIE1,0	; TMR1IE Enable 
    return 

loadTimer0ForInitializing:
    movlw   1           
    cpfseq  speed			; Checks if speed is equal to 1
    goto    loadTimer0ForInitializing2	; If not equal to 1, goto loadTimer2
    movlw   0x0B
    movwf   TMR0H
    movlw   0xDE    
    movwf   TMR0L			; Set Timer0 initial value as 0BDE
    return
    loadTimer0ForInitializing2:
    movlw   2           
    cpfseq  speed			; Checks if speed is equal to 2
    goto    loadTimer0ForInitializing3	; If not equal to 2, goto loadTimer3
    movlw   0x24
    movwf   TMR0H
    movlw   0x48
    movwf   TMR0L			; Set Timer0 initial value as 2448
    return
    loadTimer0ForInitializing3:
    movlw   3
    cpfseq  speed			; Checks if speed is equal to 3
    goto    loadTimer0ForInitializing4	; If not equal to 3, goto loadTimer4
    movlw   0x3C
    movwf   TMR0H
    movlw   0xB2
    movwf   TMR0L			; Set Timer0 initial value as 3CB2
    return
    loadTimer0ForInitializing4:
    movlw   4
    cpfseq  speed			; Checks if speed is equal to 4
    goto    loadTimer0ForInitializing5	; If not equal to 4, goto loadTimer5
    movlw   0x55
    movwf   TMR0H
    movlw   0x1C
    movwf   TMR0L			; Set Timer0 initial value as 551C
    return
    loadTimer0ForInitializing5:
    movlw   5
    cpfseq  speed			; Checks if speed is equal to 5
    goto    loadTimer0ForInitializing6	; If not equal to 5, goto loadTimer6
    movlw   0x6D
    movwf   TMR0H
    movlw   0x86
    movwf   TMR0L			; Set Timer0 initial value as 6D86
    return
    loadTimer0ForInitializing6:
    movlw   6
    cpfseq  speed			; Checks if speed is equal to 6
    goto    loadTimer0ForInitializing7	; If not equal to 6, goto loadTimer7
    movlw   0x85
    movwf   TMR0H
    movlw   0xF0
    movwf   TMR0L			; Set Timer0 initial value as 85F0
    return
    loadTimer0ForInitializing7:
    movlw   7
    cpfseq  speed			; Checks if speed is equal to 7
    goto    loadTimer0ForInitializing8	; If not equal to 7, goto loadTimer8
    movlw   0x9E
    movwf   TMR0H
    movlw   0x5A
    movwf   TMR0L			; Set Timer0 initial value as 9E5A
    return
    loadTimer0ForInitializing8:
    movlw   8
    cpfseq  speed			; Checks if speed is equal to 8
    goto    loadTimer0ForInitializing9	; If not equal to 8, goto loadTimer9
    movlw   0xB6
    movwf   TMR0H
    movlw   0xC4
    movwf   TMR0L			; Set Timer0 initial value as B6C4
    return
    loadTimer0ForInitializing9:
    movlw   0xCF
    movwf   TMR0H
    movlw   0x2E
    movwf   TMR0L   ; Finally, if speed is not equal to any values from above, it is 9. 
                    ; And set timer's initial value to CF2E.
    return
    
 loadTimer0ForInterrupt:
    movlw   1
    cpfseq  speed   ;checks if speed is equal to 1
    goto    loadTimer0ForInterrupt2 ;if not equal to 1, goto loadTimer2
    movlw   0x0B
    movwf   TMR0H
    movlw   0xD5
    movwf   TMR0L	; set Timer0 initial value as 0BD5
    return
    loadTimer0ForInterrupt2:
    movlw   2
    cpfseq  speed   ;checks if speed is equal to 2
    goto    loadTimer0ForInterrupt3 ;if not equal to 2, goto loadTimer3
    movlw   0x24
    movwf   TMR0H
    movlw   0x3F
    movwf   TMR0L	; set Timer0 initial value as 243F
    return
    loadTimer0ForInterrupt3:
    movlw   3
    cpfseq  speed   ;checks if speed is equal to 3
    goto    loadTimer0ForInterrupt4 ;if not equal to 3, goto loadTimer4
    movlw   0x3C
    movwf   TMR0H
    movlw   0xA9
    movwf   TMR0L	; set Timer0 initial value as 3CA9
    return
    loadTimer0ForInterrupt4:
    movlw   4
    cpfseq  speed   ;checks if speed is equal to 4
    goto    loadTimer0ForInterrupt5 ;if not equal to 4, goto loadTimer5
    movlw   0x55
    movwf   TMR0H
    movlw   0x13
    movwf   TMR0L	; set Timer0 initial value as 5513
    return
    loadTimer0ForInterrupt5:
    movlw   5
    cpfseq  speed   ;checks if speed is equal to 5
    goto    loadTimer0ForInterrupt6 ;if not equal to 5, goto loadTimer6
    movlw   0x6D
    movwf   TMR0H
    movlw   0x7D
    movwf   TMR0L	; set Timer0 initial value as 6D7D
    return
    loadTimer0ForInterrupt6:
    movlw   6
    cpfseq  speed   ;checks if speed is equal to 6
    goto    loadTimer0ForInterrupt7 ;if not equal to 6, goto loadTimer7
    movlw   0x85
    movwf   TMR0H
    movlw   0xE7
    movwf   TMR0L	; set Timer0 initial value as 85E7
    return
    loadTimer0ForInterrupt7:
    movlw   7
    cpfseq  speed   ;checks if speed is equal to 7
    goto    loadTimer0ForInterrupt8 ;if not equal to 7, goto loadTimer8
    movlw   0x9E
    movwf   TMR0H
    movlw   0x51
    movwf   TMR0L	; set Timer0 initial value as 9E51
    return
    loadTimer0ForInterrupt8:
    movlw   8
    cpfseq  speed   ;checks if speed is equal to 8
    goto    loadTimer0ForInterrupt9 ;if not equal to 8, goto loadTimer9
    movlw   0xB6
    movwf   TMR0H
    movlw   0xBB
    movwf   TMR0L	; set Timer0 initial value as B6BB
    return
    loadTimer0ForInterrupt9:
    movlw   0xCF
    movwf   TMR0H
    movlw   0x25
    movwf   TMR0L	; set Timer0 initial value as CF25
    return
    
main:
    nop
    call    initVariables   ; Initialize Variables
    call    initPorts	    ; Initialize Ports
    call    initInterrupts  ; Initialize INTCON and INTCON2
    call    initTimer0	    ; Initialize Timer 0
    call    initTimer1	    ; Initialize Timer 1
    
main_loop:
    bsf	    LATA,0
    call    display1        ; SETS LATA TO 1 to display 1
    call    busyWait3ms     ; waits 3 ms
    bcf	    LATA,0          ; clears to turn off display 1
    
    bsf	    LATA,1
    call    display2        ; SETS LATA TO 2 to display 2
    call    busyWait3ms     ; waits 3 ms
    bcf	    LATA,1          ; clears to turn off display 2
    
    bsf	    LATA,2
    call    display3        ; SETS LATA TO 4 to display 3
    call    busyWait3ms     ; waits 3 ms
    bcf	    LATA,2          ; clears to turn off display 3
    
    bsf	    LATA,3
    call    display4        ; SETS LATA TO 8 to display 4
    call    busyWait3ms     ; waits 3 ms
    bcf	    LATA,3          ; clears to turn off display 4
    
    bra	    main_loop

display1:
    btfsc   isPaused, 0	    ; if system is paused display P
    call    writeP
    btfss   isPaused, 0	    ; if system is running display nothing
    clrf    LATD
    return 
    
display2:
    btfss   isPaused, 0	    ; if system is running display beat
    call    displayBeat
    btfsc   isPaused, 0	    ; if system is paused display nothing
    clrf    LATD
    return
    
display3:
    clrf    LATD
    btfss   isPaused, 0	    ; if system is running display dash else nothing
    bsf	    LATD, 6
    return

    
display4:
    btfsc   isPaused, 0	    ; if system is paused display speed
    call    displaySpeed
    btfss   isPaused, 0	    ; if system is running display barLength
    call    displayBarLength
    return
    
displayBeat:
    movlw   1
    cpfseq  beat               
    goto    displayBeat2    ;if beat is not 1, go to displayBeat2
    call    write1          ;if beat is 1, write1.
    return
    displayBeat2:
    movlw   2
    cpfseq  beat
    goto    displayBeat3    ;if beat is not 2, go to displayBeat3
    call    write2          ;if beat is 2, write2.
    return
    displayBeat3:
    movlw   3
    cpfseq  beat
    goto    displayBeat4    ;if beat is not 3, go to displayBeat4
    call    write3          ;if beat is 3, write3.
    return
    displayBeat4:
    movlw   4
    cpfseq  beat
    goto    displayBeat5    ;if beat is not 4, go to displayBeat5
    call    write4          ;if beat is 4, write4.
    return
    displayBeat5:
    movlw   5
    cpfseq  beat
    goto    displayBeat6    ;if beat is not 5, go to displayBeat6
    call    write5          ;if beat is 5, write5.
    return
    displayBeat6:
    movlw   6
    cpfseq  beat
    goto    displayBeat7    ;if beat is not 6, go to displayBeat7
    call    write6          ;if beat is 6, write6.
    return
    displayBeat7:
    movlw   7
    cpfseq  beat
    goto    displayBeat8    ;if beat is not 7, go to displayBeat8
    call    write7          ;if beat is 7, write7.
    return
    displayBeat8:   
    call    write8          ;if beat is 8, write8.
    return
    
displayBarLength:
    movlw   2
    cpfseq  barLength           
    goto    displayBarLength3   ;if barLength is not 2, goto displayBarLength3
    call    write2              ;if barLength is 2, write2
    return
    displayBarLength3:
    movlw   3
    cpfseq  barLength
    goto    displayBarLength4   ;if barLength is not 3, goto displayBarLength4
    call    write3              ;if barLength is 3, write3
    return
    displayBarLength4:
    movlw   4
    cpfseq  barLength
    goto    displayBarLength5   ;if barLength is not 4, goto displayBarLength5
    call    write4              ;if barLength is 4, write4
    return
    displayBarLength5:
    movlw   5
    cpfseq  barLength
    goto    displayBarLength6   ;if barLength is not 5, goto displayBarLength6
    call    write5              ;if barLength is 5, write5
    return
    displayBarLength6:
    movlw   6
    cpfseq  barLength
    goto    displayBarLength7   ;if barLength is not 6, goto displayBarLength7
    call    write6              ;if barLength is 6, write6
    return
    displayBarLength7:
    movlw   7
    cpfseq  barLength
    goto    displayBarLength8   ;if barLength is not 7, goto displayBarLength8
    call    write7              ;if barLength is 7, write7
    return
    displayBarLength8:
    call    write8              ;if barLength is 8, write8
    return
    
displaySpeed:
    movlw   1
    cpfseq  speed           
    goto    displaySpeed2       ;if speed is not 1, goto displaySpeed2 
    call    write1              ;if speed is 1, write1
    return
    displaySpeed2:
    movlw   2
    cpfseq  speed
    goto    displaySpeed3       ;if speed is not 2, goto displaySpeed3
    call    write2              ;if speed is 2, write2
    return
    displaySpeed3:
    movlw   3
    cpfseq  speed
    goto    displaySpeed4       ;if speed is not 3, goto displaySpeed4
    call    write3              ;if speed is 3, write3
    return      
    displaySpeed4:
    movlw   4
    cpfseq  speed
    goto    displaySpeed5       ;if speed is not 4, goto displaySpeed5
    call    write4              ;if speed is 4, write4
    return
    displaySpeed5:
    movlw   5
    cpfseq  speed
    goto    displaySpeed6       ;if speed is not 5, goto displaySpeed6
    call    write5              ;if speed is 5, write5
    return
    displaySpeed6:
    movlw   6
    cpfseq  speed
    goto    displaySpeed7       ;if speed is not 6, goto displaySpeed7 
    call    write6              ;if speed is 6, write6
    return
    displaySpeed7:
    movlw   7
    cpfseq  speed
    goto    displaySpeed8       ;if speed is not 7, goto displaySpeed8 
    call    write7              ;if speed is 7, write7
    return
    displaySpeed8:
    movlw   8
    cpfseq  speed
    goto    displaySpeed9       ;if speed is not 8, goto displaySpeed9 
    call    write8              ;if speed is 8, write8
    return
    displaySpeed9:
    call    write9              ;if speed is 9, write9
    return
    
pauseButton:
    btfss   rbFlag, 4           
    goto    setRb4Flag      ;checks if rbFlag's 4th bit is zero,if true, goto setRb4Flag.
                            ;if not continues the function.
    btg	    isPaused, 0     ;toggles isPaused variable.
    btfsc   isPaused, 0      
    bcf	    TMR0, 7         ;checks if isPaused's 0th bit is one, if true, clear TMR0's 7th bit to disable Timer0
    btfss   isPaused, 0     
    call    pauseButtonHelper   ;checks if isPaused's 0th bit is zero, if true, call pauseButtonHelper.
                                ;if not continues the function.
    bcf	    rbFlag, 4           ; clear rbFlag's 4th bit.
    return
    
pauseButtonHelper:   
    movlw   1
    movwf   beat         ;beat is set to 1.
    movlw   3
    movwf   LATC        ;LATC is set to 3. (rc0, rc1 is light up)
    call    initTimer0
    call    initTimer1
    return 
    
increaseButton:
    btfss   rbFlag, 5
    goto    setRb5Flag      ; if rbFlag's 5th bit is zero, goto setRb5Flag
    btfsc   isPaused, 0	    ; if program is paused increase speed
    call    increaseSpeed
    btfss   isPaused, 0	    ; if program is running increase barLength
    call    increaseBarLength
    bcf	    rbFlag, 5
    return
    
decreaseButton:
    btfss   rbFlag, 6
    goto    setRb6Flag      ; if rbFlag's 6th bit is zero, goto setRb6Flag
    btfsc   isPaused, 0	    ; if program is paused decrease speed
    call    decreaseSpeed
    btfss   isPaused, 0	    ; if program is running decrease barLength
    call    decreaseBarLength
    bcf	    rbFlag, 6
    return
    
resetButton:
    btfss   rbFlag, 7
    goto    setRb7Flag      ; if rbFlag's 7th bit is zero, goto setRb7Flag
    btfsc   isPaused, 0	    ; if program is paused reset speed
    call    resetSpeed
    btfss   isPaused, 0	    ; if program is running reset barLength
    call    resetBarLength
    bcf	    rbFlag, 7
    return

setRb4Flag:
    bsf rbFlag, 4           ;sets rbFlag's 4th bit to one.
    return
    
setRb5Flag:
    bsf rbFlag, 5           ;sets rbFlag's 5th bit to one.
    return
    
setRb6Flag:
    bsf rbFlag, 6           ;sets rbFlag's 6th bit to one.
    return

setRb7Flag: 
    bsf rbFlag, 7           ;sets rbFlag's 7th bit to one.
    return   

increaseBarLength:
    movlw   8
    cpfseq  barLength       ;if barLength is equal to 8, skip and return
    incf    barLength       ;if not increase barLength.
    return
    
decreaseBarLength:
    movlw   2
    cpfseq  barLength       ;if barLength is equal to 2, skip and return
    decf    barLength       ;if not decrease barLength.
    return
    
resetBarLength:
    movlw   4
    movwf   barLength       ;sets barLength to 4.
    return
    
increaseSpeed:
    movlw   9
    cpfseq  speed           ;if speed is equal to 9, skip and return
    incf    speed           ;if not, increase speed.
    return
    
decreaseSpeed:
    movlw   1
    cpfseq  speed           ;if speed is equal to 1, skip and return
    decf    speed            ;if not, decrease speed.
    return
    
resetSpeed:
    movlw   6       
    movwf   speed           ;sets speed to 6.
    return

writeP:
    movlw 1110011B
    movwf LATD              ;creates P in 7-segment display.
    return
write0:
    movlw 0111111B
    movwf LATD              ;creates 0 in 7-segment display.
    return
write1:
    movlw 0000110B
    movwf LATD              ;creates 1 in 7-segment display.
    return
write2:
    movlw 1011011B
    movwf LATD              ;creates 2 in 7-segment display.
    return  
write3:
    movlw 1001111B
    movwf LATD              ;creates 3 in 7-segment display.
    return
write4:
    movlw 1100110B              
    movwf LATD              ;creates 4 in 7-segment display.
    return
write5:
    movlw 1101101B  
    movwf LATD              ;creates 5 in 7-segment display.
    return
write6:
    movlw 1111101B
    movwf LATD              ;creates 6 in 7-segment display.
    return
write7:
    movlw 0000111B
    movwf LATD              ;creates 7 in 7-segment display.
    return
write8:
    movlw 1111111B
    movwf LATD              ;creates 8 in 7-segment display.
    return
write9:
    movlw 1101111B
    movwf LATD              ;creates 9 in 7-segment display.
    return
	
busyWait3ms:
    movlw 210
    movwf num1
    movlw 4
    movwf num2
    first_loop:
	second_loop:
	    decf num1
	    bnz second_loop
	decf num2
	bnz first_loop
    clrf num1
    clrf num2
    return
    
    
; Timer2 interrupt in 256 microseconds
start_timer_short:
    clrf    TMR2
    ; Bits 6-3 T2OUTPS3:T2OUTPS0 = 0000, no postscaling.
    ; Bit 2 TMR2ON = 1, enable timer2 now.
    ; Bits 1-0 T2CKPS1:T2CKPS0 = 00, no prescaling.
    movlw   00000100B
    movwf   T2CON
    return

; Timer2 interrupt in 4 milliseconds
start_timer_4ms:
    clrf    TMR2
    ; Bits 6-3 T2OUTPS3:T2OUTPS0 = 0000, no postscaling.
    ; Bit 2 TMR2ON = 1, enable timer2 now.
    ; Bits 1-0 T2CKPS1:T2CKPS0 = 11, 1:16 prescaling.
    movlw   00000111B
    movwf   T2CON
    return
    
; Timer2 interrupt in 3 milliseconds
start_timer_3ms:
    movlw   64
    movwf   TMR2
    ; Bits 6-3 T2OUTPS3:T2OUTPS0 = 0000, no postscaling.
    ; Bit 2 TMR2ON = 1, enable timer2 now.
    ; Bits 1-0 T2CKPS1:T2CKPS0 = 11, 1:16 prescaling.
    movlw   00000111B
    movwf   T2CON
    return

; Timer2 interrupt in 2 milliseconds
start_timer_2ms:
    movlw   128
    movwf   TMR2
    ; Bits 6-3 T2OUTPS3:T2OUTPS0 = 0000, no postscaling.
    ; Bit 2 TMR2ON = 1, enable timer2 now.
    ; Bits 1-0 T2CKPS1:T2CKPS0 = 11, 1:16 prescaling.
    movlw   00000111B
    movwf   T2CON
    return
