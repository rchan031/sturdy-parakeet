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
unsigned char output = 0x00; 
unsigned char flag = 0x00;

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF; //input
    DDRC = 0xFF; PORTC = 0x00; //output
   
	state = initialState;
	
	output = 0x07;
    /* Insert your solution below */
    while (1) {
		tickFct();
		PORTC = output;
    }
    return 1;
}


void tickFct() {
	switch(state) {
		case initialState:
			state = wait;
			break;
		case wait:
			if((PINA & 0xFF) == 0xFF && (flag == 0x01)) {
				flag = 0x00;
			}
			if((~PINA & 0x03) == 0x03) {
				state = reset;
			}
			else if((~PINA & 0x01) == 0x01) {
				state = increment;
			}
			else if((~PINA & 0x02) == 0x02) {
				state = decrement;
			}
			else {
				state = wait;
			}
			break;
		case increment:
			state = wait;
			break;
		case decrement:
			state = wait;
			break;
		case reset:
			state = wait;
			break;
		default:
			state = initialState;
			break;
	}
		
		switch(state) {
			case initialState:
				break;
			case wait:
				break;
			case increment:
				if((output < 0x09) && (flag != 0x01)) {
					output = output + 1;
					flag = 0x01;
				}
				break;
			case decrement:
				if((output > 0x00) && (flag != 0x01)) {
					output = output - 1;
					flag = 0x01;
				}
				break;
			case reset:
				output = 0x00;
				break;
			
			default:
				output = 0x07;
				break;
		}
}

