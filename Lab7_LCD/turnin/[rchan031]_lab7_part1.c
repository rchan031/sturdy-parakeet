#include <avr/io.h>
#include <io.h>
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

enum States {initialState, wait, increment, decrement, reset} state;
unsigned char output = 0x07;

void tickFct() {
	switch(state) {
		case initialState:
			state = wait;
			break;
		case wait:
			if((~PINA & 0x03) == 0x03) {
				state = reset;
			}
			else if((~PINA & 0x01) == 0x01) {
				state = increment;
			}
			else if((~PINA & 0x02) == 0x02) {
				state = decrement;
			}
			break;
		case reset:
			state = wait;
			break;
		case increment:
			state = wait;
			break;
		case decrement:
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
			if(output < 0x09) {
				output = output + 1;
			}
			break;
		case decrement:
			if(output > 0x00) {
				output = output - 1;
			}
			break;
		case reset:
			output = 0x00;
			break;
		default:
			break;
	}
}

int main(void){
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	TimerSet(100);
	TimerOn();
	
	state = initialState;
	output = 0x07;
	LCD_init();
	
	while(1) {
		tickFct();
		LCD_Cursor(1);
		LCD_WriteData(output + '0');
		while(!TimerFlag);
			TimerFlag = 0x00;
	}
	return 1;
}

