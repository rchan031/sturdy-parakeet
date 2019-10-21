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
enum States {initialState, wait, transition} state;
unsigned char output = 0x00;
unsigned char flag = 0x00;

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF; //input
    DDRC = 0xFF; PORTC = 0x00; //output
   
	state = initialState;
	
	output = 0x01;
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
			if((PINA & 0xFF == 0xFF) && (flag == 0x01)) {
				flag = 0x00;
			}
			if(~PINA & 0x01 == 0x01) {
				state = transition;
			}
			else {
				state = wait;
			}
			break;
		case transition:
			state = wait;
			break;
	}
		switch(state) {
			case initialState:
				output = 0x01;
				break;
			case wait:
				break;
			case transition:
				if((output == 0x01) && (flag != 0x01)) {
					output = 0x40;
					flag = 0x01;
				}
				else if((output == 0x40) && (flag != 0x01))  {
					output = 0x02;
					flag = 0x01;
				}
				else if((output == 0x02) && (flag != 0x01)) {
					output = 0x20;
					flag = 0x01;
				}
				else if((output == 0x20) && (flag != 0x01)) {
					output = 0x04;
					flag = 0x01;
				}
				else if((output == 0x04) && (flag != 0x01)) {
					output = 0x10;
					flag = 0x01;
				}
				else if((output == 0x10) && (flag != 0x01)) {
					output = 0x08;
					flag = 0x01;
				}
				else if((output == 0x08) && (flag != 0x01)) {
					output = 0x01;
					flag = 0x01;
				}
				break;
			default:
				output = 0x01;
				break;
		}
}

