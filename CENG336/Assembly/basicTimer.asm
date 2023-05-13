#include <xc.inc> ; This will select the correct header automatically

PSECT code
 
movlw 0x3C ; Load 15536 to the timer
movwf TMR0H
movlw 0xB0
movwf TMR0L
bcf INTCON, INTCON_TMR0IF_POSITION
movlw 0x83
movwf T0CON

movlw 0x00
movwf TRISD			; PortD pin 0 is output
movlw 0x01                      ; Send a digital 1
movwf PORTD
 
wait:
     btfss INTCON, INTCON_TMR0IF_POSITION
     bra wait
   
bcf INTCON, INTCON_TMR0IF_POSITION
xorwf PORTD                      ; The last bit will change state
bra wait
   
END


