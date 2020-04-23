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
//Demo Video Link: https://www.youtube.com/watch?v=Nn1w--wIxxo
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;
	PORTA = 0xFF;
	//DDRB = 0x00;
	//PORTB = 0xFF;
	DDRC = 0xFF;
	PORTC = 0x00;
	unsigned char gas, tmpA, tmpC, b0, b1, b2, b3;
    /* Insert your solution below */
    while (1) {
	tmpA = ~PINA;
	b0 = PINA & 0x01;
	b1 = PINA & 0x02;

	gas = tmpA & 0x0F;
	//tmpB = PINB;
	tmpC = 0x00;
	switch(gas){
		case 0:
			tmpC = tmpC | 0x40;
			break;
		case 1:
		case 2:
			tmpC = tmpC | 0x60;
			break;
		case 3:
		case 4:
			tmpC = tmpC | 0x70;
			break;
		case 5:
		case 6:
			tmpC = tmpC | 0x38;
			break;
		case 7:
		case 8:
		case 9:
			tmpC = tmpC | 0x3C;
			break;
		case 10:
		case 11:
		case 12:
			tmpC = tmpC | 0x3E;
			break;
		case 13:
		case 14:
		case 15:
			tmpC = tmpC | 0x3F;
			break;
		default:
			tmpC = 0x00;
			break;
	}
	PORTC = tmpC;
    }
    return 1;
}

/*
int main(void) {
    /* Insert DDR and PORT initializations */
/*	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	unsigned char led = 0x00;
	unsigned char b0 = 0x00;
	unsigned char b1 = 0x00;
	unsigned char b2 = 0x00;
	unsigned char b3 = 0x00;
    /* Insert your solution below */
/*    while (1) {
	b0 = ~PINA & 0x01;
	b1 = ~PINA & 0x02;
	b2 = ~PINA & 0x04;
	b3 = ~PINA & 0x08;
	if((b0 && !b1 && !b2 && !b3) || (!b0 && b1 && !b2 && !b3))
		led = 0x60;
	else if((b0 && b1 && !b2 && !b3) || (!b0 && !b1 && b2 && !b3))
		led = 0x70;
	else if((b0 && !b1 && b2 && !b3) || (!b0 && b1 && b2 && !b3))
		led = 0x38;
	else if((b0 && b1 && b2 & !b3) || (!b0 && !b1 && !b2 && b3) || (b0 && !b1 && !b2 && b3))
		led = 0x3C;
	else if((!b0 && b1 && !b2 && b3) || (b0 && b1 && !b2 && b3) || (!b0 && !b1 && b2 && b3))
		led = 0x3E;
	else if((b0 && !b1 && b2 && b3) || (!b0 && b1 && b2 && b3) || (b0 && b1 && b2 && b3))
		led = 0x3F;
	if(!b0 && !b1 && !b2 && !b3)
		led = 0x40;

	PORTC = led;
    }
    return 1;
}*/
