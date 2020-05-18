/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
//LINK: https://www.youtube.com/watch?v=adcrMYMHbwk
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

void ADC_init(){
	ADCSRA = (1<<ADEN) | (1<<ADSC) | (1<<ADATE);
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; 
	PORTA = 0xFF;
	DDRB = 0xFF;
	PORTB = 0x00;
	DDRD = 0xFF;
	PORTD = 0x00;
	unsigned short a,b;
	unsigned char B;
	const unsigned short MAX = 550;
	const unsigned short MIN = 255;
	ADC_init();
    /* Insert your solution below */
    while (1) {
	a = ADC;
	b = MAX/8;
	B = 0;
	if(a <= MIN)
		B = 0;
	if(a > MIN)
		B = 1;
	if(a > (b + MIN))
		B = 2|B;
	if(a > (2*b + MIN))
		B = 4|B;
	if(a > (3*b + MIN))
		B = 8|B;
	if(a > (4*b + MIN))
		B = 16|B;
	if(a > (5*b + MIN))
		B = 32|B;
	if(a > (6*b + MIN))
		B = 64|B;
	if(a > (7*b + MIN))
		B = 128|B;

	PORTB = B;
	//PORTD = tmpD;
    }
    return 1;
}
