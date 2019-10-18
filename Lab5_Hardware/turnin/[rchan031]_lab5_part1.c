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

	unsigned char output = 0x00;
    /* Insert your solution below */
   PORTC = 0x00;
   
    while (1) {
		//PORTC = 0;
		//
		if((~PINA & 0x00) == 0x00) {
			output = 0x40;
		}
		if((~PINA & 0x01) == 0x01) {
			output = 0x60;
		}
		if((~PINA & 0x02) == 0x02) {
			output = 0x60;
		}
		if((~PINA & 0x03) == 0x03) {
			output = 0x70;
		}
		if((~PINA & 0x04) == 0x04) {
			output = 0x70;
		}
		if((~PINA & 0x05) == 0x05) {
			output = 0x38;
		}
		if((~PINA & 0x06) == 0x06) {
			output = 0x38;
		}
		if((~PINA & 0x07) == 0x07) {
			output = 0x3C;
		}
		if((~PINA & 0x08) == 0x08) {
			output = 0x3C;
		}
		if((~PINA & 0x09) == 0x09) {
			output = 0x3C;
		}
		if((~PINA & 0x0A) == 0x0A) {
			output = 0x3E;
		}
		if((~PINA & 0x0B) == 0x0B) {
			output = 0x3E;
		}
		if((~PINA & 0x0C) == 0x0C) {
			output = 0x3E;
		}
		if((~PINA & 0x0D) == 0x0D) {
			output = 0x3F;
		}
		if((~PINA & 0x0E) == 0x0E) {
			output = 0x3F;
		}
		if((~PINA & 0x0F) == 0x0F) {
			output = 0x3F;
		}
		PORTC = output;
		output = 0;
	}
    return 1;
}
