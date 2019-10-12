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
enum States {initialState, wait, increment, decrement, reset} state;

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF; //input
     
    DDRB = 0xFF; PORTB = 0x01; //output
    
    DDRC = 0xFF; PORTC = 0x07; //output
    
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
			state = wait;
			break;
		case wait:
			if((PINA & 0x03) == 0x03) {
				state = reset;
			}
			else if((PINA & 0x01) == 0x01) {
				state = increment;
			}
			else if((PINA & 0x02) == 0x02) {
				state = decrement;
			}
			
			break;
		case increment:
			state = wait;
			break;
		case decrement:
			state = wait;
			break;
		case reset:
			PORTC = 0x07;
			state = wait;
			break;
		default:
			state = initialState;
			break;
	}
		
		switch(state) {
			case initialState:
				PORTC = 0x07;
				break;
			case wait:
				break;
			case increment:
				if(PORTC < 0x09) {
					PORTC++;
				}
				break;
			case decrement:
				if(PORTC > 0x00) {
					PORTC = PORTC - 1;
				}
				break;
			case reset:
				PORTC = 0x07;
				break;
			
			default:
				PORTC = 0x07;
				break;
		}
}
			
