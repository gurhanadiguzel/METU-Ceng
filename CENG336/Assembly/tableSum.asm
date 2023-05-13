#include <xc.inc>
    
first SET 1
last SET 20
count SET last - first + 1
i SET 0
baseAddress SET 0x00

PSECT code
 
; Write values from 1 to 20 into RAM locations 0x00 (from 0 decimal) to 0x13 (19 decimal)
REPT count
    MOVLW   first + i
    MOVWF   (baseAddress + i)
    i SET i + 1 
ENDM
 
; data is from 0x00 to 0x13
; count is in 0x14
; result will go to 0x15 (21)
 
countAddress SET baseAddress + count
resultAddress SET countAddress + 1; 0x15
 
; Write the number of elements at location 0x14 (20 in decimal)
MOVLW count
MOVWF countAddress
LFSR 0, baseAddress ; write 0x00 to FSR0    
MOVLW 0     ; clear the working register
 
ADDLOOP:
    ADDWF POSTINC0, 0    ; W += *ptr++
    DECFSZ countAddress; decrement the file register in countAddress and skip the next instruction if the result is zero
    GOTO ADDLOOP
    
    MOVWF resultAddress             ; put the result here
    GOTO $                          ; loop forever

    END


;A simple example that adds some numbers in memory and stores the result in another memory location. 
;Illustrates a basic usage of assembler as well as PIC instructions. Indirect addressing is exemplified.