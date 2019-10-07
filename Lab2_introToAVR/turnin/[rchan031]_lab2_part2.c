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
  DDRC = 0xFF; PORTC = 0x00; //Configure port B's 8 pins as outputs, init 0's
  
  unsigned char cntavail;

 
   while (1) {
     if(PINA == 0x00) {
		 PORTC = 0x04;
	 }
	 else if (PINA == 0x01 || PINA == 0x02 || PINA == 0x04 || PINA == 0x08) {
		 PORTC = 0x03;
	 }
	 else if (PINA == 0x0C || PINA == 0x0A || PINA == 0x09 || PINA == 0x06 || PINA == 0x05 || PINA == 0x03) {
		 PORTC = 0x02;
	 }
	 else if (PINA == 0x0E || PINA == 0x0B || PINA == 0x0D || PINA == 0x07) {
		 PORTC = 0x01;
	 }
	else {
		PORTC = 0x00;
	}
}
   return 0;
}
