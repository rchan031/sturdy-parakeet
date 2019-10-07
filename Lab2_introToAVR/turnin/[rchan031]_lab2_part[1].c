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
  DDRA = 0x00; PORTA = 0xFF;  //Configure port A's 8 pins as inputs
  DDRB = 0xFF; PORTB = 0x00; //Configure port B's 8 pins as outputs, init 0's
                             

 
   while (1) {
     if(PINA == 0x00){
		 PORTB = 0;
		}
	else if(PINA == 0x01) {
		PORTB = 1;
		}
	else if(PINA == 0x02) {
		PORTB = 0;
		}
	else {
		PORTB = 0;
		}
	}
   return 0;
}
