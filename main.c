#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>

extern uint32_t rand_31();

volatile uint32_t millis = 0;

ISR(TIM0_OVF_vect) {
    static uint32_t nextChange = 0;
    static int8_t nextValue = 0;
    static uint16_t divisor = 0;
    uint8_t shadow = OCR0A;
    static int8_t goingUp = 0;
    ++millis;
    if (millis >= nextChange) {
        nextChange = rand_31() & 511;
        nextValue = ((rand_31() & 31) + 5);
        goingUp = rand_31() & 1;
        if (goingUp) {
            if ((uint16_t)nextValue + shadow > 255) nextValue = 255 - shadow;
        } else {
            if (nextValue > shadow) nextValue = shadow;
        }
        divisor = 0;
    }
    if (shadow != nextValue) {
        divisor += nextValue;
        while (divisor >= nextChange) {
            if (goingUp) shadow++; else shadow--;
        }
        OCR0A = shadow;
    }
}

int main(void) {
    // Set clock to 256khz
    CCP = 0xD8;
    CLKPSR = 5;

    DDRB = 1;

    // TC clock off, fast PWM mode 5(top=0xff), clear at match, set at bottom
    TCCR0A = 2 << COM0A0 | 1 << WGM00;
    TCCR0B = 1 << WGM02;
    // Enable timer interrupt, 
    TIMSK0 = 1 << TOIE0;
    // Start the clock
    TCCR0B |= 1 << CS00;

    OCR0A = 0;
}
