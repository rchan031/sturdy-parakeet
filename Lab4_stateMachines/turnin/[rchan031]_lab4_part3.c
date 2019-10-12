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
void tickFct();
enum States {initialState, locked, s1, s2} state;

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF; //input
     
    DDRB = 0xFF; PORTB = 0x00; //output
    
    DDRC = 0xFF; PORTC = 0x00; //output
    
	state = initialState;
	
    /* Insert your solution below */
    while (1) {
		tickFct();
    }
    return 1;
}

void tickFct() {
	switch(state) {
		case initialState:
			state = locked;
			break;
		case locked:
			if(PINA == 0x04) {
				state = s1;
			}
			else {
				state = locked;
			}
			break;
		case s1:
			if(PINA == 0x02) {
				state = s2;
			}
			else {
				state = locked;
			}
			break;
		case s2:
			if(PINA == 0x08) {
				state = locked;
			}
			else {
				state = s2;
			}
			break;
		default:
			state = initialState;
			break;
	}
		
		switch(state) {
			case initialState:
				break;
			case locked:
				PORTB = 0x00;
				break;
			case s1:
				PORTB = 0x00;
				break;
			case s2:
				PORTB = 0x01;
				break;
			
			default:
				PORTB = 0x00;
				break;
		}
}
			
