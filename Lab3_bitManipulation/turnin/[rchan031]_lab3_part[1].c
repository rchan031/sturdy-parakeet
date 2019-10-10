/*	Author: rchan031
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;  //Configure port A's 8 pins as inputs
    DDRB = 0x00; PORTB = 0xFF; //Configuring port B's 8 pins as inputs
    DDRC = 0xFF; PORTC = 0x00; //Configuring port c's 8 pins as outputs, init 0s

	unsigned char count = 0;
	unsigned char numBits = 0x00;
	
    /* Insert your solution below */
   
    while (1) {
		PORTC = 0;
		if(PINA & 0x01) {
			PORTC++;
		}
		if(PINA & 0x02) {
			PORTC++;
		}
		if(PINA & 0x04) {
			PORTC++;
		}
		if(PINA & 0x08) {
			PORTC++;
		}
		if(PINA & 0x10) {
			PORTC++;
		}
		if(PINA & 0x20) {
			PORTC++;
		}
		if(PINA & 0x40) {
			PORTC++;
		}
		if(PINA & 0x80) {
			PORTC++;
		}
		
		if(PINB & 0x01) {
			PORTC++;
		}
		if(PINB & 0x02) {
			PORTC++;
		}
		if(PINB & 0x04) {
			PORTC++;
		}
		if(PINB & 0x08) {
			PORTC++;
		}
		if(PINB & 0x10) {
			PORTC++;
		}
		if(PINB & 0x20) {
			PORTC++;
		}
		if(PINB & 0x40) {
			PORTC++;
		}
		if(PINB & 0x80) {
			PORTC++;
		}
		
	}
	
    return 1;
}
