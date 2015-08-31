// AVR LibC includes
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/sleep.h>
#include <avr/version.h>

/*****************************************************************************
*
*   Function name : USART_Init
*
*   Returns :       None
*
*   Parameters :    unsigned int baudrate
*
*   Purpose :       Initialize the USART
*
*****************************************************************************/
/*!
 *******************************************************************************
 *
 *  Calibrate the internal OSCCAL byte,
 *  using the external 32,768 kHz crystal as reference
 *  Implementation taken from Atmel AVR055 application note.
 *
 *  \note
 *     global interrupt has to be disabled before if not if will be
 *     disabled by this function.
 *
 ******************************************************************************/
#define EXTERNAL_TICKS 200   // ticks on XTAL. Modify to increase/decrease accuracy
#define XTAL_FREQUENCY 32768 // Frequency of the external oscillator
#define LOOP_CYCLES    7     // Number of CPU cycles the loop takes to execute
#ifndef F_CPU
#define F_CPU 1000000UL
#endif


void calibrate_rco(void)
{
    // Computes countVal for use in the calibration
    static const uint16_t countVal = (EXTERNAL_TICKS * F_CPU) / (XTAL_FREQUENCY * LOOP_CYCLES);

    cli();
    
    // Set up timer to be ASYNCHRONOUS from the CPU clock with a second
    // EXTERNAL 32,768kHz CRYSTAL driving it. No prescaling on asynchronous timer.
    ASSR = (1 << AS2);
    TCCR2A = (1 << CS20);

    // Calibrate using 128(0x80) calibration cycles
    uint8_t cycles = 0x80;
    uint16_t count;
    do {
        count = 0;
        TCNT2 = 0x00;       // Reset async timer/counter

        // Wait until async timer is updated  (Async Status reg. busy flags).
        while (ASSR & ((1 << OCR2UB) | (1 << TCN2UB) | (1 << TCR2UB)));

        // this loop needs to take exactly LOOP_CYCLES CPU cycles!
        // make sure your compiler does not mess with it!
        do {
            count++;
        } while (TCNT2 < EXTERNAL_TICKS);

        if (count > countVal)
            OSCCAL--;
        else if (count < countVal)
            OSCCAL++;
        else
            break; //cycles=0xFF;
    } while (--cycles);
}
