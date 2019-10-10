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

	unsigned char counter = 0;
	
	unsigned char mask = 0x01;
    /* Insert your solution below */
    while (1) {
		while(counter < 8) {
			//inputA = PINA;
			if(PINA & mask) {
				PORTC++;
			}
			mask = mask << 1;
			counter++;
		}
	}
    return 0;
}
