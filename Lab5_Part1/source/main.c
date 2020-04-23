/*	Author: lab
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
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	unsigned char led = 0x00;
	unsigned char b0 = 0x00;
	unsigned char b1 = 0x00;
	unsigned char b2 = 0x00;
	unsigned char b3 = 0x00;
    /* Insert your solution below */
    while (1) {
	b0 = ~PINA & 0x01;
	b1 = ~PINA & 0x02;
	b2 = ~PINA & 0x04;
	b3 = ~PINA & 0x08;
	if((b0 && !b1 && !b2 && !b3) || (!b0 && b1 && !b2 && !b4))
		led = 0x60;
	if((b0 && b1 && !b2 && !b3) || (!b0 && !b1 && b2 && !b4))
		led = 0x70;
	if((b0 && !b1 && b2 && !b3) || (!b0 && b1 && b2 && !b3))
		led = 0x38;
	if((b0 && b1 && b2 & !b3) || (!b0 && !b1 && !b2 && b3) || (b0 && !b1 && !b2 && b3)
		led = 0x3C;
	if((!b0 && b1 && !b2 && b3) || (b0 && b1 && !b2 && b3) || (!b0 && !b1 && b2 && b3))
		led = 0x3E;
	if((b0 && !b1 && b2 && b3) || (!b0 && b1 && b2 && b3) || (b0 && b1 && b2 && b3))
		led 0x3F;
		PORTB = led;
    }
    return 1;
}
