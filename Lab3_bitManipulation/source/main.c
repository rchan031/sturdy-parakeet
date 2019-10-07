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
    
    DDRC = 0xFF; PORTC = 0x00; //Configuring port c's 8 pins as outputs

    /* Insert your solution below */
    while (1) {
		char counter = 0;
		//char counter2 = 0;
		char numBits = 0;
		while(counter < 8) {
			if((PINA & 0x80) == 0x80) {
				PORTC = PORTC + 1;
				PINA = PINA << 1;
			}
			if((PINB & 0x80) == 0x80) {
				PORTC = PORTC + 1;
				PINB = PINB << 1;
			}
			counter = counter + 1;
		}
		//PORTC = numBits;
	}
    return 1;
}
