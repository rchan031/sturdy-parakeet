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

void set_PWM(double frequency) {
	static double current_frequency;
	if(frequency != current_frequency) {
		if(!frequency) { TCCR3B &= 0x08; }
		else { TCCR3B |= 0x03; }
		if(frequency < 0.954) { OCR3A = 0xFFFF;}
		else if(frequency > 31250) { OCR3A = 0x0000;}
		else { OCR3A = (short)(8000000 / (128 * frequency)) - 1; }
		TCNT3 = 0;
		current_frequency = frequency;
	}
}

void PWM_on() {
	TCCR3A = (1 << COM3A0);
	TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
	set_PWM(0);
}

void PWM_off() {
	TCCR3A = 0x00;
	TCCR3B = 0x00;
}

enum States {initialState, wait, C, D, E, F, G, A, B, C2} state;
unsigned char button = 0x00;
unsigned char scaleCounter = 0x00;
unsigned char on = 0x00;
void tickFct() {
	button = (~PINA & 0x07);
	switch(state) {
		case initialState:
			state = wait;
			break;
		case wait:
			if((button == 0x01) && (on == 0x00)) { //turns on if off
				PWM_on();
				on = 0x01;
				state = wait;
			}
			else if((button == 0x01) && (on == 0x01)) { //turns off if on
				PWM_off();
				on = 0x00;
				state = wait;
			}
			
			if((button == 0x02) && (on == 0x01)) { //if on, increment scaleCounter when 0x02
				if(scaleCounter < 8) {
					scaleCounter++;
				}
			}
			else if((button == 0x04) && (on == 0x01)) { //if on, decrement scaleCounter when 0x04
				if(scaleCounter > 1) { //don't want to hit 0, otherwise it would be init value and could cause error
					scaleCounter--;
				}
			}
			
			if((button == 0x02) && (scaleCounter == 1)) {
				state = C;
			}
			else if((button == 0x02) && (scaleCounter == 2)) {
				state = D;
			}
			else if((button == 0x02) && (scaleCounter == 3)) {
				state = E;
			}
			else if((button == 0x02) && (scaleCounter == 4)) {
				state = F;
			}
			else if((button == 0x02) && (scaleCounter == 5)) {
				state = G;
			}
			else if((button == 0x02) && (scaleCounter == 6)) {
				state = A;
			}
			else if((button == 0x02) && (scaleCounter == 7)) {
				state = B;
			}
			else if((button == 0x02) && (scaleCounter == 8)) {
				state = C2;
			}
			
			if((button == 0x04) && (scaleCounter == 1)) { //if I decrement at scale D, it should move to scale C; otherwise, should stay at scale C
				state = C;
			}
			else if((button == 0x02) && (scaleCounter == 2)) {
				state = D;
			}
			else if((button == 0x02) && (scaleCounter == 3)) {
				state = E;
			}
			else if((button == 0x02) && (scaleCounter == 4)) {
				state = F;
			}
			else if((button == 0x02) && (scaleCounter == 5)) {
				state = G;
			}
			else if((button == 0x02) && (scaleCounter == 6)) {
				state = A;
			}
			else if((button == 0x02) && (scaleCounter == 7)) {
				state = B;
			}
			else if((button == 0x02) && (scaleCounter == 8)) {
				state = C2;
			}
			break;
		case C:
			state = wait;
			break;
		case D:
			state = wait;
			break;
		case E:
			state = wait;
			break;
		case F:
			state = wait;
			break;
		case G:
			state = wait;
			break;
		case A:
			state = wait;
			break;
		case B:
			state = wait;
			break;
		case C2:
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
		case C:
			set_PWM(261.63);
			break;
		case D:
			set_PWM(293.66);
			break;
		case E:
			set_PWM(329.63);
			break;
		case F:
			set_PWM(349.23);
			break;
		case G:
			set_PWM(392.00);
			break;
		case A:
			set_PWM(440.00);
			break;
		case B:
			set_PWM(493.88);
			break;
		case C2:
			set_PWM(523.25);
			break;
		default:
			break;
	}
}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
	state = initialState;
	while(1) {
		tickFct();
	}
    return 1;
}

