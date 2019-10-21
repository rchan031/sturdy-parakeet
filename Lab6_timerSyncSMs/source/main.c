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
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {initialState, first, second, third, pressed} state;
unsigned char output = 0x00;
unsigned char flag = 0x00;
volatile unsigned char TimerFlag = 0; 
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

void TimerOn() {
	TCCR1B = 0x0B;
	OCR1A = 125;
	TIMSK1 = 0x02;
	TCNT1 = 0;
	_avr_timer_cntcurr = _avr_timer_M;
	SREG |= 0x80;
}

void TimerOff() {
	TCCR1B = 0x00;
}

void TimerISR() {
	TimerFlag = 1;
}

ISR(TIMER1_COMPA_vect) {
	_avr_timer_cntcurr--;
	if(_avr_timer_cntcurr == 0) {
		TimerISR();
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

void tickFct() {
	switch(state) {
		case initialState:
			state = first;
			break;
		case first:
			state = second;
			if(((~PINA & 0x01) == 0x01) && (flag == 0x00)) {
				state = pressed;
				flag = 0x01;
			}
			break;
		case second:
			state = third;
			if(((~PINA & 0x01) == 0x01) && (flag == 0x00)) {
				state = pressed;
				flag = 0x01;
			}
			break;
		case third:
			state = first;
			if(((~PINA & 0x01) == 0x01) && (flag == 0x00)) {
				state = pressed;
				flag = 0x01;
			}
			break;
		case pressed:
			if((PINA & 0xFF) == 0xFF) {
				flag = 0x00;
			}
			if(((~PINA & 0x01) == 0x01) && (flag == 0x00)) {
				state = first;
			}
			else {
				state = pressed;
			}
			break;
		default:
			state = initialState;
			break;
	}
	switch(state) {
		case initialState:
			break;
		case first:
			output = 0x01;
			break;
		case second:
			output = 0x02;
			break;
		case third:
			output = 0x04;
			break;
		case pressed:
			break;
		default:
			break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA =0xFF;
	DDRC = 0xFF; PORTC = 0x00; 
	TimerSet(300);
	TimerOn();
	
	state = initialState;
    /* Insert your solution below */
    while (1) {
		tickFct();
		PORTC = output;
		while(!TimerFlag);
			TimerFlag = 0x00;
    }
    return 1;
}
