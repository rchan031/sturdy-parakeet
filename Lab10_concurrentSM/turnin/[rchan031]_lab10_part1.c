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

volatile unsigned char TimerFlag = 0;

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

void TimerOn(){
	TCCR1B = 0x0B;
	OCR1A = 125;
	TIMSK1 = 0x02;
	TCNT1 = 0;
	_avr_timer_cntcurr = _avr_timer_M;
	SREG |= 0x80;
}

void TimerOff(){
	TCCR1B = 0x00;
}

void TimerISR(){
	TimerFlag = 1;
}

ISR(TIMER1_COMPA_vect){
	_avr_timer_cntcurr--;
	if (_avr_timer_cntcurr == 0){
		TimerISR();
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

void TimerSet(unsigned long M){
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

unsigned char threeLEDs = 0x00;
unsigned char blinkingLED = 0x00;

enum States {initialState, state1, state2, state3} state;
void ThreeLEDsSM() {
	switch(state) {
		case initialState:
			state = state1;
			break;
		case state1:
			state = state2;
			break;
		case state2:
			state = state3;
			break;
		case state3:
			state = state1;
			break;
		default:
			state = initialState;
			break;
	}
	switch(state) {
		case initialState:
			break;
		case state1:
			threeLEDs = 0x01;
			break;
		case state2:
			threeLEDs = 0x02;
			break;
		case state3:
			threeLEDs = 0x04;
			break;
		default:
			break;
	}
}
enum States2{initial, blinkState1, blinkState2} blinkState;
void BlinkingLEDSM() {
	switch(blinkState) {
		case initial:
			blinkState = blinkState1;
			break;
		case blinkState1:
			blinkState = blinkState2;
			break;
		case blinkState2:
			blinkState = blinkState1;
			break;
		default:
			break;
	}
	switch(blinkState) {
		case initial:
			break;
		case blinkState1:
			blinkingLED = 0x08;
			break;
		case blinkState2:
			blinkingLED = 0x00;
			break;
		default:
			break;
	}
}

enum States3{combineState} combstate;
void CombineLEDsSM() {
	switch(combstate) {
		case combineState:
			break;
	}
	switch(combstate) {
		case combineState:
			PORTB = threeLEDs + blinkingLED;
			break;
	}
}
		
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF; PORTB = 0x00;
	DDRA = 0xFF; PORTA = 0x00;
	TimerSet(1000);
	TimerOn();
    /* Insert your solution below */
    state = initialState;
    blinkState = initial;
    combstate = combineState;
    while (1) {
		ThreeLEDsSM();
		BlinkingLEDSM();
		//PORTB = threeLEDs + blinkingLED;
		CombineLEDsSM();
		while(!TimerFlag);
		TimerFlag = 0;
    }
    return 1;
}
