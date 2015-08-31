/*
 * uart.c
 *
 * Created: 20-6-2015 17:37:26
 *  Author: Jeroen
 */ 


#include "main.h"
#include "uart.h"
#include <math.h>
#ifndef F_CPU
#define F_CPU 1000000UL
#endif

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
void init_uart (int Baudrate, char AsyncDoubleSpeed)
{
	// Set baud rate
	uint16_t UBBR_val = lrint ((F_CPU / (16L * Baudrate)) - 1);
	UBRR0H = (unsigned char)(UBBR_val>>8);
	UBRR0L = (unsigned char)UBBR_val;
	// Enable double speed mode if requested
	if (AsyncDoubleSpeed == 1) UCSR0A = (1<<U2X0);
	//Set frame format: 8data, 1stop bit, set parity to even.
	UCSR0C |= (1<<USBS0)|(2<<UCSZ00)|(1<<UPM01);
	// Enable receiver and transmitter
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	UCSR0C = (1<<UPM00);
}


/*****************************************************************************
*
*   Function name : Usart_Tx
*
*   Returns :       None
*
*   Parameters :    char data: byte to send
*
*   Purpose :       Send one byte through the USART
*
*****************************************************************************/
void com_send( unsigned char data)
{
	
	//Wait until the Transmitter is ready
	while (! (UCSR0A & (1 << UDRE0)) );
	//Get that data outa here!
	UDR0 = data;
}


/*****************************************************************************
*
*   Function name : Usart_Rx
*
*   Returns :       char: byte received
*
*   Parameters :    None
*
*   Purpose :       Receives one byte from the USART
*
*****************************************************************************/
unsigned char com_recieve(void)
{
	while (!(UCSR0A & (1<<RXC0)));
	return UDR0;
}

