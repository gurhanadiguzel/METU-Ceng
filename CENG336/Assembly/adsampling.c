/*
 * This file implements a simple periodic A/D sampling system, using timer 
 * interrupts to initiate conversion and A/D interrupts to detect end 
 * of conversion. For illustration purposes, it alternates between two
 * channels of A/D input for each conversion. We will also output each
 * analog reading on PORTB pins as the value of the most significant 3 bits. 
 * You can use the analog voltage stimulus feature of the simulator to test
 * the outcome. Place a breakpoint within the TMR0 ISR and you should see
 * PORTB output alternatingly show converted values from AN0 and AN1.
 * 
 * Timer0 will be used to generate a 1KHz interrupt
 * AN0/AN1 will be sampled at 1KHz (i.e. 500Hz for each channel)
 */

#include <xc.h>
#include <stdint.h>

// Preload value to generate a 1KHz overflow for 16bit Timer0
#define TMR0_PRELOAD 55536 // This is 65536-10000

void tmr0_isr() {
    INTCONbits.T0IF = 0; // Acknowledge interrupt
    // Preload the timer with the proper value
    TMR0H = (TMR0_PRELOAD >> 8) & 0xff;
    TMR0L = TMR0_PRELOAD & 0xff;
    // Start A/D comversion right away
    ADCON0bits.GO = 1; // Start next acquisition    
}
void adc_isr() {
    PIR1bits.ADIF = 0; // Acknowledge interrupt
    // Read result of A/D conversion and add an offset to round to the nearest 
    // value for the most significant 3 bits
    int16_t adval = ((ADRESH << 8) | ADRESL) + 0x3F;
    // Retrieve the most significant 3 bits of conversion
    uint8_t temp = (adval >> 7) & 0xFF;
    // Compute PORTB output
    PORTB = (temp == 0)?0x00:((0x01 << (temp))-1);
    // Toggle between channels AN0 and AN1 right away so the acquisition
    // capacitor can catch up until the next TMR0 ISR.
    ADCON0 ^= 0x04;
}
void __interrupt(high_priority) highPriorityISR(void) {
    if (INTCONbits.T0IF) tmr0_isr();
    if (PIR1bits.ADIF) adc_isr();
}
void __interrupt(low_priority) lowPriorityISR(void) {}

void init_ports() {
    TRISA = 0xFF; // Port A is all inputs (AN0, AN1 included)
    TRISB = 0x00; // PortB is all outputs
    PORTB = 0x00; // Output 0 for now.
}
void init_timer() {
    // Initialize Timer0 to generate an accurate 1KHz interrupt
    // 16bits, no prescaler. Timer will be turned on after interrupts are
    // initialized
    T0CON = 0x08;
}
void init_adc() {
    // ** Initial channel is AN0
    // ** ADC module is on and idle to begin with
    ADCON0 = 0x01;

    // ** Vref+ and Vref- are internally generated
    // ** Only AN0 and AN1 are configured as analog
    ADCON1 = 0x0D;
    
    // ** Right-justified output
    // ** Acquisition time is disabled since we will switch channels right after
    // the end of acquisition of one channel, and we will wait for the 
    // next timer interrupt before starting acquisition.
    // *** Choose 32Tosc as the conversion clock, which is the appropriate choice
    // for 18F8722 at 40MHz.
    ADCON2 = 0x82;

    // Preload the timer for the first run (Timer is not ON yet))
    TMR0H = (TMR0_PRELOAD >> 8) & 0xff;
    TMR0L = TMR0_PRELOAD & 0xff;    
}
void init_interrupts() {
    INTCON = 0x00;
    INTCONbits.TMR0IE = 1;// Enable TMR0 interrupt
    INTCONbits.PEIE = 1;  // Enable peripheral interrupts (for A/D)
    PIE1bits.ADIE = 1;    // Enable end of A/D conversion interrupt
}

void start_system() {
    T0CONbits.TMR0ON = 1; // Start Timer 0
    INTCONbits.GIE = 1;   // Enable global interrupts
}

void main(void) {
    init_ports();
    init_timer();
    init_adc();
    init_interrupts();
    start_system();
    while (1) { /*Nothing to do here */ }
}
