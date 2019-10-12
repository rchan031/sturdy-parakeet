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
enum States {initialState, light1, light2} state;

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF; //input
     
    DDRB = 0xFF; PORTB = 0x01; //output
    
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
			state = light1;
			break;
		case light1:
			if((PINA & 0x01) == 0x01) { //button press triggers if
				state = light2;
			}
			else {
				state = light1;
			}
			break;
		case light2:
			if((PINA & 0x01) == 0x01) {
				state = light1;
			}
			else {
				state = light2;
			}
			break;
		default:
			state = initialState;
			break;
	}
		
		switch(state) {
			case light1:
				PORTB = 0x01;
				break;
			case light2:
				PORTB = 0x02;
				break;
			default:
				break;
		}
}
			
