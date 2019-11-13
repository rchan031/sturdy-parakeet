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

void ADC_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}

int main(void) {
    /* Insert DDR and PORT initializations */
    unsigned short x = 0x00;
	unsigned short MAX = 0x00;
    unsigned char output1 = 0x00;
    unsigned char output2 = 0x00;
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0xFF; PORTD = 0x00;

	MAX = 0x11F;
	ADC_init();
    /* Insert your solution below */
    while (1) {
		x = ADC;
		if(x >= MAX/2) {
			PORTB = 0x01;
		}
		else if(x < MAX/2) {
			PORTB = 0x00;	
		}
    }
    return 1;
}
