PROCESSOR    18F8722

#include <xc.inc>
; CONFIG1H
  CONFIG  OSC = HSPLL           ; Oscillator Selection bits (HS oscillator, PLL enabled (Clock Frequency = 4 x FOSC1))
  CONFIG  FCMEN = OFF           ; Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
  CONFIG  IESO = OFF            ; Internal/External Oscillator Switchover bit (Two-Speed Start-up disabled)

; CONFIG2L
  CONFIG  PWRT = OFF            ; Power-up Timer Enable bit (PWRT disabled)
  CONFIG  BOREN = OFF           ; Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
  CONFIG  BORV = 3              ; Brown-out Voltage bits (Minimum setting)

; CONFIG2H
  CONFIG  WDT = OFF             ; Watchdog Timer (WDT disabled (control is placed on the SWDTEN bit))
  CONFIG  WDTPS = 32768         ; Watchdog Timer Postscale Select bits (1:32768)

; CONFIG3L
  CONFIG  MODE = MC             ; Processor Data Memory Mode Select bits (Microcontroller mode)
  CONFIG  ADDRBW = ADDR20BIT    ; Address Bus Width Select bits (20-bit Address Bus)
  CONFIG  DATABW = DATA16BIT    ; Data Bus Width Select bit (16-bit External Bus mode)
  CONFIG  WAIT = OFF            ; External Bus Data Wait Enable bit (Wait selections are unavailable for table reads and table writes)

; CONFIG3H
  CONFIG  CCP2MX = PORTC        ; CCP2 MUX bit (ECCP2 input/output is multiplexed with RC1)
  CONFIG  ECCPMX = PORTE        ; ECCP MUX bit (ECCP1/3 (P1B/P1C/P3B/P3C) are multiplexed onto RE6, RE5, RE4 and RE3 respectively)
  CONFIG  LPT1OSC = OFF         ; Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
  CONFIG  MCLRE = ON            ; MCLR Pin Enable bit (MCLR pin enabled; RG5 input pin disabled)

; CONFIG4L
  CONFIG  STVREN = ON           ; Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
  CONFIG  LVP = OFF             ; Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
  CONFIG  BBSIZ = BB2K          ; Boot Block Size Select bits (1K word (2 Kbytes) Boot Block size)
  CONFIG  XINST = OFF           ; Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

; CONFIG5L
  CONFIG  CP0 = OFF             ; Code Protection bit Block 0 (Block 0 (000800, 001000 or 002000-003FFFh) not code-protected)
  CONFIG  CP1 = OFF             ; Code Protection bit Block 1 (Block 1 (004000-007FFFh) not code-protected)
  CONFIG  CP2 = OFF             ; Code Protection bit Block 2 (Block 2 (008000-00BFFFh) not code-protected)
  CONFIG  CP3 = OFF             ; Code Protection bit Block 3 (Block 3 (00C000-00FFFFh) not code-protected)
  CONFIG  CP4 = OFF             ; Code Protection bit Block 4 (Block 4 (010000-013FFFh) not code-protected)
  CONFIG  CP5 = OFF             ; Code Protection bit Block 5 (Block 5 (014000-017FFFh) not code-protected)
  CONFIG  CP6 = OFF             ; Code Protection bit Block 6 (Block 6 (01BFFF-018000h) not code-protected)
  CONFIG  CP7 = OFF             ; Code Protection bit Block 7 (Block 7 (01C000-01FFFFh) not code-protected)

; CONFIG5H
  CONFIG  CPB = OFF             ; Boot Block Code Protection bit (Boot Block (000000-0007FFh) not code-protected)
  CONFIG  CPD = OFF             ; Data EEPROM Code Protection bit (Data EEPROM not code-protected)

; CONFIG6L
  CONFIG  WRT0 = OFF            ; Write Protection bit Block 0 (Block 0 (000800, 001000 or 002000-003FFFh) not write-protected)
  CONFIG  WRT1 = OFF            ; Write Protection bit Block 1 (Block 1 (004000-007FFFh) not write-protected)
  CONFIG  WRT2 = OFF            ; Write Protection bit Block 2 (Block 2 (008000-00BFFFh) not write-protected)
  CONFIG  WRT3 = OFF            ; Write Protection bit Block 3 (Block 3 (00C000-00FFFFh) not write-protected)
  CONFIG  WRT4 = OFF            ; Write Protection bit Block 4 (Block 4 (010000-013FFFh) not write-protected)
  CONFIG  WRT5 = OFF            ; Write Protection bit Block 5 (Block 5 (014000-017FFFh) not write-protected)
  CONFIG  WRT6 = OFF            ; Write Protection bit Block 6 (Block 6 (01BFFF-018000h) not write-protected)
  CONFIG  WRT7 = OFF            ; Write Protection bit Block 7 (Block 7 (01C000-01FFFFh) not write-protected)

; CONFIG6H
  CONFIG  WRTC = OFF            ; Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
  CONFIG  WRTB = OFF            ; Boot Block Write Protection bit (Boot Block (000000-007FFF, 000FFF or 001FFFh) not write-protected)
  CONFIG  WRTD = OFF            ; Data EEPROM Write Protection bit (Data EEPROM not write-protected)

; CONFIG7L
  CONFIG  EBTR0 = OFF           ; Table Read Protection bit Block 0 (Block 0 (000800, 001000 or 002000-003FFFh) not protected from table reads executed in other blocks)
  CONFIG  EBTR1 = OFF           ; Table Read Protection bit Block 1 (Block 1 (004000-007FFFh) not protected from table reads executed in other blocks)
  CONFIG  EBTR2 = OFF           ; Table Read Protection bit Block 2 (Block 2 (008000-00BFFFh) not protected from table reads executed in other blocks)
  CONFIG  EBTR3 = OFF           ; Table Read Protection bit Block 3 (Block 3 (00C000-00FFFFh) not protected from table reads executed in other blocks)
  CONFIG  EBTR4 = OFF           ; Table Read Protection bit Block 4 (Block 4 (010000-013FFFh) not protected from table reads executed in other blocks)
  CONFIG  EBTR5 = OFF           ; Table Read Protection bit Block 5 (Block 5 (014000-017FFFh) not protected from table reads executed in other blocks)
  CONFIG  EBTR6 = OFF           ; Table Read Protection bit Block 6 (Block 6 (018000-01BFFFh) not protected from table reads executed in other blocks)
  CONFIG  EBTR7 = OFF           ; Table Read Protection bit Block 7 (Block 7 (01C000-01FFFFh) not protected from table reads executed in other blocks)

; CONFIG7H
  CONFIG  EBTRB = OFF           ; Boot Block Table Read Protection bit (Boot Block (000000-007FFF, 000FFF or 001FFFh) not protected from table reads executed in other blocks)


GLOBAL resetVec ;not necessary / for debugging
GLOBAL var1
GLOBAL var2
GLOBAL result
GLOBAL counter_1
GLOBAL counter_2
GLOBAL counter_3
    
;define space for the variables in RAM
PSECT udata_acs
var1:
    DS 1 ;allocate 1 byte for var1
var2:
    DS 1 
temp_result:
    DS 1   
result: 
    DS 1
counter_1:
    DS 1
counter_2:
    DS 1
counter_3:
    DS 1

PSECT resetVec,class=CODE,reloc=2
resetVec:
    goto       init

PSECT code
waste_time:
    movlw 15
    movwf counter_1,a
    nop
    do_while_counter_1_not_zero:
        do_while_counter_2_not_zero:
            do_while_counter_3_not_zero:
                decf counter_3
                bnz do_while_counter_3_not_zero
            end_do_while_counter_3_not_zero:
            decf counter_2
            bnz do_while_counter_2_not_zero
        end_do_while_counter_2_not_zero:
        decf counter_1
        bnz do_while_counter_1_not_zero
    end_do_while_counter_1_not_zero:
    return
 
init:
    movlw 0b11110111 ;set RB3 as output
    movwf TRISB,a
 
main:

    clrf var1,a ; var1 = 0		
    clrf var2,a   ; var2 = 0		
    clrf result,a ; result = 0

    movlw 4     ; WREG = 4 hexadecimal -> 04h, binary -> 0100B
    movwf var1,a  ; var1 = 4; 

    movlw 5     ; WREG = 5
    movwf var2,a  ; var1 = 5; 

    setf LATB,a ; turn PORTB ON
    call fSum   ; call the function fSum and PC will push the next instruction address to the Stack
    movwf result,a; result = WREG
    
    comf result,a ; result = the complement of the result value
    call waste_time
    clrf LATB,a ; turn PORTB OFF
    call waste_time
    goto main   ; Jump to the label main 

fSum:
    clrf temp_result,a 	; temp_result = 0
    movf var1,W,a	; WREG = var1 = 4
    addwf var2,W,a 	; WREG = WREG + var2
    movwf temp_result,F,a   ; temp_result = WREG 
    return		; The function terminates

end resetVec


