/*
 * main.h
 *
 * Created: 20-6-2015 17:40:46
 *  Author: Jeroen
 */ 

//! HR20 runs on 4MHz
#ifndef F_CPU
#define F_CPU 4000000UL
#endif

// standard includes
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// program includes
#include "uart.h"


