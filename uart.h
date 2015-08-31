/*
 * uart.h
 *
 * Created: 20-6-2015 17:37:42
 *  Author: Jeroen
 */ 

//! HR20 runs on 4MHz
#ifndef F_CPU
#define F_CPU 4000000UL
#endif

#include <avr/io.h>


void init_uart (int Baudrate, char AsyncDoubleSpeed);
void com_send(unsigned char);
unsigned char com_recieve (void);



