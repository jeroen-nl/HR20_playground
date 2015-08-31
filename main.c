/*
 * main.c
 *
 * Created: 20-6-2015 17:34:37
 *  Author: Jeroen
 */ 



// program includes
//#include "main.h"
//! HR20 runs on 4MHz
#ifndef F_CPU
#define F_CPU 1000000UL
#endif

// standard includes
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// program includes
#include "uart.h"
#include "osc_cal.h"

volatile unsigned int count;
volatile unsigned char data;

static inline void OPEN (void) {
	PORTG  =  (1<<PG4);   // PG3 LOW, PG4 HIGH
	}
static inline void CLOSE(void) {
	PORTG  =  (1<<PG3);   // PG3 HIGH, PG4 LOW
	}
static inline void STOP (void) {
	PORTG  =  0;          // PG3 LOW, PG4 LOW
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Set input and output configuration
void init(void)
{
    // set prescaler = 8, Inter RC 8Mhz / 8 = 1Mhz
    CLKPR = (1<<CLKPS1) | (1<<CLKPS0);

	
	//! Disable Analog Comparator (power save)
	ACSR = (1<<ACD);

	//! Disable Digital input on PF0-7 (power save)
	DIDR0 = 0xFF;

	//! digital I/O port direction
	DDRG = (1<<PG3)|(1<<PG4); // PG3, PG4 Motor out

	//! enable pullup on all inputs (keys and m_wheel)
	//! ATTENTION: PB0 & PB6 is input, but we will select it only for read
	PORTB = (0<<PB0)|(1<<PB1)|(1<<PB2)|(1<<PB3)|(0<<PB6);
	DDRB = (1<<PB0)|(1<<PB4)|(1<<PB7)|(1<<PB6); // PB4, PB7 Motor out
	//HR20 without RFM
	DDRE = (1<<PE3)|(1<<PE1);  // PE3  activate lighteye and PE1 for TX RS232
	
	//PORTE = (1<<PE1)|(1<<PE0); //  TXD | RXD(pullup);

	DDRF = (1<<PF3);          // PF3  activate tempsensor
	PORTF = 0xf3;

}


int main(void)
{
	
init();
  //! activate PCINT0 + PCINT1
  EIMSK = (1<<PCIE1)|(1<<PCIE0);
  PORTE |= (1<<PE3);
  init_uart(9600,0);
  data =0x65;
  count =0;
//sei(); 

while (1)
{
PORTB  |= (0<<PB4)|(1<<PB7);
PORTG  |= (0<<PG3)|(1<<PG4);
com_send(data);
_delay_ms(500);
calibrate_rco();
}

}

ISR(PCINT0_vect)
{
	count++;


}
/*!
 *******************************************************************************
 * control motor movement
 *
 * \param  direction motordirection
 *         - stop
 *         - open
 *         - close
 *
 * \note PWM runs at 15,625 kHz
 *
 * \note Output for direction: \verbatim
     direction  PG3  PG4  PB7  PB4/PWM(OC0A)    PE3    PCINT4
       stop:     0    0    0    0                0      off
       open:     0    1    1   invert. mode      1      on
       close:    1    0    0   non inv mode      1      on       \endverbatim
 ******************************************************************************/